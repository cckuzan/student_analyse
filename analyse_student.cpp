#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <set>
#include <map>
#include <sstream>

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

class subject{
	public:
		float credit;
		vector<string> courses;
		
	subject();
};

subject::subject()
{
	credit = 0.0;
}

class graduate_rule{
	public:
		subject compulsory;
		vector<subject> elective;
		vector<subject> equivalence;
};

void parse_single_rule_by_token(string &input, vector<string> &single_rule, const char token = ',')
{
	single_rule.clear();
	istringstream iss(input);
	string temp;
	
	while(getline(iss, temp, token)) {
		single_rule.push_back(temp);
	}
	//cout << single_rule[0] << endl;
}

void parse_rule_by_single_rule(vector<string> &single_rule, graduate_rule &rule)
{
	if(single_rule.size() < 2)
			return;
			
	if(single_rule[0] == "compulsory")
	{
		//cout << "compulsory" << endl;
		rule.compulsory.credit += atof(single_rule[1].c_str());
		for (vector<string>::iterator i = single_rule.begin() + 2; i != single_rule.end(); ++i)
		{
			rule.compulsory.courses.push_back(*i);
		}
	}
	if(single_rule[0] == "elective")
	{
		//cout << "elective" << endl;
		subject temp;
		temp.credit = atof(single_rule[1].c_str());
		for (vector<string>::iterator i = single_rule.begin() + 2; i != single_rule.end(); ++i)
		{
			temp.courses.push_back(*i);
		}
		rule.elective.push_back(temp);
	}
	if(single_rule[0] == "equivalence")
	{
		subject temp;
		temp.credit = atof(single_rule[1].c_str());
		for (vector<string>::iterator i = single_rule.begin() + 2; i != single_rule.end(); ++i)
		{
			temp.courses.push_back(*i);
		}
		rule.equivalence.push_back(temp);
	}
}

void parse_rule(fstream &fs, graduate_rule &rule)
{
	string intemp;
	
	while(!fs.eof())
	{
		getline(fs, intemp, '\n');
		
		//cout << intemp;
		
		vector<string> outtemp;
		parse_single_rule_by_token(intemp, outtemp, ',');
		parse_rule_by_single_rule(outtemp, rule);
	}
}

vector<student> database;
map<string, graduate_rule> stu_course;

void judge_learned_equivalence(vector<string> &equivalence, graduate_rule &single_student_rule)
{
	for (vector<string>::iterator is = equivalence.begin(); is != equivalence.end(); ++is)
	{
		vector<string>::iterator com_result = find(single_student_rule.compulsory.courses.begin(),
			single_student_rule.compulsory.courses.end(), *is);
		if (com_result != single_student_rule.compulsory.courses.end())
		{
			single_student_rule.compulsory.courses.erase(com_result);
			return;
		}

		for (vector<subject>::iterator i_sub = single_student_rule.elective.begin(); i_sub != single_student_rule.elective.end();
			++i_sub)
		{
			vector<string>::iterator ele_result = find(i_sub->courses.begin(), i_sub->courses.end(), *is);
			if(ele_result != i_sub->courses.end())
			{
				i_sub->courses.erase(ele_result);
				return;
			}
		}
	}
}

void judge_learned_course(vector<student>::iterator &i)
{
	if (stu_course.find(i->student_id) != stu_course.end())
	{
		for(vector<string>::iterator is = stu_course[i->student_id].compulsory.courses.begin();
		is != stu_course[i->student_id].compulsory.courses.end();)
		{
			if (*is == i->course)
			{
				is = stu_course[i->student_id].compulsory.courses.erase(is);
				stu_course[i->student_id].compulsory.credit -= i->float_credit;
				//stu_course[i->student_id].compulsory.courses.end();
			} else
				++is;
		}
		for(vector<subject>::iterator i_sub = stu_course[i->student_id].elective.begin();
		i_sub != stu_course[i->student_id].elective.end(); ++i_sub)
		{
			for (vector<string>::iterator is = i_sub->courses.begin(); is != i_sub->courses.end();)
			if (*is == i->course)
			{
				is = i_sub->courses.erase(is);
				i_sub->credit -= i->float_credit;
			} else
				++is;
		}
		for(vector<subject>::iterator i_sub = stu_course[i->student_id].equivalence.begin();
		i_sub != stu_course[i->student_id].equivalence.end(); ++i_sub)
		{
			for (vector<string>::iterator is = i_sub->courses.begin(); is != i_sub->courses.end();)
			if (*is == i->course)
			{
				judge_learned_equivalence(i_sub->courses, stu_course[i->student_id]);
				i_sub->courses.clear();
				i_sub->credit -= i->float_credit;
				break;
			} else
				++is;
		}
	}
}

int main(int argc, char** argv) {
	//setrlimit(10 * 1024 * 1024);
	
	fstream fs1;
	fstream fs2;
	fstream fs3;
	fstream fs4;
	fstream fs5;

	fs1.open("C://temp//1101.csv");
	fs2.open("C://temp//analyse_result_1101.csv");
	fs3.open("C://temp//student_total_credit_1101.csv");
	fs4.open("C://temp//1101_rule.csv");
	fs5.open("C://temp//graduate_result.csv");
	
	graduate_rule rule;
	parse_rule(fs4, rule);
	//cout << rule.compulsory.credit << endl;
	
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
		
		if (stu_course.find(temp_student.student_id) == stu_course.end())
		{
			stu_course[temp_student.student_id] = rule;
			//cout << stu_course.size() << endl;
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
		judge_learned_course(i);
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
	
	cout << "total record: " << database.size() << endl;
    cout << "course_count: " << course_count.size() << endl;
    cout << "count_record: " << count_record << endl;
    
    //for (vector<uint32_t>::iterator i = sort_course.begin(); i != sort_course.end(); ++i)
    //{
    //	cout << *i << endl;
	//}
    
    /*for (set<string>::iterator i = credit_type.begin(); i != credit_type.end(); ++i)
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
	}*/
	
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
	//map<string, graduate_rule> stu_course;
	cout << "stu_course_size: " << stu_course.size() << endl;
	for (map<string, graduate_rule>::iterator i = stu_course.begin(); i != stu_course.end(); ++i)
	{
		fs5 << i->first << endl;
		fs5 << "compulsory";
		if (i->second.compulsory.credit > 0.000001)
		{
			for (vector<string>::iterator is = i->second.compulsory.courses.begin(); is != i->second.compulsory.courses.end(); ++is)
			{
				if (is + 1 != i->second.compulsory.courses.end())
					fs5 << "," <<*is;
				else
				{
					fs5 << "," << *is << endl;
				}
				    
			}
		} else {
			fs5 << "pass" <<endl;
		}
		fs5 << endl;
		
		for (vector<subject>::iterator i_sub = i->second.elective.begin(); i_sub != i->second.elective.end(); ++i_sub)
		{
			if (i_sub->credit > 0.000001)
			{
				fs5 << "elective" << ",";
				for (vector<string>::iterator is = i_sub->courses.begin(); is != i_sub->courses.end(); ++is)
				{
					if (is + 1 != i_sub->courses.end())
					{
						fs5 << *is << ",";
					} else {
						fs5 << *is << endl;
					}
				}
			}
		}
		//cout << endl;
		//fs5 << i->second.
	}
    
    fs1.close();
    fs2.close();
    fs3.close();
    fs4.close();
    fs5.close();
	
	getchar();
	return 0;
}
