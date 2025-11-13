/**
 * @file processarTentativaDeLetra.c
 * @author Thayane Nascimento Rezende (thayanenascimentorezende@alunos.utfpr.edu.br)
 * @brief Arquivo da fun��o 'processarTentativaDeLetra'
 * @version 0.1
 * @date 2025-11-08
 * @copyright Copyright (c) 2025
 */

// Inclus�o de bibliotecas e arquivos

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "main.h"

// In�cio da fun��o 'processarTentativaDeLetra'

/**
 * @brief Fun��o que processa a tentativa de letra que o usu�rio digitar
 * @param estadoAtualJogo ponteiro que aponta para uma vari�vel que cont�m as informa��es do estado atual do jogo
 */

void processarTentativaDeLetra(EstadoAtualJogo *estadoAtualJogo){

    // Declara��o de vari�veis e atribui��o de valores

    char letra;
    int repetido, invalido, acertou = 0;
    int tamProducaoSorteada = strlen(estadoAtualJogo->nomeProducaoSorteada);

    // Solicita e letra para o usu�rio e verifica se a letra � repetida
        
        do{
            // Zera as vari�veis no in�cio da cada tentativa

            repetido = 0, invalido = 0;

            // Verifica e armazena o tamanho do vetor de letras tentadas 

            int tamLetrasTentadas = strlen(estadoAtualJogo->letrasTentadas);


            // Recebe a letra do usu�rio
            
            printf("\nDigite a letra: ");
            scanf(" %c", &letra); // o espa�o serve para ignorar espa�os em branco
            getchar(); // consome o 'ENTER' pressionado

            // Se não for letra, executa o bloco

            if(!isalpha(letra)){ // 'isalpha' verifica se o caractere � uma letra do alfabeto 
                printf("Entrada invalida! Digite apenas letras.\n");
                invalido = 1; // for�a o loop (do/while) a continuar
                continue; // pula a itera��o atual
            }//if

            // Se a letra for inv�lida, n�o � necess�rio checar se � repetida

            if(invalido > 0)
                continue; // Pula para a pr�xima itera��o do loop

            // Converte a letra para mai�scula antes de checar a repeti��o (padroniza a letra para facilitar compara��o)

            letra = converteParaMaiuscula(letra);

            // Remove caractere especial da letra (se houver)

            letra = normalizarLetra(letra);

            // Verifica se a letra � repetida (se est� no vetor de letras tentadas)
            
            for(int i = 0; i < tamLetrasTentadas; i++){
                if(letra == estadoAtualJogo->letrasTentadas[i]){
                    printf("Letra '%c' ja foi tentada! Tente outra.\n", letra);
                    repetido++;
                    break;
                }//if
            }//for
        }while(repetido > 0 || invalido > 0);

        // La�o de repeti��o que percorre todo o vetor do nome da produ��o

        for(int i = 0; i < tamProducaoSorteada; i++){

            // Normalizar a compara��o

            // Pega o caractere original

            char charOriginal = estadoAtualJogo->nomeProducaoSorteada[i];

            // Cria uma c�pia normnalizada dele

            char charNormalizado = normalizarLetra(charOriginal);

            // Compara a letra (normalizada) do usu�rio com a letra (normalizada) da produ��o

            if(letra == charNormalizado){
                estadoAtualJogo->statusAtual[i] = charOriginal;
                acertou++;
            }//if
        }//for

        int tamAtual = strlen(estadoAtualJogo->letrasTentadas);
        int tamMaximo = 26;

        // S� adiciona a letra se houver espa�o

        if(tamAtual < tamMaximo){
            estadoAtualJogo->letrasTentadas[tamAtual] = letra;
            estadoAtualJogo->letrasTentadas[tamAtual + 1] = '\0';
        }//if

        // Exibe uma mensagem para o usu�rio a respeito da letra tentada

        if(acertou > 0){
            printf("Acertou! A letra '%c' aparece %d vez(es).\n", letra, acertou);
        }else{
            estadoAtualJogo->errosRestantes = estadoAtualJogo->errosRestantes - 1;
            printf("Letra '%c' nao encontrada. Erros restantes: %d\n", letra, estadoAtualJogo->errosRestantes);
        }//else

    return;
}//processarTentativaDeLetra