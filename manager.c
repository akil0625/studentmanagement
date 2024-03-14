#define _CRT_SECURE_NO_WARNINGS
#include <conio.h>
#include "manager.h"

enum {
	exitwithoutsaveing,
	showallinformation,
	addcourse,
	addstudent,
	addstudenttocourse,
	modifyscore,
	deleteinfo,
	saveinfo,
	setorder,
};

enum {
	cancle,
	showstudents,
	showcourses,
	showtogerther,
	readytoinputid,
};
enum {
	deletestudent = 4,
	delatecouse,
	delatestudfromcours
};

void menu1()
{
	printf("==========================================================================\n");
	printf("========================  1.showallinformation   =========================\n");
	printf("========================  2.addcourse            =========================\n");
	printf("========================  3.addstudent           =========================\n");
	printf("========================  4.addstudenttocourse   =========================\n");
	printf("========================  5.modifyscore          =========================\n");
	printf("========================  6.deleteinfo           =========================\n");
	printf("========================  7.saveinfo             =========================\n");
	printf("========================  0.exitwithoutsaveing   =========================\n");
	printf("==========================================================================\n");
	printf(">");

}			
			
void menu2()
{			
	printf("==========================================================================\n");
	printf("========================  1.showstudents         =========================\n");
	printf("========================  2.showcourses          =========================\n");
	printf("========================  3.showtogerther        =========================\n");
	printf("========================  4.readytoinputid       =========================\n");
	printf("========================  0.cancle               =========================\n");
	printf("==========================================================================\n");
	printf(">");
}			
			
void menu3()
{			
	printf("==========================================================================\n");
	printf("========================  1.showstudents         =========================\n");
	printf("========================  2.showcourses          =========================\n");
	printf("========================  3.showtogerther        =========================\n");
	printf("========================  4.deletestudent        =========================\n");
	printf("========================  5.delatecouse          =========================\n");
	printf("========================  6.delatestud from      =========================\n");
	printf("========================        cours            =========================\n");
	printf("========================  0.cancle               =========================\n");
	printf("==========================================================================\n");
	printf(">");

}


void ShowInformation()
{
	setvbuf(stdout, NULL, _IOFBF, 4096);
	system("cls");
	int sbegin = 1;//从第sbegin个学生显示到第sbegin+9个学生//最初要从1开始
	int cbegin = 1;//从第cbegin个课程显示到第cbegin+6个课程//最初要从1开始
	int input = 0;
	int leftline = 0;
	do
	{
		g_PrintStCr(stcr, sbegin, cbegin);
		leftline = stcr->stu_num - sbegin - 10 + 1 < 0 ? 10 - (stcr->stu_num - sbegin) : 1;
		for (int i = 0; i < leftline*2; i++)
			printf("\n");
		printf("A：左移  D：右移  W：上移  S：下移动 0：退出");
		fflush(stdout);
		input = (int)_getch();
		switch (input)
		{
		case 'A':
		case 'a':
			if (cbegin != 1)
			cbegin-=5;
			break;
		case 'D':
		case 'd':
			if(stcr->co_num - cbegin - 7 + 1 >= 0)
			cbegin+=5;
			break;
		case 'W':
		case 'w':
			if(stcr->stu_num - sbegin - 10 + 1 >= 0)
			sbegin+=5;
			break;
		case 'S':
		case 's':
			if (sbegin != 1)
			sbegin-=5;
			break;
		case '0':
			input = 0;
			break;
		default:
			break;
		}
		system("cls");
	} while (input);
	setvbuf(stdout, NULL, _IONBF, 0);
}
void AddStu()
{
	g_AddStudent(stcr);
	printf("添加成功\n");
	//system("pause");
	system("cls");
}
void AddCo()
{
	g_AddCourse(stcr);
	printf("添加成功\n");
	system("pause");
	system("cls");
}
void showstu()
{
	system("cls");
	STUDENTS* p = stcr->g_students->next;

	printf("---------------------------------------------\n");
	printf("%14s   |%8s   |%12s  |\n", "姓名", "学号", "手机号");
	while (p != NULL)
	{
		printf("%14s   |%8d   |%12s  |\n", p->student.student_name, p->student.student_number, p->student.student_phone);
		p = p->next;
	}
	printf("---------------------------------------------\n\n");

}
void showco(int together)
{
	if(!together)
		system("cls");
	COURSES* q = stcr->g_courses->next;

	printf("---------------------------------------------------------------------------\n");
	printf("%14s   |%8s   |%12s  |%12s  |%12s  |\n", "课程名", "课程id","绩点","课程学分","课程总分");
	while (q != NULL)
	{
		printf("%14s   |%8d   |%12d  |%12d  |%12d  |\n", q->course.course_name, q->course.course_number,q->course.course_jidian,q->course.couese_credit,q->course.course_score);
		q = q->next;
	}
	printf("---------------------------------------------------------------------------\n\n");

}
void addsc()
{
	int studentid = 0;
	int courseid = 0;
	int score = 0;
	int tmp = 0;
	printf("请输入选取的学生id\n");
	tmp = scanf("%d", &studentid);
	printf("请输入选取的课程id\n");
	tmp = scanf("%d", &courseid);
	printf("请输入成绩,输入-2表示暂无成绩\n");
	tmp = scanf("%d", &score);
	AddScore(stcr, studentid, courseid, score);
	printf("添加成功\n");
	system("pause");
	system("cls");
}
void AddStutoCo()
{
	system("cls");
	int input = 0;
	int tmp = 0;
	do
	{
		menu2();
		tmp = scanf("%d", &input);
		switch (input)
		{
		case showstudents:
			showstu();
			break;
		case showcourses:
			showco(0);
			break;
		case showtogerther:
			showstu();
			showco(1);
			break;
		case readytoinputid:
			addsc();
			break;
		case cancle:
			break;
		}

	} while (input);
	system("cls");

}
void modstuco()
{
	int tmp = 0;
	int courseid = 0;
	int studentid = 0;
	int score = 0;
	printf("请输入选取的学生id\n");
	tmp = scanf("%d", &studentid);
	printf("请输入选取的课程id\n");
	tmp = scanf("%d", &courseid);
	printf("请输入修改后的成绩\n");
	tmp = scanf("%d", &score);
	ModifyScore(stcr->g_head, studentid, courseid, score);
	printf("修改成功\n");
	system("pause");
	system("cls");
}
void ModStuCo()
{
	system("cls");
	int input = 0;
	int tmp = 0;
	do
	{
		menu2();
		tmp = scanf("%d", &input);
		switch (input)
		{
		case showstudents:
			showstu();
			break;
		case showcourses:
			showco(0);
			break;
		case showtogerther:
			showstu();
			showco(1);
			break;
		case readytoinputid:
			modstuco();
			break;
		case cancle:
			break;
		}

	} while (input);
	system("cls");
}
void delstu()
{
	int tmp = 0;
	int studentid = 0;
	printf("请输入要删除的学生id\n");
	tmp = scanf("%d", &studentid);
	g_DeleteStudent(stcr, studentid);
	printf("删除成功\n");
	system("pause");
	system("cls");
}
void delco()
{
	int tmp = 0;
	int courseid = 0;
	printf("请输入要删除的课程id\n");
	tmp = scanf("%d", &courseid);
	g_DeleteCourse(stcr, courseid);
	printf("删除成功\n");
	system("pause");
	system("cls");
}
void delstuco()
{
	int tmp = 0;
	int studentid = 0;
	int courseid = 0;
	printf("请输入要删除的学生id\n");
	tmp = scanf("%d", &studentid);
	printf("请输入要删除的课程id\n");
	tmp = scanf("%d", &courseid);
	DeleteScore(stcr->g_head, studentid, courseid);
	printf("删除成功\n");
	system("pause");
	system("cls");
}
void DelStuCo()
{
	system("cls");
	int input = 0;
	int tmp = 0;
	do
	{
		menu3();
		tmp = scanf("%d", &input);
		switch (input)
		{
		case showstudents:
			showstu();
			break;
		case showcourses:
			showco(0);
			break;
		case showtogerther:
			showstu();
			showco(1);
			break;
		case deletestudent:
			delstu();
			break;
		case delatecouse:
			delco();
			break;
		case delatestudfromcours:
			delstuco();
			break;
		}
	} while (input);
	system("cls");
}
void SaveFile()
{
	SaveToFile(stcr);
	printf("保存成功\n");
	system("pause");
	system("cls");
}



int managerlogin()
{

	int input = 0;
	do
	{
		menu1();
		int tmp = scanf("%d", &input);
		switch (input)
		{
		case showallinformation:
			ShowInformation();
			break;
		case addcourse:
			AddCo();
			break;
		case addstudent:
			AddStu();
			break;
		case addstudenttocourse:
			AddStutoCo();
			break;
		case modifyscore:
			ModStuCo();
			break;
		case deleteinfo:
			DelStuCo();
			break;
		case saveinfo:
			SaveFile();
			break;
		case exitwithoutsaveing:
			break;
		}

	} while (input);
}