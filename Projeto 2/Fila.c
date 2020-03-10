#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <strings.h>
#include <ctype.h>

struct tipo {
    char nome[70];
    int senha;
    void *prox;
};

typedef struct tipo TIPO;

TIPO *Inicio = NULL;
TIPO *Ultimo = NULL;
TIPO *Iniciop = NULL;
TIPO *Ultimop = NULL;

int contsenha = 0;
int contsenhapref = 0;

void CriarSenha(){
    char nome[70];

    TIPO * novo, *aux, *auxValidacao;
    novo = (TIPO *) malloc(sizeof(TIPO));
    auxValidacao = Inicio;
    printf("Digite o nome do cliente: ");
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
    contsenha++;
    strcpy(novo->nome, nome);
    novo->senha = contsenha;
    novo->prox = NULL;

    if(Ultimo == NULL){
        Inicio = novo;
        aux = novo;
        Ultimo = novo;
    }
    else {
        aux = Inicio;
        aux->prox = novo;
        Inicio = novo;
        novo->prox = NULL;

    }
    printf("Senha gerada com sucesso!\n");
    printf("Sua senha é: %dC\n\n", novo->senha);
    system("pause");
    system("cls");
}

void CriarPref(){
    char nome[70];

    TIPO * novop, *auxp, *auxValidacao;
    novop = (TIPO *) malloc(sizeof(TIPO));
    auxValidacao = Iniciop;
    printf("Digite o nome do cliente: ");
    getchar();
    gets(nome);
    strupr(nome);
    while(auxValidacao != NULL){
        if (strcmp(auxValidacao->nome, nome) == 0){
            printf("\nNome já existente, acrecente um digito auxiliar \npara diferenciar ou troque o nome.\n\n ");
            system("PAUSE");
            return;
        }
        auxValidacao = auxValidacao->prox;
    }
    contsenhapref++;
    strcpy(novop->nome, nome);
    novop->senha = contsenhapref;
    novop->prox = NULL;

    if(Ultimop == NULL){
        Iniciop = novop;
        auxp = novop;
        Ultimop = novop;
    }
    else {
        auxp = Iniciop;
        auxp->prox = novop;
        Iniciop = novop;
        novop->prox = NULL;
    }
    printf("Senha gerada com sucesso!\n");
    printf("Sua senha é: %dP\n\n", novop->senha);
    system("pause");
    system("cls");
}

void ChamarSenhaNormal(){
    TIPO *aux;
    aux = Ultimo;
    if (Ultimo != NULL){
            printf("nome: %s \n", &Ultimo->nome);
            printf("senha: %dC \n", Ultimo->senha);
            printf("Por favor, comparecer ao caixa!\n");

            Ultimo = Ultimo->prox;
            free(aux);
            aux = NULL;

    }
    else printf ("FILA VAZIA!\n");
}

void ChamarSenhaPref(){
    TIPO *auxp;
    auxp = Ultimop;
    if (Ultimop != NULL){
        printf("nome: %s \n", &Ultimop->nome);
        printf("senha: %dP \n", Ultimop->senha);
        printf("Por favor, comparecer ao caixa!\n");
        Ultimop = Ultimop->prox;
        free(auxp);
        auxp = NULL;
    }
    else
        printf("FILA VAZIA!\n");
}

void ChamarSenha(){
    if(Ultimop != NULL){
        ChamarSenhaPref();
        system("pause");
        system("cls");
    }
    else {
        ChamarSenhaNormal();
        system("pause");
        system("cls");
    }
}

void ExibirFila(){
    if(Ultimo != NULL){
        printf("FILA NÃO PREFERENCIAL:\n\n");
        TIPO *auxex;
        auxex = Ultimo;
        while(auxex != NULL){
            printf ("nome: %s ", auxex->nome);
            printf ("senha: %dC\n", auxex->senha);
            auxex = auxex->prox;
        }
        printf ("\n");
    }
    else printf("FILA NÃO PREFERENCIAL VAZIA!\n");
}

void ExibirFilaPref(){
    if (Ultimop != NULL){
        printf("\n=================================\n");
        printf("\nFILA PREFERENCIAL:\n\n");
        TIPO *auxex;
        auxex = Ultimop;
        while(auxex != NULL){
            printf ("nome: %s ", auxex->nome);
            printf ("senha: %dP\n", auxex->senha);
            auxex = auxex->prox;
        }
        printf ("\n");
    }
    else {
        printf("\n=================================\n");
        printf("\nFILA PREFERENCIAL VAZIA!\n");
    }
}

void escreverMenu(){
    for (int i=0; i<44; i++){ //======== DE CIMA
        printf("=");
    }
    printf("\n");
    printf("FILA (MENU)\n");

    for (int i=0; i<44; i++){ //======== DE BAIXO
        printf("=");
    }
    printf("\n");
    printf("1.  Criar senha\n");
    printf("2.  Criar senha preferencial\n");
    printf("3.  Chamar senha\n");
    printf("4.  Imprimir fila\n");
    printf("0.  Sair do programa\n");
}
void menu(){
    escreverMenu();
    int n = 1;
    while(n!=0){
        printf("\nIngresse sua opcao: ");
        scanf("%d",& n);
        printf ("\n");
        switch(n){
            case 1:
                system("cls");
                CriarSenha();
                break;
            case 2:
                system("cls");
                CriarPref();
                break;

            case 3:
                system("cls");
                ChamarSenha();
                break;

            case 4:
                system("cls");
                ExibirFila();
                ExibirFilaPref();
                system("pause");
                system("cls");
                break;

        }
        if (n!=0){
            printf("\n\n");
            escreverMenu();
        }
    }
}

int main(){
    setlocale(LC_ALL, "Portuguese");
    menu();
    return 0;
}
