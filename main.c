#include <stdio.h>
#include <stdlib.h>
#include "matiere.h"
#include "etre_note.h"
int main()
{
    int optionMenuPrincipal;
    int optionSousMenuEtudiant, optionSousMenuMatiere, OptionSousMenuNote, optionSousMenuClasse;

    printf(" 1. Gestion des Etudiant \n 2. Gestion des classes \n 3. Gestion des matieres \n 4. Gestion des notes\n 5. Quitter \n");
    printf("Veuillez choisir votre option du Menu Principal : ");
    scanf("%d", &optionMenuPrincipal);
    printf("\n");

    switch(optionMenuPrincipal)
    {
        case 1: printf("Gestion des Etudiants\n");
                switch (optionSousMenuEtudiant)
                {
                    case 1:
                        
                        break;
                    case 2:
                        
                        break;
                    case 3:
                        
                        break;
                    case 4:
                        
                        break;
                    case 5:
                        
                        break;
                    
                    default:
                        break;
                }
                break;
        case 2: printf("Gestion des classes");
                switch (optionSousMenuClasse)
                {
                    case 1:
                        
                        break;
                    case 2:
                        
                        break;
                    case 3:
                        
                        break;
                    case 4:
                        
                        break;
                    case 5:
                        
                        break;
                    
                    default:
                        break;   
                }
            break;
        case 3: printf("Gestion des matieres\n");
                printf(" 1. Ajout matiere \n 2. Modification matiere \n 3. Recherche de matiere \n 4. Affichage des matieres \n 5. Suppression de matieres");
                switch(optionSousMenuMatiere)
                {
                    case 1 : printf("Ajouter une matiere");
                             ajout_matiere();
                        break;
                    case 2 : printf("Modifier une matiere");
                             modification_matiere();
                        break;
                    case 3 : printf("Recherche une matiere");
                             recherche_matiere();
                        break;
                    case 4 : printf("Afficher des matieres");
                             affichage_matiere();
                        break;
                    case 5 : printf("Supprimer une matiere");
                             supprimer_matiere();
                        break;
                    default : 
                        break;
                }
               
            break;
        case 4: 
    printf("Gestion des notes\n");
    printf("1. Ajout des notes d’un étudiant dans une matière\n");
    printf("2. Ajout des notes d’un étudiant dans toutes ses matières\n");
    printf("3. Ajout des notes d’une classe dans une matière\n");
    printf("4. modifier des notes\n");
    printf("5. supprimer des notes\n");
    printf("6. Afficher les notes de l’étudiant dans une matière donnée\n");
    printf("7. Afficher les notes de l’étudiant dans toutes ses matières (les matières de sa classe)\n");
    printf("8.Afficher les notes d’une classe dans une matière donnée\n");
    printf("9. Retour\n");
    printf("Veuillez choisir votre option : ");
    scanf("%d", &OptionSousMenuNote);
    
    switch(OptionSousMenuNote)
    {
        case 1: 
            ajouter_etre_note_etudiant_matiere();
            break;
        case 2: 
            ajouter_etre_note_etudiant_toutes_matieres();
            break;
        case 3: 
            ajouter_etre_note_classe_matiere();
            break;
        case 4: 
            modifier_etre_note();
            break;
        case 5: 
            supprimer_etre_note();
            break;
        case 6: 
            afficher_etre_note_etudiant_matiere();
            break;
        case 7: 
            afficher_etre_note_etudiant_toutes_matieres();
            break;
        case 8: 
            afficher_etre_note_classe_matiere();
            break;
        case 9:
            break;
        default: 
            printf("Option invalide!\n");
    }
    break;

        case 5: printf("Bye");
                return 0;
        default: printf("Veuillez choisir parmi les options");
    }
    return 0;
}