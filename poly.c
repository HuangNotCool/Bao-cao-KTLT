#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "input.h"
#include "poly.h"

#define MAX_BAC 100
#define LOG_FILE "nhatkyhethong.txt"
#define OUTPUT_FILE "output.txt"

double ytable_local[MAX][MAX];  // Sao lưu y để dùng riêng
double heSoChinhTac[MAX];       // Hệ số dạng chính tắc a₀, a₁, a₂,...

// Khởi tạo đa thức chính tắc rỗng
void khoiTaoDaThuc() {
    for (int i = 0; i < MAX_BAC; i++)
        heSoChinhTac[i] = 0;
}

// Nhân đa thức với (x - xk)
void nhanDaThucVoi(double tam[], double xk) {
    for (int i = MAX_BAC - 1; i >= 1; i--)
        tam[i] = tam[i - 1] - xk * tam[i];
    tam[0] = -xk * tam[0];
}

// Cộng đa thức
void congDaThuc(double ketqua[], double tam[], double heSo) {
    for (int i = 0; i < MAX_BAC; i++)
        ketqua[i] += tam[i] * heSo;
}


// Lấy hệ số tiến/lùi
void layHeSoTien(double heso[]) {
    for (int i = 0; i < n; i++)
        heso[i] = ytable_local[0][i];
}

void layHeSoLui(double heso[]) {
    for (int i = 0; i < n; i++)
        heso[i] = ytable_local[n - 1][i];
}

// Tạo đa thức chính tắc
void taoDaThucChinhTac(double heso[], int isTien) {
    double tam[MAX_BAC];
    double xk[MAX];
    khoiTaoDaThuc();

    for (int i = 0; i < n; i++) {
        tam[0] = 1;
        for (int j = 1; j < MAX_BAC; j++) tam[j] = 0;

        for (int j = 0; j < i; j++)
            xk[j] = isTien ? x[j] : x[n - 1 - j];

        for (int j = 0; j < i; j++)
            nhanDaThucVoi(tam, xk[j]);

        congDaThuc(heSoChinhTac, tam, heso[i]);
    }
}

// In da thức chính tắc
void inDaThucRa(FILE* fout) {
    char fmt[10];
    sprintf(fmt, "%%.%dlf", precision);

    printf("\nDa thuc dang chinh tac:\nP(x) = ");
    fprintf(fout, "\nDa thuc dang chinh tac:\nP(x) = ");

    int daIn = 0;
    for (int i = 0; i < n; i++) {
        if (fabs(heSoChinhTac[i]) > 1e-10) {
            if (daIn) { printf(" + "); fprintf(fout, " + "); }
            printf(fmt, heSoChinhTac[i]);
            fprintf(fout, fmt, heSoChinhTac[i]);
            if (i >= 1) {
                printf("x"); fprintf(fout, "x");
                if (i >= 2) { printf("^%d", i); fprintf(fout, "^%d", i); }
            }
            daIn = 1;
        }
    }
    if (!daIn) { printf("0"); fprintf(fout, "0"); }
    printf("\n"); fprintf(fout, "\n");
}

// In đa thức Newton chuẩn (tiến hoặc lùi)
void inCongThuc(double heso[], int isTien, FILE* fout) {
    char fmt[10];
    sprintf(fmt, "%%.%dlf", precision);

    printf("\nDa thuc Newton %s:\nP(x) = ", isTien ? "tien" : "lui");
    fprintf(fout, "\nDa thuc Newton %s:\nP(x) = ", isTien ? "tien" : "lui");

    int daIn = 0;
    for (int i = 0; i < n; i++) {
        if (fabs(heso[i]) < 1e-10) continue;

        if (daIn) { printf(" + "); fprintf(fout, " + "); }
        printf(fmt, heso[i]); fprintf(fout, fmt, heso[i]);

        for (int j = 0; j < i; j++) {
            double val = isTien ? x[j] : x[n - 1 - j];
            printf("(x - "); fprintf(fout, "(x - ");
            printf(fmt, val); fprintf(fout, fmt, val);
            printf(")"); fprintf(fout, ")");
        }
        daIn = 1;
    }
    if (!daIn) { printf("0"); fprintf(fout, "0"); }
    printf("\n"); fprintf(fout, "\n");
}

// Giao diện in da thức
void inDaThucNewton() {
    int chon;
    FILE* fout = fopen(OUTPUT_FILE, "a");
    FILE* flog = fopen(LOG_FILE, "a");

    tinhSaiPhanLocal();

    do {
        printf("\n=== In da thuc noi suy Newton ===\n");
        printf("1. In da thuc Newton tien\n");
        printf("2. In da thuc Newton lui \n");
        printf("0. Quay lai Menu chinh\n");

        int temp; char c;
        printf("Chon: ");
        if (scanf("%d%c", &temp, &c) != 2 || c != '\n') {
            printf("Lua chon khong hop le. Xin nhap lai.\n");
            clearBuffer(); continue;
        }

        if (temp == 1 || temp == 2) {
            double heso_tien[MAX], heso_lui[MAX];
            layHeSoTien(heso_tien);
            layHeSoLui(heso_lui);

            if (temp == 1) {
                fprintf(flog, "[Log] In da thuc Newton tien\n");
                inCongThuc(heso_tien, 1, fout);
            } else {
                fprintf(flog, "[Log] In da thuc Newton lui\n");
                inCongThuc(heso_lui, 0, fout);
            }

            taoDaThucChinhTac(heso_tien, 1); // Luon dung tien de tao chinh tac
            inDaThucRa(fout);
            fprintf(flog, "[Log] Ket thuc chuc nang in da thuc\n\n");
        } else if (temp == 0) break;
        else printf("Gia tri khong hop le.\n");
    } while (1);

    fclose(fout);
    fclose(flog);
}
