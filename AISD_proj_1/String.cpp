#define _CRT_SECURE_NO_WARNINGS
#include "String.h"
#include <math.h>

String::String() {
	text = new char[1];
	size = 0;
	text[0] = '\0';
	
}
String::String(const char* txt) {
		size = strlen(txt);
		text = new char[size + 1];
		strcpy(text, txt);
}

String::String(const String & str) {
	size = str.size;
	text = new char[size + 1];
	strcpy(text, str.text);
}

String& String::operator=(const char* txt) {
	delete[] text;
		size = strlen(txt);
		text = new char[size + 1];
		strcpy(text, txt);
	return *this;
}

String& String::operator=(const String & str) {
	delete[] text;
		size = str.size;
		text = new char[size + 1];
		strcpy(text, str.text);
	return *this;
}

String::~String() {
	delete[] text;
}

char& String::operator[](int i) {
	return text[i];
}

const char& String::operator[](int i) const{
	return text[i];
}

bool operator==(String& str, const char* text) {
	if (str.size != strlen(text)) 
		return false;
	for (int i = 0; i < strlen(text); i++) {
		if (str[i] != text[i])
			return false;
	}
	return true;
}

bool operator==(String& str1, String& str2) {
	if (str1.size != str2.size)
		return false;
	for (int i = 0; i < str2.size; i++) {
		if (str1[i] != str2[i])
			return false;
	}
	return true;
}

bool operator!=(String str, const char* text) {
	return !(str == text);
}

void String::operator+=(char ch) {
		size++;
		char* temp = new char[size + 1];
		strcpy(temp, text);
		temp[size - 1] = ch;
		temp[size] = '\0';
		delete[] text;
		text = temp;
}

int String::string_to_int() {
	for (int i = 0; i < size; i++) {
		if (text[i] < '0' || text[i] > '9') return -1;
	}
	int sum = 0;
	for (int i = 0; i < size; i++) {
		int number = int(text[i]) - int('0');
		sum += number * pow(10, size - i - 1);
	}
	return sum;
}

std::ostream& operator<<(std::ostream& os, String str) {
	os << str.text;
	return os;
}

int String::getSize() const {
	return size;
}