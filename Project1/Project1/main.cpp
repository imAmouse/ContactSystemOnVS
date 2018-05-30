/*
 *         c++ �γ���� �������� ͨѶ¼ϵͳ
 *            start at 2018-05-05
 *     Designed By �ռ���Ϣ�����ּ���1�� ���ĺ�
 */

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <sstream>

using namespace std;

//������ϵ����
class person {
private:
	string name, num_phone, num_qq, address;
	bool judge; //�жϴ������Ƿ���Ч���Ա�����ɾ�����ҡ��������
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

//����绰������
class book {
private:
	bool weizhi; //falseΪ�绰�ڲ���trueΪ�洢���洢
	person contact[1000]; //ÿ���绰���������Ϊ1000
public:
	void set_weizhi(bool weizhi) { this->weizhi = weizhi; }
	void set_contact(int Num, string Name, string PhoneNum, string QQNum, string Address, bool Judge); //������ϵ����Ϣ
	string get_contact(int Num, int Choose); //��ȡ��ϵ����Ϣ��Choose����1.���� 2.�绰 3.QQ 4.��ַ
	bool get_weizhi() { return weizhi; } //����ֵfalseΪ�绰�ڲ���trueΪ�洢���洢
	bool get_judge(int Num) { return contact[Num].get_judge(); } //������ϵ�˿ռ��Ƿ�ռ��
	void add_person();
	void delete_person(int num); //����Ҫɾ���ı��
	void revise_person(int num); //�޸�
	void find_person(string name); //��ѯ
	friend ostream& operator<<(ostream &cout, book &temp); //����<<�������ʵ���������
	book& operator+=(book &temp); //ת�棺BeTransת�浽���ȶ��󣬲�����*��this��
	string GetFileName(); //��ȡ�ļ��洢λ�ã��ұ����޸Ĵ洢�ļ���
	virtual void Read() = 0;
	virtual void Save() = 0;
};
void book::set_contact(int Num, string Name, string PhoneNum, string QQNum, string Address, bool Judge) {
	contact[Num].set_judge(Judge);
	contact[Num].set_name(Name);
	contact[Num].set_num_phone(PhoneNum);
	contact[Num].set_num_qq(QQNum);
	contact[Num].set_address(Address);
}
string book::get_contact(int Num, int Choose) {
	switch (Choose) {
	case 1:return contact[Num].get_name();
	case 2:return contact[Num].get_num_phone();
	case 3:return contact[Num].get_num_qq();
	case 4:return contact[Num].get_address();
	default:return "";
	}
}
void book::add_person() {
	int num;
	//����δ����¼����������ڣ�cout���󲢷���
	for (num = 0; num < 1000; num++) {
		if (!contact[num].get_judge()) {
			break;
		}
		else if (num == 999) {
			cout << "��ͨѶ¼������\n";
			return;
		}
	}
	string temp;
	cout << "��������ϵ��������\n";
	cin >> temp;
	contact[num].set_name(temp);
	contact[num].set_judge(true);
	cout << "�Ƿ��¼�绰���룿(Y/N)";
	cin >> temp;
	if (temp == "Y" || temp == "y") {
		cout << "�����룺";
		cin >> temp;
		contact[num].set_num_phone(temp);
	}
	if (weizhi) { //�ж�λ�ã��ֻ�ֻ��¼�����͵绰��
		cout << "�Ƿ��¼QQ���룿(Y/N)";
		cin >> temp;
		if (temp == "Y" || temp == "y") {
			cout << "�����룺";
			cin >> temp;
			contact[num].set_num_qq(temp);
		}
		cout << "�Ƿ��¼��ϵ�˵�ַ��(Y/N)";
		cin >> temp;
		if (temp == "Y" || temp == "y") {
			cout << "�����룺";
			cin >> temp;
			contact[num].set_address(temp);
		}
	}
	cout << "��ӳɹ���\n";
}
void book::delete_person(int num) {
	contact[num].set_judge(false);
	contact[num].set_name("");
	contact[num].set_num_phone("");
	contact[num].set_num_qq("");
	contact[num].set_address("");
}
void book::revise_person(int num) {
	string temp;
	cout << "�Ƿ��޸���ϵ����������Y/N��";
	cin >> temp;
	if (temp == "Y" || temp == "y") {
		cout << "��������ϵ��������\n";
		cin >> temp;
		contact[num].set_name(temp);
	}
	cout << "�Ƿ��޸ĵ绰���룿(Y/N)";
	cin >> temp;
	if (temp == "Y" || temp == "y") {
		cout << "�����룺";
		cin >> temp;
		contact[num].set_num_phone(temp);
	}
	if (weizhi) { //�ж�λ�ã��ֻ�ֻ��¼�����͵绰��
		cout << "�Ƿ��޸�QQ���룿(Y/N)";
		cin >> temp;
		if (temp == "Y" || temp == "y") {
			cout << "�����룺";
			cin >> temp;
			contact[num].set_num_qq(temp);
		}
		cout << "�Ƿ��޸���ϵ�˵�ַ��(Y/N)";
		cin >> temp;
		if (temp == "Y" || temp == "y") {
			cout << "�����룺";
			cin >> temp;
			contact[num].set_address(temp);
		}
	}
	cout << "�޸ĳɹ���\n";
}
void book::find_person(string name) {
	/*��ѯ����������/�绰��/QQ��/��ַ��ѯ��ϵ����Ϣ����ѯ�����Ψһ��
	  ��ʹ��bool�����¼��������Ų�����
	*/
	for (int i = 0; i < 1000; i++) {
		if (get_contact(i, 1).find(name) != string::npos || get_contact(i, 2).find(name) != string::npos || get_contact(i, 3).find(name) != string::npos || get_contact(i, 4).find(name) != string::npos) {
			cout << get_contact(i, 1) << "\t" << contact[i].get_num_phone();
			if (!weizhi) //�ֻ�ֻ��¼���� �绰��QQ�͵�ַ���Ϊ��\\\\\\��
				cout << "\t\\\\\\\\\\\\\t\\\\\\\\\\\\\t�ֻ�" << "\t" << i << "\n";
			if (weizhi)
				cout << "\t" << contact[i].get_num_qq() << "\t" << contact[i].get_address() << "\t���濨" << "\t" << i << "\n";
		}
	}
}
ostream& operator<<(ostream &cout, book &temp) {
	for (int i = 0; i < 1000; i++)
		if (temp.contact[i].get_judge() == true) {
			cout << temp.get_contact(i, 1) << "\t" << temp.contact[i].get_num_phone();
			if (!temp.get_weizhi())
				cout << "\t" << "\\\\\\\\\\\\" << "\t" << "\\\\\\\\\\\\" << "\t�ֻ�" << "\t" << i << endl;
			else
				cout << "\t" << temp.contact[i].get_num_qq() << "\t" << temp.contact[i].get_address() << "\t���濨" << "\t" << i << endl;
		}
	return cout;
}
book& book::operator+=(book &BeTrans) {
	/*
	BeTransת�浽��ǰ���󣬲�����*this
	ע�������ظ����ݵĴ��ڡ�������ת����Ҫ��������Ƿ����ޡ�
	*/
	//�ֱ��¼ BeTransNum������ϵ���� �� TransToNum�ɼ�¼��ϵ����
	int BeTransNum = 0, TransToNum = 0;
	//���� BeTransNum������ϵ���� �� TransToNum�ɼ�¼��ϵ����
	for (int i = 0; i < 1000; i++) {
		if (BeTrans.contact[i].get_judge())
			BeTransNum++;
		if (!contact[i].get_judge())
			TransToNum++;
	}
	//��������Ƿ�����
	if (BeTransNum > TransToNum) {
		if (!BeTrans.get_weizhi())
			cout << "�ֻ�����������\n";
		else
			cout << "�洢������������\n";
		return *this;
	}
	//ת��
	for (int i = 0; i < 1000; i++) {
		int i1 = 0;
		if (BeTrans.contact[i].get_judge()) {
			for (; i1 < 1000; i1++) {
				if (!contact[i1].get_judge()) {
					contact[i1].set_name(BeTrans.get_contact(i, 1));
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

//�����ֻ��绰����
class BookPhone :public book {
public:
	BookPhone() { set_weizhi(false); }
	void Read();
	void Save();
};
void BookPhone::Read() {
	string a, b, c, d, temp;
	fstream tooo(GetFileName().c_str(), ios::in);
	for (int i = 0; i < 1000 && getline(tooo, temp); i++, a = "", b = "", c = "", d = "") {
		stringstream stemp;
		stemp << temp;
		stemp >> a >> b >> c >> d; //��ȡ������
		if (a == "***") a = "";
		if (b == "***") b = "";
		if (c == "***") c = "";
		if (d == "***") d = "";
		if (!get_judge(i)) {
			set_contact(i, a, b, c, d, true);
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
			if (a == "") a = "***";
			if (b == "") b = "***";
			tooo << a << " " << b << " *** ***\n";
		}
	}
}

//���崢�濨�绰����
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
		stemp >> a >> b >> c >> d; //��ȡ������
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
			if (a == "") a = "***";
			if (b == "") b = "***";
			if (c == "") c = "***";
			if (d == "") d = "***";
			tooo << a << " " << b << " " << c << " " << d << "\n";
		}
	}
}

//���������
class Welcome {
private:
	book * p;
	BookPhone phone_in;
	BookCard phone_card;
	void Add(); //��
	void Del(); //ɾ
	void Find(); //��
	void Revice(); //��
	void LookThough(); //���
	void Trans(); //ת��
public:
	Welcome();
	int StartDisplay(); //��ӭ����
};
Welcome::Welcome() {
	p = &phone_in;
	p->Read();
	p = &phone_card;
	p->Read(); //����ϵ������
}
int Welcome::StartDisplay() { //��ӭ����
	while (true) {
		cout.setf(ios::left);
		cout << setw(46) << "*" << cout.fill('*') << "\n";
		cout.fill(' ');
		cout << setw(45) << "*" << "*\n";
		cout << setw(45) << "*����������ͨѶ¼����ϵͳ" << "*\n";
		cout << setw(45) << "*      �����������������йز�����" << "*\n";
		cout << setw(45) << "*������1�� �����ϵ��" << "*\n";
		cout << setw(45) << "*������2�� ɾ����ϵ��" << "*\n";
		cout << setw(45) << "*������3�� ������ϵ��" << "*\n";
		cout << setw(45) << "*������4�� �޸��Ѿ����ڵ���ϵ����Ϣ" << "*\n";
		cout << setw(45) << "*������5�� ����Ѿ����ڵ���ϵ����Ϣ" << "*\n";
		cout << setw(45) << "*������6�� ��ϵ��ת��" << "*\n";
		cout << setw(45) << "*������9�� �˳�ϵͳ" << "*\n";
		cout << setw(45) << "*" << "*\n";
		cout << setw(46) << "*" << cout.fill('*') << endl;
		cout << "������Ž��в�����";
		int num;
		cin >> num;
		switch (num) {
		case 1: //�����ϵ��
			Add(); break;
		case 2: //ɾ����ϵ��
			Del(); break;
		case 3: //������ϵ��
			Find(); break;
		case 4: //�޸���ϵ��
			Revice(); break;
		case 5: //����Ѵ洢��ϵ��
			LookThough(); break;
		case 6: //��ϵ��ת��
			Trans(); break;
		case 9: //�˳�ϵͳ
			return 0;
		default:
			cout << "������������ȷ�ĺ��룡\n";
		}
		system("pause");
		system("cls");
	}
}
void Welcome::Add() {
	int num;
	char name;
	while (true) {
		cout << "��ѡ��洢λ�ã�\n1���ֻ�\t2�����濨\n";
		cin >> num;
		if (num == 1) {
			phone_in.add_person();
		}
		else if (num == 2) {
			phone_card.add_person();
		}
		else {
			cout << "������������ȷ�ĺ��룺\n";
		}
		p = &phone_in;
		p->Save();
		p->Read();
		p = &phone_card;
		p->Save();
		p->Read();
		cout << "�Ƿ����������ϵ�ˣ���Y/N��";
		cin >> name;
		if (name == 'N' || name == 'n')
			break;
	}
}
void Welcome::Del() {
	string name;
	int num;
	while (true) {
		cout << "��������ϵ������/�绰��/QQ��/��ַ��\n";
		cin >> name;
		while (true) {
			cout << "����\t�绰��\tQQ��\t��ַ\tλ��\t���\n";
			phone_in.find_person(name);
			phone_card.find_person(name);
			cout << "����������ɾ������ϵ�����ڴ洢λ��\n��1.�ֻ���2.���濨��9.��������";
			cin >> num;
			if (num == 1) {
				cout << "����������ɾ������ϵ����ţ�";
				cin >> num;
				phone_in.delete_person(num);
				cout << "ɾ���ɹ���\n";
			}
			else if (num == 2) {
				cout << "����������ɾ������ϵ����ţ�";
				cin >> num;
				phone_card.delete_person(num);
				cout << "ɾ���ɹ���\n";
			}
			else if (num == 9)
				break;
			else
				cout << "��������ȷ����ţ�\n";
			system("cls");
		}
		p = &phone_in;
		p->Save();
		p->Read();
		p = &phone_card;
		p->Save();
		p->Read();
		cout << "�Ƿ�Ҫɾ��������ϵ�ˣ�(Y/N)";
		cin >> name;
		if (name == "n" || name == "N")break;
	}
}
void Welcome::Find() {
	string name;
	while (true) {
		cout << "�����뱻����������\n";
		cin >> name;
		cout << "����\t�绰��\tQQ��\t��ַ\tλ��\t���\n";
		phone_in.find_person(name);
		phone_card.find_person(name);
		cout << "�������������ϵ����(Y/N)\n";
		cin >> name;
		if (name == "N" || name == "n")
			break;
	}
}
void Welcome::Revice() {
	string name;
	int num1, num2;
	while (true) {
		cout << "��������ϵ��������";
		cin >> name;
		cout << "����\t�绰��\tQQ��\t��ַ\tλ��\t���\n";
		phone_in.find_person(name);
		phone_card.find_person(name);
		cout << "��������ϵ��λ�ã�\n1.�ֻ�\t2.�洢��" << endl;
		cin >> num1;
		cout << "��������ϵ����ţ�";
		cin >> num2;
		if (num2 == 1) {
			phone_in.revise_person(num2);
		}
		if (num2 == 2) {
			phone_in.revise_person(num2);
		}
		cout << "�Ƿ�Ҫ�޸�������ϵ�ˣ�(Y/N)";
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
	cout << "����\t�绰��\tQQ��\t��ַ\tλ��\t���\n";
	cout << phone_in;
	cout << phone_card;
}
void Welcome::Trans() {
	int num;
	cout << "1.�ֻ�ת�浽���濨\n2.���濨ת�浽�ֻ�\n��������ţ�";
	cin >> num;
	if (num == 1) {
		phone_card += phone_in;
	}
	else if (num == 2) {
		phone_in += phone_card;
	}
	else
		cout << "���������������ȷ����ţ�\n";
	cout << "ת��ɹ���\n";
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


