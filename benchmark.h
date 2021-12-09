//
// Created by DaNTe on 07.12.2021.
//

#ifndef OS4_BENCHMARK_H
#define OS4_BENCHMARK_H

#include <ctime>
#include <iostream>
#include <vector>
#include "storage_manager.h"

time_t bench1(int times, int size)
{
	storage_manager test = storage_manager(4, 2000);
	clock_t start = clock();
	for (int i = 0; i<times; i++) {
		auto temp = std::string();
		temp += (char)i;
		test.create_file("", temp, size);
	}
	clock_t end = clock();
	return end-start;
}

time_t bench2(int times, int size)
{
	storage_manager test = storage_manager(20, 2000);
	test.create_file("", "test", size/20);
	std::vector<int> vec(size);
	clock_t start = clock();
	for (int i = 0; i<times; i++) {
		test.write_to_file("", "test", vec);
	}
	clock_t end = clock();
	return end-start;
}

#endif //OS4_BENCHMARK_H