#ifndef MESSAGE_H
#define MESSAGE_H
#include <string>
#include <set>
#include "Folder.h"

class Message
{
	friend class Folder;
	friend void swap(Message &, Message &);
public:
	explicit Message(const std::string &str = ""):
		contents(str){}
	Message(const Message &);
	Message &operator=(const Message&);
	// �ƶ����캯��
	Message(Message &&);
	Message &operator=(Message &&);
	~Message();

	void save(Folder &);
	void remove(Folder &);
private:
	void add_to_Folders(const Message &);
	void remove_from_Folders();
	// �Ӵ�Message�ƶ�Folderָ��
	void move_folders(Message &);
private:
	std::string contents; // ʵ����Ϣ�ı�
	std::set<Folder*> folders; // ������Message��Folder
};
void swap(Message &, Message &);
#endif