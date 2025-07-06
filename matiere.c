#include <stdio.h>
#include <stdlib.h>
#include "matiere.h"

void ajouter_matiere()
{
    matiere matiere_ajouter;

    printf("Donner une reference de la matiere : ");
    scanf("%d", &matiere_ajouter.reference);
    printf("\nDonner le libelle de la matiere : ");
    scanf("%s", &matiere_ajouter.libelle);
    printf("\nDonner le coefficient de la matiere :");
    scanf("%d", &matiere_ajouter.coefficient);
   
    FILE *matiere = fopen("matiere.csv","a");

    if(matiere == NULL)
        exit(1);
    
    fprintf(matiere, "|---------------------------------------|\n");
    fprintf(matiere, "| %9d | %11s | %11d |\n", matiere_ajouter.reference, matiere_ajouter.libelle, matiere_ajouter.coefficient);
    fprintf(matiere, "|---------------------------------------|\n");

    fclose(matiere);
    printf("Ajout reussi\n");
}

void modifier_matiere()
{

}

void rechercher_matiere();

void supprimer_matiere();

void afficher_matiere()
{
    FILE *matiere = fopen("matiere.csv","r");

    signed char texte[256];

    if(matiere == NULL)
        exit(1);

    while(fgets(texte, 255, matiere) != NULL)
    {
        printf("%s", texte);
    }
    
    fclose(matiere);
}



