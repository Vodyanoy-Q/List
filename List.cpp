#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "MyAssert.h"
#include "Errors.h"
#include "colors.h"

Node* AddNode(Node** current, NodeType value)
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

ERROR ListDump(Node* node, const char* message)
{
    MY_ASSERT_RET(node, ADDRESS_ERROR)
    MY_ASSERT_RET(message, ADDRESS_ERROR)

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

ERROR ListGraph(Node* node)
{
    MY_ASSERT_RET(node, ADDRESS_ERROR);

    FILE * file = NULL;

    Node * cur = node;

    MY_FOPEN_RET(file, "list.dot", "w");

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

    MY_FCLOSE_RET(file);

    system("dot list.dot -T png -o list.png");

    return NO_ERROR;
}

ERROR FindLoop(Node* head, bool* ret_val)
{
    MY_ASSERT_RET(head,    ADDRESS_ERROR);
    MY_ASSERT_RET(ret_val, ADDRESS_ERROR);

    Node* cur1 = head;
    Node* cur2 = head->next;

    while (cur2 != NULL)
    {
        if (cur1 == cur2)
        {
            *ret_val = true;
            break;
        }
        cur1 = cur1->next;
        cur2 = cur2->next;
        if (cur2->next != NULL) cur2 = cur2->next;
    }

    return NO_ERROR;
}

ERROR NodeFind(Node* head, Node** return_ptr, NodeType value)
{
    MY_ASSERT_RET(head, ADDRESS_ERROR);
    MY_ASSERT_RET(return_ptr, ADDRESS_ERROR);

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

    return NO_NODE_IN_LIST;
}

ERROR ListDtor(Node** head)
{
    MY_ASSERT_RET(head, ADDRESS_ERROR);
    MY_ASSERT_RET(*head, ADDRESS_ERROR);

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

ERROR DeleteNode(Node** head, NodeType value)
{
    MY_ASSERT_RET(head, ADDRESS_ERROR);
    MY_ASSERT_RET(*head, ADDRESS_ERROR);

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

    return DELETE_NODE_ERROR;
}

ERROR ListReverse(Node** head)
{
    MY_ASSERT_RET(head, ADDRESS_ERROR);

    Node* cur  = *head;
    Node* next = NULL;
    Node* prev = NULL;

    while (cur != NULL)
    {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }

    *head = prev;

    return NO_ERROR;
}
