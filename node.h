//node.h
//header file for Binary Node class

#ifndef NODE_H
#define NODE_H

class Node {
    public:
        int value;
        Node* left;
        Node* right;
        
        Node(int val);
};

#endif