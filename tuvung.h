#ifndef TUVUNG_H
#define TUVUNG_H

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
using namespace std;

// ============================================================
//  STRUCT CHÍNH (Leader)
// ============================================================

struct TuVung {
    string word;           // Tu tieng Anh
    string pronunciation;  // Phien am IPA
    string type;           // n / v / adj / adv
    string meaning;        // Nghia tieng Viet
    string example;        // Cau vi du tieng Anh + dich
    bool   favorite;       // true = danh dau tu kho
};

struct TuDien {
    TuVung* data;          // Mang dong - BAT BUOC
    int soLuong;           // So tu hien co
    int dungLuong;         // Kich thuoc mang hien tai
};

// ============================================================
//  KHOI TAO & GIAI PHONG (Leader)
// ============================================================
void khoiTao(TuDien& td, int dungLuongBanDau = 10);
void giaiPhong(TuDien& td);
void moRong(TuDien& td);       // Tu dong goi khi mang day

// ============================================================
//  CRUD  (Developer)
// ============================================================
void themTuVung(TuDien& td, const TuVung& tv);
void hienThiTatCa(const TuDien& td);
void hienThiChiTiet(const TuVung& tv);
bool suaTuVung(TuDien& td, int viTri, const TuVung& tvMoi);
bool xoaTuVung(TuDien& td, int viTri);

// ============================================================
//  TIM KIEM & SAP XEP  (Leader)
// ============================================================
void sapXepTheoAlphabet(TuDien& td);
int  BinarySearch(const TuDien& td, const string& word);
void timKiem(const TuDien& td, const string& keyword);

// ============================================================
//  YEU THICH & QUIZ  (Developer)
// ============================================================
void danhDauYeuThich(TuDien& td, int viTri);
void hienThiYeuThich(const TuDien& td);
void quizNgauNhien(TuDien& td);
void hienThiThongKe(const TuDien& td);

// ============================================================
//  DOC / GHI FILE  (Tester & Documenter)
// ============================================================
void docFile(TuDien& td, const string& tenFile);
void ghiFile(const TuDien& td, const string& tenFile);
void xuatYeuThich(const TuDien& td, const string& tenFile);

// ============================================================
//  VALIDATION & UI  (Tester & Documenter)
// ============================================================
int    nhapSoNguyen(const string& thongBao, int min, int max);
string nhapChuoi(const string& thongBao);
void   veKhung(const string& tieu_de);
void   pause();
void   hienThiMenu();

#endif
