#include <iostream>
#include "parse_data.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {	

	map<string, course_list> study_info;

	map<string, course_info> course_database;

	//map<string, vector<single_course>> learned_course;
	map<string, vector<string>> learned_course;
	
	map<string, vector<string>> classify_course;

	map<string, graduate_rule> rule;

	fstream fs1;
	fstream fs2;
	fstream fs3;
	fstream fs4;
	fstream fs5;
	fstream fs6;
	fstream fs7;
	fstream fs8;
	fstream fs9;
	fstream fs10;
	fstream fs11;   //  write swe

	fs1.open("C://temp//total_record.csv");
	vector<student> database;
	read_origin_student_data(fs1, database);

	get_course_database(database, course_database);
	get_learned_course_database(database, learned_course);
	//fs2.open("C://temp//analyse_result_1101.csv");
	//fs3.open("C://temp//student_total_credit_1101.csv");
	//fs4.open("C://temp//1101_rule.csv");
	//fs5.open("C://temp//graduate_result.csv");
	//fs6.open("C://temp//course_info.csv");
	//fs7.open("C://temp//study_info.csv");
	//fs8.open("C://temp//graduate_report.csv");
	//fs9.open("C://temp//classify_course_art.csv");
	//fs10.open("C://temp//equivalence_database_art.csv");
	fs11.open("C://temp//swe_course.csv");
	
	string rule_path = "C:\\temp\\rule";
	vector<rule_file_info> files;

	getFiles(rule_path, files);

	//for (auto i = files.begin(); i != files.end(); ++i)
		//cout << i->full_path << "   "<< i->file_name << endl;


	//graduate_rule rule;
	//parse_rule(fs4, rule);
	//parse_rule(fs4, files, rule);
	//dbg_get_student_major_types(database);
	parse_all_rule(files, rule);


	map<string, graduate_rule> stu_course;
	//cout << rule.compulsory.credit << endl;
	
 	pickup_rule(rule, database, stu_course);
	auto reserve_rule = rule;

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
	
	calculate_learned_credits(database, stu_course, credit);
	
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
	/*for (auto i = learned_course.begin(); i != learned_course.end(); ++i)
	{
		cout << i->second.size() << endl;
	}*/

	get_learned_other_course(reserve_rule, learned_course);

	
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

	classify_learned_course(database, study_info);
	
	fs7 << "学号" << "," << "课程类别" << "," << "课程列表" << endl;


	//generation_study_info_report(fs7, study_info);
	generation_graduate_info(fs8, study_info,learned_course,
	credit, course_database, stu_course);

	//classify_course_info(course_database, classify_course);  //total course
	//cout << classify_course.size() << endl;
	//classify_course_art_info(course_database, classify_course, string("艺术"));

	generation_course_classify_info(fs9, classify_course);

	//generation_course_classify_art_info(fs9, classify_course);

	//generation_course_classify_info_calligraphy(fs9, classify_course);

	generation_equivalence_art_info(fs10, classify_course, course_database);

	//generation_equivalence(fs10, classify_course, course_database);

	generation_swe_result(fs11, database);
    
    fs1.close();
    //fs2.close();
    //fs3.close();
    fs4.close();
    fs5.close();
	//fs6.close();
	//fs7.close();
	fs8.close();
	fs9.close();
	fs10.close();
	//fs11 << "last" << endl;
	fs11.close();
	
	/*cout << find_course(course_database, "08241234") << endl;
	cout << find_course(course_database, "08241235") << endl;
	cout << find_course(course_database, "08241059") << endl;
	cout << find_course(course_database, "08241237") << endl;
	cout << find_course(course_database, "08241238") << endl;*/
	//cout << find_course(course_database, "08241238") << endl;
	//getchar();
	//dbg_print_rule(rule);


	cout << levenshtein("abed", "abdd") << endl;
	return 0;
}
