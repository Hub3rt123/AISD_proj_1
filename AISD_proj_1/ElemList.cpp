#include "ElemList.h"

void ElemList::append(String& elem) {
	Node* temp = new Node;
	temp->element = elem;
	temp->next = NULL;
	if (first == NULL) first = temp;
	else last->next = temp;
	temp->previous = last;
	last = temp;
}

ElemList::~ElemList() {
	while (first != last) {
		
		last = last->previous;
		delete last->next;
		last->next = NULL;
	}
	if (first != NULL)
		delete first;
}

int ElemList::search(String& s) {
	Node* temp = first;
	int i = 0;
	while (temp != NULL) {
		if (temp->element == s)
			return i;
		i++;
		temp = temp->next;
	}
	return -1;
}

String ElemList::search(int i) {
	Node* temp = first;
	while (--i && temp != NULL) {
		temp = temp->next;
	}
	if (temp == NULL)
		return ";";
	else
		return temp->element;
}

bool ElemList::remove(int i) {
	Node* temp = first;
	for (int j = 0; j < i; j++)
		temp = temp->next;
	if (temp == NULL)
		return false;
	else if (temp == first && temp == last) {
		first = NULL;
		last = NULL;
	}
	else if (temp == first && temp != last) {
		first = temp->next;
		first->previous = NULL;
	}
	else if (temp == last && temp != first) {
		last = temp->previous;
		last->next = NULL;
	}
	else {
		temp->next->previous = temp->previous;
		temp->previous->next = temp->next;
	}
	delete temp;
	return true;
}

bool ElemList::remove(String& s) {
	int i = search(s);
	if (i == -1) return false;
	return remove(i);
}

bool ElemList::IsEmpty() {
	if (first == NULL) return true;
	else return false;
}

int ElemList::HowMany() {
	Node* temp = first;
	int i = 0;
	while (temp != NULL) {
		i++;
		temp = temp->next;
	}
	return i;
}