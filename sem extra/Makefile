all: principal exec 

principal: main.c pessoas.c musicas.c playlists.c
	gcc *.c -o main

exec: main
	./main

clean:
	rm -rf Saida