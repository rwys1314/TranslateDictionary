#ifndef TUVUNG_H
#define TUVUNG_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <stdexcept>
using namespace std;

// ============================================================
//  STRUCT CHÍNH (1)
// ============================================================
struct TuVung {
    string word;           // Tu tieng Anh
    string pronunciation;  // Phien am IPA
    string type;           // n / v / adj / adv
    string meaning;        // Nghia tieng Viet
    string example;        // Cau vi du
    bool   favorite;       // true = danh dau yeu thich
};

struct TuDien {
    TuVung* data;
    int soLuong;
    int dungLuong;
};

// ============================================================
//  KHOI TAO & GIAI PHONG (2)
// ============================================================
void khoiTao   (TuDien& td, int dungLuongBanDau = 10);
void giaiPhong (TuDien& td);
void moRong    (TuDien& td);   // Goi khi mang day

// ============================================================
//  CRUD (2)
// ============================================================
void themTuVung     (TuDien& td, const TuVung& tv);
void hienThiTatCa   (const TuDien& td);
void hienThiChiTiet (const TuVung& tv);
bool suaTuVung      (TuDien& td, int viTri, const TuVung& tvMoi);
bool xoaTuVung      (TuDien& td, int viTri);

// ============================================================
//  TIM KIEM & SAP XEP (2)
// ============================================================
void sapXepTheoAlphabet (TuDien& td);
int  BinarySearch       (const TuDien& td, const string& word);
void timKiem            (const TuDien& td, const string& keyword);

// ============================================================
//  YEU THICH & QUIZ (2)
// ============================================================
void danhDauYeuThich (TuDien& td, int viTri);
void hienThiYeuThich (const TuDien& td);
void quizNgauNhien   (const TuDien& td);
void hienThiThongKe  (const TuDien& td);

// ============================================================
//  DOC / GHI FILE (3)
// ============================================================
void docFile       (TuDien& td, const string& tenFile);
void ghiFile       (const TuDien& td, const string& tenFile);
void xuatYeuThich  (const TuDien& td, const string& tenFile);

// ============================================================
//  VALIDATION & UI (3)
// ============================================================
int    nhapSoNguyen (const string& thongBao, int min = 0, int max = 9999);
string nhapChuoi    (const string& thongBao);
void   veKhung      (const string& tieuDe);
void   pauseScreen  ();
void   hienThiMenu  ();

#endif
