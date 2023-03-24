#include "header.h"

//--------------------------------------------------------GENERAL--------------------------------------------------------

DataParent makeDataParent(int idDokter, string namaDokter, string tanggalGabung, string username, string password) {
	DataParent data;
	
	data.idDokter = idDokter;
	strcpy(data.namaDokter, namaDokter);
	strcpy(data.tanggalGabung, tanggalGabung);
	strcpy(data.username, username);
	strcpy(data.password, password);
	
	return data;
}

DataChild makeDataChild(int idRiwayat, string diagnosaPenyakit, string obat, string tglPeriksa, int idHewanDiperiksa, int statusPeriksa, int idDokterPemeriksa) {
	DataChild data;
	
	data.idRiwayat = idRiwayat;
	strcpy(data.diagnosaPenyakit, diagnosaPenyakit);
	strcpy(data.obat, obat);
	strcpy(data.tglPeriksa, tglPeriksa);
	data.statusPeriksa = statusPeriksa;
	data.idHewanDiperiksa = idHewanDiperiksa;
	data.idDokterPemeriksa = idDokterPemeriksa;
	
	return data;
}

DataHewan makeDataList(int idHewan, string jenisHewan, string jenisKelaminHewan, string namaHewan, string tglLahirHewan) {
	DataHewan temp;
	
	temp.idHewan = idHewan;
	strcpy(temp.jenisHewan, jenisHewan);
	strcpy(temp.jenisKelaminHewan, jenisKelaminHewan);
	strcpy(temp.namaHewan, namaHewan);
	strcpy(temp.tglLahirHewan, tglLahirHewan);
	
	return temp;
}

void gotoxy(int x, int y) {
	COORD coord;
	
	coord.X = x;
	coord.Y = y;
	
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void logo(int x, int y) {
	gotoxy(x, y++); puts("\033[33m                             \033[36m   =%%%%++   *%%%%- :%%%=   %%%#  .%%%%%%%%.     %%*       ");
	gotoxy(x, y++); puts("\033[33m        :%%*    .%%*         \033[36m  +%%%%%%%-  *%%%+  .+%%%*  =%%:  %%%%%%%%%#    *%%%:      ");
	gotoxy(x, y++); puts("\033[33m       %%%%%*  *%%%%%        \033[34m =%%%  .%%#   %%%=   -%%%%% .%#   %% %%%..%%    *%%%%      ");
	gotoxy(x, y++); puts("\033[33m      -%%%%%%  %%%%%%%       \033[34m %%%%         %%%-   .%%%%%%%%#      %%%       +%:-%%%     ");
	gotoxy(x, y++); puts("\033[33m      -%%%%%#  %%%%%%*       \033[34m #%%%         %%%-   .%% %%%%%#      %%%       #%%%%%%=    ");
	gotoxy(x, y++); puts("\033[33m =%%=  %%%%%*  +%%%%%  .%%%  \033[35m *%%%%. .*-   %%%=   :%#  #%%%#      %%%      .%%%%%%%%    ");
	gotoxy(x, y++); puts("\033[33m %%%%. -%%%%+  .%%%%*  %%%%. \033[35m  %%%%%%%%:  .%%%+   =%%.  -%%#     :%%%%     #%.  =%%%+   ");
	gotoxy(x, y++); puts("\033[33m:%%%%*  *%%=    =%%+  -%%%%. \033[35m   *%%%%#+   %%%%%- .%%%*   .%#     %%%%%*   %%%%  %%%%%=  ");
	gotoxy(x, y++); puts("\033[33m=%%%%%:   .%%%%%%-    %%%%%= \033[35m                                                           ");
	gotoxy(x, y++); puts("\033[33m  +%%%  #%%%%%%%%%%#  %%%%   \033[36m .%%%*%%.    %%%#   :%%%%%%%%%  %%%% :%%%% :%%.  *%%%:     ");
	gotoxy(x, y++); puts("\033[33m    .  #%%%%%%%%%%%%# ..     \033[36m %%%-  *%    %%%%=  -%*-%%% %%  .%%%= %%%%  %#   #%%%%     ");
	gotoxy(x, y++); puts("\033[33m      %%%%%%%%%%%%%%%%       \033[34m #%%%%%%-   %= %%%+    -%%%      .%%%%%%%%%%%   *% *%%%    ");
	gotoxy(x, y++); puts("\033[33m      %%%%%%%%%%%%%%%%       \033[34m  *%%%%%%  +%=.*%%%    -%%%       %%%%%.%%%%.   %%.+%%%-   ");
	gotoxy(x, y++); puts("\033[33m       .%%%%%%%%%%%%-        \033[35m %  :%%%%. %%%%%%%%+   -%%%       #%%%= %%%%.  #%%%%%%%#   ");
	gotoxy(x, y++); puts("\033[33m        .%%%%%%%%%%-         \033[35m %%::#%%% +%=   %%%%   =%%%:       %%%  *%%*  .%%   +%%%:  ");
	gotoxy(x, y++); puts("\033[33m                             \033[35m *%%%%%*. %%%- =%%%%% =%%%%%.      %%#   %%. :%%%=  %%%%%= \033[30m");
}

void loadingScreen(int widthCol, int heightRow) {
	system("cls");
	system("color F0");
	
	int i, j;
	unsigned char keyEnter;
	bool isDone = false;
	
	//All Loading Screen Item Height
	int loadingScreenHeight = 27;
	int loadingScreenY = ((heightRow - loadingScreenHeight) / 2) - 2;
	
	
	//logo size (width)
	int logoWidth = 88;
	int logoX = (widthCol - logoWidth) / 2;
	
	logo(logoX-2,loadingScreenY); //awalnya Y = 2
	
	
	//Print Box
	int boxWidth = 52;
	int boxX = (widthCol - boxWidth) / 2;
	
	for(i=1; i<=boxWidth; i++) {
		printf("\e[?25l"); //Disable Cursor
		gotoxy(boxX+i,(loadingScreenY-2)+9+12); printf("\033[30m%c", 205);
		gotoxy(boxX+i,(loadingScreenY-2)+11+12); printf("%c", 205);
	}
	
	for(j=1; j<=3; j++) {
		printf("\e[?25l"); //Disable Cursor
		gotoxy(boxX+1,(loadingScreenY-2)+8+j+12); printf("%c", 186);
		gotoxy(boxX+boxWidth,(loadingScreenY-2)+8+j+12); printf("%c", 186);
	}
	
	gotoxy(boxX+1,(loadingScreenY-2)+9+12); printf("%c", 201);
	gotoxy(boxX+1,(loadingScreenY-2)+11+12); printf("%c", 200);
	gotoxy(boxX+boxWidth,(loadingScreenY-2)+9+12); printf("%c", 187);
	gotoxy(boxX+boxWidth,(loadingScreenY-2)+11+12); printf("%c", 188);
	
	
	//Print Credits
	int creditWidth = 86;
	int creditX = (widthCol - creditWidth) / 2;
	
	gotoxy(creditX, (loadingScreenY-2)+16+12); printf("\033[30m[*] System was made by Aloysius Gonzaga Seto Galih D. (210711180) & Reyhan (210711212)");
	
	
	//Print Loading
	int loadingWidth = boxWidth-2;
	int loadingX = (widthCol - loadingWidth) / 2;
	
	int loadingPercentWidth = 12;
	int loadingPercentX = (widthCol - loadingPercentWidth) / 2;
	
	for(i=1; i<=loadingWidth; i++) {
		printf("\e[?25l"); //Disable Cursor
		gotoxy(loadingPercentX,(loadingScreenY-2)+13+12); printf("Loading %d%%", i*2); //Loading Percentage
		gotoxy(boxX+1+i,(loadingScreenY-2)+10+12); printf("\033[32m%c", 177); //Loading Bar
		Sleep(50);
	}
	
	//Print Press Enter Key
	int pressEnterWidth = 20;
	int pressEnterX = (widthCol - pressEnterWidth) / 2;
	
	gotoxy(pressEnterX,(loadingScreenY-2)+13+12); printf("[PRESS \'ENTER\' KEY!]\033[30m");
	printf("\e[?25l"); //Disable Cursor

	isDone = true;
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE)); //flush getch / prevent getch input that entered too soon
	
	while(1) {
		keyEnter = getch();
		if(keyEnter == 13 && isDone) break;
	}
	
	printf("\e[?25l"); //Disable Cursor
	
	return;
}
