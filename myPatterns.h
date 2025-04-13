#ifndef MYPATTERNS_H_INCLUDED
#define MYPATTERNS_H_INCLUDED
#include <vector>

using namespace std;

template<typename T>
class Iterator
{
protected:
    Iterator() {}

public:
    virtual ~Iterator() {}
    virtual void First() = 0;
    virtual void Next() = 0;
    virtual bool IsDone() const = 0;
    virtual T GetCurrent() const = 0;
};


//Шаблонный класс "Вектор"
template <typename T>
class vectorClass
{
private:
    vector<T> vectorOfPencils;
public:
    size_t numbersOfElements() const { return vectorOfPencils.size(); }
    void pushBack(T newElement) { vectorOfPencils.push_back(newElement); }
    T getElement(size_t index) const { return vectorOfPencils[index]; }
    void information() const { wcout << L"Это вектор!"; }
};

//Итератор для обхода вектора

const size_t maxSize = 100;

//Итератор для обхода массива
template <typename T>
class arrayClassIterator : public Iterator<T>
{
private:
    const T *arrayContainer;
    size_t positionInArray;
    size_t arraySize;
public:
    arrayClassIterator(T *container, size_t sizeOfArray) : arrayContainer(container), positionInContainer(0), arraySize(sizeOfArray) {}
    void First() override { positionInArray = 0; }
    void Next() override { positionInArray++; }
    bool IsDone const override { return (positionInArray >= arraySize); }
    T GetCurrent() const override { return arrayContainer[positionInArray] }
};

//Шаблонный класс "Массив"
template <typename T>
class arrayClass
{
private:
    T items[maxSize];
    int arraySize= 0;
public:
    void printIndex() { for(int i = 0; i < arraySize; i++) { cout << i << endl; } }
    size_t numbersOfElements() const { return arraySize; }
    void pushBack(T newElement) { items[arraySize++] == newElement; }
    T getElement(size_t index) const { return items[index]; }
};


//Итератор для вектора
template<typename T>
class vectorIterator : public Iterator<T>
{
private:
    const vectorClass<T> *vectorContainer;
    int position = 0;
public:
    vectorIterator(vectorClass<T> *container) : vectorContainer(container) {}

    void First() override { position = 0; }
    void Next() override { position++; }
    bool IsDone() const override { return (position >= vectorContainer->numbersOfElements()); }
    T GetCurrent() const override { return vectorContainer->getElement(position); }
};


//Итератор для массива
template<typename T>
class arrayIterator : public Iterator<T>
{
private:
    const arrayClass<T> *arrayContainer;
    int position = 0;
public:
    arrayIterator(arrayClass<T> *container) : arrayContainer(container) {}

    void First() override { position = 0; }
    void Next() override { position++; }
    bool IsDone() const override { return (position >= arrayContainer->numbersOfElements()); }
    T GetCurrent() const override { return arrayContainer->getElement(position); }
};

#endif // MYPATTERNS_H_INCLUDED
