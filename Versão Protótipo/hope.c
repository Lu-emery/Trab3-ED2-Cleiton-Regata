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
#include "hope.h"

struct tabelaNode {
  unsigned char letras[C+1];
  Key chave;
  TabelaNode* next;
};

TabelaNode** criaTabela() {
  // Calcula o número de combinações possíveis para a tabela
  // Usamos 2x o valor mínimo para reduzir o número de colisões na hash
  tamTabela = 4000037;
  printf("A tabela tem [%d] combinações\n", tamTabela);

  // Cria a tabela na memória com o tamanho referente
  tabelaCombinacoes = malloc(tamTabela * sizeof(TabelaNode*));
  for (int l = 0; l < tamTabela; l++) {
    tabelaCombinacoes[l] = NULL;
  }

  // Chave auxiliar 'combinacao' começa vazia
  Key combinacao = {{0}};
  // String de caracteres referente à chave auxiliar 'combinacao' começa vazia ("aaaaa")
  unsigned char nome[caracteresTabela+1];
  for (int i = 0; i < caracteresTabela; i++) {
    nome[i] = 'a';
  }
  nome[caracteresTabela] = '\0';

  // Preenche a tabela de combinações
  preencheTabela(1, combinacao, nome);

  // Retorna a tabela de combinaçõeese
  return tabelaCombinacoes;
}

int tabelaKeyHash(Key key) {
  int hash = 1;

  for (int i = 0; i < C; i++) {
    hash = (251*hash + key.digit[i]) % tamTabela;
    // h = (251*h + s[i]) % M;
  }

  if (hash < 0) {
    hash -= 2*hash;
  }

  //hash = hash % tamTabela;

  // printf("Hash: [%d]\n", hash);
  return hash;
}

void preencheTabela(int atual, Key combinacao, unsigned char* nome) {

  // Cria uma chave auxiliar vazia
  Key aux = {{0}};

  // Para cada letra em ALPHABET
  for(int i = 0; i < R; i++) {

    // Adiciona o valor da letra 'ALPHABET[i]' na posição 'atual' à chave auxiliar
    aux = add(combinacao, TSomas[atual][i]);
    // Adicionamos o caracter à string
    nome[atual-1] = ALPHABET[i];

    // Se o caracter a ser inserido for fazer a
    //   string ter o tamanho de uma chave completa
    if(atual == caracteresTabela) {

      int hashTabela = tabelaKeyHash(aux);
      // printf("hashTabela: [%d]\n", hashTabela);

      if (tabelaCombinacoes[hashTabela] == NULL) {
        // printf("Entrou no NULL\n\n\n\n\n");
        tabelaCombinacoes[hashTabela] = malloc(sizeof(TabelaNode));
        for (int j = 0; j < caracteresTabela; j++) {
          tabelaCombinacoes[hashTabela]->letras[j] = nome[j];
        }
        tabelaCombinacoes[hashTabela]->letras[caracteresTabela] = '\0';
        tabelaCombinacoes[hashTabela]->chave = aux;
        tabelaCombinacoes[hashTabela]->next = NULL;
        // printf("Inseriu na tabela [%s]: ", tabela[hashTabela]->letras); print_key(tabela[hashTabela]->chave);
      } else {
        // printf("Entrou no != NULL\n");
        TabelaNode* auxNode = malloc(sizeof(TabelaNode));

        for (int j = 0; j < caracteresTabela; j++) {
          auxNode->letras[j] = nome[j];
        }
        auxNode->letras[caracteresTabela] = '\0';
        auxNode->chave = aux;

        auxNode->next = tabelaCombinacoes[hashTabela];
        tabelaCombinacoes[hashTabela] = auxNode;

        // Salvamos a chave e a string em uma posição da tabelaCombinacoes
        // printf("Inseriu na tabelaCombinacoes [%s]: ", auxNode->next->letras); print_key(auxNode->next->chave);
      }
      // printf("Fez hash [%d]\n", hashTabela);
    }

    // Se a string ainda não tem tamanho para ser útil
    if (atual < caracteresTabela) {

      // Executamos recursivamente o códido passando para a próxima posição na string
      preencheTabela(atual+1, aux, nome);
    }
  }
}

void weakComTabela(Key sum, int atual, Key pass) {
  TabelaNode* auxNode;
  Key aux = {{0}};
  testeTabela[atual] = '\0';

  // Se posição + caracteres armazenados = C
  if (atual == C-caracteresTabela) {

    Key passSub = sub(pass, sum);
    // print_key(passSub);

    int passSubHash = tabelaKeyHash(passSub);
    if (tabelaCombinacoes[passSubHash] != NULL) {
      auxNode = tabelaCombinacoes[passSubHash];
      int cmp = 0;
      while(auxNode != NULL) {
        if (comparaKey(passSub, auxNode->chave)) {
          cmp = 1;
          break;
        }
        auxNode = auxNode->next;
      }

      if (cmp) {
        for (int k = 0; k < caracteresTabela; k++) {
          testeTabela[k+atual] = auxNode->letras[k];
        }
        testeTabela[C] = '\0';

        printf("Saída: [%s]\n", testeTabela);
      }
    }
  }

  if (atual <= C-caracteresTabela) {
    // Para cada letra na posição 'atual'
    for (int i = 0; i < R; i++) {

      // Adiciona o valor da letra 'ALPHABET[i]' na posição 'atual' à chave
      aux = add(sum, TSomas[atual][i]);
      // Adiciona o caracter à string
      testeTabela[atual] = ALPHABET[i];

      // Chama recursivmente a função para a próxima posição
      weakComTabela(aux, atual+1, pass);
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
