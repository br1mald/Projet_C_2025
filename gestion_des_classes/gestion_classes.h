#include <stdio.h>
typedef enum {
    Licence = 1,
    Master = 2
}Niveau;

typedef struct Classe {
    int code;
    char nom[26];
    Niveau niveau;
} Classe;

void add_class(Classe classes[], int* size, int max_capacity);
void remove_class(Classe classes[], int* size);
void modify_class(Classe classes[], int* size);
int search(Classe tab[], int target, int current_size);
void write_to_file(Classe classes[], int *size);
void actualize(Classe classes[], int *size);
