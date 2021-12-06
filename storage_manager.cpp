//
// Created by DaNTe on 06.12.2021.
//

#include "storage_manager.h"
#include <exception>


storage_manager::storage_manager(int blockSize, int blockCount) : block_size(blockSize), block_count(blockCount) {
    storage = std::vector<block<int>>(blockCount);
    for (int i = 0; i < blockCount; i++)
        storage[i].block_init(blockSize);
}

void storage_manager::create_folder(const std::string &path, const std::string &name) {
    folder *where_to_create = path_name_check(path, name);
    if (!is_name_free(where_to_create, name))
        throw std::invalid_argument("Name already taken");
    file *new_folder = new folder(name);
    where_to_create->add_file(new_folder);
}

folder *storage_manager::path_name_check(const std::string &path, const std::string &name) {
    char sep = '/';
    std::vector<std::string> paths = std::vector<std::string>();
    for (size_t p = 0, q = 0; p != path.npos; p = q)
        paths.emplace_back(path.substr(p + (p != 0), (q = path.find(sep, p + 1)) - p - (p != 0)));
    folder *where_to_create = search_part(paths);
    return where_to_create;
}


folder *storage_manager::search_part(const std::vector<std::string> &paths) {
    folder *to_return = (folder *) root;
    for (auto &i: paths) {
        if (i.empty())continue;
        bool found = false;
        for (auto &j: to_return->getFileList())
            if (j->is_folder() && j->getName() == i) {
                found = true;
                to_return = (folder *) j;
                break;
            }
        if (!found)throw std::invalid_argument("Invalid path");
    }
    return to_return;
}

bool storage_manager::is_name_free(folder *fold, std::string name) {
    for (auto &i: fold->getFileList())
        if (name == i->getName())
            return false;
    return true;
}

void storage_manager::create_file(const std::string &path, const std::string &name, int size) {
    folder *where_to_create = path_name_check(path, name);
    int first_block = find_block_to_insert(size);
    normal_file *new_file = new normal_file(size, name);
    new_file->setFirstBlock(first_block);
    new_file->setLastBlock(size + first_block);
    mark_blocks(first_block, first_block + size, true);
    where_to_create->add_file((file *) new_file);

}

int storage_manager::find_block_to_insert(const int &size) {
    for (int i = 0; i < block_count - size + 1; i++)
        if (!storage[i].isUsed()) {
            bool can_insert = true;
            for (int j = i; j < size; j++)
                can_insert = (can_insert) && (!storage[j].isUsed());
            if (can_insert)
                return i;
        }
    throw std::length_error("Not enough space to fit block");
}

void storage_manager::mark_blocks(const int &start, const int &end, const bool &mark) {
    for (int i = start; i < end; i++)
        storage[i].set_is_used(mark);
}

void storage_manager::remove_file(const std::string &path, const std::string &name) {
    folder *where_to_remove = path_name_check(path, name);
    normal_file *to_delete = (normal_file *) get_file(where_to_remove, name);
    delete_file(where_to_remove, to_delete);
}

void storage_manager::delete_file(folder *where_to_remove, normal_file *to_delete) {
    where_to_remove->remove_file(to_delete);
    mark_blocks(to_delete->getFirstBlock(), to_delete->getLastBlock(), false);
    delete to_delete;
}

file *storage_manager::get_file(folder *to_search, std::string const &name) {
    for (auto &i: to_search->getFileList())
        if (name == i->getName())
            return i;
    throw std::invalid_argument("File with this name doesn't exist");
}

void storage_manager::remove_folder(const std::string &path, const std::string &name) {
    folder *where_to_remove = path_name_check(path, name);
    folder *to_delete = (folder *) get_file(where_to_remove, name);
    where_to_remove->remove_file(to_delete);
    delete_folder(to_delete);
}

void storage_manager::delete_folder(folder *to_delete) {
    for (auto i = to_delete->getFileList().begin(); i != to_delete->getFileList().end(); i++)
        if ((*i)->is_folder()) {
            delete_folder((folder *) *i);
        } else {
            auto temp = i;
            temp++;
            delete_file((folder *) to_delete, (normal_file *) get_file(to_delete, (*i)->getName()));
            i = temp;
        }
    delete to_delete;
}

void storage_manager::print_system_with_data() {
    print_folder((folder *) root, "");
}

void storage_manager::print_folder(folder *fold, std::string shift) {
    std::cout << shift << fold->getName() << "-Folder" << std::endl;
    for (auto &i: fold->getFileList()) {
        if (i->is_folder())
            print_folder((folder *) i, shift + "   ");
        else
            print_file((normal_file *) i, shift + "   ");
    }
}

void storage_manager::print_file(normal_file *file, std::string shift) {
    std::cout << shift << file->getName() << "-File" << std::endl;
    std::cout << shift + "   ";
    for (int i = file->getFirstBlock(); i < file->getLastBlock(); i++) {
        storage[i].print_data();
    }
    std::cout << std::endl;
}

void storage_manager::write_to_file(const std::string &path, const std::string &name, const std::vector<int> &vec) {
    folder *to_find = path_name_check(path, name);
    normal_file *to_write = (normal_file *) get_file(to_find, name);
    if (to_write->is_folder())
        throw std::logic_error("You cannot write data to folder");
    if (vec.size() > (to_write->getLastBlock() - to_write->getFirstBlock()) * block_size)
        throw std::length_error("Data is longer than file");
    for (int i = 0; i < vec.size(); i++)
        storage[to_write->getFirstBlock() + i / block_size].get_data()[i % block_size] = vec[i];
}

void storage_manager::read_from_file(const std::string &path, const std::string &name, std::vector<int> &vec) {
    folder *to_find = path_name_check(path, name);
    normal_file *to_write = (normal_file *) get_file(to_find, name);
    if (to_write->is_folder())
        throw std::logic_error("You cannot read data to folder");
    for (int i = to_write->getFirstBlock(); i < to_write->getLastBlock(); i++)
        for (int j = 0; j < block_size; j++)
            vec[(i - to_write->getFirstBlock()) * block_size + j] = storage[i].get_data()[j];
}

void storage_manager::move_file(const std::string &path, const std::string &name, const std::string &new_path,
                                const std::string &new_name) {
    if (new_path.find(path+"/"+name) != std::string::npos)
        throw std::invalid_argument("Invalid new path");
    folder *old_location = path_name_check(path, name);
    file *to_move = get_file(old_location, name);
    old_location->remove_file(to_move);
    folder *new_location = path_name_check(new_path, name);
    to_move->setName(new_name);
    new_location->add_file(to_move);
}
