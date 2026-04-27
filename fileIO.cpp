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
        ofstream f(tenFile + ".txt");

        if (!f.is_open()) {
            cout << "Khong mo duoc file de ghi!";
            return;
        }

        f << td.soLuong << "\n";

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
        ifstream f(tenFile + ".txt");

        if (!f.is_open()) {
            cout << "Khong mo duoc file de doc!";
            return;
        }

        int n;
        f >> n;

        if (f.fail()) {
            cout << "File bi sai dinh dang!";
            return;
        }

        f.ignore(); // bỏ ký tự xuống dòng

        td.soLuong = 0;

        for (int i = 0; i < n; i++) {
            TuVung tv;
            string line;

            getline(f, line);

            if (line.empty()) continue;

            stringstream ss(line);
            string fav;

            getline(ss, tv.word, '|');
            getline(ss, tv.pronunciation, '|');
            getline(ss, tv.type, '|');
            getline(ss, tv.meaning, '|');
            getline(ss, tv.example, '|');
            getline(ss, fav, '|');

            tv.favorite = (fav == "1");

            themTuVung(td, tv);
        }

        f.close();
        cout << " ✓ Da doc file thanh cong!" << endl;
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
        ofstream f(tenFile + ".txt");

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
