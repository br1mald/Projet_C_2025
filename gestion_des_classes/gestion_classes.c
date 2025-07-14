#include <stdio.h>
#include <string.h>
#include "gestion_classes.h"

void gestionclasses(){

    int size = 0;
    Classe classes[50];
    int choice, nombre, target, pos;
    char continuer[5] = "oui", level[10];

    FILE *writer = fopen("classes.csv", "w");

    while (strcmp(continuer, "non") != 0 && strcmp(continuer, "Non") != 0){
        printf("Voulez-vous: \n1. Ajouter une classe\n2. Supprimer une classe\n3. Modifier une classe\n4. Afficher la liste des classes\n5. Afficher les informations d'une classe\n6. Retourner au menu précédent\n");
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
                    write_to_file(classes, &size);
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
                // if ((size - nombre) < 0) {
                //     printf("Le nombre de classes enregistrées est inférieur à ce nombre.\n");
                //     break;
                // }
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
                    printf("Affichage des classes\n");
                    FILE *reader = fopen("classes.csv", "r");
                    char buffer[255];
                    for (int i = 0; i < size; i++){
                        fgets(buffer, 255, reader);
                        printf("%s", buffer);
                    }
                } else printf("Aucune classe à afficher\n");
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
                if (classes[pos].niveau == Licence) strcpy(level, "Licence");
                else if (classes[pos].niveau == Master) strcpy(level, "Master");
                printf("Nom de la classe: %s, Code: %d, Niveau: %s\n", classes[pos].nom, classes[pos].code, level);
                break;
            case 6:
                printf("Retour au menu précédent\n"); //Ajouter plus tard
                break;
            default:
                printf("Veuillez entrer le numéro de l'opération à réaliser\n");
        }
    printf("Souhaitez vous continuer?\n");
    scanf("%s", continuer);
    }
}

void add_class(Classe classes[], int *size, int max_capacity){
    int level = 0;

    if (*size >= max_capacity) printf("Nombre maximum de classes atteint.\n");
    else{
        printf("Veuillez saisir le nom de la classe à ajouter (max 25 caractères)\n");
        scanf("%s", classes[*size].nom);
        printf("Veuillez saisir son code (max 10 caractères)\n");
        scanf("%d", &classes[*size].code);
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
    }
}

void remove_class(Classe classes[], int *size){
    int pos, target;

    if (*size == 0) printf("Aucune classe à supprimer\n");
    else {
        printf("Veuillez saisir le code de la classe à supprimer\n");
        scanf("%d", &target);
        pos = search(classes, target, *size);
        if (pos == -1) printf("Classe introuvable\n");
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
        if (pos == -1) printf("Classe introuvable\n");
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
    FILE *writer = fopen("classes.csv", "a");
    char level[10];
    if (classes[*size - 1].niveau == Licence) strcpy(level, "Licence");
    else if (classes[*size - 1]. niveau == Master) strcpy(level, "Master");
    fprintf(writer, "%d,%s,%s\n", classes[*size - 1].code, classes[*size - 1].nom, level);
    fclose(writer);
}

void actualize(Classe classes[], int *size){
    FILE *writer = fopen("classes.csv", "w");
    char level[10];
    for (int i = 0; i < *size; i++){
        if (classes[i].niveau == Licence) strcpy(level, "Licence");
        else if (classes[i]. niveau == Master) strcpy(level, "Master");
        fprintf(writer, "%d,%s,%s\n", classes[i].code, classes[i].nom, level);
    }
    fclose(writer);
}
