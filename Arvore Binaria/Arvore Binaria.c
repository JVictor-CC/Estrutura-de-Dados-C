//Exercício 1 ED, por João Victor de Souza Pimentel Cunha.

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct arvore
{
  int valor;
  struct arvore *esq;
  struct arvore *dir;
} arvore;

arvore *ler_arvore(FILE *arq)
{
  char c;
  int num;

  fscanf(arq, "%c", &c);     //ler '('
  fscanf(arq, "%int", &num); //ler a raiz

  if (num == -1) //é null?
  {
    fscanf(arq, "%c", &c);
    return NULL;
  }
  else
  {
    arvore *a;
    a = (arvore *)malloc(sizeof(arvore));
    a->valor = num;
    a->esq = ler_arvore(arq); //subesq
    a->dir = ler_arvore(arq); //subdir
    fscanf(arq, "%c", &c);    //ler')'
    return a;
  }
}

arvore *destruir(arvore *a)
{
  if (a == NULL)
    return a;
  a->esq = destruir(a->esq);
  a->dir = destruir(a->dir);
  free(a);
}

int altura(arvore *a)
{
  if (a == NULL)
    return 0;
  else
  {
    int he, hd;
    he = altura(a->esq);
    hd = altura(a->dir);

    if (he > hd)
      return he + 1;
    else
      return hd + 1;
  }
}

void nivel(arvore *a, int n) // auxilia a largura
{
  if (a != NULL)
  {
    if (n == 0)
      printf("%d ", a->valor);
    else
    {
      nivel(a->esq, n - 1);
      nivel(a->dir, n - 1);
    }
  }
}

int existe_x(arvore *a, int x)
{
  if (a == NULL)
    return 0;
  else if (a->valor == x)
    return 1;
  else if (existe_x(a->esq, x) == 1)
    return 1;
  return existe_x(a->dir, x);
}

int contar_arvore(arvore *a)
{
  if (a == NULL)
    return 0;
  else
    return 1 + contar_arvore(a->esq) + contar_arvore(a->dir);
}

int contar_folhas(arvore *a)
{
  if (a == NULL)
    return 0;
  if (a->esq == NULL && a->dir == NULL)
    printf("\n%d\n", a->valor);
  if (a->esq == NULL && a->dir == NULL)
    return 1;
  return contar_folhas(a->esq) + contar_folhas(a->dir);
}

void imprimir_nivel(arvore *a, int cont, int valor)
{
  if (a != NULL)
  {
    if (a->valor == valor)
      printf("\nO no %d esta no nivel %d \n\n\n", valor, cont);
    else
    {
      imprimir_nivel(a->esq, cont + 1, valor);
      imprimir_nivel(a->dir, cont + 1, valor);
    }
  }
}

void imprimir_pre_ordem(arvore *a)
{
  if (a != NULL)
  {
    printf("%d ", a->valor);
    imprimir_pre_ordem(a->esq);
    imprimir_pre_ordem(a->dir);
  }
  else
    printf("(-1) ");
}

void imprimir_em_ordem(arvore *a)
{
  if (a != NULL)
  {
    imprimir_em_ordem(a->esq);
    printf("%d ", a->valor);
    imprimir_em_ordem(a->dir);
  }
  else
    printf("(-1) ");
}

void imprimir_pos_ordem(arvore *a)
{
  if (a != NULL)
  {
    imprimir_pos_ordem(a->esq);
    imprimir_pos_ordem(a->dir);
    printf("%d ", a->valor);
  }
  else
    printf("(-1) ");
}

void imprimir_em_largura(arvore *a)
{
    int h;
    h= altura(a);
    int i;
    for(i=0; i<h; i++)
    {
        nivel(a, i);
    }
}

int verificar_cheia(arvore *a)
{
  int h = altura(a);
  int n = contar_arvore(a);
  if (n == (pow(2, h)) - 1)
    return 1;
  else
    return 0;
}

int verificar_balance(arvore *a)
{
  int he, hd;
  if (a == NULL)
    return 0;
  else
  {
    he = altura(a->esq);
    hd = altura(a->dir);
    if (he > hd + 1)
      return 1 + verificar_balance(a->esq);
    else
    {
      if (hd > he + 1)
        return 1 + verificar_balance(a->dir);
      else
        return 0;
    }
  }
}

int menu(arvore *a)
{
  char nomarq[30];
  int op, x, folha;
  FILE *arq;

  while (op != 9)
  {
    system("cls");
    printf("Escolha uma das opcoes:\n\n");
    printf("1 - Ler Arvore\n\n");
    printf("2 - Imprimir Arvore\n\n");
    printf("3 - Procurar Por Um Elemento\n\n");
    printf("4 - Contar Numero De Elementos\n\n");
    printf("5 - Imprimir Nos Folhas Da Arvore\n\n");
    printf("6 - Verificar Se A Arvore Esta Balanceada\n\n");
    printf("7 - Verificar Se A Arvore Eh Cheia\n\n");
    printf("8 - Imprimir o Nivel De Um No\n\n");
    printf("9 - Sair\n\n");

    scanf("%d", &op);
    system("cls");
    switch (op)
    {
    case 1:
      do
      {
        printf("Digite o nome do arquivo(.txt): ");
        scanf("%s", nomarq);
        fflush(stdin);
        arq = fopen(nomarq, "rt");
      } while (arq == NULL);

      a = ler_arvore(arq);
      fclose(arq);
      printf("\n\n\nArvore Carregada!!!\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
      system("pause");
      break;

    case 2:
      printf("Escolha uma forma de ordenacao:\n");
      do
      {
        printf("1 - Pre-ordem\n");
        printf("2 - Em-ordem\n");
        printf("3 - Pos-Ordem\n");
        printf("4 - Largura\n");
        printf("5 - Voltar\n");

        scanf("%d", &x);
        fflush(stdin);
        if (x < 1 || x > 4)
        {
          printf("Digite uma opcao valida!\n");
        }

        switch (x)
        {
        case 1:
          printf("Pre Ordem:\n");
          imprimir_pre_ordem(a);
          printf("\n\n\n");
          system("pause");
          break;

        case 2:
          printf("\nEm Ordem:\n");
          imprimir_em_ordem(a);
          printf("\n\n\n");
          system("pause");
          break;

        case 3:
          printf("\nPos Ordem:\n");
          imprimir_pos_ordem(a);
          printf("\n\n\n");
          system("pause");
          break;

        case 4:
          printf("\nEm Largura\n");
          imprimir_em_largura(a);
          printf("\n\n\n");
          system("pause");
          break;
        }

      } while (x != 5);

      break;

    case 3:

      printf("Digite o numero que quer procurar:\n");
      scanf("%d", &x);
      if (existe_x(a, x) == 1)
      {
        printf("\nEste numero pertence a arvore.\n\n\n");
      }
      else
      {
        printf("\nEste numero nao pertence a arvore.\n\n\n");
      }
      system("pause");
      break;

    case 4:

      printf("Essa Arvore possui %d nos. \n\n\n", contar_arvore(a));
      system("pause");
      break;

    case 5:
      printf("Os nos folhas sao:\n");
      contar_folhas(a);
      printf("\n\n");
      system("pause");
      break;

    case 6:
      if (verificar_balance(a) == 0)
      {
        printf("\nEsta arvore eh balanceada.\n\n\n");
      }
      else
      {
        printf("\nEsta arvore nao eh balanceada.\n\n\n");
      }
      system("pause");
      break;

    case 7:

      if (verificar_cheia(a) == 1)
      {
        printf("\nEsta arvore eh cheia.\n\n\n");
      }
      else
      {
        printf("\nEsta arvore nao eh cheia.\n\n\n");
      }
      system("pause");
      break;

    case 8:
      printf("Voce deseja saber o nivel de qual no?\n");
      int num;
      scanf("%d", &num);
      if (existe_x(a, num) == 1){
        imprimir_nivel(a, 0, num);
      }
    system("pause");
      break;

    case 9:
      a = destruir(a);
      return 0;
      break;

    default:
      printf("\n\nDigite uma opcao valida\n\n\n\n\n");
      system("pause");
      break;
    }
  }
}

int main()
{
  arvore *a = NULL;
  menu(a);

  return 0;
}
