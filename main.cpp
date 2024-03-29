#include <iostream>
#include "block.h"
#include "storage_manager.h"
#include "files.h"
#include "benchmark.h"
int main()
{
	/*block<int> test = block<int>(10);
	std::vector<int> &temp = test.get_data();
	for (int i = 0; i < 7; i++) {
		std::cout << temp[i] << std::endl;
		temp[i] = i;
	}
	block<int> test1 = block<int>(10);
	test1 = test;
	temp = test1.get_data();
	for (int i = 0; i < 7; i++) {
		std::cout << temp[i] << std::endl;
	}
	std::cout << "Hello, World!" << std::endl;*/
	std::vector<int> data = std::vector<int>(50);
	for (int i = 0; i < 50; i++)
		data[i] = i % 5;
	storage_manager test = storage_manager(10, 200);
	test.create_folder("", "f1");
	test.create_folder("f1", "f2");
	test.create_folder("f1", "f3");
	test.create_file("f1/f2", "fi1", 5);
	test.write_to_file("f1/f2", "fi1", data);
	test.print_system_with_data();
	test.create_folder("", "f2");
	test.copy_file("", "f1", "f1","test");
	test.print_system_with_data();
	/*test.create_folder("f1", "f1inf1");
	test.create_folder("f1/f1inf1", "f1inf1inf1");
	test.create_folder("f1/f1inf1", "f2inf1inf1");
	test.create_file("f1", "fi1", 5);
	test.create_file("f1", "fi2", 5);
	test.create_file("f1", "fi3", 2);
	test.create_file("f1", "fi4", 3);
	test.create_file("f1", "fi5", 4);
	test.create_file("f1", "fi6", 1);
	test.print_system_with_data();
	test.move_file("", "f1", "f2", "test");
	test.print_system_with_data();
	std::cout << test.get_total_size();*/
	/*test.remove_folder("", "f1");
	test.create_file("", "fi1", 5);
	test.write_to_file("", "fi1", data);
	test.print_system_with_data();
	std::vector<int> data1 = std::vector<int>(50);
	test.read_from_file("", "fi1", data1);
	for (int i = 0; i < 50; i++)
		std::cout << data1[i];*/
	//for (int i = 0; i<255; i++)
	//	std::cout << bench2(i, 3000) << std::endl;

	return 0;
}
