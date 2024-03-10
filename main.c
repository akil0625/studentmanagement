#include "OrthogonalList.h"
#include "OrthogonalList.h"
#include "sch_struct.h"




//Ö÷º¯Êý
int main()
{
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
	return 0;
}