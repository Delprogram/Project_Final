#include "library.h"

// POUR COMPTER LE NOMBRE NOEUDS
int count_nodes(char *directory_file) {
    FILE *file;
    file = fopen(directory_file, "r");
    char buffer[10];
    int count = 0;
    if (file == NULL)
        return 1;

    while(fgets(buffer, sizeof(buffer), file) != NULL){
        if (buffer[1] == 'l')
            break;
        count ++;
        //printf("%s : %d\n",buffer, strcmp(buffer, "#links\n"));
    }
    fclose(file);
    return count - 3;
    
}

// METTRE LES LIGNES JUSQU'A #LINKS DANS UN TABLEAUX
int init_array_buffers(char *directory_file, char **array_buffers) {
    char buffer[10];
    int count = 0;
    FILE *file;
    file = fopen(directory_file, "r");
    while(fgets(buffer, sizeof(buffer), file) != NULL) {
        int len_str = 0;
        while (buffer[len_str] != '\n')
            len_str ++;  
        buffer[len_str - 1] = '\0';
        strcpy(array_buffers[count], buffer);  
        //printf("%s\n", array_buffers[count]); //  Afficher les lignes jusqu'à #links
        count ++;
        if (buffer[1] == 'l')
            break;
    }
    //printf("%d", count);

    fclose(file);   
    return count;
}

// METTRE LES LIENS DU FILE DANS UN TABLEAUX
int init_array_links(char *directory_file, char **array_links) {
    char buffer[10];
    int count = 0;
    FILE *file;
    file = fopen(directory_file, "r");
    while (fgets(buffer, sizeof(buffer), file) != NULL)
        if (buffer[1] == 'l')
            break;

    while(fgets(buffer, sizeof(buffer), file) != NULL) {
        int len_str = 0;
        while (buffer[len_str] != '\n')
            len_str ++;  
        buffer[len_str - 1] = '\0';
        strcpy(array_links[count], buffer);
        //printf("%s\n", array_links[count]); // Afficher les liens
        count ++;
    }

    //printf("%d", count);
    fclose(file);
    return count;
}

void init_start_list(Node *head, char **array_buffers, int total_buffers) {
    char buffer[10];
    int count = 0;
    int j = 0;
    
    for (int i = 0; i < total_buffers; i ++) {
        if (array_buffers[i][1] == 's') {
            head->id = atoi(array_buffers[i + 1]);
            //printf("a - %c", head_id_str);
        }  
    }

}

// INITIALISER LES LIENS
void init_link(Node *head, char **array_links, int total_links, char head_id_str) {
    head->number_links = 0;
    for (int i = 0; i < total_links; i++) {
        if (array_links[i][0] == head_id_str || array_links[i][2] == head_id_str)
            head->number_links++;
    }
    head->link = malloc(head->number_links * sizeof(Node*)); 
    for (int i = 0; i < head->number_links; i++)
        head->link[i] = NULL; // sécurisation
}

// VERIFIER SI UN LIEN A DEJA ETE AJOUTE
int is_visited(int id1, int id2, int **visited, int total) {
    for (int i = 0; i < total; i++) {
        if ((visited[i][0] == id1 && visited[i][1] == id2))
           // || (visited[i][1] == id1 && visited[i][0] == id2))
            return 1;
    }
    return 0;
}

// POUR CREER LA CHAINE DE NOEUDS
void init_list(Node *head, 
    char **array_buffers, 
    char **array_links, 
    int total_buffers, 
    int total_links, 
    int count_nodes,
    int **visited,
    int *visited_count) {

    char head_id_str = head->id + '0';
    int j = 0;
    
    
    init_link(head, array_links, total_links, head_id_str); 
    //printf("[INIT] head=%d a %d liens possibles\n", head->id, head->number_links);
        
    for (int i = 0; i < total_links; i ++) {
        if (array_links[i][0] == head_id_str || array_links[i][2] == head_id_str) { 
            Node *node = malloc(sizeof(Node));
            node->link = NULL;  
            if (array_links[i][0] == head_id_str) {
                node->id = array_links[i][2] - '0';
            }
                
            else if (array_links[i][2] == head_id_str) {  
                node->id = array_links[i][0] - '0';
            }

            if (is_visited(head->id, node->id, visited, *visited_count)) {
                free(node);  // éviter les pointeurs perdus
                continue;
            }

            visited[*visited_count][0] = head->id;
            visited[*visited_count][1] = node->id;
            (*visited_count)++;
            head->link[j++] = node;
            //printf("%d -> %d\n", head->id, node->id);  
            init_list(node, array_buffers, array_links, 
                total_buffers, total_links, count_nodes - 1, 
                visited, visited_count);
            //printf("%d -> %d\n", head->id, node->id);
        }
    } 
   
}


// AFFICHER LES LIENS
void print_nodes(Node *head, int **visited, int *visited_count) {
    if (!head) return;

    //printf("[PRINT] Node %d a %d liens\n", head->id, head->number_links);

    for (int i = 0; i < head->number_links; i++) {
        Node *next = head->link[i];
        if (!next) {
            //printf("[DEBUG] lien %d de %d est NULL\n", i, head->id);
            continue;
        }

        if (is_visited(head->id, next->id, visited, *visited_count)) {
            //printf("[DEBUG] lien %d -> %d déjà visité\n", head->id, next->id);
            continue;
        }

        // Vérification mémoire pour visited
        if (!visited[*visited_count]) {
            //printf("[ERROR] visited[%d] non alloué\n", *visited_count);
            continue;
        }

        visited[*visited_count][0] = head->id;
        visited[*visited_count][1] = next->id;
        (*visited_count)++;

        printf("%d -> %d\n", head->id, next->id);
        print_nodes(next, visited, visited_count);
    }
}




