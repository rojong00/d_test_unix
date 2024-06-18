#include <iostream>
#define A 3


typedef struct
{
    int a;
    int b;
    int c;
    int (*ptrFunc)(int arg);

} ST;

int funcA(int arg)
{
    return arg*2;
}

int funcB(int arg)
{
    return arg*3;
}

ST stFunc[10] = 
{
#ifdef A
    {1, 2, 3, funcA},
#endif
#ifdef B
    {4,5,6, funcB},
#endif
};

int main()
{
    int len = sizeof(stFunc)/sizeof(stFunc[0]);
    int i = 0;
    
    for (i = 0; i < len; i++)
    {
        std::cout << "TEST " << i << " : " << stFunc[i].a << " " <<
            stFunc[i].b << " " << stFunc[i].c << " ";
        if (stFunc[i].ptrFunc != nullptr)
            std::cout << stFunc[i].ptrFunc(10) << '\n';
        else
            std::cout << '_' << '\n';
    }

    return 0;
}
