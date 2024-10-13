#ifndef FORCA_H
#define FORCA_H

// Declara��o de vari�veis globais
extern char palavrasecreta[];
extern char chutes[];
extern int chutesdados;
extern int max_erros;

// Declara��o das fun��es
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

