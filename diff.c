#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "input.h"
#include "diff.h"

#define LOG_FILE "nhatkyhethong.txt"
#define OUTPUT_FILE "output.txt"

double ytable[MAX][MAX]; // Bảng sai phân (copy từ y[])

void tinhSaiPhanTien(int n) {
    for (int j = 1; j < n; j++) {
        for (int i = 0; i < n - j; i++) {
            ytable[i][j] = ytable[i + 1][j - 1] - ytable[i][j - 1];
        }
    }
}

void tinhSaiPhanLui(int n) {
    for (int j = 1; j < n; j++) {
        for (int i = n - 1; i >= j; i--) {
            ytable[i][j] = ytable[i][j - 1] - ytable[i - 1][j - 1];
        }
    }
}

void inBangSaiPhan(FILE* fout) {
    char fmt[10];
    sprintf(fmt, "%%.%dlf", precision);

    printf("Bang sai phan tien:\n");
    fprintf(fout, "Bang sai phan tien:\n");

    for (int i = 0; i < n; i++) {
        printf("%-8.2lf", x[i]);
        fprintf(fout, "%-8.2lf", x[i]);

        for (int j = 0; j < n - i; j++) {
            printf("  ");
            printf(fmt, ytable[i][j]);
            fprintf(fout, "  ");
            fprintf(fout, fmt, ytable[i][j]);
        }
        printf("\n");
        fprintf(fout, "\n");
    }

    printf("\nBang sai phan lui:\n");
    fprintf(fout, "\nBang sai phan lui:\n");

    for (int i = 0; i < n; i++) {
        printf("%-8.2lf", x[i]);
        fprintf(fout, "%-8.2lf", x[i]);

        for (int j = 0; j <= i; j++) {
            printf("  ");
            printf(fmt, ytable[i][j]);
            fprintf(fout, "  ");
            fprintf(fout, fmt, ytable[i][j]);
        }
        printf("\n");
        fprintf(fout, "\n");
    }
}

void tinhBangSaiPhan() {
    FILE* fout = fopen(OUTPUT_FILE, "a");
    FILE* flog = fopen(LOG_FILE, "a");

    // Copy y[] vào ytable[i][0]
    for (int i = 0; i < n; i++) {
        ytable[i][0] = y[i];
    }

    tinhSaiPhanTien(n);
    tinhSaiPhanLui(n);

    fprintf(flog, "[Log] Thuc hien chuc nang 1: In bang sai phan\n");

    inBangSaiPhan(fout);

    fprintf(flog, "[Log] Ket thuc bang sai phan.\n\n");

    fclose(fout);
    fclose(flog);
}
