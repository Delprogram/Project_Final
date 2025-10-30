#include "library.h"

int found_file(char *directory_file) {
    if (directory_file == NULL) {
        printf("%d\n", FILE_NOT_FOUND);
        return 0;
    }
    FILE *file;
    file = fopen(directory_file, "r");
    if (file == NULL){
        printf("%d\n", FILE_NOT_FOUND);
        return 0;
    }
    return 1;
    fclose(file);
}


void init_lines_array(char **array_buffers, int **array_links) {
    for (int i = 0; i < 30; i ++) {
        array_buffers[i] = malloc(10*sizeof(char));
        array_links[i] = malloc(2*sizeof(int));
    }
}


// METTRE LES LIGNES JUSQU'A #LINKS DANS UN TABLEAU
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
        count ++;
        if (buffer[1] == 'l')
            break;
    }
    if (strcmp(array_buffers[0], "#nodes") != 0)
        return 0;
    fclose(file);   
    return count;
}


// METTRE LES LIENS DU FILE DANS UN TABLEAU
int init_array_links(char *directory_file, int **array_links) {
    char buffer[10];
    int count = 0;
    char concat1[3];
    char concat2[3];
    FILE *file;
    file = fopen(directory_file, "r");
    while (fgets(buffer, sizeof(buffer), file) != NULL)
        if (buffer[1] == 'l')
            break;
    if (buffer[1] != 'l')
            return 0;
    while(fgets(buffer, sizeof(buffer), file) != NULL) {
        int len_str = 0;
        while (buffer[len_str] != '\n')
            len_str ++;  
        buffer[len_str - 1] = '\0';
        if (buffer[1] != '-') {
            concat1[0] = buffer[0];
            concat1[1] = buffer[1];
            concat1[2] = '\0';
            array_links[count][0] = atoi(concat1);
            if(buffer[4] != '\0') {
                concat2[0] = buffer[3];
                concat2[1] = buffer[4];
                concat2[2] = '\0';
                array_links[count][1] = atoi(concat2);   
            } else 
                array_links[count][1] = buffer[3] - '0';
        } else {
            array_links[count][0] = buffer[0] - '0';
            array_links[count][1] = buffer[2] - '0';
        }
        if(is_double(array_links, count, 
            array_links[count][0], array_links[count][1]) == 0)
            count --;
        count ++;
    }
    fclose(file);
    return count;
}


int is_double(int **array_links, int count, int node1, int node2) {
    for (int i = 0; i < count; i++) {
        if ((node1 == array_links[i][0] && node2 == array_links[i][1]) ||
            (node2 == array_links[i][0] && node1 == array_links[i][1])) {
            for (int j = i; j < count - 1; j++) {
                array_links[j][0] = array_links[j + 1][0];
                array_links[j][1] = array_links[j + 1][1];
            }
            return 0;
        }
    }
    return 1;
}


int init_array_nodes_id(char **array_buffers, 
int total_buffers, int *array_nodes_id) {
    int count = 0;
    for (int i = 0; i < total_buffers; i ++) {
        if (array_buffers[i][0] != '#') {
            if (array_buffers[i][1] != '\0') 
                array_nodes_id[count] = atoi(array_buffers[i]);
            else
                array_nodes_id[count] = array_buffers[i][0] - '0';
            count ++;
        }
    }
    return count;
}


int init_start_list(Node *head, char **array_buffers, int total_buffers) {
    for (int i = 0; i < total_buffers; i ++) {
        if (array_buffers[i][1] == 's') {
            head->id = atoi(array_buffers[i + 1]);
            head->visited = 0;
            return 1;
        }  
    }
    return 0;
}


Node* find_end_node(Node *head, int end_course, 
Node ***array_unconnected_nodes, 
int total_unconnected_nodes) {
    if (head == NULL) 
        return NULL;
    if (head->id == end_course)
        return head;

    head->visited = 0;

    for (int i = 0; i < head->number_links; i++) {
        Node *next = head->links[i];
        if (next == NULL || !next->visited) 
            continue;
        Node *found = find_end_node(next, end_course, 
                                    array_unconnected_nodes, 
                                    total_unconnected_nodes);
        if (found != NULL)
            return found;  
    }
    for (int i = 0; i < total_unconnected_nodes; i++) {
        Node *next = (*array_unconnected_nodes)[i];
        if (next == NULL || !next->visited) 
            continue;
        Node *found = find_end_node(next, end_course, 
                                    array_unconnected_nodes, 
                                    total_unconnected_nodes);
        if (found != NULL)
            return found;  
    }
    return NULL; 
}


int top_exe(Node *head, char **array_buffers, 
int total_buffers, int total_links) {
    int start = init_start_list(head, array_buffers, total_buffers);
    int end = end_list(array_buffers, total_buffers);
    
    if (!total_buffers || !total_links) {
        printf("%d\n", BAD_FILE_FORMAT);
        return 1;
    }
    if (!start) {
        printf("%d\n", NO_START_NODE);
        return 1;
    }

    if (!end) {
        printf("%d\n", NO_END_NODE);
        return 1;
    }
    
    return 0;
    
}


int is_exist_pathfinding(Node ***array_unconnected_nodes, 
int total_unconnected_nodes, Node *end_node) {

    for (int i = 0; i < total_unconnected_nodes; i++) 
        if ((*array_unconnected_nodes)[i]->id == end_node->id) {
            printf("Ce programme ne peut pas être exécuté, ");
            printf("car pas de pathfinding possible.\n");
            return 0;
        }
    return 1;
}


int end_list(char **array_buffers, int total_buffers) {
    for (int i = 0; i < total_buffers; i ++) 
        if (array_buffers[i][1] == 'e') {
            return 1;
        } 
    return 0; 
} 


Node *init_end_list(Node *head, char **array_buffers, 
int total_buffers, int total_nodes, 
Node ***array_unconnected_nodes, 
int total_unconnected_nodes) {

    for (int i = 0; i < total_buffers; i ++) 
        if (array_buffers[i][1] == 'e') {
            Node *end_node = find_end_node(head, atoi(array_buffers[i + 1]),
                                array_unconnected_nodes, 
                                total_unconnected_nodes);
            return end_node;
        } 
    return NULL; 
}


// INITIALISER LES LIENS
void init_link(Node *head, int **array_links, int total_links) {
    head->number_links = 0;
    for (int i = 0; i < total_links; i++) 
        if (array_links[i][0] == head->id || array_links[i][1] == head->id)
            head->number_links++;
    
    head->links = malloc(head->number_links * sizeof(Node*)); 
    for (int i = 0; i < head->number_links; i++)
        head->links[i] = NULL;
}


// VERIFIER SI UN LIEN A DEJA ETE AJOUTE
int is_visited(int id, int *visited, int total) {
    for (int i = 0; i < total; i++){
        if (visited[i] == id)
            return 1; 
    }      
    return 0;
}


int is_visited_link(int id1, int id2, int **visited_link, int total) {
    for (int i = 0; i < total; i++) {
        if ((visited_link[i][0] == id1 && visited_link[i][1] == id2)
            && (visited_link[i][1] == id1 && visited_link[i][0] == id2))
            return 1;
    }
    return 0;
}


void init_node(Node *node) {
    node->id = 0;
    node->number_links = 0;
    node->visited = 0;
}


int is_incluse(int node_id, Node ***array_nodes, int count_nodes) {
    for (int i = 0; i < count_nodes; i++) 
        if ((*array_nodes)[i]->id == node_id)
            return i;
    return 100;
}


int skip_node(int *link, Node *head, 
int *visited, int visited_count,
int **visited_link,
int visited_count_link) {

    if (is_visited_link(head->id, link[0], visited_link, visited_count_link)){
        if (is_visited(link[0], visited, visited_count) 
            && link[1] == head->id){
            head->number_links--;
            return 1;
        }
        if (is_visited(link[1], visited, visited_count) 
            && link[0] == head->id){
            head->number_links--;
            return 1;
        }
    }
    return 0;
}


Node *create_node(Node *head, int *link, 
Node ***array_nodes, int *count_nodes) {

    Node *node = malloc(sizeof(Node));
    init_node(node);
    int incluse;

    if (link[0] == head->id) {
        incluse = is_incluse(link[1], array_nodes, *count_nodes);
        if (incluse != 100)
            node = (*array_nodes)[incluse];
        else {
            node->id = link[1];
            stock_nodes(node, array_nodes, count_nodes);
        }
    } else if (link[1] == head->id) {
        incluse = is_incluse(link[0], array_nodes, *count_nodes);
        if (incluse != 100)
            node = (*array_nodes)[incluse];
        else {
            node->id = link[0];
            stock_nodes(node, array_nodes, count_nodes);
        }
    }
    return node;
}


void add_link(Node *head, Node *node, 
int **visited_link, int *visited_count_link, int count) {
    visited_link[*visited_count_link][0] = head->id;
    visited_link[*visited_count_link][1] = node->id;
    (*visited_count_link)++;
    head->links[head->number_links - count] = node;
    }

// POUR CREER LA CHAINE DE NOEUDS
void init_list(Node *head,  
int **array_links,
int total_links,   
int total_nodes,
int *visited,
int *visited_count,
Node ***array_nodes, 
int *count_nodes,
int **visited_link,
int *visited_count_link) {

    stock_nodes(head, array_nodes, count_nodes);
    init_link(head, array_links, total_links); 
    visited[*visited_count] = head->id;
    (*visited_count)++;
    int count = head->number_links;
    int count_link = 0;
    while (count_link < total_links) {
        if (count > 0) {
            if (array_links[count_link][0] == head->id || 
                array_links[count_link][1] == head->id) { 
                if (skip_node(array_links[count_link], 
                    head, visited, *visited_count,
                    visited_link, *visited_count_link)){
                    count--;
                    count_link ++;
                    continue;
                }     
                Node *node = create_node(head, array_links[count_link], 
                array_nodes, count_nodes);
                add_link(head, node, visited_link, visited_count_link, count);
                count--;                         
            }             
        }else break;
        count_link ++; 
    }
    for (int i = 0; i < head->number_links; i++) {
        if (!is_visited(head->links[i]->id, visited, *visited_count)) {
            Node *next = head->links[i];
            init_list(next, array_links, 
                total_links, total_nodes, 
                visited, visited_count, 
                array_nodes, count_nodes, 
                visited_link, visited_count_link);
        }
    }
}


int find_unconnected_nodes(int *array_nodes_id, 
Node ***array_unconnected_nodes,
int total_nodes, 
int *visited, 
int *visited_count) {

    int count = 0;
    for (int i = 0; i < total_nodes; i++)
        if (!is_visited(array_nodes_id[i], visited, *visited_count)) {
            Node *unconnected_node = malloc(sizeof(Node));
            unconnected_node->id = array_nodes_id[i];
            unconnected_node->visited = 0;
            unconnected_node->links = NULL;
            *array_unconnected_nodes = realloc(*array_unconnected_nodes, 
                (count + 1)*sizeof(Node*));
            (*array_unconnected_nodes)[count] = unconnected_node;
            count ++;
        }
        
    return count;
}


void init_unconnected_nodes(Node ***array_unconnected_nodes, 
int total_unconnected_nodes,
int **array_links,
int total_links,
int *visited,
int *visited_count,
Node ***array_nodes, 
int *count_nodes,
int **visited_link,
int *visited_count_link) {
    for (int i = 0; i < total_unconnected_nodes; i++) {
        if (!is_visited((*array_unconnected_nodes)[i]->id,
             visited, *visited_count)) {
            init_list((*array_unconnected_nodes)[i], array_links, 
                total_links, total_unconnected_nodes, 
                visited, visited_count, 
                array_nodes, count_nodes, 
                visited_link, visited_count_link);
        } 
        (*array_unconnected_nodes)[i]->visited = 1;
    }
    
}


void remove_difference(Node ***array_nodes, 
int *count_nodes, 
Node ***array_unconnected_nodes, 
int total_unconnected_nodes) {
    Node **A = *array_nodes;
    Node **B = *array_unconnected_nodes;
    for (int i = 0; i < *count_nodes; i++) 
        for (int j = 0; j < total_unconnected_nodes; j++) 
            if (A[i]->id == B[j]->id) {
                for (int k = i; k < *count_nodes - 1; k++)
                    A[k] = A[k + 1];
                (*count_nodes)--;  
                i--;  
                break;
            }   
}


int stock_nodes(Node *node, Node ***array_nodes, int *count_nodes) {
    if (node->visited == 0) {
        *array_nodes = realloc(*array_nodes, 
            (*count_nodes + 1)*sizeof(Node*));
        (*array_nodes)[*count_nodes] = node;
        (*count_nodes)++;
        return node->number_links;
    }
    return 0;
}


// AFFICHER LES LIENS
void browse_list(Node *head, Node ***array_nodes, 
int *count_nodes, int *total_links_nodes) {
    if (!head || head->visited) return;
        *total_links_nodes += stock_nodes(head, array_nodes, count_nodes);
        head->visited = 1;
    
        for (int i = 0; i < head->number_links; i++) {
            Node *next = head->links[i];
            if (next && !next->visited) { 
                browse_list(next, array_nodes, 
                    count_nodes, total_links_nodes);
            }
        }
}


void put_in_queue(Way **front, Way **behind, Node *node, Node *parent) {
    Way *w = malloc(sizeof(Way));
    w->node = node;
    w->parent = parent;
    w->next = NULL;
    if (*behind) 
        (*behind)->next = w;
    *behind = w;
    if (!*front) 
        *front = w;
}


Way* get_out_queue(Way **front, Way **behind) {
    if (!*front) 
        return NULL;
    Way *w = *front;
    *front = (*front)->next;
    if (!*front) 
        *behind = NULL;
    return w;
}


void shortest_path(Node *start, Node *end, int total, Node **array_nodes) {
    int max_id = 0;
    for (int i = 0; i < total; i++) {
        if (array_nodes[i]->id > max_id) 
            max_id = array_nodes[i]->id;
    }

    for (int i = 0; i < total; i++) 
        array_nodes[i]->visited = 0;
    Node **parent = malloc((max_id + 1) * sizeof(Node*));
    for (int i = 0; i <= max_id; i++) 
        parent[i] = NULL;

    Way *front = NULL;
    Way *rear = NULL;
    put_in_queue(&front, &rear, start, NULL);
    start->visited = 1;
    parent[start->id] = NULL;

    Way *w;
    while ((w = get_out_queue(&front, &rear)) != NULL) {
        Node *cur = w->node;
        parent[cur->id] = w->parent;

        if (cur == end) {
            int cap = 8;
            int *stack = malloc(cap * sizeof(int));
            int top = 0;
            Node *p = end;
            while (p) {
                if (top >= cap) { 
                    cap *= 2; 
                    stack = realloc(stack, cap * sizeof(int)); 
                }
                stack[top++] = p->id;
                p = parent[p->id];
            }
            printf("pathfinding: \n");
            for (int i = top - 1; i >= 0; i--) 
                printf("%d ", stack[i]);
            printf("\n");
            free(stack);
            free(w);
            break;
        }

        for (int i = 0; i < cur->number_links; i++) {
            Node *neigh = cur->links[i];
            if (!neigh->visited) {
                neigh->visited = 1;
                put_in_queue(&front, &rear, neigh, cur);
            }
        }
        free(w);
    }
    free(parent);
}


void print_exit(int count_nodes, 
int total_links_nodes, 
int head_id, int end_node_id, 
Node ***array_unconnected_nodes, 
int total_unconnected_nodes) {

    print_node(count_nodes);
    print_links(total_links_nodes);
    print_start(head_id);
    print_end(end_node_id);
    print_unconnected_nodes(array_unconnected_nodes, 
        total_unconnected_nodes);

}


void print_node(int count_nodes) {
    printf("nodes: %d\n", count_nodes);
}


void print_start(int head_id) {
    printf("start: %d\n", head_id);
}


void print_end(int end_node_id) {
    printf("end: %d\n", end_node_id);
}


void print_links(int total_links_nodes) {
    printf("links: %d\n", total_links_nodes);
}


void print_unconnected_nodes(Node ***array_unconnected_nodes, 
int total_unconnected_nodes) {
    if (!total_unconnected_nodes)
        return;
    printf("unconnected nodes:\n");
    for (int i = 0; i < total_unconnected_nodes; i++)
        printf("%d ", (*array_unconnected_nodes)[i]->id);
    printf("\n");
}


void free_end(char **array_buffers, int **array_links,
int *array_nodes_id, int *visited,
int *visited_count, int **visited_link,
int *visited_count_link, int *count_nodes,
int *total_links_nodes,
Node **array_unconnected_nodes, Node **array_nodes) {

    free(count_nodes);
    free(array_nodes);
    free(total_links_nodes);
    free(visited_count);
    free(visited_count_link);
    for (int i = 0; i < 30; i++) {
        free(array_buffers[i]);
        free(array_links[i]);
    }
    free(array_buffers);
    free(array_links);
    free(array_nodes_id);
    free(array_unconnected_nodes);
    free(visited);
    free(visited_link);
}
