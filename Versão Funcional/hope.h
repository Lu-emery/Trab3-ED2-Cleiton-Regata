#include "key.h"

// Armazena, em ordem, todas as combinações possíveis de 5 caracteres (caso base)
// "aaaaa", "aaaaab", ..., "aaaa5", "aaaba", ..., "baaaa", ..., "55555"
// Para cada caracter na primeira posição, tem 32^4 combinações
// Logo, o tamanho da tabela é 32^5(33.554.432) chaves
// Cada chave tem 6 caracteres de 5 bits, logo, a tabela tem 33.554.432*6*5(1.006.632.960) bits
// Que equivale a aprox. 1,006 GB de RAM em uso pelo programa
typedef struct tabelaNode TabelaNode;

// VARIÁVEIS GLOBAIS
  // A tabela T.
  Key T[N];
  // Cada resultado refente a um caracter específico em uma posição específica da string
  Key TSomas[C][32];

  // Uma variável que armazena o tamanho da tabela de combinações
  int tamTabela;
  // O número de caracteres de cada combinação da tabela de combinações
  int caracteresTabela;

  // A contagem do número de saídas (usado para facilitar visualização da saída)
  // O vetor de caracteres utilizado para armazenar a sequência de caracteres que chegou no valor correto
  unsigned char testeTabela[C+1];


// TABELA DE SÍMBOLOS
  // Cria, malloca e retorna a tabela de combinações usada no código.
  TabelaNode** criaTabela();
  // Preenche recursivamente a tabela de combinações, usando a recursão como pilha para melhorar o desempenho
  void preencheTabela(TabelaNode**, int, Key, unsigned char*);
  // Faz o brute force para os (C-caracteresTabela) primeiros elementos das strings
  //   depois, soma os resultados com cada valores pré-calculados na tabela de combinações
  //   se algum dos resultados for igual à key 'pass' da entrada, imprime a string que gerou a chave
  void weakComTabela(TabelaNode**, Key, int, Key);

// Cria uma tabela que armazena todos os valores de um caracter específico em uma posição específica da string
//   isso é feito para evitar a necessidade de fazer o cálculo sempre que isso for necessário
void somaCaracteres(int);
// Lê e armazena a tabela de encriptação T do arquivo inserido
void leituraTabela();
// Transforma todos os caracteres de uma string em 'a', que tem o valor 0
void palavraVazia(char*);
