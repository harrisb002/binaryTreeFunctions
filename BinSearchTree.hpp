//
// Created by Ali Kooshesh on 3/1/23.
//

#ifndef BINSEARCHTREE_BINSEARCHTREE_HPP
#define BINSEARCHTREE_BINSEARCHTREE_HPP


#include "TreeNode.hpp"
class BinSearchTree{
public:
    BinSearchTree();
    void insert( int v );
    bool find( int v );
    bool find(TreeNode *,  int v );
    bool iterFind( int v );
    int size();
    int size(TreeNode *);
    void inorderDump();
    void inorderDump(TreeNode *);
    int maxDepth();
    int maxDepth(TreeNode *);
    ~BinSearchTree();
    void deletingHelper(TreeNode * );

    //Added for Project
    void levelOrderDump();
    void levelOrderDump(TreeNode *);
    int kthSmallest( int k );
    int kthSmallest(TreeNode *, int k);
    void valuesAtLevel( int k );
    void valuesAtLevel(TreeNode *, int k, int depth);
    void iterValuesAtLevel( int k );
    int iterMaxDepth();
    bool areIdentical( BinSearchTree *bst );
    bool areIdentical( TreeNode *, TreeNode *bst);
    BinSearchTree *intersectWith( BinSearchTree *bst );
    BinSearchTree* intersectWith(TreeNode *,BinSearchTree * result);
    BinSearchTree* differenceOf( BinSearchTree *bst );
    BinSearchTree* differenceOf( BinSearchTree * t1, TreeNode * bst, BinSearchTree * result);


//Needs work
    bool remove( int v );
    void splice(TreeNode *, TreeNode *, TreeNode *);
    bool hasRootToLeafSum( int sum );
    bool hasRootToLeafSum(TreeNode * ,int sum);
    BinSearchTree* unionWith( BinSearchTree *bst );
    BinSearchTree* unionWith( TreeNode *, BinSearchTree * result);
    TreeNode* cloneBST(TreeNode* );


        private:
    //TreeNode* local_insert( TreeNode *, int );
    TreeNode* insert( TreeNode *, int );
    // Whatever private members you added for this part
    TreeNode *root;
};


#endif //BINSEARCHTREE_BINSEARCHTREE_HPP
