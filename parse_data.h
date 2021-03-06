#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <set>
#include <map>
#include <sstream>
#include <io.h>

using namespace std;

typedef unsigned int uint32_t;

class student
{
	public:
	string serial_id;
	string major;
	string student_id;
	string course;
	string course_name;
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
	float gpa_value;
	
	void record_detail(fstream &fs);
};

class single_course
{
public:
	string course_id;
	float score;

	single_course();

	//bool operator==(single_course &rvalue);
};

/*bool single_course::operator==(single_course &rvalue)
{
	return this->course_id == rvalue.course_id;
}*/

single_course::single_course()
{
	score = 0.0;
}

class course_list
{
public:
	/*vector<single_course> require_select;
	vector<single_course> free_select;
	vector<single_course> restrict_select;
	vector<single_course> general_require;
	vector<single_course> general_restrict;
	vector<single_course> subject_basic;
	vector<single_course> professional_core;
	vector<single_course> professional_restrict;

	vector<single_course> other;*/

	vector<string> require_select;
	vector<string> free_select;
	vector<string> restrict_select;
	vector<string> general_require;
	vector<string> general_restrict;
	vector<string> subject_basic;
	vector<string> professional_core;
	vector<string> professional_restrict;

	vector<string> other;
};

class rule_file_info {
public:
	string full_path;
	string file_name;
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
	gpa_value = 0.0;
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

void parse_rule(fstream &fs, graduate_rule &rule);

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
	if (single_rule[0] == "import")
	{
		string file_name = single_rule[1];
		fstream temp_fs;
		temp_fs.open(file_name);
		if (temp_fs)
		{
			parse_rule(temp_fs, rule);
		}
	}
}

//class rule_file_info;

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
//class rule_file_info;

void parse_all_rule(vector<rule_file_info> &file_info, map<string, graduate_rule> &rule)
{
	for (auto i = file_info.begin(); i != file_info.end(); ++i)
	{
		string file_name = i->file_name.substr(0,i->file_name.find('.'));
		if (rule.find(file_name) == rule.end())
		{
			graduate_rule temp_rule;
			rule[file_name] = temp_rule;
		}
		else
			return;

		fstream temp_fs;
		temp_fs.open(i->full_path);
		parse_rule(temp_fs, rule[file_name]);
		temp_fs.close();
	}
}

void judge_learned_equivalence(vector<string> &equivalence, graduate_rule &single_student_rule, float credit)
{
	for (vector<string>::iterator is = equivalence.begin(); is != equivalence.end(); ++is)
	{
		vector<string>::iterator com_result = find(single_student_rule.compulsory.courses.begin(),
			single_student_rule.compulsory.courses.end(), *is);
		if (com_result != single_student_rule.compulsory.courses.end())
		{
			single_student_rule.compulsory.courses.erase(com_result);
			single_student_rule.compulsory.credit -= credit;
			return;
		}

		for (vector<subject>::iterator i_sub = single_student_rule.elective.begin(); i_sub != single_student_rule.elective.end();
			++i_sub)
		{
			vector<string>::iterator ele_result = find(i_sub->courses.begin(), i_sub->courses.end(), *is);
			if(ele_result != i_sub->courses.end())
			{
				i_sub->courses.erase(ele_result);
				i_sub->credit -= credit;
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
				//cout << i->course << ":  " << i->float_credit << "leave:  " << i_sub->credit << endl;

			} else
				++is;
		}
		for(vector<subject>::iterator i_sub = stu_course[i->student_id].equivalence.begin();
		i_sub != stu_course[i->student_id].equivalence.end(); ++i_sub)
		{
			for (vector<string>::iterator is = i_sub->courses.begin(); is != i_sub->courses.end();)
			if (*is == i->course)
			{
				judge_learned_equivalence(i_sub->courses, stu_course[i->student_id], i_sub->credit);
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
		//cout << entrance_year << "  " << study_year << "  " << study_term << endl;
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

void get_course_database(vector<student> &database, map<string, course_info> &course_database)
{
	for (auto i = database.begin(); i != database.end(); ++i)
	{
		if (course_database.find(i->course) == course_database.end())
		{
			course_info course_info_temp;
			course_info_temp.course_name = i->course_name;
			course_info_temp.credit = i->float_credit;
			//cout << course_info_temp.credit << endl;
			course_info_temp.exam_type = i->exam_type;

			calculate_semester(course_info_temp, *i);

			course_database[i->course] = course_info_temp;
		} else {
			course_info course_temp;
			if (course_database[i->course].credit != i->float_credit)
				cout << "find not equal:" << i->serial_id << i->course_name << "old["<< course_database[i->student_id].credit << "],new[" 
				<< i->float_credit << "]" <<endl;
			if (course_database[i->course].semester > calculate_semester(course_temp, *i))
				course_database[i->course].semester = calculate_semester(course_temp, *i);

			if (course_database[i->course].semester == 0)
				calculate_semester(course_database[i->course], *i);
		}
	}
}

void get_learned_course_database(vector<student> &database, map<string, vector<string>> &learned_course)
{
	for (auto i = database.begin(); i != database.end(); ++i)
	{
		if (i->float_final_score > 59.99)
		{
			if (learned_course.find(i->student_id) == learned_course.end())
			{
				vector<string> tempstring;
				learned_course[i->student_id] = tempstring;
			}
			learned_course[i->student_id].push_back(i->course);
		}
	}
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
			temp_student.course_name = intemp.substr(pos2 + 1);
			//temp_student.course_
			//course_name = intemp.substr(pos2 + 1);
		} else {
			temp_student.course = intemp.substr(1, 8);
			temp_student.course_name = intemp.substr(8 + 1);
			//course_name = intemp.substr(8 + 1);
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
	}
}

void pickup_rule(map<string, graduate_rule> &rule, vector<student> &database, map<string, graduate_rule> &stu_course)
{
	for (auto i = database.begin(); i != database.end(); ++i)
	{
		if (rule.find(i->student_id.substr(0,6)) != rule.end())
		{
			if (stu_course.find(i->student_id) == stu_course.end())
			{
				stu_course[i->student_id] = rule[i->student_id.substr(0, 6)];
			}
		}
	}
}

void generation_graduate_report(fstream &fs, map<string, graduate_rule> &stu_course, map<string, vector<string> > &learned_course)
{
	for (map<string, graduate_rule>::iterator i = stu_course.begin(); i != stu_course.end(); ++i)
	{
		fs << i->first << endl;
		fs << "compulsory:";
		if ((i->second.compulsory.credit) > 0.000001 && !i->second.compulsory.courses.empty())
		{
			for (vector<string>::iterator is = i->second.compulsory.courses.begin(); is != i->second.compulsory.courses.end(); ++is)
			{
				if (is + 1 != i->second.compulsory.courses.end())
					fs << "," <<*is;
				else
				{
					fs << "," << *is << endl;
				}
				    
			}
		} else {
			fs << "pass" <<endl;
		}
		//fs << endl;
		
		for (vector<subject>::iterator i_sub = i->second.elective.begin(); i_sub != i->second.elective.end(); ++i_sub)
		{
			if (i_sub->credit > 0.000001)
			{
				//cout << i_sub->credit << endl;
				fs << "elective" << ",";
				for (vector<string>::iterator is = i_sub->courses.begin(); is != i_sub->courses.end(); ++is)
				{
					if (is + 1 != i_sub->courses.end())
					{
						fs << *is << ",";
					} else {
						fs << *is << endl;
					}
				}
			}
		}

		if (learned_course.find(i->first) != learned_course.end())
		{
			if (!learned_course[i->first].empty())
			{
				fs << "other learned:";
				for (auto iter = learned_course[i->first].begin(); iter != learned_course[i->first].end(); ++iter)
				{
					fs << "," << *iter;
				}
				fs << endl;
			}
			
		}
		//fs << endl;
		//fs5 << i->second.
	}
}

float find_course(map<string, course_info> &course_info, string course_id)
{
	if (course_info.find(course_id) == course_info.end())
		return 0.0;

	return course_info[course_id].credit;
}

void dbg_print_rule(graduate_rule &rule)
{
	cout << "compulsory:";
	for (auto i = rule.compulsory.courses.begin(); i != rule.compulsory.courses.end(); ++i)
	{
		cout << *i << ",";
	}
	cout << endl;

	for (auto i = rule.elective.begin(); i != rule.elective.end(); ++i)
	{
		cout << "elective:";
		for (auto j = i->courses.begin(); j != i->courses.end(); ++j)
		{
			cout << *j << ",";
		}
		cout << endl;
	}

	for (auto i = rule.equivalence.begin(); i != rule.equivalence.end(); ++i)
	{
		cout << "equivalence:";
		for (auto j = i->courses.begin(); j != i->courses.end(); ++j)
		{
			cout << *j << ",";
		}
		cout << endl;
	}
}

void calculate_learned_credits(vector<student> &database, map<string, graduate_rule> &stu_course,
	map<string, credit_calculate> &credit)
{
	for (vector<student>::iterator i = database.begin(); i != database.end(); ++i)
	{
		judge_learned_course(i, stu_course);
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
			
			if (i->exam_type == "考试" && i->float_final_score >= 60.0)
			{
				credit[i->student_id].gpa_value += (i->float_final_score - 50.0) * i->float_credit / 10;
			}
		}
	}
}

void get_learned_other_course(map<string, graduate_rule> &reserve_rule, map<string, vector<string>> &learned_course)
{
	for (auto i = learned_course.begin(); i != learned_course.end();)
	{
		for (auto j = reserve_rule[i->first].compulsory.courses.begin(); j != reserve_rule[i->first].compulsory.courses.end(); ++j)
		{
			auto erase_iter = find(i->second.begin(), i->second.end(), *j);
			if (erase_iter != i->second.end())
			{
				i->second.erase(erase_iter);
			}
		}

		for (auto j = reserve_rule[i->first].elective.begin(); j != reserve_rule[i->first].elective.end(); ++j)
		{
			for (auto k = j->courses.begin(); k != j->courses.end(); ++k)
			{
				auto erase_iter = find(i->second.begin(), i->second.end(), *k);
				if (erase_iter != i->second.end())
				{
					i->second.erase(erase_iter);
				}
			}
		}
		
		for (auto j = reserve_rule[i->first].equivalence.begin(); j != reserve_rule[i->first].equivalence.end(); ++j)
		{
			for (auto k = j->courses.begin(); k != j->courses.end(); ++k)
			{
				auto erase_iter = find(i->second.begin(), i->second.end(), *k);
				if (erase_iter != i->second.end())
				{
					i->second.erase(erase_iter);
				}
			}
		}
		++i;
	}
}

void classify_learned_course(vector<student> &database, map<string, course_list> &study_info)
{
	for (auto i = database.begin(); i != database.end(); ++i)
	{
		string temp_single_course;
		temp_single_course = i->course;
		//temp_single_course.score = i->float_final_score;

		if (study_info.find(i->student_id) == study_info.end())
		{
			course_list temp_course_list;
			study_info[i->student_id] = temp_course_list;
		}

		/*if (learned_course.find(i->student_id)  == learned_course.end())
		{
			vector<string> temp_vstring_course;
			learned_course[i->student_id] = temp_vstring_course;
			learned_course[i->student_id].push_back(temp_single_course);
		} else {
			learned_course[i->student_id].push_back(temp_single_course);
		}*/

		if (i->course_type1 == "必修课")
		{
			study_info[i->student_id].require_select.push_back(temp_single_course);
		} else if (i->course_type1 == "任选课")
		{
			study_info[i->student_id].free_select.push_back(temp_single_course);
		} else if (i->course_type1 == "通识必修（改）")
		{
			study_info[i->student_id].general_require.push_back(temp_single_course);
		} else if (i->course_type1 == "学科基础（改）")
		{
			study_info[i->student_id].subject_basic.push_back(temp_single_course);
		} else if (i->course_type1 == "专业核心（改）")
		{
			study_info[i->student_id].professional_core.push_back(temp_single_course);
		} else if (i->course_type1 == "限选课")
		{
			study_info[i->student_id].restrict_select.push_back(temp_single_course);
		} else if (i->course_type1 == "通识限选（改）")
		{
			study_info[i->student_id].general_restrict.push_back(temp_single_course);
		}  else if (i->course_type1 == "专业限选（改）")
		{
			study_info[i->student_id].professional_restrict.push_back(temp_single_course);
		}  else
		{
			study_info[i->student_id].other.push_back(temp_single_course);
		}
	}
}

void generation_study_info_report(fstream &fs, map<string, course_list> &study_info)
{
	for (auto i = study_info.begin(); i != study_info.end(); ++i)
	{
		fs << i->first << ",";
		if (!i->second.require_select.empty())
		{
			fs << "必修课";
			for (auto j = i->second.require_select.begin(); j != i->second.require_select.end(); ++j)
			{
				fs << "," << *j;
			}
			fs << endl;
		} 
		if (!i->second.free_select.empty())
		{
			fs << ",任选课";
			for (auto j = i->second.free_select.begin(); j != i->second.free_select.end(); ++j)
			{
				fs << "," << *j;
			}
			fs << endl;
		} 
		if (!i->second.general_require.empty())
		{
			fs << ",通识必修（改）";
			for (auto j = i->second.general_require.begin(); j != i->second.general_require.end(); ++j)
			{
				fs << "," << *j;
			}
			fs << endl;
		} 
		if (!i->second.subject_basic.empty())
		{
			fs << ",学科基础（改）";
			for (auto j = i->second.subject_basic.begin(); j != i->second.subject_basic.end(); ++j)
			{
				fs << "," << *j;
			}
			fs << endl;
		} 
		if (!i->second.professional_core.empty())
		{
			fs << ",专业核心（改）";
			for (auto j = i->second.professional_core.begin(); j != i->second.professional_core.end(); ++j)
			{
				fs << "," << *j;
			}
			fs << endl;
		} 
		if (!i->second.restrict_select.empty())
		{
			fs << ",限选课";
			for (auto j = i->second.restrict_select.begin(); j != i->second.restrict_select.end(); ++j)
			{
				fs << "," << *j;
			}
			fs << endl;
		} 
		if (!i->second.general_restrict.empty())
		{
			fs << ",通识限选（改）";
			for (auto j = i->second.general_restrict.begin(); j != i->second.general_restrict.end(); ++j)
			{
				fs << "," << *j;
			}
			fs << endl;
		} 
		if (!i->second.professional_restrict.empty())
		{
			fs << ",专业限选（改）";
			for (auto j = i->second.professional_restrict.begin(); j != i->second.professional_restrict.end(); ++j)
			{
				fs << "," << *j;
			}
			fs << endl;
		} 
		if (!i->second.other.empty()){
			fs << ",其他";
			for (auto j = i->second.other.begin(); j != i->second.other.end(); ++j)
			{
				fs << "," << *j;
			}
			fs << endl;
		}
	}
}

bool judge_graduate(graduate_rule &graduate)
{
	if (!graduate.compulsory.courses.empty())
		return false;

	for (auto i = graduate.elective.begin(); i != graduate.elective.end(); ++i)
	{
		if (i->credit > 0.000001)
			return false;
	}

    return true;
}

void generation_graduate_info(fstream &fs, map<string, course_list> &study_info, map<string, vector<string>> &learned_course,
	map<string, credit_calculate> &credit, map<string, course_info> &course_database, map<string, graduate_rule> &stu_course)
{
	fs << "学号" << "," << "课程类别" << "," << "学分" << "," << "课程列表" << endl;
	for (auto i = stu_course.begin(); i != stu_course.end(); ++i)
	{
		if (i->first.substr(0, 6) == "201101")
		{
		fs << i->first << ","; fs << "总学分:," << credit[i->first].student_total_credit << endl;

		fs << "," << "必修课," << credit[i->first].required_course_credit;
		for (auto j = study_info[i->first].require_select.begin(); j != study_info[i->first].require_select.end(); ++j)
		{
			fs << "," << *j;
		}
		fs << endl;

		fs << "," << "任选课," << credit[i->first].free_course_credit;
		for (auto j = study_info[i->first].free_select.begin(); j != study_info[i->first].free_select.end(); ++j)
		{
			fs << "," << *j;
		}
		fs << endl;

		fs << "," << "通识必修（改）," << credit[i->first].general_required_course_credit;
		for (auto j = study_info[i->first].general_require.begin(); j != study_info[i->first].general_require.end(); ++j)
		{
			fs << "," << *j;
		}
		fs << endl;

		fs << "," << "学科基础（改）," << credit[i->first].basic_course;
		for (auto j = study_info[i->first].subject_basic.begin(); j != study_info[i->first].subject_basic.end(); ++j)
		{
			fs << "," << *j;
		}
		fs << endl;

		fs << "," << "专业核心（改）," << credit[i->first].professional_course;
		for (auto j = study_info[i->first].professional_core.begin(); j != study_info[i->first].professional_core.end(); ++j)
		{
			fs << "," << *j;
		}
		fs << endl;

		fs << "," << "限选课," << credit[i->first].restrict_course;
		for (auto j = study_info[i->first].restrict_select.begin(); j != study_info[i->first].restrict_select.end(); ++j)
		{
			fs << "," << *j;
		}
		fs << endl;

		fs << "," << "通识限选（改）," << credit[i->first].general_restrict_credit;
		for (auto j = study_info[i->first].general_restrict.begin(); j != study_info[i->first].general_restrict.end(); ++j)
		{
			fs << "," << *j;
		}
		fs << endl;

		fs << "," << "专业限选（改）," << credit[i->first].professional_restrict_credit;
		for (auto j = study_info[i->first].professional_restrict.begin(); j != study_info[i->first].professional_restrict.end(); ++j)
		{
			fs << "," << *j;
		}
		fs << endl;

		fs << "," << "其他," << credit[i->first].other_credit;
		for (auto j = study_info[i->first].other.begin(); j != study_info[i->first].other.end(); ++j)
		{
			fs << "," << *j;
		}
		fs << endl;

		fs << "," << "要求以外,";
		float temp = 0.0;
		for (auto j = learned_course[i->first].begin(); j != learned_course[i->first].end(); ++j)
		{
			temp += course_database[*j].credit;
		}
		fs << temp;

		for (auto j = learned_course[i->first].begin(); j != learned_course[i->first].end(); ++j)
		{
			fs << "," << *j;
		}
		fs << endl;

		fs << "是否毕业，";

		bool is_graduate = true;

		is_graduate = judge_graduate(stu_course[i->first]);

		if (is_graduate)
			fs << "是" << endl;
		else 
			fs << "否" << endl;

		if (is_graduate)
		{
			fs << "绩点," << credit[i->first].gpa_value << endl;
		}

		if (!is_graduate)
		{
			fs << ",原因" << endl;
			if (!stu_course[i->first].compulsory.courses.empty())
			{
				fs << "必修未修";
				float temp = 0.0;
				for (auto k = stu_course[i->first].compulsory.courses.begin(); k != stu_course[i->first].compulsory.courses.end(); ++k)
				{
					temp += course_database[*k].credit;
				}
				fs << "," << temp;

				for (auto k = stu_course[i->first].compulsory.courses.begin(); k != stu_course[i->first].compulsory.courses.end(); ++k)
				{
					fs << "," << *k;
				}
				fs << endl;
			}

			for (auto k = stu_course[i->first].elective.begin(); k != stu_course[i->first].elective.end(); ++k)
			{
				if (k->credit > 0.0000001)
				{
					fs << "选修未修";
					fs << "," << k->credit;

					for (auto m = k->courses.begin(); m != k->courses.end(); ++m)
					{
						fs << "," << *m;
					}
					fs << endl;
				}
			}
			fs << endl;
		}
	}
	}
}
 
int levenshtein(string str1,string str2)
{
	int n = str1.size();
	int m = str2.size();
	if ( n == 0)
		return m;
	if ( m == 0)
		return n;
	int **Arr = (int**)malloc( (m+1)*sizeof(int*) );
	for (int i=0;i<=m;i++)
		Arr[i] = (int*)malloc( (n+1)*sizeof(int) );
	int cost = 0;
	for(int i=0;i<=n;i++)
		Arr[0][i] = i;
	for(int j=0;j<=m;j++)
		Arr[j][0] = j;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			if (str1[i-1] == str2[j-1])
				cost = 0;
			else
				cost = 1;
			Arr[j][i] = Arr[j-1][i]+1<Arr[j][i-1]+1?Arr[j-1][i]+1:Arr[j][i-1] +1 ;
			Arr[j][i] = Arr[j][i]<Arr[j-1][i-1]+cost?Arr[j][i]:Arr[j-1][i-1]+cost;
		}
	int nEdit = Arr[m][n];
 
	for(int i=0;i<=m;i++)
		free(Arr[i]);
	free(Arr);
	
	return nEdit;
 
}

void classify_course_info(map<string, course_info> &course_database, map<string, vector<string>> &classify_course)
{
	map<string, course_info> temp_course_database = course_database;
	//cout << "course_database_size " << temp_course_database.size() << endl;
	for (; !temp_course_database.empty();)
	{
		auto i = temp_course_database.begin();
		//auto index = ++i;
		
		if (classify_course.find(i->second.course_name) == classify_course.end())
		{
			vector<string> temp_course_list;
			temp_course_list.push_back(i->first);
			classify_course[i->second.course_name] = temp_course_list;
			//i = temp_course_database.erase(i);
		}

		auto temp_iter = i;
		for (auto index = ++temp_iter; index != temp_course_database.end();)
		{
			if (levenshtein(i->second.course_name, index->second.course_name) < 3)
			{
				classify_course[i->second.course_name].push_back(index->first);
				index = temp_course_database.erase(index);
			}
			else {
				++index;
			}
		}

		temp_course_database.erase(temp_course_database.begin());
	}
}


void classify_course_art_info(map<string, course_info> &course_database, map<string, vector<string>> &classify_course, string &type)
{
	map<string, course_info> temp_course_database = course_database;
	//cout << "course_database_size " << temp_course_database.size() << endl;
	vector<string> art_prefix;
	if (type == "书法")
	{
		art_prefix.push_back("书法");
	}

	if (type == "戏曲")
	{
		art_prefix.push_back("戏曲");
	}

	if (type == "戏剧")
	{
		art_prefix.push_back("戏剧");
	}

	if (type == "舞蹈")
	{
		art_prefix.push_back("舞蹈形体");
		art_prefix.push_back("舞蹈鉴赏");
	}

	if (type == "影视")
	{
		art_prefix.push_back("影视鉴赏");
		art_prefix.push_back("电影与幸福感");
		art_prefix.push_back("英语电影视听说");
		art_prefix.push_back("影视服装设计");
		art_prefix.push_back("影视戏剧服装鉴赏");
		art_prefix.push_back("中外法律电影赏析");
	}

	if (type == "美术")
	{
		art_prefix.push_back("美术鉴赏");
	}

	if (type == "音乐")
	{
		art_prefix.push_back("欧美流行音乐与信息技术");
		art_prefix.push_back("欧洲音乐简史");
		art_prefix.push_back("西方音乐魅力赏析");
		art_prefix.push_back("信息技术下的欧美音乐工业");
		art_prefix.push_back("音乐鉴赏");
		art_prefix.push_back("中国民族音乐");
	}

	if (type == "艺术")
	{
		art_prefix.push_back("古代艺术品鉴赏");
		art_prefix.push_back("艺术导论");
		art_prefix.push_back("中国绘画艺术解读");
		art_prefix.push_back("中国绘画艺术赏析");
	}

	/*art_prefix.push_back("艺术");
	art_prefix.push_back("鉴赏");
	art_prefix.push_back("戏曲");
	art_prefix.push_back("书法");
	art_prefix.push_back("戏剧");
	art_prefix.push_back("音乐");
	art_prefix.push_back("美术");
	art_prefix.push_back("影视");
	art_prefix.push_back("文艺");
	art_prefix.push_back("舞蹈");*/
	for (; !temp_course_database.empty();)
	{
		auto i = temp_course_database.begin();
		//auto index = ++i;
		
		bool is_art = false;
		for (auto i_art = art_prefix.begin(); i_art != art_prefix.end(); ++i_art)
		{
			if (i->second.course_name.find(*i_art) != std::string::npos)
			{
				is_art = true;
				break;
			}
		}

		if (!is_art)
		{
			temp_course_database.erase(temp_course_database.begin());
			continue;
		}

		if (classify_course.find(i->second.course_name) == classify_course.end())
		{
			vector<string> temp_course_list;
			temp_course_list.push_back(i->first);
			classify_course[i->second.course_name] = temp_course_list;
			//i = temp_course_database.erase(i);
		}

		auto temp_iter = i;
		for (auto index = ++temp_iter; index != temp_course_database.end();)
		{
			if (levenshtein(i->second.course_name, index->second.course_name) < 3)
			{
				classify_course[i->second.course_name].push_back(index->first);
				index = temp_course_database.erase(index);
			}
			else {
				++index;
			}
		}

		temp_course_database.erase(temp_course_database.begin());
	}
}

void generation_course_classify_info(fstream &fs, map<string, vector<string>> &classify_course)
{
	for (auto i = classify_course.begin(); i != classify_course.end(); ++i)
	{
		fs << i->first;
		for (auto j = i->second.begin(); j != i->second.end(); ++j)
		{
			fs << "," << *j;
		}
		fs << endl;
	}
}

void generation_equivalence_art_info(fstream &fs, map<string, vector<string>> &classify_course, map<string, course_info> &course_database)
{
	if (classify_course.empty())
		return;

	string main_id;
	auto itr = classify_course.begin();
	main_id = itr->second[0];
	auto main_credit = course_database[main_id].credit;

	for (auto i = classify_course.begin(); i != classify_course.end(); ++i)
	{
		if (i->second.size() > 1)
		{
			for (auto j = i->second.begin(); j != i->second.end(); ++j)
			{
				if (*j == main_id)
					continue;

				fs << "equivalence" << ",";
				fs << main_credit << ",";
				fs << main_id << ",";
				fs << *j << endl;
			}
		}
	}
	//cout << "total_size " << total_size << endl;
	//cout << "cal_size " << cal_size << endl;
	//cout << "count " << count << endl;
}

void generation_equivalence(fstream &fs, map<string, vector<string>> &classify_course, map<string, course_info> &course_database)
{
	//int total_size = 0;
	//int cal_size = 0;
	//int count = 0;
	for (auto i = classify_course.begin(); i != classify_course.end(); ++i)
	{
		//total_size += i->second.size();
		string base_course_id = i->second[0];
		if (i->second.size() > 1)
		{
			//count++;
			//cal_size += i->second.size();
			for (auto j = i->second.begin() + 1; j != i->second.end(); ++j)
			{
				fs << "equivalence" << ",";
				fs << course_database[base_course_id].credit << ",";
				fs << base_course_id << ",";
				fs << *j << endl;
			}
		}
	}
	//cout << "total_size " << total_size << endl;
	//cout << "cal_size " << cal_size << endl;
	//cout << "count " << count << endl;
}

void getFiles(string path, vector<rule_file_info>& files)
{
	//文件句柄  
	long   hFile = 0;
	//文件信息  
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//如果是目录,迭代之  
			//如果不是,加入列表  
			if ((fileinfo.attrib &  _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
			    getFiles(p.assign(path).append("\\").append(fileinfo.name), files);
			}
			else {
				rule_file_info temp_info;
				temp_info.full_path = p.assign(path).append("\\").append(fileinfo.name);
				temp_info.file_name = fileinfo.name;
				files.push_back(temp_info);
				//files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			}

		}while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}

void dbg_get_student_major_types(vector<student> &database)
{
	set<string> result;

	for (auto i = database.begin(); i != database.end(); ++i)
	{
		result.insert(i->student_id.substr(0, 6));
	}

	for (auto i = result.begin(); i != result.end(); ++i)
		cout << *i << endl;
}

class pass_or_not
{
public:
	vector<string> pass;
	vector<string> nopass;
};

vector<string> swe_course;
void init_swe_course()
{
	if (!swe_course.empty())
		return;

	swe_course.push_back("05241135");
	swe_course.push_back("05251125");
	swe_course.push_back("05251129");
	swe_course.push_back("06221024");
	swe_course.push_back("06231199");
	swe_course.push_back("06231241");
	swe_course.push_back("08211003");
	swe_course.push_back("08211008");
	swe_course.push_back("08211105");
	swe_course.push_back("08211111");
	swe_course.push_back("08211134");
	swe_course.push_back("08212035");
	swe_course.push_back("08241007");
	swe_course.push_back("08241038");
	swe_course.push_back("08241047");
	swe_course.push_back("08241048");
	swe_course.push_back("08241055");
	swe_course.push_back("08241056");
	swe_course.push_back("08241057");
	swe_course.push_back("08241087");
	swe_course.push_back("08241111");
	swe_course.push_back("08241152");
	swe_course.push_back("08241173");
	swe_course.push_back("08241200");
	swe_course.push_back("08241225");
	swe_course.push_back("08241238");
	swe_course.push_back("08241246");
	swe_course.push_back("08241249");
	swe_course.push_back("08241301");
	swe_course.push_back("08241434");
	swe_course.push_back("08251081");
	swe_course.push_back("08251082");
	swe_course.push_back("08251083");
	swe_course.push_back("08251084");
	swe_course.push_back("08261003");
	swe_course.push_back("08261080");
	swe_course.push_back("08271315");
	swe_course.push_back("08281011");
	swe_course.push_back("08291002");
	swe_course.push_back("08291005");
	swe_course.push_back("08291015");
	swe_course.push_back("08291035");
	swe_course.push_back("08291039");
	swe_course.push_back("08291063");
}

bool filter_swe_course(string course)
{
	init_swe_course();
	for (auto i = swe_course.begin(); i != swe_course.end(); ++i)
	{
		if (*i == course)
			return true;
	}
	return false;
}


void generation_swe_result(fstream &fs, vector<student> &database)
{
	map<string, pass_or_not> study_info;
	for (auto i = database.begin(); i != database.end(); ++i)
	{
		if (i->student_id.substr(4, 2) == "02")
		{
			if (study_info.find(i->student_id) == study_info.end())
			{
				pass_or_not temp_pass;
				study_info[i->student_id] = temp_pass;
			}

			if (!filter_swe_course(i->course))
				continue;

			if (i->float_final_score - 59.9999 > 0.0000000001)
			{
				study_info[i->student_id].pass.push_back(i->course);
			} else
				study_info[i->student_id].nopass.push_back(i->course);
		}
	}

	for (auto i = study_info.begin(); i != study_info.end(); ++i)
	{
		//fs << i->first << endl;

		for (auto j = i->second.pass.begin(); j != i->second.pass.end(); ++j)
		{
			fs << *j << "P";
			if (j != i->second.pass.end() - 1)
				fs << ",";
		}

		if (!i->second.nopass.empty())
			fs << ",";
		for (auto j = i->second.nopass.begin(); j != i->second.nopass.end(); ++j)
		{
			fs << *j << "N";
			if (j != i->second.nopass.end() - 1)
				fs << ",";
		}
		fs << endl;
	}
}