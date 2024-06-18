#include <iostream>
#include <array>
#include <typeinfo>
#include <type_traits>
#include <string>

class A
{
    public:
    A(int a) : a(a){}
    int getA()
    {
        return a;
    }
    virtual int getVF() = 0;
    virtual int setVF(int arg)
    {
        std::cout << "base" << '\n';
        int tmp = arg;
    }
    void testFunc()
    {
        std::cout << "base test\n";
    }
    virtual ~A(){}

    private:
    int a;
};

class B : public A
{
    public:
    B(int arg1, int arg2) : A(arg1)
    {
        b = arg2;
    }
    int getB()
    {
        return b;
    }
    virtual int getVF() override
    {
        return val;
    }
    virtual int setVF(int arg) override
    {
        val = arg;
    }
    void testFunc()
    {
        std::cout << "derived test\n";
    }

    template <typename T1, typename T2>
    int templateFunc(T1& arg1, T2& arg2)
    {
        if constexpr (std::is_same<T1, int>())
        {
            return arg1+arg2;
        }
        else if constexpr (std::is_same<T1, std::string>())
        {
            return arg1.length()+arg2.length();
        }
    }
    ~B(){}

    private:
    int b;
    int val;
};

constexpr auto get_values()
{
    std::array<int, 1000> retVal{};
    int count = 0;
    for ( auto& val : retVal)
    {
        val = count* 3;
        ++count;
    }

    return retVal;
}

int main()
{
    A* objB0 = new B(3, 5);
    B* objB1 = new B(1, 2);
    const int* p = nullptr;

    objB0->testFunc();
    objB1->testFunc();
    std::cout << objB1->getA() << '\n';
    objB1->setVF(100);
    std::cout << objB1->getVF() << '\n';

    constexpr auto values = get_values();
    p = &values[5];
    std::cout << "typeinfo : " << typeid(values).name() << ", 5th : " << *p << '\n';
    
    int retArg1 = 10;
    int retArg2 = 11;
    int ret = objB1->templateFunc<int,int>(retArg1, retArg2);
    std::cout << "templateFunc return : " << ret <<'\n';

    std::string retArg3 = "aacd";
    std::string retArg4 = "abcde";
    ret = objB1->templateFunc(retArg3, retArg4);
    std::cout << "templateFunc return : " << ret <<'\n';

    ret = retArg3.compare(retArg4);
    std::cout << "templateFunc return : " << ret <<'\n';

    return 0;
}