#include "List.h"
extern const int T;

void List::append() {
	if (last == NULL || last->size >= T) {
		Node* temp = new Node;
		temp->next = NULL;
		temp->size = 1;
		if (first == NULL) {
			first = temp;
			last = temp;
			temp->previous = NULL;
		}
		else {
			last->next = temp;
			temp->previous = last;
			last = temp;
		}
	}
	else {
		last->size = last->size + 1;
	}
}

void List::append_elem(String& elem, char ch) {
	if (ch == 's') last->sections[last->size - 1].selectors.append(elem);
	else if (ch == 'a') {
		int i = last->sections[last->size - 1].attributes.search(elem);
		if (i >= 0) {
			last->sections[last->size - 1].attributes.remove(i);
			last->sections[last->size - 1].values.remove(i);
		}
		last->sections[last->size - 1].attributes.append(elem);
	}
	else if (ch == 'v') last->sections[last->size - 1].values.append(elem);
}

List::~List() {
	while (first != last) {
		last = last->previous;
		delete last->next;
		last->next = NULL;
	}
	if (first != NULL) {
		delete first;
	}
}

bool List::remove(int index) {
	Node* temp = first;
	index--;
	int x = 0;
	for (int j = 0; j <= index && temp != NULL; j++) {
		if (temp->size > index - j) {
			x = index - j;
			j = index;
		}
		else {
			if (temp->size > 0)
				j += temp->size - 1;
		}
		if (j < index)
			temp = temp->next;
	}
	if (temp == NULL) return false;
	if (x >= temp->size) return false;
	if (move(temp, x) == false) {
		if (temp == first && temp == last) {
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
	}
	return true;
}

bool List::move(Node* temp, int x) {
	for (int j = x; j < temp->size - 1; j++) {
		temp->sections[j] = temp->sections[j + 1];
	}
	temp->sections[temp->size - 1].attributes = ElemList();
	temp->sections[temp->size - 1].selectors = ElemList();
	temp->sections[temp->size - 1].values = ElemList();
	temp->size = temp->size - 1;
	if (temp->size <= 0)
		return false;
	else
		return true;
}

bool List::remove(int index, String& s) {
	Node* temp = first;
	index--;
	int x = 0;
	for (int j = 0; j <= index && temp != NULL; j++) {
		if (temp->size > index - j) {
			x = index - j;
			j = index;
		}
		else {
			if (temp->size > 0)
				j += temp->size - 1;
		}
		if (j < index)
			temp = temp->next;
	}
	if (temp == NULL)
		return false;
	if (x > temp->size - 1)
		return false;
	int i = temp->sections[x].attributes.search(s);
	if (i >= 0) {
			temp->sections[x].attributes.remove(i);
			temp->sections[x].values.remove(i);
	}
	else
		return false;
	if (temp->sections[x].attributes.IsEmpty()) {
		remove(index+1);
	}
	return true;
}

int List::HowMany() {
	Node* temp = first;
	int i = 0;
	while (temp != NULL) {
		i += temp->size;
		temp = temp->next;
	}
	return i;
}

int List::HowManyInSection(int index, char ch) {
	Node* temp = first;
	index--;
	int x = index;
	for (int j = 0; j <= index && temp != NULL; j++) {
		if (temp->size > index - j) {
			x = index - j;
			j = index;
		}
		else {
			if (temp->size > 0)
				j += temp->size - 1;
		}
		if (j < index)
			temp = temp->next;
	}
	if (temp == NULL) return -1;
	if (x > temp->size - 1)
		return false;
	else if (ch == 'S') return temp->sections[x].selectors.HowMany();
	else if (ch == 'A') return temp->sections[x].attributes.HowMany();
	else return -1;
}

int List::HowManyElem(String& s, char ch) {
	Node* temp = first;
	int sum = 0;
	while (temp != NULL) {
		for (int x = 0; x < temp->size; x++)
		{
			if (ch == 'S') {
				if (temp->sections[x].selectors.search(s) != -1)
					sum++;
			}
			else if (ch == 'A') {
				if (temp->sections[x].attributes.search(s) != -1)
					sum++;
			}
		}
		temp = temp->next;
	}
	return sum;
}

String List::SelInSection(int index, int j) {
	index--;
	Node* temp = first;
	int x = index;
	for (int j = 0; j <= index && temp != NULL; j++) {
		if (temp->size > index - j) {
			x = index - j;
			j = index;
		}
		else {
			if (temp->size > 0)
				j += temp->size - 1;
		}
		if (j < index)
			temp = temp->next;
	}
	if (temp == NULL)
		return ";";
	else
		return temp->sections[x].selectors.search(j);
}

String List::AttrInSection(int index, String& s) {
	index--;
	Node* temp = first;
	int x = index;
	for (int j = 0; j <= index && temp != NULL; j++) {
		if (temp->size > index - j) {
			x = index - j;
			j = index;
		}
		else {
			if (temp->size > 0)
				j += temp->size - 1;
		}
		if (j < index)
			temp = temp->next;
	}
	if (temp == NULL)
		return ";";
	else {
		int j = temp->sections[x].attributes.search(s) + 1;
		if (j == -1)
			return ";";
		else
			return temp->sections[x].values.search(j);
	}
}

String List::search_value(String& sel, String& attr) {
	Node* temp = last;
	int x = -1;
	while (temp != NULL) {
		for (x = temp->size - 1; x >= 0; x--) {
			if (temp->sections[x].selectors.search(sel) != -1)
				break;
		}
		if (x != -1)
			break;
		temp = temp->previous;
	}
	if (temp == NULL)
		return ";";
	int i = temp->sections[x].attributes.search(attr) + 1;
	if (i == -1)
		return ";";
	return temp->sections[x].values.search(i);
}