#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "main.h"   // struct Producao e defines como NUM_PRODUCOES, MAX_NOME etc.

#define MAX_DICAS 10
#define MAX_TAM_DICA 200
#define LINHA_MAX 2048

// ------------------------------------------------------------
// Protótipos locais
// ------------------------------------------------------------
int existeBinario(void);
void listarDoCSV(void);
void listarDoBIN(void);
void carregarCSVmemoria(Producao p[], int *total);
void carregarBINmemoria(Producao p[], int *total);
void salvarBIN(Producao p[], int total);
void confirmarESalvar(Producao p[], int total, int *houveAlteracao);
void liberarProducao(Producao *p);

// ------------------------------------------------------------
// Verifica existencia do binario
// ------------------------------------------------------------
int existeBinario(void) {
    FILE *f = fopen("filmes.bin", "rb");
    if (f) { fclose(f); return 1; }
    return 0;
}

// ------------------------------------------------------------
// LISTAR — lê direto do CSV (sem tocar em memória do jogo)
// ------------------------------------------------------------
void listarDoCSV(void) {
    FILE *csv = fopen("filmes.csv", "r");
    if (!csv) {
        printf("\nCSV não encontrado.\n");
        return;
    }

    char linha[LINHA_MAX];

    printf("\n%-10s | %-40s | %-5s | %-5s\n", "TIPO", "NOME", "DICAS", "DIF");
    printf("--------------------------------------------------------------------------\n");

    while (fgets(linha, sizeof(linha), csv)) {
        linha[strcspn(linha, "\r\n")] = '\0';

        // tokeniza localmente (cópia porque strtok altera)
        char tmp[LINHA_MAX];
        strncpy(tmp, linha, LINHA_MAX - 1);
        tmp[LINHA_MAX - 1] = '\0';

        char *token = strtok(tmp, ",");
        if (!token) continue;

        int tipo = atoi(token);

        token = strtok(NULL, ",");
        char nome[MAX_NOME];
        if (token) strncpy(nome, token, MAX_NOME - 1);
        else nome[0] = '\0';
        nome[MAX_NOME - 1] = '\0';

        int totalDicas = 0;
        for (int i = 0; i < 10; i++) {
            token = strtok(NULL, ",");
            if (token && strlen(token) > 0) totalDicas++;
        }

        token = strtok(NULL, ",");
        int dif = token ? atoi(token) : 0;

        printf("%-10s | %-40s | %-5d | %-5d\n",
               (tipo == 1) ? "Filme" : "Serie",
               nome,
               totalDicas,
               dif);
    }

    fclose(csv);
}

// ------------------------------------------------------------
// LISTAR — lê direto do BIN (sem tocar em memória do jogo)
// ------------------------------------------------------------
void listarDoBIN(void) {
    FILE *f = fopen("filmes.bin", "rb");
    if (!f) {
        printf("\nfilmes.bin não encontrado.\n");
        return;
    }

    int total = 0;
    if (fread(&total, sizeof(int), 1, f) != 1) {
        printf("\nArquivo binário vazio ou corrompido.\n");
        fclose(f);
        return;
    }

    if (total == 0) {
        printf("\nNenhuma produção salva no BIN.\n");
        fclose(f);
        return;
    }

    printf("\n%-10s | %-40s | %-5s | %-5s\n", "TIPO", "NOME", "DICAS", "DIF");
    printf("--------------------------------------------------------------------------\n");

    for (int i = 0; i < total; i++) {
        int tipo;
        fread(&tipo, sizeof(int), 1, f);

        int tamNome = 0;
        fread(&tamNome, sizeof(int), 1, f);
        char nome[MAX_NOME];
        if (tamNome > 0 && tamNome < MAX_NOME) {
            if (fread(nome, sizeof(char), tamNome, f) != (size_t)tamNome) {
                // leitura incompleta -> abortar
                nome[0] = '\0';
            }
            nome[tamNome - 1] = '\0';
        } else {
            // pula se tamanho inválido
            if (tamNome > 0) fseek(f, tamNome, SEEK_CUR);
            nome[0] = '\0';
        }

        int totalDicas = 0;
        if (fread(&totalDicas, sizeof(int), 1, f) != 1) totalDicas = 0;
        for (int d = 0; d < totalDicas; d++) {
            int tam;
            if (fread(&tam, sizeof(int), 1, f) != 1) break;
            if (tam > 0) {
                // pular bytes da dica
                fseek(f, tam, SEEK_CUR);
            }
        }

        int dificuldade = 0;
        fread(&dificuldade, sizeof(int), 1, f);

        printf("%-10s | %-40s | %-5d | %-5d\n",
               (tipo == 1) ? "Filme" : "Serie",
               nome,
               totalDicas,
               dificuldade);
    }

    fclose(f);
}

// ------------------------------------------------------------
// CARREGAR CSV para memória (aloca nomeProducao e dicas corretamente)
// p[] deve ter espaço suficiente (caller passa array com NUM_PRODUCOES)
// ------------------------------------------------------------
void carregarCSVmemoria(Producao p[], int *total) {
    *total = 0;
    FILE *csv = fopen("filmes.csv", "r");
    if (!csv) return;

    char linha[LINHA_MAX];
    while (fgets(linha, sizeof(linha), csv)) {
        if (*total >= NUM_PRODUCOES) {
            // prevenindo overflow do array passado pelo caller
            printf("Aviso: atingido limite NUM_PRODUCOES ao carregar CSV.\n");
            break;
        }

        linha[strcspn(linha, "\r\n")] = '\0';
        char tmp[LINHA_MAX];
        strncpy(tmp, linha, LINHA_MAX - 1);
        tmp[LINHA_MAX - 1] = '\0';

        char *token = strtok(tmp, ",");
        if (!token) continue;

        // tipo
        p[*total].tipoProducao = atoi(token);

        // nome (aloca dinamicamente)
        token = strtok(NULL, ",");
        if (token && strlen(token) > 0) {
            p[*total].nomeProducao = (char *)malloc(strlen(token) + 1);
            if (!p[*total].nomeProducao) { p[*total].nomeProducao = NULL; }
            else strcpy(p[*total].nomeProducao, token);
        } else {
            p[*total].nomeProducao = (char *)malloc(1);
            if (p[*total].nomeProducao) p[*total].nomeProducao[0] = '\0';
        }

        // aloca array de ponteiros para dicas
        p[*total].dicas = (char **)malloc(sizeof(char *) * MAX_DICAS);
        if (!p[*total].dicas) {
            // alocação falhou — garantir estado consistente
            p[*total].dicas = NULL;
            p[*total].totalDicas = 0;
        } else {
            p[*total].totalDicas = 0;
            for (int j = 0; j < MAX_DICAS; j++) p[*total].dicas[j] = NULL;

            for (int j = 0; j < MAX_DICAS; j++) {
                token = strtok(NULL, ",");
                if (token && strlen(token) > 0) {
                    p[*total].dicas[j] = (char *)malloc(strlen(token) + 1);
                    if (p[*total].dicas[j]) {
                        strcpy(p[*total].dicas[j], token);
                        p[*total].totalDicas++;
                    }
                } else {
                    // se token é NULL ou vazio, cria string vazia para consistência
                    if (token) {
                        p[*total].dicas[j] = (char *)malloc(1);
                        if (p[*total].dicas[j]) p[*total].dicas[j][0] = '\0';
                    } else {
                        p[*total].dicas[j] = (char *)malloc(1);
                        if (p[*total].dicas[j]) p[*total].dicas[j][0] = '\0';
                    }
                }
            }
        }

        // dificuldade (último campo)
        token = strtok(NULL, ",");
        p[*total].dificuldade = token ? atoi(token) : 0;

        (*total)++;
    }

    fclose(csv);
}

// ------------------------------------------------------------
// CARREGAR BIN para memória (aloca nomeProducao e dicas corretamente)
// p[] deve ter espaço suficiente (caller passa array com NUM_PRODUCOES)
// ------------------------------------------------------------
void carregarBINmemoria(Producao p[], int *total) {
    *total = 0;

    FILE *f = fopen("filmes.bin", "rb");
    if (!f) return;

    int n = 0;
    if (fread(&n, sizeof(int), 1, f) != 1) {
        fclose(f);
        return;
    }

    if (n < 0) { fclose(f); return; }

    // if (n > NUM_PRODUCOES) {
    //     // não podemos ler mais que o array suporta
    //     printf("Aviso: binário contém mais produções (%d) do que NUM_PRODUCOES (%d). Lendo até o limite.\n", n, NUM_PRODUCOES);
    //     n = NUM_PRODUCOES;
    // }

    for (int i = 0; i < n; i++) {
        // inicializar
        p[i].nomeProducao = NULL;
        p[i].dicas = NULL;
        p[i].totalDicas = 0;
        p[i].dificuldade = 0;
        p[i].tipoProducao = 0;

        // tipo
        fread(&p[i].tipoProducao, sizeof(int), 1, f);

        // nome
        int tamNome = 0;
        fread(&tamNome, sizeof(int), 1, f);
        if (tamNome > 0) {
            p[i].nomeProducao = (char *)malloc(tamNome);
            if (p[i].nomeProducao) {
                fread(p[i].nomeProducao, sizeof(char), tamNome, f);
                p[i].nomeProducao[tamNome - 1] = '\0';
            } else {
                // se malloc falhar, pular leitura
                fseek(f, tamNome, SEEK_CUR);
            }
        }

        // totalDicas
        int td = 0;
        fread(&td, sizeof(int), 1, f);
        if (td < 0) td = 0;
        if (td > MAX_DICAS) td = MAX_DICAS;

        // aloca vetor de dicas
        p[i].dicas = (char **)malloc(sizeof(char *) * MAX_DICAS);
        if (!p[i].dicas) {
            // pular as dicas no arquivo
            for (int d = 0; d < td; d++) {
                int tamD = 0;
                fread(&tamD, sizeof(int), 1, f);
                if (tamD > 0) fseek(f, tamD, SEEK_CUR);
            }
            p[i].totalDicas = 0;
        } else {
            for (int d = 0; d < MAX_DICAS; d++) p[i].dicas[d] = NULL;

            for (int d = 0; d < td; d++) {
                int tamD = 0;
                fread(&tamD, sizeof(int), 1, f);
                if (tamD <= 0) {
                    p[i].dicas[d] = (char *)malloc(1);
                    if (p[i].dicas[d]) p[i].dicas[d][0] = '\0';
                    continue;
                }
                p[i].dicas[d] = (char *)malloc(tamD);
                if (p[i].dicas[d]) {
                    fread(p[i].dicas[d], sizeof(char), tamD, f);
                    p[i].dicas[d][tamD - 1] = '\0';
                } else {
                    // se malloc falhar, pular leitura
                    fseek(f, tamD, SEEK_CUR);
                }
            }
            p[i].totalDicas = td;
        }

        // dificuldade
        fread(&p[i].dificuldade, sizeof(int), 1, f);

        (*total)++;
    }

    fclose(f);
}

// ------------------------------------------------------------
// SALVAR em BIN (escreve do array p[], que deve conter ponteiros válidos)
// ------------------------------------------------------------
void salvarBIN(Producao p[], int total) {
    FILE *f = fopen("filmes.bin", "wb");
    if (!f) {
        printf("Erro ao salvar BIN!\n");
        return;
    }

    fwrite(&total, sizeof(int), 1, f);

    for (int i = 0; i < total; i++) {
        // tipo
        fwrite(&p[i].tipoProducao, sizeof(int), 1, f);

        // nome
        int tamNome = p[i].nomeProducao ? (int)strlen(p[i].nomeProducao) + 1 : 1;
        fwrite(&tamNome, sizeof(int), 1, f);
        if (p[i].nomeProducao)
            fwrite(p[i].nomeProducao, sizeof(char), tamNome, f);
        else {
            char empty = '\0';
            fwrite(&empty, sizeof(char), 1, f);
        }

        // totalDicas
        int td = p[i].totalDicas;
        fwrite(&td, sizeof(int), 1, f);

        for (int j = 0; j < td; j++) {
            int tamD = p[i].dicas[j] ? (int)strlen(p[i].dicas[j]) + 1 : 1;
            fwrite(&tamD, sizeof(int), 1, f);
            if (p[i].dicas[j])
                fwrite(p[i].dicas[j], sizeof(char), tamD, f);
            else {
                char e = '\0';
                fwrite(&e, sizeof(char), 1, f);
            }
        }

        // dificuldade
        fwrite(&p[i].dificuldade, sizeof(int), 1, f);
    }

    fclose(f);
}

// ------------------------------------------------------------
// liberarProducao: libera nome e dicas de uma produção
// ------------------------------------------------------------
void liberarProducao(Producao *p) {
    if (!p) return;
    if (p->nomeProducao) {
        free(p->nomeProducao);
        p->nomeProducao = NULL;
    }
    if (p->dicas) {
        for (int i = 0; i < p->totalDicas && i < MAX_DICAS; i++) {
            if (p->dicas[i]) {
                free(p->dicas[i]);
                p->dicas[i] = NULL;
            }
        }
        free(p->dicas);
        p->dicas = NULL;
    }
    p->totalDicas = 0;
}

// ------------------------------------------------------------
// confirmação de salvamento
// ------------------------------------------------------------
void confirmarESalvar(Producao p[], int total, int *houveAlteracao) {
    if (!*houveAlteracao) return;

    printf("\nSalvar alterações no BIN agora? S/N: ");
    char r;
    if (scanf(" %c", &r) != 1) { while (getchar() != '\n'); return; }
    getchar(); // consumir newline

    if (toupper((unsigned char)r) == 'S') {
        salvarBIN(p, total);
        printf("Salvo no BIN!\n");
        *houveAlteracao = 0;
    } else {
        printf("Alterações não salvas. Você pode salvar mais tarde.\n");
    }
}

// ------------------------------------------------------------
// MENU PRINCIPAL (usa array estático passado pelo caller)
// ------------------------------------------------------------
void menuGerenciamentoProducoes(Producao producoes[], int *totalProducoes) {

    int opcao;
    int houveAlteracao = 0;

    int usarBIN = existeBinario();

    if (usarBIN) {
        carregarBINmemoria(producoes, totalProducoes);
        printf("\n[INFO] Dados carregados do BIN (%d producoes).\n", *totalProducoes);
    } else {
        carregarCSVmemoria(producoes, totalProducoes);
        printf("\n[INFO] Dados carregados do CSV (%d producoes).\n", *totalProducoes);
    }

    do {
        printf("\n=== MENU PRODUÇÕES ===\n");
        printf("1. Listar produções\n");
        printf("2. Adicionar Produção\n");
        printf("3. Remover Produção\n");
        printf("4. Resetar ao padrão de fábrica\n");
        printf("0. Sair\n");
        printf("Escolha: ");

        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n');
            printf("Entrada inválida.\n");
            continue;
        }
        getchar();

        switch (opcao) {

            case 1:
                if (usarBIN) listarDoBIN();
                else listarDoCSV();
                break;

            case 2: {
                // if (*totalProducoes >= NUM_PRODUCOES) {
                //     printf("Limite atingido (%d produções permitidas).\n", NUM_PRODUCOES);
                //     break;
                // }

                Producao nova;
                nova.nomeProducao = NULL;
                nova.dicas = NULL;
                nova.totalDicas = 0;
                nova.dificuldade = 0;
                nova.tipoProducao = 0;

                // tipo
                do {
                    printf("Tipo (1-Filme, 2-Serie): ");
                    if (scanf("%d", &nova.tipoProducao) != 1) {
                        while (getchar() != '\n');
                        nova.tipoProducao = 0;
                    }
                    getchar();
                } while (nova.tipoProducao != 1 && nova.tipoProducao != 2);

                // nome
                char bufferNome[MAX_NOME];

                printf("Nome: ");
                fgets(bufferNome, sizeof(bufferNome), stdin);
                bufferNome[strcspn(bufferNome, "\n")] = '\0';
                for (int i = 0; bufferNome[i]; i++) {
                    bufferNome[i] = toupper((unsigned char)bufferNome[i]);
                }
                nova.nomeProducao = malloc(strlen(bufferNome) + 1);
                if (nova.nomeProducao){
                    strcpy(nova.nomeProducao, bufferNome);
                }

                // dificuldade
                do {
                    printf("Dificuldade (1 - Fácil | 2 - Difícil): ");
                
                    // Tentativa de leitura
                    if (scanf("%d", &nova.dificuldade) != 1) {
                        // Entrada inválida (letras, símbolos...)
                        while (getchar() != '\n'); // limpa buffer
                        nova.dificuldade = 0;      // força repetição
                        printf("Entrada inválida! Digite 1 ou 2.\n");
                        continue;
                    }
                
                    // Limpa eventual \n
                    while (getchar() != '\n' && getchar() != EOF);
                
                    // Validação
                    if (nova.dificuldade != 1 && nova.dificuldade != 2) {
                        printf("Opção inválida! Digite 1 ou 2.\n");
                        nova.dificuldade = 0; // força repetição
                    }
                
                } while (nova.dificuldade != 1 && nova.dificuldade != 2);

                // totalDicas
                int td = 0;
                do {
                    printf("Total de dicas (0-%d): ", MAX_DICAS);
                    if (scanf("%d", &td) != 1) { while (getchar() != '\n'); td = -1; }
                    getchar();
                } while (td < 0 || td > MAX_DICAS);

                nova.totalDicas = td;
                nova.dicas = (char **)malloc(sizeof(char *) * MAX_DICAS);
                for (int i = 0; i < MAX_DICAS; i++) nova.dicas[i] = NULL;

                for (int i = 0; i < nova.totalDicas; i++) {
                    char buf[MAX_TAM_DICA];
                    printf("Dica %d: ", i + 1);
                    fgets(buf, sizeof(buf), stdin);
                    buf[strcspn(buf, "\n")] = '\0';
                    nova.dicas[i] = malloc(strlen(buf) + 1);
                    if (nova.dicas[i]) strcpy(nova.dicas[i], buf);
                }

                // adicionar ao array (cópia de struct; ponteiros são copiados)
                producoes[*totalProducoes] = nova;
                (*totalProducoes)++;
                houveAlteracao = 1;
                usarBIN = 1; // agora representamos que BIN é a fonte persistida

                printf("Adicionado.\n");
                confirmarESalvar(producoes, *totalProducoes, &houveAlteracao);
                break;
            }

            case 3: {
                if (*totalProducoes == 0) {
                    printf("Nenhuma produção.\n");
                    break;
                }

                char nomeBusca[MAX_NOME];
                printf("Nome a remover: ");
                fgets(nomeBusca, sizeof(nomeBusca), stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
                for (int i = 0; nomeBusca[i]; i++) {
                    nomeBusca[i] = toupper((unsigned char)nomeBusca[i]);
                }


                int achou = 0;
                for (int i = 0; i < *totalProducoes; i++) {
                    if (producoes[i].nomeProducao && strcmp(producoes[i].nomeProducao, nomeBusca) == 0) {
                        // libera memória da produção
                        liberarProducao(&producoes[i]);

                        // desloca para esquerda
                        for (int j = i; j < *totalProducoes - 1; j++) {
                            producoes[j] = producoes[j + 1];
                        }
                        (*totalProducoes)--;
                        houveAlteracao = 1;
                        usarBIN = 1;
                        achou = 1;
                        printf("Removido.\n");
                        confirmarESalvar(producoes, *totalProducoes, &houveAlteracao);
                        break;
                    }
                }
                if (!achou) printf("Não encontrado.\n");
                break;
            }

            case 4: {
                printf("Resetar? S/N: ");
                char r;
                if (scanf(" %c", &r) != 1) { while (getchar() != '\n'); break; }
                getchar();

                if (toupper((unsigned char)r) == 'S') {
                    remove("filmes.bin");
                    // liberar todas producoes em memória
                    for (int i = 0; i < *totalProducoes; i++) liberarProducao(&producoes[i]);
                    *totalProducoes = 0;
                    usarBIN = 0;
                    // recarrega do CSV (preenche producoes até NUM_PRODUCOES)
                    carregarCSVmemoria(producoes, totalProducoes);
                    printf("Sistema resetado (recarregado do CSV).\n");
                }
                break;
            }

            case 0:
                if (houveAlteracao) {
                    printf("Ainda há alterações não salvas. Deseja salvar antes de sair? S/N: ");
                    char r;
                    if (scanf(" %c", &r) == 1) {
                        getchar();
                        if (toupper((unsigned char)r) == 'S') {
                            salvarBIN(producoes, *totalProducoes);
                            printf("Salvo no BIN!\n");
                        } else {
                            printf("Saindo sem salvar alterações.\n");
                        }
                    } else {
                        while (getchar() != '\n');
                    }
                } else {
                    printf("Saindo...\n");
                }
                break;

            default:
                printf("Opção inválida.\n");
        }

    } while (opcao != 0);
}
