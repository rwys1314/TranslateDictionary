#include "tuvung.h"
#include <cstdlib>
#include <ctime>
#include <limits>

// ============================================================
//  XỬ LÝ TÌM KIẾM
// ============================================================
void xuLyTimKiem(TuDien& td) {
    veKhung("TIM KIEM TU");
    string keyword = nhapChuoi("Nhap tu can tim: ");

    // Lưu vào lịch sử trước khi tìm
    themLichSu(td, keyword);

    // Sắp xếp để Binary Search hoạt động đúng
    sapXepTheoAlphabet(td);
    int idx = BinarySearch(td, keyword);

    if (idx != -1) {
        // TTìm thấy chính xác
        cout << "\n  Tim thay chinh xac:\n";
        cout << "  " << string(60, '-') << "\n";
        hienThiChiTiet(td.data[idx]);
        cout << "  " << string(60, '-') << "\n";
    } else {
        // Không tìm thấy chính xác => fallback chuỗi con
        timKiem(td, keyword);
    }
}

// ============================================================
//  XỬ LÝ THÊM TỪ MỚI
// ============================================================
void xuLyThem(TuDien& td) {
    veKhung("THEM TU MOI");
    TuVung tv;
    tv.word          = nhapChuoi("Tu tieng Anh         : ");
    tv.pronunciation = nhapChuoi("Phien am             : ");
    tv.type          = nhapChuoi("Loai tu (n/v/adj/adv): ");
    tv.meaning       = nhapChuoi("Nghia tieng Viet     : ");
    tv.example       = nhapChuoi("Cau vi du            : ");
    tv.favorite      = false;
    themTuVung(td, tv);
    cout << "\n  Da them tu '" << tv.word << "' thanh cong!\n";
}

// ============================================================
//  XỬ LÝ SỬA TỪ
// ============================================================
void xuLySua(TuDien& td) {
    veKhung("SUA THONG TIN TU");

    if (td.soLuong == 0) {
        cout << "  Tu dien rong!\n";
        return;
    }

    hienThiTatCa(td);
    int index = nhapSoNguyen("Nhap STT tu muon sua (bat dau tu 0): ", 0, td.soLuong - 1);

    // Lấy thông tin cũ làm giá trị mặc định
    TuVung tvMoi = td.data[index];

    cout << "  (Nhan Enter de giu nguyen gia tri cu)\n\n";

    string input;

    cout << "  Tu tieng Anh [" << tvMoi.word << "]: ";
    getline(cin, input);
    if (!input.empty()) tvMoi.word = input;

    cout << "  Phien am [" << tvMoi.pronunciation << "]: ";
    getline(cin, input);
    if (!input.empty()) tvMoi.pronunciation = input;

    cout << "  Loai tu [" << tvMoi.type << "]: ";
    getline(cin, input);
    if (!input.empty()) tvMoi.type = input;

    cout << "  Nghia [" << tvMoi.meaning << "]: ";
    getline(cin, input);
    if (!input.empty()) tvMoi.meaning = input;

    cout << "  Vi du [" << tvMoi.example << "]: ";
    getline(cin, input);
    if (!input.empty()) tvMoi.example = input;

    suaTuVung(td, index, tvMoi);
    cout << "\n  Da cap nhat tu '" << tvMoi.word << "' thanh cong!\n";
}

// ============================================================
//  XỬ LÝ XÓA TỪ
// ============================================================
void xuLyXoa(TuDien& td) {
    veKhung("XOA TU");

    if (td.soLuong == 0) {
        cout << "  Tu dien rong!\n";
        return;
    }

    hienThiTatCa(td);
    int index = nhapSoNguyen("Nhap STT tu muon xoa (bat dau tu 0): ", 0, td.soLuong - 1);

    cout << "  Ban co chac muon xoa '" << td.data[index].word << "'? (y/n): ";
    char confirm;
    cin >> confirm;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (confirm == 'y' || confirm == 'Y') {
        string ten = td.data[index].word;
        if (xoaTuVung(td, index))
            cout << "  Da xoa tu '" << ten << "' thanh cong!\n";
    } else {
        cout << "  Huy bo thao tac xoa.\n";
    }
}

// ============================================================
//  XỬ LÝ YÊU THÍCH
// ============================================================
void xuLyYeuThich(TuDien& td) {
    cout << "\n  1. Danh dau / bo danh dau yeu thich\n";
    cout << "  2. Xem danh sach yeu thich\n";
    int sub = nhapSoNguyen("  Chon: ", 1, 2);

    if (sub == 1) {
        veKhung("DANH DAU YEU THICH");
        if (td.soLuong == 0) { cout << "  Tu dien rong!\n"; return; }
        hienThiTatCa(td);
        int index = nhapSoNguyen("Nhap STT tu muon danh dau (bat dau tu 0): ", 0, td.soLuong - 1);
        danhDauYeuThich(td, index);
    } else {
        veKhung("DANH SACH YEU THICH");
        hienThiYeuThich(td);
    }
}

// ============================================================
//  MAIN
// ============================================================
int main() {
    srand(static_cast<unsigned int>(time(nullptr))); // Khởi tạo 1 lần

    const string TEN_FILE = "tudien.txt";
    TuDien td;
    khoiTao(td); // Khởi tạo mảng động

    // Đọc dữ liệu từ file khi khởi động
    try {
        docFile(td, TEN_FILE);
        docThongKe(td, "thongke.txt");
        cout << "  Da tai " << td.soLuong << " tu tu file '" << TEN_FILE << "'\n";
    } catch (const exception& e) {
        cout << "  Khong tim thay file, bat dau voi tu dien rong.\n";
    }

    int luaChon = -1;

    while (luaChon != 0) {
        hienThiMenu();
        luaChon = nhapSoNguyen("", 0, 10);

        switch (luaChon) {
            case 1:
                xuLyTimKiem(td);
                break;
            case 2:
                xuLyThem(td);
                break;
            case 3:
                xuLySua(td);
                break;
            case 4:
                xuLyXoa(td);
                break;
            case 5:
                veKhung("DANH SACH TAT CA TU");
                hienThiTatCa(td);
                break;
            case 6:
                xuLyYeuThich(td);
                break;
            case 7:
                veKhung("QUIZ ON TAP");
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                quizNgauNhien(td);
                break;
            case 8:
                veKhung("THONG KE");
                hienThiThongKe(td);
                break;
            case 9:
                try {
                    xuatYeuThich(td, "yeuthich.txt");
                } catch (const exception& e) {
                    cout << "  Loi: " << e.what() << "\n";
                }
                break;
            case 10:
                veKhung("LICH SU TRA CUU");
                hienThiLichSu(td);
                break;
            case 0:
                cout << "\n  Dang luu du lieu...\n";
                try {
                    ghiFile(td, TEN_FILE);
                    ghiThongKe(td, "thongke.txt");
                    cout << "  Da luu " << td.soLuong << " tu. Tam biet!\n";
                } catch (const exception& e) {
                    cout << "  Loi khi luu: " << e.what() << "\n";
                }
                break;
            default:
                cout << "  Lua chon khong hop le!\n";
        }

        if (luaChon != 0) pauseScreen();
    }

    giaiPhong(td);
    return 0;
}
