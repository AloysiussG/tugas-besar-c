#include "header.h"

//--------------------------------------------------------LINKED LIST (HEWAN)--------------------------------------------------------
void createEmptyList(List *L) {
	(*L).first = NULL;
}

bool isEmptyList(List L) {
	return (L.first == NULL);
}

bool isOneElementList(List L) {
	return (!isEmptyList(L) && L.first->next == NULL);
}

AddressHewan alokasiList(DataHewan D) {
	AddressHewan P;
	
	P = (Node*) malloc(sizeof(Node));
	P->hewan = D;
	P->next = NULL;
	
	return P;
}

void insertFirstList(List *L, AddressHewan newNode) {
	newNode->next = (*L).first;
	(*L).first = newNode;
}

void insertLastList(List *L, AddressHewan newNode) {
	AddressHewan P;
	
	if(isEmptyList(*L)) {
		insertFirstList(L, newNode);
	}
	else {
		for(P = (*L).first; P->next != NULL; P = P->next);
		P->next = newNode;
	}
}

void deleteFirstList(List *L) {
	if(!isEmptyList(*L)) {
		AddressHewan del = (*L).first;
		(*L).first = (*L).first->next;
		free(del);
	}
}

void deleteAtList(List *L, AddressHewan del) {
	AddressHewan P;
	
	if(!isEmptyList(*L)) {
		if((*L).first == del) {
			deleteFirstList(L);
		}
		else {
			P = (*L).first;
			while(P->next != del) {
				P = P->next;
			}
			P->next = del->next;
			free(del);
		}
	}
}

void printDataList(AddressHewan addrHewan) {
	if(addrHewan != NULL) {
		printf("\n\t--- DATA HEWAN ---");
		printf("\n\tID Hewan      : %d", addrHewan->hewan.idHewan);
		printf("\n\tNama Hewan    : %s", addrHewan->hewan.namaHewan);
		printf("\n\tTgl. Lahir    : %s", addrHewan->hewan.tglLahirHewan);
		printf("\n\tJenis Hewan   : %s", addrHewan->hewan.jenisHewan);
		printf("\n\tJenis Kelamin : %s\n", addrHewan->hewan.jenisKelaminHewan);
	}
}

void printAllList(List L) {
	AddressHewan P;
	int noUrut=1;
	
	for(P = L.first; P != NULL; P = P->next) {
		printDataList(P);
		noUrut++;
	}
}

AddressHewan findNodeList(List L, int idHewan) {
	AddressHewan P;
	
	for(P = L.first; P != NULL && P->hewan.idHewan != idHewan; P = P->next);
	return P;
}

void sortByJenisHewanList(List *L) {
	AddressHewan P, Anchor;
	DataHewan temp;

	for(Anchor = (*L).first; Anchor->next != NULL; Anchor = Anchor->next) {
		for(P = Anchor->next; P != NULL; P = P->next) {
			if(strcmp(Anchor->hewan.jenisHewan, P->hewan.jenisHewan) > 0) {
				//Swap Data
				temp = Anchor->hewan;
				Anchor->hewan = P->hewan;
				P->hewan = temp;
			}
		}
	}
}

//Print Seluruh Hewan Dan Seluruh Riwayatnya, Dari Seluruh Dokter
void printAllListWithRiwayat(List L, Multilist M) {
	AddressParent dokter;
	AddressChild riwayat;
	AddressHewan hewan;
	
	for(hewan = L.first; hewan != NULL; hewan = hewan->next) {
		printDataList(hewan);
		
		dokter = M.firstParent;
		while(dokter != NULL) {
			riwayat = dokter->firstChild;
			
			while(riwayat != NULL) {
				if(riwayat->dataChild.idHewanDiperiksa == hewan->hewan.idHewan) {
					printf("\n\t\t=== Data Riwayat Periksa ===");
					printChild(riwayat);
					printf("\n");
				}
				riwayat = riwayat->next;
			}
			
			dokter = dokter->next;
		}
	}
}

//Print Hewan (Yg Diperiksa Seorang Dokter) Beserta Seluruh Riwayat Yang Statusnya "Belum Diperiksa"
void printActiveListWithRiwayatPerDokter(List L, AddressParent P) {
	AddressChild C;
	AddressHewan addrHewan = L.first;
	
	while(addrHewan != NULL) {
		if(findRiwayatByIdHewanAndStatusPeriksa(P, addrHewan->hewan.idHewan, 0)) {
			printDataList(addrHewan);
			
			C = P->firstChild;
			while(C != NULL) {
				if(C->dataChild.idHewanDiperiksa == addrHewan->hewan.idHewan && C->dataChild.statusPeriksa == 0) {
					printf("\n\t\t=== Data Riwayat Periksa ===");
					printChild(C);
					printf("\n");
				}
				C = C->next;
			}
		}
		
		addrHewan = addrHewan->next;
	}
}	

//Print Hewan (Yg Diperiksa Seorang Dokter) Beserta Seluruh Riwayatnya, Baik Yang "Belum Diperiksa" Maupun "Sudah Diperiksa"
void printAllListWithRiwayatPerDokter(List L, AddressParent P) {
	AddressChild C;
	AddressHewan addrHewan = L.first;
	
	while(addrHewan != NULL) {
		if(findRiwayatByIdHewan(P, addrHewan->hewan.idHewan)) {
			printDataList(addrHewan);
			
			C = P->firstChild;
			while(C != NULL) {
				if(C->dataChild.idHewanDiperiksa == addrHewan->hewan.idHewan) {
					printf("\n\t\t=== Data Riwayat Periksa ===");
					printChild(C);
					printf("\n");
				}
				C = C->next;
			}
		}
		
		addrHewan = addrHewan->next;
	}	
}
