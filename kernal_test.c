#include <conio.h>

#include "kernal_test.h"

struct regs testregs;

int err = 0;
int sum = 0;

void banner()
{
   cputs("        --------------------------------------------------------------\r\n");
   cputs("        '##:::'##:'########:'########::'##::: ##::::'###::::'##:::::::\r\n");
   cputs("         ##::'##:: ##.....:: ##.... ##: ###:: ##:::'## ##::: ##:::::::\r\n");
   cputs("         ##:'##::: ##::::::: ##:::: ##: ####: ##::'##:. ##:: ##:::::::\r\n");
   cputs("         #####:::: ######::: ########:: ## ## ##:'##:::. ##: ##:::::::\r\n");
   cputs("         ##. ##::: ##...:::: ##.. ##::: ##. ####: #########: ##:::::::\r\n");
   cputs("         ##:. ##:: ##::::::: ##::. ##:: ##:. ###: ##.... ##: ##:::::::\r\n");
   cputs("         ##::. ##: ########: ##:::. ##: ##::. ##: ##:::: ##: ########:\r\n");
   cputs("        ..::::..::........::..:::::..::..::::..::..:::::..::........::\r\n");
   cputs("        ::::::::::'########:'########::'######::'########:::::::::::::\r\n");
   cputs("        ::::::::::... ##..:: ##.....::'##... ##:... ##..::::::::::::::\r\n");
   cputs("        ::::::::::::: ##:::: ##::::::: ##:::..::::: ##::::::::::::::::\r\n");
   cputs("        ::::::::::::: ##:::: ######:::. ######::::: ##::::::::::::::::\r\n");
   cputs("        ::::::::::::: ##:::: ##...:::::..... ##:::: ##::::::::::::::::\r\n");
   cputs("        ::::::::::::: ##:::: ##:::::::'##::: ##:::: ##::::::::::::::::\r\n");
   cputs("        ::::::::::::: ##:::: ########:. ######::::: ##::::::::::::::::\r\n");
   cputs("        :::::::::::::..:::::........:::......::::::..:::::::::::::::::\r\n");
   cputs("        --------------------------------------------------------------\r\n");
}

void testAll()
{
    int x;

    //clrscr();
    banner();

    cprintf("x16 kernal test program\r\n\r\n");
    cprintf("if this is in a \"pet\" font, then load to vera works.\r\n\r\n");
    cprintf(" %20s : %s     %2s   %2s   %2s  %4s  %s \r\n ", 
        "test name",
        "rslt",
        "a",
        "x",
        "y",
        "flags",
        "pc" );

   for(x=2; x<80; ++x) cputc(192);      
   cputs("        \r\n");

   sum += showResult("chrout",   kernal_test_chrout('a'));
   sum += showResult("memtop/r", kernal_test_memtop_read());
   sum += showResult("memtop/w", kernal_test_memtop_write());
   sum += showResult("membot/r", kernal_test_membot_read());
   sum += showResult("membot/w", kernal_test_membot_write());
   sum += showResult("setnam setlfs load", kernal_test_setnam_setlfs_load());

   cprintf("\r\n %16s : %d", "errors", err);
}

void setregs(
        unsigned char a,
        unsigned char x,
        unsigned char y,
        unsigned char flags,
        unsigned pc)
{
    testregs.a = a;
    testregs.x = x;
    testregs.y = y;
    testregs.flags = flags;
    testregs.pc = pc;
}

void doit()
{
    _sys(&testregs);
}

unsigned char showResult(char *label, unsigned char res)
{
    cprintf(" %20s : %4s     %2x   %2x   %2x   %2x   %x \r\n", 
        label, 
        res == 0? "ok" : " *** fail ***",
        testregs.a,
        testregs.x,
        testregs.y,
        testregs.flags,
        testregs.pc );

    return res;
}

unsigned char accumulator()
{
    return testregs.a;
}

unsigned char x_register()
{
    return testregs.x;
}

unsigned char y_register()
{
    return testregs.y;
}

unsigned pc()
{
    return testregs.pc;
}
