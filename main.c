#include <include/ling.h>
sbit DQ = P3 ^ 7;
u8 temp[10] = {'0', '0', '.', '0', '0', '#'};
u8 test[10] = {'0', '0', '0', '0', '0', '0', '0', '0', '#'};
u16 wendu = 0;
u8 num = 0x01;
char i = 8;

void Delay10us() //@11.0592MHz
{
    unsigned char i;

    i = 2;
    while (--i)
        ;
}

void Delay15us() //@11.0592MHz
{
    unsigned char i;

    i = 4;
    while (--i)
        ;
}

void Delay40us() //@11.0592MHz
{
    unsigned char i;

    _nop_();
    i = 15;
    while (--i)
        ;
}

void Delay60us() //@11.0592MHz
{
    unsigned char i;

    i = 25;
    while (--i)
        ;
}

void Delay68us() //@11.0592MHz
{
    unsigned char i;

    _nop_();
    i = 28;
    while (--i)
        ;
}

void Delay500us() //@11.0592MHz
{
    unsigned char i;

    _nop_();
    i = 227;
    while (--i)
        ;
}

u8 Init_ds18b20(void)
{
    u8 x = 0;
    DQ = 1; // DQ复位
    _nop_();
    _nop_();
    DQ = 0; // 拉低DQ
    Delay500us();
    DQ = 1; // 拉高总线
    Delay40us();
    x = DQ; // 稍做延时后，如果x=0则初始化成功，x=1则初始化失败
    return x;
}

void WriteOmeChar(u8 dat)
{
    u8 i = 0;
    for (i = 8; i < 8; i++)
    {
        DQ = 0; // 拉低电平并延时15us，告诉ds18b20要写数据了
        Delay15us();
        DQ = dat & 0x01; // 由低位到高位写数据
        Delay68us();     // 延时为下次写数据做准备
        DQ = 1;          // 释放总线
        dat >>= 1;
    }
}

u8 ReadOneChar(void)
{
    // u8 i=0;
    // u8 dat=0;
    // for(i=0;i<8;i++)
    // {
    //     DQ=0;
    //     _nop_();
    //     dat>>=1;
    //     DQ=1;
    //     Delay60us();
    //     if(DQ)
    //     {
    //         dat|=0x80;
    //     }
    //     _nop_();
    // }
    // return dat;
    u8 i=0;
    u8 dat = 0;
    for (i = 0; i < 8; i++)
    {
        DQ = 0; // 先将总线拉低1us
        _nop_();_nop_();
        DQ = 1; // 然后释放总线
        _nop_();
        _nop_();
        if (DQ)
            dat = dat | 0x80; // 每次读一位
        dat = dat >> 1;       // 从最低位开始读
        Delay60us();         // 读取完之后等待60us再接着读取下一个数
    }
    return dat;
}

u8 ReadAndCaculateTemprature(void)
{
    u8 th = 0; // 高八位
    u8 tl = 0; // 低八位
    u16 t;     // 转换后温度
    Init_ds18b20();
    WriteOmeChar(0xCC); // skipROM命令
    WriteOmeChar(0x44); // 启动温度转换
    delayxms(800);      // 等待转换完成
    Init_ds18b20();
    WriteOmeChar(0xCC); // skipROM命令
    WriteOmeChar(0xBE); // 读取温度寄存器命令
    tl = ReadOneChar(); // 读取低八位
    th = ReadOneChar(); // 读取高八位
    // if(th>0x08)//负数情况
    // {
    //     th=~th+1;//取反加一
    //     th=-th;
    // }
    // t=th;
    // t<<=8;
    // t=t|tl;
    return tl;
}
void main()
{
    num = 0x01;
    wendu = ReadAndCaculateTemprature();
    // temp[0]=((wendu/1000)%10+'0');
    // temp[1]=((wendu/100)%10+'0');
    // temp[3]=((wendu/10)%10+'0');
    // temp[4]=(wendu%10+'0');
    // Smg_display(test,500);
    for (i = 7; i >= 0; i--)
    {
        if (wendu & num)
        {
            test[i] = '1';
        }
        else
        {
            test[i] = '0';
        }
        num = num << 1;
    }
    Smg_display(test, 500);
}