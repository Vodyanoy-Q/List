#include <stdio.h>
#include "List.h"
#include "colors.h"

int main()
{
    Node * cur = NULL;
    AddNode(&cur, 100);

    Node * head = cur;

    for (int i = 0; i < 10; i++)
    {
        AddNode(&cur, (i + 2) * 100);
        cur = cur->next;
    }


    Node * ret = 0;
    NodeFind(head, &ret, 700);
    printf("Node with value 700 ptr = %p\n", ret);

    DeleteNode(&head, 100);
    DeleteNode(&head, 800);
    ListGraph(head);

//     cur = head;
//     for (int i = 0; i < 7; i++)
//     {
//         cur = cur->next;
//     }
//     cur->next = head;
//
//     bool ret_val = false;
//     FindLoop(head, &ret_val);
//
//     if (ret_val) printf(RED "List has loop!!!\n" RESET_COLOR);

    ListDump(head, "BEFORE");
    ListReverse(&head);
    ListDump(head, "AFTER");

    ListDtor(&head);

    return NO_ERROR;
}
