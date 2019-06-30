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
uint i, cnt, cnt1; //cnt:ѡ��ͬ���ӽ��е�ʱ���ñ��(�빦�ܼ�key3�й�)
				   //cnt1:ѡ��ͬ���ӽ�����ʾ���ñ��(�빦�ܼ�key2�й�)
uint nian = 2019, yue = 6, ri = 28,
	 hour = 23, hourshi, hourge, min = 59, minshi, minge, sec = 0, secshi, secge,
	 ahour1 = 6, ahourshi1, ahourge1, amin1 = 30, aminshi1, aminge1,
	 ahour2, ahourshi2, ahourge2, amin2, aminshi2, aminge2,
	 ahour3, ahourshi3, ahourge3, amin3 = 50, aminshi3, aminge3,
	 ahour4 = 23, ahourshi4, ahourge4, amin4 = 30, aminshi4, aminge4; //����ϵͳ���ڡ�ʱ�估�ĸ���ͬ������
uchar num;															  //��ʱ��������ʱ1s�����ܴ���
bit flag = 1;														  //�����־λ
uchar code table1[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
//uchar code riqi[]="2019-06-26      ";
uchar code table2[] = "Time 00:00      ";
uchar code Alarm_1[] = "GB    00:00     ";
uchar code Alarm_2[] = "SK    00:00     ";
uchar code Alarm_3[] = "XK    00:00     ";
uchar code Alarm_4[] = "JQ    00:00     ";
uchar code keyValue[] = "123456789*0#a"; //���ذ�����ʵֵ��
uint key;

void delay(uint z)
{ //��ʱz����
	uint i, j;
	for (i = z; i > 0; i--)
		for (j = 110; j > 0; j--)
			;
}

void write_com(uchar com)
{ //LCD������ƣ�дָ���
	delay(5);
	lcdrs = 0;
	P0 = com;
	delay(5);
	lcden = 1;
	delay(5);
	lcden = 0;
}

void write_data(uchar date)
{ //LCD���ݿ��ƣ�д���ݺ���
	delay(5);
	lcdrs = 1;
	P0 = date;
	delay(5);
	lcden = 1;
	delay(5);
	lcden = 0;
}

void write_nian(uchar add, uint date)
{ //����ʾ����
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
{ //����ʾ����
	uchar shi, ge;
	shi = date / 10;
	ge = date % 10;
	write_com(0x80 + 0x40 + add);
	write_data(0x30 + shi);
	write_data(0x30 + ge);
}

void write_ri(uchar add, uchar date)
{ //����ʾ����
	uchar shi, ge;
	shi = date / 10;
	ge = date % 10;
	write_com(0x80 + 0x40 + add);
	write_data(0x30 + shi);
	write_data(0x30 + ge);
	write_data(' ');
}

void qi()
{ //��ʾ�������ں���
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

void scan()
{ //����ɨ��
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

void time()
{ //ϵͳʱ��ʱ������
	do
	{ //ϵͳʱ�ӡ�ʱ������
		write_com(0x0f);
		delay(2);
		write_com(0x80 + 5);
		scan();
		hourshi = key;
		write_data(keyValue[hourshi - 1]);
		if (key == 11)
		{ //�����ϵ�0����Ӧ11������������ᵼ��ѭ������
			hourshi = 0;
		}
		delay(5);
		write_com(0x80 + 6);
		scan();
		hourge = key;
		delay(2);
		write_data(keyValue[hourge - 1]);
		if (key == 11)
		{ //�����ϵ�0����Ӧ11������������ᵼ��ѭ������
			hourge = 0;
		}
	} while (hourshi * 10 + hourge >= 24);
	hour = hourshi * 10 + hourge;
	write_com(0x80 + 7);
	delay(2);
	write_data(':');
	do
	{ //ϵͳʱ�ӡ��֡�����
		write_com(0x0f);
		delay(2);
		write_com(0x80 + 8);
		scan();
		minshi = key;
		write_data(keyValue[minshi - 1]);
		if (key == 11)
		{ //�����ϵ�0����Ӧ11������������ᵼ��ѭ������
			minshi = 0;
		}
		delay(5);
		scan();
		minge = key;
		write_com(0x80 + 9);
		delay(2);
		write_data(keyValue[minge - 1]);
		if (key == 11)
		{ //�����ϵ�0����Ӧ11������������ᵼ��ѭ������
			minge = 0;
		}
		delay(1);
	} while (minshi * 10 + minge >= 60);
	min = minshi * 10 + minge;
	write_com(0x0c); //������ʾ���ع�꣬����˸
	TR1 = 1;		 //������ʱ��1
}

void alarm11()
{ //���õ�һ������
	do
	{ //����ʱ�ӡ�ʱ������
		write_com(0x0f);
		delay(2);
		write_com(0x80 + 0x40 + 6);
		scan();
		ahourshi1 = key;
		write_data(keyValue[ahourshi1 - 1]);
		if (key == 11)
		{ //�����ϵ�0����Ӧ11������������ᵼ��ѭ������
			ahourshi1 = 0;
		}
		delay(5);
		write_com(0x80 + 0x40 + 7);
		scan();
		ahourge1 = key;
		delay(2);
		write_data(keyValue[ahourge1 - 1]);
		if (key == 11)
		{ //�����ϵ�0����Ӧ11������������ᵼ��ѭ������
			ahourge1 = 0;
		}
	} while (ahourshi1 * 10 + ahourge1 >= 24);
	ahour1 = ahourshi1 * 10 + ahourge1;
	write_com(0x80 + 0x40 + 8);
	delay(2);
	write_data(':');
	do
	{ //ϵͳʱ�ӡ��֡�����
		write_com(0x0f);
		delay(2);
		write_com(0x80 + 0x40 + 9);
		scan();
		aminshi1 = key;
		write_data(keyValue[aminshi1 - 1]);
		if (key == 11)
		{ //�����ϵ�0����Ӧ11������������ᵼ��ѭ������
			aminshi1 = 0;
		}
		delay(5);
		scan();
		aminge1 = key;
		write_com(0x80 + 0x40 + 10);
		delay(2);
		write_data(keyValue[aminge1 - 1]);
		if (key == 11)
		{ //�����ϵ�0����Ӧ11������������ᵼ��ѭ������
			aminge1 = 0;
		}
		delay(1);
	} while (aminshi1 * 10 + aminge1 >= 60);
	amin1 = aminshi1 * 10 + aminge1;
	delay(1000);
	write_com(0x0c); //������ʾ���ع�꣬����˸
	write_com(0x80 + 0x40);
	qi(); //��ʾ����
}

void alarm22()
{ //���õڶ�������
	do
	{ //����ʱ�ӡ�ʱ������
		write_com(0x0f);
		delay(2);
		write_com(0x80 + 0x40 + 6);
		scan();
		ahourshi2 = key;
		write_data(keyValue[ahourshi2 - 1]);
		if (key == 11)
		{ //�����ϵ�0����Ӧ11������������ᵼ��ѭ������
			ahourshi2 = 0;
		}
		delay(5);
		write_com(0x80 + 0x40 + 7);
		scan();
		ahourge2 = key;
		delay(2);
		write_data(keyValue[ahourge2 - 1]);
		if (key == 11)
		{ //�����ϵ�0����Ӧ11������������ᵼ��ѭ������
			ahourge2 = 0;
		}
	} while (ahourshi2 * 10 + ahourge2 >= 24);
	ahour2 = ahourshi2 * 10 + ahourge2;
	write_com(0x80 + 0x40 + 8);
	delay(2);
	write_data(':');
	do
	{ //ϵͳʱ�ӡ��֡�����
		write_com(0x0f);
		delay(2);
		write_com(0x80 + 0x40 + 9);
		scan();
		aminshi2 = key;
		write_data(keyValue[aminshi2 - 1]);
		if (key == 11)
		{ //�����ϵ�0����Ӧ11������������ᵼ��ѭ������
			aminshi2 = 0;
		}
		delay(5);
		scan();
		aminge2 = key;
		write_com(0x80 + 0x40 + 10);
		delay(2);
		write_data(keyValue[aminge2 - 1]);
		if (key == 11)
		{ //�����ϵ�0����Ӧ11������������ᵼ��ѭ������
			aminge2 = 0;
		}
		delay(1);
	} while (aminshi2 * 10 + aminge2 >= 60);
	amin2 = aminshi2 * 10 + aminge2;
	delay(1000);
	write_com(0x0c); //������ʾ���ع�꣬����˸
	write_com(0x80 + 0x40);
	qi(); //��ʾ����
}

void alarm33()
{ //���õ���������
	do
	{ //����ʱ�ӡ�ʱ������
		write_com(0x0f);
		delay(2);
		write_com(0x80 + 0x40 + 6);
		scan();
		ahourshi3 = key;
		write_data(keyValue[ahourshi3 - 1]);
		if (key == 11)
		{ //�����ϵ�0����Ӧ11������������ᵼ��ѭ������
			ahourshi3 = 0;
		}
		delay(5);
		write_com(0x80 + 0x40 + 7);
		scan();
		ahourge3 = key;
		delay(2);
		write_data(keyValue[ahourge3 - 1]);
		if (key == 11)
		{ //�����ϵ�0����Ӧ11������������ᵼ��ѭ������
			ahourge3 = 0;
		}
	} while (ahourshi3 * 10 + ahourge3 >= 24);
	ahour3 = ahourshi3 * 10 + ahourge3;
	write_com(0x80 + 0x40 + 8);
	delay(2);
	write_data(':');
	do
	{ //ϵͳʱ�ӡ��֡�����
		write_com(0x0f);
		delay(2);
		write_com(0x80 + 0x40 + 9);
		scan();
		aminshi3 = key;
		write_data(keyValue[aminshi3 - 1]);
		if (key == 11)
		{ //�����ϵ�0����Ӧ11������������ᵼ��ѭ������
			aminshi3 = 0;
		}
		delay(5);
		scan();
		aminge3 = key;
		write_com(0x80 + 0x40 + 10);
		delay(2);
		write_data(keyValue[aminge3 - 1]);
		if (key == 11)
		{ //�����ϵ�0����Ӧ11������������ᵼ��ѭ������
			aminge3 = 0;
		}
		delay(1);
	} while (aminshi3 * 10 + aminge3 >= 60);
	amin3 = aminshi3 * 10 + aminge3;
	delay(1000);
	write_com(0x0c); //������ʾ���ع�꣬����˸
	write_com(0x80 + 0x40);
	qi(); //��ʾ����
}

void alarm44()
{ //���õ��ĸ�����
	do
	{ //����ʱ�ӡ�ʱ������
		write_com(0x0f);
		delay(2);
		write_com(0x80 + 0x40 + 6);
		scan();
		ahourshi4 = key;
		write_data(keyValue[ahourshi4 - 1]);
		if (key == 11)
		{ //�����ϵ�0����Ӧ11������������ᵼ��ѭ������
			ahourshi4 = 0;
		}
		delay(5);
		write_com(0x80 + 0x40 + 7);
		scan();
		ahourge4 = key;
		delay(2);
		write_data(keyValue[ahourge4 - 1]);
		if (key == 11)
		{ //�����ϵ�0����Ӧ11������������ᵼ��ѭ������
			ahourge4 = 0;
		}
	} while (ahourshi4 * 10 + ahourge4 >= 24);
	ahour4 = ahourshi4 * 10 + ahourge4;
	write_com(0x80 + 0x40 + 8);
	delay(2);
	write_data(':');
	do
	{ //ϵͳʱ�ӡ��֡�����
		write_com(0x0f);
		delay(2);
		write_com(0x80 + 0x40 + 9);
		scan();
		aminshi4 = key;
		write_data(keyValue[aminshi4 - 1]);
		if (key == 11)
		{ //�����ϵ�0����Ӧ11������������ᵼ��ѭ������
			aminshi4 = 0;
		}
		delay(5);
		scan();
		aminge4 = key;
		write_com(0x80 + 0x40 + 10);
		delay(2);
		write_data(keyValue[aminge4 - 1]);
		if (key == 11)
		{ //�����ϵ�0����Ӧ11������������ᵼ��ѭ������
			aminge4 = 0;
		}
		delay(1);
	} while (aminshi4 * 10 + aminge4 >= 60);
	amin4 = aminshi4 * 10 + aminge4;
	delay(1000);
	write_com(0x0c); //������ʾ���ع�꣬����˸
	write_com(0x80 + 0x40);
	qi(); //��ʾ����
}

void keyscan1()
{ //����ɨ�����
	if (key1 == 0)
	{ //���¹��ܼ�key1����ϵͳʱ������
		delay(10);
		if (key1 == 0)
		{
			while (!key1)
				;
			time(); //����ϵͳʱ�����ú���
		}
	}
	else if (key2 == 0)
	{ //���¹��ܼ�key2�鿴��������
		cnt1++;
		delay(10);
		if (cnt1 == 1)
		{
			write_com(0x80 + 0x40);
			for (i = 0; i < 6; ++i)
				write_data(Alarm_1[i]); //��ʾ�������õ�ʱ��
			while (!key2)
			{
				ahourge1 = ahour1 % 10;
				ahourshi1 = ahour1 / 10;
				write_com(0x80 + 0x40 + 7);
				write_data(table1[ahourge1]);
				delay(5);
				write_com(0x80 + 0x40 + 6);
				delay(2);
				write_data(table1[ahourshi1]);
				write_com(0x80 + 0x40 + 8);
				write_data(':');
				delay(2);
				aminge1 = amin1 % 10;
				aminshi1 = amin1 / 10;
				write_com(0x80 + 0x40 + 10);
				write_data(table1[aminge1]);
				delay(5);
				write_com(0x80 + 0x40 + 9);
				delay(2);
				write_data(table1[aminshi1]);
			}
			qi();
		}
		if (cnt1 == 2)
		{
			write_com(0x80 + 0x40);
			for (i = 0; i < 6; ++i)
				write_data(Alarm_2[i]); //��ʾ�������õ�ʱ��
			while (!key2)
			{
				ahourge2 = ahour2 % 10;
				ahourshi2 = ahour2 / 10;
				write_com(0x80 + 0x40 + 7);
				write_data(table1[ahourge2]);
				delay(5);
				write_com(0x80 + 0x40 + 6);
				delay(2);
				write_data(table1[ahourshi2]);
				write_com(0x80 + 0x40 + 8);
				write_data(':');
				delay(2);
				aminge2 = amin2 % 10;
				aminshi2 = amin2 / 10;
				write_com(0x80 + 0x40 + 10);
				write_data(table1[aminge2]);
				delay(5);
				write_com(0x80 + 0x40 + 9);
				delay(2);
				write_data(table1[aminshi2]);
			}
			qi();
		}
		if (cnt1 == 3)
		{
			write_com(0x80 + 0x40);
			for (i = 0; i < 6; ++i)
				write_data(Alarm_3[i]); //��ʾ�������õ�ʱ��
			while (!key2)
			{
				ahourge3 = ahour3 % 10;
				ahourshi3 = ahour3 / 10;
				write_com(0x80 + 0x40 + 7);
				write_data(table1[ahourge3]);
				delay(5);
				write_com(0x80 + 0x40 + 6);
				delay(2);
				write_data(table1[ahourshi3]);
				write_com(0x80 + 0x40 + 8);
				write_data(':');
				delay(2);
				aminge3 = amin3 % 10;
				aminshi3 = amin3 / 10;
				write_com(0x80 + 0x40 + 10);
				write_data(table1[aminge3]);
				delay(5);
				write_com(0x80 + 0x40 + 9);
				delay(2);
				write_data(table1[aminshi3]);
			}
			qi();
		}
		if (cnt1 == 4)
		{
			write_com(0x80 + 0x40);
			for (i = 0; i < 6; ++i)
				write_data(Alarm_4[i]); //��ʾ�������õ�ʱ��
			while (!key2)
			{
				ahourge4 = ahour4 % 10;
				ahourshi4 = ahour4 / 10;
				write_com(0x80 + 0x40 + 7);
				write_data(table1[ahourge4]);
				delay(5);
				write_com(0x80 + 0x40 + 6);
				delay(2);
				write_data(table1[ahourshi4]);
				write_com(0x80 + 0x40 + 8);
				write_data(':');
				delay(2);
				aminge4 = amin4 % 10;
				aminshi4 = amin4 / 10;
				write_com(0x80 + 0x40 + 10);
				write_data(table1[aminge4]);
				delay(5);
				write_com(0x80 + 0x40 + 9);
				delay(2);
				write_data(table1[aminshi4]);
			}
			qi();
		}
		if (cnt1 > 4)
			cnt1 = 0;
	}
	else if (key3 == 0)
	{ //���¹��ܼ�key3������������
		cnt++;
		delay(10);
		if (cnt == 1)
		{
			while (!key3)
				;
			write_com(0x80 + 0x40);
			for (i = 0; i < 6; ++i)
				write_data(Alarm_1[i]);
			ahourge1 = ahour1 % 10;
			ahourshi1 = ahour1 / 10;
			write_com(0x80 + 0x40 + 7);
			write_data(table1[ahourge1]);
			delay(5);
			write_com(0x80 + 0x40 + 6);
			delay(2);
			write_data(table1[ahourshi1]);
			write_com(0x80 + 0x40 + 8);
			write_data(':');
			delay(2);
			aminge1 = amin1 % 10;
			aminshi1 = amin1 / 10;
			write_com(0x80 + 0x40 + 10);
			write_data(table1[aminge1]);
			delay(5);
			write_com(0x80 + 0x40 + 9);
			delay(2);
			write_data(table1[aminshi1]);
			alarm11();
		}
		if (cnt == 2)
		{
			while (!key3)
				;
			write_com(0x80 + 0x40);
			for (i = 0; i < 6; ++i)
				write_data(Alarm_2[i]);
			ahourge2 = ahour2 % 10;
			ahourshi2 = ahour2 / 10;
			write_com(0x80 + 0x40 + 7);
			write_data(table1[ahourge2]);
			delay(5);
			write_com(0x80 + 0x40 + 6);
			delay(2);
			write_data(table1[ahourshi2]);
			write_com(0x80 + 0x40 + 8);
			write_data(':');
			delay(2);
			aminge2 = amin2 % 10;
			aminshi2 = amin2 / 10;
			write_com(0x80 + 0x40 + 10);
			write_data(table1[aminge2]);
			delay(5);
			write_com(0x80 + 0x40 + 9);
			delay(2);
			write_data(table1[aminshi2]);
			alarm22();
		}
		if (cnt == 3)
		{
			while (!key3)
				;
			write_com(0x80 + 0x40);
			for (i = 0; i < 6; ++i)
				write_data(Alarm_3[i]);
			ahourge3 = ahour3 % 10;
			ahourshi3 = ahour3 / 10;
			write_com(0x80 + 0x40 + 7);
			write_data(table1[ahourge3]);
			delay(5);
			write_com(0x80 + 0x40 + 6);
			delay(2);
			write_data(table1[ahourshi3]);
			write_com(0x80 + 0x40 + 8);
			write_data(':');
			delay(2);
			aminge3 = amin3 % 10;
			aminshi3 = amin3 / 10;
			write_com(0x80 + 0x40 + 10);
			write_data(table1[aminge3]);
			delay(5);
			write_com(0x80 + 0x40 + 9);
			delay(2);
			write_data(table1[aminshi3]);
			alarm33();
		}
		if (cnt == 4)
		{
			while (!key3)
				;
			write_com(0x80 + 0x40);
			for (i = 0; i < 6; ++i)
				write_data(Alarm_4[i]);
			ahourge4 = ahour4 % 10;
			ahourshi4 = ahour4 / 10;
			write_com(0x80 + 0x40 + 7);
			write_data(table1[ahourge4]);
			delay(5);
			write_com(0x80 + 0x40 + 6);
			delay(2);
			write_data(table1[ahourshi4]);
			write_com(0x80 + 0x40 + 8);
			write_data(':');
			delay(2);
			aminge4 = amin4 % 10;
			aminshi4 = amin4 / 10;
			write_com(0x80 + 0x40 + 10);
			write_data(table1[aminge4]);
			delay(5);
			write_com(0x80 + 0x40 + 9);
			delay(2);
			write_data(table1[aminshi4]);
			alarm44();
		}
		if (cnt > 4)
			cnt = 0;
	}
	else if (key4 == 0) //�¹��ܼ�key4�ر��������ֵ�����
		delay(5);
	if (key4 == 0)
	{
		while (!key4)
			;
		flag = 0;  //�޸����ӱ�־λ
		sound = 1; //�ر�������
	}
}

void lcd_init()
{ //LCD��ʼ��
	lcden = 0;
	lcdrw = 0;
	write_com(0x38); //����8λ��ʽ��2��
	write_com(0x0c); //������ʾ���ع�꣬����˸
	write_com(0x06); //�趨���뷽ʽ��������ת��
	write_com(0x01); //�����Ļ��ʾ
	delay(2);
	write_com(0x80);
	for (i = 0; i < 16; i++)
	{
		write_data(table2[i]); //д����ʾʱ������
		delay(1);
	}
}

void pannian()
{
	if (nian % 400 == 0 || (nian % 4 == 0 && nian % 100 != 0))
	{ //����Ϊ����
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
	else if (!(nian % 400 == 0) || !(nian % 4 == 0 && nian % 100 != 0))
	{ //����Ϊƽ��
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
{ //C51��ʼ��
	key1 = 1;
	key2 = 1;
	key3 = 1;
	key4 = 1;
	sound = 1;
	TMOD = 0x10; //��ʱ��1�����ڷ�ʽ1
	TL1 = 0xB0;
	TH1 = 0x3C; //������ֵ15536
	EA = 1;
	ET1 = 1;
	TR1 = 1;
}

void speak()
{ //���ӡ����˵㡱����
	if ((amin1 == min && ahour1 == hour || (amin2 == min && ((hour >= 7 && hour <= 12) || (hour >= 14 && hour <= 21))) || (amin3 == min && ((hour >= 7 && hour <= 12) || (hour >= 14 && hour <= 21))) || amin4 == min && ahour4 == hour) && flag == 1)
	{
		//�κ�һ�����ӡ����㡱���������־λΪ1ʱ��������
		delay(5);
		sound = 0;
	}
	delay(10);
	delay(10);
	delay(10);
	sound = 1;
}

void led1() interrupt 3
{
	TL1 = 0xB0;
	TH1 = 0x3C;
	if ((amin1 != min || ahour1 != hour) && (amin2 != min) && (amin3 != min) && (amin4 != min || ahour4 != hour))
	{
		//�����κ�һ������ʱ�������������־λΪ1��Ϊ��һ��������׼��
		flag = 1;
		sound = 1; //�ر�������
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
		keyscan1(); //����ɨ��
		minge = min % 10;
		minshi = min / 10;
		write_com(0x80 + 9);
		write_data(table1[minge]);
		delay(5);
		write_com(0x80 + 8);
		write_data(table1[minshi]);
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
		secge = sec % 10;
		secshi = sec / 10;
		write_com(0x80 + 15);
		write_data(table1[secge]);
		delay(5);
		write_com(0x80 + 14);
		write_data(table1[secshi]);
		qi();
	}
}