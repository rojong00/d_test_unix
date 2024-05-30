#include <iostream>

using namespace std;

template <typename T>
class Type
{
    private:
        T myVar;

    public:
        Type(T c) : myVar(c){}
        ~Type(){}

        void add(T x);
        void sub(T x);
        void show() const;
};

template <typename T>
void Type<T>::add(T x)
{
    this->myVar += x;
}

template <typename T>
void Type<T>::sub(T x)
{
    this->myVar -= x;
}

template <typename T>
void Type<T>::show() const
{
    cout << "var : " << myVar << '\n';
}
