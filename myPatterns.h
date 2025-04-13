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

template<typename T>
class Containers
{
public:
    Containers() {}
    virtual Iterator<T>* GetIterator() = 0;
    virtual ~Containers() {}
};

template<typename T>
class vectorClassIterator;

template<typename T>
class arrayClassIterator;

//Шаблонный класс "Вектор"
template <typename T>
class vectorClass : public Containers<T>
{
private:
    vector<T> vectorOfPencils;
public:
    size_t numbersOfElements() const { return vectorOfPencils.size(); }
    void pushBack(T newElement) { vectorOfPencils.push_back(newElement); }
    T getElement(size_t index) const { return vectorOfPencils[index]; }
    void information() const { wcout << L"Это вектор!"; }
    Iterator<T>* GetIterator() override { return new vectorClassIterator<T>(vectorOfPencils, vectorOfPencils.size()); }
};

//Итератор для обхода вектора

template <typename T>
class vectorClassIterator : public Iterator<T>
{
private:
    const vector<T>* vectorContainer;
    size_t positionInVector;
    size_t vectorSize;
public:
    vectorClassIterator(const vector<T>& container, size_t sizeOfVector) : vectorContainer(&container), positionInVector(0), vectorSize(sizeOfVector) {}
    void First() override { positionInVector = 0; }
    void Next() override { positionInVector++; }
    bool IsDone() const override { return (positionInVector >= vectorSize); }
    T GetCurrent()const override { return (*vectorContainer)[positionInVector]; }
};

const size_t maxSize = 100;

//Шаблонный класс "Массив"
template <typename T>
class arrayClass : public Containers<T>
{
private:
    T items[maxSize];
    size_t arraySize = 0;
public:
    void printIndex() { for(size_t i = 0; i < arraySize; i++) { cout << i << endl; } }
    size_t numbersOfElements() const { return arraySize; }
    void pushBack(T newElement) { items[arraySize++] = newElement; }
    T getElement(size_t index) const { return items[index]; }
    Iterator<T>* GetIterator() override { return new arrayClassIterator<T>(items, arraySize); }
};

//Итератор для обхода массива
template <typename T>
class arrayClassIterator : public Iterator<T>
{
private:
    const T *arrayContainer;
    size_t positionInArray;
    size_t arraySize;
public:
    arrayClassIterator(T *container, size_t sizeOfArray) : arrayContainer(container), positionInArray(0), arraySize(sizeOfArray) {}
    void First() override { positionInArray = 0; }
    void Next() override { positionInArray++; }
    bool IsDone() const override { return (positionInArray >= arraySize); }
    T GetCurrent()const override { return arrayContainer[positionInArray]; }
};

//Декоратор
template<typename T>
class IteratorDecorator : public Iterator<T>
{
protected:
    Iterator<T> *It;

public:
    IteratorDecorator(Iterator<T> *it) : It(it) {}
    virtual ~IteratorDecorator() { delete It; }
    virtual void First() { It->First(); }
    virtual void Next() { It->Next(); }
    virtual bool IsDone() const { return It->IsDone(); }
    virtual T GetCurrent() const { return It->GetCurrent(); }
};

//Адаптер
template<typename ContainerType, typename ItemType>
class ConstIteratorAdapter : public Iterator<ItemType>
{
protected:
    ContainerType *Container;
    typename ContainerType::const_iterator It;

public:
    ConstIteratorAdapter(ContainerType *container)
    : Container(container)
    {
        It = Container->begin();
    }

    virtual ~ConstIteratorAdapter() {}
    virtual void First() { It = Container->begin(); }
    virtual void Next() { It++; }
    virtual bool IsDone() const { return (It == Container->end()); }
    virtual ItemType GetCurrent() const { return *It; }
};


#endif // MYPATTERNS_H_INCLUDED
