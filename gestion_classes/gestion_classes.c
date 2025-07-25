#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "se_faire.h"

int gestion_classes(){

    Se_faire tab_associations[255];
    int se_faire_size = 0;
    int size = 0;
    Classe classes[50];
    int choice, nombre, target, pos, code, reference;
    char continuer[5] = "oui", level[10];
    int buffer_code;
    char buffer_nom[15], buffer_niveau[15];

    FILE *writer = fopen("gestion_classes/classes.csv", "a");
    FILE *se_faire = fopen("gestion_classes/se_faire.csv", "a");

    initialize_classes(classes, &size);
    initialize_se_faire(tab_associations, &se_faire_size);

    while (strcmp(continuer, "non") != 0 && strcmp(continuer, "Non") != 0){
        printf("Gestion des classes \n\t1. Ajouter une classe\n\t2. Supprimer une classe\n\t3. Modifier une classe\n\t4. Afficher la liste des classes\n\t5. Afficher les informations d'une classe\n\t6. Associer une classe à une matière\n\t7. Dissocier une classe et une matière\n\t8. Afficher la liste des matières enseignées dans une classe\n\t9. Retourner au menu précédent\t10. Quitter\n");
        scanf("%d", &choice);
        switch (choice){
            case 1:
                if (size == 50) {
                    printf("Maximum de classes atteint\n");
                    break;
                }
                printf("Menu d'ajout de classes\n");
                printf("Veuillez saisir le nombre d'éléments à ajouter: \n");
                scanf("%d", &nombre);
                for (int i = 0; i < nombre; i++){
                    if ((size + nombre) > 50) {
                        printf("Impossible d'ajouter, le nombre de classes a atteint le maximum\n");
                        break;
                    }
                    printf("Ajout de la classe numéro %d\n", i + 1);
                    add_class(classes, &size, 50);
                }
                break;
            case 2:
                if (size == 0) {
                    printf("Aucune classe n'est disponible.\n");
                    break;
                }
                printf("Menu de suppression de classes\n");
                printf("Combien de classes souhaitez-vous supprimer?\n");
                scanf("%d", &nombre);
                if ((size - nombre) < 0) {
                    printf("Le nombre de classes enregistrées est inférieur à ce nombre.\n");
                    break;
                }
                for (int i = 0; i < nombre; i++) remove_class(classes, &size);
                actualize(classes, &size);
                break;
            case 3:
                if (size == 0) {
                    printf("Aucune classe n'est disponible.\n");
                    break;
                }
                printf("Menu de modification de classes\n");
                printf("Combien de classes souhaitez-vous modifier?\n");
                scanf("%d", &nombre);
                for (int i = 0; i < nombre; i++) modify_class(classes, &size);
                actualize(classes, &size);
                break;
            case 4:
                if (size > 0){
                    printf("=== Liste des classes ===\n");

                    printf("+------+------------+-------------+\n");
                    printf("| Code |     Nom    |   Niveau    |\n");
                    printf("+------+------------+-------------+\n");

                    FILE *reader = fopen("gestion_classes/classes.csv", "r");
                    char buffer[255];
                    for (int i = 0; i < size; i++){
                        fgets(buffer, 255, reader);
                        int line = sscanf(buffer, "%d,%[^,],%[^\n]", &buffer_code, buffer_nom, buffer_niveau);
                        printf("| %4d | %10s | %11s |\n", buffer_code, buffer_nom, buffer_niveau);
                    }

                    printf("+------+------------+-------------+\n");

                } else printf("Aucune classe à afficher.\n");
                break;
            case 5:
                if (size == 0) {
                    printf("Aucune classe n'est disponible.\n");
                    break;
                }
                printf("Menu d'information sur une classe\n");
                printf("Veuillez saisir le code de la classe dont vous souhaitez connaître les informations\n");
                scanf("%d", &target);
                pos = search(classes, target, size);
                if (pos != -1) {
                    printf(" === Informations sur la classe de code %d ===\n", target);
                    if (classes[pos].niveau == Licence) strcpy(level, "Licence");
                    else if (classes[pos].niveau == Master) strcpy(level, "Master");
                    printf("+----------+--------+----------+\n");
                    printf("|    Nom   |  Code  |  Niveau  |\n");
                    printf("+----------+--------+----------+\n");
                    printf("|  %7s |  %3d   | %7s  |\n", classes[pos].nom, classes[pos].code, level);
                    printf("+----------+--------+----------+\n");
                } else printf("Classe inexistante.\n");
                break;
            case 6:
                printf("Menu d'association de classe-matière\n");
                printf("Veuillez saisir le code de la classe à associer: \n");
                scanf("%d", &code);
                printf("Veuillez saisir la référence de la matière à associer: \n");
                scanf("%d", &reference);
                associer_matiere_classe(code, reference, classes, &size, tab_associations, &se_faire_size); // Fonction se trouve dans relations.c
                break;
            case 7:
                printf("Menu de dissociation de classe-matière\n");
                printf("Veuillez saisir le code de la classe à dissocier: \n");
                scanf("%d", &code);
                printf("Veuillez saisir la référence de la matière à dissocier: \n");
                scanf("%d", &reference);
                dissocier_matiere_classe(code, reference); // Fonction se trouve dans relations.c
                break;
            case 8:
                printf("Veuillez saisir le code de la classe dont vous souhaitez consulter les matières: \n");
                scanf("%d", &code);
                pos = search(classes, code, size);
                if (pos != -1) {
                    printf("=== Liste des matières de la classe %s === \n", classes[pos].nom);
                    afficher_matieres_classe(code);
                } else printf("Classe inexistance.\n");
                break;
            case 9:
                printf("Retour au menu principal\t");
                return 1;
            case 10:
                printf("Au revoir!\n");
                exit(0);
            default:
                printf("Veuillez entrer le numéro de l'opération à réaliser\n");
        }
    printf("Souhaitez vous continuer dans le sous-menu Gestion des classes?\n");
    scanf("%s", continuer);
    }
    fclose(writer);
    fclose(se_faire);
    return 1;
}

void add_class(Classe classes[], int *size, int max_capacity){
    int level = 0;
    int code;

    if (*size >= max_capacity) printf("Nombre maximum de classes atteint.\n");
    else{
        printf("Veuillez saisir le code de la classe à ajouter (max 10 caractères)\n");
        scanf("%d", &code);
        if (search(classes, code, *size) == -1) {
            classes[*size].code = code;
            printf("Veuillez saisir son nom (max 25 caractères)\n");
            scanf("%s", classes[*size].nom);
            while (level != 1 && level != 2){
                printf("Veuillez saisir le niveau de cette classe: 1 pour Licence ou 2 pour Master\n");
                scanf("%d", &level);
                switch (level){
                    case 1:
                        classes[*size].niveau = Licence;
                        break;
                    case 2:
                        classes[*size].niveau = Master;
                        break;
                    default:
                        printf("Invalide.\n");
                }
            }
            (*size)++;
            write_to_file(classes, &(*size));
        } else printf("Cette classe existe déjà.\n");
    }
}

void remove_class(Classe classes[], int *size){
    int pos, target;

    if (*size == 0) printf("Aucune classe à supprimer\n");
    else {
        printf("Veuillez saisir le code de la classe à supprimer\n");
        scanf("%d", &target);
        pos = search(classes, target, *size);
        if (pos == -1) printf("Classe inexistante.\n");
        else {
            printf("Classe %s supprimée.\n", classes[pos].nom);
            for (int i = pos; i < *size - 1; i++) classes[i] = classes[i + 1];
            (*size)--;
        }
    }
}

void modify_class(Classe classes[], int *size){
    char continuer[5] = "oui";
    int pos, mod, level = 0, target;

    if (*size == 0) printf("Aucune classe à modifier\n");
    else {
        printf("Veuillez saisir le code de la classe à modifier\n");
        scanf("%d", &target);
        pos = search(classes, target, *size);
        if (pos == -1) printf("Classe inexistante.\n");
        else {
            while (strcmp(continuer, "non") != 0 && strcmp(continuer, "Non") != 0){
                printf("Que souhaitez-vous modifier?\n1. Code\n2. Nom\n3. Niveau\n");
                scanf("%d", &mod);

                switch(mod){
                    case 1:
                        printf("Veuillez saisir le nouveau code (max 10 caractères)\n");
                        scanf("%d", &classes[pos].code);
                        printf("Le code a été modifié avec succès.\n");
                        break;
                    case 2:
                        printf("Veuillez saisir le nouveau nom (max 25 caractères)\n");
                        scanf("%s", classes[pos].nom);
                        printf("Le nom a été modifié avec succès\n");
                        break;
                    case 3:
                        while (level != 1 && level != 2) {
                            printf("Veuillez saisir %d pour Licence ou %d pour Master\n", Licence, Master);
                            scanf("%d", &level);
                            switch(level){
                                case 1:
                                    classes[pos].niveau = Licence;
                                    break;
                                case 2:
                                    classes[pos].niveau = Master;
                                    break;
                                default:
                                    printf("Invalide.\n");
                            }
                        }
                        printf("Le niveau a été modifié avec succès.\n");
                        break;
                }
                printf("Souhaitez-vous continuer à modifier la classe %s?\n", classes[pos].nom);
                scanf("%s", continuer);
            }
        }
    }
}

int search(Classe tab[], int target, int size){
    for (int i = 0; i < size; i++){
        if (tab[i].code == target) return i;
    }
    return -1;
}

void write_to_file(Classe classes[], int *size){
    FILE *writer = fopen("gestion_classes/classes.csv", "a");
    char level[10];
    if (classes[*size - 1].niveau == Licence) strcpy(level, "Licence");
    else if (classes[*size - 1]. niveau == Master) strcpy(level, "Master");
    fprintf(writer, "%d,%s,%s\n", classes[*size - 1].code, classes[*size - 1].nom, level);
    fclose(writer);
}

void actualize(Classe classes[], int *size){
    FILE *writer = fopen("gestion_classes/classes.csv", "w");
    char level[10];
    for (int i = 0; i < *size; i++){
        if (classes[i].niveau == Licence) strcpy(level, "Licence");
        else if (classes[i]. niveau == Master) strcpy(level, "Master");
        fprintf(writer, "%d,%s,%s\n", classes[i].code, classes[i].nom, level);
    }
    fclose(writer);
}

void initialize_classes(Classe classes[], int *size){
    FILE *reader = fopen("gestion_classes/classes.csv", "r");
    char buffer[50],level[10];
    while (fgets(buffer, sizeof(buffer), reader) != NULL) {
        int line = sscanf(buffer, "%d,%29[^,],%9[^\n]", &classes[*size].code, classes[*size].nom, level);
        if (strcmp(level, "Licence") == 0) classes[*size].niveau = Licence;
        else if (strcmp(level, "Master") == 0) classes[*size].niveau = Master;
        (*size)++;
    }
}
