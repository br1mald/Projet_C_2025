typedef enum {
    Licence = 1,
    Master = 2
}Niveau;

typedef struct Classe {
    int code;
    char nom[30];
    Niveau niveau;
} Classe;

typedef struct {
    int code;
    int reference;
} Se_faire;

int gestionclasses();
void add_class(Classe classes[], int* size, int max_capacity);
void remove_class(Classe classes[], int* size);
void modify_class(Classe classes[], int* size);
int search(Classe tab[], int target, int current_size);
void write_to_file(Classe classes[], int *size);
void actualize(Classe classes[], int *size);
void initialize_classes(Classe classes[], int *size);
void matiere_classe(int code, int reference, Classe classes[], int* size, Se_faire tab[], int* se_faire_size);
void initialize_se_faire(Se_faire tab[], int* se_faire_size);
