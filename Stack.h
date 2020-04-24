#pragma once

using namespace std;

template <typename T>
struct Node
{
	Node<T> *next;
	T value;
};

template <typename T>
class Stack // linked-list stack
{
private:
	Node<T>* head;
	int count; //size of stack
public:
	Stack();
	T top();
	void push(const T&);
	void pop();
	bool empty();
	int size();
};

template <typename T>
Stack<T>::Stack()
{
	head = nullptr;
	count = 0;
}

template <typename T>
T Stack<T>::top()
{
	if (empty())
	{
		cout << "Stack is empty!(top)" << endl;
		return 0;
	}
	return head->value;
}

template <typename T>
bool Stack<T>::empty()
{
	if (count == 0)
	{
		return true;
	}
	else
		return false;
}

template <typename T>
int Stack<T>::size()
{
	return count;
}

template <typename T>
void Stack<T>::push(const T& v)
{
	Node<T> *newNode = new Node<T>;
	newNode->value = v;
	newNode->next = head;
	head = newNode;
	count++;
}

template <typename T>
void Stack<T>::pop()
{
	if (empty())
	{
		cout << "Unable to pop, stack is empty!" << endl;
		return;
	}
	Node<T> *deleteNode = head;
	head = head->next;
	delete deleteNode;
	count--;
}