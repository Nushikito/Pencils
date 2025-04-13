#include <iostream>
#include <ctime>
#include "myPatterns.h"
#include <list>

using namespace std;

enum class pencilsType : int
{
    Black = 1,
    White = 2,
    Colored = 3,
    Undifined = 0
};

class Pencils
{
public:
    Pencils() {};

    double lenght = 12.5;
    int cost;
    wstring doh;
    bool sharpened;
    wstring bl = L"У вас есть упаковка черных карандашей! ";


    //Общие методы
    virtual double getLenght() { return lenght; }
    virtual wstring getDegreeOfHardness (wstring doh) { return doh; }
    virtual int getCost (int cost) { return cost; };
    virtual bool getSharpenes () { srand(time(0)); bool res = rand()%2; return res; }

    virtual wstring message() { return bl; } //Метод для черных карандашей
    virtual void random() { srand(time(0)); int z = 0; for(int i = 0; i < 20; i++){ int rndm = rand()%10; if(rndm <= 5){z += 1;} } cout << z; } //Метод для белых карандашей
    virtual void coloredPencils() { wcout << L"Количество цветных карандашей: "; } //Метод для цветных карандашей

    virtual ~Pencils() { wcout << "Карандашей больше нет :(" << endl; };
};

class BlackPencils : public Pencils
{
public:
    BlackPencils() {};

    wstring message() { Pencils::message(); wcout << L"Давайте узнаем, какие они!" << endl; return Pencils::message(); }
    wstring getDegreeOfHardness(wstring doh) { wcout << L"Их степень твердости: " << Pencils::getDegreeOfHardness(doh) << endl; return Pencils::getDegreeOfHardness(doh); }
    double getLenght() { wcout << L"Их длина: " << Pencils::getLenght() << endl; return Pencils::getLenght(); }
    int getCost(int cost) { wcout << L"Цена за штуку: " << Pencils::getCost(cost) << endl; return Pencils::getCost(cost); }
    bool getSharpenes() { wcout << L"Заточен ли карандаш? " << Pencils::getSharpenes() << endl; return Pencils::getSharpenes(); }

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
    bool getSharpenes() { wcout << L"Заточен ли карандаш? " << Pencils::getSharpenes() << endl; return Pencils::getSharpenes(); }

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
    bool getSharpenes() { wcout << L"Заточен ли карандаш? " << Pencils::getSharpenes() << endl; return Pencils::getSharpenes(); }

    ~ColoredPencils() { wcout << L"Цветных карандашей больше нет :(" << endl; };
};

Pencils *createPencils(int a, wstring b, int c)
{
    Pencils *newPencils = nullptr;

    if (a == 1) { newPencils = new BlackPencils; newPencils->message(); newPencils->getDegreeOfHardness(b); newPencils->getLenght(); newPencils->getSharpenes(); newPencils->getCost(c); }
    else if (a == 2) { newPencils = new WhitePencils; newPencils->random(); newPencils->getDegreeOfHardness(b); newPencils->getLenght(); newPencils->getSharpenes(); newPencils->getCost(c); }
    else if (a == 3) { newPencils = new ColoredPencils;  newPencils->coloredPencils();  newPencils->getDegreeOfHardness(b); newPencils->getLenght(); newPencils->getSharpenes(); newPencils->getCost(c); }

    return newPencils;
}

Pencils *createPencilsENUM(int a, wstring b, int c)
{
    Pencils *newPencils = nullptr;

    if (a == static_cast<int>(pencilsType::Black)) { newPencils = new BlackPencils; newPencils->message(); newPencils->getDegreeOfHardness(b); newPencils->getLenght(); newPencils->getSharpenes(); newPencils->getCost(c); }
    else if (a == static_cast<int>(pencilsType::White)) { newPencils = new WhitePencils; newPencils->random(); newPencils->getDegreeOfHardness(b); newPencils->getLenght(); newPencils->getSharpenes(); newPencils->getCost(c); }
    else if (a == static_cast<int>(pencilsType::Colored)) { newPencils = new ColoredPencils;  newPencils->coloredPencils();  newPencils->getDegreeOfHardness(b); newPencils->getLenght(); newPencils->getSharpenes(); newPencils->getCost(c); }

    return newPencils;
}

void create(Iterator<Pencils*> *it)
{
    for(it->First(); !it->IsDone(); it->Next()) { Pencils *currentPencils = it->GetCurrent(); }
}

class sharpenedPencilDecorator : public IteratorDecorator<class Pencils*>
{
private:
    bool targetGood;
public:
    sharpenedPencilDecorator(Iterator<Pencils*> *it, bool isGood) : IteratorDecorator<Pencils*>(it), targetGood(isGood) {}
    void First() { It->First(); while(!It->IsDone() && It->GetCurrent()->getSharpenes() != targetGood) { It->Next(); } }
    void Next() { do { It->Next(); } while(!It->IsDone() && It->GetCurrent()->getSharpenes() != targetGood ); }
};

class blackPencilsDecorator : public IteratorDecorator<class Pencils*>
{
private:
    wstring targetBlack;
public:
    blackPencilsDecorator(Iterator<Pencils*> *it, wstring isBlack) : IteratorDecorator<Pencils*>(it), targetBlack(isBlack) {}
    void First() { It->First(); while(!It->IsDone() && It->GetCurrent()->message() != targetBlack) { It->Next(); } }
    void Next() { do { It->Next(); } while(!It->IsDone() && It->GetCurrent()->message() != targetBlack ); }
};

class costOfPencilsDecorator : public IteratorDecorator<class Pencils*>
{
private:
    int costDecorator;
public:
    costOfPencilsDecorator(Iterator<Pencils*> *it, int isGood) : IteratorDecorator<Pencils*>(it), costDecorator(isGood) {}
    void First() { It->First(); while(!It->IsDone() && It->GetCurrent()->getCost(costDecorator) != costDecorator) { It->Next(); } }
    void Next() { do { It->Next(); } while(!It->IsDone() && It->GetCurrent()->getCost(costDecorator) != costDecorator); }
};

int main()
{
    setlocale(LC_ALL, "Russian");

    wcout << L"Введите степень твердости карандашей: ";
    wstring degreeOfHardness;
    wcin >> degreeOfHardness;

    wcout << L"Введите цену за карандаш для вектора: ";
    int costVector;
    cin >> costVector;

    wcout << L"Введите цену за карандаш для массива: ";
    int costArray;
    cin >> costArray;
    cout << endl;

    //Создадим вектор
    vectorClass<Pencils*> pencilsVector;

    wcout << L"Введите размер вектора: ";
    int sizeVector;
    cin >> sizeVector;
    cout << endl;

    for(int i = 0; i < sizeVector; i++) { int randomPencils = rand()%3 + 1; Pencils* newPencilsForVector = createPencils(randomPencils, degreeOfHardness, costVector);
    pencilsVector.pushBack(newPencilsForVector); cout << endl; }
    wcout << L"Какой же у нас контейнер?: ";
    pencilsVector.information();
    create(pencilsVector.GetIterator());
    cout << endl << endl;

    wcout << L"Использовали декоратор для поиска заточенных карандашей в векторе: " << endl;
    Iterator<Pencils*>* It = new sharpenedPencilDecorator(pencilsVector.GetIterator(), true);
    create(It);
    delete It;
    cout << endl << endl;

    wcout << L"Использовали декоратор для поиска черных карандашей в векторе: " << endl;
    Iterator<Pencils*>* It2 = new blackPencilsDecorator(pencilsVector.GetIterator(), L"У вас есть упаковка черных карандашей! ");
    create(It2);
    delete It2;
    cout << endl << endl;

    wcout << L"Использовали декоратор для поиска карандашей с нужной стоимостью в векторе: " << endl;
    Iterator<Pencils*>* It3= new costOfPencilsDecorator(pencilsVector.GetIterator(), costVector);
    create(It3);
    delete It3;
    cout << endl << endl;

    //Создадим массив
    arrayClass<Pencils*> pencilsArray;

    wcout << L"Введите размер массива: ";
    int sizeArray;
    cin >> sizeArray;
    cout << endl;

    for(int i = 0; i < sizeArray; i++) { int randomPencils = rand()%3 + 1; pencilsArray.pushBack(createPencils(randomPencils, degreeOfHardness, costArray)); cout << endl; }
    wcout << L"Индексы элементов массива: " << endl;
    pencilsArray.printIndex();
    cout << endl << endl;
    create(pencilsArray.GetIterator());
    cout << endl << endl;

    wcout << L"Работа декоратора на примере массива: " << endl;

    list<Pencils*> adapterPencilsVector;
	for (size_t i = 0; i < 5; i++)
	{
		int rndm = rand() % 3 + 1;
		pencilsType typeOfPencil = static_cast<pencilsType>(rndm);
		Pencils* newPencil = createPencilsENUM(static_cast<int>(typeOfPencil), degreeOfHardness, costVector);
		adapterPencilsVector.push_back(newPencil);
		cout << endl;
	}

    Iterator<Pencils*>* adaptedIterator = new ConstIteratorAdapter<list<Pencils*>, Pencils*>(&adapterPencilsVector);
    Iterator<Pencils*>* adaptedBlackPencilsIterator = new blackPencilsDecorator(new sharpenedPencilDecorator(adaptedIterator, true), L"У вас есть упаковка черных карандашей! ");
    create(adaptedBlackPencilsIterator);
    delete adaptedBlackPencilsIterator;

    return 0;
}
