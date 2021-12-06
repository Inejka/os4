//
// Created by DaNTe on 06.12.2021.
//

#ifndef OS4_BLOCK_H
#define OS4_BLOCK_H

#include <vector>
#include <iostream>

template<typename T>
class block {
    int size;
    std::vector<T> data;
    bool is_used = false;


public:
    block() {}

    void block_init(int size) {
        this->size = size;
        data = std::vector<T>(size);
    }

    block &operator=(block<T> const &r) {
        for (int i = 0; i < size; i++) {
            this->data[i] = r.data[i];
        }
        return *this;
    }

    std::vector<T> &get_data() {
        return this->data;
    }


    bool isUsed() const {
        return is_used;
    }

    void set_is_used(bool isUsed) {
        is_used = isUsed;
    }

    void print_data() {
        for (auto &i: data)
            std::cout << i;
    }
};


#endif //OS4_BLOCK_H
