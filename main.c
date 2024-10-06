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

// Calculated the height of a node
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

// Add a point (x, y) to the tree and balance it
treeNode* add(treeNode* node, int x, int y){

}