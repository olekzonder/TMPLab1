#pragma once
#include <vector>
class Stack
{
private:
	unsigned int size;
	std::vector <int> item;
	bool checksize();
	bool checkpos(int pos);
	long long N_op;
public:
	Stack();
	Stack(Stack*);
	~Stack();
	void push(int value);
	void push(int* arr,int N);
	int pop();
	int peek();
	int& peek(char addr);
	unsigned int getSize();
	int get(unsigned int pos);
	void set(int value, unsigned int pos);
	void clear();
	int& operator[] (unsigned int index);
	long long get_Nop();
};

