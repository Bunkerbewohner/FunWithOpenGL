// RoboGiants.cpp : Definiert den Einstiegspunkt für die Anwendung.
//

#include "stdafx.h"
#include "RoboGiants.h"
#include <gl\GL.h>
#include <gl\GLU.h>
#include "Renderer.h"
#include "Drawable.h"

#define MAX_LOADSTRING 100

// Globale Variablen:
HINSTANCE hInst;								// Aktuelle Instanz
TCHAR szTitle[MAX_LOADSTRING];					// Titelleistentext
TCHAR szWindowClass[MAX_LOADSTRING];			// Klassenname des Hauptfensters

// Vorwärtsdeklarationen der in diesem Codemodul enthaltenen Funktionen:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

void draw(HWND hWnd)
{
	auto hdc = GetDC(hWnd);

	glClearColor(100.0 / 255.0, 149.0 / 255.0, 237.0 / 255.0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	SwapBuffers(hdc);
	ReleaseDC(hWnd, hdc);
}

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Hier Code einfügen.
	MSG msg;
	HACCEL hAccelTable;

	// Globale Zeichenfolgen initialisieren
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_ROBOGIANTS, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Anwendungsinitialisierung ausführen:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ROBOGIANTS));

	Renderer* renderer = new Renderer();
	IDrawable placeholder = std::make_shared<Placeholder>();

	renderer->Add(placeholder);

	renderer->Draw();

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

		draw(msg.hwnd);
	}

	return (int) msg.wParam;
}



//
//  FUNKTION: MyRegisterClass()
//
//  ZWECK: Registriert die Fensterklasse.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;	
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ROBOGIANTS));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	//wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_ROBOGIANTS);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNKTION: InitInstance(HINSTANCE, int)
//
//   ZWECK: Speichert das Instanzenhandle und erstellt das Hauptfenster.
//
//   KOMMENTARE:
//
//        In dieser Funktion wird das Instanzenhandle in einer globalen Variablen gespeichert, und das
//        Hauptprogrammfenster wird erstellt und angezeigt.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Instanzenhandle in der globalen Variablen speichern

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNKTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ZWECK:  Verarbeitet Meldungen vom Hauptfenster.
//
//  WM_COMMAND	- Verarbeiten des Anwendungsmenüs
//  WM_PAINT	- Zeichnen des Hauptfensters
//  WM_DESTROY	- Beenden-Meldung anzeigen und zurückgeben
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_CREATE:
	{
					  HDC hdc = GetDC(hWnd);					  

					  PIXELFORMATDESCRIPTOR pxf = {
						  sizeof(PIXELFORMATDESCRIPTOR),
						  1, // version nr
						  PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
						  PFD_TYPE_RGBA,
						  24, // 24 bit color depth
						  0, 0, 0, 0, 0, // color bits ignored,
						  0, // no alpha buffer
						  0, // shift bit ignored
						  0, // no accumulation buffer
						  0, 0, 0, 0, // accumulation bits ignored
						  32, // 32 bit z-buffer
						  0, // no stencil buffer
						  0, // no auxiliary buffer
						  PFD_MAIN_PLANE, //  main layer
						  0, // reversed
						  0, 0, 0, 0 // layer mask ignored
					  };
					  int iPixelFormat = ChoosePixelFormat(hdc, &pxf);
					  SetPixelFormat(hdc, iPixelFormat, &pxf);

					  HGLRC renderingContext = wglCreateContext(hdc);

					  if (renderingContext)
					  {
						  if (!wglMakeCurrent(hdc, renderingContext))
						  {
							  MessageBox(hWnd, (LPCWSTR)"Failed to initialize OpenGL (wglMakeCurrent)", (LPCWSTR)"Error", 0);
						  }
					  }
					  else
					  {
						  MessageBoxA(hWnd, "Failed to initialize OpenGL (wglCreateContext)", "Error", 0);
					  }

					  break;
	}
	case WM_ERASEBKGND:
		// don't erase background every time dude
		return 1;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Menüauswahl bearbeiten:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
	{
					 hdc = GetDC(hWnd);

					 glClearColor(100.0/255.0, 149.0/255.0, 237.0/255.0, 0);
					 glClear(GL_COLOR_BUFFER_BIT);
					 
					 SwapBuffers(hdc);
					 ReleaseDC(hWnd, hdc);

					 //hdc = BeginPaint(hWnd, &ps);
					 // TODO: Hier den Zeichnungscode hinzufügen.
					 //EndPaint(hWnd, &ps);
					 break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Meldungshandler für Infofeld.
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
