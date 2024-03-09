#pragma once


//学生信息
struct STUDENT;
typedef struct STUDENT STUDENT;

//课程信息
struct COURSE;
typedef struct COURSE COURSE;

//学院信息
struct ACADEMY;
typedef struct ACADEMY ACADEMY;

//老师信息
struct TEACHER;
typedef struct TEACHER TEACHER;

//ID链表
struct ID;
typedef struct ID ID;

//班级信息
struct studentCLASS;
typedef struct studentCLASS studentCLASS;

//班级链表
struct CLASSLINK;
typedef struct CLASSLINK CLASSLINK;

//项目链表
struct item_link;
typedef struct item_link item_link;

//论文链表
struct thesis_link;
typedef struct thesis_link thesis_link;

//获奖链表
struct prize_link;
typedef struct prize_link prize_link;




//ID链表
struct ID
{
	int id;										//学生id
	struct id* next;
};

//学生信息
struct STUDENT
{
	int student_number;           //学号
	char student_name[20];        //学生姓名
	char student_phone[12];        //学生电话
	ID* item_head;
	ID* thesis_head;
	ID* prize_head;
};

//课程信息
struct COURSE
{
	int course_number;								    //课程序号
	char course_name[20];								//课程名称
	int couese_credit;									//课程学分
	int course_jidian;									//课程总绩点
	int course_score;									//该课程总分数
};

//学院信息
struct ACADEMY
{
	int acadmy_number;						//学院号
	char acadmy_name[20];					//学院名
	ID* teacher_head;
	ID* class_head;
};

//老师信息
struct TEACHER
{
	int teacher_number[6];						//老师的教师号
	int teacher_year;							//老师年龄
	char teacher_name[20];						//老师姓名
	int teacher_phone[11];						//老师电话
};


//班级信息
struct studentCLASS
{
	int class_number;							//班级号
	ID* students_head;
};
//班级链表
struct CLASSLINK
{
	studentCLASS class1;
	struct CLASSLIKE* next;
};

//项目链表
struct item_link
{
	int item_number;
	char itme_name[20];           //学生参加的项目名称
	int itme_number[4];           //学生参加的项目编号
	int itme_begin[3];            //学生参加的项目的立项时间
	int  itme_end[3];             //学生参加的项目的结束时间

	struct studentite_link* next;
};

//论文链表
struct thesis_link
{
	int thesis_number;
	char thesis_name[20];				//论文的名字
	char thesis_periodical[20];			//论文发表的期刊
	int thesis_pubish[3];				//论文发表的时间 年 月 日
	int thesis_grade;					//论文级别
	struct thesis_link* next;
};

//获奖链表
struct prize_link
{
	int prize_number;
	char prize_name[20];          //获奖项目
	char prize_auspice[20];       //获奖主办方
	int  prize_grade;             //获奖等级：校级，市级，省级，国级，世界级
	int prize_time[3];            //获奖时间 年，月，日
	struct prize_link* next;
};



//读取文件创建学生
STUDENT* CreateStudent(int student_number, char* student_name, char* student_phone)
{


}


