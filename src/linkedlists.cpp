#include <iostream>
#include <memory>

template <typename T>
class DoublyLinkedList {
private:
    struct Node;
    using NodePtr = std::unique_ptr<Node>;

    struct Node {
        T data;
        NodePtr next; 
        Node* prev;  

        Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
    };

    NodePtr head; 
    Node* tail;  

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    void push_front(const T& value) {
        auto newNode = std::make_unique<Node>(value);
        newNode->next = std::move(head); 
        newNode->prev = nullptr;
        if (newNode->next) {
            newNode->next->prev = newNode.get();
        } else {
            tail = newNode.get();
        }
        head = std::move(newNode);
    }

    void push_back(const T& value) {
        auto newNode = std::make_unique<Node>(value);
        newNode->next = nullptr;
        newNode->prev = tail;
        if (tail) {
            tail->next = std::move(newNode);
            tail = tail->next.get();
        } else {
            head = std::move(newNode);
            tail = head.get();
        }
    }

    void pop_front() {
        if (!head) return; 
        head = std::move(head->next);
        if (head)
            head->prev = nullptr;
        else
            tail = nullptr;
    }

    void pop_back() {
        if (!tail) return;
        if (tail->prev) {
            Node* newTail = tail->prev;
            newTail->next.reset(); 
            tail = newTail;
        } else {
            head.reset();
            tail = nullptr;
        }
    }

    void print() const {
        Node* current = head.get();
        while (current) {
            std::cout << current->data << " ";
            current = current->next.get();
        }
        std::cout << "\n";
    }
    std::vector<T> to_vector() const {
        std::vector<T> result;
        Node* current = head.get();
        while (current) {
            result.push_back(current->data);
            current = current->next.get();
        }
        return result;
    }
};


