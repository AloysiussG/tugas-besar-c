#include "header.h"

//--------------------------------------------------------MULTI LIST PARENT (DOKTER)--------------------------------------------------------
void createEmpty(Multilist *L) {
	L->firstParent = NULL;
}

bool isEmpty(Multilist L) {
	return L.firstParent == NULL;
}

bool haveChild(AddressParent ap) {
	return (ap->firstChild != NULL);
}

AddressParent alokasiParent(DataParent data) {
	AddressParent ap;
	
	ap = (AddressParent) malloc(sizeof(NodeParent));
	ap->next = NULL;
	ap->firstChild = NULL;
	ap->dataParent = data;
	
	return ap;
}

AddressParent findParent(Multilist L, int cariId) {
	AddressParent parentBantu = NULL;
	parentBantu = L.firstParent;

	while(parentBantu != NULL) {
		if(parentBantu->dataParent.idDokter == cariId) {
			return parentBantu;
		}
		parentBantu = parentBantu->next;
	}
	
	return NULL;
}

AddressParent findParentByUsername(Multilist L, string username) {
	AddressParent parentBantu = NULL;
	parentBantu = L.firstParent;

	while(parentBantu != NULL) {
		if(strcmp(parentBantu->dataParent.username, username) == 0) {
			return parentBantu;
		}
		parentBantu = parentBantu->next;
	}
	
	return NULL;
}

AddressParent findParentByLoginInfo(Multilist L, string username, string password) {
	AddressParent parentBantu = NULL;
	parentBantu = L.firstParent;

	while(parentBantu != NULL) {
		if(strcmp(parentBantu->dataParent.username, username) == 0 && strcmp(parentBantu->dataParent.password, password) == 0) {
			return parentBantu;
		}
		parentBantu = parentBantu->next;
	}
	
	return NULL;
}

AddressParent findParentByName(Multilist L, string namaDokter) {
	AddressParent parentBantu = NULL;
	parentBantu = L.firstParent;

	while(parentBantu != NULL) {
		if(strcmpi(parentBantu->dataParent.namaDokter, namaDokter) == 0) {
			return parentBantu;
		}
		parentBantu = parentBantu->next;
	}
	
	return NULL;
}

void insertFirstParent(Multilist *L, DataParent data) {
	AddressParent dataParent = alokasiParent(data);
	
	dataParent->next = L->firstParent;
	L->firstParent = dataParent;
}

void insertLastParent(Multilist *L, DataParent data) {
	AddressParent dataParent = alokasiParent(data);
	
	if(isEmpty(*L)) {
		insertFirstParent(L, data);
	}
	else {
		AddressParent temp = L->firstParent;
		
		while(temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = dataParent;
	}
}

void deleteFirstParent(Multilist *L) {
	AddressParent temp = L->firstParent;
	
	if(!isEmpty(*L)) {
		deleteAllChild(temp);
		
		L->firstParent = L->firstParent->next;
		free(temp);
	}
}

void deleteAtParent(Multilist *L, int idParent) {
	AddressParent temp = L->firstParent;
	AddressParent hapus;
	
	if(!isEmpty(*L)) {
		if(temp->dataParent.idDokter == idParent) {
			deleteFirstParent(L);
		}
		else {
			while(temp->next != NULL) {
				if(temp->next->dataParent.idDokter == idParent) {
					hapus = temp->next;
					temp->next = temp->next->next;
					
					deleteAllChild(hapus);
					free(hapus);
					break;
				}
				temp = temp->next;
			}
		}
	}
}

void deleteAllChild(AddressParent parent) {
	AddressChild temp;
	
	while(haveChild(parent)) {
		temp = parent->firstChild;
		parent->firstChild = parent->firstChild->next;
		
		free(temp);
	}
}

void printParent(AddressParent parent) {
	printf("\n\t=== Data Dokter ===");
	printf("\n\tID Dokter      : %d", parent->dataParent.idDokter);
	printf("\n\tNama Dokter    : %s", parent->dataParent.namaDokter);
	printf("\n\tTanggal Gabung : %s\n", parent->dataParent.tanggalGabung);
	
	printf("\n\t\t--- Data Login ---");
	printf("\n\t\tUsername       : %s", parent->dataParent.username);
	printf("\n\t\tPassword       : %s", parent->dataParent.password);
}

void printAllParent(Multilist L) {
	AddressParent temp = L.firstParent;
	
	while(temp != NULL) {
		printParent(temp);
		
		printf("\n");
		temp = temp->next;
	}
}

//Print All Parent Horizontal (For Pasien Needs)
void printAllParentForPasien(Multilist L) {
	AddressParent temp = L.firstParent;
	int column=1;
	
	while(temp != NULL) {
		printf("\t[drh. %s]", temp->dataParent.namaDokter);
		if(column == 3) {
			printf("\n"); 
			column=1;
		}
		temp = temp->next;
	}
}

//Print All Parents + All Their Children
void printAll(Multilist L) {
	AddressParent temp = L.firstParent;
	
	while(temp != NULL) {
		printParent(temp);
		
		if(haveChild(temp) == 1) {
			printAllChild(temp);
		}
		printf("\n");
		
		temp = temp->next;
	}
}
