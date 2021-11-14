            
#include <iostream>
using namespace std;

template <class Type>

struct nodeType //linked list structure
{
	Type info, value;
	nodeType<Type>* link; 
};

template <class Type>
class linkedListType
{
public:
	
	linkedListType ();
	
	linkedListType (const linkedListType<Type>& otherlist);
	
	~linkedListType ();

	const linkedListType<Type>& operator=(const linkedListType<Type>& otherlist);

	bool isEmptyList () const;
	
	void print () const;

	void insertFirst (const Type& newItem);

	void insertLast (const Type& newItem);
	void deleteAllNode (const Type& deleteItem);
	void deleteNode (const Type& deleteItem);
	void deleteMinNode ();
	Type min () const;
	void destroyList ();


protected:
	int count;		// store number of list elements

	nodeType<Type>* first;		// pointer to fist node
	nodeType<Type>* last;		// pointer to last node

private:
	void copyList (const linkedListType<Type>& otherlist);
};

template <class Type>
linkedListType<Type>::linkedListType ()
{
//initialize it
	first = NULL;
	last = NULL;
	count = 0;
}

template <class Type>
linkedListType<Type>::linkedListType (const linkedListType<Type>& otherlist)
{
	first = NULL;
	copyList (otherlist);
}

template <class Type>
linkedListType<Type>::~linkedListType ()
{
	// delete all the nodes from the list
	destroyList ();
}

//overload an operator
template <class Type>
const linkedListType<Type>& linkedListType<Type>::operator= (const linkedListType<Type>& otherlist)
{
	if (this != &otherlist)
		copyList (otherlist);
	return *this;
}

template <class Type>
bool linkedListType<Type>::isEmptyList () const
{
	return (first == NULL);
}
	
template <class Type>
void linkedListType<Type>::print () const
{
	nodeType<Type>* current;

	current = first;
  cout << "[ ";
	while (current != NULL)
	{
		cout<<current->info<<" ";
		current = current->link;
	}
  cout << " ]" << endl;
}
	
template <class Type>
void linkedListType<Type>::insertFirst (const Type& newItem)
{
	nodeType<Type>* newNode;

	newNode = new nodeType<Type>;
	newNode->info = newItem;
	newNode->link = first;
	first = newNode;
	count++;

	if (last == NULL)		
		last = newNode;
}

template <class Type>
void linkedListType<Type>::insertLast (const Type& newItem)
{
	nodeType<Type>* newNode;

	newNode = new nodeType<Type>;
	newNode->info = newItem;
	newNode->link = NULL;

	if (first == NULL)
	{
		first = last = newNode;
		count++;
	}
	else
	{
		last->link = newNode;
		last = newNode;
		count++;
	}
}

template <class Type>
void linkedListType<Type>::deleteNode (const Type& deleteItem)
{
	nodeType<Type>* current;
	nodeType<Type>* trailCurrent;	// pointer just before current
	bool found;

	if (first == NULL)
		cout<<"Cannot delete from an empty list\n";
	else
	{
		if (first->info == deleteItem)	// node to be deleted is the first
		{
			current = first;
			first = first->link;
			count--;

			if (first == NULL)			
				last = NULL;

			delete current;
		}
		else							
		{
			found = false;
			trailCurrent = first;
			current = first->link;

			while (current != NULL && !found)
			{
				if (current->info != deleteItem)
				{
					trailCurrent = current;
					current = current->link;
				}
				else
					found = true;
			}

			if (found)	// if found, delete the node
			{
				trailCurrent->link = current->link;
				count--;

				if (last == current)		
					last = trailCurrent;

				delete current;
			}
			else
				cout<<"The item to be deleted is not in the list\n";
		}
	}
}

//delete min value
template <class Type>
void linkedListType<Type>::deleteMinNode ()
{
	nodeType<Type>* current;
	nodeType<Type>* trailCurrent;	// pointer just before current
	bool found;
    Type deleteItem = min();
	if (first == NULL)
		cout<<"Cannot delete from an empty list\n";
	else
	{
		if (first->info == deleteItem)	// node to be deleted is the first
		{
			current = first;
			first = first->link;
			count--;

			if (first == NULL)			// the list becomes empty
				last = NULL;

			delete current;
		}
		else							// search the list for the node to be deleted
		{
			found = false;
			trailCurrent = first;
			current = first->link;

			while (current != NULL && !found)
			{
				if (current->info != deleteItem)
				{
					trailCurrent = current;
					current = current->link;
				}
				else
					found = true;
			}

			if (found)	// if found, delete the node
			{
				trailCurrent->link = current->link;
				count--;

				if (last == current)		// node to be deleted is last
					last = trailCurrent;

				delete current;
			}
			else
				cout<<"The item to be deleted is not in the list\n";
		}
	}
}

template <class Type>
void linkedListType<Type>::deleteAllNode (const Type& deleteItem)
{
nodeType<Type>** p = &first;
while(*p)
if((*p)->info == deleteItem) {
nodeType<Type>* tmp = (*p)->link;
delete *p;
*p = tmp;
} else
p = &(*p)->link;

}
template <class Type>
Type linkedListType<Type>::min () const
{
	nodeType<Type>* current;
	
	current = first;
    Type min_val = current->info;

	while (current != NULL)
	{
	
		if (current->info < min_val)
			min_val = current->info;
		current = current->link;

    }
	return min_val;
}

template <class Type>
void linkedListType<Type>::destroyList ()
{
	// delete all nodes from the list
	nodeType<Type>* tmp;

	while (first != NULL)
	{
		tmp = first;
		first = first->link;
		delete tmp;
	}

	last = NULL;
	count = 0;
}

void testFunc(linkedListType<int>& myList){

	//lets insert 10 elements into the list
  //5 from the beginnig and 5 from the end

	myList.insertFirst(100);
	myList.insertFirst(1);
	myList.insertFirst(10);
	myList.insertFirst(70);
	myList.insertFirst(35);
	myList.insertLast(20);
	myList.insertLast(15);
	myList.insertLast(15);
	myList.insertLast(15);
	myList.insertLast(50);
	
  cout<< "**************************************************************\n";
	cout<< "\tInitial List values : ";
	myList.print();
  

	cout <<"\n\tdelete all elements that equal to 15: ";

	myList.deleteAllNode(15);
	myList.print();

  //get min value
	cout <<"\n\tMin value:";
	cout << myList.min();
	cout <<"\n\tList Before min delete :";
	myList.print();
	myList.deleteMinNode();
	cout  <<"\n\tList after min delete : ";
	myList.print();
  cout<< "************************* END *********************************\n";

}

int main()
{
	
	
	linkedListType<int> myList;

  testFunc(myList);//test the functions

	system("pause");
	return 0;
}


