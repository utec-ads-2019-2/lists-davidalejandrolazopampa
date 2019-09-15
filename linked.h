#ifndef LINKED_H
#define LINKED_H

#include "list.h"
#include "iterators/bidirectional_iterator.h"

template <typename T>
class LinkedList : public List<T> {
public:
    LinkedList() : List<T>() {}

    T front() {
        if(!empty()){
            return this->head->data;
        }
        throw out_of_range("No hay nodos para mostrar");
    }

    T back() {
        if(!empty()){
            return this->tail->data;
        }else{
            throw out_of_range("No hay nodos para mostrar");
        }
    }

    void push_front(T value) {
        auto* temp = new Node<T>;
        if (!empty()){
            this->head->prev = temp;
            temp->next = this->head;
            temp->prev = nullptr;
            this->head = temp;
        } else {
            this->head = temp;
            this->tail = temp;
        }
        temp->data = value;
        ++(this->nodes);

    }

    void push_back(T value) {
        auto* temp = new Node<T>;
        if (!empty()){
            this->tail->next = temp;
            temp->prev = this->tail;
            temp->next = nullptr;
            this->tail = temp;
        } else {
            this->head = temp;
            this->tail = temp;
        }
        temp->data = value;
        ++(this->nodes);
    }

    void pop_front() {
        if (!empty()){
            auto *temp = this->head;
            this->head = this->head->next;
            this->head->prev = nullptr;
            delete temp;
            --(this->nodes);
        } else {
            throw out_of_range("No hay nodos para eliminar");
        }
    }

    void pop_back() {
        if (!empty()){
            if (size() == 1) {
                delete this->tail;
                this->head = nullptr;
                this->tail = nullptr;
            }else {
                auto *temp = this->tail;
                this->tail = this->tail->prev;
                this->tail->next = nullptr;
                delete temp;
            }
            --(this->nodes);
        } else {
            throw out_of_range("No hay nodos para eliminar");
        }
    }

    T operator[](int index) {
        if(!empty() || index > this->nodes) {
            int half = (this->nodes) / 2;
            if (index < half) {
                int i = 0;
                auto* temp = this->head;
                while (i != index) {
                    temp = temp->next;
                    ++i;
                }
                return temp->data;
            } else {
                int i = this->nodes - 1;
                auto* temp = this->tail;
                while (i != index) {
                    temp = temp->prev;
                    --i;
                }
                return temp->data;
            }
        } else {throw out_of_range("No hay nodos en esta posición");}
    }

    bool empty() {
        return this->nodes == 0;
    }

    int size() {
        return this->nodes;
    }

    void clear() {
        while(this->head!= nullptr){
            pop_back();
        }
    }

    void sort() {
        // TODO
    }

    void reverse() {
        auto* temp = this->tail;
        this->tail = this->head;
        this->head = temp;
        this->head->next = temp->prev;

        while (temp->next != this->tail) {
            temp->next->next = temp->next->prev;
            temp->next->prev = temp;
            temp = temp->next;
        }
        this->tail->prev = temp;
        this->tail->next = nullptr;
        this->head->prev = nullptr;
    }

    string name() {
        return "Linked List";
    }

    BidirectionalIterator<T> begin() {
        return BidirectionalIterator<T>(this->head);
    }

    BidirectionalIterator<T> end() {
        auto* nendnode = new Node<T>;
        this->tail->next = nendnode;
        nendnode->prev = this->tail;
        return BidirectionalIterator<T>(nendnode);
    }

    void merge(LinkedList<T> list) {
        if(!list.empty()){
            if(empty()){
                this->head = list.head;
            }else{
                this->tail->next = list.head;
                list.head->prev = this->tail;
            }
            this->tail = list.tail;
        }
        this->nodes+=list.size();
    }
};

#endif