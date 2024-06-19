#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include "test_typename.h"

Parents::Parents(std::string arg)
    : myStr(arg){}

bool Parents::operator<(const Parents* arg) const
{
    if (this->myStr.size() != arg->getMyStr().size())
        return this->myStr.size() < arg->getMyStr().size();

    return this->myStr > arg->getMyStr();
}

std::string Parents::getMyStr() const
{
    return myStr;
}

template<typename T>
T Test0<T>::getMynum() const
{
    return mynum;
}

template <typename T>
Test0<T>::Test0(std::string arg)
    : Parents(arg){}

template<typename T>
void Test0<T>::setMynum(T _mynum)
{
    this->mynum = _mynum;
}

template <typename T>
void Test0<T>::setMyStr(std::string arg)
{
    this->myStr = arg;
}

template <typename T>
std::string Test0<T>::getMyStr() const
{
    return myStr;
}

template <typename T>
bool Test0<T>::operator<(const Test0<T>* arg) const
{
    if (this->myStr.size() != arg.getMyStr().size())
        return this->myStr.size() < arg->getMyStr().size();

    return this->myStr > arg.getMyStr();
}

class Test
{
    public:
        Test(){}
        ~Test(){}
        
        template<typename T>
            void printFront(T& v)
            {
                auto a = v.front();
                std::cout << "front is " << a << std::endl;
            }
        
        template<typename T, int tmp>
            void printSomething(T& v)
            {
                auto a = v[v.size()/2];
                std::cout << "Something is " << a + tmp << std::endl;
            }
};

struct customSt
{
    template <typename T>
    bool operator()(const Test0<T>* a, const Test0<T>* b)
    {
        return a->getMynum() > b->getMynum();
    }
};

int main()
{
    Test* obj = new Test();
    std::vector<int> v{5,4,3};
    obj->printFront<std::vector<int>>(v);
    obj->printSomething<std::vector<int>, 10>(v);
    int i = 0;

    auto obj2_1 = new Test0<float>();
    obj2_1->setMynum(50.01);
    std::cout << "obj 2 Number : " << obj2_1->getMynum() << std::endl;
    
    auto obj2_2 = new Test0<float>();
    obj2_2->setMynum(50.2);

    struct customSt ST;
    std::cout << "compare : " << ST(obj2_1, obj2_2) << '\n';

    Parents* obj2_3 = new Test0<int>("azcf");
    obj2_1->setMyStr("bcdef");
    obj2_2->setMyStr("cdefg");

    std::vector<Parents*> v2;
    v2.push_back(obj2_1);
    v2.push_back(obj2_2);
    v2.push_back(obj2_3);
    sort(v2.begin(), v2.end());
    
    for ( auto j : v2 )
        std::cout << j->getMyStr() << std::endl;


    std::string _para = "abcdizefghzijkl";
    //std::vector<std::make_shared<Test0<int>>> v3;
    std::vector<std::shared_ptr<Test0<int>>> v3(3);
    for (auto& i : v3)
        i = std::make_shared<Test0<int>>();

    int pos = 0;
    std::string token;
    i = 0;
    std::cout << "1" << '\n';
    while ((pos = _para.find("z")) != std::string::npos)
    {
        token = _para.substr(0, pos);
        v3[i]->setMyStr(token);
        _para.erase(0, pos+1);
        i++;
    }
    token = _para.substr(0, pos);
    v3[i]->setMyStr(token);
    
    
    std::cout << "2" << '\n';
    for (auto& j : v3)
        std::cout << j->getMyStr() << std::endl;



    delete obj, obj2_1, obj2_2, obj2_3;


    return 0;
}
