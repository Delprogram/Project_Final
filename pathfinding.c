#include "library.h"

int main(int argc, char *argv[]) {
    Node *head = malloc(sizeof(Node));
    char **array_buffers = malloc(30*sizeof(char*));
    char **array_links = malloc(30*sizeof(char*));
    int max_links = 30;
    int **visited = malloc(max_links * sizeof(int*));
    for (int i = 0; i < max_links; i++) {
        visited[i] = malloc(2*sizeof(int));
    }

    int *visited_count = malloc(sizeof(int));
    *visited_count = 0;
    for (int i = 0; i < 30; i ++) {
        array_buffers[i] = malloc(10*sizeof(char));
        array_links[i] = malloc(4*sizeof(char));
    }
    
    //init_array_buffers(argv[1], array_buffers);
    //init_array_links(argv[1], array_links);
    int total_buffers = init_array_buffers(argv[1], array_buffers);
    int total_links = init_array_links(argv[1], array_links);
    init_start_list(head, array_buffers, total_buffers);
    init_list(head, array_buffers, 
        array_links, total_buffers, 
        total_links, count_nodes(argv[1]), 
        visited, visited_count);
    int visited_print_count = 0;
    print_nodes(head, visited, &visited_print_count);
    //printf("%d", count_nodes(argv[1]));


    return 0;
}