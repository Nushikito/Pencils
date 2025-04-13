#include <iostream>
#include <ctime>
#include "myPatterns.h"

using namespace std;

class Pencils
{
public:
    Pencils() {};

    double lenght = 12.5;
    int cost;
    wstring doh;


    //Общие методы
    virtual double getLenght() { return lenght; }
    virtual wstring getDegreeOfHardness (wstring doh) { return doh; }
    virtual int getCost (int cost) { return cost; };

    virtual void message() { wcout << L"У вас есть упаковка черных карандашей! "; } //Метод для черных карандашей
    virtual void random() { srand(time(0)); int z = 0; for(int i = 0; i < 20; i++){ int rndm = rand()%10; if(rndm <= 5){z += 1;} } cout << z; } //Метод для белых карандашей
    virtual void coloredPencils() { wcout << L"Количество цветных карандашей: "; } //Метод для цветных карандашей

    virtual ~Pencils() { wcout << "Карандашей больше нет :(" << endl; };
};

class BlackPencils : public Pencils
{
public:
    BlackPencils() {};

    void message() { Pencils::message(); wcout << L"Давайте узнаем, какие они!" << endl; }
    wstring getDegreeOfHardness(wstring doh) { wcout << L"Их степень твердости: " << Pencils::getDegreeOfHardness(doh) << endl; return Pencils::getDegreeOfHardness(doh); }
    double getLenght() { wcout << L"Их длина: " << Pencils::getLenght() << endl; return Pencils::getLenght(); }
    int getCost(int cost) { wcout << L"Цена за штуку: " << Pencils::getCost(cost) << endl; return Pencils::getCost(cost); }

    ~BlackPencils() { wcout << L"Черных карандашей больше нет :(" << endl; };
};

class WhitePencils : public Pencils
{
public:
    WhitePencils() {};

    void random() { wcout << L"Ох, в упаковке есть сломанные карандаши: "; Pencils::random(); cout << endl; }
    wstring getDegreeOfHardness(wstring doh) { wcout << L"Их степень твердости: " << Pencils::getDegreeOfHardness(doh) << endl; return Pencils::getDegreeOfHardness(doh); }
    double getLenght() { wcout << L"Их длина: " << Pencils::getLenght() << endl; return Pencils::getLenght(); }
    int getCost(int cost) { wcout << L"Цена за штуку: " << Pencils::getCost(cost) << endl; return Pencils::getCost(cost); }

   ~WhitePencils() { wcout << L"Больше нет белых карандашей :(" << endl; };
};

class ColoredPencils : public Pencils
{
public:
    int numbers = 20;

    ColoredPencils() {};

    void coloredPencils() { Pencils::coloredPencils(); cout << numbers << endl; }
    wstring getDegreeOfHardness(wstring doh) { wcout << L"Их степень твердости: " << Pencils::getDegreeOfHardness(doh) << endl; return Pencils::getDegreeOfHardness(doh); }
    double getLenght() { wcout << L"Их длина: " << Pencils::getLenght() << endl; return Pencils::getLenght(); }
    int getCost(int cost) { wcout << L"Цена за штуку: " << Pencils::getCost(cost) << endl; return Pencils::getCost(cost); }

    ~ColoredPencils() { wcout << L"Цветных карандашей больше нет :(" << endl; };
};

Pencils *createPencils(int a, wstring b, int c)
{
    Pencils *newPencils = nullptr;

    if (a == 1) { newPencils = new BlackPencils; newPencils->message(); newPencils->getDegreeOfHardness(b); newPencils->getLenght(); newPencils->getCost(c); }
    else if (a == 2) { newPencils = new WhitePencils; newPencils->random(); newPencils->getDegreeOfHardness(b); newPencils->getLenght(); newPencils->getCost(c); }
    else if (a == 3) { newPencils = new ColoredPencils;  newPencils->coloredPencils();  newPencils->getDegreeOfHardness(b); newPencils->getLenght(); newPencils->getCost(c); }

    return newPencils;
}

void costAll(Iterator<Pencils*> *it, int cost)
{
    for(it->First(); !it->IsDone(); it->Next()) { Pencils *currentPencils = it->GetCurrent(); currentPencils->getCost(cost); }
}

int main()
{
    setlocale(LC_ALL, "Russian");

    wcout << L"Введите цвет карандаша (1 - черный, 2 - белый, 3 - цветной): ";

    int choise;
    cin >> choise;

    wcout << L"Введите степень твердости карандашей: ";
    wstring degreeOfHardness;
    wcin >> degreeOfHardness;

    wcout << L"Введите цену за карандаш: ";
    int cost;
    cin >> cost;
    cout << endl;

    Pencils *newPencils = createPencils(choise, degreeOfHardness, cost);
    cout << endl;

    //Создадим вектор
    vectorClass<Pencils*> pencilsVector;

    wcout << L"Введите размер вектора: ";
    int sizeVector;
    cin >> sizeVector;
    cout << endl;

    for(int i = 0; i < sizeVector; i++) { int randomPencils = rand()%3 + 1; Pencils* newPencilsForVector = createPencils(randomPencils, degreeOfHardness, cost);
    pencilsVector.pushBack(newPencilsForVector); cout << endl; }
    wcout << L"Какой же у нас контейнер?: ";
    pencilsVector.information();
    cout << endl << endl;

    //Создадим массив
    arrayClass<Pencils*> pencilsArray;

    wcout << L"Введите размер массива: ";
    int sizeArray;
    cin >> sizeArray;
    cout << endl;

    for(int i = 0; i < sizeArray; i++) { int randomPencils = rand()%3 + 1; pencilsArray.pushBack(createPencils(randomPencils, degreeOfHardness, cost)); cout << endl; }
    wcout << L"Индексы элементов массива: " << endl;
    pencilsArray.printIndex();
    cout << endl << endl;
    wcout << L"Демонстрация взаимосвязи контейнеров:" << endl;

    //Воспользуемся итераторами для вектора и массива
    Iterator<Pencils*> *ptr_1 = new vectorIterator<Pencils*>(&pencilsVector);
    costAll(ptr_1, cost);
    cout << endl;
    delete ptr_1;

    Iterator<Pencils*> *ptr_2 = new arrayIterator<Pencils*>(&pencilsArray);
    costAll(ptr_2, cost);
    delete ptr_2;

    return 0;
}
