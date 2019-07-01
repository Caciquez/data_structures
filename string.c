#include "string.h"

int equals(char *string_1, char *string_2){
  int len1, len2;

  len1 = lenght(string_1);
  len2 = lenght(string_2);

  if(len1 != len2){
    return 0;
  }
  else if(string_1[0] == string_2[0]){
    if(len1 == 1){
      return 1;
    }
    return(equals(++string_1, ++string_2));
  }
  return 0;
}

void toLowerCase(char *string_1){

  int len;
  len = lenght(string_1);

  if(string_1[0] >= 65 && string_1[0] <= 90){
    string_1[0] += 32;
  }

  if(len == 1){
    return;
  }
  else{
    return(toLowerCase(++string_1));
  }
}

void toUpperCase(char *string_1){

  int len;
  len = lenght(string_1);

  if(string_1[0] >= 97 && string_1[0] <= 122){
    string_1[0] -= 32;
  }

  if(len == 1){
    return;
  }
  else{
    return(toUpperCase(++string_1));
  }
}

int equalsIgnoreCase(char *string_1, char *string_2){
  char *token1, *token2;
  token1 = (char *) malloc(lenght(string_1)*sizeof(char));
  token2 = (char *) malloc(lenght(string_2)*sizeof(char));
  substring(token1, string_1, 0, lenght(string_1)-1);
  substring(token2, string_2, 0, lenght(string_2)-1);
  toLowerCase(token1);
  toLowerCase(token2);
  if(equals(token1, token2)){
    free(token1);
    free(token2);
    return 1;
  }
  else{
    free(token1);
    free(token2);
    return 0;

  }
}

void substring(char *string_1, char *string_2, int pos_ini, int pos_fin){
  int i, j;

  for (j = 0, i = pos_ini; i <= pos_fin; i++, j++) {
    string_1[j] = string_2[i];
  }
  string_1[j] = '\0';
}

int lenght(char *string_1){
  if(*string_1 == '\0'){
    return 0;
  }
  return(1+(lenght(++string_1)));
}

void replace(char *string_1, char* Caracteres_antigo, char* Caracteres_novo){
  int len1, len2, i, j;
  char *token;

  len1 = lenght(string_1);
  len2 = lenght(Caracteres_antigo);

  token = (char *) malloc(len2*sizeof(char));

  for (i = 0; i < len1; i++) {
    if(i+(len2-1) >= len1){
      break;
    }
    substring(token, string_1, i, i+(len2-1));
    if(equals(token, Caracteres_antigo)){
      for(j = i; j < i + len2; j++){
        string_1[j] = Caracteres_novo[j-i];
      }
    }
  }
}
