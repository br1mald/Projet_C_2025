#include <stdio.h>
#include "Etudiant.h"
#include <stdlib.h>

int sous_menu_etudiant(){
    int optionSousMenuEtudiant;
    do{
        sous_menu_etudiant : printf("Gestion des Etudiants\n");
        printf(" 1. Ajout Etudiant \n 2. Modification Etudiant \n 3. Recherche Etudiant \n 4. Affichage des Etudiants \n 5. Suppression Etudiant\n 6. Retour au menu principal\n");
        printf("Veuillez choisir votre option du Sous Menu Etudiant : ");
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
            case 6: printf("Retour au menu principal\n");
                    return 1; // Retourne au menu principal
            default: printf("Veuillez choisir parmi les options du sous menu Etudiant\n");
                        goto sous_menu_etudiant;
                break;
        }
    } while(optionSousMenuEtudiant != 6);
    return 0;
}


int ajou_etudiant() {
    Etudiant etu;
    FILE *fichier = fopen("file_etudiant.csv", "a");
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
    printf("Ann‚e de Naissance : ");
    scanf("%d", &etu.date_naissance.annee);

    printf("Email : ");
    scanf("%s", etu.email);

    printf("Code : ");
    scanf("%d", &etu.code);


    if (fprintf(fichier, "%s, %s, %d, %d/%d/%d, %s, %d\n", etu.prenom, etu.nom, etu.numero, etu.date_naissance.jour, etu.date_naissance.mois, etu.date_naissance.annee, etu.email, etu.code) < 0) {
        printf("Erreur lors de l'‚criture dans le fichier.\n");
        fclose(fichier);
        return -1;
    }

    fclose(fichier);
    printf("Etudiant ajoute avec succes !\n");
    return 0;
}



int modif_etudiant(){
     int numero, trouve = 0;
    printf("Entrez le numero de l'etudiant … modifier : ");
    scanf("%d", &numero);

    FILE *fichier = fopen("file_etudiant.csv", "r");
    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return -1;
    }

    FILE *temp = fopen("temp.csv", "w");
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
                printf("Modification de l'‚tudiant %s %s\n", etu.prenom, etu.nom);
                printf("Nouveau prenom : ");
                scanf("%s", etu.prenom);
                printf("Nouveau nom : ");
                scanf("%s", etu.nom);
                printf("Nouveau jour de naissance : ");
                scanf("%d", &etu.date_naissance.jour);
                printf("Nouveau mois de naissance : ");
                scanf("%d", &etu.date_naissance.mois);
                printf("Nouvelle ann‚e de naissance : ");
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

    remove("file_etudiant.csv");
    rename("temp.csv", "file_etudiant.csv");

    if (trouve == 1) {
        printf("Modification effectu‚e avec succŠs !\n");
        return 0;
    } else {
        printf("Aucun ‚tudiant trouv‚ avec ce num‚ro.\n");
        return -1;
    }

}


int suppr_etudiant(){
    FILE *fichier = fopen("file_etudiant.csv", "r");
    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return -1;
    }
    FILE *temp = fopen("temp.csv", "w");
    if (temp == NULL) {
        fclose(fichier);
        printf("Erreur d'ouverture du fichier temporaire.\n");
        return -1;
    }
    int numero, trouve = 0;
    printf("Entrez le numero de l'etudiant … supprimer : ");
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
                printf("Suppression de l'‚tudiant %s %s\n", etu.prenom, etu.nom);
                continue; // Ne pas ‚crire cette ligne dans le fichier temporaire
            }
            fprintf(temp, "%s, %s, %d, %d/%d/%d, %s, %d\n",etu.prenom, etu.nom, etu.numero,
            etu.date_naissance.jour, etu.date_naissance.mois, etu.date_naissance.annee,etu.email, etu.code);         
        }
    }
    fclose(fichier);
    fclose(temp);
    remove("file_etudiant.csv");
    rename("temp.csv", "file_etudiant.csv");
    if (trouve == 1) {
        printf("Etudiant supprim‚ avec succŠs !\n");
        return 0;
    } else {
        printf("Aucun ‚tudiant trouv‚ avec le num‚ro %d.\n", numero);
        return -1;
    }
}



int recherche_etudiant(){
   FILE *fichier = fopen("file_etudiant.csv", "r");
    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return -1;
    }
    int numero;
    printf("Entrez le numero de l'etudiant … rechercher : ");
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
        printf("Aucun ‚tudiant trouv‚ avec le num‚ro %d.\n", numero);
    }
    
    fclose(fichier);
    printf("Recherche termin‚e.\n");
    return 0;
}



int liste_etudiant(){
    FILE *fichier = fopen("file_etudiant.csv", "r");
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