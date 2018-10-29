#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <set>
#include <map>
#include <sstream>

using namespace std;

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

class single_course
{
public:
	string course_id;
	float score;

	single_course();
};

single_course::single_course()
{
	score = 0.0;
}

class course_list
{
public:
	vector<single_course> require_select;
	vector<single_course> free_select;
	vector<single_course> restrict_select;
	vector<single_course> general_require;
	vector<single_course> general_restrict;
	vector<single_course> subject_basic;
	vector<single_course> professional_core;
	vector<single_course> professional_restrict;

	vector<single_course> other;
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

class course_info
{
public:
	course_info();
	string course_name;
	string exam_type;
	float total_time;
	float lecture_time;
	float practice_time;
	float credit;
	int semester;
	float week_time;
};

course_info::course_info()
{
	total_time = 0.0;
	lecture_time = 0.0;
	practice_time = 0.0;
	credit = 0.0;
	semester = 0;
	week_time = 0.0;
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

void judge_learned_course(vector<student>::iterator &i, map<string, graduate_rule> &stu_course)
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

int calculate_semester(course_info &output, student &input)
{
	int result = 1000;
	if (input.remark != "")
		return result;
	int entrance_year = atoi(input.student_id.substr(0, 4).c_str());
	int study_year = atoi(input.study_year.substr(0, 4).c_str());
	int study_term = 0;
	if (input.study_term == "第一学期")
		study_term = 1;
	else
		study_term = 2;

	output.semester = (study_year - entrance_year) * 2 + study_term;
	result = output.semester;
	if (output.semester > 8)
	{
		cout << entrance_year << "  " << study_year << "  " << study_term << endl;
		output.semester = 0;
		return result;
	}

	return result;
}

void ignore_the_first_line(fstream &fs)
{
	string intemp;
	getline(fs, intemp, '\n');
}

void read_origin_student_data(fstream &fs, vector<student> &database)
{
	ignore_the_first_line(fs);
	while(!fs.eof())
	{
		string intemp;
		string course_name;
		student temp_student;
		getline(fs, temp_student.serial_id, ',');
		getline(fs, temp_student.major, ',');
		getline(fs, temp_student.student_id, ',');
		
		/*if (credit.find(temp_student.student_id) != credit.end())
		{
			credit_calculate temp_credit;
			credit[temp_student.student_id] = temp_credit;
		}
		
		if (stu_course.find(temp_student.student_id) == stu_course.end())
		{
			stu_course[temp_student.student_id] = rule;
			//cout << stu_course.size() << endl;
		}*/
		
		getline(fs, intemp, ',');

		size_t pos1 = intemp.find('[');
		size_t pos2 = intemp.find(']');
		if (pos1 != string::npos)
		{
			temp_student.course = intemp.substr(pos1 + 1, pos2 - pos1 - 1);
			course_name = intemp.substr(pos2 + 1);
		} else {
			temp_student.course = intemp.substr(1, 8);
			course_name = intemp.substr(8 + 1);
		}

		getline(fs, temp_student.credit, ',');
		temp_student.float_credit = atof(temp_student.credit.c_str());
		getline(fs, temp_student.exam_type, ',');
		getline(fs, temp_student.course_type1, ',');
		getline(fs, temp_student.course_type2, ',');
		getline(fs, temp_student.study_year, ',');
		getline(fs, temp_student.study_term, ',');
		getline(fs, temp_student.finish_year, ',');
		getline(fs, temp_student.finish_term, ',');
		getline(fs, temp_student.study_type, ',');
		getline(fs, temp_student.finish_type, ',');
		getline(fs, temp_student.daily_exam, ',');
		getline(fs, temp_student.mid_exam, ',');
		getline(fs, temp_student.finial_exam, ',');
		getline(fs, temp_student.skill_score, ',');
		getline(fs, temp_student.final_score, ',');
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
		
		getline(fs, temp_student.special_case, ',');
		getline(fs, temp_student.remark, '\n');
		database.push_back(temp_student);

		/*if (course_database.find(temp_student.course) == course_database.end())
		{
			course_info course_info_temp;
			course_info_temp.course_name = course_name;
			course_info_temp.credit = temp_student.float_credit;
			//cout << course_info_temp.credit << endl;
			course_info_temp.exam_type = temp_student.exam_type;

			calculate_semester(course_info_temp, temp_student);

			course_database[temp_student.course] = course_info_temp;
		} else {
			course_info course_temp;
			if (course_database[temp_student.course].credit != temp_student.float_credit)
				cout << "find not equal:" << temp_student.serial_id << course_name << "old["<< course_database[temp_student.student_id].credit << "],new[" 
				<< temp_student.float_credit << "]" <<endl;
			if (course_database[temp_student.course].semester > calculate_semester(course_temp, temp_student))
				course_database[temp_student.course].semester = calculate_semester(course_temp, temp_student);

			if (course_database[temp_student.course].semester == 0)
				calculate_semester(course_database[temp_student.course], temp_student);
		}*/

	}
}

void pickup_rule(graduate_rule &rule, vector<student> &database, map<string, graduate_rule> &stu_course, string subject)
{
	for (auto i = database.begin(); i != database.end(); ++i)
	{
		if (i->student_id.substr(0,6) == subject)
		{
			if (stu_course.find(i->student_id) == stu_course.end())
			{
				stu_course[i->student_id] = rule;
			}
		}
	}
}