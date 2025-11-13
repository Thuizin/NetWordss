/**
 * @file exibeDica.c
 * @author Thayane Nascimento Rezende (thayanenascimentorezende@alunos.utfpr.edu.br)
 * @brief Arquivo da fun��o 'exibeDica'
 * @version 0.1
 * @date 2025-11-08
 * @copyright Copyright (c) 2025
 */

// Inclus�o de bibliotecas e arquivos

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "main.h"

/**
 * @brief Fun��o que exibe dica para o usu�rio
 * @param estadoAtualJogo ponteiro que aponta para uma vari�vel que cont�m as informa��es do estado atual do jogo
 * @param producao vari�vel que cont�m o nome da produ��o sorteada
 */

// In��cio da fun��o 'exibeDica'

void exibeDica(EstadoAtualJogo *estadoAtualJogo, Producao producaoSorteada){

    // Alocação dinâmica implementada aqui - array dinâmico para manter as dicas já sorteadas (-1 = campo vazio)
    static int *dicasSorteadas = NULL;
    static int inicializado = 0;
    
    // Inicializa o array na primeira chamada
    if(!inicializado){
        dicasSorteadas = (int *)calloc(10, sizeof(int));
        if(dicasSorteadas == NULL){
            printf("Erro ao alocar memória para dicas sorteadas!\n");
            return;
        }
        // Inicializa todos os valores com -1
        for(int i = 0; i < 10; i++){
            dicasSorteadas[i] = -1;
        }
        inicializado = 1;
    }
    int jaFoiSorteada = 0;
    int indiceVazio = -1;
    int sortearDica;

    // Declara��o de vari�veis e atribui��o de valores

    int dicasUtilizadas = estadoAtualJogo->dicasUsadas;

    // Verifica se o limite m�ximo de dicas foi atingido

    if(dicasUtilizadas == 2){
        // Exibe uma mensagem e sai da fun��o
        printf("\nLimite m�ximo de 2 dicas atingido!\n");
        return; 
    }else{
    
        if(dicasUtilizadas == 0){ // Exibe a dica 1
            srand(time(NULL));
            
            // Sorteia uma dica que ainda não foi sorteada
            do{
                sortearDica = rand() % producaoSorteada.totalDicas;
                jaFoiSorteada = 0;
                indiceVazio = -1;
                
                // Verifica se a dica já foi sorteada e encontra o primeiro campo vazio
                for(int i = 0; i < 10; i++){
                    if(dicasSorteadas[i] == sortearDica){
                        jaFoiSorteada = 1;
                        break;
                    }
                    if(dicasSorteadas[i] == -1 && indiceVazio == -1){
                        indiceVazio = i;
                    }
                }
            }while(jaFoiSorteada);
            
            // Adiciona a dica sorteada no primeiro campo vazio
            if(indiceVazio != -1){
                dicasSorteadas[indiceVazio] = sortearDica;
            }
            
            printf("\nDICA EXTRA 1: %s\n", producaoSorteada.dicas[sortearDica]);
        }else{ // Exibe a dica 2
            srand(time(NULL));
            
            // Sorteia uma dica que ainda não foi sorteada
            do{
                sortearDica = rand() % producaoSorteada.totalDicas;
                jaFoiSorteada = 0;
                indiceVazio = -1;
                
                // Verifica se a dica já foi sorteada e encontra o primeiro campo vazio
                for(int i = 0; i < 10; i++){
                    if(dicasSorteadas[i] == sortearDica){
                        jaFoiSorteada = 1;
                        break;
                    }
                    if(dicasSorteadas[i] == -1 && indiceVazio == -1){
                        indiceVazio = i;
                    }
                }
            }while(jaFoiSorteada);
            
            // Adiciona a dica sorteada no primeiro campo vazio
            if(indiceVazio != -1){
                dicasSorteadas[indiceVazio] = sortearDica;
            }
            
            printf("\nDICA EXTRA 2: %s\n", producaoSorteada.dicas[sortearDica]);
        }

        // Atualiza as vari�veis de controle de dicas e a pontua��o

        dicasUtilizadas++;
        estadoAtualJogo->dicasUsadas = dicasUtilizadas;
        estadoAtualJogo->pontuacao += -3;
    }//else

    return;
}//pedirDica
