#ifndef FORWARD_H
#define FORWARD_H

#include <algorithm>
#include "list.h"
#include "node.h"
#include "iterators/forward_iterator.h"


template <typename T>
class ForwardList : public List<T> {
public:
    ForwardList() : List<T>() {}

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
        auto *temp = new Node<T>;
        temp->data = value;
        temp->next = nullptr;
        if (empty()){
            this->head = temp;
            this->tail = temp;
        } else {
            temp->next = this->head;
            this->head = temp;
            delete temp;
        }
        ++(this->nodes);
    }

    void push_back(T value) {
        auto *temp = new Node<T>;
        temp->data = value;
        temp->next = nullptr;
        if (empty()){
            this->head = temp;
            this->tail = temp;
        } else {
            this->tail->next = temp;
            this->tail = temp;
        }
        ++(this->nodes);
    }

    void pop_front() {
        if (size() == 1) {
            delete this->head;
            this->head = nullptr;
            this->tail = nullptr;
            --(this->nodes);
        }else if (!empty()){
            auto *temp = this->head;
            this->head = this->head->next;
            delete temp;
            --(this->nodes);
        } else {
            throw out_of_range("No hay nodos para eliminar");
        }

    }

    void pop_back() {
        if (!empty()) {
            if (size() == 1) {
                delete this->tail;
                this->head = nullptr;
                this->tail = nullptr;
            }else {
                auto *temp = this->head;
                while (temp->next != this->tail) {
                    temp = temp->next;
                }
                delete this->tail;
                this->tail = temp;
            }
            --(this->nodes);
        } else {
            throw out_of_range("No hay nodos para eliminar");
        }
    }

    T operator[](int index) {
        if (!empty() || index > this->nodes) {
            auto* temp = this->head;
            for (int i = 0; i < index; ++i) {
                temp = temp->next;
            }
            return temp->data;
        } else {throw out_of_range("No hay nodos en esta posición");}
    }

    bool empty() {
        return this->nodes == 0;
    }

    int size() {
        return this->nodes;
    }

    void clear() {
        while (this->head != nullptr){
            pop_front();
        }
    }


    void sort() {
        int x = 1;
        T *temparray = new T[this->nodes];
        auto* aux = this->head->next;
        temparray[0] = aux->data;
        while(aux->next != nullptr ) {
            aux = aux->next;
            temparray[x] = aux->data;
            x++;
        }
        std::sort(temparray, temparray+this->nodes);
        clear();
        x=0;
        while (x != size()) {
            push_back(temparray[x]);
            x++;
        }
    }


    void reverse() {
        auto* aux = this->head;
        this->head = this->tail;
        this->tail = aux;
        auto* temp = this->head;
        for (int i = 2; i < size(); i++) {
            for (int j = i; j < size(); j++) {
                aux = aux->next;
            }
            temp->next = aux;
            temp = temp->next;
            aux = this->tail;
        }
        temp->next = this->tail;
    }

    string name() {
        return "Forward List";
    }

    ForwardIterator<T> begin() {
        return ForwardIterator<T>(this->head);
    }

    ForwardIterator<T> end() {
        auto* nendnode = new Node<T>;
        this->tail->next = nendnode;
        return ForwardIterator<T>(nendnode);
    }

    void merge(ForwardList<T> list) {
        if(!list.empty()){
            if(empty()){
                this->head = list.head;
            }else{
                this->tail->next = list.head;
            }
            this->tail = list.tail;
        }
        this->nodes+=list.size();
    }
};

#endif