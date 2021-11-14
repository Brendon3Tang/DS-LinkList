//============================================================================
// Name        : LinkBlank.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>
#include<stdbool.h>

#pragma warning(disable:4996)
#define NO_LENGTH  20
#define NAME_LENGTH 11

/* 定义学生结构体的数据结构 */
typedef struct Student {
	char studentNo[NO_LENGTH];
	char studentName[NAME_LENGTH];
}st;

/* 定义每条记录或节点的数据结构 */
typedef struct node
{
	struct Student data; //数据域
	struct node* next; //指针域
}Node, * Link;  //Node为node类型的别名,Link为node类型的指针别名

//定义提示菜单
void myMenu() {
	printf(" * * * * * * * * * 菜     单 * * * * * * * * * *\n");
	printf("     1 增加学生记录            2 删除学生记录                     \n");
	printf("     3 查找学生记录            4 修改学生记录                     \n");
	printf("     5 统计学生人数            6 显示学生记录                     \n");
	printf("     7 退出系统                                     \n");
	printf(" * * * * * * * * * * * * * * * * * * * * * * * *\n");
}

void inputStudent(Link l) {
	printf("请输入学生学号:");
	scanf("%s", l->data.studentNo);
	printf("请输入学生的姓名:");
	scanf("%s", l->data.studentName);

	//每个新创建的节点的next域都初始化为NULL
	l->next = NULL;
}

void inputStudentNo(char s[], char no[]) {
	printf("请输入要%s的学生学号:", s);
	scanf("%s", no);
}

void displayNode(Link head) {
	// 填写代码，根据传入的链表head头指针，扫描链表显示所有节点的信息
	Link p;

	p = head->next;
	if (p == NULL)
		printf("系统信息为空！\n");
	while (p != NULL)
	{
		printf("--------------------------------\n");
		printf("学生姓名: ");
		printf("%s\n", p->data.studentName);
		printf("学号: ");
		printf("%s\n", p->data.studentNo);
		printf("--------------------------------\n");

		p = p->next;
	}

}

/* 增加学生记录 */
bool addNode(Link head) {
	Link p, q;   //p,q两个节点一前一后
	Link node;  //node指针指向新创建的节点
	node = (Link)malloc(sizeof(Node));
	inputStudent(node);

	q = head;
	p = head->next;
	if (p == NULL) //链表为空时
	{
		head->next = node;
	}
	else //链表不为空时
	{
		while (p != NULL)
		{
			if (strcmp(node->data.studentNo,p->data.studentNo) < 0)
			{
				node->next = p;
				q->next = node;

				return true;
			}
			else if (strcmp(node->data.studentNo, p->data.studentNo) > 0)
			{
				q = p;
				p = p->next;
			}
			else if (strcmp(node->data.studentNo, p->data.studentNo) == 0)//不允许插入同序号的数据
			{
				printf("该序号已存在\n");
				return false;
			}
		}
		q->next = node;
	}
	return true;

	//q = head;
	//p = head->next;  //q指向head后面的第一个有效节点
	//if (head->next == NULL)
	////链表为空时
	//	head->next = node;
	//else {
	//	//循环访问链表中的所有节点
	//	while (p != NULL) {
	//		if (node->data.studentNo < p->data.studentNo) {
	//			//如果node节点的学号比p节点的学号小，则插在p的前面，完成插入后，提前退出子程序
	//			q->next = node;
	//			node->next = p;
	//			return true;
	//		}
	//		else {
	//			//如果node节点的学号比p节点的学号大，继续向后移动指针（依然保持pq一前一后）
	//			q = p;
	//			p = p->next;

	//		}
	//	}
	//	//如果没能提前退出循环，则说明之前没有插入，那么当前node节点的学号是最大值，此时插在链表的最后面
	//	q->next = node;

	//}
	//return true;
}

bool deleteNode(Link head) {
	// 按照给定的学号删除学生记录，如果删除成功返回true，如果没找到学号返回false

	Link p, q;

	q = head;
	p = head->next;

	if (head->next == NULL)//当链表为空的情况
	{
		printf("系统内信息为空");
		return false;
	}
	else
	{
		//输入要处理的学号
		char no[NO_LENGTH];
		inputStudentNo("删除", no);
		while (p != NULL)
		{
			if (strcmp(no, p->data.studentNo) == 0)//找到目标节点
			{
				printf("\n找到目标节点\n");
				q->next = p->next;
				free(p);
				return true;
			}
			else//找不到目标节点
			{
				q = p;
				p = p->next;
			}
		}
		printf("要修改的信息不存在！");
	}

	return false;
}

bool queryNode(Link head) {
	// 按照给定的学号查询学生记录，如果成功找到返回true，如果没找到学号返回false

	//输入要处理的学号
	char no[NO_LENGTH];
	inputStudentNo("查询", no);

	Link p;
	p = head->next;
	if (p == NULL)
	{
		printf("系统内信息为空！");
		return false;
	}
	else
	{
		while (p != NULL)
		{
			if (strcmp(no, p->data.studentNo) == 0)
				return true;
			p = p->next;
		}
	}
	return false;
}

bool modifyNode(Link head) {
	// 按照给定的学号找到学生记录节点，如果修改成功返回true，如果没找到学号返回false

	//输入要处理的学号
	char no[NO_LENGTH];
	int choice = 0;
	char newName[NO_LENGTH];
	inputStudentNo("修改", no);
	Link tmpNode;
	tmpNode = (Link)malloc(sizeof(Node));
	tmpNode->next = NULL;
	Link p = head->next;
	Link q = head;

	if (p == NULL)
	{
		printf("系统内信息为空！");
		return false;
	}
	else
	{
		printf("请选择修改的内容：\n1.姓名\n2.学号\n");
		
		scanf("%d", &choice);

		while (p != NULL)
		{
			if (strcmp(no, p->data.studentNo) == 0)
			{
				if (choice == 1)
				{
					printf("原姓名为：%s\n请输入新的姓名：", p->data.studentName);
					scanf("%s", &newName);
					strcpy(p->data.studentName, newName);
					printf("修改成功！新姓名为：%s\n", p->data.studentName);
					return true;
				}
				else if (choice == 2)
				{
					printf("原学号为：%s\n请输入新的学号：", p->data.studentNo);

					scanf("%s", tmpNode->data.studentNo);
					strcpy(tmpNode->data.studentName, p->data.studentName);

					q->next = p->next;
					free(p);

					Link ptr1 = head;
					Link ptr2 = head->next;

					while (ptr2 != NULL)
					{
						if (strcmp(tmpNode->data.studentNo, ptr2->data.studentNo) < 0)
						{
							tmpNode->next = ptr2;
							ptr1->next = tmpNode;
							printf("修改成功！新学号为: %s", tmpNode->data.studentNo);
							return true;
						}
						else if ((strcmp(tmpNode->data.studentNo, ptr2->data.studentNo) > 0))
						{
							ptr1 = ptr2;
							ptr2 = ptr2->next;
						}
						else
						{
							printf("添加失败，该学号已存在");
						}
					}
					ptr1->next = tmpNode;
					printf("修改成功！新学号为: %s", tmpNode->data.studentNo);
					return true;

				}
				else
					printf("请输入正确选项！\n");
			}
			q = p;
			p = p->next;
		}
		printf("修改失败，未找到该学号！");
	}

	return false;
}

int countNode(Link head) {
	//统计学生人数，扫描链表统计节点个数，返回节点数
	Link p;
	int count = 0;
	p = head->next;

	//填充代码
	if (p == NULL)
		 return 0;
	else
	{
		while (p != NULL)
		{
			count++;
			p = p->next;
		}
	}
	return count;
}

void clearLink(Link head) {
	Link q, p;
	//遍历链表，用free语句删除链表中用malloc建立起的所有的节点
	p = head->next;
	q = head;
	while (p != NULL)
	{
		//free(q);
		q = p;
		p = p->next;
		free(q);
	}
	free(p);
}

int main() {
	int select;
	int count;
	Link head;  // 定义链表

	//建立head头结点，在这个程序中head指向头结点，头结点data部分没有内容，其后续节点才有真正的数据
	head = (Link)malloc(sizeof(Node));
	head->next = NULL;

	while (1)
	{
		myMenu();
		printf("\n请输入你的选择(1-7):");  //显示提示信息
		scanf("%d", &select);
		switch (select)
		{
		case 1:
			//增加学生记录
			if (addNode(head))
				printf("成功插入一个学生记录。\n\n");
			break;
		case 2:
			//删除学生记录
			if (deleteNode(head))
				printf("成功删除一个学生记录。\n\n");
			else
				printf("没有找到要删除的学生节点。\n\n");
			break;
		case 3:
			//查询学生记录
			if (queryNode(head))
				printf("成功找到学生记录。\n\n");
			else
				printf("没有找到要查询的学生节点。\n\n");
			break;
		case 4:
			//修改学生记录
			if (modifyNode(head))
				printf("成功修改一个学生记录。\n\n");
			else
				printf("没有找到要修改的学生节点。\n\n");
			break;
		case 5:
			//统计学生人数
			count = countNode(head);
			printf("学生人数为：%d\n\n", count);
			break;
		case 6:
			//显示学生记录
			displayNode(head);
			break;
		case 7:
			//退出前清除链表中的所有结点
			clearLink(head);
			return 0;
		default:
			printf("输入不正确，应该输入1-7之间的数。\n\n");
			break;
		}
	}

	
	return 0;
}