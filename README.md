# 🎮 Jogo de Adivinhação de Filmes e Séries (Networds)

Um jogo interativo no estilo "Jogo da Forca" onde os jogadores tentam adivinhar nomes de filmes e séries da Netflix baseando-se em dicas. Desenvolvido em C com foco em gerenciamento de memória dinâmica e persistência de dados.

## 📋 Descrição do Projeto

O jogo desafia os jogadores a descobrirem produções cinematográficas (filmes e séries) através de um sistema de tentativas de letras, chutes de palavras e uso estratégico de dicas. O projeto implementa:

- **Sistema de pontuação** com penalidades por tempo e uso de dicas
- **Gerenciamento completo de produções** (CRUD)
- **Persistência de dados** em arquivos CSV e binários
- **Interface em português** com tratamento de caracteres especiais
- **Alocação dinâmica de memória** para todas as estruturas de dados

## 🛠️ Como Compilar

### Pré-requisitos
- Compilador C (GCC recomendado)
- Sistema operacional: Windows, Linux ou macOS
- Terminal/Prompt de comando

### Compilação no Windows

1. **Abra o Prompt de Comando** ou PowerShell
2. **Navegue até a pasta do projeto**:
   ```cmd
   cd caminho\para\a\pasta\do\projeto
   ```

3. **Compile todos os arquivos**:
   ```cmd
   gcc -o jogo.exe main.c cadastraJogador.c preencheProducao.c inicializarJogo.c inicializarMascara.c converteParaMaiuscula.c processarTentativaDeLetra.c exibeDica.c chutarPalavra.c normalizarLetra.c jogar.c menuGerenciamentoProducoes.c
   ```

### Compilação no Linux/macOS

1. **Abra o terminal**
2. **Navegue até a pasta do projeto**:
   ```bash
   cd caminho/para/a/pasta/do/projeto
   ```

3. **Compile todos os arquivos**:
   ```bash
   gcc -o jogo main.c cadastraJogador.c preencheProducao.c inicializarJogo.c inicializarMascara.c converteParaMaiuscula.c processarTentativaDeLetra.c exibeDica.c chutarPalavra.c normalizarLetra.c jogar.c menuGerenciamentoProducoes.c
   ```

## 🎯 Como Executar

### Execução no Windows
```cmd
jogo.exe
```

### Execução no Linux/macOS
```bash
./jogo
```

## 📁 Estrutura de Arquivos

```
📦 projeto-jogo/
├── 🎯 main.c                    # Arquivo principal
├── 📄 main.h                    # Header com definições e structs
├── 👤 cadastraJogador.c         # Cadastro de jogadores
├── 🎬 preencheProducao.c        # Popula banco de dados inicial
├── 🎮 inicializarJogo.c         # Inicialização do estado do jogo
├── 🎭 inicializarMascara.c      # Cria máscara da palavra
├── 🔠 converteParaMaiuscula.c   # Conversão de caracteres
├── 💬 processarTentativaDeLetra.c # Processa tentativas
├── 💡 exibeDica.c               # Sistema de dicas
├── 🎯 chutarPalavra.c           # Processa chutes completos
├── 🔤 normalizarLetra.c         # Normalização de caracteres
├── ⏱️ jogar.c                   # Loop principal do jogo
├── ⚙️ menuGerenciamentoProducoes.c # Menu administrativo
├── 📊 filmes.csv               # Banco de dados em CSV
└── 💾 filmes.bin               # Banco de dados binário (gerado)
```

## 🎮 Como Jogar

### Menu Principal
1. **Iniciar o jogo** - Começa uma nova partida
2. **Gerenciar produções** - Menu administrativo

### Durante o Jogo
- **Tentar uma letra**: Digite letras para revelar na palavra
- **Chutar a palavra**: Tente adivinhar a produção completa (risco alto!)
- **Pedir dica**: Revele uma dica extra (-3 pontos)

### Sistema de Pontuação
- **+10 pontos** por acertar a produção
- **+20 pontos** por acertar com chute completo
- **-3 pontos** por cada dica usada
- **-2 pontos** por minuto utilizado
- **70 pontos** para vencer o jogo

## ⚙️ Gerenciamento de Produções

No menu de configurações, você pode:
- ✅ **Listar** todas as produções
- ➕ **Adicionar** novas produções
- ❌ **Remover** produções existentes
- 🔄 **Resetar** para configuração padrão

## 🏆 Características Técnicas

- **Memória Dinâmica**: Uso intensivo de `malloc()` e `free()`
- **Persistência**: Dados salvos em CSV e formato binário
- **Normalização**: Tratamento de acentos e caracteres especiais
- **Cronômetro**: Sistema de tempo limite por rodada
- **Validação**: Entrada robusta e tratamento de erros

## 🐛 Solução de Problemas

### Erro de Compilação
- Verifique se todos os arquivos `.c` estão na mesma pasta
- Certifique-se de ter o GCC instalado

### Arquivo Não Encontrado
- O jogo cria automaticamente `filmes.csv` na primeira execução
- Se o arquivo for deletado, execute `preencheProducao()` para recriar

### Caracteres Especiais
- O sistema normaliza automaticamente letras com acento
- Funciona melhor em terminais que suportam UTF-8

## 📝 Notas de Desenvolvimento

- Desenvolvido como projeto acadêmico para UTFPR
- Foco em boas práticas de programação em C
- Implementação completa de gerenciamento de memória
- Código documentado em português

---

**Desenvolvido por:** Thayane Nascimento Rezende

                      Isabelle Beatriz Lopes
                      
                      Matheus Miquelão Prado
                      
**Instituição:** UTFPR - Universidade Tecnológica Federal do Paraná
