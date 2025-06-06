#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"
#include "system.h"

#define LOG_FILE "nhatkyhethong.txt"

int resetFlag = 0;  // Biến toàn cục đánh dấu có reset không

void resetDuLieu() {
    // Ghi nhật ký trước khi xóa
    FILE* flog = fopen("nhatkyhethong.txt", "a");
    fprintf(flog, "[Log] Da reset toan bo du lieu.\n\n");
    fclose(flog);

    // Xoá nội dung file bằng cách mở với mode "w"
    FILE* fout = fopen("output.txt", "w");
    if (fout) fclose(fout);

    FILE* flog2 = fopen("nhatkyhethong.txt", "w");
    if (flog2) fclose(flog2);

    // Xoá dữ liệu trong bộ nhớ
    n = 0;
    precision = 0;
    for (int i = 0; i < MAX; i++) {
        x[i] = 0;
        y[i] = 0;
    }

    resetFlag = 1;
    printf("Da reset toan bo du lieu.\n");
}


void hienThiNhatKy() {
    FILE* flog = fopen(LOG_FILE, "r");

    if (!flog) {
        printf(" Khong tim thay nhat ky.\n");
        return;
    }

    printf("\n📄 Nhat ky he thong:\n");
    printf("--------------------------------\n");

    char line[256];
    int empty = 1;
    while (fgets(line, sizeof(line), flog)) {
        printf("%s", line);
        empty = 0;
    }

    if (empty) {
        printf(" Chua co log de hien thi.\n");
    }

    fclose(flog);
}

void quanLyHeThong() {
    clearBuffer();
    int chon;
    char buffer[100];

    while (1) {
        printf("=== Thao tac he thong ===\n");
        printf("1. Reset du lieu\n");
        printf("2. Hien thi nhat ky he thong\n");
        printf("0. Quay lai menu chinh\n");
        printf("Chon: ");

        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Loi khi doc du lieu. Vui long thu lai.\n");
            continue;
        }

        int temp;
        char r;
        int success = sscanf(buffer, "%d %c", &temp, &r);

        if (success == 1 && temp >= 0 && temp <= 2) {
            chon = temp;
            break;  // ra khỏi vòng lặp và xử lý bên ngoài
        } else {
            printf(" Lua chon khong hop le. Xin nhap lai.\n");
        }
    }

    // Xử lý chức năng sau khi đã có lựa chọn hợp lệ
    switch (chon) {
        case 1:
            resetDuLieu();
            break;
        case 2:
            hienThiNhatKy();
            break;
        case 0:
            return;
    }
}

