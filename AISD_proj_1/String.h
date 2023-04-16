#pragma once
#include <iostream>
#include <string.h>
class String
{
private:
	char* text = NULL;
	size_t size = 0;
	static int num;
public:
	String();
	String(const char* txt);
	String(const String& str);
	String& operator=(const char* txt);
	String& operator=(const String & str);
	int getSize() const;
	void operator+=(char ch);
	friend bool operator==(String & str, const char* text);
	friend bool operator==(String & str1, String & str2);
	friend bool operator!=(String str, const char* text);
	friend std::ostream& operator<<(std::ostream & os, String str);
	int string_to_int();
	~String();
	char& operator[](int i);
	const char& operator[](int i) const;
};

