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
    current->height = (height(current->left) > height(current->right) ? height(current->left) : height(current->right)) + 1;
    new->height = (height(new->left) > height(new->right) ? height(new->left) : height(new->right)) + 1;

    return(new);
}

// Rotate tree to the left for balancing with AVL (from lecture slides)
treeNode* rotateL(treeNode* current){
    treeNode* new = current->right;
    current->right = new->left;
    new->left = current;

    // Update heights of current and new
    current->height = (height(current->left) > height(current->right) ? height(current->left) : height(current->right)) + 1;
    new->height = (height(new->left) > height(new->right) ? height(new->left) : height(new->right)) + 1;

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
    else if(x < node->x || (x == node->x && y < node->y)){
        node->left = add(node->left, x, y);
    }
    else if(x >= node->x || (x == node->x && y > node->y)){
        node->right = add(node->right, x, y);
    }

    // Update height and balance
    node->height = height(node->left) > height(node->right) ? height(node->left) : height(node->right) + 1;
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
        count = 1;
    }

    if(node->x > (cx + r)){
        return count + countPoints(node->left, cx, cy, r);
    }
    else if(node->x < (cx - r)){
        return count + countPoints(node->right, cx, cy, r);
    }
    else{
       return count + countPoints(node->left, cx, cy, r) + countPoints(node->right, cx, cy, r);
    }
}

// Frees tree memory
void freeTree(treeNode* node){
    if(node == NULL) return;

    // Recursively free left and right subtrees
    freeTree(node->left);
    freeTree(node->right);

    // Free current node
    free(node);
}

int main(int argc, char *argv[]){
    // LOCAL VARIABLES
    FILE* file = fopen(argv[1], "r"); // File to read data from
    treeNode* root = NULL; // Root of tree
    int x; // x-coordinate
    int y; // y-coordinate

    // EXECUTABLE STATEMENTS
    // Read from file and insert into the tree
    while(fscanf(file, "%d %d", &x, &y) != EOF){
        root = add(root, x, y);
    }

    fclose(file); // Close file

    int cx; // current x-coordinate (loop)
    int cy; // current y-coordinate (loop)
    int r; // Radius (loop)


    // Handle collision queries from stdin
    char line[100];
    while(fgets(line, 100, stdin) != NULL){

        int numArgs = sscanf(line, "%d %d %d\n", &cx, &cy, &r);

        if(numArgs != 3){
            break;
        }

        // Count the number of points inside the given circle
       int count = countPoints(root, cx, cy, r);
       printf("%d\n", count);
    }
    // Free tree
    freeTree(root);
    return(0);
}
