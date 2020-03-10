#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <strings.h>
#include <ctype.h>
// isso nao conta nao, mas tem que tratar acho que ela se ligou quando digitei



struct tipo {
    char nome[70];
    float nota;
    void *prox;
};

struct tipoaux {
    char nome[70];
    float nota;
};

typedef struct tipoaux TIPOAUX;

long tamanho = sizeof(struct tipoaux);

typedef struct tipo TIPO;

TIPO *Inicio = NULL;

int cont1 = 0;

char nomeaux[70];

void AdcAluno(){
    char nome[70];
    float nota = -1;
    TIPO * novo, *aux, *ant, *auxValidacao;
    novo = (TIPO *) malloc(sizeof(TIPO));
    auxValidacao = Inicio;
    printf("Digite o nome do aluno: ");
    getchar();
    gets(nome);
    strupr(nome);
    while(auxValidacao != NULL){
        if (strcmp(auxValidacao->nome, nome) == 0){
            printf("\nNome já existente, acrecente um digito \nauxiliar para diferenciar ou troque o nome.\n\n ");
            system("PAUSE");
            return;
        }
        auxValidacao = auxValidacao->prox;
    }
    printf ("Digite a nota do aluno: ");
    while (nota < 0.00 || nota > 10.00){
        scanf ("%f", &nota);
        if (nota < 0.00 || nota > 10.00){
            printf ("nota inválida, digite um numero entre 0 e 10: \n");
        }
    }

    strcpy(novo->nome, nome);
    novo->nota = nota;
    novo->prox = NULL;

    if(Inicio== NULL){
        Inicio = novo;
    }
    else {
        aux = Inicio;
        ant = Inicio;
        if(aux->nota < novo->nota){
            novo->prox = aux;
            Inicio = novo;
        }
        else{
            aux = aux->prox;
            while(aux!=NULL){
                if(aux->nota < novo->nota){
                        novo->prox = aux;
                        ant->prox = novo;
                        return;
                }
                ant= aux;
                aux = aux->prox;
            }
            ant->prox = novo;
        }
    }
    printf("Aluno criado com sucesso!\n");
    system("pause");
}

void AuxEditarAdc(){
    float nota = -1;
    TIPO *novo, *aux, *ant, *auxValidacao;
    novo=(TIPO *) malloc(sizeof(TIPO));
    auxValidacao = Inicio;

    printf ("\nDigite a nova nota do aluno: ");
    while (nota < 0.00 || nota > 10.00){
        scanf ("%f", &nota);
        if (nota < 0.00 || nota > 10.00){
            printf ("\nNota inválida, digite um numero entre 0 e 10: \n");
        }
    }
    strcpy(novo->nome, nomeaux);
    novo->nota = nota;
    novo->prox = NULL;

    if(Inicio== NULL){
        Inicio = novo;
    }
    else {
        aux = Inicio;
        ant = Inicio;

        if(aux->nota < novo->nota){
            novo->prox = aux;
            Inicio = novo;
        }
        else{
            aux = aux->prox;

            while(aux!=NULL){
                if(aux->nota < novo->nota){
                        novo->prox = aux;
                        ant->prox = novo;
                        return;
                }
                ant= aux;
                aux = aux->prox;
            }
            ant->prox = novo;
        }
    }
}

void EditarAluno(){
    AuxEditarExcluir();

    if(cont1 != 0){
        AuxEditarAdc(); // tratar, ele entra nessa funcao de qualquer jeito
        printf("Aluno editado com sucesso!\n");
    }
    else
        printf("Aluno nao encontrado!\n");
        system("pause");
}

void AuxEditarExcluir(){
    char nome[70];
    float nota;

    struct tipo *aux, *anterior;
    aux=(TIPO *) malloc(sizeof(TIPO));
    printf("Digite o nome do aluno que deseja Alterar\n");
    getchar();
    gets(nome);
    strupr(nome);
    if (Inicio->prox == NULL){
        if (strcmp(Inicio->nome, nome) == 0){
            strcpy(nomeaux, Inicio->nome);
            free(Inicio);
            Inicio = NULL;
            cont1++;
            printf("Aluno encontrado, pressione qualquer tecla para continuar!\n");
            system("pause");
            return;
        }
    }else{
        int cont = 0;
        aux = Inicio;
        anterior = Inicio;
        while (aux != NULL){
            cont++;
            if (strcmp(aux->nome, nome) == 0){
                strcpy(nomeaux, aux->nome);
                if(cont==1){
                    Inicio=Inicio->prox;
                }
                anterior->prox = aux->prox;
                free(aux);
                aux = NULL;
                cont1++;
                printf("Aluno encontrado, pressione qualquer tecla para continuar!\n");
                system("pause");
                return;
            }
            anterior = aux;
            aux = aux->prox;
            }
        }
}

void ExcluirAluno(){
    char nome[70];
    float nota;
    struct tipo *aux, *anterior;
    aux=(TIPO *) malloc(sizeof(TIPO));
    printf("Digite o nome do aluno que deseja excluir:\n");
    getchar();
    gets(nome);
    strupr(nome);
    if (Inicio->prox == NULL){
        if (strcmp(Inicio->nome, nome) == 0){
            free(Inicio);
            Inicio = NULL;
            printf("Aluno excluído com sucesso!\n");
            return;
        }
    }else{
        int cont = 0;
        aux = Inicio;
        anterior = Inicio;
        while (aux != NULL){
            cont++;
            if (strcmp(aux->nome, nome) == 0){
                if(cont==1){
                    Inicio=Inicio->prox;
                }
                anterior->prox = aux->prox;
                free(aux);
                aux = NULL;
                printf("Aluno excluído com sucesso!\n");
                return;
            }
            anterior = aux;
            aux = aux->prox;
            }
        }
    printf ("Aluno nao encontrado\n");
}

void escreverMenu(){
    for (int i=0; i<44; i++){ //======== DE CIMA
        printf("=");
    }
    printf("\n");
    printf("Ranking de alunos (MENU)\n");

    for (int i=0; i<44; i++){ //======== DE BAIXO
        printf("=");
    }
    printf("\n");
    printf("1.  Adicionar aluno\n");                                       //
    printf("2.  Editar aluno\n");                                             //
    printf("3.  Excluir aluno\n");                                               //
    printf("4.  Exibir o Ranking de alunos\n");                                     //
    printf("0.  Sair do programa\n");                                                  // feito
}

void ExibirRanking(){
    struct tipo *auxex;
    int cont = 1;
    auxex = Inicio;
    while(auxex != NULL){
        printf ("%d - ", cont);
        printf ("nome: %s ", auxex->nome);
        printf ("nota: %.2f;\n", auxex->nota);
        cont++;
        auxex = auxex->prox;
    }
}

void gravarArquivo(){
    FILE *arq;
    arq = fopen ("alunos.dat", "wb");
    TIPO *aux;
    TIPOAUX *auxstr;
    auxstr = (TIPOAUX *) malloc(sizeof(TIPOAUX));
    aux = Inicio;
    int cont = 0;
    while (aux != NULL){
        strcpy(auxstr->nome, aux->nome);
        auxstr->nota = aux->nota;
        fseek(arq,cont*tamanho,0);
        fwrite(auxstr,sizeof(TIPOAUX),1,arq);
        aux = aux->prox;
        cont++;

    }
    fclose(arq);

}

void lerArquivo(){
    int cont = 0;
    FILE *arq;
    arq = fopen("alunos.dat", "rb");

    TIPOAUX *AUXSTR;
    AUXSTR = (TIPOAUX *) malloc(sizeof(TIPOAUX));
    TIPO *aux;
    TIPO *novo;
    TIPO *ant;

    Inicio = NULL;
    aux =(TIPO *) malloc(sizeof(TIPO));
    fseek(arq, 0, 0);

    while(fread(AUXSTR, tamanho, 1, arq) == 1){
            fseek(arq,cont*tamanho,0);
            novo=(TIPO *) malloc(sizeof(TIPO));

            strcpy(novo->nome, AUXSTR->nome);
            novo->nota = AUXSTR->nota;
            novo->prox = NULL;
            cont++;

        if(Inicio == NULL){
            Inicio = novo;
            ant = novo;
        }
        else{
            ant->prox = novo;
            ant = novo;
        }
    }
    fclose(arq);
}

void Organizar(){
    TIPO *AUXX;
    AUXX = (TIPO *) malloc(sizeof(TIPO));
    AUXX = Inicio;
    if (AUXX != NULL && AUXX->prox !=NULL){
        Inicio = AUXX->prox;
        free(AUXX);
        AUXX = NULL;
    }
}

void menu(){
    lerArquivo();
    Organizar();
    escreverMenu();
    int n = 1;
    while(n!=0){
        printf("\nIngresse sua opcao: ");
        scanf("%d",& n);
        printf ("\n");
        switch(n){
            case 1:
                system("cls");
                AdcAluno();
                break;
            case 2:
                system("cls");
                EditarAluno();
                break;
            case 3:
                system("cls");
                ExcluirAluno();
                break;
            case 4:
                system("cls");
                ExibirRanking();
                //Organizar();
                system("PAUSE");
                break;
        }
        if (n!=0){
            printf("\n\n");
            escreverMenu();
        }
        if (n==0){
            int j;
            printf("programa sendo finalizado, digite 0 para salvar as alterações:\n");
            scanf("%d", &j);
            if (j == 0){
                gravarArquivo();
            }
            printf("Execução finalizada!");
        }
    }
}

int main(){
    setlocale(LC_ALL, "Portuguese");
    menu();
    return 0;
}

