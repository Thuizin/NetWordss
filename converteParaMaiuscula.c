/**
 * @file converteParaMaiuscula.c
 * @author Thayane Nascimento Rezende (thayanenascimentorezende@alunos.utfpr.edu.br)
 * @brief Arquivo da função 'converteParaMaiuscula'
 * @version 0.1
 * @date 2025-11-08
 * @copyright Copyright (c) 2025
 */

// Inclusão de bibliotecas e arquivos

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "main.h"

// Iní­cio da função 'converteParaMaiuscula'

/**
 * @brief Função que converte a letra em maiúscula
 * @param letra letra a ser convertida
 * @return char letra convertida em maiúscula
 */

char converteParaMaiuscula(char letra){

    // Retorna a letra convertida para maiúscula
    return letra = toupper(letra);
    
}//converteParaMaiuscula