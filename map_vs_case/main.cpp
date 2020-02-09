#include <stdio.h>
#include <map>
#include <array>
#include <vector>
#include <assert.h>
#include "stopwatch.h"
using namespace std;

int _func0(int a, int b) { return a+b; }
int _func1(int a, int b) { return a-b; }
int _func2(int a, int b) { return a*b; }
int _func3(int a, int b) { return a/b; }
int _func4(int a, int b) { return a+b+1; }
int _func5(int a, int b) { return a-b+1; }
int _func6(int a, int b) { return a*b+1; }
int _func7(int a, int b) { return a/b+1; }
int _func8(int a, int b) { return a+b+2; }
int _func9(int a, int b) { return a-b+2; }

#define FUNCTION_COUNT 10

typedef int (*func_ptr)(int a, int b);

map<int, func_ptr> func_map;
vector<func_ptr> func_vector;

func_ptr func_arr[FUNCTION_COUNT] = { _func0, _func1, _func2, _func3, _func4, _func5, _func6, _func7, _func8, _func9 };

array<func_ptr, FUNCTION_COUNT> func_stdarr = { _func0, _func1, _func2, _func3, _func4, _func5, _func6, _func7, _func8, _func9 };

void create_map() {	
	func_map[0] = _func0;
	func_map[1] = _func1;
	func_map[2] = _func2;
	func_map[3] = _func3;
	func_map[4] = _func4;
	func_map[5] = _func5;
	func_map[6] = _func6;
	func_map[7] = _func7;
	func_map[8] = _func8;
	func_map[9] = _func9;
}

void create_vector() {
	func_vector.push_back(_func0);
	func_vector.push_back(_func1);
	func_vector.push_back(_func2);
	func_vector.push_back(_func3);
	func_vector.push_back(_func4);
	func_vector.push_back(_func5);
	func_vector.push_back(_func6);
	func_vector.push_back(_func7);
	func_vector.push_back(_func8);
	func_vector.push_back(_func9);
}

typedef func_ptr (*fn_test)(int index);

func_ptr test_case(int index) {
	switch(index)
	{
	case 0:	return _func0;
	case 1:	return _func1;
	case 2:	return _func2;
	case 3: return _func3;
	case 4:	return _func4;
	case 5:	return _func5;
	case 6:	return _func6;
	case 7: return _func7;
	case 8:	return _func8;
	case 9:	return _func9;
	}
	return nullptr;
}

func_ptr test_if_else(int index) {
	if(index==0)		return _func0;
	else if(index==1)	return _func1;
	else if(index==2)	return _func2;
	else if(index==3)	return _func3;
	else if(index==4)	return _func4;
	else if(index==5)	return _func5;
	else if(index==6)	return _func6;
	else if(index==7)	return _func7;
	else if(index==8)	return _func8;
	else if(index==9)	return _func9;
	return nullptr;
}

func_ptr test_map(int index) {
	return func_map[index];
}

func_ptr test_map2(int index) {
	auto it = func_map.find(index);
	if(it != func_map.end())
		return it->second;
	return nullptr;
}

func_ptr test_array(int index) {
	return func_arr[index];
}

func_ptr test_std_array(int index) {
	return func_stdarr[index];
}

func_ptr test_vector(int index) {
	return func_vector[index];
}

void do_test(const char* name, int count, fn_test test_func) {
	stopwatch sw;
	int ret = 0;
	sw.start();	
	for(int i=0; i<count; i++) {
		func_ptr f = test_func(i%FUNCTION_COUNT);
		ret = f(i+1,i);
		assert(f != nullptr);
	}
	sw.finish();
	printf("%-10s\n\tduration: %.3f ms\n", name, sw.duration()*1000);
}

int main(int argc, char** argv) {

	create_map();
	create_vector();
	
	int count = 10000000;

	if(argc >= 2)
		count = atoi(argv[1]);
	
	printf("count: %d\n", count);

	do_test("case", count, test_case);
	do_test("if-else", count, test_if_else);
	do_test("array", count, test_array);
	do_test("std::array", count, test_std_array);
	do_test("std::vector", count, test_vector);
	do_test("std::map - operator[]", count, test_map);
	do_test("std::map - find()", count, test_map2);

	return 0;
}  