#ifndef _XLISTH
#define _XLISTH
#include <cstdint>

template <class T>
class XList
{
public:
	XList() : size(0), head(NULL), tail(NULL), iterator(NULL){};
	~XList();
	
	void AddFront(T const &);
	void AddEnd(T const &);
	void RemoveFront();
	void RemoveEnd();
	bool IsEmpty() const { return (head == NULL); }
	void Clear();
	void Show();

	uint32_t GetLength() const { return size; }
	T GetFirst() const { return head->value; }
	T GetLast() const { return lastElement->value; }

	//Iterator for getting value of the elements of the list.
	void IteratorInitial() { iterator = head; }
	T IteratorGetValue() const 
	{ 
		try
		{
			if (IsEmpty())
				throw "Error - list is empty!";
			return iterator->value;
		}
		catch (char * str)
		{
			std::cout << str << std::endl;
		}
	}
	void IteratorToNext() { iterator = iterator->next; }
	bool IteratorIsEnd() const {return (iterator == NULL) ? true : false;}

private:
	class Element {
	public:
		Element(T const &_value, Element *_next = NULL) : value(_value), next(_next) {}
		T value;
		Element * next;
	};

	uint32_t size;

	Element * head;
	Element * tail;
	Element * lastElement;

	Element * iterator;
};

template <class T>
XList<T>::~XList()
{
	//Clear();
}

template <class T>
void XList<T>::AddFront(T const & element)
{
	++size;
	Element * newElement = new Element(element, head);

	if (size == 1)
	{
		lastElement = newElement;
	}

	head = newElement;
}

template <class T>
void XList<T>::AddEnd(T const & element)
{
	++size;
	Element * newElement = new Element(element);

	if (size > 1) 
		lastElement->next = newElement;
	else 
		head = newElement;
		
	lastElement = newElement;
}

template <class T>
void XList<T>::RemoveFront()
{
	if (IsEmpty()) return;

	--size;
	
	Element * newHead = head->next;
	delete head;

	if (size == 0)
	{
		head = tail = lastElement = NULL;
	}
	else
	{
		head = newHead;
		tail = newHead->next;
	}
}

template <class T>
void XList<T>::RemoveEnd()
{
	if (IsEmpty()) return;

	--size;

	Element * iter = head;

	while (iter->next != lastElement)
	{
		iter = iter->next;
	}

	iter->next = NULL;
	delete lastElement;

	if (size == 0)
	{
		 head = tail = lastElement = NULL;
	}
	else
	{
		lastElement = iter;
	}
}

template <class T>
void XList<T>::Clear()
{
	if (IsEmpty()) return;

	Element * iter = head;

	while (iter != NULL)
	{
		Element * newHead = iter->next;
		delete iter;
		iter = newHead;
	}
	size = 0;
	head = tail = NULL;
}


template <class T>
void XList<T>::Show()
{
	if (size == 0)
	{
		std::cout << "List is empty";
		return;
	}
	Element * iter = head;

	while (iter != NULL)
	{
		std::cout << iter->value << std::endl;
		iter = iter->next;
	}
}

#endif _XLISTH