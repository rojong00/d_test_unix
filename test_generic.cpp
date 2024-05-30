#include "generic.hpp"

int main()
{
    Type<int> type(10);

    type.add(2);
    type.sub(5);
    type.show();

    Type<double> type2(100.5);
    type2.add(2.7);
    type2.sub(5.1);
    type2.show();
    return 0;
}
