#include <stdio.h>
#include <stdlib.h>
#include "input.h"

// TẠM khai báo các hàm xử lý từng module
void tinhBangSaiPhan();
void inDaThucNewton();
void tinhGiaTriHoocne();
void daoHamTaiMotDiem();
void daoHamTaiCacMoc();
void quanLyHeThong();

// Hàm chờ người dùng nhấn Enter để quay lại menu
void doiNhapEnter() {
    printf("\nNhan Enter de quay lai menu chinh...");
    while (getchar() != '\n'); // Ăn ký tự thừa
    getchar(); // Đợi Enter thật
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

int main() {
	int luaChon;
    nhapDuLieu(); // Gọi nhập dữ liệu đầu vào 1 lần duy nhất int luaChon;

    do {
        system("cls"); // Xóa màn hình (dùng được trong Dev-C++)
        hienThiMenu();

        if (scanf("%d", &luaChon) != 1) {
            while (getchar() != '\n'); // clear bộ đệm
            luaChon = -1;
        }

        system("cls"); // Xóa màn hình trước khi xử lý

        switch (luaChon) {
            case 1:
                tinhBangSaiPhan();
                doiNhapEnter();
                break;
            case 2:
                inDaThucNewton();
                doiNhapEnter();
                break;
            case 3:
                tinhGiaTriHoocne();
                doiNhapEnter();
                break;
            case 4:
                daoHamTaiMotDiem();
                doiNhapEnter();
                break;
            case 5:
                daoHamTaiCacMoc();
                doiNhapEnter();
                break;
            case 6:
                quanLyHeThong();
                doiNhapEnter();
                break;
            case 0:
                printf("Da thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le. Xin nhap lai!\n");
                doiNhapEnter();
        }

    } while (luaChon != 0);

    return 0;
}
