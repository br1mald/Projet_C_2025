#include <stdio.h>
#include <stdlib.h>
#include "matiere.h"

matiere matiere_ajouter;
int menu_matiere()
{
    int optionSousMenuMatiere;

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
    
    
}

static int reference_existe(int x)
{
    char libelle[15];
    int reference, coefficient;

    FILE  *fichier_matiere = fopen ("matiere.csv", "r");

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

    FILE *matiere = fopen("matiere.csv","a");

    
    if (matiere == NULL)
    { 
        printf("Erreur d'ouverture du fichier matiere");
        exit(1);
    }

    fprintf(matiere, "%d  %s  %d \n", matiere_ajouter.reference, matiere_ajouter.libelle, matiere_ajouter.coefficient);

    fclose(matiere);
    printf("Ajout reussi\n");
    
    
}



void modifier_matiere()
{
        int numeroEnreg;
        
        printf("Numero de l'enregistrement a modifier : ");
        scanf("%d", &numeroEnreg);

        FILE *matiere = fopen("matiere.csv","r");
        FILE *temp = fopen("temp.csv", "w");
    

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
        remove("matiere.csv");
        rename("temp.csv", "matiere.csv");
        printf("Enregistrement modifie avec succees\n");
}



int rechercher_matiere(int reference_rechercher)
{
    FILE *Fichier = fopen("matiere.csv","r");

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
    
        printf("Entrez la reference de la matiere a supprimer : ");
        scanf("%d", &reference_a_supp);

        if(!(reference_existe(reference_a_supp)))
            exit(1);

        FILE *fichier = fopen("matiere.csv", "r+");
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
        if(remove("matiere.csv") != 0)
            printf("ERREUR DE SUPPRESSION\n");
        else
            printf("SUPPRESSION REUSSIEE\n");

        if(rename("test.csv","matiere.csv") != 0)
            printf("ERREUR DE RENOMMAGE\n");
        else
            printf("RENOMMAGE REUSSIE\n");
            
        printf("Matiere supprimee avec succes.\n");
}


void afficher_matiere()
{
    
        FILE *matiere = fopen("matiere.csv","r");

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



