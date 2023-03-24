// [TUGAS BESAR ISD]
// Aloysius Gonzaga Seto Galih Damarjati / 210711180 / A (PERCENTAGE OF WORK == 99%)
// Reyhan / 210711212 / A

#include "header.h"

int main() {
	//SETTING WINDOW CONSOLE & GETTING INFO SCREEN RESOLUTION
	system("color F0");
	HWND hwnd = GetConsoleWindow();
	
	DWORD dwWidth = GetSystemMetrics(SM_CXSCREEN);
	DWORD dwHeight = GetSystemMetrics(SM_CYSCREEN);
	MoveWindow(hwnd, 0, 0, dwWidth, dwHeight, TRUE);
	
	ShowWindow(hwnd, SW_MAXIMIZE); system("color F0");
	
	
	//GETTING INFO COL/ROW
	CONSOLE_SCREEN_BUFFER_INFOEX info = {0};
    int width, height;
    HANDLE hConsole = NULL;

    //width/height of this window in terms of columns and rows
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    info.cbSize = sizeof(info);
    GetConsoleScreenBufferInfoEx(hConsole, &info);

    width = info.srWindow.Right+1;
    height = info.srWindow.Bottom+1;
	
    //MessageBox(0,"Message bodeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeey\ntestststests", "Message titleeeeeeeeeeeeeeeeeeeeeeeeeeeeeee", MB_OK);

	
	//START INITIALIZATION PROGRAM
	Multilist L;
	List Hewan;
	
	AddressParent cek;
	
	createEmpty(&L);
	createEmptyList(&Hewan);
	
	bool menu = true;
	
	string username;
	string password;
	
	unsigned char key;
	int i;
	
	//Loading Screen	
	loadingScreen(width, height); printf("\e[?25h"); //Re-Enable Cursor
	
//	menuAdmin(&L, &Hewan);
	
	do {
		system("color E0");
		
		system("cls");
		printf("\n\n\n\033[31m");
		printf("\n\t\t\t\t   ================================================");
		printf("\n\t\t\t\t     ||                                        ||");
		printf("\n\t\t\t\t     ||               LOGIN PAGE               ||");
		printf("\n\t\t\t\t     ||       KLINIK HEWAN - CINTA SATWA       ||");
		printf("\n\t\t\t\t     ||                                        ||");
		printf("\n\t\t\t\t   ================================================");
		printf("\n\n\n\033[30m"); 
		printf("\t\t\t\t\t    <> Username      : "); fflush(stdin); gets(username);
		printf("\t\t\t\t\t    <> Password      : "); fflush(stdin);
		
		//Input Password
		i = 0;
		while(1) {
			key = getch();
			if(key == 0 || key == 0xE0) key = getch();
			
			//Detect Enter
			if(key == 13) {
				password[i] = '\0';
				break;
			}
			//Detect Backspace
			else if(key == 8) {
				if(i!=0) {
					i--;
					putch('\b'); putch(' '); //Delete Asterisk (Backspace + InsertBlank)
					putch('\b'); //Move Cursor Backspace
				}
			}
			//Detect Esc, Horizontal Tab, ArrowKeys (Up, Down, Left, Right)
			else if(key == 27 || key == 9 || key == 72 || key == 80 || key == 75 || key == 77) {
				//doNothing
			}
			
			else {
				password[i] = key;
				i++;
				putch('*');
			}
		}
		
		if(strcmp(username, "admincintasatwa")==0 && strcmp(password, "admincintasatwa")==0) {
			printf("\n\n\t\t\t\t             Berhasil login sebagai Admin!"); getch();
			menuAdmin(&L, &Hewan);
		}
		else if(strcmpi(username, "logout")==0 && strcmpi(password, "logout")==0) {
			printf("\n\n\n\n\t\t\t\t             Keluar program, terima kasih!\n");
			printf("\n\t\t\t\t    Aloysius Gonzaga Seto Galih D. - 210711180 - A");
			printf("\n\t\t\t\t                Reyhan - 210711212 - A");
			menu = false;
		}
		else if(strlen(username)==0 || strlen(password)==0) {
			printf("\n\n\t\t\t\t      Username atau password tidak boleh kosong!");
		}
		else {
			cek=findParentByLoginInfo(L, username, password);
			if(cek != NULL) {
				printf("\n\n\t\t\t\t            Berhasil login sebagai Dokter!"); getch();
				menuDokter(&L, &Hewan, cek);
			}
			else {
				printf("\n\n\t\t\t\t            Username atau password salah!");
			}
		}
		
		getch();
		
	} while(menu != false);
	
	return 0;
}
