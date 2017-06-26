// ---------------------------------------------------------------------------

#include <vcl.h>
#include <stdlib>
#include <list>
#include <System.SysUtils.hpp>
#include <Vcl.ValEdit.hpp>
#include <System.StrUtils.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.ExtCtrls.hpp>
#pragma hdrstop

#include "QM.h"
#include "Main.h"
#include "MatEdit.hpp"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMQCForm *MQCForm;
// ---------------------------------------------------------------------------

void SetCEV(QC::ComputeElement* v);

QC::QC() {
	elements = new std::list<QC::ComputeElement*>();
	materials = NULL;
	name = "Новая очередь";
	nowRun = -1;
}

QC::~QC() {
	delete elements;
}

QC::ComputeElement* QC::AddItem() {
	QC::ComputeElement* v = new QC::ComputeElement();
	v->name = "Расчёт " + IntToStr((__int64)elements->size());
	v->status = QC::Status::Missing;
	elements->push_back(v);
	return v;
}

QC::ComputeElement* QC::GetElementByIndex(int index) {
	int i = 0;
	for (auto v : *elements) {
		if (index == i++)
			return v;
	}
	return NULL;
}

void QC::DeleteItem(int index) {
	int i = 0;
	for (auto v : *elements) {
		if (index == i++)
			elements->remove(v);
	}
}

UnicodeString QC::GetFormName() {
	return "Менеджер очереди расчёта: " + name;
}

void QC::ResetItem(TListItem* li, ComputeElement* v, int cproc) {
	li->Caption = v->name;
	if (li->Checked && (v->status != QC::Status::Ready))
		li->Checked = false;
	if (!li->Checked && (v->status == QC::Status::Ready))
		li->Checked = true;
	li->SubItems->Text = (QC::StatusToStr(v->status) + ((v->status == QC::Status::Computing && cproc > -1) ?
		(": " + IntToStr(cproc) + "%") : ""));
}

void QC::FillList(TListView* lv) {
	lv->Clear();
	for (auto v : *elements) {
		auto item = lv->Items->Add();
		item->Caption = v->name;
		item->SubItems->Add(StatusToStr(v->status));
		item->Checked = true;
	}
}

UnicodeString QC::StatusToStr(QC::Status s) {
	switch (s) {
	case QC::Status::Ready:
		return "В очереди";
	case QC::Status::Complete:
		return "Завершён";
	case QC::Status::Missing:
		return "Пропущен";
	case QC::Status::Error:
		return "Ошибка";
	case QC::Status::Computing:
		return "Выполнение";
	}
}

void QC::SaveToFile(UnicodeString path) {
	const UnicodeString blank = "<?xml version=\"1.0\" encoding=\"UTF-8\"?> <xbcq> </xbcq>";
	auto xml = MQCForm->XML;
	xml->Active = true;
	if (materials != NULL) {
		auto form = new TForm1((System::Classes::TComponent*)NULL);
		form->matarr.set_length(materials->Length + 1);
		for (int i = 0; i < materials->Length; ++i)
			form->matarr[i + 1] = (*materials)[i];
		form->ReinitList();
		auto mat = form->SaveToXML()->Node->ChildNodes->Nodes[(UnicodeString)"materials"]->XML;
		xml->LoadFromXML(ReplaceStr(ReplaceStr(blank, "> </", "> "+mat+" </"), "><", "> <"));
		delete form;
	}
	else
		xml->LoadFromXML(blank);
	auto tnode = xml->Node->ChildNodes->GetNode((UnicodeString)"xbcq");
	QC::ComputeElement* lel = new QC::ComputeElement();
	for (auto v : *elements) {
		auto cn = tnode->AddChild((UnicodeString)"ComputeElement");
		cn->Attributes[(UnicodeString)"name"] = v->name;
		if (v->fixation != lel->fixation)
			cn->Attributes[(UnicodeString)"fixation"] = v->fixation;
		if (v->fixationT != lel->fixationT)
			cn->Attributes[(UnicodeString)"fixationT"] = v->fixationT;
		if (v->timePeriod != lel->timePeriod)
			cn->Attributes[(UnicodeString)"timePeriod"] = FloatToStr(v->timePeriod);
		if (v->timeStepCount != lel->timeStepCount)
			cn->Attributes[(UnicodeString)"timeStepCount"] = v->timeStepCount;
		if (v->overheadRadius != lel->overheadRadius)
			cn->Attributes[(UnicodeString)"overheadRadius"] = FloatToStr(v->overheadRadius);
		if (v->baseRadius != lel->baseRadius)
			cn->Attributes[(UnicodeString)"baseRadius"] = FloatToStr(v->baseRadius);
		if (v->rFECount != lel->rFECount)
			cn->Attributes[(UnicodeString)"rFECount"] = v->rFECount;
		if (v->zFECount != lel->zFECount)
			cn->Attributes[(UnicodeString)"zFECount"] = v->zFECount;
		if (v->overheadHight != lel->overheadHight)
			cn->Attributes[(UnicodeString)"overheadHight"] = FloatToStr(v->overheadHight);
		if (v->stratCount != lel->stratCount)
			cn->Attributes[(UnicodeString)"stratCount"] = v->stratCount;
		if (v->baseStrat1Hight != lel->baseStrat1Hight)
			cn->Attributes[(UnicodeString)"baseStrat1Hight"] = FloatToStr(v->baseStrat1Hight);
		if (v->baseStrat2Hight != lel->baseStrat2Hight && v->stratCount > 1)
			cn->Attributes[(UnicodeString)"baseStrat2Hight"] = FloatToStr(v->baseStrat2Hight);
		if (v->baseStrat3Hight != lel->baseStrat3Hight && v->stratCount > 2)
			cn->Attributes[(UnicodeString)"baseStrat3Hight"] = FloatToStr(v->baseStrat3Hight);
		if (v->recess != lel->recess)
			cn->Attributes[(UnicodeString)"recess"] = v->recess;
		if (v->ohPoints != lel->ohPoints)
			cn->Attributes[(UnicodeString)"ohPoints"] = BoolToStr(v->ohPoints, true);
		if (v->verticalStrats != lel->verticalStrats)
			cn->Attributes[(UnicodeString)"verticalStrats"] = BoolToStr(v->verticalStrats, true);
		if (v->ohMaterial != lel->ohMaterial)
			cn->Attributes[(UnicodeString)"ohMaterial"] = v->ohMaterial;
		if (v->baseStrat1Material != lel->baseStrat1Material)
			cn->Attributes[(UnicodeString)"baseStrat1Material"] = v->baseStrat1Material;
		if (v->baseStrat2Material != lel->baseStrat2Material && v->stratCount > 1)
			cn->Attributes[(UnicodeString)"baseStrat2Material"] = v->baseStrat2Material;
		if (v->baseStrat3Material != lel->baseStrat3Material && v->stratCount > 2)
			cn->Attributes[(UnicodeString)"baseStrat3Material"] = v->baseStrat3Material;
		if (v->sinImpact != lel->sinImpact)
			cn->Attributes[(UnicodeString)"sinImpact"] = BoolToStr(v->sinImpact, true);
		if (v->bottomWave != lel->bottomWave)
			cn->Attributes[(UnicodeString)"bottomWave"] = BoolToStr(v->bottomWave, true);
		if (v->bottomWaveForte != lel->bottomWaveForte)
			cn->Attributes[(UnicodeString)"bottomWaveForte"] = BoolToStr(v->bottomWaveForte, true);
		if (v->bottomContWave1 != lel->bottomContWave1)
			cn->Attributes[(UnicodeString)"bottomContWave1"] = BoolToStr(v->bottomContWave1, true);
		if (v->bottomContWave2 != lel->bottomContWave2)
			cn->Attributes[(UnicodeString)"bottomContWave2"] = BoolToStr(v->bottomContWave2, true);
		if (v->bottomContWave3 != lel->bottomContWave3)
			cn->Attributes[(UnicodeString)"bottomContWave3"] = BoolToStr(v->bottomContWave3, true);
		if (v->lateralSide != lel->lateralSide)
			cn->Attributes[(UnicodeString)"lateralSide"] = BoolToStr(v->lateralSide, true);
		if (v->lateralSideForte != lel->lateralSideForte)
			cn->Attributes[(UnicodeString)"lateralSideForte"] = BoolToStr(v->lateralSideForte, true);
		if (v->movingOverhead != lel->movingOverhead)
			cn->Attributes[(UnicodeString)"movingOverhead"] = BoolToStr(v->movingOverhead, true);
		if (v->internalWave != lel->internalWave)
			cn->Attributes[(UnicodeString)"internalWave"] = BoolToStr(v->internalWave, true);
		if (v->indentor != lel->indentor)
			cn->Attributes[(UnicodeString)"indentor"] = BoolToStr(v->indentor, true);
		if (v->bottomImpact != lel->bottomImpact)
			cn->Attributes[(UnicodeString)"bottomImpact"] = BoolToStr(v->bottomImpact, true);
		if (v->glassful != lel->glassful)
			cn->Attributes[(UnicodeString)"glassful"] = BoolToStr(v->glassful, true);
		if (v->overheadSpeed != lel->overheadSpeed)
			cn->Attributes[(UnicodeString)"overheadSpeed"] = FloatToStr(v->overheadSpeed);
		if (v->lateralWaveSpeed != lel->lateralWaveSpeed)
			cn->Attributes[(UnicodeString)"lateralWaveSpeed"] = FloatToStr(v->lateralWaveSpeed);
		if (v->internalWaveSpeed != lel->internalWaveSpeed)
			cn->Attributes[(UnicodeString)"internalWaveSpeed"] = FloatToStr(v->internalWaveSpeed);
		if (v->indentorSpeed != lel->indentorSpeed)
			cn->Attributes[(UnicodeString)"indentorSpeed"] = FloatToStr(v->indentorSpeed);
		if (v->showHeat != lel->showHeat)
			cn->Attributes[(UnicodeString)"showHeat"] = BoolToStr(v->showHeat, true);
		if (v->beautyHeat != lel->beautyHeat)
			cn->Attributes[(UnicodeString)"beautyHeat"] = BoolToStr(v->beautyHeat, true);
		if (v->cinema != lel->cinema)
			cn->Attributes[(UnicodeString)"cinema"] = BoolToStr(v->cinema, true);
		if (v->cinemaFrameCount != lel->cinemaFrameCount)
			cn->Attributes[(UnicodeString)"cinemaFrameCount"] = v->cinemaFrameCount;
		if (v->grayScale != lel->grayScale)
			cn->Attributes[(UnicodeString)"grayScale"] = BoolToStr(v->grayScale, true);
		if (v->symmetry != lel->symmetry)
			cn->Attributes[(UnicodeString)"symmetry"] = BoolToStr(v->symmetry, true);
		if (v->softSymmetry != lel->softSymmetry)
			cn->Attributes[(UnicodeString)"softSymmetry"] = BoolToStr(v->softSymmetry, true);
		lel = v;
	}
	xml->SaveToFile(path);
	xml->Active = false;
}

int ReadXmlValue(UnicodeString name, _di_IXMLNode node, int def = 0) {
	if (node->HasAttribute(name))
		return StrToInt(node->Attributes[name]);
	else
		return def;
}

long double ReadXmlValue(UnicodeString name, _di_IXMLNode node, long double def = 0) {
	if (node->HasAttribute(name))
		return StrToFloat(node->Attributes[name]);
	else
		return def;
}

bool ReadXmlValue(UnicodeString name, _di_IXMLNode node, bool def = false) {
	if (node->HasAttribute(name))
		return StrToBool(node->Attributes[name]);
	else
		return def;
}

void QC::ReadFromFile(UnicodeString path) {
	auto xml = MQCForm->XML;
	xml->LoadFromFile(path);
	name = ChangeFileExt(ExtractFileName(path), "");
	xml->Active = true;
	elements->clear();
	QC::ComputeElement* lel = new QC::ComputeElement();
	auto tnode = xml->Node->ChildNodes->GetNode((UnicodeString)"xbcq");
	bool mat = false;
	for (int i = 0; i < tnode->ChildNodes->Count; ++i) {
		auto cn = tnode->ChildNodes->Nodes[i];
		if (cn->NodeName == (UnicodeString)"materials") {
			if (mat)
				throw new Exception("Несколько записей материалов в файле!");
			mat = true;
			materials = new DynamicArray<TMaterial>();
			auto form = new TForm1((System::Classes::TComponent*)NULL);
			form->ReadFromNode(cn);
			materials->set_length(form->matarr.Length - 1);
			for (int i = 1; i < form->matarr.Length; ++i)
				(*materials)[i - 1] = form->matarr[i];
			delete form;
		}
		else {
			auto v = new QC::ComputeElement();
			v->status = QC::Status::Ready;
			v->name = cn->Attributes[(UnicodeString)"name"];
			v->fixation = ReadXmlValue("fixation", cn, lel->fixation);
			v->fixationT = ReadXmlValue("fixationT", cn, lel->fixationT);
			v->timePeriod = ReadXmlValue("timePeriod", cn, lel->timePeriod);
			v->timeStepCount = ReadXmlValue("timeStepCount", cn, lel->timeStepCount);
			v->overheadRadius = ReadXmlValue("overheadRadius", cn, lel->overheadRadius);
			v->baseRadius = ReadXmlValue("baseRadius", cn, lel->baseRadius);
			v->rFECount = ReadXmlValue("rFECount", cn, lel->rFECount);
			v->zFECount = ReadXmlValue("zFECount", cn, lel->zFECount);
			v->overheadHight = ReadXmlValue("overheadHight", cn, lel->overheadHight);
			v->baseStrat1Hight = ReadXmlValue("baseStrat1Hight", cn, lel->baseStrat1Hight);
			v->baseStrat2Hight = ReadXmlValue("baseStrat2Hight", cn, lel->baseStrat2Hight);
			v->baseStrat3Hight = ReadXmlValue("baseStrat3Hight", cn, lel->baseStrat3Hight);
			v->recess = ReadXmlValue("recess", cn, lel->recess);
			v->ohPoints = ReadXmlValue("ohPoints", cn, lel->ohPoints);
			v->verticalStrats = ReadXmlValue("verticalStrats", cn, lel->verticalStrats);
			v->stratCount = ReadXmlValue("stratCount", cn, lel->stratCount);
			v->ohMaterial = ReadXmlValue("ohMaterial", cn, lel->ohMaterial);
			v->baseStrat1Material = ReadXmlValue("baseStrat1Material", cn, lel->baseStrat1Material);
			v->baseStrat2Material = ReadXmlValue("baseStrat2Material", cn, lel->baseStrat2Material);
			v->baseStrat3Material = ReadXmlValue("baseStrat3Material", cn, lel->baseStrat3Material);
			v->sinImpact = ReadXmlValue("sinImpact", cn, lel->sinImpact);
			v->bottomWave = ReadXmlValue("bottomWave", cn, lel->bottomWave);
			v->bottomWaveForte = ReadXmlValue("bottomWaveForte", cn, lel->bottomWaveForte);
			v->bottomContWave1 = ReadXmlValue("bottomContWave1", cn, lel->bottomContWave1);
			v->bottomContWave2 = ReadXmlValue("bottomContWave2", cn, lel->bottomContWave2);
			v->bottomContWave3 = ReadXmlValue("bottomContWave3", cn, lel->bottomContWave3);
			v->lateralSide = ReadXmlValue("lateralSide", cn, lel->lateralSide);
			v->lateralSideForte = ReadXmlValue("lateralSideForte", cn, lel->lateralSideForte);
			v->movingOverhead = ReadXmlValue("movingOverhead", cn, lel->movingOverhead);
			v->internalWave = ReadXmlValue("internalWave", cn, lel->internalWave);
			v->indentor = ReadXmlValue("indentor", cn, lel->indentor);
			v->bottomImpact = ReadXmlValue("bottomImpact", cn, lel->bottomImpact);
			v->glassful = ReadXmlValue("glassful", cn, lel->glassful);
			v->overheadSpeed = ReadXmlValue("overheadSpeed", cn, lel->overheadSpeed);
			v->lateralWaveSpeed = ReadXmlValue("lateralWaveSpeed", cn, lel->lateralWaveSpeed);
			v->internalWaveSpeed = ReadXmlValue("internalWaveSpeed", cn, lel->internalWaveSpeed);
			v->indentorSpeed = ReadXmlValue("indentorSpeed", cn, lel->indentorSpeed);
			v->showHeat = ReadXmlValue("showHeat", cn, lel->showHeat);
			v->beautyHeat = ReadXmlValue("beautyHeat", cn, lel->beautyHeat);
			v->cinema = ReadXmlValue("cinema", cn, lel->cinema);
			v->cinemaFrameCount = ReadXmlValue("cinemaFrameCount", cn, lel->cinemaFrameCount);
			v->grayScale = ReadXmlValue("grayScale", cn, lel->grayScale);
			v->symmetry = ReadXmlValue("symmetry", cn, lel->symmetry);
			v->softSymmetry = ReadXmlValue("softSymmetry", cn, lel->softSymmetry);
			elements->push_back(v);
			lel = v;
		}
	}
}

void SetPBVal(int v, int max) {
	MQCForm->SetPBVal(v, max);
}

void QC::Run(TListView * list, bool hideGraph) {
	int i = 0;
	auto startTime = Now();
	auto report = new TStringList();
	UnicodeString sstamp;
	report->Add("Очередь расчёта: «" + name + "»");
	report->Add("Запущено на выполнение: " + DateTimeToStr(startTime));
	DateTimeToString(sstamp, "yymmddhhnnss", startTime);
	int rcnt = 0;
	for (auto v : *elements)
		if (v->status == QC::Status::Ready)
			++rcnt;
	if(rcnt == 0) {
		MQCForm->ProgressBar->Position = MQCForm->ProgressBar->Max;
		MQCForm->ProgressBar->State = pbsError;
		return;
	}
	int cnt = 0;
	if (materials != NULL)
		mainForm->SetMaterials(materials);
    list->Items->Item[0]->MakeVisible(false);
	for (auto v : *elements) {
		UnicodeString repres = "";
		if (v->status == QC::Status::Ready) {
			auto etime = Now();
			auto elem = list->Items->Item[i];
            list->Items->Item[(i > list->Items->Count - 4)? list->Items->Count - 1: i + 3]->MakeVisible(false);
			elem->Checked = false;
			nowRun = i;
			++cnt;
			v->status = QC::Status::Computing;
			UnicodeString dtstamp, msg = "";
			DateTimeToString(dtstamp, "yymmddhhnnss", etime);
			QC::ResetItem(elem, v, 0);
			SetCEV(v);
			Application->ProcessMessages();
			bool res;
			mainForm->ResetUS();
			etime = Now();
			try {
				res = mainForm->Calculate(dtstamp, hideGraph, "#" + name + "\\series" + sstamp + "\\" +
					ReplaceStr(ReplaceStr(v->name, "/", "_"), "\\", "_") + " ", [v, elem, rcnt, cnt](int i)
				{SetPBVal((cnt - 1) * 100 + i, rcnt * 100); QC::ResetItem(elem, v, i);});
			}
			catch (Exception &e) {
				res = false;
				msg = e.Message;
			}
			catch (...) {
				res = false;
				msg = "Неизвестная ошибка";
			}
			etime = Now() - etime;
			v->status = (res) ? QC::Status::Complete : QC::Status::Error;
			QC::ResetItem(elem, v);
			UnicodeString resstr;
			DateTimeToString(resstr, ":nn:ss.zzz", etime);
			resstr = IntToStr((int)((double)etime * 24.)) + resstr;
			if (res) {
				repres = "Выполнено успешно за " + resstr;
			}
			else {
				repres = "Выполнение прервано через " + resstr + ((msg != "") ? (" с сообщением «" + msg + "»") : "");
			}
		}
		else {
			repres = "Пропущено";
		}
		report->Add((UnicodeString)"  [" + ((i < 100) ? ((i < 10) ? "  " : " ") : "") + IntToStr(i) + "|" + TimeToStr(Now()) +
			"]«" + v->name + "»");
		report->Add("      " + repres);
		++i;
	}
	report->SaveToFile(DirToResDir(mainForm->DirEdit->Text) + "#" + name + "\\series" + sstamp + "\\#report.txt");
	delete report;
	mainForm->FormCreate(NULL);
	Application->ProcessMessages();
	nowRun = -1;
}

__fastcall TMQCForm::TMQCForm(TComponent * Owner) : TForm(Owner) {
	computeQueue = new QC();
	Caption = computeQueue->GetFormName();
}

// ---------------------------------------------------------------------------
void __fastcall TMQCForm::SaveBtnClick(TObject * Sender) {
	FileSaveDialog->FileName = computeQueue->name;
	if (FileSaveDialog->Execute()) {
		computeQueue->SaveToFile(FileSaveDialog->FileName);
		computeQueue->name = ChangeFileExt(ExtractFileName(FileSaveDialog->FileName), "");
		Caption = computeQueue->GetFormName();
	}
}

// ---------------------------------------------------------------------------
void __fastcall TMQCForm::AddBtnClick(TObject * Sender) {
	QC::ResetItem(EList->Items->Add(), computeQueue->AddItem());
	EList->ItemIndex = EList->Items->Count - 1;
	EditBtn->Click();
}
// ---------------------------------------------------------------------------

void __fastcall TMQCForm::EListItemChecked(TObject * Sender, TListItem * Item) {
	auto elem = computeQueue->GetElementByIndex(Item->Index);
	if (elem == NULL)
		return;
	if (Item->Checked) {
		elem->status = QC::Status::Ready;
	}
	else {
		elem->status = QC::Status::Missing;
	}
	QC::ResetItem(Item, elem);
}

// ---------------------------------------------------------------------------
void __fastcall TMQCForm::LoadBtnClick(TObject * Sender) {
	if (FileOpenDialog->Execute()) {
		computeQueue->ReadFromFile(FileOpenDialog->FileName);
		computeQueue->FillList(EList);
		Caption = computeQueue->GetFormName();
	}
}
// ---------------------------------------------------------------------------

void __fastcall TMQCForm::EListSelectItem(TObject * Sender, TListItem * Item, bool Selected) {
	DelBtn->Enabled = Selected;
	DubBtn->Enabled = Selected;
	EditBtn->Enabled = Selected;
	FillFormBtn->Enabled = Selected;
}
// ---------------------------------------------------------------------------

void __fastcall TMQCForm::DubBtnClick(TObject * Sender) {
	auto vd = computeQueue->AddItem(), vs = computeQueue->GetElementByIndex(EList->ItemIndex);
	memcpy(vd, vs, sizeof(QC::ComputeElement));
	vd->name = vs->name; // дабы не вводить менеджер памяти в заблуждение
	QC::ResetItem(EList->Items->Add(), vd);
}
// ---------------------------------------------------------------------------

void __fastcall TMQCForm::DelBtnClick(TObject * Sender) {
	if (Application->MessageBoxW(("Удалить «" + computeQueue->GetElementByIndex(EList->ItemIndex)->name + "»?").w_str(),
		((UnicodeString)"Удаление элемента").w_str(), MB_ICONQUESTION + MB_YESNO) == mrYes) {
		computeQueue->DeleteItem(EList->ItemIndex);
		EList->DeleteSelected();
	}
}
// ---------------------------------------------------------------------------

void SetCEV(QC::ComputeElement * v) {
	mainForm->jjjjBox->ItemIndex = v->fixation;
	mainForm->tEdit->Text = IntToStr(v->fixationT);
	mainForm->dtimeprEdit->Text = FloatToStr(v->timePeriod);
	mainForm->ntEdit->Text = IntToStr(v->timeStepCount);
	mainForm->rad0Edit->Text = FloatToStr(v->overheadRadius);
	mainForm->rad1Edit->Text = FloatToStr(v->baseRadius);
	mainForm->n3Edit->Text = IntToStr(v->rFECount);
	mainForm->h0Edit->Text = FloatToStr(v->overheadHight);
	mainForm->n1Edit->Text = IntToStr(v->zFECount);
	mainForm->matstrat0Box->ItemIndex = v->ohMaterial;
	mainForm->nstratBox->ItemIndex = v->stratCount - 1;
	mainForm->h2iEdit1->Text = FloatToStr(v->baseStrat1Hight);
	mainForm->h2iEdit2->Text = FloatToStr(v->baseStrat2Hight);
	mainForm->h2iEdit3->Text = FloatToStr(v->baseStrat3Hight);
	mainForm->matstrat1Box->ItemIndex = v->baseStrat1Material;
	mainForm->matstrat2Box->ItemIndex = v->baseStrat2Material;
	mainForm->matstrat3Box->ItemIndex = v->baseStrat3Material;
	mainForm->CheckBox5->Checked = v->showHeat;
	mainForm->BeautyCBox->Checked = v->beautyHeat;
	mainForm->CheckBox3->Checked = (v->verticalStrats) ? true : false;
	mainForm->CheckBox4->Checked = (v->verticalStrats) ? false : true;
	mainForm->RadioGroup1->ItemIndex = (v->sinImpact) ? 1 : 0;
	mainForm->CheckBoxn->Checked = v->bottomWave;
	mainForm->CheckBoxns->Checked = v->bottomWaveForte;
	mainForm->CheckBoxnp1->Checked = v->bottomContWave1;
	mainForm->CheckBoxnp2->Checked = v->bottomContWave2;
	mainForm->CheckBoxnp3->Checked = v->bottomContWave3;
	mainForm->CheckBoxb->Checked = v->lateralSide;
	mainForm->CheckBoxbs->Checked = v->lateralSideForte;
	mainForm->CheckBoxs->Checked = v->movingOverhead;
	mainForm->CheckBoxinss->Checked = v->internalWave;
	mainForm->CheckBoxbsh->Checked = v->indentor;
	mainForm->BBCBox->Checked = v->bottomImpact;
	mainForm->CheckBoxStakan->Checked = v->glassful;
	mainForm->vindentEdit->Text = FloatToStr(v->overheadSpeed);
	mainForm->Editb->Text = FloatToStr(v->lateralWaveSpeed);
	mainForm->Editinss->Text = FloatToStr(v->internalWaveSpeed);
	mainForm->Editbsh->Text = FloatToStr(v->indentorSpeed);
	mainForm->CinemaCBox->Checked = v->cinema;
	mainForm->CinemaEdit->Value = v->cinemaFrameCount;
	mainForm->BWCBox->Checked = v->grayScale;
	mainForm->InputEdit1->Value = v->recess;
	mainForm->AltInpCBox->Checked = v->ohPoints;
	mainForm->SymCBox->Checked = v->symmetry;
	if(v->symmetry && v->softSymmetry){
		mainForm->SymCBox->Checked = false;
		mainForm->SoftSymCBox->Checked = true;
	}
}

void GetCEV(QC::ComputeElement * v) {
	v->fixation = mainForm->jjjjBox->ItemIndex;
	v->fixationT = StrToInt(mainForm->tEdit->Text);
	v->timePeriod = StrToFloat(mainForm->dtimeprEdit->Text);
	v->timeStepCount = StrToInt(mainForm->ntEdit->Text);
	v->overheadRadius = StrToFloat(mainForm->rad0Edit->Text);
	v->baseRadius = StrToFloat(mainForm->rad1Edit->Text);
	v->rFECount = StrToInt(mainForm->n3Edit->Text);
	v->overheadHight = StrToFloat(mainForm->h0Edit->Text);
	v->zFECount = StrToInt(mainForm->n1Edit->Text);
	v->ohMaterial = mainForm->matstrat0Box->ItemIndex;
	v->stratCount = mainForm->nstratBox->ItemIndex + 1;
	v->baseStrat1Hight = StrToFloat(mainForm->h2iEdit1->Text);
	v->baseStrat2Hight = StrToFloat(mainForm->h2iEdit2->Text);
	v->baseStrat3Hight = StrToFloat(mainForm->h2iEdit3->Text);
	v->baseStrat1Material = mainForm->matstrat1Box->ItemIndex;
	v->baseStrat2Material = mainForm->matstrat2Box->ItemIndex;
	v->baseStrat3Material = mainForm->matstrat3Box->ItemIndex;
	v->showHeat = mainForm->CheckBox5->Checked;
	v->beautyHeat = mainForm->BeautyCBox->Checked;
	v->verticalStrats = mainForm->CheckBox3->Checked;
	v->sinImpact = mainForm->RadioGroup1->ItemIndex == 1;
	v->bottomWave = mainForm->CheckBoxn->Checked;
	v->bottomWaveForte = mainForm->CheckBoxns->Checked;
	v->bottomContWave1 = mainForm->CheckBoxnp1->Checked;
	v->bottomContWave2 = mainForm->CheckBoxnp2->Checked;
	v->bottomContWave3 = mainForm->CheckBoxnp3->Checked;
	v->lateralSide = mainForm->CheckBoxb->Checked;
	v->lateralSideForte = mainForm->CheckBoxbs->Checked;
	v->movingOverhead = mainForm->CheckBoxs->Checked;
	v->internalWave = mainForm->CheckBoxinss->Checked;
	v->indentor = mainForm->CheckBoxbsh->Checked;
	v->bottomImpact = mainForm->BBCBox->Checked;
	v->glassful = mainForm->CheckBoxStakan->Checked;
	v->overheadSpeed = StrToFloat(mainForm->vindentEdit->Text);
	v->lateralWaveSpeed = StrToFloat(mainForm->Editb->Text);
	v->internalWaveSpeed = StrToFloat(mainForm->Editinss->Text);
	v->indentorSpeed = StrToFloat(mainForm->Editbsh->Text);
	v->cinema = mainForm->CinemaCBox->Checked;
	v->cinemaFrameCount = mainForm->CinemaEdit->Value;
	v->grayScale = mainForm->BWCBox->Checked;
	v->recess = mainForm->InputEdit1->Value;
	v->ohPoints = mainForm->AltInpCBox->Checked;
	v->symmetry = mainForm->SymCBox->Checked || mainForm->SoftSymCBox->Checked;
	v->softSymmetry = mainForm->SoftSymCBox->Checked;
}

void __fastcall TMQCForm::AbNowBtnClick(TObject * Sender) {
	mainForm->SetUS();
}
// ---------------------------------------------------------------------------

void __fastcall TMQCForm::AbAllBtnClick(TObject * Sender) {
	for (int i = 0; i < EList->Items->Count; ++i)
		if (EList->Items->Item[i]->Checked)
			EList->Items->Item[i]->Checked = false;
	mainForm->SetUS();
	ProgressBar->State = pbsError;
}

// ---------------------------------------------------------------------------
void __fastcall TMQCForm::StartBtnClick(TObject * Sender) {
	AddBtn->Enabled = false;
	AddFormBtn->Enabled = false;
	DelBtn->Enabled = false;
	DubBtn->Enabled = false;
	LoadBtn->Enabled = false;
	SaveBtn->Enabled = false;
	EditBtn->Enabled = false;
	FillFormBtn->Enabled = false;
	AbNowBtn->Enabled = true;
	AbAllBtn->Enabled = true;
	EList->Enabled = false;
	StartBtn->Enabled = false;
	HideGraphCBox->Enabled = false;
	ProgressBar->Position = 0;
	ProgressBar->State = pbsNormal;
	computeQueue->Run(EList, HideGraphCBox->Checked);
	AddBtn->Enabled = true;
	AddFormBtn->Enabled = true;
	LoadBtn->Enabled = true;
	SaveBtn->Enabled = true;
	AbNowBtn->Enabled = false;
	AbAllBtn->Enabled = false;
	EList->Enabled = true;
	EList->ItemIndex = -1;
	StartBtn->Enabled = true;
	HideGraphCBox->Enabled = true;
}
// ---------------------------------------------------------------------------

void __fastcall TMQCForm::FormCloseQuery(TObject * Sender, bool &CanClose) {
	CanClose = computeQueue->GetREI() == -1;
}

// ---------------------------------------------------------------------------

void __fastcall TMQCForm::EditBtnClick(TObject * Sender) {
	auto elem = computeQueue->GetElementByIndex(EList->ItemIndex);
	if (elem == NULL)
		return;

	const int icnt = 12;
	int* ival[icnt] = {
		&elem->stratCount, &elem->ohMaterial, &elem->baseStrat1Material, &elem->baseStrat2Material, &elem->baseStrat3Material,
		&elem->fixation, &elem->fixationT, &elem->rFECount, &elem->zFECount, &elem->timeStepCount, &elem->recess,
		&elem->cinemaFrameCount};
	UnicodeString iname[icnt] = {
		"Число слоёв", "Материал ударника", "Материал слоя 1", "Материал слоя 2", "Материал слоя 3", "Режим фиксации",
		"Период для режима 5", "Число разбиений по радиусу", "Число разбиений по высоте", "Число разбиений по времени",
		"Заглубление", "Число кадров анимации"};
	const int bcnt = 21;
	bool* bval[bcnt] = {
		&elem->ohPoints, &elem->sinImpact, &elem->verticalStrats, &elem->bottomWave, &elem->bottomWaveForte,
		&elem->bottomContWave1, &elem->bottomContWave2, &elem->bottomContWave3, &elem->lateralSide, &elem->lateralSideForte,
		&elem->movingOverhead, &elem->internalWave, &elem->indentor, &elem->bottomImpact, &elem->glassful, &elem->showHeat,
		&elem->beautyHeat, &elem->grayScale, &elem->cinema, &elem->symmetry, &elem->softSymmetry};
	UnicodeString bname[bcnt] = {
		"Точки в ударнике", "Синусоидальный удар", "Вертикальные слои", "Нижняя волна", "Сильная нижняя волна",
		"Пространственная нижняя волна 1", "Пространственная нижняя волна 2", "Пространственная нижняя волна 3", "Боковая волна",
		"Сильная боковая волна", "Снаряд", "Внутрення волна", "Индентор", "Нижний удар", "«Стакан»", "Показывать нагрев",
		"Сглаживание нагрева", "Чёрно-белая графика", "Записывать анимацию", "Принудительная симметрия",
		"Мягкая принудительная симметрия"};
	const int fcnt = 11;
	long double* fval[fcnt] = {
		&elem->timePeriod, &elem->baseRadius, &elem->overheadRadius, &elem->overheadHight, &elem->baseStrat1Hight,
		&elem->baseStrat2Hight, &elem->baseStrat3Hight, &elem->internalWaveSpeed, &elem->lateralWaveSpeed, &elem->overheadSpeed,
		&elem->indentorSpeed};
	UnicodeString fname[fcnt] = {
		"Временной период", "Радиус основания", "Радиус ударника", "Высота ударника", "Высота слоя 1", "Высота слоя 2",
		"Высота слоя 3", "Скорость внутренней волны", "Скорость боковой волны", "Скорость ударника", "Скорость индентора"};

	auto form = new TForm(this);
	form->Caption = "Изменить: " + elem->name;
	form->BorderStyle = bsToolWindow;
	form->ClientWidth = 400;
	form->ClientHeight = 500;
	form->Position = poOwnerFormCenter;

	auto btnOk = new TButton(form);
	btnOk->Parent = form;
	btnOk->Width = 100;
	btnOk->Height = 25;
	btnOk->Caption = "Изменить";
	btnOk->Left = 290;
	btnOk->Top = 465;
	btnOk->ModalResult = mrOk;

	auto btnCancel = new TButton(form);
	btnCancel->Parent = form;
	btnCancel->Width = 100;
	btnCancel->Height = 25;
	btnCancel->Caption = "Отмена";
	btnCancel->Left = 186;
	btnCancel->Top = 465;
	btnCancel->ModalResult = mrCancel;

	auto nameEdit = new TLabeledEdit(form);
	nameEdit->Parent = form;
	nameEdit->Width = 380;
	nameEdit->Height = 21;
	nameEdit->Left = 10;
	nameEdit->Top = 20;
	nameEdit->EditLabel->Caption = "Название";
	nameEdit->Text = elem->name;

	auto valEdit = new TValueListEditor(form);
	valEdit->Parent = form;
	valEdit->Width = 380;
	valEdit->Height = 414;
	valEdit->Top = 47;
	valEdit->Left = 10;
	valEdit->ColWidths[0] = 220;
	valEdit->TitleCaptions->Text = "Величина\r\nЗначение";

	int ei = 0;
	for (int i = 0; i < icnt; ++ei, ++i) {
		valEdit->Strings->AddPair(iname[i], IntToStr(*ival[i]));
	}
	for (int i = 0; i < bcnt; ++ei, ++i) {
		valEdit->Strings->AddPair(bname[i], BoolToStr(*bval[i], true));
		valEdit->ItemProps[ei]->PickList->Text = BoolToStr(false, true) + "\r\n" + BoolToStr(true, true);
		valEdit->ItemProps[ei]->EditStyle = esPickList;
	}
	for (int i = 0; i < fcnt; ++ei, ++i) {
		valEdit->Strings->AddPair(fname[i], FloatToStr(*fval[i]));
	}

	if (form->ShowModal() == mrOk) {
		elem->name = nameEdit->Text;
		ei = 0;
		for (int i = 0; i < icnt; ++ei, ++i) {
			*ival[i] = StrToInt(valEdit->Strings->ValueFromIndex[ei]);
		}
		for (int i = 0; i < bcnt; ++ei, ++i) {
			*bval[i] = StrToBool(valEdit->Strings->ValueFromIndex[ei]);
		}
		for (int i = 0; i < fcnt; ++ei, ++i) {
			*fval[i] = StrToFloat(valEdit->Strings->ValueFromIndex[ei]);
		}
		QC::ResetItem(EList->Selected, elem);
	}

	delete form;
}

// ---------------------------------------------------------------------------
void __fastcall TMQCForm::AddFormBtnClick(TObject * Sender) {
	auto v = computeQueue->AddItem();
	QC::ResetItem(EList->Items->Add(), v);
	EList->ItemIndex = EList->Items->Count - 1;
	GetCEV(v);
	EditBtn->Click();
}

// ---------------------------------------------------------------------------
void __fastcall TMQCForm::FillFormBtnClick(TObject *Sender) {
	auto v = computeQueue->GetElementByIndex(EList->ItemIndex);
	if (v != NULL)
		SetCEV(v);
}
// ---------------------------------------------------------------------------
