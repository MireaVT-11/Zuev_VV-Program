// ---------------------------------------------------------------------------

#ifndef QMH
#define QMH
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.ValEdit.hpp>
#include <Xml.XMLDoc.hpp>
#include <Xml.xmldom.hpp>
#include <Xml.XMLIntf.hpp>
#include <Xml.adomxmldom.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <stdlib>
#include <list>

// ---------------------------------------------------------------------------

class QC {
public:
	enum Status: int {
		Error = 0, Ready, Complete, Computing, Missing
	};

	struct ComputeElement {
		UnicodeString name;
		Status status;
		int fixation;
		int fixationT;
		long double timePeriod;
		int timeStepCount;
		long double overheadRadius;
		long double baseRadius;
		int rFECount;
		int zFECount;
		long double overheadHight;
		long double baseStrat1Hight;
		long double baseStrat2Hight;
		long double baseStrat3Hight;
		int recess;
		bool ohPoints;
		bool verticalStrats;
		int stratCount;
		int ohMaterial;
		int baseStrat1Material;
		int baseStrat2Material;
		int baseStrat3Material;
		bool sinImpact;

		bool bottomWave;
		bool bottomWaveForte;
		bool bottomContWave1;
		bool bottomContWave2;
		bool bottomContWave3;
		bool lateralSide;
		bool lateralSideForte;
		bool movingOverhead;
		bool internalWave;
		bool indentor;
		bool bottomImpact;
		bool glassful;

		long double overheadSpeed;
		long double lateralWaveSpeed;
		long double internalWaveSpeed;
		long double indentorSpeed;

		bool showHeat;
		bool beautyHeat;
		bool cinema;
		int cinemaFrameCount;
		bool grayScale;
	};

private:
	std::list<ComputeElement*> *elements;
	int nowRun;

public:
	UnicodeString name;

	QC();
	~QC();
	ComputeElement* AddItem();
	ComputeElement* GetElementByIndex(int index);
	void DeleteItem(int index);
	UnicodeString GetFormName();
	void FillList(TListView* lv);
	static UnicodeString StatusToStr(Status s);
	void SaveToFile(UnicodeString path);
	void ReadFromFile(UnicodeString path);
	void Run(TListView* list, bool hideGraph);
    int GetREI(){return nowRun;}
    static void ResetItem(TListItem* li, ComputeElement* v, int cproc = -1);
};

class TMQCForm : public TForm {
__published: // IDE-managed Components
	TListView *EList;
	TButton *AddBtn;
	TButton *DelBtn;
	TButton *EditBtn;
	TButton *DubBtn;
	TButton *LoadBtn;
	TButton *SaveBtn;
	TButton *AbNowBtn;
	TButton *AbAllBtn;
	TButton *StartBtn;
	TFileSaveDialog *FileSaveDialog;
	TFileOpenDialog *FileOpenDialog;
	TXMLDocument *XML;
	TCheckBox *HideGraphCBox;
	TButton *AddFormBtn;
	void __fastcall SaveBtnClick(TObject *Sender);
	void __fastcall AddBtnClick(TObject *Sender);
	void __fastcall EListItemChecked(TObject *Sender, TListItem *Item);
	void __fastcall LoadBtnClick(TObject *Sender);
	void __fastcall EListSelectItem(TObject *Sender, TListItem *Item, bool Selected);
	void __fastcall DubBtnClick(TObject *Sender);
	void __fastcall DelBtnClick(TObject *Sender);
	void __fastcall AbNowBtnClick(TObject *Sender);
	void __fastcall AbAllBtnClick(TObject *Sender);
	void __fastcall StartBtnClick(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall EditBtnClick(TObject *Sender);
	void __fastcall AddFormBtnClick(TObject *Sender);

private: // User declarations
	QC* computeQueue;

public: // User declarations
	__fastcall TMQCForm(TComponent* Owner);
};

// ---------------------------------------------------------------------------
extern PACKAGE TMQCForm *MQCForm;
// ---------------------------------------------------------------------------
#endif
