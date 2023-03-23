#include "dxgraphics.h"

// Khai báo các biến sử dụng
LPDIRECT3D9 d3d = NULL;                       // đối tượng D3D
LPDIRECT3DDEVICE9 d3ddev = NULL;               // đối tượng D3D device
LPDIRECT3DSURFACE9 backbuffer = NULL;          // surface backbuffer

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
    D3DPRESENT_PARAMETERS d3dpp; // Khai báo biến cấu hình hiển thị Direct3D
    ZeroMemory(&d3dpp, sizeof(d3dpp)); // Xóa toàn bộ bộ nhớ của biến cấu hình hiển thị Direct3D
    d3dpp.Windowed = TRUE; // Đặt cửa sổ hiển thị là windowed mode (không full screen)
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD; // Đặt phương pháp swap buffer là D3DSWAPEFFECT_DISCARD
    d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8; // Đặt định dạng buffer là D3DFMT_X8R8G8B8
    d3dpp.BackBufferCount = 1; // Đặt số lượng back buffer là 1
    d3dpp.BackBufferWidth = SCREEN_WIDTH; // Đặt chiều rộng back buffer bằng SCREEN_WIDTH (đã được định nghĩa ở đâu đó)
    d3dpp.BackBufferHeight = SCREEN_HEIGHT; // Đặt chiều cao back buffer bằng SCREEN_HEIGHT (đã được định nghĩa ở đâu đó)
    d3dpp.hDeviceWindow = hWnd; // Đặt cửa sổ hiển thị là hWnd (handle của cửa sổ hiện tại)

    // Tạo thiết bị Direct3D
    HRESULT result_create_device = d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &d3ddev);

    // Kiểm tra nếu không thể tạo thiết bị Direct3D thì hiển thị thông báo lỗi
    if (FAILED(result_create_device)) {
        MessageBox(hWnd, L"Error creating Direct3D device", L"Error", MB_OK);
        return 0;
    }

    // Xóa nền màn hình
    d3ddev->Clear(
        0, // 0: Không sử dụng scissor rectangle
        NULL, // Không cần truyền giá trị scissor rectangle
        D3DCLEAR_TARGET, // Xác định loại buffer cần xóa, ở đây là buffer đích (back buffer)
        D3DCOLOR_XRGB(0, 0, 0), // Màu để xóa back buffer, ở đây là đen (RGB: 0, 0, 0)
        1.0f, // Độ sâu mặc định của depth buffer
        0 // Giá trị stencil mặc định
    );

    // tạo con trỏ tới backbuffer
    d3ddev->GetBackBuffer(
        0,              // Chỉ số của back buffer
        0,              // Mức độ chi tiết của surface của back buffer
        D3DBACKBUFFER_TYPE_MONO, // Loại của back buffer
        &backbuffer     // Con trỏ đến đối tượng back buffer được trả về
    );

    return 1;
}

LPDIRECT3DSURFACE9 LoadSurface(LPCWSTR filename, D3DCOLOR transcolor)
{
    LPDIRECT3DSURFACE9 image = NULL;  // Khởi tạo surface được sử dụng để lưu trữ dữ liệu từ file ảnh và trả về

    D3DXIMAGE_INFO info; // Khởi tạo biến để lưu trữ thông tin về file ảnh

    HRESULT result; // Khởi tạo biến để lưu trữ kết quả trả về của các hàm

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
        image, // con trỏ tới surface đích, được tạo ra trước đó để lưu trữ dữ liệu từ file ảnh
        NULL, // con trỏ tới palette nếu cần, ở đây không sử dụng
        NULL, // con trỏ tới hình chữ nhật (RECT) xác định phần của surface mà sẽ được điền vào, ở đây không sử dụng nên để NULL
        filename, // đường dẫn tới file ảnh cần load lên surface
        NULL, // con trỏ tới hình chữ nhật (RECT) xác định phần của file ảnh mà sẽ được load lên surface, ở đây không sử dụng nên để NULL
        D3DX_DEFAULT, // giá trị mặc định của filter, dùng để áp dụng cho việc scale ảnh, ở đây dùng giá trị mặc định
        transcolor, // giá trị màu sắc của key color, được sử dụng để loại bỏ một màu sắc cụ thể khỏi ảnh khi load, ở đây không sử dụng nên để 0
        NULL // con trỏ tới D3DXIMAGE_INFO structure chứa thông tin về ảnh được load, ở đây không sử dụng nên để NULL
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
    LPDIRECT3DTEXTURE9 texture = NULL;  // Khởi tạo surface được sử dụng để lưu trữ dữ liệu từ file ảnh và trả về

    D3DXIMAGE_INFO info; // Khởi tạo biến để lưu trữ thông tin về file ảnh

    HRESULT result; // Khởi tạo biến để lưu trữ kết quả trả về của các hàm

    // Lấy thông tin về file ảnh, nếu thất bại trả về NULL
    result = D3DXGetImageInfoFromFile(filename, &info);
    if (!SUCCEEDED(result))
    {
        return NULL;
    }

    // Load dữ liệu từ file ảnh lên texture
    result = D3DXCreateTextureFromFileEx(
        d3ddev,                     // Con trỏ tới đối tượng thiết bị DirectX để sử dụng
        filename,                   // Đường dẫn tới file ảnh cần load lên texture
        info.Width * SCALE_CHARACTER,   // Chiều rộng của texture (được nhân với SCALE_CHARACTER)
        info.Height * SCALE_CHARACTER,  // Chiều cao của texture (được nhân với SCALE_CHARACTER)
        1,                          // Số level của texture (thường là 1)
        D3DPOOL_MANAGED,            // Cách quản lý bộ nhớ cho texture (thường là D3DPOOL_MANAGED)
        D3DFMT_A8R8G8B8,            // Định dạng của texture (thường là D3DFMT_A8R8G8B8)
        D3DPOOL_DEFAULT,            // Cách quản lý bộ nhớ cho các dữ liệu khác liên quan đến texture (thường là D3DPOOL_DEFAULT)
        D3DX_DEFAULT,               // Sử dụng cấu hình mặc định cho các giá trị khác liên quan đến texture
        D3DX_DEFAULT,               // Sử dụng cấu hình mặc định cho các giá trị khác liên quan đến texture
        transcolor,                 // Màu trong suốt để làm màu chuyển đổi (thường là màu nền của ảnh)
        &info,                      // Thông tin về ảnh được load lên texture (được trả về bởi D3DXGetImageInfoFromFile())
        NULL,                       // Con trỏ tới một đối tượng tùy chọn IDirect3DDevice9 (nếu sử dụng IDirect3DDevice9)
        &texture                    // Con trỏ tới đối tượng texture được tạo ra
    );

    // Nếu load dữ liệu không thành công thì trả về NULL
    if (!SUCCEEDED(result))
    {
        return NULL;
    }

    // Nếu load dữ liệu thành công, trả về surface lưu trữ dữ liệu đã được load
    return texture;
}