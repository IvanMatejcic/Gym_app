#define _CRT_SECURE_NO_WARNINGS //Da radi localtime funkcija

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>

using namespace std;

class Datum {
private:
    int dan = 0, mjesec = 0, godina = 0;
public:
    //Konstruktor datuma
    Datum(int dan, int mjesec, int godina) {
        postavi_godinu(godina); //Postavljanje godine
        postavi_mjesec(mjesec); //Postavljanje mjeseca
        postavi_dan(dan); //Postavljanje dana
    }

    //Postavljanje godine datuma te provjera da li je valjana (Valjana je od 1900 - ...)
    void postavi_godinu(int godina) {
        if (godina >= 1900) {
            this->godina = godina;
        }
        else {
            do {
                cout << "Godina ne moze biti manja od 1900-te." << endl;
                cout << "Unesite godinu: ";
                cin >> godina;
            } while (godina < 1900);

            this->godina = godina;
        }
    }

    //Postavljanje mjeseca datuma te provjera da li je valjani (Valjani mjeseci su 1 - 12)
    void postavi_mjesec(int mjesec)
    {
        if (mjesec >= 1 && mjesec <= 12)
        {
            this->mjesec = mjesec;
        }
        else
        {
            do {
                cout << "Mjesec ne moze biti manji od 1. i veci od 12." << endl;
                cout << "Unesite mjesec: ";
                cin >> mjesec;
            } while (mjesec < 1 || mjesec > 12);

            this->mjesec = mjesec;
        }
    }

    //Postavljanje dana datuma te provjera da li je valjani (Valjani dani su 1 - 31, osim za veljace koji je 29)
    void postavi_dan(int dan)
    {
        if (dan >= 1 && dan <= 31)
        {
            if (mjesec == 2 && dan > 29)
            {
                do {
                    cout << "Veljaca moze imati maksimalno 29 dana." << endl;
                    cout << "Unesite dan: ";
                    cin >> dan;
                } while (dan > 29);

                this->dan = dan;
            }
            else
            {
                this->dan = dan;
            }
        }
        else
        {
            do {
                cout << "Dani ne mogu biti manji od 1 i veci od 31" << endl;
                cout << "Unesite dan: ";
                cin >> dan;
            } while (dan < 1 || dan > 31);

            this->dan = dan;
        }
    }

    //Getteri
    int getDan() { return dan; }
    int getMjesec() { return mjesec; }
    int getGodina() { return godina; }

    //Usporedba dvaju datuma da li su jednaki
    friend bool operator == (Datum const& d1, Datum const& d2)
    {
        if (d1.dan == d2.dan && d1.mjesec == d2.mjesec && d1.godina == d2.godina)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    friend bool operator<(Datum const& d1, Datum const& d2)
    {
        if (d1.godina < d2.godina) {
            return true;
        }
        else if (d1.godina == d2.godina && d1.mjesec < d2.mjesec) {
            return true;
        }
        else if (d1.godina == d2.godina && d1.mjesec == d2.mjesec && d1.dan < d2.dan) {
            return true;
        }
        else {
            return false;
        }
    }

    friend bool operator>(Datum const& d1, Datum const& d2)
    {
        if (d1.godina > d2.godina) {
            return true;
        }
        else if (d1.godina == d2.godina && d1.mjesec > d2.mjesec) {
            return true;
        }
        else if (d1.godina == d2.godina && d1.mjesec == d2.mjesec && d1.dan > d2.dan) {
            return true;
        }
        else {
            return false;
        }
    }

    friend bool operator>=(Datum const& d1, Datum const& d2)
    {
        if (d1.godina >= d2.godina) {
            return true;
        }
        else if (d1.godina == d2.godina && d1.mjesec >= d2.mjesec) {
            return true;
        }
        else if (d1.godina == d2.godina && d1.mjesec == d2.mjesec && d1.dan >= d2.dan) {
            return true;
        }
        else {
            return false;
        }
    }

    friend bool operator<=(Datum const& d1, Datum const& d2)
    {
        if (d1.godina <= d2.godina) {
            return true;
        }
        else if (d1.godina == d2.godina && d1.mjesec <= d2.mjesec) {
            return true;
        }
        else if (d1.godina == d2.godina && d1.mjesec == d2.mjesec && d1.dan <= d2.dan) {
            return true;
        }
        else {
            return false;
        }
    }
};

struct Clan
{
    string ime = ""; //Ime clana
    string prezime = ""; //Prezime clana
    int broj_clana = 0; //Broj clana
    bool aktivan; //Da li je clan aktivan?
    Datum trajanje_clanarine;

    //Konstruktor strukture Clan, poziva se na stvaranje svake nove instance clana
    Clan(string ime, string prezime, int broj_clana, bool aktivan, Datum trajanje_clanarine) : ime(ime), prezime(prezime), broj_clana(broj_clana), aktivan(aktivan), trajanje_clanarine(trajanje_clanarine) {}
};

class Teretana
{
private:

    string ime = ""; //Ime teretane
    string adresa = ""; //Adresa teretane
    vector<Clan> popis_clanova; //Popis clanova teretane

public:

    //Konstruktor za klasu teretana
    Teretana(string ime, string adresa) : ime(ime), adresa(adresa) {}

    //Pomocna metoda za ucitavanje clanova iz datoteke
    void ucitajClana(string ime, string prezime, int broj_clana, bool aktivan, string s)
    {
        int i;
        for (i = 0; i < s.length(); i++) if (s[i] == '/') break;
        int dan = stoi(s.substr(0, i)); //Dan
        s = s.substr(i + 1, s.length());

        for (i = 0; i < s.length(); i++) if (s[i] == '/') break;
        int mjesec = stoi(s.substr(0, i)); //Mjesec
        s = s.substr(i + 1, s.length());

        for (i = 0; i < s.length(); i++) if (s[i] == ';') break;
        int godina = stoi(s.substr(0, i)); //Godina

        Datum trajanje_clanarine = Datum(dan, mjesec, godina);

        Clan c = Clan(ime, prezime, broj_clana, aktivan, trajanje_clanarine);
        popis_clanova.push_back(c);
    }

    //Unos novog clana teretane
    void unesiClana()
    {

        string ime = "";
        string prezime = "";
        int broj_clana = 0;
        bool aktivan;
        int dan = 0, mjesec = 0, godina = 0;

        cout << "\nUnesite podatke o novom clanu teretane: " << endl;
        cout << "Ime: ";
        cin >> ime;
        cout << "Prezime: ";
        cin >> prezime;
        cout << "ID: ";
        cin >> broj_clana;
        cout << "Aktivan: ";
        cin >> aktivan;
        cout << "== Trajanje clanarine ==\nUnesite dan: ";
        cin >> dan;
        cout << "Unesite mjesec: ";
        cin >> mjesec;
        cout << "Unesite godinu: ";
        cin >> godina;
        Datum trajanje_clanarine = Datum(dan, mjesec, godina);
        Clan noviClan = Clan(ime, prezime, broj_clana, aktivan, trajanje_clanarine); //Nova instanca clana stvorena
        popis_clanova.push_back(noviClan); //Spremanje novostvorenog clana u vektor popis_clanova
        cout << trajanje_clanarine.getDan() << "/" << trajanje_clanarine.getMjesec() << "/" << trajanje_clanarine.getGodina();
        //Azuriranje datoteke clanovi.txt
        azurirajClanoveFile(popis_clanova);
    }

    //Dohvacanje velicine privatnog atributa (ujedino i vektora) popis_clanova
    int BrojClanova()
    {
        return popis_clanova.size();
    }

    //Brisanje postojeceg clana teretane preko njegovog identifikacijskog broja (broj_clana)
    void obrisiClana(int broj_clana) {

        //Trazenje clana u vektoru sekvencijalno (po redu)
        for (int i = 0; i < popis_clanova.size(); i++) {

            //Usporedujemo i ako je pronaden clan, obrisemo ga
            if (popis_clanova[i].broj_clana == broj_clana) {
                popis_clanova.erase(popis_clanova.begin() + i);
            }
        }

        azurirajClanoveFile(popis_clanova);
    }

    //Ispisivanje podataka o teretani
    void ispisiPodatke()
    {
        cout << "\nClanovi teretane:" << endl;
        cout << "\n===" << endl;
        for (const auto& clan : popis_clanova) {
            cout << "Ime: " << clan.ime << endl;
            cout << "Prezime: " << clan.prezime << endl;
            cout << "ID: " << clan.broj_clana << endl;
            cout << "Aktivan: " << clan.aktivan << endl;
            //cout << "Datum uclanjenja: " << clan.datum_uclanjenja << endl;
            cout << "====" << endl;
        }
    }

    //Ispisi clanove kojima je istekla clanarina
    void ispisiIstekleClanarine() {
        //Trenutni datum
        time_t now = time(0);
        tm* ltm = localtime(&now);
        int trenutni_dan = ltm->tm_mday;
        int trenutni_mjesec = ltm->tm_mon + 1;
        int trenutna_godina = ltm->tm_year + 1900;
        Datum trenutni_datum = Datum(trenutni_dan, trenutni_mjesec, trenutna_godina);
        for (auto& clan : popis_clanova) {
            if (clan.trajanje_clanarine < trenutni_datum) {
                cout << "Ime: " << clan.ime << endl;
                cout << "Prezime: " << clan.prezime << endl;
                cout << "ID: " << clan.broj_clana << endl;
                cout << "Aktivan: " << clan.aktivan << endl;
                cout << "Clanarina trajala do: " << clan.trajanje_clanarine.getDan() << "/" << clan.trajanje_clanarine.getMjesec() << "/" << clan.trajanje_clanarine.getGodina() << endl;
                cout << "====" << endl;
            }
        }
    }

    //Azuriranje datoteke popis clanova
    void azurirajClanoveFile(vector<Clan> popis_clanova)
    {
        ofstream f;
        f.open("clanovi.txt");
        for (auto& clan : popis_clanova) {
            f << clan.ime << ";" << clan.prezime << ";" << clan.broj_clana << ";" << clan.aktivan << ";" << clan.trajanje_clanarine.getDan() << "/" << clan.trajanje_clanarine.getMjesec() << "/" << clan.trajanje_clanarine.getGodina() << ";" << endl;
        }
        f.close();
    }

    void menu()
    {
        Teretana teretana1 = Teretana("Fit4Life", "UL. Kralja Tomislava 111, 51260 Crikvenica, Primorsko-goranska, Hrvatska");

        //Ucitavanje postojecih clanova iz datoteke clanovi.txt
        fstream checkFile;
        checkFile.open("clanovi.txt", ios::in);
        int opened = checkFile.fail();
        checkFile.close();

        if (!opened) { //Postoji li datoteka
            ifstream f;
            string line = "", ime = "", prezime = "", trajanje_clanarine = "";
            int broj_clana = 0;
            bool aktivan = false;
            int i = 0;
            f.open("clanovi.txt");
            while (!f.eof()) {
                getline(f, line);

                //Izvlacenje podataka iz linije u varijable
                for (i = 0; i < line.length(); i++) if (line[i] == ';') break;
                ime = line.substr(0, i); //Ime
                line = line.substr(i + 1, line.length());

                for (i = 0; i < line.length(); i++) if (line[i] == ';') break;
                prezime = line.substr(0, i); //Prezime
                line = line.substr(i + 1, line.length());

                for (i = 0; i < line.length(); i++) if (line[i] == ';') break;
                broj_clana = stoi(line.substr(0, i)); //Broj clana
                line = line.substr(i + 1, line.length());

                for (i = 0; i < line.length(); i++) if (line[i] == ';') break;
                aktivan = stoi(line.substr(0, i)); //Aktivan
                line = line.substr(i + 1, line.length());

                for (i = 0; i < line.length(); i++) if (line[i] == ';') break;
                trajanje_clanarine = line.substr(0, i); //Trajanje clanarine

                teretana1.ucitajClana(ime, prezime, broj_clana, aktivan, trajanje_clanarine);

                f.ignore();
            }
            f.close();
        }
        char odabir;

        do
        {
            cout << "\n\n========== Teretana Fit4Life ==========" << endl;
            cout << "\nOdaberite sto zelite uciniti: " << endl;
            cout << "[1] Dodavanje novog clana" << endl;
            cout << "[2] Brisanje clana" << endl;
            cout << "[3] Ispis svih clanova" << endl;
            cout << "[4] Ispis clanova kojima je istekla clanarina" << endl;
            cout << "[5] Izlaz" << endl;
            cout << "\nVas odabir: ";
            cin >> odabir;

            switch (odabir)
            {
            case '1':
                teretana1.unesiClana();
                break;

            case '2':
                if (teretana1.BrojClanova() == 0)
                {
                    cout << "\nTeretana trenutno nema clanova. Unesite clana da biste ga mogli izbrisati.";
                }
                else
                {
                    int broj_clana = 0;
                    cout << "\nOdabrali ste brisanje clana. \nUnesite ID broj clana kojeg zelite brisati: ";
                    cin >> broj_clana;
                    teretana1.obrisiClana(broj_clana);
                    cout << "Obrisan je clan s identifikacijskim brojem " << broj_clana << ".";
                }
                break;

            case '3':
                if (teretana1.BrojClanova() == 0)
                {
                    cout << "\nTeretana trenutno nema clanova. Unesite clana da bi se prikazao.";
                }
                else
                {
                    cout << "\nOdabrali ste ispis svih clanova teretane.";
                    teretana1.ispisiPodatke();
                }
                break;

            case '4':
                if (teretana1.BrojClanova() == 0)
                {
                    cout << "\nTeretana trenutno nema clanova. Unesite clana da bi se prikazao.";
                }
                else
                {
                    cout << "\nClanovi kojima je istekla clanarina:\n" << endl;
                    teretana1.ispisiIstekleClanarine();
                }
                break;

            case '5':
                exit(0);
                break;

            default:
                cout << "\nPogresan unos. Pokusajte ponovo.";
                cout << "Vas odabir: ";
                cin >> odabir;
                break;
            }
        } while (odabir >= 1 || odabir <= 4);

    }
};

int main()
{
    Teretana teretana1 = Teretana("Fit4Life", "UL. Kralja Tomislava 111, 51260 Crikvenica, Primorsko-goranska, Hrvatska");
    teretana1.menu();

    return 0;
}