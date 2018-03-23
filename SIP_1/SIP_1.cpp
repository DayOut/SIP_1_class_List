/*
	Класс для реализации работы с однонаправленным списком, которая хранит список данных
	Если что-то не работает - пишите сюда https://t.me/Novarely 
*/

#include "stdafx.h"
#include <stdio.h>
#include <tchar.h>
#include <ctime>
#include <time.h>
#include <iostream>

#define COUNT 1000000

#include "List.h"




// just for tests
// int mas[] =	{ 27,	7,	6,	5,	4,	3,	2,	1,	0,	25 };
//int mas[] = { 15, 12, 18, 26, 23, 38, 31, 39, 40, 41 };





int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_CTYPE, "rus");
	srand( time(0) );
	int tmp;

	List<int> test;
	std::wcout << L"Сортировка списка из " << COUNT << L" элементов\n";
	std::wcout << L"Заполняем структуру...\n";
	unsigned int start = clock();
	
	for(int i=0; i<COUNT; i++)
	{
		test.addToBegin(rand() %100);
	}
	unsigned int end = clock();
	test.show();
	std::wcout << L"Времени на заполнение: " << end - start << L" мс \n";
	std::wcout << L"Заполнили структуру...\n";
	
	std::wcout << L"Сортировка..." << std::endl;
	start = clock();
	test.Sort();
	end = clock();
	std::wcout << L"Времени на сортировку: " << end - start << L" мс \n";
	test.show();
	std::wcout << L"Comparison = " << test.comparison << std::endl;
	std::wcout << L"Deep = " << test.deep << std::endl;

	std::wcout << L"Удаление числа: ";
	std::wcin >> tmp;
	test.deleteElem(tmp);
	test.show();

	//test.deleteAllElems();
	//test.show();
	
	std::wcout << L"Добавление в начало числа: ";
	std::wcin >> tmp;
	//test.addToEnd(tmp); // fix
	test.addToBegin(tmp);
	test.show();
	//TODO: find elem by inf and sort this element as TElem into the right place
	// maybe it's woud be a good idea to create temp func which can sort current element
	std::wcout << "findig and sorting elem " << tmp << std::endl;
	test.findAndSort(tmp);

	//try to sort added elem
	test.show();
	std::cout << std::endl;
	system("pause");
	return 0;
}
