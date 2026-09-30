# BÁO CÁO NGHIỆM THU
## Bài tập 05: Tổng hợp Thực hành Demo Xây dựng POS Highlands Coffee

### 1. Mục tiêu

Xây dựng chương trình C xử lý danh sách hóa đơn trong một ca bán hàng, áp dụng vòng lặp `for`, `continue`, `break` và các phép tính giảm giá để tổng hợp doanh thu.

### 2. Quy tắc nghiệp vụ

- Giá trị đơn bằng `0`: đơn hàng bị hủy, sử dụng `continue` để bỏ qua.
- Giá trị đơn nhỏ hơn `0`: lỗi dữ liệu nghiêm trọng, sử dụng `break` để dừng ca.
- Giá trị đơn từ `100000` VNĐ trở lên: giảm giá `10%`.
- Giá trị đơn dưới `100000` VNĐ: giữ nguyên giá trị.
- Chỉ đơn hàng hợp lệ được cộng vào số đơn hợp lệ và doanh thu.

### 3. Biến sử dụng

- `n`: số lượng hóa đơn dự kiến.
- `gia_tri_don`: giá trị của hóa đơn hiện tại.
- `so_don_hop_le`: số đơn hợp lệ.
- `tong_doanh_thu_goc`: tổng giá trị các đơn hợp lệ trước giảm giá.
- `tong_tien_giam_gia`: tổng tiền giảm giá.
- `tong_doanh_thu_thuc_thu`: tổng tiền thực tế thu được.
- `tien_giam_gia`: tiền giảm của đơn hiện tại.
- `thanh_tien`: số tiền khách phải trả của đơn hiện tại.

### 4. Kiểm tra trường hợp chuẩn

Input:

```text
4
50000
120000
0
200000
```

Kết quả:

```text
Don 1: Hop le - Thanh tien: 50000 VND
Don 2: Ap dung giam gia 10% (12000 VND) - Thanh tien: 108000 VND
Don 3: Don hang bi huy - Bo qua
Don 4: Ap dung giam gia 10% (20000 VND) - Thanh tien: 180000 VND

--- TONG KET CA BAN HANG ---
So don hop le: 3
Tong doanh thu goc: 370000 VND
Tong tien giam gia: 32000 VND
Tong doanh thu thuc thu: 338000 VND
```

### 5. Kiểm tra trường hợp ngoại lệ

Input:

```text
5
45000
-1
150000
80000
60000
```

Kết quả:

```text
Don 1: Hop le - Thanh tien: 45000 VND
Don 2: Loi du lieu am! Dung he thong khan cap.

--- TONG KET CA BAN HANG ---
So don hop le: 1
Tong doanh thu goc: 45000 VND
Tong tien giam gia: 0 VND
Tong doanh thu thuc thu: 45000 VND
```

### 6. Kiến thức đáp ứng

- Sử dụng duy nhất vòng lặp `for`.
- Sử dụng `continue` cho đơn hàng bằng `0`.
- Sử dụng `break` cho đơn hàng âm.
- Sử dụng `if/else`.
- Sử dụng biến đơn, không dùng mảng.
- Không sử dụng `while`.
- Không sử dụng `do-while`.
- Không sử dụng `struct`.
- Không định nghĩa hàm tự tạo.
- Chương trình chỉ có hàm `main()`.

### 7. Kết luận

Chương trình đáp ứng các yêu cầu nghiệp vụ và giới hạn cú pháp của Bài tập 05, đồng thời xử lý đúng hai trường hợp mẫu được cung cấp trong đề.
