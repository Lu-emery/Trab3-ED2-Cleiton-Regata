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


[7, 8], [6, 8, 1],

				3
				|
				v
				7
			6		8
		5				9
	4						10
1								14							


*/