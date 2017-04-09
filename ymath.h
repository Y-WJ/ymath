// test.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdlib.h"

//˵����
//---------------------------------headfile-------------------------------------------------
struct array
{
	int x;							//����
	int y;							//����
	float **p;                      //�����׵�ַ
};

array createarray(int x, int y);			//1.�½�����:	����Ϊ�������� �¾�������Ԫ�ض���0����������������ƫ��1,��a.p[0][y]��a.p[x][0]�����к�����Ĭ�ϲ�����Ԫ��
bool evaluation(array a, array b);			//2.��ֵ:		��b�����Ԫ�ظ���a  �ɹ�����1����С��һ����0
bool output(array a);						//3.���
array transpose(array &a);					//4.ת��:		ԭ����ת�ã�����ת�þ���
array deleteline(array &a, int x, int y);   //5.ɾ������:	ɾ��a��x�л�y�У�ȡֵ������Χ��ղ�����ע����ƺ��������ڴ汻�ͷŵ���  ���������︳ֵ
array addline(array &a, int x, int y);		//6.��������:	���ӵ�x�л��y��,Ԫ��Ϊ0��ȡֵ0��ղ���
array deletearray(array &a);                //7.�ͷž���
array cofactor(array a, int x, int y);      //8.������ʽ:	��a[x][y]������ʽ,x or y������Χ���ؿվ���,�������ԭ����
float mod(array a);							//9.��ģ:		���Ƿ��󷵻�0
array dot(array a, array b);				//10.������:	�����г�ͻ������������Ϊ0�Ŀվ���
array moveline(array &a,int x,int y,float c);//11.�в���:	ԭ�����Ϊx+y*c�����ز�����ľ���		
array triangulation(array a);				//12.�����ǻ�:	ԭ���󲻶���������������
int rank(array a);							//13.����
array inverse(array a);						//14.����:		�������ԭ���󣬲������򷵻ؿվ���



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

array addline(array &a, int x, int y)
{
	if (x > 0&&x<=a.x+1)
	{
		a.p = (float**)realloc(a.p, sizeof(float)*(a.x + 2));
		a.p[a.x + 1] = (float*)malloc(sizeof(float)*(a.y + 1));
		for (int i = a.x + 1; i > x; i--)
			for (int j = 1; j <= a.y; j++)
				a.p[i][j] = a.p[i - 1][j];
		for (int j = 1; j <= a.y; j++)
			a.p[x][j] = 0;
		a.x++;
	}
	if (y > 0&&x<=a.y+1)
	{
		for (int i = 0; i <= a.x; i++)
			a.p[i] = (float*)realloc(a.p[i], sizeof(float)*(a.y+2));
		for (int j = a.y + 1; j > y; j--)
			for (int i = 1; i <= a.x; i++)
				a.p[i][j] = a.p[i][j - 1];
		for (int i = 1; i <= a.x; i++)
			a.p[i][y] = 0;
		a.y++;
	}
	return a;
}

array deletearray(array &a)              //�ͷž���ռ�õ��ڴ棬����������
{
	for (int i = a.x; i >= 0; i--)
		free(a.p[i]);
	free(a.p);
	a.x = 0;
	a.y = 0;
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
	printf("\n");
	return 1;
}

array moveline(array &a, int x, int y, float c)
{
	for (int j = 1; j <= a.y; j++)
		a.p[x][j] += a.p[y][j] * c;
	return a;
}

array triangulation(array a)    //����a���б任���õ���������
{
	array r = createarray(a.x, a.y);
	evaluation(r, a);
	for (int i = 1; i < r.x; i++)             //�����i��+��֮�������У���֤����ɴ󶥶���״
	{                                         //���������i�е�һ������Ԫ�������бȵ�i+n�е�һ��
		for (int k = i + 1; k <= r.x; k++)		//����Ԫ���������С�����
			for (int j = 1; j <= r.y; j++)
				r.p[i][j] += r.p[k][j];
	}
//	output(r);
	for (int i = 1; i < r.x; i++)
	{
		int p = i;
		while (r.p[i][p] == 0)
			p++;
		for (int k = i+1; k<=r.x; k++)
		{
			float m = r.p[k][p] / r.p[i][p];
			for (int j = 0; j <= r.y; j++)
				r.p[k][j] -= r.p[i][j] * m;
		}
	}
	return r;
}

int rank(array a)
{
	a = triangulation(a);
	int n= 0;
	for (int i = 1; i <= a.x; i++)
	{
		int k = 0;
		for (int j = 1; j <= a.y; j++)
			if (a.p[i][j] != 0)
				k = 1;
		if (k == 1)
			n++;
	}
	return n ;
}

array inverse(array a)
{
	array r;
	int c = rank(a);
	if (c != a.x || c != a.y)
	{
		r.x = 0;
		r.y = 0;
		r.p = NULL;
	}
	r = createarray(a.x, a.y);
	for (int i = 1; i <= a.x; i++)
		r.p[i][i] = 1;
	for (int i = 1; i < a.x; i++)             	                                     
		for (int k = i + 1; k <= a.x; k++)	
		{
			moveline(a, i, k, 1);
			moveline(r, i, k, 1);
		}
	for (int i = 1; i < a.x; i++)
	{
		int p = i;
		while (a.p[i][p] == 0)
			p++;
		for (int k = i + 1; k <= a.x; k++)
		{
			float m = a.p[k][p] / a.p[i][p]*(-1);
			moveline(a, k, i, m);
			moveline(r, k, i, m);
		}
	}
	for (int i = a.x; i > 1; i--)
	{
		for (int k = i - 1; k >= 1; k--)
		{
			float n = a.p[k][i] / a.p[i][i] * (-1);
			moveline(a, k, i, n);
			moveline(r, k, i, n);
		}
	}
	for (int i = 1; i <= a.x; i++)
		moveline(r, i, i, ((a.p[i][i] - 1) / a.p[i][i]*(-1)));
	return r;
}
