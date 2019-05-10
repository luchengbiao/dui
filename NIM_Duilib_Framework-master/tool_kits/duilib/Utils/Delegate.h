#ifndef UI_UTILS_DELEGATE_H_
#define UI_UTILS_DELEGATE_H_

#pragma once

#include "Core/Define.h"

namespace ui 
{

typedef std::function<bool(ui::EventArgs*)> EventCallback;

class CEventSource : public std::vector<EventCallback>
{
public:
	CEventSource& operator += (const EventCallback& item) 
	{
		push_back(item);
		return *this;
	}

	bool operator() (ui::EventArgs* param) const 
	{
		/*
		for (auto it = this->begin(); it != this->end(); it++) { // TODO: 在回调函数中如果追加了其他回调，有迭代器被破坏的问题/
			if(!(*it)(param)) return false;
		}
		*/

		for (size_t i = 0; i < size(); ++i) {
			if (!(at(i))(param)) return false;
		}

		return true;
	}

private:
	using std::vector<EventCallback>::erase;
	using std::vector<EventCallback>::clear;
};

typedef std::map<EventType, CEventSource> EventMap;

}

#endif // UI_UTILS_DELEGATE_H_