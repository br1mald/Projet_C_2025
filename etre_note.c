#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "etre_note.h"
#include "matiere.h"
#include "classe.h"
#include "etudiant.h"
#define FICHIER_ETRE_NOTE "etre_note.csv"
#define NOTE_MIN 0.0f
#define NOTE_MAX 20.0f

float calculer_moyenne(float noteCC, float noteDS) {
    return (noteCC * 0.3f) + (noteDS * 0.7f);
}

int valider_note(float note) {
    return (note >= NOTE_MIN) && (note <= NOTE_MAX);
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

void ajouter_note_etudiant_matiere() {
    Etre_note note;
    Etudiant etudiant;
    Matiere matiere;
    int etudiant_existe = 0, matiere_existe = 0;
    char choix;
    
    do {
        etudiant_existe = 0;
        printf("Numero etudiant: ");
        scanf("%d", &note.numero);
        
        FILE *f_etudiants = fopen("etudiants.csv", "r");
        if (f_etudiants) {
            while(fscanf(f_etudiants, "%d,%[^,],%[^,],%[^,],%[^,],%d\n", 
                        &etudiant.numero, etudiant.nom, etudiant.prenom, 
                        etudiant.email, etudiant.date_naissance, 
                        &etudiant.code) != EOF) {
                if (etudiant.numero == note.numero) {
                    etudiant_existe = 1;
                    break;
                }
            }
            fclose(f_etudiants);
        }
        
        if (!etudiant_existe) {
            printf("Erreur: Etudiant inexistant!\n");
            printf("Voulez-vous resaisir? (o/n): ");
            scanf(" %c", &choix);
            if (choix != 'o' && choix != 'O') return;
        }
    } while (!etudiant_existe);
    
    do {
        matiere_existe = 0;
        printf("Reference matiere: ");
        scanf("%d", &note.reference);
        
        FILE *f_matieres = fopen("matieres.csv", "r");
        if (f_matieres) {
            while(fscanf(f_matieres, "%d,%[^,],%d\n", 
                        &matiere.reference, matiere.libelle, 
                        &matiere.coefficient) != EOF) {
                if (matiere.reference == note.reference) {
                    matiere_existe = 1;
                    break;
                }
            }
            fclose(f_matieres);
        }
        
        if (!matiere_existe) {
            printf("Erreur: Matiere inexistante!\n");
            printf("Voulez-vous resaisir? (o/n): ");
            scanf(" %c", &choix);
            if (choix != 'o' && choix != 'O') return;
        }
    } while (!matiere_existe);
    
    if (!matiere_associee_classe(note.reference, etudiant.code)) {
        printf("Erreur: Cette matiere n'est pas associee a la classe de l'etudiant!\n");
        return;
    }
    
    note.noteCC = saisir_note_valide("Note CC");
    note.noteDS = saisir_note_valide("Note DS");
    
    FILE *f_notes = fopen(FICHIER_ETRE_NOTE, "a");
    if (f_notes) {
        fprintf(f_notes, "%d,%d,%.2f,%.2f\n", 
                note.numero, note.reference, 
                note.noteCC, note.noteDS);
        fclose(f_notes);
        printf("Note ajoutee avec succes!\n");
    } else {
        printf("Erreur lors de l'enregistrement!\n");
    }
}

void afficher_note_etudiant_matiere() {
    int numero;
    int reference;
    Etre_note en;
    int trouve = 0;
    
    printf("Numero etudiant: ");
    scanf("%d", &numero);
    
    printf("Reference matiere: ");
    scanf("%d", &reference);
    
    FILE *fichier = fopen(FICHIER_ETRE_NOTE, "r");
    if (!fichier) {
        printf("Aucune note enregistree!\n");
        return;
    }
    
    printf("\n=== Notes de l'etudiant %d dans %d ===\n", numero, reference);
    
    while(fscanf(fichier, "%d,%d,%f,%f\n", 
                 &en.numero, &en.reference, 
                 &en.noteCC, &en.noteDS) != EOF) {
        if (en.numero == numero && 
            en.reference == reference) {
            float moyenne = calculer_moyenne(en.noteCC, en.noteDS);
            printf("CC: %.2f | DS: %.2f | Moyenne: %.2f\n", 
                   en.noteCC, en.noteDS, moyenne);
            trouve = 1;
            break;
        }
    }
    
    if (!trouve) {
        printf("Aucune note trouvee pour cette combinaison!\n");
    }
    
    fclose(fichier);
}

void modifier_note() {
    int numero;
    int reference;
    Etre_note en;
    int trouve = 0;
    FILE *fichier = fopen(FICHIER_ETRE_NOTE, "r");
    FILE *temp = fopen("temp.csv", "w");

    printf("Numero etudiant: ");
    scanf("%d", &numero);
    
    printf("Reference matiere: ");
    scanf("%d", &reference);

    if (!fichier || !temp) {
        printf("Erreur d'ouverture des fichiers!\n");
        if (fichier) fclose(fichier);
        if (temp) fclose(temp);
        return;
    }

    while(fscanf(fichier, "%d,%d,%f,%f\n", 
               &en.numero, &en.reference, 
               &en.noteCC, &en.noteDS) != EOF) {
        if (en.numero == numero && 
            en.reference == reference) {
            printf("Anciennes notes - CC: %.2f, DS: %.2f\n", en.noteCC, en.noteDS);
            en.noteCC = saisir_note_valide("Nouvelle note CC");
            en.noteDS = saisir_note_valide("Nouvelle note DS");
            trouve = 1;
        }
        fprintf(temp, "%d,%d,%.2f,%.2f\n", 
                en.numero, en.reference, 
                en.noteCC, en.noteDS);
    }

    fclose(fichier);
    fclose(temp);

    if (trouve) {
        remove(FICHIER_ETRE_NOTE);
        rename("temp.csv", FICHIER_ETRE_NOTE);
        printf("Note modifiee avec succes!\n");
    } else {
        remove("temp.csv");
        printf("Aucune note trouvee!\n");
    }
}

void supprimer_note() {
    int numero;
    int reference;
    Etre_note en;
    int trouve = 0;
    FILE *fichier = fopen(FICHIER_ETRE_NOTE, "r");
    FILE *temp = fopen("temp.csv", "w");

    printf("Numero etudiant: ");
    scanf("%d", &numero);
    
    printf("Reference matiere: ");
    scanf("%d", &reference);

    if (!fichier || !temp) {
        printf("Erreur d'ouverture des fichiers!\n");
        if (fichier) fclose(fichier);
        if (temp) fclose(temp);
        return;
    }

    while(fscanf(fichier, "%d,%d,%f,%f\n", 
               &en.numero, &en.reference, 
               &en.noteCC, &en.noteDS) != EOF) {
        if (en.numero == numero && 
            en.reference == reference) {
            printf("Note supprimee: %d %d (CC: %.2f, DS: %.2f)\n", 
                   en.numero, en.reference, 
                   en.noteCC, en.noteDS);
            trouve = 1;
        } else {
            fprintf(temp, "%d,%d,%.2f,%.2f\n", 
                    en.numero, en.reference, 
                    en.noteCC, en.noteDS);
        }
    }

    fclose(fichier);
    fclose(temp);

    if (trouve) {
        remove(FICHIER_ETRE_NOTE);
        rename("temp.csv", FICHIER_ETRE_NOTE);
        printf("Suppression reussie!\n");
    } else {
        remove("temp.csv");
        printf("Aucune note trouvee!\n");
    }
}

void afficher_note_etudiant_toutes_matieres() {
    int numero;
    Etre_note en;
    Etudiant etudiant;
    Matiere matiere;
    int trouve = 0;
    float moyenne_generale = 0;
    int nb_matieres = 0;
    int etudiant_trouve = 0;
    
    printf("Numero etudiant: ");
    scanf("%d", &numero);
    
    FILE *f_etud = fopen("etudiants.csv", "r");
    if (f_etud) {
        while(fscanf(f_etud, "%d,%[^,],%[^,],%[^,],%[^,],%d\n", 
                    &etudiant.numero, etudiant.nom, etudiant.prenom, 
                    etudiant.email, etudiant.date_naissance, 
                    &etudiant.code) != EOF) {
            if (etudiant.numero == numero) {
                etudiant_trouve = 1;
                break;
            }
        }
        fclose(f_etud);
    }
    
    if (!etudiant_trouve) {
        printf("Erreur: Etudiant inexistant!\n");
        return;
    }
    
    FILE *f_notes = fopen(FICHIER_ETRE_NOTE, "r");
    if (!f_notes) {
        printf("Aucune note enregistree!\n");
        return;
    }
    
    printf("\n=== Toutes les notes pour l'etudiant %d ===\n", numero);
    printf("Nom: %s %s\n", etudiant.prenom, etudiant.nom);
    
    while(fscanf(f_notes, "%d,%d,%f,%f\n", 
                 &en.numero, &en.reference, 
                 &en.noteCC, &en.noteDS) != EOF) {
        if (en.numero == numero) {
            FILE *f_mat = fopen("matieres.csv", "r");
            char libelle[100] = "Inconnu";
            if (f_mat) {
                while(fscanf(f_mat, "%d,%[^,],%d\n", 
                            &matiere.reference, matiere.libelle, 
                            &matiere.coefficient) != EOF) {
                    if (matiere.reference == en.reference) {
                        strcpy(libelle, matiere.libelle);
                        break;
                    }
                }
                fclose(f_mat);
            }
            
            float moyenne = calculer_moyenne(en.noteCC, en.noteDS);
            printf("Matiere: %s (%d) | CC: %.2f | DS: %.2f | Moyenne: %.2f\n", 
                   libelle, en.reference, 
                   en.noteCC, en.noteDS, moyenne);
            moyenne_generale += moyenne;
            nb_matieres++;
            trouve = 1;
        }
    }
    
    fclose(f_notes);
    
    if (trouve) {
        printf("\nMoyenne generale: %.2f\n", moyenne_generale / nb_matieres);
    } else {
        printf("Aucune note trouvee pour cet etudiant!\n");
    }
}

void ajouter_note_etudiant_toutes_matieres() {
    int numero;
    Etudiant etudiant;
    Matiere matiere;
    Etre_note en;
    int etudiant_trouve = 0;
    int nb_matieres = 0;

    printf("Numero etudiant: ");
    scanf("%d", &numero);

    FILE *f_etud = fopen("etudiants.csv", "r");
    if (f_etud) {
        while(fscanf(f_etud, "%d,%[^,],%[^,],%[^,],%[^,],%d\n", 
                    &etudiant.numero, etudiant.nom, etudiant.prenom, 
                    etudiant.email, etudiant.date_naissance, 
                    &etudiant.code) != EOF) {
            if (etudiant.numero == numero) {
                etudiant_trouve = 1;
                break;
            }
        }
        fclose(f_etud);
    }

    if (!etudiant_trouve) {
        printf("Erreur: Etudiant inexistant!\n");
        return;
    }

    FILE *f_mat = fopen("matieres.csv", "r");
    FILE *f_notes = fopen(FICHIER_ETRE_NOTE, "a");

    if (!f_mat || !f_notes) {
        printf("Erreur d'ouverture des fichiers!\n");
        if (f_mat) fclose(f_mat);
        if (f_notes) fclose(f_notes);
        return;
    }

    printf("\nSaisie des notes pour %s %s\n", etudiant.prenom, etudiant.nom);

    while(fscanf(f_mat, "%d,%[^,],%d\n", 
                &matiere.reference, matiere.libelle, 
                &matiere.coefficient) != EOF) {
        if (matiere_associee_classe(matiere.reference, etudiant.code)) {
            printf("\nMatiere: %s (Coeff: %d)\n", matiere.libelle, matiere.coefficient);
            
            en.numero = numero;
            en.reference = matiere.reference;
            
            en.noteCC = saisir_note_valide("Note CC");
            en.noteDS = saisir_note_valide("Note DS");
            
            fprintf(f_notes, "%d,%d,%.2f,%.2f\n", 
                    en.numero, en.reference, 
                    en.noteCC, en.noteDS);
            nb_matieres++;
        }
    }

    fclose(f_mat);
    fclose(f_notes);
    
    if (nb_matieres > 0) {
        printf("Notes ajoutees pour %d matieres!\n", nb_matieres);
    } else {
        printf("Aucune matiere trouvee pour cette classe!\n");
    }
}

void ajouter_note_classe_matiere() {
    int code_classe;
    int reference;
    Etudiant etudiant;
    Etre_note en;
    Matiere matiere;
    int matiere_valide = 0;
    
    printf("Code classe: ");
    scanf("%d", &code_classe);
    
    printf("Reference matiere: ");
    scanf("%d", &reference);

    FILE *f_matieres = fopen("matieres.csv", "r");
    if (f_matieres) {
        while(fscanf(f_matieres, "%d,%[^,],%d\n", 
                    &matiere.reference, matiere.libelle, 
                    &matiere.coefficient) != EOF) {
            if (matiere.reference == reference && 
                matiere_associee_classe(reference, code_classe)) {
                matiere_valide = 1;
                break;
            }
        }
        fclose(f_matieres);
    }
    
    if (!matiere_valide) {
        printf("Erreur: Matiere inexistante ou non associee a cette classe!\n");
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
    
    printf("\nSaisie des notes pour la classe %d en %s\n", code_classe, matiere.libelle);
    
    while(fscanf(f_etudiants, "%d,%[^,],%[^,],%[^,],%[^,],%d\n", 
                &etudiant.numero, etudiant.nom, etudiant.prenom, 
                etudiant.email, etudiant.date_naissance, 
                &etudiant.code) != EOF) {
        if (etudiant.code == code_classe) {
            printf("\nEtudiant: %s %s\n", etudiant.prenom, etudiant.nom);
            
            en.numero = etudiant.numero;
            en.reference = reference;
            
            en.noteCC = saisir_note_valide("Note CC");
            en.noteDS = saisir_note_valide("Note DS");
            
            fprintf(f_notes, "%d,%d,%.2f,%.2f\n", 
                    en.numero, en.reference, 
                    en.noteCC, en.noteDS);
        }
    }
    
    fclose(f_etudiants);
    fclose(f_notes);
    printf("Notes ajoutees avec succes!\n");
}

int matiere_associee_classe(int ref_matiere, int code_classe) {
    FILE *f = fopen("matiere_classe.csv", "r");
    if (!f) return 0;
    
    int ref, code;
    int trouve = 0;
    
    while (fscanf(f, "%d,%d\n", &ref, &code) == 2) {
        if (ref == ref_matiere && code == code_classe) {
            trouve = 1;
            break;
        }
    }
    
    fclose(f);
    return trouve;
}