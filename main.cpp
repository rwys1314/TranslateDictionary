#include "tuvung.h"

// ============================================================
//  VẼ MENU CHÍNH
// ============================================================
void hienThiMenu() {
    cout << "\n";
    cout << "╔══════════════════════════════════════╗\n";
    cout << "║       TU DIEN ANH - VIET v1.0        ║\n";
    cout << "╠══════════════════════════════════════╣\n";
    cout << "║  1. Tim kiem tu                      ║\n";
    cout << "║  2. Them tu moi                      ║\n";
    cout << "║  3. Sua thong tin tu                 ║\n";
    cout << "║  4. Xoa tu                           ║\n";
    cout << "║  5. Hien thi tat ca tu               ║\n";
    cout << "║  6. Danh sach yeu thich              ║\n";
    cout << "║  7. Quiz on tap ngau nhien           ║\n";
    cout << "║  8. Thong ke                         ║\n";
    cout << "║  9. Xuat file yeu thich              ║\n";
    cout << "║  0. Thoat                            ║\n";
    cout << "╚══════════════════════════════════════╝\n";
    cout << "  Chon chuc nang: ";
}

// ============================================================
//  XỬ LÝ TỪNG CHỨC NĂNG
// ============================================================
void xuLyTimKiem(TuDien& td) {
    string keyword = nhapChuoi("Nhap tu can tim: ");
    sapXepTheoAlphabet(td);  // Sắp xếp trước khi Binary Search
    timKiem(td, keyword);
}

void xuLyThem(TuDien& td) {
    veKhung("THEM TU MOI");
    TuVung tv;
    tv.word          = nhapChuoi("Tu tieng Anh   : ");
    tv.pronunciation = nhapChuoi("Phien am       : ");
    tv.type          = nhapChuoi("Loai tu (n/v/adj/adv): ");
    tv.meaning       = nhapChuoi("Nghia tieng Viet: ");
    tv.example       = nhapChuoi("Cau vi du      : ");
    tv.favorite      = false;
    themTuVung(td, tv);
    cout << "✓ Da them tu '" << tv.word << "' thanh cong!\n";
}

void xuLySua(TuDien& td) {
    veKhung("SUA THONG TIN TU");
    hienThiTatCa(td);
    int index = nhapSoHopLe("Nhap STT tu muon sua (bat dau tu 0): ");
    if (index < 0 || index >= td.soLuong) {
        cout << "✗ Chi so khong hop le!\n";
        return;
    }
    suaTuVung(td, index);
}

void xuLyXoa(TuDien& td) {
    veKhung("XOA TU");
    hienThiTatCa(td);
    int index = nhapSoHopLe("Nhap STT tu muon xoa (bat dau tu 0): ");
    if (index < 0 || index >= td.soLuong) {
        cout << "✗ Chi so khong hop le!\n";
        return;
    }
    cout << "Ban co chac muon xoa '" << td.data[index].word << "'? (y/n): ";
    char confirm;
    cin >> confirm;
    if (confirm == 'y' || confirm == 'Y') {
        xoaTuVung(td, index);
        cout << "✓ Da xoa thanh cong!\n";
    }
}

void xuLyYeuThich(TuDien& td) {
    veKhung("DANH DAU YEU THICH");
    hienThiTatCa(td);
    int index = nhapSoHopLe("Nhap STT tu muon danh dau (bat dau tu 0): ");
    if (index < 0 || index >= td.soLuong) {
        cout << "✗ Chi so khong hop le!\n";
        return;
    }
    danhDauYeuThich(td, index);
    cout << "✓ Da cap nhat trang thai yeu thich!\n";
}

// ============================================================
//  HÀM MAIN
// ============================================================
int main() {
    const string TEN_FILE = "tudien.txt";
    TuDien td;

    // Đọc dữ liệu từ file khi khởi động
    try {
        docFile(td, TEN_FILE);
        cout << "✓ Da tai " << td.soLuong << " tu tu file '" << TEN_FILE << "'\n";
    } catch (const exception& e) {
        cout << "! Khong tim thay file, bat dau voi tu dien rong.\n";
    }

    int luaChon = -1;

    while (luaChon != 0) {
        hienThiMenu();

        try {
            luaChon = nhapSoNguyen("");
        } catch (...) {
            cout << "✗ Vui long nhap so!\n";
            continue;
        }

        switch (luaChon) {
            case 1: xuLyTimKiem(td);          break;
            case 2: xuLyThem(td);             break;
            case 3: xuLySua(td);              break;
            case 4: xuLyXoa(td);              break;
            case 5:
                veKhung("DANH SACH TAT CA TU");
                hienThiTatCa(td);
                break;
            case 6:
                veKhung("DANH SACH YEU THICH");
                hienThiYeuThich(td);
                break;
            case 7:
                veKhung("QUIZ ON TAP");
                quizNgauNhien(td);
                break;
            case 8:
                veKhung("THONG KE");
                hienThiThongKe(td);
                break;
            case 9:
                xuatYeuThich(td, "yeuthich.txt");
                cout << "✓ Da xuat file 'yeuthich.txt'!\n";
                break;
            case 0:
                cout << "Dang luu du lieu...\n";
                ghiFile(td, TEN_FILE);
                cout << "✓ Da luu. Tam biet!\n";
                break;
            default:
                cout << "✗ Lua chon khong hop le, vui long thu lai!\n";
        }

        if (luaChon != 0) pause();
    }

    return 0;
}
