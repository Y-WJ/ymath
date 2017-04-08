// test.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "stdlib.h"

//˵����
//---------------------------------headfile-------------------------------------------------
struct array
{
	int x;							//����
	int y;							//����
	float **p;                      //�����׵�ַ
};

array createarray(int x, int y);  //�½����� ����Ϊ�������� �¾�������Ԫ�ض���0����������������ƫ��1,��a.p[0][y]��a.p[x][0]�����к�����Ĭ�ϲ�����Ԫ��
bool evaluation(array a, array b);//��b�����Ԫ�ظ���a  �ɹ�����1����С��һ����0
bool output(array a);             //�������
array transpose(array &a);        //ת�ã�������
array deleteline(array &a, int x, int y);   //ɾ��a��x�л�y�У�ȡֵ������Χ��ղ�����ע����ƺ��������ڴ汻�ͷŵ���  ���������︳ֵ
array cofactor(array a, int x, int y);      //��a[x][y]������ʽ,x or y������Χ���ؿվ���,�������ԭ����
float mod(array a);               //��ģ  ���Ƿ��󷵻�0
array dot(array a, array b);      //�������������г�ͻ������������Ϊ0�Ŀվ���



//-------------------------------sourcefile---------------------------------------------------
bool evaluation(array a, array b)   //��b�����Ԫ�ظ���a  �ɹ�����1����С��һ����0
{
	if (a.x != b.x || a.y != b.y)
		return 0;
	for (int i = 1; i <= a.x; i++)
		for (int j = 1; j <= a.y; j++)
			a.p[i][j] = b.p[i][j];
	return 1;
}
array transpose(array &a)           //ת�ã�������
{
	float temp;
	for(int i=1;i<=a.x;i++)
		for (int j = i; j <= a.y; j++)
		{
			temp = a.p[i][j];
			a.p[i][j] = a.p[j][i];
			a.p[j][i] = temp;
		}
	return a;
}

array createarray(int x, int y)     //�½����� ����Ϊ�������� �¾�������Ԫ�ض���0  ��������������ƫ��1
{									//��a.p[0][y]��a.p[x][0]�ڱ�����Ĭ�ϲ�����Ԫ��
	array a;
	a.x = x;
	a.y = y;
	a.p= (float**)malloc(sizeof(float)*(x+1));
	for (int i = 0; i <= x; i++)
		a.p[i] = (float *)malloc(sizeof(float)*(y+1));
	for (int i = 0; i <=a.x; i++)
		for (int j = 0; j <= a.y; j++)
			a.p[i][j] = 0;
	return a;
}

array dot(array a, array b)         //�������������г�ͻ������������Ϊ0�Ŀվ���
{
	array r;
	r.x = 0;
	r.y = 0;
	r.p = NULL;
	if (a.y != b.x)
		return r;
	r = createarray(a.x, b.y);
	for(int i=1;i<=r.x;i++)
		for (int j = 1; j <= r.y; j++)
			for (int k = 1; k <= a.y; k++)
				r.p[i][j] += a.p[i][k] * b.p[k][j];
	return r;
}

array deleteline(array &a, int x, int y)     //ɾ��a��x�л�y�У�ȡֵ������Χ��ղ�����
{                                            //ע����ƺ��������ڴ汻�ͷŵ���  ���������︳ֵ
	if (x <= a.x&&x > 0)
	{
		for (int i = x; i < a.x; i++)
			for (int j = 1; j <= a.y; j++)
				a.p[i][j] = a.p[i + 1][j];
		free(a.p[a.x]);
		a.p = (float**)realloc(a.p,sizeof(float)*a.x );
		a.x--;
	}
	if (y <= a.y&&y > 0)
	{
		for (int j = y; j < a.y; j++)
			for (int i = 1; i <= a.x; i++)
				a.p[i][j] = a.p[i ][j+1];
		for (int i = 0; i <= a.x; i++)
			a.p[i] = (float *)realloc(a.p[i],sizeof(float)*a.y);
		a.y--;
	}
	return a;
}

array cofactor(array a,int x,int y)         //��a[x][y]������ʽ,x or y������Χ���ؿվ���,�������ԭ����
{
	array r;
	if (x > a.x || y > a.y || x < 1 || y < 1)
	{
		r.x = 0;
		r.y = 0;
		r.p = NULL;
		return r;
	}
	r = createarray(a.x,a.y);
	evaluation(r, a);
	return deleteline(r, x, y);
}

float mod(array a)              //��ģ  ���Ƿ��󷵻�0
{
	if (a.x != a.y)
		return 0;
	if (a.x == 1)
		return a.p[1][1];
	else
	{
		int i = 1;
		float sum=0;
		for (int j = 1; j <= a.y; j++, i *= -1)
			sum += i*a.p[1][j] * mod(cofactor(a, 1, j));
		return sum;
	}
}

bool output(array a)             //�������
{
	if (a.x <= 0 || a.y <= 0)
		return 0;
	for (int i = 1; i <= a.x; i++)
	{
		for (int j = 1; j <=a.y ; j++)
			printf("%f ", a.p[i][j]);
		printf("\n");
	}
	return 1;
}

int main()
{
//	array a,b,c;
//	float f;
//	a = createarray(3, 3);
//	b = createarray(2, 1);
//	a.p[1][1] = 1;
//	a.p[1][2] = 2;
//	a.p[2][1] = 3;
//	a.p[2][2] = 4;
//	b.p[1][1] = 1;
//	b.p[2][1] = 2;
//	a.p[3][3] = 5;
//	c = dot(a, b);
//	transpose(a);
//	deleteline(a, 2, 0);
//	b = cofactor(a, 1, 1);
//	output(a);
//	output(b);
//	output(c);
//	f = mod(a);
//	printf("%f\n", f);
    return 0;
}

