#define _CRT_SECURE_NO_WARNINGS
#include "OrthogonalList.h"
#include "OrthogonalList.h"
#include "sch_struct.h"
struct St_Crs* stcr;
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
	clearscreen,
};

enum {
	cancle,
	showstudents,
	showcourses,
	readytoinputid,
};
enum {
	deletestudent = 3,
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
	printf("========================  8.setorder             =========================\n");
	printf("========================  9.clearscreen          =========================\n");
	printf("========================  0.exitwithoutsaveing   =========================\n");
	printf("==========================================================================\n");
}

void menu2()
{
	printf("==========================================================================\n");
	printf("========================  1.showstudents         =========================\n");
	printf("========================  2.showcourses          =========================\n");
	printf("========================  3.readytoinputid       =========================\n");
	printf("========================  0.cancle               =========================\n");
	printf("==========================================================================\n");
}

void menu3()
{
	printf("==========================================================================\n");
	printf("========================  1.showstudents         =========================\n");
	printf("========================  2.showcourses          =========================\n");
	printf("========================  3.deletestudent        =========================\n");
	printf("========================  4.delatecouse          =========================\n");
	printf("========================  5.delatestud from      =========================\n");
	printf("========================        cours            =========================\n");
	printf("========================  0.cancle               =========================\n");
	printf("==========================================================================\n");
}

void AddStutoCo()
{

	int input = 0;
	int tmp = 0;
	STUDENTS* p = stcr->g_students->next;
	COURSES* q = stcr->g_courses->next;
	int courseid = 0;
	int studentid = 0;
	do
	{
		menu2();
		tmp = scanf("%d", &input);
		switch (input)
		{
			
		case showstudents:
			p = stcr->g_students->next;
			printf("%20s %6s %12s", "姓名", "学号", "手机号\n");
			while (p != NULL)
			{
				printf("%20s %6d %12s\n", p->student.student_name,  p->student.student_number, p->student.student_phone);
				p = p->next;
			}
			break;
		case showcourses:
			q = stcr->g_courses->next;
			printf("%20s %6s\n", "课程名", "课程id");
			while (q != NULL)
			{
				printf("%20s %6d\n", q->course.course_name, q->course.course_number);
				q = q->next;
			}
			break;
		case readytoinputid:
			printf("请输入选取的学生id\n");
			tmp = scanf("%d", &studentid);
			printf("请输入选取的课程id\n");
			tmp = scanf("%d", &courseid);
			AddScore(stcr, studentid, courseid, -2);
			break;
		case cancle:
			break;
		}

	} while (input);
	

}
void ModStuCo()
{
	int input = 0;
	int tmp = 0;
	STUDENTS* p = stcr->g_students->next;
	COURSES* q = stcr->g_courses->next;
	int courseid = 0;
	int studentid = 0;
	int score = 0;
	do
	{
		menu2();
		tmp = scanf("%d", &input);
		switch (input)
		{
		case showstudents:
			p = stcr->g_students->next;
			printf("%20s %6s %12s", "姓名", "学号", "手机号\n");
			while (p != NULL)
			{
				printf("%20s %6d %12s\n", p->student.student_name, p->student.student_number, p->student.student_phone);
				p = p->next;
			}
			break;
		case showcourses:
			q = stcr->g_courses->next;
			printf("%20s %6s\n", "课程名", "课程id");
			while (q != NULL)
			{
				printf("%20s %6d\n", q->course.course_name, q->course.course_number);
				q = q->next;
			}
			break;
		case readytoinputid:
			printf("请输入选取的学生id\n");
			tmp = scanf("%d", &studentid);
			printf("请输入选取的课程id\n");
			tmp = scanf("%d", &courseid);
			printf("请输入修改后的成绩\n");
			tmp = scanf("%d", &score);
			ModifyScore(stcr->g_head, studentid, courseid, score);
			break;
		case cancle:
			break;
		}

	} while (input);
}
void DelStuCo()
{
	int input = 0;
	int tmp = 0;
	int studentid = 0;
	int courseid = 0;
	STUDENTS* p = stcr->g_students->next;
	COURSES* q = stcr->g_courses->next;
	do
	{
		menu3();
		tmp = scanf("%d", &input);
		switch (input)
		{
		case showstudents:
			p = stcr->g_students->next;
			printf("%20s %6s %12s", "姓名", "学号", "手机号\n");
			while (p != NULL)
			{
				printf("%20s %6d %12s\n", p->student.student_name, p->student.student_number, p->student.student_phone);
				p = p->next;
			}
			break;
		case showcourses:
			q = stcr->g_courses->next;
			printf("%20s %6s\n", "课程名", "课程id");
			while (q != NULL)
			{
				printf("%20s %6d\n", q->course.course_name, q->course.course_number);
				q = q->next;
			}
			break;
		case deletestudent:
			printf("请输入要删除的学生id\n");
			tmp = scanf("%d", &studentid);
			g_DeleteStudent(stcr, studentid);
			break;
		case delatecouse:
			printf("请输入要删除的课程id\n");
			tmp = scanf("%d", &courseid);
			g_DeleteCourse(stcr, courseid);
			break;
		case delatestudfromcours:
			break;
		}
	} while (input);
}

//主函数
int main()
{
	stcr = ReadFromFile();
	//stcr = g_initStCr();

	int input = 0;

	do
	{
		menu1();
		int tmp = scanf("%d", &input);
		switch (input)
		{
		case showallinformation:
			g_PrintStCr(stcr);
			break;
		case addcourse:
			g_AddCourse(stcr);
			break;
		case addstudent:
			g_AddStudent(stcr);
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
			SaveToFile(stcr);
			break;
		case clearscreen:
			system("cls");
			break;
		case exitwithoutsaveing:
			break;
		}

	} while (input);

	//SaveToFile(stcr);
	g_DestroySt_Crs(stcr);
	return 0;
}

/*
int studentid[] = { 1, 2, 3,7,8 };
	int courseid[] = { 1, 2,3,4 };

	int score[] = { 100, -1, 4,5,
					85, 95, 20,70,
					-2, 100 ,-1,-2,
					2, 10 ,-1,-2 ,
					20, 70 ,-2,-1 };
	struct OrthogonalList* head = CreateOrthogonalList(studentid, courseid, score, 5, 4);
	//AddCourse(head, 3);
	//AddStudent(head, 4);
	//AddScore(head, 4, 3, 100);
	//AddScore(head, 4, 1, -2);
	//ModifyScore(head, 4, 3, -2);
	PrintOrthogonalList(head);
	struct O_students* stu4 = GetScoresOfCrs(head, 3);
	struct O_students* p = stu4;
	printf("sturs_in_3crs\n");
	while (p != NULL)
	{
		printf("\tstu_id:%d,stu_score:%d\n", p->studentid, p->score);
		p = p->next;
	}
	//struct O_courses* crs3 = GetScoresOfStu(head, 8);
	//struct O_courses* q = crs3;
	//printf("crs_of_8stu\n");
	//while (q != NULL)
	//{
	//	printf("\tcrs_id:%d\n", q->courseid);
	//	q = q->next;
	//}
	DeleteStudent(head, 8);
	DeleteStudent(head, 1);
	DeleteStudent(head, 9);
	DeleteScore(head, 3, 2);
	DeleteScore(head, 3, 1);
	PrintOrthogonalList(head);
	DestroyOrthogonalList(head);
*/