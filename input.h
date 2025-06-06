#ifndef INPUT_H
#define INPUT_H

#define MAX 100

extern int n;                  // Số điểm nội suy
extern double x[MAX], y[MAX];  // Dữ liệu đầu vào
extern int precision;          // Số chữ số thập phân hiển thị
void nhapDuLieu();             // Gọi để nhập toàn bộ đầu vào
void clearBuffer();

#endif
