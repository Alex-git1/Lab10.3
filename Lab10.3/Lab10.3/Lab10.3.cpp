#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>

using namespace std;

struct Note {
    string surname;
    string name;
    string phone;
    int birthdate[3]; 
};

void displayMenu() {
    cout << "\n--- Меню ---\n";
    cout << "1. Додати дані про людину\n";
    cout << "2. Відсортувати за прізвищем\n";
    cout << "3. Показати людей, народжених у заданому місяці\n";
    cout << "4. Зберегти дані у файл\n";
    cout << "5. Зчитати дані з файлу\n";
    cout << "6. Вийти\n";
    cout << "Виберіть опцію: ";
}

void addPerson(Note*& people, int& size) {
    Note newPerson;
    cout << "Введіть прізвище: ";
    cin >> newPerson.surname;
    cout << "Введіть ім'я: ";
    cin >> newPerson.name;
    cout << "Введіть номер телефону: ";
    cin >> newPerson.phone;
    cout << "Введіть дату народження (день, місяць, рік): ";
    cin >> newPerson.birthdate[0] >> newPerson.birthdate[1] >> newPerson.birthdate[2];

    Note* temp = new Note[size + 1];
    for (int i = 0; i < size; ++i) {
        temp[i] = people[i];
    }
    temp[size] = newPerson;
    delete[] people;
    people = temp;
    size++;
}

void sortBySurname(Note* people, int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if (people[i].surname > people[j].surname) {
                Note temp = people[i];
                people[i] = people[j];
                people[j] = temp;
            }
        }
    }
    cout << "Масив відсортовано за прізвищем.\n";
}

void displayByMonth(Note* people, int size, int month) {
    bool found = false;
    for (int i = 0; i < size; ++i) {
        if (people[i].birthdate[1] == month) {
            cout << "Прізвище: " << people[i].surname
                << ", Ім'я: " << people[i].name
                << ", Номер телефону: " << people[i].phone
                << ", Дата народження: " << people[i].birthdate[0] << "."
                << people[i].birthdate[1] << "." << people[i].birthdate[2] << "\n";
            found = true;
        }
    }
    if (!found) {
        cout << "Немає людей, народжених у цьому місяці.\n";
    }
}

void saveToFile(Note* people, int size, const string& filename) {
    ofstream file(filename);
    if (!file) {
        cout << "Помилка відкриття файлу для запису.\n";
        return;
    }
    for (int i = 0; i < size; ++i) {
        file << people[i].surname << " "
            << people[i].name << " "
            << people[i].phone << " "
            << people[i].birthdate[0] << " "
            << people[i].birthdate[1] << " "
            << people[i].birthdate[2] << "\n";
    }
    file.close();
    cout << "Дані збережено у файл.\n";
}

void loadFromFile(Note*& people, int& size, const string& filename) {
    ifstream file(filename);
    if (!file) {
        cout << "Помилка відкриття файлу для зчитування.\n";
        return;
    }
    size = 0;
    Note temp[100];
    while (file >> temp[size].surname >> temp[size].name >> temp[size].phone
        >> temp[size].birthdate[0] >> temp[size].birthdate[1] >> temp[size].birthdate[2]) {
        size++;
    }
    delete[] people;
    people = new Note[size];
    for (int i = 0; i < size; ++i) {
        people[i] = temp[i];
    }
    file.close();
    cout << "Дані зчитано з файлу.\n";
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Note* people = nullptr;
    int size = 0;
    bool running = true;

    while (running) {
        displayMenu();
        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            addPerson(people, size);
            break;
        case 2:
            sortBySurname(people, size);
            break;
        case 3: {
            int month;
            cout << "Введіть номер місяця: ";
            cin >> month;
            if (month >= 1 && month <= 12) {
                displayByMonth(people, size, month);
            }
            else {
                cout << "Невірний місяць. Спробуйте ще раз.\n";
            }
            break;
        }
        case 4: {
            string filename;
            cout << "Введіть ім'я файлу для збереження: ";
            cin >> filename;
            saveToFile(people, size, filename);
            break;
        }
        case 5: {
            string filename;
            cout << "Введіть ім'я файлу для зчитування: ";
            cin >> filename;
            loadFromFile(people, size, filename);
            break;
        }
        case 6:
            running = false;
            break;
        default:
            cout << "Невірний вибір. Спробуйте ще раз.\n";
        }
    }

    delete[] people;
    return 0;
}
