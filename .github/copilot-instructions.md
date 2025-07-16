# Copilot Instructions for Projet_C_2025

## Project Overview
This project is a C-based student/class/subject/grade management system, organized into modular directories for each domain:
- **gestion_etudiants/**: Student management (add, modify, search, list, delete)
- **gestion_des_classes/**: Class management (add, modify, search, list, delete)
- **gestion_matiere/**: Subject management (add, modify, search, list, delete)
- **gestion_notes/**: Grade management (add, modify, search, list, delete, statistics)

Each module uses CSV files for persistent storage. Data flows between modules via file reads/writes, not direct function calls.

## Key Files & Structure
- `main.c` and `test_prog_c/main.c`: Entry points with menu-driven navigation
- Each `gestion_*` directory contains its own `.c` and `.h` files, plus CSV data files
- CSV file formats are module-specific (see code for field order)

## Developer Workflows
- **Build**: No build system; compile manually. Example:
  ```sh
  gcc -o gestion_notes.exe main.c gestion_des_classes/gestion_classes.c gestion_etudiants/imple_etudiant.c gestion_matiere/matiere.c gestion_notes/etre_note.c
  ```
  Adjust file list as needed for your entry point.
- **Run**: Execute the resulting binary (e.g., `./gestion_notes.exe`)
- **Test**: No automated tests; test via interactive menu
- **Debug**: Use `printf` debugging; no advanced tooling

## Project Conventions & Patterns
- **Menu navigation**: All user interaction is via text menus and `scanf`/`printf` loops
- **Data persistence**: All data is stored in CSV files in the relevant subdirectory
- **Cross-module access**: Each module reads/writes only its own CSVs, except for grade management, which may read student/class/subject files for validation
- **Error handling**: On file errors, print a message and return/exit
- **Naming**: French is used for variable/function names and user prompts
- **No dynamic memory**: All arrays are statically sized

## Integration Points
- **CSV file contracts**: Changing a CSV format requires updating all code that reads/writes it
- **Grade management**: Relies on student, class, and subject CSVs for validation and reporting

## Examples
- To add a student: Use the menu in `gestion_etudiants/imple_etudiant.c`, which appends to `gestion_etudiants/file_etudiant.csv`
- To add a note: Use the menu in `gestion_notes/etre_note.c`, which validates existence in other CSVs before writing

## Tips for AI Agents
- Always check for file existence before reading/writing
- Follow the menu-driven flow for all user actions
- When adding new features, mirror the structure of existing modules
- Keep all data operations in the relevant module's directory

---
_Last updated: 2025-07-16_
