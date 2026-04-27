# TranslateDictionary
Từ điển Anh - Việt 

Cấu trúc:
- main.cpp     <- Leader viết
- tuvung.h     <- Leader viết
- tuvung.cpp   <- Developer viết
- fileIO.cpp   <- Tester & Documenter viết
- tudien.txt   <- Có sẵn

---------------------------------------------------
Leader (main.cpp + tuvung.h):
- [x] struct TuVung, TuDien
- [x] khoiTao() / giaiPhong() / moRong()
- [x] menu chính, validation input
- [x] ghép code cuối + test tích hợp
- [x] viết báo cáo

---------------------------------------------------
Developer (tuvung.cpp):
- [x] crud: themTuVung(), hienThiTatCa() + hienThiChiTiet(), suaTuVung(), xoaTuVung()
- [x] danhDauYeuThich() + hienThiYeuThich()
- [x] quizNgauNhien()
- [x] hienThiThongKe()

---------------------------------------------------
Tester & Documenter (fileIO.cpp + validation):
- [x] docFile() - đọc từ file khi khởi động
- [x] ghiFile() - ghi ra file khi thoát
- [x] xuatYeuThich() - xuất file riêng
- [x] validation input: nhapSoNguyen(), nhapChuoi(), veKhung()
- [x] try-catch cho tất cả các trường hợp lỗi
- [ ] test toàn bộ chức năng, ghi bug ra

---------------------------------------------------
CÁCH COMPILE:
  g++ main.cpp tuvung.cpp crud.cpp fileIO.cpp -o tudien
  ./tudien

---------------------------------------------------
LƯU Ý QUAN TRỌNG:
  - Cả 3 đều phải hiểu TOÀN BỘ code
  - GV sẽ vấn đáp từng người
  - Dữ liệu KHÔNG được mất khi tắt/mở lại
  - Bắt buộc có new/delete và try-catch
===================================================
