
FLAGS=-O3 -Ofast -c -Wall -Wno-strict-overflow -Wno-unused-result
#We wont be using -pedantic -ansi because we want variadic macros
LNFLAGS=-O3 -Ofast
LNLIBS=
CC = gcc
LN = gcc
IDIR=include
ODIR=objects
CDIR=code
TDIR=$(CDIR)/tests
TBIN=bin
OBJECTS=trie.o matrix.o input_man.o solver.o stl.o avl.o
OBJECTSPATH = $(patsubst %,$(ODIR)/%,$(OBJECTS))
.PHONY: all clean debug


all: wordmatic

#executa para todos os testes em ./tests/
execall: wordmatic
		find ./tests/ -name "*.puz" -exec sh -c "echo {}; ./wordmatic dictionaries/input.dic {}" \;

#mede o tempo e o tamanho da heap para todos os testes em ./tests/
execall-time: wordmatic
	find ./tests/ -name "*.puz" -exec sh -c "echo {}; /usr/bin/time -v ./wordmatic dictionaries/input.dic {}" \;

#mede a utilizacao exata de memoria para todos os testes em ./tests/
execall-valgrind: wordmatic
	find ./tests/ -name "*.puz" -exec sh -c "echo {}; valgrind --leak-check=full ./wordmatic dictionaries/input.dic {}" \;

#(para a solucao oficial) executa para todos os testes em ./tests/
testall: wordmatic
	find ./tests/ -name "*.puz" -exec sh -c "./verifwrdmtc01 dictionaries/input.dic {}" \;
#(para a solucao oficial) mede o tempo e o tamanho da heap para todos os testes em ./tests/
testall-time: wordmatic
		find ./tests/ -name "*.puz" -exec sh -c "echo {}; /usr/bin/time -v ./verifwrdmtc01 dictionaries/input.dic {}" \;
#(para a solucao oficial) mede a utilizacao exata de memoria para todos os testes em ./tests/
testall-valgrind: wordmatic
		find ./tests/ -name "*.puz" -exec sh -c "echo {}; valgrind --leak-check=full ./verifwrdmtc01 dictionaries/input.dic {}" \;

#cria um zip do projeto
createzip: clean
	rm sendtomoo.zip
	zip -r sendtomoo.zip Makefile
	zip -r sendtomoo.zip include
	zip -r sendtomoo.zip code
	zip -r sendtomoo.zip objects
	zip -r sendtomoo.zip bin

#corre o programa apos compilar com as flags de debus
drun: debug
	./wordmatic

#corre o programa normalmente
run: release
	./wordmatic

#chama o clean e depois compila normalmente
release: clean
release: wormatic

#compila em modo de debug e executa com o gdb
gdb: debug
	gdb ./wordmatic

#compila o programa em modo debug
debug: clean
debug: FLAGS = -c -D_DEBUG -g -Wall
debug: LNFLAGS += -D_DEBUG -g -Wall
debug: wordmatic

#compila os unit tests para a trie e para a avl
test: clean
test: FLAGS += -D_DEBUG -g
test: LNFLAGS += -D_DEBUG -g
test: $(TBIN)/avl.test $(TBIN)/trie.test

#limpa todos os objetos e executaveis
clean:
	rm -f $(ODIR)/*.o wordmatic $(TBIN)/*

#rules to link wordmatic
wordmatic: $(OBJECTSPATH) $(ODIR)/main.o
	$(LN) $(LNFLAGS) $(OBJECTSPATH) $(ODIR)/main.o $(LNLIBS) -o wordmatic

#rules to compile objects on code dir
$(ODIR)/%.o: $(CDIR)/%.c
	$(CC) $(FLAGS) $< -o $@
#rules to compile objects on tests dir
$(ODIR)/%.o: $(TDIR)/%.c
	$(CC) $(FLAGS) $< -o $@


##############
# UNIT TESTS #
##############

$(TBIN)/trie.test: $(OBJECTSPATH) $(ODIR)/trie.test.o
	$(LN) $(LNFLAGS) $(OBJECTSPATH) $(ODIR)/trie.test.o $(LNLIBS) -o $(TBIN)/trie.test

$(TBIN)/avl.test: $(OBJECTSPATH) $(ODIR)/avl.test.o
	$(LN) $(LNFLAGS) $(OBJECTSPATH) $(ODIR)/avl.test.o $(LNLIBS) -o $(TBIN)/avl.test
