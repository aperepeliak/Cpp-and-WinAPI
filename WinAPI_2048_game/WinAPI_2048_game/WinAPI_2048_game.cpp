// WinAPI_2048_game.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "WinAPI_2048_game.h"
#include "Game_2048.h"

#include <objidl.h>
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

// Game Field margins
const int MRGN_TPLEFT = 20;
const int MRGN_RIGHT = 280;
const int MRGN_BOTTOM = 280;
const int MRGN_CELL = 65;

HWND hPoints, hScore;
HMENU hMenu;
Game_2048 game;
TCHAR pts[10];
TCHAR scr[10];



VOID OnPaint(HDC hdc)
{
	// Game Field Drawing
	Graphics graphics(hdc);
	Pen      pen(Color(255, 0, 140, 150));
	graphics.DrawLine(&pen, MRGN_TPLEFT, MRGN_TPLEFT, MRGN_TPLEFT, MRGN_BOTTOM);
	graphics.DrawLine(&pen, MRGN_TPLEFT, MRGN_TPLEFT, MRGN_RIGHT, MRGN_TPLEFT);
	graphics.DrawLine(&pen, MRGN_RIGHT, MRGN_TPLEFT, MRGN_RIGHT, MRGN_BOTTOM);
	graphics.DrawLine(&pen, MRGN_TPLEFT, MRGN_BOTTOM, MRGN_RIGHT, MRGN_BOTTOM);

	// Horizontal lines
	graphics.DrawLine(&pen, MRGN_TPLEFT, MRGN_TPLEFT + MRGN_CELL, MRGN_RIGHT, MRGN_TPLEFT + MRGN_CELL);
	graphics.DrawLine(&pen, MRGN_TPLEFT, MRGN_TPLEFT + 2 * MRGN_CELL, MRGN_RIGHT, MRGN_TPLEFT + 2 * MRGN_CELL);
	graphics.DrawLine(&pen, MRGN_TPLEFT, MRGN_TPLEFT + 3 * MRGN_CELL, MRGN_RIGHT, MRGN_TPLEFT + 3 * MRGN_CELL);

	// Vertical lines
	graphics.DrawLine(&pen, MRGN_TPLEFT + MRGN_CELL, MRGN_TPLEFT, MRGN_TPLEFT + MRGN_CELL, MRGN_BOTTOM);
	graphics.DrawLine(&pen, MRGN_TPLEFT + 2 * MRGN_CELL, MRGN_TPLEFT, MRGN_TPLEFT + 2 * MRGN_CELL, MRGN_BOTTOM);
	graphics.DrawLine(&pen, MRGN_TPLEFT + 3 * MRGN_CELL, MRGN_TPLEFT, MRGN_TPLEFT + 3 * MRGN_CELL, MRGN_BOTTOM);

	// Frame Drawing

	Pen blackPen(Color(255, 0, 0, 0));
	graphics.DrawLine(&blackPen, 10, 10, 10, 290);
	graphics.DrawLine(&blackPen, 10, 10, 400, 10);
	graphics.DrawLine(&blackPen, 10, 290, 400, 290);
	graphics.DrawLine(&blackPen, 400, 10, 400, 290);

	graphics.DrawLine(&blackPen, 7, 7, 7, 293);
	graphics.DrawLine(&blackPen, 7, 7, 403, 7);
	graphics.DrawLine(&blackPen, 7, 293, 403, 293);
	graphics.DrawLine(&blackPen, 403, 7, 403, 293);
}

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{

	srand((unsigned)time(NULL));

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;

	// Initialize GDI+.
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WINAPI_2048_GAME, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPI_2048_GAME));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	GdiplusShutdown(gdiplusToken);
	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPI_2048_GAME));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_WINAPI_2048_GAME);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // Store instance handle in our global variable

	hWnd = CreateWindow(szWindowClass, TEXT("Game 2048"), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, 425, 375, NULL, NULL, hInstance, NULL);

	hPoints = CreateWindowEx(0, TEXT("STATIC"), 0, WS_CHILD | WS_VISIBLE | SS_CENTER | WS_EX_CLIENTEDGE,
		300, 27, 90, 50, hWnd, 0, hInst, 0);
	SetWindowText(hPoints, TEXT("Points: "));
	hScore = CreateWindowEx(0, TEXT("STATIC"), 0, WS_CHILD | WS_VISIBLE | SS_CENTER | WS_EX_CLIENTEDGE,
		300, 87, 90, 50, hWnd, 0, hInst, 0);
	SetWindowText(hScore, TEXT("Score: "));

	hMenu = GetMenu(hWnd);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	game.StartField();
	EnableMenuItem(hMenu, ID_GAME_UNDO, MF_GRAYED);
	game.Show(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
		{
			game.Left();
			TCHAR pts_txt[50] = L"Points: +";
			TCHAR scr_txt[50] = L"Score: ";
			_itow_s(game.getPoints(), pts, 10);
			_itow_s(game.getScore(), scr, 10);
			wcscat_s(pts_txt, 50, pts);
			wcscat_s(scr_txt, 50, scr);
			SetWindowText(hPoints, pts_txt);
			SetWindowText(hScore, scr_txt);
			EnableMenuItem(hMenu, ID_GAME_UNDO, MF_ENABLED);
			game.Show(hWnd);
			break;
		}
		case VK_RIGHT:
		{
			game.Right();
			TCHAR pts_txt[50] = L"Points: +";
			TCHAR scr_txt[50] = L"Score: ";
			_itow_s(game.getPoints(), pts, 10);
			_itow_s(game.getScore(), scr, 10);
			wcscat_s(pts_txt, 50, pts);
			wcscat_s(scr_txt, 50, scr);
			SetWindowText(hPoints, pts_txt);
			SetWindowText(hScore, scr_txt);
			EnableMenuItem(hMenu, ID_GAME_UNDO, MF_ENABLED);
			game.Show(hWnd);
			break;
		}

		case VK_UP:
		{
			game.Up();
			TCHAR pts_txt[50] = L"Points: +";
			TCHAR scr_txt[50] = L"Score: ";
			_itow_s(game.getPoints(), pts, 10);
			_itow_s(game.getScore(), scr, 10);
			wcscat_s(pts_txt, 50, pts);
			wcscat_s(scr_txt, 50, scr);
			SetWindowText(hPoints, pts_txt);
			SetWindowText(hScore, scr_txt);
			EnableMenuItem(hMenu, ID_GAME_UNDO, MF_ENABLED);
			game.Show(hWnd);
			break;
		}

		case VK_DOWN:
		{
			game.Down();
			TCHAR pts_txt[50] = L"Points: +";
			TCHAR scr_txt[50] = L"Score: ";
			_itow_s(game.getPoints(), pts, 10);
			_itow_s(game.getScore(), scr, 10);
			wcscat_s(pts_txt, 50, pts);
			wcscat_s(scr_txt, 50, scr);
			SetWindowText(hPoints, pts_txt);
			SetWindowText(hScore, scr_txt);
			EnableMenuItem(hMenu, ID_GAME_UNDO, MF_ENABLED);
			game.Show(hWnd);
			break;
		}
		}
		break;

	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;

		case ID_GAME_UNDO:
		{
			game.Undo();
			TCHAR pts_txt[50] = L"Points: +";
			TCHAR scr_txt[50] = L"Score: ";
			_itow_s(game.getPoints(), pts, 10);
			_itow_s(game.getScore(), scr, 10);
			wcscat_s(pts_txt, 50, pts);
			wcscat_s(scr_txt, 50, scr);
			SetWindowText(hPoints, pts_txt);
			SetWindowText(hScore, scr_txt);
			EnableMenuItem(hMenu, ID_GAME_UNDO, MF_GRAYED);
			game.Show(hWnd);
			break;
		}
			
		case ID_GAME_NEWGAME:
			game.StartField();
			EnableMenuItem(hMenu, ID_GAME_UNDO, MF_GRAYED);
			game.Show(hWnd);
			SetWindowText(hPoints, L"Points: +0");
			SetWindowText(hScore, L"Score: 0");
			break;

		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		OnPaint(hdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
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
