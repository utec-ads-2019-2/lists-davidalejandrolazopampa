#ifndef NODE_H
#define NODE_H

template <typename T>
struct Node {
    T data;
    Node<T>* next;
    Node<T>* prev;

    void killSelf() {
        // Así no es el killSelf, de hecho aquí no estás borrando nada
        next = nullptr;
        prev = nullptr;
        delete next;
        delete prev;
    }
};

#endif