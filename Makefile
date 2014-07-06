CC=gcc
CFLAGS=-Wall -g -O3
DEPS = algorithm.h controlTable.h dataParse.h nodeOperations.h types.h
OBJ = main.o algorithm.o controlTable.o dataParse.o nodeOperations.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

exec: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(OBJ) *~ core exec