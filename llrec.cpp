#include "llrec.h"

void llpivot(Node*& head, Node*& smaller, Node*& larger, int pivot)
{
    // Base case: empty list -> both outputs empty
    if (head == NULL) {
        smaller = NULL;
        larger  = NULL;
        return;
    }

    // Recurse on the rest first; smaller/larger get built from the tail
    Node* rest = head->next;
    llpivot(rest, smaller, larger, pivot);

    // Prepend current node to the correct list
    if (head->val <= pivot) {
        head->next = smaller;
        smaller = head;
    } else {
        head->next = larger;
        larger = head;
    }

    head = NULL;
}

