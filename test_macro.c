#include <stdio.h>

#define dlist_for_each(pos, head, member)   \
    for (pos;  \
        head < pos; \
        (*member)++)

#define TRANS(tmp) (tmp<<4)
#define TRA TRANS(tmp)
        

int main(int argc, char *argv[])
{
    int pos_ = 5, head_ = 2, member = 1;
    dlist_for_each(pos_, head_, &member)
    {
        printf("head : %d\n", head_);
        head_++;
    }
    printf("first : pos_:%d, head_:%d, member:%d\n", pos_, head_, member);

    int tmp = 15;
    printf("transed tmp : %d\n", TRANS(tmp));
    printf("transed tmp : %d\n", TRA);


    /*
    head_ = pos_;
    dlist_for_each(pos_, head_, &member);
    printf("first : pos_:%d, head_:%d, member:%d\n", pos_, head_, member);
    */

    return 0;
}

