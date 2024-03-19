#define _CRT_SECURE_NO_WARNINGS
#include <conio.h>
#include "manager.h"

MANAGERACOUNT* manager_h;
char username[20] = { 0 };
int issuperpowerd = 0;

//主菜单枚举常量
enum {
	exitwithoutsaveing,
	showallinformation,
	showsortedinformation,
	addcourse,
	addstudent,
	addstudenttocourse,
	modifyscore,
	deleteinfo,
	saveinfo,
	modifymanager,
	changepassword
};
//子菜单枚举常量
enum {
	cancle,
	showstudents,
	showcourses,
	showtogerther,
	readytoinputid,
};
//删除菜单枚举常量
enum {
	deletestudent = 4,
	delatecouse,
	delatestudfromcours
};
//排序菜单枚举常量
enum {
	sortedbycourse = 1,
	sortedbyevaluation,
	showevaluationbyclass
};
//主菜单
void menu1()
{
	printf("==========================================================================\n");
	printf("========================  1.showallinformation   =========================\n");
	printf("========================  2.showsortedinformation=========================\n");
	printf("========================  3.addcourse            =========================\n");
	printf("========================  4.addstudent           =========================\n");
	printf("========================  5.addstudenttocourse   =========================\n");
	printf("========================  6.modifyscore          =========================\n");
	printf("========================  7.deleteinfo           =========================\n");
	printf("========================  8.saveinfo             =========================\n");
	printf("========================  9.modifymanager        =========================\n");
	printf("========================  10.changepassword       =========================\n");
	printf("========================  0.exitwithoutsaveing   =========================\n");
	printf("==========================================================================\n");
	printf(">");

}
//子菜单
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
//删除菜单
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
//排序菜单
void menu4()
{
	printf("==========================================================================\n");
	printf("========================  1.sorted by course     =========================\n");
	printf("========================    (in same class)      =========================\n");
	printf("========================  2.sorted by evaluation =========================\n");
	printf("========================  3.show evaluation by   =========================\n");
	printf("========================         class           =========================\n");
	printf("========================  0.cancle               =========================\n");
	printf("==========================================================================\n");
	printf(">");
}
void menu5()
{
	printf("==========================================================================\n");
	printf("========================  1.showcourses          =========================\n");
	printf("========================  2.readytoinputid       =========================\n");
	printf("========================  0.cancle               =========================\n");
	printf("==========================================================================\n");
	printf(">");
}

//===================================   显示部分   ============================================
//显示学生和课程信息
//显示学生
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
//显示课程
void showco(int together)
{
	if (!together)
		system("cls");
	COURSES* q = stcr->g_courses->next;

	printf("---------------------------------------------------------------------------\n");
	printf("%14s   |%8s   |%12s  |%12s  |%12s  |\n", "课程名", "课程id", "绩点", "课程学分", "课程总分");
	while (q != NULL)
	{
		printf("%14s   |%8d   |%12.2f  |%12.2f  |%12.2f  |\n", q->course.course_name, q->course.course_number, q->course.course_jidian, q->course.couese_credit, q->course.course_score);
		q = q->next;
	}
	printf("---------------------------------------------------------------------------\n\n");

}
void ShowInformation()
{
	//setvbuf(stdout, NULL, _IOFBF, 4096);
	system("cls");
	int sbegin = 1;//从第sbegin个学生显示到第sbegin+9个学生//最初要从1开始
	int cbegin = 1;//从第cbegin个课程显示到第cbegin+6个课程//最初要从1开始
	int input = 0;
	int leftline = 0;
	do
	{
		g_PrintStCr(stcr, sbegin, cbegin);
		leftline = stcr->stu_num - sbegin - 10 + 1 < 0 ? 10 - (stcr->stu_num - sbegin) : 1;
		for (int i = 0; i < leftline * 2; i++)
			printf("\n");
		printf("A：左移  D：右移  W：上移  S：下移动 0：退出");
		//fflush(stdout);
		input = (int)_getch();
		switch (input)
		{
		case 'A':
		case 'a':
			if (cbegin != 1)
				cbegin -= 1;
			break;
		case 'D':
		case 'd':
			if (stcr->co_num - cbegin - 7 + 1 >= 0)
				cbegin += 1;
			break;
		case 'W':
		case 'w':
			if (stcr->stu_num - sbegin - 10 + 1 >= 0)
				sbegin += 5;
			break;
		case 'S':
		case 's':
			if (sbegin != 5)
				sbegin -= 5;
			if(sbegin<1)
				sbegin = 1;
			break;
		case '0':
			input = 0;
			break;
		default:
			break;
		}
		system("cls");
	} while (input);
	//setvbuf(stdout, NULL, _IONBF, 0);
}
void informasionsortedbycourse(int cid)
{
	struct O_students* studentsid_sc = GetScoresOfCrs(stcr->g_head, cid, 1);
	STUDENTS* studentsinfo = GetStInfo(studentsid_sc,stcr, 1);
	struct O_students* p = studentsid_sc;
	STUDENTS* q = studentsinfo;

	COURSES* cop = stcr->g_courses;//找到课程
	while (cop != NULL && cop->course.course_number != cid)
	{
		cop = cop->next;
	}
	if(cop!=NULL)
	{
		printf("课程id:%d 课程名:%s 课程绩点:%f 课程学分:%f 课程总成绩:%.2f\n", cid,
			cop->course.course_name, cop->course.course_jidian, cop->course.couese_credit, cop->course.course_score);
		printf("-------------------------------------------\n");
	}
	else
	{
		printf("课程id:%d 课程名未找到\n", cid);
	}
	printf("%8s   |%14s   |%9s   |\n","学生id","学生姓名","学生成绩");
	while (p != NULL)
	{
		printf("%8d   |%14s   |%9.2f   |\n", p->studentid, q->student.student_name, p->score);
		p = p->next;
		q = q->next;
	}
	printf("-------------------------------------------\n");
	DestroySts(studentsinfo);//销毁学生信息
	struct O_students* tmp = studentsid_sc;
	while (studentsid_sc != NULL)//销毁学生id和成绩
	{
		tmp = studentsid_sc;
		studentsid_sc = studentsid_sc->next;
		free(tmp);
	}
	system("pause");
	system("cls");
}
void SortByCourse()
{
	system("cls");
	int input = 0;
	int chosedclassid = 0;
	do {
		menu5();
		scanf("%d", &input);
		switch (input)
		{
		case (showcourses-1):
			showco(0);
			break;
		case (readytoinputid-2):
			printf("请输入课程id\n");
			scanf("%d", &chosedclassid);
			informasionsortedbycourse(chosedclassid);
			break;
		case cancle:
			break;
		default:
			printf("又？哎\n");
			system("pause");
			system("cls");
			break;
		}
	} while (input);
	system("cls");
}
void SortByEvaluation()
{
	//构建所有课程的数组，以方便快速访问
	COURSES* courses = stcr->g_courses->next;
	COURSE * course_arr = (COURSE*)malloc(sizeof(COURSE) * stcr->co_num);
	if (course_arr == NULL || courses == NULL)
	{
		printf("开辟空间失败\n");
		return;
	}
	while(courses!= NULL)
	{
		course_arr[courses->course.course_number].couese_credit = courses->course.couese_credit;
		course_arr[courses->course.course_number].course_jidian = courses->course.course_jidian;
		course_arr[courses->course.course_number].course_number = courses->course.course_number;
		course_arr[courses->course.course_number].course_score = courses->course.course_score;
		strcpy(course_arr[courses->course.course_number].course_name, courses->course.course_name);
		courses = courses->next;
	}

	//构建指向所有学生的指针数组，以方便快速访问并且不会改变原来的链表
	struct OrthogonalList**student_ps = (struct OrthogonalList**)malloc(sizeof(struct OrthogonalList*) * stcr->stu_num);
	if (student_ps == NULL)
	{
		printf("开辟空间失败\n");
		return;
	}
	struct OrthogonalList* p = stcr->g_head->down;

	while(p!=NULL)
	{
		student_ps[p->studentid] = p;
		p = p->down;
	}
	//对应的构建学生信息指针数组
	STUDENTS** students_ifp = (STUDENTS**)malloc(sizeof(STUDENTS*) * stcr->stu_num);
	if (students_ifp == NULL)
	{
		printf("开辟空间失败\n");
		return;
	}
	STUDENTS* q = stcr->g_students->next;
	while(q!=NULL)
	{
		students_ifp[q->student.student_number] = q;
		q = q->next;
	}
	//student_ps和students_ifp对应使用，排序时需要同时改变两个数组的值
	//计算所有学生的综合成绩
	float* student_score = (float*)malloc(sizeof(float) * stcr->stu_num);
	if (student_score == NULL)
	{
		printf("开辟空间失败\n");
		return;
	}
	for(int i = 0;i<stcr->stu_num;i++)
	{
		student_score[i] = 0;
	}
	for(int i = 0;i<stcr->stu_num;i++)
	{
		struct OrthogonalList* p = student_ps[i]->right;
		int sum_credit = 0;
		while(p!=NULL)
		{
			if(p->score==-2)
			{
				p = p->right;
				continue;
			}
			student_score[i] += (p->score/10-5) * course_arr[p->courseid].couese_credit;//相加所有的课程成绩*课程学分
			sum_credit += course_arr[p->courseid].couese_credit;
			p = p->right;
		}
		if(sum_credit==0)
			student_score[i] = 0;
		else
			student_score[i] /= sum_credit;//综合分
	}
	//排序
	for (int i = 1; i < stcr->stu_num; i++)
	{
		for(int j = 0;j<stcr->stu_num-i;j++)
		{
			if(student_score[j]> student_score[j + 1])
			{
				//交换成绩
				float tmp = student_score[j];
				student_score[j] = student_score[j+1];
				student_score[j+1] = tmp;
				
				//交换学生id和成绩
				struct OrthogonalList* tmp1 = student_ps[j];
				student_ps[j] = student_ps[j + 1];
				student_ps[j + 1] = tmp1;

				//交换学生信息
				STUDENTS* tmp2 = students_ifp[j];
				students_ifp[j] = students_ifp[j + 1];
				students_ifp[j + 1] = tmp2;
			}
		}
	}
	//显示
	printf("-------------------------------------------\n");
	printf("%8s   |%14s   |%9s   |\n","学生id","学生姓名","综合成绩");
	printf("-------------------------------------------\n");
	for(int i = 0;i<stcr->stu_num;i++)
	{
		printf("%8d   |%14s   |%9f   |\n", student_ps[i]->studentid, students_ifp[i]->student.student_name, student_score[i]);
	}
	printf("-------------------------------------------\n");
	printf("%8s   |%14s   |%9s   |\n", "学生id", "学生姓名", "综合成绩");
	printf("-------------------------------------------\n");
	//释放空间
	free(student_ps);
	free(students_ifp);
	free(student_score);
	free(course_arr);
	system("pause");
	system("cls");
}
void ShowEvaluationByClass()
{
	
}

//显示排序过的信息
void ShowSortedInformation()
{
	system("cls");
	int input = 0;
	do
	{
		menu4();
		scanf("%d", &input);
		switch (input)
		{
		case sortedbycourse:
			SortByCourse();
			break;
		case sortedbyevaluation:
			SortByEvaluation();
			break;
		case showevaluationbyclass:
			//ShowEvaluationByClass(stcr);
			break;
		case cancle:
			break;
		default:
			printf("你是不是按错了？\n");
			system("pause");
			break;
		}
	} while (input);
	system("cls");
}


//===================================   添加部分   ============================================
//添加学生
void AddStu()
{
	g_AddStudent(stcr);
	printf("添加成功\n");
	//system("pause");
	system("cls");
}
//添加课程
void AddCo()
{
	g_AddCourse(stcr);
	printf("添加成功\n");
	system("pause");
	system("cls");
}
//添加学生到课程
void addsc()
{
	int studentid = 0;
	int courseid = 0;
	float score = 0;
	int tmp = 0;
	printf("请输入选取的学生id\n");
	tmp = scanf("%d", &studentid);
	printf("请输入选取的课程id\n");
	tmp = scanf("%d", &courseid);
	printf("请输入成绩,输入-2表示暂无成绩\n");
	tmp = scanf("%f", &score);
	AddScore(stcr, studentid, courseid, score);
	printf("添加成功\n");
	//system("pause");
	system("cls");
}
//添加学生到课程
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
//===================================   修改部分   ============================================
//修改学生成绩
void modstuco()
{
	int tmp = 0;
	int courseid = 0;
	int studentid = 0;
	float score = 0;
	printf("请输入选取的学生id\n");
	tmp = scanf("%d", &studentid);
	printf("请输入选取的课程id\n");
	tmp = scanf("%d", &courseid);
	printf("请输入修改后的成绩\n");
	tmp = scanf("%f", &score);
	ModifyScore(stcr->g_head, studentid, courseid, score);
	printf("修改成功\n");
	system("pause");
	system("cls");
}
//修改学生成绩
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
//===================================   删除部分   ============================================
//删除学生
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
//删除课程
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
//删除学生成绩
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
//删除学生课程信息
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
//===================================   保存部分   ============================================
//保存信息到文件
void SaveFile()
{
	SaveToFile(stcr);
	printf("保存成功\n");
	system("pause");
	system("cls");
}

//===================================   管理员部分   ============================================
enum
{
	addmanager = 1,
	deletemanager,
	showmanager
};
managerMenu()
{
	printf("==========================================================================\n");
	printf("========================  1.addmanager         =========================\n");
	printf("========================  2.deletemanager          =========================\n");
	printf("========================  3.showmanager        =========================\n");
	printf("========================  0.cancle               =========================\n");
	printf("==========================================================================\n");
}
void initmanager()
{
	int tmp = 0;
	manager_h = (MANAGERACOUNT*)malloc(sizeof(MANAGERACOUNT));//为账户组开辟空间
	if (manager_h == NULL)//检验是否开辟成功
	{
		printf("开辟空间失败\n");
		return;
	}
	MANAGERACOUNT* p = manager_h;//利用指针p进行账号读取
	manager_h->next = NULL;
	FILE* file;
	file = fopen("mana.dat", "r");
	if (file == NULL)
	{
		printf("打开文件失败\n");
		return;
	}
	char strLine[1024] = { 0 };//用来读取一行
	char readedstr[20] = { 0 };//用来读取一行首字符串
	while (!feof(file))
	{
		fgets(strLine, 1024, file);//读取一行
		sscanf(strLine, "%s", readedstr); //读取一行首字符串
		if (0 == strcmp("info", readedstr))//作比较
		{
			p->next = (MANAGERACOUNT*)malloc(sizeof(MANAGERACOUNT));
			if (p->next == NULL)
			{
				printf("开辟空间失败\n");
				return;
			}
			p = p->next;
			tmp = sscanf(strLine, "%s%s%s%d", readedstr, p->username, p->password, &(p->issuperpowerd));
			p->next = NULL;
		}
		else
			break;
	}
	if (manager_h != NULL)
	{
		p = manager_h;
		manager_h = manager_h->next;
		free(p);
	}
	fclose(file);
	char password[20] = { 0 };
	int input = 0;
	do
	{
		printf("请输入用户名:>\n");
		scanf("%s", username);
		printf("请输入用户密码:>\n");
		scanf("%s", password);
		input = checkuser(username, password);
		if (input == 2)
			printf("输入密码不正确\n");
		else if (input == 1)
			printf("不存在此账号\n");
		else
			printf("登录成功\n");
		system("pause");
		system("cls");

	} while (input);
}
int checkuser(char username[20], char password[20])
{
	MANAGERACOUNT* p = manager_h;
	while (p != NULL)
	{
		if (0 == strcmp(username, p->username) && 0 == strcmp(password, p->password))
		{
			issuperpowerd = p->issuperpowerd;
			return 0;
		}
		else if (0 == strcmp(username, p->username))
		{
			return 2;//表示密码不正确
		}
		p = p->next;
	}
	return 1;//表示未找到该账户
}
void saveManager()
{
	FILE* file;
	file = fopen("mana.dat", "w");
	if (file == NULL)
	{
		printf("保存失败\n");
		return;
	}
	MANAGERACOUNT* p = manager_h;
	while (p != NULL)
	{
		fprintf(file, "info %s %s %d\n", p->username, p->password, p->issuperpowerd);
		p = p->next;
	}
	fprintf(file, "eof");
}
void addManager()
{
	char username[20] = { 0 };
	char password[20] = { 0 };
	int input = 0;
	do
	{
		system("cls");
		printf("请输入要添加的账户名:\n");
		scanf("%s", username);
		input = checkuser(username, "@@@");
		if (input != 1)
			printf("该用户已存在!\n");
		if (strlen(username) < 4)
			printf("用户名最小长度为4\n");
		if (input != 1 || strlen(username) < 4)
			system("pause");
	} while (input != 1);//一直输入账户名，直到找到没有使用过的账号
	do
	{
		system("cls");
		printf("请输入新密码:\n");
		scanf("%s", password);
		if (strlen(password) < 8)
			printf("密码长度不能小于8\n");
		if (0 == strcmp("@@@", password))
			printf("请不要输入3个@的密码\n");
		if (strlen(password) < 8 || 0 == strcmp("@@@", password))
			system("pause");
	} while (0 == strcmp("@@@", password) || strlen(password) < 8);
	MANAGERACOUNT* tmp = (MANAGERACOUNT*)malloc(sizeof(MANAGERACOUNT));
	if (tmp == NULL)
	{
		printf("空间开辟失败\n");
		return;
	}
	tmp->next = manager_h->next;
	manager_h->next = tmp;
	for (int i = 0; i < 20; i++)
	{
		tmp->username[i] = username[i];
		tmp->password[i] = password[i];
	}
	printf("是否授予他管理员权限?是输入yes/no\n");
	scanf("%s", username);
	if (strcmp(username, "yes") == 0)
		tmp->issuperpowerd = 1;
	else
		tmp->issuperpowerd = 0;
	saveManager();
	printf("添加成功\n");
	system("pause");
	system("cls");
}
void showManager()
{
	MANAGERACOUNT* p = manager_h;
	while (p != NULL)
	{
		printf("%s\n", p->username);
		p = p->next;
	}
}
void deleteManager()
{
	char targetname[20] = { 0 };
	do
	{
		system("cls");
		showManager();
		printf("\n请输入你要删除的用户名,输入quit退出\n");
		scanf("%s", targetname);
		if (0 == strcmp("root", targetname))
		{
			printf("不允许删掉root用户\n");
			system("pause");
			continue;
		}
		if (0 == strcmp(targetname, "quit"))
			break;
		if (checkuser(targetname, "@@@") != 1)
		{
			MANAGERACOUNT* p = manager_h;
			if (manager_h != NULL && !strcmp(manager_h->username, targetname))
			{
				p = manager_h;
				manager_h = manager_h->next;
				free(p);
				continue;
			}
			else
			{
				while (p->next != NULL)
				{
					if (0 == strcmp(p->next->username, targetname))
					{
						MANAGERACOUNT* tmp = p->next;
						p->next = p->next->next;
						free(tmp);
						break;
					}
					p = p->next;
				}
			}

		}
	} while (1);
	saveManager();
	printf("添加成功\n");
	system("pause");
	system("cls");
}
void modifyManager()
{
	if(issuperpowerd==0)
	{
		printf("回家练几年再来吧，逼格还不够\n");
		system("pause");
		return;
	}
	int input = 0;
	do
	{
		system("cls");
		managerMenu();
		scanf("%d", &input);
		switch (input)
		{
		case addmanager:
			addManager();
			break;
		case deletemanager:
			deleteManager();
			break;
		case showmanager:
			showManager();
			system("pause");
			break;
		case cancle:
			break;
		default:
			printf("管理员也调皮？\n");
			system("pause");
			break;
		}

	} while (input);

	//modifaymedu();
}
void changePsaaword()
{
	char password[20] = { 0 };
	char newpassword[20] = { 0 };
	int input = 0;
	do
	{
		system("cls");
		printf("请输入原密码以继续更改密码:\n或输入exit来退出\n");
		scanf("%s", password);
		if (0 == strcmp(password, "exit"))
			return;
		if (0 == strcmp(password, "@@@"))
		{
			printf("密码不能为@@@\n");
			system("pause");
			continue;
		}
		if (checkuser(username, password) != 0)
		{
			printf("密码错误\n");
			system("pause");
			continue;
		}
		printf("请输入新密码:\n");
		scanf("%s", newpassword);
		if (0 == strcmp(newpassword, "@@@"))
		{
			printf("密码不能为@@@\n");
			system("pause");
			continue;
		}
		if (strlen(newpassword) < 8)
		{
			printf("密码长度不能小于8\n");
			system("pause");
			continue;
		}
		if (0 == strcmp(newpassword, password))
		{
			printf("新密码不能和旧密码相同\n");
			system("pause");
			continue;
		}
		break;
	} while (1);
	MANAGERACOUNT* p = manager_h;
	while (p != NULL)
	{
		if (0 == strcmp(username, p->username))
		{
			for (int i = 0; i < 20; i++)
				p->password[i] = newpassword[i];
			break;
		}
		p = p->next;
	}
	saveManager();
	printf("修改成功\n");
	system("pause");
	system("cls");

}
//===================================   管理员主页   ============================================
int managerlogin()
{
	//initmanager();
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
		case showsortedinformation:
			ShowSortedInformation();
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
		case modifymanager:
			modifyManager();
			break;
		case 	changepassword:
			//changePsaaword();
			break;
		default:
			printf("嘿嘿，你真会开玩笑\n");
			system("pause");
		}
		system("cls");
	} while (input);
}