#include "tuvung.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>

// ============================================================
//  KHỞI TẠO & GIẢI PHÓNG
// ============================================================

void khoiTao(TuDien& td, int dungLuongBanDau) {
    td.dungLuong     = dungLuongBanDau;
    td.soLuong       = 0;
    td.data          = new TuVung[td.dungLuong];
    td.soLichSu      = 0;
    td.tongSoCauQuiz = 0;
    td.tongSoCauDung = 0;
}

void giaiPhong(TuDien& td) {
    delete[] td.data;
    td.data      = nullptr;
    td.soLuong   = 0;
    td.dungLuong = 0;
}

// Khi mảng đầy, cấp phát mảng mới gấp đôi kích thước
void moRong(TuDien& td) {
    int dungLuongMoi  = td.dungLuong * 2;
    TuVung* mangMoi   = new TuVung[dungLuongMoi];

    for (int i = 0; i < td.soLuong; i++) {
        mangMoi[i] = td.data[i];
    }

    delete[] td.data;
    td.data      = mangMoi;
    td.dungLuong = dungLuongMoi;
}

// ============================================================
//  CRUD
// ============================================================

void themTuVung(TuDien& td, const TuVung& tv) {
    if (td.soLuong >= td.dungLuong) {
        moRong(td);
    }
    td.data[td.soLuong] = tv;
    td.soLuong++;
}

void hienThiTatCa(const TuDien& td) {
    if (td.soLuong == 0) {
        cout << "  (Danh sach rong)\n";
        return;
    }
    cout << left;
    cout << "  " << string(72, '-') << "\n";
    cout << "  " << setw(4)  << "STT"
                 << setw(15) << "Tu"
                 << setw(8)  << "Loai"
                 << setw(35) << "Nghia"
                 << "YT\n";
    cout << "  " << string(72, '-') << "\n";

    for (int i = 0; i < td.soLuong; i++) {
        const TuVung& tv = td.data[i];
        cout << "  " << setw(4)  << i
                     << setw(15) << tv.word
                     << setw(8)  << tv.type
                     << setw(35) << tv.meaning
                     << (tv.favorite ? "*" : " ") << "\n";
    }

    cout << "  " << string(72, '-') << "\n";
    cout << "  Tong: " << td.soLuong << " tu\n";
}

void hienThiChiTiet(const TuVung& tv) {
    cout << "  Tu       : " << tv.word          << "\n";
    cout << "  Phien am : " << tv.pronunciation  << "\n";
    cout << "  Loai tu  : " << tv.type           << "\n";
    cout << "  Nghia    : " << tv.meaning         << "\n";
    cout << "  Vi du    : " << tv.example         << "\n";
    cout << "  Yeu thich: " << (tv.favorite ? "* Co" : "Chua") << "\n";
}

// Sửa theo vitri, trả về false nếu vitri không hợp lệ
bool suaTuVung(TuDien& td, int viTri, const TuVung& tvMoi) {
    if (viTri < 0 || viTri >= td.soLuong) return false;
    td.data[viTri] = tvMoi;
    return true;
}

// Xóa theo vitri, dồn mảng lại
bool xoaTuVung(TuDien& td, int viTri) {
    if (viTri < 0 || viTri >= td.soLuong) return false;
    for (int i = viTri; i < td.soLuong - 1; i++) {
        td.data[i] = td.data[i + 1];
    }
    td.soLuong--;
    return true;
}

// ============================================================
//  TÌM KIẾM & SẮP XẾP
// ============================================================

void sapXepTheoAlphabet(TuDien& td) {
    for (int i = 0; i < td.soLuong - 1; i++) {
        for (int j = 0; j < td.soLuong - i - 1; j++) {
            if (td.data[j].word > td.data[j + 1].word) {
                swap(td.data[j], td.data[j + 1]);
            }
        }
    }
}

// Binary Search chính xác (yêu cầu đã sắp xếp trước)
int BinarySearch(const TuDien& td, const string& word) {
    int left = 0, right = td.soLuong - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (td.data[mid].word == word) return mid;
        if (td.data[mid].word < word)  left  = mid + 1;
        else                           right = mid - 1;
    }
    return -1;
}

// Tìm Kiếm: Binary Search + fallback chuỗi con
void timKiem(const TuDien& td, const string& keyword) {
    // Phải sắp xếp trước khi gọi Binary Search
    // Nhưng timKiem là const nên xử lý: tìm chuỗi con trước
    // rồi trả kết quả chính xác nếu có
    bool found = false;

    cout << "\n  Ket qua tim kiem cho '" << keyword << "':\n";
    cout << "  " << string(60, '-') << "\n";

    for (int i = 0; i < td.soLuong; i++) {
    string w = td.data[i].word;
    string k = keyword;
    string m = td.data[i].meaning;

    // Chuyển về thường để so sánh
    for (int j = 0; j < w.length(); j++) w[j] = tolower(w[j]);
    for (int j = 0; j < k.length(); j++) k[j] = tolower(k[j]);
    for (int j = 0; j < m.length(); j++) m[j] = tolower(m[j]);

    if (w.find(k) != string::npos ||
        m.find(k) != string::npos) {
        cout << "  ";
        hienThiChiTiet(td.data[i]);
        cout << "\n";
        found = true;
    }
}

    if (!found) cout << "  Khong tim thay ket qua nao.\n";
}

// ============================================================
//  LỊCH SỬ TRA CỨU
// ============================================================

void themLichSu(TuDien& td, const string& word) {
    // Tránh trùng lặp
    for (int i = 0; i < td.soLichSu; i++)
        if (td.lichSu[i] == word) return;

    // Dịch mảng lên nếu đầy
    if (td.soLichSu == 10) {
        for (int i = 0; i < 9; i++)
            td.lichSu[i] = td.lichSu[i + 1];
        td.soLichSu = 9;
    }
    td.lichSu[td.soLichSu++] = word;
}

void hienThiLichSu(const TuDien& td) {
    if (td.soLichSu == 0) {
        cout << "  (Chua co lich su tra cuu)\n";
        return;
    }
    cout << "  10 tu tra gan day (moi nhat o cuoi):\n";
    for (int i = 0; i < td.soLichSu; i++)
        cout << "  " << (i + 1) << ". " << td.lichSu[i] << "\n";
}

// ============================================================
//  YÊU THÍCH
// ============================================================

void danhDauYeuThich(TuDien& td, int viTri) {
    if (viTri < 0 || viTri >= td.soLuong) {
        cout << "  Chi so khong hop le!\n";
        return;
    }
    td.data[viTri].favorite = !td.data[viTri].favorite;
    cout << "  Tu '" << td.data[viTri].word << "': "
         << (td.data[viTri].favorite ? "* Da them vao yeu thich"
                                     : "Da bo khoi yeu thich") << "\n";
}

void hienThiYeuThich(const TuDien& td) {
    int dem = 0;
    for (int i = 0; i < td.soLuong; i++) {
        if (td.data[i].favorite) {
            cout << "  * " << td.data[i].word
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

void quizNgauNhien(TuDien& td) {
    if (td.soLuong == 0) {
        cout << "  Tu dien rong, khong the quiz!\n";
        return;
    }

    int soCau = (td.soLuong < 5) ? td.soLuong : 5;
    int diem  = 0;

    cout << "  Quiz " << soCau << " cau ngau nhien. Nhap nghia tieng Viet:\n\n";

    // Tạo mảng index ngẫu nhiên không trùng lặp
    int* indices = new int[td.soLuong];
    for (int i = 0; i < td.soLuong; i++) indices[i] = i;
    // Shuffle (Fisher-Yates)
    for (int i = td.soLuong - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(indices[i], indices[j]);
    }

    for (int i = 0; i < soCau; i++) {
        const TuVung& tv = td.data[indices[i]];
        cout << "  Cau " << (i + 1) << ": " << tv.word
             << " (" << tv.type << ")\n";
        cout << "  Tra loi: ";

        string answer;
        getline(cin, answer);

        if (answer == tv.meaning) {
            cout << "  Dung!\n\n";
            diem++;
        } else {
            cout << "  Sai. Dap an dung: " << tv.meaning << "\n\n";
        }
    }

    cout << "  ===========================\n";
    cout << "  Ket qua: " << diem << "/" << soCau << " cau dung\n";
    cout << "  Ti le  : " << (diem * 100 / soCau) << "%\n";
    cout << "  ===========================\n";

    // Lưu lại vào struct
    td.tongSoCauQuiz += soCau;
    td.tongSoCauDung += diem;

    delete[] indices;
}

// ============================================================
//  THỐNG KÊ
// ============================================================

void hienThiThongKe(const TuDien& td) {
    int soYeuThich = 0;
    int soN = 0, soV = 0, soAdj = 0, soAdv = 0, soKhac = 0;

    for (int i = 0; i < td.soLuong; i++) {
        if (td.data[i].favorite)          soYeuThich++;
        if (td.data[i].type == "n")        soN++;
        else if (td.data[i].type == "v")   soV++;
        else if (td.data[i].type == "adj") soAdj++;
        else if (td.data[i].type == "adv") soAdv++;
        else                               soKhac++;
    }

    cout << "  Tong so tu      : " << td.soLuong  << "\n";
    cout << "  Tu yeu thich    : " << soYeuThich   << "\n";
    cout << "  Danh tu (n)     : " << soN          << "\n";
    cout << "  Dong tu (v)     : " << soV          << "\n";
    cout << "  Tinh tu (adj)   : " << soAdj        << "\n";
    cout << "  Trang tu (adv)  : " << soAdv        << "\n";
    cout << "  Loai khac       : " << soKhac        << "\n";
    cout << "  Dung luong mang : " << td.dungLuong  << "\n";

    cout << "  Tong cau quiz da lam : " << td.tongSoCauQuiz << "\n";
    if (td.tongSoCauQuiz > 0)
    cout << "  Do chinh xac tich luy: "
         << (td.tongSoCauDung * 100 / td.tongSoCauQuiz) << "%\n";
    else
    cout << "  Do chinh xac tich luy: Chua co du lieu\n";
}
