#include "Priority.h"
#include <fstream>
#include <string>

int main() {
	setlocale(LC_ALL, "Rus");

	cout << "������� ��� �����: ";
	string fname;
	cin >> fname;

	ifstream fin(fname);
	if (!fin.is_open()) {
		cout << "�� ����� ������� ���� " << fname << endl;
	}
	else {
		string s;
		Priority<string> p;

		while (getline(fin, s)) {
			int len = s.length();
			p.add(s, -len);
		}
		cout << p;

		fin.close();
	}

	return 0;
}