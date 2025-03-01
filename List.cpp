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
int ListDump(Node* node, const char* message);
int ListGraph(Node* node);
int NodeFind(Node* head, Node** return_ptr, NodeType value);
int ListDtor(Node** head);
int DeleteNode(Node** head, NodeType value);

int main()
{
    Node * cur = NULL;
    AddNode(&cur, 100);

    ListDump(cur, "12312");

    Node * head = cur;

    for (int i = 0; i < 10; i++)
    {
        AddNode(&cur, (i + 2) * 100);
        cur = cur->next;
    }
    ListDump(head, "For cycle");


    Node * ret = 0;
    NodeFind(head, &ret, 700);
    printf("Node with value 700 ptr = %p\n", ret);

    DeleteNode(&head, 100);
    DeleteNode(&head, 800);
    ListGraph(head);

    ListDtor(&head);

    return 0;
}

Node * AddNode(Node** current, NodeType value)
{
    Node * new_node = (Node*)calloc(1, sizeof(Node));
    if (new_node == NULL)
    {
        printf(RED "ERROR MAKE NODE WITH VALUE: %lg\n" RESET_COLOR, value);
        return NULL;
    }

    new_node->value = value;

    if (*current == NULL)
    {
        *current = new_node;
        (*current)->next = NULL;
    }
    else
    {
        new_node->next = (*current)->next;
        (*current)->next = new_node;
    }

    return new_node;
}

int ListDump(Node* node, const char* message)
{
    MY_ASSERT(node, ADDRESS_ERROR)
    MY_ASSERT(message, ADDRESS_ERROR)

    Node * cur = node;

    YELLOW_TEXT("==================================================\n");
    YELLOW_TEXT("START DUMP\n");
    printf(YELLOW "%s\n" RESET_COLOR, message);

    while (cur != NULL)
    {
        printf(YELLOW "[%p] value = %lg, next = %p\n" RESET_COLOR, cur, cur->value, cur->next);
        cur = cur->next;
    }
    YELLOW_TEXT("END DUMP\n");
    YELLOW_TEXT("==================================================\n");

    return NO_ERROR;
}

int ListGraph(Node* node)
{
    MY_ASSERT(node, ADDRESS_ERROR);

    ERROR error = NO_ERROR;

    FILE * file = NULL;

    Node * cur = node;

    _FOPEN(file, "list.dot", "w");

    fprintf(file, "digraph {\n");

    while (cur != NULL)
    {
        fprintf(file, "    node%p [shape = \"Mrecord\", label=\"{ptr = %p | value = %lg |"
                      "next = %p}\", style=\"filled\", fillcolor=\"#BEDAFF\"]\n", cur, cur, cur->value, cur->next);
        cur = cur->next;
    }

    cur = node;
    fprintf(file, "\n");

    while (cur->next != NULL)
    {
        fprintf(file,"    node%p -> node%p\n", cur, cur->next);
        cur = cur->next;
    }

    fprintf(file, "}\n");

    _FCLOSE(file);

    system("dot list.dot -T png -o list.png");

    return NO_ERROR;
}

int NodeFind(Node* head, Node** return_ptr, NodeType value)
{
    MY_ASSERT(head, ADDRESS_ERROR);
    MY_ASSERT(return_ptr, ADDRESS_ERROR);

    Node * cur = head;

    while (cur != NULL)
    {
        if (cur->value == value)
        {
            *return_ptr = cur;
            return NO_ERROR;
        }
        cur = cur->next;
    }

    if (cur == NULL)
    {
        *return_ptr = NULL;
        return NO_NODE_IN_LIST;
    }

    return NO_ERROR;
}

int ListDtor(Node** head)
{
    MY_ASSERT(head, ADDRESS_ERROR);
    MY_ASSERT(*head, ADDRESS_ERROR);

    Node * cur = *head;
    Node * prev = *head;

    while (cur != NULL)
    {
        cur = prev->next;
        prev->next  = NULL;
        prev->value = 0;

        free(prev);
        prev = cur;
    }

    *head = NULL;

    return NO_ERROR;
}

int DeleteNode(Node** head, NodeType value)
{
    MY_ASSERT(head, ADDRESS_ERROR);
    MY_ASSERT(*head, ADDRESS_ERROR);

    Node * node = NULL;

    if ((*head)->value == value)
    {
        node = (*head)->next;
        (*head)->value = 0;
        (*head)->next = NULL;

        free(*head);

        *head = node;
        return NO_ERROR;
    }

    Node * cur = *head;

    while (cur->next != NULL)
    {
        if (cur->next->value == value)
        {
            node = cur->next->next;
            cur->next->next  = NULL;
            cur->next->value = 0;
            free(cur->next);
            cur->next = node;

            return NO_ERROR;
        }
        cur = cur->next;
    }

    if (cur->next == NULL)
    {
        return DELETE_NODE_ERROR;
    }

    return NO_ERROR;
}
