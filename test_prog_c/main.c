#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gestion_notes/etre_note.h"
#include "gestion_etudiants/Etudiant.h"
#include "gestion_matiere/matiere.h"
#include "gestion_classes/gestion_classes.h"


int main()
{
    int optionMenuPrincipal, returnValue;
    char choix;
    int optionSousMenuEtudiant, optionSousMenuMatiere, OptionSousMenuNote, optionSousMenuClasse;
    matiere matiere_ajouter;
    int size = 0;
    Classe classes[50];
    int choice, nombre;
    char continuer[5] = "oui";
    FILE *writer = fopen("gestion_des_classes/classes.csv", "w");

    while(strcmp(continuer, "non") != 0 && strcmp(continuer, "Non") != 0)
    {
        princ_menu: printf("\n\n \tBienvenue dans notre programme");
        printf("\n\n******************************Menu*********************************************\n\n");
        printf(" 1. Gestion des Etudiant \n 2. Gestion des classes \n 3. Gestion des matieres \n 4. Gestion des notes\n 5. Quitter \n");
        printf("\nVeuillez choisir votre option du Menu Principal : ");
        scanf("%d", &optionMenuPrincipal);
        printf("\n");

        switch(optionMenuPrincipal)
        {
            case 1:
                while (strcmp(continuer, "non") != 0 && strcmp(continuer, "Non") != 0){
                    returnValue = sous_menu_etudiant();
                    if (returnValue == 1) {
                        goto princ_menu ; // Retourne au menu principal
                    }else if (returnValue == 0){
                        exit(0);
                    }else{
                        printf("Souhaitez-vous continuer dans le sous-menu Etudiant? (oui/non): ");
                        scanf("%s", continuer);
                    }
                } break;
            case 2:
                returnValue = gestion_classes();
                if (returnValue == 1) {
                        goto princ_menu ; // Retourne au menu principal
                    }else{
                        exit(0);
                    }
                break;
            case 3:
                while(strcmp(continuer, "non") != 0 && strcmp(continuer, "Non") != 0){
                    returnValue = gestion_matiere();
                    if (returnValue == 1) {
                            goto princ_menu ; // Retourne au menu principal
                        }else if (returnValue == 0){
                            exit(0);
                        }else{
                            printf("Souhaitez-vous continuer dans le sous-menu Matiere? (oui/non): ");
                            scanf("%s", continuer);
                        }
                    }
                break;
            case 4:
                while(strcmp(continuer, "non") != 0 && strcmp(continuer, "Non") != 0){
                    returnValue = gestion_notes();
                    if (returnValue == 1) {
                            goto princ_menu ; // Retourne au menu principal
                        }else if (returnValue == 0){
                            exit(0);
                        }else{
                            printf("Souhaitez-vous continuer dans le sous-menu Notes? (oui/non): ");
                            scanf("%s", continuer);
                        }
                }
                break;
            case 5: printf("A la prochaine fois\n");
                exit(0);
            default: printf("Veuillez choisir parmi les options du menu principal\n");
                goto princ_menu;
        }
        printf("\nSouhaitez-vous continuer dans le menu principal? (oui/non): ");
        scanf("%s", continuer);
    }
    fclose(writer);
    return 0;
}
