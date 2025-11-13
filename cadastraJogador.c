/**
 * @file cadastraJogador.c
 * @author Thayane Nascimento Rezende (thayanenascimentorezende@alunos.utfpr.edu.br)
 * @brief Arquivo da fun��o 'cadastraJogador'
 * @version 0.1
 * @date 2025-11-08
 * @copyright Copyright (c) 2025
 */

// Inclus�o de bibliotecas e arquivos

#include <stdio.h>
#include <string.h>
#include "main.h"

// In��cio da fun��o 'cadastraJogador'

/**
 * @brief Fun��o que cadastra o jogador
 * @param jogador ponteiro que aponta para um jogador
 */

void cadastraJogador(Jogador *jogador){

    // Solicita o nome do jogador
    
    printf("Digite o nome do jogador: ");
    fflush(stdout); // Garante que a mensagem seja exibida
    
    if(fgets(jogador->nomeJogador, 51, stdin) == NULL){
        // Se fgets falhar, inicializa com string vazia
        jogador->nomeJogador[0] = '\0';
    } else {
        // Remove o caractere de nova linha se existir
        jogador->nomeJogador[strcspn(jogador->nomeJogador, "\n")] = '\0';
    }

    // Inicializa a pontua��o
    
    jogador->pontos = 0;

    return;
}//cadastraJogador