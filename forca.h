#ifndef FORCA_H
#define FORCA_H

// Declaração de variáveis globais
extern char palavrasecreta[];
extern char chutes[];
extern int chutesdados;
extern int max_erros;

// Declaração das funções
int letraexiste(char letra);
int chuteserrados();
int enforcou();
int ganhou();
void abertura();
void chuta();
int jachutou(char letra);
void desenhaforca();
void escolhepalavra();
void adicionapalavra();
void escolhedificuldade();

#endif

