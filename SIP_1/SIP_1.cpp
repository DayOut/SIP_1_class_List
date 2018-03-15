/*
	Класс для реализации работы с однонаправленным списком, которая хранит список данных

	Если что-то не работает - пишите сюда https://t.me/Novarely 
*/

#include "stdafx.h"
#define COUNT 1000000
// just for tests
// int mas[] =	{ 27,	7,	6,	5,	4,	3,	2,	1,	0,	25 };
//int mas[] = { 15, 12, 18, 26, 23, 38, 31, 39, 40, 41 };


template <typename LISTTYPE>
class List 
{
private:
	template <typename LISTTYPE>
	struct TElem //структура самого элемента списка
	{
		LISTTYPE inf;
		TElem<LISTTYPE> *next;
	};

	TElem<LISTTYPE> *head, *elem; // переменная указатель на голову списка
	//elem - это указатель на текущий элемент, пока класс существует - существует список и этот элемент
	

public:
	List() 
	{
		head = NULL; 
	}
	
	List(LISTTYPE value)
	{
		head->inf = value;
		head->next = NULL;
	}


	void addToBegin(const LISTTYPE& value) // add_to_begin / add_begin 
	{
		TElem<LISTTYPE> *tmp = new TElem<LISTTYPE>; // выделяем память на новый элемент
		tmp->inf = value;	// записываем значение 
		tmp->next = head;	
		head = tmp;
	}

	//функция добавления элемента в конец списка
	void addToEnd(LISTTYPE value) // add_end / ...
	{
		if(!head) // если список отсутствует ()
		{
			head = new TElem<LISTTYPE>;	// Выделяем память под новый элемент
			head->inf = value;	// записываем значение 
			head->next = NULL;	// указатель на последний элемент
		}
		else
		{
			elem = head;
			while(elem->next)
			{
				elem = elem->next; // доходим до конца списка
			}
			TElem<LISTTYPE> *tmp = new TElem<LISTTYPE>; // выделяем память на новый элемент
			tmp->inf = value;	// записываем значение 
			tmp->next = NULL;	
			elem->next = tmp;
		}
	}

	//ф-ция для вывода информационной части жлементов списка (пока используется только для отладки)
	void show()
	{
		if (COUNT > 100) return;

		elem = head;
		while(elem)
		{
			cout << elem->inf << "\t";
			elem = elem->next; // доходим до конца списка
		}
		cout << endl;
	}

	void show(TElem<LISTTYPE> *list)
	{
		TElem<LISTTYPE> *tmp = list;
		for (; tmp; tmp = tmp->next)
			cout << tmp->inf << " ";
		cout << endl;
	}

	//----------------------------------------------------------------------------------------------------------------------------
	static struct TElem<LISTTYPE>* mergeList(struct TElem<LISTTYPE> *list1, struct TElem<LISTTYPE> *list2)
	{
		struct TElem<LISTTYPE> tempHead = { 0, NULL }, *tail = &tempHead;

		while ((list1 != NULL) && (list2 != NULL))
		{
			struct TElem<LISTTYPE> **min = (list1->inf < list2->inf) ? &list1 : &list2;
			struct TElem<LISTTYPE> *next = (*min)->next;
			tail = tail->next = *min;
			*min = next;
		}
		tail->next = list1 ? list1 : list2;
		return tempHead.next;
	}

	/**
	* Возвращает указатель на элемент структуры TElem<LISTTYPE> рядом с серединой списка
	* и после обрезаем оригинальный списко перед этим элементом
	*/
	void findMid(struct TElem<LISTTYPE> *root, struct TElem<LISTTYPE> **list1, struct TElem<LISTTYPE> **list2)
	{

		struct TElem<LISTTYPE> *slow, *fast;

		//в случае пустого списка (или один элемент)
		if ((root == NULL) || (root->next == NULL))
		{
			*list1 = root;
			*list2 = NULL;
			return;
		}
		else
		{
			/*
				два курсора, fast движется в 2 раза быстрее slow, на одну итерацию slow происходит 2 итерации fast
				за счет этого находится середина списка (когда fast == NULL, slow будет ровно в центре списка)
			*/
			slow = root;
			fast = root->next;
			while (fast != NULL)
			{
				fast = fast->next;
				if (fast != NULL)
				{
					slow = slow->next;
					fast = fast->next;
				}
			}

			*list1 = root;
			*list2 = slow->next;
			slow->next = NULL; 
		}
	}


	void mergeSort()
	{
		mergeSort(&head);
	}

	void mergeSort(struct TElem<LISTTYPE> **root)
	{
		struct TElem<LISTTYPE> *list1, *list2;
		struct TElem<LISTTYPE> *head = *root;
		if ((head == NULL) || (head->next == NULL))
		{
			return;
		}

		findMid(head, &list1, &list2);

		mergeSort(&list1);
		mergeSort(&list2);

		*root = mergeList(list1, list2);

	}
	//----------------------------------------------------------------------------------------------------------------------------

	/*
		Функция поиска элемента. Поскольку поиск элемента идет по значению, никто не 
		исключает возможность дублирования иноформации, поэтому необходим поиск по 
		всему списку с выводом всех найденых элементов.
		Но для начала поиск будет по принципу "есть ли такой элемент вообще?"
	*/
	TElem<LISTTYPE> search(LISTTYPE value)
	{
		// пока только один элемент искать будем

		// TODO: поиск элемента
	}

	~List()
	{
		if(head)
		{	
			
			while (head->next) // поэлементно удаляем все жлементы списка
			{
				TElem<LISTTYPE> *tmp = head;
				head = head->next;
				delete tmp;
			}
			//далее есть небольшие сомнения в правильности
			// тут у нас остается последний элемент
			delete [] head; // удаляем его

		}
	}
	

};


using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_CTYPE, "rus");
	srand( time(0) );

	List<int> test;
	wcout << L"Сортировка списка из " << COUNT << L" элементов\n";
	wcout << L"Заполняем структуру...\n";
	unsigned int start = clock();
	
	for(int i=0; i<COUNT; i++)
	{
		test.addToBegin(rand() %100);
	}
	unsigned int end = clock();
	test.show();
	wcout << L"Времени на заполнение: " << end - start << L" мс \n";
	wcout << L"Заполнили структуру...\n";
	
	cout << "Сортировка..." << endl; 
	start = clock();
	test.mergeSort();
	end = clock();
	wcout << L"Времени на заполнение: " << end - start << L" мс \n";
	test.show();

	cout << endl;
	system("pause");
	return 0;
}
