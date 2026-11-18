# CIS-277 Assignment 4: Binary Tree Explorer
## Student
Logan Ganesh
## Design
The design initally was pretty simple. For the traversal I would use what was taught in class, but when it came to implementation, I could not use the given function without making a helper function. Although I intially planned to not use any, in order to keep up the recursion requirement, I used helper functions. The vector that was used to store the results was made in the inital function then passed to the helper function. To add them, the mehod push_back was used. This is what I originally planned. The intial plan for level order wasn't to use a queue, however after re-reading the instructions, a queue made-much more sense to use. The intial wasn't really properly thought out as I was just going to run tests while I coded. For adding the results to the vector, it was just going to be similar to the earlier traversals, but the queue slightly complicated things. Although not enough to make changes to the original plan. For counting functions, their plans didn't undergo any change. With them just being travered and counted according to the conditions. The base case for all of the functions was to be (root = nullptr) and no changes were made to that. The only time the functions would control the nodes would be for the deleteTree function, where the allocated nodes were released. Besides this, the function made no changes to the tree or the nodes. 
## How to Compile
Requires a C++ compiler such as g++. Open a terminal in the project folder and run: g++ -std=c++23 -Wall -Wextra -pedantic main.cpp TreeExplorer.cpp -o tree_explorer
and:
g++ -std=c++23 -Wall -Wextra -pedantic -I. tests/student_tests.cpp TreeExplorer.cpp -o student_tests
## How to Run
./tree_explorer
./student_tests
## Tests and Results
Test	
Input / shape	
Expected	
Actual

1	
Empty tree + double destroy	
root = nullptr	
all traversals empty; nodes 0, leaves 0, height 0, sum 0; still nullptr after destroyTree twice	
PASS

2	
Singleton	single node -4
every traversal = [-4]; nodes 1, leaves 1, height 1, sum -4	
PASS

3a	
Left-only chain	Chain L	
pre 10 20 30 40; in = post = 40 30 20 10; level 10 20 30 40; nodes 4, leaves 1, height 4, sum 100	

PASS
3b	
Right-only chain	
Chain R	pre = in = level 1 2 3 4; post 4 3 2 1; leaves 1, height 4, sum 10	
PASS

4	
Duplicate/zero/negative	diagram above	
pre 0 -2 0 -2 5 5; in 0 -2 -2 0 5 5; post 0 -2 -2 5 5 0; level 0 -2 5 0 -2 5; nodes 6 (not 3 — nothing merged), leaves 2, height 3, sum 6	
PASS

5	
Repeated calls + edited return value	
50/30/70 tree; edit vector returned by inorder()	next inorder still 30 50 70; preorder unchanged — tree untouched	
PASS

6	
Destroy, rebuild, destroy again	
5 with left child, then rebuild 8(3,10)	
root nullptr after each destroy; rebuilt preorder 8 3 10; nodes 3	
PASS

7	
Own test: long long sum	
2000000000 + right child 2000000000	
sum 4000000000 — exceeds int range, fits long long	
PASS

Memory check
valgrind: unavailable — Linux-only tool, not present on this Windows machine.
AddressSanitizer: attempted with MSYS2 UCRT64 g++ 15.2.0(g++ -std=c++17 -g -fsanitize=address ...). Linker failed with "cannot find -lasan: No such file or directory" — the ASan runtime is not included in this MinGW toolchain, so ASan is unavailable here.
Conclusion: no automated memory checker was available on this machine, so none is claimed. 

Manual new/delete trace for the 3-node tree in test 5:
Allocations: new 50, new 30, new 70 (3 total).
destroyTree: recurse left -> delete 30; recurse right -> delete 70; delete 50; root set to nullptr (3 deletions, postorder order).
A second destroyTree sees nullptr and returns immediately.
Every test block builds with new and ends with destroyTree; test 1 only calls destroyTree(nullptr) twice.

## Analysis Questions
1) Trace the preorder, inorder, and postorder processing steps for the subtree rooted at 30 in Tree A. Explain why the sequences change while the sum does not.
Prorder - Process 30, go left and process 20, then go right and process 40.
Inorder - Process the left of the root first, which is 20, process the root, 30, then the right, 40.
postorder - Process the left, 20, the right, 40, then the node, 30.
The sequence changes because from prorder to postorder, when the root/node gets process happen later and later. With preorder it happens first, with inorder it happens second, and with postorder it happens last. But, this order does not matter when calucating the sum since the order of which numbers are added doesn't change the answer.
2) Explain why Tree B is a binary tree but not a BST, using a specific violated ordering relationship. Why is its inorder sequence not sorted?
Tree B us not BST because with BST the values that are less than the node go to the left while those that are greater go to the right. In Tree B, 5 is to the right of 30 despite being lower, and 15 is to the right of 20 despite being lower as well. Due to this change the inorder sequence would be not sorted.
3) Give the depth of node 40 in Tree A and distinguish depth in edges from this assignment's height in levels.
The depth of node 40 would be 2 if one were to measure its depth in edges, or 3 if it were measured in levels. The difference is that when counting levels the nodes along the path and the root are counted, while in edges the number of edges it takes to get there is the depth.
4) Explain how the FIFO queue produces level order. Connect this to the queue behavior from earlier work.
FIFO produces level order by enqueuing all of that level first. It enqueues the left and right of a node at the same time. When it enqueues it, the new nodes go to the back, after any node that was queue'd before it. If the root has two children, they both get queue'd together. Then, when the root's children get processed, their children get queue'd after the root's children, and so on.
5) For n nodes, height h, and maximum level width w, explain the time and auxiliary space for depth-first traversal, level-order traversal, measurements, and destruction. Discuss the O(n) returned vector separately from the call stack or queue. Compare the height of a balanced tree with a chain. Explain why a normal traversal does not need dynamic-programming tabulation.
The time is O(n) for all of them. For depth-first traversal, measurements and destruction the auxiliary space would be O(h) since it only holds one root to leaf path, thereby scaling with the height. Level-order traversal auxiliary space is O(w) since it holds the entire level scaling with the width. The returned vector is O(n) and it does not grow or shrink depending on the height or width of the tree, only the number of nodes. A balanced tree would be h = O(log n) as the recursion stays logarithmic. While the chain would be h = O(n) since the recursive operations become  linear. Tabulation is not needed since there are no overlaps, each node only has one parent.
6) Explain why deletion uses postorder and what TreeNode*& changes in the caller. What would go wrong if the parent were deleted before reading its child pointers?
Deletion uses postorder because it fufills the requirements for properly deleting the tree. The tree must be deleted children first, and postorder processes the children first and the node last. The root is passed by referance so that changes made to the tree actually change the tree for the caller as well. If it were passed by value, the caller's tree would be unchanged. If the parent node were deleted first, the children can become unreachable, a use-after-free error can occur, or garbage pointer can be read.
## AI Use
I did use AI. I used a model called GLM-5.3. The AI helped me look for mainly logic errors and it helped me plan how to implement certain functions. It did that by breaking down what to do, sometimes writing the algorithm if I was really confused. However, most of the the code used in the implementation of TreeExplorer was done entirely by me. I had problems writing the treeHeight function to where I practically gave me the code because I was so confused and unable to properly implement it. When it comes to traversals I understood it pretty well but I had it help me keep the helper functions private. The only thing I truly needed its help with was the aforementioned function. I didn't really test any of the functions until I was finished with all of them, but I did use a pieve of paper and did the recursions and such by hand to make sure that the code worked as intended. I learned about the traversal methods and how to properly implement them, but I still needed a lot more help with counting the nodes, leaves, and height. My understanding of those three things are worse, but not enough to where I am not able to replicate it. It also wrote the tests given a few lines of code. I told it to output it and include any tests that I had missed. I can write tests, however I often miss certain things as I just assume that it would work, like the root being null when passed. So, I can get better writing tests as my tests are often not extensive so things can slip through.