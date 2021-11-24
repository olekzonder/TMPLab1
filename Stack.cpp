#include "Stack.h"
#include <stdexcept>
Stack::Stack() {
	size = 0; //+1
	N_op++;
}

Stack::Stack(Stack* src) {  //Клонирование стека, F(N) = 1+2+1+1+2+2+13N+9N = 22N+9
	N_op += 22;
	size = src->getSize(); //+1
	if (checksize()) { //+2
		Stack temp; //+1
		int val; //+1

		//+2 цикл
		for (int i = size; i > 0; i--) { //+9N
			//+1 +1 цикл
			temp.push(src->pop()); //+4 pop, +3 push
			N_op += 9;
		}
		//+2 цикл
		for (int i = size; i > 0; i--) { //+13N
			//+2 цикл
			val = temp.pop(); //+4 pop +1 присвоение переменной, итого +5
			this->push(val); //+3
			src->push(val); //+3
			N_op += 13;
		}
	}
}
Stack::~Stack()
{
	clear();
}
bool Stack::checksize() { //Проверка, пустой ли стек, F(N) = 2
	N_op += 2;
	if (size) return true;
	else return false;
}
bool Stack::checkpos(int pos) { //Проверка на выход за пределы стека для ф-ций get, set и перегрузки [], F(N) = 2
	N_op += 2;
	if (pos > size) return false;
	else return true;
}

void Stack::push(int value) { //Реализация функции push, F(N) = 3;
	N_op += 3;
	item.push_back(value); //+1
	size++; //+1
}
void Stack::push(int* array, int N) { //Перегрузка функции push для работы с массивом, F(N) = 3*N;
	for (int i = 0; i < N; i++) {
		N_op += 3;
		push(array[i]); //3
	}
}

int Stack::pop() { //Реализация функции pop, F(N) = 4;
	int value = peek(); //+1
	item.pop_back(); //+1
	size--; //+1
	return value; //+1
	N_op += 4;
}

int Stack::peek() //Просмотреть элемент стека без удаления элемента, F(N) = 1;
{
	N_op++;
	return item.back(); //+1
}

int& Stack::peek(char addr) { //Перегрузка функции peek для получения адреса элемента, F(N)=2
	N_op += 2;
	return item.back();
}
unsigned int Stack::getSize() //Получить размер стека, F(N) = 1
{
	N_op++;
	return size;
}

int Stack::get(unsigned int pos) //Функция get - получение элемента стека по позиции, F(N) = 7N+22N+9+2+1+3+1=29N+16
{
	N_op += 16;
	if (checkpos(pos)) { //+2
		Stack buffer(this); //22N+9
		int result; //+1
		//+3 цикл
		for (int i = size; i >= size-pos; i--) { //Худший случай - получение значения в самом низу стека, 7*N
			//+2 цикл
			result = buffer.pop(); //+4 pop +1 назначение, итого +5
			N_op += 7;
		}
		return result; //+1
	}
	else throw std::runtime_error("POS ERR");
}

void Stack::set(int value, unsigned int pos) //Функция set - установление значения по позиции, F(N) = 2+1+2+2+7N+9N-9+2 = 16N
{
	if (checkpos((pos))) { //+2
		Stack buffer; //+1
		//+2 цикл
		for (int i = 0; i < pos;i++) buffer.push(this->pop()); //+4 pop +3 push +2 цикл, итого 7*N т.к худший случай - установка значения в самом низу стека
		this->pop(); //+4
		this->push(value); //+3
		N_op += 7;
		//+2 условие цикла
		while (buffer.checksize()) {
			this->push(buffer.pop());
				N_op += 7;
		}; //+4 pop +3 push +2 условие цикла, худший случай - N-1, итого 9N-9
	}
}
void Stack::clear() //Очистить весь стек для деструкторa, F(N) = 1
{
	item.clear(); //+1
}

int& Stack::operator[](unsigned int pos) //Перегрузка оператора [], F(N) = 2+1+2+2+1+1+1+9N+9N-9 = 18N+1
{
	if (checkpos((pos))) { //+2
		Stack buffer; //+1
		//+2 цикл
		N_op += 10;
		for (int i = 0; i < pos; i++) { 
			buffer.push(this->pop()); 
			N_op += 9;
		} //+4 pop +3 push +2 цикл, 9N
		int &addr = this->peek(1); //+2 peek +1 присвоение
		N_op += 7;
		while (buffer.checksize()) {
			this->push(buffer.pop());
			N_op += 9;
		} //9N-9
		return addr; //+1
	}
}

long long Stack::get_Nop()
{
	return N_op;
}
