#pragma once
#include <stdio.h>
#include <malloc.h>

struct O_courses;
struct O_students;
struct OrthogonalList;

struct O_students {
	int studentid;
	struct O_students* next;
};

struct O_courses {
	int courseid;
	struct O_courses* next;
};

struct OrthogonalList {//����ṹ��
	int studentid, courseid;
	int score;
	struct OrthogonalList* right;
	struct OrthogonalList* down;
};

//����ʮ������
struct OrthogonalList* CreateOrthogonalList(int* studentid, int* courseid, int* score, int ns, int nc);

//����ʮ������
void DestroyOrthogonalList(struct OrthogonalList* head);

//��ӡʮ������
void PrintOrthogonalList(struct OrthogonalList* head);

//��ӿγ�
void AddCourse(struct OrthogonalList* head, int courseid);

//���ѧ��
void AddStudent(struct OrthogonalList* head, int studentid);

//���ѧ�����γ� score=-2��ʾ���޳ɼ�
void AddScore(struct OrthogonalList* head, int studentid, int courseid, int score);

//�޸�ѧ���Ŀγ̳ɼ�
void ModifyScore(struct OrthogonalList* head, int studentid, int courseid, int score);

//�õ�ѧ���Ŀγ̳ɼ�
struct O_courses* GetScoresOfStu(struct OrthogonalList* head, int studentid);

//�õ��γ̵�ѧ���ɼ�
struct O_students* GetScoresOfCrs(struct OrthogonalList* head, int courseid);

//ɾ��ѧ��
void DeleteStudent(struct OrthogonalList* head, int studentid);

//ɾ���γ�
void DeleteCourse(struct OrthogonalList* head, int courseid);

//ɾ��ѧ���ɼ�
void DeleteScore(struct OrthogonalList* head, int studentid, int courseid);