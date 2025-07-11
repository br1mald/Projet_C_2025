
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "etre_note.h"
#include "matiere.h"
#include "classe.h"
#include "etudiant.h"

// Fonction calculer_moyenne
float calculer_moyenne(float noteCC, float noteDS) {
    return (noteCC * 0.3f) + (noteDS * 0.7f); // 30% CC, 70% DS
}

// Fonction matiere_associee_classe
int matiere_associee_classe(const char* ref_matiere, int code_classe) {
    FILE *f = fopen("matiere_classe.csv", "r");
    if (!f) return 0;
    
    char ref[15];
    int code;
    int trouve = 0;
    
    while (fscanf(f, "%[^,],%d\n", ref, &code) != EOF) {
        if (strcmp(ref, ref_matiere) == 0 && code == code_classe) {
            trouve = 1;
            break;
        }
    }
    
    fclose(f);
    return trouve;
}

#define FICHIER_ETRE_NOTE "etre_note.csv"
#define NOTE_MIN 0.0f
#define NOTE_MAX 20.0f //20.0 → double (par défaut) 20.0f → float

int valider_note(float note) {
    return (note >= NOTE_MIN) && (note <= NOTE_MAX);
}

float saisir_note_valide(const char* message)
{
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
    Note note;
    Etudiant etudiant;
    Matiere matiere;
    int etudiant_existe = 0, matiere_existe = 0;
    char choix;
    
    // Saisie et vérification de l'étudiant
    do {
        etudiant_existe = 0;
        printf("Veuillez saisir un Numero etudiant: ");
        scanf("%d", &note.numero);
        
        FILE *f_etudiants = fopen("etudiants.csv", "r");
        if (f_etudiants) {
            while(fscanf(f_etudiants, "%d,%[^,],%[^,],%[^,],%[^,],%d\n", 
                        &etudiant.numero, 
                        etudiant.nom, 
                        etudiant.prenom, 
                        etudiant.email, 
                        etudiant.date_naissance, 
                        &etudiant.code_classe) != EOF) {
                if (etudiant.numero == note.numero) {
                    etudiant_existe = 1;
                    break;
                }
            }
            fclose(f_etudiants);
        }
        
        if (!etudiant_existe) {
            printf("Erreur: Etudiant inexistant!\n");
            printf("Voulez-vous resaisir le numero etudiant? (o/n): ");
            scanf(" %c", &choix);
            if (choix != 'o' && choix != 'O') {
                return;
            }
        }
    } while (!etudiant_existe);
    
    // Saisie et vérification de la matière
    do {
        matiere_existe = 0;
        printf("Veuillez entrer la Reference de la matiere: ");
        scanf("%d", &note.reference);
        
        FILE *f_matieres = fopen("matiere.csv", "r");
        if (f_matieres) {
            while(fscanf(f_matieres, "%[^,],%[^,],%d\n", 
                        matiere.reference, 
                        matiere.libelle, 
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
            printf("Voulez-vous resaisir la reference de la matiere? (o/n): ");
            scanf(" %c", &choix);
            if (choix != 'o' && choix != 'O') {
                return;
            }
        }
    } while (!matiere_existe);
    
    // Saisie des notes
    note.noteCC = saisir_note_valide("Note CC");
    note.noteDS = saisir_note_valide("Note DS");
    
    // Enregistrement
    FILE *f_notes = fopen(FICHIER_NOTES, "a");
    if (f_notes) {
        fprintf(f_notes, "%d,%d,%.2f,%.2f\n", 
                note.numero, 
                note.reference, 
                note.noteCC, 
                note.noteDS);
        fclose(f_notes);
        printf("Note ajoutee avec succes!\n");
    } else {
        printf("Erreur lors de l'enregistrement!\n");
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

    // Vérifier que l'étudiant existe et récupérer sa classe
    FILE *f_etud = fopen("etudiants.csv", "r");
    if (f_etud) {
        while(fscanf(f_etud, "%d,%[^,],%[^,],%[^,],%[^,],%d\n", 
                    &etudiant.numero, 
                    etudiant.nom, 
                    etudiant.prenom, 
                    etudiant.email, 
                    etudiant.date_naissance, 
                    &etudiant.code_classe) != EOF) {
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

    // Ouvrir le fichier des matières et le fichier des relations
    FILE *f_mat = fopen("matieres.csv", "r");
    FILE *f_notes = fopen(FICHIER_ETRE_NOTE, "a");

    if (!f_mat || !f_notes) {
        printf("Erreur d'ouverture des fichiers!\n");
        if (f_mat) fclose(f_mat);
        if (f_notes) fclose(f_notes);
        return;
    }

    printf("\nSaisie des notes pour %s %s\n", etudiant.prenom, etudiant.nom);

    // Parcourir toutes les matières associées à la classe de l'étudiant
    while(fscanf(f_mat, "%[^,],%[^,],%d\n", 
                matiere.reference, 
                matiere.libelle, 
                &matiere.coefficient) != EOF) {
        // Vérifier si la matière est associée à la classe de l'étudiant
        if (matiere_associee_classe(matiere.reference, etudiant.code_classe)) {
            printf("\nMatiere: %s (Coeff: %d)\n", matiere.libelle, matiere.coefficient);
            
            en.numero_etudiant = numero;
            strcpy(en.reference_matiere, matiere.reference);
            
            en.noteCC = saisir_note_valide("Note CC");
            en.noteDS = saisir_note_valide("Note DS");
            
            fprintf(f_notes, "%d,%s,%.2f,%.2f\n", 
                    en.numero_etudiant, 
                    en.reference_matiere, 
                    en.noteCC, 
                    en.noteDS);
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
    char reference_matiere[15];
    Etudiant etudiant;
    Etre_note en;
    
    printf("Veuillez saisir le Code de la classe: ");
    scanf("%d", &code_classe);
    
    printf("Etrer la Reference de la matiere: ");
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
void afficher_note_etudiant_matiere() {
    int numero;
    int reference;
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
    
    printf("\n=== Notes de l'etudiant %d dans %s ===\n", numero, reference);
    
    while(fscanf(fichier, "%d,%[^,],%f,%f\n", 
                 &en.numero_etudiant, 
                 en.reference_matiere, 
                 &en.noteCC, 
                 &en.noteDS) != EOF) {
        if (en.numero == numero && 
            en.reference == reference) {
            float moyenne = calculer_moyenne(en.noteCC, en.noteDS);
            printf("CC: %.2f | DS: %.2f | Moyenne: %.2f\n", 
                   en.noteCC, 
                   en.noteDS, 
                   moyenne);
            trouve = 1;
        }
    }
    
    if (!trouve) {
        printf("Aucune note trouvee pour cette combinaison etudiant-matiere!\n");
    }
    
    fclose(fichier);
}

void afficher_note_etudiant_toutes_matieres() {
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
                 &en.numero, 
                 en.reference, 
                 &en.noteCC, 
                 &en.noteDS) != EOF) {
        if (en.numero == numero) {
            float moyenne = (en.noteCC + en.noteDS) / 2;
            printf("Matiere: %s | CC: %.2f | DS: %.2f | Moyenne: %.2f\n", 
                   en.reference, 
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

void afficher_note_etudiant_classe() {
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
        printf("Aucune note enregistree!\n");
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
        printf("Données invalides!\n");
    }
    
    fclose(fichier);
}




//Fonction pour modifier une relation existante

void modifier_note() {
    int numero;
    char reference[15];
    Etre_note en;
    int trouve = 0;
    FILE *fichier = fopen(FICHIER_ETRE_NOTE, "r");
    FILE *temp = fopen("temp.csv", "w");

    printf("Numero etudiant: ");
    scanf("%d", &numero);
    
    printf("Reference matiere: ");
    scanf("%s", reference);

    if (!fichier || !temp) {
        printf("Erreur d'ouverture des fichiers!\n");
        if (fichier) fclose(fichier);
        if (temp) fclose(temp);
        return;
    }

    while(fscanf(fichier, "%d,%[^,],%f,%f\n", 
               &en.numero, 
               en.reference, 
               &en.noteCC, 
               &en.noteDS) != EOF) {
        if (en.numero == numero && 
            en.reference == reference) {
            printf("Anciennes notes - CC: %.2f, DS: %.2f\n", en.noteCC, en.noteDS);
            en.noteCC = saisir_note_valide("Nouvelle note CC");
            en.noteDS = saisir_note_valide("Nouvelle note DS");
            trouve = 1;
        }
        fprintf(temp, "%d,%s,%.2f,%.2f\n", 
                en.numero, 
                en.reference, 
                en.noteCC, 
                en.noteDS);
    }

    fclose(fichier);
    fclose(temp);

    if (trouve) {
        remove(FICHIER_ETRE_NOTE);
        rename("temp.csv", FICHIER_ETRE_NOTE);
        printf("Relation modifiee avec succes!\n");
    } else {
        remove("temp.csv");
        printf("Aucune relation trouvee!\n");
    }
}

void supprimer_note() {
    int numero;
    char reference[15];
    Etre_note en;
    int trouve = 0;
    FILE *fichier = fopen(FICHIER_ETRE_NOTE, "r");
    FILE *temp = fopen("temp.csv", "w");

    printf("Numero etudiant: ");
    scanf("%d", &numero);
    
    printf("Reference matiere: ");
    scanf("%s", reference);

    if (!fichier || !temp) {
        printf("Erreur d'ouverture des fichiers!\n");
        if (fichier) fclose(fichier);
        if (temp) fclose(temp);
        return;
    }

    while(fscanf(fichier, "%d,%[^,],%f,%f\n", 
               &en.numero, 
               en.reference_matiere, 
               &en.noteCC, 
               &en.noteDS) != EOF) {
        if (en.numero == numero && 
            en.reference == reference) {
            printf("Relation supprimee: %d %s (CC: %.2f, DS: %.2f)\n", 
                   en.numero, 
                   en.reference, 
                   en.noteCC, 
                   en.noteDS);
            trouve = 1;
        } else {
            fprintf(temp, "%d,%s,%.2f,%.2f\n", 
                    en.numero, 
                    en.reference, 
                    en.noteCC, 
                    en.noteDS);
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
        printf("Aucune relation trouvee!\n");
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

    // Vérifier que l'étudiant existe et récupérer sa classe
    FILE *f_etud = fopen("etudiants.csv", "r");
    if (f_etud) {
        while(fscanf(f_etud, "%d,%[^,],%[^,],%[^,],%[^,],%d\n", 
                    &etudiant.numero, 
                    etudiant.nom, 
                    etudiant.prenom, 
                    etudiant.email, 
                    etudiant.date_naissance, 
                    &etudiant.code_classe) != EOF) {
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

    // Ouvrir le fichier des matières et le fichier des relations
    FILE *f_mat = fopen("matieres.csv", "r");
    FILE *f_notes = fopen(FICHIER_ETRE_NOTE, "a");

    if (!f_mat || !f_notes) {
        printf("Erreur d'ouverture des fichiers!\n");
        if (f_mat) fclose(f_mat);
        if (f_notes) fclose(f_notes);
        return;
    }

    printf("\nSaisie des notes pour %s %s\n", etudiant.prenom, etudiant.nom);

    // Parcourir toutes les matières associées à la classe de l'étudiant
    while(fscanf(f_mat, "%[^,],%[^,],%d\n", 
                matiere.reference, 
                matiere.libelle, 
                &matiere.coefficient) != EOF) {
        // Vérifier si la matière est associée à la classe de l'étudiant
        if (matiere_associee_classe(matiere.reference, etudiant.code_classe)) {
            printf("\nMatiere: %s (Coeff: %d)\n", matiere.libelle, matiere.coefficient);
            
            en.numero = numero;
            strcpy(en.reference, matiere.reference);
            
            en.noteCC = saisir_note_valide("Note CC");
            en.noteDS = saisir_note_valide("Note DS");
            
            fprintf(f_notes, "%d,%s,%.2f,%.2f\n", 
                    en.numero, 
                    en.reference, 
                    en.noteCC, 
                    en.noteDS);
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


