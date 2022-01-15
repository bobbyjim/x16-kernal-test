#include <conio.h>
#include <6502.h>

#include "kernal_test.h"

unsigned char kernal_test_settim()
{
    unsigned char *a = (unsigned char*)(0xa0);

    setregs(10, 20, 30, 0, KERNAL_SETTIM);
    doit();
    return a[0] == 30 && a[1] == 20 && a[2] == 10;
}

unsigned char kernal_test_rdtim()
{
    setregs(0x40, 0x50, 0x60, 0, KERNAL_SETTIM);
    doit();

    setregs(0, 0, 0, 0, KERNAL_RDTIM);
    doit();

    return accumulator_is(0x60) && x_register_is(0x50) && y_register_is(0x40);
}
