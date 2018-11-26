#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "key.h"

typedef struct node Node;

// Compara duas strings a partir do alfabeto fornecido
//     (012345 > abcdefghijklmnopqrstuvwxyz)
int comparaString (char *, char *);

// Compara as strings de dois nós
int comparaNode (Node*, Node*);

// Retorna uma Bst vazia (NULL)
Node* inicializaBst ();

// Cria uma Bst a partir de uma string
Node* criaBst (char string[C]);

// Insere um nó novo na Bst, a partir de uma string
Node* insereBst (Node*, char string[C]);

// Cria uma Bst a partir de uma tabela de símbolos fornecida
Node* criaBstDeTabela ();

// Imprime a Bst (usado para testes)
void imprimeBst (Node*);

int comparaKey (Key key, Node* node);
void percorre (Node* senha, Node* arv);
void checaPossibilidades (Key senha, Node* arv);
