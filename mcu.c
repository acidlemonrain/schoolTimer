#include <reg52.h>
#define uint unsigned int
#define uchar unsigned char
sbit key1 = P3 ^ 0;
sbit key2 = P3 ^ 1;
sbit key3 = P3 ^ 2;
sbit key4 = P3 ^ 3;
sbit lcden = P2 ^ 7;
sbit lcdrs = P2 ^ 6;
sbit lcdrw = P2 ^ 5;
sbit sound = P1 ^ 5;
uint i, cnt, cnt1;
//date and timer variables
uint nian = 2019, yue = 6, ri = 28,
	 hour = 23, hourshi, hourge, min = 59, minshi, minge, sec = 0, secshi, secge,
	 ahour1 = 6, ahourshi1, ahourge1, amin1 = 30, aminshi1, aminge1,
	 ahour2, ahourshi2, ahourge2, amin2, aminshi2, aminge2,
	 ahour3, ahourshi3, ahourge3, amin3 = 50, aminshi3, aminge3,
	 ahour4 = 23, ahourshi4, ahourge4, amin4 = 30, aminshi4, aminge4;

uchar num;
//beep enable flag
bit flag = 1;
//what is this? 0~9...
uchar code table1[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
//uchar code riqi[]="2019-06-26      ";
uchar code table2[] = "Time 00:00      ";
uchar code Alarm_1[] = "GB    00:00     ";
uchar code Alarm_2[] = "SK    00:00     ";
uchar code Alarm_3[] = "XK    00:00     ";
uchar code Alarm_4[] = "JQ    00:00     ";
uchar code keyValue[] = "123456789*0#a";
uint key;
//just delay nothing more
void delay(uint z)
{
	uint i, j;
	for (i = z; i > 0; i--)
		for (j = 110; j > 0; j--)
			;
}
//lcd 1602  basic  config function
void write_com(uchar com)
{
	delay(5);
	lcdrs = 0;
	P0 = com;
	delay(5);
	lcden = 1;
	delay(5);
	lcden = 0;
}
//lcd 1602  basic  write data function
void write_data(uchar date)
{
	delay(5);
	lcdrs = 1;
	P0 = date;
	delay(5);
	lcden = 1;
	delay(5);
	lcden = 0;
}

void write_nian(uchar add, uint date)
{
	uchar qian, bai, shi, ge;
	qian = date / 1000;
	bai = (date - 1000 * qian) / 100;
	shi = (date - qian * 1000 - bai * 100) / 10;
	ge = date % 10;
	write_com(0x80 + 0x40 + add);
	write_data(table1[qian]);
	write_data(table1[bai]);
	write_data(table1[shi]);
	write_data(table1[ge]);
}

void write_yue(uchar add, uchar date)
{
	uchar shi, ge;
	shi = date / 10;
	ge = date % 10;
	write_com(0x80 + 0x40 + add);
	write_data(0x30 + shi);
	write_data(0x30 + ge);
}

void write_ri(uchar add, uchar date)
{
	uchar shi, ge;
	shi = date / 10;
	ge = date % 10;
	write_com(0x80 + 0x40 + add);
	write_data(0x30 + shi);
	write_data(0x30 + ge);
	write_data(' ');
}
//display date 20xx-xx-xx
void qi()
{
	write_nian(0, nian);
	write_yue(5, yue);
	write_ri(8, ri);
	write_com(0x80 + 0x40 + 7);
	write_data('-');
	write_com(0x80 + 0x40 + 4);
	write_data('-');
	write_com(0x80 + 0x40 + 4);
	write_data('-');
}
// very important!!
void scan()
{
	uchar temp;
	while (1)
	{
		P1 = 0xF7;
		temp = P1;
		temp = temp & 0xF0;
		if (temp != 0xF0)
		{
			delay(1);
			temp = P1;
			temp = temp & 0xF0;
			if (temp != 0xF0)
			{
				temp = P1;
				switch (temp)
				{
				case 0x77:
					key = 1;
					break;
				case 0xB7:
					key = 4;
					break;
				case 0xD7:
					key = 7;
					break;
				case 0xE7:
					key = 10;
					break;
				}
				while (temp != 0xF0)
				{
					temp = P1;
					temp = temp & 0xF0;
				}
				return;
			}
		}
		P1 = 0xFB;
		temp = P1;
		temp = temp & 0xF0;
		if (temp != 0xF0)
		{
			delay(1);
			temp = P1;
			temp = temp & 0xF0;
			if (temp != 0xF0)
			{
				temp = P1;
				switch (temp)
				{
				case 0x7B:
					key = 2;
					break;
				case 0xBB:
					key = 5;
					break;
				case 0xDB:
					key = 8;
					break;
				case 0xEB:
					key = 11;
					break;
				}
				while (temp != 0xF0)
				{
					temp = P1;
					temp = temp & 0xF0;
				}
				return;
			}
		}
		P1 = 0xFD;
		temp = P1;
		temp = temp & 0xF0;
		if (temp != 0xF0)
		{
			delay(1);
			temp = P1;
			temp = temp & 0xF0;
			if (temp != 0xF0)
			{
				temp = P1;
				switch (temp)
				{
				case 0x7D:
					key = 3;
					break;
				case 0xBD:
					key = 6;
					break;
				case 0xDD:
					key = 9;
					break;
				case 0xED:
					key = 12;
					break;
				}
				while (temp != 0xF0)
				{
					temp = P1;
					temp = temp & 0xF0;
				}
				return;
			}
		}
	}
}
//what is this?
void time()
{
	do
	{
		write_com(0x0f);
		delay(2);
		write_com(0x80 + 5);
		scan();
		hourshi = key;
		write_data(keyValue[hourshi - 1]);
		if (key == 11)
		{
			hourshi = 0;
		}
		delay(5);
		write_com(0x80 + 6);
		scan();
		hourge = key;
		delay(2);
		write_data(keyValue[hourge - 1]);
		if (key == 11)
		{
			hourge = 0;
		}
	} while (hourshi * 10 + hourge >= 24);
	hour = hourshi * 10 + hourge;
	write_com(0x80 + 7);
	delay(2);
	write_data(':');
	do
	{
		write_com(0x0f);
		delay(2);
		write_com(0x80 + 8);
		scan();
		minshi = key;
		write_data(keyValue[minshi - 1]);
		if (key == 11)
		{
			minshi = 0;
		}
		delay(5);
		scan();
		minge = key;
		write_com(0x80 + 9);
		delay(2);
		write_data(keyValue[minge - 1]);
		if (key == 11)
		{
			minge = 0;
		}
		delay(1);
	} while (minshi * 10 + minge >= 60);
	min = minshi * 10 + minge;
	write_com(0x0c);
	TR1 = 1;
}

//what is this?
//delete it this is small btn used for controll keybords

//lcd init
void lcd_init()
{
	lcden = 0;
	lcdrw = 0;
	write_com(0x38);
	write_com(0x0c);
	write_com(0x06);
	write_com(0x01);
	delay(2);
	write_com(0x80);
	for (i = 0; i < 16; i++)
	{
		write_data(table2[i]);
		delay(1);
	}
}

void pannian()
{
	if (nian % 400 == 0 || (nian % 4 == 0 && nian % 100 != 0))
	{
		if (yue == 2 && ri == 30)
		{
			yue++;
			ri = 1;
		}
		else if ((yue == 1 || yue == 3 || yue == 5 || yue == 7 || yue == 8 || yue == 10 || yue == 12) && ri == 32)
		{
			yue++;
			ri = 1;
		}
		else if ((yue == 4 || yue == 6 || yue == 9 || yue == 11) && ri == 31)
		{
			yue++;
			ri = 1;
		}
	}
	else
	{
		if (yue == 2 && ri == 29)
		{
			yue++;
			ri = 1;
		}
		else if ((yue == 1 || yue == 3 || yue == 5 || yue == 7 || yue == 8 || yue == 10 || yue == 12) && ri == 32)
		{
			yue++;
			ri = 1;
		}
		else if ((yue == 4 || yue == 6 || yue == 9 || yue == 11) && ri == 31)
		{
			yue++;
			ri = 1;
		}
	}
}

void judge()
{
	if (sec == 60)
	{
		min++;
		sec = 0;
	}
	if (min == 60)
	{
		hour++;
		min = 0;
	}
	if (hour == 24)
	{
		ri++;
		hour = 0;
	}
	pannian();
	if (yue == 12)
	{
		nian++;
		yue = 1;
	}
}

void init()
{

	key1 = 1;
	key2 = 1;
	key3 = 1;
	key4 = 1;
	sound = 1; //muted
	TMOD = 0x10;
	TL1 = 0xB0;
	TH1 = 0x3C;
	EA = 1;
	ET1 = 1;
	TR1 = 1;
}

void speak()
{
	//check if it is alarm time
	if ((amin1 == min && ahour1 == hour || (amin2 == min && ((hour >= 7 && hour <= 12) || (hour >= 14 && hour <= 21))) || (amin3 == min && ((hour >= 7 && hour <= 12) || (hour >= 14 && hour <= 21))) || amin4 == min && ahour4 == hour) && flag == 1)
	{
		delay(5);
		sound = 0;
	}
	delay(10);
	delay(10);
	delay(10);
	sound = 1;
}

//interrupt function
void led1() interrupt 3
{
	TL1 = 0xB0;
	TH1 = 0x3C;
	//ticks ticks check if it is alarm time
	if ((amin1 != min || ahour1 != hour) && (amin2 != min) && (amin3 != min) && (amin4 != min || ahour4 != hour))
	{
		flag = 1; //enabled sound
		sound = 1;
	}
	speak();
	num++;
	if (num == 20)
	{
		sec++;
		num = 0;
		judge();
	}
}

void main()
{
	lcd_init();
	init();
	while (1)
	{
		//scan
		scan();
		//calculate time minutes and display
		minge = min % 10;
		minshi = min / 10;
		write_com(0x80 + 9);
		write_data(table1[minge]);
		delay(5);
		write_com(0x80 + 8);
		write_data(table1[minshi]);

		//calculate time hours and display
		hourge = hour % 10;
		hourshi = hour / 10;
		write_com(0x80 + 6);
		write_data(table1[hourge]);
		delay(5);
		write_com(0x80 + 5);
		write_data(table1[hourshi]);
		write_com(0x80 + 7);
		write_data(':');
		delay(5);

		//calculate time seconds and display
		secge = sec % 10;
		secshi = sec / 10;
		write_com(0x80 + 15);
		write_data(table1[secge]);
		delay(5);
		write_com(0x80 + 14);
		write_data(table1[secshi]);
		//calculate date and display
		qi();
	}
}