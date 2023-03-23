#include "dxgraphics.h"

// Khai báo các biến sử dụng
LPDIRECT3D9 d3d = NULL;                       
LPDIRECT3DDEVICE9 d3ddev = NULL;               
LPDIRECT3DSURFACE9 backbuffer = NULL;          

int Init_Direct3D(HWND hWnd, int width, int height, int fullscreen)
{
    // Tạo đối tượng Direct3D
    d3d = Direct3DCreate9(D3D_SDK_VERSION);

    // Kiểm tra nếu không thể tạo Direct3D thì hiển thị thông báo lỗi
    if (d3d == NULL) {
        MessageBox(hWnd, L"Error initializing Direct3D", L"Error", MB_OK);
        return 0;
    }

    // Khởi tạo cấu hình hiển thị Direct3D (D3DPRESENT_PARAMETERS)
    D3DPRESENT_PARAMETERS d3dpp; 
    ZeroMemory(&d3dpp, sizeof(d3dpp)); 
    d3dpp.Windowed = TRUE; 
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD; 
    d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8; 
    d3dpp.BackBufferCount = 1; 
    d3dpp.BackBufferWidth = SCREEN_WIDTH; 
    d3dpp.BackBufferHeight = SCREEN_HEIGHT; 
    d3dpp.hDeviceWindow = hWnd; 

    // Tạo thiết bị Direct3D
    HRESULT result_create_device = d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &d3ddev);

    // Kiểm tra nếu không thể tạo thiết bị Direct3D thì hiển thị thông báo lỗi
    if (FAILED(result_create_device)) {
        MessageBox(hWnd, L"Error creating Direct3D device", L"Error", MB_OK);
        return 0;
    }

    // Xóa nền màn hình
    d3ddev->Clear(
        0, 
        NULL, 
        D3DCLEAR_TARGET, 
        D3DCOLOR_XRGB(0, 0, 0), 
        1.0f, 
        0 
    );

    // tạo con trỏ tới backbuffer
    d3ddev->GetBackBuffer(
        0,              
        0,              
        D3DBACKBUFFER_TYPE_MONO, 
        &backbuffer     
    );

    return 1;
}

LPDIRECT3DSURFACE9 LoadSurface(LPCWSTR filename, D3DCOLOR transcolor)
{
    LPDIRECT3DSURFACE9 image = NULL;  

    D3DXIMAGE_INFO info; 

    HRESULT result; 

    // Lấy thông tin về file ảnh, nếu thất bại trả về NULL
    result = D3DXGetImageInfoFromFile(filename, &info);
    if (!SUCCEEDED(result))
    {
        return NULL;
    }

    // Tạo surface để lưu trữ dữ liệu từ file ảnh
    result = d3ddev->CreateOffscreenPlainSurface(info.Width, info.Height, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &image, NULL);

    if (!SUCCEEDED(result)) 
    {
        return NULL;
    }

    // Load dữ liệu từ file ảnh lên surface đã tạo
    result = D3DXLoadSurfaceFromFile(
        image, 
        NULL, 
        NULL, 
        filename, 
        NULL, 
        D3DX_DEFAULT, 
        transcolor, 
        NULL 
    );

    // Nếu load dữ liệu không thành công thì trả về NULL
    if (!SUCCEEDED(result)) 
    {
        return NULL;
    }

    // Nếu load dữ liệu thành công, trả về surface lưu trữ dữ liệu đã được load
    return image;
}

LPDIRECT3DTEXTURE9 LoadTexture(LPCWSTR filename, D3DCOLOR transcolor, INT SCALE)
{
    LPDIRECT3DTEXTURE9 texture = NULL;  

    D3DXIMAGE_INFO info; 

    HRESULT result; 

    // Lấy thông tin về file ảnh, nếu thất bại trả về NULL
    result = D3DXGetImageInfoFromFile(filename, &info);
    if (!SUCCEEDED(result))
    {
        return NULL;
    }

    // Load dữ liệu từ file ảnh lên texture
    result = D3DXCreateTextureFromFileEx(
        d3ddev,                     
        filename,                   
        info.Width * SCALE_CHARACTER,   
        info.Height * SCALE_CHARACTER,  
        1,                          
        D3DPOOL_MANAGED,            
        D3DFMT_A8R8G8B8,            
        D3DPOOL_DEFAULT,           
        D3DX_DEFAULT,               
        D3DX_DEFAULT,               
        transcolor,                 
        &info,                      
        NULL,                       
        &texture                   
    );

    // Nếu load dữ liệu không thành công thì trả về NULL
    if (!SUCCEEDED(result))
    {
        return NULL;
    }

    // Nếu load dữ liệu thành công, trả về surface lưu trữ dữ liệu đã được load
    return texture;
}