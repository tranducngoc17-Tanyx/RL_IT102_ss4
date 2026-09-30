# C_POS_Session05_Highlands_Coffee

## Bài tập 05 - Tổng hợp Thực hành Demo Xây dựng POS Highlands Coffee

### Thành phần

- `main.c`: Mã nguồn chương trình C.
- `BAO_CAO_NGHIEM_THU.md`: Tài liệu báo cáo nghiệm thu.

### Phạm vi cú pháp

Chương trình chỉ sử dụng:

- `main()`
- Biến đơn
- `int`
- Toán tử số học, so sánh
- `if/else`
- `for`
- `continue`
- `break`

Không sử dụng:

- `while`
- `do-while`
- Mảng
- `struct`
- Hàm tự định nghĩa

### Quy tắc xử lý

- `gia_tri_don == 0` → `continue`
- `gia_tri_don < 0` → `break`
- `gia_tri_don >= 100000` → giảm 10%
- `gia_tri_don > 0 && gia_tri_don < 100000` → không giảm giá

### Biên dịch GCC

```bash
gcc -std=c11 -Wall -Wextra -pedantic main.c -o main
```
