#pragma once
#include <string>
#include <list>

void ReplaceAll(std::string& src, const std::string & from, const std::string & to)
{
	std::string::iterator iter = src.begin();

	while (iter != src.end())
	{
		std::string::iterator temp = iter;
		size_t fromlength = from.length();
		std::string find;
		for (int i = 0; i < fromlength && temp != src.end(); i++, temp++)
		{
			find += (*temp);
		}
		if (find == from)
		{
			src.replace(iter, temp, to);
			iter += fromlength;
			continue;
		}
		iter++;
	}
}


using intiter = std::list<int>::iterator;

namespace Chain_of_Responsibility
{
	class ChangeHandler
	{
	public:
		int hid;
		ChangeHandler(int hid)
		{
			this->hid = hid;
			Successor = nullptr;
		}
		ChangeHandler * Successor;
		virtual std::string ChangeRequest(std::list<int> mode, std::string picture) = 0;
		bool IncludeMode(std::list<int>mode)
		{
			intiter it;
			it = std::find(mode.begin(), mode.end(), hid);
			if (it == mode.end())
				return false;
			return true;
		}
	};

	class GrayChangeHandler : public ChangeHandler
	{
	public:
		GrayChangeHandler(int hid) : ChangeHandler(hid)
		{}
		std::string ChangeRequest(std::list<int> mode, std::string picture) override
		{
			if (IncludeMode(mode))
			{
				ReplaceAll(picture, "Ä®¶ó", "Èæ¹é");
			}
			if (Successor != nullptr)
			{
				picture = Successor->ChangeRequest(mode, picture);
			}	
			return picture;
		}
	};
	class RedEyeChangeHandler : public ChangeHandler
	{
	public:
		RedEyeChangeHandler(int hid) : ChangeHandler(hid)
		{}
		std::string ChangeRequest(std::list<int>mode, std::string picture) override
		{
			if (IncludeMode(mode))
			{
				ReplaceAll(picture, "»¡°£´«", "Á¤»ó´«");
			}
			if (Successor != nullptr)
			{
				picture = Successor->ChangeRequest(mode, picture);
			}
			return picture;
		}
	};
	class SoftChangeHandler : public ChangeHandler
	{
	public:
		SoftChangeHandler(int hid) : ChangeHandler(hid)
		{}
		std::string ChangeRequest(std::list<int>mode, std::string picture) override
		{
			if (IncludeMode(mode))
			{
				ReplaceAll(picture, "³¯Ä«·Î¿î", "ºÎµå·¯¿î");
			}
			if (Successor != nullptr)
			{
				picture = Successor->ChangeRequest(mode, picture);
			}
			return picture;
		}
	};
	class UIPart
	{
	public:
		ChangeHandler * head = nullptr;
		ChangeHandler * tail = nullptr;
		void AddChangeHandler(ChangeHandler * handler)
		{
			if (head != nullptr)
			{
				tail->Successor = handler;
				tail = handler;
			}
			else
			{
				head = tail = handler;
			}
		}
		std::string ChangeRequest(std::list<int> mode, std::string subject)
		{
			if (head != nullptr)
			{
				return head->ChangeRequest(mode, subject);
			}
			return subject;
		}
	};
}