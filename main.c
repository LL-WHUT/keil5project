#include <ling.h>

u8 smg[10] = {'6', '6', '#'};
u8 key = 0;
int xs = 7;


void main()
{
    while (1)
    {
        Smg_display(smg, xs);
        while (keyscan())
        {
            key = keyscan();
            smg[0] = '0' + key / 10;
            smg[1] = '0' + key % 10;
        }
    }
}