#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "key.h"
#include "bst.h"
Key T[N];                      // A tabela T.

int main(int argc, char const *argv[]) {
  srand(time(NULL));

  if (argc != 2) {
      fprintf(stderr, "Usage: ./encrypt [password] < [table.txt]\n");
      exit(EXIT_FAILURE);
  }

  unsigned char buffer[C+1];     // Buffer temporário.
  for (int i = 0; i < N; i++) {
      scanf("%s", buffer);
      T[i] = init_key(buffer);
      T[i].linha = i;
  }



  //criaBstDeTabela();

  return 0;
}
