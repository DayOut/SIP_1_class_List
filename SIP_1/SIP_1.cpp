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

#include "blist.h"

#define COUNT 1000000

#include "List.h"

int _tmain(int argc, _TCHAR* argv[])
{
    setlocale(LC_CTYPE, "rus");  
    
    List<int> lista;
    for (int i = 0; i<5; i++)
    {
        int tmp = rand() % (10);
        lista.addToBegin(tmp);
    }

    out << lista << std::endl;
    lista.sort();
    out << lista << std::endl;
    lista.setCurrToHead();
    ++lista;
    int *val = NULL;

    std::cout.setf(std::ios::boolalpha);
    val = &lista.getCurrInfPtr();
    for (int i = 0; i < 100; i++)
    {
        std::cout << "Current elem : " << lista.getCurrElem() << std::endl;
        
        std::cin >> *val;
        lista.sortCurrElem();
        out << lista.bubleCheck() << "\t";
        out << lista;

    }

    List<int> listb(lista);
    out << listb;


    /*
    std::cout << "Введите сколько элементов должно быть в списке: ";
    int count;
    std::cin >> count;

    TBList<int> tblist;
    List<int> list;

    std::cout << "Сортировка Егорова: \n";

    for (int i = 0; i<count; i++)
    {
        int tmp = rand() % (count);
        tblist.AddBeforeHead(tmp);
        list.addToBegin(tmp);
    }

    List<int> list2 = list;
    std::cout << "list: \n";
    list.show();

    list2.addToBegin(57);
    list2.addToBegin(57);
    list2.addToBegin(57);
    list2.addToBegin(57);
    list2.addToBegin(57);
    list2.addToBegin(57);
    std::cout << "list2: \n";
    list2.show();

    list2 = list;
    std::cout << "list2: \n";
    list2.show();
    */
    //std::cout << list;
    /*
    unsigned int start_time1 = clock(); // начальное время
    tblist.SortListBiDir();
    unsigned int end_time1 = clock(); // начальное время
    std::cout << "Времени на сортировку: " << end_time1 - start_time1 << " ms \n";

    std::cout << "\nlist cписок элементов: \n";
    //list.show();

    //добавление элемента после последнего;
    customInput = rand() % 100;
    std::cout << "Добавление элемента после последнего (" << customInput << ") \n";
    list.addToEnd(customInput);
    //list.show();

    //добавление элемента перед первым;
    customInput = rand() % 100;
    std::cout << "\nДобавление элемента перед первым (" << customInput << ") \n";
    list.addToBegin(customInput);
    //list.show();

    //удаление элемента с указанной информационной частью;
    std::cout << "\nУдаление элемента:";
    std::cin >> customInput;
    list.deleteElem(customInput);
    //list.show();

    //поиск элемента;
    std::cout << "\nПоиск элемента: ";
    std::cin >> customInput;
    list.findElem(customInput);
    //list.show();

    //сортировка элементов;
    std::cout << "\nСортировка элементов, список \" до\" \n";
    //list.show();
    unsigned int start_time = clock(); // начальное время
    list.sort();
    unsigned int end_time = clock(); // начальное время
    std::cout << "Сортировка элементов, список \" после\" \n";
    //list.show();
    //std::cout << "Кол-во сравнений при сортировке: " << comp << std::endl;
    std::cout << "Времени на сортировку: " << end_time - start_time << " ms \n";
    list.bubleCheck();

    //добавление элемента по порядку;
    customInput = rand() % 100;
    std::cout << "\nДобавление элемента по порядку (" << customInput << ") \n";
    list.addSorted(customInput);
    //list.show();

    //упорядочение текущего элемента (предполагается, что все остальные элементы упорядочены)
    customInput = rand() % 100;
    std::cout << "\nДобавление элемента в начало (" << customInput << ") и сортировка текущего элемента\n";
    list.addToBegin(customInput);
    list.setCurrToHead(); // задаем текущий элемент = голове
    list.sortCurrElem();// сортируем текущий элемент
    //list.show();

    //копирование структуры данных с помощью перегруженного оператора присваивания;
    List<int> list2;
    if (!list2)
    {
        list2 = list;
    }
    std::cout << "\nСодание списка list2 и присваивание ему значение list \n list2: \n";
    //list2.show();


    //удаление всех элементов;
    std::cout << "\nУдаление всех элементов list \n";
    list.deleteAllElems();

    // демонстрация удаленного списка
    std::cout << std::endl;
    std::cout << "Вызов list.show() в пустом списке \n";
    //list.show();


    std::cout << "\nlist2 элементы: \n";
    //list2.show();

    //получение текущего элемента списка
    std::cout << "list2 текущий элемент: ";
    std::cout << list2.getCurrElem();

    //перегруженный оператор ++
    std::cout << "\n++list2\n";
    ++list2;
    std::cout << "\nlist2 текущий элемент: ";
    std::cout << list2.getCurrElem();
    std::cout << std::endl;
    */
    system("pause");
    return 0;
}
