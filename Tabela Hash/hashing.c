//Exercício ED - Tabela Hash, por João Victor de Souza Pimentel Cunha.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 10

typedef struct alunos{
    int matricula;
    char nome[60];
    char curso[50];
    int disponibilidade;
}alunos;

int hash(int valor,int n){
    return valor%n;
}

void inicializar (char *path){
    FILE *arq = fopen(path, "wb");
    alunos a;
    int i;
    a.disponibilidade = 1;
    for (i=0;i<N;i++)
        fwrite(&a,sizeof(alunos),1,arq);
    fclose(arq);
}

int AcharPosicao(char *path, int matricula){
    int pos = hash(matricula, N);
    alunos a;
    FILE *arq = fopen(path, "rb");
    fseek(arq, pos*sizeof(alunos), SEEK_SET);
    fread(&a,sizeof(alunos),1,arq);
    while(a.disponibilidade == 0){
        pos = (pos+1)%N;
        fseek(arq,pos*sizeof(alunos), SEEK_SET);
        fread(&a,sizeof(alunos),1,arq);
    }
    fclose(arq);
    return pos;
}

void inserir(char *path, int matricula, char nome[70], char curso[50]){
    int pos = AcharPosicao(path,matricula);
    FILE *arq = fopen(path,"r+b");
    alunos a;
    a.matricula = matricula;
    strcpy(a.nome, nome);
    strcpy(a.curso, curso);
    a.disponibilidade = 0;
    fseek(arq,pos*sizeof(alunos), SEEK_SET);
    fwrite(&a,sizeof(alunos),1,arq);
    fclose(arq);
}

void buscarMat(char *path, int matricula){
    int pos = hash(matricula, N);
    int achou = 0;
    FILE *arq = fopen(path,"rb");
    alunos b;
    fseek(arq, pos*sizeof(alunos), SEEK_SET);
    fread(&b,sizeof(alunos),1,arq);
    while(b.disponibilidade == 0){
        if(b.matricula == matricula){
            achou=1;
            printf("\nAluno Encontrado!\n\n");
            printf("Matricula: %d \nNome: %s \nCurso: %s \n",b.matricula,b.nome,b.curso);
        }
        pos = (pos+1)%N;
        fseek(arq,pos*sizeof(alunos), SEEK_SET);
        fread(&b,sizeof(alunos),1,arq);
    }
    if(achou == 0){
        printf(" \n\t\tMatricula nao encontrada! \n");
    }
    fclose(arq);
}

void imprimir(char *path){
    int i,pos;
    FILE *arq = fopen(path,"rb");
    alunos b;
    fseek(arq, sizeof(alunos), SEEK_SET);
    fread(&b,sizeof(alunos),1,arq);
    for(i=1;i<=N;i++)
    {
        if(b.disponibilidade == 1)
            printf("%d = (%d) Disponivel \n\n", i, b.disponibilidade);
        else
            printf("%d = (%d) Matricula: %d, Nome: %s, Curso: %s \n\n",i,b.disponibilidade,b.matricula,b.nome,b.curso);
        pos = (i+1)%N;
        fseek(arq,pos*sizeof(alunos), SEEK_SET);
        fread(&b,sizeof(alunos),1,arq);
    }
    fclose(arq);
}

int main(void)
{
    int op=0,x;
    int matricula;
    char nome[70], curso[50];
    char path[10] = "hash.bin";
    FILE* hash;
    hash = fopen(path, "rb");
    if(hash == NULL)
    {
        printf("\n\nArquivo Nao Existe, Criando Novo... \n\n\n");
        inicializar(path);
    }
    else{
        printf("\n\nInicializando arquivo... \n\n\n");
    }
    fclose(hash);
    system("PAUSE");

    while(1)
    {
        system("CLS");
        printf("\n\nSelecione Uma Opcao: \n\n");
        printf("\n1 - Inserir Um Novo Aluno");
        printf("\n2 - Imprimir As Informacoes De Um Determinado Aluno.");
        printf("\n3 - Imprimir A Tabela De Dispersao.");
        printf("\n4 - Sair\n\n");
        scanf("%d",&x);

        switch(x)
        {
        case 1:
            system("cls");
            fflush(stdin);
            printf("Matricula: ");
            scanf("%d", &matricula);
            fflush(stdin);
            printf("Nome: ");
            gets(nome);
            fflush(stdin);
            printf("Curso: ");
            gets(curso);
            fflush(stdin);
            inserir(path,matricula,nome,curso);
            printf("\n\nAluno inserido com sucesso!\n\n");
            system("pause");

        break;
        case 2:
            system("cls");
            fflush(stdin);
            printf("Matricula: ");
            scanf("%d", &matricula);
            buscarMat(path,matricula);
            printf("\n");
            system("pause");
        break;
        case 3:
            system("cls");
            printf("\n");
            printf("\n\n TABELA HASH \n\n\n");
            imprimir(path);
            printf("\n");
            system("pause");
        break;
        case 4:
            system("cls");
            printf("\n\nSaindo...\n\n\n");
            return 0;
        break;
        default:
            system("cls");
            printf("\n\nSelecione Uma Opcao Valida!!!\n\n\n");
            system("pause");
        break;
        }
    }
}
