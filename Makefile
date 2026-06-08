CC = gcc
FLEX = flex
BISON = bison
CFLAGS = -std=c99 -Wall -g

all: atlas simulateur

atlas: lex.yy.c atlas.tab.c atlas.tab.h main.c
	$(CC) $(CFLAGS) -o atlas lex.yy.c atlas.tab.c main.c -lm

simulateur: simulateur.c
	$(CC) $(CFLAGS) -o simulateur simulateur.c -lm

lex.yy.c: atlas.l atlas.tab.h
	$(FLEX) atlas.l

atlas.tab.c atlas.tab.h: atlas.y
	$(BISON) -d atlas.y

test1: atlas simulateur
	@echo "=== Test 1: Somme ==="
	@echo "10" > /tmp/input.txt
	@echo "20" >> /tmp/input.txt
	@if [ -f prog1.atlas ]; then ./atlas prog1.atlas < /tmp/input.txt; else echo "Erreur: prog1.atlas manquant"; fi

test2: atlas simulateur
	@echo "=== Test 2: Conditionnel ==="
	@echo "50" > /tmp/input.txt
	@if [ -f prog2.atlas ]; then ./atlas prog2.atlas < /tmp/input.txt; else echo "Erreur: prog2.atlas manquant"; fi

test3: atlas simulateur
	@echo "=== Test 3: Factoriel ==="
	@echo "5" > /tmp/input.txt
	@if [ -f prog3.atlas ]; then ./atlas prog3.atlas < /tmp/input.txt; else echo "Erreur: prog3.atlas manquant"; fi

clean:
	rm -f lex.yy.c atlas.tab.c atlas.tab.h *.o atlas simulateur
	rm -f *.map

.PHONY: all clean test1 test2 test3