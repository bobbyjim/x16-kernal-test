#include <conio.h>
#include <6502.h>

#include "kernal_test.h"

unsigned char kernal_test_chrout(char c)
{
    setregs(c, 0, 0, 0, KERNAL_CHROUT);
    doit();
    gotox(0);
    c = cpeekc();
    if (c != 'a') return 1; // error
    return 0;
}
