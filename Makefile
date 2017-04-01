all: a1 runPost makeLibrary1 makeLibrary2 compilePost1 compilePost2 adAuthor1 adAuthor2 view a3 db db.o

a1: main.c listOfKeys.c readFromFile.c findAndReplace.c
	gcc -Iinclude main.c listOfKeys.c readFromFile.c findAndReplace.c -std=c99 -g -Wall -ansi -o a1

runPost:
	./a1 post.cc

makeLibrary1: stream.c
	gcc -c stream.c -g -Wall -ansi -o stream.o

makeLibrary2:
	ar cr libstream.a stream.o

compilePost1: post.c
	gcc post.c -o post.o -g -Wall -ansi -c

compilePost2: post.o
	gcc post.o -o post -L. -g -Wall -ansi -lstream

adAuthor1: addauthor.c
	gcc addauthor.c -o addauthor.o -Wall -ansi -g -c

adAuthor2: addauthor.o
	gcc addauthor.o -o addauthor -L. -Wall -ansi -g -lstream

view: view.py
	chmod +x view.py

a3: configParse.c
		gcc configParse.c -std=c99 -g -Wall -ansi -o a3

db: db.o
	gcc db.o -o db -lmysqlclient -L/usr/lib/x86_64-linux-gnu/

db.o: db.c
	gcc db.c -o db.o -c
