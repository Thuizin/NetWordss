/**
 * @file inicializarJogo.c
 * @author Thayane Nascimento Rezende (thayanenascimentorezende@alunos.utfpr.edu.br)
 * @brief Arquivo da fun��o 'inicializarJogo'
 * @version 0.1
 * @date 2025-11-08
 * @copyright Copyright (c) 2025
 */

// Inclus�o de bibliotecas e arquivos

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"

// In��cio da fun��o 'inicializarJogo'

/**
 * @brief Fun��o que inicializa o jogo
 * @param estadoAtualJogo ponteiro que aponta para uma vari�vel que cont�m as informa��s do estado atual do jogo
 * @param producao vetor de produ��es
 */

void inicializarJogo(EstadoAtualJogo *estadoAtualJogo, Producao producao[]){

    // Declara��o de vari�veis e atribui��o de valores

    int indiceProducaoSorteada = rand() % NUM_PRODUCOES;

    // Criamos uma nova vari�vel para ficar mais leg��vel e f�cil de utilizar

    Producao producaoSorteada = producao[indiceProducaoSorteada];

    // Inicializa os valores que ser�o utilizados no decorrer do jogo

    strcpy(estadoAtualJogo->nomeProducaoSorteada, producaoSorteada.nomeProducao);
    estadoAtualJogo->errosRestantes = 7;
    estadoAtualJogo->dicasUsadas = 0;
    estadoAtualJogo->pontuacao = 0;
    estadoAtualJogo->letrasTentadas[0] = '\0';

    // Chama a fun��o 'inicializarMascara'

    inicializarMascara(producaoSorteada, estadoAtualJogo);

    return;
}//inicializarJogo