# Projet de Langage C

Ce projet vise à la création d'un programme de gestion de classes, matières, étudiants et notes.

## Fonctionnalités principales

- Ajouter, modifier et supprimer des classes, matières, étudiants et notes
- Associer des matières à des classes
- Attribuer des notes aux étudiants dans différentes matières
- Afficher les différentes données enregistrées

## Structure du projet

- `main.c`: point d'entrée du programme
- `gestion_classes.c`: fonctions qui se chargent de la gestion des classes (création, modification, suppression, affichage)
- `se_faire.c`: fonctions qui permettent d'associer des classes et des matières
- `matiere.c`: fonctions qui se chargent de la gestion des matières (création, modification, suppression, affichage)
- `imple_etudiant.c`: fonctions qui se chargent de la gestion des étudiants (création, modification, suppression, affichage) et de l'attribution de classes aux étudiants
- `etre_note.c`: fonctions qui se chargent de la gestion des notes (attribution à des étudiants individuels dans une ou plusieurs matières ou aux élèves d'une classe dans une matière et affichage des notes)

## Compilation et exécution

- **Sur Mac/Linux**: `gcc main.c gestion_classes/gestion_classes.c gestion_etudiants/imple_etudiant.c gestion_matiere/matiere.c gestion_notes/etre_note.c gestion_classes/se_faire.c -o gestion_scolaire && ./gestion_scolaire`
- **Sur Windows**: `gcc main.c gestion_classes/gestion_classes.c gestion_etudiants/imple_etudiant.c gestion_matiere/matiere.c gestion_notes/etre_note.c gestion_classes/se_faire.c -o gestion_scolaire.exe && gestion_scolaire.exe`

