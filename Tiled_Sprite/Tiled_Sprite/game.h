//Anim_Sprite program header file

#ifndef _GAME_H //Đảm bảo không xảy ra lỗi khi định nghĩa trùng lặp
#define _GAME_H

#include <d3d9.h> // Thư viện DirectX
#include <d3dx9.h>
#include <DxErr.h>
#include <dsound.h>
#include <dinput.h>
#include <windows.h>
#include <time.h> // Thư viện thời gian
#include <stdio.h>
#include <stdlib.h>

#include "dxgraphics.h" // File header tự định nghĩa, chứa các hàm để vẽ đồ họa
#include "game.h"

#define APPTITLE L"Trans_Sprite" //Tên ứng dụng

// Kích thước màn hình
#define FULLSCREEN 0
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

// Tọa độ của cửa sổ so với màn hình
#define SCREENX (GetSystemMetrics(SM_CXSCREEN) - SCREEN_WIDTH) / 2
#define SCREENY (GetSystemMetrics(SM_CYSCREEN) - SCREEN_HEIGHT) / 2

// Định nghĩa các phím bàn phím
#define KEYDOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEYUP(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

//FPS
#define FPS 60

#define SCALE_CHARACTER 3 // Hằng số để tỷ lệ phóng to/thu nhỏ kích thước Sprite
#define SCALE_MAP 2

// Khai báo hàm
int GameInit(HWND hWnd); // Hàm khởi tạo game
void GameRun(HWND hWnd); // Hàm chạy game
void GameEnd(HWND hWnd); // Hàm kết thúc game

// Khai báo struct SPRITE (đối tượng Sprite)
typedef struct {
	int x, y; // Vị trí của Sprite trên màn hình
	int width,height; // Kích thước của Sprite
	int movex, movey; // Tốc độ di chuyển của Sprite
	RECT rects; // Mảng chứa các hình chữ nhật tạo thành Sprite
	int curframe, lastframe; // Hiệu ứng chuyển động của Sprite
	int animdelay, animcount;
} SPRITE;

#endif // Kết thúc phần định nghĩa không xảy ra lỗi khi định nghĩa trùng lặp