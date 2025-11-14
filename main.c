/**
 * @file main.c
 * @author 
 * @brief Arquivo principal do game
 * @version 0.2
 * @date 2025-11-12
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <locale.h>
 #include <ctype.h>
 #include <time.h>
 #include "main.h"
 
 int main() {
     setlocale(LC_ALL, "");
     srand(time(NULL));
 
     // Declaração de variáveis
     Jogador jogador;
     Producao *producao = (Producao *)malloc(NUM_PRODUCOES * sizeof(Producao));
     if (!producao) {
         printf("Erro ao alocar memória para produções!\n");
         return 1;
     }
 
     jogador.nomeJogador = (char *)malloc(51 * sizeof(char));
     if (!jogador.nomeJogador) {
         printf("Erro ao alocar memória para nome do jogador!\n");
         free(producao);
         return 1;
     }
 
     jogador.pontos = 0;
 
     // Cadastro do jogador e preenchimento inicial das produções
     cadastraJogador(&jogador);
     // preencheProducao(producao);

     FILE *arq = fopen("filmes.bin", "wb");
     if(arq == NULL){
        FILE *arq = fopen("filmes.csv", "r");
        if(arq == NULL){
            perror("Erro: ");
            exit(1);
        }
     }
 
     int tempoLimite = 2; // temporário fixo
 
     // MENU INICIAL: 1 - Jogar | 2 - Gerenciar produções
     int escolhaMenu = 0;
     do {
         printf("\n=== MENU INICIAL ===\n");
         printf("1 - Iniciar o jogo\n");
         printf("2 - Abrir configurações (gerenciar produções)\n");
         printf("Escolha: ");
         scanf("%d", &escolhaMenu);
         getchar(); // limpa buffer
 
         if (escolhaMenu != 1 && escolhaMenu != 2)
             printf("Opção inválida! Digite 1 ou 2.\n");
     } while (escolhaMenu != 1 && escolhaMenu != 2);
 
     if (escolhaMenu == 2) {
         int totalProducoes = NUM_PRODUCOES;
         menuGerenciamentoProducoes(producao, &totalProducoes);
     }
 
     // Laço principal do jogo
     char jogarNovamente = 'S';
     do {
         // Cria novo estado do jogo
         EstadoAtualJogo estadoAtualJogo;
         estadoAtualJogo.nomeProducaoSorteada = (char *)malloc(51 * sizeof(char));
         estadoAtualJogo.statusAtual = (char *)malloc(51 * sizeof(char));
         estadoAtualJogo.letrasTentadas = (char *)malloc(27 * sizeof(char));
 
         if (!estadoAtualJogo.nomeProducaoSorteada || !estadoAtualJogo.statusAtual || !estadoAtualJogo.letrasTentadas) {
             printf("Erro ao alocar memória para estado do jogo!\n");
             free(jogador.nomeJogador);
             free(producao);
             return 1;
         }
 
         inicializarJogo(&estadoAtualJogo, producao);
 
         jogar(&estadoAtualJogo, producao, tempoLimite);
 
         jogador.pontos += estadoAtualJogo.pontuacao;
         printf("Jogador: %s | Pontuação total: %d.\n", jogador.nomeJogador, jogador.pontos);
 
         // Libera memória do estado do jogo
         free(estadoAtualJogo.nomeProducaoSorteada);
         free(estadoAtualJogo.statusAtual);
         free(estadoAtualJogo.letrasTentadas);
 
         if (jogador.pontos >= 70) {
             printf("Parabéns! Você alcançou %d pontos e venceu o jogo.\n", jogador.pontos);
             break;
         }
 
         // Pergunta se deseja jogar novamente
         do {
             printf("Deseja jogar novamente (S - SIM | N - NÃO)? ");
             scanf(" %c", &jogarNovamente);
             jogarNovamente = toupper(jogarNovamente);
         } while (jogarNovamente != 'S' && jogarNovamente != 'N');
 
     } while (jogarNovamente == 'S');
 
     printf("Fim de jogo. Obrigado por jogar, %s!\n", jogador.nomeJogador);
 
     // Libera memória do jogador
     free(jogador.nomeJogador);
 
     // Libera memória das produções
     if (producao) {
         for (int i = 0; i < NUM_PRODUCOES; i++) {
             if (producao[i].nomeProducao)
                 free(producao[i].nomeProducao);
             if (producao[i].dicas) {
                 for (int j = 0; j < producao[i].totalDicas; j++) {
                     if (producao[i].dicas[j])
                         free(producao[i].dicas[j]);
                 }
                 free(producao[i].dicas);
             }
         }
         free(producao);
     }
 
     return 0;
 }
