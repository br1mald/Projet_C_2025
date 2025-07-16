#include <stdio.h>
#include "Etudiant.h"
#include <stdlib.h>

int sous_menu_etudiant(){
    int optionSousMenuEtudiant;
        etu_menu :printf("\nGestion des Etudiants\n");
        printf("\t 1. Ajout Etudiant \n \t 2. Modification Etudiant \n \t 3. Recherche Etudiant \n \t 4. Affichage des Etudiants \n \t 5. Suppression Etudiant\n \t 6. Retour au menu principal \t 7.Quitter \n");
        printf("\nVeuillez choisir votre option du Sous Menu Etudiant : ");
        scanf("%d", &optionSousMenuEtudiant);
        printf("\n");
        switch (optionSousMenuEtudiant)
        {
            case 1: printf("Ajouter un etudiant\n");
                    ajou_etudiant();
                break;
            case 2: printf("Modifier un etudiant\n");
                    modif_etudiant();
                break;
            case 3: printf("Rechercher un etudiant\n");
                    recherche_etudiant();
                break;
            case 4: printf("Affichage des etudiants\n");
                    liste_etudiant();
                break;
            case 5: printf("Supprimer un etudiant\n");
                    suppr_etudiant();
                break;
            case 6: printf("Retour au menu principal...\n");
                    return 1; // Retourne au menu principal
            case 7: printf("Au revoir!\n");
                    return 0; // Quitte le programme
            default: printf("Veuillez choisir parmi les options du sous menu Etudiant\n");
            goto etu_menu; 
        }
    return 2; // Continue dans le sous-menu Etudiant
}


int ajou_etudiant() {
    Etudiant etu;
    FILE *fichier = fopen("gestion_etudiants/file_etudiant.csv", "a");
    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return -1;
    }

    printf("=== Ajout d'un nouvel etudiant ===\n");
    printf("Prenom : ");
    scanf("%s", etu.prenom);

    printf("Nom : ");
    scanf("%s", etu.nom);

    printf("Numero : ");
    scanf("%d", &etu.numero);

    printf("Date de Naissance : \n");
    printf("Jour de Naissance : ");
    scanf("%d", &etu.date_naissance.jour);
    printf("Mois de Naissance : ");
    scanf("%d", &etu.date_naissance.mois);
    printf("Annee de Naissance : ");
    scanf("%d", &etu.date_naissance.annee);

    printf("Email : ");
    scanf("%s", etu.email);

    printf("Code : ");
    scanf("%d", &etu.code);


    if (fprintf(fichier, "%s, %s, %d, %d/%d/%d, %s, %d\n", etu.prenom, etu.nom, etu.numero, etu.date_naissance.jour, etu.date_naissance.mois, etu.date_naissance.annee, etu.email, etu.code) < 0) {
        printf("Erreur lors de l'ecriture dans le fichier.\n");
        fclose(fichier);
        return -1;
    }

    fclose(fichier);
    printf("Etudiant ajoute avec succes !\n");
    return 0;
}



int modif_etudiant(){
     int numero, trouve = 0;
    printf("Entrez le numero de l'etudiant a modifier : ");
    scanf("%d", &numero);

    FILE *fichier = fopen("gestion_etudiants/file_etudiant.csv", "r");
    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return -1;
    }

    FILE *temp = fopen("gestion_etudiants/temp.csv", "w");
    if (temp == NULL) {
        fclose(fichier);
        printf("Erreur d'ouverture du fichier temporaire.\n");
        return -1;
    }

    Etudiant etu;
    char ligne[256];
    while (fgets(ligne, sizeof(ligne), fichier)) {
        // le format est : prenom, nom, numero, jj/mm/aaaa, email, code
        if (sscanf(ligne, "%[^,], %[^,], %d, %d/%d/%d, %[^,], %d",
                   etu.prenom, etu.nom, &etu.numero,
                   &etu.date_naissance.jour, &etu.date_naissance.mois, &etu.date_naissance.annee,
                   etu.email, &etu.code) == 8) {
            if (etu.numero == numero) {
                trouve = 1;
                printf("Modification de l'etudiant %s %s\n", etu.prenom, etu.nom);
                printf("Nouveau prenom : ");
                scanf("%s", etu.prenom);
                printf("Nouveau nom : ");
                scanf("%s", etu.nom);
                printf("Nouveau jour de naissance : ");
                scanf("%d", &etu.date_naissance.jour);
                printf("Nouveau mois de naissance : ");
                scanf("%d", &etu.date_naissance.mois);
                printf("Nouvelle annee de naissance : ");
                scanf("%d", &etu.date_naissance.annee);
                printf("Nouvel email : ");
                scanf("%s", etu.email);
                printf("Nouveau code : ");
                scanf("%d", &etu.code);
            }
            fprintf(temp, "%s, %s, %d, %d/%d/%d, %s, %d\n",
                    etu.prenom, etu.nom, etu.numero,
                    etu.date_naissance.jour, etu.date_naissance.mois, etu.date_naissance.annee,
                    etu.email, etu.code);
        }
    }

    fclose(fichier);
    fclose(temp);

    remove("gestion_etudiants/file_etudiant.csv");
    rename("gestion_etudiants/temp.csv", "gestion_etudiants/file_etudiant.csv");

    if (trouve == 1) {
        printf("Modification effectuee avec succes !\n");
        return 0;
    } else {
        printf("Aucun etudiant trouve avec ce numero.\n");
        return -1;
    }

}


int suppr_etudiant(){
    FILE *fichier = fopen("gestion_etudiants/file_etudiant.csv", "r");
    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return -1;
    }
    FILE *temp = fopen("gestion_etudiants/temp.csv", "w");
    if (temp == NULL) {
        fclose(fichier);
        printf("Erreur d'ouverture du fichier temporaire.\n");
        return -1;
    }
    int numero, trouve = 0;
    printf("Entrez le numero de l'etudiant e supprimer : ");
    scanf("%d", &numero);
    Etudiant etu;
    char ligne[256];
    while (fgets(ligne, sizeof(ligne), fichier)) {
        // Supposons que le format est : prenom, nom, numero, jj/mm/aaaa, email, code
        if (sscanf(ligne, "%[^,], %[^,], %d, %d/%d/%d, %[^,], %d",
                   etu.prenom, etu.nom, &etu.numero,
                   &etu.date_naissance.jour, &etu.date_naissance.mois, &etu.date_naissance.annee,
                   etu.email, &etu.code) == 8) {
            if (etu.numero == numero) {
                trouve = 1;
                printf("Suppression de l'etudiant %s %s\n", etu.prenom, etu.nom);
                continue; // Ne pas ecrire cette ligne dans le fichier temporaire
            }
            fprintf(temp, "%s, %s, %d, %d/%d/%d, %s, %d\n",etu.prenom, etu.nom, etu.numero,
            etu.date_naissance.jour, etu.date_naissance.mois, etu.date_naissance.annee,etu.email, etu.code);         
        }
    }
    fclose(fichier);
    fclose(temp);
    remove("gestion_etudiants/file_etudiant.csv");
    rename("gestion_etudiants/temp.csv", "gestion_etudiants/file_etudiant.csv");
    if (trouve == 1) {
        printf("Etudiant supprime avec succes !\n");
        return 0;
    } else {
        printf("Aucun etudiant trouve avec le numero %d.\n", numero);
        return -1;
    }
}



int recherche_etudiant(){
   FILE *fichier = fopen("gestion_etudiants/file_etudiant.csv", "r");
    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return -1;
    }
    int numero;
    printf("Entrez le numero de l'etudiant a rechercher : ");
    scanf("%d", &numero);
    
    Etudiant etu;
    char ligne[256];
    int trouve = 0;
    
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        // Supposons que le format est : prenom, nom, numero, jj/mm/aaaa, email, code
        if (sscanf(ligne, "%[^,], %[^,], %d, %d/%d/%d, %[^,], %d",
                   etu.prenom, etu.nom, &etu.numero,
                   &etu.date_naissance.jour, &etu.date_naissance.mois, &etu.date_naissance.annee,
                   etu.email, &etu.code) == 8) {
            if (etu.numero == numero) {
                trouve = 1;
                printf("| %-12s | %-12s | %-8s | %-12s | %-25s | %-8s |\n", 
                "Prenom", "Nom", "Numero", "Naissance", "Email", "Code");
                printf("|--------------|--------------|----------|--------------|---------------------------|----------|\n");
                printf("| %-12s | %-12s | %-8d | %02d/%02d/%04d   | %-25s | %-8d |\n",
                   etu.prenom, etu.nom, etu.numero,
                   etu.date_naissance.jour, etu.date_naissance.mois, etu.date_naissance.annee,
                   etu.email, etu.code);
                break;
            }
        }
    }
    
    if (trouve == 0) {
        printf("Aucun etudiant trouve avec le numero %d.\n", numero);
    }
    
    fclose(fichier);
    printf("Recherche terminee.\n");
    return 0;
}



int liste_etudiant(){
    FILE *fichier = fopen("gestion_etudiants/file_etudiant.csv", "r");
    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return -1;
    }
    Etudiant etu;
    char ligne[256];
    printf("=== Liste des etudiants ===\n");
    printf("| %-12s | %-12s | %-8s | %-12s | %-25s | %-8s |\n", 
           "Prenom", "Nom", "Numero", "Naissance", "Email", "Code");
    printf("|--------------|--------------|----------|--------------|---------------------------|----------|\n");
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        if (sscanf(ligne, "%[^,], %[^,], %d, %d/%d/%d, %[^,], %d",
                   etu.prenom, etu.nom, &etu.numero,
                   &etu.date_naissance.jour, &etu.date_naissance.mois, &etu.date_naissance.annee,
                   etu.email, &etu.code) == 8) {
            printf("| %-12s | %-12s | %-8d | %02d/%02d/%04d   | %-25s | %-8d |\n",
                   etu.prenom, etu.nom, etu.numero,
                   etu.date_naissance.jour, etu.date_naissance.mois, etu.date_naissance.annee,
                   etu.email, etu.code);
        }
    }
    fclose(fichier);
    return 0;
}