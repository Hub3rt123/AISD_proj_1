#pragma once
#include "String.h"

class ElemList
{
	struct Node {
		String element;
		Node* previous = NULL;
		Node* next = NULL;
	};
	Node* first;
	Node* last;
public:
	ElemList() : first(NULL), last(NULL) {}
	int search(String& s);
	String search(int i);
	void append(String& elem);
	bool remove(String& elem);
	bool remove(int i);
	bool IsEmpty();
	int HowMany();
	~ElemList();
};