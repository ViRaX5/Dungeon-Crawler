// Noam Eilat : 322713025
// Amit Lachmann : 207448267

#include <stdexcept>
#include <iostream>

#pragma once
template <class T>
class List
{
public:
    typedef struct Node_s
    {
        T data;
        struct Node_s *prev;
        struct Node_s *next;
    } Node;
    Node *head;
    Node *tail;

    List(const List&) = delete;           
    List& operator=(const List&) = delete;

    List()
    {
        try
        {
            this->head = nullptr;
            this->tail = this->head;
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    ~List()
    {
        Node *curr = this->head;
        Node *temp = nullptr;
        while (curr)
        {
            temp = curr->next;
            delete curr->data;
            delete curr;
            curr = temp;
        }
        // delete temp;
    }

    Node *createNode(T data);
    void insertEnd(T data);
    void insertStart(T data);
    void insertAfterNode(T currData, T newData);
    void remove(T data);
    void deleteNode(T data);
    Node *search(T data);
    bool isEmpty();
    int size();
    void printList();
};

template <class T>
inline typename List<T>::Node *List<T>::createNode(T data)
{
    Node *newNode = new Node{data, nullptr, nullptr};
    if (!newNode)
        throw std::runtime_error("Error : Out of Memory List::createNode");

    return newNode;
}

template <class T>
inline void List<T>::insertEnd(T data)
{
    if (!head)
    {
        Node *newNode = createNode(data);
        if (newNode)
        {
            head = tail = newNode;
        }
        return;
    }
    if (!this->tail->data)
    {
        this->tail->data = data;
        return;
    }
    Node *newNode = createNode(data);
    if (newNode)
    {
        this->tail->next = newNode;
        newNode->prev = this->tail;
        this->tail = this->tail->next;
    }
}

template <class T>
inline void List<T>::insertStart(T data)
{
    if (!head)
    {
        Node *newNode = createNode(data);
        if (newNode)
        {
            head = tail = newNode;
        }
        return;
    }
    if (!this->head->data)
    {
        this->head->data = data;
        return;
    }
    Node *newNode = createNode(data);
    if (newNode)
    {
        this->head->prev = newNode;
        newNode->next = this->head;
        this->head = this->head->prev;
    }
}

template <class T>
inline void List<T>::insertAfterNode(T currData, T newData)
{
    if (!head)
    {
        Node *newNode = createNode(newData);
        if (newNode)
        {
            head = tail = newNode;
        }
        return;
    }
    Node *currNode = search(currData);
    if (!currNode)
        return;
    Node *newNode = createNode(newData);
    if (newNode)
    {
        if (currNode == this->tail)
        {
            this->tail->next = newNode;
            newNode->prev = this->tail;
            this->tail = this->tail->next;
            return;
        }
        newNode->next = currNode->next;
        currNode->next = newNode;
        newNode->prev = currNode;
        newNode->next->prev = newNode;
    }
}

template <class T>
inline void List<T>::remove(T data)
{
    if (!head->data)
    {
        return;
    }
    if (this->head == this->tail)
    {
        if (this->head->data == data)
        {
            delete head->data;
            delete this->head;
            this->head = nullptr;
            this->tail = this->head;
            return;
        }
    }
    if (this->head->data == data)
    {
        Node *temp = this->head;
        this->head = this->head->next;
        if (this->head)
            this->head->prev = nullptr;
        else
            this->tail = nullptr;

        delete temp->data;
        delete temp;
        return;

    }
    if (this->tail->data == data)
    {
        Node *temp = this->tail;
        this->tail = this->tail->prev;
        if (this->tail)
            this->tail->next = nullptr;
        else
            this->head = nullptr;

        delete temp->data;
        delete temp;
        return;

    }
    Node *curr = this->head;
    while (curr)
    {
        if (curr->data == data)
        {
            Node *temp = curr;
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;

            delete temp->data;
            delete temp;
            return;

        }
        curr = curr->next;
    }
}

template <class T>
inline void List<T>::deleteNode(T data)
{
    if (!head->data)
    {
        return;
    }
    if (this->head == this->tail)
    {
        if (this->head->data == data)
        {
            delete this->head;
            this->head = nullptr;
            this->tail = this->head;
            return;
        }
    }
    if (this->head->data == data)
    {
        Node *temp = this->head;
        this->head = this->head->next;
        if (this->head)
            this->head->prev = nullptr;
        else
            this->tail = nullptr;
        delete temp;
        return;
    }
    if (this->tail->data == data)
    {
        Node *temp = this->tail;
        this->tail = this->tail->prev;
        if (this->tail)
            this->tail->next = nullptr;
        else
            this->head = nullptr;
        delete temp;
        return;
    }
    Node *curr = this->head;
    while (curr)
    {
        if (curr->data == data)
        {
            Node *temp = curr;
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
            delete temp;
            return;
        }
        curr = curr->next;
    }
}

template <class T>
inline typename List<T>::Node *List<T>::search(T data)
{
    Node *curr = this->head;
    while (curr)
    {
        if (curr->data == data)
            return curr;
        curr = curr->next;
    }
    return nullptr;
}

template <class T>
inline bool List<T>::isEmpty()
{
    return (this->head->data) ? false : true;
}

template <class T>
inline int List<T>::size()
{
    int sizeCount = 0;
    Node *curr = this->head;
    while (curr)
    {
        sizeCount++;
        curr = curr->next;
    }
    return sizeCount;
}

template <class T>
inline void List<T>::printList()
{
    Node *curr = this->head;
    while (curr)
    {
        std::cout << *curr->data << std::endl;
        curr = curr->next;
    }
}
