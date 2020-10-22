#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<cstdlib>
#include<stdio.h>
#include<vector>
#include<cmath>
#include<iomanip>
#define PI 3.1415926
using namespace std;

long double stringToDou(string);
int stringToInt(string);
class Answer
{
	private:
		int dim;
		vector<long double>point;
	public:
		void setPoint(int);
		int getPoint(int);
		void setDim(int);
		int getDim();
		void rotation(int);
		void rotation(char, int);
		void reflection(char);
		void contract(float);
		void dilation(float);
		void print();
		~Answer();
};

int main(int argc, char* argv[])
{
	ifstream inFile;
	inFile.open("case1.txt");
	string word, buf;
	int caseNum, dim, problem;
	getline(inFile, word);
	caseNum = stringToInt(word);
	for (int h = 0; h < caseNum; ++h) {
		getline(inFile, word);
		int a = 0;
		dim = 0;
		Answer ans;
		for (int i = 0; i < word.length(); ++i) {
			if (word[i] != '(' && word[i] != ',' && word[i] != ')') {
				buf.resize(buf.size() + 1);
				buf[a] = word[i];
				a++;
			}
			else if (word[i] != '(') {
				ans.setPoint(stringToInt(buf));
				a = 0;
				dim++;
				buf.clear();
			}
		}
		ans.setDim(dim);
		getline(inFile, word);
		problem = stringToInt(word);
		for (int i = 0; i < problem; ++i) {
			getline(inFile, word);
			if (word.find("Rotation") != std::string::npos) {
				int j = 0;
				if (ans.getDim() == 3) {
					while (word[j] != 'X' && word[j] != 'Y' && word[j] != 'Z')
						++j;
					int k = j;
					int h = 0;
					while (k < word.length()) {
						if ((word[k] <= '9' && word[k] >= '0') || word[k] == '-') {
							buf.resize(buf.size() + 1);
							buf[h] = word[k];
							++h;
						}
						++k;
					}
					ans.rotation(word[j], stringToInt(buf));
				}
				else if (ans.getDim() == 2) {
					int n = 0;
					while (j < word.size()) {
						if ((word[j] <= '9' && word[j] >= '0') || word[j] == '-') {
							buf.resize(buf.size() + 1);
							buf[n] = word[j];
							n++;
						}
						j++;
					}
					ans.rotation(stringToInt(buf));
				}
			}
			else if (word.find("Dilation") != std::string::npos) {
				int j = 0;
				int k = 0;
				while (j < word.length()) {
					if ((word[j] <= '9' && word[j] >= '0') || word[j] == '-') {
						buf.resize(buf.size() + 1);
						buf[k] = word[j];
						k++;
					}
					j++;
				}
				ans.dilation(stringToInt(buf));
			}
			else if (word.find("Contraction") != std::string::npos) {
				int j = 0;
				int k = 0;
				while (j != word.length()) {
					if ((word[j] <= '9' && word[j] >= '0') || word[j] == '-') {
						buf.resize(buf.size() + 1);
						buf[k] = word[j];
						k++;
					}
					j++;
				}
				ans.contract(stringToInt(buf));
			}
			else if (word.find("Reflection") != std::string::npos) {
				int j = 0;
				while (j != word.length()) {
					if (word[j] == 'X' || word[j] == 'Y' || word[j] == 'Z') {
						ans.reflection(word[j]);
					}
					j++;
				}
			}
			word.clear();
			buf.clear();
		}
		ans.print();
		if (h != caseNum - 1)
			cout << endl << endl;
	}
	inFile.close();
}

long double stringToDou(string str)
{
	long double buffer;
	stringstream ss;
	ss << str;
	ss >> buffer;
	ss.str("");
	ss.clear();
	return buffer;
}

int stringToInt(string str)
{
	int buffer;
	stringstream ss;
	ss << str;
	ss >> buffer;
	ss.str("");
	ss.clear();
	return buffer;
}

void Answer::setPoint(int p)
{
	point.push_back(p);
}

int Answer::getPoint(int i)
{
	return point[i];
}

void Answer::setDim(int d)
{
	dim = d;
}

int Answer::getDim()
{
	return dim;
}

void Answer::rotation(int ang)
{
	long double a = point[0];
	point[0] = point[0] * cos(ang * PI / 180.0f) - point[1] * sin(ang * PI / 180.0f);
	point[1] = a * sin(ang * PI / 180.0f) + point[1] * cos(ang * PI / 180.0f);
}

void Answer::rotation(char p, int ang)
{
	if (p == 'X') {
		long double a = point[1];
		point[1] = point[1] * cos(ang * PI / 180.0f) - point[2] * sin(ang * PI / 180.0f);
		point[2] = a * sin(ang * PI / 180.0f) + point[2] * (cos(ang * PI / 180.0f));
	}
	else if (p == 'Y') {
		long double a = point[0];
		point[0] = point[0] * cos(ang * PI / 180.0f) + point[2] * sin(ang * PI / 180.0f);
		point[2] = a * sin(ang * PI / 180.0f) * (-1) + point[2] * cos(ang * PI / 180.0f);
	}
	else if (p == 'Z') {
		long double a = point[0];
		point[0] = point[0] * cos(ang * PI / 180.0f) - point[1] * sin(ang * PI / 180.0f);
		point[1] = a * sin(ang * PI / 180.0f) + point[1] * cos(ang * PI / 180.0f);
	}
}

void Answer::reflection(char r)
{
	int p;
	if (r == 'X')
		p = 0;
	else if (r == 'Y')
		p = 1;
	else if (r == 'Z')
		p = 2;
	for (int i = 0; i < point.size(); ++i)
		if (i != p)
			point[i] *= (-1);
}

void Answer::contract(float n)
{
	for (int i = 0; i < point.size(); ++i)
		point[i] /= n;
}

void Answer::dilation(float n)
{
	for (int i = 0; i < point.size(); ++i)
		point[i] *= n;
}

void Answer::print()
{
	for (int i = 0; i < point.size(); ++i) {
		cout << fixed << setprecision(7) << point[i];
		if (i != point.size() - 1)
			cout << " ";
	}
	cout << endl<<endl;
}

Answer::~Answer()
{
	point.clear();
}