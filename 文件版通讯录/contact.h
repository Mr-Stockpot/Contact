#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define DEFAULT_SZ 3
//#define MAX 1000
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
	SORT,
	SAVE
};

//个人信息类型
struct PeoInfo
{
	char name[MAX_NAME];
	int age;
	char sex[MAX_SEX];
	char tele[MAX_TELE];
	char addr[MAX_ADDR];
};

//通讯录类型
typedef struct Contact
{
	//struct PeoInfo data[MAX];//存放1000人信息
	struct PeoInfo* data;//存放信息地址
	int size;//记录当前已有的元素个数
	int capacity;//当前通讯录的最大容量
}Contact;

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
//销毁内存
void DestroyContact(Contact* ps);
//保存
void SaveContact(Contact* ps);
//加载
void LoadContact(Contact* ps);