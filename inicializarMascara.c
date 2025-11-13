/**
 * @file inicializarMascara.c
 * @author Thayane Nascimento Rezende (thayanenascimentorezende@alunos.utfpr.edu.br)
 * @brief Arquivo da fun��o 'inicializarMascara'
 * @version 0.1
 * @date 2025-11-08
 * @copyright Copyright (c) 2025
 */

// Inclus�o de bibliotecas e arquivos

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"

// In��cio da fun��o 'inicializarMascara'

/**
 * @brief Fun��o que inicializa a m�scara da palavra
 * @param producaoSorteada vari�vel que cont�m o nome da produ��o sorteada
 * @param estadoAtualJogo ponteiro que aponta para uma vari�vel que cont�m as informa��es do estado atual do jogo
 */

void inicializarMascara(Producao producaoSorteada, EstadoAtualJogo *estadoAtualJogo){

    // Declara��o de vari�veis e atribui��o de valores

    int tamProducaoSorteada = strlen(producaoSorteada.nomeProducao);
    char *mascara = estadoAtualJogo->statusAtual;
    char c;

    // La�o de repeti��o que exibe a "m�scara" para cada caractere

    for(int i = 0; i < tamProducaoSorteada; i++){

        c = producaoSorteada.nomeProducao[i];

        // Verifica o conte�do do caractere 

        if(c == ' ' || c == '-')
            mascara[i] = c;
        else
            mascara[i] = '_';
    }//for

    // Adiciona o caractere nulo no final da m�scara

    mascara[tamProducaoSorteada] = '\0';

}//inicializarMascara