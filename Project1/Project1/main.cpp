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
public:
	person contact[1000]; //ÿ���绰���������Ϊ1000
	void set_weizhi(bool weizhi) { this->weizhi = weizhi; }
	bool get_weizhi() { return weizhi; } //����ֵfalseΪ�绰�ڲ���trueΪ�洢���洢
	bool get_judge(int PhoneNum) { return contact[PhoneNum].get_judge(); }
	void add_person();
	void delete_person(int num); //����Ҫɾ���ı��
	void revise_person(string name); //�޸�
	void find_person(string name); //��ѯ
	friend ostream& operator<<(ostream &cout, book &temp); //����<<�������ʵ���������
	book& operator+=(book &temp); //ת�棺BeTransת�浽���ȶ��󣬲�����*this
	string GetFileName(); //��ȡ�ļ��洢λ�ã��ұ����޸Ĵ洢�ļ���
	virtual void Read() = 0;
	virtual void Save() = 0;
};
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
	//��ѯ���������ֲ�ѯ��ϵ����Ϣ����ѯ�����Ψһ��
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
ostream& operator<<(ostream &cout, book &temp) {
	for (int i = 0; i < 1000; i++)
		if (temp.contact[i].get_judge() == true) {
			cout << temp.contact[i].get_name() << "\t" << temp.contact[i].get_num_phone() << "\t" << temp.contact[i].get_num_qq() << "\t"
				<< temp.contact[i].get_address();
			if (!temp.get_weizhi())
				cout << "\t�ֻ�" << "\t" << i << "\n";
			else
				cout << "\t���濨" << "\t" << i << "\n";
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

//�����ֻ��绰����
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

//���崢�濨�绰����
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
	BookCard phone_card; //�����ֻ�ͨѶ¼ �����濨ͨѶ¼
	phone_in.Read();
	phone_card.Read();
	while (true) {
		StartDisplay(); //��ӭ����
		int num;
		string name;
		cin >> num;
		switch (num) {
		case 1: //�����ϵ��
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
				phone_in.Save();
				phone_card.Save();
				cout << "�Ƿ����������ϵ�ˣ���Y/N��";
				cin >> name;
				if (name == "N" || name == "n")break;
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
				phone_in.Save();
				phone_card.Save();
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
				phone_in.Save();
				phone_card.Save();
				if (name == "n" || name == "N")break;
			}
			break;
		case 5: //����Ѵ洢��ϵ��
			cout << "����\t�绰��\tQQ��\t��ַ\tλ��\t���\n";
			cout << phone_in;
			cout << phone_card;
			break;
		case 6: //��ϵ��ת��
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
			phone_in.Save();
			phone_card.Save();
			break;
		case 9: //�˳�ϵͳ
			return 0;
		default:
			cout << "������������ȷ�ĺ��룡\n";
		}
		system("pause");
		system("cls");
	}
}

void StartDisplay() { //��ӭ����
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
	cout << "������Ž��в�����";
}