#include "bst.h"
#include "key.h"

#define BRANCO 0
#define CINZA 1
#define PRETO 2

struct node {
	char string[C+1];
	Key chave;
	int cor;
	Node* esq;
	Node* dir;
};

int comparaString (char *p1, char *p2) {

	// Para cada caracter na string
	for (int i = 0; i < C; i++) {

		char c1, c2;

		if (p1[i] != p2[i]) {
			c1 = p1[i];
			c2 = p2[i];

			// Se for um número, soma 75 para ficar logo depois do 'z' na tabela ascii
			if (c1 < 'a') {
				c1 += 75;
			}
			if (c2 < 'a') {
				c2 += 75;
			}

      // E retorna a diferença dos dois
      if (c1 < c2) {
        return -1;
      } else {
        return 1;
      }
		}
	}

  // Ou retorna 0 se forem iguais
  return 0;
}

int comparaKey (Key key, Node* node) {
	char keyString[C];
	for (int i = 0; i < C; i++) {
		keyString[i] = ALPHABET[key.digit[i]];
	}
	return comparaString(keyString, node->string);
}

Node* inicializaBst () {
  return NULL;
}

Node* criaBst (char string[C+1]) {
  Node* n = malloc(sizeof(Node));

  strcpy(n->string, string);

	n->chave = init_key((unsigned char *) string);
  n->cor = BRANCO;
  n->esq = NULL;
  n->dir = NULL;

  return n;
}

Node* insereBst (Node* arv, char string[C+1]) {

  if (arv == NULL) {
	  arv = criaBst(string);
    return arv;
	}

	else {
    // Se a string a ser inserida for menor que o nó, vai pra esquerda
    if (comparaString(string, arv->string) == -1) {
			arv->esq = insereBst(arv->esq, string);
    }
    // É impossível existirem duas linhas iguais na tabela, logo os outros casos são maiores
    else {
      arv->dir = insereBst(arv->dir, string);
    }
  }
	return arv;
}

Node* criaBstDeTabela () {
  char aux[C+1];

  scanf("%s\n", aux);

  Node* arv = inicializaBst();
  arv = criaBst(aux);

	for (int i = 0; i < N; i++) {
		scanf("%s\n", aux);
		arv = insereBst(arv, aux);
	}

	printf("\n\n");
  imprimeBst(arv);
	printf("\n\n");

  return arv;
}

void imprimeBst (Node* arv) {
	if (arv == NULL) {
		printf("< >");
		return;
	}
	printf("< ");
	printf(" %s ", arv->string);
	imprimeBst(arv->esq);
	printf(" ");
	imprimeBst(arv->dir);
	printf(" >");
}

/*
Key copiaKey (Key ori) {
	Key dest = malloc(sizeof(Key));
	for(int i = 0; i < C; i++){
			dest.digit[i] = ori.digit[i];
	}
	return dest;
}
*/

Key resultados;
Key vetKeys[N];
int pos = 0;
Node* entrada;
void percorre (Node* senha, Node* arv) {
	if (arv == NULL) {
		return;
	}
	entrada = senha;
	Key soma = setZero(); // TODO: Settar tudo como zero

	printf("Checando todas as possibilidades para o primeiro nó\n");
	arv->cor = PRETO;

	Node* aux = arv;
	while (aux != NULL) {
		checaPossibilidades(soma, aux);
		aux = aux->esq;
	}


}

void checaPossibilidades (Key senhaAtual, Node* arv) {
	if (arv == NULL) {
		return;
	}

	if (arv->cor == BRANCO) {
		vetKeys[pos] = arv->chave;
		arv->cor = CINZA;
		pos++;
		senhaAtual = add(senhaAtual, arv->chave);
	}

	int compara = comparaKey(senhaAtual, entrada);

	// Se a senha atual for maior que a original
	if (compara > 0) {
		// Continua pra esquerda
		checaPossibilidades(senhaAtual, arv);
		pos--;
		if (arv->cor != PRETO) {
			arv->cor = BRANCO;
		}
		return;
	}

	// Se for igual é uma resposta
	if (compara == 0) {
		// printar resposta
		// para isso precisamos converter esse vetor
		// numa string
		pos--;
		if (arv->cor != PRETO) {
			arv->cor = BRANCO;
		}
		return;
	}

	// TALVEZ A GENTE TENHA QUE PULAR POSIÇÕES TAMBÉM
	// Se a senha atual for menor
	if (compara < 0) {
		// Continua para a esquerda
		checaPossibilidades(senhaAtual, arv);
		return;
	}

}
