%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

extern int line_num;
extern FILE *yyin;

typedef struct {
    char name[50];
    char genre[10];
    char type[10];
    int address;
    int value;
    int initialized;
} Symbol;

Symbol symbol_table[100];
int symbol_count = 0;
int label_counter = 1000; /* Labels >= 1000 pour ne pas collisionner avec instruction_counter */
FILE *output_file;
int instruction_counter = 1;
int const_values[100];
int const_count = 0;
int lbl_sinon_global = 0;
int lbl_fin_global = 0;
/* Pile pour les labels SI imbriqués */
int sinon_stack[100];
int sinon_top = -1;

void push_sinon(int lbl) { sinon_stack[++sinon_top] = lbl; }
int  pop_sinon()         { return sinon_stack[sinon_top--]; }
int  peek_sinon()        { return sinon_stack[sinon_top]; }

int fin_stack[100];
int fin_top = -1;

void push_fin(int lbl) { fin_stack[++fin_top] = lbl; }
int  pop_fin()         { return fin_stack[fin_top--]; }

int lookup(const char *name) {
    for (int i = 0; i < symbol_count; i++)
        if (strcmp(symbol_table[i].name, name) == 0) return i;
    return -1;
}

void put_symbol(const char *name, const char *genre, const char *type, int value) {
    if (lookup(name) != -1) {
        fprintf(stderr, "Erreur ligne %d: Declaration multiple de '%s'\n", line_num, name);
        exit(1);
    }
    if (symbol_count >= 100) { fprintf(stderr, "Erreur: Table des symboles pleine\n"); exit(1); }
    strcpy(symbol_table[symbol_count].name, name);
    strcpy(symbol_table[symbol_count].genre, genre);
    strcpy(symbol_table[symbol_count].type, type);
    symbol_table[symbol_count].address = symbol_count;
    symbol_table[symbol_count].value = value;
    if (strcmp(genre, "const") == 0) const_values[const_count++] = value;
    symbol_table[symbol_count].initialized = (strcmp(genre, "const") == 0);
    symbol_count++;
}

int getAdr(const char *name) {
    int idx = lookup(name);
    if (idx == -1) {
        fprintf(stderr, "Erreur ligne %d: Identificateur '%s' non declare\n", line_num, name);
        exit(1);
    }
    return symbol_table[idx].address;
}

char *getGenre(const char *name) {
    int idx = lookup(name);
    if (idx == -1) return NULL;
    return symbol_table[idx].genre;
}

char *getType(const char *name) {
    int idx = lookup(name);
    if (idx == -1) return NULL;
    return symbol_table[idx].type;
}

int getLabel() { return label_counter++; }

void emit(const char *instruction, const char *arg) {
    if (arg)
        fprintf(output_file, "%d\t%s %s\n", instruction_counter, instruction, arg);
    else
        fprintf(output_file, "%d\t%s\n", instruction_counter, instruction);
    instruction_counter++;
}

void yyerror(const char *s) {
    fprintf(stderr, "Erreur syntaxique ligne %d: %s\n", line_num, s);
    exit(1);
}

extern int yylex();
%}

%union {
    int val;
    char *str;
    struct {
        char type[10];
        int value;
    } expr;
}

%token PROGRAMME VAR CONST DEBUT FIN
%token LIRE LIRERC ECRIRE ECRIRERC IMPRIMER IMPRIMERRC PASSER
%token SI ALORS SINON FSI POUR DEPUIS JUSQUA PARPAS FAIRE FPOUR TANTQUE FTQ
%token ENT BOOL_TYPE ET OU NON PUISS VALABS
%token ASSIGN DIFF GTE LTE GT LT EQ PLUS MINUS MULT DIV MOD
%token SEMICOLON LPAREN RPAREN COMMA
%token <str> ID STRING
%token <val> INT BOOL_VAL
%token DOT
%type <expr> expression condition
%type <str> type_decl
%type <val> sinon_opt pas_opt

%left OU
%left ET
%left EQ DIFF LT LTE GT GTE
%left PLUS MINUS
%left MULT DIV MOD
%right PUISS
%right UMINUS NON VALABS

%%

programme:
    PROGRAMME ID SEMICOLON {
        emit("ouverture-bloc", NULL);
    }
    corps FIN DOT {
        emit("fermeture-bloc", NULL);
        printf("\nCode MAP genere avec succes.\n");
    }
;

corps:
    declarations_opt {
        int num_consts = 0, num_vars = 0;
        for (int i = 0; i < symbol_count; i++) {
            if (strcmp(symbol_table[i].genre, "const") == 0) num_consts++;
            else num_vars++;
        }
        if (const_count > 0) {
            fprintf(output_file, ".global ");
            for (int i = 0; i < const_count; i++)
                fprintf(output_file, "%d ", const_values[i]);
            fprintf(output_file, "\n");
        }
        if (num_consts > 0) {
            char buf[20]; sprintf(buf, "%d", num_consts);
            emit("reserver-kst", buf);
        }
        if (num_vars > 0) {
            char buf[20]; sprintf(buf, "%d", num_vars);
            emit("reserver-var", buf);
        }
    }
    DEBUT instructions
;

declarations_opt:
    /* vide */
    | const_section var_section
    | const_section
    | var_section
;

const_section: CONST const_decl_list ;
var_section:   VAR var_decl_list ;

const_decl_list:
    const_decl
    | const_decl_list const_decl
;

const_decl:
    ENT ID EQ INT SEMICOLON        { put_symbol($2, "const", "ent",  $4); }
    | BOOL_TYPE ID EQ BOOL_VAL SEMICOLON { put_symbol($2, "const", "bool", $4); }
;

var_decl_list:
    var_decl
    | var_decl_list var_decl
;

var_decl: type_decl list_vars SEMICOLON ;

type_decl:
    ENT        { $$ = "ent";  }
    | BOOL_TYPE  { $$ = "bool"; }
;

list_vars:
    ID                   { put_symbol($1, "var", $<str>0, 0); }
    | list_vars COMMA ID { put_symbol($3, "var", $<str>0, 0); }
;

instructions:
    instruction
    | instructions instruction
;

instruction:

    /* ===== AFFECTATION ===== */
    ID ASSIGN {
        char *genre = getGenre($1);
        if (!genre) {
            fprintf(stderr, "Erreur ligne %d: '%s' non declare\n", line_num, $1); exit(1);
        }
        if (strcmp(genre, "const") == 0) {
            fprintf(stderr, "Erreur ligne %d: '%s' est une constante, affectation impossible\n", line_num, $1); exit(1);
        }
        char buf[20]; sprintf(buf, "%d", getAdr($1));
        emit("empiler-adr", buf);
    }
    expression SEMICOLON {
        if (strcmp(getType($1), $4.type) != 0) {
            fprintf(stderr, "Erreur ligne %d: Incompatibilite de type dans l'affectation\n", line_num); exit(1);
        }
        emit("affect", NULL);
    }

    /* ===== LIRE ===== */
    | LIRE ID SEMICOLON {
        char *genre = getGenre($2);
        if (!genre) { fprintf(stderr, "Erreur ligne %d: '%s' non declare\n", line_num, $2); exit(1); }
        if (strcmp(genre, "const") == 0) { fprintf(stderr, "Erreur ligne %d: '%s' est une constante\n", line_num, $2); exit(1); }
        char buf[20]; sprintf(buf, "%d", getAdr($2));
        emit("empiler-adr", buf);
        emit("lire", NULL);
    }

    /* ===== LIRERC ===== */
    | LIRERC ID SEMICOLON {
        char *genre = getGenre($2);
        if (!genre) { fprintf(stderr, "Erreur ligne %d: '%s' non declare\n", line_num, $2); exit(1); }
        if (strcmp(genre, "const") == 0) { fprintf(stderr, "Erreur ligne %d: '%s' est une constante\n", line_num, $2); exit(1); }
        char buf[20]; sprintf(buf, "%d", getAdr($2));
        emit("empiler-adr", buf);
        emit("lireRC", NULL);
    }

    /* ===== ECRIRE ===== */
    | ECRIRE ID SEMICOLON {
        char buf[20]; sprintf(buf, "%d", getAdr($2));
        emit("empiler-adr", buf);
        emit("valeur-pile", NULL);
        emit("ecrire", NULL);
    }

    /* ===== ECRIRERC ===== */
    | ECRIRERC ID SEMICOLON {
        char buf[20]; sprintf(buf, "%d", getAdr($2));
        emit("empiler-adr", buf);
        emit("valeur-pile", NULL);
        emit("ecrireRC", NULL);
    }

    /* ===== IMPRIMER ===== */
    | IMPRIMER STRING SEMICOLON   { emit("imprimer",   $2); }

    /* ===== IMPRIMERRC ===== */
    | IMPRIMERRC STRING SEMICOLON { emit("imprimerRC", $2); }

    /* ===== PASSER ===== */
    | PASSER SEMICOLON { /* rien a generer */ }

    /* ===== SI (avec ou sans SINON) =====
       On utilise une regle unifiee pour eviter le conflit dangling-else.
       Schema :
         condition -> bsf lbl_sinon
         [bloc alors]
         bra lbl_fin        (seulement si sinon present)
         lbl_sinon:
         [bloc sinon]       (seulement si sinon present)
         lbl_fin:
    */
    | SI condition {
        int lbl_sinon = getLabel();
        int lbl_fin   = getLabel();

        push_sinon(lbl_sinon); 
        push_fin(lbl_fin);

        char buf[20]; 
        sprintf(buf, "%d", lbl_sinon);
        emit("bsf", buf);
    }
    ALORS instructions sinon_opt FSI {
        int lbl_fin = pop_fin();
        char buf[20];
        sprintf(buf, "%d", lbl_fin);
        emit("bra", buf);
    }

    /* ===== TANTQUE ===== */
    | TANTQUE {
        $<val>$ = instruction_counter; /* memoriser le debut du test */
    }
    condition {
        int lbl_fin = getLabel();
        $<val>$ = lbl_fin;
        char buf[20]; sprintf(buf, "%d", lbl_fin);
        emit("bsf", buf);
    }
    FAIRE instruction FTQ SEMICOLON {
        int lbl_debut = $<val>2;
        int lbl_fin   = $<val>4;
        char buf[20]; sprintf(buf, "%d", lbl_debut);
        emit("bra", buf);
        instruction_counter = lbl_fin;
    }

    /* ===== POUR ===== */
| POUR ID {
    if (strcmp(getType($2), "ent") != 0) {
        fprintf(stderr, "Erreur ligne %d: La variable de boucle '%s' doit etre entiere\n", line_num, $2);
        exit(1);
    }
    if (strcmp(getGenre($2), "const") == 0) {
        fprintf(stderr, "Erreur ligne %d: '%s' est une constante, impossible comme variable de boucle\n", line_num, $2);
        exit(1);
    }
}
DEPUIS {
    /* Empiler l'adresse de i AVANT d'évaluer vi */
    char buf[20]; sprintf(buf, "%d", getAdr($2));
    emit("empiler-adr", buf);
    /* pile : [adr_i]  → vi sera empilé après par expression */
}
expression {
    if (strcmp($6.type, "ent") != 0) {
        fprintf(stderr, "Erreur ligne %d: La valeur initiale doit etre entiere\n", line_num);
        exit(1);
    }
    /* pile : [adr_i, vi] → affect correct ✓ */
    emit("affect", NULL);

    /* lbl_debut APRÈS affect, AVANT le test */
    $<val>$ = instruction_counter;
}
JUSQUA {
    /* Empiler i EN PREMIER */
    char buf[20]; sprintf(buf, "%d", getAdr($2));
    emit("empiler-adr", buf);
    emit("valeur-pile", NULL);
}
expression pas_opt {
    if (strcmp($10.type, "ent") != 0) {
        fprintf(stderr, "Erreur ligne %d: La valeur finale doit etre entiere\n", line_num);
        exit(1);
    }
    /* pile : [i, vf] → pp-egal : i <= vf ✓ */
    emit("pp-egal", NULL);

    int lbl_fin = getLabel();
    $<val>$ = lbl_fin;
    char buf[20]; sprintf(buf, "%d", lbl_fin);
    emit("bsf", buf);
}
FAIRE instruction FPOUR {
    int lbl_debut = $<val>7;    /* action après affect      */
    int lbl_fin   = $<val>12;   /* action après pas_opt     */
    int pas       = $<val>11;   /* pas_opt                  */

    char buf[20]; sprintf(buf, "%d", getAdr($2));
    emit("empiler-adr", buf);
    emit("empiler-adr", buf);
    emit("valeur-pile", NULL);
    char pas_str[20]; sprintf(pas_str, "%d", pas);
    emit("empiler-val", pas_str);
    emit("plus", NULL);
    emit("affect", NULL);

    char buf2[20]; sprintf(buf2, "%d", lbl_debut);
    emit("bra", buf2);
    instruction_counter = lbl_fin;
}

sinon_opt:
    /* vide */
    {
        int lbl_sinon = pop_sinon();
        int lbl_fin   = pop_fin();

        $$ = lbl_fin;  
    }
|
SINON instructions
    {
        int lbl_fin = pop_fin();

        char buf[20];
        sprintf(buf, "%d", lbl_fin);
        emit("bra", buf);

        int lbl_sinon = pop_sinon();
        

        $$ = lbl_fin;
    }
;
/* Pas optionnel pour la boucle POUR */
pas_opt:
    /* vide */ { $$ = 1; }
    | PARPAS INT { $$ = $2; }
;

condition:
    LPAREN expression RPAREN {
        if (strcmp($2.type, "bool") != 0) {
            fprintf(stderr, "Erreur ligne %d: La condition doit etre un booleen\n", line_num);
            exit(1);
        }
        $$ = $2;
    }
;

expression:
    INT {
        strcpy($$.type, "ent"); $$.value = $1;
        char buf[20]; sprintf(buf, "%d", $1);
        emit("empiler-val", buf);
    }
    | BOOL_VAL {
        strcpy($$.type, "bool"); $$.value = $1;
        char buf[20]; sprintf(buf, "%d", $1);
        emit("empiler-val", buf);
    }
    | ID {
        int idx = lookup($1);
        if (idx == -1) {
            fprintf(stderr, "Erreur ligne %d: '%s' non declare\n", line_num, $1); exit(1);
        }
        strcpy($$.type, symbol_table[idx].type);
        $$.value = symbol_table[idx].value;
        char buf[20]; sprintf(buf, "%d", symbol_table[idx].address);
        emit("empiler-adr", buf);
        emit("valeur-pile", NULL);
    }
    /* Operateurs arithmetiques */
    | expression PLUS expression {
        if (strcmp($1.type, "ent") != 0 || strcmp($3.type, "ent") != 0)
            yyerror("Les operandes de '+' doivent etre des entiers");
        strcpy($$.type, "ent"); emit("plus", NULL);
    }
    | expression MINUS expression {
        if (strcmp($1.type, "ent") != 0 || strcmp($3.type, "ent") != 0)
            yyerror("Les operandes de '-' doivent etre des entiers");
        strcpy($$.type, "ent"); emit("moins", NULL);
    }
    | expression MULT expression {
        if (strcmp($1.type, "ent") != 0 || strcmp($3.type, "ent") != 0)
            yyerror("Les operandes de '*' doivent etre des entiers");
        strcpy($$.type, "ent"); emit("mult", NULL);
    }
    | expression DIV expression {
        if (strcmp($1.type, "ent") != 0 || strcmp($3.type, "ent") != 0)
            yyerror("Les operandes de '/' doivent etre des entiers");
        strcpy($$.type, "ent"); emit("div", NULL);
    }
    | expression MOD expression {
        if (strcmp($1.type, "ent") != 0 || strcmp($3.type, "ent") != 0)
            yyerror("Les operandes de '%' doivent etre des entiers");
        strcpy($$.type, "ent"); emit("mod", NULL);
    }
    | PUISS LPAREN expression COMMA expression RPAREN {
    if (strcmp($3.type, "ent") != 0 || strcmp($5.type, "ent") != 0)
        yyerror("Les operandes de 'puiss' doivent etre des entiers");
    strcpy($$.type, "ent");
    emit("puiss", NULL);
}
    | VALABS LPAREN expression RPAREN {
        if (strcmp($3.type, "ent") != 0)
            yyerror("L'operande de 'valabs' doit etre un entier");
        strcpy($$.type, "ent"); emit("valabs", NULL);
    }
    | MINUS expression %prec UMINUS {
        if (strcmp($2.type, "ent") != 0)
            yyerror("L'operande du moins unaire doit etre un entier");
        strcpy($$.type, "ent"); emit("neg", NULL);
    }
    /* Operateurs de comparaison */
    | expression EQ  expression { strcpy($$.type, "bool"); emit("egal",    NULL); }
    | expression DIFF expression { strcpy($$.type, "bool"); emit("dif",    NULL); }
    | expression LT  expression { strcpy($$.type, "bool"); emit("pps",     NULL); }
    | expression GT  expression { strcpy($$.type, "bool"); emit("pgs",     NULL); }
    | expression LTE expression { strcpy($$.type, "bool"); emit("pp-egal", NULL); }
    | expression GTE expression { strcpy($$.type, "bool"); emit("pg-egal", NULL); }
    /* Operateurs logiques */
    | expression ET expression {
        if (strcmp($1.type, "bool") != 0 || strcmp($3.type, "bool") != 0)
            yyerror("Les operandes de 'et' doivent etre des booleens");
        strcpy($$.type, "bool"); emit("et", NULL);
    }
    | expression OU expression {
        if (strcmp($1.type, "bool") != 0 || strcmp($3.type, "bool") != 0)
            yyerror("Les operandes de 'ou' doivent etre des booleens");
        strcpy($$.type, "bool"); emit("ou", NULL);
    }
    | NON expression {
        if (strcmp($2.type, "bool") != 0)
            yyerror("L'operande de 'non' doit etre un booleen");
        strcpy($$.type, "bool"); emit("non", NULL);
    }
    | LPAREN expression RPAREN { $$ = $2; }
;

%%
