#ifndef SOMEONE_TO_KISS_SOMEONE_TO_KICK_YOU
#define SOMEONE_TO_KISS_SOMEONE_TO_KICK_YOU

#include <stdio.h>
#include <stdlib.h>
#include "string.h"

  typedef struct aluno{
    char *NomeCompleto;
    char *Endereco;
    char *Nascimento;
    char matricula[30];
    struct aluno *prox;
  }aluno;

  typedef struct Lista{
    int nalunos;
    aluno *primeiro, *ultimo;
  }TLista;

  int temespaco(char *string_1);

  int verificaendereco(char *string_1);

  void corrigenome(char *string_1);

  int verificadata(char *string_1);

  void geramatricula(aluno **jovem, int num);

  void crialista(TLista **lista);

  void liberaitem(aluno **aluno);

  void liberalista(TLista **lista);

  int listavazia(TLista **lista);

  void inserenalista(TLista **lista, aluno **jovem);

  void alocaaluno(aluno **jovem,  char *nome, char *Endereco, char *data);

  void criaaluno(TLista **lista);

  void pesquisa(TLista **lista, char *busca, int tipo);

  int comparancasa(char *rua, char *num);

  int comparanome(char *nome, char *busca);

  void printaaluno(aluno **jovem);

  int comparaano(char* data, char* busca);

  int comparames(char* data, char* busca);

  void alteracao(TLista **lista, char *matricula, char *antigo, char *novo, int tipo);
#endif
