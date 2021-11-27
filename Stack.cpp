#include "Stack.h"
#include <stdexcept>
Stack::Stack() {
	size = 0;
}

Stack::Stack(Stack* src) {  
	size = src->getSize(); 
	if (checksize()) { 
		Stack temp;
		int val;
		for (int i = size; i > 0; i--) {
			temp.push(src->pop()); 
		}
		for (int i = size; i > 0; i--) { 
			val = temp.pop(); 
			this->push(val); 
			src->push(val); 
		}
	}
}
Stack::~Stack()
{
	clear();
}
bool Stack::checksize() { 
	if (size) return true;
	else return false;
}
bool Stack::checkpos(int pos) { 
	if (pos > size) return false;
	else return true;
}

void Stack::push(int value) {
	item.push_back(value);
	size++;
}
void Stack::push(int* array, int N) { 
	for (int i = 0; i < N; i++) push(array[i]); 
}

int Stack::pop() { 
	int value = peek(); 
	item.pop_back(); 
	size--; 
	return value; 
}

int Stack::peek()
{
	return item.back(); 
}
int& Stack::peek(char addr) { 
	return item.back();
}

unsigned int Stack::getSize() {
	return size;
}

int Stack::get(unsigned int pos) 
{
	if (checkpos(pos)) { 
		Stack buffer(this); 
		int result; 

		for (int i = size; i >= size-pos; i--) {
		
			result = buffer.pop(); 
		}
		return result; 
	}
	else throw std::runtime_error("POS ERR");
}

void Stack::set(int value, unsigned int pos) 
{
	if (checkpos((pos))) { 
		Stack buffer; 
		
		for (int i = 0; i < pos;i++) buffer.push(this->pop()); 
		this->pop(); 
		this->push(value); 
		while (buffer.checksize()) this->push(buffer.pop()); 
	}
}
void Stack::clear() 
{
	item.clear();
}

int& Stack::operator[](unsigned int pos)
{
	if (checkpos((pos))) { 
		Stack buffer; 
		
		for (int i = 0; i < pos;i++) buffer.push(this->pop()); 
		int &addr = this->peek(1); 
		while (buffer.checksize()) this->push(buffer.pop()); 
		return addr;
	}
}