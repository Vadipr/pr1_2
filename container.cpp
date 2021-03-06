
#include "container.h"

void container::readContainer(std::ifstream &stream) {
    while(!stream.eof()) {
        transport *temp_tr = transport::readTransport(stream);
        if (temp_tr == nullptr) return; // Если не считалось, то ошибка
        element *el = new element{};
        el->t = temp_tr;
        containerAdd(el);
    }
}

void container::containerAdd(element *el) {
    size++;
    if(starting == nullptr) {
        starting = ending = el;
    } else {
        ending->forward = el;
        ending = el;
        el->forward = starting;
    }
}

container::container() {
    size = 0;
    starting = ending = nullptr;
}

void container::containerClear() {
    element *el = starting;
    for(int i = 0; i < size; i++) {
        delete el->t;
        element *next = el->forward;
        delete el;
        el = next;
    }
}

void container::outContainer(std::ofstream &stream) {
    element *el = starting;
    for(int i = 0; i < size; i++) {
        stream << i+1 << ". ";
        el->t->outTransport(stream);
        el = el ->forward;
    }
}

void container::sort() {
    element *el1 = starting;
    element *el2 = starting;
    for (int i = 0; i < size-1; i++) {
        el2 = el1->forward;
        for (int j = 0; j < size-1-i; j++) {
            if(transport::comparator(el1->t, el2->t)) {
                transport *el_temp = el1->t;
                el1->t = el2->t;
                el2->t = el_temp;
            }
            el2 = el2->forward;
        }
        el1 = el1->forward;
    }
}

int container::outContainer(std::ofstream &stream, t_type typ) {
    element *el = starting;
    int count1 = 0;
    for(int i = 0; i < size; i++) {
        if(typ != el->t->tr_type) {
            stream << i + 1 << ". ";
            count1++;
            el->t->outTransport(stream);
        }
        el = el ->forward;
    }
    return count1;
}


void container::multi(std::ofstream &ofst) {
    ofst << "_.-._.-._.-._.-MULTIMETHOD-._.-._.-._.-._" << std::endl;
    element *el1 = starting;
    int count1 = 0;
    for(int i = 0; i < size; i++) {
        element *el2 = starting;
        for(int j = 0; j < size; j++) {
            if(i == j) {
                el2 = el2->forward;
                continue;
            }
            el1->t->multi(el2->t, ofst);
            el1->t->outTransport(ofst);
            el2->t->outTransport(ofst);
            el2 = el2->forward;
        }
        el1 = el1->forward;
    }
}