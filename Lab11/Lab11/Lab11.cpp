// Lab6.cpp : Определяет точку входа для приложения.
//

#include "stdafx.h"
#include "Lab11.h"
#include "math.h"

#define MAX_LOADSTRING 100
#define ID_BUTTON_1 3000
#define ID_BUTTON_2 3001

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
HWND hBtn1;
HWND hBtn2;

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

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
	LoadStringW(hInstance, IDC_LAB11, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Выполнить инициализацию приложения:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB11));

	MSG msg;

	// Цикл основного сообщения:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
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
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB11));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_LAB11);
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
HWND hWnd;
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

	hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
	hBtn1 = CreateWindowW(L"BUTTON", L"Start", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP, 10, 10, 100, 50, hWnd, (HMENU)ID_BUTTON_1, hInstance, NULL);
	hBtn2 = CreateWindowW(L"BUTTON", L"Stop", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP, 150, 10, 100, 50, hWnd, (HMENU)ID_BUTTON_2, hInstance, NULL);
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
double alpha1 = 0.0, alpha2 = 0.0;
DWORD WINAPI ThreadFunc(LPVOID lpParam)
{
	for (;;)
	{
		if ((int)lpParam == 1)
		{
			alpha1 += 0.1;
			if (alpha1 == 360) alpha1 = 0.0;
		}
		else
		{ 
			alpha2 += 0.3;
			if (alpha2 == 360) alpha2 = 0.0;
		}
		InvalidateRect(hWnd, NULL, FALSE);
		Sleep(50);
	}
	return 0;
}
HANDLE hThread1, hThread2;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	DWORD dwThreadId1, dwThreadId2;
	int param1 = 1;
	int param2 = 2;
	switch (message)
	{
	case WM_CREATE:
		hThread1 = CreateThread(NULL, 0, ThreadFunc, (LPVOID)param1, 0, &dwThreadId1);
		hThread2 = CreateThread(NULL, 0, ThreadFunc, (LPVOID)param2, 0, &dwThreadId2);
		//атрибуты без-ти, размер стека, функция, аргумент функции,флажки создания, идентификатор потока
		if (hThread1 == NULL) MessageBoxW(NULL, L"Cannot create first thread", L"Fail", MB_OK);
		if (hThread2 == NULL) MessageBoxW(NULL, L"Cannot create second thread", L"Fail", MB_OK);
		SuspendThread(hThread1);
		SuspendThread(hThread2);
		break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Разобрать выбор в меню:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case ID_BUTTON_1:             //Start
			ResumeThread(hThread1);
			ResumeThread(hThread2);
			break;
		case ID_BUTTON_2:                      //Stop
			SuspendThread(hThread1);
			SuspendThread(hThread2);
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
		RECT Rect;
		GetClientRect(hWnd, &Rect);
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		HBRUSH hBrush;                                 //создаём объект-кисть
		hBrush = CreateSolidBrush(RGB(255, 255, 255)); //задаём сплошную кисть, закрашенную цветом RGB
		FillRect(hdc, &Rect, hBrush);
		HPEN hPen1;                                    //Объявляется черную кисть
		hPen1 = CreatePen(1, 4, RGB(0, 0, 0));
		SelectObject(hdc, hPen1);
		MoveToEx(hdc, 200 + 100 * sin(alpha1), 300 - 100 * cos(alpha1), NULL);     //1 палочка
		LineTo(hdc, 200 - 100 * sin(alpha1), 300 + 100 * cos(alpha1));
		MoveToEx(hdc, 500 + 100 * sin(alpha2), 300 - 100 * cos(alpha2), NULL);     //2 палочка
		LineTo(hdc, 500 - 100 * sin(alpha2), 300 + 100 * cos(alpha2));
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		CloseHandle(hThread1);
		CloseHandle(hThread2);
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
