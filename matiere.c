#include <stdio.h>
#include <stdlib.h>
#include "matiere.h"

void ajout_matiere()
{
   FILE *matiere = fopen("matiere.csv","w");
   signed char texte[256] = {0};

    if(matiere == NULL)
        exit(1);

    fputs(texte, matiere);

   fclose(matiere);
}
void modification_matiere();
void recherche_matiere();
void supprimer_matiere();

void affichage_matiere()
{
    FILE *matiere = fopen("matiere.csv","r");
    //int caractere = 0;
    signed char texte[256];

    if(matiere == NULL)
        exit(1);

    while(fgets(texte, 255, matiere) != NULL)
        printf("%s", texte);
    // while(caractere != EOF)
    // {
    //     caractere = fgetc(matiere);
    //     printf("%c", caractere);
    // }
    
    fclose(matiere);
}



