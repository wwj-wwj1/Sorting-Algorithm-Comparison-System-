#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<string.h>
#include <chrono>
void* getdata(int* a, int n, const char* filename);//生成数据 
void readdata(int* a, int n, const char* filename);//读取数据
void showdata(int* a, int n, const char* filename);//显示数据 
void insertsort(int* a, int n, const char* filename);//插入排序 
void shell(int* a, int n, const char* filename);//希尔排序 
void shellsort(int* a, int n, int t);
void bubble(int* a, int n, const char* filename);//起泡排序 
void quick(int* a, int n, const char* filename);//快排 
int pivot(int* a, int low, int high);
void quicksort(int* a, int low, int high);
void selectsort(int* a, int n, const char* filename);//选择排序 
void heapsort(int* a, int n, const char* filename);//堆排 
void heapadjust(int* a, int n, int index);
void Mergesort(int* a, int n, const char* filename);//归并排序 
void Merge(int* b, int* c, int low, int mid, int high);
void showMenu()
{
	printf("请选择要运行的排序算法（输入对应的数字）：\n");
	printf("1. 直接插入排序\n");
	printf("2. 希尔排序\n");
	printf("3. 冒泡排序\n");
	printf("4. 快速排序\n");
	printf("5. 选择排序\n");
	printf("6. 堆排序\n");
	printf("7. 归并排序\n");
	printf("0. 退出\n");
}


int main()
{
	int* a, n;
	system("color 1E");
	printf("\n--------------排序算法比较--------------\n\n");  //说明该代码的实现功能 
	printf("请输入需要的数据规模：");
	scanf("%d", &n);
	while (n > 0)
	{
		a = (int*)malloc((n + 1) * sizeof(int));
		getdata(a, n, "data.txt");

		using namespace std::chrono;

		auto start = high_resolution_clock::now();
		readdata(a, n, "data.txt");
		insertsort(a, n, "insertsort.txt");
		auto end = high_resolution_clock::now();
		duration<double> cpu_time_used = duration_cast<duration<double>>(end - start);
		printf("直接插入排序运行时间: %.9f 秒\n", cpu_time_used.count());

		start = high_resolution_clock::now();
		readdata(a, n, "data.txt");
		shell(a, n, "shell.txt");
		end = high_resolution_clock::now();
		cpu_time_used = duration_cast<duration<double>>(end - start);
		printf("希尔排序运行时间: %.9f 秒\n", cpu_time_used.count());

		start = high_resolution_clock::now();
		readdata(a, n, "data.txt");
		bubble(a, n, "bubble.txt");
		end = high_resolution_clock::now();
		cpu_time_used = duration_cast<duration<double>>(end - start);
		printf("冒泡排序运行时间: %.9f 秒\n", cpu_time_used.count());

		start = high_resolution_clock::now();
		readdata(a, n, "data.txt");
		quick(a, n, "quick.txt");
		end = high_resolution_clock::now();
		cpu_time_used = duration_cast<duration<double>>(end - start);
		printf("快速排序运行时间: %.9f 秒\n", cpu_time_used.count());

		start = high_resolution_clock::now();
		readdata(a, n, "data.txt");
		selectsort(a, n, "selectsort.txt");
		end = high_resolution_clock::now();
		cpu_time_used = duration_cast<duration<double>>(end - start);
		printf("选择排序运行时间: %.9f 秒\n", cpu_time_used.count());

		start = high_resolution_clock::now();
		readdata(a, n, "data.txt");
		heapsort(a, n, "heapsort.txt");
		end = high_resolution_clock::now();
		cpu_time_used = duration_cast<duration<double>>(end - start);
		printf("堆排序运行时间: %.9f 秒\n", cpu_time_used.count());

		start = high_resolution_clock::now();
		readdata(a, n, "data.txt");
		Mergesort(a, n, "mergesort.txt");
		end = high_resolution_clock::now();
		cpu_time_used = duration_cast<duration<double>>(end - start);
		printf("归并排序运行时间: %.9f 秒\n", cpu_time_used.count());

		printf("\n请输入需要的数据规模：");
		scanf("%d", &n);
		free(a);
	}
}

void showdata(int* a, int n, const char* filename)
{
	FILE* file = fopen(filename, "w");
	if (file == NULL) {
		printf("无法打开文件 %s\n", filename);
		return;
	}
	int i, j = 0;
	for (i = 1; i <= n; i++)
	{
		fprintf(file, "%-6d", a[i]);
		j++;
		if (j % 15 == 0)
			fprintf(file, "\n");
	}
	fprintf(file, "\n");
	fclose(file);
}

void* getdata(int* a, int n, const char* filename)
{
	int i;
	srand(time(0));
	FILE* file = fopen(filename, "w");
	if (file == NULL) {
		printf("无法打开文件 %s\n", filename);
		return NULL;
	}
	for (i = 1; i <= n; i++) {
		a[i] = rand() % n;
		fprintf(file, "\t%d", a[i]);
	}
	fclose(file);
	return a;
}

void readdata(int* a, int n, const char* filename)
{
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		printf("无法打开文件 %s\n", filename);
		return;
	}
	for (int i = 1; i <= n; i++) {
		fscanf(file, "%d", &a[i]);
	}
	fclose(file);
}

void insertsort(int* a, int n, const char* filename)
{
	int i, j, * b;
	b = (int*)malloc((n + 1) * sizeof(int));
	memcpy(b, a, (n + 1) * sizeof(int));
	for (i = 2; i <= n; i++)
	{
		if (b[i] < b[i - 1])
		{
			b[0] = b[i];
			for (j = i - 1;; j--)
			{
				if (b[j] > b[0])
				{
					b[j + 1] = b[j];
				}
				else
					break;
			}
			j++;
			b[j] = b[0];
		}
	}
	showdata(b, n, filename);
	free(b);
}

void shellsort(int* a, int n, int t)
{
	int i, j;
	for (i = t + 1; i <= n; i++)
	{
		if (a[i] < a[i - t])
		{
			a[0] = a[i];
			for (j = i - t; j >= 1; j = j - t)
			{
				if (a[j] > a[0])
				{
					a[j + t] = a[j];
				}
				else
					break;
			}
			j = j + t;
			a[j] = a[0];
		}
	}
}

void shell(int* a, int n, const char* filename)
{
	int i, j, * b, k, t;
	b = (int*)malloc((n + 1) * sizeof(int));
	memcpy(b, a, (n + 1) * sizeof(int));
	for (i = 1; pow(2, i) <= n; i++);
	for (i = i - 1; i >= 1; i--)
	{
		t = pow(2, i) - 1;
		shellsort(b, n, t);
	}
	showdata(b, n, filename);
	free(b);
}

void bubble(int* a, int n, const char* filename)
{
	int i, j, t, * b, lastindex = 1;
	b = (int*)malloc((n + 1) * sizeof(int));
	memcpy(b, a, (n + 1) * sizeof(int));
	i = n;
	while (i > 1)
	{
		lastindex = 1;
		for (j = 1; j < i; j++)
		{
			if (b[j] > b[j + 1])
			{
				t = b[j];
				b[j] = b[j + 1];
				b[j + 1] = t;
				lastindex = j;
			}
		}
		i = lastindex;
	}
	showdata(b, n, filename);
	free(b);
}

void quick(int* a, int n, const char* filename)
{
	int i, * b;
	b = (int*)malloc((n + 1) * sizeof(int));
	memcpy(b, a, (n + 1) * sizeof(int));
	quicksort(b, 1, n);
	showdata(b, n, filename);
	free(b);
}

int pivot(int* a, int low, int high)
{
	a[0] = a[low];
	while (low < high)
	{
		while (low < high && a[high] >= a[0])
		{
			high--;
		}
		a[low] = a[high];
		while (low < high && a[low] <= a[0])
		{
			low++;
		}
		a[high] = a[low];
	}
	a[low] = a[0];
	return low;
}

void quicksort(int* a, int low, int high)
{
	int pos;
	if (low < high)
	{
		pos = pivot(a, low, high);
		quicksort(a, low, pos - 1);
		quicksort(a, pos + 1, high);
	}
}

void selectsort(int* a, int n, const char* filename)
{
	int i, j, p, t, * b;
	b = (int*)malloc((n + 1) * sizeof(int));
	memcpy(b, a, (n + 1) * sizeof(int));
	for (i = 1; i < n; i++)
	{
		p = i;
		for (j = i + 1; j <= n; j++)
		{
			if (b[j] < b[p])
				p = j;
		}
		if (p != i)
		{
			t = b[p];
			b[p] = b[i];
			b[i] = t;
		}
	}
	showdata(b, n, filename);
	free(b);
}

void heapsort(int* a, int n, const char* filename)//堆排序 
{
	int* b, i;
	b = (int*)malloc((n + 1) * sizeof(int));
	memcpy(b, a, (n + 1) * sizeof(int));
	for (i = n / 2; i >= 1; i--)
		heapadjust(b, n, i);
	for (i = 1; i < n; i++)
	{
		b[0] = b[1];
		b[1] = b[n - i + 1];
		b[n - i + 1] = b[0];
		heapadjust(b, n - i, 1);
	}
	showdata(b, n, filename);
	free(b);
}

void heapadjust(int* a, int n, int index)
{
	int i, j;
	i = index;
	j = 2 * i;
	a[0] = a[i];
	while (j <= n)
	{
		if (j<n && a[j + 1]>a[j])
			j++;
		if (a[j] > a[0])
		{
			a[i] = a[j];
			i = j;
			j *= 2;
		}
		else
			break;
	}
	a[i] = a[0];
}

void Merge(int* b, int* c, int low, int mid, int high)
{
	int i = low, j = mid + 1, k = low;
	while (i <= mid && j <= high)
	{
		if (b[i] <= b[j])
			c[k++] = b[i++];
		else
			c[k++] = b[j++];
	}
	while (i <= mid)
	{
		c[k++] = b[i++];
	}
	while (j <= high)
	{
		c[k++] = b[j++];
	}
}

void Mergesort(int* a, int n, const char* filename)
{
	int* b = (int*)malloc(sizeof(int) * (n + 1));//原数组 
	int* c = (int*)malloc(sizeof(int) * (n + 1));//辅助数组 
	memcpy(b, a, sizeof(int) * (n + 1));
	int i, j, k, low, top, mid, len = 1;
	while (len < n)
	{
		for (j = 1; j <= (n - 2 * len + 1); j += 2 * len)
			Merge(b, c, j, j + len - 1, j + 2 * len - 1);
		if ((n + 1 - j) > len)
			Merge(b, c, j, j + len - 1, n);
		else
			for (k = j; k <= n; k++)
				c[k] = b[k];
		//辅助数组每趟归并后要复制到原数组 
		memcpy(b, c, sizeof(int) * (n + 1));
		len *= 2;
	}
	showdata(b, n, filename);
	free(b);
	free(c);
}
