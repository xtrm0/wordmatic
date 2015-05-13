
FLAGS=-O3 -Ofast -c -Wall -Wno-strict-overflow -Wno-unused-result
#-pedantic -ansi
LNFLAGS=-O3 -Ofast -Wall -Wno-strict-overflow -Wno-unused-result
#-pedantic -ansi
LNLIBS=
CC = gcc
IDIR=include
ODIR=objects
CDIR=code
TDIR=$(CDIR)/tests
TBIN=bin
OBJECTS=trie.o matrix.o input_man.o solver.o stl.o avl.o
OBJECTSPATH = $(patsubst %,$(ODIR)/%,$(OBJECTS))
.PHONY: all clean debug


all: wordmatic

execall: wordmatic
		find ./tests/ -name "*.puz" -exec sh -c "echo {}; ./wordmatic dictionaries/input.dic {}" \;

execall-time: wordmatic
	find ./tests/ -name "*.puz" -exec sh -c "echo {}; /usr/bin/time -v ./wordmatic dictionaries/input.dic {}" \;

execall-valgrind: wordmatic
	find ./tests/ -name "*.puz" -exec sh -c "echo {}; valgrind --leak-check=full ./wordmatic dictionaries/input.dic {}" \;


testall: wordmatic
	find ./tests/ -name "*.puz" -exec sh -c "./verifwrdmtc01 dictionaries/input.dic {}" \;

testall-time: wordmatic
		find ./tests/ -name "*.puz" -exec sh -c "echo {}; /usr/bin/time -v ./verifwrdmtc01 dictionaries/input.dic {}" \;

testall-valgrind: wordmatic
		find ./tests/ -name "*.puz" -exec sh -c "echo {}; valgrind --leak-check=full ./verifwrdmtc01 dictionaries/input.dic {}" \;

createzip: clean
	rm sendtomoo.zip
	zip -r sendtomoo.zip Makefile
	zip -r sendtomoo.zip include
	zip -r sendtomoo.zip code
	zip -r sendtomoo.zip objects
	zip -r sendtomoo.zip bin


drun: debug
	./wordmatic

run: release
	./wordmatic

release: clean
release: wormatic

gdb: debug
	gdb ./wordmatic

debug: clean
debug: FLAGS += -D_DEBUG -g
debug: LNFLAGS += -D_DEBUG -g
debug: wordmatic

test: clean
test: FLAGS += -D_DEBUG -g
test: LNFLAGS += -D_DEBUG -g
test: $(TBIN)/avl.test $(TBIN)/trie.test


clean:
	rm -f $(ODIR)/*.o wordmatic $(TBIN)/*


wordmatic: $(OBJECTSPATH) $(ODIR)/main.o
	$(CC) $(LNFLAGS) $(OBJECTSPATH) $(ODIR)/main.o $(LNLIBS) -o wordmatic

$(ODIR)/%.o: $(CDIR)/%.c
	$(CC) $(FLAGS) $< -o $@
$(ODIR)/%.o: $(TDIR)/%.c
	$(CC) $(FLAGS) $< -o $@


$(TBIN)/trie.test: $(OBJECTSPATH) $(ODIR)/trie.test.o
	$(CC) $(LNFLAGS) $(OBJECTSPATH) $(ODIR)/trie.test.o $(LNLIBS) -o $(TBIN)/trie.test

$(TBIN)/avl.test: $(OBJECTSPATH) $(ODIR)/avl.test.o
	$(CC) $(LNFLAGS) $(OBJECTSPATH) $(ODIR)/avl.test.o $(LNLIBS) -o $(TBIN)/avl.test
