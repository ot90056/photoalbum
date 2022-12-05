all: buffer_test pabackend_test

buffer_test: buffer.o buffer_test.o
	gcc $^ -o $@

buffer.o: buffer.c
	gcc $^ -g -Wall -c -o $@
	
buffer_test.o: buffer_test.c
	gcc $^ -g -Wall -c -o $@
	
pabackend_test: pabackend.o pabackendtest.o
	g++ $^ -std=c++17 -Wall -o $@
	
pabackendtest.o: pabackendtest.cpp
	g++ $^ -std=c++17 -Wall -c -o $@

pabackend.o: pabackend.cpp
	g++ $^ -std=c++17 -Wall -c -o $@

api: pabackend.o
	g++ -std=c++11 api.cpp -ljsoncpp -o api.o
	./api.o

.PHONY: clean
clean:
	rm *.o
	rm buffer_test
	rm pabackend_test
