#ifndef FOLDER_H
#define FOLDER_H
#include <set>
#include "Message.h"

class Message;
class Folder
{
public:
	void addMsg(Message &message)
	{
		msgs.insert(&message);
	}
	void remMsg(Message &message)
	{
		msgs.erase(&message);
	}
private:
	std::set<Message*> msgs;
};

#endif