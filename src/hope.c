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


unsigned char testeAtual[C+1];
int contSaidas = 0;

void weakNew(Key sum, int atual, Key pass){
  Key aux;

  for(int i = 0; i < R; i++){
    if (atual == C) {
      if (comparaKey(pass, aux)) {
        printf("[%d] - %s\n", ++contSaidas, testeAtual);
      }
      return;
    }
    aux = add(sum, TSomas[atual][i]);

    if(atual < C){
      testeAtual[atual] = ALPHABET[i];
      weakNew(aux, atual +1, pass);
    }
  }
}
/*

*/
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
  printf("Criando tabela\n");
  tamTabela = R;
  for (int i = 1; i < caracteresTabela; i++) {
    tamTabela *= R;
  }
  printf("Tabela tem tamanho %d\n", tamTabela);
  TabelaNode** tabelaCombinacoes = malloc(tamTabela * sizeof(TabelaNode*));
  for (int i = 0; i < tamTabela; i++) {
    tabelaCombinacoes[i] = malloc(sizeof(TabelaNode));
  }
  printf("Tabela mallocada\n");

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

      // printf("Inseriu na tabela [%d] - Nome: [%s] | Chave: ", contTabela+1, nome); print_key(combinacao);

      // TESTE
      /*
      unsigned char nomeTeste[C+1];
      Key teste = {{0}};
      nomeTeste[0] = 'a';
      nomeTeste[C] = '\0';
      for (int l = 1; l < C; l++) {
        nomeTeste[l] = nome[l-1];
      }
      printf("Nome = [%s] | NomeTeste = [%s]\n", nome, nomeTeste);
      teste = init_key(nomeTeste);
      teste = subset_sum(teste, T);
      printf("aux | teste\n");
      for (int l = 0; l < C; l++) {
        printf(" %2d | %2d\n", aux.digit[l], teste.digit[l]);
      }
      printf("\n");
      if (!comparaKey(aux, teste)) {
        printf("Chave: ");print_key(aux);printf("==/==\nTeste: ");print_key(teste);
        printf("O erro tá nessa porra aqui\n");
      } else {
        printf("Chave: ");print_key(aux);printf("=====\nTeste: ");print_key(teste);
        printf("Esse aqui deu certo\n");
      }
      */
      //TESTE

      // printf("\n");
      tabela[contTabela]->chave = aux;
      for (int j = 0; j < caracteresTabela; j++) {
        tabela[contTabela]->letras[j-1] = nome[j-1];
      }
      contTabela++;
    }

    if (atual < caracteresTabela) {
      nome[atual-1] = ALPHABET[i];
      preencheTabela(tabela, atual+1, aux, nome);
    }
  }
}

unsigned char testeTabela[C+1];
void weakComTabela(TabelaNode** tabela, Key sum, int atual, Key pass) {
  Key aux;
  testeTabela[atual] = '\0';

  // sum tá virando pass na primeira execuçãao

  for (int i = 0; i < R; i++) {
    if (atual == C-caracteresTabela) {
      for (int j = 0; j < tamTabela; j++) {
        if (testeTabela[1] == 'i') {
          printf("Somando: [%s] e [%s]\n", testeTabela, tabela[j]->letras);
          printf("Somando: \n");print_key(sum);print_key(tabela[j]->chave);
        }
        aux = add(sum, tabela[j]->chave);
        if (testeTabela[1] == 'i') {
          printf("=== ");print_key(aux);printf("\n");
        }
        // printf("Comparando keys: \n");
        // print_key(pass); print_key(aux);

        if (comparaKey(pass, aux)) {
          for (int k = atual; k < C; k++) {
            testeTabela[k] = tabela[j]->letras[k];
          }
          printf("Saída [%d] - %s\n", ++contSaidas, testeTabela);
          return;
        }
      }
    }

    if (atual < C-caracteresTabela) {
      // printf("Foi de [%s] --para-> ", testeTabela);
      testeTabela[atual] = ALPHABET[i];
      // printf("[%s]\n", testeTabela);
      weakComTabela(tabela, sum, atual+1, pass);
    }
  }
}

// Encripta a palavra dada como entrada e compara a
// Encriptação gerada com a que queremos encontrar
void weak(char* palavra){
    int i;
    Key sum = {{0}};
    Key password = init_key((unsigned char *) palavra);

    printf("Entrada: \n");
    print_key(password);
    printf("\n");


    for(i = 0; i < C-1; i++){
      printf("Sum [%d]: \n", i);
      print_key(sum);
      // TSoma[qual posição do caracter][qual caracter]
      sum = add(sum, TSomas[i][password.digit[i]]);
    }


    printf("Sum [%d]: \n", i);
    print_key(sum);

    printf("\n" );

    sum = subset_sum(password, T);
    printf("Sum Final: \n");
    print_key(sum);

    printf("\n\n");

    // Compara a emcriptação da entrada em questão
    //     com a encriptação gerada
    if(comparaKey(entrada, sum) == 0){
      printf("Senha foi encontrada.\nEntrada:\n");
      print_key(password);
      printf("Senha Resultante: \n");
      print_key(sum);
      printf("\n\n");
    }
}

// Cada loop varia um caracter com todas as varieades possiveis
//     a recursão é chamada novamente somente se ainda couber mais
//     um elemento
void geradorPalavra(int atual, char palavra[C]){
    for(int j = 0; j < 32; j++) {
        if(atual == C-1) {
            palavra[atual] = ALPHABET[j];
            weak(palavra);
        } else {
            palavra[atual] = ALPHABET[j];
            geradorPalavra(atual+1, palavra);

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

/* Aqui iremos fazer o pre-processamento de todas as combinações
   referentes a cada caracter.

   Cada caracter da senha referece a 5 linhas de T, logo existem
   5*5 possibilidades para cada caracter.
   ao pre-processar todas essas 25 possibilidades para cada caracter
   iremos apenas acessar as somas posteriormente.

   O acesso se dá por uma matriz onde o primeiro indice se refere
   a posição do caracter na senha e o segundo a qual caracter está
   na posição em questão. Assim o acesso se dá de forma linear.

   A geração de tal matriz se dá na realização de todas as possiveis
   somas das 5 keys referentes ao caracter.
*/
void geraTSoma(){

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
    testeAtual[C] = '\0';
    testeTabela[C] = '\0';

    leituraTabela();

    somaCaracteres(0);

    if (C > 1 && C <= 5) {
      caracteresTabela = C-1;
      tabelaCombinacoes = criaTabela();
    } else if (C > 5) {
      caracteresTabela = 5;
      tabelaCombinacoes = criaTabela();
    }

    printf("\n\n===\nTabela feita com sucesso\n===\n\n");

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

    printf("\n\n===\nPrograma encerrado com sucesso\n===\n\n");
    return 0;

    //weak(palavra);



    weakNew(sum, 0, pass);

    if (contSaidas == 0) {
      printf("Nenhuma senha possível\n");
    }

    //geradorPalavra(0, palavra);

}
