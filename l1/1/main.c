#include <stdio.h>
#include "solution.h"

int main()
{
    char buf[2] = "xy";
    size_t m = 2;
    int a = 5;
    printf("%d\n", stringStat((const char *)buf, m, &a));
    printf("%d\n", a);
    return 0;
}
