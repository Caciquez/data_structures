#include <stdio.h>
#include <stdlib.h>
#include "aluno.h"
#include "string.h"

int main(){
  int op, op2, op3;
  char busca[500], matricula[50], dadoant[500], dadonov[500], dump;
  TLista *lista;
  crialista(&lista);

  while(1){
    printf("Sistema de cadastro de aluno\n\nDigite a sua opção:\n1- Cadastrar novo aluno\n2- Pesquisar aluno/alunos\n3- Alterar dado de um Aluno\n4- Sair\n");
    scanf("%d", &op);
    switch (op) {
      case 1:
        criaaluno(&lista);
        break;
      case 2:
        printf("Indique qual o tipo de pesquisa:\n1- Buscar pelo número de casa\n2- Buscar pelo sobrenome\n3- Buscar pelo ano de nascimento\n4- Buscar pelo mês de nascimento\n5- Buscar pela matrícula\n");
        scanf("%d%c", &op2, &dump);
        printf("Indique o termo a pesquisar:\n");
        fgets(busca, 500, stdin);
        busca[lenght(busca)-1] = '\0';
        pesquisa(&lista, busca, op2);
        break;
      case 3:
        printf("Indique a matrícula do aluno cujo dado será alterado:\n");
        scanf("%c", &dump);
        fgets(matricula, 50, stdin);
        matricula[lenght(matricula)-1] = '\0';
        printf("Indique o dado a ser alterado, o antigo valor e o novo valor(Ambos devem ter o mesmo tamanho):\n1- Nome\n2- Endereço\n3- Data de nascimento\n");
        scanf("%d%c", &op3, &dump);
        fgets(dadoant, 500, stdin);
        dadoant[lenght(dadoant)-1] = '\0';
        fgets(dadonov, 500, stdin);
        dadonov[lenght(dadonov)-1] = '\0';
        alteracao(&lista, matricula, dadoant, dadonov, op3);
        break;
      case 4:
        liberalista(&lista);
        return 0;
        break;
    }
  }
  return 0;
}
