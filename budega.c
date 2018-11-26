/*
double possibilidades[N];

senha = 516019665443
268435456

checa(senha, Abb, pos) {
	if(senha < minimo) {
		break;
	}
	checa(senha-dec(T[0]);
}
*/

#define BRANCO 0
#define CINZA 1
#define PRETO 2

typedef struct node {
	char string[C];
	Key chave;
	int cor;
	Node* sae;
	Node* sad;
} Node;


int comparaNode (char string[C], Node* no) {
	return comparaString (string, no->string);
}

int comparaString (char *p1, char *p2) {

	// Para cada caracter na string
	for (int i, i < C, i++) {

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
		}
	}

	// E retorna a diferença dos dois
	return c1 - c2;
}

Key somaNodes (Node* n1, Node* n2) {

}

Node* senha {
	[senha];
	[chave];
	[sem cor];
}

void percorre (Node* arv, Node* senha) {
	percorreOpera (arv->sae, senha)
}

void percorreOpera (Node* arv, Node* senha) {

}

/*
sempre desce pra esquerda e, depois que começa, testa a direita primeiro
	colocar uma tag se tal posição já começou por ela
	não pode usar nada acima ou à direita

armazenar os vetores de respostas em um vetor global

4 - 3 = 1
0 0100
+
1 0011
=
1 0111
+
0 0001
=
1 1000

[7, 

entrada 15

	senha atual 7 + 8 = 15
				7
				|
				v
				7
			6		8
		5				9
	4						10
1								14

7 PRETO
TESTA 0 + 7 = 7
	  7 > 15 N
	  7 == 15 N
	  7 < 15 S
	  DIREITA COM TESTA 7 8

	  	8 CINZA
		7 + 8 = 15
		15 > 15 N
		15 == 15 S
		PRINTA
		8 BRANCO
		POS --
		RETURN

	 ESQUERDA COM TESTA 7 6

		6 CINZA
		7 + 6 = 13
		13 > 15 N
		13 == 15 N
		13 < 15 S
		DIRETA COM TESTA 7 6 NAO TEM
		ESQUERDA COM TESTA 7 6 5

			5 CINZA
			13 + 5 = 18
			18 > 15 RETURN


*/
