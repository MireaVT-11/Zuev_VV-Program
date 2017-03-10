#ifndef SaverH
#define SaverH

#include <System.Classes.hpp>
#include <System.Generics.Collections.hpp>
#include <functional>
#include <stdlib>
#include <list>
#include <System.Math.hpp>

class Saver
{
	private:
		UnicodeString fileName;
		TStringList *data;
		std::list<std::function<long double()>> *fl;
	public:
		Saver(UnicodeString fName);
		~Saver();
		void AddItem(UnicodeString name, std::function<long double()> f);
		void SaveValues(long double time);
		void Final();
};

#endif
