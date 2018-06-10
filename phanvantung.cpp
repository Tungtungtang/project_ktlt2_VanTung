/* tac gia: Phan Van Tung
phan cong: ham phieu muon */
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <conio.h>
#include <list>
#include <sstream>
#include <iomanip>
#include "Admin.h"
#include "GiaoVien.h"
#include "SinhVien.h"
#include "PhieuMuon.h"
#include "Sach.h"
using namespace std;
int PhieuMuon::nTongPM = 0;
//nguyen mau ham 
void inputData_PhieuMuon(list <PhieuMuon> &L4);
void them_PhieuMuon(list <PhieuMuon> &L4, list <BanDoc*> L2, list <Sach> &L3);
void outputData_PhieuMuon_ToScreen(list <PhieuMuon> L4);
void outputData_PhieuMuon_File(list <PhieuMuon> L4, list <BanDoc*> L2, list <Sach> L3);
int demTongPhieuMuon(list <PhieuMuon> L4);
void traSach_PhieuMuon(list <PhieuMuon> &L4, list <BanDoc*> L2, list <Sach> &L3);
void lietKeSach1BanDocDangMuon(list <PhieuMuon> L4, list <Sach> L3);
bool ktrHetHanMuon(int nNgayTra, int nThangTra, int nNamTra, int nNgayHienTai, int nThangHienTai, int nNamHienTai);
void xuat_DS_PM_HetHanMuonSach(list <PhieuMuon> L4);
//dinh nghia ham con
int demTongPhieuMuon(list <PhieuMuon> L4)
{
	int nDem = 0;
	list <PhieuMuon> ::iterator p = L4.begin();
	while(p != L4.end())
	{
		nDem++;
		p++;
	}
	return nDem;
}
void them_PhieuMuon(list <PhieuMuon> &L4, list <BanDoc*> L2, list <Sach> &L3)
{
	string sMBD = "";
	while(true)
	{
		system("cls");
		textColor(4);
		cout << "\t\tNhap N de thoat!\n";
		textColor(7);
		cout << "\t\tNhap ma ban doc can muon sach: ";
		fflush(stdin);
		getline(cin, sMBD);
		if (sMBD == "")
		{
			textColor(4);
			cout << "Khong duoc de trong ! \n";
			textColor(7);
			system("pause");
		}
		else if (sMBD == "N")
		{
			textColor(10);
			cout << "\t\tBan chon thoat!\n";
			textColor(7);
			return;
		}
		else if (kiemTraBD(L2, sMBD) != true)
		{
			textColor(4);
			cout << "\t\tMa ban doc khong ton tai!\n";
			textColor(7);
			system("pause");
		}
		else
		{
			break;
		}
	}
	string sMS = "";
	while(true)
	{
		cout << "\t\tNhap ma sach: ";
		fflush(stdin);
		getline(cin, sMS);
		if (sMS == "")
		{
			textColor(4);
			cout << "Khong duoc de trong ! \n";
			textColor(7);
			system("pause");
		}
		else if (kiemTraSach_DuTieuChuanMuon(L3, sMS) == true)
		{
			break;
		}
		else 
		{
			textColor(4);
			cout << "\t\tMa sach khong ton tai! hoac dang co ban doc muon.\n";
			textColor(7);
			system("pause");
		}	
	}
	PhieuMuon pm(sMBD, sMS);
	L4.push_back(pm);
	textColor(10);
	cout << "\t\tTao phieu muon thanh cong!\n";
	textColor(7);
	ofstream File;
	File.open("PhieuMuon.txt", ios::app);
	File << "\n" << L4.rbegin()->getMaPM() << "," << L4.rbegin()->getBanDoc().getMBD() << "," << L4.rbegin()->getSach().getMS() << "," << L4.rbegin()->getNgayMuon().getNgay() << "," << L4.rbegin()->getNgayMuon().getThang() << "," << L4.rbegin()->getNgayMuon().getNam() << ","  << L4.rbegin()->getNgayTra().getNgay() << "," << L4.rbegin()->getNgayTra().getThang() << "," << L4.rbegin()->getNgayTra().getNam() << "," << L4.rbegin()->getTrangThai();
	File.close();
	int nTT = L4.rbegin()->getMaPM(); // trang thai
	list <Sach> ::iterator p = L3.begin();
	while(p != L3.end())
	{
		if (p->getMS() == sMS)
		{
			p->setTT(nTT);// tinh trang
			break;
		}
		p++;
	}
	outputData_Sach_File(L3);

}
void outputData_PhieuMuon_File(list <PhieuMuon> L4, list <BanDoc*> L2, list <Sach> L3)
{
	
	int nTongPM = demTongPhieuMuon(L4);
	int nDem = 1;
	ofstream File;
	File.open("PhieuMuon.txt");
	list <PhieuMuon> ::iterator p = L4.begin();
	while (p != L4.end())
	{
		File << p->getMaPM() << "," << p->getBanDoc().getMBD() << "," << p->getSach().getMS() << "," << p->getNgayMuon().getNgay() << "," << p->getNgayMuon().getThang() << "," << p->getNgayMuon().getNam() << "," << p->getNgayTra().getNgay() << "," << p->getNgayTra().getThang() << "," << p->getNgayTra().getNam() << "," << p->getTrangThai();
		if (nDem < nTongPM)
		{
			File << endl;
			nDem++;
		}
		p++;
	}
	File.close();
}
void outputData_PhieuMuon_ToScreen(list <PhieuMuon> L4)
{
	list <PhieuMuon> ::iterator p = L4.begin();
	while(p != L4.end())
	{
		p->xuat();
		p++;
	}
}
void inputData_PhieuMuon(list <PhieuMuon> &L4)
{
	int nSPM = 0;
	string sMBD = "";
	string sMS = "";
	int nNgayMuon = 0;
	int nThangMuon = 0;
	int nNamMuon = 0;
	int nNgayTra = 0;
	int nThangTra = 0;
	int nNamTra = 0;
	int nTrangThai = 0;
	ifstream File;
	File.open("PhieuMuon.txt");
	while(!File.eof())
	{
		File >> nSPM;
		File.ignore(1, ',');
		getline(File, sMBD, ',');
		getline(File, sMS, ',');
		File >> nNgayMuon;
		File.ignore(1, ',');
		File >> nThangMuon;
		File.ignore(1, ',');
		File >> nNamMuon;
		File.ignore(1, ',');
		File >> nNgayTra;
		File.ignore(1, ',');
		File >> nThangTra;
		File.ignore(1, ',');
		File >> nNamTra;
		File.ignore(1, ',');
		File >> nTrangThai;
		File.ignore(1, '\n');
		PhieuMuon pm(nSPM, sMBD,sMS,nNgayMuon,nThangMuon,nNamMuon,nNgayTra,nThangTra,nNamTra,nTrangThai);
		L4.push_back(pm);
	}
	File.close();
}