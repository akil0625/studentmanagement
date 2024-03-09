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

struct OrthogonalList {//定义结构体
	int studentid, courseid;
	int score;
	struct OrthogonalList* right;
	struct OrthogonalList* down;
};

//创建十字链表
struct OrthogonalList* CreateOrthogonalList(int* studentid, int* courseid, int* score, int ns, int nc);

//销毁十字链表
void DestroyOrthogonalList(struct OrthogonalList* head);

//打印十字链表
void PrintOrthogonalList(struct OrthogonalList* head);

//添加课程
void AddCourse(struct OrthogonalList* head, int courseid);

//添加学生
void AddStudent(struct OrthogonalList* head, int studentid);

//添加学生到课程 score=-2表示暂无成绩
void AddScore(struct OrthogonalList* head, int studentid, int courseid, int score);

//修改学生的课程成绩
void ModifyScore(struct OrthogonalList* head, int studentid, int courseid, int score);

//得到学生的课程成绩
struct O_courses* GetScoresOfStu(struct OrthogonalList* head, int studentid);

//得到课程的学生成绩
struct O_students* GetScoresOfCrs(struct OrthogonalList* head, int courseid);

//删除学生
void DeleteStudent(struct OrthogonalList* head, int studentid);

//删除课程
void DeleteCourse(struct OrthogonalList* head, int courseid);

//删除学生成绩
void DeleteScore(struct OrthogonalList* head, int studentid, int courseid);