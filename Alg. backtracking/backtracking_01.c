// Exercício Backtracking, por João Victor de Souza Pimentel Cunha.

/* Todas as combinações de {a,e,i}, de tamanho n em que o numero de a's seja maior que  numero de e's e i's */

#include <stdlib.h>
#include <stdio.h>

void imprimirCombinacoes(char *vet, int pos, int n, char *vetAux){
  int i,j;
  if(pos == n){
    int cont = 0;
    for( j=0; j<=n; j++ )
      if (vet[j]=='a')
        cont++;
    if(cont >= (n/2)+1){
      for( i=0; i<=n; i++ )
        printf("%c ", vet[i]);
      printf("\n");
    }
  }else{
    for( i=0; i<=2; i++ ){
      vet[pos] = vetAux[i];
      imprimirCombinacoes(vet, pos+1, n, vetAux);
    }
  }
}

char* criaVetor(int n){
  char *vet = (char *) malloc(n*sizeof(char));
  if(vet == NULL)
    printf("Erro ao criar o vetor!");
  return vet;
}

int main() {
  char vetAux[3] = {'a', 'e', 'i'};
  int n;

  printf("Insira um valor pra n: ");
  scanf("%d",&n);

  char *vet = criaVetor(n);
  imprimirCombinacoes(vet, 0, n, vetAux);

  free(vet);
  return 0;
}