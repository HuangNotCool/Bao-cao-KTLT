#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"
#include "poly.h"

#define MAX_BAC 100
#define LOG_FILE "nhatkyhethong.txt"
#define OUTPUT_FILE "output.txt"

double ytable_local[MAX][MAX];  // Sao lưu y để dùng riêng
double heSoChinhTac[MAX];       // Hệ số dạng chính tắc a₀, a₁, a₂,...

// Hàm khởi tạo hệ số đa thức chính tắc rỗng
void khoiTaoDaThuc() {
    for (int i = 0; i < MAX_BAC; i++)
        heSoChinhTac[i] = 0;
}

// Nhân đa thức hiện tại với (x - xk)
void nhanDaThucVoi(double tam[], double xk) {
    for (int i = MAX_BAC - 1; i >= 1; i--)
        tam[i] = tam[i - 1] - xk * tam[i];
    tam[0] = -xk * tam[0];
}

// Cộng đa thức mới vào đa thức tổng
void congDaThuc(double ketqua[], double tam[], double heSo) {
    for (int i = 0; i < MAX_BAC; i++)
        ketqua[i] += tam[i] * heSo;
}

// Tính hệ số Newton dạng tiến (trích từ bảng sai phân)
void layHeSoTien(double heSoNewton[]) {
    for (int i = 0; i < n; i++)
        heSoNewton[i] = ytable_local[0][i];
}

// Tính hệ số Newton dạng lùi (trích từ bảng sai phân)
void layHeSoLui(double heSoNewton[]) {
    for (int i = 0; i < n; i++)
        heSoNewton[i] = ytable_local[n - 1][i];
}

// Tạo đa thức dạng chính tắc từ hệ số Newton
void taoDaThucChinhTac(double heSoNewton[], int isTien) {
    double tam[MAX_BAC];   // đa thức tạm thời

    khoiTaoDaThuc();
    double xk[MAX];
    for (int i = 0; i < n; i++) {
        tam[0] = 1;
        for (int j = 1; j < MAX_BAC; j++) tam[j] = 0;

        for (int j = 0; j < i; j++)
            xk[j] = isTien ? x[j] : x[n - 1 - j];

        for (int j = 0; j < i; j++)
            nhanDaThucVoi(tam, xk[j]);

        congDaThuc(heSoChinhTac, tam, heSoNewton[i]);
    }
}

void inDaThucRa(FILE* fout) {
    char fmt[10];
    sprintf(fmt, "%%.%dlf", precision);

    printf("\nDa thuc dang chinh tac:\nP(x) = ");
    fprintf(fout, "\nDa thuc dang chinh tac:\nP(x) = ");

    int daIn = 0;
    for (int i = 0; i < n; i++) {
        if (fabs(heSoChinhTac[i]) > 1e-10) {
            if (daIn) {
                printf(" + ");
                fprintf(fout, " + ");
            }
            printf(fmt, heSoChinhTac[i]);
            fprintf(fout, fmt, heSoChinhTac[i]);
            if (i >= 1) {
                printf("x");
                fprintf(fout, "x");
                if (i >= 2) {
                    printf("^%d", i);
                    fprintf(fout, "^%d", i);
                }
            }
            daIn = 1;
        }
    }

    if (!daIn) {
        printf("0");
        fprintf(fout, "0");
    }

    printf("\n");
    fprintf(fout, "\n");
}

void inDaThucNewton() {
    int chon;
    FILE* fout = fopen(OUTPUT_FILE, "a");
    FILE* flog = fopen(LOG_FILE, "a");

    // Sao chép y[] vào bảng sai phân địa phương
    for (int i = 0; i < n; i++)
        ytable_local[i][0] = y[i];

    // Tính sai phân tiến
    for (int j = 1; j < n; j++)
        for (int i = 0; i < n - j; i++)
            ytable_local[i][j] = ytable_local[i + 1][j - 1] - ytable_local[i][j - 1];

    // Tính sai phân lùi
    for (int j = 1; j < n; j++)
        for (int i = n - 1; i >= j; i--)
            ytable_local[i][j] = ytable_local[i][j - 1] - ytable_local[i - 1][j - 1];

    do {
        printf("\n=== In da thuc noi suy Newton ===\n");
        printf("1. In da thuc Newton tien\n");
        printf("2. In da thuc Newton lui\n");
        printf("0. Quay lai menu chinh\n");
        printf("Chon: ");
        scanf("%d", &chon);
        while (getchar() != '\n'); // clear buffer

        if (chon == 1 || chon == 2) {
            double heso[MAX];
            if (chon == 1) {
                fprintf(flog, "[Log] In da thuc Newton tien\n");
                layHeSoTien(heso);
                taoDaThucChinhTac(heso, 1);
            } else {
                fprintf(flog, "[Log] In da thuc Newton lui\n");
                layHeSoLui(heso);
                taoDaThucChinhTac(heso, 0);
            }

            inDaThucRa(fout);
            fprintf(flog, "[Log] Ket thuc chuc nang in da thuc\n\n");
        } else if (chon != 0) {
            printf("❌ Lua chon khong hop le. Xin nhap lai!\n");
        }

    } while (chon != 0);

    fclose(fout);
    fclose(flog);
}
