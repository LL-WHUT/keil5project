#ifndef __LING_H__
#define __LING_H__

#include <REGx52.H>
#include <INTRINS.H>
typedef unsigned char u8;
typedef unsigned int u16;

void delayxms(u16 xms)
{
    int i, j;
    for (i = 0; i < 114; ++i)
    {
        for (j = 0; j < xms; ++j)
        {
            ;
        }
    }
}

void delay_10us(u16 ten_us)
{
    while (ten_us--)
        ;
}

void hc595_write_data(u8 dat)
{
    u8 i = 0;

    for (i = 0; i < 8; i++) // 循环8次即可将一个字节写入寄存器中
    {
        P3_4 = dat >> 7; // 优先传输一个字节中的高位
        dat <<= 1;       // 将低位移动到高位
        P3_6 = 0;
        _nop_();
        P3_6 = 1;
        _nop_(); // 移位寄存器时钟上升沿将端口数据送入寄存器中
    }
    P3_5 = 0;
    _nop_();
    P3_5 = 1; // 存储寄存器时钟上升沿将前面写入到寄存器的数据输出
}

void gled_display(u8 *gled_row, u16 xms)
{
    int j;
    u8 row = 0;
    u8 gled_col[8] = {0x7f, 0xbf, 0xdf, 0xef, 0xf7, 0xfb, 0xfd, 0xfe};
    for (j = 0; j < (xms / 3 + 1); ++j)
    {
        for (row = 0; row < 8; row++)
        {
            P0 = gled_col[row];
            hc595_write_data(gled_row[row]);
            _nop_();
            hc595_write_data(0x00);
        }
    }
}

void Smg_display(u8 *input, int xms)
{
    u8 smg_code[26] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x80, 0x77, 0x39, 0x5E, 0x79, 0x71, 0x76, 0x38, 0x5C, 0x73, 0x3E, 0x7C, 0x58, 0x54, 0x1C, 0x6E};
    u8 i = 0;
    u8 j = 0;
    // u8 t = 0;
    for (; xms != 0; xms--)
    {

        {
            i = 0;
            j = 0;
            while (input[j] != '#')
            {

                {
                    switch (i) // 位选
                    {
                    case 0:
                        P2_4 = 1;
                        P2_3 = 1;
                        P2_2 = 1;
                        break;
                    case 1:
                        P2_4 = 1;
                        P2_3 = 1;
                        P2_2 = 0;
                        break;
                    case 2:
                        P2_4 = 1;
                        P2_3 = 0;
                        P2_2 = 1;
                        break;
                    case 3:
                        P2_4 = 1;
                        P2_3 = 0;
                        P2_2 = 0;
                        break;
                    case 4:
                        P2_4 = 0;
                        P2_3 = 1;
                        P2_2 = 1;
                        break;
                    case 5:
                        P2_4 = 0;
                        P2_3 = 1;
                        P2_2 = 0;
                        break;
                    case 6:
                        P2_4 = 0;
                        P2_3 = 0;
                        P2_2 = 1;
                        break;
                    case 7:
                        P2_4 = 0;
                        P2_3 = 0;
                        P2_2 = 0;
                        break;
                    }
                    switch (input[j])
                    {
                    case '0':
                        P0 = smg_code[0];
                        break;
                    case '1':
                        P0 = smg_code[1];
                        break;
                    case '2':
                        P0 = smg_code[2];
                        break;
                    case '3':
                        P0 = smg_code[3];
                        break;
                    case '4':
                        P0 = smg_code[4];
                        break;
                    case '5':
                        P0 = smg_code[5];
                        break;
                    case '6':
                        P0 = smg_code[6];
                        break;
                    case '7':
                        P0 = smg_code[7];
                        break;
                    case '8':
                        P0 = smg_code[8];
                        break;
                    case '9':
                        P0 = smg_code[9];
                        break;
                    case '.':
                        P0 = smg_code[10];
                        break;
                    case 'A':
                        P0 = smg_code[11];
                        break;
                    case 'C':
                        P0 = smg_code[12];
                        break;
                    case 'd':
                        P0 = smg_code[13];
                        break;
                    case 'E':
                        P0 = smg_code[14];
                        break;
                    case 'F':
                        P0 = smg_code[15];
                        break;
                    case 'H':
                        P0 = smg_code[16];
                        break;
                    case 'L':
                        P0 = smg_code[17];
                        break;
                    case 'o':
                        P0 = smg_code[18];
                        break;
                    case 'P':
                        P0 = smg_code[19];
                        break;
                    case 'U':
                        P0 = smg_code[20];
                        break;
                    case 'b':
                        P0 = smg_code[21];
                        break;
                    case 'c':
                        P0 = smg_code[22];
                        break;
                    case 'n':
                        P0 = smg_code[23];
                        break;
                    case 'u':
                        P0 = smg_code[24];
                        break;
                    case 'y':
                        P0 = smg_code[25];
                        break;
                    default:
                        P0 = 0x00;
                        break;
                    }
                    delay_10us(20);
                    if (input[j + 1] == '.')
                    {
                        P0 = smg_code[10];
                        delay_10us(20);
                        j++;
                    }
                    i++;
                    j++;
                    P0 = 0x00;
                }
            }
        }
    }
}

u8 keyscan(void)//矩阵键盘扫描函数，返回按键的位置(1--16)
{
    u8 key_value = 0;
    P1 = 0x0F;
    if (P1 != 0x0F)
    {
        delayxms(20);
        if (P1 != 0x0F)
        {
            P1 = 0x0F;
            switch (P1)
            {
            case 0x07:
                key_value = 1; // 第一列
                break;
            case 0x0B:
                key_value = 2; // 第二列
                break;
            case 0x0D:
                key_value = 3; // 第三列
                break;
            case 0x0E:
                key_value = 4; // 第四列
            }
            P1 = 0xF0;
            switch (P1)
            {
            case 0x70:
                key_value += 0; // 第一行
                break;
            case 0xB0:
                key_value += 4; // 第二行
                break;
            case 0xD0:
                key_value += 8; // 第三行
                break;
            case 0xE0:
                key_value += 12; // 第四行
                break;
            }
            // while (P1!=0xF0);//等待按键松开
        }
    }
    else
    {
        key_value = 0;
    }
    return key_value;
}

#endif