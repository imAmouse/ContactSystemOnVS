/*
 *         c++ �γ���� �������� ͨѶ¼ϵͳ
 *            start at 2018-05-05
 *     Designed By �ռ���Ϣ�����ּ���1�� ���ĺ�
 */

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;


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


class book {
private:
	bool weizhi; //falseΪ�绰�ڲ���trueΪ�洢���洢
public:
	person contact[1000]; //ÿ���绰���������Ϊ1000
	void set_weizhi(bool weizhi) { this->weizhi = weizhi; }
	bool get_weizhi() { return weizhi; } //����ֵfalseΪ�绰�ڲ���trueΪ�洢���洢
	void add_person();
	void delete_person(int num); //����Ҫɾ���ı��
	void revise_person(string name); //�޸�
	void find_person(string name); //��ѯ
	void look_though(); //���ȫ��
	void transfer(bool j); //ת�棺False:phone to card True:card to phone
	bool get_judge(int PhoneNum) { return contact[PhoneNum].get_judge(); }
	string GetFileName(); //��ȡ�ļ��洢λ�ã��ұ����޸Ĵ洢�ļ���
	virtual void Read() = 0;
	virtual void Save() = 0;
};
void book::add_person() {
	int num;
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
	bool judge;
	cout << "��������ϵ��������\n";
	cin >> temp;
	contact[num].set_name(temp);
	contact[num].set_judge(true);
	cout << "�Ƿ��¼�绰���룿(1/0)";
	cin >> judge;
	if (judge) {
		cout << "�����룺";
		cin >> temp;
		contact[num].set_num_phone(temp);
	}
	cout << "�Ƿ��¼QQ���룿(1/0)";
	cin >> judge;
	if (judge) {
		cout << "�����룺";
		cin >> temp;
		contact[num].set_num_qq(temp);
	}
	cout << "�Ƿ��¼��ϵ�˵�ַ��(1/0)";
	cin >> judge;
	if (judge) {
		cout << "�����룺";
		cin >> temp;
		contact[num].set_address(temp);
	}
	cout << "��ӳɹ���\n";
}
void book::delete_person(int num) {
	cin >> num;
	contact[num].set_judge(false);
	contact[num].set_name("");
	contact[num].set_num_phone("");
	contact[num].set_num_qq("");
	contact[num].set_num_phone("");
	cout << "ɾ���ɹ���\n";
}
void book::revise_person(string name) {

	cout << "�޸ĳɹ���\n";
}
void book::find_person(string name) {
	for (int i = 0; i < 1000; i++) {
		if (name == contact[i].get_name()) {
			cout << contact[i].get_name() << "\t" << contact[i].get_num_phone() << "\t" << contact[i].get_num_qq() << "\t"
				<< contact[i].get_address();
			if (!weizhi)
				cout << "\t�ֻ�" << "\t" << i << "\n";
			if (weizhi)
				cout << "\t���濨" << "\t" << i << "\n";
		}
	}
}
void book::look_though() {
	for (int i = 0; i < 1000; i++)
		if (contact[i].get_judge() == true) {
			cout << contact[i].get_name() << "\t" << contact[i].get_num_phone() << "\t" << contact[i].get_num_qq() << "\t"
				<< contact[i].get_address();
			if (!weizhi)
				cout << "\t�ֻ�" << "\t" << i << "\n";
			if (weizhi)
				cout << "\t���濨" << "\t" << i << "\n";
		}
}
string book::GetFileName() {
	if (!weizhi)
		return "PhoneIn.ini";
	else
		return "PhoneCard.ini";
}

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
	BookPhone phone_in;
	BookCard phone_card; //�����ֻ�ͨѶ¼ �����濨ͨѶ¼
	phone_in.Read();
	phone_card.Read();
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
		cout << setw(46) << "*" << cout.fill('*') << "\n";
		int num;
		string name;
		cout << "������Ž��в�����";
		cin >> num;
		switch (num) {
		case 1: //�����ϵ��
			while (true) {
				cout << "��ѡ��洢λ�ã�\n1���ֻ�\t2�����濨\n";
				cin >> num;
				if (num == 1) {
					phone_in.add_person();
					break;
				}
				else if (num == 2) {
					phone_card.add_person();
					break;
				}
				else {
					cout << "������������ȷ�ĺ��룺\n";
				}
			}break;
		case 2: //ɾ����ϵ��
			while (true) {
				cout << "��������ϵ��������\n";
				cin >> name;
				cout << "����\t�绰��\tQQ��\t��ַ\tλ��\t���\n";
				phone_in.find_person(name);
				phone_card.find_person(name);
				while (true) {
					cout << "����������ɾ������ϵ�˴洢λ��\n��1.�ֻ���2.���濨����";
					cin >> num;
					if (num == 1) {
						cout << "����������ɾ������ϵ����ţ�";
						cin >> num;
						phone_in.delete_person(num);
						break;
					}
					else if (num == 2) {
						cout << "����������ɾ������ϵ����ţ�";
						cin >> num;
						phone_card.delete_person(num);
						break;
					}
					else
						cout << "��������ȷ����ţ�\n";
				}
				cout << "�Ƿ�Ҫɾ��������ϵ�ˣ�(Y/N)";
				cin >> name;
				if (name == "n" || name == "N")break;
			}break;
		case 3: //������ϵ��
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
			}break;
		case 4: //�޸���ϵ��
			while (true) {
				cout << "��������ϵ��������";
				cin >> name;
				cout << "�Ƿ�Ҫ�޸�������ϵ�ˣ�(Y/N)";
				cin >> name;
				if (name == "n" || name == "N")break;
			}break;
		case 5: //����Ѵ洢��ϵ��
			cout << "����\t�绰��\tQQ��\t��ַ\tλ��\t���\n";
			phone_in.look_though();
			phone_card.look_though();
			break;
		case 6: //��ϵ��ת��

		case 9: //�˳�ϵͳ������
			phone_in.Save();
			phone_card.Save();
			return 0;
		default:
			cout << "������������ȷ�ĺ��룡\n";
		}
		system("pause");
		system("cls");
	}
}
