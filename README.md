# 1082_Linear-Algebra_hw3
## 主要目標:  
實作這些線性轉換，將原座標點轉換至新座標點。  

## 程式運行方式:  

**該程式執行軟體為Visual 2019。**   
請將程式碼複製至上述軟體中，再編譯執行。  
創建1個檔案，為 case1.txt包含原始座標點及轉換指令，

## 簡要使用說明:  
- Input: 輸入皆由讀檔，檔案格式為: 
- case1.txt  

![avatar](https://upload.cc/i1/2020/10/22/27S1MI.png) 

>> 第 1 行：總共 n 個問題
>> 第 2 行 ~ 第 n+1 行：原始座標點 //例如：(1,1,1) 或 (1,2)
>> 第 n+2 行：總共 m 個問題
>> 第 n+3 行 ~ 第 n+m+2 行：轉換指令 //例如：Rotation 60, Reflection Z 

- Output: 共有n行，輸出內容為A物品和B物品共同出現在幾張訂單中。 
> 輸出範例  
![avatar](https://upload.cc/i1/2020/10/22/gxIT5n.png)  

>> 第 1 行~第 n 行：新座標點

## 程式結構說明:  

### 基本原理:  
相鄰矩陣(Adjacency matrix)在圖學中常被使用來表示資料點(node)間的關係。 

### 引用函式庫說明:
```cpp
#include<iostream> //負責輸出/輸入
#include<string> //負責處理string相關函式
#include<fstream> //負責讀檔
#include<sstream> //引入string恨int轉換公式
#include<vector> //引用vector
#include<cstdlib> //將相關名稱新增至 std 命名空間
#include<cmath>  //引入三角函數計算
#include<iomanip>  //排版用
```

### 變數說明:
```cpp
  ifstream inFile;  //讀檔
	inFile.open("case1.txt");  //讀檔
	string word;  //存放讀入字串
  string buf;  //處理字串用
	int caseNum;  //測資數
  int dim;  //計算座標維度
  int problem;  //每個測資轉換次數
```

### class說明
```cpp
class Answer
{
	private:
		int dim;  //存放座標維度
		vector<long double>point;  //存放座標
	public:
		void setPoint(int); //設定座標點
		int getPoint(int);  //回傳座標點
		void setDim(int); //設定維度
		int getDim(); //回傳維度
		void rotation(int); //旋轉座標
		void rotation(char, int); //沿著某軸旋轉座標
		void reflection(char);  //反射座標
		void contract(float); //收縮座標
		void dilation(float); //擴張座標
		void print(); //輸出結果
		~Answer();  //清除
};
```
### 詳細程式碼說明

```cpp
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
```
> 將讀入的問題資訊做處理存入problem中，
> 並將座標資訊存入ans中。

```cpp
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
```
> 將 string轉成 long double回傳  

```cpp
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
```
> 將 string轉成 int回傳 

```cpp
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
```
> 分別為設定座標點、回傳座標點、設定維度和回傳維度

```cpp
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
oid Answer::reflection(char r)
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
```
> 依照公式將相應數字帶入並計算  


```cpp
void Answer::print()
{
	for (int i = 0; i < point.size(); ++i) {
		cout << fixed << setprecision(7) << point[i];
		if (i != point.size() - 1)
			cout << " ";
	}
}
```
> 依照格是輸出答案
