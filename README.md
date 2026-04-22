# TranslateDictionary
Từ điển Anh - Việt 

Cấu trúc:
- main.cpp     <- Leader viết
- tuvung.h     <- Leader viết
- tuvung.cpp   <- Cả 3 viết
- crud.cpp     <- Developer viết
- fileIO.cpp   <- Tester & Documenter viết
- tudien.txt   <- Có sẵn

---------------------------------------------------
Leader:
- [x] struct TuVung + TuDien (mảng động)
- [x] khoiTao() / giaiPhong() / moRong()
- [x] sapXepTheoAlphabet()
- [x] timKiemBinarySearch()
- [x] timKiemChuoiCon()
- [x] hienThiMenu() / veKhung()
- [x] main.cpp (vong lap menu chinh)
- [ ] Ghép code cuối + test tích hợp

---------------------------------------------------
Developer
- [ ] themTuVung()
- [ ] hienThiTatCa() + hienThiChiTiet()
- [ ] suaTuVung()
- [ ] xoaTuVung()
- [ ] danhDauYeuThich() + hienThiYeuThich()
- [ ] quizNgauNhien()
- [ ] hienThiThongKe()
  => File: crud.cpp 

---------------------------------------------------
Tester & Documenter:
- [ ] docFile() - đọc từ file khi khởi động
- [ ] ghiFile() - ghi khi thoát
- [ ] xuatYeuThich() - xuất file riêng
- [ ] nhapSoHopLe() - validation số
- [ ] nhapChuoiHopLe() - validation chuỗi
- [ ] try-catch cho tất cả các trường hợp lỗi
- [ ] Test toàn bộ chức năng, ghi bug ra
- [ ] Viết báo cáo
  => File: fileIO.cpp 

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
