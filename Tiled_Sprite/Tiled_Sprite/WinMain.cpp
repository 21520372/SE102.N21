#include <d3d9.h>      //Thư viện DirectX
#include <d3dx9.h>     //Thư viện DirectX
#include <time.h>      //Thư viện thời gian
#include <Windows.h>   //Thư viện Win32
#include <stdio.h>
#include "dxgraphics.h" // Thư viện tự tạo, chứa các hàm tạo cửa sổ và thiết lập DirectX
#include "game.h"       // Thư viện tự tạo, chứa hàm xử lý game

// Hàm xử lý sự kiện của cửa sổ
LRESULT WINAPI WinProc(
    HWND hWnd, // Handle của cửa sổ hiện tại
    UINT msg, // Mã của thông điệp được gửi đến cửa sổ
    WPARAM wParam, // Tham số 1 của thông điệp (tuỳ theo mã thông điệp)
    LPARAM lParam ) { // Tham số 2 của thông điệp (tuỳ theo mã thông điệp)

    switch (msg) {
    case WM_DESTROY: // Xử lý khi cửa sổ bị hủy
        if (d3ddev != NULL) {
            d3ddev->Release(); // Giải phóng bộ nhớ của thiết bị đồ họa DirectX
            d3ddev = NULL;
        }

        if (d3d != NULL) {
            d3d->Release(); // Giải phóng bộ nhớ của đối tượng Direct3D
            d3d = NULL;
        }

        GameEnd(hWnd); // Gọi hàm xử lý game khi kết thúc
        PostQuitMessage(0); // Thoát khỏi vòng lặp xử lý thông điệp
        return 0;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam); // Gọi hàm xử lý thông điệp mặc định của Windows
}

// Hàm đăng ký lớp cửa sổ
// hInstance: con trỏ đến instance của chương trình
ATOM MyRegisterClass(HINSTANCE hInstance) {
    WNDCLASSEX wc;
    wc.cbSize = sizeof(WNDCLASSEX); // Đặt kích thước của WNDCLASSEX
    wc.style = CS_HREDRAW | CS_VREDRAW; // Đặt kiểu lớp cửa sổ để xử lý sự kiện vẽ lại khi kích thước hoặc vị trí của cửa sổ thay đổi
    wc.lpfnWndProc = (WNDPROC)WinProc; // Con trỏ đến hàm xử lý sự kiện cho cửa sổ
    wc.cbClsExtra = 0; // Không sử dụng bộ nhớ dự phòng lớp
    wc.cbWndExtra = 0; // Không sử dụng bộ nhớ dự phòng cửa sổ
    wc.hInstance = hInstance; // Con trỏ đến instance của chương trình
    wc.hIcon = NULL; // Không sử dụng biểu tượng
    wc.hCursor = LoadCursor(NULL, IDC_ARROW); // Sử dụng con trỏ chuột mặc định
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // Đặt màu nền của cửa sổ
    wc.lpszMenuName = NULL; // Không sử dụng menu
    wc.lpszClassName = APPTITLE; // Đặt tên lớp cửa sổ
    wc.hIconSm = NULL; // Không sử dụng biểu tượng nhỏ
    return RegisterClassEx(&wc); // Đăng ký lớp cửa sổ và trả về ATOM (Atom là một loại dữ liệu kiểu unsigned short int và được sử dụng để đại diện cho một chuỗi duy nhất)
}

int WINAPI WinMain(HINSTANCE hInstance,        // Tham số chứa handle của ứng dụng
    HINSTANCE hPrevInstance,    // Tham số chứa handle của ứng dụng trước đó
    LPSTR lpCmdLine,            // Tham số chứa các tham số dòng lệnh truyền vào cho ứng dụng
    int nCmdShow) {             // Tham số chứa các thông tin hiển thị cho cửa sổ

    MSG msg; // Khai báo biến msg kiểu MSG để chứa tin nhắn của cửa sổ
    MyRegisterClass(hInstance); // Đăng ký lớp cửa sổ

    //Tạo cửa sổ mới
    HWND hWnd = CreateWindowEx(
        0, // dwExStyle: Thông số mở rộng của cửa sổ, trong trường hợp này không có
        APPTITLE, // lpClassName: Tên lớp cửa sổ được đăng ký trước đó
        APPTITLE, // lpWindowName: Tiêu đề của cửa sổ
        WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX, // dwStyle: Kiểu của cửa sổ, gồm WS_OVERLAPPED, WS_SYSMENU và WS_MINIMIZEBOX
        SCREENX, // X: Vị trí của cửa sổ trên trục x
        SCREENY, // Y: Vị trí của cửa sổ trên trục y
        SCREEN_WIDTH, // nWidth: Độ rộng của cửa sổ
        SCREEN_HEIGHT, // nHeight: Chiều cao của cửa sổ
        NULL, // hWndParent: Handle của cửa sổ cha, trong trường hợp này không có
        NULL, // hMenu: Handle của menu, trong trường hợp này không có
        hInstance, // hInstance: Handle của chương trình đang chạy
        NULL); // lpParam: Con trỏ tùy chọn, trong trường hợp này không có

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
    //DWORD frame_start = GetTickCount(); // Lấy thời gian hiện tại
    //DWORD count_per_frame = 1000 / 1; // Điểm dừng của mỗi khung hình, trong trường hợp này là 1ms
    while (!done) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) { // Kiểm tra xem có tin nhắn mới không
            if (msg.message == WM_QUIT) // Nếu là tin nhắn thoát
            {
                done = 1; // Thoát khỏi vòng lặp
            }
            TranslateMessage(&msg); // Dịch chuỗi kí tự trong tin nhắn
            DispatchMessage(&msg); // Gửi tin nhắn đến bộ xử lý cửa sổ để xử lý
        }
        else { // Nếu không có tin nhắn mới
            //DWORD now = GetTickCount(); // Lấy thời gian hiện tại
            //if (now - frame_start >= count_per_frame) { // Nếu đã đến điểm dừng của khung hình
                //frame_start = now; // Cập nhật lại thời điểm bắt đầu của khung hình mới
                GameRun(hWnd); // Chạy game với handle của cửa sổ đã tạo
            //}
        }
    }

    return msg.wParam; // Trả về giá trị của tham số wParam trong tin nhắn WM_QUIT để biết lý do thoát của ứng dụng
}

