# COFFEE_POS_Session04_HW13

Bài tập 04: Thiết kế Kiến trúc POS Transaction Engine cho Highlands Coffee.

## File chính

- `main.c`: Chương trình xử lý bán hàng theo ca.

## Kiến thức sử dụng

- Biến đơn
- `int`, `double`
- Toán tử số học, so sánh
- `if/else`
- Vòng lặp `for`
- `continue`
- `break`
- Hàm `main()`

Không sử dụng:

- `while`
- `do-while`
- Mảng
- `struct`
- Hàm tự định nghĩa

## Quy tắc nghiệp vụ

- Size S: giá gốc
- Size M: giá gốc + 6.000 VNĐ
- Size L: giá gốc + 10.000 VNĐ
- Mỗi topping: 8.000 VNĐ
- Gold Membership: giảm 10% tổng giá trị đơn
- Mã trạng thái 2: hủy/bỏ qua đơn và dùng `continue`
- Mã trạng thái 3: dừng ca khẩn cấp và dùng `break`

## Báo cáo cuối ca

Chương trình hiển thị:

- Số đơn hoàn thành
- Số đơn bị hủy/bỏ qua
- Tổng doanh thu thực tế
