/**********************************************************************
 *  Criptografa uma senha usando o algoritmo de soma de subconjunto.
 *
 *  Compilação:   $ gcc -Wall key.c encrypt.c -o encrypt
 *  Execução:     $ ./encrypt password < in/rand8.txt
 *                   vbskbezp
 *
 *  Nota: lembre-se de sempre ajustar a macro C em key.h antes de
 *  compilar e executar com uma senha de tamanho específico.
 *
 **********************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "key.h"

// Variaveis globais
// Key entrada;

Key T[N];                      // A tabela T.
Key entrada;                   // Password dado como entrada
Key TSomas[C][32];             // Cada resultado refente a um
                               // será guardado aqui


int contSaidas = 0;
// Armazena, em ordem, todas as combinações possíveis de 5 caracteres
// "aaaaa", "aaaaab", ..., "aaaa5", "aaaba", ..., "baaaa", ..., "55555"
// Para cada caracter na primeira posição, tem 32^4 combinações
// Logo, o tamanho da tabela é 32^5(33.554.432) chaves
// Cada chave tem 6 caracteres de 5 bits, logo, a tabela tem 33.554.432*6*5(1.006.632.960) bits
// Que equivale a aprox. 1,006 GB de RAM em uso pelo programa

                       // 32^5
typedef struct tabelaNode TabelaNode;
struct tabelaNode {
  unsigned char letras[C];
  Key chave;
};

int contTabela = 0;
int tamTabela = R;
int caracteresTabela;

TabelaNode** criaTabela();
void preencheTabela(TabelaNode**, int, Key, unsigned char*);
// A tabela é criada dentro da função para não usar ela se C <= 5
TabelaNode** criaTabela() {
  tamTabela = R;
  for (int i = 1; i < caracteresTabela; i++) {
    tamTabela *= R;
  }
  printf("A tabela tem [%d] combinações\n", tamTabela);
  TabelaNode** tabelaCombinacoes = malloc(tamTabela * sizeof(TabelaNode*));
  for (int i = 0; i < tamTabela; i++) {
    tabelaCombinacoes[i] = malloc(sizeof(TabelaNode));
  }

  Key combinacao = {{0}};
  unsigned char nome[caracteresTabela+1];
  for (int i = 0; i < caracteresTabela; i++) {
    nome[i] = 'a';
  }
  nome[caracteresTabela] = '\0';
  preencheTabela(tabelaCombinacoes, 1, combinacao, nome);

  return tabelaCombinacoes;
}

void preencheTabela(TabelaNode** tabela, int atual, Key combinacao, unsigned char* nome) {
  Key aux = {{0}};
  for(int i = 0; i < R; i++) {
    aux = add(combinacao, TSomas[atual][i]);
    //printf("Somando na chave da tabela TSomas[%d][%c] | Nome: [%s]: ", atual, ALPHABET[i], nome); print_key(TSomas[atual][i]);
    if(atual == caracteresTabela) {
      nome[atual-1] = ALPHABET[i];

      tabela[contTabela]->chave = aux;
      for (int j = 0; j < caracteresTabela; j++) {
        tabela[contTabela]->letras[j] = nome[j];
      }
      tabela[contTabela]->letras[caracteresTabela] = '\0';
      contTabela++;
    }

    if (atual < caracteresTabela) {
      nome[atual-1] = ALPHABET[i];
      preencheTabela(tabela, atual+1, aux, nome);
    }
  }
}

unsigned char testeTabela[C+1];
// C = 6 | caracteresTabela = 5
void weakComTabela(TabelaNode** tabela, Key sum, int atual, Key pass) {
  Key aux = {{0}};
  testeTabela[atual] = '\0';

  // Se posição + caracteres armazenados = C
  if (atual == C-caracteresTabela) {

    // Percorre todas as posições da tabela de combinações armazenada
    for (int j = 0; j < tamTabela; j++) {

      // Adiciona o valor da combinação com o valor da chave até agora
      aux = add(sum, tabela[j]->chave);

      // Se o valor for igual ao da senha
      if (comparaKey(pass, aux)) {

        // Concatena as letras que geraram o valor armazenado à chave até agora
        for (int k = 0; k < caracteresTabela; k++) {
          testeTabela[k+atual] = tabela[j]->letras[k];
        }
        testeTabela[C] = '\0';

        // Printa a string resultante na tela
        printf("[%d] - %s\n", ++contSaidas, testeTabela);
        return;
      }
    }
  }

  // Para cada letra na posição 'atual'
  for (int i = 0; i < R; i++) {

    // Adiciona o valor da letra 'ALPHABET[i]' na posição 'atual' à chave
    aux = add(sum, TSomas[atual][i]);

    if (atual < C-caracteresTabela) {
      // printf("Foi de [%s] --para-> ", testeTabela);
      testeTabela[atual] = ALPHABET[i];
      // printf("[%s]\n", testeTabela);
      weakComTabela(tabela, aux, atual+1, pass);
    }
  }
}

// Cada loop varia um caracter com todas as varieades possiveis
// enquanto os outros elemento permanecem em 'a', isso é feito
// pois queremos todas as possibilidades para um caracter
// específico.

void palavraVazia(char* s){

    for(int i= 0; i < C; i++){
        s[i] = 'a';
    }
    s[C] = '\0';
}

void somaCaracteres(int atual){
    char string[C+1];
    Key chave;
    palavraVazia(string);

    for(int j = 0; j < R; j++) {
      string[atual] = ALPHABET[j];
      chave = init_key((unsigned char *) string);
      TSomas[atual][j] = subset_sum(chave, T);
      }


    if(atual < C-1){
        atual++;
        somaCaracteres(atual);
    }
}


void leituraTabela(){
    // Lê a tabela T.
    // T está como variavel global nessa implementação
    unsigned char buffer[C+1];     // Buffer temporário.
    for (int i = 0; i < N; i++) {
        scanf("%s", buffer);
        T[i] = init_key(buffer);
    }
}

// ./a.out ../in/rand5.txt
//./a.out palaf < ../in/rand5.txt
int main(int argc, char *argv[]) {
    TabelaNode** tabelaCombinacoes = NULL;

    if (argc != 2) {
        fprintf(stderr, "Usage: ./encrypt [password] < [table.txt]\n");
        exit(EXIT_FAILURE);
    }

    unsigned char palavra[C+1];
    for (int i = 0; i < C; i++) {
      palavra[i] = argv[1][i];
    }
    palavra[C] = '\0';// para a string ser printada precisa terinar com '\0

    entrada = init_key((unsigned char *) argv[1]);
    //print_key(entrada);
    // Gera palavra de tamanho variad
    //     palvra é a string que recebe todas as combinações
    //     a ser comparadas com o resultado
    testeTabela[C] = '\0';

    leituraTabela();

    somaCaracteres(0);

    printf("Criando tabela de símbolos\n");
    if (C > 1 && C <= 5) {
      caracteresTabela = C-1;
      tabelaCombinacoes = criaTabela();
    } else if (C > 5) {
      caracteresTabela = 5;
      tabelaCombinacoes = criaTabela();
    }
    printf("Tabela de símbolos criada com sucesso\n");

    Key sum = {{0}};
    Key pass = init_key(palavra);

    printf("Entrada: \n");
    print_key(pass);
    printf("Senhas possíveis: \n");

    weakComTabela(tabelaCombinacoes, sum, 0, pass);

    if (tabelaCombinacoes != NULL) {
      for (int i = 0; i < tamTabela; i++) {
        free(tabelaCombinacoes[i]);
      }
      free(tabelaCombinacoes);
    }

    if (contSaidas == 0) {
      printf("\nERRO\nNenhuma senha possível\n\n");
    }

    printf("\nPrograma encerrado com sucesso\n\n");
    return 0;
}
