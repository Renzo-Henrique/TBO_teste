CC=gcc
CFLAGS=\
	-g \
	-Wall \
	-Wextra \
	-pedantic \
	#-ansi 
LIBS=-lm -I ./headers 

SRC=$(wildcard ./src/*.c)

all: clean trab2

trab2: $(SRC)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	$(RM) ./trab2

test:
	bash ./utils/test.sh

docs:
	doxygen ./Doxyfile

format:
	clang-format --style=file -i ./src/*.c ./headers/*.h

.PHONY: all clean test docs format

tes: all
	./trab2 in/in_t saida.txt

testar: all create_output
	
	./trab2 in/in_t output/in.txt
	./trab2 in/N10_S3_C3_M3.txt output/in10.txt
	./trab2 in/N100_S20_C30_M5.txt output/in100.txt
	./trab2 in/N1000_S50_C300_M10.txt output/in1000.txt

create_output:
	rm -rf output
	mkdir output

maior: all
	./trab2 in/N10000_S50_C300_M10.txt maior_caso.txt

valgrind: all create_output
	valgrind ./trab2 in/in_t output/in.txt
	valgrind ./trab2 in/N10_S3_C3_M3.txt output/in10.txt
	valgrind ./trab2 in/N100_S20_C30_M5.txt output/in100.txt
	valgrind ./trab2 in/N1000_S50_C300_M10.txt output/in1000.txt

