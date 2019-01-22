#ifndef STR_VEC_H
#define STR_VEC_H
#include <memory>
#include <string>

class StrVec
{
public:
	StrVec():
		elements(nullptr), first_free(nullptr), cap(nullptr){}
	// �������캯��
	StrVec(const StrVec&);
	// ������ֵ�����
	StrVec &operator=(const StrVec&);
	// �ƶ����캯��
	StrVec(StrVec &&)noexcept;
	// �ƶ���ֵ�����
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
	// ��ø����ڴ沢���������ڴ�
	void reallocate();
	// ����Ԫ�ز��ͷ��ڴ�
	void free();
private:
	static std::allocator<std::string> alloc;
	// ָ��������Ԫ�ص�ָ��
	std::string *elements;
	// ָ�������һ������Ԫ�ص�ָ��
	std::string *first_free;
	// ָ������β��Ԫ�ص�ָ��
	std::string *cap;
};

#endif