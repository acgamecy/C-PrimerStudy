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
	~Message();

	void save(Folder &);
	void remove(Folder &);
private:
	void add_to_Folders(const Message &);
	void remove_from_Folders();
private:
	std::string contents; // 实际消息文本
	std::set<Folder*> folders; // 包含此Message的Folder
};
void swap(Message &, Message &);
#endif