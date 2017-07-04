#pragma hdrstop

#include <cmath>
#include <algorithm>
#include <cassert>

#include <System.Threading.hpp>
#include <System.SyncObjs.hpp>
#include <System.Math.hpp>
#include <System.Classes.hpp>
#include <Vcl.Imaging.pngimage.hpp>

#include "Main.h"
#include "Matedit.hpp"
#include "Extendedutils.hpp"
#include "Saver.h"
#include "QM.h"

#pragma package(smart_init)
#pragma resource "*.dfm"

#ifndef DEBUG
  #define UseParallel
#endif DEBUG

using namespace std;

TmainForm *mainForm;
// ---------------------------------------------------------------------------
const int nus = 32000;
const int nel = 32000;
const int nn = 32000;

// меняем память на производительность
long double Gs[nel];
long double sigma0s[nel];
long double ro0s[nel];
long double ks[nel];
long double alphas[nel];
long double k1s[nel];
long double as[nel];
long double aks[nel];
long double sigma1s[nel];
bool crashed[nel];

// температура
#define Cels2Kelvin(x) (x+273.15)
long double T[nel];
long double T_old[nel];
long double T0 = Cels2Kelvin(20);
long double T_max = Cels2Kelvin(700);
long double T_rec = T0;
long double T_plast[nel];
long double T_elast[nel];
long double T_in[nel];
long double T_m[nel];
#undef Cels2Kelvin

long double amaselm[nel];
long double amasstop[nus];
long double rcent[nel];
long double constm[6][9];
long double radius0;
long double radius1;
long double H1;
long double sizepic;
long double alf;
long double sqI2p[nel];
long double m_sqI2p = 0;
long double dr0;
long double dz0;
long double dr1;
long double dr;
long double dz;
long double h0;
long double h2i[4];
long double dz2[4];
long double vindent;
long double dens0[9];
long double n1;
long double n2;
long double n3;
long double n4;
long double n2i[4];
long double dtime;
long double rcoord[nus];
long double zcoord[nus];
long double rcoord1[nus];
long double zcoord1[nus];
long double speedr[nus];
long double speedz[nus];
long double speedr1[nus];
long double speedz1[nus];
long double dens[nel];
long double v0[nel];
long double tet[nel];
long double tetp[nel];
long double tete[nel];
long double I2p[nel];
long double Y2[nel];
long double F[nel];
long double p[nel];
long double psi[nel];
long double psidot[nel];
long double square[nel];
long double square1[nel];
long double srr[nel];
long double szz[nel];
long double srz[nel];
long double stt[nel];
long double epsrr[nel];
long double epszz[nel];
long double epsrz[nel];
long double epstt[nel];
long double epsrrp[nel];
long double epszzp[nel];
long double epsrzp[nel];
long double epsttp[nel];
long double sigmarr[nel];
long double sigmazz[nel];
long double sigmarz[nel];
long double sigmatt[nel];
long double q1;
long double tfinish;
long double sin2omega;
long double cos2omega;
long double timepr;
long double ka;
long double dtimepr;
long double minh;
long double Heps;
long double maxsum;
long double GPa = 1.e9; // А-а-а-а!!!!
long double alpha;
long double speedsound;
long double v;
long double vk;
long double r1;
long double r2;
long double r3;
long double z1;
long double z2;
long double z3;
long double u1;
long double u2;
long double u3;
long double v1;
long double v2;
long double v3;
long double G;
long double ak;
long double rctk;
long double cl;
long double ca;
long double c0;
long double vdif;
long double tim;
long double q;
long double dt;
long double sigma0;
long double sigma1;
long double epsdotrr;
long double epsdotzz;
long double epsdotrz;
long double epsdottt;
long double epsdotrrp;
long double epsdotzzp;
long double epsdotrzp;
long double epsdotttp;
long double temp0;
long double ener[nel];
long double k1;

int CPointTarget[nn];
int numb[nel][9][3];
int matelm[nel];
int itop[4][nel];
int CElemTarget[nn];
int SPointTarget[nn];
int SElemTarget[nn];
int BPointTarget[nn];
int BElemTarget[nn];
int TPointTarget[nn];
int TElemTarget[nn];
int CPointImpactor[nn];
int CElemImpactor[nn];
int SPointImpactor[nn];
int SElemImpactor[nn];
int BPointImpactor[nn];
int numberelem;
int BElemImpactor[nn];
int TPointImpactor[nn];
int TElemImpactor[nn];
int numbertop;
int matstrat[4]; // материалы основания
int matstrat0; // материал сооружения
int nstrat;
int nearel[nus];
int jjjj;
int H;
int n;
int t;
int nt;
int it1;
int it2;
int it3;
// int MatCount = 9;
int UElemIndex;

// bool NoAnim = false;
bool UnlimStop = false;

int nforgraf = 0;

DynamicArray<TMaterial> Material;

long double step;
long double aa[30][30];
long double C[30];
long double S[60];
long double tt[30];

int N;
int m;

// ----------------------------------------------------------------------
void draw();
void sizeofelement();
void pointelem();
void topology();
void topcoord();
void masses();
void threeangle(int k);
void newspeed();
void NewMat();
void WriteToFile(FILE *file, FILE *file1, FILE *file2, FILE *file3);
void GraficRefresh(int n);

struct MyPoint {
	long double x;
	long double y;
};

MyPoint points[11][24][9][100];
int *Colorletch;

long double vb;
long double vs;
long double vb2;
long double vn2;
long double inss;
long double bsh;

int tns;
int tnc;
int tns2;
int tnc2;
int tbs;
int tbc;
int tbs2;
int tbc2;

int *massn1;
int *massn2;
int *massb1;
int *massb2;

long double WidthCoef;
long double HeightCoef;
long double HeightCoef1;
long double WidthCoef1;
long double HeightCoef2;
long double WidthCoef2;

int point1 = 0, point2 = 0, point3 = 0;

long double BigI2pValue = 1.0;
bool BigI2p = false;

// ---------------------------------------------------------------------------
__fastcall TmainForm::TmainForm(TComponent* Owner) : TForm(Owner) {
}
// ---------------------------------------------------------------------------

void SaveAsPNG(TBitmap* bmp, UnicodeString name) {
	static auto pngi = new Vcl::Imaging::Pngimage::TPngImage();
	pngi->Assign(bmp);
	pngi->SaveToFile(name);
	// delete pngi;
}

UnicodeString DirToResDir(UnicodeString path) {
	if (path.LastChar() != ((UnicodeString)("\\")).LastChar())
		return path + "\\#Results\\";
	return path + "#Results\\";
}

void __fastcall TmainForm::InitLoop(TObject *, int k) {
	F[k] = Material[matelm[k]].sigma0;
	// long double a = square[k];
	// if( a == 0 ) a = 0.00001;
	v0[k] = 2. * M_PI * /* a */ square[k] * rcent[k];
	epsrrp[k] = 0.;
	epszzp[k] = 0.;
	epsrzp[k] = 0.;
	epsttp[k] = 0.;
	sqI2p[k] = 0.;
	tet[k] = 0.;
	T[k] = T_old[k] = T_plast[k] = T_elast[k] = T_m[k] = T0;
	T_in[k] = 0.;
	crashed[k] = false;
}

#define _varalpha(t, maa, mia, mint, maxt) ((mia)+((maa)-(mia))/(1.0+exp((-20.0/((maxt)-(mint)))*((t)-((maxt)+(mint))/2.0))))
#define _dvaralpha(t, maa, mia, mint, maxt) (20.0*((mia)-(maa))*exp(-20.0*((t)-((mint)+(maxt))/2.0)/((mint)-(maxt)))/(((mint)-(maxt))*(exp(-20.0*((t)-((mint)+(maxt))/2.0)/((mint)-(maxt)))+1)*(exp(-20.0*((t)-((mint)+(maxt))/2.0)/((mint)-(maxt)))+1)))

void __fastcall TmainForm::BaseLoop(TObject *, int k) {
	Gs[k] = Material[matelm[k]].G;
	ks[k] = Material[matelm[k]].k;
	long double alphadot = 0; // содержит производную от alpha по времени
	if (Material[matelm[k]].VarAlpha.Enabled) {
		// ВНИМАНИЕ! «varalpha» — это макрос!
		alphadot = alphas[k];
		alphas[k] = _varalpha(T_m[k], Material[matelm[k]].alpha, Material[matelm[k]].VarAlpha.MinAlpha,
			Material[matelm[k]].VarAlpha.MinT, Material[matelm[k]].VarAlpha.MaxT);
		alphadot = alphas[k] - alphadot;
		// Здесь вводится зависимость разупрочнения от температуры:
		// до MinT разупрочнение ≈MinAlpha, после чего начинает изменяться и
		// при температуре MaxT почти достигает своего номинального значения.
	}
	else
		alphas[k] = Material[matelm[k]].alpha;
	sigma0s[k] = Material[matelm[k]].sigma0;
	sigma1s[k] = Material[matelm[k]].sigma1;
	ro0s[k] = Material[matelm[k]].ro0;
	k1s[k] = Material[matelm[k]].k1;
	as[k] = abs(square[k]);
	if (IsZero(as[k]))
		as[k] = 0.00001;
	aks[k] = square1[k];
	long double lmb = ks[k] - 2 / 3 * Gs[k];
	long double mu = Gs[k];
	long double ctep = Material[matelm[k]].ctep;
	long double gammatep = Material[matelm[k]].gammatep;
	long double v = 2. * M_PI * as[k] * rcent[k];
	long double vk = 2. * M_PI * aks[k] * (rcoord1[itop[1][k]] + rcoord1[itop[2][k]] + rcoord1[itop[3][k]]) / 3.;
	long double vdif = 2. * (v - vk) / ((v + vk) * dtime);
	long double z1 = 0.5 * (zcoord[itop[1][k]] + zcoord1[itop[1][k]]);
	long double z2 = 0.5 * (zcoord[itop[2][k]] + zcoord1[itop[2][k]]);
	long double z3 = 0.5 * (zcoord[itop[3][k]] + zcoord1[itop[3][k]]);
	long double r1 = 0.5 * (rcoord[itop[1][k]] + rcoord1[itop[1][k]]);
	long double r2 = 0.5 * (rcoord[itop[2][k]] + rcoord1[itop[2][k]]);
	long double r3 = 0.5 * (rcoord[itop[3][k]] + rcoord1[itop[3][k]]);
	long double u1 = speedr[itop[1][k]];
	long double u2 = speedr[itop[2][k]];
	long double u3 = speedr[itop[3][k]];
	long double v1 = speedz[itop[1][k]];
	long double v2 = speedz[itop[2][k]];
	long double v3 = speedz[itop[3][k]];

	long double dTptime = -gammatep * (T_in[k]) / dtime;
	// попытка посчитать температурные деформации
	T_old[k] += T_in[k];
	T_in[k] = 0.0;

	// КОМПОНЕНТЫ ТЕНЗОРА СКОРОСТЕЙ ДЕФОРМАЦИЙ
	long double epsdotrr = ((z2 - z3) * u1 + (z3 - z1) * u2 + (z1 - z2) * u3) / (as[k] + aks[k]) + dTptime; // ;
	long double epsdotrz = ((r3 - r2) * u1 + (r1 - r3) * u2 + (r2 - r1) * u3 + (z2 - z3) * v1 + (z3 - z1) * v2 +
		(z1 - z2) * v3) / (2. * (as[k] + aks[k])) + dTptime; // ;
	long double epsdotzz = ((r3 - r2) * v1 + (r1 - r3) * v2 + (r2 - r1) * v3) / (as[k] + aks[k]) + dTptime; // ;
	long double epsdottt = -epsdotrr - epsdotzz + vdif; // + dTptime;

	// КОМПОНЕНТЫ ТЕНЗОРА ПОЛНЫХ ДЕФОРМАЦИЙ
	long double depsrr;
	long double depsrz;
	long double depszz;
	long double depstt;
	epsrr[k] += depsrr = epsdotrr * dtime;
	epsrz[k] += depsrz = epsdotrz * dtime;
	epszz[k] += depszz = epsdotzz * dtime;
	epstt[k] += depstt = epsdottt * dtime;

	// КОМПОНЕНТЫ ДЕВИАТОРА ТЕНЗОРА НАПРЯЖЕНИЙ
	srr[k] += 2. * Gs[k] * dtime * (epsdotrr - vdif / 3.);
	szz[k] += 2. * Gs[k] * dtime * (epsdotzz - vdif / 3.);
	srz[k] += Gs[k] * dtime * epsdotrz;
	stt[k] = -srr[k] - szz[k];

	// КОМПОНЕНТЫ ДЕВИАТОРА ТЕНЗОРА НАПРЯЖЕНИЙ С УЧЁТОМ ПОВОРОТА
	long double sin2omega = dtime / (as[k] + aks[k]) * ((z2 - z3) * v1 + (z3 - z1) * v2 + (z1 - z2) * v3 - (r3 - r2) * u1 -
		(r1 - r3) * u2 - (r2 - r1) * u3);
	long double cos2omega = sqrtl(powl(1 - sin2omega, 2));
	long double srrt = 0.5 * (srr[k] + szz[k]) + 0.5 * (srr[k] - szz[k]) * cos2omega - srz[k] * sin2omega;
	long double szzt = 0.5 * (srr[k] + szz[k]) - 0.5 * (srr[k] - szz[k]) * cos2omega + srz[k] * sin2omega;
	long double srzt = srz[k] * cos2omega + 0.5 * (srr[k] - szz[k]) * sin2omega;
	srr[k] = srrt;
	szz[k] = szzt;
	srz[k] = srzt;

	/*
	 частные производные функции F по компонентам тензора пластических
	 деформаций и по давлению
	 dfdp = k1s[k];
	 dfdepsrrp = -k1s[k] * ks[k] - alphas[k] * (0.2e1 / 0.3e1 * epsrrp[k] - epszzp[k] / 0.3e1 - epsttp[k] / 0.3e1);
	 dfdepszzp = -k1s[k] * ks[k] - alphas[k] * (0.2e1 / 0.3e1 * epszzp[k] - epsrrp[k] / 0.3e1 - epsttp[k] / 0.3e1);
	 dfdepsttp = -k1s[k] * ks[k] - alphas[k] * (0.2e1 / 0.3e1 * epsttp[k] - epsrrp[k] / 0.3e1 - epszzp[k] / 0.3e1);
	 dfdepsrzp = -2 * alphas[k] * epsrzp[k];
	 */

	// ФУНКЦИЯ УПРОЧНЕНИЯ С УЧЁТОМ ПАДАЮЩЕЙ ДИАГРАММЫ
	if (IsZero(F[k]))
		F[k] = 0.000001; // потому что так надо // (2015 year) Хорошо. Верим.
	long double Heps = 2. * Gs[k];
	if (sigma1s[k] < alf * p[k] + sigma0s[k] - alphas[k] * I2p[k]) {
		Heps = 2. * Gs[k] + ks[k] * powl(k1s[k], 2) - k1s[k] * k1s[k] / ks[k] -
			alphas[k] / F[k] * (srr[k] * (epsrrp[k] - epsttp[k]) + szz[k] * (epszzp[k] - epsttp[k]) +
			2. * srz[k] * epsrzp[k]);
	}

	// то что было в новой версии
	/*
	 Heps = 2.*Gs[k]-alphas[k]/F[k]*(srr[k]*
	 (epsrrp[k]-epsttp[k])+szz[k]*
	 (epszzp[k]-epsttp[k])+2.*srz[k]*epsrzp[k]);
	 */
	// в 2008 версии
	/*
	 Heps[k] = 2.e0*Gs[k] + ks[k]*Power(dfdp,2) -
	 dfdp/3*(dfdepsrrp + dfdepszzp + dfdepsttp)+
	 1/F[k]*(srr[k]*(dfdepsrrp-dfdepsttp) +
	 szz[k]*(dfdepszzp-dfdepsttp) + 2*srz[k]*dfdepsrzp);
	 */

	// ФУНКЦИЯ ДЕФОРМИРОВАНИЯ
	psi[k] = sqrtl(2. * (powl(srr[k], 2.) + powl(szz[k], 2.) + powl(srz[k], 2.) + srr[k] * szz[k])) - F[k];

	// ПРОИЗВОДНАЯ ФУНКЦИИ ДЕФОРМИРОВАНИЯ ПО ВРЕМЕНИ
	// (2015 год) За такое надо руки отрывать!
	// (2017 год) Поддерживаю предыдущего оратора.
	psidot[k] = 2.e0 * Gs[k] / F[k] * (srr[k] * (epsdotrr - epsdottt) + szz[k] * (epsdotzz - epsdottt) +
		2.e0 * srz[k] * epsdotrz) - ks[k] * alf * k1s[k] * (epsdotrr + epsdotzz + epsdottt);

	// (2017 год) По уверениям Зуева, к psidot нужно добавить производную от alpha по температуре.
	// Ниже: d(alpha)/dT*dT/dt, если alpha не константа.
	if (Material[matelm[k]].VarAlpha.Enabled) {
		// ВНИМАНИЕ! «dvaralpha» — это макрос!
		psidot[k] += _dvaralpha(T_m[k], Material[matelm[k]].alpha, Material[matelm[k]].VarAlpha.MinAlpha,
			Material[matelm[k]].VarAlpha.MinT, Material[matelm[k]].VarAlpha.MaxT) * (T[k] - T_old[k]) / dtime;
	}

	// то что было в новой версии
	/*
	 psidot[k] = 2.e0* Gs[k]/F[k]*(srr[k]*(epsdotrr-epsdottt)+szz[k]*
	 (epsdotzz-epsdottt)+2.e0*srz[k]*epsdotrz)-ks[k]*alf*
	 (epsdotrr+epsdotzz+epsdottt);
	 */

	// ПЕРЕКЛЮЧАТЕЛЬ УПРУГОСТЬ/ПЛАСТИЧНОСТЬ
	int H = (psi[k] >= 0.) && (psidot[k] > 0.);
	/* if (psi[k]>=0.&&psidot[k]>0.)
	 H=1;
	 else
	 H=0; */

	// КОМПОНЕНТЫ ТЕНЗОРА СКОРОСТЕЙ ПЛАСТИЧЕСКИХ ДЕФОРМАЦИЙ
	long double epsdotrrp = H * psidot[k] / Heps * (srr[k] / F[k] - alf * (3. * ks[k] - k1s[k] * Gs[k]) / (3. * Gs[k]));
	long double epsdotzzp = H * psidot[k] / Heps * (szz[k] / F[k] - alf * (3. * ks[k] - k1s[k] * Gs[k]) / (3. * Gs[k]));
	long double epsdotttp = H * psidot[k] / Heps * (stt[k] / F[k] - alf * (3. * ks[k] - k1s[k] * Gs[k]) / (3. * Gs[k]));
	long double epsdotrzp = H * psidot[k] / Heps * (srz[k] / F[k]);
	/*
	 epsdotrrp=H*psidot[k]/Heps*(srr[k]/F[k]-alf*(3.*ks[k]-Gs[k])/(3.*Gs[k]));
	 epsdotzzp=H*psidot[k]/Heps*(szz[k]/F[k]-alf*(3.*ks[k]-Gs[k])/(3.*Gs[k]));
	 epsdotttp=H*psidot[k]/Heps*(stt[k]/F[k]-alf*(3.*ks[k]-Gs[k])/(3.*Gs[k]));
	 epsdotrzp=H*psidot[k]/Heps*(srz[k]/F[k]);
	 */
	/*
	 epsdotrrp=H*psidot[k]/Heps[k]*(srr[k]/F[k]-dfdp/3.);
	 epsdotzzp=H*psidot[k]/Heps[k]*(szz[k]/F[k]-dfdp/3.);
	 epsdotttp=H*psidot[k]/Heps[k]*(stt[k]/F[k]-dfdp/3.);
	 epsdotrzp=H*psidot[k]/Heps[k]*(srz[k]/F[k]);
	 */

	// КОМПОНЕНТЫ ТЕНЗОРА ПЛАСТИЧЕСКИХ ДЕФОРМАЦИЙ
	epsrrp[k] += epsdotrrp * dtime;
	epszzp[k] += epsdotzzp * dtime;
	epsrzp[k] += epsdotrzp * dtime;
	epsttp[k] += epsdotttp * dtime;

	// ПОЛНАЯ ОБЪЁМНАЯ ДЕФОРМАЦИЯ
	tet[k] = epsrr[k] + epszz[k] + epstt[k];

	// ПЛАСТИЧЕСКАЯ ОБЪЁМНАЯ ДЕФОРМАЦИЯ
	tetp[k] += -H * psidot[k] * k1s[k] * dtime / Heps;
	// tetp[k]=epsrrp[k]+epszzp[k]+epsttp[k];
	if (IsZero(alf))
		tetp[k] = 0.;

	// УПРУГАЯ ОБЪЁМНАЯ ДЕФОРМАЦИЯ
	tete[k] = tet[k] - tetp[k];
	// УЧЁТ ПСЕВДОВЯЗКОСТИ
	long double speedsound = sqrtl((ks[k] + 4. / 3. * Gs[k]) / ro0s[k]);
	long double q = 0;
	if (vdif < 0.) {
		q = powl(c0, 2) * ro0s[k] * (as[k] + aks[k]) / (v + vk) * powl(vdif, 2) + cl * speedsound * ro0s[k] * sqrtl
			(0.5 * (as[k] + aks[k])) * abs(vdif) / (0.5 * (v + vk));
	}
	long double q1 = ca * speedsound * ro0s[k] * (as[k] + aks[k]) / (v + vk);

	// ГИДРОСТАТИЧЕСКОЕ ДАВЛЕНИЕ
	p[k] = -ks[k] * tete[k];

	// КОМПОНЕНТЫ ТЕНЗОРА НАПРЯЖЕНИЙ С УЧЁТОМ ПСЕВДОВЯЗКОСТИ
	sigmarr[k] = -(p[k] + q) + (srr[k] + 2. * q1 * (epsdotrr - vdif / 3.));
	sigmazz[k] = -(p[k] + q) + (szz[k] + 2. * q1 * (epsdotzz - vdif / 3.));
	sigmatt[k] = -sigmarr[k] - sigmazz[k] - 3. * (p[k] + q);
	sigmarz[k] = srz[k] + q1 * epsdotrz;

	// ИНТЕНСИВНОСТЬ ПЛАСТИЧЕСКИХ ДЕФОРМАЦИЙ
	/* I2p[k] = 0.5 *
	 (
	 powl(epsrrp[k], 2) + powl(epszzp[k], 2) +
	 powl(tetp[k] - epsrrp[k] - epszzp[k], 2) +
	 2. * powl(epsrzp[k], 2) -
	 tetp[k] * tetp[k] / 3.
	 ); */
	/* I2p[k] = 0.5*(powl(epsrrp[k], 2) + powl(epszzp[k], 2) + 2*powl(epsrzp[k], 2) + powl(epsrrp[k]+epszzp[k], 2));
	 */
	I2p[k] = 0.5 * (powl(epsrrp[k] - tetp[k] / 3., 2) + powl(epszzp[k] - tetp[k] / 3., 2) + 2 * powl(epsrzp[k], 2));
	// Версия 2015 - надо писать так!
	// (2015 год) Ололололо!!!
	sqI2p[k] = sqrtl(I2p[k]);
	if (sqI2p[k] > BigI2pValue)
		BigI2p = true;

	// if(m_sqI2p<sqI2p[k]) {m_sqI2p = sqI2p[k];}

	// ЭНЕРГИЯ
	ener[k] = ener[k] + rcent[k] * dtime * (sigmarr[k] * ((z1 - z2) * u3 + (z2 - z3) * u1 + (z3 - z1) * u2) +
		sigmazz[k] * ((r2 - r1) * v3 + (r1 - r3) * v2 + (r3 - r2) * v1) + sigmarz[k] * ((r2 - r1) * u3 + (r1 - r3) * u2 +
		(r3 - r2) * u1 + (z1 - z2) * v3 + (z2 - z3) * v1 + (z3 - z1) * v2) +
		// (2015 год) А мне нравится 3.e0. В этом числе есть глубокая загадочность
		sigmatt[k] * square[k] * (u1 + u2 + u3) / (3.e0 * rcent[k])) / amaselm[k];

	// ПЕРЕМЕННЫЙ ПРЕДЕЛ ТЕКУЧЕСТИ (ФУНКЦИЯ F) С УЧЁТОМ ПАДАЮЩЕЙ ДИАГРАММЫ
	F[k] = k1s[k] * alf * p[k] + sigma0s[k] - alphas[k] * I2p[k];
	if (alphas[k] > 0 && F[k] < sigma1s[k]) {
		crashed[k] = true;
		F[k] = sigma1s[k];
	}
	if(alphas[k] < 0) {
		if ((sigma1s[k] > sigma0s[k] + 1) && F[k] > sigma1s[k]) {
			crashed[k] = true;
			F[k] = sigma1s[k];
		}
	}

	// F[k]=max(sigma1s[k], alf*p[k]+sigma0s[k]-alphas[k]*I2p[k]);
	// F[k]=k1s[k]*p[k]+sigma0s[k]-alphas[k]*I2p[k];

	// 2-Й ИНВАРИАНТ ДЕВИАТОРА ТЕНЗОРА НАПРЯЖЕНИЙ
	Y2[k] = powl(srr[k], 2.) + powl(szz[k], 2.) + powl(srz[k], 2.) + srr[k] * szz[k];

	// КОМПОНЕНТЫ ДЕВИАТОРА ТЕНЗОРА НАПРЯЖЕНИЙ С УЧЁТОМ ПЛАСТИЧНОСТИ
	if (psi[k] >= 0.) {
		srr[k] = srr[k] * F[k] / sqrtl(2. * Y2[k]);
		szz[k] = szz[k] * F[k] / sqrtl(2. * Y2[k]);
		srz[k] = srz[k] * F[k] / sqrtl(2. * Y2[k]);
	}

	// ТЕМПЕРАТУРА by Ales'hon'ne
	long double Told = T_old[k];
	// long double eee = epsrr[k]+epszz[k]+/*epsrz[k]*/+epstt[k];
	// T_old[k] = T[k];
	// T_plast[k] = (2*T0*G*H*(srr[k]*epsrr[k]+szz[k]*epszz[k]+srz[k]*epsrz[k]+stt[k]*epstt[k]))/
	// (ro0s[k]*ctep*Told*Heps);
	// T_elast[k] = (T0*(3*lmb+2*mu)*gammatep*(eee))/(ctep*ro0s[k]);
	// T[k] = 2.L*(T_plast[k]-T_elast[k])+T0;
	long double eee = depsrr + depszz + /* epsrz[k] */ +depstt;
	T_old[k] = T[k];
	long double Tplast = (2. * T0 * G * H * (srr[k] * depsrr + szz[k] * depszz + srz[k] * depsrz + stt[k] * depstt)) /
		(ro0s[k] * ctep * Told * Heps);
	T_plast[k] += Tplast;
	long double Telast = -(T0 * (3. * lmb + 2. * mu) * gammatep * (eee)) / (ctep * ro0s[k]);
	T_elast[k] += Telast;
	T[k] = (Tplast + Telast) + Told;
	if (T[k] > T_m[k])
		T_m[k] = T[k];
	if (T[k] > T_rec)
		T_rec = T[k];
	if (T_rec >= T_max)
		T_max += 10.0;
}

#undef _varalpha
#undef _dvaralpha

// Нужно для заглубления ударника. Проверяет, будет ли элемент мишени с номером k заменён элементом ударника
bool test_k(int k) {
	if (k > 2 * n2 * n4)
		return true;
	for (int i = 0; i < mainForm->InputEdit1->Value; ++i) {
		if (k > 2 * (n2 - i - 1) * n4 && k <= 2 * (n2 - i) * n4 - 2 * (n4 - n3))
			return true;
	}
	return false;
}

bool __fastcall TmainForm::Calculate(UnicodeString dtstamp, bool hideGraph, UnicodeString subfolder,
	std::function < void(int) > percentCallBack) {
	Application->ProcessMessages();
	graphForm->Canvas->Brush->Color = clWhite;
	graphForm->Canvas->FillRect(Rect(0, 0, graphForm->ClientWidth, graphForm->ClientHeight));
	GPa = 1.e9;
	// *****************************************************************
	// ЗАДАНИЕ НАЧАЛЬНЫХ ДАННЫХ (Считывание информации с формы)
	GetBeginValue();
	// ****************************************
	step = nt / 10.;
	BigI2p = false;
	// if (!NoAnim) {
	graphForm->Canvas->Brush->Color = clWhite;
	graphForm->Canvas->FillRect(Rect(0, 0, graphForm->ClientWidth, graphForm->ClientHeight));

	if (CheckBox1->Checked) {
		// graphForm->ClientWidth = Screen->Width;
		// graphForm->ClientHeight = Screen->Height;
		graphForm->BorderStyle = bsNone;
		graphForm->WindowState = wsMaximized;
		assert(graphForm->ClientWidth != Screen->Width);
	}
	if (CheckBox4->Checked) {
		HeightCoef2 = h0 + h2i[1] + h2i[2] + h2i[3];
		WidthCoef2 = max(radius1, radius0);
	}
	if (CheckBox3->Checked) {
		HeightCoef2 = radius1 + h0;
		WidthCoef2 = 0.7 * max(h2i[1] + h2i[2] + h2i[3], radius0);
	}

	int width = graphForm->ClientWidth;
	int height = graphForm->ClientHeight;

	graphForm->Left = 0;
	graphForm->Top = 0;
	graphForm->Canvas->Pen->Color = clBlack;
	graphForm->Visible = !hideGraph;

	WidthCoef1 = 0.;
	HeightCoef1 = height - 40; // width=640, height=480
	HeightCoef = 0.85 * height / HeightCoef2;
	WidthCoef = 0.85 * width / WidthCoef2;
	// }

	// *****************************************************************
	sizeofelement(); // n2,dr0,dr1,dz0,dz2(i),numbertop,numberelem
	pointelem(); // C/S/B/T,Point/Elem,Target/Impactor
	topology(); // matelm,itop,nearel,numb
	topcoord(); // rcoord,zcoord,sizepic
	squareall(); // rcent,square
	masses(); // amaselm,amasstop
	int zcl = InputEdit1->Value;
	if (CBoxPoints->Checked) {
		// точки в ударнике
		point1 = 2 * (n2 - zcl) * n4 + 2;
		point2 = 2 * (n2 - zcl + 1) * n4 - 2 * (n4 - n3);
		point3 = 2 * (n2) * n4 - 2 * (n4 - n3);
	}
	else {
		// точки в мишени
		point1 = 2 * (n2 - zcl - 1) * n4 + 2;
		point2 = 2 * (n2 - zcl) * n4 - 2 * (n4 - n3 - 1);
		point3 = 2 * (n2) * n4 - 2 * (n4 - n3 - 1);
	}
	auto centralPoints = new int[(int)(n1 + n2 + 1)];
	centralPoints[0] = 1;
	for (int i = 1; i <= n1 + n2 + 1; ++i) {
		if (i <= n2 + 1)
			centralPoints[i] = centralPoints[i - 1] + (n4 + 1);
		else
			centralPoints[i] = centralPoints[i - 1] + (n3 + 1);
		if (rcoord[centralPoints[i]] > 1.e-5)
			throw new Exception("Ошибочная топология; обратитесь к разработчику");
	}
	// *****************************************************************
	// Массив для удаления эффекта "залечивания"
	Colorletch = new int[numberelem];
	for (int f = 0; f < numberelem; f++)
		Colorletch[f] = 1;
	// *****************************************************************
	// Массивы состояния для нескольких волн
	if (CheckBoxn2->Checked) {
		massn1 = new int[1 + nt];
		massn2 = new int[1 + nt];
		for (int i = 0; i <= nt; i++) {
			if ((i <= tns) || (i >= tnc))
				massn1[i] = 0;
			else
				massn1[i] = i;
		}
		for (int i = 0; i <= nt; i++) {
			if ((i <= tns2) || (i >= tnc2))
				massn2[i] = 0;
			else
				massn2[i] = i;
		}
	}
	if (CheckBoxno2->Checked) {
		// (2015 год) ЗДЕСЬ ВОЗМОЖНО ЕСТЬ ОШИБКА!!!
		massn1 = new int[1 + nt];
		massn2 = new int[1 + nt];
		for (int i = 0; i <= nt; i++) {
			if (i >= tnc)
				massn1[i] = 0;
			else
				massn1[i] = i;
		}
		for (int i = 0; i <= nt; i++) {
			if (i >= tnc2)
				massn2[i] = 0;
			else
				massn2[i] = i;
		}
	}
	if (CheckBoxb2->Checked) {
		// (2015 год) ИЛИ ЗДЕСЬ ОШИБКА???
		massb1 = new int[1 + nt];
		massb2 = new int[1 + nt];
		for (int i = 0; i <= nt; i++) {
			if ((i <= tbs) || (i >= tbc))
				massb1[i] = 0;
			else
				massb1[i] = i;
		}
		for (int i = 0; i <= nt; i++) {
			if ((i <= tbs2) || (i >= tbc2))
				massb2[i] = 0;
			else
				massb2[i] = i;
		}
	}
	// *****************************************************************
	// ЗАДАНИЕ НАЧАЛЬНОЙ СКОРОСТИ СОУДАРЕНИЯ
	if (CheckBoxs->Checked) // Движение снаряда
	{
		if (!AltInpCBox->Checked)
			zcl = 0;
		for (int i = (n2 - zcl) * (n4 + 1) + 1; i <= (n2 - zcl) * (n4 + 1) + n3 + 1; i++) {
			speedz[i] = -0.5 * vindent; // сохранение симметрии
		}
		// speedz[i] = vs;
		for (int i = (n2 + 1) * (n4 + 1) + 1; i <= numbertop; i++) {
			speedz[i] = -vindent;
		}
		for (int c = 0; c < zcl - 1; ++c) {
			for (int i = (n2 - c) * (n4 + 1) + 1; i <= (n2 - c) * (n4 + 1) + n3; ++i)
				speedz[i] = -vindent;
			speedz[(int)((n2 - c) * (n4 + 1) + n3 + 1)] = -0.5 * vindent;
		}
	}
	if (CheckBoxn->Checked) // Нижняя волна
		for (int i = 1; i <= n4 + 1; i++)
			// speedz[i] = vindent;
				speedz[i] = 0.;
	if (CheckBoxns->Checked) // Сильная нижняя волна
		for (int i = 1; i <= n4 + 1; i++)
			speedz[i] = vindent;
	if (CheckBoxb->Checked) // Боковая волна
	{
		for (int i = 1; i <= n4 + 1; i++)
			speedz[i] = 0.;
		// for (int i=1; i<=numbertop; i++)
		for (int i = n4 + 1; i <= (n4 + 1) * (n2 + 1); i += n4 + 1)
			// if (rcoord[i]==radius1)
			// speedr[i]=-vb;
				speedr[i] = 0.;
	}
	if (CheckBoxbs->Checked) // Сильная боковая волна
	{
		for (int i = 1; i <= n4 + 1; i++)
			speedz[i] = 0.;
		// for (int i=1; i<=numbertop; i++)
		// if (rcoord[i]==radius1)
		for (int i = n4 + 1; i <= (n4 + 1) * (n2 + 1); i += n4 + 1)
			speedr[i] = -vb;
	}
	if (CheckBoxn2->Checked) // 2 нижних волны
		for (int i = 1; i <= n4 + 1; i++)
			speedz[i] = 0.;
	if (CheckBoxno2->Checked) // 2 нижних одновременных волны
		for (int i = 1; i <= n4 + 1; i++)
			speedz[i] = 0.;
	if (CheckBoxnp1->Checked) // Нижняя пространствення волна 1
		for (int i = 1; i <= n4 + 1; i++)
			speedz[i] = abs(vindent * sin(M_PI_2 - M_PI_2 * i / (n4 + 1)));
	if (CheckBoxnp2->Checked) // Нижняя пространствення волна 2
		for (int i = 1; i <= n4 + 1; i++)
			speedz[i] = abs(vindent * sin(M_PI_2 * i / (n4 + 1)));
	if (CheckBoxnp3->Checked) // Нижняя пространствення волна 3
		for (int i = 1; i <= n4 + 1; i++)
			speedz[i] = abs(vindent * sin(M_PI_2 * i / (n4 + 1)));
	if (CheckBoxb2->Checked) // 2 боковых волны
	{
		for (int i = 1; i <= n4 + 1; i++)
			speedz[i] = 0.;
		for (int i = 1; i <= numbertop; i++)
			if (SameValue(rcoord[i], radius1))
				speedr[i] = 0.;
	}

	// Внутренняя волна
	if (CheckBoxinss->Checked) {
		// Ступенчатый удар в начальный момент времени
		if (RadioGroup1->ItemIndex == 0) {
			for (int i = 1; i <= n4 + 1; i++)
				speedz[i] = 0.;
			for (int i = h2i[1] / (h0 / n1) + 1; i <= (n4) * (n2 + 1); i += n4 + 1)
				speedr[i] = inss;
			for (int i = (n4 + 1) * (n2) + 1; i <= (n4 + 1) * (n2) + h2i[1] / (h0 / n1); i++)
				// int i=(n4+1)*(n2);
					speedz[i] = inss;
		}
		// Синусоидальный удар в начальный момент времени
		if (RadioGroup1->ItemIndex == 1) {
			for (int i = 1; i <= n4 + 1; i++)
				speedz[i] = 0;
			for (int i = h2i[1] / (h0 / n1) + 1; i <= (n4) * (n2 + 1); i += n4 + 1)
				speedr[i] = 0;
			for (int i = (n4 + 1) * (n2 + 1) + 1; i <= (n4 + 1) * (n2 + 1) + h2i[1] / (h0 / n1); i++)
				speedz[i] = 0;
		}
	}
	if (CheckBoxbsh->Checked) // Индентор
	{
		if (RadioGroup1->ItemIndex == 0) // Ступенчатый
		{
			// for (int i=1; i<=numbertop; i++)
			for (int i = (n2 + 1) * (n4 + 1) + (n1) * (n3); i <= (n2 + 1) * (n4 + 1) + (n1) * (n3 + 1); i++)
				// (n2+1)*(n4+1)+(n1+1)*n3
				// int i=(n2+1)*(n4+1)+(n1)*(n3+1);
				// if (zcoord[i]==h0+h2i[1])
					speedz[i] = -bsh;
			for (int i = 1; i <= n4 + 1; i++) {
				speedr[i] = 0.;
				speedz[i] = 0.;
			}
		}
		if (RadioGroup1->ItemIndex == 1) // Синусоидальный
			// for (int i=1; i<=numbertop; i++)
			// if (zcoord[i]==h0+h2i[1])
			for (int i = (n2 + 1) * (n4 + 1) + (n1) * (n3); i <= (n2 + 1) * (n4 + 1) + (n1) * (n3 + 1); i++)
				speedz[i] = 0.;
	}
	if (BBCBox->Checked) // Нижний удар
	{
		if (RadioGroup1->ItemIndex == 0) {
			for (int i = 1; i <= n4 + 1; ++i) {
				speedz[i] = bsh;
			}
		}
	}
	if (UnlimStop) {
		throw new Exception("Прервано пользователем");
	}
	// *****************************************************************
	tim = 0;

#ifdef UseParallel
	TParallel::For(NULL, 1, numberelem, InitLoop);
#else
	for (int k = 1; k <= numberelem; k++)
		InitLoop(Sender, k);
#endif
	bool cinemaEnabled = CinemaCBox->Checked;
	UnicodeString path, exstamp;
	int dirnmb = 0;
	do {
		path = DirToResDir(DirEdit->Text) + subfolder + (exstamp = (dtstamp + IntToStr(dirnmb++))) + "\\";
	}
	while (Sysutils::DirectoryExists(path));

	if (!Sysutils::DirectoryExists(DirToResDir(DirEdit->Text)))
		MkDir(DirToResDir(DirEdit->Text));
	ForceDirectories(path);
	if (cinemaEnabled)
		MkDir(path + "Cinema\\");

SavingStartInformation: {
		auto BaseInfo = new TStringList();
		BaseInfo->Add("Время      = " + GetScPref(dtimepr*nt, 5, "с"));
		BaseInfo->Add("Материал 0 = " + Material[matstrat0Box->ItemIndex].ToString());
		BaseInfo->Add("Материал 1 = " + Material[matstrat1Box->ItemIndex].ToString());
		if (matstrat2Box->Enabled)
			BaseInfo->Add("Материал 2 = " + Material[matstrat2Box->ItemIndex].ToString());
		if (matstrat3Box->Enabled)
			BaseInfo->Add("Материал 3 = " + Material[matstrat3Box->ItemIndex].ToString());
		if (CheckBoxs->Checked)
			BaseInfo->Add("V_снар.    = " + vindentEdit->Text + " м/с");
		if (CheckBoxbsh->Checked)
			BaseInfo->Add("V_инд.     = " + Editbsh->Text + " м/с");
		BaseInfo->Add("Размер уд. = " + rad0Edit->Text + "x" + h0Edit->Text + " (м)");
		BaseInfo->Add("Размер м.  = " + rad1Edit->Text + "x(" + h2iEdit1->Text + "+" + h2iEdit2->Text + "+" +
			h2iEdit3->Text + ") (м)");
		BaseInfo->SaveToFile(GetFileName("#", "", "", path, exstamp, "txt"));

		delete BaseInfo;
	}

	int minpp[nel];
	long double tcrd = max(zcoord[itop[1][TElemTarget[1]]], max(zcoord[itop[2][TElemTarget[1]]],
		zcoord[itop[3][TElemTarget[1]]])) / 0.001;
	for (int i = 1; i <= 2 * (int)n4; ++i) {
		minpp[i] = -1;
	}

	// Сохранение данных, вариант 4, теперь с ООП и лямбдами!
	// Недоделанный, правда.

	Saver *sT = new Saver(GetFileName("T", "all", "", path, exstamp));
	for (int i = 1; i <= n4; ++i) {
		sT->AddItem(FloatToStr((double)((int)((double)(i - 1) / (double)(n4 - 1) * 1000.0) / 10.0)) + "%", [i]()
		{return RoundTo((T[TElemTarget[i]] + T[TElemTarget[i] - 1]) / 2., -2);});
	}

	Saver *sData1 = new Saver(GetFileName("data", "all", "point1", path, exstamp));
	sData1->AddItem("epsrr", []() {return epsrr[point1];});
	sData1->AddItem("epszz", []() {return epszz[point1];});
	sData1->AddItem("epsrz", []() {return epsrz[point1];});
	sData1->AddItem("epstt", []() {return epstt[point1];});
	sData1->AddItem("epsrrp", []() {return epsrrp[point1];});
	sData1->AddItem("epszzp", []() {return epszzp[point1];});
	sData1->AddItem("epsrzp", []() {return epsrzp[point1];});
	sData1->AddItem("epsttp", []() {return epsttp[point1];});
	sData1->AddItem("sigmarr", []() {return sigmarr[point1];});
	sData1->AddItem("sigmazz", []() {return sigmazz[point1];});
	sData1->AddItem("sigmarz", []() {return sigmarz[point1];});
	sData1->AddItem("sigmatt", []() {return sigmatt[point1];});
	sData1->AddItem("tet", []() {return tet[point1];});
	sData1->AddItem("p", []() {return p[point1];});
	sData1->AddItem("Y2", []() {return Y2[point1];});
	sData1->AddItem("sqI2p", []() {return sqI2p[point1];});
	sData1->AddItem("T, K", []() {return (T[point1] + T[point1 + ((point1 % 2) ? 1 : -1)]) / 2.0;});
	sData1->AddItem("R, mm", []()
	{return (rcoord[itop[1][point1]] + rcoord[itop[2][point1]] + rcoord[itop[3][point1]]) / 0.003;});
	sData1->AddItem("Z, mm", []()
	{return (zcoord[itop[1][point1]] + zcoord[itop[2][point1]] + zcoord[itop[3][point1]]) / 0.003;});

	Saver *sData2 = new Saver(GetFileName("data", "all", "point2", path, exstamp));
	sData2->AddItem("epsrr", []() {return epsrr[point2];});
	sData2->AddItem("epszz", []() {return epszz[point2];});
	sData2->AddItem("epsrz", []() {return epsrz[point2];});
	sData2->AddItem("epstt", []() {return epstt[point2];});
	sData2->AddItem("epsrrp", []() {return epsrrp[point2];});
	sData2->AddItem("epszzp", []() {return epszzp[point2];});
	sData2->AddItem("epsrzp", []() {return epsrzp[point2];});
	sData2->AddItem("epsttp", []() {return epsttp[point2];});
	sData2->AddItem("sigmarr", []() {return sigmarr[point2];});
	sData2->AddItem("sigmazz", []() {return sigmazz[point2];});
	sData2->AddItem("sigmarz", []() {return sigmarz[point2];});
	sData2->AddItem("sigmatt", []() {return sigmatt[point2];});
	sData2->AddItem("tet", []() {return tet[point2];});
	sData2->AddItem("p", []() {return p[point2];});
	sData2->AddItem("Y2", []() {return Y2[point2];});
	sData2->AddItem("sqI2p", []() {return sqI2p[point2];});
	sData2->AddItem("T, K", []() {return (T[point2] + T[point2 + ((point2 % 2) ? 1 : -1)]) / 2.0;});
	sData2->AddItem("R, mm", []()
	{return (rcoord[itop[1][point2]] + rcoord[itop[2][point2]] + rcoord[itop[3][point2]]) / 0.003;});
	sData2->AddItem("Z, mm", []()
	{return (zcoord[itop[1][point2]] + zcoord[itop[2][point2]] + zcoord[itop[3][point2]]) / 0.003;});

	Saver *sData3 = new Saver(GetFileName("data", "all", "point3", path, exstamp));
	sData3->AddItem("epsrr", []() {return epsrr[point3];});
	sData3->AddItem("epszz", []() {return epszz[point3];});
	sData3->AddItem("epsrz", []() {return epsrz[point3];});
	sData3->AddItem("epstt", []() {return epstt[point3];});
	sData3->AddItem("epsrrp", []() {return epsrrp[point3];});
	sData3->AddItem("epszzp", []() {return epszzp[point3];});
	sData3->AddItem("epsrzp", []() {return epsrzp[point3];});
	sData3->AddItem("epsttp", []() {return epsttp[point3];});
	sData3->AddItem("sigmarr", []() {return sigmarr[point3];});
	sData3->AddItem("sigmazz", []() {return sigmazz[point3];});
	sData3->AddItem("sigmarz", []() {return sigmarz[point3];});
	sData3->AddItem("sigmatt", []() {return sigmatt[point3];});
	sData3->AddItem("tet", []() {return tet[point3];});
	sData3->AddItem("p", []() {return p[point3];});
	sData3->AddItem("Y2", []() {return Y2[point3];});
	sData3->AddItem("sqI2p", []() {return sqI2p[point3];});
	sData3->AddItem("T, K", []() {return (T[point3] + T[point3 + ((point3 % 2) ? 1 : -1)]) / 2.0;});
	sData3->AddItem("R, mm", []()
	{return (rcoord[itop[1][point3]] + rcoord[itop[2][point3]] + rcoord[itop[3][point3]]) / 0.003;});
	sData3->AddItem("Z, mm", []()
	{return (zcoord[itop[1][point3]] + zcoord[itop[2][point3]] + zcoord[itop[3][point3]]) / 0.003;});

	T_rec = T0;
	dtime = dtimepr;
	tfinish = nt * dtimepr;
	// if (!NoAnim)
	threegraphs(true, 0, false, path);
	for (auto n = 0; n <= nt; n++) {
		timepr = n * dtimepr;
		int ctec = 0;
		// Application->ProcessMessages(); // (2015 год) О господь!!!  //Уехало пониже.
		if (tim + 2. * dtime > timepr && tim + dtime < timepr)
			dtime = 0.51 * (timepr - tim);
		while (tim < timepr) {
		L1:
			++ctec;
			if (ctec > 300) {
				throw new Exception("Решение, скорее всего, расходится. Выявлено на шаге " + IntToStr(n));
			}
			if (UnlimStop) {
				throw new Exception("Прервано пользователем");
			}
			if (BigI2p) {
				throw new Exception("Интенсивность пластической деформации превысила предел. Выявлено на шаге " +
					IntToStr(n));
			}
			Application->ProcessMessages();
			newspeed(); // speedr1,speedz1
			// ************************************************************
			// УСЛОВИЯ ЗАКРЕПЛЕНИЯ
			for (int i = 0; i < n1 + n2 + 1; i++) {
				speedr1[centralPoints[i]] = 0.; // симметрия, нам всем нужна симметрия
				speedr[centralPoints[i]] = 0.;
				if (SymCBox->Checked && !SoftSymCBox->Checked) // совсем симметрия
				{
					// скорости центрального узла устанвливаются равными соседним для избежания артефактов
					speedz[centralPoints[i]] = speedz[centralPoints[i] + 1];
					speedz1[centralPoints[i]] = speedz1[centralPoints[i] + 1];
				}
				if (SymCBox->Checked && SoftSymCBox->Checked) // мягкая симметрия
				{
					// скорости центрального узла меньше влияют на него
					speedz[centralPoints[i]] = 0.8 * speedz[centralPoints[i] + 1] + 0.2 * speedz[centralPoints[i]];
					speedz1[centralPoints[i]] = 0.8 * speedz1[centralPoints[i] + 1] + 0.2 * speedz1[centralPoints[i]];
				}
			}
			if (jjjj != 1)
				for (int i = 1; i <= numbertop; i++) {
					switch (jjjj) {
					case 2: // жёсткое закрепление дна (тыльной стороны)
						if (zcoord[i] == 0.) {
							speedr1[i] = 0.;
							speedz1[i] = 0.;
						}
						break;
					case 3: // жёсткое закрепление боковой стороны мишени
						if (rcoord[i] == radius1) {
							speedr1[i] = 0.;
							speedz1[i] = 0.;
						}
						break;
					case 4: // закрепление "стакан"(боковой и тыльной сторон)
						if (rcoord[i] == radius1 || zcoord[i] == 0.) {
							speedr1[i] = 0.;
							speedz1[i] = 0.;
						}
						break;
					case 5: // закрепление ударника по оси r (жёсткий ударник)
						if (i > (n2 + 1)*(n4 + 1))
							speedr1[i] = 0.;
						break;
					case 6:
						// случай со сваей
						// t - период пилообразного графика
						// скорости на тыльной стороне ударника
						for (int k = n2 * (n4 + 1) + 1; k <= n2 * (n4 + 1) + n3 + 1; k++)
							if (sin(6. * n / t + 1.) > 0.)
								speedz1[k] = -0.5 * vindent;
							else
								speedz1[k] = 0.;
						break;
					case 7: // закрепление центра (центр не двигается по оси r):
						if (IsZero(rcoord[i], 1.e-10L))
							speedr1[i] = 0.;
						break;
					default:
						throw(" Ищите switch ");
					}
				}
			// *************************************************************
			for (int i = 1; i <= numbertop; i++) {
				rcoord1[i] = rcoord[i];
				rcoord[i] += dtime * speedr1[i];
				zcoord1[i] = zcoord[i];
				zcoord[i] += dtime * speedz1[i];
			}
			for (int k = 1; k <= numberelem; k++)
				square1[k] = square[k];
			squareall();
			dt = 1.e10;
			int it1, it2, it3;
			long double a;
			long double ro0;
			for (int k = 1; k <= numberelem; k++) {
				it1 = itop[1][k];
				it2 = itop[2][k];
				it3 = itop[3][k];
				G = Material[matelm[k]].G;
				ka = Material[matelm[k]].k;
				ro0 = Material[matelm[k]].ro0;
				a = square[k];
				// if (a==0) a=0.00001; // Отладка не забыть!
				long double sum[3];
				sum[0] = powl(zcoord[it3] - zcoord[it1], 2) + powl(rcoord[it3] - rcoord[it1], 2);
				sum[1] = powl(zcoord[it2] - zcoord[it3], 2) + powl(rcoord[it2] - rcoord[it3], 2);
				sum[2] = powl(zcoord[it1] - zcoord[it2], 2) + powl(rcoord[it1] - rcoord[it2], 2);
				maxsum = max(sum[0], max(sum[1], sum[2]));
				minh = 2. * a / sqrtl(maxsum);
				dt = min(minh / (3. * sqrt((ka + 4. / 3. * G) / ro0 + 1.)), dt);
			}
			if (dt < dtime) {
				for (int i = 1; i <= numbertop; i++) {
					rcoord[i] = rcoord1[i];
					zcoord[i] = zcoord1[i];
				}
				squareall();
				dtime = 0.9 * dt;
				goto L1;
			}
			// (2015 год) Пускай уж лучше рухнит здесь, чем потом вывидет неверный результат!
			if (dtimepr >= dtime*1.e10)
				abort();
			tim += dtime;
			for (int i = 1; i <= numbertop; i++) {
				speedr[i] = speedr1[i];
				speedz[i] = speedz1[i];
			}
			// СКОРОСТЬ НА НИЖНЕЙ ГРАНИЦЕ ОСНОВАНИЯ
			if (CheckBoxn->Checked) // Нижняя волна
			{
				for (int i = 1; i <= n4 + 1; i++) {
					// (2015 год) Проверить на ошибки!!!!
					if (n < nt / 2) // <-- (2015 год) Проверить здесь
							speedz[i] = vindent * sin(n * M_PI / (nt / 2.));
					else
						speedz[i] = 0.;
				}
			}
			if (CheckBoxns->Checked) // Сильная нижняя волна
			{
				for (int i = 1; i <= n4 + 1; i++) {
					speedz[i] = vindent;
				}
			}
			if (CheckBoxn2->Checked) // 2 нижних волны
			{
				for (int i = 1; i <= n4 + 1; i++) {
					speedz[i] = abs(vindent * sin(massn1[n] * M_PI / (tnc - tns))) +
						abs(vn2 * sin(massn2[n] * M_PI / (tnc2 - tns2)));
				}
			}
			if (CheckBoxno2->Checked) // 2 нижних одновременных волных
			{
				// (2015 год) ТОЧНО ПРОВЕРИТЬ НА ОШИБКИ!!!!
				for (int i = 1; i <= n4 + 1 / 2; i++) // <-- (2015 год) Особенно вот такой бред!
						speedz[i] = vindent * sin(massn1[n] * M_PI / tnc);
				for (int i = n4 + 1 / 2; i <= n4 + 1; i++) // <-- (2015 год) Особенно вот такой бред!
						speedz[i] = vn2 * sin(massn1[n] * M_PI / tnc2);
			}
			if (CheckBoxnp1->Checked) // Нижняя пространственная волна 1
				for (int i = 0; i <= n4 + 1; i++)
					speedz[i] = abs(vindent * sin(M_PI_2 - M_PI_2 * i / (n4 + 1)) * sin(M_PI_2 - M_PI_2 * n / nt));
			if (CheckBoxnp2->Checked) // Нижняя пространственная волна 2
				for (int i = 0; i <= n4 + 1; i++)
					speedz[i] = abs(vindent * sin((M_PI_2) * i / (n4 + 1)) * sin(M_PI_2 - M_PI_2 * n / nt));
			if (CheckBoxnp3->Checked) // Нижняя пространственная волна 3
			{
				for (int i = 0; i < n4; i++) {
					if (rcoord[i] <= radius1 / 4.) {
						speedz[i] = abs(vindent * sin(M_PI_2 * 8. * rcoord[i] / radius1) * sin(M_PI_2 - M_PI_2 * n / nt));
					}
					else {
						if ((rcoord[i] > radius1 / 4.) && (rcoord[i] <= radius1 / 2.)) {
							speedz[i] = abs(vn2 * sin(M_PI_2 * 4. * rcoord[i] / radius1) * sin(M_PI_2 - M_PI_2 * n / nt));
						}
						else {
							if ((rcoord[i] > radius1 / 2.) && (rcoord[i] <= 3. * radius1 / 4.)) {
								speedz[i] =
									abs(vindent * sin(M_PI_2 * 8. * rcoord[i] / (3. * radius1)) * sin
									(M_PI_2 - M_PI_2 * n / nt));
							}
							else {
								if ((rcoord[i] > 3. * radius1 / 4.) && (rcoord[i] <= radius1)) {
									speedz[i] =
										abs(vn2 * sin(M_PI_2 * 2. * rcoord[i] / radius1) * sin(M_PI_2 - M_PI_2 * n / nt));
								}
							}
						}
					}
				}
			}
			// Скорость на боковой границе основания
			if (CheckBoxb->Checked) // Боковая волна  (синусоидальная)
			{
				// for (int i=1; i<=numbertop; i++)
				// if (rcoord[i]==radius1)
				for (int i = n4 + 1; i <= (n4 + 1) * (n2 + 1); i += n4 + 1) {
					// (2015 год) Проверить на ошибки!!!
					if (n < nt / 2) // <-- (2015 год) Проверить здесь
							speedr[i] = -vb * sin(n * M_PI / (nt / 2));
					// <-- (2015 год) и здесь
					else
						speedz[i] = 0;
				}
			}
			if (CheckBoxbs->Checked) // Сильная боковая Волна (Прямая)
			{
				// for (int i=1; i<=numbertop; i++)
				// if (rcoord[i]==radius1)
				for (int i = n4 + 1; i <= (n4 + 1) * (n2 + 1); i += n4 + 1)
					speedr[i] = -vb;
			}
			if (CheckBoxb2->Checked) // 2 боковых волны
			{
				for (int i = 1; i <= numbertop; i++)
					if (SameValue(rcoord[i], radius1))
						speedr[i] = -abs(vb * sin(massb1[n] * M_PI / (tbc - tbs))) -
							abs(vb2 * sin(massb2[n] * M_PI / (tbc2 - tbs2)));
			}
			if (CheckBoxinss->Checked) // Внутренняя волна
			{
				if (RadioGroup1->ItemIndex == 0) // Прямая
				{
					for (int i = h2i[1] / (h0 / n1) + 1; i <= (n4) * (n2 + 1); i += n4 + 1)
						speedr[i] = inss;
					for (int i = (n4 + 1) * (n2) + 1; i <= (n4 + 1) * (n2) + h2i[1] / (h0 / n1); i++)
						// int i=(n4+1)*(n2)+1;
							speedz[i] = inss;
				}
				if (RadioGroup1->ItemIndex == 1) // Синусоидальная
				{
					for (int i = h2i[1] / (h0 / n1) + 1; i <= (n4) * (n2 + 1); i += n4 + 1)
						if (n < nt / 2) // <-- (2015 год) Проверить здесь
								speedr[i] = inss * sin(n * M_PI / (nt / 2));
						else
							speedr[i] = 0;
					for (int i = (n4 + 1) * (n2 + 1) + 1; i <= (n4 + 1) * (n2 + 1) + h2i[1] / (h0 / n1); i++)
						if (n < nt / 2)
							speedz[i] = inss * sin(n * M_PI / (nt / 2));
						else
							speedz[i] = 0;
				}
			}

			if (CheckBoxbsh->Checked) // Волна Индентора
			{
				if (RadioGroup1->ItemIndex == 0) // Прямая
				{
					// for (int i=1; i<=numbertop; i++)
					// if (zcoord[i]==h0+h2i[1])
					for (int i = (n2 + 1) * (n4 + 1) + (n1) * (n3); i <= (n2 + 1) * (n4 + 1) + (n1) * (n3 + 1) + 1; i++)
						// int i=(n2+1)*(n4+1)+(n1)*(n3+1);
							speedz[i] = -bsh;
					for (int i = 1; i <= n4 + 1; i++) {
						speedr[i] = 0.;
						speedz[i] = 0.;
					}
				}
				if (RadioGroup1->ItemIndex == 1) // Синусоидальная
				{
					// for (int i=1; i<=numbertop; i++)
					// if (zcoord[i]==h0+h2i[1])
					for (int i = (n2 + 1) * (n4 + 1) + (n1) * (n3); i <= (n2 + 1) * (n4 + 1) + (n1) * (n3 + 1); i++)
						if (n < nt / 2)
							speedz[i] = -bsh * sin(n * M_PI / (nt / 2));
					// <-- (2015 год) Проверить здесь
					// else speedz[i] = 0;
					for (int i = 1; i <= n4 + 1; i++) {
						speedr[i] = 0.;
						speedz[i] = 0.;
					}
				}
			}
			if (BBCBox->Checked) {
				if (RadioGroup1->ItemIndex == 0) {
					for (int i = 1; i <= n4 + 1; ++i) {
						speedz[i] = bsh;
					}
				}
			}
#ifdef UseParallel
			TParallel::For(NULL, 1, numberelem, BaseLoop);
#else
			for (int k = 1; k <= numberelem; k++)
				BaseLoop(Sender, k);
#endif
			int elementWithMaximalDeformationInTarget = 2 * n4 * (n2 - 1) + 2 * (n3 + 1) + 2; // убейте меня, пожалуйста
			m_sqI2p = max(sqI2p[elementWithMaximalDeformationInTarget], sqI2p[elementWithMaximalDeformationInTarget - 2]);
		}
		if (!(n % (nt / 100))) {
			sT->SaveValues(timepr);

			sData1->SaveValues(timepr);
			sData2->SaveValues(timepr);
			sData3->SaveValues(timepr);

			percentCallBack((n * 100) / nt);
		}
		// if (!NoAnim) {
		bool cinema = cinemaEnabled && !(n % (nt / CinemaEdit->Value));
		if (cinema || !(n % (nt / Min(1000, nt)))) {
			if (!hideGraph || (hideGraph && cinema)) {
				threegraphs(false, n / (nt / CinemaEdit->Value), cinema, path);
				graphForm->Caption = FloatToStr(RoundTo(n * 100. / nt, -1)) + "%|"; // <-- (2015 год) Проверить здесь
				graphForm->Caption = graphForm->Caption + FloatToStr(RoundTo(T_max, 0)) + "|" +
					FloatToStr(RoundTo(T_rec, 0));
			}
		}
		// }
		/* else {
		 if (!(n % (nt / 100)))
		 Button2->Caption = FloatToStr(RoundTo(n * 100. / nt, 0)) + "%";
		 if (!(n % (nt / (numSeries - 1))))
		 GraficRefresh(nforgraf++);
		 //Теперь без картинок нельзя!
		 } */
		if (!(n % (nt >> 7))) {
			StaticText1->Caption = "max(sqI2p)=" + FloatToStr(RoundTo(m_sqI2p, -4));
		}
	}
	threegraphs(true, 1, false, path);

	sData1->Final();
	sData2->Final();
	sData3->Final();
	sT->Final();
	delete sData1;
	delete sData2;
	delete sData3;
	delete sT;

	FinalSaver *sTI = new FinalSaver(GetFileName("T", "final", "", path, exstamp));
	sTI->AddItem("R, %", [](int i) {return (double)(i - 1) / (double)(n4 - 1);}, [](long double v)
	{return FloatToStr(RoundTo(v * 100, -2)) + "%";});
	sTI->AddItem("T, K", [](int i) {return (T[TElemTarget[i]] + T[TElemTarget[i] - 1]) / 2;});
	sTI->AddItem("sqI2p", [](int i) {return sqI2p[TElemTarget[i]];});

	for (int i = 1; i <= n4; ++i) {
		sTI->SaveValues(i);
	}

	sTI->Final();
	delete sTI;

	const int dataSize = 11;
	long double *data[dataSize] = {epsrr, epszz, epsrz, epstt, epsrrp, epszzp, epsrzp, epsttp, tet, p, sqI2p};
	UnicodeString dname[dataSize] = {
		"epsrr", "epszz", "epsrz", "epstt", "epsrrp", "epszzp", "epsrzp", "epsttp", "tet", "p", "sqI2p"};

	FinalSaver *sD = new FinalSaver(GetFileName("data", "final", "", path, exstamp));
	sD->AddItem("R, %", [](int i) {return (double)(i - 1) / (double)(n4 - 1);}, [](long double v)
	{return FloatToStr(RoundTo(v * 100, -2)) + "%";});
	for (int j = 0; j < dataSize; ++j) {
		long double *dj = data[j];
		sD->AddItem(dname[j], [dj](int i) {return dj[TElemTarget[i]];});
	}
	sD->AddItem("T, K", [](int i) {return (T[TElemTarget[i]] + T[TElemTarget[i] - 1]) / 2.;});

	for (int i = 2 * n2 * n4; i > 0; --i) {
		if (I2p[i] > 0)
			minpp[(i - 1) % (2 * (int)n4) + 1] = i;
	}
	sD->AddItem("MaxPD, mm", [tcrd, &minpp](int i) {int res = min(minpp[2 * i], minpp[2 * i - 1]);
		if (res < 0)
			res = max(minpp[2 * i], minpp[2 * i - 1]);
		if (res < 0)
			return 0.L; return tcrd - (zcoord[itop[1][res]] + zcoord[itop[2][res]] + zcoord[itop[3][res]]) / 0.003;});

	for (int i = 1; i <= n4; ++i) {
		sD->SaveValues(i);
	}

	sD->Final();
	delete sD;

    delete[]centralPoints;

	// Button2->Caption = capt;
	// fclose(file);
	// fclose(file1);
	// fclose(file2);
	// fclose(file3);
	if (graphForm->BorderStyle == bsNone) {
		graphForm->BorderStyle = bsSizeable;
		graphForm->ClientWidth = 640;
		graphForm->ClientHeight = 480;
	}

	// (2015 год) О да!!!
	if (CheckBoxb2->Checked) {
		delete[]massb1;
		delete[]massb2;
	}
	if (CheckBoxn2->Checked) {
		delete[]massn1;
		delete[]massn2;
	}
	if (CheckBoxno2->Checked) {
		delete[]massn1;
		delete[]massn2;
	}
	return true;
}

// Нажатие книпки "Пуск". Основная функция.
void __fastcall TmainForm::RefreshClick(TObject *Sender) {
	TDateTime etime = Sysutils::Now();
	SetFormState(false);
	UnicodeString dtstamp;
	DateTimeToString(dtstamp, "yymmddhhnnss", etime);
	bool res;
	UnlimStop = false;
	UnicodeString msg = "";
	try {
		res = Calculate(dtstamp, false, "exper");
	}
	catch (Exception &e) {
		res = false;
		msg = e.Message;
	}
	catch (...) {
		res = false;
		msg = "Неизвестная ошибка";
	}
	etime = Sysutils::Now() - etime;
	UnicodeString resstr;
	DateTimeToString(resstr, ":nn:ss.zzz", etime);
	resstr = IntToStr((int)((double)etime * 24.)) + resstr;
	resstr = (res) ? ("Выполнено успешно. Время выполнения: " + resstr) :
		("Выполнение прервано через " + resstr + ((msg == "") ? "" : (" с сообщением «" + msg + "»")));
	if (res)
		Application->MessageBoxW(resstr.w_str(), ((UnicodeString)"Расчёт завершён").w_str(), 0x40);
	else
		Application->MessageBoxW(resstr.w_str(), ((UnicodeString)"Расчёт прерван").w_str(), 0x10);
	SetFormState(true);
}

// *****************************************************************
// ПРОЦЕДУРА ВЫЧИСЛЕНИЯ ЧИСЛА УЗЛОВ И ЭЛЕМЕНТОВ
void sizeofelement() {
	dr = radius0 / n3;
	dz = h0 / n1;
	if (mainForm->CheckBox4->Checked) {
		n2 = 0;
		for (int i = 1; i <= nstrat; i++) {
			n2i[i] = h2i[i] / dz;
			n2 = n2 + n2i[i];
		}
		if (n1 > n2)
			n1 = n2; // сохранение симметрии
		n4 = n3 + (radius1 - radius0) / dr;
		dr0 = dr;
		dz0 = dz;
		if (radius1 > radius0)
			dr1 = dr0;
		else
			dr1 = 0.;
		for (int i = 1; i <= nstrat; i++)
			dz2[i] = h2i[i] / n2i[i];
	}
	if (mainForm->CheckBox3->Checked) {
		n4 = 0;
		n2 = radius1 / dz;
		H1 = radius1;
		radius1 = 0.;
		for (int i = 1; i <= nstrat; i++) {
			n2i[i] = h2i[i] / dr;
			// количество разбиений по толщине кольца для каждого слоя
			n4 = n4 + n2i[i];
			dz2[i] = h2i[i] / n2i[i];
			// dzi - шаг по радиусу для итого материала
			radius1 = radius1 + h2i[i];
		}
		dr0 = dr;
		dz0 = dz;
	}
	/* if (radius1>radius0)
	 dr1 = dr0;
	 else
	 dr1 = 0.; */
	numbertop = (n2 + 1) * (n4 + 1) + (n3 + 1) * n1;
	// Количество точек в правой половине отображаемой конструкции.
	// n1 без единицы, потому что количество точек на нижней границе уже было учтено
	numberelem = 2 * (n4 * n2 + n1 * n3);
}

// *****************************************************************
// ПРОЦЕДУРА ОПРЕДЕЛЕНИЯ УЗЛОВ И ЭЛЕМЕНТОВ В ЦЕНТРЕ, СВЕРХУ,
// НА БОКОВОЙ И НА ТЫЛЬНОЙ СТОРОНАХ МИШЕНИ И УДАРНИКА
void pointelem() {
	// CENTER/SIDE TARGET
	for (int i = 1; i <= n2 + 1; i++) {
		CPointTarget[i] = i * (n4 + 1) - n4;
		SPointTarget[i] = i * (n4 + 1);
	}
	for (int i = 1; i <= n2; i++) {
		CElemTarget[i] = 1 + 2 * n4 * (i - 1);
		SElemTarget[i] = 2 * i * n4;
	}
	// BOTTOM/TOP	TARGET
	for (int i = 1; i <= n4 + 1; i++) {
		BPointTarget[i] = i;
		TPointTarget[i] = n2 * (n4 + 1) + i;
	}
	for (int i = 1; i <= n4; i++) {
		BElemTarget[i] = 2 * i - 1;
		TElemTarget[i] = 2 * n4 * (n2 - 1) + 2 * i;
	}
	// CENTER/SIDE IMPACTOR
	CPointImpactor[1] = n2 * (n4 + 1) + 1;
	SPointImpactor[1] = n2 * (n4 + 1) + n3 + 1;
	for (int i = 2; i <= n1 + 1; i++) {
		CPointImpactor[i] = n2 * (n4 + 1) + n4 - 2 * n3 + i * (n3 + 1);
		SPointImpactor[i] = n2 * (n4 + 1) + n4 - n3 + i * (n3 + 1);
	}

	for (int i = 1; i <= n1; i++) {
		CElemImpactor[i] = 2 * (n2 * n4 - n3 + 1 + i * n3);
		SElemImpactor[i] = 2 * (n2 * n4 + i * n3) - 1;
	}
	// BOTTOM/TOP IMPACTOR
	for (int i = 1; i <= n3 + 1; i++) {
		BPointImpactor[i] = n2 * (n4 + 1) + i;
		TPointImpactor[i] = n2 * (n4 + 1) + n4 - n3 + n1 * (n3 + 1) + i;
	}

	for (int i = 1; i <= n3; i++) {
		BElemImpactor[i] = 2 * (n2 * n4 + i) - 1;
		TElemImpactor[i] = 2 * (n2 * n4 + n1 * n3 - n3 + i);
	}
}

// *****************************************************************
// ПРОЦЕДУРА ОПРЕДЕЛЕНИЯ МАТЕРИАЛА КАЖДОГО ЭЛЕМЕНТА}

void topology() {
	int k = 2 * n2 * n4 + 2 * n3;
	// (2015 год) Адский коддинг! Что тут вообще делается и происходит!
	// (Ales'hon'ne 15.2.5) Здесь происходит заполнение массива matelm с середины.
	// (Ales'hon'ne 15.2.5) Сатана доволен своими учениками.
	for (int i = 1; i <= 2 * n3; i++) {
		matelm[k--] = matstrat0;
		// k = k - 1;
	}
	if (mainForm->CheckBox4->Checked)
		// (Ales'hon'ne 15.2.5) горизонтальные слои
	{
		for (int i = 1; i <= nstrat; i++)
			for (int j = 1; j <= n2i[i] * 2 * n4; j++) {
				int tmat = matstrat[i];
				if (test_k(k))
					tmat = matstrat0;
				matelm[k--] = tmat;
				// k = k - 1;
			}
	}
	if (mainForm->CheckBox3->Checked) // (Ales'hon'ne 15.2.5) вертикальные слои
	{
		for (int i = 1; i <= n2; i++) {
			switch (nstrat) {
			case 1: // (Ales'hon'ne 15.2.5) один вертикальный слой
				for (int j = 1; j <= n2i[1] * 2; j++) {
					matelm[k--] = matstrat[1];
					// k = k - 1;
				}
				break;
			case 2: // (Ales'hon'ne 15.2.5) два вертикальных слоя
				for (int j = 1; j <= n2i[2] * 2; j++) {
					matelm[k--] = matstrat[2];
					// k = k - 1;
				}
				for (int j = 1; j <= n2i[1] * 2; j++) {
					matelm[k--] = matstrat[1];
					// k = k - 1;
				}
				break;
			case 3: // (Ales'hon'ne 15.2.5) три вертикаьлных слоя
				for (int j = 1; j <= n2i[3] * 2; j++) {
					matelm[k--] = matstrat[3];
					// k = k - 1;
				}
				for (int j = 1; j <= n2i[2] * 2; j++) {
					matelm[k--] = matstrat[2];
					// k = k - 1;
				}
				for (int j = 1; j <= n2i[1] * 2; j++) {
					matelm[k--] = matstrat[1];
					// k = k - 1;
				}
				break;
			default:
				throw(" Ищите switch ");
			}
		}
	}
	/////////////////////////////////////////////////////////////////////////////
	int i1, k1, j1, kv, kn, k2;
	for (int l = 1; l <= n2 * n4 + n3; l++) // <-- (2015 год) Новая реализация
	{
		// (2015 год) Проверить на ошибки!!!
		i1 = l + (l - 1) / n4;
		k1 = i1 + 2 + n4;
		j1 = i1 + 1;
		k2 = k1 - 1;
		kv = 2 * l;
		kn = kv - 1;
		if (l <= n2 * n4) {
			itop[1][kn] = i1;
			itop[2][kn] = j1;
			itop[3][kn] = k2;
			itop[1][kv] = j1;
			itop[2][kv] = k1;
			itop[3][kv] = k2;

			nearel[i1] = nearel[i1] + 1;
			nearel[j1] = nearel[j1] + 2;
			nearel[k1] = nearel[k1] + 1;
			nearel[k2] = nearel[k2] + 2;

			numb[i1][nearel[i1]][1] = kn;
			numb[k1][nearel[k1]][1] = kv;
			numb[j1][nearel[j1]][1] = kn;
			numb[j1][nearel[j1] - 1][1] = kv;
			numb[k2][nearel[k2]][1] = kv;
			numb[k2][nearel[k2] - 1][1] = kn;
			numb[i1][nearel[i1]][2] = 1;
			numb[k1][nearel[k1]][2] = 2;
			numb[j1][nearel[j1]][2] = 2;
			numb[j1][nearel[j1] - 1][2] = 1;
			numb[k2][nearel[k2]][2] = 3;
			numb[k2][nearel[k2] - 1][2] = 3;
		}
		else {
			i1 = l + (l - 1) / n4;
			k1 = i1 + 2 + n4;
			j1 = i1 + 1;
			k2 = k1 - 1;
			kv = 2 * l;
			kn = kv - 1;

			itop[1][kn] = i1;
			itop[2][kn] = j1;
			itop[3][kn] = k1;
			itop[1][kv] = i1;
			itop[2][kv] = k1;
			itop[3][kv] = k2;

			nearel[i1] = nearel[i1] + 2;
			nearel[j1] = nearel[j1] + 1;
			nearel[k1] = nearel[k1] + 2;
			nearel[k2] = nearel[k2] + 1;

			numb[i1][nearel[i1]][1] = kv;
			numb[i1][nearel[i1] - 1][1] = kn;
			numb[k1][nearel[k1]][1] = kv;
			numb[k1][nearel[k1] - 1][1] = kn;
			numb[j1][nearel[j1]][1] = kn;
			numb[k2][nearel[k2]][1] = kv;
			numb[i1][nearel[i1]][2] = 1;
			numb[i1][nearel[i1] - 1][2] = 1;
			numb[k1][nearel[k1]][2] = 2;
			numb[k1][nearel[k1] - 1][2] = 3;
			numb[j1][nearel[j1]][2] = 2;
			numb[k2][nearel[k2]][2] = 3;
		}
	}

	int istart = (n2 + 1) * (n4 + 1);
	int trast = n3; // Штука для определения, дошли ли мы до конца строки
	int tzast = n1;
	// int poluverh = (n1 - 1)/3;//полуверх :-)
	int tmat /* = matstrat0 */ ;
	int tcrdr = -1, tcrdz = -1;
	// magic is here - координаты текущего квадратика с двумя треугольничками
	for (int l = 1; l <= n3 * (n1 - 1); l++) // <-- (2015 год) Новая реализация
	{
		tcrdr = (tcrdr + 1) % trast;
		if (!tcrdr)
			tcrdz++;
		i1 = l + (l - 1) / n3 + istart;
		k1 = i1 + 2 + n3;
		j1 = i1 + 1;
		k2 = k1 - 1;
		kv = 2 * (l + n2 * n4 + n3);
		kn = kv - 1;
		tmat = matstrat0;
		/* if (tcrdr*tcrdr+pow(tcrdz-0.5*tzast,2)<=0.125*tzast*tzast) {
		 tmat = 1;
		 } */
		// Случай стакана в качестве сооружения
		if (mainForm->CheckBoxStakan->Checked) {
			if ((l == trast) + (l == trast - 1) + (l == trast - 2) + (l > ((n3 - 2) * (n1))))
				// <-- (2015 год) Подозрительный код
			{
				if (l == trast)
					trast += n3;
				matelm[kn] = tmat;
				matelm[kv] = tmat;
			}
			else {
				// Теперь воздух - это 0!!!
				matelm[kn] = 0; // (Ales'hon'ne 15.2.5) 9 - это воздух
				matelm[kv] = 0; // (Ales'hon'ne 15.2.5) но только здесь
			}
			if (mainForm->ComboBoxBuild->ItemIndex == 1) {
				if ((l > ((n3 - 10) * (n1))) * (l < ((n3 - 8) * (n1))))
					// <-- (2015 год) Подозрительный код
				{
					matelm[kn] = tmat;
					matelm[kv] = tmat;
				}
			}
			if (mainForm->ComboBoxBuild->ItemIndex == 2) {
				if ((l > ((n3 - 14) * (n1))) * (l < ((n3 - 12) * (n1))))
					// <-- (2015 год) Подозрительный код
				{
					matelm[kn] = tmat;
					matelm[kv] = tmat;
				}
				if ((l > ((n3 - 8) * (n1))) * (l < ((n3 - 6) * (n1))))
					// <-- (2015 год) Подозрительный код
				{
					matelm[kn] = tmat;
					matelm[kv] = tmat;
				}
			}
			if (mainForm->ComboBoxBuild->ItemIndex == 3) {
				if ((l > ((n3 - 14) * (n1))) * (l < ((n3 - 12) * (n1))))
					// <-- (2015 год) Подозрительный код
				{
					matelm[kn] = tmat;
					matelm[kv] = tmat;
				}
				if ((l > ((n3 - 10) * (n1))) * (l < ((n3 - 8) * (n1))))
					// <-- (2015 год) Подозрительный код
				{
					matelm[kn] = tmat;
					matelm[kv] = tmat;
				}
				if ((l > ((n3 - 6) * (n1))) * (l < ((n3 - 4) * (n1))))
					// <-- (2015 год) Подозрительный код
				{
					matelm[kn] = tmat;
					matelm[kv] = tmat;
				}
			}
		}
		else {
			matelm[kn] = tmat;
			matelm[kv] = tmat;
		}

		itop[1][kn] = i1;
		itop[2][kn] = j1;
		itop[3][kn] = k1;
		itop[1][kv] = i1;
		itop[2][kv] = k1;
		itop[3][kv] = k2;

		nearel[i1] = nearel[i1] + 2;
		nearel[j1] = nearel[j1] + 1;
		nearel[k1] = nearel[k1] + 2;
		nearel[k2] = nearel[k2] + 1;

		numb[i1][nearel[i1]][1] = kv;
		numb[i1][nearel[i1] - 1][1] = kn;
		numb[k1][nearel[k1]][1] = kv;
		numb[k1][nearel[k1] - 1][1] = kn;
		numb[j1][nearel[j1]][1] = kn;
		numb[k2][nearel[k2]][1] = kv;
		numb[i1][nearel[i1]][2] = 1;
		numb[i1][nearel[i1] - 1][2] = 1;
		numb[k1][nearel[k1]][2] = 2;
		numb[k1][nearel[k1] - 1][2] = 3;
		numb[j1][nearel[j1]][2] = 2;
		numb[k2][nearel[k2]][2] = 3;
	}
}

// *****************************************************************
// ПРОЦЕДУРА ВЫЧИСЛЕНИЯ НАЧАЛЬНЫХ КООРДИНАТ УЗЛОВ
void topcoord() {
	int ntop;
	long double rnew1, rnew, znow;
	if (mainForm->CheckBox4->Checked) {
		for (int i = 1; i <= n3 + 1; i++) {
			for (int j = 1; j <= n2 + 1; j++) {
				rnew = dr0 * (i - 1);
				ntop = i + (n4 + 1) * (j - 1);
				rcoord[ntop] = rnew;
			} // for (int j = 1; j<=n2 + 1; j++)
			for (int j = 1; j <= n1; j++) {
				ntop = i + (n4 + 1) * (n2 + 1) + (n3 + 1) * (j - 1);
				rcoord[ntop] = rnew;
			} // for (int j = 1; j<=n1; j++)
		} // for (int i = 1; i<=n3 + 1; i++)
		if (n4 > n3)
			for (int i = 1; i <= n4 - n3; i++) {
				rnew1 = rnew + dr1 * i;
				for (int j = 1; j <= n2 + 1; j++) {
					ntop = (n4 + 1) * (j - 1) + i + n3 + 1;
					rcoord[ntop] = rnew1;
				} // for (int j = 1; j<=n2 + 1; j++)
			} // for (int i = 1; i<=n4-n3; i++)
		// *********************************************************************
		znow = 0.;
		ntop = 0;
		for (int i = 1; i <= n4 + 1; i++) {
			ntop = ntop + 1;
			zcoord[ntop] = znow;
		} // for (int i = 1; i<=n4 + 1; i++)
		for (int i = 1; i <= nstrat; i++) {
			// (2015 год) Адский коддинг! Что ту вообще делается и происходит!
			for (int k = 1; k <= n2i[nstrat - i + 1]; k++) {
				znow = znow + dz2[nstrat - i + 1];
				for (int j = 1; j <= n4 + 1; j++) {
					ntop = ntop + 1;
					zcoord[ntop] = znow;
				} // for (int j = 1; j<=n4 + 1; j++)
			} // for (int k = 1; k<= n2i[nstrat-i+1]; k++)
		} // for (int i = 1; i<=nstrat; i++)
		for (int k = 1; k <= n1; k++) {
			znow = znow + dz0;
			for (int j = 1; j <= n3 + 1; j++) {
				ntop = ntop + 1;
				zcoord[ntop] = znow;
			} // for (int j = 1; j<=n3 + 1; j++)
		} // for (int k = 1; k <= n1; k++)
		// sizepic = zcoord[numbertop];
	} // if (Form1->CheckBox4->Checked)

	if (mainForm->CheckBox3->Checked) {
		znow = 0;
		ntop = 0.;
		// ****************************************************
		for (int i = 1; i <= n4 + 1; i++) {
			ntop = ntop + 1;
			zcoord[ntop] = znow;
		} // for(int i = 1; i<=n4+1; i++)
		for (int i = 1; i <= n2; i++) {
			znow = znow + dz0;
			for (int j = 1; j <= n4 + 1; j++) {
				ntop = ntop + 1;
				zcoord[ntop] = znow;
			} // for(int j = 1; j <= n4+1; j++)
		} // for(int i = 1; i<=n2; i++)
		for (int i = 1; i <= n1; i++) {
			znow = znow + dz0;
			for (int j = 1; j <= n3 + 1; j++) {
				ntop = ntop + 1;
				zcoord[ntop] = znow;
			} // for(int j = 1; j <= n4+1; j++)
		} // for(int i = 1; i <= n1; i++)
		// ****************************************************
		for (int i = 1; i <= n3 + 1; i++) {
			for (int j = 1; j <= n2 + 1; j++) {
				rnew = dr0 * (i - 1);
				ntop = i + (n4 + 1) * (j - 1);
				rcoord[ntop] = rnew;
			} // for (int j = 1; j<=n2 + 1; j++)
			for (int j = 1; j <= n1; j++) {
				ntop = i + (n4 + 1) * (n2 + 1) + (n3 + 1) * (j - 1);
				rcoord[ntop] = rnew;
			} // for (int j = 1; j<=n1; j++)
		} // for (int i = 1; i<=n3 + 1; i++)
		if (n4 > n3)
			for (int i = 1; i <= n4 - n3; i++) {
				rnew1 = rnew + dr0 * i;
				for (int j = 1; j <= n2 + 1; j++) {
					ntop = (n4 + 1) * (j - 1) + i + n3 + 1;
					rcoord[ntop] = rnew1;
				} // for (int j = 1; j<=n2 + 1; j++)
			} // for (int i = 1; i<=n3 + 1; i++)
	} // if (Form1->CheckBox3->Checked)
}

// *****************************************************************
// ПРОЦЕДУРА ВЫЧИСЛЕНИЯ ПЛОЩАДИ И КООРДИНАТЫ ЦЕНТРА ТЯЖЕСТИ
// КАЖДОГО ЭЛЕМЕНТА (ТРЕУГОЛЬНИКА)
void __fastcall TmainForm::SquareLoop(TObject *, int k) {
	int it1 = itop[1][k];
	int it2 = itop[2][k];
	int it3 = itop[3][k];
	rcent[k] = (rcoord[it1] + rcoord[it2] + rcoord[it3]) / 3.;
	square[k] = abs(0.5 * (rcoord[it2] * (zcoord[it3] - zcoord[it1]) + rcoord[it1] * (zcoord[it2] - zcoord[it3]) +
		rcoord[it3] * (zcoord[it1] - zcoord[it2])));
	// (2015 год) Чтоб вы каждый день считали площади различных треугольников!
	// (2015 год) : треугольных треугольников, кватдратных треугольников, круглых треугольников!
	// (2015 год) : и да - конечно же треугольников с отрицательной площадью!
	// if (square[k] == 0.)
	// square[k] = 0.00000001;
	// if (square[k] < 0.)
	// abort();
}

void __fastcall TmainForm::squareall() {
	// int it1, it2, it3;
#ifdef UseParallel
	TParallel::For(NULL, 1, numberelem, SquareLoop);
#else
	for (int k = 1; k <= numberelem; k++) {
		SquareLoop(NULL, k);
	}
#endif
}

// *****************************************************************
// ПРОЦЕДУРА ВЫЧИСЛЕНИЯ МАССЫ УЗЛОВ И ЭЛЕМЕНТОВ
void masses() {
	long double a, ro0, rct;
	for (int k = 1; k <= numberelem; k++) {
		ro0 = Material[matelm[k]].ro0;
		rct = rcent[k];
		a = square[k];
		amaselm[k] = 2. * M_PI * ro0 * rct * a;
	}
	for (int i = 1; i <= numbertop; i++) {
		amasstop[i] = 0.;
		for (int j = 1; j <= nearel[i]; j++)
			amasstop[i] = amasstop[i] + amaselm[numb[i][j][1]] / 3.;
	}
}

// КАРТИНОЧКИ
TBitmap *bmp;
TCanvas *holst;
TRect rect;
bool beauty;

TColor TempToColor(long double T, bool bw);

void _fastcall TmainForm::threegraphs(bool save, int i, bool cinema, UnicodeString path) {
	rect = Rect(0, 0, graphForm->ClientWidth, graphForm->ClientHeight);
	bmp = new TBitmap();
	bmp->PixelFormat = pf24bit;
	bmp->SetSize(rect.Width(), rect.Height());
	holst = bmp->Canvas;
	holst->FillRect(rect);
	beauty = BeautyCBox->Checked;

	for (int k = 1; k <= numberelem; k++)
		threeangle(k);

	// if (beauty) AntiAliasing();//Антиальясинг - зло!
	graphForm->Canvas->CopyRect(rect, holst, rect);
	if (save || cinema) {
		SaveAsPNG(bmp, path + ((cinema) ? "Cinema\\" : "") + IntToStr(i) + ".png");
	}
	// bmp->ReleaseHandle();
	// bmp->Free();
	delete bmp;
}

// *****************************************************************
// ПРОЦЕДУРА ПОСТРОЕНИЯ ЭЛЕМЕНТА (ТРЕУГОЛЬНИКА)
TColor TempToColor(long double T, bool bw) {
	struct MyRGB {
		int r, g, b;
		long double T;

		TColor color() {
			return static_cast<TColor>(RGB(r, g, b));
		}
	} TG[5] = {
		{0, 0, 0, 0.}, {(bw) ? 20 : 70, (bw) ? 20 : 70, (bw) ? 20 : 70, 300.},
		{(bw) ? 150 : 175, (bw) ? 150 : 43, (bw) ? 150 : 30, 350.}, {(bw) ? 220 : 255, (bw) ? 220 : 255, (bw) ? 220 : 0, 400.
		}, {255, 255, 255, T_max}};
	if (T >= TG[4].T) {
		return TG[4].color();
	}
	if (T <= TG[0].T) {
		return TG[0].color();
	}
	MyRGB a, b, c;
	for (int i = 0; i < 4;) {
		if (InRange(T, (a = TG[i], a.T), (b = TG[++i], b.T))) {
			break;
		}
	}
	float p = (T - a.T) / (b.T - a.T);
	c.r = a.r + (int)(p * (b.r - a.r));
	c.g = a.g + (int)(p * (b.g - a.g));
	c.b = a.b + (int)(p * (b.b - a.b));
	return c.color();
}

void threeangle(int k) {
	TColor DefColor, HotColor;
	TPoint poly[3];
	bool bw = mainForm->BWCBox->Checked;
	holst->Pen->Color = (bw) ? clBlack : static_cast<TColor>(RGB(30, 30, 30));
	DefColor = (bw) ? clWhite : static_cast<TColor>(Material[matelm[k]].Color);
	if (Colorletch[k - 1] && matelm[k]) {//материал — не воздух
		if (I2p[k] > 0) {
			DefColor = (bw) ? clGray : clYellow;
		}
		if (crashed[k]) {
			DefColor = (bw) ? clBlack : clRed;
			Colorletch[k - 1] = 0;
		}
	}
	else
		DefColor = (bw) ? clBlack : clRed;
	if (mainForm->CheckBox5->Checked) {
		if (beauty) {
			if (k % 2 == 0)
				HotColor = TempToColor((T[k] + T[k - 1]) / 2, bw);
			else
				HotColor = TempToColor((T[k] + T[k + 1]) / 2, bw);
		}
		else
			HotColor = TempToColor(T[k], bw);
	}
	else
		HotColor = DefColor;
	// (2015 год) Проверить на ошибки!!!
	for (int il = 1; il <= 3; ++il) {
		poly[il - 1] = Point((graphForm->ClientWidth + WidthCoef1 + rcoord[itop[il][k]] * WidthCoef) / 2,
			HeightCoef1 - zcoord[itop[il][k]] * HeightCoef);
	}
	holst->Brush->Color = DefColor;
	// holst->Pen->Color = DefColor;
	holst->Polygon(poly, 2);
	if (mainForm->CheckBox5->Checked)
		holst->Pen->Color = (bw) ? clBlack : static_cast<TColor>(Material[matelm[k]].Color);
	for (int il = 1; il <= 3; ++il) {
		poly[il - 1] = Point((graphForm->ClientWidth - WidthCoef1 - rcoord[itop[il][k]] * WidthCoef) / 2,
			HeightCoef1 - zcoord[itop[il][k]] * HeightCoef);
	}
	holst->Brush->Color = HotColor;
	// holst->Pen->Color = HotColor;
	holst->Polygon(poly, 2);
	/* if(k==point1 || k==point2 || k==point3)
	 holst->TextOutW((poly[0].x+poly[1].x+poly[2].x)/3-4, (poly[0].y+poly[1].y+poly[2].y)/3-4,IntToStr(k)); */
	// holst->Brush->Color = clBlack;
}

void newspeed() {
	long double sumr, sumz, rc, zc;
	int k, it1, it2, it3;
	for (int i = 1; i <= numbertop; i++) {
		sumr = 0.;
		sumz = 0.;
		rc = 0.;
		zc = 0.;
		for (int j = 1; j <= nearel[i]; j++) {
			k = numb[i][j][1];
			it1 = itop[1][k];
			it2 = itop[2][k];
			it3 = itop[3][k];
			switch (numb[i][j][2]) {
			case 1:
				rc = rcoord[it3] - rcoord[it2];
				zc = zcoord[it2] - zcoord[it3];
				break;
			case 2:
				rc = rcoord[it1] - rcoord[it3];
				zc = zcoord[it3] - zcoord[it1];
				break;
			case 3:
				rc = rcoord[it2] - rcoord[it1];
				zc = zcoord[it1] - zcoord[it2];
				break;
			default:
				throw(" Ищите switch ");
			}
			sumr += rcent[k] * (sigmarr[k] * zc + sigmarz[k] * rc) + 2. / 3. * square[k] * sigmatt[k];
			sumz += rcent[k] * (sigmazz[k] * rc + sigmarz[k] * zc);
		}
		speedr1[i] = speedr[i] - dtime * sumr / amasstop[i];
		speedz1[i] = speedz[i] - dtime * sumz / amasstop[i];
	}
}

// ---------------------------------------------------------------------------

void ReinitBoxes() {
	int i0 = mainForm->matstrat0Box->ItemIndex;
	int i1 = mainForm->matstrat1Box->ItemIndex;
	int i2 = mainForm->matstrat2Box->ItemIndex;
	int i3 = mainForm->matstrat3Box->ItemIndex;
	mainForm->matstrat0Box->Items->Clear();
	mainForm->matstrat1Box->Items->Clear();
	mainForm->matstrat2Box->Items->Clear();
	mainForm->matstrat3Box->Items->Clear();
	for (auto i = 0; i < Material.Length; ++i) {
		mainForm->matstrat0Box->Items->Add(Material[i].Name);
		mainForm->matstrat1Box->Items->Add(Material[i].Name);
		mainForm->matstrat2Box->Items->Add(Material[i].Name);
		mainForm->matstrat3Box->Items->Add(Material[i].Name);
	}
	mainForm->matstrat0Box->ItemIndex = (!(Material.Length > i0)) ? Material.Length - 1 : i0;
	mainForm->matstrat1Box->ItemIndex = (!(Material.Length > i1)) ? Material.Length - 1 : i1;
	mainForm->matstrat2Box->ItemIndex = (!(Material.Length > i2)) ? Material.Length - 1 : i2;
	mainForm->matstrat3Box->ItemIndex = (!(Material.Length > i3)) ? Material.Length - 1 : i3;
}

void __fastcall TmainForm::FormCreate(TObject *) {
	DirEdit->Text = ExtractFilePath(Application->ExeName);
	auto path = DirEdit->Text + "materials.xml";
	TForm1* form = new TForm1(this);
	form->ReadFromFile(path);
	Material.set_length(form->matarr.Length);
	for (int i = 1; i < form->matarr.Length; ++i)
		Material[i] = form->matarr[i];
	delete form;

	Material[0].Name = "Воздух";
	Material[0].Color = clWhite;
	Material[0].ro0 = 1.2;
	Material[0].G = 0.0001 * GPa;
	Material[0].sigma0 = 1000;
	Material[0].k1 = 1;
	Material[0].k = 0.00001 * GPa;
	Material[0].alpha = 0 * GPa;
	Material[0].sigma1 = 0.00001 * GPa;
	Material[0].ctep = 0.0;
	Material[0].gammatep = 0.0;

	ReinitBoxes();

	mainForm->matstrat0Box->ItemIndex = (Material.Length <= 2) ? Material.Length - 1 : 1;
	mainForm->matstrat1Box->ItemIndex = (Material.Length <= 3) ? Material.Length - 1 : 2;
	mainForm->matstrat2Box->ItemIndex = (Material.Length <= 4) ? Material.Length - 1 : 3;
	mainForm->matstrat3Box->ItemIndex = (Material.Length <= 5) ? Material.Length - 1 : 4;

	SetFormState(true);

	// *******************************************************************
	// ПАРАМЕТРЫ МАТЕРИАЛОВ
	// 1-Аллюминий, 2-сталь, 3-скальный грунт1, 4-скальный грунт2, бетон
	// 5-скальный грунт3, 6-скальный грунт4, 7-стеклопластик, 8-песок, 9-воздух
	/*
	 // ro0 - ПЛОТНОСТЬ

	 Material[1].ro0 = 2700.;
	 Material[2].ro0 = 7800.;
	 Material[3].ro0 = 3000.;
	 Material[4].ro0 = 2500.;
	 Material[5].ro0 = 2500.;
	 Material[6].ro0 = 2720.;
	 Material[7].ro0 = 1900.;
	 Material[8].ro0 = 1600.;
	 Material[9].ro0 = 1.2;
	 Material[10].ro0 = 2500;

	 // G - МОДУЛЬ СДВИГА
	 Material[1].G = 26.2 * GPa;
	 Material[2].G = 81. * GPa;
	 Material[3].G = 64 * GPa;
	 Material[4].G = 4.17 * GPa;
	 Material[5].G = 7.7 * GPa;
	 Material[6].G = 0.0093 * GPa;
	 Material[3].G = 184 * GPa;
	 Material[4].G = 4.17 * GPa;
	 Material[5].G = 87.7 * GPa;
	 Material[6].G = 0.0093 * GPa;
	 Material[7].G = 26.2 * GPa;
	 Material[8].G = 0.0077 * GPa;
	 Material[9].G = 0.0001 * GPa;
	 Material[10].G = 7.7 * GPa;

	 // sigma0 - начальный предел текучести
	 Material[1].sigma0 = 0.37 * GPa;
	 Material[2].sigma0 = 1.66 * GPa;
	 Material[3].sigma0 = 0.7 * GPa;
	 Material[4].sigma0 = 0.3 * GPa;
	 Material[5].sigma0 = 0.04 * GPa;
	 Material[6].sigma0 = 0.0012 * GPa;
	 Material[7].sigma0 = 0.37 * GPa;
	 Material[8].sigma0 = 100;
	 Material[9].sigma0 = 1000;
	 Material[10].sigma0 = 0.04 * GPa;

	 // k1 - коэффициент угла внутреннего трения
	 Material[1].k1 = 0.;
	 Material[2].k1 = 0.;
	 Material[3].k1 = 0.4;
	 Material[4].k1 = 0.4;
	 // Material[5].k1=0.4;
	 Material[5].k1 = 0.004;
	 Material[6].k1 = 0.73;
	 Material[7].k1 = 0.2;
	 Material[8].k1 = 0.77;
	 Material[9].k1 = 1;
	 Material[10].k1 = 0.4;

	 // K - коэффициент объёмного сжатия
	 Material[1].k = 64. * GPa;
	 Material[2].k = 175. * GPa;
	 Material[3].k = 50 * GPa;
	 Material[4].k = 16.67 * GPa;
	 Material[5].k = 8.4 * GPa;
	 Material[6].k = 0.0278 * GPa;
	 Material[3].k = 160 * GPa;
	 Material[4].k = 16.67 * GPa;
	 Material[5].k = 78.4 * GPa;
	 Material[6].k = 0.0278 * GPa;
	 Material[7].k = 64 * GPa;
	 Material[8].k = 0.01667 * GPa;
	 Material[9].k = 0.00001 * GPa;
	 Material[10].k = 8.4 * GPa;

	 // alpha - коэффициент убывания предела текучести
	 Material[1].alpha = 50.0 * GPa;
	 Material[2].alpha = 0.0 * GPa;
	 Material[3].alpha = -20.11 * GPa;
	 Material[4].alpha = 15.8 * GPa;
	 Material[5].alpha = 100. * GPa;
	 Material[6].alpha = 10.5 * GPa;
	 Material[7].alpha = 1. * GPa;
	 Material[8].alpha = -0.5 * GPa;
	 Material[9].alpha = 0 * GPa;
	 Material[10].alpha = 700 * GPa;

	 // sigma1 - предел текучести при разрушении или упрочнении
	 Material[1].sigma1 = 0.07 * GPa;
	 Material[2].sigma1 = 1.66 * GPa;
	 Material[3].sigma1 = 0.007 * GPa;
	 Material[4].sigma1 = 0.07 * GPa;
	 Material[5].sigma1 = 0.009 * GPa;
	 Material[6].sigma1 = 0.00012 * GPa;
	 Material[7].sigma1 = 0.07 * GPa;
	 Material[8].sigma1 = 0.00007 * GPa;
	 Material[9].sigma1 = 0.00001 * GPa;
	 Material[9].sigma1 = 0.007 * GPa;

	 // Цвета материалов при выводе анимации
	 Material[1].Color = clNavy;
	 Material[2].Color = clGreen;
	 Material[3].Color = clLime;
	 Material[4].Color = clSilver;
	 Material[5].Color = clPurple;
	 Material[6].Color = clOlive;
	 Material[7].Color = clLtGray;
	 Material[8].Color = clGray;
	 Material[9].Color = clWhite;
	 Material[10].Color = clBlue;

	 // Это, наверное, теплопроводность... Или нет...
	 Material[1].ctep = 210;
	 Material[2].ctep = 58;
	 Material[3].ctep = 3.49;
	 Material[4].ctep = 2.91;
	 Material[5].ctep = 2.3;
	 Material[6].ctep = 2.4;
	 Material[7].ctep = 0.1;
	 Material[8].ctep = 0.8;
	 Material[9].ctep = 0.0;
	 Material[10].ctep = 1.4;

	 // Коэффициент температурного расширения
	 Material[1].gammatep = 22.2e-6;
	 Material[2].gammatep = 13e-6;
	 Material[3].gammatep = 8e-6;
	 Material[4].gammatep = 8e-6;
	 Material[5].gammatep = 8e-6;
	 Material[6].gammatep = 8e-6;
	 Material[7].gammatep = 27.8e-6;
	 Material[8].gammatep = 11.6e-6;
	 Material[9].gammatep = 0.0;
	 Material[10].gammatep = 14.5e-6;
	 */
	/*
	 // (2015 год) Для будущей загрузки материалов.
	 struct SaveDefaultMatirials
	 {
	 ofstream out;
	 SaveDefaultMatirials(): out( "./defaultMaterials.txt" ) {;}
	 void operator()( TMaterial mats[], int size )
	 {
	 for( int i = 1; i < size; ++i )
	 {
	 out << "// Material: " << i << endl;
	 out << "ro0 \t= "		<< mats[ i ].ro0		<< endl;
	 out << "G \t= "			<< mats[ i ].G			<< endl;
	 out << "sigma0 \t= "	<< mats[ i ].sigma0		<< endl;
	 out << "k1 \t= "		<< mats[ i ].k1			<< endl;
	 out << "k \t= "			<< mats[ i ].k			<< endl;
	 out << "alpha \t= "		<< mats[ i ].alpha		<< endl;
	 out << "sigma1 \t= "	<< mats[ i ].sigma1		<< endl;
	 out << "Color \t= "		<< mats[ i ].Color		<< endl;
	 //out << "lmb \t= "		<< mats[ i ].lmb		<< endl; больше не нужны
	 //out << "mu \t= "		<< mats[ i ].mu			<< endl;
	 out << "ctep \t= "		<< mats[ i ].ctep		<< endl;
	 out << "gammatep \t= "	<< mats[ i ].gammatep	<< endl;
	 out << endl;
	 }
	 }
	 } sdm;
	 sdm( Material, 11 );

	 // *******************************************************************
	 // (2015 год) Переписать!!! // (2015 год) Переписать!!!
	 // (2015 год) Переписать!!! // (2015 год) Переписать!!!
	 FILE *F;
	 if (FileExists("MatBase.dat"))
	 {
	 F = fopen("MatBase.dat", "rb");
	 do
	 {
	 fread(&Material[MatCount], sizeof(TMaterial), 1, F);
	 if (feof(F))
	 break;
	 matstrat0Box->Items->Add(Material[MatCount].Name);
	 matstrat1Box->Items->Add(Material[MatCount].Name);
	 matstrat2Box->Items->Add(Material[MatCount].Name);
	 matstrat3Box->Items->Add(Material[MatCount].Name);
	 MatCount++;
	 }
	 while (true);
	 fclose(F);
	 }
	 jjjjBox->ItemIndex = 0;
	 matstrat0Box->ItemIndex = 3;
	 nstratBox->ItemIndex = 0;
	 matstrat1Box->ItemIndex = 4;
	 matstrat2Box->ItemIndex = 2;
	 matstrat3Box->ItemIndex = 1; */
}

// ---------------------------------------------------------------------------

void __fastcall TmainForm::jjjjBoxChange(TObject *) {
	if (jjjjBox->ItemIndex == 5) {
		tEdit->Enabled = true;
		Label6->Enabled = true;
	}
	else {
		tEdit->Enabled = false;
		Label6->Enabled = false;
	}
}

// ---------------------------------------------------------------------------
void __fastcall TmainForm::GetBeginValue() {
	for (int i = 0; i < nel; i++) {
		srr[i] = szz[i] = srz[i] = stt[i] = epsrr[i] = epszz[i] = epsrz[i] = epstt[i] = matelm[i] = epsrrp[i] = epszzp[i] =
			epsrzp[i] = epsttp[i] = sigmarr[i] = sigmazz[i] = sigmarz[i] = sigmatt[i] = ener[i] = I2p[i] = 0.;
	}
	for (int i = 0; i < nus; i++) {
		speedr[i] = speedz[i] = nearel[i] = 0.;
	}
	timepr = 0.;
	// **************************************************************
	// (2015 год) Переписать в виде цикла
	/* for (int i = 0; i < numSeries; ++i)
	 graficForm->Series[i]->ShowInLegend = false; */
	// *************************************************************
	alf = StrToFloat(alfEdit->Text); // Введённая альфа
	c0 = StrToFloat(c0Edit->Text); // Коэффициент квадратичной псевдовязкости
	cl = StrToFloat(clEdit->Text); // Коэффициент линейной псевдовязкости
	ca = StrToFloat(caEdit->Text); // Коэффициент сдвиговой вязкости
	jjjj = jjjjBox->ItemIndex + 1; // Условия закрепления (0-5) переводим в (1-6)
	t = StrToInt(tEdit->Text); // ??? Выясняется // (2015 год) 0_0 - я, 8_8 - мой мозг, *_* - моё сознание
	nt = StrToInt(ntEdit->Text); // Число разбиений по времени (сек)
	dtimepr = StrToFloat(dtimeprEdit->Text) / nt; // Интервал времени, поделённый на число разбиений,
	// то есть длина одного временного шага
	vindent = StrToFloat(vindentEdit->Text); // Скорость нижней волны (м/с)
	vb = StrToFloat(Editb->Text); // Скорость боковой волны (м/с)
	inss = StrToFloat(Editinss->Text); // Скорость внутренней волны (м/с)
	bsh = StrToFloat(Editbsh->Text); // Скорость удара индентора (м/с)
	radius0 = StrToFloat(rad0Edit->Text); // Радиус сооружения (м)
	radius1 = StrToFloat(rad1Edit->Text); // Радиус основания (м)
	h0 = StrToFloat(h0Edit->Text); // Высота сооружения (м)
	n1 = EnsureRange(StrToInt(n1Edit->Text), 3, 30); // Число разбиений по высоте сооружения
	n3 = EnsureRange(StrToInt(n3Edit->Text), 3, 30); // Число разбиений по радиусу сооружения
	matstrat0 = matstrat0Box->ItemIndex; // + 1;// Материал сооружения (0-9) переводим в (1-10)
	nstrat = nstratBox->ItemIndex + 1; // Число слоёв основания (0-2) переводим в (1-3)
	h2i[1] = StrToFloat(h2iEdit1->Text); // Высота первого слоя (м)
	h2i[2] = StrToFloat(h2iEdit2->Text); // Высота второго слоя (м)
	h2i[3] = StrToFloat(h2iEdit3->Text); // Высота третьего слоя (м)
	matstrat[1] = matstrat1Box->ItemIndex; // + 1; // Материал первого слоя (0-9) переводим в (1-10)
	matstrat[2] = matstrat2Box->ItemIndex; // + 1; // Материал второго слоя (0-9) переводим в (1-10)
	matstrat[3] = matstrat3Box->ItemIndex; // + 1; // Материал третьего слоя (0-9) переводим в (1-10)
}

// ---------------------------------------------------------------------------

void __fastcall TmainForm::CheckBoxb2Click(TObject *) {
	if (CheckBoxb2->Checked) {
		// vb = StrToFloat(Editb->Text);
		CheckBoxbs->Checked = false;
		CheckBoxb->Checked = false;
		vb2 = StrToFloat(Editb2->Text);
		tbs = StrToInt(InputBox((UTF8String)"Ввод времени старта первой волны", "t =", "0"));
		tbc = StrToInt(InputBox((UTF8String)"Ввод времени окончания первой волны", "t =", "5"));
		tbs2 = StrToInt(InputBox((UTF8String)"Ввод времени старта второй волны", "t =", "5"));
		tbc2 = StrToInt(InputBox((UTF8String)"Ввод времени окончания второй волны", "t =", "10"));
	}
}
// ---------------------------------------------------------------------------

void __fastcall TmainForm::CheckBoxn2Click(TObject *) {
	if (CheckBoxn2->Checked) {
		CheckBoxns->Checked = false;
		CheckBoxn->Checked = false;
		CheckBoxno2->Checked = false;
		CheckBoxnp1->Checked = false;
		CheckBoxnp2->Checked = false;
		CheckBoxnp3->Checked = false;
		vn2 = StrToFloat(Editn2->Text);
		tns = StrToInt(InputBox((UTF8String)"Ввод времени старта первой волны", "t =", "0"));
		tnc = StrToInt(InputBox((UTF8String)"Ввод времени окончания первой волны", "t =", "5"));
		tns2 = StrToInt(InputBox((UTF8String)"Ввод времени старта второй волны", "t =", "5"));
		tnc2 = StrToInt(InputBox((UTF8String)"Ввод времени окончания второй волны", "t =", "10"));
	}
}
// ---------------------------------------------------------------------------

void __fastcall TmainForm::CheckBoxno2Click(TObject *) {
	if (CheckBoxno2->Checked) {
		CheckBoxns->Checked = false;
		CheckBoxn->Checked = false;
		CheckBoxn2->Checked = false;
		CheckBoxnp1->Checked = false;
		CheckBoxnp2->Checked = false;
		CheckBoxnp3->Checked = false;
		vn2 = StrToFloat(Editn2->Text);
		tnc = StrToInt(InputBox((UTF8String)"Ввод времени окончания первой волны", "t =", "5"));
		tnc2 = StrToInt(InputBox((UTF8String)"Ввод времени окончания второй волны", "t =", "10"));
	}
}
// ---------------------------------------------------------------------------

void __fastcall TmainForm::CheckBoxnp3Click(TObject *) {
	if (CheckBoxnp3->Checked) {
		CheckBoxns->Checked = false;
		CheckBoxn->Checked = false;
		CheckBoxn2->Checked = false;
		CheckBoxnp2->Checked = false;
		CheckBoxno2->Checked = false;
		CheckBoxnp1->Checked = false;
		vn2 = StrToFloat(Editn2->Text);
	}
}
// ---------------------------------------------------------------------------

void __fastcall TmainForm::CheckBoxinssClick(TObject *) {
	if (CheckBoxinss->Checked)
		inss = StrToFloat(Editinss->Text);
}

// ---------------------------------------------------------------------------
void __fastcall TmainForm::CheckBoxbshClick(TObject *) {
	if (CheckBoxbsh->Checked || BBCBox->Checked)
		bsh = StrToFloat(Editbsh->Text);
}
// ---------------------------------------------------------------------------

void __fastcall TmainForm::nstratBoxChange(TObject *) {
	int l = nstratBox->ItemIndex;
	bool E2(l), E3(l && (l - 1));
	matstrat2Box->Enabled = E2;
	h2iEdit2->Enabled = E2;
	Label23->Enabled = E2;
	Label20->Enabled = E2;
	matstrat3Box->Enabled = E3;
	h2iEdit3->Enabled = E3;
	Label24->Enabled = E3;
	Label21->Enabled = E3;
}

// ---------------------------------------------------------------------------

void __fastcall TmainForm::Button3Click(TObject *) {
	UnicodeString path = ExtractFilePath(DirEdit->Text);
	Vcl::Filectrl::SelectDirectory(path, TSelectDirOpts() << sdAllowCreate << sdPerformCreate << sdPrompt, 0);
	if (path.LastChar() != ((UnicodeString)("\\")).LastChar())
		path += "\\";
	DirEdit->Text = path;
}

// ---------------------------------------------------------------------------

void __fastcall TmainForm::CheckBoxbClick(TObject *) {
	if (CheckBoxb->Checked) {
		// vb = StrToFloat(Editb->Text);
		CheckBoxbs->Checked = false;
		CheckBoxb2->Checked = false;
	}
}
// ---------------------------------------------------------------------------

void __fastcall TmainForm::CheckBoxbsClick(TObject *) {
	if (CheckBoxbs->Checked) {
		// vb = StrToFloat(Editb->Text);
		CheckBoxb->Checked = false;
		CheckBoxb2->Checked = false;
	}
}
// ---------------------------------------------------------------------------

void __fastcall TmainForm::CheckBoxnClick(TObject *) {
	if (CheckBoxn->Checked) {
		CheckBoxns->Checked = false;
		CheckBoxn2->Checked = false;
		CheckBoxno2->Checked = false;
		CheckBoxnp1->Checked = false;
		CheckBoxnp2->Checked = false;
		CheckBoxnp3->Checked = false;
	}
}
// ---------------------------------------------------------------------------

void __fastcall TmainForm::CheckBoxnsClick(TObject *) {
	if (CheckBoxns->Checked) {
		CheckBoxn->Checked = false;
		CheckBoxn2->Checked = false;
		CheckBoxno2->Checked = false;
		CheckBoxnp1->Checked = false;
		CheckBoxnp2->Checked = false;
		CheckBoxnp3->Checked = false;
	}
}
// ---------------------------------------------------------------------------

void __fastcall TmainForm::CheckBoxnp1Click(TObject *) {
	if (CheckBoxnp1->Checked) {
		CheckBoxns->Checked = false;
		CheckBoxn->Checked = false;
		CheckBoxn2->Checked = false;
		CheckBoxnp2->Checked = false;
		CheckBoxno2->Checked = false;
		CheckBoxnp3->Checked = false;
	}
}
// ---------------------------------------------------------------------------

void __fastcall TmainForm::CheckBoxnp2Click(TObject *) {
	if (CheckBoxnp2->Checked) {
		CheckBoxns->Checked = false;
		CheckBoxn->Checked = false;
		CheckBoxn2->Checked = false;
		CheckBoxnp1->Checked = false;
		CheckBoxno2->Checked = false;
		CheckBoxnp3->Checked = false;
	}
}
// ---------------------------------------------------------------------------

void __fastcall TmainForm::CheckBox4Click(TObject *) {
	if (CheckBox4->Checked) {
		CheckBox3->Checked = false;
		Label17->Caption = (UTF8String)"высоты слоёв основания";
		Label11->Caption = (UTF8String)"радиус основания";
		AltInpCBox->Enabled = true;
		InputEdit1->Enabled = true;
		// h2iEdit1->Text = "0.006";
		// rad1Edit->Text = "0.009";
		// CheckBox3->State = cbUnchecked;
	}
	else {
		CheckBox3->Checked = true;
		Label17->Caption = (UTF8String)"Толщина кольца слоя основания";
		Label11->Caption = (UTF8String)"Высота основания";
		InputEdit1->Enabled = false;
		AltInpCBox->Enabled = false;
	}
}
// ---------------------------------------------------------------------------

void __fastcall TmainForm::CheckBox3Click(TObject *) {
	if (CheckBox3->Checked) {
		CheckBox4->Checked = false;
		Label17->Caption = (UTF8String)"Толщина кольца слоя основания";
		Label11->Caption = (UTF8String)"Высота основания";
		// h2iEdit1->Text = "0.009";
		// rad1Edit->Text = "0.006";
		// CheckBox4->State = cbUnchecked;
	}
	else {
		CheckBox4->Checked = true;
		Label17->Caption = (UTF8String)"высоты слоёв основания";
		Label11->Caption = (UTF8String)"радиус основания";
	}
}

// ---------------------------------------------------------------------------
void __fastcall TmainForm::CheckBoxStakanClick(TObject *) {
	if (CheckBoxStakan->Checked) {
		Label29->Visible = true;
		ComboBoxBuild->Visible = true;
	}
	else {
		Label29->Visible = false;
		ComboBoxBuild->Visible = false;
	}

}

// ---------------------------------------------------------------------------
void __fastcall TmainForm::FormClose(TObject *, TCloseAction &) {
	// throw(1);
	UnlimStop = true;
	Application->Terminate();
	// Application->Free();
}
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------

void __fastcall TmainForm::Button4Click(TObject *Sender) {
	TForm1* form = new TForm1(this);
	form->matarr.set_length(Material.Length);
	for (int i = 0; i < Material.Length; ++i)
		form->matarr[i] = Material[i];
	form->ReinitList();
	form->ShowModal();
	Material.set_length(form->matarr.Length);
	for (int i = 0; i < Material.Length; ++i)
		Material[i] = form->matarr[i];
	delete form;
	ReinitBoxes();
}
// ---------------------------------------------------------------------------

void __fastcall TmainForm::CheckBox5Click(TObject *Sender) {
	BeautyCBox->Enabled = CheckBox5->Checked;
}
// ---------------------------------------------------------------------------

void __fastcall TmainForm::ntEditChange(TObject *Sender) {;
}

// ---------------------------------------------------------------------------
void __fastcall TmainForm::LineButtonClick(TObject *Sender) {
	TBitmap *bmp = new TBitmap();
	bmp->PixelFormat = pf24bit;
	bmp->SetSize((int)T_max + 20, 87);
	holst = bmp->Canvas;
	int x = 10, y = 10;
	holst->MoveTo(x, y);
	for (long double i = 0; i < T_max; i -= -1.) // Муа-ха-ха-ха
	{
		holst->Pen->Color = TempToColor(i, BWCBox->Checked);
		holst->LineTo(x++, y + 30);
		holst->MoveTo(x, y);
	}
	holst->Pen->Color = clBlack;
	holst->MoveTo(++x, y - 2);
	holst->LineTo(8, y - 2);
	holst->LineTo(8, y + 31);
	holst->LineTo(x, y + 31);
	holst->LineTo(x, y - 2);
	holst->Font->Name = "Times New Roman";
	holst->Font->Size = 26;
	holst->TextOutW(5, 45, GetScPref(0, 0, "K"));
	holst->TextOutW((int)T_max + 15 - holst->TextWidth(GetScPref(T_max, 0, "K")), 45, GetScPref(T_max, 0, "K"));
	if (!Sysutils::DirectoryExists(DirToResDir(DirEdit->Text)))
		MkDir(DirToResDir(DirEdit->Text));
	SaveAsPNG(bmp, DirToResDir(DirEdit->Text) + ((BWCBox->Checked) ? "bwline.png" : "colorline.png"));
	delete bmp;
}
// ---------------------------------------------------------------------------

void __fastcall TmainForm::StopRFClick(TObject *) {
	UnlimStop = true;
}

void __fastcall TmainForm::SetFormState(bool enabled) {
	alfEdit->Enabled = enabled;
	c0Edit->Enabled = enabled;
	clEdit->Enabled = enabled;
	caEdit->Enabled = enabled;
	jjjjBox->Enabled = enabled;
	jjjjBoxChange(this);
	dtimeprEdit->Enabled = enabled;
	ntEdit->Enabled = enabled;
	rad0Edit->Enabled = enabled;
	rad1Edit->Enabled = enabled;
	n3Edit->Enabled = enabled;
	h0Edit->Enabled = enabled;
	n1Edit->Enabled = enabled;
	matstrat0Box->Enabled = enabled;
	nstratBox->Enabled = enabled;
	h2iEdit1->Enabled = enabled;
	h2iEdit2->Enabled = enabled;
	h2iEdit3->Enabled = enabled;
	matstrat1Box->Enabled = enabled;
	matstrat2Box->Enabled = enabled;
	matstrat3Box->Enabled = enabled;
	nstratBoxChange(this);
	Button4->Enabled = enabled;
	vindentEdit->Enabled = enabled;
	Editb->Enabled = enabled;
	Edits->Enabled = enabled;
	Editn2->Enabled = enabled;
	Editb2->Enabled = enabled;
	Editinss->Enabled = enabled;
	Editbsh->Enabled = enabled;
	RadioGroup1->Enabled = enabled;
	CheckBox3->Enabled = enabled;
	CheckBox4->Enabled = enabled;
	ComboBoxBuild->Enabled = enabled;
	CheckBoxn->Enabled = enabled;
	CheckBoxn2->Enabled = enabled;
	CheckBoxns->Enabled = enabled;
	CheckBoxnp1->Enabled = enabled;
	CheckBoxnp2->Enabled = enabled;
	CheckBoxnp3->Enabled = enabled;
	CheckBoxno2->Enabled = enabled;
	CheckBoxb->Enabled = enabled;
	CheckBoxb2->Enabled = enabled;
	CheckBoxbs->Enabled = enabled;
	CheckBoxs->Enabled = enabled;
	CheckBoxinss->Enabled = enabled;
	CheckBoxbsh->Enabled = enabled;
	BBCBox->Enabled = enabled;
	Button3->Enabled = enabled;
	DirEdit->Enabled = enabled;
	CinemaCBox->Enabled = enabled;
	CinemaEdit->Enabled = enabled;
	CheckBoxStakan->Enabled = enabled;
	InputEdit1->Enabled = enabled;
	AltInpCBox->Enabled = enabled;
	CBoxPoints->Enabled = enabled;
	MQCButton->Enabled = enabled;
	if (enabled) {
		Refresh->Caption = "Пуск";
		Refresh->OnClick = &RefreshClick;
	}
	else {
		Refresh->Caption = "Стоп";
		Refresh->OnClick = &StopRFClick;
	}
}

void __fastcall TmainForm::MQCButtonClick(TObject *Sender) {
	MQCForm->ShowModal();
}
// ---------------------------------------------------------------------------

void __fastcall TmainForm::SetUS() {
	UnlimStop = true;
}

void __fastcall TmainForm::ResetUS() {
	UnlimStop = false;
}

void __fastcall TmainForm::SetMaterials(DynamicArray<TMaterial> *mat) {
	Material.set_length(mat->Length + 1);
	for (int i = 0; i < mat->Length; ++i)
		Material[i + 1] = (*mat)[i];
	ReinitBoxes();
}
