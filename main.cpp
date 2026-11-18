#include <iostream>
#include "TreeExplorer.h"

using namespace std;

static void print(const std::vector<int>& v){
    for(std::size_t i = 0; i < v.size(); ++i)
        std::cout << v[i] << (i + 1 < v.size() ? " " : "\n");
}

int main(){
    TreeNode* a = new TreeNode{50};
    a->left        = new TreeNode{30};
    a->right       = new TreeNode{70};
    a->left->left  = new TreeNode{20};
    a->left->right = new TreeNode{40};
    a->right->left  = new TreeNode{60};
    a->right->right = new TreeNode{80};

    TreeNode* b = new TreeNode{10};
    b->left         = new TreeNode{30};
    b->right        = new TreeNode{20};
    b->left->right  = new TreeNode{5};
    b->right->right = new TreeNode{15};

    cout << "Tree A\n";
    cout << "Preorder:    "; print(preorder(a));
    cout << "Inorder:     "; print(inorder(a));
    cout << "Postorder:   "; print(postorder(a));
    cout << "Level order: "; print(levelOrder(a));
    cout << "Nodes:  " << countNodes(a)  << "\n";
    cout << "Leaves: " << countLeaves(a) << "\n";
    cout << "Height: " << treeHeight(a)  << "\n";
    cout << "Sum:    " << sumValues(a)   << "\n\n";

    cout << "Tree B\n";
    cout << "Preorder:    "; print(preorder(b));
    cout << "Inorder:     "; print(inorder(b));
    cout << "Postorder:   "; print(postorder(b));
    cout << "Level order: "; print(levelOrder(b));
    cout << "Nodes:  " << countNodes(b)  << "\n";
    cout << "Leaves: " << countLeaves(b) << "\n";
    cout << "Height: " << treeHeight(b)  << "\n";
    cout << "Sum:    " << sumValues(b)   << "\n";

    destroyTree(a);
    destroyTree(b);
    return 0;
}