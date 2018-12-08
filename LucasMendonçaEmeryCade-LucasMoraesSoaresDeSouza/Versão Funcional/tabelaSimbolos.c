#include <stdio.h>
#include <stdlib.h>
#include "hope.h"
#include "key.h"

int main(int argc, char *argv[]) {

  // Cria a estrutura da tabela de símbolos
  TabelaNode** tabelaCombinacoes = NULL;

  if (argc != 2) {
      fprintf(stderr, "Usage: ./encrypt [password] < [table.txt]\n");
      exit(EXIT_FAILURE);
  }

  // Cria uma palavra de unsigned char a partir de argv[1]
  unsigned char palavra[C+1];
  for (int i = 0; i < C; i++) {
    palavra[i] = argv[1][i];
  }

  // Colocamos '\0' no final dos vetores de caracteres para facilitar a impressão
  palavra[C] = '\0';

  // Cria a chave pass (a que deve ser encontrada nas funções)
  Key pass = init_key(palavra);

  // Lê e armazena a tabela
  leituraTabela();

  // Cria a matriz de valores de cada caracter em cada posição
  somaCaracteres(0);

  // Cria o vetor de todas as combinações possíveis de um número de caracteres
  printf("Criando tabela de símbolos\n");
  if (C > 1 && C <= 5) {
    // Se C < 5, usamos C-1
    caracteresTabela = C-1;
    tabelaCombinacoes = criaTabela();
  } else if (C > 5) {
    // Se C > 5, usamos 5 para não ocupar RAM de mais
    caracteresTabela = 5;
    tabelaCombinacoes = criaTabela();
  }
  printf("Tabela de símbolos criada com sucesso\n");

  // Cria mais uma chave auxiliar 'sum' com valor 0
  Key sum = {{0}};

  printf("Entrada: \n");
  print_key(pass);
  printf("Senhas possíveis: \n");

  // Define as possibilidades de senhas que possam ter sido encriptadas para gerar
  //   a string 'palavra' (e a chave 'pass')
  weakComTabela(tabelaCombinacoes, sum, 0, pass);

  // Confirma se a tabela realmente foi feita
  //   se sim, dá free na estrutura
  if (tabelaCombinacoes != NULL) {
    for (int i = 0; i < tamTabela; i++) {
      free(tabelaCombinacoes[i]);
    }
    free(tabelaCombinacoes);
  }

  // Encerra a execução
  printf("\nPrograma encerrado com sucesso\n\n");
  return 0;
}
