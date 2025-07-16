#include <stdio.h>
#include "relations.h"

void associer_matiere_classe(int class_code, int mat_reference, Classe classes[], int *size, Se_faire tab[], int *Se_faire_size) {
    if (rechercher_association(class_code, mat_reference) == 1) {
        printf("Matière et classe déjà associées.\n");
    } else if (search(classes, class_code, *size) != -1 && rechercher_matiere(mat_reference) == 1) {
        tab[*Se_faire_size].code = class_code;
        tab[*Se_faire_size].reference = mat_reference;
        FILE *writer = fopen("gestion_des_classes/Se_faire.csv", "a");
        fprintf(writer, "%d,%d\n", tab[*Se_faire_size].code, tab[*Se_faire_size].reference);
        fclose(writer);
        printf("Opération réussie.\n");
        (*Se_faire_size)++;
    } else printf("Matière ou classe inexistante. Veuillez vérifier puis réessayer.\n");
}

int rechercher_association(int target_classe, int target_matiere) {
    int classe, matiere;
    FILE *reader = fopen("gestion_des_classes/Se_faire.csv", "r");
    char buffer[50];
    while (fgets(buffer, sizeof(buffer), reader) != NULL) {
        int line = sscanf(buffer, "%d, %d", &classe, &matiere);
        if (classe == target_classe && matiere == target_matiere) return 1;
    }
    return 0;
}

void initialize_Se_faire(Se_faire tab[], int *Se_faire_size) {
    FILE *reader = fopen("gestion_des_classes/Se_faire.csv", "r");
    char buffer[50],level[10];
    while (fgets(buffer, sizeof(buffer), reader) != NULL) {
        int line = sscanf(buffer, "%d,%d", &tab[*Se_faire_size].code, &tab[*Se_faire_size].reference);
        (*Se_faire_size)++;
    }
}

void dissocier_matiere_classe(int target_classe, int target_matiere) {
    FILE *og_file = fopen("gestion_des_classes/Se_faire.csv", "r");
    FILE *new_file = fopen("gestion_des_classes/temp.csv", "w");
    int classe_code, matiere_ref;
    char buffer[50];
    const char *new_name = "gestion_des_classes/Se_faire.csv";
    while (fgets(buffer, sizeof(buffer), og_file) != NULL) {
        int line = sscanf(buffer, "%d,%d", &classe_code, &matiere_ref);
        if (classe_code != target_classe || matiere_ref != target_matiere) {
            fprintf(new_file, "%d,%d\n", classe_code, matiere_ref);
        }
    }
    fclose(og_file);
    fclose(new_file);
    remove("gestion_des_classes/Se_faire.csv");
    rename("gestion_des_classes/temp.csv", new_name);
}
