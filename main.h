/**
 * @file main.h
 * @author Thayane Nascimento Rezende (thayanenascimentorezende@alunos.utfpr.edu.br)
 * @brief Header do arquivo 'main.c'
 * @version 0.2
 * @date 2025-11-12
 * @copyright Copyright (c) 2025
 */

#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>

// =======================
// Definições de constantes
// =======================
#define NUM_PRODUCOES 25      // Número máximo de produções cadastráveis
#define MAX_PERGUNTAS 100     // Número máximo de perguntas ou dicas
#define TAM_NOME 100          // Tamanho máximo para nome de produção ou jogador
#define TAM_DICA 200          // Tamanho máximo de cada dica
#define MAX_DICAS 5           // Máximo de dicas por produção

// =======================
// Enum 'TipoProducao'
// =======================
typedef enum {
    SERIE = 1,
    FILME
} TipoProducao;

// =======================
// Enum 'Dificuldade'
// =======================
typedef enum {
    FACIL = 1,
    MEDIO,
    DIFICIL
} Dificuldade;

// =======================
// Struct 'Producao'
// =======================
typedef struct {
    int tipoProducao;        // Tipo: SERIE ou FILME
    char *nomeProducao;      // Nome da produção (alocado dinamicamente)
    char **dicas;            // Array de strings com dicas (alocação dinâmica)
    int totalDicas;          // Quantidade de dicas cadastradas
    int dificuldade;         // FACIL, MEDIO ou DIFICIL
} Producao;

// =======================
// Struct 'Jogador'
// =======================
typedef struct {
    char *nomeJogador;       // Nome do jogador (alocado dinamicamente)
    int pontos;              // Pontuação acumulada
} Jogador;

// =======================
// Struct 'EstadoAtualJogo'
// =======================
typedef struct {
    char *nomeProducaoSorteada;  // Nome da produção sorteada (dinâmico)
    char *statusAtual;           // Status do jogo (_ para letras não descobertas)
    int errosRestantes;          // Quantidade de erros restantes
    int pontuacao;               // Pontuação do jogador
    int dicasUsadas;             // Quantidade de dicas já usadas
    char *letrasTentadas;        // Letras já tentadas (dinâmico)
} EstadoAtualJogo;

// =======================
// Cabeçalhos das funções
// =======================

// Funções do jogo
void cadastraJogador(Jogador *jogador);
void preencheProducao(Producao producao[]);
void inicializarJogo(EstadoAtualJogo *estadoAtualJogo, Producao producao[]);
void inicializarMascara(Producao producaoSorteada, EstadoAtualJogo *estadoAtualJogo);
char converteParaMaiuscula(char letra);
void processarTentativaDeLetra(EstadoAtualJogo *estadoAtualJogo);
void exibeDica(EstadoAtualJogo *estadoAtualJogo, Producao producaoSorteada);
void chutarPalavra(EstadoAtualJogo *estadoAtualJogo);
char normalizarLetra(char c);
void jogar(EstadoAtualJogo *estadoAtualJogo, Producao producao[], int tempoLimite);

// Funções de gerenciamento de produções
void menuGerenciamentoProducoes(Producao producoes[], int *totalProducoes);
void exportarParaCSV(Producao producoes[], int total);

#endif /* MAIN_H */
