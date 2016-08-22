//1325: 算法2 - 3~2 - 6：Big Bang

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INIT_SIZE 100
#define INCREMENT 10

typedef struct
{
	char name[30];
} Elem;

typedef struct
{
	Elem *elem;
	int length;
	int listsize;
} SqList;

//初始化
void InitList_Sq(SqList *L);
//在L中的第i个元素之前插入e
void ListInsert_Sq(SqList *L, int i, Elem e);
//删除L中的第i个元素，返回其值e
void ListDelete_Sq(SqList *L, Elem e);
//查找L中第i个元素和e相同的值，返回其位置
int LocateElem_Sq(SqList L, Elem e);
//打印出表中所有元素
void ShowElem_Sq(SqList L);

int main(void)
{
	SqList L;
	InitList_Sq(&L);

	Elem e;
	char str[30];
	int num;

	while (scanf("%s", str) == 1)
	{
		if (!strcmp(str, "insert"))
		{
			scanf("%d%s", &num, e.name);
			ListInsert_Sq(&L, num, e);
		}
		else if (!strcmp(str, "delete"))
		{
			scanf("%s", e.name);
			ListDelete_Sq(&L, e);
		}
		else if (!strcmp(str, "search"))
		{
			scanf("%s", e.name);
			printf("%d\n", LocateElem_Sq(L, e));
		}
		else if (!strcmp(str, "show"))
		{
			ShowElem_Sq(L);
		}
	}
	return 0;
}

void InitList_Sq(SqList *L)
{
	(*L).elem = (Elem*)malloc(INIT_SIZE * sizeof(Elem));
	if (!(*L).elem)
		exit(EXIT_FAILURE);
	(*L).length = 0;
	(*L).listsize = INIT_SIZE;
}

void ListInsert_Sq(SqList *L, int i, Elem e)
{
	if (i<1 || i>(*L).length + 1)
		exit(EXIT_FAILURE);

	Elem *p, *q;

	if ((*L).length >= (*L).listsize)
	{
		Elem *newbase;

		newbase = (Elem *)realloc((*L).elem, ((*L).listsize + INCREMENT) * sizeof(Elem));
		if (!newbase)
			exit(EXIT_FAILURE);
		(*L).elem = newbase;
		(*L).listsize += INCREMENT;
	}
	q = (*L).elem + i - 1; //q为插入位置
	for (p = (*L).elem + (*L).length - 1; p >= q; --p)
		*(p + 1) = *p;
	*q = e;
	++(*L).length;
}

void ListDelete_Sq(SqList *L, Elem e)
{
	int i = LocateElem_Sq(*L,e);
	Elem *p,*q;	//q指向被删除的元素

	q = (*L).elem + i - 1;
	for (p = q; p < (*L).elem + (*L).length; ++p)
	{
		*p = *(p + 1);
	}
	--(*L).length;
}

int LocateElem_Sq(SqList L, Elem e)
{
	int count = 0;
	Elem *p = L.elem;

	while (p < L.elem + L.length)
	{
		++count;
		if (!strcmp((*p).name, e.name))
		{
			return count;
		}
		++p;
	}
	return 0;
}

void ShowElem_Sq(SqList L)
{
	int i;

	for (i = 0; i < L.length; i++)
	{
		if (i)
		{
			putchar(' ');
		}
		printf("%s", (L.elem[i].name));
	}
	putchar('\n');
}
