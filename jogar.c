/**
 * @file jogar.c
 * @author Thayane Nascimento Rezende (thayanenascimentorezende@alunos.utfpr.edu.br)
 * @brief Arquivo da fun��o 'jogar'
 * @version 0.1
 * @date 2025-11-08
 * @copyright Copyright (c) 2025
 */

// Inclus�o de bibliotecas e arquivos

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Necess�rio para o cron�metro
#include "main.h"

// In��cio da fun��o 'jogar'

/**
 * @brief Fun��o que controla o fluxo do jogo
 * @param estadoAtualJogo ponteiro que aponta para uma vari�vel que cont�m as informa��es do estado atual do jogo
 * @param producao vetor de produ��es
 */

void jogar(EstadoAtualJogo *estadoAtualJogo, Producao producao[], int tempoLimite){

    // Declara��o de vari�veis e atribui��o de valores 

    time_t tempoInicio  = time(NULL); // Salva o tempo de in��cio da rodada 
    int estourouTempo = 0; // Vari�vel para controlar a derrota por tempo

    int tamLetrasTentadas;
    int escolha;
    Producao producaoSorteada;

    // Converter minutos para segundos

    int tempoLimiteSegundos = tempoLimite * 60;

    // Tempor�rio, apenas para fins de testes
    // printf("Nome: %s\n\n", estadoAtualJogo->nomeProducaoSorteada);

    // Busca a produ��o para ter acesso �s dicas

    for(int i = 0; i < NUM_PRODUCOES; i++){
        if(strcmp(producao[i].nomeProducao, estadoAtualJogo->nomeProducaoSorteada) == 0){
            producaoSorteada = producao[i];
            break;
        }//if
    }//for

    // Exibe a dica inicial da produ��o e o tempo escolhido

    printf("\nDICA INICIAL: %s\n", producaoSorteada.dicas[0]);
    printf("Tempo limite: %d minutos\n", tempoLimite);

    // La�o de repeti��o que controla o fluxo do jogo (loop principal do jogo) 

    while(estadoAtualJogo->errosRestantes > 0 && strcmp(estadoAtualJogo->statusAtual, estadoAtualJogo->nomeProducaoSorteada) != 0 && estourouTempo == 0){

        // Calcula a diferen�a de tempo

        double segundosDecorridos = difftime(time(NULL), tempoInicio);

        if(segundosDecorridos >= tempoLimiteSegundos){ // Tempo limite personalizado
            estourouTempo = 1;
            break; // sai do loop (while) imediatamente
        }//if

        // Calcula minutos e segundos restantes para exibir

        int segundosRestantesTotal = tempoLimiteSegundos - (int)segundosDecorridos;
        int minutosRestantes = segundosRestantesTotal / 60;
        int segundosRestantes = segundosRestantesTotal % 60;

        // Exibe a 'm�scara' (palavra a ser adivinhada)

        printf("\n---------------------------------------\n");
        printf("\nProdu��o: %s\n\n", estadoAtualJogo->statusAtual);
        printf("---------------------------------------\n");

        // Exibe status de forma organizada

        printf("\nSTATUS:\n");
        printf("Erros restantes: %d\n", estadoAtualJogo->errosRestantes);
        printf("Tempo: %02d:%02d\n", minutosRestantes, segundosRestantes);
        printf("Pontos: %d\n", estadoAtualJogo->pontuacao);
        
        // Exibe as letras tentadas (se houver) ANTES da escolha
        tamLetrasTentadas = strlen(estadoAtualJogo->letrasTentadas);
        if(tamLetrasTentadas > 0){
            printf("Letras tentadas: ");
            for(int i = 0; i < tamLetrasTentadas; i++){
                printf("%c ", estadoAtualJogo->letrasTentadas[i]);
            }//for
            printf("\n");
        }//if

        // Solicita a op��o do usu�rio

        do{
            printf("\nOP��ES:\n");
            printf("1 - Tentar uma letra\n");
            printf("2 - Chutar a palavra (RISCO!)\n");
            printf("3 - Pedir dica (-3 pontos)\n");
            
            printf("\nDigite sua escolha: ");
            scanf("%d", &escolha);
            getchar(); // limpa o buffer do 'ENTER'

            if(escolha != 1 && escolha != 2 && escolha != 3)
                printf("Inv�lido! Tente novamente.\n");
        }while(escolha != 1 && escolha != 2 && escolha != 3);

        // Verifica o tempo depois da entrada

        segundosDecorridos = difftime(time(NULL), tempoInicio);
    
        if(segundosDecorridos >= tempoLimiteSegundos){
            estourouTempo = 1;
            break;
        }//if

        // switch que direciona a escolha do usu�rio para a respectiva fun��o

        switch(escolha){
            case 1:
                processarTentativaDeLetra(estadoAtualJogo);
                break;

            case 2:
                chutarPalavra(estadoAtualJogo);
                break;

            case 3:
                exibeDica(estadoAtualJogo, producaoSorteada);
                break;
        }//switch�vel
    }//while

    // Calcular penalidade de tempo

    if(estourouTempo  == 0){ // S� aplica penalidade se n�o perdeu por tempo
        double segundosFinais = difftime(time(NULL), tempoInicio);
        int minutosJogados = (int)(segundosFinais / 60);

        if(minutosJogados > tempoLimite)
            minutosJogados = tempoLimite;

        int penalidadeTempo = minutosJogados * 2; // -2 pontos por minutos

        if(penalidadeTempo > 0){
            printf("Penalidade por tempo: -%d pontos (%d minutos).\n", penalidadeTempo, minutosJogados);
            estadoAtualJogo->pontuacao -= penalidadeTempo;
        }//if
    }//if   
    
    // Exibe o resultado 

    if(estourouTempo > 0){ // Perdeu por tempo

        printf("\nTEMPO ESGOTADO! Voc� perdeu a rodada.\n");
        printf("A produ��o era: '%s'.\n", estadoAtualJogo->nomeProducaoSorteada);

    }else if(strcmp(estadoAtualJogo->statusAtual, estadoAtualJogo->nomeProducaoSorteada) == 0){ // Ganhou a rodada

        // Verifica se j� ganhou pontos pelo chute (20 pontos)

        if(estadoAtualJogo->pontuacao < 20){ 
            // Se n�o ganhou 20 pontos, ganha 10
            
            estadoAtualJogo->pontuacao += 10;
            printf("VIT�RIA! Voce acertou a produ��o. +10 pontos.\n");
        }else{
            // J� ganhou 20 pontos pelo chute, s� exibe mensagem

            printf("VIT�RIA! Voce acertou a produ��o.\n");
        }//else

    }else{

        // Verifica se perdeu por xeque-mate ou falta de tentativas

        if(estadoAtualJogo->errosRestantes > 0){ // Perdeu por xeque-mate
            printf("\nXEQUE-MATE! Seu chute estava incorreto.\n");
            printf("A produ��o era: '%s'.\n", estadoAtualJogo->nomeProducaoSorteada);
        }else{ // Perdeu por falta de tentativas
            printf("\nVoc� perdeu! Suas tentativas se esgotaram.\n");
            printf("A produ��o era: '%s'.\n", estadoAtualJogo->nomeProducaoSorteada);
        }//else

    }//else

    // Exibe a pontua��o final da rodada

    printf("\nPontua��o desta rodada: %d.\n", estadoAtualJogo->pontuacao);

    return;
}//jogar