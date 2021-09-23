#pragma once
#ifndef HEADER_H
#define HEADER_H


typedef struct datum {
	unsigned short dan;
	unsigned short mjesec;
	unsigned short godina;
}DATUM;

typedef struct datumDolaska {
	unsigned short danDolaska;
	unsigned short mjesecDolaska;
	unsigned short godinaDolaska;
	char vrijeme[20];
}DOLAZAK;

typedef struct anamneza {

	char prethodneBolesti[100];
	char simptomi[500];
	char temperatura[10];
	char alergija[50];
	char navike[50];
	char lijekovi[50];

}ANAMNEZA;

typedef struct otpust {

	unsigned short danOtpusta;
	unsigned short mjesecOtpusta;
	unsigned short godinaOtpusta;
	char vrijemeOtpusta[20];

}OTPUST;

typedef struct adresa {

	char mjestoStanovanja[30];
	char adresaStanovanja[50];
}ADRESA;

typedef struct pacijent {

	char ime[30];
	char prezime[40];
	int OIB;
	char brojMob[15];
	ADRESA prebivaliste;
	DATUM dob;
	ANAMNEZA anamneza;
	char dolazak[200];
	DOLAZAK datum;
	char odjel[40];
	int brojSobe;
	OTPUST datumOtpusta;

}PACIJENT;

void menu();
void red();
void stvaranje();
void unos();
void counter();
void pretraga();
void sortiranje(PACIJENT*, const int);
void ispis(void);
void izlaz();
void zamjena(PACIJENT*, PACIJENT*);
void brisanje();

#endif //HEADER_H
