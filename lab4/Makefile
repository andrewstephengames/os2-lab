all: tema
tema: tema.o utils.o rsa.o
	gcc -Wall tema.o utils.o rsa.o -o tema
tema.o: tema.c utils.h rsa.h
	gcc -Wall -c tema.c
rsa.o: rsa.c
	gcc -Wall -c rsa.c
utils.o: utils.c
	gcc -Wall -c utils.c
run: tema
	./tema
clean:
	rm -f *.o *~ tema
