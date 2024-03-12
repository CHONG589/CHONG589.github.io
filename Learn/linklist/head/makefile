

main: main.o list.o
	$(CC)  $^ -o $@

main.o: main.c 
	$(CC) $^ -c -g -o $@

list.o: list.c
	$(CC) $^ -c -g -o $@

clean:
	rm *.o main -rf