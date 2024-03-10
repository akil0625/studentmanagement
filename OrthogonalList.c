#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include "OrthogonalList.h"

//��ʼ��
struct St_Crs* g_initStCr()
{
	struct St_Crs* stcr = (struct St_Crs*)malloc(sizeof(struct St_Crs));//����ͷ���
	if (stcr == NULL)
	{
		printf("�ڴ����ʧ��\n");
		return NULL;
	}
	stcr->co_num = 0;
	stcr->stu_num = 0;
	stcr->g_courses = (COURSES*)malloc(sizeof(COURSES));//�����γ̽��
	if (stcr->g_courses == NULL)
	{
		printf("�ڴ����ʧ��\n");
		return NULL;
	}
	stcr->g_courses->next = NULL;
	stcr->g_students = (STUDENTS*)malloc(sizeof(STUDENTS));//����ѧ�����
	if (stcr->g_students == NULL)
	{
		printf("�ڴ����ʧ��\n");
		return NULL;
	}
	stcr->g_students->next = NULL;
	stcr->g_head = (struct OrthogonalList*)malloc(sizeof(struct OrthogonalList));//����ͷ���
	if (stcr->g_head == NULL)
	{
		printf("�ڴ����ʧ��\n");
		return NULL;
	}
	stcr->g_head->right = NULL;
	stcr->g_head->down = NULL;
	stcr->g_head->studentid = -1;
	stcr->g_head->courseid = -1;
	stcr->g_head->score = -1;
	return stcr;
}

//����ʮ������
struct OrthogonalList* CreateOrthogonalList(int* studentid, int* courseid, int* score, int ns,int nc)
{
	struct OrthogonalList *head, *p, *q;
	int i;
	head = (struct OrthogonalList *)malloc(sizeof(struct OrthogonalList));//����ͷ���
	if (head == NULL)
	{
		printf("�ڴ����ʧ��\n");
		return NULL;
	}
	head->right = NULL;
	head->down = NULL;
	head->studentid = -1;
	head->courseid = -1;
	head->score = -1;
	p = head;//pָ��ͷ���
	for (i = 0; i < nc; i++) {//�������пγ̽��
		q = (struct OrthogonalList *)malloc(sizeof(struct OrthogonalList));//�����γ̽��
		if (q == NULL)
		{
			printf("�ڴ����ʧ��\n");
			return NULL;
		}
		q->studentid = -1;//ѧ�����
		q->courseid = courseid[i];//�γ̱��
		q->score = -1;//�ɼ�
		q->right = NULL;//��ָ��
		q->down = NULL;//��ָ��
		p->right = q;//ͷ������ָ��ָ��γ̽��
		p = q;//pָ��γ̽��
	}
	p = head;//pָ��ͷ���
	for (i = 0; i < ns; i++) {//��������ѧ����㲢�Ҵ������гɼ����
		struct OrthogonalList* tmpup = head;//tmpupָ��γ̽�㣬�����������ӳɼ��ڵ�
		q = (struct OrthogonalList *)malloc(sizeof(struct OrthogonalList));//����ѧ�����
		if (q == NULL)
		{
			printf("�ڴ����ʧ��\n");
			return NULL;
		}
		q->right = NULL;//��ָ��
		q->down = NULL;//��ָ��
		q->courseid = -1;//�γ̱��
		q->studentid = studentid[i];//ѧ�����
		q->score = -1;//�ɼ�
		p->down = q;//pָ����һ��ѧ�����
		for (int j = 0; j < nc; j++) {//�������гɼ����
			if(tmpup->right!=NULL)
				tmpup = tmpup->right;
			else
			{
				printf("�γ����ݳ���\n");
				return NULL;
			}
			if (score[i * nc + j] != -1)
			{
				q->right = (struct OrthogonalList *)malloc(sizeof(struct OrthogonalList));//�����ɼ����
				if (q->right == NULL)
				{
					printf("�ڴ����ʧ��\n");
					return NULL;
				}
				q = q->right;//qָ��ɼ����
				q->right = NULL;//��ָ��
				q->down = NULL;//��ָ��
				q->studentid = studentid[i];//ѧ�����
				q->courseid = courseid[j];//�γ̱��
				q->score = score[i * nc + j];//�ɼ�
				struct OrthogonalList* tmpup2 = tmpup;//tmpupָ��γ̽�㣬�����������ӳɼ��ڵ�
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
		p = p->down;//pָ����һ��ѧ�����
	}
	return head;
}

//�����ܵ�ʮ������
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

//����ʮ������
void DestroyOrthogonalList(struct OrthogonalList* head)
{
	struct OrthogonalList* p, * q;
	struct OrthogonalList* tmp;
	p = head;
	while (p != NULL)//pһֱ�����ƶ���ֱ��pΪ��
	{
		q = p;//��Ϊ��ʱ��qָ��p
		p = p->down;//pָ���±ߵĽ��
		while (q != NULL)//qһֱ�����ƶ���ֱ��qΪ��
		{
			tmp = q;
			q = q->right;//qָ���ұߵĽ��
			free(tmp);//�ͷ�q
		}
	}
}

//��ӡʮ������
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
					printf("%10d��   ", q->score);
				else
					printf("      ���޳ɼ� ");

			}
			else if (q->studentid == -1&&q->courseid!=-1)
			{
				printf("%10d��   ", q->courseid);
			}
			else if (q->studentid != -1 && q->courseid == -1)
			{
				printf("%10dͬѧ   ", q->studentid);
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

//��ӿγ�
void AddCourse(struct OrthogonalList* head, int courseid)
{
	struct OrthogonalList* p;
	p = head;
	while (p->right != NULL)//�ҵ����һ���γ̽��
	{
		if(p->right->courseid==courseid)//����γ��Ѿ�����
			return;
		p = p->right;
	}
	p->right = (struct OrthogonalList*)malloc(sizeof(struct OrthogonalList));
	if (p->right == NULL)
	{
		printf("�ڴ����ʧ��\n");
		return;
	}
	p->right->courseid = courseid;
	p->right->studentid = -1;
	p->right->score = -1;
	p->right->down = NULL;
	p->right->right = NULL;
	
}

//���ѧ��
void AddStudent(struct OrthogonalList* head, int studentid)
{
	struct OrthogonalList* p;
	p = head;
	while (p->down != NULL)//�ҵ����һ��ѧ�����
	{
		if (p->down->studentid == studentid)//���ѧ���Ѿ�����
			return;
		p = p->down;
	}
	p->down = (struct OrthogonalList*)malloc(sizeof(struct OrthogonalList));
	if (p->down == NULL)
	{
		printf("�ڴ����ʧ��\n");
		return;
	}
	p->down->studentid = studentid;
	p->down->courseid = -1;
	p->down->score = -1;
	p->down->right = NULL;
	p->down->down = NULL;
}

//���ܵ�ʮ��������ӿγ�
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
		printf("���ٿռ�ʧ��\n");
		return;
	}
	p = p->next;
	printf("������γ�id��\n");
	int tmp = scanf("%d", &(p->course.course_number));//�γ�id
	printf("������γ�����\n");
	tmp = scanf("%s", p->course.course_name);//�γ���
	printf("�����뼨�㣺\n");
	tmp = scanf("%d", &(p->course.course_jidian));//����
	printf("������γ�ѧ��\n");
	tmp = scanf("%d", &(p->course.couese_credit));//�γ�ѧ��
	printf("������γ��ܷ֣�\n");
	tmp = scanf("%d", &(p->course.course_score));//�γ��ܷ�
	AddCourse(stcr->g_head, stcr->co_num);
	stcr->co_num++;
}

//���ܵ�ʮ���������ѧ��
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
		printf("���ٿռ�ʧ��\n");
		return;
	}
	p = p->next;
	p->student.item_head = (ID*)malloc(sizeof(ID));//��Ŀ��Ϣ
	if (p->student.item_head == NULL)
		return;
	p->student.item_head->id = -1;
	p->student.item_head->next = NULL;

	p->student.prize_head = (ID*)malloc(sizeof(ID));//��Ʒ��Ϣ
	if (p->student.prize_head == NULL)
		return;
	p->student.prize_head->id = -1;
	p->student.prize_head->next = NULL;

	p->student.thesis_head = (ID*)malloc(sizeof(ID));//������Ϣ
	if (p->student.thesis_head == NULL)
		return;
	p->student.thesis_head->id = -1;
	p->student.thesis_head->next = NULL;

	printf("������������\n");
	int tmp = scanf("%s", p->student.student_name);//����
	printf("������绰��\n");
	tmp = scanf("%s", p->student.student_phone);//�绰
	p->student.student_number = stcr->stu_num;//ѧ��id
	AddStudent(stcr->g_head, stcr->stu_num);
	stcr->stu_num++;
}

//���ѧ�����γ� score=-2��ʾ���޳ɼ�
void AddScore(struct OrthogonalList* head, int studentid, int courseid, int score)
{
	if (head == NULL)
	{
		printf("��Ϊ��\n");
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
		printf("û�и�ѧ��\n");
		return;
	}
	pc = head;
	while (pc != NULL && pc->courseid != courseid)
	{
		pc = pc->right;
	}
	if (pc == NULL)
	{
		printf("û�иÿγ�\n");
		return;
	}
	while (ps->right != NULL && ps->right->courseid < courseid)//�ҵ���ѧ���Ŀγ̽ڵ�
	{
		ps = ps->right;
	}
	if (ps->right != NULL && ps->right->courseid == courseid)//�����ѧ���Ŀγ̽ڵ����
	{
		return;
	}
	else
	{
		struct OrthogonalList* p = (struct OrthogonalList*)malloc(sizeof(struct OrthogonalList));
		if (p == NULL)
		{
			printf("�ڴ����ʧ��\n");
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
			printf("�ڴ����ʧ��\n");
			return;
		}
		p->courseid = courseid;
		p->studentid = studentid;
		p->score = score;
		p->down = pc->down;
		pc->down = p;
	}
}

//�޸�ѧ���Ŀγ̳ɼ�
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
		printf("û�и�ѧ��\n");
		return;
	}

	pc = head;
	while (pc != NULL && pc->courseid != courseid)
	{
		pc = pc->right;
	}
	if (pc == NULL)
	{
		printf("û�иÿγ�\n");
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
		printf("û�и�ѧ���ĸÿγ�\n");
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
		printf("û�и�ѧ���ĸÿγ�\n");
		return;
	}
}

//�õ�ѧ���Ŀγ̳ɼ�
struct O_courses * GetScoresOfStu(struct OrthogonalList* head, int studentid)
{
	if(head==NULL)
	{
		printf("��Ϊ��\n");
		return NULL;
	}
	struct OrthogonalList* p;
	p = head;
	while (p != NULL && p->studentid != studentid)//�ҵ���ѧ��
	{
		p = p->down;
	}
	if (p == NULL)
	{
		printf("û�и�ѧ��\n");
		return NULL;
	}
	struct O_courses* ans = (struct O_courses*)malloc(sizeof(struct O_courses));
	struct O_courses* pc = ans;
	if (pc == NULL)
	{
		printf("�ڴ����ʧ��\n");
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
			printf("�ڴ����ʧ��\n");
			return NULL;
		}
		pc->next = NULL;
		p = p->right;
	}
	return ans;
}


//�õ��γ̵�ѧ���ɼ�
struct O_students* GetScoresOfCrs(struct OrthogonalList* head, int courseid)
{
	if (head == NULL)
	{
		printf("��Ϊ��\n");
		return NULL;
	}
	struct OrthogonalList* p;
	p = head;
	while (p != NULL && p->courseid != courseid)//�ҵ��ÿγ�
	{
		p = p->right;
	}
	if (p == NULL)
	{
		printf("û�иÿγ�\n");
		return NULL;
	}
	struct O_students* ans = (struct O_students*)malloc(sizeof(struct O_students));
	struct O_students* ps = ans;
	if (ps == NULL)
	{
		printf("�ڴ����ʧ��\n");
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
			printf("�ڴ����ʧ��\n");
			return NULL;
		}
		ps->next = NULL;
		p = p->down;
	}
	return ans;
}

//ɾ��ѧ��
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
		printf("û�и�ѧ��\n");
		return;
	}
	struct OrthogonalList* pc;
	pc = head;
	while (pc != NULL)
	{
		struct OrthogonalList* ps = pc;
		pc = pc->right;
		while (ps->down != NULL)//ɾ����һ�γ����ѧ��
		{
			if(ps->down->studentid==studentid)//����һ����ѧ��
			{
				struct OrthogonalList* tmp = ps->down;//tmpָ��ѧ�����,�����ͷ�
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

//ɾ���γ�
void DeleteCourse(struct OrthogonalList* head, int courseid)
{
	struct OrthogonalList* ps;
	ps = head;
	while (ps != NULL)
	{
		struct OrthogonalList* pc = ps;
		ps = ps->down;
		while (pc->right != NULL)//ɾ����һѧ���Ŀγ�
		{
			if (pc->right->courseid == courseid)//����һ���ǿγ�
			{
				struct OrthogonalList* tmp = pc->right;//tmpָ��γ̽��,�����ͷ�
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

//ɾ��ѧ���Ŀγ�
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
		printf("û�и�ѧ��\n");
		return;
	}
	pc = head;
	while (pc != NULL && pc->courseid != courseid)
	{
		pc = pc->right;
	}
	if (pc == NULL)
	{
		printf("û�иÿγ�\n");
		return;
	}
	while (ps->right != NULL && ps->right->courseid != courseid)
	{
		ps = ps->right;
	}
	if (ps->right == NULL)
	{
		printf("û�и�ѧ���ĸÿγ�\n");
		return;
	}
	while (pc->down != NULL && pc->down->studentid != studentid)
	{
		pc = pc->down;
	}
	if (pc->down == NULL)
	{
		printf("û�и�ѧ���ĸÿγ�\n");
		return;
	}
	struct OrthogonalList* down, * right;
	down = pc->down;
	right = ps->right;
	pc->down = pc->down->down;
	ps->right = ps->right->right;
	free(down);
}

//������Ϣ���ļ�
void SaveToFile(struct OrthogonalList* head, STUDENTS* h_students, COURSES* h_courses)
{
	FILE* fp;
	fp = fopen("st_co.dat", "w");
	if (fp == NULL)
	{
		printf("�ļ���ʧ��\n");
		return;
	}
	//����ѧ����Ϣ
	STUDENTS* stup = h_students;
	fprintf(fp, "students\n");//��־�ſ�ʼд��ѧ����Ϣ
	while (stup != NULL)
	{
		//���ȴ���һ�б����ɿո�ֿ��� ѧ�� ���� �绰��
		fprintf(fp, "%d %s %s \n",
			stup->student.student_number, 
			stup->student.student_name,
			stup->student.student_phone);

		//������һ�б�����Ŀid
		ID* q = stup->student.item_head;
		while (q != NULL)
		{
			fprintf(fp, "%d ", q->id);
			q = q->next;
		}
		fprintf(fp, "\n");

		//��������һ�б�������id
		q = stup->student.thesis_head;
		while (q != NULL)
		{
			fprintf(fp, "%d ", q->id);
			q = q->next;
		}
		fprintf(fp, "\n");

		//����������һ�б���ý�id
		q = stup->student.prize_head;
		while (q != NULL)
		{
			fprintf(fp, "%d ", q->id);
			q = q->next;
		}
		fprintf(fp, "\n");
		stup = stup->next;
	}

	//�����Ŀ��Ϣ
	COURSES* cop = h_courses;
	while (cop != NULL)
	{
		//���ȴ���һ�б����ɿո�ֿ��� ѧ�� ���� �绰��
		fprintf(fp, "%d %s %d %d %d \n",
			cop->course.course_number,
			cop->course.course_name,
			cop->course.course_jidian,
			cop->course.couese_credit,
			cop->course.course_score);
			cop = cop->next;
	}
	//----------------------------------------------
	//����ѧ���Ŀγ̳ɼ�
	struct OrthogonalList* p, * q;
	p = head;

	while (p != NULL)//pָ��ѧ���ڵ㣬һֱ�����ƶ�
	{
		q = p;
		struct OrthogonalList* pco = head;
		while (q != NULL)//q��pָ���ѧ���ڵ㿪ʼ��һֱ�����ƶ�
		{
			if (q->studentid != -1 && q->courseid != -1)
			{
				if (q->courseid != pco->courseid)//����γ̱��벻��ȣ�˵��q�߹��˲����ڵĽڵ㣬�˴�д��-1��ʾ�����ڽڵ�
				{
					while (pco != NULL && pco->courseid != q->courseid)
					{
						pco = pco->right;
						fprintf(fp, "-1 ");
					}
				}
				//����ɼ�����-2��˵�����ڳɼ������۴治���ڳɼ�����Ҫд��
				fprintf(fp, "%d ", q->score);

			}
			else if (q->studentid == -1 && q->courseid != -1) {}//���������ʾ���˵㲻�ǳɼ��ڵ㣬����Ҫд��
			else if (q->studentid != -1 && q->courseid == -1) {}//���������ʾ���˵㲻�ǳɼ��ڵ㣬����Ҫд��
			else {}//���������ʾ���˵㲻�ǳɼ��ڵ㣬����Ҫд��
			q = q->right;
			if (pco != NULL)
				pco = pco->right;;
		}
		p = p->down;
	}





	fclose(fp);
}
