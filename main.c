#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct treeNode{
    int x; // x-coordinate
    int y; // y-coordinate
    struct treeNode* left; // Left child
    struct treeNode* right; // Right child
    int height; // For AVL balancing
}treeNode;

// Creates a new tree node with a given coordinate (x, y)
treeNode* newNode(int x, int y){
    treeNode* node = (treeNode*)malloc(sizeof(treeNode));
    node->x = x;
    node->y = y;
    node->left = NULL;
    node->right = NULL;
    node->height = 0;
    return node;
}

// Calculated the height of a node (from lecture slides)
int height(treeNode* node){
    if(node == NULL) return -1;
    return node->height;
}

// Rotate tree to the right for balancing with AVL (from lecture slides)
treeNode* rotateR(treeNode* current){
    treeNode* new = current->left;
    current->left = new->right;
    new->right = current;

    // Updates heights of current and new
    current->height = fmax(height(current->left), height(current->right)) + 1;
    new->height = fmax(height(new->left), height(new->right)) + 1;

    return(new);
}

// Rotate tree to the left for balancing with AVL (from lecture slides)
treeNode* rotateL(treeNode* current){
    treeNode* new = current->right;
    current->right = new->left;
    new->left = current;

    // Update heights of current and new
    current->height =fmax(height(current->left), height(current->right)) + 1;
    new->height = fmax(height(new->left), height(new->right)) + 1;

    return(new);
}

// Rotate tree to the right and then left for balancing with AVL (from lecture slides)
treeNode* rotateRL(treeNode* current){
    current->right = rotateR(current->right);
    return rotateL(current);
}

// Rotate tree to the left and then right for balancing with AVL (from lecture slides)
treeNode* rotateLR(treeNode* current){
    current->left = rotateL(current->left);
    return rotateR(current);
}

// Balance tree using AVL (from lecture slides)
treeNode* balance(treeNode* node){
    if(node == NULL) return node;
    
    // Left-heavy subtree
    if(height(node->left) - height(node->right) > 1){
        if(height(node->left->left) >= height(node->left->right)){
            node = rotateR(node);
        }
        else{
            node = rotateLR(node);
        }
    }
    // Right-heavy subtree
    else if(height(node->left) - height(node->right) < -1){
        if(height(node->right->right) >= height(node->right->left)){
            node = rotateL(node);
        }
        else{
            node = rotateRL(node);
        }
    }
    return node;    
}

// Add a point (x, y) to the tree and balance it (modified from lecture slides)
treeNode* add(treeNode* node, int x, int y){
    if(node == NULL){
        return(newNode(x, y));
    }

    // Add new node to left or right subtree based on x (& y if x values are equal)
    if(x < node->x || (x == node->x && y < node->y)){
        node->left = add(node->left, x, y);
    }
    else if(x > node->x || (x == node->x && y > node->y)){
        node->right = add(node->right, x, y);
    }

    // Update height and balance
    node->height = fmax(height(node->left), height(node->right)) + 1;
    return balance(node);
}

// Check if a point (x1, y1) is inside a circle with radius r and center (cx, cy)
int inCircle(int cx, int cy, int r, int x1, int y1){
    int x = x1 - cx;
    int y = y1 - cy;
    return (x * x + y * y) <= (r * r);
}

// Counts points inside a given circle with radius r and center (cx, cy)
int countPoints(treeNode* node, int cx, int cy, int r){
    if(node == NULL) return 0;

    int count = 0; // Total count of points in circle

    if(inCircle(cx, cy, r, node->x, node->y)){
        count++;
    }

    count += countPoints(node->left, cx, cy, r);
    count += countPoints(node->right, cx, cy, r);

    return count;
}

int main(void){
    // LOCAL VARIABLES
    char name[100];
    scanf("%s", name);
    FILE* file = fopen(name, "r"); // File to read data from
    treeNode* root = NULL; // Root of tree
    int x; // x-coordinate
    int y; // y-coordinate

    // EXECUTABLE STATEMENTS
    // Read from file and insert into the tree
    while(fscanf(file, "%d %d", &x, &y) != EOF){
        root = add(root, x, y);
    }

    fclose(file); // Close file

    // Handle collision queries from stdin
    while(1){
        int cx;
        int cy;
        int r;
        if(scanf("%d %d %d", &cx, &cy, &r) != 3) break;

        // count the number of points inside the given circle
        int count = countPoints(root, cx, cy, r);
        printf("%d\n", count);
    }

    return(0);
}
