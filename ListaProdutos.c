#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>

typedef struct nodoArv{
	
	char produto[20];
    int info;
    struct nodoArv *esq;
    struct nodoArv *dir;
    struct nodoArv *pai;
    
   } NodoArv;

/*----------- FUNCTIONS --------*/

//Menu
void menu(){

  printf("\n");

  printf("Entre a opcao desejada: \n\n");
  printf(" 1. Inserir produto; \n");
  printf(" 2. Consultar produto; \n");
  printf(" 3. Remover produto; \n");
  printf(" 4. Total de produtos; \n");
  printf(" 5. Total de produtos; \n");
  printf(" 6. Lista todos os produtos; \n");
  printf(" 7. Lista todos os produtos de determinada letra; \n");
  printf(" 8. Lista produtos com quantidade acima; \n");
  printf(" 9. Lista produtos com quantidade abaixo; \n");
}

//Inserir produto
void *insereNodo(NodoArv *atual, NodoArv *novo ){
  if( strcmp(atual->produto, novo->produto) > 0){
      if(atual->esq == NULL ){
          atual->esq = novo;
          atual->esq->pai = atual; //seta o pai 
          return;
        }
        else {
          insereNodo( atual->esq, novo);
          return;
        }
  } else if(atual->dir == NULL){
            atual->dir = novo;
            atual->dir->pai = atual;
            return;
        }
        else {
          insereNodo( atual->dir, novo );
          return;
        }
}
    
NodoArv *insere(NodoArv** raiz, char produto[], int dado){
    NodoArv* novo = (NodoArv*) malloc(sizeof(NodoArv));
    
    strcpy(novo->produto, produto);   
    novo->info = dado;
    novo->esq = NULL;
    novo->dir = NULL;
    novo->pai = NULL;
        
    if( *raiz == NULL ){
        *raiz = novo;
        return *raiz;
    }
    else{
        insereNodo(*raiz, novo);
    }
}

//Imprime lista de produtos
void imprimeOrdenado(NodoArv** raiz){
    if(*raiz == NULL ){
      return;
    }
    
    imprimeOrdenado(&(*raiz)->esq);
    printf("Produto: %s, quantidade %d\n",(*raiz)->produto, (*raiz)->info);
    imprimeOrdenado(&(*raiz)->dir);
}

void imprimeValoresMaiores(NodoArv** raiz, int qtd){
    if(*raiz == NULL ){
      return;
    }
    
    imprimeValoresMaiores(&(*raiz)->esq, qtd);
    if((*raiz)->info >= qtd){
      printf("Produto: %s, quantidade %d\n",(*raiz)->produto, (*raiz)->info);
    }
    imprimeValoresMaiores(&(*raiz)->dir, qtd);
}

void imprimeValoresMenores(NodoArv** raiz, int qtd){
    if(*raiz == NULL ){
      return;
    }
    
    imprimeValoresMenores(&(*raiz)->esq, qtd);
    if((*raiz)->info <= qtd){
      printf("Produto: %s, quantidade %d\n",(*raiz)->produto, (*raiz)->info);
    }
    imprimeValoresMenores(&(*raiz)->dir, qtd);
}


//Pesquisas na Lista

int contaProdutosTotal(NodoArv** raiz) { 
    if((*raiz) == NULL ){
      return 0;
    }
   
    int contagem = 1; 
  
    contagem += contaProdutosTotal(&(*raiz)->esq);
    contagem += contaProdutosTotal(&(*raiz)->dir);
    
    return contagem; 
} 

int contaProdutosQtdTotal(NodoArv** raiz){
	if((*raiz) == NULL ){
      return 0;
    }
   
    int contagem = (*raiz)->info; 
  
    contagem += contaProdutosQtdTotal(&(*raiz)->esq);
    contagem += contaProdutosQtdTotal(&(*raiz)->dir);
    
    return contagem;	
}

int pesquisa(NodoArv** raiz, char produto[]){ 
    if((*raiz)==NULL){
          return -1;
      }
	
    if (strcmp((*raiz)->produto, produto) == 0){
        return (*raiz)->info;
       }
     
    if (strcmp((*raiz)->produto, produto) < 0) {
       return pesquisa(&(*raiz)->dir, produto);
    }
  
    return pesquisa(&(*raiz)->esq, produto); 
} 

//Deleta nodo

NodoArv* menorNodo(NodoArv *raiz) {
    NodoArv *aux = raiz;

    while (aux->esq != NULL)
        aux = aux->esq;

    return aux;
}

NodoArv* deletaNodo(NodoArv *raiz, char produto[]){
  if(raiz == NULL){
    return raiz;
  }
  
  if(strcmp(raiz->produto, produto) < 0){
    raiz->esq = deletaNodo(raiz->dir, produto);
  } else {
      if((raiz->esq == NULL) || (raiz->dir == NULL)){
        NodoArv *aux; 
        
        if(raiz->esq != NULL){
          aux = raiz->esq;
        }else{
          aux  = raiz->dir;  
        }
        
        if(aux == NULL){
          aux = raiz;
          raiz = NULL;
        }
        else {
          *raiz = *aux;
          
          free(aux);
        }
      }
        else {
          NodoArv *aux = menorNodo(raiz->dir);
          
          strcpy(raiz->produto, aux->produto);
          
          raiz->dir = deletaNodo(raiz->dir, aux->produto);
        }
      }
      
    return raiz;
}

/*---------------- MAIN -----------------*/

int main(){
    
  NodoArv *arvore[26];
  char produto[20];
  char alfa;
  int i, opcao, qtd, imprQtd, soma, resultado;
  for(i = 0; i<=26 ; i++){
    arvore[i] = NULL;
  }
  

  menu();    
    scanf("%d",&opcao);
    while (opcao != 0){
        switch (opcao) {
        case 1://INSERE PRODUTO
        	
        	printf("Entre o nome do produto: ");
			scanf("%s",&produto);
			printf("Entre a quantidade do produto: ");
			scanf("%d",&qtd);
			
			i = produto[0]-97;			
			insere(&arvore[i], produto, qtd);

          break;
        	case 2://CONSULTA PRODUTO
        	printf("Entre o nome do produto: ");
			scanf("%s",&produto);
			i = produto[0]-97;	
			
			resultado = pesquisa(&arvore[i],produto);
			
			if(resultado >= 0){
				printf("Produto %s encontrado, estoque de %d unidades.\n", produto, resultado);
			} else {
				printf("Produto nao encontrado.\n");
			}
					
          break;
    	case 3://REMOVE PRODUTO
        	printf("Entre o nome do produto: ");
			scanf("%s",&produto);
			i = produto[0]-97;
			
			arvore[i] = deletaNodo(arvore[i], produto);
          break;
            case 4://TOTAL PRODUTOS
            	soma=0;
	        	for(i=0;i<=26;i++){
					soma+=contaProdutosTotal(&arvore[i]);
				}
				printf("Total de produtos: %d.\n", soma);
          break;
        case 5://TOTAL QUANTIDADE PRODUTOS
            	soma=0;
	        	for(i=0;i<=26;i++){
					soma+=contaProdutosQtdTotal(&arvore[i]);
				}
				printf("Total da quantidade de produtos: %d.\n", soma);
        break;
          case 6://EXIBE PRODUTOS TOTAL
        		printf("Lista de produtos em ordem alfabetica:\n");
				for(i=0;i<=26;i++){
					imprimeOrdenado(&arvore[i]);
				}
          break;
         case 7: //EXIBE PRODUTOS LETRA
         	printf("Entre qual letra do alfabeto deseja listar:\n");
			 
			alfa = getch();
			i = alfa - 97;
			imprimeOrdenado(&arvore[i]);
			
        break;
        case 8: //EXIBE POR QUANTIDADE ACIMA
			printf("Entre o valor a ser consultado:\n");
			scanf("%d",&imprQtd);

			for(i=0;i<=26;i++){
				imprimeValoresMaiores(&arvore[i], imprQtd);
			}
				
        break;
        case 9: //AXIBE POR QUANTIDADE ABAIXO
			printf("Entre o valor a ser consultado:\n");
			scanf("%d",&imprQtd);
			for(i=0;i<=26;i++){
  				imprimeValoresMenores(&arvore[i], imprQtd);
			}
        break;
        }
        menu();
        scanf("%d",&opcao);
    }
    
  return 0;    
}


