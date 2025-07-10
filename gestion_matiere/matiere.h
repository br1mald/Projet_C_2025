
typedef struct 
{
    int reference;
    char libelle[15];
    int short coefficient;
}matiere;

int menu_matiere();
void ajouter_matiere();
void modifier_matiere();
int rechercher_matiere(int);
void supprimer_matiere();
void afficher_matiere();

