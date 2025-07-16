# Copilot Instructions for AI Coding Agents

## Project Overview
This is a modular C project for managing students, classes, subjects, and grades. Data is persisted in CSV files, and each domain (students, classes, subjects, grades) is managed in its own directory/module.

### Major Components
- `gestion_etudiants/`: Student management (`Etudiant` struct, file: `file_etudiant.csv`)
- `gestion_des_classes/`: Class management (`Classe` struct, file: `classes.csv`)
- `gestion_matiere/`: Subject management (`matiere` struct, file: `matiere.csv`)
- `gestion_notes/`: Grade management (`Etre_note` struct, file: `etre_note.csv`)
- `main.c`: Entry point, coordinates user interaction and module calls

## Data Flow & Patterns
- All persistent data is stored in CSV files, one per module.
- Each module provides functions to read/write its CSV, using `fscanf`/`fprintf` with strict format specifiers (e.g., `%hd` for `short int`).
- File paths are relative and hardcoded per module (e.g., `gestion_etudiants/file_etudiant.csv`).
- Date fields are stored as `d/m/yyyy` strings and parsed as such.

## Build & Debug Workflow
- Build with: `gcc main.c gestion_*/**/*.c -o gestion_notes.exe`
- Fix all warnings, especially format specifiers for `short int` (`%hd`) and string arrays (`%s` without `&`).
- Run with: `./gestion_notes.exe`
- No automated tests; manual testing via CLI.

## Project-Specific Conventions
- Use `short int` for coefficients and always use `%hd` in format strings.
- Do not use `&` with string arrays in `scanf`/`fscanf`.
- CSV files must match struct field order exactly.
- Each module is responsible for its own data file and should not access others directly.
- All user input/output is via the console; no GUI or web integration.

## Key Files & Examples
- `gestion_etudiants/Etudiant.h`, `gestion_etudiants/imple_etudiant.c`: Student struct and logic
- `gestion_matiere/matiere.h`, `gestion_matiere/matiere.c`: Subject struct and logic
- `gestion_notes/etre_note.h`, `gestion_notes/etre_note.c`: Grade struct and logic
- `main.c`: Shows how modules are orchestrated

## Integration Points
- Data is linked by IDs (e.g., student ID, subject ID) across CSVs, but no foreign key enforcement.
- Adding/modifying grades requires reading both student and subject files for validation.

## Example: Reading a `short int` from CSV
```c
fscanf(file, "%[^,],%hd\n", matiere.nom, &matiere.coef);
```

## When in Doubt
- Check the relevant module's `.h` and `.c` files for struct and function definitions.
- Ensure all file paths and format specifiers match the conventions above.

---

_If any section is unclear or missing, please provide feedback for further refinement._
