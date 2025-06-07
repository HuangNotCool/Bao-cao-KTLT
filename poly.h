#ifndef POLY_H
#define POLY_H

#include "input.h"

void inDaThucNewton(); // Gọi từ main menu – hiển thị menu phụ + xử lý
void tinhSaiPhanLocal(); // Tính bảng sai phân local
void layHeSoTien(double[]); // Lấy hệ số sai phân tiến từ bảng local
void inCongThuc(double heso[], int isTien, FILE* fout);
 // In công thức Newton đã thay số
void taoDaThucChinhTac(double[], int); // Dùng chung cho tiến/lùi (với hệ số vào)

extern double ytable_local[MAX][MAX];
extern double heSoChinhTac[MAX]; // Cho derivative.c dùng

#endif