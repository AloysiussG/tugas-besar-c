#include "header.h"

//--------------------------------------------------------MENU ITEMS--------------------------------------------------------
void menuAdmin(Multilist *L, List *H) {
	int menu;
	char key;
	
	DataParent dokter;
	DataChild riwayat;
	DataHewan hewan;
	
	AddressParent P;
	AddressChild addrRiwayat;
	AddressHewan addrHewan;
	
	Tanggal tgl;
	
	menu = 1;
	int x = 3, y = menu+3;
	
	do {
		//Inisialisasi Seluruh Temporary Variable
		//menu = -1;
		dokter = makeDataParent(-1, "", "", "", "");
		riwayat = makeDataChild(-1, "", "", "", -1, -1, -1);
		hewan = makeDataList(-1, "", "", "", "");
		
		//Sorting Jenis Hewan
		if(!isEmptyList(*H)) sortByJenisHewanList(H);
		
		system("color E0");
		
		system("cls");
		printf("\n\t\033[31m========== MENU ADMIN ==========\n\033[30m");
		printf("\n\t--- Menu Kelola Dokter ---");
		printf("\n\t[1] Tambah Dokter");
		printf("\n\t[2] Tampil Dokter");
		printf("\n\t[3] Cari Dokter");
		printf("\n\t[4] Ubah Dokter");
		printf("\n\t[5] Hapus Dokter\n"); //jika dokter keluar
		printf("\n\t--- Menu Periksa Hewan ---");
		printf("\n\t[6] Pendaftaran Periksa Hewan"); //datahewan, dokter yg mana, id riwayat periksa
		printf("\n\t[7] Hapus Data Periksa Hewan"); //jika hewan mati
		printf("\n\t[8] Tampil Data Master Hewan\n");
		printf("\n\t--- Laporan ---");
		printf("\n\t[9] Laporan Admin\n");
		printf("\n\t[Esc] Logout\n");
		printf("\n\t>>> ");		
		
		
		
		while(1) {	
			printf("\e[?25l"); //hideCursor
			//gotoxy(x,20); printf("Y = %2d", y);
			
			gotoxy(x,y); printf("->");
			key = getch(); 
			
			if(key == 0 || key == 0xE0) key = getch();
			
			if(key == 13) {
				y = 20;
				gotoxy(x,y);
				break;
			}
			else if(key == 72) { //up
				if(menu != 1) {
					if(menu == 9 || menu == 6) {
						gotoxy(x,y); printf("  ");
						y-=3;
						menu--;
					}
					else if(menu == 0) {
						gotoxy(x,y); printf("  ");
						y-=2;
						menu = 9;
					}
					else {
						gotoxy(x,y); printf("  ");
						y--;
						menu--;
					}
				}
			}
			else if(key == 80) { //down
				if(menu != 0) {
					if(menu == 5 || menu == 8) {
						gotoxy(x,y); printf("  ");
						y+=3;
						menu++;
					}
					else if(menu == 9) {
						gotoxy(x,y); printf("  ");
						y+=2;
						menu = 0;
					}
					else {
						gotoxy(x,y); printf("  ");
						y++;
						menu++;
					}
				}
			}
			else if(key == 27) {
				gotoxy(x,y); printf("  ");
				y = 18; //koordinat Y untuk menu ESC Logout
				gotoxy(x,y); printf("->");
				menu = 0;
				
				y = 20;
				gotoxy(x,y);
				break;
			} 
			else {
				//doNothing
			}
		}
		
		
		
		
		/*
		// ---- KEY GETCH ----
		
		key = getch();
		
		if(key == 27) menu = 0;
		else if(key == 49) menu = 1;
		else if(key == 50) menu = 2;
		else if(key == 51) menu = 3;
		else if(key == 52) menu = 4;
		else if(key == 53) menu = 5;
		else if(key == 54) menu = 6;
		else if(key == 55) menu = 7;
		else if(key == 56) menu = 8;
		else if(key == 57) menu = 9;
		else menu = -1;
		// -------------------
		*/
		
		
		printf("\n");
		
		printf("\e[?25h"); //showCursor
		
		switch(menu) {
			
			//Menu Kelola Dokter
			
			case 1: //Tambah Dokter
				system("cls");
				printf("\n\t--- Tambah Data Dokter ---\n");
				
				//Cek Keunikan ID Dokter
				while(1) {
					printf("\tMasukkan ID Dokter       : "); fflush(stdin); scanf("%d", &dokter.idDokter);
					if(dokter.idDokter <= 0) printf("\n\t[!] ID Dokter Invalid\n\n");
					else if(findParent(*L, dokter.idDokter) == NULL) {
						break;
					}
					else {
						printf("\n\t[!] ID Dokter Ditemukan pada List! ID Dokter Harus Unik\n\n");
					}
				}
				
				while(1) {
					printf("\tMasukkan Nama Dokter     : "); fflush(stdin); gets(dokter.namaDokter);
					if(strlen(dokter.namaDokter) == 0) printf("\n\t[!] Nama Dokter Tidak Boleh Kosong\n\n");
					else if(findParentByName(*L, dokter.namaDokter) != NULL) printf("\n\t[!] Nama Dokter Ditemukan pada List! Nama Dokter Harus Unik\n\n");
					else break;
				}
				
				while(1) {
					printf("\tTanggal Gabung Dokter    : "); fflush(stdin); gets(dokter.tanggalGabung);
					sscanf(dokter.tanggalGabung, "%d-%d-%d", &tgl.day, &tgl.month, &tgl.year);
					
					if(strlen(dokter.tanggalGabung)!=10 || tgl.day>31 || tgl.day<1 || tgl.month>12 || tgl.month<1 || tgl.year<1 || dokter.tanggalGabung[2]!='-' || dokter.tanggalGabung[5]!='-') {
						printf("\n\t[!] Tanggal invalid/format tanggal harus DD-MM-YYYY!\n\n");
					}
					else {
						break;
					}
				}
				
				printf("\n\t--- Data Login Dokter ---\n");
				
				//Cek Keunikan Username Dokter, Agar Tidak Double Data Login
				while(1) {
					printf("\tMasukkan Username Dokter : "); fflush(stdin); gets(dokter.username);
					if(strlen(dokter.username) == 0) printf("\n\t[!] Username Tidak Boleh Kosong\n\n");
					else if(strcmpi(dokter.username, "admincintasatwa") == 0) printf("\n\t[!] Username Tidak Boleh \"admincintasatwa\"\n\n");
					else if(strcmpi(dokter.username, "logout") == 0) printf("\n\t[!] Username Tidak Boleh \"logout\"\n\n");
					else if(findParentByUsername(*L, dokter.username) == NULL) {
						break;
					}
					else {
						printf("\n\t[!] Username Ditemukan pada List! Username Harus Unik\n\n");
					}
				}
				
				while(1) {
					printf("\tMasukkan Password Dokter : "); fflush(stdin); gets(dokter.password);
					if(strlen(dokter.password) == 0) printf("\n\t[!] Password Tidak Boleh Kosong\n\n");
					else break;
				}
				
				insertLastParent(L, dokter);
				
				printf("\n\t[!] Berhasil menambah dokter");
				
				y=menu+3;
				break;

			case 2: //Tampil Dokter
				if(!isEmpty(*L)) {
					system("cls");
					printf("\n\t--- Tampil Semua Dokter ---\n");
					printAllParent((*L));
				}
				else {
					printf("\n\t[!] Data Dokter Masih Kosong");
				}
				
				y=menu+3;
				break;

			case 3: //Cari Dokter
				if(!isEmpty(*L)) {
					system("cls");
					printf("\n\t--- Cari Data Dokter ---\n");
					printf("\tMasukkan ID Dokter yang Ingin Dicari : "); fflush(stdin); scanf("%d", &dokter.idDokter);
					P = findParent(*L, dokter.idDokter);
					if(P != NULL) {
						printParent(P);
					}
					else {
						printf("\n\t[!] Not Found");
					}
				}
				else {
					printf("\n\t[!] Data Dokter Masih Kosong");
				}
				
				y=menu+3;
				break;
				
			case 4: //Ubah Dokter
				if(!isEmpty(*L)) {
					system("cls");
					printf("\n\t--- Ubah Data Dokter ---\n");
					printf("\tMasukkan ID Dokter yang Ingin Diubah : "); fflush(stdin); scanf("%d", &dokter.idDokter);
					P = findParent(*L, dokter.idDokter);
					if(P != NULL) {
						dokter = P->dataParent;
						
						printf("\n\t--- Input Data Dokter Baru ---\n");
						
						//Cek Keunikan ID Dokter
						while(1) {
							printf("\tMasukkan ID Dokter       : "); fflush(stdin); scanf("%d", &dokter.idDokter);
							if(dokter.idDokter <= 0) printf("\n\t[!] ID Dokter Invalid\n\n");
							else if(findParent(*L, dokter.idDokter) == P) break;
							else if(findParent(*L, dokter.idDokter) == NULL) {
								break;
							}
							else {
								printf("\n\t[!] ID Dokter Ditemukan pada List! ID Dokter Harus Unik\n\n");
							}
						}
						
						while(1) {
							printf("\tMasukkan Nama Dokter     : "); fflush(stdin); gets(dokter.namaDokter);
							if(strlen(dokter.namaDokter) == 0) printf("\n\t[!] Nama Dokter Tidak Boleh Kosong\n\n");
							else if(findParentByName(*L, dokter.namaDokter) == P) break;
							else if(findParentByName(*L, dokter.namaDokter) != NULL) printf("\n\t[!] Nama Dokter Ditemukan pada List! Nama Dokter Harus Unik\n\n");
							else break;
						}
						
						while(1) {
							printf("\tTanggal Gabung Dokter    : "); fflush(stdin); gets(dokter.tanggalGabung);
							sscanf(dokter.tanggalGabung, "%d-%d-%d", &tgl.day, &tgl.month, &tgl.year);
							
							if(strlen(dokter.tanggalGabung)!=10 || tgl.day>31 || tgl.day<1 || tgl.month>12 || tgl.month<1 || tgl.year<1 || dokter.tanggalGabung[2]!='-' || dokter.tanggalGabung[5]!='-') {
								printf("\n\t[!] Tanggal invalid/format tanggal harus DD-MM-YYYY!\n\n");
							}
							else {
								break;
							}
						}
						
						printf("\n\t--- Data Login Dokter ---\n");
						
						//Cek Keunikan Username Dokter, Agar Tidak Double Data Login
						while(1) {
							printf("\tMasukkan Username Dokter : "); fflush(stdin); gets(dokter.username);
							if(strlen(dokter.username) == 0) printf("\n\t[!] Username Tidak Boleh Kosong\n\n");
							else if(strcmpi(dokter.username, "admincintasatwa") == 0) printf("\n\t[!] Username Tidak Boleh \"admincintasatwa\"\n\n");
							else if(strcmpi(dokter.username, "logout") == 0) printf("\n\t[!] Username Tidak Boleh \"logout\"\n\n");
							else if(findParentByUsername(*L, dokter.username) == P) break;
							else if(findParentByUsername(*L, dokter.username) == NULL) {
								break;
							}
							else {
								printf("\n\t[!] Username Ditemukan pada List! Username Harus Unik\n\n");
							}
						}
						
						while(1) {
							printf("\tMasukkan Password Dokter : "); fflush(stdin); gets(dokter.password);
							if(strlen(dokter.password) == 0) printf("\n\t[!] Password Tidak Boleh Kosong\n\n");
							else break;
						}
						
						P->dataParent = dokter;
						
						printf("\n\t[!] Berhasil Mengubah Data Dokter");
					}
					else {
						printf("\n\t[!] Not Found");
					}
				}
				else {
					printf("\n\t[!] Data Dokter Masih Kosong");
				}
				
				y=menu+3;
				break;
				
			case 5: //Hapus Dokter
				if(!isEmpty(*L)) {
					system("cls");
					printf("\n\t--- Hapus Data Dokter ---\n");
					printf("\tMasukkan ID Dokter : "); fflush(stdin); scanf("%d", &dokter.idDokter);
					P = findParent(*L, dokter.idDokter);
					if(P != NULL) {
						printf("\n\t[!] Berhasil Menghapus Data \"drh. %s\" beserta Seluruh Riwayatnya", P->dataParent.namaDokter);
						deleteAtParent(L, dokter.idDokter);
					}
					else {
						printf("\n\t[!] Not Found");
					}
				}
				else {
					printf("\n\t[!] Data Dokter Masih Kosong");
				}
				
				y=menu+3;
				break;
				
			//Menu Periksa Hewan
			
			case 6: //Pendaftaran Periksa Hewan
				if(!isEmpty(*L)) {
					system("cls");
					printf("\n\t--- Pendaftaran Periksa Hewan ---\n");
					
					while(1) {
						printf("\tMasukkan ID Hewan : "); fflush(stdin); scanf("%d", &hewan.idHewan);
						if(hewan.idHewan <= 0) printf("\n\t[!] ID Hewan Invalid\n\n");
						else break;
					}
					
					//FIND ID hewan, if belum ada, insertNew, if sudah ada skip
					addrHewan = findNodeList(*H, hewan.idHewan);
					
					//Data Hewan Ditemukan / Tidak Perlu InsertNew
					if(addrHewan != NULL) {
						printf("\n\t[*] Data Hewan Ditemukan Pada List Master Hewan");
						printf("\n\t    Tidak Perlu Insert Data Baru!\n");
						printDataList(addrHewan);
						
						//PRINT List Dokter Available
						printf("\n\t--- List Dokter yang Tersedia ---\n");
						printAllParentForPasien(*L);
						printf("\n\n");
						
						//PILIH Dokter
						while(1) {
							printf("\tPilih Nama Dokter   : drh. "); fflush(stdin); gets(dokter.namaDokter);
							P = findParentByName(*L, dokter.namaDokter);
							
							if(P != NULL) {
								
								//Cek Keunikan ID Riwayat
								while(1) {
									printf("\tMasukkan ID Periksa : "); fflush(stdin); scanf("%d", &riwayat.idRiwayat);
									if(riwayat.idRiwayat <= 0) printf("\n\t[!] ID Riwayat Invalid\n\n");
									else if(findRiwayatByIdRiwayatInAllDokter((*L), riwayat.idRiwayat) == NULL) {
										break;
									}
									else {
										printf("\n\t[!] ID Riwayat Ditemukan pada List! ID Riwayat Harus Unik\n\n");
									}
								}
								
								while(1) {
									printf("\tTanggal Periksa     : "); fflush(stdin); gets(riwayat.tglPeriksa);
									sscanf(riwayat.tglPeriksa, "%d-%d-%d", &tgl.day, &tgl.month, &tgl.year);
									
									if(strlen(riwayat.tglPeriksa)!=10 || tgl.day>31 || tgl.day<1 || tgl.month>12 || tgl.month<1 || tgl.year<1 || riwayat.tglPeriksa[2]!='-' || riwayat.tglPeriksa[5]!='-') {
										printf("\n\t[!] Tanggal invalid/format tanggal harus DD-MM-YYYY!\n\n");
									}
									else {
										break;
									}
								}
								
								insertLastChild(*L, P->dataParent.idDokter, makeDataChild(riwayat.idRiwayat, "", "", riwayat.tglPeriksa, addrHewan->hewan.idHewan, 0, P->dataParent.idDokter));
								
								printf("\n\t[!] Berhasil Input Data Periksa Hewan");
								break;
							}
							else {
								printf("\n\t[!] Dokter Tidak Ditemukan\n\n");
							}
						}
					}
					
					//Data Hewan Tidak Ditemukan / InsertNew
					else {
						//START Input Data Hewan Baru
						printf("\n\t--- Input Data Hewan Baru ---\n");
						
						while(1) {
							printf("\tMasukkan Nama Hewan          : "); fflush(stdin); gets(hewan.namaHewan);
							if(strlen(hewan.namaHewan) == 0) printf("\n\t[!] Nama Hewan Tidak Boleh Kosong\n\n");
							else break;
						}
						
						while(1) {
							printf("\tMasukkan Tanggal Lahir Hewan : "); fflush(stdin); gets(hewan.tglLahirHewan);
							sscanf(hewan.tglLahirHewan, "%d-%d-%d", &tgl.day, &tgl.month, &tgl.year);
							
							if(strlen(hewan.tglLahirHewan)!=10 || tgl.day>31 || tgl.day<1 || tgl.month>12 || tgl.month<1 || tgl.year<1 || hewan.tglLahirHewan[2]!='-' || hewan.tglLahirHewan[5]!='-') {
								printf("\n\t[!] Tanggal invalid/format tanggal harus DD-MM-YYYY!\n\n");
							}
							else {
								break;
							}
						}
						
						while(1) {
							printf("\tMasukkan Jenis Hewan         : "); fflush(stdin); gets(hewan.jenisHewan);
							if(strcmpi(hewan.jenisHewan, "Anjing") == 0 || strcmpi(hewan.jenisHewan, "Burung") == 0 || strcmpi(hewan.jenisHewan, "Kucing") == 0) {
								break;
							}
							else {
								printf("\n\t[!] Jenis Hewan Harus Anjing, Burung, atau Kucing\n\n");
							}
						}
						
						while(1) {
							printf("\tMasukkan Jenis Kelamin Hewan : "); fflush(stdin); gets(hewan.jenisKelaminHewan);
							if(strcmpi(hewan.jenisKelaminHewan, "Jantan") == 0 || strcmpi(hewan.jenisKelaminHewan, "Betina") == 0) {
								break;
							}
							else {
								printf("\n\t[!] Jenis Kelamin Hewan Harus Jantan atau Betina\n\n");
							}
						}
						
						addrHewan = alokasiList(hewan);
						insertLastList(H, addrHewan);
					
						printf("\n\t[!] Berhasil Menambahkan Data Hewan Baru\n");
						
						//END Input Data Hewan New
						
						
						//PRINT List Dokter Available
						printf("\n\t--- List Dokter yang Tersedia ---\n");
						printAllParentForPasien(*L);
						printf("\n\n");
						
						//PILIH Dokter
						while(1) {
							printf("\tPilih Nama Dokter   : drh. "); fflush(stdin); gets(dokter.namaDokter);
							P = findParentByName(*L, dokter.namaDokter);
							
							if(P != NULL) {
								
								//Cek Keunikan ID Riwayat
								while(1) {
									printf("\tMasukkan ID Periksa : "); fflush(stdin); scanf("%d", &riwayat.idRiwayat);
									if(riwayat.idRiwayat <= 0) printf("\n\t[!] ID Riwayat Invalid\n\n");
									else if(findRiwayatByIdRiwayatInAllDokter((*L), riwayat.idRiwayat) == NULL) {
										break;
									}
									else {
										printf("\n\t[!] ID Riwayat Ditemukan pada List! ID Riwayat Harus Unik\n\n");
									}
								}
								
								while(1) {
									printf("\tTanggal Periksa     : "); fflush(stdin); gets(riwayat.tglPeriksa);
									sscanf(riwayat.tglPeriksa, "%d-%d-%d", &tgl.day, &tgl.month, &tgl.year);
									
									if(strlen(riwayat.tglPeriksa)!=10 || tgl.day>31 || tgl.day<1 || tgl.month>12 || tgl.month<1 || tgl.year<1 || riwayat.tglPeriksa[2]!='-' || riwayat.tglPeriksa[5]!='-') {
										printf("\n\t[!] Tanggal invalid/format tanggal harus DD-MM-YYYY!\n\n");
									}
									else {
										break;
									}
								}
								
								insertLastChild(*L, P->dataParent.idDokter, makeDataChild(riwayat.idRiwayat, "", "", riwayat.tglPeriksa, addrHewan->hewan.idHewan, 0, P->dataParent.idDokter));
								
								printf("\n\t[!] Berhasil Input Data Periksa Hewan");
								break;
							}
							else {
								printf("\n\t[!] Dokter Tidak Ditemukan\n\n");
							}
						}
					}
				}
				else {
					printf("\n\t[!] Tidak Ada Dokter Yang Aktif Saat Ini");
				}
				
				y=menu+5;
				break;
				
			case 7: //Hapus Daftar Periksa Hewan
				if(!isEmptyList(*H)) {
					system("cls");
					printf("\n\t--- Hapus Daftar Periksa Hewan ---\n");
					printf("\tMasukkan ID Hewan : "); fflush(stdin); scanf("%d", &hewan.idHewan);
					addrHewan = findNodeList(*H, hewan.idHewan);
					if(addrHewan != NULL) {
						printf("\n\t[!] Berhasil Hapus Daftar Periksa Hewan dengan Nama \"%s\" beserta Seluruh Riwayatnya", addrHewan->hewan.namaHewan);
						
						// Delete All Riwayat
						delAllRiwayatByHewan(L, addrHewan->hewan.idHewan);
						
						//RE ENABLE
						deleteAtList(H, addrHewan);
					}
					else {
						printf("\n\t[!] Not Found");
					}
				}
				else {
					printf("\n\t[!] Data Hewan Masih Kosong");
				}
				
				y=menu+5;
				break;
				
			case 8: //Tampil Data Seluruh Hewan
				if(!isEmptyList(*H)) {
					system("cls");
					printf("\n\t--- Tampil Data Hewan ---\n");
					printAllList(*H);
				}
				else {
					printf("\n\t[!] Data Hewan Masih Kosong");
				}
				
				y=menu+5;
				break;
				
			case 9: //Laporan Admin
				if(!isEmptyList(*H)) {
					system("cls");
					printf("\n\t--- Laporan Admin ---\n");
					printAllListWithRiwayat(*H, *L);
					
				}
				else {
					printf("\n\t[!] Data Hewan Masih Kosong, Tidak Ada Laporan Admin");
				}
				
				y=menu+7;
				break;
				
			case 0: //Logout
				printf("\n\t[!] Logout");
				return;
				
			default:
				printf("\n\t[!] Menu Tidak Ada");
				break;

		}
		
		getch();
		
	} while(menu!=0);
	
}


void menuDokter(Multilist *L, List *H, AddressParent P) {
	int menu;
	char key;
	
	DataParent dokter;
	DataChild riwayat;
	
	AddressParent tempAddrDokter;
	AddressChild c;
	
	do {
		//Inisialisasi Seluruh Temporary Variable
		menu = -1;
		dokter = makeDataParent(-1, "", "", "", "");
		riwayat = makeDataChild(-1, "", "", "", -1, -1, -1);
		
		system("color E0");
		
		system("cls");
		printf("\n\tSelamat datang,\033[32m drh. %s\033[30m!\n", P->dataParent.namaDokter);
		printf("\n\t\033[31m========== MENU DOKTER ==========\n\033[30m");
		printf("\n\t--- Menu Kelola Pasien ---");
		printf("\n\t[1] Periksa Hewan"); //jika sudah selesai diperiksa
		printf("\n\t[2] Laporan Tiap Dokter\n");
		printf("\n\t[Esc] Logout\n");
		printf("\n\t>>> "); fflush(stdin); key = getch(); printf("\n");
		
		if(key == 27) menu = 0;
		else if(key == 49) menu = 1;
		else if(key == 50) menu = 2;
		else menu = -1;
		
		switch(menu) {
			case 1:
				if(countAntrianPeriksaPerParent(P) != 0) {
					system("cls");
					printf("\n\t--- Daftar Seluruh Hewan yang Perlu Diperiksa ---\n");
					printActiveListWithRiwayatPerDokter(*H, P);
					printf("\n");
					
					printf("\tMasukkan ID Hewan yang Akan Diperiksa : "); fflush(stdin); scanf("%d", &riwayat.idHewanDiperiksa);
					c = findRiwayatByIdHewanAndStatusPeriksa(P, riwayat.idHewanDiperiksa, 0);
					
					if(c != NULL) {
						printf("\n\t--- Tambah Riwayat Periksa ---\n");
						
						while(1) {
							printf("\tDiagnosa Penyakit   : "); fflush(stdin); gets(riwayat.diagnosaPenyakit);
							if(strlen(riwayat.diagnosaPenyakit) == 0) printf("\n\t[!] Diagnosa Tidak Boleh Kosong\n\n");
							else break;
						}
						
						while(1) {
							printf("\tObat yang Diberikan : "); fflush(stdin); gets(riwayat.obat);
							if(strlen(riwayat.obat) == 0) printf("\n\t[!] Obat Tidak Boleh Kosong\n\n");
							else break;
						}
						
						// Pointer untuk mengubah data diagnosa penyakit dan obat yang diberikan
						// Status riwayat diubah menjadi sudah diperiksa
						
						strcpy(c->dataChild.diagnosaPenyakit, riwayat.diagnosaPenyakit);
						strcpy(c->dataChild.obat, riwayat.obat);
						c->dataChild.statusPeriksa = 1;
						
						printf("\n\t[!] Berhasil Menambahkan Data Diagnosa dan Obat Pada Riwayat Periksa");
						
					}
					else {
						printf("\n\t[!] Data Periksa Hewan Tidak Ditemukan");
					}
				}
				else {
					printf("\n\t[!] Tidak Ada Antrian Periksa Yang Aktif");
				}
				
				break;

			case 2:
				if(!isEmpty(*L)) {
					system("cls");
					printf("\n\tMasukkan ID Dokter : "); fflush(stdin); scanf("%d", &dokter.idDokter);
					tempAddrDokter = findParent(*L, dokter.idDokter);
					
					if(tempAddrDokter != NULL) {
						if(haveChild(tempAddrDokter)) {
							printf("\n\tMenampilkan Seluruh Riwayat Periksa dari\033[32m drh. %s\033[30m..\n", tempAddrDokter->dataParent.namaDokter);
							printAllListWithRiwayatPerDokter((*H), tempAddrDokter);
						}
						else {
							printf("\n\t[!]\033[32m drh. %s\033[30m Belum Memiliki Riwayat Periksa", tempAddrDokter->dataParent.namaDokter);
						}
					}
					else {
						printf("\n\t[!] Dokter Tidak Ada");
					}
				}
				else {
					printf("\n\t[!] Tidak Ada Dokter Yang Tersedia");
				}
				break;

			case 0:
				printf("\n\t[!] Logout");
				return;
				
			default:
				printf("\n\t[!] Menu Tidak Ada");
				break;
		}
		
		getch();
		
	} while(menu!=0);
}
