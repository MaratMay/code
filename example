#include<iostream>
#include <cstring>
using namespace std;

class event{
		int year, month, day;
		char *name;
		event(event const &a) {}
	public:
		event(const char* name_, int year_, int month_, int day_);
		virtual void print_res() const;
		void change_date(int new_year,int new_month,int new_day);
		virtual ~event();
		virtual void change_grade(int passed_) = 0;

};

event::event(const char* name_, int year_, int month_, int day_)
{
	year = year_; month = month_; day = day_;
	char *str = new char[strlen(name_) + 1];
	strcpy(str, name_); 
	name = str;
}

event::~event()
{
	delete []name;
}

void event::print_res() const
{
	cout << name << " " << year << " " << month << " " << day;
}

void event::change_date(int new_year,int new_month,int new_day)
{
	year = new_year; 
	month = new_month;
	day = new_day;
}

class test : public event
{
		bool passed;
	public:
		test(const char* name_, int year_, int month_, int day_, bool passed_) : event(name_, year_, month_, day_), passed(passed_) {}
		test(const char* name_, int year_, int month_, int day_, int passed_) : event(name_, year_, month_, day_), passed(passed_ >= 3) {}
		virtual void print_res() const;
		void change_grade(int passed_);
};

void test::print_res() const 
{
	event::print_res();
	cout << " " << (passed ? "true" : "false") << endl;
}

void test::change_grade(int passed_)
{
	passed = passed_ >= 3;
}

class exam : public event
{
		int grade;
	public:
		exam(const char* name_, int year_, int month_, int day_, int grade_) : event(name_, year_, month_, day_), grade(grade_) {}
		virtual void print_res() const;
		void change_grade(int grade_);
};

void exam::print_res() const 
{
	event::print_res();
	cout << " Grade " << grade << endl;
}

void exam::change_grade(int grade_)
{
	grade = grade_;
}
/*
int main()
{
        enum {NUM = 7};
        event *session[NUM];

        session[0]=new test("Mathematical analysis",2023,12,23,true);
        session[1]=new exam("Operation System",2024,1,15,2);
        session[2]=new test("Practicum",2023,12,25,false);
        session[3]=new exam("Differential equation",2024,1,20,3);
        session[4]=new test("Theory of probability",2023,12,29,5);
        session[5]=new exam("Philosophy",2024,1,24,5);
        session[6]=new exam("Numerical methods",2024,1,11,4);

        for (int i=0;i<NUM;i++)
                session[i]->print_res();

        session[2]->change_date(2024,2,25);
        session[2]->change_grade(4);

        session[1]->change_date(2024,3,3);
        session[1]->change_grade(3);

        cout<<endl;
        for (int i=0;i<NUM;i++)
                session[i]->print_res();

        for (int i=0;i<NUM;i++)
        delete session[i];
        return 0;
}*/
