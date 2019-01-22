#ifndef STR_VEC_H
#define STR_VEC_H
#include <memory>
#include <string>

class StrVec
{
public:
	StrVec():
		elements(nullptr), first_free(nullptr), cap(nullptr){}
	// 拷贝构造函数
	StrVec(const StrVec&);
	// 拷贝赋值运算符
	StrVec &operator=(const StrVec&);
	// 移动构造函数
	StrVec(StrVec &&)noexcept;
	// 移动赋值运算符
	StrVec &operator=(StrVec &&)noexcept;
	~StrVec();

	void push_back(const std::string &);
	std::size_t size() const{ return first_free - elements; }
	std::size_t capacity() const{ return cap - elements; }
	std::string *begin() const{ return elements; }
	std::string *end()const{ return first_free; }
private:
	void check_n_alloc()
	{
		if (size() == capacity())
			reallocate();
	}
	std::pair<std::string *, std::string *> alloc_n_copy
		(const std::string *, const std::string *);
	// 获得更多内存并拷贝已有内存
	void reallocate();
	// 销毁元素并释放内存
	void free();
private:
	static std::allocator<std::string> alloc;
	// 指向数组首元素的指针
	std::string *elements;
	// 指向数组第一个空闲元素的指针
	std::string *first_free;
	// 指向数组尾后元素的指针
	std::string *cap;
};

#endif