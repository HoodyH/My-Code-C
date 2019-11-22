
output: main
	gcc main.o -o output
.PHONY: output


main: main.c
	gcc -c main.c

.PHONY: clean
clean:
	rm *.o output
	
run:
	{ \
	make ;\
	./output ;\
	}

