#include <iostream>
#include <regex>
#include <string>
#include <fstream>
#include <windows.h>
#include <map>


using namespace std;

const string Menu[] = { "1. Input", "2. Read from file", "3. Show statistic", "4. Timing", "5. Write file", "6. Quit" };

int Input(), Read(), Show(), Timing(), Write();
int(*Funcs[])() = { nullptr, Input,Read, Show,Timing,Write };
bool checkString(const string& source, string& result);


int getInt(int&);

const int Num = sizeof(Menu) / sizeof(Menu[0]);
map <string, int> mp;
int main()
{
	int c;
	const char* msg = "";
	do
	{
		system("cls");
		for (int i = 0; i < Num; i++)
		{
			cout << Menu[i].c_str() << endl;
		}
		cout << "Your choice:------>";
		do
		{
			cout << msg;
			getInt(c);
			msg = "Error! Repeat, please!";

		} while (c > 6);
		if (c != 6) Funcs[c]();
		msg = "";
	} while (c != 6);

	cout << "\n\n" << endl;
	cout << "--------------That's all! Bye!--------------------------";
	return 0;
}

int Input()
{
	cout << "Enter string:" << endl;
	string str;
	cin.ignore();
	getline(cin, str);
	string result;
	if (checkString(str, result))
	{
		map <string, int> ::iterator it;
		it = mp.find(result);
		if (it == mp.end()) {
			mp.insert(make_pair(result, 1));
		}
		else {
			it->second = it->second + 1;
		}

		cout << "Right!" << result << endl;
	}
	else
	{
		cout << "Wrong!" << endl;
	}
	system("pause");
	return 1;
}


int Read()
{
	fstream fi;
	fi.open("input.txt", ios::in);
	if (fi.good())
	{
		while (!fi.eof())
		{
			string str;
			string result;
			getline(fi, str);
			cout << "string: " << str << " -> ";
			if (checkString(str, result))
			{
				cout << "Right! " << result << endl;
				map <string, int> ::iterator it;
				it = mp.find(result);
				if (it == mp.end()) {
					mp.insert(make_pair(result, 1));
				}
				else {
					it->second = it->second + 1;
				}
			}
			else
			{
				cout << "Wrong!" << endl;
			}
		}
		cout << "file ended" << endl;
	}
	else
	{
		cout << "file input.txt not found" << endl;
	}
	fi.close();
	system("pause");
	return 1;
}



int Write() {
	ofstream f;
	f.open("statistic.txt", ios_base::trunc);
	for (auto it = mp.begin(); it != mp.end(); it++) {
		cout << 1;
		f << it->first << " ";
		f << it->second << endl;
		cout << 1;
	}
	f.close();
	return 1;
}
int Show()
{
	cout << "STATISTIC" << endl;
	for (auto it = mp.begin(); it != mp.end(); it++) {
		cout << "Zone: " << it->first;
		cout << " " << it->second << endl;
	}
	cout << "-------------" << endl;
	system("pause");
	return 1;
}


bool checkString(const string& source, string& result)
{


	regex re("([[:space:]]*)(http:\\/\\/([a-zA-Z0-9]{1,20})|www)(\\.)([a-zA-Z0-9]{1,20})(\\.)([a-zA-Z]{1,5})([[:space:]]*)");

	smatch match;
	if ((!regex_match(source, match, re)))
		return false;
	else {

		result = match[7];

		return true;
	}
}
int Timing()
{
	cout << "Preparing for timing" << endl;
	vector<string> vector;
	ifstream fi = ifstream("input.txt");
	if (fi.good())
	{
		while (!fi.eof())
		{
			string str;
			getline(fi, str);
			vector.push_back(str);
		}
		fi.close();
		cout << "Timing started" << endl;


		auto t = time(0);
		string result;
		for (int j = 0; j < 100000; ++j)
		{
			checkString(vector[j % vector.size()], result);
			if ((j + 1) % 10000 == 0)
				cout << (j + 1) << " : " << time(0) - t << " s" << endl;
		}
		cout << "Timing ended" << endl;
	}
	else
	{
		cout << "file input.txt for timing not found" << endl;
	}
	system("pause");
	return 1;
}

int getInt(int& a)
{
	cin >> a;
	if (!cin.good())
		return -1;
	return 1;
}
