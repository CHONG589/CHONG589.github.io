


main: main.o llist.o
	$(CC)  $^ -o $@

main.o: main.c 
	$(CC) $^ -c -g -o $@

llist.o: llist.c
	$(CC) $^ -c -g -o $@

clean:
	rm *.o main -rf