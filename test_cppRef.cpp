#include <iostream>
#include <memory>
#include <algorithm>

class CustomMemory
{
    public:
    CustomMemory(int val1) : C{val1}
    {
        dynamic = new int[C];
        std::fill(dynamic, dynamic+C, 6);
        size = C;
        std::cout << "real dynamic addr : " << &dynamic << '\n' << std::endl;
    }
    ~CustomMemory()
    {
        std::cout << "destruct CustomMemory activated" << std::endl;
        delete dynamic;
    }

    void setPtr(int val)
    {
        *dynamic = val;
    }

    int* get_dynamic_ptr()
    {
        return dynamic;
    }

    int*& get_dynamic_ref()
    {
        return dynamic;
    }

    int getConst()
    {
        return C;
    }

    int size = 0;
    
    private:
        const int C;
        int* dynamic;
};

int main(void)
{
    CustomMemory* first = new CustomMemory(5);
    CustomMemory* second = new CustomMemory(7);
    int* handlePtr = first->get_dynamic_ptr();
    int*& handleRef = first->get_dynamic_ref();
    int i = 0;

    std::cout << "customMem const val : " << first->getConst() << '\n'; 
    std::cout << "customMem ptr Value : " << handlePtr << std::endl;
    std::cout << "customMem ptr Addr : " << &handlePtr << std::endl;
    std::cout << "customMem ref Value : " << handleRef << std::endl;
    std::cout << "customMem ref Addr : " << &handleRef << std::endl;
    std::cout << '\n';
    std::cout << "customMem ptr Asterisk : " << *handlePtr << std::endl;
    std::cout << "customMem ref Asterisk : " << *handleRef << std::endl;
    std::cout << "customMem ref Asterisk of Ref : " << *(&handleRef) << std::endl;
    std::cout << '\n';
    std::cout << "customMem ptr prefix++ : " << ++handlePtr << std::endl;
    std::cout << "customMem ptr Value : " << handlePtr << std::endl;
    std::cout << "customMem ref prefix++ : " << ++handleRef << std::endl;
    std::cout << "customMem ref Value : " << handleRef << std::endl;

    for (i = 0; i < first->getConst(); i++)
    {
        std::cout << i+1 << " : " << handleRef[i] << "\t";
    }
    std::cout << '\n';
    std::cout << "second obj C : " << second->getConst() << '\n';

    return 0;
}