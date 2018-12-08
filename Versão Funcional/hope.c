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
  unsigned char letras[C];
  Key chave;
};

TabelaNode** criaTabela() {

  // Calcula o número de combinações possíveis para a tabela
  tamTabela = R;
  for (int i = 1; i < caracteresTabela; i++) {
    tamTabela *= R;
  }
  printf("A tabela tem [%d] combinações\n", tamTabela);

  // Cria a tabela na memória com o tamanho referente
  TabelaNode** tabelaCombinacoes = malloc(tamTabela * sizeof(TabelaNode*));
  for (int i = 0; i < tamTabela; i++) {
    tabelaCombinacoes[i] = malloc(sizeof(TabelaNode));
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
  preencheTabela(tabelaCombinacoes, 1, combinacao, nome);

  // Retorna a tabela de combinaçõeese
  return tabelaCombinacoes;
}

// Um contador para a posição onde inserir um elemento na tabela de combinações
int contTabela = 0;

void preencheTabela(TabelaNode** tabela, int atual, Key combinacao, unsigned char* nome) {

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

      // Salvamos a chave e a string em uma posição da tabela
      tabela[contTabela]->chave = aux;
      for (int j = 0; j < caracteresTabela; j++) {
        tabela[contTabela]->letras[j] = nome[j];
      }
      tabela[contTabela]->letras[caracteresTabela] = '\0';

      // Incrementamos o contador de posição, fazendo a tabela estar em ordem crescente (alfabética)
      contTabela++;
    }

    // Se a string ainda não tem tamanho para ser útil
    if (atual < caracteresTabela) {

      // Executamos recursivamente o códido passando para a próxima posição na string
      preencheTabela(tabela, atual+1, aux, nome);
    }
  }
}

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
        printf("%s\n", testeTabela);
        return;
      }
    }
  }

  // Para cada letra na posição 'atual'
  for (int i = 0; i < R; i++) {

    // Adiciona o valor da letra 'ALPHABET[i]' na posição 'atual' à chave
    aux = add(sum, TSomas[atual][i]);
    // Adiciona o caracter à string
    testeTabela[atual] = ALPHABET[i];

    // Chama recursivmente a função para a próxima posição
    weakComTabela(tabela, aux, atual+1, pass);
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
