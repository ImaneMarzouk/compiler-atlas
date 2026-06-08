#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>


extern int yyparse();
extern FILE *yyin;
extern FILE *output_file; // Récupération du pointeur de fichier défini dans atlas.y

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <fichier.atlas>\n", argv[0]);
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    if (!input) {
        fprintf(stderr, "Erreur: Impossible d'ouvrir %s\n", argv[1]);
        return 1;
    }

    // Définition et construction du nom de fichier de sortie .map
    char map_filename[256];
    strcpy(map_filename, argv[1]);
    char *dot = strrchr(map_filename, '.');
    if (dot) *dot = '\0';
    strcat(map_filename, ".map");

    // Ouvrir le fichier de sortie .map pour Bison/atlas.y
    output_file = fopen(map_filename, "w");
    if (!output_file) {
        fprintf(stderr, "Erreur: Impossible de créer %s\n", map_filename);
        fclose(input);
        return 1;
    }

    yyin = input;

    printf("=== Compilation de %s ===\n", argv[1]);
    if (yyparse() != 0) {
        fprintf(stderr, "Erreur: Compilation échouée\n");
        fclose(input);
        fclose(output_file);
        return 1;
    }

    fclose(input);
    fclose(output_file); // Finalisation de l'écriture sémantique

    printf("\n=== Code MAP généré (%s) ===\n", map_filename);
    FILE *map_file = fopen(map_filename, "r");
    if (map_file) {
        char line[256];
        while (fgets(line, sizeof(line), map_file)) {
            printf("%s", line);
        }
        fclose(map_file);
    }

    printf("\n=== Exécution automatique par la VM ===\n");
   printf("\n=== Exécution du simulateur ===\n");
printf("Lance manuellement : ./simulateur %s\n", map_filename);

    return 0;
}