#include<iostream>
#include<stdio.h>
#include<string>
#include <conio.h>
#include <iostream>
#include <fstream>
#include<vector>
#include<algorithm>
#include<list>
#include <set>
#include <map>
using namespace std;



class Participant {
private:
	char* nume;
	char prenume[20];
	const int id;
	float* inaltime;
	int varsta;
	static int nrTotalP; //nrTotalP = contor ca sa tin minte 

	//CONSTRUCTOR FARA PARAMETRI
public:
	Participant() :id(nrTotalP++) {
		this->nume = NULL;
		*this->prenume = NULL;
		this->inaltime = NULL;
		this->varsta = 20;
		cout << "S-a apelat constructorul fara parametri!" << endl;
	}

	//CONSTRUCTOR CU 1 PARAMETRU
	Participant(int varsta) :id(nrTotalP++) {
		this->varsta = varsta;
		this->nume = NULL;
		this->inaltime = NULL;
		cout << "S-a apelat constructor cu 1 parametru" << endl;
	}

	//CONSTRUCTOR CU TOTI PARAMETRII
	Participant(char* nume, char prenume[20], float* inaltime, int varsta) :id(nrTotalP++) {
		this->nume = new char[strlen(nume) + 1];
		strcpy(this->nume, nume);
		strcpy(this->prenume, prenume);
		this->inaltime = new float[nrTotalP];
		for (int i = 0; i < nrTotalP; i++)
			this->inaltime[i] = inaltime[i];
		this->varsta = varsta;
		cout << "S-a apelat si constructorul cu TOTI parametrii!" << endl;
	}

	//CONSTRUCTOR DE COPIERE
	Participant(const Participant& p) :id(nrTotalP++) {
		this->nume = new char[strlen(p.nume) + 1];
		strcpy(this->nume, p.nume);
		this->inaltime = new float[p.nrTotalP];
		for (int i = 0; i < p.nrTotalP; i++)
			this->inaltime[i] = p.inaltime[i];
		this->varsta = p.varsta;
		cout << "S-a apelat CONSTRUCTORUL DE COPIERE!" << endl;
	}

	//OPERATORUL =
	Participant& operator=(const Participant& p) {
		this->nume = new char[strlen(p.nume) + 1];
		strcpy(this->nume, p.nume);
		this->inaltime = new float[p.nrTotalP];
		for (int i = 0; i < p.nrTotalP; i++)
			this->inaltime[i] = p.inaltime[i];
		this->varsta = p.varsta;
		cout << "S-a apelat OPERATORUL =!!!!!!" << endl;
		return *this;
	}

	//SUPRAINCARCARE <<
	friend ostream& operator<<(ostream& out, Participant& p) {
		out << "Nume: " << p.nume << endl;
		for (int i = 0; i < p.nrTotalP; i++)
			out << "Inaltime participant " << i + 1 << ":" << p.inaltime[i] << endl;
		out << "Varsta: " << p.varsta << endl;
		out << "Numarul total de obiecte create este: " << p.nrTotalP << endl;
		return out;
	}

	//SUPRAINCARCARE >>
	friend istream& operator>>(istream& in, Participant& p) {
		cout << "Nume:";
		in >> p.nume;
		for (int i = 0; i < p.nrTotalP; i++) {
			cout << "Inaltime participant " << i + 1 << ":";
			in >> p.inaltime[i];
		}
		cout << "Varsta: ";
		in >> p.varsta;
		cout << "Numarul total de obiecte create este: " << p.nrTotalP << endl;
		return in;
	}

	//din fisier pentrut FAZA TREI
	friend ofstream& operator << (ofstream& out, Participant& p) {
		out << p.nume << endl;
		out << p.nrTotalP << endl;
		for (int i = 0; i < p.nrTotalP; i++) {
			out << p.inaltime[i] << endl;
		}
		out << p.varsta << endl;
		return out;
	}

	friend ifstream& operator >> (ifstream& in, Participant& p) {

		in >> p.nume;
		in >> p.nrTotalP;
		for (int i = 0; i < p.nrTotalP; i++) {
			cout << "Inaltime participant:" << i + 1 << ":";
			in >> p.inaltime[i];
		}
		in >> p.varsta;
		return in;
	}

	//Supraincarcare OPERATOR DE INDEXARE []
	float& operator [](int index) {
		if (index<0 || index> this->nrTotalP) {
			cout << "Hey u, ai depasit limita!!" << endl;
			throw new exception("Exceptie*");
		}
		else return this->inaltime[index];
	}

	//SUPRAINCARCARE OPERATOR CAST la float
	explicit operator float() {
		return *this->inaltime;
	}

	//SUPRAINCARCARE OPEEATOR + pentru apel p1+5
	Participant operator+(int varsta) {
		Participant copie = *this;
		copie.varsta = copie.varsta + varsta;
		return copie;
	}

	//SUPRAINCARCARE OPEEATOR - pentru apel p1-5
	Participant operator-(int varsta) {
		Participant copie = *this;
		copie.varsta = copie.varsta - varsta;
		return copie;
	}

	// SUPRAINCARCARE operator ++ prefixat; ++p1; adaugam un nou participant
	Participant operator++()
	{
		this->nume++;
		return *this;
	}

	//SUPRAINCARCARE operator postincrementare
	Participant operator++(int)
	{
		Participant copie = *this;
		this->nume++;
		return copie;
	}

	//SUPRAINCARCARE OPERATOR ==
	bool operator == (Participant p) {
		if (this->nume == p.nume && this->varsta == p.varsta)
			return true;
		else
			return false;
	}

	//SUPRAINCARCARE >= verificare varsta a doi participanti
	//() varsta primului participant mai mare sau egala decat varsta participantului 2
	bool operator>=(Participant p) {
		if (this->varsta == p.varsta)
			return true;
		else
			return false;
	}

	//OPERATORUL DE NEGATIE
	bool operator!() {
		if (this->inaltime != NULL)
			return false;
		else
			return true;
	}


	//DESTRUCTOR
	~Participant() {
		if (this->nume != NULL) {
			delete[]this->nume;
		}
		if (this->inaltime != NULL) {
			delete[]this->inaltime;
		}
		cout << "S-a apelat destructor PARTICIPANT!" << endl;
	}

	//FUNCTIE DE AFISARE
	void afisareParticipant() {
		printf("Nume: %s \n", this->nume);
		for (int i = 0; i < nrTotalP; i++)
			cout << "Inaltime participant " << i + 1 << ":" << this->inaltime << endl;
		cout << "Varsta: " << this->varsta << endl;
		cout << "Numarul total de obiecte create este: " << this->nrTotalP << endl;
	}


	//functie de verificare varsta
	bool validareNumar(const char* p) {
		for (int i = 0; i < strlen(p); i++)
			if (isdigit(p[i]) == false)
				return false;
			else return true;
	}

	//setter varsta
	void setVarsta(int varsta) {
		if (varsta <= 10)
			cout << "Nu puteti participa!" << endl;
		else this->varsta = varsta;
	}


	//setter nume
	void setNume(const char* numeNOU) {
		while (validareNumar(numeNOU)) {
			cout << "Vezi BA ca ai introdus cifre in MY NAME!" << endl;
			scanf("%s", nume);
		}
		this->nume = new char[strlen(numeNOU) + 1];
		strcpy(this->nume, numeNOU);

	}

	//setter prenume
	void setPrenume(char prenumeNOU) {
		if (prenumeNOU == NULL)
			throw new exception("Prenumele nu poate fi null!!!!");
		this->prenume[20] = prenumeNOU;
	}

	//setter inaltime
	void setInaltime(float* inaltime, int nrTotalP) {
		this->nrTotalP = nrTotalP;
		if (this->inaltime != NULL)
			delete[]this->inaltime;
		this->inaltime = new float[nrTotalP];
		for (int i = 0; i < nrTotalP; i++)
			this->inaltime[i] = inaltime[i];
	}

	//getter varsta
	int getVarsta() {
		return this->varsta;
	}
	//getter pentru nume
	const char* getNume() {
		return nume;
	}

	//getter prenume
	char getPrenume() {
		return prenume[20];
	}

	//getter inaltime
	float* getInaltime() {
		return this->inaltime;
	}
};
int Participant::nrTotalP = 1;

class Probe {
private:
	const int id;
	static int nrProbe;
	char* numeProba;
	char numeJurati[5];
	float* punctajProba;
	int nrJurati;

	//CONSTRUCTOR FARA PARAMETRI
public:
	Probe() :id(nrProbe++) {
		this->numeProba = NULL;
		*this->numeJurati = NULL;
		this->punctajProba = NULL;
		this->nrJurati = 5;
		cout << "S-a apelat constructorul fara parametrii PROBE!" << endl;
	}

	//CONSTRUCTOR CU 1 PARAMETRU
	Probe(char* numeProba) :id(nrProbe++) {
		this->numeProba = new char[strlen(numeProba) + 1];
		strcpy(this->numeProba, numeProba);
		this->punctajProba = NULL;
		cout << "S-a apelat constructorul cu 1 parametru PROBE!" << endl;
	}

	//CONSTRUCTOR CU TOTI PARAMETRII
	Probe(char* numeProba, char numeJurati[5], float* punctajProba, int nrJurati) :id(nrProbe++) {
		this->numeProba = new char[strlen(numeProba) + 1];
		strcpy(this->numeProba, numeProba);
		strcpy(this->numeJurati, numeJurati);
		this->punctajProba = new float[nrProbe];
		for (int i = 0; i < nrProbe; i++) {
			this->punctajProba[i] = punctajProba[i];
		}
		this->nrJurati = nrJurati;
		cout << "S-a apelat constructorul cu TOTI parametrii PROBE!" << endl;
	}

	//CONSTRUCTOR DE COPIERE
	Probe(const Probe& pr) :id(nrProbe++) {
		this->numeProba = new char[strlen(pr.numeProba) + 1];
		strcpy(this->numeProba, pr.numeProba);
		strcpy(this->numeJurati, pr.numeJurati);
		this->punctajProba = new float[pr.nrProbe];
		for (int i = 0; i < pr.nrProbe; i++) {
			this->punctajProba[i] = pr.punctajProba[i];
		}
		this->nrJurati = pr.nrJurati;
		cout << "S-a apelat constructorul de COPIERE PROBE!" << endl;
	}

	//OPERATORUL =
	Probe& operator=(const Probe& pr) {
		this->numeProba = new char[strlen(pr.numeProba) + 1];
		strcpy(this->numeProba, pr.numeProba);
		strcpy(this->numeJurati, pr.numeJurati);
		this->punctajProba = new float[pr.nrProbe];
		for (int i = 0; i < pr.nrProbe; i++) {
			this->punctajProba[i] = pr.punctajProba[i];
		}
		this->nrJurati = pr.nrJurati;
		cout << "S-a apelat constructorul de COPIERE PROBE!" << endl;
		return *this;
	}

	//SUPRAINCARCARE <<
	friend ostream& operator<<(ostream& out, Probe& pr) {
		out << "Nume proba: " << pr.numeProba << endl;
		for (int i = 0; i < pr.nrProbe; i++)
			out << "Punctajul probei " << i + 1 << ":" << pr.punctajProba[i] << endl;
		out << "Numar jurati: " << pr.nrJurati << endl;
		out << "Numarul de probe este: " << pr.nrProbe << endl;
		return out;
	}

	//SUPRAINCARCARE >>
	friend istream& operator>>(istream& in, Probe& pr) {
		cout << "Nume proba: ";
		in >> pr.numeProba;
		for (int i = 0; i < pr.nrProbe; i++) {
			cout << "Punctajul probei " << i + 1 << ":" << endl;
			in >> pr.punctajProba[i];
		}
		cout << "Numar jurati: ";
		in >> pr.nrJurati;
		cout << "Numarul de probe este: " << pr.nrProbe << endl;
		return in;
	}


	//Supraincarcare OPERATOR DE INDEXARE []
	float& operator [](int index) {
		if (index<0 || index> this->nrProbe) {
			cout << "Hey u, potoleste-te!!!!" << endl;
			throw new exception("Exceptie*");
		}
		else return this->punctajProba[index];
	}

	//SUPRAINCARCARE OPERATOR CAST la float
	explicit operator float() {
		return *this->punctajProba;
	}

	//SUPRAINCARCARE OPEEATOR + pentru apel pr1+2
	Probe operator+(int nrJurati) {
		Probe copie = *this;
		copie.nrJurati = copie.nrJurati + nrJurati;
		return copie;
	}

	//SUPRAINCARCARE OPEEATOR - pentru apel pr1-2
	Probe operator-(int nrJurati) {
		Probe copie = *this;
		copie.nrJurati = copie.nrJurati - nrJurati;
		return copie;
	}

	// SUPRAINCARCARE operator ++ prefixat; ++pr1; adaugam o noua proba
	Probe operator++()
	{
		this->numeProba++;
		return *this;
	}

	//SUPRAINCARCARE operator postincrementare
	Probe operator++(int)
	{
		Probe copie = *this;
		this->numeProba++;
		return copie;
	}

	//SUPRAINCARCARE OPERATOR ==
	bool operator == (Probe pr) {
		if (this->numeProba == pr.numeProba && this->nrJurati == pr.nrJurati)
			return true;
		else
			return false;
	}

	//SUPRAINCARCARE >= verificare punctajului a doi participanti
	//() punctajul primei probe mai mare sau egala decat punctajul probei 2
	bool operator>=(Probe pr) {
		if (this->punctajProba == pr.punctajProba)
			return true;
		else
			return false;
	}

	//OPERATORUL DE NEGATIE
	bool operator!() {
		if (this->punctajProba != NULL)
			return false;
		else
			return true;
	}

	//DESTRUCTOR
	~Probe() {
		if (this->numeProba != NULL)
			delete[]this->numeProba;
		if (this->punctajProba != NULL)
			delete[]this->punctajProba;
		cout << "S-a apelat destructor PROBE!" << endl;
	}

	//FUNCTIE DE AFISARE
	void afisareProbe() {
		printf("Nume Proba: %s \n", this->numeProba);
		for (int i = 0; i < nrProbe; i++)
			cout << "Punctaj proba " << i + 1 << ":" << this->punctajProba << endl;
		cout << "Numar jurati: " << this->nrJurati << endl;
		cout << "Numarul total de probe este: " << this->nrProbe << endl;
	}


	//functie de verificare nrJurati
	bool validareNrJurati(const char* pr) {
		for (int i = 0; i < strlen(pr); i++)
			if (isdigit(pr[i]) == false)
				return false;
			else return true;
	}

	//setter numeProba
	void setNumeProba(char* numeProba, int nrProbenou) {
		if (this->numeProba != NULL) {
			delete[] this->numeProba;
		}
		this->nrProbe = nrProbenou;
		this->numeProba = new char[this->nrProbe];
		for (int i = 0; i < this->nrProbe; i++) {
			this->numeProba[i] = numeProba[i];
		}
	}

	//setter nrJurati
	void setNrJurati(int nrJurati) {
		if (nrJurati >= 5)
			cout << "Ai grija!! Te las sa mai introduci o data!!!!" << endl;
		else this->nrJurati = nrJurati;
	}

	//setter punctajProba
	void setPunctajProba(float* punctajProba, int nrProbe) {
		this->nrProbe = nrProbe;
		if (this->punctajProba != NULL)
			delete[]this->punctajProba;
		this->punctajProba = new float[nrProbe];
		for (int i = 0; i < nrProbe; i++)
			this->punctajProba[i] = punctajProba[i];
	}

	//getter pentru numeProba
	const char* getNumeProba() {
		return numeProba;
	}

	//getter punctajProba
	float* getPunctajProba() {
		return this->punctajProba;
	}

	//getter nrJurati
	int getNrJurati() {
		return this->nrJurati;
	}

};

//initializare variabila statica
int Probe::nrProbe = 1;

class Clasament {
	const int loc;	// locul 1,2,3 etc
	static int nrLocuri;
	char* titlu;	// gen locul 1 pentru cel mai bun...
	float* punctajTotal;
	char numeArbitru[10];
	int nrArbitrii;


	//CONSTRUCTOR FARA PARAMETRI
public:
	Clasament() :loc(nrLocuri++) {
		this->titlu = NULL;
		this->punctajTotal = NULL;
		*this->numeArbitru = NULL;
		this->nrArbitrii = NULL;
		cout << "S-a apelat constructorul FARA parametri CLASAMENT!" << endl;
	}

	//CONSTRUCTOR CU 1 PARAMETRU
	Clasament(char* titlu) :loc(nrLocuri++) {
		this->titlu = new char[strlen(titlu) + 1];
		strcpy(this->titlu, titlu);
		this->punctajTotal = NULL;
		cout << "S-a apelat constructorul cu 1 parametru CLASAMENT!" << endl;
	}

	//CONSTRUCTOR CU TOTI PARAMETRII
	Clasament(char* titlu, float* punctajTotal, char numeArbitru[10], int nrArbitrii) :loc(nrLocuri++) {
		this->titlu = new char[strlen(titlu) + 1];
		strcpy(this->titlu, titlu);
		this->punctajTotal = new float[nrLocuri];
		for (int i = 0; i < nrLocuri; i++) {
			this->punctajTotal[i] = punctajTotal[i];
		}
		strcpy(this->numeArbitru, numeArbitru);
		this->nrArbitrii = nrArbitrii;
		cout << "S-a apelat constructorul cu TOTI parametrii CLASAMENT!" << endl;
	}

	//CONSTRUCTOR DE COPIERE
	Clasament(const Clasament& c) :loc(nrLocuri++) {
		this->titlu = new char[strlen(c.titlu) + 1];
		strcpy(this->titlu, c.titlu);
		this->punctajTotal = new float[c.nrLocuri];
		for (int i = 0; i < c.nrLocuri; i++) {
			this->punctajTotal[i] = c.punctajTotal[i];
		}
		strcpy(this->numeArbitru, c.numeArbitru);
		this->nrArbitrii = c.nrArbitrii;
		cout << "S-a apelat constructorul de COPIERE pt CLASAMENT!" << endl;
	}

	//SUPRAINCARCARE OPERATOR =
	Clasament& operator=(const Clasament& c) {
		this->titlu = new char[strlen(c.titlu) + 1];
		strcpy(this->titlu, c.titlu);
		this->punctajTotal = new float[c.nrLocuri];
		for (int i = 0; i < c.nrLocuri; i++) {
			this->punctajTotal[i] = c.punctajTotal[i];
		}
		strcpy(this->numeArbitru, c.numeArbitru);
		this->nrArbitrii = c.nrArbitrii;
		cout << "S-a apelat OPERATORUL = pt CLASAMENT!!" << endl;
		return *this;
	}

	//SUPRAINCARCARE <<
	friend ostream& operator<<(ostream& out, Clasament& c) {
		out << "Titlu: " << c.titlu << endl;
		for (int i = 0; i < c.nrLocuri; i++)
			out << "Punctaj total " << i + 1 << ":" << c.punctajTotal[i] << endl;
		out << "Introduceti nume arbitru: " << c.numeArbitru << endl;
		out << "Numarul arbitrilor: " << c.nrArbitrii << endl;
		out << "Numarul de locuri este: " << c.nrLocuri << endl;
		return out;
	}

	//SUPRAINCARCARE >>
	friend istream& operator >>(istream& in, Clasament& c) {
		cout << "Titlu: ";
		in >> c.titlu;
		for (int i = 0; i < c.nrLocuri; i++) {
			cout << "Punctaj total " << i + 1 << ":";
			in >> c.punctajTotal[i];
		}
		cout << "Nume arbitru: ";
		in >> c.numeArbitru;
		cout << "Numar arbitrii: ";
		in >> c.nrArbitrii;
		cout << "Numarul de locuri este: " << c.nrLocuri << endl;
		return in;
	}

	//Supraincarcare OPERATOR DE INDEXARE []
	float& operator [](int index) {
		if (index<0 || index> this->nrLocuri) {
			cout << "Hey u, ai depasit nr de LOCURI!!" << endl;
			throw new exception("Exceptie*");
		}
		else return this->punctajTotal[index];
	}

	//SUPRAINCARCARE OPERATOR CAST la float
	explicit operator float() {
		return *this->punctajTotal;
	}


	//SUPRAINCARCARE OPEEATOR + pentru apel c1+3
	Clasament operator+(int nrArbitrii) {
		Clasament copie = *this;
		copie.nrArbitrii = copie.nrArbitrii + nrArbitrii;
		return copie;
	}

	//SUPRAINCARCARE OPEEATOR - pentru apel c1-3
	Clasament operator-(int nrArbitrii) {
		Clasament copie = *this;
		copie.nrArbitrii = copie.nrArbitrii - nrArbitrii;
		return copie;
	}


	// SUPRAINCARCARE operator ++ prefixat; ++c1; adaugam un nou titlu
	Clasament operator++()
	{
		this->titlu++;
		return *this;
	}

	//SUPRAINCARCARE operator postincrementare
	Clasament operator++(int)
	{
		Clasament copie = *this;
		this->titlu++;
		return copie;
	}

	//SUPRAINCARCARE OPERATOR ==
	bool operator == (Clasament c) {
		if (this->titlu == c.titlu && this->punctajTotal == c.punctajTotal)
			return true;
		else
			return false;
	}

	//SUPRAINCARCARE >= verificare punctaj total a doi participanti
	//() punctajul total al primului participant mai mare sau egal decat al celui de-al doilea participant
	bool operator>=(Clasament c) {
		if (this->punctajTotal == c.punctajTotal)
			return true;
		else
			return false;
	}

	//OPERATORUL DE NEGATIE
	bool operator!() {
		if (this->punctajTotal != NULL)
			return false;
		else
			return true;
	}


	//DESTRUCTOR
	~Clasament() {
		if (this->titlu != NULL)
			delete[]this->titlu;
		if (this->punctajTotal != NULL)
			delete[]this->punctajTotal;
		cout << "S-a apelat destructor CLASAMENT!" << endl;
	}


	//FUNCTIE DE AFISARE
	void afisareClasament() {
		printf("Titlu: %s \n", this->titlu);
		for (int i = 0; i < nrLocuri; i++)
			cout << "Punctajul total " << i + 1 << ":" << this->punctajTotal << endl;
		cout << "Numar arbitrii: " << this->nrArbitrii << endl;
		cout << "Numarul de locuri create este: " << this->nrLocuri << endl;
	}


	//functie de verificare nrArbitrii
	bool validareNrArbitrii(const char* c) {
		for (int i = 0; i < strlen(c); i++)
			if (isdigit(c[i]) == false)
				return false;
			else return true;
	}

	//setter titlu
	void setTitlu(char* titlu, int nrLocuriNou) {
		if (this->titlu != NULL) {
			delete[] this->titlu;
		}
		this->nrLocuri = nrLocuriNou;
		this->titlu = new char[this->nrLocuri];
		for (int i = 0; i < this->nrLocuri; i++) {
			this->titlu[i] = titlu[i];
		}
	}

	//setter punctajTotal
	void setPunctajTotal(float* punctajTotal, int nrLocuriNou) {
		this->nrLocuri = nrLocuriNou;
		if (this->punctajTotal != NULL)
			delete[]this->punctajTotal;
		this->punctajTotal = new float[nrLocuri];
		for (int i = 0; i < nrLocuri; i++)
			this->punctajTotal[i] = punctajTotal[i];
	}

	//setter numeArbitru
	void setNumeArbitru(char numeArbitruNOU)
	{
		if (numeArbitruNOU == NULL)
			throw new exception("Nume arbitru nu poate fi NULL!!!");
		this->numeArbitru[10] = numeArbitruNOU;
	}

	//setter nrArbitrii
	void setNrArbitrii(int nrArbitrii) {
		if (nrArbitrii > 10)
			cout << "Sun pre mult arbitrii, nu avem ce face cu ei. Ne pare raaaaau!!!" << endl;
		else this->nrArbitrii = nrArbitrii;
	}

	//getter pentru titlu
	const char* getTitlu() {
		return titlu;
	}

	//getter punctajTotal
	float* getPunctajTotal() {
		return this->punctajTotal;
	}

	//getter numeArbitru
	char getNumeArbitru() {
		return numeArbitru[10];
	}

	//getter nrArbitrii
	int getNrArbitrii() {
		return this->nrArbitrii;
	}
};

int Clasament::nrLocuri = 1;

//===================================================================================================================================
class Proba1 :public Probe { //mostenim tot ce e in public in Probe
protected: //vor fi vizibile in ambele clase
	float punctajParticipant;

public:

	Proba1() :Probe() { //apeleaza si constructorul default al clasei Probe
		this->punctajParticipant = NULL;
	}

	Proba1(char* numeProba, char numeJurati[5], float* punctajProba, int nrJurati, float punctajParticipant) :Probe(numeProba, numeJurati, punctajProba, nrJurati) {
		cout << "Costructor cu parametrii clasa Proba1 " << endl;
		this->punctajParticipant = punctajParticipant;
	}

	Proba1(const Probe& pr) :Probe(pr) {
		this->punctajParticipant = punctajParticipant;
	}

	void setPunctajParticipant(int punctajParticipant) {
		this->punctajParticipant = punctajParticipant;
	}

	float getPunctajParticipant() {
		return this->punctajParticipant;
	}

	~Proba1() {
		cout << "Destructor clasa Proba1!!!" << endl;
	}

	void afisareProbe2() { //nume si varsta cu getteri pt ca sunt in zona PRIVATE a clasei Probe
		printf("Nume Proba: %s \n", this->getNumeProba());
		cout << "Numar jurati: " << this->getNrJurati() << endl;
		cout << "Punctaj Proba: " << this->getPunctajProba() << endl;
		cout << "Punctaj participant: " << this->punctajParticipant << endl;
	}
};

//===================================================================================================================================

class Atletism :public Clasament {
protected:
	char gen;

public:
	Atletism() :Clasament() {
		this->gen = NULL;
	}

	Atletism(char* titlu, float* punctajTotal, char numeArbitru[10], int nrArbitrii, char gen) :Clasament(titlu, punctajTotal, numeArbitru, nrArbitrii) {
		cout << "Apel constructor cu parametri clasa ProfesorPOO" << endl;
		this->gen = gen;
	}

	~Atletism() {
		cout << "Destructor clasa ATLETISM" << endl;
	}

	char getGen() {
		return this->gen;
	}

	void setGen(char genN) {
		this->gen = genN;
	}

	void afisareAtletism() {
		printf("Titlu: %s \n", this->getTitlu());
		cout << "Punctaj total: " << this->getPunctajTotal() << endl;
		cout << "Numar arbitrii: " << this->getNrArbitrii() << endl;
		cout << "Nume arbitru " << this->getNumeArbitru() << endl;
		cout << "Numar arbitrii " << this->getNrArbitrii() << endl;
		cout << "Genul Participantului: " << this->gen << endl;

	}

	void afisareAtletism2() {
		afisareClasament();
		cout << "Genul " << this->gen << endl;
	}

};
//------------------------------------------------------------------------------------------------------------------------------------


//CLASA ABSTRACTA

class ParticipantStrain :public Participant {
private:
	string cetatenie;
public:
	string getCetatenie() {
		return this->cetatenie;
	}

	virtual void calculMediaVarstaParticipanti() = 0;
};

//INTERFATA

class IVarstaParticipanti {
public:
	virtual void maresteVarstaParticipanti() = 0;
	virtual void scadeVarstaParticipanti() = 0;
};

//clasa ParticipantSpaniol

class ParticipantSpaniol :public ParticipantStrain, public IVarstaParticipanti {
public:
	virtual void calculMedieVarsta() {
		cout << "Media varstei unul participant spaniol este  " << endl;
	}
};

//HAS A
class Juriu {
private:
	int nrPersoane;
	Participant** p1;
public:
	Juriu() {
		this->nrPersoane = 0;
		this->p1 = NULL;
	}

	Juriu(int nrPersoane, Participant** p1) {
		this->nrPersoane = nrPersoane;
		this->p1 = new Participant * [this->nrPersoane];
		for (int i = 0; i < this->nrPersoane; i++) {
			this->p1[i] = p1[i];
		}
	}

	~Juriu() {
		if (this->p1 != NULL) {
			delete[]this->p1;
		}
	}

	void afisareJuriu() {
		cout << "Afisare JURIU!!! " << endl;
		cout << "Numarul de Participanti: " << this->nrPersoane << endl;
		for (int i = 0; i < this->nrPersoane; i++) {
			this->p1[i]->afisareParticipant();
		}
	}
};
//------------------------------------------------------------------------------------------------------------------------------------
int main() {

	//CLASA PARTICIPANT
	//apelare costructor fara parametrii
	Participant p1;
	p1.afisareParticipant();

	//apelare funct varsta
	int varsta = 0;
	cout << "Introduceti varsta: " << endl;
	cin >> varsta;
	p1.setVarsta(varsta);
	cout << p1.getVarsta() << endl;


	//apelare costructor cu 1 parametru
	Participant p2(25);
	cout << p2.getVarsta() << endl;

	//apelare costructor cu toti parametrii
	char nume[] = { "Numele participantului este Ion." };
	float inaltime[] = { 1.2 };
	char prenume[] = { "Prenumele este Costel. " };
	Participant p3(nume, prenume, inaltime, 21);

	//apel constructor copiere
	Participant p4 = p3;
	p4.afisareParticipant();

	//apel op >>
	cin >> p4;
	cout << p4;

	//apel functie de afisare 1
	p2.afisareParticipant();
	cout << "Prima afisare." << endl << endl << endl;

	//apel operator =
	p2 = p3;
	cout << "A doua afisare." << endl << endl << endl;

	//apel functie de afisare 2
	p2.afisareParticipant();

	//apel setter nume
	//p3.setNumeNOU(nume, strlen(nume) + 1);
	//apel getter nume
	cout << p3.getNume() << endl;
	//apel setter inaltime
	p3.setInaltime(inaltime, sizeof(inaltime) + 1);
	//apel getter inaltime
	float* inaltimeNoua = { p3.getInaltime() };
	cout << *inaltimeNoua << endl;

	//apelare INDEX []
	cout << "Participantul de pe prima pozitie: " << endl;
	try {
		cout << p1[4] << endl;
	}
	catch (exception* e) {
		cout << "Prima exceptie a fost prinsa. " << endl;
	}
	catch (...) {
		cout << "A doua exceptie a fost prinsa. " << endl;
	}

	//------------------------------------------------------------------------------------------------------------------------------------


	//CLASA PROBE
	//apelare costructor fara parametrii
	Probe pr1;

	//apelare costructor cu 1 parametru
	Probe pr2("Paralele");

	//apelare funct nrJurati
	int nrJurati = 0;
	cout << "Introduceti nrJurati: " << endl;
	cin >> nrJurati;
	pr1.setNrJurati(nrJurati);
	cout << pr1.getNrJurati() << endl;

	//tot cu toti parametrii
	char numeProba[] = { "Numele probei este: Paralele." };
	char numeJurati[] = { "Nume jurat: Andrei. " };
	float punctajProba[] = { 9 };
	Probe pr3(numeProba, numeJurati, punctajProba, 5);

	//apel functie de afisare 1
	pr2.afisareProbe();
	cout << "Prima afisare PROBE." << endl << endl << endl;

	//apel operator =
	pr2 = pr3;
	cout << "A doua afisare PROBE." << endl << endl << endl;

	//apel functie de afisare 2
	pr2.afisareProbe();

	//apel constructor copiere
	Probe pr4 = pr3;

	//apel op >>
	cin >> pr4;
	cout << pr4;

	//apel setter numeProba
	pr3.setNumeProba(numeProba, strlen(numeProba) + 1);
	//apel getter numeProba
	cout << pr3.getNumeProba() << endl;
	//apel setter punctajProba
	pr3.setPunctajProba(punctajProba, sizeof(punctajProba) + 1);
	//apel getter punctajProba
	float* punctajProbaNou = { pr3.getPunctajProba() };
	cout << *punctajProbaNou << endl;

	//apelare INDEX []
	cout << "Prima proba este: " << endl;
	try {
		cout << pr1[4] << endl;
	}
	catch (exception* ep) {
		cout << "Prima exceptie a fost prinsa. " << endl;
	}
	catch (...) {
		cout << "A doua exceptie a fost prinsa. " << endl;
	}

	//apel operator CAST;
	cout << "Punctajul primei probe este " << (float)pr1 << endl; //afisam punctajul primei probe
	cout << "S-a apelat operatorul CAST pt PROBE" << endl;


	//apel operator ==
	if (pr4 == pr3)
		cout << "pr4==pr3" << endl;
	else
		cout << "pr4!=pr3" << endl;

	//apel operator >=
	if (pr4 >= pr3)
		cout << "Adevarat" << endl;
	else
		cout << "Fals" << endl;

	//test supraincarcare preincrementare 
	Probe pr9;
	pr9 = ++pr9;
	cout << "\n\nProba numita " << pr9.getNumeProba() << " are " << pr9.getPunctajProba() << " punctajul." << endl;

	//test supraincarcare postincrementare 
	pr9 = pr9++;
	cout << "\n\nProba numita " << pr9.getNumeProba() << " are " << pr9.getPunctajProba() << " punctajul." << endl;


	//apel operator !
	if (!pr2)
		cout << "Adevarat" << endl;
	else
		cout << "Fals" << endl;

	//------------------------------------------------------------------------------------------------------------------------------------

	//CLASA CLASAMENT
	//apelare costructor fara parametri
	Clasament c1;

	//apelare costructor cu 1 parametru
	Clasament c2("Locul 1");

	//tot cu toti parametrii 
	char titlu[] = { "Titlul obtinut de participant este: Locul 1." };
	float punctajTotal[] = { 37 };
	char numeArbitru[] = { "Numele arbitrului este: Ionel. " };
	Clasament c3(titlu, punctajTotal, numeArbitru, 10);

	//apel functie de afisare 1
	c2.afisareClasament();
	cout << "Prima afisare CLASAMENT." << endl << endl << endl;

	//apel operator =
	c2 = c3;
	cout << "A doua afisare CLASAMENT." << endl << endl << endl;

	//apel functie de afisare 2
	c2.afisareClasament();

	//apel constructor copiere
	Clasament c4 = c3;

	//apel op >>
	cin >> c4;
	cout << c4;


	//apel setter titlu
	c3.setTitlu(titlu, strlen(titlu) + 1);
	//apel getter titlu
	cout << c3.getTitlu() << endl;
	//apel setter punctajTotal
	c3.setPunctajTotal(punctajTotal, sizeof(punctajTotal) + 1);
	//apel getter punctajTotal
	float* punctajTotalNou = { c3.getPunctajTotal() };
	cout << *punctajTotalNou << endl;

	//apelare INDEX []
	cout << "Primul loc este: " << endl;
	try {
		cout << c1[4] << endl;
	}
	catch (exception* ec) {
		cout << "Prima exceptie a fost prinsa. " << endl;
	}
	catch (...) {
		cout << "A doua exceptie a fost prinsa. " << endl;
	}

	//apel operator CAST;
	cout << "Punctajul total al primei probe este " << (float)c1 << endl; //afisam punctajul total al primei probe
	cout << "S-a apelat operatorul CAST pt CLASAMENT" << endl;


	//apel operator ==
	if (c4 == c3)
		cout << "c4==c3" << endl;
	else
		cout << "c4!=c3" << endl;

	//apel operator >=
	if (c4 >= c3)
		cout << "ADEVARAT" << endl;
	else
		cout << "FALS" << endl;

	//test supraincarcare preincrementare 
	Clasament c9;
	c9 = ++c9;
	cout << "\n\nTitlul " << c9.getTitlu() << " are " << c9.getPunctajTotal() << " punctajul total." << endl;

	//test supraincarcare postincrementare 
	c9 = c9++;
	cout << "\n\nTitlul " << c9.getTitlu() << " are " << c9.getPunctajTotal() << " punctajul total." << endl;


	//apel operator !
	if (!c2)
		cout << "ADEVARAT!!" << endl;
	else
		cout << "FALS!!" << endl;

	return 0;

	//------------------------------------------------------------------------------------------------------------------------------------
	//MOSTENIRE
	cout << "----------------------------------------------------------------------------" << endl;
	Probe pr;
	pr.afisareProbe();
	cout << "----------------------------------------------------------------------------" << endl;
	Proba1 prb1;
	prb1.afisareProbe();
	cout << "----------------------------------------------------------------------------" << endl;
	Atletism a;
	a.afisareAtletism();
	cout << "----------------------------------------------------------------------------" << endl;
	a.afisareAtletism2();

	//------------------------------------------------------------------------------------------------------------------------------------
	//CLASA ABSTRACTA&Interfata

	/* articipant* p;
	p->afisareParticipant();

	ParticipantSpaniol ps;
	ps.calculMedieVarsta();

	Juriu j;
	j.afisareJuriu(); */

	//------------------------------------------------------------------------------------------------------------------------------------

	//FAZA TREI

	// Scriere intr-un fisier normal
	ofstream fileWrite;
	fileWrite.open("Raluca.txt", ios::out);
	fileWrite << "Rlk";
	fileWrite.close();

	//Scriere intr-un fisier binar
	ofstream fileWriteBin;
	fileWriteBin.open("fisier_binar.dat", ios::binary | ios::out);
	fileWriteBin << p1;
	fileWriteBin.close();

	// Citire din fisier normal
	ifstream fileRead;
	fileRead.open("Raluca.txt", ios::in);
	Participant p31;
	fileRead >> p31;
	cout << "Obiect citit din fisier: " << endl << p31;
	fileRead.close();

	// Citire din fisier binar
	ifstream fileReadBin;
	fileReadBin.open("fisier_bin.dat", ios::binary | ios::in);
	Participant p21;
	fileReadBin >> p21;
	cout << "Obiect citit din fisier: " << endl << p21;
	fileReadBin.close();

	//STL VECTOR
	cout << "----------------------STL---VECTOR---------------------" << endl;
	vector<int>varstaNoua;
	varstaNoua.push_back(2);
	varstaNoua.push_back(3);
	varstaNoua.push_back(4);
	cout << "Afisare varsta: " << endl;
	for (int i = 0; i < varstaNoua.size(); i++) {
		cout << varstaNoua[i] + 2 << endl;
	}

	sort(varstaNoua.begin(), varstaNoua.end());
	cout << "ITERATOR VARSTA INT!!!!" << endl;
	vector<int>::iterator it;
	for (it = varstaNoua.begin(); it != varstaNoua.end(); it++) {
		cout << *it << endl;
	}
	cout << "ITERATOR VARSTA INT 2!!!!" << endl;
	varstaNoua.pop_back();
	for (it = varstaNoua.begin(); it != varstaNoua.end(); it++) {
		cout << *it << endl;
	}

	//STL SET
	cout << "----------------------STL---SET---------------------" << endl;
	set<string> numeParticipant;
	numeParticipant.insert("Vasilescu");
	numeParticipant.insert("Badea");
	numeParticipant.insert("Popescu");
	cout << "Afisare nume participant din set: " << endl;
	set<string>::iterator it2;
	for (it2 = numeParticipant.begin(); it2 != numeParticipant.end(); it2++) {
		cout << *it2 << endl;
	}
	cout << endl;
	it2 = numeParticipant.find("Badea");//verifica daca gasim participantul "Badea"
	if (it2 != numeParticipant.end()) {
		cout << "S-a gasit participantul.\n";
	}
	else {
		cout << "Nu s-a gasit participantul.\n";
	}


	//STL LIST
	cout << "----------------------STL---LIST---------------------" << endl;
	list<int>listaNR;
	listaNR.push_back(11);
	listaNR.push_front(1);
	listaNR.push_back(5);
	listaNR.push_front(9);

	cout << "Afisare listaNR: " << endl;
	list<int>::iterator it3;
	for (it3 = listaNR.begin(); it3 != listaNR.end(); it3++) {
		cout << *it3 << endl;
	}

	cout << "Afisare listaNR dupa apel pop_front: " << endl;
	listaNR.pop_front();
	for (it3 = listaNR.begin(); it3 != listaNR.end(); it3++) {
		cout << *it3 << endl;
	}

	cout << "Afisare lista dupa apel pop_back: " << endl;
	listaNR.pop_back();
	for (it3 = listaNR.begin(); it3 != listaNR.end(); it3++) {
		cout << *it3 << endl;
	}

	cout << "\nAfisare listaNR sortata: " << endl;
	listaNR.sort();
	for (it3 = listaNR.begin(); it3 != listaNR.end(); it3++) {
		cout << *it3 << endl;
	}

	cout << "\nAfisare listaNR reversed: " << endl;
	listaNR.reverse();
	for (it3 = listaNR.begin(); it3 != listaNR.end(); it3++) {
		cout << *it3 << endl;
	}

	//STL MAP
	cout << "----------STL------map--------" << endl;
	map<int, Participant> p50;
	//map-ul retine valorile sub forma de perechi de tip <cheie,valoare>
	//folosim metoda make_pair(...) pentru a crea perechi de tip cheie valoare
	//Atentie, cheia trebuie sa fie unica! Valorile sunt identificate in map dupa cheie! 
	p50.insert(make_pair(2020, 3));
	p50.insert(make_pair(2019, 4));
	p50.insert(make_pair(2918, 5));

	map<int, Participant>::iterator itMap;
	for (itMap = p50.begin(); itMap != p50.end(); itMap++) {
		cout << "In anul " << itMap->first << " a fost participantul " << itMap->second << endl;//afisare cheie si valoare
	}

	cout << "Apel map dupa cheie participant[2020] = " << endl << p50[2020];//identificare pereche dupa cheie


	//MENIU

	int MENIUclasaP;
	cin >> MENIUclasaP;
	switch (MENIUclasaP) {
	case 1:
	{
		if (MENIUclasaP == 1) cout << p1; //daca apasam tasta 1 va aparea obiectul p1 al clasei Participant
	}
	case 2:

		if (MENIUclasaP == 2) {
			Participant p12;
			cin >> p12; // daca apas tasta 2 introducem de la tastatura
		}

	case 3:
		if (MENIUclasaP == 3) { // daca apas tasta 3 imi la crea un poo.txt si imi va scrie ceva in el
			fstream RLK;
			RLK.open("ProiectPOO.txt", ios::out);
			if (RLK.is_open())
			{
				RLK << "ESTE TOTUL bn, sper, Doamne ajuta!!! \n";
				RLK.close();
			}
			RLK.open("ProiectPOO.txt", ios::in);
			if (RLK.is_open()) {
				string ProiectPOO;
				while (getline(RLK, ProiectPOO)) {
					cout << ProiectPOO << "\n";
				}
				RLK.close();
			}
		}

	}

}