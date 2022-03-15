// Exercício Estruturas Genericas, por João Victor de Souza Pimentel Cunha.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct aluno{
    int matricula;
    char nome[50];
    char curso[50];
    int ano;
}*Aluno;

typedef struct professor{
    int matricula;
    char nome[50];
    float salario;
}*Professor;

typedef struct pessoa{
    int tipo;
    void *item;
    struct pessoa *prox;
}*Pessoa;


void iniciaLista(Pessoa *lista){
    (*lista)=NULL;
}

void inserirPessoa(Pessoa *lista,int tipo,void *info){
    Pessoa new=(Pessoa)malloc(sizeof(struct pessoa));
    new->tipo = tipo;
    new->item = info;
    new->prox = (*lista);
    (*lista)=new;
}

Pessoa Buscar(Pessoa lista, int matricula){
    if(lista != NULL){
        if(lista->tipo == 1){
            Aluno a=(Aluno)lista->item;
            if(a->matricula == matricula){
                return lista;
            }
            return Buscar(lista->prox,matricula);
        }
        else if(lista->tipo == 2){
            Professor p=(Professor)lista->item;
            if(p->matricula == matricula){
                return lista;
            }
            return Buscar(lista->prox,matricula);
        }
    }
    else{
        return NULL;
    }
}


void Remover(Pessoa *lista, int matricula){
    Pessoa remove = Buscar(*lista,matricula);
    if(remove != NULL){
        if(remove == *lista){
            *lista = remove->prox;
            free(remove);
        }
        else{
            Pessoa aux = *lista;
            while(aux->prox != remove){
                aux = aux->prox;
            }
            aux->prox = remove->prox;
            free(remove);
        }
    }else{
      printf("Matricula nao encontrada!\n");
    }
}

void ImprimirDados(Pessoa lista,int matricula){
    Pessoa impr = Buscar(lista,matricula);
    if(impr!=NULL){
        if(impr->tipo==1){
            Aluno a = (Aluno)impr->item;
            printf("\nNome: %s\n",a->nome);
            printf("Matricula: %d\n",a->matricula);
            printf("Curso: %s\n",a->curso);
            printf("Ano: %d\n",a->ano);

        }
        if(impr->tipo==2){
            Professor p=(Professor)impr->item;
            printf("\nNome:%s\n",p->nome);
            printf("Salario:%.2f\n",p->salario);
            printf("Matricula:%d\n",p->matricula);
        }
    }
    else{
        printf("Matricula nao encontrada!\n");
    }
}

int ContarAlunos(Pessoa lista,char *curso){
    if (lista!=NULL){
        if (lista->tipo==1){
            Aluno a=(Aluno)lista->item;
            if (strcmp(a->curso,curso)==0){
                return (1+ ContarAlunos(lista->prox,curso));
            }
        }
            return (0 + ContarAlunos(lista->prox,curso));
    }
    else
        return 0;
}

void imprimeMaiorSalario( Pessoa lista){
    float maiorSalario = 0,cont=0;
    Pessoa aux = lista;
    Professor p;
    while(aux!=NULL){
      if(aux->tipo==2){
        p=(Professor)aux->item;
        if(p->salario > maiorSalario){
          maiorSalario=p->salario;
        }
      }
      aux=aux->prox;
    }
    aux=lista;
    while(aux!=NULL){
      if(aux->tipo == 2){
        p=(Professor)aux->item;
        if(p->salario == maiorSalario){
          printf("\n\nNome: %s\n",p->nome);
          printf("Salario: R$%.2f\n",p->salario);
          printf("Matricula: %d\n\n",p->matricula);
        }
        cont++;
      }
      aux=aux->prox;
    }
    if(cont==0){
      printf("Não tem professores cadastrados!\n");
    }
}

int main(){
    int op=0,x=0,mat=0,ano;
    char *nome,curso[40];
    Pessoa lista;
    iniciaLista(&lista);

    printf("1-Inserir uma pessoa na lista\n");
    printf("2-Remover uma pessoa pela matricula\n");
    printf("3-buscar uma pessoa pela matricula\n");
    printf("4-Contar o numero de alunos em um curso\n");
    printf("5-Imprimir os professores de maior salario\n");
    printf("6-Sair\n");

    do{
        printf("\nDigite uma opcao:");
        scanf("%d",&op);
        switch(op){
        case 1:
            printf("\nDigite qual tipo deseja inserir:\n");
            printf("1-Aluno\n2-Professor\n");
            scanf("%d",&x);
            if(x==1){
                Aluno a = (Aluno)malloc(sizeof(struct aluno));
                printf("Digite o nome do Aluno:");
                fflush(stdin);
                scanf("%s",a->nome);
                fflush(stdin);
                printf("Digite o curso de ingresso:");
                scanf("%s",a->curso);
                fflush(stdin);
                printf("Digite o ano de ingresso:");
                scanf("%d",&ano);
                a->ano = ano;
                printf("Digite sua matricula: ");
                fflush(stdin);
                scanf("%d",&mat);
                a->matricula=mat;
                inserirPessoa(&lista,x,a);
            }
            else if(x==2)
            {
                Professor p=(Professor)malloc(sizeof(struct professor));
                printf("Digite o nome do professor:");
                scanf("%s",p->nome);
                printf("Digite o salario do professor:");
                scanf("%f",&(p->salario));
                printf("Digite sua matricula: ");
                scanf("%d",&mat);
                p->matricula = mat;
                inserirPessoa(&lista,x,p);
            }

            break;

        case 2:
            printf("Digite a matricula que deseja remover:");
            scanf("%d",&mat);
            Remover(&lista,mat);
            break;

        case 3:
            printf("Digite a matricula que deseja procurar: ");
            scanf("%d",&mat);
            ImprimirDados(lista,mat);
            break;

        case 4:
            printf("Digite o nome do curso:\n");
            fflush(stdin);
            scanf("%s",curso);
            printf("%d alunos cursam %s",ContarAlunos(lista,curso),curso);
            break;

        case 5:
            imprimeMaiorSalario(lista);
            break;
        case 6:
            return 0;
            break;
        default:
            printf("Digite uma opcao valida!\n");
            break;
        }
    }
    while(op!=6);
    return 0;
}
