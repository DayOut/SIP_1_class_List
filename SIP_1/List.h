#pragma once

template <typename LISTTYPE> class ListIterator;

template <typename LISTTYPE>
class List
{

    friend ListIterator<LISTTYPE>;

private:
    template <typename LISTTYPE>
    struct TElem //��������� ������ �������� ������
    {
        LISTTYPE		inf;
        TElem<LISTTYPE> *next;
    };

    TElem<LISTTYPE>		*headPtr,
        *tailPtr,
        *currentPtr;	// ���������� ��������� �� ������ ������
                        //currentPtr - ��� ��������� �� ������� �������, ���� ����� ���������� - ���������� ������ � ���� �������

    TElem<LISTTYPE>*	getHeadPtr();
    void                deleteCurrentElement(TElem<LISTTYPE> *prevTmp);

public:
    List();
    //List(const List& value);
    ~List();

    //bool				isEmpty() const;
    bool				operator!() const;
    List<LISTTYPE>&		operator++();
    const List<LISTTYPE>& operator= (List<LISTTYPE>& right);



    LISTTYPE&			getCurrInfPtr();
    LISTTYPE			getCurrElem();
    void				setCurrToHead();


    TElem<LISTTYPE>*	findElem(LISTTYPE value);

    void				addToBegin(const LISTTYPE& value);

    void				addToEnd(const LISTTYPE& value);

    void				addSorted(const LISTTYPE& value);
    void				sortCurrElem();

    bool				deleteElem(const LISTTYPE& value);
    void				deleteAllElems();

    void				show();
    void				show(TElem<LISTTYPE> *list);

    void				sort();
    void                findTail();
    bool				bubleSort();

private:
    void				mergeSort(struct TElem<LISTTYPE> **root);
    static TElem<LISTTYPE>* mergeList(struct TElem<LISTTYPE> *list1, struct TElem<LISTTYPE> *list2);
    void				findMid(struct TElem<LISTTYPE> *root, struct TElem<LISTTYPE> **list1, struct TElem<LISTTYPE> **list2);
};


template <typename LISTTYPE>
List<LISTTYPE>::List()
{
    headPtr = NULL;
    tailPtr = NULL;
    currentPtr = NULL;
}

template <typename LISTTYPE>
List<LISTTYPE>::~List()
{
    deleteAllElems();
    headPtr = NULL;
    tailPtr = NULL;
    currentPtr = NULL;
}

template <typename LISTTYPE>
bool List<LISTTYPE>::operator!() const
{
    return (headPtr == NULL);
}

template <typename LISTTYPE>
const List<LISTTYPE>& List<LISTTYPE>::operator= (List<LISTTYPE>& right)
{

    if (this == &right) //�������� �� ���������������� 
    {
        return *this;
    }

    TElem<LISTTYPE> *rightHead = right.getHeadPtr();
    TElem<LISTTYPE> *rightCurrent = rightHead;

    TElem<LISTTYPE> *tmp = headPtr, *prevTmp = NULL; // ������� � ����� ������

    while (tmp || rightCurrent)
    {
        if (rightCurrent && tmp)
        {
            tmp->inf = rightCurrent->inf;
        }
        else if (tmp && !rightCurrent)
        {
            currentPtr = tmp;
            tmp = prevTmp;
            deleteCurrentElement(prevTmp);
        }
        else if (!tmp && rightCurrent)
        {
            addToEnd(rightCurrent->inf);
        }

        if (prevTmp != tmp)
            prevTmp = (tmp) ? tmp : NULL;

        if (tmp)
            tmp = (tmp->next == NULL) ? NULL : tmp->next;

        if (rightCurrent)
            rightCurrent = (rightCurrent->next == NULL) ? NULL : rightCurrent->next;
    }
    return *this;
}

template<typename LISTTYPE>
List<LISTTYPE>& List<LISTTYPE>::operator++()
{
    currentPtr = (currentPtr) ? currentPtr->next : ((headPtr) ? headPtr : NULL);
    return *this;
}

template<typename LISTTYPE>
typename List<LISTTYPE>::TElem<LISTTYPE>* List<LISTTYPE>::getHeadPtr()
{
    return (headPtr) ? headPtr : NULL;
}

template <typename LISTTYPE>
LISTTYPE& List<LISTTYPE>::getCurrInfPtr()
{
    if (headPtr)
    {
        if (currentPtr)
        {
            return currentPtr->inf;
        }
    }
    return false;
}

template<typename LISTTYPE>
LISTTYPE List<LISTTYPE>::getCurrElem()
{
    if (headPtr)
    {
        if (currentPtr)
        {
            return currentPtr->inf;
        }
        else
        {
            currentPtr = headPtr;
            return currentPtr->inf;
        }
    }
    return false;
}

template<typename LISTTYPE>
void List<LISTTYPE>::deleteCurrentElement(TElem<LISTTYPE> *prevTmp)
{
    TElem<LISTTYPE> *tmp;
    if (!headPtr)
        return;
    else if (currentPtr == headPtr)
    {
        tmp = headPtr;

        if (headPtr->next == headPtr)
        {
            headPtr = NULL;
        }
        else
        {
            currentPtr = headPtr->next;
            headPtr = currentPtr;
            tailPtr->next = headPtr;
        }
    }
    else
    {
        tmp = currentPtr;
        currentPtr = currentPtr->next;
        prevTmp->next = currentPtr;

    }
    delete tmp;
}

template <typename LISTTYPE>
void List<LISTTYPE>::setCurrToHead()
{
    if (headPtr)
    {
        currentPtr = headPtr;
    }
}

template<typename LISTTYPE>
typename List<LISTTYPE>::TElem<LISTTYPE>* List<LISTTYPE>::findElem(LISTTYPE value)
{
    if (headPtr)
    {
        for (currentPtr = headPtr; currentPtr; currentPtr = currentPtr->next)
        {
            if (currentPtr->inf == value)
            {
                return currentPtr;
            }
        }
    }
    return NULL;
}

template <typename LISTTYPE>
void List<LISTTYPE>::addToBegin(const LISTTYPE& value)
{
    TElem<LISTTYPE> *tmp = new TElem<LISTTYPE>; // �������� ������ �� ����� �������
    tmp->inf = value;	// ���������� �������� 
    tmp->next = headPtr;
    headPtr = tmp;
    if (!tailPtr)
    {
        tailPtr = headPtr;
    }
}

template <typename LISTTYPE>
void List<LISTTYPE>::addToEnd(const LISTTYPE& value)
{
    TElem<LISTTYPE> *tmp = new TElem<LISTTYPE>; // �������� ������ �� ����� �������
    tmp->inf = value;	// ���������� �������� 
    tmp->next = NULL;

    if (headPtr && tailPtr)
    {
        tailPtr->next = tmp;
        tailPtr = tmp;
    }
    else if(!headPtr)
    {
        headPtr = tmp;
        tailPtr = headPtr;
    }
}

template<typename LISTTYPE>
void List<LISTTYPE>::addSorted(const LISTTYPE& value)
{
    //if (isEmpty() || value <= headPtr->inf)
    if (!this || value <= headPtr->inf)
    {
        addToBegin(value);
    }
    else
    {
        currentPtr = headPtr;
        while (currentPtr->next)
        {
            if (currentPtr->next->inf > value)
            {
                break;
            }
            currentPtr = currentPtr->next;
        }
        TElem<LISTTYPE> *tmp = new TElem<LISTTYPE>; // �������� ������ �� ����� �������
        tmp->inf = value;	// ���������� �������� 
        tmp->next = currentPtr->next;
        currentPtr->next = tmp;
    }
}

template<typename LISTTYPE>
void List<LISTTYPE>::sortCurrElem()
{
    // �������� �� ������ ������
    if (!headPtr)
    {
        return;
    }

    // �������� �� ������� "��������" ��������
    if (!currentPtr)
    {
        currentPtr = headPtr;
    }

    TElem<LISTTYPE> *tmp = headPtr;

    if (currentPtr == headPtr)
    {
        if (currentPtr->inf <= headPtr->next->inf)
            return; // ������ ����������� ������ ���
                    //�������� 
        headPtr = headPtr->next;
    }
    else
    {
        //������� ��-� ����� �������
        while (tmp->next != currentPtr)
        {
            tmp = tmp->next;
        }

        if (currentPtr == tailPtr)
        {
            if (tmp->inf < currentPtr->inf)
                return;// ����� ��� ������ �����������

                       //��������
            tailPtr = tmp;
            tailPtr = currentPtr->next;
        }
        else
        {
            if (tmp->inf < currentPtr->inf && currentPtr->inf < currentPtr->next->inf)
                return;// ����� ��� ������ �����������

                       // ��������
            tmp->next = currentPtr->next;
            tmp = currentPtr;
            currentPtr = headPtr;
        }
    }

    tmp = (currentPtr->inf > currentPtr->next->inf) ? currentPtr->next : headPtr;

    while (currentPtr->inf > tmp->inf)
    {
        // ����� ������ �����
        if (tmp->next && currentPtr->inf <= tmp->next->inf)
        {
            //��������
            currentPtr->next = tmp->next;
            tmp->next = currentPtr;
            break;
        }
        
        if (tmp == tailPtr) //���� ����� �� ����� ������
        {
            currentPtr->next = NULL;
            tailPtr->next = currentPtr;
            tailPtr = currentPtr;
            
            break;
        }
        tmp = tmp->next;
    }

    /*
    // �������� �� ������ ������
    if (headPtr && tailPtr)
    {
        // �������� �� ������� "��������" ��������
        if (!currentPtr)
            currentPtr = headPtr;

        TElem<LISTTYPE> *tmp = headPtr;

        if (currentPtr == headPtr)
        {
            if (currentPtr->Inf <= headPtr->next->Inf)
                return; // ������ ����������� ������ ���

            headPtr = headPtr->next;
        }
        else
        {
            //������� ��-� ����� �������
            while (tmp->next != currentPtr)
            {
                tmp = tmp->next;
            }

            if (currentPtr == tail)
            {
                if (tmp->Inf < currentPtr->Inf)
                    return;// ����� ��� ������ �����������

                //��������
                tail = tmp;
                tail = currentPtr->next;
            }
            else
            {
                if (tmp->Inf < currentPtr->Inf && currentPtr->Inf < currentPtr->next->Inf)
                    return;// ����� ��� ������ �����������
                
                //��������
                tmp->next = currentPtr->next;
                tmp = currentPtr;
                currentPtr = tmp->next;
            }
        }



        // ���� ������� ������ ���������� - ���������� ������ ����� �������� �������� �� ������ ����� ������
        // ����� �� ����� �����
        tmp = (currentPtr->Inf > currentPtr->next->Inf) ? currentPtr->next : head;

        while (currentPtr->Inf > tmp->Inf)
        {
            // ����� ������ �����
            if (currentPtr->Inf <= tmp->next->Inf)
            {
                //��������
                currentPtr->next = tmp->next;
                tmp->next = currentPtr;
                break;
            }
            else if (tmp == tail) //���� ����� �� ����� ������
            {
                currentPtr->next = head;
                tail->next = currentPtr;
                tail = currentPtr;
                break;
            }
            tmp = tmp->next;
        }
    }*/
}

template<typename LISTTYPE>
bool List<LISTTYPE>::deleteElem(const LISTTYPE& value)
{
    TElem<LISTTYPE>* tmpPtr = NULL;
    bool findFlag = false;

    currentPtr = headPtr;

    if (headPtr->inf == value)
    {
        tmpPtr = headPtr;
        headPtr = headPtr->next;
        delete tmpPtr;
        findFlag = true;
    }
    else
    {
        while (currentPtr->next)
        {
            if (currentPtr->next->inf == value)
            {
                findFlag = true;
                break;
            }
            else
            {
                currentPtr = currentPtr->next;
            }
        }
        if (findFlag)
        {
            tmpPtr = currentPtr->next;
            currentPtr->next = tmpPtr->next;
            delete tmpPtr;
        }
    }

    if (!findFlag)
    {
        std::wcout << L"Elem was not found... \n";
    }
    return findFlag;
}

template<typename LISTTYPE>
void List<LISTTYPE>::deleteAllElems()
{
    currentPtr = headPtr;

    while (headPtr)
    {
        currentPtr = headPtr;
        headPtr = headPtr->next;
        delete currentPtr;
    }
    currentPtr = NULL;
    headPtr = tailPtr = NULL;
}

template<typename LISTTYPE>
void List<LISTTYPE>::show()
{/*
    if (SHOW_FLAG)
    {
        if (headPtr)
        {
            currentPtr = headPtr;
            while (currentPtr)
            {
                std::cout << currentPtr->inf << "\t";
                currentPtr = currentPtr->next; // ������� �� ����� ������
            }
            std::cout << std::endl;
        }
        else
        {
            std::wcout << L"������ ����!\n";
        }
    }*/
}

template<typename LISTTYPE>
void List<LISTTYPE>::show(TElem<LISTTYPE> *list)
{
    if (headPtr)
    {
        TElem<LISTTYPE> *tmp = list;
        for (; tmp; tmp = tmp->next)
            cout << tmp->inf << " ";
        cout << endl;
    }
    else
    {
        std::wcout << "List is empty!";
    }
}

template <typename LISTTYPE>
void List<LISTTYPE>::sort()
{
    mergeSort(&headPtr);
    findTail();
}

template <typename LISTTYPE>
void List<LISTTYPE>::findTail()
{
    if (!headPtr)
    {
        return;
    }

    TElem<LISTTYPE> *tmp = headPtr;
    while (tmp->next)
    {
        tmp = tmp->next;
    }
    tailPtr = tmp;
}

template<typename LISTTYPE>
bool List<LISTTYPE>::bubleSort() {
    TElem<LISTTYPE> *tmp = NULL, *prev = NULL;
    currentPtr = headPtr;
    bool flag = false, isChanged = false;
    do
    {
        flag = false;
        currentPtr = headPtr;
        while (currentPtr->next)
        {
            if (currentPtr->inf > currentPtr->next->inf)
            {
                return false;
            }
            prev = currentPtr;
            currentPtr = currentPtr->next;
        }
    } while (flag);

    return true;
}

template <typename LISTTYPE>
void List<LISTTYPE>::mergeSort(struct TElem<LISTTYPE> **root)
{
    struct TElem<LISTTYPE> *list1, *list2;
    struct TElem<LISTTYPE> *headPtr1 = *root;

    if ((headPtr1 == NULL) || (headPtr1->next == NULL))
    {
        return;
    }

    findMid(headPtr1, &list1, &list2);

    mergeSort(&list1);
    mergeSort(&list2);

    *root = mergeList(list1, list2);
}

template<typename LISTTYPE>
typename List<LISTTYPE>::TElem<LISTTYPE>* List<LISTTYPE>::mergeList(struct TElem<LISTTYPE> *list1, struct TElem<LISTTYPE> *list2)
{
    struct TElem<LISTTYPE> tempheadPtr = { 0, NULL }, *tail = &tempheadPtr;

    while ((list1 != NULL) && (list2 != NULL))
    {
        struct TElem<LISTTYPE> **min = (list1->inf < list2->inf) ? &list1 : &list2;
        struct TElem<LISTTYPE> *next = (*min)->next;
        tail = tail->next = *min;
        *min = next;
    }
    tail->next = list1 ? list1 : list2;
    return tempheadPtr.next;
}

template<typename LISTTYPE>
void List<LISTTYPE>::findMid(TElem<LISTTYPE> *root, TElem<LISTTYPE> **list1, TElem<LISTTYPE> **list2)
{
    /**
    * ���������� ��������� �� ������� ��������� TElem<LISTTYPE> ����� � ��������� ������
    * � ����� �������� ������������ ������ ����� ���� ���������
    */
    TElem<LISTTYPE> *slow, *fast;

    //� ������ ������� ������ (��� ���� �������)
    if ((root == NULL) || (root->next == NULL))
    {
        *list1 = root;
        *list2 = NULL;
        return;
    }
    else
    {
        /*
        ��� �������, fast �������� � 2 ���� ������� slow, �� ���� �������� slow ���������� 2 �������� fast
        �� ���� ����� ��������� �������� ������ (����� fast == NULL, slow ����� ����� � ������ ������)
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




