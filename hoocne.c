#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "input.h"
#include "hoocne.h"

#define LOG_FILE "nhatkyhethong.txt"
#define OUTPUT_FILE "output.txt"

double ytable_local[MAX][MAX];

// Tính sai phân tiến & lùi
void tinhSaiPhanLocal() {
    for (int i = 0; i < n; i++)
        ytable_local[i][0] = y[i];

    // Tiến
    for (int j = 1; j < n; j++)
        for (int i = 0; i < n - j; i++)
            ytable_local[i][j] = ytable_local[i + 1][j - 1] - ytable_local[i][j - 1];

    // Lùi
    for (int j = 1; j < n; j++)
        for (int i = n - 1; i >= j; i--)
            ytable_local[i][j] = ytable_local[i][j - 1] - ytable_local[i - 1][j - 1];
}

void tinhGiaTriHoocne() {
	double x0;
    int chon;
    FILE* fout = fopen(OUTPUT_FILE, "a");
    FILE* flog = fopen(LOG_FILE, "a");

    tinhSaiPhanLocal();

    printf("\n=== Tinh gia tri tai 1 diem bang so do HOOCNE ===\n");
    while (1) {
    printf("Nhap gia tri x can noi suy: ");
    if (scanf("%lf", &x0) == 1) {
        clearBuffer();
        break;
    }
    printf("Du lieu khong hop le. Xin nhap lai.\n");
    clearBuffer();
}
	char buffer[100];
while (1) {
    printf("Chon phuong phap tinh:\n");
    printf("1. Newton tien\n");
    printf("2. Newton lui\n");

    printf("Chon: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        printf("Lua chon khong hop le. Xin nhap lai.\n");
        continue;
    }

    int temp;
    char r;
    int success = sscanf(buffer, "%d %c", &temp, &r);

    if (success == 1 && (temp == 1 || temp == 2)) {
        chon = temp;
        break;
    } else {
        printf("Lua chon khong hop le. Xin nhap lai.\n");
    }
}


    fprintf(flog, "[Log] Tinh gia tri tai x = %.5lf bang so do HOOCNE (%s)\n",
            x0, (chon == 1) ? "tien" : "lui");
    fprintf(fout, "\n--- Tinh P(%.5lf) theo so do HOOCNE ---\n", x0);

    char fmt[10];
    sprintf(fmt, "%%.%dlf", precision);

    double p = 0;
    printf("\nCac buoc thuc hien:\n");
    fprintf(fout, "Cac buoc thuc hien:\n");

    if (chon == 1) {
        // Newton tiến
        double h = x[1] - x[0];
        double t = (x0 - x[0]) / h;
        double q = ytable_local[0][n - 1];
        
        printf("b[%d] = ", n - 1);
		printf(fmt, q);
		printf("\n");
        fprintf(fout, "b[%d] = %.10lf\n", n - 1, q);

        for (int i = n - 2; i >= 0; i--) {
            q = ytable_local[0][i] + (t - i) * q;

            printf("b[%d] = y[0][%d] + (t - %d) * b[%d] = ", i, i, i, i + 1);
            printf(fmt, ytable_local[0][i]);
            printf(" + (");
			printf(fmt, t);
			printf(" - %d) * ", i);
			printf(fmt, q - ytable_local[0][i]);
			printf(" = ");
			printf(fmt, q);
			printf("\n");

            fprintf(fout, "b[%d] = y[0][%d] + (t - %d) * b[%d] = ", i, i, i, i + 1);
            fprintf(fout, fmt, ytable_local[0][i]);
            fprintf(fout, " + (%.4lf - %d) * %.10lf = %.10lf\n", t, i, q - ytable_local[0][i], q);
        }

        p = q;
    } else {
        // Newton lùi
        double h = x[1] - x[0];
        double t = (x0 - x[n - 1]) / h;
        double q = ytable_local[n - 1][n - 1];
        
        printf("b[%d] = ", n - 1);
		printf(fmt, q);
		printf("\n");
        fprintf(fout, "b[%d] = %.10lf\n", n - 1, q);

               for (int i = n - 2; i >= 0; i--) {
            q = ytable_local[n - 1][i] + (t + i - (n - 1)) * q;

            printf("b[%d] = y[%d][%d] + (t + %d - %d) * b[%d] = ", i, n - 1, i, i, n - 1, i + 1);
            printf(fmt, ytable_local[n - 1][i]);
            printf(" + ");
			printf(fmt, t + i - (n - 1));
			printf(" * ");
			printf(fmt, q - ytable_local[n - 1][i]);
			printf(" = ");
			printf(fmt, q);
			printf("\n");

            fprintf(fout, "b[%d] = y[%d][%d] + (t + %d - %d) * b[%d] = ", i, n - 1, i, i, n - 1, i + 1);
            fprintf(fout, fmt, ytable_local[n - 1][i]);
            fprintf(fout, " + (%.4lf) * %.10lf = %.10lf\n", t + i - (n - 1), q - ytable_local[n - 1][i], q);
        }

        p = q;
    }

    // In kết luận
    printf("\nKet luan: P(");
	printf(fmt, x0);
	printf(") = ");
	printf(fmt, p);
    printf("\n");

    fprintf(fout, "\nKet luan: P(%.5lf) = ", x0);
    fprintf(fout, fmt, p);
    fprintf(fout, "\n\n");

    fprintf(flog, "[Log] Da thuc hien tinh P(%.5lf) = ", x0);
    fprintf(flog, fmt, p);
    fprintf(flog, "\n\n");

    fclose(fout);
    fclose(flog);
}
