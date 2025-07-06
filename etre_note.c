
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "etre_note.h"

#define FICHIER_ETRE_NOTE "etre_note.csv"
#define NOTE_MIN 0.0f
#define NOTE_MAX 20.0f

void menu_etre_note() {
    int choix;
    do {
        printf("\n=== GESTION DES RELATIONS ETRE_NOTE ===\n");
        printf("1. Ajouter relation etudiant-matiere\n");
        printf("2. Ajouter relations pour toutes les matieres d'un etudiant\n");
        printf("3. Ajouter relations pour une classe dans une matiere\n");
        printf("4. Modifier une relation\n");
        printf("5. Supprimer une relation\n");
        printf("6. Afficher relations etudiant-matiere\n");
        printf("7. Afficher toutes les relations d'un etudiant\n");
        printf("8. Afficher relations classe-matiere\n");
        printf("9. Retour au menu principal\n");
        printf("Choix : ");
        scanf("%d", &choix);
        
        switch(choix) {
            case 1: ajouter_etre_note_etudiant_matiere(); break;
            case 2: ajouter_etre_note_etudiant_toutes_matieres(); break;
            case 3: ajouter_etre_note_classe_matiere(); break;
            case 4: modifier_etre_note(); break;
            case 5: supprimer_etre_note(); break;
            case 6: afficher_etre_note_etudiant_matiere(); break;
            case 7: afficher_etre_note_etudiant_toutes_matieres(); break;
            case 8: afficher_etre_note_classe_matiere(); break;
            case 9: return;
            default: printf("Choix invalide!\n");
        }
    } while(1);
}

int valider_note(float note) {
    return note >= NOTE_MIN && note <= NOTE_MAX;
}

float saisir_note_valide(const char* message) {
    float note;
    do {
        printf("%s (%.1f-%.1f): ", message, NOTE_MIN, NOTE_MAX);
        scanf("%f", &note);
        if (!valider_note(note)) {
            printf("Erreur: La note doit etre entre %.1f et %.1f\n", NOTE_MIN, NOTE_MAX);
        }
    } while (!valider_note(note));
    return note;
}

void ajouter_etre_note_etudiant_matiere() {
    Etre_note en;
    Etudiant etudiant;
    Matiere matiere;
    int etudiant_existe = 0, matiere_existe = 0;
    
    printf("Numero etudiant: ");
    scanf("%d", &en.numero_etudiant);
    
    FILE *f_etudiants = fopen("etudiants.csv", "r");
    if (f_etudiants) {
        while(fscanf(f_etudiants, "%d,%[^,],%[^,],%[^,],%[^,],%d\n", 
                    &etudiant.numero, 
                    etudiant.nom, 
                    etudiant.prenom, 
                    etudiant.email, 
                    etudiant.date_naissance, 
                    &etudiant.code_classe) != EOF) {
            if (etudiant.numero == en.numero_etudiant) {
                etudiant_existe = 1;
                break;
            }
        }
        fclose(f_etudiants);
    }
    
    if (!etudiant_existe) {
        printf("Erreur: Etudiant inexistant!\n");
        return;
    }
    
    printf("Reference matiere: ");
    scanf("%s", en.reference_matiere);
    
    FILE *f_matieres = fopen("matieres.csv", "r");
    if (f_matieres) {
        while(fscanf(f_matieres, "%[^,],%[^,],%d\n", 
                    matiere.reference, 
                    matiere.libelle, 
                    &matiere.coefficient) != EOF) {
            if (strcmp(matiere.reference, en.reference_matiere) == 0) {
                matiere_existe = 1;
                break;
            }
        }
        fclose(f_matieres);
    }
    
    if (!matiere_existe) {
        printf("Erreur: Matiere inexistante!\n");
        return;
    }
    
    en.noteCC = saisir_note_valide("Note CC");
    en.noteDS = saisir_note_valide("Note DS");
    
    FILE *f_notes = fopen(FICHIER_ETRE_NOTE, "a");
    if (f_notes) {
        fprintf(f_notes, "%d,%s,%.2f,%.2f\n", 
                en.numero_etudiant, 
                en.reference_matiere, 
                en.noteCC, 
                en.noteDS);
        fclose(f_notes);
        printf("Relation ajoutee avec succes!\n");
    } else {
        printf("Erreur lors de l'enregistrement!\n");
    }
}

void afficher_etre_note_etudiant_matiere() {
    int numero;
    char reference[15];
    Etre_note en;
    int trouve = 0;
    
    printf("Numero etudiant: ");
    scanf("%d", &numero);
    
    printf("Reference matiere: ");
    scanf("%s", reference);
    
    FILE *fichier = fopen(FICHIER_ETRE_NOTE, "r");
    if (!fichier) {
        printf("Aucune relation enregistree!\n");
        return;
    }
    
    printf("\n=== Relations pour l'etudiant %d dans %s ===\n", numero, reference);
    
    while(fscanf(fichier, "%d,%[^,],%f,%f\n", 
                 &en.numero_etudiant, 
                 en.reference_matiere, 
                 &en.noteCC, 
                 &en.noteDS) != EOF) {
        if (en.numero_etudiant == numero && 
            strcmp(en.reference_matiere, reference) == 0) {
            float moyenne = (en.noteCC + en.noteDS) / 2;
            printf("CC: %.2f | DS: %.2f | Moyenne: %.2f\n", 
                   en.noteCC, 
                   en.noteDS, 
                   moyenne);
            trouve = 1;
        }
    }
    
    if (!trouve) {
        printf("Aucune relation trouvee!\n");
    }
    
    fclose(fichier);
}

void ajouter_etre_note_classe_matiere() {
    int code_classe;
    char reference_matiere[15];
    Etudiant etudiant;
    Etre_note en;
    
    printf("Code classe: ");
    scanf("%d", &code_classe);
    
    printf("Reference matiere: ");
    scanf("%s", reference_matiere);
    
    Matiere matiere;
    int matiere_existe = 0;
    FILE *f_matieres = fopen("matieres.csv", "r");
    if (f_matieres) {
        while(fscanf(f_matieres, "%[^,],%[^,],%d\n", 
                    matiere.reference, 
                    matiere.libelle, 
                    &matiere.coefficient) != EOF) {
            if (strcmp(matiere.reference, reference_matiere) == 0) {
                matiere_existe = 1;
                break;
            }
        }
        fclose(f_matieres);
    }
    
    if (!matiere_existe) {
        printf("Erreur: Matiere inexistante!\n");
        return;
    }
    
    FILE *f_etudiants = fopen("etudiants.csv", "r");
    FILE *f_notes = fopen(FICHIER_ETRE_NOTE, "a");
    
    if (!f_etudiants || !f_notes) {
        printf("Erreur d'ouverture des fichiers!\n");
        if (f_etudiants) fclose(f_etudiants);
        if (f_notes) fclose(f_notes);
        return;
    }
    
    printf("\nSaisie des relations pour la classe %d en %s\n", code_classe, reference_matiere);
    
    while(fscanf(f_etudiants, "%d,%[^,],%[^,],%[^,],%[^,],%d\n", 
                &etudiant.numero, 
                etudiant.nom, 
                etudiant.prenom, 
                etudiant.email, 
                etudiant.date_naissance, 
                &etudiant.code_classe) != EOF) {
        if (etudiant.code_classe == code_classe) {
            printf("\nEtudiant: %s %s\n", etudiant.prenom, etudiant.nom);
            
            en.numero_etudiant = etudiant.numero;
            strcpy(en.reference_matiere, reference_matiere);
            
            en.noteCC = saisir_note_valide("Note CC");
            en.noteDS = saisir_note_valide("Note DS");
            
            fprintf(f_notes, "%d,%s,%.2f,%.2f\n", 
                    en.numero_etudiant, 
                    en.reference_matiere, 
                    en.noteCC, 
                    en.noteDS);
        }
    }
    
    fclose(f_etudiants);
    fclose(f_notes);
    printf("Relations ajoutees avec succes!\n");
}

void afficher_etre_note_etudiant_toutes_matieres() {
    int numero;
    Etre_note en;
    int trouve = 0;
    float moyenne_generale = 0;
    int nb_matieres = 0;
    
    printf("Numero etudiant: ");
    scanf("%d", &numero);
    
    FILE *fichier = fopen(FICHIER_ETRE_NOTE, "r");
    if (!fichier) {
        printf("Aucune relation enregistree!\n");
        return;
    }
    
    printf("\n=== Toutes les relations pour l'etudiant %d ===\n", &numero);
    
    while(fscanf(fichier, "%d,%[^,],%f,%f\n", 
                 &en.numero_etudiant, 
                 en.reference_matiere, 
                 &en.noteCC, 
                 &en.noteDS) != EOF) {
        if (en.numero_etudiant == numero) {
            float moyenne = (en.noteCC + en.noteDS) / 2;
            printf("Matiere: %s | CC: %.2f | DS: %.2f | Moyenne: %.2f\n", 
                   en.reference_matiere, 
                   en.noteCC, 
                   en.noteDS, 
                   moyenne);
            moyenne_generale += moyenne;
            nb_matieres++;
            trouve = 1;
        }
    }
    
    if (trouve) {
        printf("\nMoyenne generale: %.2f\n", moyenne_generale / nb_matieres);
    } else {
        printf("Aucune relation trouvee pour cet etudiant!\n");
    }
    
    fclose(fichier);
}


