#ifndef TUVUNG_H
#define TUVUNG_H

#include <iostream>
#include <fstream> // Dùng cho file
#include <iomanip> // Dùng cho setw và left
#include <string>
#include <stdexcept>  // Dùng cho try-catch
using namespace std;

// ============================================================
//  STRUCT CHÍNH (1)
// ============================================================
struct TuVung {
    string word;           // Từ tiếng Anh
    string pronunciation;  // Phiên âm IPA
    string type;           // n / v / adj / adv
    string meaning;        // Nghĩa tiếng Việt
    string example;        // Câu ví dụ
    bool   favorite;       // true = đánh dấu yêu thích
};

struct TuDien {
    TuVung* data;
    int soLuong;
    int dungLuong;

    // Recent search
    string lichSu[10];
    int soLichSu;

    // Thống kê quiz
    int tongSoCauQuiz;
    int tongSoCauDung;
};

// ============================================================
//  KHỞI TẠO & GIẢI PHÓNG (2)
// ============================================================
void khoiTao   (TuDien& td, int dungLuongBanDau = 10);
void giaiPhong (TuDien& td);
void moRong    (TuDien& td);   // Gọi khi mảng đầy

// ============================================================
//  CRUD (2)
// ============================================================
void themTuVung     (TuDien& td, const TuVung& tv);
void hienThiTatCa   (const TuDien& td);
void hienThiChiTiet (const TuVung& tv);
bool suaTuVung      (TuDien& td, int viTri, const TuVung& tvMoi);
bool xoaTuVung      (TuDien& td, int viTri);

// ============================================================
//  TÌM KIẾM & SẮP XẾP (2)
// ============================================================
void sapXepTheoAlphabet (TuDien& td);
int  BinarySearch       (const TuDien& td, const string& word);
void timKiem            (TuDien& td, const string& keyword);

// ============================================================
// LỊCH SỬ (2)
// ============================================================
void themLichSu    (TuDien& td, const string& word);
void hienThiLichSu (const TuDien& td);

// ============================================================
//  YÊU THÍCH & QUIZ (2)
// ============================================================
void danhDauYeuThich (TuDien& td, int viTri);
void hienThiYeuThich (const TuDien& td);
void quizNgauNhien   (TuDien& td);
void hienThiThongKe  (const TuDien& td);

// ============================================================
//  ĐỌC/GHI FILE (3)
// ============================================================
void docFile       (TuDien& td, const string& tenFile);
void ghiFile       (const TuDien& td, const string& tenFile);
void xuatYeuThich  (const TuDien& td, const string& tenFile);
void docThongKe    (TuDien& td, const string& tenFile);
void ghiThongKe    (const TuDien& td, const string& tenFile);

// ============================================================
//  VALIDATION & UI (3)
// ============================================================
int    nhapSoNguyen (const string& thongBao, int min = 0, int max = 9999);
string nhapChuoi    (const string& thongBao);
void   veKhung      (const string& tieuDe);
void   pauseScreen  ();
void   hienThiMenu  ();

#endif
