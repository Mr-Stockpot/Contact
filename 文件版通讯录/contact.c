#define _CRT_SECURE_NO_WARNINGS 1
#include "contact.h"

static int FindByName(const struct Contact* ps, char name[MAX_NAME])
{
	int i = 0;
	for (i = 0; i < ps->size; i++)
	{
		if (0 == strcmp(ps->data[i]. name, name))
		{
			return i;
		}
	}
	return -1;
}

void InitContact(struct Contact* ps)
{
	//memset(ps -> data, 0, sizeof(ps -> data));
	//ps->size = 0;//设置通讯录最初只有0个元素
	ps->data = (struct PeoInfo*)malloc(DEFAULT_SZ *sizeof(struct PeoInfo));
	if (ps->data == NULL)
	{
		return;
	}
	ps->size = 0;
	ps->capacity = DEFAULT_SZ;
	//把文件中存放的信息加载到通讯录中
	LoadContact(ps);
}

void CheckCapacity(struct Contact* ps)
{
	if (ps->size == ps->capacity)
	{
		struct PeoInfo* ptr = realloc(ps->data, (ps->capacity + 2) * sizeof(struct PeoInfo));
		if (ptr != NULL)
		{
			ps->data = ptr;
			ps->capacity += 2;
			printf("增容成功\n");
		}
		else
			printf("增容失败\n");
	}
}

void LoadContact(Contact* ps)
{
	struct PeoInfo tmp = {0};
	FILE* pfRead = fopen("contact.dat", "rb");
	if (pfRead == NULL)
	{
		printf("LoadContact::%s\n", strerror(errno));
		return;
	}
	//读取文件放到通讯录中
	while (fread(&tmp, sizeof(struct PeoInfo), 1, pfRead))
	{
		CheckCapacity(ps);
		ps->data[ps->size]= tmp;
		ps->size++;
	}

	fclose(pfRead);
	pfRead = NULL;
}

void AddContact(struct Contact* ps)
{
	/*if (ps ->size == MAX)
	{
		printf("通讯录已满，无法增加\n");
	}
	else
	{
		printf("请输入名字：>");
		scanf("%s", ps->data[ps->size].name);
		printf("请输入年龄：>");
		scanf("%d", &(ps->data[ps->size].age));
 		printf("请输入性别：>");
		scanf("%s", ps->data[ps->size].sex);
		printf("请输入电话：>");
		scanf("%s", ps->data[ps->size].tele);
		printf("请输入地址：>");
		scanf("%s", ps->data[ps->size].addr);

		ps->size++;
		printf("添加成功\n");
	}*/

	//检测当前通讯录的容量
	//1.如果满了，先用CheckCapacity(ps)增容
	//2.如果不满，直接增加信息数据
	CheckCapacity(ps);
	printf("请输入名字：>");
	scanf("%s", ps->data[ps->size].name);
	printf("请输入年龄：>");
	scanf("%d", &(ps->data[ps->size].age));
	printf("请输入性别：>");
	scanf("%s", ps->data[ps->size].sex);
	printf("请输入电话：>");
	scanf("%s", ps->data[ps->size].tele);
	printf("请输入地址：>");
	scanf("%s", ps->data[ps->size].addr);

	ps->size++;
	printf("添加成功\n");
}

void DelContact(struct Contact* ps)
{
	char name[MAX_NAME];
	printf("请输入名字\n");
	scanf("%s", name);
	//1.查找要删除的人在什么位置
	//找到了返回元素所在下标
	//找不到返回 -1
	int pos = FindByName(ps, name);
	
	//2.删除
	if (-1 == pos)
		printf("要删除的人不存在\n");
	else
	{
		//删除数据
		int j = 0;
		for (j = pos; j < ps->size - 1; j++)
		{
			ps->data[j] = ps->data[j + 1];
		}
		ps->size--;
	 	printf("删除成功\n");
	}
}

void SearchContact(const struct Contact* ps)
{
	int pos = 0;
	char name[MAX_NAME];
	printf("请输入名字\n");
	scanf("%s", name);
	pos = FindByName(ps, name);
	if (-1 == pos)
		printf("要查找的人不存在\n");
	else
	{
		printf("%-20s\t%-4s\t%-5s\t%-12s\t%-30s\n", "名字", "年龄", "性别", "电话", "地址");
		//数据
		printf("%-20s\t%-4d\t%-5s\t%-12s\t%-30s\n",
			ps->data[pos].name,
			ps->data[pos].age,
			ps->data[pos].sex,
			ps->data[pos].tele,
			ps->data[pos].addr);
	}
}

void ModifyContact(struct Contact* ps)
{
	int pos = 0;
	char name[MAX_NAME];
	printf("请输入名字\n");
	scanf("%s", name);
	pos = FindByName(ps, name);
	if (-1 == pos)
		printf("要修改的人不存在\n");
	else
	{
		printf("请输入名字：>");
		scanf("%s", ps->data[pos].name);
		printf("请输入年龄：>");
		scanf("%d", &(ps->data[pos].age));
		printf("请输入性别：>");
		scanf("%s", ps->data[pos].sex);
		printf("请输入电话：>");
		scanf("%s", ps->data[pos].tele);
		printf("请输入地址：>");
		scanf("%s", ps->data[pos].addr);

		printf("修改成功\n");
	}
}

void SortContactByName(struct Contact* ps)
{
	int i = 0;
	for ( i = 0; i < ps->size; i++)
	{
		int j = 0;
		for ( j = 0; j < ps->size-i-1; j++)
		{
			if (strcmp(ps->data[j].name, ps->data[j + 1].name) > 0)
			{
				struct PeoInfo tmp = ps->data[j];
				ps->data[j]= ps->data[j + 1];
				ps->data[j + 1] = tmp;
			}
		}
	}
}
void SortContact(struct Contact* ps)
{
	SortContactByName(ps);
}

void ShowContact(struct Contact* ps)
{
	if (ps->size == 0)
	{
		printf("通讯录为空\n");
	}
	else
	{
		int i = 0;
		//标题
		printf("%-20s\t%-4s\t%-5s\t%-12s\t%-30s\n", "名字", "年龄", "性别", "电话", "地址");
		//数据
		for ( i = 0; i < ps->size; i++)
		{
			printf("%-20s\t%-4d\t%-5s\t%-12s\t%-30s\n",
				ps->data[i].name,
				ps->data[i].age,
				ps->data[i].sex,
				ps->data[i].tele,
				ps->data[i].addr
				);
		}
	}
}

void DestroyContact(Contact* ps) 
{
	free(ps->data);
	ps->data = NULL;
}

void SaveContact(Contact* ps)
{
	FILE* pfWrite = fopen("contact.dat", "wb");
	if (pfWrite == NULL)
	{
		printf("SaveContact::%s\n", strerror(errno));
		return;
	}
	//写通讯录中数据到文件中
	int i = 0;
	for (i = 0; i < ps->size; i++)
	{
		fwrite(&(ps->data[i]), sizeof(struct PeoInfo), 1, pfWrite);
	}

	fclose(pfWrite);
	pfWrite = NULL;
}