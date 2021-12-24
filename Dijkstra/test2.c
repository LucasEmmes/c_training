#include <assert.h>

void foo(int * bar) {
    *bar = 10;
}

int main(int argc, char const *argv[])
{
    int * p;
    int a = 0;
    p = &a;
    assert(*p == 0);
    foo(p);
    assert(*p == 10);
    return 0;
}
