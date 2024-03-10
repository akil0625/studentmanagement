#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include "OrthogonalList.h"

//初始化
struct St_Crs* g_initStCr()
{
	struct St_Crs* stcr = (struct St_Crs*)malloc(sizeof(struct St_Crs));//创建头结点
	if (stcr == NULL)
	{
		printf("内存分配失败\n");
		return NULL;
	}
	stcr->co_num = 0;
	stcr->stu_num = 0;
	stcr->g_courses = (COURSES*)malloc(sizeof(COURSES));//创建课程结点
	if (stcr->g_courses == NULL)
	{
		printf("内存分配失败\n");
		return NULL;
	}
	stcr->g_courses->next = NULL;
	stcr->g_students = (STUDENTS*)malloc(sizeof(STUDENTS));//创建学生结点
	if (stcr->g_students == NULL)
	{
		printf("内存分配失败\n");
		return NULL;
	}
	stcr->g_students->next = NULL;
	stcr->g_head = (struct OrthogonalList*)malloc(sizeof(struct OrthogonalList));//创建头结点
	if (stcr->g_head == NULL)
	{
		printf("内存分配失败\n");
		return NULL;
	}
	stcr->g_head->right = NULL;
	stcr->g_head->down = NULL;
	stcr->g_head->studentid = -1;
	stcr->g_head->courseid = -1;
	stcr->g_head->score = -1;
	return stcr;
}

//创建十字链表
struct OrthogonalList* CreateOrthogonalList(int* studentid, int* courseid, int* score, int ns,int nc)
{
	struct OrthogonalList *head, *p, *q;
	int i;
	head = (struct OrthogonalList *)malloc(sizeof(struct OrthogonalList));//创建头结点
	if (head == NULL)
	{
		printf("内存分配失败\n");
		return NULL;
	}
	head->right = NULL;
	head->down = NULL;
	head->studentid = -1;
	head->courseid = -1;
	head->score = -1;
	p = head;//p指向头结点
	for (i = 0; i < nc; i++) {//创建所有课程结点
		q = (struct OrthogonalList *)malloc(sizeof(struct OrthogonalList));//创建课程结点
		if (q == NULL)
		{
			printf("内存分配失败\n");
			return NULL;
		}
		q->studentid = -1;//学生编号
		q->courseid = courseid[i];//课程编号
		q->score = -1;//成绩
		q->right = NULL;//右指针
		q->down = NULL;//下指针
		p->right = q;//头结点的右指针指向课程结点
		p = q;//p指向课程结点
	}
	p = head;//p指向头结点
	for (i = 0; i < ns; i++) {//创建所有学生结点并且创建所有成绩结点
		struct OrthogonalList* tmpup = head;//tmpup指向课程结点，负责向下连接成绩节点
		q = (struct OrthogonalList *)malloc(sizeof(struct OrthogonalList));//创建学生结点
		if (q == NULL)
		{
			printf("内存分配失败\n");
			return NULL;
		}
		q->right = NULL;//右指针
		q->down = NULL;//下指针
		q->courseid = -1;//课程编号
		q->studentid = studentid[i];//学生编号
		q->score = -1;//成绩
		p->down = q;//p指向下一个学生结点
		for (int j = 0; j < nc; j++) {//创建所有成绩结点
			if(tmpup->right!=NULL)
				tmpup = tmpup->right;
			else
			{
				printf("课程数据出错！\n");
				return NULL;
			}
			if (score[i * nc + j] != -1)
			{
				q->right = (struct OrthogonalList *)malloc(sizeof(struct OrthogonalList));//创建成绩结点
				if (q->right == NULL)
				{
					printf("内存分配失败\n");
					return NULL;
				}
				q = q->right;//q指向成绩结点
				q->right = NULL;//右指针
				q->down = NULL;//下指针
				q->studentid = studentid[i];//学生编号
				q->courseid = courseid[j];//课程编号
				q->score = score[i * nc + j];//成绩
				struct OrthogonalList* tmpup2 = tmpup;//tmpup指向课程结点，负责向下连接成绩节点
				for (int k = 0; k <= nc; k++)
				{
					if (tmpup2->down == NULL)
						break;
					tmpup2 = tmpup2->down;
				}
				tmpup2->down = q;

			}
		}
		tmpup = head;
		p = p->down;//p指向下一个学生结点
	}
	return head;
}

//销毁总的十字链表
void g_DestroySt_Crs(struct St_Crs* stcr)
{
	struct COURSES* p, * tmpp;
	p = stcr->g_courses;
	while (p != NULL)
	{
		tmpp = p;
		p = p->next;
		free(tmpp);
	}
	struct STUDENTS* q, * tmpq;
	q = stcr->g_students;
	while (q != NULL)
	{
		tmpq = q;
		q = q->next;
		free(tmpq);
	}
	DestroyOrthogonalList(stcr->g_head);
	free(stcr);
}

//销毁十字链表
void DestroyOrthogonalList(struct OrthogonalList* head)
{
	struct OrthogonalList* p, * q;
	struct OrthogonalList* tmp;
	p = head;
	while (p != NULL)//p一直往下移动，直到p为空
	{
		q = p;//不为空时，q指向p
		p = p->down;//p指向下边的结点
		while (q != NULL)//q一直往右移动，直到q为空
		{
			tmp = q;
			q = q->right;//q指向右边的结点
			free(tmp);//释放q
		}
	}
}

//打印十字链表
void PrintOrthogonalList(struct OrthogonalList* head)
{
	struct OrthogonalList* p, * q;
	p = head;

	while (p != NULL)
	{
		q = p;
		struct OrthogonalList* pco = head;
		while (q != NULL)
		{
			if (q->studentid != -1 && q->courseid != -1)
			{		
				if (q->courseid != pco->courseid)
				{
					while (pco!=NULL&&pco->courseid != q->courseid)
					{
						pco = pco->right;
						printf("               ");
					}
				}
				if (q->score != -2)
					printf("%10d分   ", q->score);
				else
					printf("      暂无成绩 ");

			}
			else if (q->studentid == -1&&q->courseid!=-1)
			{
				printf("%10d课   ", q->courseid);
			}
			else if (q->studentid != -1 && q->courseid == -1)
			{
				printf("%10d同学   ", q->studentid);
			}
			else
			{
				printf("                ");
			}	
			q = q->right;
			if(pco!=NULL)
				pco = pco->right;;
		}
		printf("\n");
		p = p->down;
	}
}

//添加课程
void AddCourse(struct OrthogonalList* head, int courseid)
{
	struct OrthogonalList* p;
	p = head;
	while (p->right != NULL)//找到最后一个课程结点
	{
		if(p->right->courseid==courseid)//如果课程已经存在
			return;
		p = p->right;
	}
	p->right = (struct OrthogonalList*)malloc(sizeof(struct OrthogonalList));
	if (p->right == NULL)
	{
		printf("内存分配失败\n");
		return;
	}
	p->right->courseid = courseid;
	p->right->studentid = -1;
	p->right->score = -1;
	p->right->down = NULL;
	p->right->right = NULL;
	
}

//添加学生
void AddStudent(struct OrthogonalList* head, int studentid)
{
	struct OrthogonalList* p;
	p = head;
	while (p->down != NULL)//找到最后一个学生结点
	{
		if (p->down->studentid == studentid)//如果学生已经存在
			return;
		p = p->down;
	}
	p->down = (struct OrthogonalList*)malloc(sizeof(struct OrthogonalList));
	if (p->down == NULL)
	{
		printf("内存分配失败\n");
		return;
	}
	p->down->studentid = studentid;
	p->down->courseid = -1;
	p->down->score = -1;
	p->down->right = NULL;
	p->down->down = NULL;
}

//向总的十字链表添加课程
void g_AddCourse(struct St_Crs* stcr)
{
	COURSES* p = stcr->g_courses;
	if (p == NULL)
		return;
	while (p->next != NULL)
	{
		p = p->next;
	}
	p->next = (COURSES*)malloc(sizeof(COURSES));
	if (p->next == NULL)
	{
		printf("开辟空间失败\n");
		return;
	}
	p = p->next;
	printf("请输入课程id：\n");
	int tmp = scanf("%d", &(p->course.course_number));//课程id
	printf("请输入课程名：\n");
	tmp = scanf("%s", p->course.course_name);//课程名
	printf("请输入绩点：\n");
	tmp = scanf("%d", &(p->course.course_jidian));//绩点
	printf("请输入课程学分\n");
	tmp = scanf("%d", &(p->course.couese_credit));//课程学分
	printf("请输入课程总分：\n");
	tmp = scanf("%d", &(p->course.course_score));//课程总分
	AddCourse(stcr->g_head, stcr->co_num);
	stcr->co_num++;
}

//向总的十字链表添加学生
void g_AddStudent(struct St_Crs* stcr)
{
	STUDENTS* p = stcr;
	if (p == NULL)
		return;
	while (p->next != NULL)
	{
		p = p->next;
	}
	p->next = (STUDENTS*)malloc(sizeof(STUDENTS));
	if (p->next == NULL)
	{
		printf("开辟空间失败\n");
		return;
	}
	p = p->next;
	p->student.item_head = (ID*)malloc(sizeof(ID));//项目信息
	if (p->student.item_head == NULL)
		return;
	p->student.item_head->id = -1;
	p->student.item_head->next = NULL;

	p->student.prize_head = (ID*)malloc(sizeof(ID));//奖品信息
	if (p->student.prize_head == NULL)
		return;
	p->student.prize_head->id = -1;
	p->student.prize_head->next = NULL;

	p->student.thesis_head = (ID*)malloc(sizeof(ID));//论文信息
	if (p->student.thesis_head == NULL)
		return;
	p->student.thesis_head->id = -1;
	p->student.thesis_head->next = NULL;

	printf("请输入姓名：\n");
	int tmp = scanf("%s", p->student.student_name);//姓名
	printf("请输入电话：\n");
	tmp = scanf("%s", p->student.student_phone);//电话
	p->student.student_number = stcr->stu_num;//学生id
	AddStudent(stcr->g_head, stcr->stu_num);
	stcr->stu_num++;
}

//添加学生到课程 score=-2表示暂无成绩
void AddScore(struct OrthogonalList* head, int studentid, int courseid, int score)
{
	if (head == NULL)
	{
		printf("表为空\n");
		return;
	}
	struct OrthogonalList* ps, * pc;
	ps = head;
	while (ps != NULL && ps->studentid != studentid)
	{
		ps = ps->down;
	}
	if (ps == NULL)
	{
		printf("没有该学生\n");
		return;
	}
	pc = head;
	while (pc != NULL && pc->courseid != courseid)
	{
		pc = pc->right;
	}
	if (pc == NULL)
	{
		printf("没有该课程\n");
		return;
	}
	while (ps->right != NULL && ps->right->courseid < courseid)//找到该学生的课程节点
	{
		ps = ps->right;
	}
	if (ps->right != NULL && ps->right->courseid == courseid)//如果该学生的课程节点存在
	{
		return;
	}
	else
	{
		struct OrthogonalList* p = (struct OrthogonalList*)malloc(sizeof(struct OrthogonalList));
		if (p == NULL)
		{
			printf("内存分配失败\n");
			return;
		}
		p->courseid = courseid;
		p->studentid = studentid;
		p->score = score;
		p->right = ps->right;
		ps->right = p;
	}
	while (pc->down != NULL && pc->down->studentid < studentid)
	{
		pc = pc->down;
	}
	if (pc->down != NULL && pc->down->studentid == studentid)
	{
		return;
	}
	else
	{
		struct OrthogonalList* p = (struct OrthogonalList*)malloc(sizeof(struct OrthogonalList));
		if (p == NULL)
		{
			printf("内存分配失败\n");
			return;
		}
		p->courseid = courseid;
		p->studentid = studentid;
		p->score = score;
		p->down = pc->down;
		pc->down = p;
	}
}

//修改学生的课程成绩
void ModifyScore(struct OrthogonalList* head, int studentid, int courseid, int score,int isteacher)
{
	struct OrthogonalList* ps, * pc;

	ps = head;
	while (ps != NULL && ps->studentid != studentid)
	{
		ps = ps->down;
	}
	if (ps == NULL)
	{
		printf("没有该学生\n");
		return;
	}

	pc = head;
	while (pc != NULL && pc->courseid != courseid)
	{
		pc = pc->right;
	}
	if (pc == NULL)
	{
		printf("没有该课程\n");
		return;
	}

	while (ps->right != NULL && ps->right->courseid < courseid)
	{
		ps = ps->right;
	}
	if (ps->right != NULL && ps->right->courseid == courseid)
	{
		ps->right->score = score;
	}
	else
	{
		printf("没有该学生的该课程\n");
		return;
	}

	while (pc->down != NULL && pc->down->studentid < studentid)
	{
		pc = pc->down;
	}
	if (pc->down != NULL && pc->down->studentid == studentid)
	{
		pc->down->score = score;
	}
	else
	{
		printf("没有该学生的该课程\n");
		return;
	}
}

//得到学生的课程成绩
struct O_courses * GetScoresOfStu(struct OrthogonalList* head, int studentid)
{
	if(head==NULL)
	{
		printf("表为空\n");
		return NULL;
	}
	struct OrthogonalList* p;
	p = head;
	while (p != NULL && p->studentid != studentid)//找到该学生
	{
		p = p->down;
	}
	if (p == NULL)
	{
		printf("没有该学生\n");
		return NULL;
	}
	struct O_courses* ans = (struct O_courses*)malloc(sizeof(struct O_courses));
	struct O_courses* pc = ans;
	if (pc == NULL)
	{
		printf("内存分配失败\n");
		return NULL;
	}
	while (p->right != NULL)
	{
		pc->courseid = p->right->courseid;
		pc->score = p->right->courseid;
		if (p->right->right != NULL)
		{
			pc->next = (struct O_courses*)malloc(sizeof(struct O_courses));
		}
		else
		{
			pc->next = NULL;
			break;
		}
		pc = pc->next;
		if (pc == NULL)
		{
			printf("内存分配失败\n");
			return NULL;
		}
		pc->next = NULL;
		p = p->right;
	}
	return ans;
}


//得到课程的学生成绩
struct O_students* GetScoresOfCrs(struct OrthogonalList* head, int courseid)
{
	if (head == NULL)
	{
		printf("表为空\n");
		return NULL;
	}
	struct OrthogonalList* p;
	p = head;
	while (p != NULL && p->courseid != courseid)//找到该课程
	{
		p = p->right;
	}
	if (p == NULL)
	{
		printf("没有该课程\n");
		return NULL;
	}
	struct O_students* ans = (struct O_students*)malloc(sizeof(struct O_students));
	struct O_students* ps = ans;
	if (ps == NULL)
	{
		printf("内存分配失败\n");
		return NULL;
	}
	while (p->down != NULL)
	{
		ps->studentid = p->down->studentid;
		ps->score = p->down->score;
		if (p->down->down != NULL)
		{
			ps->next = (struct O_students*)malloc(sizeof(struct O_students));
		}
		else
		{
			ps->next = NULL;
			break;
		}
		ps = ps->next;
		if (ps == NULL)
		{
			printf("内存分配失败\n");
			return NULL;
		}
		ps->next = NULL;
		p = p->down;
	}
	return ans;
}

//删除学生
void DeleteStudent(struct OrthogonalList* head, int studentid)
{
	struct OrthogonalList* check;
	check = head;
	int flag = 1;
	while (check != NULL)
	{
		if (check->studentid == studentid)
		{
			flag = 0;
		}
		check = check->down;
	}
	if(flag)
	{
		printf("没有该学生\n");
		return;
	}
	struct OrthogonalList* pc;
	pc = head;
	while (pc != NULL)
	{
		struct OrthogonalList* ps = pc;
		pc = pc->right;
		while (ps->down != NULL)//删除这一课程里的学生
		{
			if(ps->down->studentid==studentid)//下下一个是学生
			{
				struct OrthogonalList* tmp = ps->down;//tmp指向学生结点,负责释放
				ps->down = ps->down->down;
				free(tmp);
				break;
			}
			else 
			{
				ps = ps->down;
			}

		}
	}
}

//删除课程
void DeleteCourse(struct OrthogonalList* head, int courseid)
{
	struct OrthogonalList* ps;
	ps = head;
	while (ps != NULL)
	{
		struct OrthogonalList* pc = ps;
		ps = ps->down;
		while (pc->right != NULL)//删除这一学生的课程
		{
			if (pc->right->courseid == courseid)//下下一个是课程
			{
				struct OrthogonalList* tmp = pc->right;//tmp指向课程结点,负责释放
				pc->right = pc->right->right;
				free(tmp);
				break;
			}
			else
			{
				pc = pc->right;
			}

		}
	}
}

//删除学生的课程
void DeleteScore(struct OrthogonalList* head, int studentid, int courseid)
{
	struct OrthogonalList* ps, * pc;
	ps = head;
	while (ps != NULL && ps->studentid != studentid)
	{
		ps = ps->down;
	}
	if (ps == NULL)
	{
		printf("没有该学生\n");
		return;
	}
	pc = head;
	while (pc != NULL && pc->courseid != courseid)
	{
		pc = pc->right;
	}
	if (pc == NULL)
	{
		printf("没有该课程\n");
		return;
	}
	while (ps->right != NULL && ps->right->courseid != courseid)
	{
		ps = ps->right;
	}
	if (ps->right == NULL)
	{
		printf("没有该学生的该课程\n");
		return;
	}
	while (pc->down != NULL && pc->down->studentid != studentid)
	{
		pc = pc->down;
	}
	if (pc->down == NULL)
	{
		printf("没有该学生的该课程\n");
		return;
	}
	struct OrthogonalList* down, * right;
	down = pc->down;
	right = ps->right;
	pc->down = pc->down->down;
	ps->right = ps->right->right;
	free(down);
}

//保存信息到文件
void SaveToFile(struct OrthogonalList* head, STUDENTS* h_students, COURSES* h_courses)
{
	FILE* fp;
	fp = fopen("st_co.dat", "w");
	if (fp == NULL)
	{
		printf("文件打开失败\n");
		return;
	}
	//保存学生信息
	STUDENTS* stup = h_students;
	fprintf(fp, "students\n");//标志着开始写入学生信息
	while (stup != NULL)
	{
		//首先带第一行保存由空格分开的 学号 姓名 电话号
		fprintf(fp, "%d %s %s \n",
			stup->student.student_number, 
			stup->student.student_name,
			stup->student.student_phone);

		//再在下一行保存项目id
		ID* q = stup->student.item_head;
		while (q != NULL)
		{
			fprintf(fp, "%d ", q->id);
			q = q->next;
		}
		fprintf(fp, "\n");

		//再在下下一行保存论文id
		q = stup->student.thesis_head;
		while (q != NULL)
		{
			fprintf(fp, "%d ", q->id);
			q = q->next;
		}
		fprintf(fp, "\n");

		//再在下下下一行保存得奖id
		q = stup->student.prize_head;
		while (q != NULL)
		{
			fprintf(fp, "%d ", q->id);
			q = q->next;
		}
		fprintf(fp, "\n");
		stup = stup->next;
	}

	//保存科目信息
	COURSES* cop = h_courses;
	while (cop != NULL)
	{
		//首先带第一行保存由空格分开的 学号 姓名 电话号
		fprintf(fp, "%d %s %d %d %d \n",
			cop->course.course_number,
			cop->course.course_name,
			cop->course.course_jidian,
			cop->course.couese_credit,
			cop->course.course_score);
			cop = cop->next;
	}
	//----------------------------------------------
	//保存学生的课程成绩
	struct OrthogonalList* p, * q;
	p = head;

	while (p != NULL)//p指向学生节点，一直往下移动
	{
		q = p;
		struct OrthogonalList* pco = head;
		while (q != NULL)//q从p指向的学生节点开始，一直往右移动
		{
			if (q->studentid != -1 && q->courseid != -1)
			{
				if (q->courseid != pco->courseid)//如果课程编码不相等，说明q走过了不存在的节点，此处写入-1表示不存在节点
				{
					while (pco != NULL && pco->courseid != q->courseid)
					{
						pco = pco->right;
						fprintf(fp, "-1 ");
					}
				}
				//如果成绩不是-2，说明存在成绩，无论存不存在成绩，都要写入
				fprintf(fp, "%d ", q->score);

			}
			else if (q->studentid == -1 && q->courseid != -1) {}//此种情况表示，此点不是成绩节点，不需要写入
			else if (q->studentid != -1 && q->courseid == -1) {}//此种情况表示，此点不是成绩节点，不需要写入
			else {}//此种情况表示，此点不是成绩节点，不需要写入
			q = q->right;
			if (pco != NULL)
				pco = pco->right;;
		}
		p = p->down;
	}





	fclose(fp);
}
