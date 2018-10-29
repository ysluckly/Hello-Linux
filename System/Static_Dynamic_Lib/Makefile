libmymath.a:add.o sub.o
	ar -rc libmymath.a add.o sub.o
add.o:add.c
	gcc -c add.c -o add.o
sub.o:sub.c
	gcc -c sub.c -o sub.o
.PHONY:clean
clean:
	rm -f add.o sub.o
