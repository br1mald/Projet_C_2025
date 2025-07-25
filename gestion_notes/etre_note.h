#ifndef ETRE_NOTE_H
#define ETRE_NOTE_H

typedef struct Etudiant Etudiant;
typedef struct Matiere Matiere;
typedef struct Classe Classe;
typedef struct {
    int numero_etudiant;
    int reference_matiere;
    int numero;
    int reference;
    float noteCC;
    float noteDS;
} Etre_note;

// Fonctions utilitaires
int valider_note(float note);
float saisir_note_valide(const char* message);
float calculer_moyenne(float noteCC, float noteDS);
int matiere_associee_classe(int ref_matiere, int code_classe);

// Fonctions principales
int gestion_notes();
void ajouter_note_etudiant_matiere();
void ajouter_note_etudiant_toutes_matieres();
void ajouter_note_classe_matiere();
void modifier_note();
void supprimer_note();
void afficher_note_etudiant_matiere();
void afficher_note_classe_matiere();
void afficher_note_etudiant_toutes_matieres();

#endif