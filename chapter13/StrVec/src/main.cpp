#include <iostream>
#include <string>
#include "header/StrVec.h"

// ��̬����������һ��Ҫ����
std::allocator<std::string> StrVec::alloc;
int main()
{
	StrVec vec;
	vec.push_back("QAQ");
	return 0;
}