// Main.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "Stack.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <Windows.h>
int* GetArray(int N, int K) {
	std::stringstream filename;
	filename << "K = " << K << ".txt";
	std::ifstream file(filename.str());
	//Если нет файла с готовым массивом, создаётся новый, иначе просто используем тот же файл, что и использовался ранее
	if (!file.good()) {
		file.close();
		srand(time(0));
		int* array = new int[10000];
		for (int i = 0; i < 10000; i++) array[i] = std::rand() % K;
		std::ofstream filewrite(filename.str());
		for (int i = 0; i < 10000; i++) filewrite << array[i] << " ";
		filewrite.close();
		file.open(filename.str());
	}
	int* output = new int[N];
	for (int i = 0; i < N; i++) file >> output[i];
	file.close();
	return output;
}

int main()
{
	setlocale(LC_ALL, "Russian");

	int N;
	const int K = 1000;
	std::cout << "Введите N (N_min = 3000) > ";
	std::cin >> N;


	//Получение из файла (или создание) массива из случайных чисел размером N
	int* arr = GetArray(N, K);

	int* sort = new int[K];
	std::fill_n(sort, K, 0);



	Stack A;
	Stack C;

	A.push(arr, N); //инициализация стека элементами из массива
	C.push(sort, K); //инициализация словаря

	std::cout << "Сортируемый стек: " << std::endl;
	for (int i = 0; i < N; i++) std::cout << A[i] << " ";
	std::cout << std::endl;

	//Алгоритм сортировки подсчётом с использованием стека:
	unsigned int t1 = GetTickCount64();
	for (int i = 0; i < N; i++) { C[A[i]]++; } 
	int k = 0;
	for (int i = 0; i < K; i++) while (C[i]--) A[k++] = i; 
	unsigned int t2 = GetTickCount64();
	//

	std::cout << "Отсортированный стек:" << std::endl;
	for (int i = 0; i < N; i++) { std::cout << A[i] << ' '; }

	std::cout << std::endl << "T = " << t2 - t1 << "ms" << std::endl;
}