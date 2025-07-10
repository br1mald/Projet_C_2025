#include <stdio.h>
#include <stdlib.h>
#include "matiere.h"

int main()
{
    int optionMenuPrincipal;
    char choix;
    int optionSousMenuEtudiant, optionSousMenuMatiere, OptionSousMenuNote, optionSousMenuClasse;

    do
    { 
        printf("\n\n \tBienvenue dans notre programme");
        printf("\n\n******************************Menu*********************************************\n\n");
        printf(" 1. Gestion des Etudiant \n 2. Gestion des classes \n 3. Gestion des matieres \n 4. Gestion des notes\n 5. Quitter \n");
        printf("\nVeuillez choisir votre option du Menu Principal : ");
        scanf("%d", &optionMenuPrincipal);
        printf("\n");

        switch(optionMenuPrincipal)
        {
            case 1: printf("Gestion des Etudiants\n");
                    break;
            case 2: printf("Gestion des classes");
                break;
            case 3: menu_matiere();
                break;
            case 4: printf("Gestion des notes");
                break;
            case 5: printf("A la prochaine fois");
                    return 0;
            default: printf("Veuillez choisir parmi les options");
        }
        
    }while(optionMenuPrincipal != 5);
    
    return 0;

}