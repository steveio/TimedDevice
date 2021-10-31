/**

mergeSortLinkedList.cpp

OO merge sort linked list implementation
Sort a set of Timer objects on unix timestamp

**/

#include <bits/stdc++.h>
#include <time.h>

using namespace std;


class Timer {
public:


	Timer(int id = 0, unsigned long nextEvent = 0)
	{
		_id = id;
		_nextEvent = nextEvent;
	}

	unsigned long getNextEvent()
	{
		return _nextEvent;
	}

	int getId()
	{
		return _id;
	}

protected:
	int _id;
	unsigned long  _nextEvent; // timestamp next event begin

};


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

    /* Function to print nodes in a given linked list */
    void printList(Node* node)
    {
    	while (node != NULL) {
				cout << node->timer.getId() << " ";
    		cout << node->timer.getNextEvent() << "\n";
    		node = node->next;
    	}
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



/* Driver program to test above functions*/
int main()
{

	printf("Timestamp: %d\n",(int)time(NULL));

	srand(time(NULL));

	/* Start with the empty list */
	Node* res = NULL;
	Node* a = NULL;

	MergeSort mergeSort;

	int ts1 = time(NULL) + rand() % 1000;;
	Timer t1(1,ts1);
	printf("T1 Id: %d\n",(int)t1.getId());
	printf("T1 timestamp: %d\n",(int)t1.getNextEvent());

	int ts2 = time(NULL) + rand() % 1000;;
	Timer t2(2,ts2);
	printf("T2 Id: %d\n",(int)t2.getId());
	printf("T2 timestamp: %d\n",(int)ts2);

	int ts3 = time(NULL) + rand() % 1000;;
	Timer t3(3,ts3);
	printf("T3 Id: %d\n",(int)t3.getId());
	printf("T3 timestamp: %d\n",(int)ts3);

	mergeSort.push(&a, t1);
	mergeSort.push(&a, t2);
	mergeSort.push(&a, t3);

	/*
	push(&a, 5);
	push(&a, 20);
	push(&a, 3);
	push(&a, 2);
	*/

	mergeSort.Sort(&a);

	printf("Sorted Linked List: \n\n");

	mergeSort.printList(a);

	return 0;
}
