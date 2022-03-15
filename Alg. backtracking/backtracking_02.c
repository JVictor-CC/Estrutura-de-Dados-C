// Exercício 2 Backtracking, por João Victor de Souza Pimentel Cunha.

/* Todas as combinações de {15, 31, 55, 44}, de tamanho n ,cujo a soma dos elementos da combinacao e par*/

#include <stdlib.h>
#include <stdio.h>

void imprimirCombinacoes(int *vet, int pos, int n, int *vetAux){
  int i,j;
  if(pos == n){
    int cont=0;
    for( i=0; i<n; i++)
      cont+=vet[i];
    if(cont%2 == 0){
      for(j=0; j<n; j++)
        printf("%d ", vet[j]);
      printf("\n");
    }
  }else{
    for( i=0; i<=3; i++ ){
      vet[pos] = vetAux[i];
      imprimirCombinacoes(vet, pos+1, n, vetAux);
    }
  }
}

int* criaVetor(int n){
  int *vet = (int *) malloc(n*sizeof(int));
  if(vet == NULL)
    printf("Erro ao criar o vetor!");
  return vet;
}

int main() {
  int vetAux[4] = {15, 31, 55, 44};
  int n;

  printf("Insira um valor pra n: ");
  scanf("%d",&n);

  int *vet = criaVetor(n);
  imprimirCombinacoes(vet, 0, n, vetAux);

  free(vet);
  return 0;
}