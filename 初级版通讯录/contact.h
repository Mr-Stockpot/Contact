#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>

#define MAX 1000
#define MAX_NAME 20
#define MAX_SEX 5
#define MAX_TELE 12
#define MAX_ADDR 30

enum Option
{
	EXIT,
	ADD,
	DEL,
	SEARCH,
	MODIFY,
	SHOW,
	SORT
};

struct PeoInfo
{
	char name[MAX_NAME];
	int age;
	char sex[MAX_SEX];
	char tele[MAX_TELE];
	char addr[MAX_ADDR];
};

struct Contact
{
	struct PeoInfo data[MAX];
	int size;
};

//声明函数
//初始化
void InitContact(struct Contact* ps);
//增加
void AddContact(struct Contact* ps);
//删减
void DelContact(struct Contact* ps);
//查找
void SearchContact(const struct Contact* ps);
//修改
void ModifyContact(struct Contact* ps);
//排序
void SortContact(struct Contact* ps);
//展示
void ShowContact(struct Contact* ps);
