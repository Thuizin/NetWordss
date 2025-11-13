/**
 * @file chutarPalavra.c
 * @author Thayane Nascimento Rezende (thayanenascimentorezende@alunos.utfpr.edu.br)
 * @brief Arquivo da fun��o 'chutarPalavra'
 * @version 0.1
 * @date 2025-11-08
 * @copyright Copyright (c) 2025
 */

// Inclus�o de bibliotecas e arquivos

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "main.h"

// In��cio da fun��o 'chutarPalavra'

/**
 * @brief Fun��o que processa a tentativa de chute de palavra do usu�rio
 * @param estadoAtualJogo ponteiro que aponta para uma vari�vel que cont�m as informa��es do estado atual do jogo
 */

void chutarPalavra(EstadoAtualJogo *estadoAtualJogo){

    // Declara��o de vari�veis e atribui��o de valores

    // Alocação dinâmica implementada aqui
    char *palavra = (char *)malloc(51 * sizeof(char));
    if(palavra == NULL){
        printf("Erro ao alocar memória!\n");
        return;
    }
    int tamPalavra;
    
    int tamGabarito;

    // Inicializamos para evitar problemas com lixo de mem�ria
    // Alocação dinâmica implementada aqui
    char *chuteNormalizado = (char *)calloc(51, sizeof(char)); 
    char *gabaritoNormalizado = (char *)calloc(51, sizeof(char));
    
    if(chuteNormalizado == NULL || gabaritoNormalizado == NULL){
        printf("Erro ao alocar memória!\n");
        free(palavra);
        if(chuteNormalizado != NULL) free(chuteNormalizado);
        if(gabaritoNormalizado != NULL) free(gabaritoNormalizado);
        return;
    }

    // Solicita a palavra para o usu�rio

    printf("Digite a palavra completa: ");
    fgets(palavra, 50, stdin);
    palavra[strcspn(palavra, "\n")] = '\0';
    
    // Verifica o tamanho da palavra e salva em uma vari�vel
    
    tamPalavra = strlen(palavra);
    
    // Trata o caso se a string estiver vazia

    if(tamPalavra == 0){
        printf("Palavra vazia, invalido! Tente novamente.\n");
        // Libera memória antes de retornar
        free(palavra);
        free(chuteNormalizado);
        free(gabaritoNormalizado);
        return;
    }//if
    
    // Converte a palavra para mai�scula

    for(int i = 0; i < tamPalavra; i++){
        palavra[i] = converteParaMaiuscula(palavra[i]);
    }//for

    // Atribui��o de valor para a vari�vel de compara��o

    tamGabarito = strlen(estadoAtualJogo->nomeProducaoSorteada);

    // Normaliza o chute do usu�rio

    for(int i = 0; i < tamPalavra; i++){
        chuteNormalizado[i] = normalizarLetra(palavra[i]);
    }//for  

    // Fecha a string normalizada

    chuteNormalizado[tamPalavra] = '\0';

    // Normaliza o gabarito (nome da produ��o)

    for(int i = 0; i < tamGabarito; i++){
        gabaritoNormalizado[i] = normalizarLetra(estadoAtualJogo->nomeProducaoSorteada[i]);
    }//for

    // Fecha a string normalizada

    gabaritoNormalizado[tamGabarito] = '\0';

    // Compara as duas palavras normalizadas

    if(strcmp(chuteNormalizado, gabaritoNormalizado) == 0){
        // Atualiza a m�scara (vers�o original) para mostrar a palavra completa
        strcpy(estadoAtualJogo->statusAtual, estadoAtualJogo->nomeProducaoSorteada);

        printf("\nAcertou em cheio! +20 pontos!\n");
        
        // Adiciona pontos por acertar a palavra completa
        estadoAtualJogo->pontuacao += 20; 
    }else{
        printf("\nErrou! A producao esta incorreta.\n");
        printf("XEQUE-MATE! Voce usou seu chute e perdeu a rodada.\n");

        // Penalidade do xeque-mate
        estadoAtualJogo->errosRestantes = 0;
    }//else

    // Libera memória alocada dinamicamente
    // Alocação dinâmica implementada aqui
    if(palavra != NULL){
        free(palavra);
    }
    if(chuteNormalizado != NULL){
        free(chuteNormalizado);
    }
    if(gabaritoNormalizado != NULL){
        free(gabaritoNormalizado);
    }

    return;
}//chutarPalavra
