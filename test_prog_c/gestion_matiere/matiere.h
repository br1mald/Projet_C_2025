#ifndef MATIERE_H
#define MATIERE_H
typedef struct 
{
    int reference;
    char libelle[15];
    int short coefficient;
}matiere;

typedef struct 
{
    int reference_matiere;
    int code_classe;
}se_faire;

int gestion_matiere();
void ajouter_matiere();
void modifier_matiere();
int rechercher_matiere(int);
void supprimer_matiere();
void afficher_matiere();
void associer_matiere_classe();
void dissocier_matiere_classe();
void afficher_matiere_classe();

#endif