//
// Created by DaNTe on 06.12.2021.
//

#ifndef OS4_FILES_H
#define OS4_FILES_H

#include <string>
#include <list>


class file {
    std::string name;

private:
    bool is_folder_data;
protected:
    file(bool is_folder_data) : is_folder_data(is_folder_data) {}

    file(bool is_folder_data, std::string name) : is_folder_data(is_folder_data), name(name) {}

public:
    const std::string &getName() const {
        return name;
    }

    void setName(const std::string &name) {
        file::name = name;
    }

    bool is_folder() const {
        return is_folder_data;
    }
};

class folder : public file {
    std::list<file *> file_list;
public:
    folder() : file(true) {}

    folder(std::string name) : file(true, name) {}

    std::list<file *> &getFileList() {
        return file_list;
    }

    void add_file(file *to_add) {
        file_list.emplace_back(to_add);
    }

    void remove_file(file *to_remove) {
        file_list.remove(to_remove);
    }
};

class normal_file : public file {
    int first_block, last_block;

private:
    int blocks_count;
public:
    normal_file(int blocks_count) : file(false), blocks_count(blocks_count) {}

    normal_file(int blocks_count, std::string name) : file(false, name), blocks_count(blocks_count) {}


    int getFirstBlock() const {
        return first_block;
    }

    void setFirstBlock(int firstBlock) {
        first_block = firstBlock;
    }

    int getLastBlock() const {
        return last_block;
    }

    void setLastBlock(int lastBlock) {
        last_block = lastBlock;
    }
};


#endif //OS4_FILES_H
