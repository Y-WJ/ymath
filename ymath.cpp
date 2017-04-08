// test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "stdlib.h"

//说明书
//---------------------------------headfile-------------------------------------------------
struct array
{
	int x;							//行数
	int y;							//列数
	float **p;                      //矩阵首地址
};

array createarray(int x, int y);  //新建矩阵 参数为行数列数 新矩阵所有元素都是0，行列坐标往右下偏置1,即a.p[0][y]和a.p[x][0]在所有函数中默认不保存元素
bool evaluation(array a, array b);//把b矩阵的元素赋给a  成功返回1，大小不一返回0
bool output(array a);             //输出矩阵
array transpose(array &a);        //转置，传引用
array deleteline(array &a, int x, int y);   //删除a的x行或y列，取值超出范围则空操作，注意搬移后多出来的内存被释放掉了  请勿往这里赋值
array cofactor(array a, int x, int y);      //求a[x][y]的余子式,x or y超出范围返回空矩阵,不会操作原矩阵
float mod(array a);               //求模  不是方阵返回0
array dot(array a, array b);      //矩阵点积，若行列冲突，返回行列数为0的空矩阵



//-------------------------------sourcefile---------------------------------------------------
bool evaluation(array a, array b)   //把b矩阵的元素赋给a  成功返回1，大小不一返回0
{
	if (a.x != b.x || a.y != b.y)
		return 0;
	for (int i = 1; i <= a.x; i++)
		for (int j = 1; j <= a.y; j++)
			a.p[i][j] = b.p[i][j];
	return 1;
}
array transpose(array &a)           //转置，传引用
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

array createarray(int x, int y)     //新建矩阵 参数为行数列数 新矩阵所有元素都是0  行列坐标往右下偏置1
{									//即a.p[0][y]和a.p[x][0]在本库中默认不保存元素
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

array dot(array a, array b)         //矩阵点积，若行列冲突，返回行列数为0的空矩阵
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

array deleteline(array &a, int x, int y)     //删除a的x行或y列，取值超出范围则空操作，
{                                            //注意搬移候多出来的内存被释放掉了  请勿往这里赋值
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

array cofactor(array a,int x,int y)         //求a[x][y]的余子式,x or y超出范围返回空矩阵,不会操作原矩阵
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

float mod(array a)              //求模  不是方阵返回0
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

bool output(array a)             //输出矩阵
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

