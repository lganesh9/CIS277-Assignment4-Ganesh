#include "TreeExplorer.h"
#include <queue>
#include <algorithm>

static void preorderHelper(const TreeNode* node, std::vector<int> &output){
    if(node == nullptr)
    return;
    output.push_back(node->value);
    preorderHelper(node->left, output);
    preorderHelper(node->right, output);
}

static void inorderHelper(const TreeNode* node, std::vector<int> &output){
    if(node == nullptr)
    return;
    inorderHelper(node->left, output);
    output.push_back(node->value);
    inorderHelper(node->right, output);
}

static void postorderHelper(const TreeNode* node, std::vector<int> &output){
    if(node == nullptr)
    return;
    postorderHelper(node->left, output);
    postorderHelper(node->right, output);
    output.push_back(node->value);
}


std::vector<int> preorder(const TreeNode* root){
    std::vector<int> output;
    preorderHelper(root, output);
    return output;
}

std::vector<int> inorder(const TreeNode* root){
    std::vector<int> output;
    inorderHelper(root, output);
    return output;
}

std::vector<int> postorder(const TreeNode* root){
    std::vector<int> output;
    postorderHelper(root, output);
    return output;
}

std::vector<int> levelOrder(const TreeNode* root){
    if(root == nullptr)
    return{};
    std::vector<int> output;
    std::queue<const TreeNode*> process;
    process.push(root);
    while(!process.empty()){
        const TreeNode*  node = process.front();
        output.push_back(node->value);
        process.pop();
        if(node->left != nullptr)
        process.push(node->left);
        if(node->right != nullptr)
        process.push(node->right);
    }
    return output;
}

std::size_t countNodes(const TreeNode* root){
    if(root == nullptr)
    return 0;
    std::size_t numNode = 1;
    numNode += countNodes(root->left);
    numNode += countNodes(root->right);
    return numNode;
}

std::size_t countLeaves(const TreeNode* root){
    if(root == nullptr)     
    return 0;
    std::size_t numLeaves = 0;
    if(root->left == nullptr && root->right == nullptr)
    numLeaves++;
    numLeaves += countLeaves(root->left);
    numLeaves += countLeaves(root->right);
    return numLeaves;
}

int treeHeight(const TreeNode* root){
    if (root == nullptr)
    return 0;
    return 1 + std::max(treeHeight(root->left), treeHeight(root->right));
}

long long sumValues(const TreeNode* root){
    if (root == nullptr)
    return 0;
    return root->value + sumValues(root->left) + sumValues(root->right);
}

void destroyTree(TreeNode*& root){
    if(root == nullptr)
    return;
    destroyTree(root->left);
    destroyTree(root->right);
    delete root;
    root = nullptr;
}