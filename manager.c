#define _CRT_SECURE_NO_WARNINGS
#include <conio.h>
#include "manager.h"

MANAGERACOUNT* manager_h;
char username[20] = { 0 };
int issuperpowerd = 0;

//���˵�ö�ٳ���
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
//�Ӳ˵�ö�ٳ���
enum {
	cancle,
	showstudents,
	showcourses,
	showtogerther,
	readytoinputid,
};
//ɾ���˵�ö�ٳ���
enum {
	deletestudent = 4,
	delatecouse,
	delatestudfromcours
};
//����˵�ö�ٳ���
enum {
	sortedbycourse = 1,
	sortedbyevaluation,
	showevaluationbyclass
};
//���˵�
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
//�Ӳ˵�
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
//ɾ���˵�
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
//����˵�
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

//===================================   ��ʾ����   ============================================
//��ʾѧ���Ϳγ���Ϣ
//��ʾѧ��
void showstu()
{
	system("cls");
	STUDENTS* p = stcr->g_students->next;

	printf("---------------------------------------------\n");
	printf("%14s   |%8s   |%12s  |\n", "����", "ѧ��", "�ֻ���");
	while (p != NULL)
	{
		printf("%14s   |%8d   |%12s  |\n", p->student.student_name, p->student.student_number, p->student.student_phone);
		p = p->next;
	}
	printf("---------------------------------------------\n\n");

}
//��ʾ�γ�
void showco(int together)
{
	if (!together)
		system("cls");
	COURSES* q = stcr->g_courses->next;

	printf("---------------------------------------------------------------------------\n");
	printf("%14s   |%8s   |%12s  |%12s  |%12s  |\n", "�γ���", "�γ�id", "����", "�γ�ѧ��", "�γ��ܷ�");
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
	int sbegin = 1;//�ӵ�sbegin��ѧ����ʾ����sbegin+9��ѧ��//���Ҫ��1��ʼ
	int cbegin = 1;//�ӵ�cbegin���γ���ʾ����cbegin+6���γ�//���Ҫ��1��ʼ
	int input = 0;
	int leftline = 0;
	do
	{
		g_PrintStCr(stcr, sbegin, cbegin);
		leftline = stcr->stu_num - sbegin - 10 + 1 < 0 ? 10 - (stcr->stu_num - sbegin) : 1;
		for (int i = 0; i < leftline * 2; i++)
			printf("\n");
		printf("A������  D������  W������  S�����ƶ� 0���˳�");
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

	COURSES* cop = stcr->g_courses;//�ҵ��γ�
	while (cop != NULL && cop->course.course_number != cid)
	{
		cop = cop->next;
	}
	if(cop!=NULL)
	{
		printf("�γ�id:%d �γ���:%s �γ̼���:%f �γ�ѧ��:%f �γ��ܳɼ�:%.2f\n", cid,
			cop->course.course_name, cop->course.course_jidian, cop->course.couese_credit, cop->course.course_score);
		printf("-------------------------------------------\n");
	}
	else
	{
		printf("�γ�id:%d �γ���δ�ҵ�\n", cid);
	}
	printf("%8s   |%14s   |%9s   |\n","ѧ��id","ѧ������","ѧ���ɼ�");
	while (p != NULL)
	{
		printf("%8d   |%14s   |%9.2f   |\n", p->studentid, q->student.student_name, p->score);
		p = p->next;
		q = q->next;
	}
	printf("-------------------------------------------\n");
	DestroySts(studentsinfo);//����ѧ����Ϣ
	struct O_students* tmp = studentsid_sc;
	while (studentsid_sc != NULL)//����ѧ��id�ͳɼ�
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
			printf("������γ�id\n");
			scanf("%d", &chosedclassid);
			informasionsortedbycourse(chosedclassid);
			break;
		case cancle:
			break;
		default:
			printf("�֣���\n");
			system("pause");
			system("cls");
			break;
		}
	} while (input);
	system("cls");
}
void SortByEvaluation()
{
	//�������пγ̵����飬�Է�����ٷ���
	COURSES* courses = stcr->g_courses->next;
	COURSE * course_arr = (COURSE*)malloc(sizeof(COURSE) * stcr->co_num);
	if (course_arr == NULL || courses == NULL)
	{
		printf("���ٿռ�ʧ��\n");
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

	//����ָ������ѧ����ָ�����飬�Է�����ٷ��ʲ��Ҳ���ı�ԭ��������
	struct OrthogonalList**student_ps = (struct OrthogonalList**)malloc(sizeof(struct OrthogonalList*) * stcr->stu_num);
	if (student_ps == NULL)
	{
		printf("���ٿռ�ʧ��\n");
		return;
	}
	struct OrthogonalList* p = stcr->g_head->down;

	while(p!=NULL)
	{
		student_ps[p->studentid] = p;
		p = p->down;
	}
	//��Ӧ�Ĺ���ѧ����Ϣָ������
	STUDENTS** students_ifp = (STUDENTS**)malloc(sizeof(STUDENTS*) * stcr->stu_num);
	if (students_ifp == NULL)
	{
		printf("���ٿռ�ʧ��\n");
		return;
	}
	STUDENTS* q = stcr->g_students->next;
	while(q!=NULL)
	{
		students_ifp[q->student.student_number] = q;
		q = q->next;
	}
	//student_ps��students_ifp��Ӧʹ�ã�����ʱ��Ҫͬʱ�ı����������ֵ
	//��������ѧ�����ۺϳɼ�
	float* student_score = (float*)malloc(sizeof(float) * stcr->stu_num);
	if (student_score == NULL)
	{
		printf("���ٿռ�ʧ��\n");
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
			student_score[i] += (p->score/10-5) * course_arr[p->courseid].couese_credit;//������еĿγ̳ɼ�*�γ�ѧ��
			sum_credit += course_arr[p->courseid].couese_credit;
			p = p->right;
		}
		if(sum_credit==0)
			student_score[i] = 0;
		else
			student_score[i] /= sum_credit;//�ۺϷ�
	}
	//����
	for (int i = 1; i < stcr->stu_num; i++)
	{
		for(int j = 0;j<stcr->stu_num-i;j++)
		{
			if(student_score[j]> student_score[j + 1])
			{
				//�����ɼ�
				float tmp = student_score[j];
				student_score[j] = student_score[j+1];
				student_score[j+1] = tmp;
				
				//����ѧ��id�ͳɼ�
				struct OrthogonalList* tmp1 = student_ps[j];
				student_ps[j] = student_ps[j + 1];
				student_ps[j + 1] = tmp1;

				//����ѧ����Ϣ
				STUDENTS* tmp2 = students_ifp[j];
				students_ifp[j] = students_ifp[j + 1];
				students_ifp[j + 1] = tmp2;
			}
		}
	}
	//��ʾ
	printf("-------------------------------------------\n");
	printf("%8s   |%14s   |%9s   |\n","ѧ��id","ѧ������","�ۺϳɼ�");
	printf("-------------------------------------------\n");
	for(int i = 0;i<stcr->stu_num;i++)
	{
		printf("%8d   |%14s   |%9f   |\n", student_ps[i]->studentid, students_ifp[i]->student.student_name, student_score[i]);
	}
	printf("-------------------------------------------\n");
	printf("%8s   |%14s   |%9s   |\n", "ѧ��id", "ѧ������", "�ۺϳɼ�");
	printf("-------------------------------------------\n");
	//�ͷſռ�
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

//��ʾ���������Ϣ
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
			printf("���ǲ��ǰ����ˣ�\n");
			system("pause");
			break;
		}
	} while (input);
	system("cls");
}


//===================================   ��Ӳ���   ============================================
//���ѧ��
void AddStu()
{
	g_AddStudent(stcr);
	printf("��ӳɹ�\n");
	//system("pause");
	system("cls");
}
//��ӿγ�
void AddCo()
{
	g_AddCourse(stcr);
	printf("��ӳɹ�\n");
	system("pause");
	system("cls");
}
//���ѧ�����γ�
void addsc()
{
	int studentid = 0;
	int courseid = 0;
	float score = 0;
	int tmp = 0;
	printf("������ѡȡ��ѧ��id\n");
	tmp = scanf("%d", &studentid);
	printf("������ѡȡ�Ŀγ�id\n");
	tmp = scanf("%d", &courseid);
	printf("������ɼ�,����-2��ʾ���޳ɼ�\n");
	tmp = scanf("%f", &score);
	AddScore(stcr, studentid, courseid, score);
	printf("��ӳɹ�\n");
	//system("pause");
	system("cls");
}
//���ѧ�����γ�
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
//===================================   �޸Ĳ���   ============================================
//�޸�ѧ���ɼ�
void modstuco()
{
	int tmp = 0;
	int courseid = 0;
	int studentid = 0;
	float score = 0;
	printf("������ѡȡ��ѧ��id\n");
	tmp = scanf("%d", &studentid);
	printf("������ѡȡ�Ŀγ�id\n");
	tmp = scanf("%d", &courseid);
	printf("�������޸ĺ�ĳɼ�\n");
	tmp = scanf("%f", &score);
	ModifyScore(stcr->g_head, studentid, courseid, score);
	printf("�޸ĳɹ�\n");
	system("pause");
	system("cls");
}
//�޸�ѧ���ɼ�
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
//===================================   ɾ������   ============================================
//ɾ��ѧ��
void delstu()
{
	int tmp = 0;
	int studentid = 0;
	printf("������Ҫɾ����ѧ��id\n");
	tmp = scanf("%d", &studentid);
	g_DeleteStudent(stcr, studentid);
	printf("ɾ���ɹ�\n");
	system("pause");
	system("cls");
}
//ɾ���γ�
void delco()
{
	int tmp = 0;
	int courseid = 0;
	printf("������Ҫɾ���Ŀγ�id\n");
	tmp = scanf("%d", &courseid);
	g_DeleteCourse(stcr, courseid);
	printf("ɾ���ɹ�\n");
	system("pause");
	system("cls");
}
//ɾ��ѧ���ɼ�
void delstuco()
{
	int tmp = 0;
	int studentid = 0;
	int courseid = 0;
	printf("������Ҫɾ����ѧ��id\n");
	tmp = scanf("%d", &studentid);
	printf("������Ҫɾ���Ŀγ�id\n");
	tmp = scanf("%d", &courseid);
	DeleteScore(stcr->g_head, studentid, courseid);
	printf("ɾ���ɹ�\n");
	system("pause");
	system("cls");
}
//ɾ��ѧ���γ���Ϣ
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
//===================================   ���沿��   ============================================
//������Ϣ���ļ�
void SaveFile()
{
	SaveToFile(stcr);
	printf("����ɹ�\n");
	system("pause");
	system("cls");
}

//===================================   ����Ա����   ============================================
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
	manager_h = (MANAGERACOUNT*)malloc(sizeof(MANAGERACOUNT));//Ϊ�˻��鿪�ٿռ�
	if (manager_h == NULL)//�����Ƿ񿪱ٳɹ�
	{
		printf("���ٿռ�ʧ��\n");
		return;
	}
	MANAGERACOUNT* p = manager_h;//����ָ��p�����˺Ŷ�ȡ
	manager_h->next = NULL;
	FILE* file;
	file = fopen("mana.dat", "r");
	if (file == NULL)
	{
		printf("���ļ�ʧ��\n");
		return;
	}
	char strLine[1024] = { 0 };//������ȡһ��
	char readedstr[20] = { 0 };//������ȡһ�����ַ���
	while (!feof(file))
	{
		fgets(strLine, 1024, file);//��ȡһ��
		sscanf(strLine, "%s", readedstr); //��ȡһ�����ַ���
		if (0 == strcmp("info", readedstr))//���Ƚ�
		{
			p->next = (MANAGERACOUNT*)malloc(sizeof(MANAGERACOUNT));
			if (p->next == NULL)
			{
				printf("���ٿռ�ʧ��\n");
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
		printf("�������û���:>\n");
		scanf("%s", username);
		printf("�������û�����:>\n");
		scanf("%s", password);
		input = checkuser(username, password);
		if (input == 2)
			printf("�������벻��ȷ\n");
		else if (input == 1)
			printf("�����ڴ��˺�\n");
		else
			printf("��¼�ɹ�\n");
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
			return 2;//��ʾ���벻��ȷ
		}
		p = p->next;
	}
	return 1;//��ʾδ�ҵ����˻�
}
void saveManager()
{
	FILE* file;
	file = fopen("mana.dat", "w");
	if (file == NULL)
	{
		printf("����ʧ��\n");
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
		printf("������Ҫ��ӵ��˻���:\n");
		scanf("%s", username);
		input = checkuser(username, "@@@");
		if (input != 1)
			printf("���û��Ѵ���!\n");
		if (strlen(username) < 4)
			printf("�û�����С����Ϊ4\n");
		if (input != 1 || strlen(username) < 4)
			system("pause");
	} while (input != 1);//һֱ�����˻�����ֱ���ҵ�û��ʹ�ù����˺�
	do
	{
		system("cls");
		printf("������������:\n");
		scanf("%s", password);
		if (strlen(password) < 8)
			printf("���볤�Ȳ���С��8\n");
		if (0 == strcmp("@@@", password))
			printf("�벻Ҫ����3��@������\n");
		if (strlen(password) < 8 || 0 == strcmp("@@@", password))
			system("pause");
	} while (0 == strcmp("@@@", password) || strlen(password) < 8);
	MANAGERACOUNT* tmp = (MANAGERACOUNT*)malloc(sizeof(MANAGERACOUNT));
	if (tmp == NULL)
	{
		printf("�ռ俪��ʧ��\n");
		return;
	}
	tmp->next = manager_h->next;
	manager_h->next = tmp;
	for (int i = 0; i < 20; i++)
	{
		tmp->username[i] = username[i];
		tmp->password[i] = password[i];
	}
	printf("�Ƿ�����������ԱȨ��?������yes/no\n");
	scanf("%s", username);
	if (strcmp(username, "yes") == 0)
		tmp->issuperpowerd = 1;
	else
		tmp->issuperpowerd = 0;
	saveManager();
	printf("��ӳɹ�\n");
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
		printf("\n��������Ҫɾ�����û���,����quit�˳�\n");
		scanf("%s", targetname);
		if (0 == strcmp("root", targetname))
		{
			printf("������ɾ��root�û�\n");
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
	printf("��ӳɹ�\n");
	system("pause");
	system("cls");
}
void modifyManager()
{
	if(issuperpowerd==0)
	{
		printf("�ؼ������������ɣ��Ƹ񻹲���\n");
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
			printf("����ԱҲ��Ƥ��\n");
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
		printf("������ԭ�����Լ�����������:\n������exit���˳�\n");
		scanf("%s", password);
		if (0 == strcmp(password, "exit"))
			return;
		if (0 == strcmp(password, "@@@"))
		{
			printf("���벻��Ϊ@@@\n");
			system("pause");
			continue;
		}
		if (checkuser(username, password) != 0)
		{
			printf("�������\n");
			system("pause");
			continue;
		}
		printf("������������:\n");
		scanf("%s", newpassword);
		if (0 == strcmp(newpassword, "@@@"))
		{
			printf("���벻��Ϊ@@@\n");
			system("pause");
			continue;
		}
		if (strlen(newpassword) < 8)
		{
			printf("���볤�Ȳ���С��8\n");
			system("pause");
			continue;
		}
		if (0 == strcmp(newpassword, password))
		{
			printf("�����벻�ܺ;�������ͬ\n");
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
	printf("�޸ĳɹ�\n");
	system("pause");
	system("cls");

}
//===================================   ����Ա��ҳ   ============================================
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
			printf("�ٺ٣�����Ὺ��Ц\n");
			system("pause");
		}
		system("cls");
	} while (input);
}