#include"pch.h"

LRESULT CALLBACK WindowsInfo::NewWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    return DefWindowProc(hWnd, message, wParam, lParam);
}


void WindowsInfo::CreateNewWindow(const wchar_t* name) {
    WNDCLASSEX wc;
    ZeroMemory(&wc, sizeof(WNDCLASSEX));
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = NewWindowProc;
    wc.hInstance = GetModuleHandle(0);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)RGB(0, 0, 0);
    wc.lpszClassName = name;
    RegisterClassEx(&wc);

    newhWnd = CreateWindowEx(WS_EX_LAYERED | WS_EX_TRANSPARENT, wc.lpszClassName, name, WS_POPUP, winRect.left, winRect.top,
        (winRect.right - winRect.left), (winRect.bottom - winRect.top), NULL, NULL, wc.hInstance, NULL);

    SetLayeredWindowAttributes(newhWnd, RGB(0, 0, 0), 0, 1);
    ShowWindow(newhWnd, SW_SHOW);
    UpdateWindow(newhWnd);
}


bool WindowsInfo::GameIsForegroundWindow() {
    HWND hWnd = GetForegroundWindow();
    if (hWnd == FindWindow(NULL, L"AssaultCube"))
    {
        return TRUE;
    }
    return FALSE;
}

void WindowsInfo::UpdateScreen() {
    RECT rect = { 0,0,winRect.right - winRect.left,winRect.bottom - winRect.top };
    HWND hWnd = GetForegroundWindow();
    if (hWnd == FindWindow(NULL, L"AssaultCube"))
    {
        HDC hDc = GetDC(newhWnd);
        HBRUSH hBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);//¿Õ»­Ë¢
        SelectObject(hDc, hBrush);

        FillRect(hDc, &rect, hBrush);

        DeleteObject(hBrush);
        ReleaseDC(newhWnd, hDc);
    }
}

void WindowsInfo::DrawEsp(vec2d screen, float distance,PlayerInfo* player) {
    vec4d Rect = { 0 };
    Rect.w = 1100 / distance;
    Rect.z = 2000 / distance;
    Rect.x = (screen.x - (Rect.w / 2));
    Rect.y = screen.y - Rect.z;

    HWND hwnd = GetForegroundWindow();
    if (hwnd == FindWindow(NULL, L"AssaultCube")) {
        HDC hDc = GetDC(newhWnd);
        HPEN hPen = CreatePen(PS_SOLID, 2, 0xFF);
        HBRUSH hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
        SelectObject(hDc, hPen);
        SelectObject(hDc, hBrush);
        if (!player->dead) {
            Rectangle(hDc, Rect.x, Rect.y, Rect.x + Rect.w, Rect.y + Rect.z);
        }
        HFONT hFont = CreateFont(
            20,                         
            0,                          
            0,                          
            0,                          
            FW_DONTCARE,                
            FALSE,                      
            FALSE,                      
            FALSE,                      
            DEFAULT_CHARSET,            
            OUT_DEFAULT_PRECIS,         
            CLIP_DEFAULT_PRECIS,        
            DEFAULT_QUALITY,            
            DEFAULT_PITCH | FF_SWISS,   
            TEXT("Arial")               
        );
        SelectObject(hDc, hFont); 
        SetTextColor(hDc, RGB(255,255, 255));
        SetBkMode(hDc, NULL_BRUSH);     
        std::string text = print_info(player);
        TextOutA(hDc, Rect.x, Rect.y - 15, text.c_str(), strlen(text.c_str()));
        DeleteObject(hFont);
        DeleteObject(hBrush);
        DeleteObject(hPen);
        ReleaseDC(newhWnd, hDc);
    }
}