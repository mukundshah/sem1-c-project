#include <windows.h>

const char g_szClassName[] = "myWindowClass";
HMENU hMenu;

enum MENU
{
    FILE_SIGNOUT,
    FILE_EXIT,
    ABOUT
};

LRESULT CALLBACK WndProc(HWND hwnd, int msg, WPARAM wParam, LPARAM lParam);
void addMenus(HWND);
void addControls(HWND);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char* lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc;
    HWND hwnd;
    MSG msg;

    wc.cbSize           = sizeof(WNDCLASSEX);
    wc.style            = 0;
    wc.lpfnWndProc      = WndProc;
    wc.cbClsExtra       = 0;
    wc.cbWndExtra       = 0;
    wc.hInstance        = hInstance;
    wc.hIcon            = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor          = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground    = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName     = NULL;
    wc.lpszClassName    = g_szClassName;
    wc.hIconSm          = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        g_szClassName,
        "CAuth",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, 700, 500,
        NULL, NULL, hInstance, NULL);

    if(hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!",
                   MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    while(GetMessage(&msg, NULL, 0, 0)>0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // MessageBox(NULL, "Hello, world!", "C GUI", MB_OK);
    // return 0;

    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, int msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_COMMAND:
            switch (wParam)
            {
            case FILE_SIGNOUT:
                break;
            case FILE_EXIT:
                DestroyWindow(hwnd);
                break;
            case ABOUT:
                break;
            default:
                MessageBeep(MB_OK);
                break;
            }
        case WM_CREATE:
            addMenus(hwnd);
            addControls(hwnd);
            break;
        // case WM_LBUTTONDOWN:
        // {
        //     char szFileName[MAX_PATH];
        //     HINSTANCE hInstance = GetModuleHandle(NULL);

        //     GetModuleFileName(hInstance, szFileName, MAX_PATH);
        //     MessageBox(hwnd, szFileName, "This program is:", MB_OK | MB_ICONINFORMATION);
        // }
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

void addMenus(HWND hWnd){
    hMenu = CreateMenu();
    
    HMENU hFileMenu = CreateMenu();
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, "File");
    AppendMenu(hFileMenu, MF_STRING, FILE_SIGNOUT, "Sign out");
    AppendMenu(hFileMenu, MF_SEPARATOR, NULL, NULL);
    AppendMenu(hFileMenu, MF_STRING, FILE_EXIT, "Exit");

    AppendMenu(hMenu, MF_STRING, ABOUT, "About");
    SetMenu(hWnd, hMenu);
}

void addControls(HWND hWnd){

    CreateWindowW(L"static", L"Username: ", WS_VISIBLE | WS_CHILD, 200, 100, 100, 25, hWnd, NULL, NULL, NULL);
    CreateWindowW(L"Edit", NULL, WS_VISIBLE | WS_CHILD|WS_BORDER | ES_AUTOHSCROLL, 305, 100, 300, 25, hWnd, NULL, NULL, NULL);
    CreateWindowW(L"static", L"Password: ", WS_VISIBLE | WS_CHILD, 200, 130, 100, 25, hWnd, NULL, NULL, NULL);
    CreateWindowW(L"Edit", NULL, WS_VISIBLE | WS_CHILD|WS_BORDER | ES_AUTOHSCROLL, 305, 130, 300, 25, hWnd, NULL, NULL, NULL);
    CreateWindowW(L"Button", L"Login",WS_VISIBLE | WS_CHILD ,200, 160, 80, 25, hWnd, (HMENU)1, NULL, NULL);
    CreateWindowW(L"Button", L"Signup",WS_VISIBLE | WS_CHILD ,300, 160, 80, 25, hWnd, (HMENU)1, NULL, NULL);
    //CreateWindowW(L"Edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER,50, 50, 150, 20, hWnd, (HMENU)1, NULL, NULL);
}
