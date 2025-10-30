#include "library.h"

int main(int argc, char *argv[]) {
    Node *head = malloc(sizeof(Node));
    Node **array_unconnected_nodes = NULL;
    Node **array_nodes = NULL;
    Node *end_node;
    if(!found_file(argv[1])) 
        return 1;
    char **array_buffers = malloc(99*sizeof(char*));
    int **array_links = malloc(99*sizeof(int*));
    int *array_nodes_id = malloc(99*sizeof(int));
    int total_buffers, total_links, total_nodes, total_unconnected_nodes = 0;
    int max_links = 1000;
    int *visited = malloc(max_links * sizeof(int));
    int *visited_count = malloc(sizeof(int));
    int *visited_count_link = malloc(sizeof(int));
    int **visited_link = malloc(max_links * sizeof(int*));
    for (int i = 0; i < max_links; i++) {
        visited_link[i] = malloc(2*sizeof(int));
    }
    int *total_links_nodes = malloc(sizeof(int));
    int *count_nodes = malloc(sizeof(int));
    *visited_count = 0;
    *visited_count_link = 0;
    *count_nodes = 0;
    *total_links_nodes = 0;
    init_lines_array(array_buffers, array_links);  
    total_buffers = init_array_buffers(argv[1], array_buffers);
    total_links = init_array_links(argv[1], array_links);
    if (top_exe(head, array_buffers, total_buffers, total_links)) 
        return 1;
    total_nodes = init_array_nodes_id(array_buffers, 
                                    total_buffers, array_nodes_id);
    init_list(head, array_links, 
        total_links, total_nodes, 
        visited, visited_count, 
        &array_nodes, count_nodes, 
        visited_link, visited_count_link);
    total_unconnected_nodes = find_unconnected_nodes(array_nodes_id, 
                                    &array_unconnected_nodes, 
                                    total_nodes, visited, visited_count);
    init_unconnected_nodes(&array_unconnected_nodes, 
        total_unconnected_nodes,
        array_links,
        total_links,
        visited,
        visited_count, 
        &array_nodes, 
        count_nodes, 
        visited_link, 
        visited_count_link);
    remove_difference(&array_nodes, 
        count_nodes, 
        &array_unconnected_nodes, 
        total_unconnected_nodes);
    
    *count_nodes = 0;
    browse_list(head, &array_nodes, count_nodes, total_links_nodes);
    end_node = init_end_list(head, array_buffers, total_buffers, 
        total_nodes, &array_unconnected_nodes, 
        total_unconnected_nodes);
    if (!is_exist_pathfinding(&array_unconnected_nodes, 
        total_unconnected_nodes, end_node)) 
        return 1;
    print_exit(*count_nodes, *total_links_nodes/2, 
        head->id, end_node->id, 
        &array_unconnected_nodes, 
        total_unconnected_nodes);
    shortest_path(head, end_node, *count_nodes, array_nodes);
    free_end(array_buffers, array_links, 
        array_nodes_id, visited, 
        visited_count, visited_link,
        visited_count_link, count_nodes, total_links_nodes, 
        array_unconnected_nodes, array_nodes);
    
    return 0;
}