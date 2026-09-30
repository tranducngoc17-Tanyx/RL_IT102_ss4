/*
 * =============================================================================
 * BAI TAP 03: PHAN TICH TRADE-OFF VONG LAP FOR VS WHILE (NESTED IF-ELSE
 *             VS GUARD CLAUSES) TRONG XU LY GIAO DICH DO UONG
 * He thong: Highlands POS - Shift Revenue Audit Engine
 * =============================================================================
 *
 * ---------------------------------------------------------------------------
 * A. PHAN TICH INPUT / OUTPUT
 * ---------------------------------------------------------------------------
 * INPUT:
 *   - tong_so_giao_dich (int): So luong giao dich N can kiem toan trong ca.
 *   Voi MOI giao dich (lap toi da N lan):
 *   - ma_do_uong (int): -1 (ngat khan cap), 0 (huy don), 1/2/3 (ma mon hop le).
 *   - size (int)      : chi nhap khi ma_do_uong hop le (1,2,3). 1=S,2=M,3=L.
 *   - so_luong_topping (int): chi nhap khi ma_do_uong hop le. Hop le: 0..5.
 *   - the_gold (int)  : chi nhap khi ma_do_uong hop le. 1=co the, 0=khong.
 *
 * OUTPUT:
 *   - trang_thai_ca (chuoi thong bao): Hoan thanh binh thuong / Bi ngat khan cap.
 *   - so_giao_dich_thanh_cong (int)
 *   - so_giao_dich_bi_huy (int)         (ma_do_uong == 0)
 *   - so_giao_dich_loi_du_lieu (int)    (ma rac hoac size/topping sai lech)
 *   - tong_doanh_thu_ca (long long, VND)
 *
 * ---------------------------------------------------------------------------
 * B. DE XUAT 2 GIAI PHAP KY THUAT
 * ---------------------------------------------------------------------------
 *
 * GIAI PHAP 1 - LEGACY APPROACH (Nested if-else, khong continue/break):
 *   Tu duy: chi tinh tien khi TAT CA dieu kien deu dung, long dieu kien
 *   vao nhau nhieu tang. Minh hoa cau truc (khong dung lam code chinh):
 *
 *       for (i = 1; i <= N; i++) {
 *           if (ma_do_uong != -1) {                  // tang 1
 *               if (ma_do_uong != 0) {                // tang 2
 *                   if (ma_do_uong == 1 || ma_do_uong == 2 || ma_do_uong == 3) { // tang 3
 *                       if (size == 1 || size == 2 || size == 3) {              // tang 4
 *                           if (topping >= 0 && topping <= 5) {                 // tang 5
 *                               // ... tinh tien (nam sau trong 5 tang) ...
 *                           }
 *                       }
 *                   }
 *               }
 *           } else {
 *               // xu ly ngat khan cap - nhung van phai "chay het" than
 *               // vong lap vi khong co break, kho dung ngay tuc khac.
 *           }
 *       }
 *
 *   Nhuoc diem: do sau long (nesting depth) tang toi 5 tang cho 1 giao
 *   dich hop le; muon them 1 dieu kien nghiep vu moi (vi du kiem tra ma
 *   khuyen mai) phai chen them 1 tang if nua, code ngay cang thu hep va
 *   kho doc; khong co "break" nen tin hieu ngat khan cap (-1) khong the
 *   thoat vong lap ngay, phai dung bien co (flag) roi kiem tra flag do o
 *   NHIEU noi trong than vong lap con lai -> de sot logic, dan den loi.
 *
 * GIAI PHAP 2 - OPTIMIZED APPROACH (Guard Clauses + continue/break):
 *   Tu duy: kiem tra va LOAI BO SOM (early exit) tung loai du lieu xau
 *   ngay khi phat hien, tra vong lap ve trang thai "phang" (flat), moi
 *   dieu kien loi chi nam trong 1 khoi if doc lap, khong long nhau:
 *       - ma_do_uong == -1        -> break (ngat khan cap, thoat for ngay)
 *       - ma_do_uong == 0         -> continue (huy don, qua giao dich ke)
 *       - ma rac (!= -1,0,1,2,3)  -> continue (loi du lieu, qua giao dich ke)
 *       - size/topping sai lech   -> continue (loi du lieu, qua giao dich ke)
 *       - con lai: chac chan hop le -> tinh tien binh thuong, khong long if.
 *
 * ---------------------------------------------------------------------------
 * C. BANG SO SANH 2 GIAI PHAP
 * ---------------------------------------------------------------------------
 *  ---------------------------------------------------------------------------------------------------
 * | Tieu chi                    | GP1: Nested if-else            | GP2: Guard Clauses (chon)         |
 * ---------------------------------------------------------------------------------------------------
 * | So tang long logic           | Toi da 5 tang cho 1 giao dich  | Toi da 1 tang (cac if doc lap)    |
 * | Do phuc tap duy tri          | Cao - sua 1 cho de gay loi cho | Thap - moi rule la 1 khoi doc     |
 * |                              | khac vi cac tang long nhau     | lap, sua/them khong anh huong     |
 * |                              |                                | rule khac                         |
 * | Toc do loai bo du lieu rac   | Cham - phai di qua het cac tang| Nhanh - continue thoat ngay ra    |
 * |                              | if truoc khi biet la du lieu rac| khoi than vong lap tai buoc phat  |
 * |                              |                                | hien dau tien                     |
 * | Kha nang ngat khan cap       | Kho - khong co break, phai dung| De - break thoat for ngay lap tuc,|
 * |                              | flag va kiem tra flag rai rac  | dam bao "chot doanh thu tuc thoi" |
 * | Kha nang mo rong nghiep vu   | Kho - them rule moi phai chen  | De - chi can them 1 guard clause  |
 * |                              | them 1 tang if long vao trong  | moi, khong pha vo cau truc cu     |
 * ---------------------------------------------------------------------------------------------------
 *
 * LAP LUAN CHON GIAI PHAP: Chon GIAI PHAP 2 (Guard Clauses + continue/break)
 * vi day la he thong Real-time Audit xu ly hang tram giao dich/ca: yeu cau
 * (1) phan hoi nhanh khi gap du lieu rac (continue thoat ngay, khong di qua
 * cac tang kiem tra thua), (2) phan ung tuc thoi voi tin hieu an ninh/loi
 * thiet bi (break dung tuyet doi dung ca ngay tai thoi diem phat hien, dam
 * bao doanh thu chot dung so voi thuc te), va (3) de bao tri/mo rong quy
 * tac nghiep vu moi trong tuong lai ma khong lam tang do sau long code.
 *
 * ---------------------------------------------------------------------------
 * D. PSEUDOCODE CHO GIAI PHAP DA CHON (GUARD CLAUSES)
 * ---------------------------------------------------------------------------
 *   1. Nhap N.
 *   2. Neu N <= 0 -> in loi nghiep vu -> DUNG chuong trinh (loi thuong gap 1).
 *   3. Khoi tao: tong_doanh_thu_ca=0, so_thanh_cong=0, so_bi_huy=0,
 *      so_loi_du_lieu=0, bi_ngat_khan_cap=0.
 *   4. Lap for i = 1 den N:
 *      4.1 Nhap ma_do_uong.
 *      4.2 GUARD: neu ma_do_uong == -1 -> bao ngat khan cap -> break.
 *      4.3 GUARD: neu ma_do_uong == 0  -> tang so_bi_huy -> continue.
 *      4.4 GUARD: neu ma_do_uong khong thuoc {1,2,3} -> tang so_loi_du_lieu
 *          -> continue.
 *      4.5 Nhap size, so_luong_topping, the_gold.
 *      4.6 GUARD: neu size khong thuoc {1,2,3} HOAC topping <0 hoac >5
 *          -> tang so_loi_du_lieu -> continue.
 *      4.7 Tinh gia_co_ban theo ma_do_uong; phu_thu_size theo size;
 *          phu_thu_topping = topping * 8000.
 *      4.8 tong_tien_mon = gia_co_ban + phu_thu_size + phu_thu_topping.
 *      4.9 Neu the_gold == 1 -> tong_tien_mon = tong_tien_mon * 90 / 100
 *          (nhan truoc, chia sau de khong troi so thap phan - loi thuong gap 5).
 *      4.10 Cong tong_tien_mon vao tong_doanh_thu_ca; tang so_thanh_cong.
 *   5. In bao cao chot ca (trang thai, so lieu thong ke, tong doanh thu).
 *
 *   Bien dich: gcc -std=c11 main.c -o main
 * =============================================================================
 */

#include <stdio.h>

int main() {
    int tong_so_giao_dich = 0;

    printf("=== HIGHLANDS POS - SHIFT REVENUE AUDIT ENGINE ===\n");
    printf("Nhap tong so giao dich trong ca (N): ");
    scanf("%d", &tong_so_giao_dich);

    /* LOI THUONG GAP 1: N <= 0 la du lieu ca lam viec khong hop le
       -> xuat thong bao loi nghiep vu va DUNG chuong trinh ngay, khong
       chay vong lap va khong in bao cao doanh thu. */
    if (tong_so_giao_dich <= 0) {
        printf("Loi nghiep vu: Tong so giao dich (N) phai la so nguyen duong.\n");
        printf("Chuong trinh dung lai.\n");
        return 0;
    }

    long long tong_doanh_thu_ca = 0;
    int so_giao_dich_thanh_cong = 0;
    int so_giao_dich_bi_huy = 0;
    int so_giao_dich_loi_du_lieu = 0;
    int bi_ngat_khan_cap = 0; /* co (flag) chi de in bao cao, khong dung de dieu khien luong */

    for (int i = 1; i <= tong_so_giao_dich; i++) {
        int ma_do_uong = 0;

        printf("\n--- Giao dich thu %d ---\n", i);
        printf("Ma do uong (-1:ngat khan cap, 0:huy don, 1-3:mon hop le): ");
        scanf("%d", &ma_do_uong);

        /* GUARD CLAUSE 1: Tin hieu ngat khan cap. Loi thuong gap 4 duoc
           xu ly tu nhien: neu -1 xuat hien ngay i=1, break xay ra truoc
           khi cham vao tong_doanh_thu_ca nen doanh thu ca van la 0 VND. */
        if (ma_do_uong == -1) {
            printf("!!! NGAT KHAN CAP: Phat hien tin hieu -1 tai giao dich thu %d.\n", i);
            printf("!!! Chot doanh thu ngay tai thoi diem hien tai, dung nhan giao dich moi.\n");
            bi_ngat_khan_cap = 1;
            break;
        }

        /* GUARD CLAUSE 2: Don bi huy tai quay - bo qua, xu ly ngay giao
           dich tiep theo, khong tinh vao doanh thu, khong tinh la loi. */
        if (ma_do_uong == 0) {
            printf("--- Giao dich thu %d: khach huy don tai quay, bo qua. ---\n", i);
            so_giao_dich_bi_huy++;
            continue;
        }

        /* GUARD CLAUSE 3: Ma do uong rac, khong thuoc tap chuan {-1,0,1,2,3}. */
        if (ma_do_uong != 1 && ma_do_uong != 2 && ma_do_uong != 3) {
            printf("--- Giao dich thu %d: ma do uong khong hop le (%d), bo qua. ---\n",
                   i, ma_do_uong);
            so_giao_dich_loi_du_lieu++;
            continue;
        }

        /* Den day, ma_do_uong chac chan la 1, 2 hoac 3 -> tiep tuc nhap
           size, topping, the thanh vien de tinh tien. */
        int size = 0;
        int so_luong_topping = 0;
        int the_gold = 0;

        printf("Size (1:S, 2:M, 3:L): ");
        scanf("%d", &size);
        printf("So luong topping (0-5): ");
        scanf("%d", &so_luong_topping);
        printf("The Gold (1:co, 0:khong): ");
        scanf("%d", &the_gold);

        /* GUARD CLAUSE 4: Size hoac so luong topping sai lech - loi du
           lieu order, khong phai gian lan, chi bo qua mon nay. */
        if ((size != 1 && size != 2 && size != 3) ||
            so_luong_topping < 0 || so_luong_topping > 5) {
            printf("--- Giao dich thu %d: size/topping sai lech, bo qua. ---\n", i);
            so_giao_dich_loi_du_lieu++;
            continue;
        }

        /* Tu day tro xuong, khong con dieu kien loi nao nua (dac trung
           cua Guard Clauses): logic tinh tien nam "phang", khong long if. */
        long long gia_co_ban = 0;
        if (ma_do_uong == 1) {
            gia_co_ban = 29000; /* Phin Sua Da */
        } else if (ma_do_uong == 2) {
            gia_co_ban = 39000; /* Tra Sen Vang */
        } else {
            gia_co_ban = 49000; /* Freeze Ca Phe */
        }

        long long phu_thu_size = 0;
        if (size == 2) {
            phu_thu_size = 6000;
        } else if (size == 3) {
            phu_thu_size = 10000;
        }

        long long phu_thu_topping = (long long) so_luong_topping * 8000;

        long long tong_tien_mon = gia_co_ban + phu_thu_size + phu_thu_topping;

        /* LOI THUONG GAP 5: Nhan truoc roi moi chia (* 90 / 100) de dam
           bao ket qua la so nguyen VND chinh xac, khong troi thap phan. */
        if (the_gold == 1) {
            tong_tien_mon = tong_tien_mon * 90 / 100;
        }

        tong_doanh_thu_ca += tong_tien_mon;
        so_giao_dich_thanh_cong++;

        printf("--> Giao dich thu %d thanh cong, thanh tien: %lld VND\n", i, tong_tien_mon);
    }

    printf("\n===================================================\n");
    printf("BAO CAO CHOT CA - HIGHLANDS POS AUDIT ENGINE\n");
    printf("===================================================\n");
    if (bi_ngat_khan_cap == 1) {
        printf("Trang thai ca            : BI NGAT KHAN CAP GIUA CA\n");
    } else {
        printf("Trang thai ca            : HOAN THANH BINH THUONG\n");
    }
    printf("So giao dich thanh cong   : %d\n", so_giao_dich_thanh_cong);
    printf("So giao dich bi huy       : %d\n", so_giao_dich_bi_huy);
    printf("So giao dich loi du lieu  : %d\n", so_giao_dich_loi_du_lieu);
    printf("Tong doanh thu ca         : %lld VND\n", tong_doanh_thu_ca);

    return 0;
}
