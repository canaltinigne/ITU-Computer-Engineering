#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <iomanip>
#include "diziislemleri.h"
using namespace std;

void Dizi::kayit() {
	
    teldefteri = fopen(dosyaadi, "r+");

	for (int i = 0; i < kayitsayisi; i++) {
		fwrite(k + i, sizeof(Tel_Kayit), 1, teldefteri);
	}
	
    fclose(teldefteri);
}


void Dizi::ekle(Tel_Kayit *ykptr) {
    
    char * record1 = ykptr->ad;
    
    for (int i = 0; i < kayitsayisi; i++) {
        
        if (strcmp(record1,(k+i)->ad) < 0) {
            break;
        }
    }
    
    for (int sira = kayitsayisi; sira > i; sira--) {
        
        strcpy((k + sira)->ad,(k + sira - 1)->ad);
        strcpy((k + sira)->telno, (k + sira - 1)->telno);
    }
    
    strcpy((k+i)->ad, ykptr->ad);
    strcpy((k+i)->telno, ykptr->telno);
    
    kayitsayisi++;
}


void Dizi::olustur() {
	
    kayitsayisi = 0;
	
    dosyaadi = "text.txt";
	
    teldefteri = fopen(dosyaadi, "r+");

	if (!teldefteri) {
		teldefteri = fopen(dosyaadi, "w+");
		if (!teldefteri) {
			cout << "dosya acilamadi" << endl;
			exit(1);
		}
	}
	int i = 0;
	
    /*for ( ;!feof(teldefteri); i++) {
		fread( k+i , sizeof(Tel_Kayit), 1, teldefteri);

		if (feof(teldefteri)) break;
	}*/
    
    while (!feof(teldefteri)) {
        
        fread( k+i , sizeof(Tel_Kayit), 1, teldefteri);
        
        if (feof(teldefteri)) break;
        
        i++;
    }
	
	kayitsayisi += i;


}

int Dizi::ara(char aranacak[]) {
	int sayac = 0;
	bool tumu = false;
	int bulunan, flag = 0;
	if (strcmp(aranacak, "*") == 0)
		tumu = true;
	for (int i = 0;i<kayitsayisi;i++) {
		if (tumu || strcmp(k[i].ad, aranacak) == 0)
		{
			cout << i + 1 << ". " << k[i].ad << endl;
			bulunan = i;
			flag = 1;
		}
	}
	return flag;
}
void Dizi::guncelle(int kayitno, Tel_Kayit *ykptr) {
	strcpy(k[kayitno - 1].ad, ykptr->ad);
	strcpy(k[kayitno - 1].telno, ykptr->telno);
}
void Dizi::sil(int kayitno) {
	
	
}

void Dizi::listele() {
	for (int i = 0;i<kayitsayisi;i++)
		cout << i + 1 << ". " << k[i].ad << " " << k[i].telno << endl;
}