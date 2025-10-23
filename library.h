#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <time.h>

typedef struct n{
    int id;
    struct n **link;
    
} Node;