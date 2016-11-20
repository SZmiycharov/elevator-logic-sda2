/**
*
* Solution to homework task
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Stanislav Zmiycharov
* @idnumber 61883
* @task 2
* @compiler VC
*
*/

#include <assert.h>
#include <exception>
#include <stdlib.h>

template <typename T>
class PriorityQueue {
public:
	PriorityQueue();
	~PriorityQueue();
	PriorityQueue(PriorityQueue const& obj);
	PriorityQueue& operator=(PriorityQueue const& obj);

	void Enqueue(T const& Element, int priority = -1);
	T Dequeue();
	T Head() const;
	bool isEmpty() const;
	
protected:
	void Init();
	void RemoveAll();
	void CopyFrom(PriorityQueue<T> const& obj);
	
	struct Container 
	{
		T Value;
		Container* pNext;
		int priority;

		Container(T Value, int priority = -1, Container* pNext = NULL);
	};
	Container *front, *back;
	int Used;
};

template <typename T>
PriorityQueue<T>::Container::Container(T Value, int priority = -1, Container* pNext = NULL)
{
	this->Value = Value;
	this->priority = priority;
	this->pNext = pNext;
}

template <typename T>
PriorityQueue<T>::PriorityQueue()
{
	Init();
}

template <typename T>
PriorityQueue<T>::~PriorityQueue()
{
	RemoveAll();
}

template <typename T>
PriorityQueue<T>::PriorityQueue(PriorityQueue const& obj)
{
	Init();
	CopyFrom(obj);
}

template <typename T>
PriorityQueue<T>& PriorityQueue<T>::operator=(PriorityQueue const& obj)
{
	if (this != &obj) 
	{
		RemoveAll();
		CopyFrom(obj);
	}
	return *this;
}

template <typename T>
void PriorityQueue<T>::Enqueue(T const& Element, int priority = -1)
{
	Container* p = new Container(Element, priority);
	bool insertElementAtBack = true;

	if (isEmpty()) 
	{  
		front = p;
		back = p;
		insertElementAtBack = false;
	}
	else if (!(front->pNext))
	{
		if (priority < front->priority)
		{
			front = p;
			front->pNext = back;
		}
		else
		{
			front->pNext = p;
			back = p;
		}
		insertElementAtBack = false;
	}
	else if (priority < front->priority)
	{
		p->pNext = front;
		front = p;
		insertElementAtBack = false;
	}
	else
	{
		Container* oldFront = front;

		while (front->pNext)
		{
			if (priority < front->pNext->priority)
			{
				insertElementAtBack = false;
				p->pNext = front->pNext;
				front->pNext = p;
				break;
			}

			front = front->pNext;
		}

		if (insertElementAtBack)
		{
			back->pNext = p;
			back = p;
		}

		front = oldFront;
		oldFront = NULL;
		delete oldFront;
	}

	p = NULL;
	delete p;
	++Used;
}

template <typename T>
T PriorityQueue<T>::Dequeue()
{
	assert(!isEmpty());

	Container* p = front;
	front = front->pNext;

	if (front == NULL)
	{
		back = NULL;
	}
		
	T Element = p->Value;
	delete p;
	--Used;

	return Element;
}

template <typename T>
T PriorityQueue<T>::Head() const
{
	assert(!isEmpty());

	return front->Value;
}

template <typename T>
bool PriorityQueue<T>::isEmpty() const
{
	return back == NULL;
}

template <typename T>
void PriorityQueue<T>::Init()
{
	front = NULL;
	back = NULL;
	Used = 0;
}

template <typename T>
void PriorityQueue<T>::RemoveAll()
{
	while (!isEmpty())
	{
		Dequeue();
	}
}

template <typename T>
void PriorityQueue<T>::CopyFrom(PriorityQueue<T> const& obj)
{
	if (obj.Used == 0) return;

	try
	{
		Container* p = obj.front;

		while (obj.front)
		{
			Enqueue(p->Value);
			p = p->pNext;
		}
	}
	catch (const bad_alloc& err)
	{
		RemoveAll();
		cerr << "Exception caught: " << err.what() << '\n';
		exit(EXIT_FAILURE);
	}
}
