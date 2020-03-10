
struct arv
{
    int num;
    int linha_arquivo;
  struct arv *esq;
  struct arv *dir;
};

struct BancoDeDados{
  int codigo;
  char Nome[30];
  };

typedef struct BancoDeDados produto;

static const struct BancoDeDados vaziaStruct;

typedef struct arv arv;


/*  Funcoes normas de uma arvore  */

void impressao(arv*raiz);
arv** menorDireito(arv*raiz);
arv** maiorEsquerdo(arv*raiz);
void criaGalhoNulo(arv**raiz);
int busca(arv*raiz, int elemento);
void galho(arv**raiz, int elemento, int pos);
int insereElemento(arv**raiz, int elemento, int pos);
void excluirElemento(arv**raiz, int elemento, int pos);
void excluiElementoArquivo(int pos);

/*  Funcoes que transformam uma arvore em AVL  */

int contEsq(arv*raiz);
int contDir(arv*raiz);
int balanceamento(arv*raiz);
arv* duplaDireita(arv*raiz);
arv* duplaEsquerda(arv*raiz);
arv* rotacaoDireita(arv*raiz);
arv* rotacaoEsquerda(arv*raiz);
void atualizaDir(arv**raiz,int elemento);
void atualizaEsq(arv**raiz,int elemento);

/*  Funcoes para interface e saida (usabilidade) */

void aviso();
void aviso1();
void aviso2();
void aviso3();
void aviso4();
void aviso5();
void mensagem();
int menu();
void linha( int q, int a);
void lerNumero(int *numero);

/*  Funcoes para criacao, entrada, saida de arquivos **
*/

int carregaArquivo(arv**raiz);
void criarArquivo(FILE* arquivo);
void EscreverArquivo(FILE* arquivo, produto prod, int i);
void lerDadosProduto(int linha);
void alterarStatus(int linha);
