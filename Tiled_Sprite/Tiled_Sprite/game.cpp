

#include "game.h" 

LPDIRECT3DTEXTURE9 bill_run, bill_stand, bill_swim, bill_jump; 
LPDIRECT3DSURFACE9 background; 
SPRITE Run,Stand,Swim,Jump; 
LPD3DXSPRITE sprite_handler;
HRESULT result;
long start = GetTickCount(); 
//khởi tạo game
int GameInit(HWND hWnd)
{
    wchar_t s[20];
    int n;
    srand(time(NULL));

    result = D3DXCreateSprite(d3ddev, &sprite_handler); 
    if (!SUCCEEDED(result))
    {
        return 0; 
    }
    bill_run = LoadTexture(L"bill_move.png", D3DCOLOR_XRGB(255, 0, 255), SCALE_CHARACTER); 
    if (bill_run == NULL)
    {
        return 0; 
    }
    bill_stand = LoadTexture(L"bill_stand.png", D3DCOLOR_XRGB(255, 0, 255), SCALE_CHARACTER); 
    if (bill_stand == NULL)
    {
        return 0; 
    }
    bill_swim = LoadTexture(L"bill_in_water.png", D3DCOLOR_XRGB(255, 0, 255), SCALE_CHARACTER); 
    if (bill_swim == NULL)
    {
        return 0; 
    }
    bill_jump = LoadTexture(L"bill_jump.png", D3DCOLOR_XRGB(255, 0, 255), SCALE_CHARACTER); 
    if (bill_swim == NULL)
    {
        return 0; 
    }
    //Khởi tạo background
    background = LoadSurface(L"green.png", NULL); 
    if (background == NULL)
    {
        return 0; 
    }
    // Thiết lập thông tin ban đầu cho 1 hành động của sprite
    Run.x = 0;
    Run.y = 0;
    Run.width = 28 * SCALE_CHARACTER;
    Run.height = 40 * SCALE_CHARACTER;
    Run.rects = { 0,0,Run.width,Run.height };
    Run.curframe = 0;
    Run.lastframe = 4;
    Run.animdelay = 5;
    Run.animcount = 0;
    Run.movex = 1;
    Run.movey = 0; 
    Swim.x = 0;
    Swim.y = 400;
    Swim.width = 24 * SCALE_CHARACTER;
    Swim.height = 32 * SCALE_CHARACTER;
    Swim.rects = { 0,0,Run.width,Run.height };
    Swim.curframe = 0;
    Swim.lastframe = 3;
    Swim.animdelay = 20;
    Swim.animcount = 0;
    Swim.movex = 1;
    Swim.movey = 0;
    Stand.x = 0;
    Stand.y = 200;
    Stand.width = 35 * SCALE_CHARACTER ;
    Stand.height = 50 * SCALE_CHARACTER;
    Stand.rects = { 0,0,Stand.width,Stand.height };
    Stand.curframe = 0;
    Stand.lastframe = 1;
    Stand.animcount = 0;
    Stand.animdelay = 5;
    Stand.animcount = 0;
    Stand.movex = 0;
    Stand.movey = 0;
    Jump.x = 0;
    Jump.y = 500;
    Jump.width = 22 * SCALE_CHARACTER;
    Jump.height = 20 * SCALE_CHARACTER;
    Jump.rects = { 0,0,Jump.width,Jump.height };
    Jump.curframe = 0;
    Jump.lastframe = 3;
    Jump.animcount = 0;
    Jump.animdelay = 5;
    Jump.animcount = 0;
    Jump.movex = 0;
    Jump.movey = 10;
    return 1; 
}

// Hàm này được gọi để chạy game
void GameRun(HWND hwnd) {
    // Nếu không có thiết bị Direct3D, thoát khỏi hàm
    if (d3ddev == NULL) {
        return;
    }
    // Kiểm tra thời gian chạy game để cập nhật trạng thái của Sprite và thực hiện di chuyển
    if (GetTickCount() - start >= 1000 / FPS)
    {
        start = GetTickCount();
        Run.x += Run.movex;
        Swim.x += Swim.movex;
        Jump.y += Jump.movey * ((Jump.curframe >= 2)? -1 : 1);
        if (++Run.animcount > Run.animdelay)
        {
            Run.animcount = 0;
            if (++Run.curframe > Run.lastframe)
            {
                Run.curframe = 0;
            }
        }
        if (++Swim.animcount > Swim.animdelay)
        {
            Swim.animcount = 0;
            if (++Swim.curframe > Swim.lastframe)
            {
                Swim.curframe = 0;
            }
        }
        if (++Stand.animcount > Stand.animdelay)
        {
            Stand.animcount = 0;
            if (++Stand.curframe > Stand.lastframe)
            {
                Stand.curframe = 0;
            }
        }
        if (++Jump.animcount > Jump.animdelay)
        {
            Jump.animcount = 0;
            if (++Jump.curframe > Jump.lastframe)
            {
                Jump.curframe = 0;
            }
        }
        if (Run.x > 1280 - Run.width)
        {
            Run.x = 0;
        }
        if (Swim.x > 1280 - Swim.width)
        {
            Swim.x = 0;
        }
    }

    // Bắt đầu vẽ màn hình
    if (d3ddev->BeginScene()) {

        //tạo background
        d3ddev->StretchRect(background, NULL, backbuffer, NULL, D3DTEXF_NONE);
        
        D3DXMATRIX mt; // ma trận biến đổi

        sprite_handler->Begin(D3DXSPRITE_ALPHABLEND);
        D3DXVECTOR3 position_run(Run.x, Run.y, 0), position_stand(Stand.x, Stand.y, 0), position_swim(Swim.x,Swim.y,0), position_jump(Jump.x, Jump.y, 0);
        RECT tmp_run = Run.rects , tmp_stand = Stand.rects, tmp_swim = Swim.rects, tmp_jump = Jump.rects;
        tmp_run.left = Run.width * Run.curframe;
        tmp_run.right = tmp_run.left + Run.width ;
        tmp_stand.left = Stand.width * Stand.curframe;
        tmp_stand.right = tmp_stand.left + Stand.width;
        tmp_swim.left = Swim.width * Swim.curframe;
        tmp_swim.right = tmp_swim.left + Swim.width;
        tmp_jump.left = Jump.width * Jump.curframe;
        tmp_jump.right = tmp_jump.left + Jump.width;
        sprite_handler->Draw(
            bill_run,
            &tmp_run,
            NULL,
            &position_run,
            D3DCOLOR_XRGB(255, 255, 255)
        );
        sprite_handler->Draw(
            bill_stand,
            &tmp_stand,
            NULL,
            &position_stand,
            D3DCOLOR_XRGB(255, 255, 255)
        );
        sprite_handler->Draw(
            bill_swim,
            &tmp_swim,
            NULL,
            &position_swim,
            D3DCOLOR_XRGB(255, 255, 255)
        );
        sprite_handler->Draw(
            bill_jump,
            &tmp_jump,
            NULL,
            &position_jump,
            D3DCOLOR_XRGB(255, 255, 255)
        );
        sprite_handler->End();

        
        d3ddev->EndScene();
    }

    // Hiển thị màn hình lên đầu ra
    d3ddev->Present(NULL, NULL, NULL, NULL);

    // Nếu người dùng nhấn phím ESC, gửi thông điệp hủy bỏ cửa sổ
    if (KEYDOWN(VK_ESCAPE)) {
        PostMessage(hwnd, WM_DESTROY, 0, 0);
    }

}

//Kết thúc game
void GameEnd(HWND hWnd)
{
    int n;
    //Giải phóng các tài nguyên hình ảnh và sprite đã sử dụng
    if (bill_run != NULL)
        bill_run->Release();
    //Giải phóng background
    if (background != NULL)
    {
        background->Release();
    }
    //Giải phóng sprite handler
    if (sprite_handler != NULL)
    {
        sprite_handler->Release();
    }
}

