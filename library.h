#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <time.h>

typedef struct n{
    int id;
    int number_links;
    struct n **link;
    
} Node;

int count_nodes(char *directory_file); // POUR COMPTER LE NOMBRE NOEUDS
int init_array_buffers(char *directory_file, char **array_buffers); // METTRE LES LIGNES JUSQU'A #LINKS DANS UN TABLEAUX
int init_array_links(char *directory_file, char **array_links); // METTRE LES LIENS DU FILE DANS UN TABLEAUX
void init_list(Node *head, char **array_buffers, 
    char **array_links, int total_buffers, 
    int total_links, int count_nodes, 
    int **visited, int *visited_count); // POUR CREER LA CHAINE DE NOEUDS
int is_visited(int id1, int id2, int **visited, int total);
void init_link(Node *head, char **array_links, int total_links, char head_id_str);
void init_start_list(Node *head, char **array_buffers, int total_buffers);
void print_nodes(Node *head, int **visited, int *visited_count);