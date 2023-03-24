#include "header.h"

//--------------------------------------------------------MULTI LIST CHILD (RIWAYAT)--------------------------------------------------------
AddressChild alokasiChild(DataChild data) {
	AddressChild ac;
	ac = (AddressChild) malloc(sizeof(NodeChild));
	
	ac->next = NULL;
	ac->dataChild = data;
	
	return ac;
}

void insertFirstChild(Multilist L, int idParent, DataChild data) {
	AddressParent parent = findParent(L, idParent);
	
	if(parent != NULL) {
		AddressChild dataBaru = alokasiChild(data);
		dataBaru->next = parent->firstChild;
		
		parent->firstChild = dataBaru;
	}
}

void insertLastChild(Multilist L, int idParent, DataChild data) {
	AddressParent parent = findParent(L, idParent);
	
	if(parent != NULL) {
		if(!haveChild(parent)) {
			insertFirstChild(L, idParent, data);
		}
		else {
			AddressChild temp = parent->firstChild;
			AddressChild dataBaru = alokasiChild(data);
			
			while(temp->next != NULL) {
				temp = temp->next;
			}
			
			temp->next = dataBaru;
		}
	}
}

void printChild(AddressChild child) {
	printf("\n\t\tID Riwayat          : %d", child->dataChild.idRiwayat);
	printf("\n\t\tTgl. Periksa        : %s", child->dataChild.tglPeriksa);
	printf("\n\t\tID Hewan Diperiksa  : %d", child->dataChild.idHewanDiperiksa);
	printf("\n\t\tID Dokter Pemeriksa : %d", child->dataChild.idDokterPemeriksa);
	
	if(child->dataChild.statusPeriksa == 0) {
	printf("\n\t\t[Belum Periksa!]");
	}
	else {
		printf("\n\t\t[Sudah Periksa!]");
		printf("\n\t\t\t> Diagnosa  : %s", child->dataChild.diagnosaPenyakit);
		printf("\n\t\t\t> Obat      : %s", child->dataChild.obat);
	}
	
}

void printAllChild(AddressParent parent) {
	AddressChild temp = parent->firstChild;
	
	printf("\n\t\t=== Data Riwayat Periksa ===");
	while(temp != NULL) {
		printChild(temp);
		printf("\n");
		temp = temp->next;
	}
}

int countAntrianPeriksaPerParent(AddressParent parent) {
	AddressChild c = parent->firstChild;
	int count=0;
	
	while(c != NULL) {
		if(c->dataChild.statusPeriksa == 0) {
			count++;
		}
		c = c->next;
	}
	return count;
}

void deleteAtChild(Multilist L, AddressParent parent, AddressChild c) {
	AddressChild before = parent->firstChild;
	
	if(c == parent->firstChild) {
		parent->firstChild = c->next;
		free(c);
	}
	else {
		before = parent->firstChild;
		
		while(before->next != c) {
			before = before->next;
		}
		before->next = c->next;
		free(c);
	}
}

void delAllRiwayatByHewan(Multilist *L, int idHewan) {
	AddressParent P = (*L).firstParent;
	AddressChild C;
	
	while(P != NULL) {
		C = P->firstChild;
		while(C != NULL) {
			if(C->dataChild.idHewanDiperiksa == idHewan) {
				deleteAtChild(*L, P, C);
			}
			C = C->next;
		}
		P = P->next;
	}
}

AddressChild findRiwayatByIdRiwayatInAllDokter(Multilist L, int idRiwayat) {
	AddressParent P = L.firstParent;
	AddressChild C;
	
	while(P != NULL) {
		C = P->firstChild;
		
		while(C != NULL) {
			if(C->dataChild.idRiwayat == idRiwayat) {
				return C;
			}
			C = C->next;
		}
		P = P->next;
	}
	return NULL;
}

AddressChild findRiwayatByIdHewan(AddressParent parent, int idHewan) {
	AddressChild child = parent->firstChild;
	
	while(child != NULL) {
		if(child->dataChild.idHewanDiperiksa == idHewan) {
			return child;
		}
		child = child->next;
	}
	return NULL;
}

AddressChild findRiwayatByIdHewanAndStatusPeriksa(AddressParent parent, int idHewan, int statusPeriksa) {
	AddressChild child = parent->firstChild;
	
	while(child != NULL) {
		if(child->dataChild.idHewanDiperiksa == idHewan && child->dataChild.statusPeriksa == statusPeriksa) {
			return child;
		}
		child = child->next;
	}
	return NULL;
}

