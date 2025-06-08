#include <stdio.h>
#include <stdlib.h>
#include "input.h"
#include "menu.h"

void tinhBangSaiPhan();
void inDaThucNewton();
void tinhGiaTriHoocne();
void daoHamTaiMotDiem();
void daoHamTaiCacMoc();
void quanLyHeThong();

// Hàm chờ Enter để quay lại menu
void doiNhapEnter() {
    printf("\nNhan Enter de quay lai menu chinh...");
    while (getchar() != '\n');
    getchar();
}

// Hiển thị menu chính
void hienThiMenu() {
    printf("\n================ MENU ================\n");
    printf("1. In bang sai phan\n");
    printf("2. In da thuc noi suy Newton dang chinh tac\n");
    printf("3. Tinh gia tri tai 1 diem bang so do HOOCNE\n");
    printf("4. Tinh gan dung dao ham tai mot diem\n");
    printf("5. Tinh gan dung dao ham tai cac moc noi suy theo cong thuc 3 diem\n");
    printf("6. Thao tac he thong\n");
    printf("0. Thoat chuong trinh\n");
    printf("============================================\n");
    printf("Chon chuc nang: ");
}

// Thực thi menu chính
void chayMenu() {
    int luaChon;
    char buffer[100];
    nhapDuLieu();

    do {
        system("cls");
        hienThiMenu();

        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            luaChon = -1;
        } else {
            int temp;
            char r;
            if (sscanf(buffer, "%d %c", &temp, &r) == 1 && temp >= 0 && temp <= 6) {
                luaChon = temp;
            } else {
                luaChon = -1;
            }
        }

       switch (luaChon) {
    case 1: system("cls"); tinhBangSaiPhan(); break;
    case 2: system("cls"); inDaThucNewton(); break;
    case 3: system("cls"); tinhGiaTriHoocne(); break;
    case 4: system("cls"); daoHamTaiMotDiem(); break;
    case 5: system("cls"); daoHamTaiCacMoc(); break;
    case 6: system("cls"); quanLyHeThong(); break;
    case 0: printf("Da thoat chuong trinh.\n"); break;
    default: printf("Lua chon khong hop le. Xin nhap lai!\n"); break;
}

        if (luaChon != 0) doiNhapEnter();

    } while (luaChon != 0);
}
