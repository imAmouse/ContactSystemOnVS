/*
*         c++ 课程设计 ———— 通讯录系统
*            start at 2018-05-05
*     Designed By 空间信息与数字技术1班 官文豪
*/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <sstream>

using namespace std;

//定义联系人
struct person {
	string name, num_phone, num_qq, address;
	bool judge; //判断此数据是否有效，以便于增删、查找、浏览操作
};

//定义电话本基类
class book {
private:
	bool weizhi; //false为电话内部，true为存储卡存储
	person contact[1000]; //每个电话本最大容量为1000
public:
	book();
	void set_weizhi(bool weizhi) { this->weizhi = weizhi; }//返回false为电话内部，true为存储卡存储
	void set_contact(int Num, string Name, string PhoneNum, string QQNum, string Address, bool Judge); //设置联系人信息
	string get_contact(int Num, int Choose); //获取联系人信息（Choose）：1.姓名 2.电话 3.QQ 4.地址
	bool get_weizhi() { return weizhi; } //返回值false为电话内部，true为存储卡存储
	bool get_judge(int Num) { return contact[Num].judge; } //返回联系人空间是否被占用
	void add_person();
	void delete_person(int num); //传入要删除的编号
	void revise_person(int num); //修改
	void find_person(string name, bool IfDel); //查询
	friend ostream& operator<<(ostream &cout, book &temp); //重载<<运算符，实现浏览功能
	book& operator+=(book &temp); //转存：BeTrans转存到当先对象，并返回*（this）
	string GetFileName(); //获取文件存储位置，且便于修改存储文件名
	virtual void Read() = 0;
	virtual void Save() = 0;
};
book::book(){
	for(int i=0;i<1000;i++)
		contact[i].judge=false;
}
void book::set_contact(int Num, string Name, string PhoneNum, string QQNum, string Address, bool Judge) {
	contact[Num].judge=Judge;
	contact[Num].name=Name;
	contact[Num].num_phone=PhoneNum;
	contact[Num].num_qq=QQNum;
	contact[Num].address=Address;
}
string book::get_contact(int Num, int Choose) {
	switch (Choose) {
	case 1:return contact[Num].name;
	case 2:return contact[Num].num_phone;
	case 3:return contact[Num].num_qq;
	case 4:return contact[Num].address;
	default:return "";
	}
}
void book::add_person() {
	int num;
	//查找未被记录的项，若不存在，cout错误并返回
	for (num = 0; num < 1000; num++) {
		if (!contact[num].judge) {
			break;
		}
		else if (num == 999) {
			cout << "此通讯录已满！\n";
			return;
		}
	}
	string temp;
	cout << "请输入联系人姓名：\n";
	cin >> temp;
	contact[num].name=temp;
	contact[num].judge=true;
	cout << "是否记录电话号码？(Y/N)";
	cin >> temp;
	if (temp == "Y" || temp == "y") {
		cout << "请输入：";
		cin >> temp;
		contact[num].num_phone=temp;
	}
	if (weizhi) { //判断位置，手机只记录姓名和电话号
		cout << "是否记录QQ号码？(Y/N)";
		cin >> temp;
		if (temp == "Y" || temp == "y") {
			cout << "请输入：";
			cin >> temp;
			contact[num].num_qq=temp;
		}
		cout << "是否记录联系人地址？(Y/N)";
		cin >> temp;
		if (temp == "Y" || temp == "y") {
			cout << "请输入：";
			cin >> temp;
			contact[num].address=temp;
		}
	}
	cout << "添加成功！\n";
}
void book::delete_person(int num) {
	contact[num].judge=false;
	contact[num].name="";
	contact[num].num_phone="";
	contact[num].num_qq="";
	contact[num].address="";
}
void book::revise_person(int num) {
	string temp;
	cout << "是否修改联系人姓名？（Y/N）";
	cin >> temp;
	if (temp == "Y" || temp == "y") {
		cout << "请输入联系人姓名：\n";
		cin >> temp;
		contact[num].name=temp;
	}
	cout << "是否修改电话号码？(Y/N)";
	cin >> temp;
	if (temp == "Y" || temp == "y") {
		cout << "请输入：";
		cin >> temp;
		contact[num].num_phone=temp;
	}
	if (weizhi) { //判断位置，手机只记录姓名和电话号
		cout << "是否修改QQ号码？(Y/N)";
		cin >> temp;
		if (temp == "Y" || temp == "y") {
			cout << "请输入：";
			cin >> temp;
			contact[num].num_qq=temp;
		}
		cout << "是否修改联系人地址？(Y/N)";
		cin >> temp;
		if (temp == "Y" || temp == "y") {
			cout << "请输入：";
			cin >> temp;
			contact[num].address=temp;
		}
	}
	cout << "修改成功！\n";
}
void book::find_person(string name, bool IfDel = false) {
	/*查询：根据名字/电话号/QQ号/地址查询联系人信息（查询结果不唯一）
	*/
	for (int i = 0; i < 1000; i++) {
		if (get_contact(i, 1).find(name) != string::npos || get_contact(i, 2).find(name) != string::npos || get_contact(i, 3).find(name) != string::npos || get_contact(i, 4).find(name) != string::npos) {
			cout << get_contact(i, 1) << "\t" << contact[i].num_phone;
			if (IfDel == false) {
				if (!weizhi) //手机只记录姓名 电话，QQ和地址输出为“\\\\\\”
					cout << "\t\\\\\\\\\\\\\t\\\\\\\\\\\\\t手机" << "\t" << i << "\n";
				if (weizhi)
					cout << "\t" << contact[i].num_qq << "\t" << contact[i].address << "\t储存卡" << "\t" << i << "\n";
			}
			else if (IfDel == true)
				delete_person(i);
		}
	}
}
ostream& operator<<(ostream &cout, book &temp) {
	for (int i = 0; i < 1000; i++)
		if (temp.contact[i].judge == true) {
			cout << temp.get_contact(i, 1) << "\t" << temp.contact[i].num_phone;
			if (!temp.get_weizhi())
				cout << "\t" << "\\\\\\\\\\\\" << "\t" << "\\\\\\\\\\\\" << "\t手机" << "\t" << i << endl;
			else
				cout << "\t" << temp.contact[i].num_qq << "\t" << temp.contact[i].address << "\t储存卡" << "\t" << i << endl;
		}
		return cout;
}
book& book::operator+=(book &BeTrans) {
	/*
	BeTrans转存到当前对象，并返回*this
	注：避免重复数据的存在。并且在转存是要检查容量是否受限。
	*/
	//分别记录 BeTransNum已有联系人数 和 TransToNum可记录联系人数
	int BeTransNum = 0, TransToNum = 0;
	//计算 BeTransNum已有联系人数 和 TransToNum可记录联系人数
	for (int i = 0; i < 1000; i++) {
		if (BeTrans.contact[i].judge)
			BeTransNum++;
		if (!contact[i].judge)
			TransToNum++;
	}
	//检查容量是否受限
	if (BeTransNum > TransToNum) {
		if (!BeTrans.get_weizhi())
			cout << "手机容量不够！\n";
		else
			cout << "存储卡容量不够！\n";
		return *this;
	}
	//转存
	for (int i = 0; i < 1000; i++) {
		int i1 = 0;
		if (BeTrans.contact[i].judge) {
			//根据姓名判断是否数据重复
			bool JudgeChongFu=false;
			for(int i2=0;i2<1000;i2++){
				if(BeTrans.get_contact(i,1)==contact[i2].name){
					JudgeChongFu=true;
					break;
				}
			}
			if(JudgeChongFu) continue;
			for (; i1 < 1000; i1++) {
				if (!contact[i1].judge) {
					contact[i1].name=BeTrans.get_contact(i, 1);
					contact[i1].address=BeTrans.contact[i].address;
					contact[i1].num_qq=BeTrans.contact[i].num_qq;
					contact[i1].num_phone=BeTrans.contact[i].num_phone;
					contact[i1].judge=true;
					break;
				}
			}
		}
	}
	return *this;
}
string book::GetFileName() { //获取文件名
	if (!weizhi)
		return "PhoneIn.ini";
	else
		return "PhoneCard.ini";
}

//定义手机电话本类
class BookPhone :public book {
public:
	BookPhone() { set_weizhi(false); }
	void Read();
	void Save();
};
void BookPhone::Read() {
	string a, b, temp;
	fstream tooo(GetFileName().c_str(), ios::in);
	for (int i = 0; i < 1000 && getline(tooo, temp); i++, a = "", b = "") {
		stringstream stemp;
		stemp << temp;
		stemp >> a >> b; //读取行内容
		//空白数据“***”读取为空白字符串
		if (a == "***") a = "";
		if (b == "***") b = "";
		if (!get_judge(i)) {
			set_contact(i, a, b, "", "", true);
		}
	}
}
void BookPhone::Save() {
	fstream tooo(GetFileName().c_str(), ios::out);
	string a, b;
	for (int i = 0; i < 1000; i++) {
		if (get_judge(i)) {
			a = get_contact(i, 1);
			b = get_contact(i, 2);
			//空白数据记录为“***”
			if (a == "") a = "***";
			if (b == "") b = "***";
			tooo << a << " " << b << endl;
		}
	}
}

//定义储存卡电话本类
class BookCard :public book {
public:
	BookCard() { set_weizhi(true); }
	void Read();
	void Save();
};
void BookCard::Read() {
	string a, b, c, d, temp;
	fstream tooo(GetFileName().c_str(), ios::in);
	for (int i = 0; i < 1000 && getline(tooo, temp); i++, a = "", b = "", c = "", d = "") {
		stringstream stemp;
		stemp << temp;
		stemp >> a >> b >> c >> d; //读取行内容
		//空白数据“***”读取为空白字符串
		if (a == "***") a = "";
		if (b == "***") b = "";
		if (c == "***") c = "";
		if (d == "***") d = "";
		if (!get_judge(i)) {
			set_contact(i, a, b, c, d, true);
		}
	}
}
void BookCard::Save() {
	fstream tooo(GetFileName().c_str(), ios::out);
	string a, b, c, d;
	for (int i = 0; i < 1000; i++) {
		if (get_judge(i)) {
			a = get_contact(i, 1);
			b = get_contact(i, 2);
			c = get_contact(i, 3);
			d = get_contact(i, 4);
			//空白数据记录为“***”
			if (a == "") a = "***";
			if (b == "") b = "***";
			if (c == "") c = "***";
			if (d == "") d = "***";
			tooo << a << " " << b << " " << c << " " << d << "\n";
		}
	}
}

//定义界面类
class Welcome {
private:
	book * p;
	BookPhone phone_in;
	BookCard phone_card;
	void Add(); //增
	void Del(); //删
	void Find(); //查
	void Revice(); //改
	void LookThough(); //浏览
	void Trans(); //转存
public:
	Welcome();
	~Welcome();
	int StartDisplay(); //欢迎界面
};
Welcome::Welcome() {
	//读联系人数据
	p = &phone_in;
	p->Read();
	p = &phone_card;
	p->Read();
}
Welcome::~Welcome() {
	//结束时自动保存
	p = &phone_in;
	p->Save();
	p = &phone_card;
	p->Save();
}
int Welcome::StartDisplay() { //欢迎界面
	while (true) {
		cout.setf(ios::left);
		cout << setw(46) << "*" << cout.fill('*') << "\n";
		cout.fill(' ');
		cout << setw(45) << "*" << "*\n";
		cout << setw(45) << "*　　　　　通讯录管理系统" << "*\n";
		cout << setw(45) << "*      请输入数字来进行有关操作：" << "*\n";
		cout << setw(45) << "*　　　1、 添加联系人" << "*\n";
		cout << setw(45) << "*　　　2、 删除联系人" << "*\n";
		cout << setw(45) << "*　　　3、 查找联系人" << "*\n";
		cout << setw(45) << "*　　　4、 修改已经存在的联系人信息" << "*\n";
		cout << setw(45) << "*　　　5、 浏览已经存在的联系人信息" << "*\n";
		cout << setw(45) << "*　　　6、 联系人转存" << "*\n";
		cout << setw(45) << "*　　　9、 退出系统" << "*\n";
		cout << setw(45) << "*" << "*\n";
		cout << setw(46) << "*" << cout.fill('*') << endl;
		cout << "输入序号进行操作：";
		int num;
		cin >> num;
		switch (num) {
		case 1: //添加联系人
			Add(); break;
		case 2: //删除联系人
			Del(); break;
		case 3: //查找联系人
			Find(); break;
		case 4: //修改联系人
			Revice(); break;
		case 5: //浏览已存储联系人
			LookThough(); break;
		case 6: //联系人转存
			Trans(); break;
		case 9: //退出系统
			return 0;
		default:
			cout << "错误！请输入正确的号码！\n";
		}
		system("pause");
		system("cls");
	}
}
void Welcome::Add() {
	int num;
	char name;
	while (true) {
		cout << "请选择存储位置：\n1、手机\t2、储存卡\n";
		cin >> num;
		if (num == 1) {
			phone_in.add_person();
		}
		else if (num == 2) {
			phone_card.add_person();
		}
		else {
			cout << "错误！请输入正确的号码：\n";
		}
		p = &phone_in;
		p->Save();
		p->Read();
		p = &phone_card;
		p->Save();
		p->Read();
		cout << "是否添加其他联系人？（Y/N）";
		cin >> name;
		if (name == 'N' || name == 'n')
			break;
	}
}
void Welcome::Del() {
	string name;
	int num;
	while (true) {
		cout << "请输入联系人名字/电话号/QQ号/地址：\n";
		cin >> name;
		while (true) {
			cout << "姓名\t电话号\tQQ号\t地址\t位置\t序号\n";
			phone_in.find_person(name);
			phone_card.find_person(name);
			cout << "请输入你想删除的联系人所在存储位置\n（1.手机，2.储存卡，3，全部删除，9.结束）：";
			cin >> num;
			if (num == 1) {
				cout << "请输入你想删除的联系人序号：";
				cin >> num;
				phone_in.delete_person(num);
				cout << "删除成功！\n";
			}
			else if (num == 2) {
				cout << "请输入你想删除的联系人序号：";
				cin >> num;
				phone_card.delete_person(num);
				cout << "删除成功！\n";
			}
			else if (num == 3) {
				phone_in.find_person(name, true);
				phone_card.find_person(name, true);
				cout << "删除成功！\n";
			}
			else if (num == 9)
				break;
			else
				cout << "请输入正确的序号！\n";
			system("cls");
		}
		p = &phone_in;
		p->Save();
		p->Read();
		p = &phone_card;
		p->Save();
		p->Read();
		cout << "是否还要删除其他联系人？(Y/N)";
		cin >> name;
		if (name == "n" || name == "N")break;
	}
}
void Welcome::Find() {
	string name;
	while (true) {
		cout << "请输入被查找姓名：\n";
		cin >> name;
		cout << "姓名\t电话号\tQQ号\t地址\t位置\t序号\n";
		phone_in.find_person(name);
		phone_card.find_person(name);
		cout << "你想查找其他联系人吗？(Y/N)\n";
		cin >> name;
		if (name == "N" || name == "n")
			break;
	}
}
void Welcome::Revice() {
	string name;
	int num1, num2;
	while (true) {
		cout << "请输入联系人姓名：";
		cin >> name;
		cout << "姓名\t电话号\tQQ号\t地址\t位置\t序号\n";
		phone_in.find_person(name);
		phone_card.find_person(name);
		cout << "请输入联系人位置：\n1.手机\t2.存储卡" << endl;
		cin >> num1;
		cout << "请输入联系人序号：";
		cin >> num2;
		if (num2 == 1) {
			phone_in.revise_person(num2);
		}
		if (num2 == 2) {
			phone_in.revise_person(num2);
		}
		cout << "是否还要修改其他联系人？(Y/N)";
		cin >> name;
		if (name == "n" || name == "N") {
			p = &phone_in;
			p->Save();
			p->Read();
			p = &phone_card;
			p->Save();
			p->Read();
			break;
		}
	}
}
void Welcome::LookThough() {
	cout << "姓名\t电话号\tQQ号\t地址\t位置\t序号\n";
	cout << phone_in;
	cout << phone_card;
}
void Welcome::Trans() {
	int num;
	cout << "1.手机转存到储存卡\n2.储存卡转存到手机\n请输入序号：";
	cin >> num;
	if (num == 1) {
		phone_card += phone_in;
	}
	else if (num == 2) {
		phone_in += phone_card;
	}
	else{
		cout << "输入错误！请输入正确的序号！\n";
		return;
	}
	cout << "转存成功！\n";
	p = &phone_in;
	p->Save();
	p->Read();
	p = &phone_card;
	p->Save();
	p->Read();
}


int main() {
	Welcome Display;
	return Display.StartDisplay();
}
