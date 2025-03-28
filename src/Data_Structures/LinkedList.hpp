#pragma once
#include <iostream>

namespace dataStructures
{
template <typename T> class LinkedList
{
  public:
    struct Node
    {
        T value;
        Node *next;
        Node *prev;
    };

    LinkedList()
    {
        head->next = tail;
        tail->prev = head;
    }

    void add_item(T item)
    {
        Node *toAdd = new Node(item);
        Node *temp = tail->prev;
        temp->next = toAdd;
        toAdd->prev = temp;
        toAdd->next = tail;
        tail->prev = toAdd;
    }

    void print_list()
    {
        Node *printer = head->next;
        while (printer != tail)
        {
            std::cout << printer->value << " ";
        }
        std::cout << "print done!\n";
    }

  private:
    Node *head;
    Node *tail;
};
} // namespace dataStructures