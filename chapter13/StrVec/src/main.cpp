#include <iostream>
#include <string>
#include "header/StrVec.h"

// 静态变量在类外一定要定义
std::allocator<std::string> StrVec::alloc;
int main()
{
	StrVec vec;
	vec.push_back("QAQ");
	return 0;
}