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
Key entrada;

// Encripta a palavra dada como entrada e compara a
// Encriptação gerada com a que queremos encontrar
void brute(char* palavra){
    Key password;                  // A senha fornecida pelo usuário.
    Key encrypted;                 // A senha criptografada.

    // Cria key regerente ao password informado
    password = init_key((unsigned char *) palavra);

    // Calcula a soma de subconjunto.
    encrypted = subset_sum(password, T);

    // Compara a emcriptação da entrada em questão
    //     com a encriptação gerada
    if(comparaKey(entrada, encrypted)){
        print_key(password);
    }

}

// Cada loop varia um caracter com todas as varieades possiveis
//     a recursão é chamada novamente somente se ainda couber mais
//     um elemento
void geradorPalavra(int atual, char palavra[C]){
    for(int j = 0; j < 32; j++) {
        if(atual == C-1) {
            palavra[atual] = ALPHABET[j];
            brute(palavra);
        } else {
            palavra[atual] = ALPHABET[j];
            geradorPalavra(atual+1, palavra);

        }
    }
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
    char palavra[C+1];
    palavra[C] = '\0';// para a string ser printada precisa terinar com '\0'

    // Lê a tabela T.
    // T está como variavel global nessa implementação
    unsigned char buffer[C+1];     // Buffer temporário.
    for (int i = 0; i < N; i++) {
        scanf("%s", buffer);
        T[i] = init_key(buffer);
    }

    geradorPalavra(0, palavra);

    return 0;
}
