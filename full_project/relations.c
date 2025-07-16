#include <stdio.h>
#include "relations.h"
#include "gestion_matiere/matiere.h"

void associer_matiere_classe(int class_code, int mat_reference, Classe classes[], int *size, Se_faire tab[], int *se_faire_size) {
    if (rechercher_association(class_code, mat_reference) == 1) {
        printf("Matière et classe déjà associées.\n");
    } else if (search(classes, class_code, *size) != -1 && rechercher_matiere(mat_reference) == 1) {
        tab[*se_faire_size].code = class_code;
        tab[*se_faire_size].reference = mat_reference;

        FILE *writer = fopen("gestion_classes/se_faire.csv", "a");
        fprintf(writer, "%d,%d\n", tab[*se_faire_size].code, tab[*se_faire_size].reference);
        fclose(writer);

        printf("Opération réussie.\n");
        (*se_faire_size)++;
    } else printf("Matière ou classe inexistante. Veuillez vérifier puis réessayer.\n");
}

int rechercher_association(int target_classe, int target_matiere) {
    int classe, matiere;
    FILE *reader = fopen("gestion_classes/se_faire.csv", "r");
    char buffer[50];
    while (fgets(buffer, sizeof(buffer), reader) != NULL) {
        int line = sscanf(buffer, "%d, %d", &classe, &matiere);
        if (classe == target_classe && matiere == target_matiere) return 1;
    }
    return 0;
}

void initialize_se_faire(Se_faire tab[], int *se_faire_size) {
    FILE *reader = fopen("gestion_classes/se_faire.csv", "r");
    char buffer[50],level[10];
    while (fgets(buffer, sizeof(buffer), reader) != NULL) {
        int line = sscanf(buffer, "%d,%d", &tab[*se_faire_size].code, &tab[*se_faire_size].reference);
        (*se_faire_size)++;
    }
}

void dissocier_matiere_classe(int target_classe, int target_matiere) {
    FILE *og_file = fopen("gestion_classes/se_faire.csv", "r");
    FILE *new_file = fopen("gestion_classes/temp.csv", "w");

    int classe_code, matiere_ref;
    char buffer[50];
    const char *new_name = "gestion_classes/se_faire.csv";

    while (fgets(buffer, sizeof(buffer), og_file) != NULL) {
        int line = sscanf(buffer, "%d,%d", &classe_code, &matiere_ref);
        if (classe_code != target_classe || matiere_ref != target_matiere) {
            fprintf(new_file, "%d,%d\n", classe_code, matiere_ref);
        }
    }
    fclose(og_file);
    fclose(new_file);

    remove("gestion_classes/se_faire.csv");
    rename("gestion_classes/temp.csv", new_name);
}

void afficher_matieres_classe(int class_code) {
    FILE *matieres = fopen("gestion_matiere/matiere.csv", "r");
    FILE *associations = fopen("gestion_classes/se_faire.csv", "r");

    char mat_buffer[50], asso_buffer[50], mat_name[15];
    int code, file_ref, ref;

    while (fgets(asso_buffer, sizeof(asso_buffer), associations) != NULL) {
        int line = sscanf(asso_buffer, "%d,%d", &code, &ref);
        rewind(matieres);
        if (code == class_code) {
            while (fgets(mat_buffer, sizeof(mat_buffer), matieres) != NULL) {
                int row = sscanf(mat_buffer, "%d %s", &file_ref, mat_name);
                if (file_ref == ref) printf("%s\n", mat_name);
            }
        }
    }

    fclose(associations);
    fclose(matieres);
}
