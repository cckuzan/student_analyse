#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <set>
#include <map>

using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

typedef unsigned int uint32_t;

class student
{
	public:
	string serial_id;
	string major;
	string student_id;
	string course;
	string credit;
	float float_credit;
	string exam_type;
	string course_type1;
	string course_type2;
	string study_year;
	string study_term;
	string finish_year;
	string finish_term;
	string study_type;
	string finish_type;
	string daily_exam;
	string mid_exam;
	string finial_exam;
	string skill_score;
	string final_score;
	float float_final_score;
	string special_case;
	string remark;
	
	void pickup();
	void cout_serial_id();
};

class credit_calculate
{
	public:
	credit_calculate();
		
	float student_total_credit;
	float required_course_credit;
	float free_course_credit;
	float general_required_course_credit;
	float basic_course;
	float professional_course;
	float restrict_course;
	float general_restrict_credit;
	float professional_restrict_credit;
	float other_credit;
	
	void record_detail(fstream &fs);
};

void record_title(fstream &fs, vector<string> &course_types)
{
	for (vector<string>::iterator i = course_types.begin(); i != course_types.end(); ++i)
	{
		fs << *i;
		if(i + 1 != course_types.end())
			fs << ",";
		else
			fs << endl; 
	}
}

void credit_calculate::record_detail(fstream &fs)
{
	fs << student_total_credit << ",";
	fs << required_course_credit << ",";
	fs << free_course_credit << ",";
	fs << general_required_course_credit << ",";
	fs << basic_course << ",";
	fs << professional_course << ",";
	fs << restrict_course << ",";
	fs << general_restrict_credit << ",";
	fs << professional_restrict_credit << ",";
	fs << other_credit << endl;
}

credit_calculate::credit_calculate()
{
	student_total_credit = 0.0;
	required_course_credit = 0.0;
	free_course_credit = 0.0;
	general_required_course_credit = 0.0;
	basic_course = 0.0;
	professional_course = 0.0;
	restrict_course = 0.0;
	general_restrict_credit = 0.0;
	professional_restrict_credit = 0.0;
	other_credit = 0.0;
}

void student::pickup()
{
	cout << serial_id << endl;
	cout << major << endl;
	cout << student_id << endl;
	cout << course << endl;
	cout << credit << endl;
	cout << exam_type << endl;
	cout << course_type1 << endl;
	cout << course_type2 << endl;
	cout << study_year << endl;
	cout << study_term << endl;
	cout << finish_year << endl;
	cout << finish_term << endl;
	cout << study_type << endl;
	cout << finish_type << endl;
	cout << daily_exam << endl;
	cout << mid_exam << endl;
	cout << finial_exam << endl;
	cout << skill_score << endl;
	cout << final_score << endl;
	cout << special_case << endl;
	cout << remark << endl;
}

void student::cout_serial_id()
{
	cout << serial_id << endl;
}

vector<student> database;

int main(int argc, char** argv) {
	
	fstream fs1;
	fstream fs2;
	fstream fs3;

	fs1.open("C://temp//result_new.csv");
	fs2.open("C://temp//analyse_result.csv");
	fs3.open("C://temp//student_total_credit.csv");
	
	vector<string> course_types;
	course_types.push_back("学号");
	course_types.push_back("总学分");
	course_types.push_back("必修课");
	course_types.push_back("任选课");
	course_types.push_back("通识必修（改）");
	course_types.push_back("学科基础（改）");
	course_types.push_back("专业核心（改）");
	course_types.push_back("限选课");
	course_types.push_back("通识限选（改）");
	course_types.push_back("专业限选（改）");
	course_types.push_back("其他");
	
	string intemp;
	fs1 >> intemp;
	
	map<string, credit_calculate> credit;
	
	while(!fs1.eof())
	{
		student temp_student;
		getline(fs1, temp_student.serial_id, ',');
		getline(fs1, temp_student.major, ',');
		getline(fs1, temp_student.student_id, ',');
		
		if (credit.find(temp_student.student_id) != credit.end())
		{
			credit_calculate temp_credit;
			credit[temp_student.student_id] = temp_credit;
		}
		
		getline(fs1, temp_student.course, ',');
		getline(fs1, temp_student.credit, ',');
		temp_student.float_credit = atof(temp_student.credit.c_str());
		getline(fs1, temp_student.exam_type, ',');
		getline(fs1, temp_student.course_type1, ',');
		getline(fs1, temp_student.course_type2, ',');
		getline(fs1, temp_student.study_year, ',');
		getline(fs1, temp_student.study_term, ',');
		getline(fs1, temp_student.finish_year, ',');
		getline(fs1, temp_student.finish_term, ',');
		getline(fs1, temp_student.study_type, ',');
		getline(fs1, temp_student.finish_type, ',');
		getline(fs1, temp_student.daily_exam, ',');
		getline(fs1, temp_student.mid_exam, ',');
		getline(fs1, temp_student.finial_exam, ',');
		getline(fs1, temp_student.skill_score, ',');
		getline(fs1, temp_student.final_score, ',');
		if (temp_student.final_score == "不及格")
		{
			//cout << "find 合格" << endl;
			temp_student.final_score = "0.0";
		}
		
		if (temp_student.final_score == "合格")
		{
			//cout << "find 合格" << endl;
			temp_student.final_score = "60.0";
		}
		if (temp_student.final_score == "及格")
		{
			//cout << "find 合格" << endl;
			temp_student.final_score = "60.0";
		}
		if (temp_student.final_score == "良好")
		{
			//cout << "find 合格" << endl;
			temp_student.final_score = "80.0";
		}
		if (temp_student.final_score == "中等")
		{
			//cout << "find 合格" << endl;
			temp_student.final_score = "80.0";
		}
		if (temp_student.final_score == "优秀")
		{
			//cout << "find 合格" << endl;
			temp_student.final_score = "90.0";
		}
		
		temp_student.float_final_score = atof(temp_student.final_score.c_str());
		
		getline(fs1, temp_student.special_case, ',');
		getline(fs1, temp_student.remark, '\n');
		database.push_back(temp_student);
	}
	

    //database[0].pickup();
    
    //for (int i = 0; i < 1000; i++)
    //{
    //	database[i].cout_serial_id();
	//}
	
	set<string> course_count;
	set<string> credit_type;
	set<float> credit_set;
	set<float> final_score_set;
	set<string> course_type1_count;
	set<string> course_type2_count;
	for (vector<student>::iterator i = database.begin(); i != database.end(); ++i)
	{
		course_count.insert(i->course);
		credit_type.insert(i->credit);
		credit_set.insert(i->float_credit);
		final_score_set.insert(i->float_final_score);
		course_type1_count.insert(i->course_type1);
		course_type2_count.insert(i->course_type2);
		if (i->float_final_score >= 60.0)
		{
			credit[i->student_id].student_total_credit += i->float_credit;
			if (i->course_type1 == "必修课")
			{
				credit[i->student_id].required_course_credit +=  i->float_credit;
			} else if (i->course_type1 == "任选课")
			{
				credit[i->student_id].free_course_credit +=  i->float_credit;
			} else if (i->course_type1 == "通识必修（改）")
			{
				credit[i->student_id].general_required_course_credit +=  i->float_credit;
			} else if (i->course_type1 == "学科基础（改）")
			{
				credit[i->student_id].basic_course +=  i->float_credit;
			} else if (i->course_type1 == "专业核心（改）")
			{
				credit[i->student_id].professional_course +=  i->float_credit;
			} else if (i->course_type1 == "限选课")
			{
				credit[i->student_id].restrict_course +=  i->float_credit;
			} else if (i->course_type1 == "通识限选（改）")
			{
				credit[i->student_id].general_restrict_credit +=  i->float_credit;
			}  else if (i->course_type1 == "专业限选（改）")
			{
				credit[i->student_id].professional_restrict_credit +=  i->float_credit;
			}  else
			{
				credit[i->student_id].other_credit +=  i->float_credit;
			}
			
		}
	}
	
	uint32_t count_record = 0;
	vector<uint32_t> sort_course;
	
	for (set<string>::iterator j = course_count.begin(); j != course_count.end(); ++j)
	{
		uint32_t total_course = 0;
		for (vector<student>::iterator i = database.begin(); i != database.end(); ++i)
		{
			if (*j == i->course)
			{
				++total_course;
			}
		}
		count_record += total_course;
		sort_course.push_back(total_course);
		//cout << *j << ": " << total_course << endl;
	}
	
	sort(sort_course.begin(), sort_course.end());
	
	cout << database.size() << endl;
    cout << course_count.size() << endl;
    cout << count_record << endl;
    
    //for (vector<uint32_t>::iterator i = sort_course.begin(); i != sort_course.end(); ++i)
    //{
    //	cout << *i << endl;
	//}
    
    for (set<string>::iterator i = credit_type.begin(); i != credit_type.end(); ++i)
    {
    	cout << *i << endl;
	}
	
	for (set<float>::iterator i = credit_set.begin(); i != credit_set.end(); ++i)
	{
		cout << *i << endl;
	}
	
	for (set<float>::iterator i = final_score_set.begin(); i != final_score_set.end(); ++i)
	{
		static uint32_t count = 0; 
		cout << *i << "  ";
		if (count++ % 10 == 0)
			cout << endl; 
	}
	
	for (set<string>::iterator i = course_type1_count.begin(); i != course_type1_count.end(); ++i)
	{
		cout << *i << "  " << endl;
	}
	
	for (set<string>::iterator i = course_type2_count.begin(); i != course_type2_count.end(); ++i)
	{
		cout << *i << "  " << endl;
	}
	
	cout << "credit_type: " << credit_type.size() << endl;
	cout << "credit_set:" <<credit_set.size() << endl;
	cout << "score_size:" << final_score_set.size() << endl; 
	cout << "course_type1:" << course_type1_count.size() << endl;
	cout << "course_type2:" << course_type2_count.size() << endl;
	
	record_title(fs3, course_types);
	
	for (map<string, credit_calculate>::iterator i = credit.begin(); i != credit.end(); ++i)
	{
		fs3 << i->first << ",";
		i->second.record_detail(fs3);
	} 
    
    fs1.close();
    fs2.close();
    fs3.close();
	
	return 0;
}
