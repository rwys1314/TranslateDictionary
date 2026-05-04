#include "tuvung.h"

// ============================================================
//  VẼ KHUNG
// ============================================================
void veKhung(const string& tieuDe) {
    cout << "\n  ============================================\n";
    cout << "  " << tieuDe << "\n";
    cout << "  ============================================\n\n";
}

// ============================================================
//  NHẬP SỐ NGUYÊN HỢP LỆ
// ============================================================
int nhapSoNguyen(const string& thongBao, int min, int max) {
    int x;
    while (true) {
        if (!thongBao.empty()) cout << thongBao;
        cin >> x;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "  Vui long nhap so nguyen!\n";
            continue;
        }
        cin.ignore(1000, '\n');
        if (x < min || x > max) {
            cout << "  Nhap tu " << min << " den " << max << "!\n";
            continue;
        }
        return x;
    }
}

// ============================================================
//  NHẬP CHUỖI KHÔNG RỖNG
// ============================================================
string nhapChuoi(const string& thongBao) {
    string s;
    while (true) {
        cout << thongBao;
        getline(cin, s);
        if (!s.empty()) return s;
        cout << "  Khong duoc de trong!\n";
    }
}

// ============================================================
//  DỪNG MÀN HÌNH
// ============================================================
void pauseScreen() {
    cout << "\n  [Nhan Enter de tiep tuc...]";
    cin.get();
}

// ============================================================
//  HIỆN THỊ MÀN HÌNH
// ============================================================
void hienThiMenu() {
    cout << "\n";
    cout << "  +======================================+\n";
    cout << "  |      TU DIEN ANH - VIET              |\n";
    cout << "  +======================================+\n";
    cout << "  |  1. Tim kiem tu                     |\n";
    cout << "  |  2. Them tu moi                     |\n";
    cout << "  |  3. Sua thong tin tu                |\n";
    cout << "  |  4. Xoa tu                          |\n";
    cout << "  |  5. Hien thi tat ca tu              |\n";
    cout << "  |  6. Danh dau / xem yeu thich        |\n";
    cout << "  |  7. Quiz on tap ngau nhien          |\n";
    cout << "  |  8. Thong ke                        |\n";
    cout << "  |  9. Xuat file yeu thich             |\n";
    cout << "  | 10. Lich su tra cuu                 |\n";
    cout << "  |  0. Luu va thoat                    |\n";
    cout << "  +======================================+\n";
    cout << "  Chon chuc nang: ";
}
