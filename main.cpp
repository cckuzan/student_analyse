#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
#define STU_NUM (1101000)
#define STU_NUM_BEGIN ("201110801")

class student_map
{
public:
	student_map(long long _stu_num, string stu_num_begin);
	long long stu_num;
	string stu_num_begin;
};

student_map::student_map(long long _stu_num, string _stu_num_begin){
	stu_num = _stu_num;
	stu_num_begin = _stu_num_begin;
}

/*class subject_code
{
public:
	subject_code(string &_subject_name, string &_code);
	string subject_name;
	string code;
};

subject_code::subject_code(string &_subject_name, string &_code)
{
	subject_name = _subject_name;
	code = _code;
}*/



int main(int argc, char** argv) {
	map<string, string> subject_code;
	subject_code["计算机科学与技术"] = "01";
	subject_code["软件工程"] = "02";
	subject_code["网络工程"] = "03";
	subject_code["信息与计算科学"] = "04";

	map<string, int> subject_student_num;
	subject_student_num["计算机科学与技术"] = 0;
	subject_student_num["软件工程"] = 0;
	subject_student_num["网络工程"] = 0;
	subject_student_num["信息与计算科学"] = 0;

	//int count = 10000;

	fstream fs1;
	fstream fs2;
	fstream fs3;
	fs1.open("C://temp//student_score.csv");
	fs2.open("C://temp//total_record.csv");
	fs3.open("C://temp//total_record.txt");
	
	string intemp;
	string serial_id;
	string major;
	string stu_num_old;
	string stu_num_new;
	long long stu_num = STU_NUM;
	cout << stu_num;
	getline(fs1, intemp, ',');
	fs2 << intemp << ",";
	getline(fs1, intemp, ',');
	fs2 << intemp << ",";
	getline(fs1, intemp, ',');
	fs2 << intemp << ",";
	getline(fs1, intemp, ',');
	fs1 >> intemp;
	fs2 << intemp;
	while(!fs1.eof())
	{
		getline(fs1, serial_id, ',');
		
		getline(fs1, major, ',');
		
		getline(fs1, intemp, ',');
		string new_stu_num;
		
		new_stu_num = intemp.substr(0, 4);
		new_stu_num += subject_code[major];
		//if (atoi(serial_id.c_str()) >= 16991 && atoi(serial_id.c_str()) < 17010)
		//	cout << new_stu_num << endl;

		if(intemp == "考查")
			cout << "why" << endl;

		long long new_number = 0;
		//cout << "in" << endl;
		fs2 << serial_id << ",";
		fs2 << major << ",";
		if (intemp == stu_num_old)
		{
			//cout << "true" << endl;
			//cout << stu_num << endl;;
			new_number = atoi(new_stu_num.c_str()) * 10000 + subject_student_num[major];
			fs2 << new_number << ",";
		} else {
			//cout << "false" << endl;
			//cout << stu_num << endl;;
			subject_student_num[major]++;
			stu_num_old = intemp;
			new_number = atoi(new_stu_num.c_str()) * 10000 + subject_student_num[major];
			fs2 << new_number << ",";
			fs3 << new_number << "," << intemp << endl;
		}
		getline(fs1, intemp, ',');
		/*getline(fs1, intemp, ',');
		size_t pos1 = intemp.find('[');
		size_t pos2 = intemp.find(']');
		if (pos1 != string::npos)
			fs2 << intemp.substr(pos1 + 1, pos2 - pos1 - 1) << ",";
		else {
			fs2 << intemp.substr(1, 8) << ",";
			cout << stu_num << endl;
		}*/
		getline(fs1, intemp, '\n');
		fs2 << intemp << endl;
	}
	//cout << intemp;
	
	cout << "hello world" << endl;
	
	fs1.close();
	fs2.close();
	fs3.close();
	return 0;
}
