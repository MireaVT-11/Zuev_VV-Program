// ---------------------------------------------------------------------------

#pragma hdrstop

#include "Saver.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)

UnicodeString GetFileName(UnicodeString name, UnicodeString style, UnicodeString id, UnicodeString path, UnicodeString exstamp,
	UnicodeString ext) {
	UnicodeString res = path;
	if (path.LastChar() != ((UnicodeString)("\\")).LastChar())
		res += "\\";
	res += name;
	if (style.Length() > 0) {
		res += "_" + style + ".";
	}
	if (id.Length() > 0) {
		res += id + ".";
	}
	res += exstamp + "." + ext;
    return res;
}

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
