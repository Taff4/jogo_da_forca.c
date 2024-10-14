#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>  // para usar toupper()
#include "forca.h"
#include <locale.h>


#define MAX_CHUTES 26
#define TAMANHO_PALAVRA 20

char palavrasecreta[TAMANHO_PALAVRA];
char chutes[MAX_CHUTES];
int chutesdados = 0;
int max_erros;  // Limite de erros baseado no nível de dificuldade

// Verifica se a letra chutada existe na palavra secreta
int letraexiste(char letra) {
    int j;  // Declara fora do for
    for(j = 0; j < strlen(palavrasecreta); j++) {
        if(letra == palavrasecreta[j]) {
            return 1;
        }
    }
    return 0;
}

// Conta o número de chutes errados
int chuteserrados() {
    int erros = 0;
    int i;  // Declara fora do for
    for(i = 0; i < chutesdados; i++) {
        if(!letraexiste(chutes[i])) {
            erros++;
        }
    }
    return erros;
}

// Verifica se o jogador perdeu
int enforcou() {
    return chuteserrados() >= max_erros;
}

// Verifica se o jogador acertou todas as letras da palavra secreta
int ganhou() {
    int i;  // Declara fora do for
    for(i = 0; i < strlen(palavrasecreta); i++) {
        if(!jachutou(palavrasecreta[i])) {
            return 0;
        }
    }
    return 1;
}

// Exibe a tela de abertura do jogo
void abertura() {
    printf("/****************/\n");
    printf("/ Jogo da Forca */\n");
    printf("/****************/\n\n");
}

// Recebe um chute e verifica se é válido
void chuta() {
    char chute;
    printf("Qual letra? ");
    scanf(" %c", &chute);
    
    chute = toupper(chute);  // Converte para maiúscula

    if(chute < 'A' || chute > 'Z') {  // Verifica se o chute é uma letra válida
        printf("Digite apenas letras maiúsculas!\n");
        return;
    }

    if(letraexiste(chute)) {
        printf("Você acertou: a palavra tem a letra %c\n\n", chute);
    } else {
        printf("\nVocê errou: a palavra NÃO tem a letra %c\n\n", chute);
    }

    chutes[chutesdados] = chute;
    chutesdados++;
}

// Verifica se uma letra já foi chutada
int jachutou(char letra) {
    int j;  // Declara fora do for
    for(j = 0; j < chutesdados; j++) {
        if(chutes[j] == letra) {
            return 1;
        }
    }
    return 0;
}

// Desenha a forca com base nos erros
void desenhaforca() {
    int erros = chuteserrados();
    int i;  // Declara fora do for
    printf("  _______       \n");
    printf(" |/      |      \n");
    printf(" |      %c%c%c  \n", (erros>=1?'(':' '), (erros>=1?'_':' '), (erros>=1?')':' '));
    printf(" |      %c%c%c  \n", (erros>=3?'\\':' '), (erros>=2?'|':' '), (erros>=3?'/': ' '));
    printf(" |       %c     \n", (erros>=2?'|':' '));
    printf(" |      %c %c   \n", (erros>=4?'/':' '), (erros>=4?'\\':' '));
    printf(" |              \n");
    printf("_|___           \n\n");

    for(i = 0; i < strlen(palavrasecreta); i++) {
        if(jachutou(palavrasecreta[i])) {
            printf("%c ", palavrasecreta[i]);
        } else {
            printf("_ ");
        }
    }
    printf("\n");
}

// Escolhe a palavra secreta do arquivo
void escolhepalavra() {
    FILE* f = fopen("palavras.txt", "r");
    if(f == 0) {
        printf("Banco de dados de palavras não disponível\n\n");
        exit(1);
    }

    int qtddepalavras;
    fscanf(f, "%d", &qtddepalavras);
    srand(time(0));
    int randomico = rand() % qtddepalavras;

    int i;  // Declara fora do for
    for(i = 0; i <= randomico; i++) {
        fscanf(f, "%s", palavrasecreta);
    }
    fclose(f);
}

// Adiciona uma nova palavra ao arquivo
void adicionapalavra() {
    if (!ganhou()) {
        printf("Você precisa ganhar para adicionar uma nova palavra.\n");
        return;
    }

    char quer;
    printf("Você deseja adicionar uma nova palavra no jogo (S/N)? ");
    scanf(" %c", &quer);
    if(quer == 'S') {
        char novapalavra[TAMANHO_PALAVRA];
        printf("Digite a nova palavra, em letras maiúsculas: ");
        scanf("%s", novapalavra);

        FILE* f = fopen("palavras.txt", "r+");
        if(f == 0) {
            printf("Banco de dados de palavras não disponível\n\n");
            exit(1);
        }

        int qtd;
        fscanf(f, "%d", &qtd);
        fseek(f, 0, SEEK_SET);
        fprintf(f, "%d", qtd+1);

        fseek(f, 0, SEEK_END);
        fprintf(f, "\n%s", novapalavra);
        fclose(f);
    }
}

// Define a dificuldade e o número de tentativas
void escolhedificuldade() {
    int dificuldade;
    printf("Escolha o nível de dificuldade (1) Fácil, (2) Médio, (3) Difícil: ");
    scanf("%d", &dificuldade);

    switch(dificuldade) {
        case 1: max_erros = 7; break;
        case 2: max_erros = 5; break;
        case 3: max_erros = 3; break;
        default: max_erros = 5;
    }
}

int main() {
	setlocale(LC_ALL,"Portuguese");
    abertura();
    escolhedificuldade();
    escolhepalavra();

    do {
        desenhaforca();
        chuta();
    } while (!ganhou() && !enforcou());

    if(ganhou()) {
        printf("\nParabéns, você ganhou!\n\n");
        printf("       ___________      \n");
        printf("      '._==_==_=_.'     \n");
        printf("      .-\\:      /-.    \n");
        printf("     | (|:.     |) |    \n");
        printf("      '-|:.     |-'     \n");
        printf("        \\::.    /      \n");
        printf("         '::. .'        \n");
        printf("           ) (          \n");
        printf("         _.' '._        \n");
        printf("        '-------'       \n\n");
    } else {
        printf("\nPuxa, você foi enforcado!\n");
        printf("A palavra era **%s**\n\n", palavrasecreta);
        printf("    _______________         \n");
        printf("   /               \\       \n"); 
        printf("  /                 \\      \n");
        printf("//                   \\/\\  \n");
        printf("\\|   XXXX     XXXX   | /   \n");
        printf(" |   XXXX     XXXX   |/     \n");
        printf(" |   XXX       XXX   |      \n");
        printf(" |                   |      \n");
        printf(" \\__      XXX      __/     \n");
        printf("   |\\     XXX     /|       \n");
        printf("   | |           | |        \n");
        printf("   | I I I I I I I |        \n");
        printf("   |  I I I I I I  |        \n");
        printf("   \\_             _/       \n");
        printf("     \\_         _/         \n");
        printf("       \\_______/           \n");
    }

    adicionapalavra();
    
    return 0;
}

