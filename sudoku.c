#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n)
{
  
  for(int i = 0 ; i < 9 ; i++)
  {
    int arregloF[10] = {0};
    int arregloC[10] = {0};
    int arregloS[10] = {0};
    
    for(int j = 0 ; j < 9 ; j++)
    {
      if(n->sudo[i][j] != 0)
      {
        if(arregloF[n->sudo[i][j]] == 1)
        {
          return 0;
        }
        else
        {
          arregloF[n->sudo[i][j]] = 1;
        }
      }

      if(n->sudo[j][i] != 0)
      {
        if(arregloC[n->sudo[j][i]] == 1)
        {
          return 0;
        }
        else
        {
          arregloC[n->sudo[j][i]] = 1;
        }
      }
      
      int iS=3*(i/3) + (j/3) ;
      int jS=3*(i%3) + (j%3) ;
      
      if(n->sudo[iS][jS] != 0)
      {
        if(arregloS[n->sudo[iS][jS]] == 1)
        {
          return 0;
        }
        else
        {
          arregloS[n->sudo[iS][jS]] = 1;
        }
      }
    
    }
  }
  return 1;
}


List* get_adj_nodes(Node* n)
{
  List* list=createList();

    for(int i = 1; i <= 9 ; i++)
    {
      Node* copia = copy(n);
      int num = 0;
      
      for(int j = 0 ; j < 9 ; j++)
      {
        for(int k = 0 ; k < 9 ; k++)
        {
          if(n->sudo[j][k] == 0 && num == 0)
          {
            num = 1;
            copia->sudo[j][k] = i;  
          }
        }
      }
      if(num == 1 && is_valid(copia) == 1)
      {
        pushBack(list, copia);
      }
    }
  return list;
}


int is_final(Node* n)
{
  int cont = 0;
  for(int i = 0 ; i < 9 ; i++)
  {
    for(int j = 0 ; j < 9 ; j++)
    {
       if(n->sudo[i][j] == 0)
       {
         cont = 1;
       }
    }
  }
  if(cont == 0)
  {
    return 1;
  }
  else{
    return 0;
  }
 
}

Node* DFS(Node* initial, int* cont)
{
  Stack *pila = createStack();
  push(pila, initial);
  
  while(is_empty(pila) != NULL)
  {
    Node* auxDato = top(pila);
    pop(pila);
    cont++;
    
    if(is_final(auxDato) == 1)
    {
      return auxDato;
    }

    List *Lista = get_adj_nodes(auxDato);
    Node *datoLista = first(Lista);

    while(datoLista != NULL)
    {
      push(pila,datoLista);
      datoLista = next(Lista);
    }
    
   
  }
  
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/