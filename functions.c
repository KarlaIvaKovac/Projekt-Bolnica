#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "header.h"

void red() {
	printf("\033[1;31m");
}

void menu() {
	int n;
	do {
		printf("***************************************\n");		
		printf("|          ~ Izbornik ~               |\n");	
		printf("***************************************\n");
		printf("|1 - Unos novog pacijenta             |\n");
		printf("---------------------------------------\n");
		printf(" 2 - Citanje datoteke s pacijentima    \n");
		printf("---------------------------------------\n");
		printf("|3 - Pretraga pacijenta               |\n");
		printf("---------------------------------------\n");
		printf(" 4 - Brisanje				           \n");
		printf("---------------------------------------\n");
		printf("|5 - Izlaz                            |\n");
		printf("***************************************\n");
		printf("\nKoju radnju zelite?\n");

		do {
			scanf("%d", &n);
		} while (n > 5 || n < 1);


		switch (n) {

		case 1:

			system("cls");
			unos();
			menu();

			break;


		case 2:

			system("cls");
			ispis();
			menu();

			break;


		case 3:

			system("cls");
			pretraga();
			menu();

			break;


		case 4:

			system("cls");
			brisanje();
			menu();
			break;


		case 5:

			izlaz();
			break;


		default:

			printf("Krivo uneseni broj!\n");
			menu();

		}

	} while (1);
	return;
}


void stvaranje(void) {      //prvo provjera postoji li datoteka, ako ne kreira se

	int podatak = 0;

	FILE* fp = NULL;

	fp = fopen("Popis Pacijenata.bin", "rb+");//otvaranje binarne datoteke za citanje i pisanje

	if (fp == NULL)
	{
		perror("Datoteka ne postoji");

		FILE* fp2 = fopen("Popis Pacijenata.bin", "wb+"); //kreira binarnu datoteku za citanje i pisanje

		if (fp2 == NULL) {

			printf("Datoteku nije moguce napraviti.\n");
			exit(EXIT_FAILURE);

		}
		else {

			fwrite(&podatak, sizeof(int), 1, fp2);
			fclose(fp2);
			printf("Datoteka uspjesno kreirana.\n");
		}

	}
	return;
}


void unos() {

	PACIJENT* noviPacijent = NULL;

	noviPacijent = (PACIJENT*)calloc(1, sizeof(PACIJENT));

	if (noviPacijent == NULL) {

		perror("Error");
		exit(EXIT_FAILURE);
	}

	char broj[15] = { '\0' };

	FILE* fp = NULL;

	fp = fopen("Popis Pacijenata.bin", "ab+");

	if (fp == NULL) {

		perror("Greska pri dodavnju novog pacijenta");
		exit(EXIT_FAILURE);
	}
	else {
		printf("Ime pacijenta:\n");
		scanf(" %29[^\n]%*c", noviPacijent->ime);

		printf("Prezime pacijenta:\n");
		scanf(" %39[^\n]%*c", noviPacijent->prezime);

		printf("OIB:\n");
		scanf("%d", &noviPacijent->OIB);

		printf("Broj mobitela +385:\n");
		scanf("%14s", broj);
		strcpy(noviPacijent->brojMob, "+385");
		strcat(noviPacijent->brojMob, broj);

		printf("Adresa:\n");
		scanf(" %49[^\n]%*c", noviPacijent->prebivaliste.adresaStanovanja);
		printf("Mjesto stanovanja:\n");
		scanf(" %29[^\n]%*c", noviPacijent->prebivaliste.mjestoStanovanja);

		printf("Datum rodenja:\n");
		printf("Dan:\n");
		scanf("%hu", &noviPacijent->dob.dan);
		printf("Mjesec:\n");
		scanf("%hu", &noviPacijent->dob.mjesec);
		printf("Godina:\n");
		scanf("%hu", &noviPacijent->dob.godina);

		printf("Anamneza:\n");
		printf("Prethodne bolesti:\n");
		scanf(" %99[^\n]%*c", noviPacijent->anamneza.prethodneBolesti);
		printf("Simptomi:\n");
		scanf(" %499[^\n]%*c", noviPacijent->anamneza.simptomi);
		printf("Temperatura:\n");
		scanf(" %9[^\n]%*c", noviPacijent->anamneza.temperatura);
		printf("Alergije:\n");
		scanf(" %49[^\n]%*c", noviPacijent->anamneza.alergija);
		printf("Lose navike:\n");
		scanf(" %49[^\n]%*c", noviPacijent->anamneza.navike);
		printf("Lijekovi:\n");
		scanf(" %49[^\n]%*c", noviPacijent->anamneza.lijekovi);

		printf("Dolazak zbog:\n");
		scanf(" %199[^\n]%*c", noviPacijent->dolazak);
		printf("Datum dolaska:\n");
		printf("Dan:\n");
		scanf("%hu", &noviPacijent->datum.danDolaska);
		printf("Mjesec:\n");
		scanf("%hu", &noviPacijent->datum.mjesecDolaska);
		printf("Godina:\n");
		scanf("%hu", &noviPacijent->datum.godinaDolaska);
		printf("Vrijeme:\n");
		scanf("%19s", noviPacijent->datum.vrijeme);

		printf("Odjel:\n");
		scanf(" %39[^\n]%*c", noviPacijent->odjel);

		printf("Broj sobe:\n");
		scanf("%d", &noviPacijent->brojSobe);

		printf("Datum otpusta:\n");
		printf("Dan:\n");
		scanf("%hu", &noviPacijent->datumOtpusta.danOtpusta);
		printf("Mjesec:\n");
		scanf("%hu", &noviPacijent->datumOtpusta.mjesecOtpusta);
		printf("Godina:\n");
		scanf("%hu", &noviPacijent->datumOtpusta.godinaOtpusta);

		printf("Vrijeme otpusta:\n");
		scanf(" %19[^\n]%*c", noviPacijent->datumOtpusta.vrijemeOtpusta);

		fwrite(noviPacijent, sizeof(PACIJENT), 1, fp);
		counter();
		fclose(fp);
	}
	return;
}


void counter(void) {

	int brojPacijenata = 0;

	FILE* brPacijenata = NULL;

	brPacijenata = fopen("Popis Pacijenata.bin", "rb+");

	if (brPacijenata == NULL) {

		printf("Nemoguce otvoriti datoteku.\n");
		exit(EXIT_FAILURE);
	}
	else {
		fread(&brojPacijenata, sizeof(int), 1, brPacijenata);
		if (brojPacijenata == 0) {
			brojPacijenata = 1;
			fseek(brPacijenata, 0, SEEK_SET); //vracanje na pocetak reda
			fwrite(&brojPacijenata, sizeof(int), 1, brPacijenata);
			//funkcija zapisuje info u datoteku pomocu adrese informacije, velicina tog elementa, broj koliko se puta mora zapisati i mjesto gdje ce se zapisati														   
		}
		else {
			brojPacijenata++;
			fseek(brPacijenata, 0, SEEK_SET); //da se vrati na pocetak nakon read-a
			fwrite(&brojPacijenata, sizeof(int), 1, brPacijenata);
		}
		fclose(brPacijenata);
	}
	return;
}


void pretraga(void) {

	FILE* readData = NULL;

	readData = fopen("Popis Pacijenata.bin", "rb");//otvaranje binarne datoteke za citanje

	if (readData == NULL) {

		perror("Pogreska pri pretrazivanju pacijenata");

		exit(EXIT_FAILURE);
	}
	else {

		PACIJENT* sviPacijenti = NULL;
		int brPacijenata = 0;

		fread(&brPacijenata, sizeof(int), 1, readData);
		if (brPacijenata == 0) {

			perror("Datoteka je prazna");
			fclose(readData);

			exit(EXIT_FAILURE);
		}
		else {

			sviPacijenti = (PACIJENT*)calloc(brPacijenata, sizeof(PACIJENT));

			if (sviPacijenti == NULL) {

				perror("Greska pri citanju datoteke s pacijentima");
				exit(EXIT_FAILURE);
			}
			else {
				fread(sviPacijenti, sizeof(PACIJENT), brPacijenata, readData);
				fclose(readData);

				sortiranje(sviPacijenti, brPacijenata);

				int i;
				int trazeniOIB = { 0 };

				printf("Unesite OIB trazenog pacijenta:\n");
				fflush(stdin); //brise standardni ulaz u slucaju da je ostalo nesto od inputa
				scanf("%d", &trazeniOIB);

				int found = 0;
				int index = -1;

				for (i = 0; i < brPacijenata; i++) {

					if ((sviPacijenti + i)->OIB == trazeniOIB) {

						found = 1;
						index = i;
					}
				}
				if (found) {

					printf("\nTRAZENI PACIJENT:\n");
					printf("Ime: %s\n", (sviPacijenti + index)->ime);
					printf("Prezime: %s\n", (sviPacijenti + index)->prezime);
					printf("OIB: %d\n", (sviPacijenti + index)->OIB);
					printf("Broj Mobitela: %s\n", (sviPacijenti + index)->brojMob);
					printf("Adresa: %s, %s\n", (sviPacijenti + index)->prebivaliste.adresaStanovanja, (sviPacijenti + index)->prebivaliste.mjestoStanovanja);
					printf("Datum rodenja:\n");
					printf("Dan: %hu.\n", (sviPacijenti + index)->dob.dan);
					printf("Mjesec: %hu.\n", (sviPacijenti + index)->dob.mjesec);
					printf("Godina: %hu.\n", (sviPacijenti + index)->dob.godina);

					printf("\nAnamneza:\n");
					printf("Prethodne bolesti:\n%s\n", (sviPacijenti + index)->anamneza.prethodneBolesti);
					printf("Simptomi:\n%s\n", (sviPacijenti + index)->anamneza.simptomi);
					printf("Temperatura: %s\n", (sviPacijenti + index)->anamneza.temperatura);
					printf("Alergije: %s\n", (sviPacijenti + index)->anamneza.alergija);
					printf("Lose navike: %s\n", (sviPacijenti + index)->anamneza.navike);
					printf("Lijekovi: %s\n", (sviPacijenti + index)->anamneza.lijekovi);

					printf("\nDolazak zbog: %s\n", (sviPacijenti + index)->dolazak);
					printf("Datum dolaska:\n");
					printf("Dan: %hu\n", (sviPacijenti + index)->datum.danDolaska);
					printf("Mjesec: %hu\n", (sviPacijenti + index)->datum.mjesecDolaska);
					printf("Godina: %hu\n", (sviPacijenti + index)->datum.godinaDolaska);
					printf("Vrijeme: %s\n", (sviPacijenti + index)->datum.vrijeme);
					printf("Odjel: %s\n", (sviPacijenti + index)->odjel);
					printf("\nDatum otpusta:\n");
					printf("Dan: %hu.\n", (sviPacijenti + index)->datumOtpusta.danOtpusta);
					printf("Mjesec:%hu.\n", (sviPacijenti + index)->datumOtpusta.mjesecOtpusta);
					printf("Godina: %hu.\n", (sviPacijenti + index)->datumOtpusta.godinaOtpusta);
					printf("Vrijeme: %s\n\n", (sviPacijenti + index)->datumOtpusta.vrijemeOtpusta);

				}
				else {
					printf("Pacijent ne postoji.\n");
				}
				free(sviPacijenti);
			}
		}

	}
	return;
}

void zamjena(PACIJENT* veci, PACIJENT* manji) {

	PACIJENT temp = *manji;
	*manji = *veci;
	*veci = temp;
}

void sortiranje(PACIJENT* sviPacijenti, const int brPacijenata) {

	int min = 0;

	for (int i = 0; i < brPacijenata - 1; i++)
	{
		min = i;

		for (int j = i + 1; j < brPacijenata; j++)
		{
			if (strcmp((sviPacijenti + j)->ime, (sviPacijenti + min)->ime) < 0) {//usporeduje vrijednosti, ako su jednake daje nulu
				min = j;
			}
			if (min != i) {

				zamjena((sviPacijenti + i), (sviPacijenti + min));
			}
		}
	}
}

void ispis(void) {

	PACIJENT* sviPacijenti = NULL;

	FILE* pacijenti = NULL;

	pacijenti = fopen("Popis Pacijenata.bin", "rb");

	if (pacijenti == NULL) {

		printf("Datoteka se ne moze procitati.\n");
		exit(EXIT_FAILURE);
	}

	else {

		int x = 0;
		fread(&x, sizeof(int), 1, pacijenti);//otvaranje i citanje ukupnog broja struktura
		sviPacijenti = (PACIJENT*)calloc(x, sizeof(PACIJENT));   //zauzimanje mjesta za onoliko struktura koliko ih je u datoteci

		if (sviPacijenti == NULL) {

			perror("Greska pri citanju datoteke s pacijentima.\n");
			exit(EXIT_FAILURE);
		}

		fread(sviPacijenti, sizeof(PACIJENT), x, pacijenti); //	funkcija koja cita sve strukture iz datoteke														 


		for (int i = 0; i < x; i++) {


			printf("\nPACIJENT %d.\n", i + 1);
			printf("Ime: %s\n", (sviPacijenti + i)->ime);
			printf("Prezime: %s\n", (sviPacijenti + i)->prezime);
			printf("OIB: %d\n", (sviPacijenti + i)->OIB);
			printf("Broj Mobitela: %s\n", (sviPacijenti + i)->brojMob);
			printf("Adresa: %s, %s\n", (sviPacijenti + i)->prebivaliste.adresaStanovanja, (sviPacijenti + i)->prebivaliste.mjestoStanovanja);
			printf("Datum rodenja:\n");
			printf("Dan: %hu.\n", (sviPacijenti + i)->dob.dan);
			printf("Mjesec: %hu.\n", (sviPacijenti + i)->dob.mjesec);
			printf("Godina: %hu.\n", (sviPacijenti + i)->dob.godina);

			printf("\nAnamneza:\n");
			printf("Prethodne bolesti:\n%s\n", (sviPacijenti + i)->anamneza.prethodneBolesti);
			printf("Simptomi:%s\n", (sviPacijenti + i)->anamneza.simptomi);
			printf("Temperatura: %s\n", (sviPacijenti + i)->anamneza.temperatura);
			printf("Alergije: %s\n", (sviPacijenti + i)->anamneza.alergija);
			printf("Lose navike: %s\n", (sviPacijenti + i)->anamneza.navike);
			printf("Lijekovi: %s\n", (sviPacijenti + i)->anamneza.lijekovi);

			printf("\nDolazak zbog: %s\n", (sviPacijenti + i)->dolazak);
			printf("Datum dolaska:\n");
			printf("Dan: %hu\n", (sviPacijenti + i)->datum.danDolaska);
			printf("Mjesec: %hu\n", (sviPacijenti + i)->datum.mjesecDolaska);
			printf("Godina: %hu\n", (sviPacijenti + i)->datum.godinaDolaska);
			printf("Vrijeme: %s\n", (sviPacijenti + i)->datum.vrijeme);
			printf("Odjel: %s\n", (sviPacijenti)->odjel);
			printf("\nDatum otpusta:\n");
			printf("Dan: %hu.\n", (sviPacijenti + i)->datumOtpusta.danOtpusta);
			printf("Mjesec:%hu.\n", (sviPacijenti + i)->datumOtpusta.mjesecOtpusta);
			printf("Godina: %hu.\n", (sviPacijenti + i)->datumOtpusta.godinaOtpusta);
			printf("Vrijeme: %s\n", (sviPacijenti + i)->datumOtpusta.vrijemeOtpusta);
			printf("\n");
			printf("------------------------------------------------------------\n");
		}
		fclose(pacijenti);
		free(sviPacijenti);
	}
}


void izlaz(void) {

	char odgovor[3] = { 0 };

	printf("Jeste li sigurni da zelite izaci iz programa? [da/ne]:\n");
	scanf("%2s", &odgovor);

	if (!strcmp("da", odgovor)) {

		exit(EXIT_FAILURE);
	}
	else {
		system("cls");
		menu();
	}
	return;
}



void brisanje() {

	int brPacijenata = 0;

	PACIJENT* sviPacijenti = NULL;

	FILE* pacijenti = NULL;

	pacijenti = fopen("Popis Pacijenata.bin", "ab+");//otvaranje datoteke za citanje i pisanje

	if (pacijenti == NULL) {

		printf("Datoteka se ne moze otvoriti.\n");
		exit(EXIT_FAILURE);
	}
	else {

		fread(&brPacijenata, sizeof(int), 1, pacijenti);
		sviPacijenti = (PACIJENT*)calloc(brPacijenata, sizeof(PACIJENT));

		if (sviPacijenti == NULL) {

			printf("Greska pri citanju datoteke.\n");
			exit(EXIT_FAILURE);
		}
		else {

			fread(sviPacijenti, sizeof(PACIJENT), brPacijenata, pacijenti);
			fclose(pacijenti);
			sortiranje(sviPacijenti, brPacijenata);
			int i;
			int trazeniOIB = { 0 };
			for (int i = 0; i < brPacijenata; i++) {


				printf("\nPACIJENT %d.\n", i + 1);
				printf("Ime: %s\n", (sviPacijenti + i)->ime);
				printf("Prezime: %s\n", (sviPacijenti + i)->prezime);
				printf("OIB: %d\n", (sviPacijenti + i)->OIB);
				printf("Broj Mobitela: %s\n", (sviPacijenti + i)->brojMob);
				printf("Adresa: %s, %s\n", (sviPacijenti + i)->prebivaliste.adresaStanovanja, (sviPacijenti + i)->prebivaliste.mjestoStanovanja);
				printf("Datum rodenja:\n");
				printf("Dan: %hu.\n", (sviPacijenti + i)->dob.dan);
				printf("Mjesec: %hu.\n", (sviPacijenti + i)->dob.mjesec);
				printf("Godina: %hu.\n", (sviPacijenti + i)->dob.godina);

				printf("\nAnamneza:\n");
				printf("Prethodne bolesti:\n%s\n", (sviPacijenti + i)->anamneza.prethodneBolesti);
				printf("Simptomi:%s\n", (sviPacijenti + i)->anamneza.simptomi);
				printf("Temperatura: %s\n", (sviPacijenti + i)->anamneza.temperatura);
				printf("Alergije: %s\n", (sviPacijenti + i)->anamneza.alergija);
				printf("Lose navike: %s\n", (sviPacijenti + i)->anamneza.navike);
				printf("Lijekovi: %s\n", (sviPacijenti + i)->anamneza.lijekovi);

				printf("\nDolazak zbog: %s\n", (sviPacijenti + i)->dolazak);
				printf("Datum dolaska:\n");
				printf("Dan: %hu\n", (sviPacijenti + i)->datum.danDolaska);
				printf("Mjesec: %hu\n", (sviPacijenti + i)->datum.mjesecDolaska);
				printf("Godina: %hu\n", (sviPacijenti + i)->datum.godinaDolaska);
				printf("Vrijeme: %s\n", (sviPacijenti + i)->datum.vrijeme);
				printf("Odjel: %s\n", (sviPacijenti)->odjel);
				printf("\nDatum otpusta:\n");
				printf("Dan: %hu.\n", (sviPacijenti + i)->datumOtpusta.danOtpusta);
				printf("Mjesec:%hu.\n", (sviPacijenti + i)->datumOtpusta.mjesecOtpusta);
				printf("Godina: %hu.\n", (sviPacijenti + i)->datumOtpusta.godinaOtpusta);
				printf("Vrijeme: %s\n", (sviPacijenti + i)->datumOtpusta.vrijemeOtpusta);
				printf("\n");
				printf("------------------------------------------------------------\n");


			}
			printf("Unesite OIB pacijenta kojeg zelite obrisati:\n");
			fflush(stdin); //brise standardni ulaz u slucaju da je ostalo nesto od inputa
			scanf("%d", &trazeniOIB);

			int found = 0;
			int index = -1;

			for (i = 0; i < brPacijenata; i++) {

				if ((sviPacijenti + i)->OIB == trazeniOIB) {

					found = 1;
					index = i;
				}
			}
			if (found) {

				for (int mjesto = index; mjesto < brPacijenata - 1; mjesto++)

					*(sviPacijenti + mjesto) = *(sviPacijenti + mjesto + 1);
				// na mjesto obrisanog pacijenta dolaze podaci o sljedecem pacijentu	
								
				printf("\n/Pacijent uspjesno obrisan/\n\n");
			}
			else {
				printf("Pacijent ne postoji.\n");
			}

			FILE* datoteka = NULL;
			int x = brPacijenata - 1; // od ukupnog broja treba oduzeti jedan jer smo iz pokazivaca obrisali trazenog pacijenta
			datoteka = fopen("Popis Pacijenata.bin", "wb+"); //brise sve podatke iz datoteke
			rewind(datoteka);
			fwrite(&x, sizeof(int), 1, datoteka); //upisuje broj pacijenata koje imamo nakon brisanja jednog 
			fwrite(sviPacijenti, sizeof(PACIJENT), x, datoteka); //upisuje sve informacije s pokazivaca bez zadnjeg elementa --- pogledaj *(1)
			fclose(datoteka);
			free(sviPacijenti);
		}
	}
}
