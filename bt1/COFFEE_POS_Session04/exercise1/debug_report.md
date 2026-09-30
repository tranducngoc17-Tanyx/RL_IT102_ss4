# BÁO CÁO DÒ LỖI & SỬA LỖI VÒNG LẶP FOR
## Module tính tiền hóa đơn đồ uống — Highlands POS (pos_order.c)

---

## 1. Xác định dòng lệnh gây lỗi

Trong mã nguồn gốc, vòng lặp `for` được viết:

```c
for (int i = 1; i < so_luong_ly; i++) {
    ...
}
```

Đây chính là dòng lệnh gây ra sự cố thất thoát doanh thu.

## 2. Phân tích nguyên nhân kỹ thuật

Vòng lặp `for` trong C gồm 3 phần: khởi tạo (`i = 1`), điều kiện dừng
(`i < so_luong_ly`), và bước nhảy (`i++`). Vòng lặp sẽ **tiếp tục chạy**
khi điều kiện còn **đúng (true)**, và **dừng ngay khi điều kiện sai**.

Với biến đếm bắt đầu từ `i = 1` (đại diện cho "ly thứ 1"), để duyệt đủ
`so_luong_ly` ly (ly thứ 1, thứ 2, ..., thứ N), điều kiện dừng đúng phải
là `i <= so_luong_ly`.

Nhưng mã nguồn gốc dùng điều kiện `i < so_luong_ly`, khiến vòng lặp kết
thúc **ngay khi `i` bằng `so_luong_ly`**, tức là dừng lại **trước khi xử
lý ly cuối cùng**. Đây là lỗi **lệch một đơn vị (off-by-one error)** —
lỗi logic phổ biến khi phối hợp sai giữa điểm bắt đầu của biến đếm
(bắt đầu từ 1) và điều kiện dừng (dùng dấu `<` thay vì `<=`).

Ví dụ với `so_luong_ly = 3`:
- `i = 1` → `1 < 3` đúng → xử lý ly 1
- `i = 2` → `2 < 3` đúng → xử lý ly 2
- `i = 3` → `3 < 3` **sai** → vòng lặp dừng, **ly thứ 3 bị bỏ qua hoàn toàn**

→ Chương trình chỉ nhập và tính tiền cho 2/3 ly, biến `tong_tien` bị
thiếu đúng giá trị của ly cuối cùng, dẫn đến hóa đơn in ra thấp hơn thực
tế. Vì đây là lỗi logic (không phải lỗi cú pháp), GCC biên dịch thành
công, không báo warning/error, nên lỗi rất khó phát hiện nếu chỉ dựa vào
kết quả compile.

## 3. Bảng Test Cases đối chứng

| Trường hợp kiểm thử | Dữ liệu đầu vào | Kết quả sai thực tế (mã gốc) | Kết quả đúng mong đợi (mã đã sửa) |
|---|---|---|---|
| **TC01: Đơn hàng 3 ly, đủ 3 size khác nhau** | `so_luong_ly = 3`<br>Ly 1: size 1 (S)<br>Ly 2: size 2 (M)<br>Ly 3: size 3 (L) | Chỉ nhập & tính 2 ly (ly 1, ly 2)<br>Tổng = 30.000 + 36.000 = **66.000 VNĐ**<br>(ly 3 - size L bị bỏ qua hoàn toàn) | Nhập & tính đủ 3 ly<br>Tổng = 30.000 + 36.000 + 40.000 = **106.000 VNĐ** |
| **TC02: Đơn hàng 1 ly duy nhất, size S** | `so_luong_ly = 1`<br>Ly 1: size 1 (S) | Vòng lặp không chạy lần nào (`1 < 1` sai ngay từ đầu)<br>Tổng = **0 VNĐ**<br>(khách hàng không bị tính tiền dù đã gọi 1 ly) | Vòng lặp chạy đúng 1 lần<br>Tổng = **30.000 VNĐ** |

## 4. Kết luận & Hướng sửa lỗi

Sửa điều kiện dừng của vòng lặp từ `i < so_luong_ly` thành
`i <= so_luong_ly` để vòng lặp duyệt đủ toàn bộ `so_luong_ly` ly trong
đơn hàng (từ ly thứ 1 đến ly thứ `so_luong_ly`), đảm bảo mọi ly nước
đều được nhập thông tin size và cộng dồn đúng vào `tong_tien`. Phần
logic tính giá theo size (S/M/L) và kiểu dữ liệu `long long` cho tiền tệ
được giữ nguyên vì không phải nguyên nhân gây lỗi.

Mã nguồn đã sửa được biên dịch kiểm tra thành công bằng lệnh:
```
gcc -std=c11 pos_order.c -o pos_order
```
không phát sinh warning/error, và đã kiểm thử lại với dữ liệu của TC01
cho ra đúng kết quả **106.000 VNĐ**.
