#include "tree.h"
/**********  Helper functions for removing from an AVL tree **********/
TNode* removeNextInorder( TNode** pRoot );
/**********  Helper functions for balancing an AVL tree **********/
void updateHeights(TNode* root);
void rebalanceTree(Tree* t, TNode* x);
void rightRotate(TNode* root);
void leftRotate(TNode* root);
int getBalance(TNode* x);
TNode* getTallerSubTree(TNode* x);
bool isSameSignBalance(TNode* x, TNode* z);
int subTreeHeight(TNode* root);

/* printName
* input: none
* output: none
*
* Prints name the student who worked on this solution
*/
void printName( )
{
/* TODO : Fill in your name*/
    printf("\nThis solution was completed by:\n");
    printf("<Kendall Ramos>\n\n");
}

/* createTree
* input: none
* output: a pointer to a Tree (this is malloc-ed so must be freed eventually!)
*
* Creates a new empty Tree and returns a pointer to it.
*/
Tree *createTree( ){
    Tree* t = (Tree*)malloc( sizeof(Tree) );
    t->root = (TNode*)malloc( sizeof(TNode) );
    t->root->leaf = true;
    t->root->height = 0;
    t->root->pParent = t->root->pLeft = t->root->pRight = NULL;
    return t;  
} 

Tree *createTreeFromTNode( TNode* root ){
    Tree* t = (Tree*)malloc( sizeof(Tree) );
    t->root = root;
    return t; 
}

/* attachLeafNodes
* input: a pointer to a TNode
* output: none
*
* Mallocs and stores leaf nodes below the passed in TNode ins
*/
void attachLeafNodes( TNode *ins )
{
    /* Mark this node as not a leaf */
    ins->leaf = false;
    /* Add empty leaf nodes below this node */
    ins->pLeft = (TNode *)malloc( sizeof(TNode) );
    ins->pRight = (TNode *)malloc( sizeof(TNode) );
    if( ins->pLeft==NULL || ins->pRight==NULL ){
        fprintf( stderr, "malloc failed\n" );
        exit(-1);
    } 
    ins->pLeft->leaf = ins->pRight->leaf = true;
    ins->pLeft->pParent = ins->pRight->pParent = ins;
    ins->pLeft->pLeft = ins->pRight->pLeft = ins->pLeft->pRight = ins->pRight->pRight = NULL;
    ins->pLeft->height = ins->pRight->height = 0;
} 

/* attachChildNodes
    * input: three pointers to a TNodes
    * output: none
    *
    * Sets root's left and right children to the specified nodes
    */
void attachChildNodes( TNode* root, TNode* left, TNode* right ){
    root->pLeft = left;
    root->pRight = right;
    root->pLeft->pParent = root->pRight->pParent = root;
} 

/* freeTree and freeTreeContents
* input: a pointer to a Tree
* output: none
*
* frees the given Tree and all of Data elements
*/
void freeTree( Tree *t ){
    freeTreeContents(t->root, t->type);
    free(t); 
} 
void freeTreeContents( TNode *root, treeType type ){
    if(root==NULL)
        return;
    freeTreeContents(root->pLeft, type);
    freeTreeContents(root->pRight, type);
    if(root->leaf==false){
        if(type==AVL && root->data!=NULL)
            freeData(root->data);
        if(type==HUFFMAN && root->str!=NULL)
            free(root->str);
    } 
    free(root);
}

/**********  Functions for searching an AVL tree **********/

/* searchTree and searchTreeRec
 * input: a pointer to a Tree, a Data* tData
 * output: a pointer to the TNode that contains tData or, if no such node exists, NULL
 *
 * Finds and returns a pointer to the TNode that contains tData or, if no such node exists, it returns a NULL
 */
TNode* searchTree( Tree *t, Data* tData ){
    return searchTreeRec( t->root, tData );
}

TNode* searchTreeRec( TNode *root, Data* tData ){
    if( root==NULL || compareData( tData, root->data ) == 0 )
        return root;
    else if( compareData( tData, root->data ) < 0 )
        return searchTreeRec( root->pLeft, tData );
    else /* compareData( tData, root->data ) > 0 */
        return searchTreeRec( root->pRight, tData );
}

void insertAtTNode( TNode *ins, Data* tData ){
    if( !ins->leaf ){
        fprintf( stderr, "inserting into non-leaf node\n" );
        exit(-1); 
    } 
    attachLeafNodes( ins );
    updateHeights( ins );
    /* Put data in the node returned by search */
    ins->data = tData;
    ins->str = NULL;
} 

/* insertTree
    * input: a pointer to a Tree, a Data*
    * output: none
    *
    * Stores the passed Data* into the Tree following BST order, Does not rebalance tree */ 
void insertTree( Tree *t, Data* tData ){
    TNode* ins = searchTree( t, tData );
    insertAtTNode( ins, tData );
}
/* insertTreeBalanced
    * input: a pointer to a Tree, a Data*
    * output: none
    *
    * Stores the passed Data* into the Tree following BST order and rebalances the tree */ 
void insertTreeBalanced( Tree *t, Data* tData ){
    TNode* ins = searchTree( t, tData );
    insertAtTNode( ins, tData );
    rebalanceTree( t, ins );
} 
/* removeTree
    * input: a pointer to a Tree
    * output: a Data*
    *
    * Remove and returns the Data* with the specified key or NULL if its not in the tree */ 
Data* removeTree( Tree *t, char* key ){
    Data temp; 
    Data* ret;
    TNode *del, *update;
    TNode **parentDelPtr;
    temp.key = key;
    del = searchTree( t, &temp );
    ret = del->data;
    if( del->leaf == true )
        return NULL;
    /* Get previous node's pointer to del */
    if( del->pParent==NULL )
        parentDelPtr = &t->root;    /* del is the root */
    else
        parentDelPtr = del->pParent->pLeft==del ? &del->pParent->pLeft : &del->pParent->pRight; /* check if del if left or right child of its parent */
    /* del has no left child */
    if( del->pLeft->leaf==true ){
        free( del->pLeft );
        *parentDelPtr = del->pRight;
        update = del->pRight->pParent = del->pParent;
        free( del );
    } 
    /* del has no right child */
    else if( del->pRight->leaf==true ){
        free( del->pRight );
        *parentDelPtr = del->pLeft;
        update = del->pLeft->pParent = del->pParent;
        free( del );
    } 
    /* del has two children */
    else{
        TNode *next = removeNextInorder( &del->pRight );
        update = next->pParent;
        del->data = next->data;
        free(next);
    } 
    /* Update the heights and rebalance around the node update */
    updateHeights(update);
    rebalanceTree(t, update);
    return ret;
}

TNode* removeNextInorder( TNode** pRoot ){
    TNode* temp = *pRoot;
    if( temp->pLeft->leaf == true ){
        *pRoot = temp->pRight;
        temp->pRight->pParent = temp->pParent;
        free( temp->pLeft );
    } else 
        temp = removeNextInorder( &temp->pLeft );
    return temp;
}

int subTreeHeight(TNode* root){
    return root->height;
} 

/* updateHeights
* input: a pointer to a TNode
* output: none
*
* Recursively recomputes the height of the current node and then recurses on
the nodes parent
*/
void updateHeights(TNode* root){
    if(root!=NULL){
        root->height = subTreeHeight(root->pLeft)>subTreeHeight(root->pRight) ?
        subTreeHeight(root->pLeft) : subTreeHeight(root->pRight);
        root->height = root->height + 1;
        updateHeights( root->pParent );
    }
}

/* rebalanceTree
* input: a pointer to a tree and a pointer to TNode
* output: none
*
* Should attempt to rebalance the tree starting at x and going up through the
root (i.e., until it reaches null).
* After this function runs, every node should be balanced (i.e. -2 < balance <
2). * 
* Hint: The t->root will need to be updated if you do a rotate on the current
root.
*/
void rebalanceTree(Tree* t, TNode* x){
    //TODO
    TNode* z;
    while(x != NULL){ //loop runs as long as x isn't NULL
        if(getBalance(x) == 2 || getBalance(x) == -2){ // if the balance of x if either 2 or -2
            z = getTallerSubTree(x); // set z to the child of x with the taller height are different
        } 
        if(getBalance(x) == 2){ //if the balance of x equal to two then rotate to the right
            if((isSameSignBalance(x, z)) == false){ //if the balances of x and z
                if(getBalance(z) >= 0){ //if the sign is positive
                    rightRotate(z);
                }
                else if(getBalance(z) < 0) { // if the sign is negative
                    leftRotate(z);
                }
                rightRotate(x);
            }
                if(getBalance(x) == -2){ //if the balance of x equals -2 then rotate
                    leftRotate(x);
                }
            if(x == t -> root){ //
                t -> root = x -> pParent; //update the root to the parent of x
            }
        } 
            x = x ->pParent;
    }
} 

/* rightRotate and leftRotate
    * input: a pointer to a TNode
    * output: none
    *
    * Performs specified rotation around a given node
    */
void rightRotate(TNode* oldRoot){
    TNode *newRoot = oldRoot->pLeft;
    if( oldRoot->pParent!=NULL ){
        if( oldRoot->pParent->pLeft==oldRoot )
            oldRoot->pParent->pLeft = oldRoot->pLeft;
        else
            oldRoot->pParent->pRight = oldRoot->pLeft;
            newRoot->pParent = oldRoot->pParent;
            oldRoot->pLeft = newRoot->pRight;
        if( newRoot->pRight!=NULL )
            newRoot->pRight->pParent = oldRoot;
            oldRoot->pParent = newRoot;
            newRoot->pRight = oldRoot;
            updateHeights( oldRoot );
    }
}

TNode* getTallerSubTree(TNode* x){
    if(x -> pLeft -> height > x -> pRight -> height) { //if left subtree is taller than return that node
        return x -> pLeft;
    } else{ 
        return x -> pRight;
    }
} 

bool isSameSignBalance(TNode* x, TNode* z){
    if(((getBalance(x) <= 0) && (getBalance(z) <= 0)) || ((getBalance(x) >= 0) && (getBalance(z) >= 0))){ //if both nodes >= 0 or <= 0
        return true;
    } else{ 
        return false;
    }
} 

void leftRotate(TNode* oldRoot){
    TNode *newRoot = oldRoot->pRight;
    if( oldRoot->pParent!=NULL ){
        if( oldRoot->pParent->pRight==oldRoot )
            oldRoot->pParent->pRight = oldRoot->pRight;
        else
            oldRoot->pParent->pLeft = oldRoot->pRight;
    }
    newRoot->pParent = oldRoot->pParent;
    oldRoot->pRight = newRoot->pLeft;
    if( newRoot->pLeft!=NULL )
        newRoot->pLeft->pParent = oldRoot;
        oldRoot->pParent = newRoot;

    newRoot->pLeft = oldRoot;
    updateHeights( oldRoot );
}

/* getBalance
    * input: a pointer to a TNode
    * output: none
    *
    * Finds the balance of the given node
    */
int getBalance(TNode* root){
    if(root->leaf==true)
        return 0;
    return subTreeHeight(root->pLeft) - subTreeHeight(root->pRight);
}

/**********  Functions for getting Huffman Encoding **********/
/* printHuffmanEncoding
    * input: a pointer to TNode and a char
    * output: none
    *
    * This function prints the Huffman encoding for the char c.  This encoding is based on the given Huffman tree.
    * */
void printHuffmanEncoding( TNode* root, char c ){
    //TODO
    char huff[2] = {c, '\0'};
    if(!root -> leaf) {
        if(strcmp(root -> str, huff) == 0) {
            return;
        }
        if(root -> pRight != NULL) { //if node is not NULL
            if(strchr(root -> pRight -> str, c) != NULL){ //if c is in the string and is not null
                printf("%c", 49); //prints a 1
                printHuffmanEncoding(root->pRight, c); //recursive call
            }
        }
        if(root -> pLeft != NULL) { //if node is not NULL
            if(strchr(root -> pLeft -> str, c) != NULL) {
                printf("%c", 48); // prints a 0
                printHuffmanEncoding(root->pLeft, c); //recursive call
            } 
        } 
    }
} 

/**********  Functions for Segment Tree **********/
/* constructSegmentTree
    * input: an array of doubles, an int low, an int high
    * output: the root of a tree
    *
    * Recursively builds a balanced tree containing all of the data in array points from index low to index high.
    */
TNode* constructSegmentTree( double* points, int low, int high ){
    TNode* root = (TNode*)malloc( sizeof(TNode) );
    root->cnt = 0;
    root->low = points[low];
    root->high = points[high];
    root->leaf = false;
    root->pParent = NULL;
    /* Recursively split the array around the mid point of the high and low indices */
    int mid = (high - low)/2 + low;
    if( low==high ) /* only one node left in the sub-array */
        attachLeafNodes( root );
    else
        attachChildNodes( root, constructSegmentTree( points, low, mid ),
        constructSegmentTree( points, mid+1, high ) );
    return root;
}

/* insertSegment
    * input: the root of a tree, a double segmentStart, and a double segmentEnd
    * output: none
    *
    * Recursively inserts the line segment from segmentStart to segmentEnd into the tree */ 
void insertSegment( TNode* root, double segmentStart, double segmentEnd ) {
    //TODO
    if (root -> leaf){ //
        return;
    } else if ((root -> high < segmentStart && root -> high < segmentEnd ) ||( root -> low > segmentEnd && root -> low > segmentStart)){ // if the segment is completely to the left or right of the nodes range
        return; } 
    else if (root -> high <= segmentEnd && root -> low >= segmentStart){ //if the segment completely covers the range represented by this node
        root -> cnt++;
        return;
    } else{
        insertSegment(root -> pRight, segmentStart, segmentEnd);
        insertSegment(root -> pLeft, segmentStart, segmentEnd);
    }
}

/* lineStabQuery
    * input: the root of a tree, a double queryPoint
    * output: none
    *
    * Recursively count the number of line segments which intersect the queryPoint.
    */
int lineStabQuery( TNode* root, double queryPoint ){
    //TODO
    if(root -> leaf) { //if the root is leaf
        return 0;
    } 
    else if(root -> high < queryPoint || root -> low > queryPoint){ //completely to the left or right of the nodes range
        return 0;
    } 
    else {
        return root -> cnt + lineStabQuery(root->pRight, queryPoint) +
        lineStabQuery(root->pLeft, queryPoint);
    }
} 

/**********  Functions for debugging an AVL tree **********/
/* printTree
* input: a pointer to a Tree
* output: none
*
* Prints the contents of the tree below the root node
*/
void printTree( TNode* root ){
    int i;
    if(root->leaf!=true){
        printTree(root->pLeft);
        for( i=1; i<root->height; i++){
            printf("\t");
        }
        printf("%s\n",root->data->key);
        printTree(root->pRight);
    } 
} 

/* checkAVLTree
* input: a pointer to a Tree
* output: none
*
* Prints error messages if there are any problems with the AVL tree
*/
void checkAVLTree(TNode* root){
    if(root->leaf != true){
        if( getBalance(root)>1 ||  getBalance(root)<-1 )
            printf("ERROR - Node %s had balance %d\n",root->data->key,getBalance(root) );
        if( root->pLeft!=NULL && root->pLeft->pParent!=root )
            printf("ERROR - Invalid edge at %s-%s\n",root->data->key,root->pLeft->data->key );
        if( root->pRight!=NULL && root->pRight->pParent!=root )
            printf("ERROR - Invalid edge at %s-%s\n",root->data->key,root->pRight->data->key );
        checkAVLTree(root->pLeft);
        checkAVLTree(root->pRight);
    }
}