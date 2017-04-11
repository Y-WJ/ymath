// test.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdlib.h"

//˵����
//---------------------------------headfile-------------------------------------------------

//---------------------------------matrix operation----------------------------------------------------
struct array
{
	int x;							//����
	int y;							//����
	double **p;                      //�����׵�ַ
};

array createarray(int x, int y);			//1.�½�����:	����Ϊ�������� �¾�������Ԫ�ض���0����������������ƫ��1,��a.p[0][y]��a.p[x][0]�����к�����Ĭ�ϲ�����Ԫ��
bool evaluation(array a, array b);			//2.��ֵ:		��b�����Ԫ�ظ���a  �ɹ�����1����С��һ����0
bool output(array a);						//3.���
array transpose(array a);					//4.ת��:		ԭ����ת�ã�����ת�þ���
array deleteline(array &a, int x, int y);   //5.ɾ������:	ɾ��a��x�л�y�У�ȡֵ������Χ��ղ�����ע����ƺ��������ڴ汻�ͷŵ���  ���������︳ֵ
array addline(array &a, int x, int y);		//6.��������:	���ӵ�x�л��y��,Ԫ��Ϊ0��ȡֵ0��ղ���
array deletearray(array &a);                //7.�ͷž���
array cofactor(array a, int x, int y);      //8.������ʽ:	��a[x][y]������ʽ,x or y������Χ���ؿվ���,�������ԭ����
float mod(array a);							//9.��ģ:		���Ƿ��󷵻�0
array dot(array a, array b);				//10.������:	�����г�ͻ������������Ϊ0�Ŀվ���
array moveline(array &a,int x,int y,double c);//11.�в���:	ԭ�����Ϊx+y*c�����ز�����ľ���		
array triangulation(array a);				//12.�����ǻ�:	ԭ���󲻶���������������
int rank(array a);							//13.����
array inverse(array a);						//14.����:		�������ԭ���󣬲������򷵻ؿվ���
array add(array a, array b,double c);		//15.�����:	����a+b*c,�������ԭ����
array selectline(array &a, array b, int x);	//16.�и�ֵ:    ��һά������ֵb�ĵ�x�л�x��
//---------------------------------data process----------------------------------------------
array initdataset(char *a);                 //17.��ʼ��:	��·���ַ���a��csv�ļ���ʼ������,���һ��Ϊ���
array LG(array a);							//18.���Իع�:  ����������������Իع���(������)
array LDA(array a);							//19.�����б�:  ������������������б����



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
array transpose(array a)           //ת��
{
	array r = createarray(a.y, a.x);
	for(int i=1;i<=r.x;i++)
		for (int j = 1; j <= r.y; j++)
			r.p[i][j] = a.p[j][i];
	return r;
}

array createarray(int x, int y)     //�½����� ����Ϊ�������� �¾�������Ԫ�ض���0  ��������������ƫ��1
{									//��a.p[0][y]��a.p[x][0]�ڱ�����Ĭ�ϲ�����Ԫ��
	array a;
	a.x = x;
	a.y = y;
	a.p= (double**)malloc(sizeof(double)*(x+1));
	for (int i = 0; i <= x; i++)
		a.p[i] = (double *)malloc(sizeof(double)*(y+1));
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
		a.p = (double**)realloc(a.p,sizeof(double)*a.x );
		a.x--;
	}
	if (y <= a.y&&y > 0)
	{
		for (int j = y; j < a.y; j++)
			for (int i = 1; i <= a.x; i++)
				a.p[i][j] = a.p[i][j+1];
		for (int i = 0; i <= a.x; i++)
			a.p[i] = (double *)realloc(a.p[i],sizeof(double)*a.y);
		a.y--;
	}
	return a;
}

array addline(array &a, int x, int y)
{
	if (x > 0&&x<=a.x+1)
	{
		a.p = (double**)realloc(a.p, sizeof(double)*(a.x + 2));
		a.p[a.x + 1] = (double*)malloc(sizeof(double)*(a.y + 1));
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
			a.p[i] = (double*)realloc(a.p[i], sizeof(double)*(a.y+2));
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
		printf("error_8");
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
			printf("%lf ", a.p[i][j]);
		printf("\n");
	}
	printf("\n");
	return 1;
}

array moveline(array &a, int x, int y, double c)
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
			double m = r.p[k][p] / r.p[i][p];
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
	array r,b;
	int c = rank(a);
	b = createarray(a.x, a.y);
	evaluation(b, a);
	if (c != a.x || c != a.y)
	{
		r.x = 0;
		r.y = 0;
		r.p = NULL;
		printf("error_14");
		return r;
	}
	r = createarray(a.x, a.y);
	for (int i = 1; i <= b.x; i++)
		r.p[i][i] = 1;
	for (int i = 1; i < b.x; i++)             	                                     
		for (int k = i + 1; k <= a.x; k++)	
		{
			moveline(b, i, k, 1);
			moveline(r, i, k, 1);
		}
	for (int i = 1; i < b.x; i++)
	{
		int p = i;
		while (b.p[i][p] == 0)
			p++;
		for (int k = i + 1; k <= b.x; k++)
		{
			double m = b.p[k][p] / b.p[i][p]*(-1);
			moveline(b, k, i, m);
			moveline(r, k, i, m);
		}
	}
	for (int i = b.x; i > 1; i--)
	{
		for (int k = i - 1; k >= 1; k--)
		{
			double n = b.p[k][i] / b.p[i][i] * (-1);
			moveline(b, k, i, n);
			moveline(r, k, i, n);
		}
	}
	for (int i = 1; i <= b.x; i++)
		moveline(r, i, i, ((b.p[i][i] - 1) / b.p[i][i]*(-1)));
	return r;
}

array add(array a, array b,double c)
{
	array r;
	if (a.x != b.x || a.y != b.y)
	{
		r.x = 0;
		r.y = 0;
		r.p = NULL;
		printf("error_15");
		return r;
	}
	r = createarray(a.x, a.y);
	for (int i = 1; i <= r.x; i++)
		for (int j = 1; j <= r.y; j++)
			r.p[i][j] = a.p[i][j] + b.p[i][j] * c;
	return r;
}


array selectline(array &a, array b, int x)    //16.
{
	if (a.y == 1 && a.x == b.x)
	{
		for (int i = 1; i <= a.x; i++)
			a.p[i][1] = b.p[i][x];
		return a;
	}
	if (a.x == 1 && a.y == b.y)
	{
		for (int i = 1; i <= a.y; i++)
			a.p[1][i] = b.p[x][i];
		return a;
	}
	printf("error_16");
	return a;
}

array initdataset(char *a)          //���ؾ���ÿ��Ϊһ��������csv�ļ���һ�б������������ö��Ż�ֺŷָ�
{
	FILE *fp;
	array r;
	char c;
	char str[30];
	int x, y, i, j, k;
	if ((fp = fopen(a, "rb")) == NULL)
	{
		printf("error_17");
		r.x = 0;
		r.y = 0;
		r.p = NULL;
		return r;
	}
	x = 0;
	y = 1;
	while ((c=fgetc(fp)) != '\n')
	{
		if (c == ',' || c == ';')
			y++;
	}
	while ((c = fgetc(fp)) != EOF)
	{
		if (c == '\n')
			x++;
	}
	r = createarray(x, y);
	rewind(fp);
	while ((c = fgetc(fp)) != '\n');
	i = 1;
	j = 1;
	k = 0;
	while ((c = fgetc(fp)) != EOF)
	{
		if (c != ','&&c != '\n'&&c != '\r'&&c != ';')
			str[k++] = c;
		else if (c == ',' || c == '\n' || c == ';')
		{
			str[k] = '\0';
			r.p[i][j] = atof(str);
			str[0] = '\0';
			k = 0;
			if (j < r.y)
				j++;
			else
			{
				i++;
				j = 1;
			}
		}
	}
	fclose(fp);
	return r;
}

array LG(array a)
{
	array w = createarray(a.y , 1);
	array y = createarray(a.x, 1);
	addline(a, 0, a.y);
	for (int i = 1; i <= a.x; i++)
		a.p[i][a.y - 1] = 1;
	for (int i = 1; i <= a.x; i++)
		y.p[i][1] = a.p[i][a.y];
	deleteline(a, 0, a.y);
	w = dot(dot(inverse(dot(transpose(a), a)), transpose(a)), y);
	return w;
}

array LDA(array a)
{

	array y = createarray(a.x, 1);
	selectline(y, a, a.y);
	deleteline(a, 0, a.y);
	array w = createarray(a.y, 1);
	array Sw = createarray(a.y, a.y);
	array u0 = createarray(a.y, 1);
	array u1 = createarray(a.y, 1);
	array x = createarray(a.y, 1);
	array E0 = createarray(a.y, a.y);
	array E1 = createarray(a.y, a.y);
	double p = 0;
	double n = 0;
	for (int i = 1; i <= y.x; i++)
	{
		p += y.p[i][1];
		n += (1 - y.p[i][1]);
	}
	for (int i = 1; i <= a.x; i++)
	{
		x = transpose(x);
		selectline(x, a, i);
		x = transpose(x);
		if (y.p[i][1] == 1)
			u0 = add(u0, x, 1 / p);
		else
			u1 = add(u1, x, 1 / n);
	}
	for (int i = 1; i <= a.x; i++)
	{
		x = transpose(x);
		selectline(x, a, i);
		x = transpose(x);
		if (y.p[i][1] == 0)
			E0 = add(E0, dot(add(x, u0, -1), transpose(add(x, u0, -1))), 1);
		else
			E1 = add(E1, dot(add(x, u1, -1), transpose(add(x, u1, -1))), 1);
	}
	Sw = add(E0, E1, 1);
	w = dot(inverse(Sw), add(u0, u1, -1));
	return w;
}
