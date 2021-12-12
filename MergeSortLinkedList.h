#include <Timer.h>


/* Link list node */
class Node {
public:
	Timer timer;
	Node* next;
};



class MergeSort {

  public:

		MergeSort() {}


    /* sorts the linked list by changing next pointers (not data) */
    void Sort(Node** headRef)
    {
    	Node* head = *headRef;
    	Node* a;
    	Node* b;

    	/* Base case -- length 0 or 1 */
    	if ((head == NULL) || (head->next == NULL)) {
    		return;
    	}

    	/* Split head into 'a' and 'b' sublists */
    	FrontBackSplit(head, &a, &b);

    	/* Recursively sort the sublists */
    	Sort(&a);
    	Sort(&b);

    	/* answer = merge the two sorted lists together */
    	*headRef = SortedMerge(a, b);
    }

    Node* SortedMerge(Node* a, Node* b)
    {
    	Node* result = NULL;

    	/* Base cases */
    	if (a == NULL)
    		return (b);
    	else if (b == NULL)
    		return (a);

    	/* Pick either a or b, and recur */
    	if (a->timer.getNextEvent() <= b->timer.getNextEvent()) {
    		result = a;
    		result->next = SortedMerge(a->next, b);
    	}
    	else {
    		result = b;
    		result->next = SortedMerge(a, b->next);
    	}
    	return (result);
    }

		/* Function to insert a node at the beginning of the linked list */
		void push(Node** head_ref, const Timer& timer)
		{
			/* allocate node */
			Node* new_node = new Node();

			/* put in the data */
			new_node->timer = timer;

			/* link the old list off the new node */
			new_node->next = (*head_ref);

			/* move the head to point to the new node */
			(*head_ref) = new_node;
		}

		void deleteNode(Node** head_ref, int key)
		{

		    // Store head node
		    Node* temp = *head_ref;
		    Node* prev = NULL;

		    // If head node itself holds
		    // the key to be deleted
		    if (temp != NULL && temp->timer.getId() == key)
		    {
		        *head_ref = temp->next; // Changed head
		        delete temp;            // free old head
		        return;
		    }

		    // Else Search for the key to be deleted,
		    // keep track of the previous node as we
		    // need to change 'prev->next' */
		      else
		    {
		    while (temp != NULL && temp->timer.getId() != key)
		    {
		        prev = temp;
		        temp = temp->next;
		    }

		    // If key was not present in linked list
		    if (temp == NULL)
		        return;

		    // Unlink the node from linked list
		    prev->next = temp->next;

		    // Free memory
		    delete temp;
		    }
		}

  protected:

    /* Split the nodes of the given list into front and back halves,
    	and return the two lists using the reference parameters.
    	If the length is odd, the extra node should go in the front list.
    	Uses the fast/slow pointer strategy. */
    void FrontBackSplit(Node* source,
    					Node** frontRef, Node** backRef)
    {
    	Node* fast;
    	Node* slow;
    	slow = source;
    	fast = source->next;

    	/* Advance 'fast' two nodes, and advance 'slow' one node */
    	while (fast != NULL) {
    		fast = fast->next;
    		if (fast != NULL) {
    			slow = slow->next;
    			fast = fast->next;
    		}
    	}

    	/* 'slow' is before the midpoint in the list, so split it in two
    	at that point. */
    	*frontRef = source;
    	*backRef = slow->next;
    	slow->next = NULL;
    }


  private:

};
