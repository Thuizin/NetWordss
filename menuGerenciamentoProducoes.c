#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "main.h"  // contém a struct Producao e a função converteParaMaiuscula(char letra)

#define MAX_DICAS_LOCAL 10
#define MAX_TAM_DICA_LOCAL 100

void menuGerenciamentoProducoes(Producao producoes[], int *totalProducoes) {

    int opcao;
    int houveAlteracao = 0; // <<< CONTROLE DE ALTERAÇÃO

    do {
        printf("\n=== MENU DE GERENCIAMENTO DE PRODUÇÕES ===\n");
        printf("1. Listar produções\n");
        printf("2. Adicionar produção\n");
        printf("3. Remover produção\n");
        printf("4. Resetar ao padrão\n");
        printf("0. Voltar ao menu principal\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {

            case 1: { // Listar
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

            case 2: { // Adicionar
                if (*totalProducoes >= NUM_PRODUCOES) {
                    printf("Limite máximo de produções atingido.\n");
                    break;
                }

                Producao nova;

                // tipo
                do {
                    printf("Digite o tipo da produção (1-Filme, 2-Série): ");
                    scanf("%d", &nova.tipoProducao);
                    getchar();
                    if (nova.tipoProducao != 1 && nova.tipoProducao != 2)
                        printf("Tipo inválido! Digite 1 ou 2.\n");
                } while (nova.tipoProducao != 1 && nova.tipoProducao != 2);

                // nome
                printf("Digite o nome da produção: ");
                fgets(nova.nomeProducao, sizeof(nova.nomeProducao), stdin);
                nova.nomeProducao[strcspn(nova.nomeProducao, "\n")] = '\0';

                for (int i = 0; nova.nomeProducao[i] != '\0'; i++)
                    nova.nomeProducao[i] = converteParaMaiuscula(nova.nomeProducao[i]);

                // dicas
                do {
                    printf("Digite o total de dicas (máximo %d): ", MAX_DICAS_LOCAL);
                    scanf("%d", &nova.totalDicas);
                    getchar();
                    if (nova.totalDicas < 1 || nova.totalDicas > MAX_DICAS_LOCAL)
                        printf("Número inválido.\n");
                } while (nova.totalDicas < 1 || nova.totalDicas > MAX_DICAS_LOCAL);

                for (int i = 0; i < nova.totalDicas; i++) {
                    nova.dicas[i] = (char *)malloc(MAX_TAM_DICA_LOCAL * sizeof(char));
                    if (!nova.dicas[i]) {
                        printf("Erro ao alocar dica!\n");
                        exit(1);
                    }

                    printf("Digite a dica %d: ", i + 1);
                    fgets(nova.dicas[i], MAX_TAM_DICA_LOCAL, stdin);
                    nova.dicas[i][strcspn(nova.dicas[i], "\n")] = '\0';

                    for (int j = 0; nova.dicas[i][j] != '\0'; j++)
                        nova.dicas[i][j] = converteParaMaiuscula(nova.dicas[i][j]);
                }

                producoes[*totalProducoes] = nova;
                (*totalProducoes)++;
                houveAlteracao = 1; 
                printf("Produção adicionada com sucesso!\n");
                break;
            }

            case 3: { // Remover
                if (*totalProducoes == 0) {
                    printf("Nenhuma produção para remover.\n");
                    break;
                }

                char nome[100];
                printf("Digite o nome da produção a remover: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';

                for (int i = 0; nome[i] != '\0'; i++)
                    nome[i] = converteParaMaiuscula(nome[i]);

                int encontrado = 0;

                for (int i = 0; i < *totalProducoes; i++) {
                    if (strcmp(producoes[i].nomeProducao, nome) == 0) {

                        for (int k = 0; k < producoes[i].totalDicas; k++)
                            free(producoes[i].dicas[k]);

                        for (int j = i; j < *totalProducoes - 1; j++)
                            producoes[j] = producoes[j + 1];

                        (*totalProducoes)--;
                        houveAlteracao = 1;
                        encontrado = 1;
                        printf("Produção removida!\n");
                        break;
                    }
                }

                if (!encontrado)
                    printf("Produção não encontrada.\n");

                break;
            }

            case 4: { // Resetar
                printf("\nATENÇÃO: Isso irá apagar o arquivo filmes.bin e restaurar tudo.\n");
                printf("Tem certeza? (S/N): ");
                char resp;
                scanf(" %c", &resp);
                resp = toupper(resp);
                getchar();

                if (resp == 'S') {

                    remove("filmes.bin");

                    
                    for (int i = 0; i < *totalProducoes; i++) {
                        for (int j = 0; j < producoes[i].totalDicas; j++)
                            free(producoes[i].dicas[j]);
                    }

                    *totalProducoes = 0;

                    printf("Sistema restaurado ao padrão!\n");
                } else {
                    printf("Reset cancelado.\n");
                }
                break;
            }

            case 0: {

                if (houveAlteracao == 1) {

                    char save;
                    do {
                        printf("Deseja salvar as alterações? (S ou N)\n");
                        scanf(" %c", &save);
                        save = toupper(save);
                    } while (save != 'S' && save != 'N');

                    if (save == 'S') {

                        FILE *aqr = fopen("filmes.bin", "wb");
                        if (!aqr) {
                            printf("Erro ao abrir arquivo para escrita.\n");
                            break;
                        }

                        fwrite(totalProducoes, sizeof(int), 1, aqr);

                        for (int i = 0; i < *totalProducoes; i++) {

                            fwrite(&producoes[i].tipoProducao, sizeof(int), 1, aqr);

                            int tamNome = strlen(producoes[i].nomeProducao) + 1;
                            fwrite(&tamNome, sizeof(int), 1, aqr);
                            fwrite(producoes[i].nomeProducao, sizeof(char), tamNome, aqr);

                            fwrite(&producoes[i].totalDicas, sizeof(int), 1, aqr);

                            for (int j = 0; j < producoes[i].totalDicas; j++) {
                                int tamDica = strlen(producoes[i].dicas[j]) + 1;
                                fwrite(&tamDica, sizeof(int), 1, aqr);
                                fwrite(producoes[i].dicas[j], sizeof(char), tamDica, aqr);
                            }
                        }

                        fclose(aqr);
                        printf("Alterações salvas com sucesso!\n");
                    }

                } else {
                    printf("Nenhuma alteração realizada. Saindo...\n");
                }

                printf("Retornando ao menu principal...\n");
                break;
            }

            default:
                printf("Opção inválida.\n");
        }

    } while (opcao != 0);
}
