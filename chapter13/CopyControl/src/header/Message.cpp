#include "Message.h"

void Message::save(Folder &f)
{
	folders.insert(&f);
	f.addMsg(*this);
}

void Message::remove(Folder &f)
{
	folders.erase(&f);
	f.remMsg(*this);
}

void Message::add_to_Folders(const Message &m)
{
	for (auto f : m.folders)
		f->addMsg(*this);
}

Message::Message(const Message &m) :
	contents(m.contents), folders(m.folders)
{
	add_to_Folders(m);
}

void Message::remove_from_Folders()
{
	for (auto f : folders)
		f->remMsg(*this);
}

Message::~Message()
{
	remove_from_Folders();
}

Message &Message::operator=(const Message &rhs)
{
	remove_from_Folders();
	contents = rhs.contents;
	folders = rhs.folders;
	add_to_Folders(rhs);
	return *this;
}

void swap(Message &lhs, Message &rhs)
{
	using std::swap;
	for (auto f : lhs.folders)
		f->remMsg(lhs);
	for (auto f : rhs.folders)
		f->remMsg(rhs);
	swap(lhs.folders, rhs.folders);
	swap(lhs.contents, rhs.contents);
	for (auto f : lhs.folders)
		f->addMsg(lhs);
	for (auto f : rhs.folders)
		f->addMsg(rhs);
}

void Message::move_folders(Message &m)
{
	folders = std::move(m.folders);
	for (auto f:folders)
	{
		f->remMsg(m);
		f->addMsg(*this);
	}
	m.folders.clear(); // 确保销毁m是无害的
}

Message::Message(Message &&m):contents(std::move(m.contents))
{
	move_folders(m); // 移动folders并更新Folder指针
}

Message &Message::operator=(Message &&rhs)
{
	if (this != &rhs)
	{
		remove_from_Folders();
		contents = std::move(rhs.contents);
		move_folders(rhs);
	}
	return *this;
}