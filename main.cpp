//heapMerging.cpp

//include statements
#include <iostream>
#include <stack>
#include <utility>
#include "node.h"

//function prototypes
std::vector<int> printHeap(Node* root);
Node* buildHeapFromArray(const std::vector<int>& arr);
Node* merge(Node* x, Node* y);

//main function
int main() {

    //array representation of the first heap
    std::vector<int> heap1Array = {4, 19, 8, 27, 20, 12, 25, 43, 15};
    //array representation of the second heap
    std::vector<int> heap2Array = {6, 8, 7, 14};

    //build heaps from arrays
    Node* heap1 = buildHeapFromArray(heap1Array);
    Node* heap2 = buildHeapFromArray(heap2Array);
    

    //print heaps
    std::cout << "Heap1 (level-order): ";
    printHeap(heap1);
    std::cout << "Heap2 (level-order): ";
    printHeap(heap2);

    //merge the heaps
    Node* mergedHeap = merge(heap1, heap2);

    //print the merged heap level-order
    std::cout << "Merged Heap (level-order): ";
    std::vector<int> output = printHeap(mergedHeap); //array representation of merged heaps

    return 0;
}


//print the heap in level-order traversal (root to leaves)
std::vector<int> printHeap(Node* root) {
    std::vector<int> output; //array to store output (merged) heap

    std::queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();
        if (current) {
            std::cout << current->value << " ";
            output.push_back(current->value);
            q.push(current->left);
            q.push(current->right);
        }
    }
    std::cout << std::endl;

    return output;
}


//function to build a heap from an array
Node* buildHeapFromArray(const std::vector<int>& arr) {
    if (arr.empty()) return nullptr;

    //create a vector of nodes
    std::vector<Node*> nodes;
    for (int val : arr) {
        nodes.push_back(new Node(val));
    }

    //link the nodes to form a complete binary tree
    for (std::size_t i = 0; i < nodes.size(); ++i) {
        if (2 * i + 1 < nodes.size()) {
            nodes[i]->left = nodes[2 * i + 1];
        }
        if (2 * i + 2 < nodes.size()) {
            nodes[i]->right = nodes[2 * i + 2];
        }
    }

    return nodes[0]; // Return the root of the heap
}

//function to merge heaps
Node* merge(Node* x, Node* y) {
    if (!x) return y;
    if (!y) return x;

    //verifies heap property
    if (x->value > y->value) {
        Node* temp = x;
        x = y;
        y = temp;
    }

    //use a stack for merging
    std::stack<std::pair<Node*, Node*>> s;
    s.push(std::make_pair(x, y));

    while (!s.empty()) {
        std::pair<Node*, Node*> top = s.top();
        Node* a = top.first;
        Node* b = top.second;
        s.pop();

        if (!b) {
            continue;
        }

        //compare and merge the right child
        if (!a->right) {
            a->right = b;
        } else {
            if (a->right->value > b->value) {
                Node* temp = a->right;
                a->right = b;
                b = temp;
            }
            s.push(std::make_pair(a->right, b));
        }

        //ensure the leftist property
        if (!a->left || (a->right && a->left->value > a->right->value)) {
            Node* temp = a->left;
            a->left = a->right;
            a->right = temp;
        }
    }

    return x;
}

