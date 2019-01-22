#include <iostream>
#include <string>
#include "StrVec.h"

void StrVec::push_back(const std::string &s)
{
	check_n_alloc();
	alloc.construct(first_free++, s);
}

std::pair<std::string *, std::string *> StrVec::alloc_n_copy
(const std::string *b, const std::string *e)
{
	auto data = alloc.allocate(e - b);
	return{ data, std::uninitialized_copy(b, e, data) };
}

void StrVec::free()
{
	if (elements)
	{
		for (auto p = first_free; p != elements;)
			alloc.destroy(--p);
		alloc.deallocate(elements, cap - elements);
		std::cout << "free" << std::endl;
	}
}

StrVec::StrVec(const StrVec &s)
{
	auto newdata = alloc_n_copy(s.begin(), s.end());
	elements = newdata.first;
	first_free = cap = newdata.second;
}

StrVec::~StrVec()
{
	free();
}

StrVec &StrVec::operator =(const StrVec &rhs)
{
	auto data = alloc_n_copy(rhs.begin(), rhs.end());
	free();
	elements = data.first;
	first_free = cap = data.second;
	return *this;
}

void StrVec::reallocate()
{
	auto newcapacity = size() ? 2 * size() : 1;
	auto newdata = alloc.allocate(newcapacity);
	auto dest = newdata;
	auto elem = elements;
	for (std::size_t i = 0; i != size(); ++i)
		alloc.construct(dest++, std::move(*elem++));
	free();
	elements = newdata;
	first_free = dest;
	cap = elements + newcapacity;
}

StrVec::StrVec(StrVec &&s)noexcept // 移动操作不应抛出任何异常
// 成员初始化器接管s中的资源
	: elements(s.elements), first_free(s.first_free), cap(s.cap)
{
	// 令s进入这样的状态——对其运行析构函数是安全的
	s.elements = s.first_free = s.cap = nullptr;
}

StrVec &StrVec::operator=(StrVec &&rhs)noexcept
{
	if (this != &rhs)
	{
		free();
		elements = rhs.elements;
		first_free = rhs.first_free;
		cap = rhs.cap;
		rhs.elements = rhs.first_free = rhs.cap = nullptr;
	}
	return *this;
}