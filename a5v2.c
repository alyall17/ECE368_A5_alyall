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

// Print tree
void printTree(treeNode* root){
    if (root != NULL) {

        printf("T %d, %d\n", root->x, root->y);

        printTree(root->left);

        
        printTree(root->right);

        
    }
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

        // printTree(root);
        // printf("----\n ");
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
