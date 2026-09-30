/*
 * =============================================================================
 * BAI TAP 02: PHAN HE BAN HANG & TINH TIEN TU DONG THEO LO DO UONG
 * Module: THONG KE DOANH THU CA LAM VIEC & PHAN TICH HOA DON
 * He thong: COFFEE_POS
 * =============================================================================
 *
 * ---------------------------------------------------------------------------
 * A. PHAN TICH I/O (INPUT / OUTPUT)
 * ---------------------------------------------------------------------------
 *
 * INPUT (nhap tu ban phim):
 *   - so_hoa_don_trong_ca (int)
 *       Y nghia: Tong so hoa don (N) du kien phat sinh trong ca lam viec,
 *       nhap 1 lan duy nhat truoc khi vao vong lap xu ly.
 *
 *   Voi MOI hoa don (lap lai so_hoa_don_trong_ca lan), nhap them:
 *   - gia_co_so (long long)
 *       Y nghia: Gia niem yet co so cua ly do uong tinh theo Size S (VND).
 *   - ky_tu_size (char)
 *       Y nghia: Ky tu dai dien Size do uong: 'S'/'s', 'M'/'m', 'L'/'l'.
 *   - so_luong_topping (int)
 *       Y nghia: So phan topping goi them cho ly do uong nay.
 *   - trang_thai_hoi_vien (int)
 *       Y nghia: Co the hoi vien: 1 = Hoi vien Vang (Gold), 0 = Khach thuong.
 *
 * OUTPUT (tong hop cuoi ca, in ra man hinh):
 *   - so_don_thanh_cong (int)
 *       Tong so hoa don hop le da tinh tien va thanh toan thanh cong.
 *   - so_don_loi_bo_qua (int)
 *       Tong so hoa don bi huy / loi du lieu bi bo qua (khong tinh tien).
 *   - tong_doanh_thu_ca (long long)
 *       Tong doanh thu thuc te thu duoc trong ca (VND).
 *   - don_hang_lon_nhat (long long)
 *       Gia tri cua hoa don thanh cong co so tien lon nhat trong ca (VND).
 *
 * ---------------------------------------------------------------------------
 * B. DE XUAT GIAI PHAP (TU DUY XU LY LUONG GIAO DICH)
 * ---------------------------------------------------------------------------
 *
 *   1) Dung DUY NHAT 1 vong lap "for" de duyet qua N hoa don (theo dung
 *      rang buoc de bai: khong dung while/do-while, khong ham phu,
 *      khong mang, khong struct).
 *
 *   2) Bo qua don rac (Loi 1 - sai cu phap nhap lieu):
 *      Neu gia_co_so <= 0 HOAC ky_tu_size khong thuoc {S,M,L,s,m,l} thi
 *      day la hoa don loi du lieu thong thuong (khong phai gian lan).
 *      -> Tang bien dem "so_don_loi_bo_qua", in canh bao, roi dung lenh
 *         "continue" de bo qua toan bo phan tinh tien cua hoa don nay
 *         va nhay ngay sang vong lap ke tiep (hoa don tiep theo), KHONG
 *         lam dung ca lam viec.
 *
 *   3) Ngat khan cap (Loi 2 - tin hieu gian lan / su co thiet bi):
 *      Neu so_luong_topping < 0 thi day la tin hieu bat thuong nghiem
 *      trong (POS bi can thiep trai phep / loi thiet bi), KHAC BAN CHAT
 *      voi loi nhap lieu thong thuong.
 *      -> In canh bao khan cap, roi dung lenh "break" de THOAT NGAY vong
 *         lap "for", dung nhan them hoa don con lai trong ca, sau do
 *         chuong trinh nhay thang xuong phan in bao cao doanh thu luy ke
 *         (doanh thu tinh duoc truoc thoi diem bi ngat van duoc giu
 *         nguyen vi da duoc cong don tu cac vong lap truoc do).
 *
 *   4) Ca lam viec rong / toan bo la don rac (Loi 3):
 *      Cac bien tong hop (tong_doanh_thu_ca, don_hang_lon_nhat,
 *      so_don_thanh_cong) deu duoc KHOI TAO BANG 0 truoc vong lap.
 *      Neu N <= 0 thi dieu kien vong lap "for" (i <= N) sai ngay tu dau
 *      nen vong lap khong chay lan nao -> cac bien giu nguyen gia tri 0,
 *      chuong trinh van chay toi phan in bao cao ma khong crash.
 *      Tuong tu, neu tat ca don deu loi/bi bo qua, khong co hoa don nao
 *      cong dong vao tong_doanh_thu_ca hay so sanh voi don_hang_lon_nhat,
 *      nen ca hai van bang 0 VND dung yeu cau.
 *
 * ---------------------------------------------------------------------------
 * C. CAC BUOC XU LY (ALGORITHM STEPS)
 * ---------------------------------------------------------------------------
 *   Buoc 1: Nhap so_hoa_don_trong_ca (N).
 *   Buoc 2: Khoi tao so_don_thanh_cong = 0, so_don_loi_bo_qua = 0,
 *           tong_doanh_thu_ca = 0, don_hang_lon_nhat = 0.
 *   Buoc 3: Lap for i = 1 den N (N <= 0 thi khong lap):
 *      3.1. Nhap gia_co_so, ky_tu_size, so_luong_topping, trang_thai_hoi_vien.
 *      3.2. Neu so_luong_topping < 0  -> in canh bao khan cap -> break.
 *      3.3. Neu gia_co_so <= 0 HOAC ky_tu_size khong hop le
 *              -> in canh bao loi du lieu -> so_don_loi_bo_qua++ -> continue.
 *      3.4. Tinh phu_thu_size theo ky_tu_size (S:+0, M:+6000, L:+10000).
 *      3.5. Tinh phu_thu_topping = so_luong_topping * 8000.
 *      3.6. tong_hoa_don = gia_co_so + phu_thu_size + phu_thu_topping.
 *      3.7. Neu trang_thai_hoi_vien == 1 -> giam 10% tren tong_hoa_don.
 *      3.8. Cong tong_hoa_don vao tong_doanh_thu_ca; tang so_don_thanh_cong.
 *      3.9. Neu tong_hoa_don > don_hang_lon_nhat -> cap nhat don_hang_lon_nhat.
 *   Buoc 4: In bao cao tong hop ca lam viec (4 chi so Output ben tren).
 *
 *   Bien dich: gcc -std=c11 bai7_chot_so_ca.c -o bai7_chot_so_ca
 * =============================================================================
 */

#include <stdio.h>
#include <ctype.h>

int main() {
    int so_hoa_don_trong_ca = 0;

    /* Cac bien tong hop ca - KHOI TAO BANG 0 de xu ly dung Loi thuong gap 3
       (ca rong hoac 100% don rac van cho ra ket qua 0, khong crash). */
    int so_don_thanh_cong = 0;
    int so_don_loi_bo_qua = 0;
    long long tong_doanh_thu_ca = 0;
    long long don_hang_lon_nhat = 0;

    printf("=== COFFEE_POS - CHOT SO DOANH THU CA LAM VIEC ===\n");
    printf("Nhap so luong hoa don trong ca: ");
    scanf("%d", &so_hoa_don_trong_ca);

    /* Neu so_hoa_don_trong_ca <= 0, dieu kien "i <= so_hoa_don_trong_ca"
       sai ngay tu dau nen vong lap for khong chay lan nao. */
    for (int i = 1; i <= so_hoa_don_trong_ca; i++) {
        long long gia_co_so = 0;
        char ky_tu_size = 0;
        int so_luong_topping = 0;
        int trang_thai_hoi_vien = 0;

        printf("\n--- Hoa don thu %d ---\n", i);
        printf("Gia co so (Size S, VND): ");
        scanf("%lld", &gia_co_so);
        printf("Size do uong (S/M/L): ");
        scanf(" %c", &ky_tu_size);
        printf("So luong topping goi them: ");
        scanf("%d", &so_luong_topping);
        printf("Trang thai hoi vien (1-Vang, 0-Thuong): ");
        scanf("%d", &trang_thai_hoi_vien);

        /* --- LOI THUONG GAP 2: TIN HIEU GIAN LAN / NGAT KHAN CAP ---
           So luong topping am (vi du -1, -999) duoc quy uoc la tin hieu
           POS bi can thiep trai phep hoac loi thiet bi nghiem trong.
           Phai NGAT NGAY toan bo ca lam viec (break), khong xu ly tiep
           hoa don nay va khong nhan them hoa don con lai trong ca. */
        if (so_luong_topping < 0) {
            printf("!!! CANH BAO KHAN CAP: Phat hien tin hieu bat thuong ");
            printf("(so luong topping am = %d) tai hoa don thu %d.\n", so_luong_topping, i);
            printf("!!! Ngat toan bo ca lam viec de bao ve du lieu doanh thu.\n");
            break;
        }

        /* --- LOI THUONG GAP 1: DON RAC / SAI CU PHAP NHAP LIEU ---
           Gia co so khong hop le (<= 0) hoac ky tu Size khong thuoc chuan
           S/M/L (khong phan biet hoa/thuong) la loi nhap lieu thong thuong,
           chi bo qua hoa don nay roi tiep tuc nhan hoa don ke tiep. */
        char size_chuan = (char) toupper((unsigned char) ky_tu_size);
        if (gia_co_so <= 0 ||
            (size_chuan != 'S' && size_chuan != 'M' && size_chuan != 'L')) {
            printf("--- CANH BAO: Hoa don thu %d du lieu khong hop le, ", i);
            printf("bo qua va chuyen sang hoa don tiep theo. ---\n");
            so_don_loi_bo_qua++;
            continue;
        }

        /* Tinh phu thu Size (S: +0, M: +6000, L: +10000). */
        long long phu_thu_size = 0;
        if (size_chuan == 'M') {
            phu_thu_size = 6000;
        } else if (size_chuan == 'L') {
            phu_thu_size = 10000;
        }

        /* Tinh phu thu Topping: 8000 VND / phan topping. */
        long long phu_thu_topping = (long long) so_luong_topping * 8000;

        /* Tong hoa don truoc uu dai hoi vien. */
        long long tong_hoa_don = gia_co_so + phu_thu_size + phu_thu_topping;

        /* Uu dai Hoi vien Vang: giam 10% tren tong hoa don. */
        if (trang_thai_hoi_vien == 1) {
            tong_hoa_don = tong_hoa_don - (tong_hoa_don * 10) / 100;
        }

        /* Cong don vao doanh thu ca va cap nhat thong ke. */
        tong_doanh_thu_ca += tong_hoa_don;
        so_don_thanh_cong++;

        if (tong_hoa_don > don_hang_lon_nhat) {
            don_hang_lon_nhat = tong_hoa_don;
        }

        printf("--> Hoa don thu %d thanh cong, tong tien: %lld VND\n", i, tong_hoa_don);
    }

    /* Bao cao tong hop ca lam viec - luon chay du bi break, continue,
       hay N <= 0, vi cac bien tong hop da khoi tao an toan bang 0. */
    printf("\n===================================================\n");
    printf("BAO CAO CHOT SO DOANH THU CA LAM VIEC\n");
    printf("===================================================\n");
    printf("Tong so don hang thanh cong      : %d\n", so_don_thanh_cong);
    printf("Tong so don hang loi bi bo qua    : %d\n", so_don_loi_bo_qua);
    printf("Tong doanh thu thuc te trong ca   : %lld VND\n", tong_doanh_thu_ca);
    printf("Gia tri hoa don lon nhat trong ca : %lld VND\n", don_hang_lon_nhat);

    return 0;
}
