#include <stdio.h>
#include <malloc.h>
#include "OrthogonalList.h"



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
void ModifyScore(struct OrthogonalList* head, int studentid, int courseid, int score)
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
