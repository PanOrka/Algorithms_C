/*
// Node structure
*/
typedef struct {
    int value;
    int priority;
} node;

/*
// Heap structure
*/
typedef struct {
    node *tab;
    int used_size, max_size;
} heap;

/*
// Creating binary-heap
*/
heap * create_heap(int max_size);

/*
// Inserting element to binary-heap
*/
void insert(heap *h, int value, int priority);

/*
// Checking whether heap is empty, returns 1 if is empty, else 0
*/
int is_empty(heap *h);

/*
// Print highest prior node value, if doesn't exist print blank line
*/
void top(heap *h);

/*
// Print highest prior node value and delete it, if doesn't exist print blank line
*/
void pop(heap *h);

/*
// For every element that has given value, change priority if it's priority is less than given
*/
void change_priority(heap *h, int value, int new_priority);

/*
// Print structure nodes as (x_i, p_i)
*/
void print(heap *h);
