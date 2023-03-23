#ifndef _DXGRAPHICS_H
#define _DXGRAPHICS_H

#include <d3d9.h> // Thư viện DirectX
#include <d3dx9.h> // Thư viện DirectX
#include "game.h" // Header file chứa các khai báo cần thiết

// Khai báo hàm Init_Direct3D
int Init_Direct3D(HWND hWnd, int width, int height, int fullscreen);
/*
Hàm Init_Direct3D sử dụng để khởi tạo DirectX Graphics và trả về giá trị là 0 nếu khởi tạo thành công,
trả về giá trị khác 0 nếu có lỗi. Tham số hWnd là handle (con trỏ) của cửa sổ hiển thị,
width và height lần lượt là chiều rộng và chiều cao của cửa sổ,
fullscreen là một biến boolean cho biết liệu chế độ hiển thị có phải là toàn màn hình hay không.
*/

// Khai báo hàm LoadSurface
LPDIRECT3DSURFACE9 LoadSurface(LPCWSTR filename, D3DCOLOR transcolor);
/*
Hàm LoadSurface sử dụng để tải lên một bề mặt (surface) từ tệp hình ảnh.
Tham số filename là tên của tệp hình ảnh cần tải, transcolor là màu trong suốt của hình ảnh.
*/

// Khai báo hàm LoadTexture
LPDIRECT3DTEXTURE9 LoadTexture(LPCWSTR filename, D3DCOLOR transcolor, INT SCALE);
/*
Hàm LoadTexture sử dụng để tải lên một texture từ tệp hình ảnh.
Tham số filename là tên của tệp hình ảnh cần tải, transcolor là màu trong suốt của hình ảnh.
*/

// Khai báo biến toàn cục
extern LPDIRECT3D9 d3d; // Con trỏ đối tượng Direct3D9
extern LPDIRECT3DDEVICE9 d3ddev; // Con trỏ đối tượng Direct3D9 Device
extern LPDIRECT3DSURFACE9 backbuffer; // Con trỏ đối tượng backbuffer
/*
Biến toàn cục d3d, d3ddev và backbuffer lần lượt là ba con trỏ đối tượng DirectX Graphics,
được sử dụng để quản lý và hiển thị các đối tượng đồ họa.
*/

#endif