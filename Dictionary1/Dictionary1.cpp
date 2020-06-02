// Dictionary1.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Dictionary1.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>

#define MAX_LOADSTRING 100
#define IDC_BUTTON1 5001
#define IDC_BUTTON2 5002
#define IDC_BUTTON3 5003
#define IDC_BUTTON4 5004
#define IDC_BUTTON5 5005

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

HWND hStatic1, hStatic2;
HWND hEdit1, hEdit2;
HWND hButton1, hButton2, hButton3, hButton4, hButton5;

std::map<std::wstring, std::wstring> words;

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
	LoadStringW(hInstance, IDC_DICTIONARY1, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Выполнить инициализацию приложения:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DICTIONARY1));

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


ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DICTIONARY1));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_DICTIONARY1);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
	{
		MoveWindow(hWnd, 100, 100, 400, 275, true);
		SetWindowText(hWnd, L"Интерактивный словарь!");

		hStatic1 = CreateWindowEx(0, L"STATIC", L"Cлово: ", WS_CHILD | WS_VISIBLE,
			30, 40, 75, 18, hWnd, NULL, hInst, NULL);
		hStatic2 = CreateWindowEx(0, L"STATIC", L"Перевод: ", WS_CHILD | WS_VISIBLE,
			30, 70, 75, 18, hWnd, NULL, hInst, NULL);

		hEdit1 = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"Слово для перевода: ", WS_CHILD | WS_VISIBLE,
			120, 40, 230, 20, hWnd, NULL, hInst, NULL);
		hEdit2 = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"Перевод: ", WS_CHILD | WS_VISIBLE,
			120, 70, 230, 20, hWnd, NULL, hInst, NULL);

		hButton1 = CreateWindowEx(0, L"BUTTON", L"Найти", WS_CHILD | WS_VISIBLE,
			40, 110, 150, 22, hWnd, (HMENU)IDC_BUTTON1, hInst, NULL);
		hButton2 = CreateWindowEx(0, L"BUTTON", L"Сбросить", WS_CHILD | WS_VISIBLE,
			195, 110, 150, 22, hWnd, (HMENU)IDC_BUTTON2, hInst, NULL);
		hButton3 = CreateWindowEx(0, L"BUTTON", L"Добавить", WS_CHILD | WS_VISIBLE,
			40, 140, 150, 22, hWnd, (HMENU)IDC_BUTTON3, hInst, NULL);
		hButton4 = CreateWindowEx(0, L"BUTTON", L"Удалить", WS_CHILD | WS_VISIBLE,
			195, 140, 150, 22, hWnd, (HMENU)IDC_BUTTON4, hInst, NULL);
		//hButton5 = CreateWindowEx(0, L"BUTTON", L"Записать в data.txt", WS_CHILD | WS_VISIBLE,
		//	97, 170, 200, 22, hWnd, (HMENU)IDC_BUTTON5, hInst, NULL);

		words.insert(std::make_pair(L"boy", L"мальчик"));
		words.insert(std::make_pair(L"girl", L"девочка"));
		words.insert(std::make_pair(L"student", L"студент"));
		words.insert(std::make_pair(L"employee", L"сотрудник"));
		words.insert(std::make_pair(L"catalog", L"каталог"));
		words.insert(std::make_pair(L"company", L"компания"));
	}
	break;
	case WM_COMMAND:
	{
		TCHAR buff[100];
		TCHAR buff2[100];
		int wmId = LOWORD(wParam);
		// Разобрать выбор в меню:
		switch (wmId)
		{
		case IDC_BUTTON1:
		{
			GetWindowText(hEdit1, buff, 100);
			if (lstrlen(buff) == 0)
			{
				MessageBox(hWnd, L"Вы не ввели слово для перевода!", L"Ошибка", MB_OK | MB_ICONERROR);
				SetFocus(hEdit1);
			}
			else
			{
				std::wstring t = buff;
				auto iter = words.find(t.c_str());
				if (iter == words.end())
				{
					MessageBox(hWnd, L"Такого слова у нас не существует!", L"Предупреждение", MB_OK | MB_ICONEXCLAMATION);
					SetFocus(hEdit1);
				}
				else
				{
					SetWindowText(hEdit2, iter->second.c_str());
				}
			}
			break;
		}
		case IDC_BUTTON2:
		{
			SetWindowText(hEdit1, L"");
			SetWindowText(hEdit2, L"");
			break;
		}
		case IDC_BUTTON3:
		{
			GetWindowText(hEdit1, buff, 100);
			GetWindowText(hEdit2, buff2, 100);
			SetWindowText(hEdit1, L"");
			SetWindowText(hEdit2, L"");
			if (lstrlen(buff) == 0 or lstrlen(buff2) == 0) {
				MessageBox(hWnd, L"Вы не ввели слово/перевод !", L"Error", MB_OK | MB_ICONERROR);
				SetFocus(hEdit1);
			}
			else {
				words.insert(std::make_pair(buff, buff2));
				SetWindowText(hEdit1, L"Успешно добавлено!");
			}
			break;
		}
		case IDC_BUTTON4:
		{
			GetWindowText(hEdit1, buff, 100);
			if (lstrlen(buff) == 0) {
				MessageBox(hWnd, L"Вы не ввели слово для удаления !", L"Error", MB_OK | MB_ICONERROR);
				SetFocus(hEdit1);
			}
			else {
				std::wstring t = buff;
				auto iter = words.find(t.c_str());
				if (iter == words.end()) {
					MessageBox(hWnd, L"Такого слова у нас не существует!", L"Предупреждение", MB_OK | MB_ICONEXCLAMATION);
					SetFocus(hEdit1);
				}
				else {
					SetWindowText(hEdit1, L"Успешно удалено!");
					words.erase(buff);
				}
			}
			break;
		}
		case IDC_BUTTON5:
		{
			//typedef std::wstring String;
			//if (words.empty()) {
			//	MessageBox(hWnd, L" Слов в словаре не осталось!", L"Error", MB_OK | MB_ICONERROR);
			//	SetFocus(hEdit1);
			//}
			//else {
			//	std::ofstream fout;
			//	fout.open("data.txt", std::ios_base::out);
			//	int iter1;
			//	int iter2;
			//	for (int i = 0; i < words.size(); i++) {
			//		fout << " Слово:" << &buff << ", Перевод: " << *buff2 << std::endl;
			//	}
			//	fout.close();
			//	SetWindowText(hEdit1, L"Успешно записано!");
			//}
			//break;
		}
		case IDM_ABOUT:
		{
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		}
		case IDM_EXIT:
		{
			DestroyWindow(hWnd);
			break;
		}
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
