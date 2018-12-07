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
$ gcc -Wall key.c hope.c -o hope
$ ./hope exvx5 < in/rand5.txt
i0ocs
passw
/
Entrada:
exvx5   4 23 21 23 31   0010010111101011011111111
Senhas possíveis:
[1] - i0ocs
[2] - passw


===
Programa encerrado com sucesso
===


real    2m44.873s
user    2m1.063s
sys     0m0.516s
*/


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

    leituraTabela();

    somaCaracteres(0);


    //weak(palavra);
    Key sum = {{0}};
    Key pass = init_key(palavra);

    printf("Entrada: \n");
    print_key(pass);
    printf("Senhas possíveis: \n");


    weakNew(sum, 0, pass);

    if (contSaidas == 0) {
      printf("Nenhuma senha possível\n");
    }

    //geradorPalavra(0, palavra);

    printf("\n\n===\nPrograma encerrado com sucesso\n===\n\n");
    return 0;
}
