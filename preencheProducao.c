#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"

// Função auxiliar para alocar e copiar string dinamicamente
// Alocação dinâmica implementada aqui
static void alocarECopiarString(char **dest, const char *src, int tamanho) {
    *dest = (char *)malloc(tamanho * sizeof(char));
    if(*dest == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }
    strcpy(*dest, src);
}

// Função auxiliar para inicializar uma produção com alocação dinâmica
// Alocação dinâmica implementada aqui
static void inicializarProducao(Producao *p, int totalDicas) {
    // Aloca memória para nomeProducao
    p->nomeProducao = (char *)malloc(51 * sizeof(char));
    if(p->nomeProducao == NULL) {
        printf("Erro ao alocar memória para nomeProducao!\n");
        exit(1);
    }
    
    // Aloca memória para array de dicas
    p->dicas = (char **)malloc(totalDicas * sizeof(char *));
    if(p->dicas == NULL) {
        printf("Erro ao alocar memória para dicas!\n");
        free(p->nomeProducao);
        exit(1);
    }
    
    // Aloca memória para cada dica
    for(int i = 0; i < totalDicas; i++) {
        p->dicas[i] = (char *)malloc(201 * sizeof(char));
        if(p->dicas[i] == NULL) {
            printf("Erro ao alocar memória para dica %d!\n", i);
            // Libera memória já alocada
            for(int j = 0; j < i; j++) {
                free(p->dicas[j]);
            }
            free(p->dicas);
            free(p->nomeProducao);
            exit(1);
        }
    }
}

void preencheProducao(Producao producao[]) {

    // 1
    // Alocação dinâmica implementada aqui
    inicializarProducao(&producao[0], 10);
    producao[0].tipoProducao = 2;
    strcpy(producao[0].nomeProducao, "HARRY POTTER E A PEDRA FILOSOFAL");
    strcpy(producao[0].dicas[0], "Garoto descobre que é bruxo");
    strcpy(producao[0].dicas[1], "Primeiro ano em escola mágica");
    strcpy(producao[0].dicas[2], "Amizade, coragem e destino");
    strcpy(producao[0].dicas[3], "Pedra misteriosa com poder de imortalidade");
    strcpy(producao[0].dicas[4], "Vilão sem nariz");
    strcpy(producao[0].dicas[5], "Trio inseparável");
    strcpy(producao[0].dicas[6], "Coruja mensageira");
    strcpy(producao[0].dicas[7], "Quadribol e magia");
    strcpy(producao[0].dicas[8], "Casa Grifinória");
    strcpy(producao[0].dicas[9], "Baseado nos livros de J.K. Rowling");
    producao[0].totalDicas = 10;
    producao[0].dificuldade = 1;

    // 2
    // Alocação dinâmica implementada aqui
    inicializarProducao(&producao[1], 10);
    producao[1].tipoProducao = 1;
    strcpy(producao[1].nomeProducao, "STRANGER THINGS");
    strcpy(producao[1].dicas[0], "Crianças enfrentam monstros sobrenaturais");
    strcpy(producao[1].dicas[1], "Pequena cidade dos anos 80");
    strcpy(producao[1].dicas[2], "Garota com poderes telecinéticos");
    strcpy(producao[1].dicas[3], "Mundo invertido");
    strcpy(producao[1].dicas[4], "Referências à cultura pop dos anos 80");
    strcpy(producao[1].dicas[5], "Amizade e coragem contra o mal");
    strcpy(producao[1].dicas[6], "Laboratório secreto");
    strcpy(producao[1].dicas[7], "Criatura chamada Demogorgon");
    strcpy(producao[1].dicas[8], "Personagem chamada Eleven");
    strcpy(producao[1].dicas[9], "Sucesso da Netflix");
    producao[1].totalDicas = 10;
    producao[1].dificuldade = 2;

    // 3
    // Alocação dinâmica implementada aqui
    inicializarProducao(&producao[2], 10);
    producao[2].tipoProducao = 2;
    strcpy(producao[2].nomeProducao, "O SENHOR DOS ANÉIS: A SOCIEDADE DO ANEL");
    strcpy(producao[2].dicas[0], "Jornada para destruir um anel poderoso");
    strcpy(producao[2].dicas[1], "Magos, elfos e hobbits");
    strcpy(producao[2].dicas[2], "Paisagens épicas da Terra Média");
    strcpy(producao[2].dicas[3], "Vilão chamado Sauron");
    strcpy(producao[2].dicas[4], "Anel com escrita élfica");
    strcpy(producao[2].dicas[5], "Personagem principal é Frodo");
    strcpy(producao[2].dicas[6], "Mentor é Gandalf");
    strcpy(producao[2].dicas[7], "Baseado na obra de Tolkien");
    strcpy(producao[2].dicas[8], "Amizade e sacrifício");
    strcpy(producao[2].dicas[9], "Trilogia premiada com Oscars");
    producao[2].totalDicas = 10;
    producao[2].dificuldade = 2;

    // 4
    // Alocação dinâmica implementada aqui
    inicializarProducao(&producao[3], 10);
    producao[3].tipoProducao = 2;
    strcpy(producao[3].nomeProducao, "VINGADORES: GUERRA INFINITA");
    strcpy(producao[3].dicas[0], "Heróis se unem para lutar contra vilão cósmico");
    strcpy(producao[3].dicas[1], "Joias do Infinito");
    strcpy(producao[3].dicas[2], "Vilão quer equilibrar o universo");
    strcpy(producao[3].dicas[3], "Heróis desaparecem com estalar de dedos");
    strcpy(producao[3].dicas[4], "Homem de Ferro e Thor em destaque");
    strcpy(producao[3].dicas[5], "Guardiões da Galáxia participam");
    strcpy(producao[3].dicas[6], "Thanos é o antagonista principal");
    strcpy(producao[3].dicas[7], "Filme da Marvel Studios");
    strcpy(producao[3].dicas[8], "Continuação de Guerra Civil");
    strcpy(producao[3].dicas[9], "Final impactante e triste");
    producao[3].totalDicas = 10;
    producao[3].dificuldade = 2;

    // 5
    // Alocação dinâmica implementada aqui
    inicializarProducao(&producao[4], 10);
    producao[4].tipoProducao = 1;
    strcpy(producao[4].nomeProducao, "BREAKING BAD");
    strcpy(producao[4].dicas[0], "Professor de química vira criminoso");
    strcpy(producao[4].dicas[1], "Negócios ilícitos com metanfetamina");
    strcpy(producao[4].dicas[2], "Personagem principal usa chapéu e óculos escuros");
    strcpy(producao[4].dicas[3], "Parceiro mais jovem e impulsivo");
    strcpy(producao[4].dicas[4], "Carro velho e deserto");
    strcpy(producao[4].dicas[5], "Personagem chamado Heisenberg");
    strcpy(producao[4].dicas[6], "Relação conturbada com a esposa");
    strcpy(producao[4].dicas[7], "Cenas intensas e tensão crescente");
    strcpy(producao[4].dicas[8], "Spin-off chamado Better Call Saul");
    strcpy(producao[4].dicas[9], "Considerada uma das melhores séries da história");
    producao[4].totalDicas = 10;
    producao[4].dificuldade = 2;

    // 6
    // Alocação dinâmica implementada aqui
    inicializarProducao(&producao[5], 10);
    producao[5].tipoProducao = 2;
    strcpy(producao[5].nomeProducao, "TITANIC");
    strcpy(producao[5].dicas[0], "Romance trágico a bordo de um navio");
    strcpy(producao[5].dicas[1], "Baseado em fatos reais");
    strcpy(producao[5].dicas[2], "Desastre em 1912");
    strcpy(producao[5].dicas[3], "Casal de classes sociais diferentes");
    strcpy(producao[5].dicas[4], "Cenário congelante no oceano Atlântico");
    strcpy(producao[5].dicas[5], "Personagens Jack e Rose");
    strcpy(producao[5].dicas[6], "Direção de James Cameron");
    strcpy(producao[5].dicas[7], "Canção tema famosa de Celine Dion");
    strcpy(producao[5].dicas[8], "Navio colide com um iceberg");
    strcpy(producao[5].dicas[9], "Vencedor de vários Oscars");
    producao[5].totalDicas = 10;
    producao[5].dificuldade = 1;

    // 7
    // Alocação dinâmica implementada aqui
    inicializarProducao(&producao[6], 10);
    producao[6].tipoProducao = 1;
    strcpy(producao[6].nomeProducao, "LA CASA DE PAPEL");
    strcpy(producao[6].dicas[0], "Roubo planejado em larga escala");
    strcpy(producao[6].dicas[1], "Personagens com nomes de cidades");
    strcpy(producao[6].dicas[2], "Máscaras e macacões vermelhos");
    strcpy(producao[6].dicas[3], "Líder chamado Professor");
    strcpy(producao[6].dicas[4], "Invasão à Casa da Moeda da Espanha");
    strcpy(producao[6].dicas[5], "Música ‘Bella Ciao’ como símbolo");
    strcpy(producao[6].dicas[6], "Mistura de ação e drama");
    strcpy(producao[6].dicas[7], "Personagem Tóquio é narradora");
    strcpy(producao[6].dicas[8], "Série espanhola da Netflix");
    strcpy(producao[6].dicas[9], "Sucesso global com várias temporadas");
    producao[6].totalDicas = 10;
    producao[6].dificuldade = 2;

    // 8
    // Alocação dinâmica implementada aqui
    inicializarProducao(&producao[7], 10);
    producao[7].tipoProducao = 2;
    strcpy(producao[7].nomeProducao, "O REI LEÃO");
    strcpy(producao[7].dicas[0], "Filhote foge após tragédia com o pai");
    strcpy(producao[7].dicas[1], "Reino animal na savana africana");
    strcpy(producao[7].dicas[2], "Vilão invejoso e traiçoeiro");
    strcpy(producao[7].dicas[3], "Amigos hilários chamados Timão e Pumba");
    strcpy(producao[7].dicas[4], "Animação da Disney");
    strcpy(producao[7].dicas[5], "Música ‘Hakuna Matata’");
    strcpy(producao[7].dicas[6], "Tema de liderança e coragem");
    strcpy(producao[7].dicas[7], "Ciclo da vida");
    strcpy(producao[7].dicas[8], "Baseado em histórias de lealdade e superação");
    strcpy(producao[7].dicas[9], "Teve remake em live action");
    producao[7].totalDicas = 10;
    producao[7].dificuldade = 1;

    // 9
    // Alocação dinâmica implementada aqui
    inicializarProducao(&producao[8], 10);
    producao[8].tipoProducao = 1;
    strcpy(producao[8].nomeProducao, "GAME OF THRONES");
    strcpy(producao[8].dicas[0], "Disputa entre reinos por um trono");
    strcpy(producao[8].dicas[1], "Baseada em livros de George R. R. Martin");
    strcpy(producao[8].dicas[2], "Dragões e magia");
    strcpy(producao[8].dicas[3], "Casamentos nem sempre felizes");
    strcpy(producao[8].dicas[4], "Personagem chamada Daenerys");
    strcpy(producao[8].dicas[5], "Muitos personagens morrem inesperadamente");
    strcpy(producao[8].dicas[6], "Reinos e intrigas políticas");
    strcpy(producao[8].dicas[7], "Frase famosa: ‘Winter is Coming’");
    strcpy(producao[8].dicas[8], "Produção da HBO");
    strcpy(producao[8].dicas[9], "Final controverso entre fãs");
    producao[8].totalDicas = 10;
    producao[8].dificuldade = 3;

    // 10
    // Alocação dinâmica implementada aqui
    inicializarProducao(&producao[9], 10);
    producao[9].tipoProducao = 2;
    strcpy(producao[9].nomeProducao, "DE VOLTA PARA O FUTURO");
    strcpy(producao[9].dicas[0], "Viagem no tempo em um carro modificado");
    strcpy(producao[9].dicas[1], "Doutor excêntrico e adolescente aventureiro");
    strcpy(producao[9].dicas[2], "Carro DeLorean");
    strcpy(producao[9].dicas[3], "Relâmpago e relógio da torre");
    strcpy(producao[9].dicas[4], "Anos 50 e anos 80 em conflito");
    strcpy(producao[9].dicas[5], "Mãe se apaixona pelo próprio filho sem saber");
    strcpy(producao[9].dicas[6], "Frase: ‘Grande Scott!’");
    strcpy(producao[9].dicas[7], "Trilogia clássica dos anos 80");
    strcpy(producao[9].dicas[8], "Produzido por Steven Spielberg");
    strcpy(producao[9].dicas[9], "Viagens temporais e paradoxos");
    producao[9].totalDicas = 10;
    producao[9].dificuldade = 2;

    // 11
    // Alocação dinâmica implementada aqui
    inicializarProducao(&producao[10], 10);
    producao[10].tipoProducao = 1;
    strcpy(producao[10].nomeProducao, "THE WITCHER");
    strcpy(producao[10].dicas[0], "Caçador de monstros mutante");
    strcpy(producao[10].dicas[1], "Espadas e magia");
    strcpy(producao[10].dicas[2], "Baseado em livros poloneses");
    strcpy(producao[10].dicas[3], "Personagem principal se chama Geralt de Rivia");
    strcpy(producao[10].dicas[4], "Princesa Ciri e feiticeira Yennefer");
    strcpy(producao[10].dicas[5], "Frase icônica: 'Hmm…'");
    strcpy(producao[10].dicas[6], "Netflix original");
    strcpy(producao[10].dicas[7], "Cenários medievais sombrios");
    strcpy(producao[10].dicas[8], "Criaturas e política se misturam");
    strcpy(producao[10].dicas[9], "Base para jogos famosos");
    producao[10].totalDicas = 10;
    producao[10].dificuldade = 3;

    // 12
    // Alocação dinâmica implementada aqui
    inicializarProducao(&producao[11], 10);
    producao[11].tipoProducao = 2;
        strcpy(producao[11].nomeProducao, "O DIABO VESTE PRADA");
        strcpy(producao[11].dicas[0], "Assistente entra em revista de moda exigente");
        strcpy(producao[11].dicas[1], "Chefe fria e perfeccionista");
        strcpy(producao[11].dicas[2], "Baseado em livro de mesmo nome");
        strcpy(producao[11].dicas[3], "Figurinos icônicos e glamour");
        strcpy(producao[11].dicas[4], "Nova-iorquino e sofisticado");
        strcpy(producao[11].dicas[5], "Personagens Miranda e Andy");
        strcpy(producao[11].dicas[6], "Comédia e drama profissional");
        strcpy(producao[11].dicas[7], "Explora o mundo da moda e ambição");
        strcpy(producao[11].dicas[8], "Atriz Meryl Streep em papel marcante");
        strcpy(producao[11].dicas[9], "Frase icônica: ‘É tudo’");
        producao[11].totalDicas = 10;
        producao[11].dificuldade = 1;
    
        // 13
        // Alocação dinâmica implementada aqui
        inicializarProducao(&producao[12], 10);
        producao[12].tipoProducao = 1;
        strcpy(producao[12].nomeProducao, "O GAMBITO DA RAINHA");
        strcpy(producao[12].dicas[0], "Garota órfã se torna prodígio do xadrez");
        strcpy(producao[12].dicas[1], "Década de 1960");
        strcpy(producao[12].dicas[2], "Temas de vício e genialidade");
        strcpy(producao[12].dicas[3], "Personagem principal chamada Beth Harmon");
        strcpy(producao[12].dicas[4], "Baseada em minissérie da Netflix");
        strcpy(producao[12].dicas[5], "Cenas com tabuleiros e estratégias mentais");
        strcpy(producao[12].dicas[6], "Foco psicológico e emocional");
        strcpy(producao[12].dicas[7], "Roupa e estética vintage");
        strcpy(producao[12].dicas[8], "Representação feminina no xadrez");
        strcpy(producao[12].dicas[9], "Baseada em livro de Walter Tevis");
        producao[12].totalDicas = 10;
        producao[12].dificuldade = 2;
    
        // 14
        // Alocação dinâmica implementada aqui
        inicializarProducao(&producao[13], 10);
        producao[13].tipoProducao = 2;
        strcpy(producao[13].nomeProducao, "AVATAR: O CAMINHO DA ÁGUA");
        strcpy(producao[13].dicas[0], "Continuação de um sucesso de 2009");
        strcpy(producao[13].dicas[1], "Planeta Pandora e povos azuis");
        strcpy(producao[13].dicas[2], "Direção de James Cameron");
        strcpy(producao[13].dicas[3], "Família e natureza são temas centrais");
        strcpy(producao[13].dicas[4], "Tecnologia 3D avançada");
        strcpy(producao[13].dicas[5], "Elementos aquáticos e novos clãs");
        strcpy(producao[13].dicas[6], "Batalhas entre humanos e Na’vi");
        strcpy(producao[13].dicas[7], "Grande sucesso de bilheteria");
        strcpy(producao[13].dicas[8], "Efeitos visuais impressionantes");
        strcpy(producao[13].dicas[9], "Ambientação em oceanos de Pandora");
        producao[13].totalDicas = 10;
        producao[13].dificuldade = 2;
    
        // 15
        // Alocação dinâmica implementada aqui
        inicializarProducao(&producao[14], 10);
        producao[14].tipoProducao = 1;
        strcpy(producao[14].nomeProducao, "SHERLOCK");
        strcpy(producao[14].dicas[0], "Detetive brilhante e excêntrico");
        strcpy(producao[14].dicas[1], "Ambientada em Londres moderna");
        strcpy(producao[14].dicas[2], "Baseada em histórias de Conan Doyle");
        strcpy(producao[14].dicas[3], "Companheiro chamado Watson");
        strcpy(producao[14].dicas[4], "Uso de dedução lógica e tecnologia");
        strcpy(producao[14].dicas[5], "Ator Benedict Cumberbatch no papel principal");
        strcpy(producao[14].dicas[6], "Vilão carismático chamado Moriarty");
        strcpy(producao[14].dicas[7], "Série britânica com poucos episódios longos");
        strcpy(producao[14].dicas[8], "Produção da BBC");
        strcpy(producao[14].dicas[9], "Cenas cheias de enigmas e suspense");
        producao[14].totalDicas = 10;
        producao[14].dificuldade = 2;
    
        // 16
        // Alocação dinâmica implementada aqui
        inicializarProducao(&producao[15], 10);
        producao[15].tipoProducao = 2;
        strcpy(producao[15].nomeProducao, "INTERESTELAR");
        strcpy(producao[15].dicas[0], "Exploração espacial em busca de novo lar");
        strcpy(producao[15].dicas[1], "Direção de Christopher Nolan");
        strcpy(producao[15].dicas[2], "Temas de tempo, gravidade e amor");
        strcpy(producao[15].dicas[3], "Pai e filha separados por anos-luz");
        strcpy(producao[15].dicas[4], "Buracos negros e dimensões temporais");
        strcpy(producao[15].dicas[5], "Trilha sonora de Hans Zimmer");
        strcpy(producao[15].dicas[6], "Naves e planetas inóspitos");
        strcpy(producao[15].dicas[7], "Drama científico e filosófico");
        strcpy(producao[15].dicas[8], "Atores Matthew McConaughey e Anne Hathaway");
        strcpy(producao[15].dicas[9], "Plot twist com dimensões e tempo");
        producao[15].totalDicas = 10;
        producao[15].dificuldade = 3;
    
        // 17
        // Alocação dinâmica implementada aqui
        inicializarProducao(&producao[16], 10);
        producao[16].tipoProducao = 1;
        strcpy(producao[16].nomeProducao, "PEAKY BLINDERS");
        strcpy(producao[16].dicas[0], "Gangue familiar na Inglaterra pós-guerra");
        strcpy(producao[16].dicas[1], "Líder carismático chamado Thomas Shelby");
        strcpy(producao[16].dicas[2], "Cenário de Birmingham dos anos 1920");
        strcpy(producao[16].dicas[3], "Criminalidade e política");
        strcpy(producao[16].dicas[4], "Estilo elegante e chapéus icônicos");
        strcpy(producao[16].dicas[5], "Série britânica com estética sombria");
        strcpy(producao[16].dicas[6], "Trilha sonora moderna e marcante");
        strcpy(producao[16].dicas[7], "Personagem principal é frio e estratégico");
        strcpy(producao[16].dicas[8], "Netflix disponibiliza todas as temporadas");
        strcpy(producao[16].dicas[9], "Mistura de drama, ação e política");
        producao[16].totalDicas = 10;
        producao[16].dificuldade = 2;
    
        // 18
        // Alocação dinâmica implementada aqui
        inicializarProducao(&producao[17], 10);
        producao[17].tipoProducao = 2;
        strcpy(producao[17].nomeProducao, "O SENHOR DOS ANÉIS: AS DUAS TORRES");
        strcpy(producao[17].dicas[0], "Segunda parte da trilogia épica");
        strcpy(producao[17].dicas[1], "Batalha em Helm’s Deep");
        strcpy(producao[17].dicas[2], "Gollum ganha destaque");
        strcpy(producao[17].dicas[3], "Amizade entre hobbits continua");
        strcpy(producao[17].dicas[4], "Paisagens da Nova Zelândia");
        strcpy(producao[17].dicas[5], "Temas de lealdade e guerra");
        strcpy(producao[17].dicas[6], "Criaturas e exércitos imensos");
        strcpy(producao[17].dicas[7], "Direção de Peter Jackson");
        strcpy(producao[17].dicas[8], "Baseado em Tolkien");
        strcpy(producao[17].dicas[9], "Continuação direta da Sociedade do Anel");
        producao[17].totalDicas = 10;
        producao[17].dificuldade = 2;
    
        // 19
        // Alocação dinâmica implementada aqui
        inicializarProducao(&producao[18], 10);
        producao[18].tipoProducao = 2;
        strcpy(producao[18].nomeProducao, "O HOBBIT: UMA JORNADA INESPERADA");
        strcpy(producao[18].dicas[0], "Viagem de um hobbit com anões");
        strcpy(producao[18].dicas[1], "Dragão chamado Smaug");
        strcpy(producao[18].dicas[2], "Baseado em livro anterior a O Senhor dos Anéis");
        strcpy(producao[18].dicas[3], "Aventura e comédia misturadas");
        strcpy(producao[18].dicas[4], "Protagonista se chama Bilbo Baggins");
        strcpy(producao[18].dicas[5], "Atores de renome em universo compartilhado");
        strcpy(producao[18].dicas[6], "Trilogia de fantasia épica");
        strcpy(producao[18].dicas[7], "Cenários deslumbrantes");
        strcpy(producao[18].dicas[8], "Encontro com Gollum");
        strcpy(producao[18].dicas[9], "Dirigido também por Peter Jackson");
        producao[18].totalDicas = 10;
        producao[18].dificuldade = 2;
    
        // 20
        // Alocação dinâmica implementada aqui
        inicializarProducao(&producao[19], 10);
        producao[19].tipoProducao = 1;
        strcpy(producao[19].nomeProducao, "THE LAST OF US");
        strcpy(producao[19].dicas[0], "Baseada em jogo de videogame");
        strcpy(producao[19].dicas[1], "Apocalipse causado por fungo");
        strcpy(producao[19].dicas[2], "Homem e garota cruzam os EUA");
        strcpy(producao[19].dicas[3], "Drama e sobrevivência");
        strcpy(producao[19].dicas[4], "Atores Pedro Pascal e Bella Ramsey");
        strcpy(producao[19].dicas[5], "Produção da HBO");
        strcpy(producao[19].dicas[6], "Relação de paternidade e trauma");
        strcpy(producao[19].dicas[7], "Infectados e ação intensa");
        strcpy(producao[19].dicas[8], "Adaptação fiel ao jogo original");
        strcpy(producao[19].dicas[9], "Série aclamada pela crítica");
        producao[19].totalDicas = 10;
        producao[19].dificuldade = 2;
    
        // 21
        // Alocação dinâmica implementada aqui
        inicializarProducao(&producao[20], 10);
        producao[20].tipoProducao = 2;
        strcpy(producao[20].nomeProducao, "HARRY POTTER E AS RELÍQUIAS DA MORTE PARTE 2");
        strcpy(producao[20].dicas[0], "Batalha final em Hogwarts");
        strcpy(producao[20].dicas[1], "Amizade e coragem culminam em guerra");
        strcpy(producao[20].dicas[2], "Vilão retorna com força total");
        strcpy(producao[20].dicas[3], "Objetos mágicos poderosos são destruídos");
        strcpy(producao[20].dicas[4], "Morte e sacrifício");
        strcpy(producao[20].dicas[5], "Final emocionante da saga");
        strcpy(producao[20].dicas[6], "Feitiços e batalhas intensas");
        strcpy(producao[20].dicas[7], "Amor vence o mal");
        strcpy(producao[20].dicas[8], "Música épica e encerramento perfeito");
        strcpy(producao[20].dicas[9], "Último filme da franquia principal");
        producao[20].totalDicas = 10;
        producao[20].dificuldade = 3;
    
        // 22
        // Alocação dinâmica implementada aqui
        inicializarProducao(&producao[21], 10);
        producao[21].tipoProducao = 1;
        strcpy(producao[21].nomeProducao, "FRIENDS");
        strcpy(producao[21].dicas[0], "Seis amigos em Nova York");
        strcpy(producao[21].dicas[1], "Cenário principal é um café");
        strcpy(producao[21].dicas[2], "Humor e amizade nos anos 90");
        strcpy(producao[21].dicas[3], "Casais vão e voltam");
        strcpy(producao[21].dicas[4], "Personagens: Ross, Rachel, Joey, Chandler, Monica e Phoebe");
        strcpy(producao[21].dicas[5], "Música tema com palmas");
        strcpy(producao[21].dicas[6], "Sitcom clássica da TV americana");
        strcpy(producao[21].dicas[7], "Apartamento roxo famoso");
        strcpy(producao[21].dicas[8], "Frases icônicas e humor leve");
        strcpy(producao[21].dicas[9], "Sucesso até hoje com reprises");
        producao[21].totalDicas = 10;
        producao[21].dificuldade = 1;
    
        // 23
        // Alocação dinâmica implementada aqui
        inicializarProducao(&producao[22], 10);
        producao[22].tipoProducao = 2;
        strcpy(producao[22].nomeProducao, "OS VINGADORES: ULTIMATO");
        strcpy(producao[22].dicas[0], "Confronto final contra vilão cósmico");
        strcpy(producao[22].dicas[1], "Viagem no tempo para recuperar joias");
        strcpy(producao[22].dicas[2], "Heróis reunidos uma última vez");
        strcpy(producao[22].dicas[3], "Sacrifícios emocionantes");
        strcpy(producao[22].dicas[4], "Homem de Ferro, Capitão América e Thor em destaque");
        strcpy(producao[22].dicas[5], "Cena épica de batalha com todos os heróis");
        strcpy(producao[22].dicas[6], "Frase ‘Eu sou inevitável’");
        strcpy(producao[22].dicas[7], "Filme mais lucrativo por um tempo");
        strcpy(producao[22].dicas[8], "Conclusão da saga do infinito");
        strcpy(producao[22].dicas[9], "Direção dos irmãos Russo");
        producao[22].totalDicas = 10;
        producao[22].dificuldade = 3;
    
        // 24
        // Alocação dinâmica implementada aqui
        inicializarProducao(&producao[23], 10);
        producao[23].tipoProducao = 2;
        strcpy(producao[23].nomeProducao, "MULAN");
        strcpy(producao[23].dicas[0], "Mulher se disfarça para lutar pelo pai");
        strcpy(producao[23].dicas[1], "Baseado em lenda chinesa");
        strcpy(producao[23].dicas[2], "Animação clássica da Disney");
        strcpy(producao[23].dicas[3], "Dragão falante como aliado");
        strcpy(producao[23].dicas[4], "Temas de honra e coragem");
        strcpy(producao[23].dicas[5], "Canção ‘Reflection’");
        strcpy(producao[23].dicas[6], "Adaptação em live action feita em 2020");
        strcpy(producao[23].dicas[7], "Paisagem oriental e épica");
        strcpy(producao[23].dicas[8], "Heróina determinada e inspiradora");
        strcpy(producao[23].dicas[9], "Produção da Disney");
        producao[23].totalDicas = 10;
        producao[23].dificuldade = 2;
    
    // 25
    // Alocação dinâmica implementada aqui
    inicializarProducao(&producao[24], 10);
    producao[24].tipoProducao = 1;
    strcpy(producao[24].nomeProducao, "THE OFFICE");
    strcpy(producao[24].dicas[0], "Comédia de escritório na Filadélfia");
    strcpy(producao[24].dicas[1], "Michael Scott é o gerente");
    strcpy(producao[24].dicas[2], "Dwight Schrute é o assistente de vendas");
    strcpy(producao[24].dicas[3], "Jim Halpert é o melhor amigo de Dwight");
    strcpy(producao[24].dicas[4], "Pam Beesly é a secretária");
    strcpy(producao[24].dicas[5], "Série de mockumentary");
    strcpy(producao[24].dicas[6], "Adaptação americana de série britânica");
    strcpy(producao[24].dicas[7], "Humor cringe e situações embaraçosas");
    strcpy(producao[24].dicas[8], "Personagens memoráveis e icônicos");
    strcpy(producao[24].dicas[9], "Considerada uma das melhores comédias da TV");
    producao[24].totalDicas = 10;
    producao[24].dificuldade = 1;
}    