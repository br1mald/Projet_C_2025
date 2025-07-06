
#ifndef ETRE_NOTE_H
#define ETRE_NOTE_H

#include "etudiant.h"
#include "matiere.h"
#include "classe.h"

// Structure représentant la relation "être noté" avec :
// - numero_etudiant : identifiant de l'étudiant (clé étrangère)
// - reference_matiere : code de la matière (clé étrangère)
// - noteCC : note de contrôle continu (entre 0 et 20)
// - noteDS : note de devoir surveillé (entre 0 et 20)
typedef struct {
    int numero_etudiant;
    char reference_matiere[15];
    float noteCC;
    float noteDS;
} Etre_note;

// Fonctions pour la gestion de la relation "être noté"
void menu_etre_note();  // Affiche le menu de gestion
void ajouter_etre_note_etudiant_matiere();  // Ajoute une relation pour un étudiant dans une matière
void ajouter_etre_note_etudiant_toutes_matieres();  // Ajoute les relations pour toutes les matières d'un étudiant
void ajouter_etre_note_classe_matiere();  // Ajoute les relations pour une matière dans toute une classe
void modifier_etre_note();  // Modifie une relation existante
void supprimer_etre_note();  // Supprime une relation
void afficher_etre_note_etudiant_matiere();  // Affiche les relations d'un étudiant dans une matière
void afficher_etre_note_etudiant_toutes_matieres();  // Affiche toutes les relations d'un étudiant
void afficher_etre_note_classe_matiere();  // Affiche les relations d'une classe dans une matière

#endif
