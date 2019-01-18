#ifndef TEXT_QUERY
#define TEXT_QUERY
#include <vector>
#include <map>
#include <set>
#include <string>
#include <fstream>
#include <sstream>
#include <memory>
#include "QueryResult.h"

class QueryResult;
class TextQuery
{
public:
	typedef std::vector<std::string>::size_type line_no;
	TextQuery(std::ifstream &);
	QueryResult query(const std::string &)const;
private:
	std::shared_ptr<std::vector<std::string>> file;
	std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
};

TextQuery::TextQuery(std::ifstream &in) :file(new std::vector<std::string>)
{
	std::string text;
	while (getline(in, text))
	{
		file->push_back(text);
		int n = file->size() - 1;
		std::istringstream line(text);
		std::string word;
		while (line>>word)
		{
			auto &lines = wm[word];
			if (!lines)
				lines.reset(new std::set<line_no>);
			lines->insert(n);
		}
	}
}

QueryResult TextQuery::query(const std::string &word) const
{
	static std::shared_ptr<std::set<line_no>> nodata(new std::set<line_no>);
	auto loc = wm.find(word);
	if (loc == wm.end())
		return QueryResult(word, nodata, file);
	else
		return QueryResult(word, loc->second, file);
}
#endif