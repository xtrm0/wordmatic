
FLAGS=-c -Wall 
#-pedantic -ansi
LNFLAGS=-Wall 
#-pedantic -ansi
LNLIBS=
CC = gcc
IDIR=include
ODIR=objects
CDIR=code
TDIR=tests
TBIN=testsbin
OBJECTS=trie.o matrix.o input_man.o solver.o
OBJECTSPATH = $(patsubst %,$(ODIR)/%,$(OBJECTS))
.PHONY: all clean debug


all: wordmatic

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

test: $(TBIN)/trie.test


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
