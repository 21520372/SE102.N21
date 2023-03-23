#include <d3d9.h>      
#include <d3dx9.h>     
#include <time.h>      
#include <Windows.h>   
#include <stdio.h>
#include "dxgraphics.h" 
#include "game.h"       
// Hàm xử lý sự kiện của cửa sổ
LRESULT WINAPI WinProc(
    HWND hWnd, 
    UINT msg, 
    WPARAM wParam, 
    LPARAM lParam ) { 

    switch (msg) {
    case WM_DESTROY: // Xử lý khi cửa sổ bị hủy
        if (d3ddev != NULL) {
            d3ddev->Release(); 
            d3ddev = NULL;
        }

        if (d3d != NULL) {
            d3d->Release(); 
            d3d = NULL;
        }

        GameEnd(hWnd); 
        PostQuitMessage(0); 
        return 0;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam); 
}

// Hàm đăng ký lớp cửa sổ
// hInstance: con trỏ đến instance của chương trình
ATOM MyRegisterClass(HINSTANCE hInstance) {
    WNDCLASSEX wc;
    wc.cbSize = sizeof(WNDCLASSEX); 
    wc.style = CS_HREDRAW | CS_VREDRAW; 
    wc.lpfnWndProc = (WNDPROC)WinProc; 
    wc.cbClsExtra = 0; 
    wc.cbWndExtra = 0; 
    wc.hInstance = hInstance; 
    wc.hIcon = NULL; 
    wc.hCursor = LoadCursor(NULL, IDC_ARROW); 
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); 
    wc.lpszMenuName = NULL; 
    wc.lpszClassName = APPTITLE; 
    wc.hIconSm = NULL; 
    return RegisterClassEx(&wc); 
}

int WINAPI WinMain(HINSTANCE hInstance,        
    HINSTANCE hPrevInstance,    
    LPSTR lpCmdLine,            
    int nCmdShow) {             

    MSG msg; 
    MyRegisterClass(hInstance); 

    //Tạo cửa sổ mới
    HWND hWnd = CreateWindowEx(
        0, 
        APPTITLE, 
        APPTITLE, 
        WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX, 
        SCREENX, 
        SCREENY, 
        SCREEN_WIDTH, 
        SCREEN_HEIGHT, 
        NULL, 
        NULL, 
        hInstance, 
        NULL); 

    if (hWnd == 0) // Nếu không thể tạo cửa sổ, thoát hàm
    {
        MessageBox(hWnd, L"Error create windows", L"Error", MB_OK);
        return 0;
    }

    ShowWindow(hWnd, nCmdShow); // Hiển thị cửa sổ với thông số đã định nghĩa
    UpdateWindow(hWnd); // Cập nhật cửa sổ
    if (!Init_Direct3D(hWnd, SCREEN_WIDTH, SCREEN_HEIGHT, FULLSCREEN))
    {
        MessageBox(hWnd, L"Error init direct 3d", L"Error", MB_OK);
        return 0;
    }

    if (!GameInit(hWnd)) // Khởi tạo game với handle của cửa sổ vừa tạo, nếu không thành công, thoát hàm
    {
        MessageBox(hWnd, L"Error initializing the game", L"Error", MB_OK);
        return 0;
    }

    //vòng lặp chính của game
    int done = 0;
    
    while (!done) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) { 
            if (msg.message == WM_QUIT) 
            {
                done = 1; 
            }
            TranslateMessage(&msg); 
            DispatchMessage(&msg); 
        }
        else { 
            
                GameRun(hWnd); 
    
        }
    }

    return msg.wParam; 
}

