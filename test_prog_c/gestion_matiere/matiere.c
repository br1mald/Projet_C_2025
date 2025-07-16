#include <stdio.h>
#include <stdlib.h>
#include "matiere.h"
#include "../gestion_des_classes/gestion_classes.h"



matiere matiere_ajouter;


int gestion_matiere()
{
    int optionSousMenuMatiere;

    do 
    {
        matiere_menu: printf("  \n\nGestion des matieres\n");
        printf(" \t 1. Ajout matiere \n\t 2. Modification matiere \n\t 3. Recherche de matiere \n\t 4. Affichage des matieres \n\t 5. Suppression de matieres\n\t 6. Association de classe et matiere \n\t 7. Precedent \n\t 8. Quitter \n");
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
            case 6: printf("\n\t 1. Associer une classe a une matiere \n\t 2. Dissocier une classe a une matiere \n\t 3. Afficher les association entre classe et matiere \n\t 4. Retour au menu principal \n\t 5. Retour au menu matiere \n\t Quitter\n");
                    int option;
                    printf("\nVeuillez choisir votre option du sous menu Association de classe et matiere : ");
                    scanf("%d", &option);
                    switch (option)
                    {
                    case 1: printf("1. Associer une classe a une matiere\n");
                            associer_matiere_classe();    
                        break;
                    case 2: printf("2. Dissocier une classe a une matiere\n");
                            dissocier_matiere_classe();
                        break;
                    case 3: printf("3. Afficher les association entre classe et matiere\n");
                            afficher_matiere_classe();
                        break;
                    case 4: return 1;
                    case 5: break;
                    case 6: exit(1);
                    default:printf("Choisis parmi les options\n");
                        break;
                    }
                break;
            case 7: return 1;
                break;
            case 8: return 0;
                break;
            default :  printf("Veuillez choisir parmi les options du sous menu matiere !");
                    goto matiere_menu; 
        }
    }while (optionSousMenuMatiere != 8); 
}


static int reference_existe(int x)
{
    char libelle[15];
    int reference, coefficient;

    FILE  *fichier_matiere = fopen ("gestion_matiere/matiere.csv", "r");

    while (fscanf(fichier_matiere, "%d  %s  %d \n", &reference, libelle, &coefficient) != -1)
    {
        if (x == reference)
        {
            fclose(fichier_matiere);
            return 1;    
        }
    }
    fclose(fichier_matiere);
    return 0;
}

void ajouter_matiere()
{
    int n,i;
    do
    { 
    printf("Combien de matiere souhaiter vous ajouter : ");
    scanf("%d", &n);
    }while(n <= 0);

    for(i = 1; i <= n; i++)
    { 
        printf("\t\tDonner une reference de la matiere : ");
        scanf("%d", &matiere_ajouter.reference);

        int retour_fonction_ref_existe = reference_existe(matiere_ajouter.reference);
        while(retour_fonction_ref_existe == 1)
        {
            printf("\t\tLa reference donnée existe deja\n");
            printf("\t\tVeuillez saisir une autre reference : ");
            scanf("%d", &matiere_ajouter.reference);
            retour_fonction_ref_existe = reference_existe(matiere_ajouter.reference);
        }
        printf("\n\t\tDonner le libelle de la matiere : ");
        scanf("%s", &matiere_ajouter.libelle);
        printf("\n\t\tDonner le coefficient de la matiere :");
        scanf("%d", &matiere_ajouter.coefficient);

        FILE *matiere = fopen("gestion_matiere/matiere.csv","a");

        
        if (matiere == NULL)
        { 
            printf("Erreur d'ouverture du fichier matiere");
            exit(1);
        }

        fprintf(matiere, "%d  %s  %d \n", matiere_ajouter.reference, matiere_ajouter.libelle, matiere_ajouter.coefficient);

        fclose(matiere);
        printf("Ajout reussi\n");
    }
    
}



void modifier_matiere()
{
    int numeroEnreg;
    int n,i;
    do
    { 
        printf("Combien de matiere souhaiter vous modifier : ");
        scanf("%d", &n);
    }while(n <= 0);
    
    for(i = 1; i <= n; i++)
    { 
        printf("Numero de l'enregistrement a modifier : ");
        scanf("%d", &numeroEnreg);

        FILE *matiere = fopen("gestion_matiere/matiere.csv","r");
        FILE *temp = fopen("gestion_matiere/temp.csv", "w");


        if( matiere == NULL || temp == NULL )
        { 
            printf("Suite a un probleme, le programme a ete arrete\n");
            exit(1);
        }

        if(reference_existe(numeroEnreg) == 1)
        {    
            while(fscanf(matiere,"%d %s %d \n", &matiere_ajouter.reference, matiere_ajouter.libelle, &matiere_ajouter.coefficient) != EOF)
            {
                
                if(reference_existe(numeroEnreg == matiere_ajouter.reference))
                {
                    printf("Entrez le nouveau libelle : ");
                    scanf("%s", matiere_ajouter.libelle);
                    printf("Entrez le nouveau coefficient : ");
                    scanf("%d", &matiere_ajouter.coefficient);
                }
                fprintf(temp,"%d %s %d \n", matiere_ajouter.reference, matiere_ajouter.libelle, matiere_ajouter.coefficient);
            }
            
        }
        else
        {
            printf("L'element a modifier est absent dans la liste des matieres");
            exit(1);
        }
        fclose(matiere);
        fclose(temp);
        remove("gestion_matiere/matiere.csv");
        rename("gestion_matiere/temp.csv", "gestion_matiere/matiere.csv");
        printf("Enregistrement modifie avec succees\n");
    }
}



int rechercher_matiere(int reference_rechercher)
{
    FILE *Fichier = fopen("gestion_matiere/matiere.csv","r");

    do
    {  
        fscanf(Fichier,"%d  %s  %d ", &matiere_ajouter.reference, matiere_ajouter.libelle, &matiere_ajouter.coefficient);
        if(matiere_ajouter.reference == reference_rechercher)
        {
            fclose(Fichier);
            return 1;
        }    

    }while(!feof(Fichier));
    
    fclose(Fichier);
    return 0;
}



void supprimer_matiere()
{
    int reference_a_supp;
    int n,i;

    do
    { 
        printf("Combien de matiere souhaiter vous modifier : ");
        scanf("%d", &n);
    }while(n <= 0); 

    for(i = 1; i <= n; i++)
    {
        printf("Entrez la reference de la matiere a supprimer : ");
        scanf("%d", &reference_a_supp);

        if(!(reference_existe(reference_a_supp)))
            exit(1);

        FILE *fichier = fopen("gestion_matiere/matiere.csv", "r+");
        FILE *temp = fopen("test.csv", "w");

        if (fichier == NULL || temp == NULL)
        {
            printf("Suite a un probleme, le programme a ete arrete\n");
            exit(1);
        }

        while(fscanf(fichier, " %d  %s  %d\n", &matiere_ajouter.reference, matiere_ajouter.libelle, &matiere_ajouter.coefficient) != EOF)
        {
            if(matiere_ajouter.reference == reference_a_supp)
            {
                printf("Supression de la matiere\n");
            }
            else
            {
                fprintf(temp, "%d  %s  %d\n", matiere_ajouter.reference, matiere_ajouter.libelle, matiere_ajouter.coefficient);
            }
        }
        fclose(temp);
        fclose(fichier);
        if(remove("gestion_matiere/matiere.csv") != 0)
            printf("ERREUR DE SUPPRESSION\n");
        else
            printf("SUPPRESSION REUSSIEE\n");

        if(rename("test.csv","gestion_matiere/matiere.csv") != 0)
            printf("ERREUR DE RENOMMAGE\n");
        else
            printf("RENOMMAGE REUSSIE\n");
            
        printf("Matiere supprimee avec succes.\n");
    }
}


void afficher_matiere()
{
    matiere matiere_ajouter;
        FILE *matiere = fopen("gestion_matiere/matiere.csv","r");

        if(matiere == NULL)
        {
            printf("Suite a un probleme, le programme a ete arrete\n");
            exit(1);
        }
            

        printf("\t+-----------+-----------------+-------------+\n");
        printf("\t| Reference |     libelle     | coefficient |\n");
        printf("\t+-----------+-----------------+-------------+\n");

        while(fscanf(matiere,"%d %s %d \n", &matiere_ajouter.reference,matiere_ajouter.libelle, &matiere_ajouter.coefficient) != EOF)
        {
            printf("\t| %9d | %15s | %11d |\n", matiere_ajouter.reference,matiere_ajouter.libelle, matiere_ajouter.coefficient);
            printf("\t+-----------+-----------------+-------------+\n");
        }

        fclose(matiere);
}

static int code_existe(int x)
{
    int code;
    char nom[26];
    char niveau[10];

    FILE  *fichier_classe = fopen ("../gestion_des_classes/classes.csv", "r");

    while (fscanf(fichier_classe, "%d,%s,%s\n", &code, nom, niveau) != EOF)
    {
        if (x == code)
        {
            fclose(fichier_classe);
            return 1;    
        }
    }
    fclose(fichier_classe);
    return 0;
}


void associer_matiere_classe()
{
    Se_faire associer;

    do
    { 
        printf("Donner la reference de la matiere : ");
        scanf("%d", &associer.reference_matiere);
    }while(associer.reference_matiere <= 0);
    
    if(!reference_existe(associer.reference_matiere))
        printf("\nLa reference de la matiere saisie n'existe pas\n");

    do
    { 
        printf("Donner le code de la classe : ");
        scanf("%d", &associer.code_classe);
    }while(associer.code_classe <= 0);
        if(!code_existe(associer.code_classe))
            printf("\nLe code de la classe saisie n'existe pas");

    if(!reference_existe(associer.reference_matiere) && code_existe(associer.code_classe))
    {
        FILE *matiere_Classe = fopen("gestion_matiere/matiere_classe.csv", "a");
        fprintf(matiere_Classe, "%d %d\n", associer.code_classe, associer.reference_matiere);
        fclose(matiere_Classe);
    }
    
}

void dissocier_matiere_classe()
{
    Se_faire dissocier;
    int code, reference;
    do
    { 
        printf("Donner la reference de la matiere : ");
        scanf("%d", &dissocier.reference_matiere);
    }while(dissocier.reference_matiere <= 0);
    if(!reference_existe(dissocier.reference_matiere))
    {
        printf("\nLa reference de la matiere saisie n'existe pas\n");
        do
        { 
        printf("Donner la reference d'une matiere existante : ");
        scanf("%d", &dissocier.reference_matiere);
        }while(dissocier.reference_matiere <= 0 || !reference_existe(dissocier.reference_matiere));
    }

    do
    { 
        printf("Donner le code de la classe : ");
        scanf("%d", &dissocier.code_classe);
    }while(dissocier.code_classe <= 0);
    if(!code_existe(dissocier.code_classe))
    {
        printf("\nLe code de la classe saisie n'existe pas");
        do
        { 
            printf("Donner le code d'une classe existante : ");
            scanf("%d", &dissocier.code_classe);
        }while(!code_existe(dissocier.code_classe) || dissocier.code_classe <= 0);
    }
            
    FILE *matiere_Classe = fopen("gestion_matiere/matiere_classe.csv", "r");
    FILE *modif_matiere_Classe = fopen("gestion_matiere/temp.csv", "w");
    do
    {
        fscanf(matiere_Classe, "%d %d", &reference, &code);
        if(code == dissocier.code_classe && reference == dissocier.reference_matiere)
            printf("Dissociation reussie entre matiere et classe\n");
        else
            fprintf(modif_matiere_Classe, "%d %d", dissocier.code_classe, dissocier.reference_matiere);
    }while(!EOF);

    fclose(matiere_Classe);
    fclose(modif_matiere_Classe);
    remove("gestion_matiere/matiere_classe.csv");
    rename("gestion_matiere/temp.csv","gestion_matiere/matiere_classe.csv");

}   

void afficher_matiere_classe()
{
        Se_faire association;
        FILE *matiere_classe = fopen("gestion_matiere/matiere_classe.csv","r");

        if(matiere_classe == NULL)
        {
            printf("Suite a un probleme, le programme a ete arrete\n");
            exit(1);
        }
            

        printf("\t+-------------------+-------------------+\n");
        printf("\t| Reference Matiere | code de la classe |\n");
        printf("\t+-------------------+-------------------+\n");
        
        while(fscanf(matiere_classe,"%d %d \n", &association.reference_matiere, &association.code_classe) != EOF)
        {
            
            printf("\t|      %19d     |         %19d         |\n", &association.reference_matiere, &association.code_classe);
            printf("\t+---------------+----------------------+\n");
        }

        fclose(matiere_classe);
}