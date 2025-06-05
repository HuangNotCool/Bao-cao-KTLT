#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "input.h"

int n;
double x[MAX], y[MAX];
int precision;

// Kiểm tra x[] có cách đều không
int kiemTraCachDeu() {
    double d = x[1] - x[0];
    for (int i = 2; i < n; i++) {
        if (fabs((x[i] - x[i - 1]) - d) > 1e-6)
            return 0;
    }
    return 1;
}

// Kiểm tra x[] có bị trùng không
int kiemTraTrung() {
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (fabs(x[i] - x[j]) < 1e-9)
                return 1;
    return 0;
}

void nhapDuLieu() {
    do {
        printf("Nhap so diem noi suy (n > 1): ");
        scanf("%d", &n);
        if (n < 2)
            printf("❌ So diem phai > 1. Xin nhap lai!\n");
    } while (n < 2);

    printf("\nNhap cac gia tri x y tuong ung:\n");
    for (int i = 0; i < n; i++) {
        printf("x[%d] = ", i);
        scanf("%lf", &x[i]);
        printf("y[%d] = ", i);
        scanf("%lf", &y[i]);
    }

    // Kiểm tra x[] không trùng
    while (kiemTraTrung()) {
        printf("\n❌ Cac gia tri x khong duoc trung nhau. Xin nhap lai tu dau:\n");
        for (int i = 0; i < n; i++) {
            printf("x[%d] = ", i);
            scanf("%lf", &x[i]);
            printf("y[%d] = ", i);
            scanf("%lf", &y[i]);
        }
    }

    // Kiểm tra x[] cách đều
    while (!kiemTraCachDeu()) {
        printf("\n❌Cac gia tri x phai cach deu nhau. Xin nhap lai tu dau:\n");
        for (int i = 0; i < n; i++) {
            printf("x[%d] = ", i);
            scanf("%lf", &x[i]);
            printf("y[%d] = ", i);
            scanf("%lf", &y[i]);
        }
    }

    do {
        printf("\nNhap vao so chu so thap phan muon hien thi (0 den 15): ");
        scanf("%d", &precision);
        if (precision < 0 || precision > 15)
            printf("❌ Gia tri khong hop le.\n");
    } while (precision < 0 || precision > 15);
}
