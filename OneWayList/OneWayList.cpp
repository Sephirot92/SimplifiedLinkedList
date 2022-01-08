#include <iostream>
#include <sstream>
using namespace std;

struct Osoba {
    string imie = "", nazwisko = "";
    int wiek;
    struct Osoba* next = nullptr;
};

bool isNullOrEmpty(Osoba* osoba) {
    if (osoba != nullptr && (osoba->imie._Equal("") || osoba->nazwisko._Equal(""))) {
        return true;
    }
    return false;
}

string getStringData(string typeOfData) {
    bool isCorrectDataFormat = true;
    string stringData;
    cin.exceptions(istream::failbit);


    do {
        try {
            cout << "Prosze podac " << typeOfData << endl;
            cin >> stringData;
            isCorrectDataFormat = true;
        }
        catch (ios_base::failure& fail) {
            isCorrectDataFormat = false;
            cout << "Prosze podac " << typeOfData << ". Nalezy podac ciag znakow (liter)" << endl;
            cin.clear();
            string tmp;
            getline(cin, tmp);
        }
    } while (isCorrectDataFormat == false);

    return stringData;
}

//This method retrieves integers and catches possible errors
int getIntegerData(string typeOfData) {
    bool isCorrectDataFormat = true;
    int intData;
    cin.exceptions(istream::failbit);


    do {
        try {
            cout << "Prosze podac " << typeOfData << endl;
            cin >> intData;
            isCorrectDataFormat = true;
        }
        catch (ios_base::failure& fail) {
            isCorrectDataFormat = false;
            cout << ". Nalezy podac liczbe/liczby" << endl;
            cin.clear();
            string tmp;
            getline(cin, tmp);
        }
    } while (isCorrectDataFormat == false);

    return intData;
}

//This method adds new person to the list. 
void addNewPerson(Osoba* osoba) {
    string name, surname;
    int age;

    name = getStringData("imie");

    surname = getStringData("nazwisko");

    age = getIntegerData("wiek");

    Osoba* newPerson = new Osoba;
    newPerson->imie = name;
    newPerson->nazwisko = surname;
    newPerson->wiek = age;
    newPerson->next = NULL;

    if (isNullOrEmpty(osoba)) {
        *osoba = *newPerson;
    }
    else {
        Osoba* previousTemporary = osoba;

        while (previousTemporary->next != NULL) {
            previousTemporary = previousTemporary->next;
        }
        previousTemporary->next = newPerson;
    }
}

void showAllPersons(Osoba* osoba) {
    if (isNullOrEmpty(osoba)) {
        cout << "Lista jest pusta" << endl << endl;
        return;
    }
    else {
        Osoba* iterationPerson = osoba;
        int counter = 1;
        while (iterationPerson != nullptr) {
            cout << counter << ". " << iterationPerson->imie << " " << iterationPerson->nazwisko << " " << iterationPerson->wiek << endl;
            counter++;
            if (!isNullOrEmpty(iterationPerson->next)) {
                iterationPerson = iterationPerson->next;
            }
        }
    }
}

void searchForPersonBySurname(Osoba* osoba) {
    string personSurname;

    cout << endl <<"==== Wyszukiwanie osoby po nazwisku ====" << endl;
    personSurname = getStringData("nazwisko");

    if (isNullOrEmpty(osoba)) {
        cout << endl << "Lista jest pusta" << endl;
        return;
    }
    else {
        Osoba* iterationPerson = osoba;
        int counter = 1;
        while (iterationPerson != nullptr) {
            if (personSurname._Equal(iterationPerson->nazwisko)) {
                cout << counter << ". " << iterationPerson->imie << " " << iterationPerson->nazwisko << " " << iterationPerson->wiek << endl;
            }
            counter++;
            if (!isNullOrEmpty(iterationPerson->next)) {
                iterationPerson = iterationPerson->next;
            }
        }
    }
}

void deletePersonById(Osoba* osoba) {
    int personNumberToBeDeleted;
    cout << "Podaj numer osoby do usuniecia \n";
    cin >> personNumberToBeDeleted;

    if (isNullOrEmpty(osoba)) {
        cout << endl << "Nie znaleziono osob na liscie" << endl;
        return;
    }
    else {
        Osoba* personOne = osoba;
        Osoba* personTwo = osoba;
        for (int i = 1; ; i++) {
            if (personNumberToBeDeleted == i) {
                if (personNumberToBeDeleted == 1) {
                    if (osoba->next != NULL) {
                        *osoba = *(osoba->next);
                    }
                    else {
                        *osoba = *(new Osoba);
                    }
                    break;
                }
                else {
                    personOne->next = personTwo->next;
                    break;
                }
            }
            else {
                if (personTwo->next != nullptr) {
                    personOne = personTwo;
                    personTwo = personTwo->next;
                }
                else {
                    cout << endl << "Podano numer spoza zakresu listy" << endl;
                }
            }
        }
    }
}

void showInstructions() {
    cout << endl << "Prosze wybierz opcje od 1 do 5." << endl;
    cout << "1. Dodaj osobe do listy" << endl;
    cout << "2. Usun osobe podajac jej numer" << endl;
    cout << "3. Wypisz wszystkie dostepne osoby" << endl;
    cout << "4. Szukaj osoby po nazwisku" << endl;
    cout << "5. Zakoncz dzialanie programu" << endl;

}

void chooseMenuOption(int activity, Osoba* firstPerson, bool *isActive) {
    switch (activity) {
        case 1:
            addNewPerson(firstPerson);
            break;
        case 2:
            deletePersonById(firstPerson);
            break;
        case 3:
            showAllPersons(firstPerson);
            break;
        case 4:
            searchForPersonBySurname(firstPerson);
            break;
        case 5:
            *isActive = false;
            cout << "Program konczy swoja dzialalnosc" << endl;
            break;
        default:
            cout << "Wybrano niepoprawny numer, prosze wybierz ponownie" << endl;
    }
}

int main()
{
    Osoba firstPerson;
    Osoba* p_pointerToFirstPerson = &firstPerson;
    bool isActive = true;
    bool* p_isActve = &isActive;
    bool isCorrectDataFormat = true;
    int activity;


    while (isActive)
    {
        cin.exceptions(istream::failbit);

        do {
            try {
                showInstructions();
                cin >> activity;
                isCorrectDataFormat = true;
            }
            catch (ios_base::failure& fail) {
                isCorrectDataFormat = false;
                cout << "Prosze podac liczbe odpowiadajaca pozycji z menu." << endl;
                cin.clear();
                string tmp;
                getline(cin, tmp);
            }
        } while (isCorrectDataFormat == false);
        chooseMenuOption(activity, p_pointerToFirstPerson, p_isActve);
    }
}