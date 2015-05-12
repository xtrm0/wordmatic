
FLAGS=-O3 -c -Wall
#-pedantic -ansi
LNFLAGS=-O3 -Wall
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
	find ./tests/ -name "*.puz" -exec sh -c "echo {}; /usr/bin/time -v ./wordmatic dictionaries/input.dic {}" \;

testall: wordmatic
	find ./tests/ -name "*.puz" -exec sh -c "echo {}; /usr/bin/time -v ./verifwrdmtc01 dictionaries/input.dic {}" \;


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
test: $(TBIN)/avl.test #$(TBIN)/trie.test


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
