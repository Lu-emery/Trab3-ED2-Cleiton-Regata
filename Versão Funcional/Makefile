
enc: key.o encrypt.o
	gcc -Wall key.c encrypt.c -o encrypt

decrypt: key.o hope.o tabelaSimbolos.o key.h
	gcc -Wall key.c hope.c tabelaSimbolos.c -o decrypt

brute: key.o brute.o
	gcc -Wall key.c brute.c -o brute

clean:
	rm -f *.o a.out encrypt gmon.out prof brute
