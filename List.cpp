#include <stdio.h>
#include <stdlib.h>
#include "MyAssert.h"
#include "Errors.h"
#include "colors.h"

typedef double NodeType;

struct Node
{
    Node* next = NULL;
    NodeType value = 0;
};

Node * AddNode(Node** current, NodeType value);

int main()
{


    return 0;
}

Node * AddNode(Node** current, NodeType value)
{
    Node * new_node = (Node*)calloc(1, sizeof(Node));
    if (new_node == NULL)
    {
        printf(RED "ERROR MAKE NODE WITH VALUE: %d\n" RESET_COLOR, value);
        return NULL;
    }
    new_node->value = value;

    if (current == NULL)
    {
        *current =
    }

    return new_node;
}
