#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "input.h"
#include "poly.h"
#include "derivative.h"

#define MAX_BAC 100
#define LOG_FILE "nhatkyhethong.txt"
#define OUTPUT_FILE "output.txt"

extern double heSoChinhTac[MAX];  // Được tạo trong poly.c

// Tính đạo hàm của đa thức chính tắc tại x0
double daoHamTai(double x0) {
    double result = 0;
    for (int i = 1; i < n; i++) {
        result += i * heSoChinhTac[i] * pow(x0, i - 1);
    }
    return result;
}

void daoHamTaiMotDiem() {
    double x0;
    char fmt[10];
    sprintf(fmt, "%%.%dlf", precision);

    FILE* fout = fopen(OUTPUT_FILE, "a");
    FILE* flog = fopen(LOG_FILE, "a");

    // Cảnh báo nếu đa thức chưa được tính
    int isEmpty = 1;
    for (int i = 0; i < n; i++)
        if (fabs(heSoChinhTac[i]) > 1e-10)
            isEmpty = 0;

    if (isEmpty) {
        printf("❗ Hay tao da thuc noi suy truoc khi tinh.\n");
        fprintf(flog, "[Log] Loi: Chua co da thuc noi suy de tinh dao ham\n\n");
        fclose(fout);
        fclose(flog);
        return;
    }

    printf("\n=== Tinh gan dung dao ham cap 1 tai mot diem ===\n");
    printf("Nhap gia tri x can tinh dao ham: ");
    scanf("%lf", &x0);
    while (getchar() != '\n');

    double f1 = daoHamTai(x0);

    printf("P'(");
    printf(fmt, x0);
    printf(") = ");
    printf(fmt, f1);
    printf("\n");

    fprintf(fout, "\n--- Tinh dao ham P'(x) tai x = ");
    fprintf(fout, fmt, x0);
    fprintf(fout, " ---\n");
    fprintf(fout, "Ket qua: ");
    fprintf(fout, fmt, f1);
    fprintf(fout, "\n");

    fprintf(flog, "[Log] Tinh dao ham tai x = ");
    fprintf(flog, fmt, x0);
    fprintf(flog, ", Ket qua: ");
    fprintf(flog, fmt, f1);
    fprintf(flog, "\n\n");

    fclose(fout);
    fclose(flog);
}

void daoHamTaiCacMoc() {
    int chon;
    double h = x[1] - x[0];
    char fmt[10];
    sprintf(fmt, "%%.%dlf", precision);

    FILE* fout = fopen(OUTPUT_FILE, "a");
    FILE* flog = fopen(LOG_FILE, "a");

    printf("\n=== Tinh gan dung dao ham tai cac muc noi suy theo cong thuc 3 diem ===\n");
    printf("Chon cong thuc tinh:\n");
    printf("1. Dao ham tien\n");
    printf("2. Dao ham lui\n");
    printf("3. Trung tam\n");
    printf("0. Quay lai menu chinh\n");
    printf("Chon: ");
    scanf("%d", &chon);
    while (getchar() != '\n');

    if (chon < 0 || chon > 3) {
        printf("❌ Lua chon khong hop le.\n");
        fclose(fout);
        fclose(flog);
        return;
    }

    if (chon == 0) {
        fclose(fout);
        fclose(flog);
        return;
    }

    fprintf(flog, "[Log] Gan dung dao ham tai cac moc, loai %d\n", chon);

    printf("\n%-10s | %-15s\n", "x", "y' gan dung");
    printf("-----------------------------\n");
    fprintf(fout, "\n=== Dao ham gan dung (loai %d) ===\n", chon);
    fprintf(fout, "%-10s | %-15s\n", "x", "y' gan dung");
    fprintf(fout, "-----------------------------\n");

    int soDiemHople = 0;

    for (int i = 0; i < n; i++) {
        double dydx = 0;
        int tinhduoc = 1;

        if (chon == 1) { // Tiến
            if (i + 1 < n)
                dydx = (y[i + 1] - y[i]) / h;
            else
                tinhduoc = 0;
        } else if (chon == 2) { // Lùi
            if (i - 1 >= 0)
                dydx = (y[i] - y[i - 1]) / h;
            else
                tinhduoc = 0;
        } else if (chon == 3) { // Trung tâm
            if (i - 1 >= 0 && i + 1 < n)
                dydx = (y[i + 1] - y[i - 1]) / (2 * h);
            else
                tinhduoc = 0;
        }

        if (tinhduoc) {
            printf(fmt, x[i]);
            printf(" | ");
            printf(fmt, dydx);
            printf("\n");

            fprintf(fout, fmt, x[i]);
            fprintf(fout, " | ");
            fprintf(fout, fmt, dydx);
            fprintf(fout, "\n");

            soDiemHople++;
        }
    }

    if (soDiemHople == 0) {
        printf("Khong co diem thoa man dieu kien.\n");
        fprintf(flog, "[Log] Khong co diem nao thoa man dieu kien de tinh dao ham.\n\n");
    } else {
        printf("\nHoan tat tinh dao ham tai %d diem.\n", soDiemHople);
        fprintf(flog, "[Log] Tinh dao ham tai %d diem thanh cong.\n\n", soDiemHople);
    }

    fclose(fout);
    fclose(flog);
}

