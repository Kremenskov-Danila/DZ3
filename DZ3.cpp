#include <iostream>
#include <stack>
using namespace std;

struct Leksema 
{
	char type;  
	double value;  
};

bool Maths(stack <Leksema>& Stack_n, stack <Leksema>& Stack_o, Leksema& item) {  
	double a, b, c;
	a = Stack_n.top().value;  
	Stack_n.pop();  
	switch (Stack_o.top().type) {   
	case '+': 
		b = Stack_n.top().value;
		Stack_n.pop();
		c = a + b;
		item.type = '0';
		item.value = c;
		Stack_n.push(item);  
		Stack_o.pop();
		break;

	case '-':
		b = Stack_n.top().value;
		Stack_n.pop();
		c = b - a;
		item.type = '0';
		item.value = c;
		Stack_n.push(item);
		Stack_o.pop();
		break;

	case '*':
		b = Stack_n.top().value;
		Stack_n.pop();
		c = a * b;
		item.type = '0';
		item.value = c;
		Stack_n.push(item);
		Stack_o.pop();
		break;

	case '/':
		b = Stack_n.top().value;
		if (a == 0) {
			cerr << "\nНа 0 делить нельзя!\n";
			return false;
		}
		else {
			Stack_n.pop();
			c = (b / a);
			item.type = '0';
			item.value = c;
			Stack_n.push(item);
			Stack_o.pop();
			break;
		}
	default:
		cerr << "\nОшибка!\n";
		return false;
		break;
	}
	return true;
}

int getRang(char Ch) {  
	if (Ch == '+' || Ch == '-')return 1;
	if (Ch == '*' || Ch == '/')return 2;
	else return 0;
}

int main()
{
	setlocale(LC_ALL, "rus");
	cout << "   Привет! Это программа - калькулятор!\n   Введи выраженние: ";
	char Ch; 
	double value;
	int k = 0, l = 0;
	bool flag = 1;  
	stack <Leksema> Stack_n;  
	stack <Leksema> Stack_o; 
	Leksema item;  
	while (1) {
		Ch = cin.peek();  
		if (Ch == '\n')break;  
		if (Ch == ' ') {  
			cin.ignore();
			continue;
		}
		if (Ch >= '0' && Ch <= '9' || Ch == '-' && flag == 1) {  
			cin >> value;
			item.type = '0';
			item.value = value;
			Stack_n.push(item); 
			flag = 0;
			continue;
		}
		if (Ch == '+' || Ch == '-' && flag == 0 || Ch == '*' || Ch == '/') {  
			if (Stack_o.size() == 0) { 
				item.type = Ch;
				item.value = 0;
				Stack_o.push(item);  
				cin.ignore();
				continue;
			}
			if (Stack_o.size() != 0 && getRang(Ch) > getRang(Stack_o.top().type)) {  
				item.type = Ch;
				item.value = 0;
				Stack_o.push(item);  
				cin.ignore();
				continue;
			}
			if (Stack_o.size() != 0 && getRang(Ch) <= getRang(Stack_o.top().type)) {  
				if (Maths(Stack_n, Stack_o, item) == false) {  
					system("pause");
					return 0;
				}
				continue;
			}
		}
		if (Ch == '(') {  
			k++;
			item.type = Ch;
			item.value = 0;
			Stack_o.push(item);  
			cin.ignore();
			continue;
		}
		if (Ch == ')') { 
			l++;
			while (Stack_o.top().type != '(') {
				if (Maths(Stack_n, Stack_o, item) == false) { 
					system("pause");
					return 0;
				}
				else continue; 	
			}
			Stack_o.pop();
			cin.ignore();
			continue;
		}
		else { 
			cout << "\nНеверно введено выражение!\n";
			system("pause");
			return 0;
		}
	}
	if (k > l) {
		cout << "Ошибка: Удалите " << k - l << " символов '('." << endl;
	}
	if (l > k) {
		cout << "Ошибка: Удалите " << k - l << " символов ')'." << endl;
	}
	else {
		while (Stack_o.size() != 0) { 
			if (Maths(Stack_n, Stack_o, item) == false) {  
				system("pause");
				return 0;
			}
			else continue; 
		}
		cout << "   Ответ: " << Stack_n.top().value << endl; 
		return 0;
	}
}
