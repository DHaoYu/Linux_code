libmymath.a:add.o sub.o
	ar -rc $@ $^
add:add.c
	gcc -c add.c -o add.o
sub:sub.c
	gcc -c sub.c -o sub.o
.PHONY:output
output:
	mkdir -p lib/lib
	mkdir -p lib/include
	cp -rf *.h lib/include
	cp -rf *.a lib/lib

.PHONY:clean
clean:
	rm -f *.o *.a
