#include <stdio.h>
#include <stdlib.h>
#include "matiere.h"

int main()
{
    int optionMenuPrincipal;
    int optionSousMenuEtudiant, optionSousMenuMatiere, OptionSousMenuNote, optionSousMenuClasse;

    Menu_principal : printf(" 1. Gestion des Etudiant \n 2. Gestion des classes \n 3. Gestion des matieres \n 4. Gestion des notes\n 5. Quitter \n");
    printf("Veuillez choisir votre option du Menu Principal : ");
    scanf("%d", &optionMenuPrincipal);
    printf("\n");

    switch(optionMenuPrincipal)
    {
        case 1: printf("Gestion des Etudiants\n");
                // switch (optionSousMenuEtudiant)
                // {
                //     case 1:
                        
                //         break;
                //     case 2:
                        
                //         break;
                //     case 3:
                        
                //         break;
                //     case 4:
                        
                //         break;
                //     case 5:
                        
                //         break;
                    
                //     default:
                //         break;
                // }
                break;
        case 2: printf("Gestion des classes");
                // switch (optionSousMenuClasse)
                // {
                //     case 1:
                        
                //         break;
                //     case 2:
                        
                //         break;
                //     case 3:
                        
                //         break;
                //     case 4:
                        
                //         break;
                //     case 5:
                        
                //         break;
                    
                //     default:
                //         break;   
                // }
            break;
        case 3: printf("Gestion des matieres\n");
     
                    printf(" 1. Ajout matiere \n 2. Modification matiere \n 3. Recherche de matiere \n 4. Affichage des matieres \n 5. Suppression de matieres\n 6. Precedent \n 7. Quitter \n");
                    printf("Veuillez choisir votre option du sous menu matiere : ");
                    scanf("%d", &optionSousMenuMatiere);
                    switch(optionSousMenuMatiere)
                    {
                        case 1 : printf("Ajouter une matiere\n");
                                ajouter_matiere();
                            break;
                        case 2 : printf("Modifier une matiere\n");
                                //modifier_matiere();
                            break;
                        case 3 : printf("Recherche une matiere\n");
                                //rechercher_matiere();
                            break;
                        case 4 : printf("Afficher les matieres\n");
                                 afficher_matiere();
                            break;
                        case 5 : printf("Supprimer une matiere\n");
                                //supprimer_matiere();
                            break;
                        case 6 : goto Menu_principal;
                            break;
                        case 7 : exit(1);
                        default :  printf("Il faut choisir parmi les options!");
                            break;
                    }
            break;
        case 4: printf("Gestion des notes");
                // switch(OptionSousMenuNote)
                // {
                //     case 1:
                        
                //         break;
                //     case 2:
                        
                //         break;
                //     case 3:
                        
                //         break;
                //     case 4:
                        
                //         break;
                //     case 5:
                        
                //         break;
                    
                //     default:
                //         break;   
                // }   
                
            break;
        case 5: printf("Bye");
                return 0;
        default: printf("Veuillez choisir parmi les options");
    }
    return 0;
}