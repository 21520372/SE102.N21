#ifndef _DXGRAPHICS_H
#define _DXGRAPHICS_H

#include <d3d9.h> 
#include <d3dx9.h> 
#include "game.h" 

// Khai báo hàm Init_Direct3D
int Init_Direct3D(HWND hWnd, int width, int height, int fullscreen);


// Khai báo hàm LoadSurface
LPDIRECT3DSURFACE9 LoadSurface(LPCWSTR filename, D3DCOLOR transcolor);


// Khai báo hàm LoadTexture
LPDIRECT3DTEXTURE9 LoadTexture(LPCWSTR filename, D3DCOLOR transcolor, INT SCALE);


// Khai báo biến toàn cục
extern LPDIRECT3D9 d3d; // Con trỏ đối tượng Direct3D9
extern LPDIRECT3DDEVICE9 d3ddev; // Con trỏ đối tượng Direct3D9 Device
extern LPDIRECT3DSURFACE9 backbuffer; // Con trỏ đối tượng backbuffer


#endif