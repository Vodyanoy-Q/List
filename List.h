#ifndef _LIST_H_
#define _LIST_H_

#include "Errors.h"

typedef double NodeType;

struct Node
{
    Node* next = NULL;
    NodeType value = 0;
};

Node* AddNode(Node** current, NodeType value);
ERROR ListDump(Node* node, const char* message);
ERROR ListGraph(Node* node);
ERROR NodeFind(Node* head, Node** return_ptr, NodeType value);
ERROR ListDtor(Node** head);
ERROR DeleteNode(Node** head, NodeType value);
ERROR FindLoop(Node* head, bool* ret_val);
ERROR ListReverse(Node** head);

#endif //_LIST_H_
