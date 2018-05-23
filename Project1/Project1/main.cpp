/*
 *         c++ 课程设计 ———— 通讯录系统
 *            start at 2018-05-05
 *     Designed By 空间信息与数字技术1班 官文豪
 */

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

//定义联系人类
class person {
private:
	string name, num_phone, num_qq, address;
	bool judge; //判断此数据是否有效，以便于增删、查找、浏览操作
public:
	person();
	void set_name(string name) { this->name = name; }
	void set_num_phone(string num_phone) { this->num_phone = num_phone; }
	void set_num_qq(string num_qq) { this->num_qq = num_qq; }
	void set_address(string address) { this->address = address; }
	void set_judge(bool judge) { this->judge = judge; }
	string get_name() { return name; }
	string get_num_phone() { return num_phone; }
	string get_num_qq() { return num_qq; }
	string get_address() { return address; }
	bool get_judge() { return judge; }
};
person::person() :judge(false) {}

//定义电话本基类
class book {
private:
	bool weizhi; //false为电话内部，true为存储卡存储
public:
	person contact[1000]; //每个电话本最大容量为1000
	void set_weizhi(bool weizhi) { this->weizhi = weizhi; }
	bool get_weizhi() { return weizhi; } //返回值false为电话内部，true为存储卡存储
	bool get_judge(int PhoneNum) { return contact[PhoneNum].get_judge(); }
	void add_person();
	void delete_person(int num); //传入要删除的编号
	void revise_person(string name); //修改
	void find_person(string name); //查询
	friend ostream& operator<<(ostream &cout, book &temp); //重载<<运算符，实现浏览功能
	book& operator+=(book &temp); //转存：BeTrans转存到当先对象，并返回*this
	string GetFileName(); //获取文件存储位置，且便于修改存储文件名
	virtual void Read() = 0;
	virtual void Save() = 0;
};
void book::add_person() {
	int num;
	//查找未被记录的项，若不存在，cout错误并返回
	for (num = 0; num < 1000; num++) {
		if (!contact[num].get_judge()) {
			break;
		}
		else if (num == 999) {
			cout << "此通讯录已满！\n";
			return;
		}
	}
	string temp;
	bool judge;
	cout << "请输入联系人姓名：\n";
	cin >> temp;
	contact[num].set_name(temp);
	contact[num].set_judge(true);
	cout << "是否记录电话号码？(1/0)";
	cin >> judge;
	if (judge) {
		cout << "请输入：";
		cin >> temp;
		contact[num].set_num_phone(temp);
	}
	cout << "是否记录QQ号码？(1/0)";
	cin >> judge;
	if (judge) {
		cout << "请输入：";
		cin >> temp;
		contact[num].set_num_qq(temp);
	}
	cout << "是否记录联系人地址？(1/0)";
	cin >> judge;
	if (judge) {
		cout << "请输入：";
		cin >> temp;
		contact[num].set_address(temp);
	}
	cout << "添加成功！\n";
}
void book::delete_person(int num) {
	contact[num].set_judge(false);
	contact[num].set_name("");
	contact[num].set_num_phone("");
	contact[num].set_num_qq("");
	contact[num].set_num_phone("");
	cout << "删除成功！\n";
}
void book::revise_person(string name) {

	cout << "修改成功！\n";
}
void book::find_person(string name) {
	//查询：根据名字查询联系人信息（查询结果不唯一）
	for (int i = 0; i < 1000; i++) {
		if (name == contact[i].get_name()) {
			cout << contact[i].get_name() << "\t" << contact[i].get_num_phone() << "\t" << contact[i].get_num_qq() << "\t"
				<< contact[i].get_address();
			if (!weizhi)
				cout << "\t手机" << "\t" << i << "\n";
			if (weizhi)
				cout << "\t储存卡" << "\t" << i << "\n";
		}
	}
}
ostream& operator<<(ostream &cout, book &temp) {
	for (int i = 0; i < 1000; i++)
		if (temp.contact[i].get_judge() == true) {
			cout << temp.contact[i].get_name() << "\t" << temp.contact[i].get_num_phone() << "\t" << temp.contact[i].get_num_qq() << "\t"
				<< temp.contact[i].get_address();
			if (!temp.get_weizhi())
				cout << "\t手机" << "\t" << i << "\n";
			else
				cout << "\t储存卡" << "\t" << i << "\n";
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
		if (BeTrans.contact[i].get_judge())
			BeTransNum++;
		if (!contact[i].get_judge())
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
		if (BeTrans.contact[i].get_judge()) {
			for (; i1 < 1000; i1++) {
				if (!contact[i1].get_judge()) {
					contact[i1].set_name(BeTrans.contact[i].get_name());
					contact[i1].set_address(BeTrans.contact[i].get_address());
					contact[i1].set_num_qq(BeTrans.contact[i].get_num_qq());
					contact[i1].set_num_phone(BeTrans.contact[i].get_num_phone());
					contact[i1].set_judge(true);
					break;
				}
			}
		}
	}
	return *this;
}
string book::GetFileName() {
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
	string a, b, c, d;
	fstream tooo(GetFileName().c_str(), ios::in);
	for (int i = 0; i<1000 && tooo >> a >> b >> c >> d; i++) {
		if (!contact[i].get_judge()) {
			contact[i].set_name(a);
			contact[i].set_num_phone(b);
			contact[i].set_num_qq(c);
			contact[i].set_address(d);
			contact[i].set_judge(true);
		}
	}
}
void BookPhone::Save() {
	fstream tooo(GetFileName().c_str(), ios::out);
	for (int i = 0; i < 1000; i++) {
		if (contact[i].get_judge()) {
			tooo << contact[i].get_name() << " " << contact[i].get_num_phone() << " " << contact[i].get_num_qq()
				<< " " << contact[i].get_address() << "\n";
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
	string a, b, c, d;
	fstream tooo(GetFileName().c_str(), ios::in);
	for (int i = 0; i<1000 && tooo >> a >> b >> c >> d; i++) {
		if (!contact[i].get_judge()) {
			contact[i].set_name(a);
			contact[i].set_num_phone(b);
			contact[i].set_num_qq(c);
			contact[i].set_address(d);
			contact[i].set_judge(true);
		}
	}
}
void BookCard::Save() {
	fstream tooo(GetFileName().c_str(), ios::out);
	for (int i = 0; i < 1000; i++) {
		if (contact[i].get_judge()) {
			tooo << contact[i].get_name() << " " << contact[i].get_num_phone() << " " << contact[i].get_num_qq()
				<< " " << contact[i].get_address() << "\n";
		}
	}
}


int main() {
	void StartDisplay();
	BookPhone phone_in;
	BookCard phone_card; //定义手机通讯录 、储存卡通讯录
	phone_in.Read();
	phone_card.Read();
	while (true) {
		StartDisplay(); //欢迎界面
		int num;
		string name;
		cin >> num;
		switch (num) {
		case 1: //添加联系人
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
				phone_in.Save();
				phone_card.Save();
				cout << "是否添加其他联系人？（Y/N）";
				cin >> name;
				if (name == "N" || name == "n")break;
			}break;
		case 2: //删除联系人
			while (true) {
				cout << "请输入联系人姓名：\n";
				cin >> name;
				cout << "姓名\t电话号\tQQ号\t地址\t位置\t序号\n";
				phone_in.find_person(name);
				phone_card.find_person(name);
				while (true) {
					cout << "请输入你想删除的联系人存储位置\n（1.手机，2.储存卡）：";
					cin >> num;
					if (num == 1) {
						cout << "请输入你想删除的联系人序号：";
						cin >> num;
						phone_in.delete_person(num);
						break;
					}
					else if (num == 2) {
						cout << "请输入你想删除的联系人序号：";
						cin >> num;
						phone_card.delete_person(num);
						break;
					}
					else
						cout << "请输入正确的序号！\n";
				}
				phone_in.Save();
				phone_card.Save();
				cout << "是否还要删除其他联系人？(Y/N)";
				cin >> name;
				if (name == "n" || name == "N")break;
			}break;
		case 3: //查找联系人
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
			}break;
		case 4: //修改联系人
			while (true) {
				cout << "请输入联系人姓名：";
				cin >> name;
				cout << "是否还要修改其他联系人？(Y/N)";
				cin >> name;
				phone_in.Save();
				phone_card.Save();
				if (name == "n" || name == "N")break;
			}
			break;
		case 5: //浏览已存储联系人
			cout << "姓名\t电话号\tQQ号\t地址\t位置\t序号\n";
			cout << phone_in;
			cout << phone_card;
			break;
		case 6: //联系人转存
			cout << "1.手机转存到储存卡\n2.储存卡转存到手机\n请输入序号：";
			cin >> num;
			if (num == 1) {
				phone_card += phone_in;
			}
			else if (num == 2) {
				phone_in += phone_card;
			}
			else
				cout << "输入错误！请输入正确的序号！\n";
			cout << "转存成功！\n";
			phone_in.Save();
			phone_card.Save();
			break;
		case 9: //退出系统
			return 0;
		default:
			cout << "错误！请输入正确的号码！\n";
		}
		system("pause");
		system("cls");
	}
}

void StartDisplay() { //欢迎界面
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
	cout << setw(46) << "*" << cout.fill('*') << "\n";
	cout << "输入序号进行操作：";
}