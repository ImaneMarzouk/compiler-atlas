#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define STACK_SIZE 1000
#define MAX_INSTRUCTIONS 10000

int pile[STACK_SIZE];
int ip = -1;
int co = 0;
int num_instructions = 0;
int global_consts[100];
int n = 0;
typedef struct {
    int id_instruction; // Le numéro de ligne réel écrit dans le .map
    char *mnemonic;
    char *arg;
} Instruction;

Instruction parsed_instructions[MAX_INSTRUCTIONS];

void push(int val) {
    if (ip + 1 >= STACK_SIZE) {
        fprintf(stderr, "Erreur: Débordement de pile\n");
        exit(1);
    }
    pile[++ip] = val;
}

int pop() {
    if (ip < 0) {
        fprintf(stderr, "Erreur: Pile vide\n");
        exit(1);
    }
    return pile[ip--];
}

// Fonction pour trouver l'index dans le tableau C à partir du numéro d'instruction MAP
int trouver_index_instruction(int target_id) {
    for (int i = 0; i < num_instructions; i++) {
        // Cas 1: C'est le numéro de ligne standard
        if (parsed_instructions[i].id_instruction == target_id) {
            return i;
        }
        // Cas 2: C'est une ligne de type "label XXX"
        if (strcmp(parsed_instructions[i].mnemonic, "label") == 0 && parsed_instructions[i].arg != NULL) {
            if (atoi(parsed_instructions[i].arg) == target_id) {
                return i;
            }
        }
    }
    return num_instructions;
}
void load_map(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        fprintf(stderr, "Erreur: Impossible d'ouvrir le fichier généré %s\n", filename);
        exit(1);
    }
    
    char line[256];
    while (fgets(line, sizeof(line), f)) {
        if (line[0] == '\n' || line[0] == '#') continue;

        int line_num;
        char mnemonic[50], arg[200];
        arg[0] = '\0';
        if (sscanf(line, "%49s", mnemonic) == 1 && strcmp(mnemonic, ".global") == 0) {

        char *p = line;
        strtok(p, " "); // skip .global

        int i = 0;
        char *token = strtok(NULL, " \n");

        while (token != NULL) {
            global_consts[i++] = atoi(token);
            token = strtok(NULL, " \n");
        }

        continue; // 
    }
        // Lecture de la ligne : "num_ligne mnem [argument]"
        int n = sscanf(line, "%d %49s %199[^\n]", &line_num, mnemonic, arg);
        if (n < 2) continue;

        parsed_instructions[num_instructions].id_instruction = line_num;
        parsed_instructions[num_instructions].mnemonic = strdup(mnemonic);
        
        if (n >= 3) {
            parsed_instructions[num_instructions].arg = strdup(arg);
        } else {
            parsed_instructions[num_instructions].arg = NULL;
        }

        num_instructions++;
        if (num_instructions >= MAX_INSTRUCTIONS) break;
    }

    fclose(f);
}

void execute() {
    co = 0; // Commencer au premier élément du tableau (index 0)
    while (co < num_instructions) {
        char *mnem = parsed_instructions[co].mnemonic;
        char *arg = parsed_instructions[co].arg;

        if (strcmp(mnem, "ouverture-bloc") == 0) {
            ip = -1;
        }
        else if (strcmp(mnem, "fermeture-bloc") == 0) {
            break;
        }
        else if (strcmp(mnem, "reserver-kst") == 0) {
            n = atoi(arg);
            for (int i = 0; i < n; i++) {
             pile[i] = global_consts[i];
            }
            ip = n - 1;
        }
        else if (strcmp(mnem, "reserver-var") == 0) {
            n = atoi(arg);
            for (int i = ip + 1; i <= ip + n; i++) {
                pile[i] = 0;
            }
            ip += n;
        }
        else if (strcmp(mnem, "empiler-val") == 0) {
            push(atoi(arg));
        }
        else if (strcmp(mnem, "empiler-adr") == 0) {
            push(atoi(arg));
        }
        else if (strcmp(mnem, "valeur-pile") == 0) {
            int addr = pile[ip];

            if (addr < 0 || addr >= STACK_SIZE) {
                fprintf(stderr, "Erreur: adresse invalide %d\n", addr);
                exit(1);
            }

            pile[ip] = pile[addr];
        }
        else if (strcmp(mnem, "affect") == 0) {
            int val = pop();
            int addr = pop();
            pile[addr] = val;
        }
        else if (strcmp(mnem, "lire") == 0 || strcmp(mnem, "lireRC") == 0) {
            int addr = pop();
            int val;
            if (scanf("%d", &val) != 1) {
                fprintf(stderr, "Erreur de lecture d'un entier\n");
                exit(1);
            }
            pile[addr] = val;
        }
        else if (strcmp(mnem, "ecrire") == 0) {
            printf("%d", pop());
        }
        else if (strcmp(mnem, "ecrireRC") == 0) {
            printf("%d\n", pop());
        }
        else if (strcmp(mnem, "imprimer") == 0 || strcmp(mnem, "imprimerRC") == 0) {
            // Nettoyage sécurisé des quotes `'` entourant le texte
            char text[200] = {0};
            if (arg[0] == '\'') {
                strncpy(text, arg + 1, strlen(arg) - 2);
            } else {
                strcpy(text, arg);
            }
            if (strcmp(mnem, "imprimerRC") == 0) {
                printf("%s\n", text);
            } else {
                printf("%s", text);
            }
        }
        else if (strcmp(mnem, "plus") == 0) {
            int b = pop(); int a = pop(); push(a + b);
        }
        else if (strcmp(mnem, "moins") == 0) {
            int b = pop(); int a = pop(); push(a - b);
        }
        else if (strcmp(mnem, "mult") == 0) {
            int b = pop(); int a = pop(); push(a * b);
        }
        else if (strcmp(mnem, "div") == 0) {
            int b = pop(); int a = pop();
            if (b == 0) { fprintf(stderr, "Erreur: Division par zéro\n"); exit(1); }
            push(a / b);
        }
        else if (strcmp(mnem, "mod") == 0) {
            int b = pop(); int a = pop();
            if (b == 0) { fprintf(stderr, "Erreur: Modulo par zéro\n"); exit(1); }
            push(a % b);
        }
        else if (strcmp(mnem, "puiss") == 0) {
            int b = pop(); int a = pop(); push((int)pow(a, b));
        }
        else if (strcmp(mnem, "valabs") == 0) {
            int a = pop(); push(a >= 0 ? a : -a);
        }
        else if (strcmp(mnem, "neg") == 0) {
            int a = pop(); push(-a);
        }
        else if (strcmp(mnem, "egal") == 0) {
            int b = pop(); int a = pop(); push(a == b ? 1 : 0);
        }
        else if (strcmp(mnem, "dif") == 0) {
            int b = pop(); int a = pop(); push(a != b ? 1 : 0);
        }
        else if (strcmp(mnem, "pps") == 0) {
            int b = pop(); int a = pop(); push(a < b ? 1 : 0);
        }
        else if (strcmp(mnem, "pgs") == 0) {
            int b = pop(); int a = pop(); push(a > b ? 1 : 0);
        }
        else if (strcmp(mnem, "pp-egal") == 0) {
            int b = pop(); int a = pop(); push(a <= b ? 1 : 0);
        }
        else if (strcmp(mnem, "pg-egal") == 0) {
            int b = pop(); int a = pop(); push(a >= b ? 1 : 0);
        }
        else if (strcmp(mnem, "ou") == 0) {
            int b = pop(); int a = pop(); push(a || b ? 1 : 0);
        }
        else if (strcmp(mnem, "et") == 0) {
            int b = pop(); int a = pop(); push(a && b ? 1 : 0);
        }
        else if (strcmp(mnem, "non") == 0) {
            int a = pop(); push(a == 0 ? 1 : 0);
        }
        else if (strcmp(mnem, "bsf") == 0) {
            int target_label = atoi(arg);
            int cond = pop();

            if (cond == 0) {
                int idx = trouver_index_instruction(target_label);

                if (idx >= num_instructions) {
                    fprintf(stderr, "Erreur: label invalide %d\n", target_label);
                    exit(1);
                }

                co = idx;
                continue;
            }
        }
        else if (strcmp(mnem, "bsv") == 0) {
            int target_label = atoi(arg);
            int cond = pop();
            if (cond == 1) {
                co = trouver_index_instruction(target_label);
                continue;
            }
        }
        else if (strcmp(mnem, "bra") == 0) {
            int target_label = atoi(arg);

            int idx = trouver_index_instruction(target_label);

            if (idx >= num_instructions) {
                fprintf(stderr, "Erreur: bra vers label invalide %d\n", target_label);
                exit(1);
            }

            co = idx;
            continue;
        }
        /* ===== AJOUT DE LA GESTION DU LABEL ICI ===== */
        else if (strcmp(mnem, "label") == 0) {
            // On ne fait absolument rien à l'exécution !
            // C'est juste un marqueur de position. 
            // La VM passe tranquillement à l'instruction suivante.
        }
        /* ============================================ */
        else {
            fprintf(stderr, "Instruction VM inconnue: %s\n", mnem);
        }

        co++;
    }
}
int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <fichier.map>\n", argv[0]);
        return 1;
    }
    load_map(argv[1]);
    execute();
    return 0;
}