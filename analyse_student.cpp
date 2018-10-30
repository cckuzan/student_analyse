#include <iostream>
#include "parse_data.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {	

	map<string, course_list> study_info;

	map<string, course_info> course_database;

	//map<string, vector<single_course>> learned_course;
	map<string, vector<string>> learned_course;

	fstream fs1;
	fstream fs2;
	fstream fs3;
	fstream fs4;
	fstream fs5;
	fstream fs6;
	fstream fs7;

	fs1.open("C://temp//total_record.csv");
	vector<student> database;
	read_origin_student_data(fs1, database, course_database, learned_course);
	//fs2.open("C://temp//analyse_result_1101.csv");
	//fs3.open("C://temp//student_total_credit_1101.csv");
	fs4.open("C://temp//1101_rule.csv");
	fs5.open("C://temp//graduate_result.csv");
	//fs6.open("C://temp//course_info.csv");
	//fs7.open("C://temp//study_info.csv");
	
	graduate_rule rule;
	parse_rule(fs4, rule);

	map<string, graduate_rule> stu_course;
	//cout << rule.compulsory.credit << endl;
	
	pickup_rule(rule, database, stu_course, "201101");
	graduate_rule reserve_rule = rule;

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
	
	map<string, credit_calculate> credit;
	
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
			
		}
	}
	
	//uint32_t count_record = 0;
	//vector<uint32_t> sort_course;
	
	/*for (set<string>::iterator j = course_count.begin(); j != course_count.end(); ++j)
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
	}*/
	
	//sort(sort_course.begin(), sort_course.end());
	
	cout << "total record: " << database.size() << endl;
    //cout << "course_count: " << course_count.size() << endl;
    //cout << "count_record: " << count_record << endl;
	for (auto i = learned_course.begin(); i != learned_course.end(); ++i)
	{
		cout << i->second.size() << endl;
	}

	for (auto i = learned_course.begin(); i != learned_course.end();)
	{
		for (auto j = reserve_rule.compulsory.courses.begin(); j != reserve_rule.compulsory.courses.end(); ++j)
		{
			auto erase_iter = find(i->second.begin(), i->second.end(), *j);
			if (erase_iter != i->second.end())
			{
				i->second.erase(erase_iter);
			} else {
				++i;
			}
			
		}

		for (auto j = reserve_rule.elective.begin(); j != reserve_rule.elective.end(); ++j)
		{
			for (auto k = j->courses.begin(); k != j->courses.end(); ++k)
			{
				auto erase_iter = find(i->second.begin(), i->second.end(), *k);
				if (erase_iter != i->second.end())
				{
					i->second.erase(erase_iter);
				} else {
					++i;
				}
			}
		}
		
		for (auto j = reserve_rule.equivalence.begin(); j != reserve_rule.equivalence.end(); ++j)
		{
			for (auto k = j->courses.begin(); k != j->courses.end(); ++k)
			{
				auto erase_iter = find(i->second.begin(), i->second.end(), *k);
				if (erase_iter != i->second.end())
				{
					i->second.erase(erase_iter);
				} else {
					++i;
				}
			}
		}
	}

	
	record_title(fs3, course_types);
	
	for (map<string, credit_calculate>::iterator i = credit.begin(); i != credit.end(); ++i)
	{
		fs3 << i->first << ",";
		i->second.record_detail(fs3);
	} 
	//map<string, graduate_rule> stu_course;
	cout << "stu_course_size: " << stu_course.size() << endl;

	generation_graduate_report(fs5, stu_course, learned_course);

	fs6 << "课程代码" << "," << "课程名称" << "," << "考核方式" << "," << "学分" << "," << "修读学年" << endl;

	for (auto i = course_database.begin(); i != course_database.end(); ++i)
	{
		fs6 << i->first << "," << i->second.course_name << "," << i->second.exam_type << "," << i->second.credit << "," << i->second.semester <<endl;
	}


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

		if (learned_course.find(i->student_id)  == learned_course.end())
		{
			vector<string> temp_vstring_course;
			learned_course[i->student_id] = temp_vstring_course;
			learned_course[i->student_id].push_back(temp_single_course);
		} else {
			learned_course[i->student_id].push_back(temp_single_course);
		}

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
	
	fs7 << "学号" << "," << "课程类别" << "," << "课程列表" << endl;


	for (auto i = study_info.begin(); i != study_info.end(); ++i)
	{
		fs7 << i->first << ",";
		if (!i->second.require_select.empty())
		{
			fs7 << "必修课";
			for (auto j = i->second.require_select.begin(); j != i->second.require_select.end(); ++j)
			{
				fs7 << "," << *j;
			}
			fs7 << endl;
		} 
		if (!i->second.free_select.empty())
		{
			fs7 << ",任选课";
			for (auto j = i->second.free_select.begin(); j != i->second.free_select.end(); ++j)
			{
				fs7 << "," << *j;
			}
			fs7 << endl;
		} 
		if (!i->second.general_require.empty())
		{
			fs7 << ",通识必修（改）";
			for (auto j = i->second.general_require.begin(); j != i->second.general_require.end(); ++j)
			{
				fs7 << "," << *j;
			}
			fs7 << endl;
		} 
		if (!i->second.subject_basic.empty())
		{
			fs7 << ",学科基础（改）";
			for (auto j = i->second.subject_basic.begin(); j != i->second.subject_basic.end(); ++j)
			{
				fs7 << "," << *j;
			}
			fs7 << endl;
		} 
		if (!i->second.professional_core.empty())
		{
			fs7 << ",专业核心（改）";
			for (auto j = i->second.professional_core.begin(); j != i->second.professional_core.end(); ++j)
			{
				fs7 << "," << *j;
			}
			fs7 << endl;
		} 
		if (!i->second.restrict_select.empty())
		{
			fs7 << ",限选课";
			for (auto j = i->second.restrict_select.begin(); j != i->second.restrict_select.end(); ++j)
			{
				fs7 << "," << *j;
			}
			fs7 << endl;
		} 
		if (!i->second.general_restrict.empty())
		{
			fs7 << ",通识限选（改）";
			for (auto j = i->second.general_restrict.begin(); j != i->second.general_restrict.end(); ++j)
			{
				fs7 << "," << *j;
			}
			fs7 << endl;
		} 
		if (!i->second.professional_restrict.empty())
		{
			fs7 << ",专业限选（改）";
			for (auto j = i->second.professional_restrict.begin(); j != i->second.professional_restrict.end(); ++j)
			{
				fs7 << "," << *j;
			}
			fs7 << endl;
		} 
		if (!i->second.other.empty()){
			fs7 << ",其他";
			for (auto j = i->second.other.begin(); j != i->second.other.end(); ++j)
			{
				fs7 << "," << *j;
			}
			fs7 << endl;
		}
	}
    
    fs1.close();
    //fs2.close();
    //fs3.close();
    fs4.close();
    fs5.close();
	//fs6.close();
	//fs7.close();
	
	/*cout << find_course(course_database, "08241234") << endl;
	cout << find_course(course_database, "08241235") << endl;
	cout << find_course(course_database, "08241059") << endl;
	cout << find_course(course_database, "08241237") << endl;
	cout << find_course(course_database, "08241238") << endl;*/
	//cout << find_course(course_database, "08241238") << endl;
	//getchar();
	return 0;
}
