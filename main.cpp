#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <limits>
#include <ctime>

using namespace std;

class HistoricalFigure {
public:
    // Конструкторы и деструктор
    HistoricalFigure();
    HistoricalFigure(int newId, string newName, string newCountry, string newContribution, int newCentury, float newScore);
    ~HistoricalFigure();
    // Методы доступа и установки значений
    int getId();
    void setId(int newId);
    std::string getFio();
    void setFio(std::string newName);
    string getCountry();
    void setCountry(string newCountry);
    string getContribution();
    void setContribution(string newContribution);
    int getCentury();
    void setCentury(int newCentury);
    float getScore();
    void setScore(float newScore);
    bool readDataFromFile(const string &filename);
private:
    int id;
    string fio;
    string country;
    string contribution;
    int century;
    float score;
};


string center(const string& text, int width) {
    int padding = width - text.size();
    int padLeft = padding / 2;
    int padRight = padding - padLeft;
    return (string(padLeft, ' ') + text + string(padRight, ' '));
}
void push_back(HistoricalFigure figure, int& arraySize, int& arrayCapacity, HistoricalFigure*& figures) {
    // Увеличиваем ёмкость, если массив полон или ещё не инициализирован
    if (arraySize >= arrayCapacity) {
        arrayCapacity = (arrayCapacity == 0) ? 1 : arrayCapacity * 2;
        HistoricalFigure* newFigures = new HistoricalFigure[arrayCapacity];
        for (int i = 0; i < arraySize; i++) {
            newFigures[i] = figures[i];
        }
        delete[] figures;
        figures = newFigures;
    }
    figures[arraySize++] = figure;
}


// Функция для чтения данных из файла
bool readDataFromFile(const string &filename, int& arraySize, int& arrayCapacity, HistoricalFigure*& figures) {
    ifstream file(filename);
    if (!file) {
        cerr << "Ошибка открытия файла: " << filename << endl;
        do {
            cout << '\n' << "Press the Enter key to continue.";
        } while (cin.get() != '\n');
        return false;
    }
    int iBuf;
    string sBuf;
    float fBuf;
    HistoricalFigure figure;
    while (file >> iBuf) {
        figure.setId(iBuf);
        file.ignore();
        getline(file, sBuf);
        figure.setFio(sBuf);
        getline(file, sBuf);
        figure.setCountry(sBuf);
        getline(file, sBuf);
        figure.setContribution(sBuf);
        file.ignore();
        file >> iBuf;
        figure.setCentury(iBuf);
        file >> fBuf;
        figure.setScore(fBuf);
        push_back(figure, arraySize, arrayCapacity, figures);
    }
    file.close();
    return true;
}

// Функция для отображения данных
void displayData(HistoricalFigure*& figures, int& arraySize) {
    system("clear");
    int widths[6] = {5, 50, 25, 25, 25, 25};
    cout << "+";
    for (const auto& width : widths) {
        cout << setfill('-') << setw(width) << "" << "+";
    }
    cout << setfill(' ') << "\n";
    string headers[6] = {"ID", "FIO", "Country", "Contribution", "Century", "Score"};
    cout << "|";
    for (size_t i = 0; i < 6; i++) {
        cout << center(headers[i], widths[i]) << "|";
    }
    cout << "\n";

    cout << "+";
    for (const auto& width : widths) {
        cout << setfill('-') << setw(width) << "" << "+";
    }
    cout << setfill(' ') << "\n";
    for (int i = 0; i < arraySize; i++) {
        cout << "|";
        cout << center(to_string(figures[i].getId()), widths[0]) << "|"
             << center(figures[i].getFio(), widths[1]) << "|"
             << center(figures[i].getCountry(), widths[2]) << "|"
             << center(figures[i].getContribution(), widths[3]) << "|"
             << center(to_string(figures[i].getCentury()), widths[4]) << "|"
             << center(to_string(figures[i].getScore()), widths[5]) << "|\n";
        cout << "+";
        for (const auto& width : widths) {
            cout << setfill('-') << setw(width) << "" << "+";
        }
        cout << setfill(' ') << "\n";
    }

    do {

    } while (cin.get() != '\n');
}

// Функция для редактирования данных
void editData(int id, HistoricalFigure*& figures, int& arraySize) {
    bool isEnd1 = false;
    bool isEnd2 = false;
    int countSuccess = 0;

    system("clear");
    for (int i = 0; i < arraySize; i++) {
        countSuccess = 0;
        int iBuf;
        string sBuf;
        float fBuf;
        if (figures[i].getId() == id) {
            system("clear");
            cout << "Введите новое имя: ";
            getline(cin, sBuf);
            figures[i].setFio(sBuf);
            system("clear");
            cout << "Введите новую страну: ";
            getline(cin, sBuf);
            figures[i].setCountry(sBuf);
            system("clear");
            cout << "Введите новый вклад: ";
            system("clear");
            getline(cin, sBuf);
            figures[i].setContribution(sBuf);
            system("clear");
            while(!isEnd1) {
                system("clear");
                cout << "Введите новый век";
                cin >> iBuf;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    system("clear");
                    cout << "Некорректный ввод." << endl;
                    do {
                        cout << '\n' << "Press the Enter key to continue.";
                    } while (cin.get() != '\n');
                } else {
                    figures[i].setCentury(iBuf);
                    countSuccess++;
                    isEnd1 = true;
                }
            }
            while(!isEnd2) {
                system("clear");
                cout << "Введите новую оценку: ";
                cin >> fBuf;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    system("clear");
                    cout << "Некорректный ввод." << endl;
                    do {
                        cout << '\n' << "Press the Enter key to continue.";
                    } while (cin.get() != '\n');
                } else {
                    figures[i].setScore(fBuf);
                    countSuccess++;
                    isEnd2 = true;
                }
            }
            cin.ignore();
            if (countSuccess == 2) {
                return;
            }
        }
    }
    cout << "Запись с ID " << id << " не найдена." << endl;
    do {
        cout << '\n' << "Press the Enter key to continue.";
    } while (cin.get() != '\n');
}


// Функция для сохранения данных в новый файл
void saveDataToFile(const string &filename, HistoricalFigure*& figures, int& arraySize) {
    ofstream file(filename);
    if (!file) {
        system("clear");
        cerr << "Ошибка открытия файла для записи: " << filename << endl;
        do {
            cout << '\n' << "Press the Enter key to continue.";
        } while (cin.get() != '\n');
        return;
    }

    for (int i = 0; i < arraySize; i++) {
        HistoricalFigure figure = figures[i];
        file << figure.getId()<< endl << figure.getFio() << endl
             << figure.getCountry() << endl << figure.getContribution() << endl
             << figure.getCentury() << endl << figure.getScore() << endl;
    }
    file.close();
}

void push_back(HistoricalFigure& figure, HistoricalFigure*& figures, int& arraySize, int& arrayCapacity) {
    // Увеличиваем ёмкость, если массив полон или ещё не инициализирован
    if (arraySize >= arrayCapacity) {
        arrayCapacity = (arrayCapacity == 0) ? 1 : arrayCapacity * 2;
        HistoricalFigure* newFigures = new HistoricalFigure[arrayCapacity];
        for (int i = 0; i < arraySize; i++) {
            newFigures[i] = figures[i];
        }
        delete[] figures;
        figures = newFigures;
    }
    figures[arraySize++] = figure;
}


int main() {
    system("clear");
    string filename;
    bool isFile = false;
    int arraySize = 0;
    int arrayCapacity = 0;
    HistoricalFigure* figures = nullptr;
    while (!isFile) {
        cout << "Введите имя файла для чтения данных: ";
        cin >> filename;
        cin.ignore(); // очищаем буфер
        cout << filename << endl;
        if (readDataFromFile(filename, arraySize, arrayCapacity, figures)) {
            isFile = true;
        }
        system("clear");
    }

    int choice;


    while (true) {
        system("clear");
        cout << "\nМеню:\n";
        cout << "1. Просмотр данных\n";
        cout << "2. Редактирование данных\n";
        cout << "3. Сохранение данных в новый файл\n";
        cout << "0. Выход\n";
        cout << "Выберите действие: ";

        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("clear");
            cout << "Некорректный ввод." << endl;
            do {
                cout << '\n' << "Press the Enter key to continue.";
            } while (cin.get() != '\n');
            continue;
        }
        if (choice == 1) {
            displayData(figures, arraySize);
            do {
                cout << '\n' << "Press the Enter key to continue.";
            } while (cin.get() != '\n');
        } else if (choice == 2) {
            int id;
            system("clear");
            cout << "Введите ID исторической личности для редактирования: ";
            cin >> id;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                system("clear");
                cout << "Некорректный ввод." << endl;
                do {
                    cout << '\n' << "Press the Enter key to continue.";
                } while (cin.get() != '\n');
                continue;
            }
            cin.ignore(); // очищаем буфер
            editData(id, figures, arraySize);
            do {
                cout << '\n' << "Press the Enter key to continue.";
            } while (cin.get() != '\n');
        } else if (choice == 3) {
            string newFilename;
            system("clear");
            cout << "Введите имя нового файла: ";
            cin >> newFilename;
            cin.ignore();
            saveDataToFile(newFilename, figures, arraySize);
            do {
                cout << '\n' << "Press the Enter key to continue.";
            } while (cin.get() != '\n');
        } else if (choice == 0) {
            system("clear");
            cout << "Выход из программы." << endl;
            do {
                cout << '\n' << "Press the Enter key to continue.";
            } while (cin.get() != '\n');
            return 0;
        } else {
            cout << "Некорректный выбор. Пожалуйста, попробуйте еще раз." << endl;
            do {
                cout << '\n' << "Press the Enter key to continue.";
            } while (cin.get() != '\n');
        }
    }
    return 0;
}


// Определение методов
HistoricalFigure::HistoricalFigure() {
    fio = "Unknown";
}

HistoricalFigure::HistoricalFigure(int newId, string newName, string newCountry, string newContribution, int newCentury, float newScore) {
    id = newId;
    fio = newName;
    country = newCountry;
    contribution = newContribution;
    century = newCentury;
    score = newScore;
}

int HistoricalFigure::getId() {
    return id;
}

std::string HistoricalFigure::getFio() {
    return fio;
}

string HistoricalFigure::getCountry() {
    return country;
}

string HistoricalFigure::getContribution() {
    return contribution;
}

int HistoricalFigure::getCentury() {
    return century;
}

float HistoricalFigure::getScore() {
    return score;
}

void HistoricalFigure::setId(int newId) {
    id = newId;
}

void HistoricalFigure::setFio(std::string newName) {
    fio = newName;
}

void HistoricalFigure::setCountry(string newCountry) {
    country = newCountry;
}

void HistoricalFigure::setContribution(string newContribution) {
    contribution = newContribution;
}

void HistoricalFigure::setCentury(int newCentury) {
    century = newCentury;
}

void HistoricalFigure::setScore(float newScore) {
    score = newScore;
}

HistoricalFigure::~HistoricalFigure() {
}