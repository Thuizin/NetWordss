#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"  // contém a struct Producao e a função converteParaMaiuscula(char letra)

#define MAX_DICAS_LOCAL 10       // limite interno de dicas
#define MAX_TAM_DICA_LOCAL 100   // tamanho máximo de cada dica

void menuGerenciamentoProducoes(Producao producoes[], int *totalProducoes) {
    int opcao;

    do {
        printf("\n=== MENU DE GERENCIAMENTO DE PRODUÇÕES ===\n");
        printf("1. Listar produções\n");
        printf("2. Adicionar produção\n");
        printf("3. Remover produção\n");
        printf("4. Salvar em CSV\n");
        printf("5. Carregar do CSV\n");
        printf("0. Voltar ao menu principal\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar(); // limpa o buffer

        switch (opcao) {
            case 1: { // Listar produções
                if (*totalProducoes == 0) {
                    printf("\nNenhuma produção cadastrada ainda.\n");
                } else {
                    printf("\n%-5s | %-40s | %-5s\n", "TIPO", "NOME", "DICAS");
                    printf("--------------------------------------------------------------\n");
                    for (int i = 0; i < *totalProducoes; i++) {
                        printf("%-5d | %-40s | %-5d\n",
                               producoes[i].tipoProducao,
                               producoes[i].nomeProducao,
                               producoes[i].totalDicas);
                    }
                }
                break;
            }

            case 2: { // Adicionar nova produção
                if (*totalProducoes >= NUM_PRODUCOES) {
                    printf("Limite máximo de produções atingido.\n");
                    break;
                }

                Producao nova;

                // tipo da produção (somente 1 ou 2)
                do {
                    printf("Digite o tipo da produção (1-Filme, 2-Série): ");
                    scanf("%d", &nova.tipoProducao);
                    getchar();
                    if (nova.tipoProducao != 1 && nova.tipoProducao != 2)
                        printf("Tipo inválido! Digite 1 ou 2.\n");
                } while (nova.tipoProducao != 1 && nova.tipoProducao != 2);

                // nome da produção
                printf("Digite o nome da produção: ");
                fgets(nova.nomeProducao, sizeof(nova.nomeProducao), stdin);
                nova.nomeProducao[strcspn(nova.nomeProducao, "\n")] = '\0';

                // converte nome para maiúsculas
                for (int i = 0; nova.nomeProducao[i] != '\0'; i++)
                    nova.nomeProducao[i] = converteParaMaiuscula(nova.nomeProducao[i]);

                // total de dicas (até MAX_DICAS_LOCAL)
                do {
                    printf("Digite o total de dicas (máximo %d): ", MAX_DICAS_LOCAL);
                    scanf("%d", &nova.totalDicas);
                    getchar();
                    if (nova.totalDicas < 1 || nova.totalDicas > MAX_DICAS_LOCAL)
                        printf("Número inválido! Digite entre 1 e %d.\n", MAX_DICAS_LOCAL);
                } while (nova.totalDicas < 1 || nova.totalDicas > MAX_DICAS_LOCAL);

                // aloca memória para cada dica
                for (int i = 0; i < nova.totalDicas; i++) {
                    nova.dicas[i] = (char *)malloc(MAX_TAM_DICA_LOCAL * sizeof(char));
                    if (!nova.dicas[i]) {
                        printf("Erro ao alocar memória para a dica %d!\n", i + 1);
                        exit(1);
                    }

                    printf("Digite a dica %d: ", i + 1);
                    fgets(nova.dicas[i], MAX_TAM_DICA_LOCAL, stdin);
                    nova.dicas[i][strcspn(nova.dicas[i], "\n")] = '\0';

                    // converte dica para maiúsculas
                    for (int j = 0; nova.dicas[i][j] != '\0'; j++)
                        nova.dicas[i][j] = converteParaMaiuscula(nova.dicas[i][j]);
                }

                producoes[*totalProducoes] = nova;
                (*totalProducoes)++;

                printf("Produção adicionada com sucesso!\n");
                break;
            }

            case 3: { // Remover produção
                if (*totalProducoes == 0) {
                    printf("Nenhuma produção para remover.\n");
                    break;
                }

                char nome[100];
                printf("Digite o nome da produção a remover: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';

                // converte para maiúsculas
                for (int i = 0; nome[i] != '\0'; i++)
                    nome[i] = converteParaMaiuscula(nome[i]);

                int encontrado = 0;
                for (int i = 0; i < *totalProducoes; i++) {
                    if (strcmp(producoes[i].nomeProducao, nome) == 0) {
                        // libera memória das dicas antes de remover
                        for (int k = 0; k < producoes[i].totalDicas; k++)
                            free(producoes[i].dicas[k]);

                        // shift para remover produção
                        for (int j = i; j < *totalProducoes - 1; j++)
                            producoes[j] = producoes[j + 1];

                        (*totalProducoes)--;
                        encontrado = 1;
                        printf("Produção removida com sucesso.\n");
                        break;
                    }
                }

                if (!encontrado)
                    printf("Produção não encontrada.\n");
                break;
            }

            case 4: { // Salvar CSV
                FILE *f = fopen("producoes.csv", "w");
                if (!f) {
                    printf("Erro ao abrir arquivo CSV.\n");
                    break;
                }
                fprintf(f, "TIPO;NOME;TOTAL_DICAS\n");
                for (int i = 0; i < *totalProducoes; i++)
                    fprintf(f, "%d;%s;%d\n",
                            producoes[i].tipoProducao,
                            producoes[i].nomeProducao,
                            producoes[i].totalDicas);
                fclose(f);
                printf("Arquivo CSV salvo com sucesso!\n");
                break;
            }

            case 5: { // Carregar CSV
                FILE *f = fopen("producoes.csv", "r");
                if (!f) {
                    printf("Nenhum arquivo CSV encontrado.\n");
                    break;
                }

                char linha[256];
                *totalProducoes = 0;
                fgets(linha, sizeof(linha), f); // pular cabeçalho

                while (fgets(linha, sizeof(linha), f) != NULL && *totalProducoes < NUM_PRODUCOES) {
                    Producao nova;
                    linha[strcspn(linha, "\n")] = '\0';
                    sscanf(linha, "%d;%49[^;];%d",
                           &nova.tipoProducao,
                           nova.nomeProducao,
                           &nova.totalDicas);

                    // converte nome para maiúsculas
                    for (int i = 0; nova.nomeProducao[i] != '\0'; i++)
                        nova.nomeProducao[i] = converteParaMaiuscula(nova.nomeProducao[i]);

                    // inicializa ponteiros de dicas como NULL (para evitar segfault)
                    for (int i = 0; i < MAX_DICAS_LOCAL; i++)
                        nova.dicas[i] = NULL;

                    producoes[*totalProducoes] = nova;
                    (*totalProducoes)++;
                }

                fclose(f);
                printf("Produções carregadas do CSV com sucesso!\n");
                break;
            }

            case 0:
                printf("Retornando ao menu principal...\n");
                break;

            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 0);
}
