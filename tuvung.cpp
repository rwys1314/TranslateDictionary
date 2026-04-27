#include "tuvung.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>

// ============================================================
//  KHOI TAO & GIAI PHONG
// ============================================================

void khoiTao(TuDien& td, int dungLuongBanDau) {
    td.dungLuong = dungLuongBanDau;
    td.soLuong   = 0;
    td.data      = new TuVung[td.dungLuong];
}

void giaiPhong(TuDien& td) {
    delete[] td.data;
    td.data      = nullptr;
    td.soLuong   = 0;
    td.dungLuong = 0;
}

// Khi mang day, cap phat mang moi gap doi kich thuoc
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

// Sua theo vitri, tra ve false neu vitri khong hop le
bool suaTuVung(TuDien& td, int viTri, const TuVung& tvMoi) {
    if (viTri < 0 || viTri >= td.soLuong) return false;
    td.data[viTri] = tvMoi;
    return true;
}

// Xoa theo vitri, don mang lai
bool xoaTuVung(TuDien& td, int viTri) {
    if (viTri < 0 || viTri >= td.soLuong) return false;
    for (int i = viTri; i < td.soLuong - 1; i++) {
        td.data[i] = td.data[i + 1];
    }
    td.soLuong--;
    return true;
}

// ============================================================
//  TIM KIEM & SAP XEP
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

// Binary Search chinh xac (yeu cau da sap xep truoc)
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

// Tim kiem: Binary Search + fallback chuoi con
void timKiem(const TuDien& td, const string& keyword) {
    // Phai sap xep truoc khi goi Binary Search
    // Nhung timKiem la const nen xu ly: tim chuoi con truoc
    // roi tra ket qua chinh xac neu co
    bool found = false;

    cout << "\n  Ket qua tim kiem cho '" << keyword << "':\n";
    cout << "  " << string(60, '-') << "\n";

    for (int i = 0; i < td.soLuong; i++) {
        // Tim trong word hoac meaning (khong phan biet hoa thuong)
        string w = td.data[i].word, k = keyword;
        // Chuyen ve thuong de so sanh
        for (char& c : w) c = tolower(c);
        for (char& c : k) c = tolower(c);

        if (w.find(k) != string::npos ||
            td.data[i].meaning.find(keyword) != string::npos) {
            cout << "  ";
            hienThiChiTiet(td.data[i]);
            cout << "  " << string(60, '-') << "\n";
            found = true;
        }
    }

    if (!found) cout << "  Khong tim thay ket qua nao.\n";
}

// ============================================================
//  YEU THICH
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
//  QUIZ NGAU NHIEN
// ============================================================

void quizNgauNhien(const TuDien& td) {
    if (td.soLuong == 0) {
        cout << "  Tu dien rong, khong the quiz!\n";
        return;
    }

    int soCau = (td.soLuong < 5) ? td.soLuong : 5;
    int diem  = 0;

    cout << "  Quiz " << soCau << " cau ngau nhien. Nhap nghia tieng Viet:\n\n";

    // Tao mang index ngau nhien khong trung lap
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

    delete[] indices;

    cout << "  ===========================\n";
    cout << "  Ket qua: " << diem << "/" << soCau << " cau dung\n";
    cout << "  Ti le  : " << (diem * 100 / soCau) << "%\n";
    cout << "  ===========================\n";
}

// ============================================================
//  THONG KE
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
}

// ============================================================
//  DOC / GHI FILE
//  Dinh dang moi dong: word|pronunciation|type|meaning|example|favorite
// ============================================================

void ghiFile(const TuDien& td, const string& tenFile) {
    ofstream f(tenFile);
    if (!f.is_open()) {
        throw runtime_error("Khong mo duoc file de ghi: " + tenFile);
    }
    for (int i = 0; i < td.soLuong; i++) {
        const TuVung& tv = td.data[i];
        f << tv.word         << "|"
          << tv.pronunciation << "|"
          << tv.type          << "|"
          << tv.meaning       << "|"
          << tv.example       << "|"
          << (tv.favorite ? "1" : "0") << "\n";
    }
    f.close();
}

void docFile(TuDien& td, const string& tenFile) {
    ifstream f(tenFile);
    if (!f.is_open()) {
        throw runtime_error("Khong mo duoc file: " + tenFile);
    }

    string line;
    while (getline(f, line)) {
        if (line.empty()) continue;

        TuVung tv;
        tv.favorite = false;

        // Tach cac truong theo ky tu '|'
        auto tach = [&](string& dest) -> bool {
            size_t pos = line.find('|');
            if (pos == string::npos) return false;
            dest = line.substr(0, pos);
            line = line.substr(pos + 1);
            return true;
        };

        if (!tach(tv.word))         continue;
        if (!tach(tv.pronunciation)) continue;
        if (!tach(tv.type))         continue;
        if (!tach(tv.meaning))      continue;
        if (!tach(tv.example))      continue;
        tv.favorite = (line == "1");

        themTuVung(td, tv);
    }
    f.close();
}

void xuatYeuThich(const TuDien& td, const string& tenFile) {
    ofstream f(tenFile);
    if (!f.is_open()) {
        throw runtime_error("Khong mo duoc file de xuat: " + tenFile);
    }
    f << "DANH SACH TU YEU THICH\n";
    f << string(50, '=') << "\n";
    int dem = 0;
    for (int i = 0; i < td.soLuong; i++) {
        if (td.data[i].favorite) {
            const TuVung& tv = td.data[i];
            f << "* " << tv.word
              << " [" << tv.pronunciation << "]"
              << " (" << tv.type << ")\n";
            f << "  Nghia  : " << tv.meaning << "\n";
            f << "  Vi du  : " << tv.example << "\n";
            f << string(50, '-') << "\n";
            dem++;
        }
    }
    if (dem == 0) f << "  (Chua co tu yeu thich nao)\n";
    else          f << "Tong: " << dem << " tu\n";
    f.close();
}
