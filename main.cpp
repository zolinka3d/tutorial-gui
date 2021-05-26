#include <windows.h>
#include <stdlib.h>

#define FILE_MENU_NEW 1
#define FILE_MENU_OPEN 2 
#define FILE_MENU_EXIT 3
#define GENERATE_BUTTON 4
//#define CHANGE_TITLE 4

LRESULT CALLBACK OkniennaProcedura(HWND, UINT, WPARAM, LPARAM);

void DodajMenu(HWND);
void DodajKontrolki(HWND);
void loadImages();


HWND hImie, hWiek, hOut, hLogo;
HBITMAP hLogoImage, hGenerateImage;
HMENU hMenu; 
//HWND hEdit;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow )
	{
		
		//MessageBox(NULL,  "Nie wiem czy chcesz to zobaczyc", "Uwazaj!", MB_OK);
		
		WNDCLASSW okno = {0};
		
		okno.hbrBackground = (HBRUSH) COLOR_WINDOW ;
		okno.hCursor = LoadCursor(NULL, IDC_ARROW);
		okno.hInstance = hInst;
		okno.lpszClassName = L"mojaKlasaOkna";
		okno.lpfnWndProc = OkniennaProcedura;
		
		
		if(!RegisterClassW(&okno)) return -1;
		
		CreateWindowW(L"mojaKlasaOkna", L"Moje Okno", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 500,150, 700,600, NULL, NULL, NULL, NULL );
		
		MSG wiad = {0};
		while(GetMessage (&wiad, NULL, NULL, NULL))
		{
			TranslateMessage(&wiad);
			DispatchMessage(&wiad);
		}
		
		return 0;
		
	}
 LRESULT CALLBACK OkniennaProcedura(HWND hWnd, UINT wiad, WPARAM wp, LPARAM lp)
 {
 	switch (wiad)
 	{
 		case WM_COMMAND:
 			
 			switch(wp)
 			{
 			
 				case FILE_MENU_EXIT:
 					DestroyWindow(hWnd);
 					break;
 				case FILE_MENU_NEW:
 					MessageBeep(MB_ICONINFORMATION);
 					break;
 				case GENERATE_BUTTON:
 					char imie[20], wiek[3], out[60];
 					
 					GetWindowText(hImie, imie, 20);
 					GetWindowText(hWiek, wiek, 3);
 					
 					strcpy(out, imie);
 					strcat(out, " ma ");
 					strcat(out, wiek);
 					strcat(out, " lat. ");
 					
 					SetWindowText(hOut, out); 
 					
 					break;
// 				case CHANGE_TITLE:
// 					wchar_t text[100];
// 					GetWindowTextW(hEdit, text, 100);
// 					SetWindowTextW(hWnd, text);
//				 	break;	
			 }
 		
 			break;
 		
 		case WM_CREATE:
 			loadImages();
 			DodajMenu(hWnd);
 			DodajKontrolki(hWnd);
 			
 			
 			
 			break;
 		
 		case WM_DESTROY:
 			PostQuitMessage(0);
 			break;
 		default:
 			return DefWindowProcW(hWnd, wiad, wp, lp);
 			
 				
	 }

	 
 }
 
 void DodajMenu(HWND hWnd)
 { 
 	hMenu = CreateMenu();
 	HMENU hPlikMenu = CreateMenu();
 	HMENU hPodMenu = CreateMenu();
 	
 	AppendMenu(hPodMenu, MF_STRING, NULL , "PodMenu");
 	
 	AppendMenu(hPlikMenu, MF_POPUP, (UINT_PTR)hPodMenu, "Otwórz PodMenu");
 	AppendMenu(hPlikMenu, MF_STRING, FILE_MENU_NEW, "Nowy");
 	AppendMenu(hPlikMenu, MF_SEPARATOR, NULL, NULL);
 	AppendMenu(hPlikMenu, MF_STRING, FILE_MENU_EXIT, "Zamknij");
 	
 	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hPlikMenu, "Plik");
 	AppendMenu(hMenu, MF_STRING, NULL, "pomocy");
 	
 	SetMenu(hWnd, hMenu);
 	
 }
 
 void DodajKontrolki(HWND hWnd)
 	{
 		CreateWindowW(L"Static", L"Imie: ", WS_VISIBLE | WS_CHILD ,
		   100, 50, 98, 38, hWnd, NULL, NULL, NULL);
		hImie = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER ,
		   200, 50, 98, 38, hWnd, NULL, NULL, NULL);   
		   
		CreateWindowW(L"Static", L"Wiek: ", WS_VISIBLE | WS_CHILD ,
		   100, 100, 98, 38, hWnd, NULL, NULL, NULL);
		hWiek = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER ,
		   200, 100, 98, 38, hWnd, NULL, NULL, NULL);    
		   
		CreateWindowW(L"Button", L"Wygeneruj", WS_VISIBLE | WS_CHILD ,
		   150, 150, 150, 20, hWnd, (HMENU)GENERATE_BUTTON, NULL, NULL);
		   
		hOut = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER ,
		   100, 200, 200, 100, hWnd, NULL, NULL, NULL); 
		   
		hLogo = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP ,
		   350, 300, 100, 100, hWnd, NULL, NULL, NULL);
		   
		SendMessageW(hLogo, STM_SETIMAGE, IMAGE_BITMAP,(LPARAM)hLogoImage);
		   
// 	CreateWindowW(L"Static", L"Dodaj tekst tutaj: ", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER,
//		   200, 100, 150, 20, hWnd, NULL, NULL, NULL); 
//	hEdit =	CreateWindowW(L"Edit", L"...", WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_AUTOVSCROLL ,
//		200, 130, 150, 80,hWnd, NULL, NULL, NULL );
//		CreateWindowW(L"Button", L"Zmien Tytul", WS_VISIBLE | WS_CHILD ,
//		   200, 215, 150, 20, hWnd, (HMENU)CHANGE_TITLE, NULL, NULL); 
		
		
		
 	}
 
 void loadImages()
	{
		hLogoImage = (HBITMAP)LoadImageW(NULL, L"Logo.bmp", IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);	
	}
 
 
