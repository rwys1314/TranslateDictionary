# Translate Dictionary
Từ điển Anh - Việt 


### CẤU TRÚC

| File          | Người viết                          | Nội dung chính                                      |
|---------------|-------------------------------------|-----------------------------------------------------|
| tuvung.h      | Leader                              | Toàn bộ struct TuVung, TuDien + prototype           |
| tuvung.cpp    | Developer                           | Khởi tạo, CRUD, tìm kiếm, quiz, thống kê            |
| main.cpp      | Leader                              | Menu, switch-case, khung chương trình               |
| fileIO.cpp    | Tester & Documenter                 | Đọc/ghi file + thống kê, xuất yêu thích             |
| ui.cpp        | Tester & Documenter                 | Vẽ khung, hiển thị menu, nhập số nguyên + chuỗi     |
| tudien.txt    | Có sẵn                              | Dữ liệu từ vựng                                     |





### PHÂN CÔNG CỤ THỂ


**Leader**

| Nhiệm vụ                                  | File        | Trạng thái |
|-------------------------------------------|-------------|------------|
| Định nghĩa struct TuVung, TuDien          | tuvung.h    | [x]        |
| Khai báo toàn bộ prototype                | tuvung.h    | [x]        |
| Menu chính, switch-case                   | main.cpp    | [x]        |
| Xử lý từng chức năng (xuLyXxx)            | main.cpp    | [x]        |
| Ghép toàn bộ code + test tích hợp         | tất cả      | [x]        |


**Developer**

| Nhiệm vụ                                               | File        | Trạng thái |
|--------------------------------------------------------|-------------|------------|
| khoiTao(), giaiPhong(), moRong()                       | tuvung.cpp  | [x]        |
| sapXepTheoAlphabet(), BinarySearch()                   | tuvung.cpp  | [x]        |
| timKiem(), themLichSu(), hienThiLichSu()               | tuvung.cpp  | [x]        |
| themTuVung(), hienThiTatCa(), hienThiChiTiet()         | tuvung.cpp  | [x]        |
| suaTuVung(), xoaTuVung()                               | tuvung.cpp  | [x]        |
| danhDauYeuThich(), hienThiYeuThich()                   | tuvung.cpp  | [x]        |
| quizNgauNhien() -- lưu kết quả vào struct              | tuvung.cpp  | [x]        |
| hienThiThongKe() -- độ chính xác quiz tích lũy         | tuvung.cpp  | [x]        |


**Tester & Documenter**

| Nhiệm vụ                                               | File        | Trạng thái |
|--------------------------------------------------------|-------------|------------|
| docFile(), ghiFile()                                   | fileIO.cpp  | [x]        |
| xuatYeuThich()                                         | fileIO.cpp  | [x]        |
| docThongKe(), ghiThongKe()                             | fileIO.cpp  | [x]        |
| veKhung(), hienThiMenu()                               | ui.cpp      | [x]        |
| nhapSoNguyen(), nhapChuoi(), pauseScreen()             | ui.cpp      | [x]        |

---

### Tính năng

| Tính năng                               | Trạng thái |
|-----------------------------------------|------------|
| Thêm / sửa / xóa từ vựng                | [x]        |
| Tìm kiếm Binary Search + chuỗi con      | [x]        |
| Đánh dấu yêu thích, xuất file           | [x]        |
| Quiz ngẫu nhiên 5 câu                   | [x]        |
| Thống kê loại từ + yêu thích            | [x]        |
| Lưu khi thoát, đọc khi khởi động        | [x]        |
| Lịch sử tra cứu gần đây (10 từ)         | [x]        |
| Thống kê độ chính xác quiz tích luỹ     | [x]        |

---

### Build

```
g++ -std=c++17 -o tudien main.cpp tuvung.cpp fileIO.cpp ui.cpp
./tudien
```

### Định dạng file

**tudien.txt**
```
word|pronunciation|type|meaning|example|favorite(0/1)
```

**thongke.txt**
```
soLichSu
tu1|tu2|tu3|...
tongSoCauQuiz
tongSoCauDung
```
---------------------------------------------------
## LƯU Ý QUAN TRỌNG:
  - Cả 3 đều phải hiểu TOÀN BỘ code
  - GV sẽ vấn đáp từng người
  - Dữ liệu KHÔNG được mất khi tắt/mở lại
  - Bắt buộc có new/delete và try-catch
===================================================
