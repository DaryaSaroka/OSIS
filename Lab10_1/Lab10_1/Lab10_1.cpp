// Lab10_1.cpp : Определяет точку входа для приложения.
//

#include "stdafx.h"
#include "Lab10_1.h"

#define MAX_LOADSTRING 100
#define ID_ChBox 3000
#define ID_GrpButtons1 3001
#define ID_GrpButtons2 3002
#define ID_RadBut11 3003
#define ID_RadBut12 3004
#define ID_RadBut13 3005
#define ID_RadBut21 3006
#define ID_RadBut22 3007
#define ID_RadBut23 3008
#define ID_RadBut24 3009

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
HWND hChBox;
HWND hGrpButtons1;
HWND hGrpButtons2;
HWND hRadBut11;
HWND hRadBut12;
HWND hRadBut13;
HWND hRadBut21;
HWND hRadBut22;
HWND hRadBut23;
HWND hRadBut24;
UINT mes;



// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
VOID CALLBACK MySendAsyncProc(__in  HWND hwnd, __in  UINT uMsg, __in  ULONG_PTR dwData, __in  LRESULT lResult);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Разместите код здесь.

	// Инициализация глобальных строк
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_LAB101, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Выполнить инициализацию приложения:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB101));

	MSG msg;

	// Цикл основного сообщения:
	while (GetMessageW(&msg, nullptr, 0, 0))
	{
		if (!TranslateAcceleratorW(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB101));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_LAB101);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);

}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
	hChBox = CreateWindowW(L"BUTTON", L"Draw", WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX, 10, 10, 100, 50, hWnd, (HMENU)ID_ChBox, hInstance, NULL);

	hGrpButtons1 = CreateWindowEx(WS_EX_WINDOWEDGE, L"BUTTON", L"Цвет:", WS_VISIBLE | WS_CHILD | BS_GROUPBOX, 10, 100, 350, 100, hWnd, (HMENU)ID_GrpButtons1, hInst, NULL);
	hRadBut11 = CreateWindowEx(WS_EX_WINDOWEDGE, L"BUTTON", L"Красный", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 20, 120, 300, 20, hWnd, (HMENU)ID_RadBut11, hInst, NULL);
	hRadBut12 = CreateWindowEx(WS_EX_WINDOWEDGE, L"BUTTON", L"Синий", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 20, 145, 300, 20, hWnd, (HMENU)ID_RadBut12, hInst, NULL);
	hRadBut13 = CreateWindowEx(WS_EX_WINDOWEDGE, L"BUTTON", L"Зелёный", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 20, 170, 300, 20, hWnd, (HMENU)ID_RadBut13, hInst, NULL);

	hGrpButtons2 = CreateWindowEx(WS_EX_WINDOWEDGE, L"BUTTON", L"Форма:", WS_VISIBLE | WS_CHILD | BS_GROUPBOX, 500, 100, 350, 120, hWnd, (HMENU)ID_GrpButtons2, hInst, NULL);
	//hRadBut21 = CreateWindowEx(WS_EX_WINDOWEDGE, L"BUTTON", L"Ромб", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 10, 20, 300, 20, hGrpButtons2, (HMENU)ID_RadBut21, hInst, NULL);
	//hRadBut22 = CreateWindowEx(WS_EX_WINDOWEDGE, L"BUTTON", L"Квадрат", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 10, 45, 300, 20, hGrpButtons2, (HMENU)ID_RadBut22, hInst, NULL);
	//hRadBut23 = CreateWindowEx(WS_EX_WINDOWEDGE, L"BUTTON", L"Круг", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 10, 70, 300, 20, hGrpButtons2, (HMENU)ID_RadBut23, hInst, NULL);
	//hRadBut24 = CreateWindowEx(WS_EX_WINDOWEDGE, L"BUTTON", L"Звезда", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 10, 95, 300, 20, hGrpButtons2, (HMENU)ID_RadBut24, hInst, NULL);

	hRadBut21 = CreateWindowEx(WS_EX_WINDOWEDGE, L"BUTTON", L"Ромб", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 510, 120, 300, 20, hWnd, (HMENU)ID_RadBut21, hInst, NULL);
	hRadBut22 = CreateWindowEx(WS_EX_WINDOWEDGE, L"BUTTON", L"Квадрат", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 510, 145, 300, 20, hWnd, (HMENU)ID_RadBut22, hInst, NULL);
	hRadBut23 = CreateWindowEx(WS_EX_WINDOWEDGE, L"BUTTON", L"Круг", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 510, 170, 300, 20, hWnd, (HMENU)ID_RadBut23, hInst, NULL);
	hRadBut24 = CreateWindowEx(WS_EX_WINDOWEDGE, L"BUTTON", L"Звезда", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 510, 195, 300, 20, hWnd, (HMENU)ID_RadBut24, hInst, NULL);

	mes = RegisterWindowMessageW(L"Lab10");

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}
//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
char buffer[4] = "000";
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	COPYDATASTRUCT cd;
	HWND app2;
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Разобрать выбор в меню:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case ID_ChBox:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				LRESULT chkState = SendMessage((HWND)lParam, BM_GETCHECK, 0, 0);
				if (chkState == BST_CHECKED)
				{
					buffer[0] = '1';
					cd.lpData = &buffer;
					cd.cbData = sizeof(buffer);
					app2 = FindWindowW(NULL, L"Lab10_2");
					if (app2 == NULL) MessageBoxA(hWnd, "App not find!", "CheckBox", MB_OK);
					else SendMessageW(app2, WM_COPYDATA, 0, (LPARAM)&cd);
				}
				else if (chkState == BST_UNCHECKED)
				{
					buffer[0] = '0';
					cd.lpData = &buffer;
					cd.cbData = sizeof(buffer);
					app2 = FindWindowW(NULL, L"Lab10_2");
					if (app2 == NULL) MessageBoxA(hWnd, "App not find!", "CheckBox", MB_OK);
					else SendMessageW(app2, WM_COPYDATA, 0, (LPARAM)&cd);
				}
			}
			break;
		case ID_RadBut11:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				LRESULT chkState = SendMessage((HWND)lParam, BM_GETCHECK, 0, 0);
				if (chkState == BST_CHECKED)
				{
					buffer[1] = '1';
					cd.lpData = &buffer;
					cd.cbData = sizeof(buffer);
					app2 = FindWindowW(NULL, L"Lab10_2");
					if (app2 == NULL) MessageBoxA(hWnd, "App not find!", "CheckBox", MB_OK);
					else SendMessageW(app2, WM_COPYDATA, 0, (LPARAM)&cd);
				}
			}
			break;
		case ID_RadBut12:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				LRESULT chkState = SendMessage((HWND)lParam, BM_GETCHECK, 0, 0);
				if (chkState == BST_CHECKED)
				{
					buffer[1] = '2';
					cd.lpData = &buffer;
					cd.cbData = sizeof(buffer);
					app2 = FindWindowW(NULL, L"Lab10_2");
					if (app2 == NULL) MessageBoxA(hWnd, "App not find!", "CheckBox", MB_OK);
					else SendMessageW(app2, WM_COPYDATA, 0, (LPARAM)&cd);
				}
			}
			break;
		case ID_RadBut13:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				LRESULT chkState = SendMessage((HWND)lParam, BM_GETCHECK, 0, 0);
				if (chkState == BST_CHECKED)
				{
					buffer[1] = '3';
					cd.lpData = &buffer;
					cd.cbData = sizeof(buffer);
					app2 = FindWindowW(NULL, L"Lab10_2");
					if (app2 == NULL) MessageBoxA(hWnd, "App not find!", "CheckBox", MB_OK);
					else SendMessageW(app2, WM_COPYDATA, 0, (LPARAM)&cd);
				}
			}
			break;
		case ID_RadBut21:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				LRESULT chkState = SendMessage((HWND)lParam, BM_GETCHECK, 0, 0);
				if (chkState == BST_CHECKED)
				{
					buffer[2] = '1';
					cd.lpData = &buffer;
					cd.cbData = sizeof(buffer);
					app2 = FindWindowW(NULL, L"Lab10_2");
					if (app2 == NULL) MessageBoxA(hWnd, "App not find!", "CheckBox", MB_OK);
					else SendMessageW(app2, WM_COPYDATA, 0, (LPARAM)&cd);
				}
			}
			break;
		case ID_RadBut22:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				LRESULT chkState = SendMessage((HWND)lParam, BM_GETCHECK, 0, 0);
				if (chkState == BST_CHECKED)
				{
					buffer[2] = '2';
					cd.lpData = &buffer;
					cd.cbData = sizeof(buffer);
					app2 = FindWindowW(NULL, L"Lab10_2");
					if (app2 == NULL) MessageBoxA(hWnd, "App not find!", "CheckBox", MB_OK);
					else SendMessageW(app2, WM_COPYDATA, 0, (LPARAM)&cd);
				}
			}
			break;
		case ID_RadBut23:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				LRESULT chkState = SendMessage((HWND)lParam, BM_GETCHECK, 0, 0);
				if (chkState == BST_CHECKED)
				{
					buffer[2] = '3';
					cd.lpData = &buffer;
					cd.cbData = sizeof(buffer);
					app2 = FindWindowW(NULL, L"Lab10_2");
					if (app2 == NULL) MessageBoxA(hWnd, "App not find!", "CheckBox", MB_OK);
					else SendMessageW(app2, WM_COPYDATA, 0, (LPARAM)&cd);
				}
			}
			break;
		case ID_RadBut24:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				LRESULT chkState = SendMessage((HWND)lParam, BM_GETCHECK, 0, 0);
				if (chkState == BST_CHECKED)
				{
					buffer[2] = '4';
					cd.lpData = &buffer;
					cd.cbData = sizeof(buffer);
					app2 = FindWindowW(NULL, L"Lab10_2");
					if (app2 == NULL) MessageBoxA(hWnd, "App not find!", "CheckBox", MB_OK);
					else SendMessageW(app2, WM_COPYDATA, 0, (LPARAM)&cd);
				}
			}
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}

	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Добавьте сюда любой код прорисовки, использующий HDC...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

VOID CALLBACK MySendAsyncProc(__in  HWND hwnd,__in  UINT uMsg,__in  ULONG_PTR dwData,__in  LRESULT lResult) 
{
	// Whohoo! It called me back!
}