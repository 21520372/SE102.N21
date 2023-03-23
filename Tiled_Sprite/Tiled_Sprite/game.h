

#ifndef _GAME_H 
#define _GAME_H

#include <d3d9.h> 
#include <d3dx9.h>
#include <windows.h>
#include <time.h> 
#include <stdio.h>
#include <stdlib.h>

#include "dxgraphics.h" 
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
	int x, y; 
	int width,height; 
	int movex, movey; 
	RECT rects; 
	int curframe, lastframe; 
	int animdelay, animcount;
} SPRITE;

#endif 