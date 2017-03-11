// ---------------------------------------------------------------------------

#pragma hdrstop

#include "Saver.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)

Saver::Saver(UnicodeString fName) : ProtoSaver(fName) {
	data->Add("\"t, µs\"");
	fl = new std::list < std::function < UnicodeString() >> ();
}

Saver::~Saver() {
	delete fl;
}

void Saver::AddItem(UnicodeString name, std::function < long double() > f, std::function < UnicodeString(long double) > formater)
{
	data->Text = data->Strings[0] + ";\"" + name + "\"";
	fl->push_back([formater, f]() {return formater(f());});
}

void Saver::SaveValues(long double time) {
	UnicodeString t = FloatToStr(RoundTo(time * 1e6, -2));
	for (auto v : *fl) {
		t += ";" + v();
	}
	data->Add(t);
}

FinalSaver::FinalSaver(UnicodeString fName) : ProtoSaver(fName) {
	data->Add("");
	fl = new std::list < std::function < UnicodeString(int) >> ();
}

FinalSaver::~FinalSaver() {
	delete fl;
}

void FinalSaver::AddItem(UnicodeString name, std::function < long double(int) > f, std::function < UnicodeString(long double) >
	formater) {
	data->Text = data->Strings[0] + "\"" + name + "\";";
	fl->push_back([formater, f](int i) {return formater(f(i));});
}

void FinalSaver::SaveValues(int index) {
	UnicodeString t = "";
	for (auto v : *fl) {
		t += v(index) + ";";
	}
	data->Add(t);
}
