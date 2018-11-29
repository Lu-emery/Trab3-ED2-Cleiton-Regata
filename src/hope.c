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

// Key easyEncrypt(char* palavra){
//     Key sum = {{0}};
//     Key password = init_key((unsigned char *) palavra);
//     print_key(password);
//     for(int i = 0; i < C-1; i++){
//         sum = add(sum, TSomas[i][password.digit[i]] );
//     }
//     print_key(sum);
//
//     return sum;
// }

// Encripta a palavra dada como entrada e compara a
// Encriptação gerada com a que queremos encontrar
void weak(char* palavra){
    Key sum = {{0}};
    Key password = init_key((unsigned char *) palavra);

    print_key(password);
    printf("\n\n");

    for(int i = 0; i < C-1; i++){
        sum = add(sum, TSomas[i][password.digit[i]] );
        print_key(TSomas[i][password.digit[i]]);
    }

    //printf("\n\n");

    //print_key(sum);

    printf("\n" );

    sum = subset_sum_print(password, T);

    printf("\n\n");
    print_key(sum);

    // Compara a emcriptação da entrada em questão
    //     com a encriptação gerada
    if(comparaKey(entrada, sum)){
        //print_key(password);
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

    for(int j = 0; j < 32; j++) {
        string[atual] = ALPHABET[j];
        chave = init_key((unsigned char *) string);
        print_key(chave);
        TSomas[atual][j] = subset_sum(chave, T);
        print_key(TSomas[atual][j]);
        printf("\n");
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


int main(int argc, char *argv[]) {

    if (argc != 2) {
        fprintf(stderr, "Usage: ./encrypt [password] < [table.txt]\n");
        exit(EXIT_FAILURE);
    }

    entrada = init_key((unsigned char *) argv[1]);
    //print_key(entrada);

    // Gera palavra de tamanho variado
    //     palvra é a string que recebe todas as combinações
    //     a ser comparadas com o resultado
    char palavra[C+1] = "i0ocs";
    //palavra[C] = '\0';// para a string ser printada precisa terinar com '\0'

    leituraTabela();

    somaCaracteres(0);

    weak(palavra);

    //geradorPalavra(0, palavra);

    return 0;
}
