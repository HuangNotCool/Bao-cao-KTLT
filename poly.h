#ifndef POLY_H
#define POLY_H

#include "input.h"

void inDaThucNewton(); // Gọi từ main menu để hiển thị menu phụ 
void tinhSaiPhanLocal(); // Tính bảng sai phân local
void layHeSoTien(double[]); // Lấy hệ số sai phân tiến từ bảng local
void inCongThuc(double heso[], int isTien, FILE* fout);  // In công thức Newton đã thay số
void taoDaThucChinhTac(double[], int); // Đa thức chính tắc

extern double ytable_local[MAX][MAX];
extern double heSoChinhTac[MAX];

#endif