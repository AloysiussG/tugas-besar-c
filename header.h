#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <dos.h>
#include <malloc.h>

typedef char string[100];

typedef struct {
	int day;
	int month;
	int year;
} Tanggal;


//Address Parent (Dokter) & Address Child (Riwayat Periksa)
typedef struct NodeParent* AddressParent;
typedef struct NodeChild* AddressChild;

//Data Dokter
typedef struct DataParent {
	int idDokter;
	string namaDokter;
	string tanggalGabung;
	
	//dataLogin
	string username;
	string password;
} DataParent;

//Data Riwayat Periksa
typedef struct DataChild {
	int idRiwayat;
	string diagnosaPenyakit;
	string obat;
	string tglPeriksa;
	int statusPeriksa;
	
	//foreignKey
	int idHewanDiperiksa;
	int idDokterPemeriksa;
} DataChild;

//Node Parent == Dokter
typedef struct NodeParent {
	DataParent dataParent;
	AddressParent next;
	AddressChild firstChild;
} NodeParent;

//Node Child == Riwayat Periksa
typedef struct NodeChild {
	DataChild dataChild;
	AddressChild next;
} NodeChild;

//Multi List
typedef struct {
	AddressParent firstParent;
} Multilist;


//Address List (Hewan)
typedef struct Node* AddressHewan;

//Data Hewan
typedef struct {
	int idHewan;
	string namaHewan;
	string tglLahirHewan;
	string jenisHewan;
	string jenisKelaminHewan;
} DataHewan;

//Node == Hewan
typedef struct Node {
	DataHewan hewan;
	AddressHewan next;
} Node;

//List (Non-Multi List)
typedef struct {
	AddressHewan first;
} List;


//--------------------------------------------------------MENU ITEMS---------------------------------------------------
void menuAdmin(Multilist *L, List *H);
void menuDokter(Multilist *L, List *H, AddressParent P);


//--------------------------------------------------------GENERAL------------------------------------------------------
DataParent makeDataParent(int idDokter, string namaDokter, string tanggalGabung, string username, string password);
DataChild makeDataChild(int idRiwayat, string diagnosaPenyakit, string obat, string tglPeriksa, int idHewanDiperiksa, int statusPeriksa, int idDokterPemeriksa);
DataHewan makeDataList(int idHewan, string jenisHewan, string jenisKelaminHewan, string namaHewan, string tglLahirHewan);
void gotoxy(int x, int y);
void logo(int x, int y);
void loadingScreen(int widthCol, int heightRow);


//--------------------------------------------------------LINKED LIST (HEWAN)------------------------------------------
void createEmptyList(List *L);
bool isEmptyList(List L);
bool isOneElementList(List L);
AddressHewan alokasiList(DataHewan D);
void insertFirstList(List *L, AddressHewan newNode);
void insertLastList(List *L, AddressHewan newNode);
void deleteFirstList(List *L);
void deleteAtList(List *L, AddressHewan del);
void printDataList(AddressHewan addrHewan);
void printAllList(List L);
AddressHewan findNodeList(List L, int idHewan);
void sortByJenisHewanList(List *L);
void printAllListWithRiwayat(List L, Multilist M);
void printActiveListWithRiwayatPerDokter(List L, AddressParent P);	
void printAllListWithRiwayatPerDokter(List L, AddressParent P);


//--------------------------------------------------------PARENT-------------------------------------------------------
void createEmpty(Multilist *L);
bool isEmpty(Multilist L);
bool haveChild(AddressParent ap);
AddressParent alokasiParent(DataParent data);
AddressParent findParent(Multilist L, int cariId);
AddressParent findParentByUsername(Multilist L, string username);
AddressParent findParentByLoginInfo(Multilist L, string username, string password);
AddressParent findParentByName(Multilist L, string namaDokter);
void insertFirstParent(Multilist *L, DataParent data);
void insertLastParent(Multilist *L, DataParent data);
void deleteFirstParent(Multilist *L);
void deleteAtParent(Multilist *L, int idParent);
void deleteAllChild(AddressParent parent);
void printParent(AddressParent parent);
void printAllParent(Multilist L);
void printAllParentForPasien(Multilist L);
void printAll(Multilist L);


//--------------------------------------------------------CHILD--------------------------------------------------------
AddressChild alokasiChild(DataChild data);
void insertFirstChild(Multilist L, int idParent, DataChild data);
void insertLastChild(Multilist L, int idParent, DataChild data);
void printChild(AddressChild child);
void printAllChild(AddressParent parent);
int countAntrianPeriksaPerParent(AddressParent parent);
void deleteAtChild(Multilist L, AddressParent parent, AddressChild c);
void delAllRiwayatByHewan(Multilist *L, int idHewan);
AddressChild findRiwayatByIdRiwayatInAllDokter(Multilist L, int idRiwayat);
AddressChild findRiwayatByIdHewan(AddressParent parent, int idHewan);
AddressChild findRiwayatByIdHewanAndStatusPeriksa(AddressParent parent, int idHewan, int statusPeriksa);
