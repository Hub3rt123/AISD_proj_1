#pragma once
#include "String.h"
#include "ElemList.h"

const int T = 8;

class List
{
	struct Section {
		ElemList selectors;
		ElemList attributes;
		ElemList values;
	};
	struct Node {
		Section sections[T];
		int size = 0;
		Node* previous = NULL;
		Node* next = NULL;
	};
	Node* first;
	Node* last;
	bool move(Node* temp, int x);
public:
	List() : first(NULL), last(NULL) {}
	void append();
	void append_elem(String& elem, char ch);
	bool remove(int index);
	bool remove(int index, String& s);
	int HowMany();
	int HowManyInSection(int i, char ch);
	int HowManyElem(String& s, char ch);
	String search_value(String& sel, String& attr);
	String SelInSection(int i, int j);
	String AttrInSection(int i, String& s);
	~List();
};


