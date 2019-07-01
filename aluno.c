#include "aluno.h"

int temespaco(char *string_1){
  int len, i;

  len = lenght(string_1);

  for (i = 0; i < len; i++) {
    if(string_1[i] == ' ' && i != len-1){
      return 0;
    }
  }
  return 1;
}

int verificaendereco(char *string_1){
  int len, i, cont;

  len = lenght(string_1);

  cont = 0;

  for (i = 0; i < len; i++) {
    if(string_1[i] == ',' && cont == 0){
      cont = 1;
    }
    else if(cont == 1 && !(string_1[i] >= 48 && string_1[i] <= 57)){
      return 1;
    }
  }
  if(cont ==0){
    return 1;
  }
  return 0;
}

void corrigenome(char *string_1){
  int i, len;

  len = lenght(string_1);

  toLowerCase(string_1);
  string_1[0] -= 32;

  for (i = 1; i < len; i++) {
    if(string_1[i] == ' ' && i != len-1){
      string_1[i+1] -= 32;
    }
  }
}

int verificadata(char *string_1){
  char teste[10];
  int teste2;

  if(!(string_1[2] == '/' && string_1[5] == '/')){
    return 1;
  }
  substring(teste, string_1, 0, 1);
  teste2 = atoi(teste);
  if(teste2 < 0 || teste2 > 31){
    return 1;
  }
  substring(teste, string_1, 3, 4);
  teste2 = atoi(teste);
  if(teste2 < 1 || teste2 > 12){
    return 1;
  }
  substring(teste, string_1, 6, 9);
  teste2 = atoi(teste);
  if(teste2 < 1900 || teste2 > 2017){
    return 1;
  }
  return 0;
}

void geramatricula(aluno **jovem, int num){
  int len;
  char data[5];

  len = lenght((*jovem)->NomeCompleto);
  substring(data, (*jovem)->Nascimento, 6, 9);

  sprintf((*jovem)->matricula, "%c%c%s%d", (*jovem)->NomeCompleto[0], (*jovem)->NomeCompleto[len-1], data, num);
}

void crialista(TLista **lista){
  (*lista) = (TLista *) malloc(sizeof(TLista));
  (*lista)->nalunos = 0;
  (*lista)->primeiro = NULL;
  (*lista)->ultimo = NULL;
}

void liberaitem(aluno **aluno){
  if((*aluno)->prox){
    liberaitem(&(*aluno)->prox);
  }
  free((*aluno)->NomeCompleto);
  free((*aluno)->Endereco);
  free((*aluno)->Nascimento);
  free(*aluno);
  *aluno = NULL;
}

void liberalista(TLista **lista){
  if((*lista) == NULL){
    return;
  }
  if((*lista)->primeiro){
    liberaitem(&(*lista)->primeiro);
  }
  free(*lista);
}

int listavazia(TLista **lista){
  return ((*lista)->primeiro == NULL);
}

void inserenalista(TLista **lista, aluno **jovem){
  if(listavazia(lista)){
    (*lista)->primeiro = *jovem;
    (*lista)->ultimo = (*lista)->primeiro;
    (*lista)->ultimo->prox = NULL;
  }
  else{
    (*lista)->ultimo->prox = *jovem;
    (*lista)->ultimo = (*lista)->ultimo->prox;
    (*lista)->ultimo->prox = NULL;
  }
  (*lista)->nalunos++;
  geramatricula(&(*lista)->ultimo, (*lista)->nalunos);
}

void alocaaluno(aluno **jovem, char *nome, char *Endereco, char *data){

  *jovem = (aluno *) malloc(sizeof(aluno));

  (*jovem)->NomeCompleto = (char *) malloc(lenght(nome)*sizeof(char));
  substring((*jovem)->NomeCompleto, nome, 0, lenght(nome));

  (*jovem)->Endereco = (char *) malloc(lenght(Endereco)*sizeof(char));
  substring((*jovem)->Endereco, Endereco, 0, lenght(Endereco));

  (*jovem)->Nascimento = (char *) malloc(lenght(data)*sizeof(char));
  substring((*jovem)->Nascimento, data, 0, lenght(data));

}

void criaaluno(TLista **lista){
  char nome[500], endereco[500], data[100], dump;
  aluno *jovem;

  printf("Insira o nome do aluno(No mínimo nome e um sobrenome):\n");
  scanf("%c", &dump);
  fgets(nome, 500, stdin);
  nome[lenght(nome)-1] = '\0';
  while(temespaco(nome)){
    printf("Erro: Formato de nome incorreto, tente novamente ou digite 'sair' para cancelar:\n");
    fgets(nome, 500, stdin);
    nome[lenght(nome)-1] = '\0';
    if(equalsIgnoreCase(nome, "sair")){
      break;
    }
  }
  if(equalsIgnoreCase(nome, "sair")){
    return;
  }

  corrigenome(nome);

  printf("Insira o endereço do aluno(Formato: Rua X, Número):\n");
  fgets(endereco, 500, stdin);
  endereco[lenght(endereco)-1] = '\0';
  while(verificaendereco(endereco)){
    printf("Erro: Formato de endereço incorreto, tente novamente ou digite 'sair' para cancelar:\n");
    fgets(endereco, 500, stdin);
    endereco[lenght(endereco)-1] = '\0';
    if(equalsIgnoreCase(endereco, "sair")){
      break;
    }
  }
  if(equalsIgnoreCase(endereco, "sair")){
    return;
  }

  printf("Insira a data de nascimento do aluno(Formato: DD/MM/YYYY):\n");
  fgets(data, 100, stdin);
  data[lenght(data)-1] = '\0';
  while(verificadata(data)){
    printf("Erro: Formato de data incorreto, tente novamente ou digite 'sair' para cancelar:\n");
    fgets(data, 100, stdin);
    data[lenght(data)-1] = '\0';
    if(equalsIgnoreCase(data, "sair")){
      break;
    }
  }
  if(equalsIgnoreCase(data, "sair")){
    return;
  }

  alocaaluno(&jovem, nome, endereco, data);

  inserenalista(lista, &jovem);
}

void pesquisa(TLista **lista, char *busca, int tipo){
  aluno *x;

  for (x = (*lista)->primeiro; x != NULL; x = x->prox) {
    switch (tipo) {
      case 1:
        if(comparancasa(x->Endereco, busca)){
          printaaluno(&x);
        }
        break;
      case 2:
        if(comparanome(x->NomeCompleto, busca)){
          printaaluno(&x);
        }
        break;
      case 3:
        if(comparaano(x->Nascimento, busca)){
          printaaluno(&x);
        }
        break;
      case 4:
        if(comparames(x->Nascimento, busca)){
          printaaluno(&x);
        }
        break;
      case 5:
        if(equalsIgnoreCase(x->matricula, busca)){
          printaaluno(&x);
        }
        break;
    }
  }
}

int comparancasa(char *rua, char *num) {
  int i, len;
  char num1[10];

  len = lenght(rua);

  for (i = 0; i < len; i++) {
    if(rua[i] == ','){
      substring(num1, rua, i+1, len-1);
      break;
    }
  }
  if(equals(num, num1)){
    return 1;
  }
  else{
    return 0;
  }
}

int comparanome(char *nome, char *busca){
  int i, len, len2;
  char *num1;

  len = lenght(nome);
  len2 = lenght(busca);

  num1 = (char *) malloc(len2*sizeof(char));

  for (i = 0; i+len2-1 < len; i++) {
    substring(num1, nome, i, i+len2-1);
    if(equalsIgnoreCase(num1, busca)){
      return 1;
    }
  }
  return 0;
}

void printaaluno(aluno **jovem){
  printf("%s\n", (*jovem)->NomeCompleto);
  printf("%s\n", (*jovem)->Endereco);
  printf("%s\n", (*jovem)->Nascimento);
  printf("%s\n", (*jovem)->matricula);
}

int comparaano(char* data, char* busca){
  char ano[5];

  substring(ano, data, 6, 9);

  if(equals(ano, busca)){
    return 1;
  }
  return 0;
}

int comparames(char* data, char* busca){
  char mes[3];

  substring(mes, data, 3, 4);

  if(equals(mes, busca)){
    return 1;
  }
  return 0;
}

void alteracao(TLista **lista, char *matricula, char *antigo, char *novo, int tipo){
  aluno *x;
  char subs[5], new[5];
  for (x = (*lista)->primeiro; x != NULL; x = x->prox) {
    if(equalsIgnoreCase(matricula, x->matricula)){
      switch (tipo) {
        case 1:
          replace(x->NomeCompleto, antigo, novo);
          substring(subs, x->matricula, 0, 1);
          sprintf(new, "%c%c", x->NomeCompleto[0], x->NomeCompleto[lenght(x->NomeCompleto)-1]);
          replace(x->matricula, subs, new);
          break;
        case 2:
          replace(x->Endereco, antigo, novo);
          break;
        case 3:
          replace(x->Nascimento, antigo, novo);
          if(lenght(antigo) == 4){
            replace(x->matricula, antigo, novo);
          }
          break;
      }
    }
  }
}
