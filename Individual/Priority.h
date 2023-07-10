#pragma once
#include <iostream>

using namespace std;

template <typename T>
struct Node
{
	T data;
	Node* next;
	int prior;

	Node(T data = 0, Node* next = nullptr, int prior = 0) {
		this->data = data;
		this->next = next;
		this->prior = prior;
	}

	friend 	ostream& operator << (ostream& out, const Node& x) {
		out << x.data << ' ';
		return out;
	}
};

template <typename T>
class Priority {
private:
	Node<T>* first; // ������ ������
	Node<T>* last; // ����� ������

public:
	Priority() : first(nullptr), last(nullptr) {}; //����������� �� ���������

	Priority(Priority& other); //����������� �����

	bool is_Empty(); //�������� �� �������

	void add(T data, int priority); //���������� �������� � �������, � �������� �����������

	//�����
	friend ostream& operator << (ostream& os, const Priority& y) {
		Node<T>* p = y.first;
		while (p)
		{
			os << *p << endl;
			p = p->next;
		}
		os << endl;
		return os;
	}
	//����
	friend istream& operator >> (istream& is, Priority& y) {
		int n; //���������� ���������
		is >> n;
		T elem;
		while (n != 0) {
			is >> elem;
			y.add(elem);
			n--;
		}
		return is;
	}

	void operator >> (T& x); //���������� �������� �� �������

	void operator << (T x); //���������� �������� � �������

	Priority operator + (const Priority& other); //������� ��������

	Priority& operator = (const Priority& other); //������������

	T get_value(); //��������� �������� ���������� ��������
	void set_value(T x);

	T extract(); //���������� ���������� ��������

	~Priority(); //����������
};



template <typename T>
Priority<T>::Priority(Priority<T>& other) {
	first = nullptr; last = nullptr;
	Node<T>* q = other.first;
	while (q) {
		*this << q->data;
		q = q->next;
	}
}

template <typename T>
Priority<T>::~Priority() {
	while (first) {
		Node<T>* cur = first;
		first = first->next;
		delete cur;
	}
	last = first = nullptr;
}

template <typename T>
bool Priority<T>::is_Empty() {
	return first == nullptr;
}

template <typename T>
void Priority<T>::add(T data, int i) {
	Node<T>* newNode = new Node<T>(data, nullptr, i);
	//���� ������ ������
	if (is_Empty()) {
		first = last = newNode;
	}
	//���������� � �����
	else if (last->prior <= i) {
		last->next = newNode;
		last = newNode;
	}
	//���������� � ������
	else if (first->prior >= i) {
		newNode->next = first;
		first = newNode;
	}
	else {
		Node<T>* p = first;
		while (i >= ((p->next)->prior)) {
			p = p->next;
		}
		newNode->next = p->next;
		p->next = newNode;
	}
}

template <typename T>
void Priority<T>::operator << (T x) {
	Node<T>* t = new Node<T>(x, nullptr);
	if (first) {
		t->prior = last->prior + 1;
		last->next = t;
		last = t;
	}
	else {
		t->prior = 0;
		first = last = t;
	}
}

template <typename T>
void Priority<T>::operator >> (T& x) {
	if (first) {
		Node<T>* t = first;
		x = t->data;
		first = first->next;
		delete t;
	}
	else
		throw exception("������� ������!");
}

template <typename T>
Priority<T> Priority<T>::operator+(const Priority& other) {
	Priority<T> res;
	Node<T>* cur = first;
	while (cur) {
		res.add(cur->data, cur->prior);
		cur = cur->next;
	}
	cur = other.first;
	while (cur) {
		res.add(cur->data, cur->prior);
		cur = cur->next;
	}
	return res;
}

template <typename T>
Priority<T>& Priority<T>::operator = (const Priority& other) {
	this->~Priority();
	Node<T>* q = other.first;
	while (q) {
		*this << (q->data);
		q = q->next;
	}
	return *this;
}

template <typename T>
T Priority<T>::extract() {
	T x;
	*this >> x;
	return x;
}

template <typename T>
T Priority<T>::get_value() {
	if (!is_Empty())
		return first->data;
	throw exception("������ ������!");
}

template <typename T>
void Priority<T>::set_value(T x) {
	*this << x;
}