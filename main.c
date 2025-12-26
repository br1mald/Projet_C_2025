#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gestion_notes/etre_note.h"
#include "gestion_etudiants/Etudiant.h"
#include "gestion_matiere/matiere.h"
#include "gestion_classes/gestion_classes.h"//commentaire


int main()
{
    int optionMenuPrincipal;
    char continuer[5] = "oui";

    while(strcmp(continuer, "non") != 0 && strcmp(continuer, "Non") != 0)
    {
        princ_menu: printf("\n\n \t\tBienvenue dans notre programme");
        printf("\n\n******************************Menu*********************************************\n\n");
        printf(" 1. Gestion des étudiants \n 2. Gestion des classes \n 3. Gestion des matières \n 4. Gestion des notes\n 5. Quitter \n");
        printf("\nVeuillez choisir votre option du Menu Principal : ");
        scanf("%d", &optionMenuPrincipal);
        printf("\n");

        switch(optionMenuPrincipal)
        {
            case 1:
                gestion_etudiants();
                goto princ_menu ; // Retourne au menu principal
                break;
            case 2:
                gestion_classes();
                goto princ_menu ; // Retourne au menu principal
                break;
            case 3:
                gestion_matiere();
                goto princ_menu ; // Retourne au menu principal
                break;
            case 4:
                gestion_notes();
                goto princ_menu ; // Retourne au menu principal
                break;
            case 5: printf("A la prochaine fois\n");
                exit(0);
            default: printf("Veuillez choisir parmi les options du menu principal\n");
                goto princ_menu;
        }
        printf("\nSouhaitez-vous continuer dans le menu principal? (oui/non): ");
        scanf("%s", continuer);
    }
    return 0;
}
