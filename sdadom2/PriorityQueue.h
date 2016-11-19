#include <iostream>
using namespace std;

template <typename T>
class PriorityQueue {
public:
	PriorityQueue();
	~PriorityQueue();
	PriorityQueue(PriorityQueue const& obj);
	PriorityQueue& operator=(PriorityQueue const& obj);

	void Enqueue(T const& x);
	T Dequeue();
	T Head() const;
	bool isEmpty() const;
	
private:
	void CopyFrom(PriorityQueue<T> const& obj);
	void RemoveAll();

	struct Container 
	{
		T Value;
		Container* pNext;

		Container(T Value, Container* pNext = NULL);
	};
	Container<T> *front, *back;
};

template <typename T>
PriorityQueue<T>::Container::Container(T Value, Container* pNext)
{
	this->Value = Value;
	this->pNext = pNext;
}

template <typename T>
PriorityQueue<T>::PriorityQueue()
{
	front = NULL;
	back = NULL;
}

template <typename T>
void PriorityQueue<T>::CopyFrom(PriorityQueue<T> const& obj)
{
	for (Container<T>* p = obj.front; p != NULL; p = p->pNext)
	{
		Enqueue(p->Value);
	}	
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
PriorityQueue<T>::~PriorityQueue()
{
	RemoveAll();
}

template <typename T>
PriorityQueue<T>::PriorityQueue(PriorityQueue const& obj)
{
	front = NULL;
	back = NULL;
	CopyFrom(obj);
}

template <typename T>
PriorityQueue<T>::PriorityQueue& operator=(PriorityQueue const& obj)
{
	if (this != &obj) {
		RemoveAll();
		CopyFrom(obj);
	}
	return *this;
}

template <typename T>
void PriorityQueue<T>::Enqueue(T const& x)
{
	Container<T>* p = new Container<T>(x);
	if (!isEmpty()) 
	{
		back->pNext = p;
	}
	else
	{
		front = p;
	}

	back = p;
}

template <typename T>
T PriorityQueue<T>::Dequeue()
{
	assert(!isEmpty());

	Container<T>* p = front;
	front = front->pNext;

	if (front == NULL)
	{
		back = NULL;
	}
		
	T x = p->Value;
	delete p;
	return x;
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