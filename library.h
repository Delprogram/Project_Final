#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <time.h>

typedef struct n{
    int id;
    int number_links;
    struct n **links;
    int visited; 
} Node;

typedef struct way {
    Node *node;
    Node *parent;
    struct way *next;
} Way;

typedef enum {
    FILE_NOT_FOUND = 1,
    NO_START_NODE = 2,
    NO_END_NODE = 3,
    BAD_FILE_FORMAT = 4
} Error;

int is_double(int **array_links, int count, int node1, int node2);

int init_array_buffers(char *directory_file, char **array_buffers); 

int init_array_links(char *directory_file, int **array_links); 

int skip_node(int *link, Node *head, 
    int *visited, int visited_count,
    int **visited_link,
    int visited_count_link);

int is_visited_link(int id1, int id2, int **visited_link, int total);

void init_list(Node *head,  
    int **array_links,
    int total_links,   
    int total_nodes,
    int *visited,
    int *visited_count,
    Node ***array_nodes, 
    int *count_nodes,
    int **visited_link,
    int *visited_count_link);

int found_file(char *directory_file);

int top_exe(Node *head, char **array_buffers, 
    int total_buffers, int total_links);

int end_list(char **array_buffers, int total_buffers);

int is_exist_pathfinding(Node ***array_unconnected_nodes, 
    int total_unconnected_nodes, Node *end_node);

int is_visited(int id, int *visited, int total);

void init_link(Node *head, int **array_links, int total_links);

int init_start_list(Node *head, char **array_buffers, int total_buffers);

Node *init_end_list(Node *head, 
    char **array_buffers, 
    int total_buffers, 
    int total_nodes, 
    Node ***array_unconnected_nodes, 
    int total_unconnected_nodes);

int init_array_nodes_id(char **array_buffers, 
    int total_buffers, 
    int *array_nodes_id);

void browse_list(Node *head, 
    Node ***array_nodes, 
    int *count_nodes, 
    int *total_links_nodes);

void remove_difference(Node ***array_nodes, 
    int *count_nodes, 
    Node ***array_unconnected_nodes, 
    int total_unconnected_nodes);

int find_unconnected_nodes(int *array_nodes_id, 
    Node ***array_unconnected_nodes, 
    int total_nodes,  
    int *visited, 
    int *visited_count);

void init_unconnected_nodes(Node ***array_unconnected_nodes, 
    int total_unconnected_nodes,
    int **array_links,
    int total_links,
    int *visited,
    int *visited_count,
    Node ***array_nodes, 
    int *count_nodes,
    int **visited_link,
    int *visited_count_link);

Node* find_end_node(Node *head, int end_course, 
    Node ***array_unconnected_nodes, 
    int total_unconnected_nodes);

void add_link(Node *head, Node *node, 
    int **visited_link, int *visited_count_link, int count);

int stock_nodes(Node *node, Node ***array_nodes, int *count_nodes);

int is_incluse(int node_id, Node ***array_nodes, int count_nodes);

void init_node(Node *node);

Node *create_node(Node *head, int *link, 
    Node ***array_nodes, int *count_nodes);

void free_node(Node *node);

void init_lines_array(char **array_buffers, int **array_links);

void print_exit(int count_nodes, 
    int total_links_nodes, 
    int head_id, int end_node_id, 
    Node ***array_unconnected_nodes, 
    int total_unconnected_nodes);

void print_node(int count_nodes);
void print_start(int head_id);
void print_end(int end_node_id);
void print_links(int total_links_nodes);
void print_unconnected_nodes(Node ***array_unconnected_nodes, 
    int total_unconnected_nodes);

void shortest_path(Node *start, Node *end, int total, Node **array_nodes);

void put_in_queue(Way **front, Way **behind, Node *node, Node *parent);

Way* get_out_queue(Way **front, Way **behind);

void free_end(char **array_buffers, int **array_links,
    int *array_nodes_id, int *visited,
    int *visited_count, int **visited_link,
    int *visited_count_link, int *count_nodes,
    int *total_links_nodes,
    Node **array_unconnected_nodes, Node **array_nodes);
