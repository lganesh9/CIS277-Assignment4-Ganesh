#include <iostream>
#include <vector>
#include "TreeExplorer.h"

static int fails = 0;

static void printVec(const std::vector<int>& v){
    for(std::size_t i = 0; i < v.size(); ++i)
        std::cout << v[i] << (i + 1 < v.size() ? " " : "\n");
}

static void checkVec(const char* name, const std::vector<int>& got, const std::vector<int>& want){
    if(got == want){
        std::cout << "PASS " << name << "\n";
    }else{
        std::cout << "FAIL " << name << "\n  got:  "; printVec(got);
        std::cout << "  want: "; printVec(want);
        ++fails;
    }
}

static void checkNum(const char* name, long long got, long long want){
    if(got == want)
        std::cout << "PASS " << name << " = " << got << "\n";
    else{
        std::cout << "FAIL " << name << " got " << got << " want " << want << "\n";
        ++fails;
    }
}

int main(){
    // 1) empty tree + repeated destroy on a null root
    {
        TreeNode* t = nullptr;
        checkVec("1 preorder empty",  preorder(t),  {});
        checkVec("1 inorder empty",   inorder(t),   {});
        checkVec("1 postorder empty", postorder(t), {});
        checkVec("1 level empty",     levelOrder(t),{});
        checkNum("1 nodes",  countNodes(t),  0);
        checkNum("1 leaves", countLeaves(t), 0);
        checkNum("1 height", treeHeight(t), 0);
        checkNum("1 sum",    sumValues(t),   0);
        destroyTree(t);
        destroyTree(t);
        checkNum("1 still null after double destroy", t == nullptr, 1);
    }

    // 2) singleton -4
    {
        TreeNode* s = new TreeNode{-4};
        checkVec("2 preorder",  preorder(s),  {-4});
        checkVec("2 inorder",   inorder(s),   {-4});
        checkVec("2 postorder", postorder(s), {-4});
        checkVec("2 level",     levelOrder(s),{-4});
        checkNum("2 nodes",  countNodes(s),  1);
        checkNum("2 leaves", countLeaves(s), 1);
        checkNum("2 height", treeHeight(s),  1);
        checkNum("2 sum",    sumValues(s),  -4);
        destroyTree(s);
    }

    // 3) left-only and right-only chains of 4 nodes
    {
        TreeNode* l = new TreeNode{10};
        l->left = new TreeNode{20};
        l->left->left = new TreeNode{30};
        l->left->left->left = new TreeNode{40};
        checkVec("3 left preorder",  preorder(l),  {10,20,30,40});
        checkVec("3 left inorder",   inorder(l),   {40,30,20,10});
        checkVec("3 left postorder", postorder(l), {40,30,20,10});
        checkVec("3 left level",     levelOrder(l),{10,20,30,40});
        checkNum("3 left nodes",  countNodes(l),  4);
        checkNum("3 left leaves", countLeaves(l), 1);
        checkNum("3 left height", treeHeight(l),  4);
        checkNum("3 left sum",    sumValues(l),   100);
        destroyTree(l);

        TreeNode* r = new TreeNode{1};
        r->right = new TreeNode{2};
        r->right->right = new TreeNode{3};
        r->right->right->right = new TreeNode{4};
        checkVec("3 right preorder",  preorder(r),  {1,2,3,4});
        checkVec("3 right inorder",   inorder(r),   {1,2,3,4});
        checkVec("3 right postorder", postorder(r), {4,3,2,1});
        checkVec("3 right level",     levelOrder(r),{1,2,3,4});
        checkNum("3 right leaves", countLeaves(r), 1);
        checkNum("3 right height", treeHeight(r),  4);
        checkNum("3 right sum",    sumValues(r),   10);
        destroyTree(r);
    }

    // 4) duplicate, zero and negative values
    //        0
    //       / \
    //     -2    5
    //     / \     \
    //    0   -2    5
    {
        TreeNode* d = new TreeNode{0};
        d->left = new TreeNode{-2};
        d->right = new TreeNode{5};
        d->left->left = new TreeNode{0};
        d->left->right = new TreeNode{-2};
        d->right->right = new TreeNode{5};
        checkVec("4 preorder",  preorder(d),  {0,-2,0,-2,5,5});
        checkVec("4 inorder",   inorder(d),   {0,-2,-2,0,5,5});
        checkVec("4 postorder", postorder(d), {0,-2,-2,5,5,0});
        checkVec("4 level",     levelOrder(d),{0,-2,5,0,-2,5});
        checkNum("4 nodes (no merging)", countNodes(d),  6);
        checkNum("4 leaves", countLeaves(d), 3);
        checkNum("4 height", treeHeight(d),  3);
        checkNum("4 sum",    sumValues(d),   6);
        destroyTree(d);
    }

    // 5) repeated calls + editing a returned vector
    {
        TreeNode* a = new TreeNode{50};
        a->left = new TreeNode{30};
        a->right = new TreeNode{70};
        std::vector<int> copy1 = inorder(a);
        copy1[0] = 999;                       // modify the returned copy only
        checkVec("5 inorder after editing copy",  inorder(a),  {30,50,70});
        checkVec("5 preorder after editing copy", preorder(a), {50,30,70});
        checkVec("5 level repeated call",         levelOrder(a),{50,30,70});
        destroyTree(a);
    }

    // 6) destroy, rebuild fresh, destroy again
    {
        TreeNode* t = new TreeNode{5};
        t->left = new TreeNode{3};
        destroyTree(t);
        checkNum("6 null after destroy", t == nullptr, 1);
        t = new TreeNode{8};
        t->left = new TreeNode{3};
        t->right = new TreeNode{10};
        checkVec("6 rebuilt preorder", preorder(t), {8,3,10});
        checkNum("6 rebuilt nodes",    countNodes(t), 3);
        destroyTree(t);
        checkNum("6 null after 2nd destroy", t == nullptr, 1);
    }

    // 7) own test: sum must survive int overflow (sumValues returns long long)
    {
        TreeNode* b = new TreeNode{2000000000};
        b->right = new TreeNode{2000000000};
        checkNum("7 sum beyond int range", sumValues(b), 4000000000LL);
        destroyTree(b);
    }

    if(fails == 0) std::cout << "\nALL TESTS PASS\n";
    else std::cout << "\n" << fails << " CHECK(S) FAILED\n";
    return fails == 0 ? 0 : 1;
}