#include "tuvung.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>

// ============================================================
//  CRUD
// ============================================================

// Thêm 1 từ vào từ điển — tự mở rộng mảng nếu đầy
void themTuVung(TuDien& td, const TuVung& tv) {
    if (td.soLuong >= td.dungLuong) {
        td.moRong(); // Cấp phát lại mảng lớn hơn
    }
    td.data[td.soLuong] = tv;
    td.soLuong++;
}

// Hiển thị toàn bộ danh sách từ
void hienThiTatCa(const TuDien& td) {
    if (td.soLuong == 0) {
        cout << "  (Danh sach rong)\n";
        return;
    }
    cout << left;
    cout << "  " << string(70, '-') << "\n";
    cout << "  " << setw(4) << "STT"
         << setw(15) << "Tu"
         << setw(8)  << "Loai"
         << setw(35) << "Nghia"
         << "YT\n";
    cout << "  " << string(70, '-') << "\n";

    for (int i = 0; i < td.soLuong; i++) {
        const TuVung& tv = td.data[i];
        cout << "  " << setw(4) << i
             << setw(15) << tv.word
             << setw(8)  << tv.type
             << setw(35) << tv.meaning
             << (tv.favorite ? "★" : " ") << "\n";
    }
    cout << "  " << string(70, '-') << "\n";
    cout << "  Tong: " << td.soLuong << " tu\n";
}

// Sửa thông tin từ theo index
void suaTuVung(TuDien& td, int index) {
    TuVung& tv = td.data[index];
    cout << "  (Enter de giu nguyen)\n";

    string input;

    cout << "Tu tieng Anh [" << tv.word << "]: ";
    cin.ignore();
    getline(cin, input);
    if (!input.empty()) tv.word = input;

    cout << "Phien am [" << tv.pronunciation << "]: ";
    getline(cin, input);
    if (!input.empty()) tv.pronunciation = input;

    cout << "Loai tu [" << tv.type << "]: ";
    getline(cin, input);
    if (!input.empty()) tv.type = input;

    cout << "Nghia [" << tv.meaning << "]: ";
    getline(cin, input);
    if (!input.empty()) tv.meaning = input;

    cout << "Vi du [" << tv.example << "]: ";
    getline(cin, input);
    if (!input.empty()) tv.example = input;

    cout << "✓ Da cap nhat!\n";
}

// Xóa từ theo index — dồn mảng lại
void xoaTuVung(TuDien& td, int index) {
    // Dồn phần tử phía sau lên để lấp chỗ trống
    for (int i = index; i < td.soLuong - 1; i++) {
        td.data[i] = td.data[i + 1];
    }
    td.soLuong--;
}

// ============================================================
//  TÌM KIẾM
// ============================================================

// Sắp xếp theo alphabet (bubble sort đơn giản)
void sapXepTheoAlphabet(TuDien& td) {
    for (int i = 0; i < td.soLuong - 1; i++) {
        for (int j = 0; j < td.soLuong - i - 1; j++) {
            if (td.data[j].word > td.data[j + 1].word) {
                swap(td.data[j], td.data[j + 1]);
            }
        }
    }
}

// Binary Search — tìm chính xác theo từ (đã sắp xếp)
int binarySearch(const TuDien& td, const string& word) {
    int left = 0, right = td.soLuong - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (td.data[mid].word == word)  return mid;  // Tìm thấy
        if (td.data[mid].word < word)   left = mid + 1;
        else                            right = mid - 1;
    }
    return -1; // Không tìm thấy
}

// Tìm kiếm kết hợp: Binary Search + tìm chuỗi con
void timKiem(const TuDien& td, const string& keyword) {
    // Thử Binary Search trước (tìm chính xác)
    int index = binarySearch(td, keyword);
    if (index != -1) {
        const TuVung& tv = td.data[index];
        cout << "\n  ✓ Tim thay:\n";
        cout << "  Tu       : " << tv.word          << "\n";
        cout << "  Phien am : " << tv.pronunciation  << "\n";
        cout << "  Loai tu  : " << tv.type           << "\n";
        cout << "  Nghia    : " << tv.meaning         << "\n";
        cout << "  Vi du    : " << tv.example         << "\n";
        cout << "  Yeu thich: " << (tv.favorite ? "★ Co" : "Chua") << "\n";
        return;
    }

    // Không tìm thấy chính xác → tìm chuỗi con gợi ý
    cout << "\n  Khong tim thay chinh xac. Goi y:\n";
    bool found = false;
    for (int i = 0; i < td.soLuong; i++) {
        // Tìm keyword trong word hoặc meaning
        if (td.data[i].word.find(keyword) != string::npos ||
            td.data[i].meaning.find(keyword) != string::npos) {
            cout << "  - " << td.data[i].word
                 << " (" << td.data[i].type << "): "
                 << td.data[i].meaning << "\n";
            found = true;
        }
    }
    if (!found) cout << "  Khong co ket qua nao.\n";
}

// ============================================================
//  YÊU THÍCH
// ============================================================

void danhDauYeuThich(TuDien& td, int index) {
    // Toggle: đang yêu thích → bỏ, chưa → thêm
    td.data[index].favorite = !td.data[index].favorite;
    cout << "  Tu '" << td.data[index].word << "': "
         << (td.data[index].favorite ? "★ Da them vao yeu thich"
                                     : "Đa bo khoi yeu thich") << "\n";
}

void hienThiYeuThich(const TuDien& td) {
    int dem = 0;
    for (int i = 0; i < td.soLuong; i++) {
        if (td.data[i].favorite) {
            cout << "  ★ " << td.data[i].word
                 << " (" << td.data[i].type << "): "
                 << td.data[i].meaning << "\n";
            dem++;
        }
    }
    if (dem == 0) cout << "  (Chua co tu yeu thich nao)\n";
    else          cout << "\n  Tong: " << dem << " tu yeu thich\n";
}

// ============================================================
//  QUIZ NGẪU NHIÊN
// ============================================================
void quizNgauNhien(const TuDien& td) {
    if (td.soLuong == 0) {
        cout << "  Tu dien rong, khong the quiz!\n";
        return;
    }

    srand(time(0));
    int soCau   = 5;
    int diem    = 0;

    cout << "  Quiz " << soCau << " cau ngau nhien. Nhap nghia tieng Viet:\n\n";

    for (int i = 0; i < soCau; i++) {
        int index = rand() % td.soLuong;
        const TuVung& tv = td.data[index];

        cout << "  Cau " << (i + 1) << ": " << tv.word
             << " (" << tv.type << ")\n";
        cout << "  Tra loi: ";

        string answer;
        cin.ignore();
        getline(cin, answer);

        // So sánh đơn giản (có thể cải tiến thêm)
        if (answer == tv.meaning) {
            cout << "  ✓ Dung! \n\n";
            diem++;
        } else {
            cout << "  ✗ Sai. Dap an dung: " << tv.meaning << "\n\n";
        }
    }

    cout << "  ===========================\n";
    cout << "  Ket qua: " << diem << "/" << soCau << " cau dung\n";
    cout << "  Ti le  : " << (diem * 100 / soCau) << "%\n";
    cout << "  ===========================\n";
}

// ============================================================
//  THỐNG KÊ
// ============================================================
void hienThiThongKe(const TuDien& td) {
    int soYeuThich = 0;
    int soN = 0, soV = 0, soAdj = 0, soAdv = 0;

    for (int i = 0; i < td.soLuong; i++) {
        if (td.data[i].favorite) soYeuThich++;
        if (td.data[i].type == "n")   soN++;
        if (td.data[i].type == "v")   soV++;
        if (td.data[i].type == "adj") soAdj++;
        if (td.data[i].type == "adv") soAdv++;
    }

    cout << "  Tong so tu      : " << td.soLuong  << "\n";
    cout << "  Tu yeu thich    : " << soYeuThich   << "\n";
    cout << "  Danh tu (n)     : " << soN          << "\n";
    cout << "  Dong tu (v)     : " << soV          << "\n";
    cout << "  Tinh tu (adj)   : " << soAdj        << "\n";
    cout << "  Trang tu (adv)  : " << soAdv        << "\n";
}
