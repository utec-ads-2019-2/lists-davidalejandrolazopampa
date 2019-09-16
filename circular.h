#ifndef CIRCULAR_H
#define CIRCULAR_H

#include "list.h"

template <typename T>
class CircularLinkedList : public List<T> {
public:
    CircularLinkedList() : List<T>() {}

    T front() {
        if(!empty()){
            return this->head->data;
        }
        throw out_of_range("No hay nodos para mostrar");
    }


    T back() {
        if(!empty()){
            return this->head->prev->data;
        }
        throw out_of_range("No hay nodos para mostrar");
    }

    void push_front(T value) {
        auto* temp = new Node<T>;
        if (!empty()){
            temp->prev = this->head->prev;
            this->head->prev->next = temp;
            temp->next = this->head;
            this->head->prev = temp;
            this->head = temp;
        } else {
            this->head = temp;
        }
        temp->data = value;
        ++(this->nodes);
    }

    void push_back(T value) {
        auto* temp = new Node<T>;
        if (!empty()){
            temp->prev = this->head->prev;
            this->head->prev->next = temp;
            temp->next = this->head;
            this->head->prev = temp;
        } else {
            this->head = temp;
            temp->next = temp;
            temp->prev = temp;
        }
        temp->data = value;
        ++(this->nodes);

    }

    void pop_front() {
        // No es necesario el throw en estos casos, pero no está mal
        if (!empty()){
            auto *temp = this->head;
            this->head = this->head->next;
            this->head->prev = temp->prev;
            temp->prev->next = this->head;
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
                auto *temp = this->head->prev;
                this->head->prev = temp->prev;
                temp->prev->next = this->head;
                delete temp;
            }--(this->nodes);
        } else {
            throw out_of_range("No hay nodos para eliminar");
        }
    }

    T operator[](int index) {
        // En la circular no es necearia la segunda condición (si estuviera bien)
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
                auto* temp = this->head->prev;
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
        while (this->head != nullptr){
            pop_back();
        }
        this->head = nullptr;
    }

    void sort() {
        // TODO

    }

    void reverse() {
        auto* temp = this->head->prev;
        this->head->next = temp;
        temp->next = temp->prev;
        temp->prev = this->head;

        while (temp->next != this->head) {
            temp->next->next = temp->next->prev;
            temp->next->prev = temp;
            temp = temp->next;
        }
        this->head->prev = temp;
        this->head = this->head->next;
    }

    string name() {
        return "Circular Linked List";
    }

    BidirectionalIterator<T> begin() {
        return BidirectionalIterator<T>(this->head);
    }

    BidirectionalIterator<T> end() {
        // Cómo controlas en este caso la iteración en bucle, sin do while?
        return BidirectionalIterator<T>(this->head);
    }

    void merge(CircularLinkedList<T> list) {
        if(!list.empty()){
            if(empty()){
                this->head = list.head;
            }else{
                this->tail->next = list.head;
                list.head->prev = this->tail;
            }
            this->tail = list.tail;
            this->head->prev = this->tail;
            this->tail->next = this->head;
        }
        this->nodes+=list.size();

    }
};

#endif