all: principal clean

principal: main.c pessoas.c musicas.c playlists.c
	gcc *.c -o main

clean:
	rm -rf *.o principal