all: buffer_test

buffer_test: buffer.o unit_test.o
	gcc $^ -o $@

buffer.o: buffer.c
	gcc $^ -Wall -c -o $@
	
unit_test.o: unit_test.c
	gcc $^ -Wall -c -o $@
