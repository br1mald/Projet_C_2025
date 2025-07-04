#include <stdio.h>
#include <stdlib.h>
#include "matiere.h"

int main()
{
    int option;

    printf(" 1. Gestion des Etudiant \n 2. Gestion des classes \n 3. Gestion des matieres \n 4. Gestion des notes\n");
    printf("Veuillez choisir votre option : ");
    scanf("%d", &option);
    printf("\n");

    switch(option){
        case 1: printf("Gestion des Etudiants");
            break;
        case 2: printf("Gestion des classes");
            break;
        case 3: printf("Gestion des matieres\n");
                ajout_matiere();
                affichage_matiere();
            break;
        case 4: printf("Gestion des notes");
            break;
        default: printf("Veuillez choisir parmi les options");
    }
    return 0;
}