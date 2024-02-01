#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

struct Czytelnik {
    string id;
    string imie;
    string nazwisko;
};

struct Ksiazka {
    string id;
    string tytul;
    string autor;
};

struct Wypozyczenie {
    string idCzytelnika;
    string idKsiazki;
};

vector<Czytelnik> czytelnicy;
vector<Ksiazka> ksiazki;
vector<Wypozyczenie> wypozyczenia;

// Funkcje do obsługi czytelników
void dodajCzytelnika() {
    Czytelnik nowyCzytelnik;
    cout << "Podaj imie czytelnika: ";
    cin >> nowyCzytelnik.imie;
    cout << "Podaj nazwisko czytelnika: ";
    cin >> nowyCzytelnik.nazwisko;

    // Generowanie ID
    nowyCzytelnik.id = to_string(czytelnicy.size() + 1);

    czytelnicy.push_back(nowyCzytelnik);
}

void wyszukajCzytelnika() {
    string szukaneImie, szukaneNazwisko;
    cout << "Podaj imie czytelnika do wyszukania: ";
    cin >> szukaneImie;
    cout << "Podaj nazwisko czytelnika do wyszukania: ";
    cin >> szukaneNazwisko;

    auto it = find_if(czytelnicy.begin(), czytelnicy.end(), [szukaneImie, szukaneNazwisko](const Czytelnik& c) {
        return c.imie == szukaneImie && c.nazwisko == szukaneNazwisko;
        });

    if (it != czytelnicy.end()) {
        cout << "Znaleziono czytelnika. ID: " << it->id << ", Imie: " << it->imie << ", Nazwisko: " << it->nazwisko << endl;
    }
    else {
        cout << "Nie znaleziono czytelnika." << endl;
    }
}

void edytujCzytelnika() {
    string idCzytelnika;
    cout << "Podaj ID czytelnika do edycji: ";
    cin >> idCzytelnika;

    auto it = find_if(czytelnicy.begin(), czytelnicy.end(), [idCzytelnika](const Czytelnik& c) {
        return c.id == idCzytelnika;
        });

    if (it != czytelnicy.end()) {
        cout << "Podaj nowe imie czytelnika: ";
        cin >> it->imie;
        cout << "Podaj nowe nazwisko czytelnika: ";
        cin >> it->nazwisko;
        cout << "Edycja czytelnika zakonczona pomyslnie." << endl;
    }
    else {
        cout << "Nie znaleziono czytelnika." << endl;
    }
}

void usunCzytelnika() {
    string idCzytelnika;
    cout << "Podaj ID czytelnika do usuniecia: ";
    cin >> idCzytelnika;

    auto it = find_if(czytelnicy.begin(), czytelnicy.end(), [idCzytelnika](const Czytelnik& c) {
        return c.id == idCzytelnika;
        });

    if (it != czytelnicy.end()) {
        czytelnicy.erase(it);
        cout << "Czytelnik usuniety pomyslnie." << endl;
    }
    else {
        cout << "Nie znaleziono czytelnika." << endl;
    }
}

// Funkcje do obsługi książek
void dodajKsiazke() {
    Ksiazka nowaKsiazka;
    cout << "Podaj tytul ksiazki: ";
    cin.ignore();
    getline(cin, nowaKsiazka.tytul);
    cout << "Podaj autora ksiazki: ";
    getline(cin, nowaKsiazka.autor);

    // Generowanie unikalnego ID
    nowaKsiazka.id = to_string(ksiazki.size() + 1);

    ksiazki.push_back(nowaKsiazka);
}

void wyszukajKsiazke() {
    string szukanyTytul, szukanyAutor;
    cout << "Podaj tytul ksiazki do wyszukania: ";
    cin.ignore();
    getline(cin, szukanyTytul);
    cout << "Podaj autora ksiazki do wyszukania: ";
    getline(cin, szukanyAutor);

    auto it = find_if(ksiazki.begin(), ksiazki.end(), [szukanyTytul, szukanyAutor](const Ksiazka& k) {
        return k.tytul == szukanyTytul && k.autor == szukanyAutor;
        });

    if (it != ksiazki.end()) {
        cout << "Znaleziono ksiazke. ID: " << it->id << ", Tytul: " << it->tytul << ", Autor: " << it->autor << endl;
    }
    else {
        cout << "Nie znaleziono ksiazki." << endl;
    }
}

void edytujKsiazke() {
    string idKsiazki;
    cout << "Podaj ID ksiazki do edycji: ";
    cin >> idKsiazki;

    auto it = find_if(ksiazki.begin(), ksiazki.end(), [idKsiazki](const Ksiazka& k) {
        return k.id == idKsiazki;
        });

    if (it != ksiazki.end()) {
        cout << "Podaj nowy tytul ksiazki: ";
        cin.ignore();
        getline(cin, it->tytul);
        cout << "Podaj nowego autora ksiazki: ";
        getline(cin, it->autor);
        cout << "Edycja ksiazki zakonczona pomyslnie." << endl;
    }
    else {
        cout << "Nie znaleziono ksiazki." << endl;
    }
}

void usunKsiazke() {
    string idKsiazki;
    cout << "Podaj ID ksiazki do usuniecia: ";
    cin >> idKsiazki;

    auto it = find_if(ksiazki.begin(), ksiazki.end(), [idKsiazki](const Ksiazka& k) {
        return k.id == idKsiazki;
        });

    if (it != ksiazki.end()) {
        ksiazki.erase(it);
        cout << "Ksiazka usunieta pomyslnie." << endl;
    }
    else {
        cout << "Nie znaleziono ksiazki." << endl;
    }
}

// Funkcje do obsługi wypożyczeń
void wypozyczKsiazke() {
    string idCzytelnika, idKsiazki;
    cout << "Podaj ID czytelnika: ";
    cin >> idCzytelnika;
    cout << "Podaj ID ksiazki: ";
    cin >> idKsiazki;

    Wypozyczenie noweWypozyczenie = { idCzytelnika, idKsiazki };
    wypozyczenia.push_back(noweWypozyczenie);
}

void oddajKsiazke() {
    string idCzytelnika, idKsiazki;
    cout << "Podaj ID czytelnika: ";
    cin >> idCzytelnika;
    cout << "Podaj ID ksiazki: ";
    cin >> idKsiazki;

    auto it = find_if(wypozyczenia.begin(), wypozyczenia.end(), [idCzytelnika, idKsiazki](const Wypozyczenie& w) {
        return w.idCzytelnika == idCzytelnika && w.idKsiazki == idKsiazki;
        });

    if (it != wypozyczenia.end()) {
        wypozyczenia.erase(it);
        cout << "Ksiazka oddana pomyslnie." << endl;
    }
    else {
        cout << "Nie znaleziono wypożyczenia." << endl;
    }
}

// Funkcje do zapisu do plików
void zapiszCzytelnikowDoPliku() {
    ofstream plik("c.txt");

    for (const auto& czytelnik : czytelnicy) {
        plik << czytelnik.id << "|" << czytelnik.imie << "|" << czytelnik.nazwisko << "\n";
    }

    plik.close();
}

void zapiszKsiazkiDoPliku() {
    ofstream plik("k.txt");

    for (const auto& ksiazka : ksiazki) {
        plik << ksiazka.id << "|" << ksiazka.tytul << "|" << ksiazka.autor << "\n";
    }

    plik.close();
}

void zapiszWypozyczeniaDoPliku() {
    ofstream plik("w.txt");

    for (const auto& wypozyczenie : wypozyczenia) {
        plik << wypozyczenie.idCzytelnika << "|" << wypozyczenie.idKsiazki << "\n";
    }

    plik.close();
}

int main(int argc, char* argv[]) {
    string plikCzytelnikow = "c.txt";
    string plikKsiazek = "k.txt";
    string plikWypozyczen = "w.txt";

    // Obsługa przełączników z linii poleceń
    for (int i = 1; i < argc; i += 2) {
        string option = argv[i];
        if (option == "-c") {
            plikCzytelnikow = argv[i + 1];
        }
        else if (option == "-k") {
            plikKsiazek = argv[i + 1];
        }
        else if (option == "-w") {
            plikWypozyczen = argv[i + 1];
        }
        else {
            cout << "Nieprawidlowy argument: " << option << "\n";
            return 1;
        }
    }

    // Wczytaj dane z plików przy starcie programu
    ifstream czytelnicyFile("c.txt");
    if (czytelnicyFile.is_open()) {
        Czytelnik czytelnik;
        while (getline(czytelnicyFile, czytelnik.id, '|') && getline(czytelnicyFile, czytelnik.imie, '|') && getline(czytelnicyFile, czytelnik.nazwisko)) {
            czytelnicy.push_back(czytelnik);
        }
        czytelnicyFile.close();
    }

    ifstream ksiazkiFile("k.txt");
    if (ksiazkiFile.is_open()) {
        Ksiazka ksiazka;
        while (getline(ksiazkiFile, ksiazka.id, '|') && getline(ksiazkiFile, ksiazka.tytul, '|') && getline(ksiazkiFile, ksiazka.autor)) {
            ksiazki.push_back(ksiazka);
        }
        ksiazkiFile.close();
    }

    ifstream wypozyczeniaFile("w.txt");
    if (wypozyczeniaFile.is_open()) {
        Wypozyczenie wypozyczenie;
        while (getline(wypozyczeniaFile, wypozyczenie.idCzytelnika, '|') && getline(wypozyczeniaFile, wypozyczenie.idKsiazki)) {
            wypozyczenia.push_back(wypozyczenie);
        }
        wypozyczeniaFile.close();
    }

    // Menu główne
    int wybor;
    do {
        cout << "Menu: \n";
        cout << "1.  Dodaj czytelnika\n";
        cout << "2.  Wyszukaj czytelnika\n";
        cout << "3.  Edytuj czytelnika\n";
        cout << "4.  Usun czytelnika\n";

        cout << "5.  Dodaj ksiazke\n";
        cout << "6.  Wyszukaj ksiazke\n";
        cout << "7.  Edytuj ksiazke\n";
        cout << "8.  Usun ksiazke\n";

        cout << "9.  Wypozycz ksiazke\n";
        cout << "10. Oddaj ksiazke\n";
        cout << "11. Zakoncz program\n";
        cout << "Wybierz opcje: ";
        cin >> wybor;

        switch (wybor) {
        case 1:
            dodajCzytelnika();
            break;
        case 2:
            wyszukajCzytelnika();
            break;
        case 3:
            edytujCzytelnika();
            break;
        case 4:
            usunCzytelnika();
            break;
        case 5:
            dodajKsiazke();
            break;
        case 6:
            wyszukajKsiazke();
            break;
        case 7:
            edytujKsiazke();
            break;
        case 8:
            usunKsiazke();
            break;
        case 9:
            wypozyczKsiazke();
            break;
        case 10:
            oddajKsiazke();
            break;
        case 11:
            // Zapisz dane do plików przed zakończeniem programu
            zapiszCzytelnikowDoPliku();
            zapiszKsiazkiDoPliku();
            zapiszWypozyczeniaDoPliku();
            cout << "Dziekujemy za skorzystanie z programu. Do widzenia!\n";
            break;
        default:
            cout << "Nieprawidlowy wybor. Sprobuj ponownie.\n";
            break;
        }
    } while (wybor != 11);

    return 0;
}
