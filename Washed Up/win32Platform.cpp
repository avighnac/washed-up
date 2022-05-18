#include "pch.hpp"
/* NOTE : Other header files like <windows.h>
   and <string> are included in pch.hpp, which
   is a pre-compiled header.*/

bool running = true;

void *buffer_memory;
int buffer_width;
int buffer_height;
BITMAPINFO buffer_bitmap_info;

LRESULT CALLBACK window_callback(HWND hwnd, UINT uMsg, WPARAM wParam,
                                 LPARAM lParam) {
  LRESULT result = 0;

  switch (uMsg) {
  case WM_CLOSE: {
    running = false;
    break;
  }
  case WM_DESTROY: {
    running = false;
  } break;
  case WM_SIZE: {
    RECT rect;
    GetClientRect(hwnd, &rect);

    buffer_width = rect.right - rect.left;
    buffer_height = rect.bottom - rect.top;

    int buffer_size = buffer_width * buffer_height * sizeof(unsigned int);

    if (buffer_memory)
      VirtualFree(buffer_memory, 0, MEM_RELEASE);
    buffer_memory =
        VirtualAlloc(0, buffer_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

    buffer_bitmap_info.bmiHeader.biSize = sizeof(buffer_bitmap_info.bmiHeader);
    buffer_bitmap_info.bmiHeader.biWidth = buffer_width;
    buffer_bitmap_info.bmiHeader.biHeight = buffer_height;
    buffer_bitmap_info.bmiHeader.biPlanes = 1;
    buffer_bitmap_info.bmiHeader.biBitCount = 32;
    buffer_bitmap_info.bmiHeader.biCompression = BI_RGB;
  } break;
  default:
    result = DefWindowProc(hwnd, uMsg, wParam, lParam);
  }
  return result;
}

inline std::string charToStr(char charac) {
  std::string str;
  str.push_back(charac);
  return str;
}

enum {
  BUTTON_UP,
  BUTTON_DOWN,
  BUTTON_W,
  BUTTON_S,
  BUTTON_LEFT,
  BUTTON_RIGHT,
  BUTTON_ENTER,
  BUTTON_CONTROL,

  BUTTON_COUNT,
};

typedef std::basic_string<TCHAR, std::char_traits<TCHAR>> tstring;

#include "renderer.cpp"
#include "menus.hpp"
#include "washedUp.cpp"
#include "scoreboard.hpp"
#include "items.hpp"

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,
            int nShowCmd) {
  TCHAR appdataTCHAR[MAX_PATH] = {0};
  SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, appdataTCHAR);

  tstring appdata = tstring(appdataTCHAR);

  if (!std::filesystem::is_directory(appdata + tstring(L"\\Washed Up"))) {
    std::filesystem::create_directory(appdata + tstring(L"\\Washed Up"));
    std::ofstream scoreboard(appdata + tstring(L"\\Washed Up\\scoreboard.dat"));
    std::filesystem::create_directory(appdata + tstring(L"\\Washed Up\\items"));
    std::ofstream bottle(appdata + tstring(L"\\Washed Up\\items\\bottle.dat"));
    std::ofstream trash_bag(appdata +
                            tstring(L"\\Washed Up\\items\\trash_bag.dat"));
    std::ofstream iron(appdata + tstring(L"\\Washed Up\\items\\iron.dat"));
    bottle << "0";
    iron << "0";
    trash_bag << "0";
    std::ofstream unlocked(appdata +
                           tstring(L"\\Washed Up\\items\\unlocked.dat"));
    unlocked << "blankBox: true\nstickman_skin_head: false\n";
    std::ofstream selectedSkin(appdata +
                           tstring(L"\\Washed Up\\items\\selectedSkin.dat"));
    selectedSkin << "blankBox";
    scoreboard.close();
    bottle.close();
    trash_bag.close();
    iron.close();
    unlocked.close();
    selectedSkin.close();
  }

  const wchar_t class_name[] = L"Washed Up";
  WNDCLASS window_class = {};
  window_class.style = CS_HREDRAW | CS_VREDRAW;
  window_class.hInstance = hInstance;
  window_class.lpszClassName = class_name;
  window_class.lpfnWndProc = window_callback;
  window_class.hCursor = LoadCursor(NULL, IDC_ARROW);

  RegisterClass(&window_class);
  HWND window = CreateWindowExW(0, class_name, window_class.lpszClassName,
                                WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
                                CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                                NULL, NULL, hInstance, NULL);
  ShowWindow(window, nShowCmd);
  HDC hdc = GetDC(window);

  int option = mainMenu(window);

  if (option == 0)
    washedUp(window, appdata);
  else if (option == 1)
    scoreboard(window, appdata);
  else if (option == 2)
    items(window, appdata);
}