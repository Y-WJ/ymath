// test.cpp : 定义控制台应用程序的入口点。
//

#include "stdlib.h"

//说明书
//---------------------------------headfile-------------------------------------------------
struct array
{
	int x;							//行数
	int y;							//列数
	float **p;                      //矩阵首地址
};

array createarray(int x, int y);			//1.新建矩阵:	参数为行数列数 新矩阵所有元素都是0，行列坐标往右下偏置1,即a.p[0][y]和a.p[x][0]在所有函数中默认不保存元素
bool evaluation(array a, array b);			//2.赋值:		把b矩阵的元素赋给a  成功返回1，大小不一返回0
bool output(array a);						//3.输出
array transpose(array &a);					//4.转置:		原矩阵被转置，返回转置矩阵
array deleteline(array &a, int x, int y);   //5.删除行列:	删除a的x行或y列，取值超出范围则空操作，注意搬移后多出来的内存被释放掉了  请勿往这里赋值
array addline(array &a, int x, int y);		//6.增加行列:	增加第x行或第y列,元素为0，取值0则空操作
array deletearray(array &a);                //7.释放矩阵
array cofactor(array a, int x, int y);      //8.求余子式:	求a[x][y]的余子式,x or y超出范围返回空矩阵,不会操作原矩阵
float mod(array a);							//9.求模:		不是方阵返回0
array dot(array a, array b);				//10.矩阵点积:	若行列冲突，返回行列数为0的空矩阵
array moveline(array &a,int x,int y,float c);//11.行操作:	原矩阵变为x+y*c，返回操作后的矩阵		
array triangulation(array a);				//12.上三角化:	原矩阵不动，返回上三角阵
int rank(array a);							//13.求秩
array inverse(array a);						//14.求逆:		不会操作原矩阵，不可逆则返回空矩阵



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

array deletearray(array &a)              //释放矩阵占用的内存，行列数归零
{
	for (int i = a.x; i >= 0; i--)
		free(a.p[i]);
	free(a.p);
	a.x = 0;
	a.y = 0;
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
	printf("\n");
	return 1;
}

array moveline(array &a, int x, int y, float c)
{
	for (int j = 1; j <= a.y; j++)
		a.p[x][j] += a.p[y][j] * c;
	return a;
}

array triangulation(array a)    //返回a经行变换所得的上三角阵
{
	array r = createarray(a.x, a.y);
	evaluation(r, a);
	for (int i = 1; i < r.x; i++)             //这里第i行+上之后所有行，保证矩阵成大顶堆形状
	{                                         //即不会出现i行第一个非零元素所在列比第i+n行第一个
		for (int k = i + 1; k <= r.x; k++)		//非零元所在列序号小的情况
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
