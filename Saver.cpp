//---------------------------------------------------------------------------

#pragma hdrstop

#include "Saver.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

Saver::Saver(UnicodeString fName)
{
	fileName = fName;
	data = new TStringList();
	data->Add("\"t, µs\"");
	fl = new std::list<std::function<long double()>>();
}

Saver::~Saver()
{
	delete data;
	delete fl;
}

void Saver::AddItem(UnicodeString name, std::function<long double()> f)
{
	data->Text = data->Strings[0] + ";\"" + name + "\"";
	fl->push_back(f);
}

void Saver::Final()
{
	data->SaveToFile(fileName);
}

void Saver::SaveValues(long double time)
{
	UnicodeString t = FloatToStr(RoundTo(time * 1e6, -2));
	for(auto v : *fl)
	{
		t += ";" + FloatToStr(v());
	}
	data->Add(t);
}

FinalSaver::FinalSaver(UnicodeString fName)
{
	fileName = fName;
	data = new TStringList();
	data->Add("");
	fl = new std::list<std::function<long double(int)>>();
}

FinalSaver::~FinalSaver()
{
	delete data;
	delete fl;
}

void FinalSaver::AddItem(UnicodeString name, std::function<long double(int)> f)
{
	data->Text = data->Strings[0] + "\"" + name + "\";";
	fl->push_back(f);
}

void FinalSaver::Final()
{
	data->SaveToFile(fileName);
}

void FinalSaver::SaveValues(int index)
{
	UnicodeString t = "";
	for(auto v : *fl)
	{
		t += FloatToStr(v(index)) + ";";
	}
	data->Add(t);
}

