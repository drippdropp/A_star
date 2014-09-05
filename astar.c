#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define kMANHATTAN "manhattan"
#define kEUCLIDEAN "euclidean"

typedef unsigned int u_int32_t;
typedef struct objPoint Point;
typedef struct objNode Node;
typedef struct objList List;

struct objPoint {
    u_int32_t x;
    u_int32_t y;
};

struct objNode {
    Point point;
    u_int32_t h_value;
    u_int32_t g_value;
    u_int32_t f_value;
    Node* parent;
};

struct objList {
    Node** nodes;
    u_int32_t list_size;
};

/************************************************************************/
/************************************************************************/
/** Struct Constructors **/
/************************************************************************/
Point* Point_new(u_int32_t, u_int32_t);
Node* Node_new(Point*);
List* List_new(Node*);
List* _List_new();
/************************************************************************/
/** Struct Function Defintions **/
/************************************************************************/
List* List_addNode(List*, Node*);
List* List_popNode(List*);
List* List_clear(List*);
/************************************************************************/

/************************************************************************/
/************************************************************************/
/** Function Definitions **/
/************************************************************************/
/************************************************************************/
inline u_int32_t get_minimum_movement_cost();
/************************************************************************/
u_int32_t get_heuristic_value(Point*, Point*, const char*);
/************************************************************************/
void construct_matrix(Node**, const u_int32_t, const u_int32_t);
/************************************************************************/
void calculate_node_heuristics(Node*, const u_int32_t, const u_int32_t);
/************************************************************************/
void print_matrix(Node**);
/************************************************************************/
void process_matrix(Node**, Node*, Node*);
/************************************************************************/
/************************************************************************/
/************************************************************************/



/******************************
* @method main
* @param argc [int]
* @param argv [char**]
* @return [int]
*******************************/
int main(int argc, char** argv) 
{
    Node* open_nodes;
    Node* closed_nodes;
    const u_int32_t max_X = 10;
    const u_int32_t max_Y = 10;

    char* hello;
    hello = "Hi there!";

    Point start_point;
    start_point.x = 0;
    start_point.y = 0;

    open_nodes = malloc(max_X*max_Y*sizeof(Node));
    closed_nodes = malloc(max_X*max_Y*sizeof(Node));

    return 0;
}

/******************************
* @method Point_new
* @param x [u_int32_t]
* @param y [u_int32_t]
* @return [Point*]
*******************************/
Point* Point_new(u_int32_t x, u_int32_t y) {
    Point* newPoint = (Point*) malloc(sizeof(Point));
    newPoint->x = x, newPoint->y = y;
    return newPoint;
}

/******************************
* @method Node_new
* @param p [Point*]
* @return [Node*]
*******************************/
Node* Node_new(Point* p) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->point = *p;
    return newNode;
}

/******************************
* @method List_new
* @param n [Node*]
* @return [List*]
*******************************/
List* List_new(Node* n) {
    List* newList = _List_new();
    newList->nodes[0] = n;
    newList->list_size++;
    return newList;
}

/******************************
* @private
* @method _List_new
* @return [List*]
*******************************/
List* _List_new() {
    List* newList = (List*) malloc(sizeof(List));
    newList->nodes = (Node**) malloc(5*sizeof(Node*));
    newList->list_size = 0;
    return newList;
}

/******************************
* @method List_addNode
* @param l [List*]
* @param n [Node*]
* @return [List*]
*******************************/
List* List_addNode(List* l, Node* n) {
    if (l->list_size <= (sizeof(l->nodes)/sizeof(Node*))/2) {
        Node** tmp_nodes = malloc(l->list_size*sizeof(Node*));
        for (int i = 0; i < l->list_size; i++)
            tmp_nodes[i] = l->nodes[i];
        free(l->nodes);
        l->nodes = (Node**) malloc(l->list_size*l->list_size*sizeof(Node*));
        for (int i = 0; i < l->list_size; i++)
            l->nodes[i] = tmp_nodes[i];
        free(tmp_nodes);
        l->nodes[l->list_size] = n;
        l->list_size++;
    } else {
        l->nodes[l->list_size] = n;
        l->list_size++;
    }
    return l;
}

/**********************************
* @inline get_minimum_movement_cost
* @return [u_int32_t]
***********************************/
inline u_int32_t get_minimum_movement_cost(){ return 1; }

/******************************
* @method get_heuristic_value
* @param p [Point*]
* @param goal [Point*]
* @param type [@const char*]
* @return [u_int32_t]
*******************************/
u_int32_t get_heuristic_value(Point* p, Point* goal, const char* type) {
    if (strcmp(type, kMANHATTAN)) {
        const u_int32_t distance_x = abs(p->x - goal->x);
        const u_int32_t distance_y = abs(p->y - goal->y);
        const u_int32_t min_move_cost = 1;
        return min_move_cost*(distance_x + distance_y);
    } else if (strcmp(type, kEUCLIDEAN)) {      
        const u_int32_t distance_x = goal->x - p->x;
        const u_int32_t distance_y = goal->y - p->y;
        return (u_int32_t) sqrt(powf((float)distance_x, 2)+powf((float)distance_y, 2));
    } else {
        fprintf(stderr, "You must include either manhattan or euclidean.\n\n");
        return 0;
    }
}

/******************************
* @method construct_matrix
* @param nodes [Node**]
* @param max_X [@const u_int32_t]
* @param max_Y [@const u_int32_t]
* @return [void]
*******************************/
void construct_matrix(  Node** nodes, 
                        const u_int32_t max_X, 
                        const u_int32_t max_Y) {
    u_int32_t pos = 0;
    for (u_int32_t i = 0; i < max_X; i++)
        for (u_int32_t j = 0; j < max_Y; j++) {
            nodes[pos] = Node_new( Point_new(i, j));
            pos++;}
}

/**********************************
* @method calculate_node_heuristics
* @param nodes [Node**]
* @param max_X [@const u_int32_t]
* @param max_Y [@const u_int32_t]
* @return [void]
***********************************/
void calculate_node_heuristics( Node* nodes, 
                                const u_int32_t max_X, 
                                const u_int32_t max_Y) {
    /* calc */

}

/******************************
* @method print_matrix
* @param matrix [Node*]
* @return [void]
*******************************/
void print_matrix(Node** matrix) {
    for (int i = 0; i < sizeof(matrix)/sizeof(Node); i++ ) {
        printf("x:%d, y:%d\n", matrix[i]->point.x, matrix[i]->point.y);
    }
}

/******************************
* @method process_matrix
* @param matrix [Node**]
* @param open [Node*]
* @param closed [Node*]
* @return [void]
*******************************/
void process_matrix(Node** matrix, Node* open, Node* closed) {

}