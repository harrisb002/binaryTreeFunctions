//
// Created by Ben Harris on 3/7/23.
//

// Ben Harris

#include "BinSearchTree.hpp"
#include <iostream>
#include <queue>

BinSearchTree::BinSearchTree(): root{nullptr} {}

TreeNode *BinSearchTree::insert( TreeNode *root, int v ) {
    if( root == nullptr )
        return new TreeNode( v );
    if( root->value() < v )
        root->rightSubtree( insert( root->rightSubtree(), v ) );
    else
        root->leftSubtree( insert( root->leftSubtree(), v ) );
    return root;
}

void BinSearchTree::insert(int v) {
    // Insert v in the tree if it is not already a member.
    if( ! find(v) )
        root = insert(root, v);
}

int BinSearchTree::size() {
    return size(root);
}
int BinSearchTree::size(TreeNode *currRoot) {
    if(currRoot == nullptr)
        return 0;
    return 1 + size(currRoot->leftSubtree()) + size(currRoot->rightSubtree());
}

bool BinSearchTree::find(int v) {
    return find(root, v);
}
bool BinSearchTree::find(TreeNode *currRoot, int v){
    if(currRoot == nullptr)
        return false;
    if(currRoot->value() == v)
        return true;
    if(currRoot->value() > v)
        return find(currRoot->leftSubtree(), v);
    return find(currRoot->rightSubtree(), v);
}

//returns true if v is a member of the values stored in the tree.
//Otherwise, it returns false. You should write a recursive implementation for this function.
bool BinSearchTree::iterFind( int v ){
    TreeNode * currNode = root;
    while(currNode != nullptr){
        if(currNode->value() == v)
            return true;
        else if(currNode->value() > v)
            currNode = currNode ->leftSubtree();
        else
            currNode = currNode ->rightSubtree();
    }
    return false;
}

void BinSearchTree::inorderDump(){
    inorderDump(root);
}
void BinSearchTree::inorderDump(TreeNode * currNode){
    if(currNode == nullptr)
        return;
    inorderDump(currNode->leftSubtree());
    std::cout << currNode->value() << std::endl;
    inorderDump(currNode->rightSubtree());
}

//returns the depth of the tree. The root of the tree is at depth 1.
//The depth of each of the child-nodes of the root,
//if it exists, is at 2. etc. Write a recursive solution for this function.
int BinSearchTree::maxDepth(){
    return maxDepth(root);
}
int BinSearchTree::maxDepth(TreeNode * currNode){
    if(currNode == nullptr)
        return 0;
    if(currNode -> leftSubtree() == nullptr && currNode-> rightSubtree() == nullptr)
        return 1;
    return std::max(maxDepth(currNode->rightSubtree()) + 1, maxDepth(currNode->leftSubtree()) + 1);
}

// This function should delete every node in the tree.
// To do that, you will have to recursively traverse the tree, using
// a post-order traversal.
BinSearchTree::~BinSearchTree() {
    deletingHelper(root);
}
void BinSearchTree::deletingHelper(TreeNode * currNode){
    if(currNode == nullptr)
        return;

    deletingHelper(currNode->leftSubtree());
    deletingHelper(currNode->rightSubtree());
    delete currNode;
}

// Prints the values in the tree, one per line, using a level-order traversal.
// You must write an iterative solution using a FCFS queue.
void BinSearchTree::levelOrderDump(){
    levelOrderDump(root);
}
void BinSearchTree::levelOrderDump(TreeNode *root) {
    if (root == nullptr)
        return;

    std::queue<TreeNode*> q;
    q.push(root); //Push root onto queue
    while (!q.empty()) { //While queue is not empty
        int size = q.size(); //Make size of queue equal to the number of nodes at curr level
        for (int i = 0; i < size; i++) { //Loop till all values at curr level have been popped off queue
            TreeNode* currNode = q.front();
            q.pop(); //take the last value printed off queue, first one is the root
            std::cout << currNode->value() << std::endl;
            if (currNode->leftSubtree() != nullptr)
                q.push(currNode->leftSubtree());

            if (currNode->rightSubtree() != nullptr)
                q.push(currNode->rightSubtree());
        }
    }
}

// Returns the "k-th smallest" value in the tree.
// The pre-condition for this function is: size() >= k.
// Returns zero if the pre-condition is not met.
// Write a recursive solution for this function.
int BinSearchTree::kthSmallest(int k){
    if(size(root) < k) //Test precondition
        return 0;

    return kthSmallest(root, k);
}
int BinSearchTree::kthSmallest(TreeNode *smallest, int k) {
    //Once the size of the leftSubtree is = k-1 the current node is the smallest
    if(size(smallest->leftSubtree()) == k-1)
        return smallest->value();

    if (size(smallest->leftSubtree()) < k-1) // If true must be in right subtree
        return kthSmallest(smallest->rightSubtree(), k - size(smallest->leftSubtree()) - 1);
    else return kthSmallest(smallest->leftSubtree(), k);
}

// Prints a list of values at level k in the tree, in increasing order of values.
// The level of the root node is 1. That is, valuesAtLevel( 1 ) should print the value at the root-node of the tree.
// The children of root, if any, are at level 2, etc. Write a recursive solution for this function.
void BinSearchTree::valuesAtLevel( int k ){
    return valuesAtLevel(root, k, 1);
}
void BinSearchTree::valuesAtLevel(TreeNode *currNode, int k, int depth){
    if (currNode == nullptr)
        return;

    if (depth == k)
        std::cout << currNode->value() << std::endl;

    valuesAtLevel(currNode->leftSubtree(), k, depth+1);
    valuesAtLevel(currNode->rightSubtree(), k, depth+1);
}

// Same as valuesAtLevel except this one is to be implemented iteratively.
void BinSearchTree::iterValuesAtLevel( int k ){
    if (root == nullptr || k < 1)
        return;

    std::queue<TreeNode*> q;
    q.push(root);
    int depth = 1;
    while (!q.empty()) {
        int size = q.size(); //Make size of queue equal to the number of nodes at curr level
        if (depth == k) {
            for (int i = 0; i < size; i++) { //Loop till all values at curr level have been popped off queue
                TreeNode* currNode = q.front();
                q.pop(); //take the last value printed off queue, first one is the root
                std::cout << currNode->value() << std::endl;
                if (currNode->leftSubtree() != nullptr)
                    q.push(currNode->leftSubtree());
                if (currNode->rightSubtree() != nullptr)
                    q.push(currNode->rightSubtree());
            }
            return;
        }
        for (int i = 0; i < size; i++) {
            TreeNode* node = q.front();
            q.pop();
            if (node->leftSubtree() != nullptr)
                q.push(node->leftSubtree());
            if (node->rightSubtree() != nullptr)
                q.push(node->rightSubtree());
        }
        depth++;
    }
}

// Using an iterative algorithm,find the depth of the tree.
// The root of the tree is at depth 1,the root of each
// of the child nodes of the root, if its exists, is at depth 2, etc.
int BinSearchTree::iterMaxDepth(){
    if (root == nullptr)
        return 1;

    std::queue<TreeNode*> q;
    q.push(root);
    int depth = 0;
    while (!q.empty()) {
        depth++;
        int levelSize = q.size();
        for (int i = 0; i < levelSize; i++) {
            TreeNode* currNode = q.front();
            q.pop();
            if (currNode->leftSubtree() != nullptr)
                q.push(currNode->leftSubtree());
            if (currNode->rightSubtree() != nullptr)
                q.push(currNode->rightSubtree());
        }
    }
    return depth;
}

// Returns true if the tree in bst is structurally identical
// to that of the tree maintained by the callee.
// Otherwise, it returns false. Write a recursive solution for this function.
bool BinSearchTree::areIdentical( BinSearchTree *bst ){
    return areIdentical(root, bst->root);
}
bool BinSearchTree::areIdentical(TreeNode *currNode, TreeNode *bstRoot ){
    if (currNode == nullptr && bstRoot == nullptr)
        return true;
    if (currNode == nullptr || bstRoot == nullptr)
        return false;
    if (currNode->value() != bstRoot->value())
        return false;
    return areIdentical(currNode->leftSubtree(), bstRoot->leftSubtree()) &&
            areIdentical(currNode->rightSubtree(), bstRoot->rightSubtree());
}

// Computes and returns, an instance of BinSearchTree,
// The set intersection of the tree in bst and the callee.
// Write a recursive solution for this function and feel free to use helper functions if necessary.
BinSearchTree* BinSearchTree::intersectWith( BinSearchTree * bst) {
    BinSearchTree *result = new BinSearchTree();
    if (bst == nullptr || root == nullptr)
        return result;

    return intersectWith(bst->root, result);
}
BinSearchTree* BinSearchTree::intersectWith(TreeNode * bst, BinSearchTree * result) {
    if (find(bst->value()))  //If value is in callee tree then insert into result
        result->insert(bst->value());
    if (bst->leftSubtree() != nullptr)
        intersectWith(bst->leftSubtree(), result);
    if (bst->rightSubtree() != nullptr)
        intersectWith(bst->rightSubtree(), result);
    return result;
}

// Computes and returns, in an instance of BinSearchTree, the set difference of the tree in bst
// And that of the callee. As you know, set difference is not a commutative operation.
// So, what is returned is T(bst) - T(callee), where T(bst) and T(callee) refer to the trees
// Of the bst and callee, respectively. What is in A, but not in B i:e result = [A - B]
BinSearchTree* BinSearchTree::differenceOf(BinSearchTree *bst){
    BinSearchTree *result = new BinSearchTree();
    if(areIdentical(root, bst->root))
        return result;

    return differenceOf(this, bst->root, result);
}

BinSearchTree* BinSearchTree::differenceOf(BinSearchTree * t1, TreeNode * bst, BinSearchTree * result) {
    if (! t1->find(bst->value())){
        result->insert(bst->value()); //If value is t1 then dont insert into result
    }
    if (bst->leftSubtree() != nullptr)
        differenceOf(t1, bst->leftSubtree(), result);
    if (bst->rightSubtree() != nullptr)
        differenceOf(t1, bst->rightSubtree(), result);

    return result;
}

// Returns true if there is a root-to-leaf path in the tree
// Where the sum of the values on that path is equal to the input argument,sum.
// Otherwise, it returns false. You should write a recursive solution for this function
bool BinSearchTree::hasRootToLeafSum( int sum ){
    return hasRootToLeafSum(root, sum);

}
bool BinSearchTree::hasRootToLeafSum(TreeNode* currNode, int sum) {
    if (currNode == nullptr)
        return false;

    if (currNode->leftSubtree() == nullptr && currNode->rightSubtree() == nullptr && (sum - currNode->value()) == 0)
        return true;

    return hasRootToLeafSum(currNode->leftSubtree(), sum - currNode->value()) ||
           hasRootToLeafSum(currNode->rightSubtree(), sum - currNode->value());
}

// Computes and returns, in an instance of BinSearchTree, the set union
// Of the tree in bst and that of the callee. Write a recursive solution
// For this function and feel free to use helper functions if necessary.
BinSearchTree* BinSearchTree::unionWith(BinSearchTree * bst){
    BinSearchTree *result = new BinSearchTree();
    if (bst == nullptr && root == nullptr)
        return result;
    if(bst == nullptr)
        return this;
    if(root == nullptr)
        return bst;

    result->root = cloneBST(bst->root);
    return unionWith(root, result);
}

//Copy one tree and then insert other tree values into iy
BinSearchTree* BinSearchTree::unionWith(TreeNode * t1, BinSearchTree * result) {
    if (! result->find(t1->value())){
        result->insert(t1->value()); //If value is in result then dont insert
    }
    if (t1->leftSubtree() != nullptr)
        unionWith(t1->leftSubtree(), result);
    if (t1->rightSubtree() != nullptr)
        unionWith(t1->rightSubtree(), result);

    return result;
}

// Function to clone Binary Search Tree - Used for unionWith function
TreeNode* BinSearchTree::cloneBST(TreeNode* root) {
    if (root == nullptr) {
        return nullptr;
    }
    // Create a new node with the same value as root
    TreeNode* newRoot = new TreeNode(root->value());
    // Recursively clone left and right subtrees
    newRoot->leftSubtree(cloneBST(root->leftSubtree()));
    newRoot->rightSubtree(cloneBST(root->rightSubtree()));
    return newRoot;
}

// Removes the node containing the value v from the tree, if it exists.
// It returns true if the value was in the tree and false otherwise.
// You can choose to write an iterative solution or a recursive solution for this function.
bool BinSearchTree::remove( int v ) {
    TreeNode *currNode = root, *prevNode = nullptr, *parentNode = nullptr, *successor = nullptr;
    if (!find(v)) // If value not present in tree
        return false;

    while (currNode != nullptr) {
        if (currNode->value() == v) {  // Once node w/value is found

            // If last element in tree then make root null and return true
            if(prevNode == nullptr && currNode->leftSubtree() == nullptr && currNode->rightSubtree() == nullptr){
                root = nullptr;
                return true;
            }

            // Root case is checked here
            if(prevNode == nullptr){
                if(currNode->rightSubtree() != nullptr){ // If root has a right subtree then find successor
                    successor = currNode->rightSubtree(); // Find In-Order successor of node being deleted
                    while (successor->leftSubtree() != nullptr) {
                        parentNode = successor;
                        successor = successor->leftSubtree(); // Use In-Order successor to replace the deleted node
                    }
                    currNode->value() = successor->value(); // Make root equal to value of successor

                    if(parentNode == nullptr){ // The deleted nodes first right child has no left child
                        if(successor->rightSubtree() == nullptr) // If Successor does not have right subtree
                            currNode->rightSubtree(nullptr); // Delete Successor
                        else currNode->rightSubtree(successor->rightSubtree());

                        return true;
                    }
                    if (successor->rightSubtree() == nullptr)
                        parentNode->leftSubtree(nullptr);  // Delete the successor
                    else parentNode->leftSubtree(successor->rightSubtree());

                    return true;
                }

                else { //Deleted node does not have successor and must use predecessor(named as successor here)
                    successor = currNode->leftSubtree(); // Find In-Order predecessor of node being deleted
                    while (successor->rightSubtree() != nullptr) {
                        parentNode = successor;
                        successor = successor->rightSubtree(); // Use In-Order predecessor to replace the deleted node
                    }
                    currNode->value() = successor->value(); // Make root equal to value of predecessor

                    if(parentNode == nullptr){ // If predecessor is first child of deleted node
                        if(successor->leftSubtree() == nullptr) // If predecessor does not have left subtree
                            currNode->leftSubtree(nullptr); // Delete predecessor
                        else currNode->leftSubtree(successor->leftSubtree());

                        return true;
                    }

                    if (successor->leftSubtree() != nullptr)  // If predecessor node has a left subtree
                        parentNode->rightSubtree(successor->leftSubtree());
                    else parentNode->rightSubtree(nullptr); // Delete the predecessor

                    return true;
                }

            }
            // If node is not the root then check other cases

            // If node has no children
            if (currNode->leftSubtree() == nullptr && currNode->rightSubtree() == nullptr) { // leaf deletion
                if(prevNode->leftSubtree() == currNode){ // If deleted node is on Left Subtree of parent
                    prevNode->leftSubtree(nullptr);
                } else prevNode->rightSubtree(nullptr); // If deleted node is on Right Subtree of parent

                return true;
            }

            //Single Child deletion
            if (currNode->leftSubtree() == nullptr || currNode->rightSubtree() == nullptr) {
                if(prevNode->leftSubtree() == currNode) { // If deleted node is on Left Subtree of parent
                    if (currNode->leftSubtree() == nullptr) { // If child to deleted node is in the right subtree
                        prevNode->leftSubtree(currNode->rightSubtree());
                    } else prevNode->leftSubtree(currNode->leftSubtree());
                }
                else {// If deleted node is on right Subtree of parent
                    if (currNode->leftSubtree() == nullptr) { // If child to deleted node is in the left subtree
                        prevNode->rightSubtree(currNode->rightSubtree());
                    } else prevNode->rightSubtree(currNode->leftSubtree());
                }
                return true;
            }

            else{ // Node has two children
                if(currNode->rightSubtree() != nullptr) { // If root has a right subtree then find successor
                    successor = currNode->rightSubtree(); // Find In-Order successor of node being deleted
                    while (successor->leftSubtree() != nullptr) {
                        parentNode = successor;
                        successor = successor->leftSubtree(); // Use In-Order successor to replace the deleted node
                    }
                    currNode->value() = successor->value(); // Make deleted node equal to successor

                    if(parentNode == nullptr){ // If Successor is first child of deleted node
                        if(successor->rightSubtree() == nullptr) // If Successor does not have right subtree
                            currNode->rightSubtree(nullptr); // Delete Successor
                        else currNode->rightSubtree(successor->rightSubtree());
                        return true;
                    }
                    if (successor->rightSubtree() == nullptr) { // If successor does not have  a right child
                        parentNode->leftSubtree(nullptr);
                    }
                    else  parentNode->leftSubtree(successor->rightSubtree());

                    return true;
                }

                //Deleted node does not have successor and must use predecessor
                else { //Deleted node does not have successor and must use predecessor(named as successor here)
                    successor = currNode->leftSubtree(); // Find In-Order predecessor of node being deleted
                    while (successor->rightSubtree() != nullptr) {
                        parentNode = successor;
                        successor = successor->rightSubtree(); // Use In-Order predecessor to replace the deleted node
                    }
                    currNode->value() = successor->value(); // Make root equal to value of predecessor

                    if(parentNode == nullptr){ // If predecessor is first child of deleted node
                        if(successor->leftSubtree() == nullptr) // If predecessor does not have left subtree
                            currNode->leftSubtree(nullptr); // Delete predecessor
                        else currNode->leftSubtree(successor->leftSubtree());

                        return true;
                    }

                    if (successor->leftSubtree() != nullptr)  // If predecessor node has a left subtree
                        parentNode->rightSubtree(successor->leftSubtree());
                    else parentNode->rightSubtree(nullptr); // Delete the predecessor

                    return true;
                }
            }
        }
            // Search for node w/value
        else if (currNode->value() > v) {
            prevNode = currNode; // Keep track of parent node of node being deleted
            currNode = currNode->leftSubtree();
        }
        else {
            prevNode = currNode; // Keep track of parent node of node being deleted
            currNode = currNode->rightSubtree();
        }
    }

    return false;  // Should never reach this statement
}















