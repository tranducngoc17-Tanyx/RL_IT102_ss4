#include <stdio.h>

int main() {
    int so_luong_ly = 0;
    long long tong_tien = 0;

    printf("=== HE THONG POS TINH TIEN COFFEE ===\n");
    printf("Nhap so luong ly trong don hang: ");
    scanf("%d", &so_luong_ly);

    // Vong lap tinh tien tung ly trong don hang
    // FIX: dieu kien phai la i <= so_luong_ly de duyet du tat ca cac ly
    // (hoac bat dau tu i = 0 va giu i < so_luong_ly).
    for (int i = 1; i <= so_luong_ly; i++) {
        long long don_gia_co_ban = 30000; // Gia ly size S mac dinh: 30.000 VND
        int size_option = 0; // 1: Size S, 2: Size M (+6000), 3: Size L (+10000)

        printf("\n--- Ly thu %d ---\n", i);
        printf("Chon size (1-Size S, 2-Size M, 3-Size L): ");
        scanf("%d", &size_option);

        if (size_option == 2) {
            don_gia_co_ban += 6000;
        } else if (size_option == 3) {
            don_gia_co_ban += 10000;
        }

        tong_tien += don_gia_co_ban;
    }

    printf("\n===================================\n");
    printf("Tong chi phi don hang: %lld VND\n", tong_tien);

    return 0;
}
