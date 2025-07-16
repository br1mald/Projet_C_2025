#include "gestion_classes/gestion_classes.h"
#include "gestion_matiere/matiere.h"

void associer_matiere_classe(int class_code, int mat_reference, Classe classes[], int *size, Se_faire tab[], int *se_faire_size);
void initialize_se_faire(Se_faire tab[], int *se_faire_size);
int rechercher_association(int target_classe, int target_matiere);
void dissocier_matiere_classe(int target_classe, int target_matiere);
void afficher_matieres_classe(int class_code);
