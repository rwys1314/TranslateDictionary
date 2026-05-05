#include "tuvung.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>
using namespace std;

// ============================================================
//  GHI FILE
// ============================================================
void ghiFile(const TuDien& td, const string& tenFile) {
    try {
        ofstream f(tenFile);

        if (!f.is_open()) {
            cout << "Khong mo duoc file de ghi!";
            return;
        }

        for (int i = 0; i < td.soLuong; i++) {
            const TuVung& tv = td.data[i];

            f << tv.word << "|"
              << tv.pronunciation << "|"
              << tv.type << "|"
              << tv.meaning << "|"
              << tv.example << "|"
              << tv.favorite << "\n";
        }

        f.close();
        cout << "  ✓ Da luu file thanh cong!" << endl;
    }
    catch (const exception& e) {
        cout << " Loi ghi file: " << e.what() << endl;
    }
}

// ============================================================
//  ĐỌC FILE
// ============================================================
void docFile(TuDien& td, const string& tenFile) {
    try {
        ifstream f(tenFile);
        if (!f.is_open()) return;

        string line;
        td.soLuong = 0; // Reset số lượng trước khi đọc

        while (getline(f, line)) { // Đọc từng dòng cho đến hết file
            if (line.empty()) continue;

            stringstream ss(line);
            TuVung tv;
            string fav;

            getline(ss, tv.word, '|');
            getline(ss, tv.pronunciation, '|');
            getline(ss, tv.type, '|');
            getline(ss, tv.meaning, '|');
            getline(ss, tv.example, '|');
            getline(ss, fav, '|');

            tv.favorite = (fav == "1");
            themTuVung(td, tv); // Hàm này sẽ tự lo việc moRong() mảng[cite: 5]
        }
        f.close();
        cout << " ✓ Da tai " << td.soLuong << " tu tu file!" << endl;
    }
    catch (const exception& e) {
        cout << " Loi doc file: " << e.what() << endl;
    }
}

// ============================================================
//  XUẤT YÊU THÍCH
// ============================================================
void xuatYeuThich(const TuDien& td, const string& tenFile) {
    try {
        ofstream f(tenFile);

        if (!f.is_open()) {
            cout << "Khong mo duoc file de ghi!";
            return;
        }

        int dem = 0;
        for (int i = 0; i < td.soLuong; i++) {
            const TuVung& tv = td.data[i];

            if (tv.favorite) {
                f << tv.word << "|"
                  << tv.pronunciation << "|"
                  << tv.type << "|"
                  << tv.meaning << "|"
                  << tv.example << "|"
                  << tv.favorite << endl;

                dem++;
            }
        }

        f.close();

        if (dem == 0) {
            cout << " Khong co tu yeu thich de xuat\n";
        } else {
            cout << " ✓ Da xuat " << dem << " tu yeu thich ra file!\n";
        }
    }
    catch (const exception& e) {
        cout << " Loi xuat yeu thich: " << e.what() << endl;
    }
}

// ============================================================
//  GHI THỐNG KÊ
// ============================================================
void ghiThongKe(const TuDien& td, const string& tenFile) {
    ofstream f(tenFile);
    if (!f.is_open()) throw runtime_error("Khong mo duoc file: " + tenFile);

    f << td.soLichSu << "\n";
    for (int i = 0; i < td.soLichSu; i++) {
        f << td.lichSu[i];
        if (i < td.soLichSu - 1) f << "|";
    }
    f << "\n";
    f << td.tongSoCauQuiz << "\n";
    f << td.tongSoCauDung << "\n";
    f.close();
}

// ============================================================
//  ĐỌC THỐNG KÊ
// ============================================================
void docThongKe(TuDien& td, const string& tenFile) {
    ifstream f(tenFile);
    if (!f.is_open()) return; // Không có file thì bỏ qua, không throw

    string line;
    getline(f, line);
    td.soLichSu = stoi(line);

    getline(f, line);
    // Tách các từ lịch sử theo '|'
    int idx = 0;
    size_t pos;
    while ((pos = line.find('|')) != string::npos && idx < 10) {
        td.lichSu[idx++] = line.substr(0, pos);
        line = line.substr(pos + 1);
    }
    if (!line.empty() && idx < 10) td.lichSu[idx] = line;

    getline(f, line); td.tongSoCauQuiz = stoi(line);
    getline(f, line); td.tongSoCauDung = stoi(line);
    f.close();
}
