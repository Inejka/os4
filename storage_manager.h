//
// Created by DaNTe on 06.12.2021.
//

#ifndef OS4_STORAGE_MANAGER_H
#define OS4_STORAGE_MANAGER_H

#include "files.h"
#include "block.h"
#include <string>
#include <vector>

class storage_manager {
    int block_size, block_count;
    file *root = new folder("root");
    std::vector<block<int>> storage;

    folder *search_part(std::vector<std::string> const &paths);

    bool is_name_free(folder *fold, std::string name);

    folder *path_name_check(const std::string &path, const std::string &name);

    int find_block_to_insert(int const &size);

    void mark_blocks(int const &start, int const &end, bool const &mark);

    file *get_file(folder *to_search, std::string const &name);

    void delete_file(folder *where_to_remove, normal_file *to_delete);

    void delete_folder(folder *to_delete);

    void print_folder(folder *fold, std::string shift);

    void print_file(normal_file *file, std::string shift);

    int get_folder_size(folder *fold);

    void copy_folder(folder *from, folder *to);

    void copy_file(folder *to, normal_file *copy);

    folder *create_folder(folder *to_create, std::string const &name);

    normal_file *create_file(folder *to_create, std::string const &name, int size);

public:
    storage_manager(int blockSize, int blockCount);

    void create_folder(std::string const &path, std::string const &name);

    void create_file(std::string const &path, std::string const &name, int size);

    void remove_file(std::string const &path, std::string const &name);

    void remove_folder(std::string const &path, std::string const &name);

    void print_system_with_data();

    void write_to_file(std::string const &path, std::string const &name, std::vector<int> const &vec);

    void read_from_file(std::string const &path, std::string const &name, std::vector<int> &vec);

    void move_file(std::string const &path, std::string const &name, std::string const &new_path,
                   std::string const &new_name);

    int get_total_size();

    void copy_file(std::string const &path, std::string const &name, std::string const &copy_path,
                   std::string const &new_name);

};


#endif //OS4_STORAGE_MANAGER_H
