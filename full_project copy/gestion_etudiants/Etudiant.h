#ifndef ETUDIANT_H
    #define ETUDIANT_H
#endif 

typedef struct{
    int jour;
    int mois;
    int annee;
}Date;

typedef struct Etudiant{
    int numero;
    char nom[50];
    char prenom[50];
    char email[100];
    Date date_naissance;
    int code;
}Etudiant;


int ajou_etudiant();
int modif_etudiant();
int suppr_etudiant();
int recherche_etudiant();
int liste_etudiant();
int sous_menu_etudiant();