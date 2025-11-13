/**
 * @file normalizarLetra.c
 * @author Thayane Nascimento Rezende (thayanenascimentorezende@alunos.utfpr.edu.br)
 * @brief Arquivo da função 'normalizarLetra'
 * @version 0.1
 * @date 2025-11-10
 * @copyright Copyright (c) 2025
 */

// Inclusão de arquivos

#include <locale.h>
#include "main.h"

// Iní­cio da função 'normalizarLetra'

/**
 * @brief Função que remove acentos de um caractere (normaliza)
 * @param c caractere a ser normalizado
 * @return char caractere normalizado
 */

char normalizarLetra(char c){

    unsigned char uc = (unsigned char)c;
    
    // switch para verificar o caractere
    
    switch (uc) {
        // 'A' com acento
        case 193: // Á
        case 192: // À
        case 195: // Ã
        case 194: // Â
        case 196: // Ä
            return 'A';

        // 'E' com acento
        case 201: // É
        case 200: // È
        case 202: // Ê
        case 203: // Ë
            return 'E';

        // 'I' com acento
        case 205: // Í
        case 204: // Ì
        case 206: // Î
        case 207: // Ï
            return 'I';

        // 'O' com acento
        case 211: // Ó
        case 210: // Ò
        case 213: // Õ
        case 212: // Ô
        case 214: // Ö
            return 'O';

        // 'U' com acento
        case 218: // Ú
        case 217: // Ù
        case 219: // Û
        case 220: // Ü
            return 'U';

        // 'C' com cedilha
        case 199: // Ç
            return 'C';

        default:
            return c;
    }//switch

}//normalizarLetras