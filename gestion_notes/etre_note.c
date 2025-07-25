#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "etre_note.h"
#include "../gestion_matiere/matiere.h"
#include "../gestion_classes/gestion_classes.h"
#include "../gestion_etudiants/Etudiant.h"
#define FICHIER_ETRE_NOTE "gestion_notes/etre_note.csv"
#define NOTE_MIN 0.0f
#define NOTE_MAX 20.0f

int gestion_notes()
{
    char continuer[5] = "oui";
    int option;
    while (strcmp(continuer, "non") != 0 && strcmp(continuer, "Non") != 0) {
        notes_menu: printf("\n=== GESTION DES NOTES ===\n");
        printf("1. Ajouter note etudiant-matiere\n");
        printf("2. Ajouter note etudiant-toutes matieres\n");
        printf("3. Ajouter note classe-matiere\n");
        printf("4. Modifier note\n");
        printf("5. Supprimer note\n");
        printf("6. Afficher note etudiant-matiere\n");
        printf("7. Afficher note classe-matiere\n");
        printf("8. Afficher note etudiant-toutes matieres\n");
        printf("9. Retour au menu principal\n");
        printf("10. Quitter le programme\n");
        printf("\nVeuillez choisir une option du sous menu note: ");
        scanf("%d", &option);

        switch(option) {
            case 1: ajouter_note_etudiant_matiere(); break;
            case 2: ajouter_note_etudiant_toutes_matieres(); break;
            case 3: ajouter_note_classe_matiere(); break;
            case 4: modifier_note(); break;
            case 5: supprimer_note(); break;
            case 6: afficher_note_etudiant_matiere(); break;
            case 7: afficher_note_classe_matiere(); break;
            case 8: afficher_note_etudiant_toutes_matieres(); break;
            case 9: printf("Retour au menu principal...\n");
                return 1; // Retour au menu principal
            case 10:
                printf("Au revoir!\n");
                exit(0);
            default: printf("Option invalide!\n"); goto notes_menu; // Retourne au menu des notes
        }
        printf("Souhaitez vous continuer dans le sous-menu Gestion des notes?\n");
        scanf("%s", continuer);
    }
    return 1;
}

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
    matiere matiere;
    int code;
    int etudiant_existe = 0, matiere_existe = 0;
    char choix;

    do {
        etudiant_existe = 0;
        printf("Vueillez saisir le Numero de l'etudiant: ");
        scanf("%d", &note.numero);

        FILE *f_etudiants = fopen("gestion_etudiants/file_etudiant.csv", "r");
        if (f_etudiants) {
            while(fscanf(f_etudiants, "%[^,], %[^,], %d, %d/%d/%d, %[^,], %d\n",
                etudiant.prenom, etudiant.nom, &etudiant.numero,
                 &etudiant.date_naissance.jour,&etudiant.date_naissance.mois,&etudiant.date_naissance.annee,etudiant.email,
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
            if (choix != 'o' && choix != 'O') return;// sortie de la fonction si le choix est different de zero
        }
    } while (!etudiant_existe);

    do {
        matiere_existe = 0;
        printf("Entrer la Reference de la matiere: ");
        scanf("%d", &note.reference);

        FILE *f_matieres = fopen("gestion_matiere/matiere.csv", "r");
        if (f_matieres) {
            while(fscanf(f_matieres, "%d %s %hd\n",
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
            if (choix == 'o' || choix == 'O') {
                continue;
            } else {
                return;
            }
        }
    } while (!matiere_existe);

    if (!matiere_associee_classe(note.reference, etudiant.code)) {
        printf("Erreur: Cette matiere n'est pas associee a la classe de l'etudiant!\n");
        return;
    }

    // Vérification de l'existence d'une note pour ce couple
    int existe_deja = 0;
    FILE *f_notes_tmp = fopen(FICHIER_ETRE_NOTE, "r");
    if (f_notes_tmp) {
        int num_tmp, ref_tmp;
        float CC_tmp, DS_tmp;
        while (fscanf(f_notes_tmp, "%d,%d,%f,%f\n", &num_tmp, &ref_tmp, &CC_tmp, &DS_tmp) == 4) {
            if (num_tmp == note.numero && ref_tmp == note.reference) {
                existe_deja = 1;
                break;
            }
        }
        fclose(f_notes_tmp);
    }
    if (existe_deja) {
        printf("Erreur : une note existe déjà pour cet étudiant et cette matière.\n");
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
void afficher_note_classe_matiere() {
    int code_classe;
    int reference;
    Etudiant etudiant;
    Etre_note note;
    matiere matiere;
    int trouve = 0;
    float moyenne_classe = 0;
    int nb_etudiants = 0;

    printf("Code de la classe: ");
    scanf("%d", &code_classe);

    printf("Reference de la matiere: ");
    scanf("%d", &reference);

    // Vérifier l'association classe-matière
    if (!matiere_associee_classe(reference, code_classe)) {
        printf("Erreur: Cette matiere n'est pas associee a cette classe!\n");
        return;
    }

    // Récupérer le libellé de la matière
    FILE *f_matieres = fopen("gestion_matiere/matiere.csv", "r");
    char libelle_matiere[100] = "Inconnu";
    int coefficient = 0;
    if (f_matieres) {
        while(fscanf(f_matieres, "%d %s %hd \n",
                    &matiere.reference, matiere.libelle,
                    &matiere.coefficient) != EOF) {
            if (matiere.reference == reference) {
                strcpy(libelle_matiere, matiere.libelle);
                coefficient = matiere.coefficient;
                break;
            }
        }
        fclose(f_matieres);
    }

    printf("\n=== NOTES CLASSE %d - %s ===\n", code_classe, libelle_matiere);

    // En-tête du tableau
    printf("+------+-------------------------+----------+----------+------------+\n");
    printf("| ID   |  Prenom    Nom          | Note CC  | Note DS  | Moyenne    |\n");
    printf("+------+-------------------------+----------+----------+------------+\n");

    // Parcourir les étudiants de la classe
    FILE *f_etudiants = fopen("gestion_etudiants/file_etudiant.csv", "r");
    if (!f_etudiants) {
        printf("Erreur: Impossible d'ouvrir le fichier des etudiants!\n");
        return;
    }

    while(fscanf(f_etudiants, "%[^,], %[^,], %d, %d/%d/%d, %[^,], %d\n",
                etudiant.prenom, etudiant.nom, &etudiant.numero,
                &etudiant.date_naissance.jour, &etudiant.date_naissance.mois, &etudiant.date_naissance.annee, etudiant.email,
                &etudiant.code) != EOF) {
        if (etudiant.code == code_classe) {
            // Chercher les notes de cet étudiant
            FILE *f_notes = fopen(FICHIER_ETRE_NOTE, "r");
            int etudiant_trouve = 0;

            if (f_notes) {
                while(fscanf(f_notes, "%d,%d,%f,%f\n",
                            &note.numero, &note.reference,
                            &note.noteCC, &note.noteDS) != EOF) {
                    if (note.numero == etudiant.numero && note.reference == reference) {
                        float moyenne = calculer_moyenne(note.noteCC, note.noteDS);
                        printf("| %-4d | %-9s %-13s | %-8.2f | %-8.2f | %-10.2f |\n",
                               etudiant.numero, etudiant.prenom, etudiant.nom,
                               note.noteCC, note.noteDS, moyenne);
                        moyenne_classe += moyenne;
                        nb_etudiants++;
                        trouve = 1;
                        etudiant_trouve = 1;
                        break;
                    }
                }
                fclose(f_notes);
            }

            if (!etudiant_trouve) {
                printf("| %-4d | %-6s %7s |  %-7s | %-8s | %-10s |\n",
                       etudiant.numero, etudiant.prenom, etudiant.nom,
                       "N/A", "N/A", "N/A");
            }
        }
    }

    fclose(f_etudiants);

    printf("+------+-------------------------+----------+----------+------------+\n");

    if (trouve) {
        printf("| Moyenne classe: %-36.2f              |\n", moyenne_classe / nb_etudiants);
        printf("+-------------------------------------------------------------------+\n");
    } else {
        printf("| Aucune note trouvee pour cette classe et cette matiere            |\n");
        printf("+-------------------------------------------------------------------+\n");
    }
}

void afficher_note_etudiant_matiere() {
    int numero;
    int reference;
    Etre_note en;
    Etudiant etudiant;
    matiere matiere;
    int trouve = 0;

    printf("Saisir le Numero de l'etudiant: ");
    scanf("%d", &numero);

    printf("Saisir la Reference de la matiere: ");
    scanf("%d", &reference);

    // Récupérer les infos étudiant
    int etudiant_trouve = 0;
    FILE *f_etud = fopen("gestion_etudiants/file_etudiant.csv", "r");
    if (f_etud) {
        while(fscanf(f_etud, "%[^,], %[^,], %d, %d/%d/%d, %[^,], %d\n",
                etudiant.prenom, etudiant.nom, &etudiant.numero,
                &etudiant.date_naissance.jour, &etudiant.date_naissance.mois, &etudiant.date_naissance.annee, etudiant.email,
                &etudiant.code) != EOF) {
            if (etudiant.numero == numero) {
                etudiant_trouve = 1;
                break;
            }
        }
        fclose(f_etud);
    }

    // Récupérer le libellé de la matière
    char libelle_matiere[100] = "Inconnu";
    FILE *f_mat = fopen("gestion_matiere/matiere.csv", "r");
    if (f_mat) {
        while(fscanf(f_mat, "%d %s %hd \n",
                    &matiere.reference, matiere.libelle,
                    &matiere.coefficient) != EOF) {
            if (matiere.reference == reference) {
                strcpy(libelle_matiere, matiere.libelle);
                break;
            }
        }
        fclose(f_mat);
    }

    FILE *fichier = fopen(FICHIER_ETRE_NOTE, "r");
    if (!fichier) {
        printf("Aucune note enregistree!\n");
        return;
    }

    printf("\n=== NOTES ETUDIANT ===\n");
    printf("Etudiant: %s %s (ID: %d)\n", etudiant.prenom, etudiant.nom, numero);
    printf("Matiere: %s (Ref: %d)\n\n", libelle_matiere, reference);

    // En-tête du tableau
    printf("+----------+----------+------------+---------+\n");
    printf("| Note CC  | Note DS  | Moyenne    | Coeff   |\n");
    printf("+----------+----------+------------+---------+\n");

    while(fscanf(fichier, "%d,%d,%f,%f\n",
                 &en.numero, &en.reference,
                 &en.noteCC, &en.noteDS) != EOF) {
        if (en.numero == numero && en.reference == reference) {
            // Recherche du coefficient à chaque note
            int coeff = 0;
            FILE *f_mat = fopen("gestion_matiere/matiere.csv", "r");
            if (f_mat) {
                int ref_tmp;
                char libelle_tmp[100];
                int coeff_tmp;
                while(fscanf(f_mat, "%d %s %d", &ref_tmp, libelle_tmp, &coeff_tmp) == 3) {
                    if (ref_tmp == reference) {
                        coeff = coeff_tmp;
                        break;
                    }
                }
                fclose(f_mat);
            }
            float moyenne = calculer_moyenne(en.noteCC, en.noteDS);
            printf("| %-8.2f | %-8.2f | %-10.2f | %-7d |\n",
                   en.noteCC, en.noteDS, moyenne, coeff);
            trouve = 1;
        }
    }

    printf("+----------+----------+------------+---------+\n");

    if (!trouve) {
        printf("| Aucune note trouvee pour cette combinaison       |\n");
        printf("+---------------------------------------------------+\n");
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

    printf("Saisir le Numeo de l'etudiant: ");
    scanf("%d", &numero);

    printf("Saisir la Reference de la matiere: ");
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

    printf("Veuillez entrer le Numero de l'etudiant: ");
    scanf("%d", &numero);

    printf("Saisir la Reference de la matiere: ");
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
    matiere matiere;
    int trouve = 0;
    float moyenne_generale = 0;
    int nb_matieres = 0;
    int etudiant_trouve = 0;

    printf("Numero etudiant: ");
    scanf("%d", &numero);

    FILE *f_etud = fopen("gestion_etudiants/file_etudiant.csv", "r");
    if (f_etud) {
        while(fscanf(f_etud, "%[^,], %[^,], %d, %d/%d/%d, %[^,], %d\n",
                etudiant.prenom, etudiant.nom, &etudiant.numero,
                &etudiant.date_naissance.jour, &etudiant.date_naissance.mois, &etudiant.date_naissance.annee, etudiant.email,
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

    printf("\n=== TOUTES LES NOTES - %s %s (ID: %d) ===\n",
           etudiant.prenom, etudiant.nom, numero);

    // En-tête du tableau
    printf("+------------+-------------------------+----------+----------+------------+\n");
    printf("| Reference  | Matiere                 | Note CC  | Note DS  | Moyenne    |\n");
    printf("+------------+-------------------------+----------+----------+------------+\n");

    while(fscanf(f_notes, "%d,%d,%f,%f\n",
                 &en.numero, &en.reference,
                 &en.noteCC, &en.noteDS) != EOF) {
        if (en.numero == numero) {
            FILE *f_mat = fopen("gestion_matiere/matiere.csv", "r");
            char libelle[100] = "Inconnu";
            int coefficient = 0;
            if (f_mat) {
                while(fscanf(f_mat, "%d %s %hd \n",
                            &matiere.reference, matiere.libelle,
                            &matiere.coefficient) != EOF) {
                    if (matiere.reference == en.reference) {
                        strcpy(libelle, matiere.libelle);
                        coefficient = matiere.coefficient;
                        break;
                    }
                }
                fclose(f_mat);
            }

            float moyenne = calculer_moyenne(en.noteCC, en.noteDS);
            printf("| %-10d | %-23s | %-8.2f | %-8.2f | %-10.2f |\n",
                   en.reference, libelle,
                   en.noteCC, en.noteDS, moyenne);
            moyenne_generale += moyenne * coefficient;
            nb_matieres += coefficient;
            trouve = 1;
        }
    }

    fclose(f_notes);

    printf("+------------+-------------------------+----------+----------+------------+\n");

    if (trouve) {
        if (nb_matieres > 0) {
            printf("| Moyenne generale: %-40.2f              |\n", moyenne_generale / nb_matieres);
            printf("+-------------------------------------------------------------------------+\n");
        }
    } else {
        printf("| Aucune note trouvee pour cet etudiant                                   |\n");
        printf("+-------------------------------------------------------------------------+\n");
    }
}


void ajouter_note_etudiant_toutes_matieres() {
    int numero;
    Etudiant etudiant;
    matiere matiere;
    Etre_note en;
    int etudiant_trouve = 0;
    int nb_matieres = 0;

    printf("Numero etudiant: ");
    scanf("%d", &numero);

    FILE *f_etud = fopen("gestion_etudiants/file_etudiant.csv", "r");
    if (f_etud) {
        while(fscanf(f_etud, "%[^,], %[^,], %d, %d/%d/%d, %[^,], %d\n",
                etudiant.prenom, etudiant.nom, &etudiant.numero,
                &etudiant.date_naissance.jour, &etudiant.date_naissance.mois, &etudiant.date_naissance.annee, etudiant.email,
                &etudiant.code ) != EOF) {
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

    FILE *f_mat = fopen("gestion_matiere/matiere.csv", "r");
    FILE *f_notes = fopen(FICHIER_ETRE_NOTE, "a");

    if (!f_mat || !f_notes) {
        printf("Erreur d'ouverture des fichiers!\n");
        if (f_mat) fclose(f_mat);
        if (f_notes) fclose(f_notes);
        return;
    }

    printf("\nSaisie des notes pour %s %s\n", etudiant.prenom, etudiant.nom);

    while(fscanf(f_mat, "%d %s %hd \n",
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
    matiere matiere;
    int matiere_valide = 0;

    printf("Code classe: ");
    scanf("%d", &code_classe);

    printf("Reference matiere: ");
    scanf("%d", &reference);

    FILE *f_matieres = fopen("gestion_matiere/matiere.csv", "r");
    if (f_matieres) {
        while(fscanf(f_matieres, "%d %s %hd \n",
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

    FILE *f_etudiants = fopen("gestion_etudiants/file_etudiant.csv", "r");
    FILE *f_notes = fopen(FICHIER_ETRE_NOTE, "a");

    if (!f_etudiants || !f_notes) {
        printf("Erreur d'ouverture des fichiers!\n");
        if (f_etudiants) fclose(f_etudiants);
        if (f_notes) fclose(f_notes);
        return;
    }

    printf("\nSaisie des notes pour la classe %d en %s\n", code_classe, matiere.libelle);

    while(fscanf(f_etudiants, "%[^,], %[^,], %d, %d/%d/%d, %[^,], %d\n",
                etudiant.prenom, etudiant.nom, &etudiant.numero,
                &etudiant.date_naissance.jour, &etudiant.date_naissance.mois, &etudiant.date_naissance.annee, etudiant.email,
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
    FILE *f = fopen("gestion_classes/se_faire.csv", "r");
    if (!f) return 0;

    int ref, code;
    int trouve = 0;

    while (fscanf(f, "%d,%d\n", &code, &ref) == 2) {
        if (ref == ref_matiere && code == code_classe) {
            trouve = 1;
            break;
        }
    }

    fclose(f);
    return trouve;
}
