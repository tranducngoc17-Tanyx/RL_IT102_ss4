#include <stdio.h>

int main() {
    int soDon;
    int i;

    int maTrangThai;
    int size;
    int soTopping;
    int gold;

    int soDonThanhCong = 0;
    int soDonBoQua = 0;

    double giaGoc;
    double tienSize;
    double tienTopping;
    double tongTruocGiam;
    double tienGiam;
    double tongDon;
    double doanhThu = 0;

    printf("===== HIGHLANDS COFFEE POS =====\n");

    printf("Nhap so luong don hang trong ca: ");
    scanf("%d", &soDon);

    for (i = 1; i <= soDon; i++) {
        printf("\n===== DON HANG %d =====\n", i);

        printf("Ma trang thai don hang:\n");
        printf("1. Don binh thuong\n");
        printf("2. Don loi nguyen lieu / khach huy\n");
        printf("3. Dung ca khan cap\n");
        printf("Nhap ma trang thai: ");
        scanf("%d", &maTrangThai);

        if (maTrangThai == 2) {
            printf("Don hang %d bi huy/bo qua.\n", i);
            soDonBoQua++;
            continue;
        }

        if (maTrangThai == 3) {
            printf("Phat hien su co khan cap. Dung ca ban hang.\n");
            break;
        }

        printf("Nhap gia goc Size S: ");
        scanf("%lf", &giaGoc);

        printf("Chon Size:\n");
        printf("1. Size S\n");
        printf("2. Size M (+6000)\n");
        printf("3. Size L (+10000)\n");
        printf("Nhap Size: ");
        scanf("%d", &size);

        if (size == 1) {
            tienSize = giaGoc;
        } else if (size == 2) {
            tienSize = giaGoc + 6000;
        } else if (size == 3) {
            tienSize = giaGoc + 10000;
        } else {
            printf("Size khong hop le. Bo qua don hang.\n");
            soDonBoQua++;
            continue;
        }

        printf("Nhap so luong topping: ");
        scanf("%d", &soTopping);

        tienTopping = soTopping * 8000;

        printf("Khach co the thanh vien Gold?\n");
        printf("1. Co\n");
        printf("0. Khong\n");
        printf("Nhap lua chon: ");
        scanf("%d", &gold);

        tongTruocGiam = tienSize + tienTopping;
        tienGiam = 0;

        if (gold == 1) {
            tienGiam = tongTruocGiam * 0.10;
        }

        tongDon = tongTruocGiam - tienGiam;

        doanhThu = doanhThu + tongDon;
        soDonThanhCong++;

        printf("\n--- HOA DON %d ---\n", i);
        printf("Gia Size: %.0f VND\n", tienSize);
        printf("Tien topping: %.0f VND\n", tienTopping);
        printf("Tien truoc giam: %.0f VND\n", tongTruocGiam);
        printf("Tien giam: %.0f VND\n", tienGiam);
        printf("Tong thanh toan: %.0f VND\n", tongDon);
    }

    printf("\n=================================\n");
    printf("       BAO CAO KET THUC CA\n");
    printf("=================================\n");
    printf("So don hoan thanh: %d\n", soDonThanhCong);
    printf("So don bi huy/bo qua: %d\n", soDonBoQua);
    printf("Tong doanh thu: %.0f VND\n", doanhThu);
    printf("=================================\n");

    return 0;
}
