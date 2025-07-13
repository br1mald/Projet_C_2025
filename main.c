#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gestion_notes/etre_note.h"
#include "gestion_etudiants/Etudiant.h"
#include "gestion_matiere/matiere.h"
#include "gestion_des_classes/gestion_classes.h"


int main()
{
    int optionMenuPrincipal;
    char choix;
    int optionSousMenuEtudiant, optionSousMenuMatiere, OptionSousMenuNote, optionSousMenuClasse;
    matiere matiere_ajouter;
    int size = 0;
    Classe classes[50];
    int choice, nombre;
    char continuer[5] = "oui";
    FILE *writer = fopen("classes.csv", "w");

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
            case 1: do{
        printf("\nGestion des Etudiants\n");
        printf("\t 1. Ajout Etudiant \n \t 2. Modification Etudiant \n \t 3. Recherche Etudiant \n \t 4. Affichage des Etudiants \n \t 5. Suppression Etudiant\n \t 6. Retour au menu principal\n");
        printf("\nVeuillez choisir votre option du Sous Menu Etudiant : ");
        scanf("%d", &optionSousMenuEtudiant);
        printf("\n");
        switch (optionSousMenuEtudiant)
        {
            case 1: printf("Ajouter un etudiant\n");
                    ajou_etudiant();
                break;
            case 2: printf("Modifier un etudiant\n");
                    modif_etudiant();
                break;
            case 3: printf("Rechercher un etudiant\n");
                    recherche_etudiant();
                break;
            case 4: printf("Affichage des etudiants\n");
                    liste_etudiant();
                break;
            case 5: printf("Supprimer un etudiant\n");
                    suppr_etudiant();
                break;
            // case 6: printf("Retour au menu principal\n");
            //         return 1; // Retourne au menu principal
            default: printf("Veuillez choisir parmi les options du sous menu Etudiant\n");
        }
    } while(optionSousMenuEtudiant != 6);

                    break;
            case 2: 
    while (strcmp(continuer, "non") != 0 && strcmp(continuer, "Non") != 0){
        printf("Voulez-vous: \n1. Ajouter une classe\n2. Supprimer une classe\n3. Modifier une classe\n4. Afficher la liste des classes\n5. Retourner au menu précédent\n");
        scanf("%d", &choice);
        switch (choice){
            case 1:
                printf("Veuillez saisir le nombre d'éléments à ajouter: \n");
                scanf("%d", &nombre);
                for (int i = 0; i < nombre; i++){
                    printf("Ajout de la classe numéro %d\n", i + 1);
                    add_class(classes, &size, 50);
                    if (size >= 50) {
                        printf("Impossible d'ajouter, le nombre de classe a atteint le maximum\n");
                        break;
                    }
                    write_to_file(classes, &size);
                }
                break;
            case 2:
                printf("Combien de classes souhaitez-vous supprimer?\n");
                scanf("%d", &nombre);
                for (int i = 0; i < nombre; i++) remove_class(classes, &size);
                actualize(classes, &size);
                break;
            case 3:
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
                printf("Retour au menu précédent"); //Ajouter plus tard
            default:
                printf("Veuillez entrer le numéro de l'opération à réaliser\n");
        }
    printf("Souhaitez vous continuer?\n");
    scanf("%s", continuer);
    }

    for (int i = 0; i < size; i++){
        printf("%s\n", classes[i].nom);
    }
                break;
            case 3: 
    do 
    {
        printf("  \n\nGestion des matieres\n");
        printf(" \t 1. Ajout matiere \n\t 2. Modification matiere \n\t 3. Recherche de matiere \n\t 4. Affichage des matieres \n\t 5. Suppression de matieres\n\t 6. Precedent \n\t 7. Quitter \n");
        printf("\nVeuillez choisir votre option du sous menu matiere : ");
        scanf("%d", &optionSousMenuMatiere);
        switch(optionSousMenuMatiere)
        {
            case 1: printf("Ajouter une matiere\n");
                    ajouter_matiere();
                break;
            case 2: printf("Modifier une matiere\n");
                    modifier_matiere();
                break;
            case 3 : printf("Recherche une matiere\n");
                    int reference;
                    printf("Donnez la reference de la matiere a rechercher : ");
                    scanf("%d", &reference);
                    if(rechercher_matiere(reference))
                        printf(" Reference : %d \n Libelle : %s \n Coefficient : %d", matiere_ajouter.coefficient, matiere_ajouter.libelle, matiere_ajouter.reference);
                    else
                        printf("L'element est absent dans la liste des matieres.\n");
                break;
            case 4: printf("Voici la liste des matieres\n");
                    afficher_matiere();
                break;
            case 5: printf("Supprimer une matiere\n");
                    supprimer_matiere();
                break;
            case 6: return 0;
                 break;
            case 7: exit(1);
                break;
            default :  printf("Il faut choisir parmi les options!");
        }
    }while (optionSousMenuMatiere != 7);
                break;
            case 4:  
                    do{ 
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
            ajouter_note_etudiant_matiere();
            break;
        case 2: 
            ajouter_note_etudiant_toutes_matieres();
            break;
        case 3: 
            ajouter_note_classe_matiere();
            break;
        case 4: 
            modifier_note();
            break;
        case 5: 
            supprimer_note();
            break;
        case 6: 
            afficher_note_etudiant_matiere();
            break;
        case 7: 
            afficher_note_etudiant_toutes_matieres();
            break;
        case 8: 
            afficher_note_classe_matiere();
            break;
        // case 9: return 0;
        //     break;
        default: 
            printf("Option invalide!\n");
    }
    }while (OptionSousMenuNote != 7);
   
                break;
            case 5: printf("A la prochaine fois\n");
                    return 0;
            default: printf("Veuillez choisir parmi les options");
        }
        
    }while(optionMenuPrincipal != 5);
    
    return 0;

}