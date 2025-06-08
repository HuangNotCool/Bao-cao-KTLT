#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "input.h"

int n;
double x[MAX], y[MAX];
int precision;

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Hàm kiểm tra x có cách đều không
int kiemTraCachDeu() {
    double d = x[1] - x[0];
    for (int i = 2; i < n; i++) {
        if (fabs((x[i] - x[i - 1]) - d) > 1e-6)
            return 0;
    }
    return 1;
}

// Hàm kiểm tra x có bị trùng không
int kiemTraTrung() {
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (fabs(x[i] - x[j]) < 1e-9)
                return 1;
    return 0;
}

void nhapDuLieu() {
   void clearBuffer() {
    while (getchar() != '\n');
}
while (1) {
    int temp;
    char c;
    printf("Nhap so diem noi suy (n > 1): ");
    if (scanf("%d%c", &temp, &c) != 2 || c != '\n') {
        printf("Du lieu khong hop le. Xin nhap vao so nguyen.\n");
        clearBuffer();
        continue;
    }

    if (temp < 2) {
        printf("Gia tri khong hop le.\n");
    } else {
        n = temp;
        break;
    }
}

    printf("\nNhap cac gia tri x y tuong ung:\n");
    for (int i = 0; i < n; i++) {
    // Nhập x[i]
    while (1) {
        printf("x[%d] = ", i);
        if (scanf("%lf", &x[i]) == 1) {
            break;
        } else {
            printf("Gia tri khong hop le. Xin hay nhap so thuc.\n", i);
            clearBuffer();
        }
    }

    // Nhập y[i]
    while (1) {
        printf("y[%d] = ", i);
        if (scanf("%lf", &y[i]) == 1) {
            break;
        } else {
            printf("Gia tri khong hop le. Xin hay nhap so thuc.\n", i);
            clearBuffer();
        }
    }
}

    // Gọi hàm kiểm tra trùng
    while (kiemTraTrung()) {
        printf("\nCac gia tri x khong duoc trung nhau. Xin nhap lai tu dau:\n");
        for (int i = 0; i < n; i++) {
            printf("x[%d] = ", i);
            scanf("%lf", &x[i]);
            printf("y[%d] = ", i);
            scanf("%lf", &y[i]);
        }
    }

    // Gọi hàm kiểm tra cách đều
    while (!kiemTraCachDeu()) {
        printf("\nCac gia tri x phai cach deu nhau. Xin nhap lai tu dau:\n");
        for (int i = 0; i < n; i++) {
            printf("x[%d] = ", i);
            scanf("%lf", &x[i]);
            printf("y[%d] = ", i);
            scanf("%lf", &y[i]);
        }
    }

  while (1) {
    printf("\nNhap so chu so thap phan hien thi (0 den 15): ");
    int temp;
    char c;
    if (scanf("%d%c", &temp, &c) != 2 || c != '\n') {
        printf("Du lieu khong hop le. Xin nhap vao so nguyen.\n");
        clearBuffer();
        continue;
    }

    if (temp < 0 || temp > 15) {
        printf("Gia tri khong hop le.\n");
    } else {
        precision = temp;
        break;
    }
}

}
