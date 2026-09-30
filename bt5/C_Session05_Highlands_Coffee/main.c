#include <stdio.h>

int main() {
    int n;
    int i;
    int gia_tri_don;

    int so_don_hop_le = 0;
    int tong_doanh_thu_goc = 0;
    int tong_tien_giam_gia = 0;
    int tong_doanh_thu_thuc_thu = 0;
    int tien_giam_gia;
    int thanh_tien;

    printf("===== COFFEE POS - XU LY HOA DON =====\n");

    printf("Nhap so luong hoa don: ");
    scanf("%d", &n);

    for (i = 1; i <= n; i++) {
        printf("\nNhap gia tri don %d: ", i);
        scanf("%d", &gia_tri_don);

        // Don hang am: loi du lieu nghiem trong, dung ca ngay lap tuc.
        if (gia_tri_don < 0) {
            printf("Don %d: Loi du lieu am! Dung he thong khan cap.\n", i);
            break;
        }

        // Don hang bang 0: don da bi huy, bo qua don hien tai.
        if (gia_tri_don == 0) {
            printf("Don %d: Don hang bi huy - Bo qua\n", i);
            continue;
        }

        // Don hop le: kiem tra dieu kien giam gia 10%.
        tien_giam_gia = 0;

        if (gia_tri_don >= 100000) {
            tien_giam_gia = gia_tri_don * 10 / 100;
            thanh_tien = gia_tri_don - tien_giam_gia;

            printf(
                "Don %d: Ap dung giam gia 10%% (%d VND) - Thanh tien: %d VND\n",
                i, tien_giam_gia, thanh_tien
            );
        } else {
            thanh_tien = gia_tri_don;

            printf(
                "Don %d: Hop le - Thanh tien: %d VND\n",
                i, thanh_tien
            );
        }

        so_don_hop_le++;
        tong_doanh_thu_goc += gia_tri_don;
        tong_tien_giam_gia += tien_giam_gia;
        tong_doanh_thu_thuc_thu += thanh_tien;
    }

    printf("\n--- TONG KET CA BAN HANG ---\n");
    printf("So don hop le: %d\n", so_don_hop_le);
    printf("Tong doanh thu goc: %d VND\n", tong_doanh_thu_goc);
    printf("Tong tien giam gia: %d VND\n", tong_tien_giam_gia);
    printf("Tong doanh thu thuc thu: %d VND\n", tong_doanh_thu_thuc_thu);

    return 0;
}
