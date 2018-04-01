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

#define COUNT 5
#include "List.h"

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_CTYPE, "rus");
	srand( time(0) );
	//чтобы не запрашивать у пользователя каждый раз
	int customInput;

	List<int> list;
	//заполняем список (просто для объема)
	for (int i = 0; i<COUNT; i++)
	{
		list.addToBegin(rand() % 100);
	}
	list.show();

	//добавление элемента после последнего;
	customInput = rand() % 100;
	std::cout << "Добавление элемента после последнего (" << customInput << ") \n";
	list.addToEnd(customInput);
	list.show();

	//добавление элемента перед первым;
	customInput = rand() % 100;
	std::cout << "\nДобавление элемента перед первым (" << customInput << ") \n";
	list.addToBegin(customInput);
	list.show();

	//удаление элемента с указанной информационной частью;
	std::cout << "\nУдаление элемента:";
	std::cin >> customInput;
	list.deleteElem(customInput);
	list.show();

	//поиск элемента;
	std::cout << "\nПоиск элемента: ";
	std::cin >> customInput;
	list.findElem(customInput);
	list.show();

	//сортировка элементов;
	std::cout << "\nСортировка элементов, список \" до\" \n";
	list.show();
	list.sort();
	std::cout << "Сортировка элементов, список \" после\" \n";
	list.show();

	//добавление элемента по порядку;
	customInput = rand() % 100;
	std::cout << "\nДобавление элемента по порядку (" << customInput << ") \n";
	list.addSorted(customInput);
	list.show();

	//упорядочение текущего элемента (предполагается, что все остальные элементы упорядочены)
	customInput = rand() % 100;
	std::cout << "\nДобавление элемента в начало (" << customInput << ") и сортировка текущего элемента\n";
	list.addToBegin(customInput);
	list.setCurrToHead(); // задаем текущий элемент = голове
	list.sortCurrElem();// сортируем текущий элемент
	list.show();

	//копирование структуры данных с помощью перегруженного оператора присваивания;
	List<int> list2;
	if (!list2)
	{
		list2 = list;
	}
	//list2 = list;
	std::cout << "\nСодание списка list2 и присваивание ему значение list \n list2: \n";
	list2.show();
	

	//удаление всех элементов;
	std::cout << "\nУдаление всех элементов list \n";
	list.deleteAllElems();

	
	std::cout << std::endl;
	std::cout << "Вызов list.show() в пустом списке \n";
	list.show();

	std::cout << "\nlist2 элементы: ";
	list2.show();

	std::cout << "\nlist2 текущий элемент: ";
	std::cout << list2.getCurrElem();

	++list2;
	std::cout << "\nlist2 текущий элемент: ";
	std::cout << list2.getCurrElem();
	std::cout << std::endl;

	return 0;
}
