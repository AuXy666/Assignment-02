#include<iostream>
#include<string>
#include<string.h>
#include<stack>
#include <windows.h>


void setConsoleColor(WORD c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
using namespace std;

struct Node
{
	string data;
	Node* next;
};
class List
{
private:
	Node* head;
	int length;
public:
	List();
	bool IsFull() const;
	bool IsEmpty() const;
	int GetLength() const;
	void MakeEmpty();
	string ReadHead() const;
	void InsertAtHead(string value);
	string DeleteFromHead();
	void Display();
};

List::List()
{
	length = 0;
	head = NULL;
}


bool List::IsFull() const
{
	Node* temp;
	try {
		temp = new Node;
		delete temp;
		return false;
	}
	catch (bad_alloc exception)
	{
		return true;
	}
}

bool List::IsEmpty() const
{
	return (length == 0 || head == NULL);
}

void List::MakeEmpty()
{
	Node* temp;
	while (head != NULL)
	{
		temp = head;
		head = head->next;
		delete temp;
	}
	length = 0;
}

int List::GetLength() const
{
	return length;
}


string List::ReadHead() const
{
	string data = "";
	if (head != NULL)
	{
		data = head->data;
	}
	return data;
}


void List::InsertAtHead(string value)
{
	Node* newNode = new Node;
	newNode->data = value;
	newNode->next = head;

	head = newNode;
	length++;
}

string List::DeleteFromHead()
{
	string data = "";
	if (head != NULL)
	{
		Node* temp = head;
		head = temp->next;
		data = temp->data;
		delete temp;
		length--;
	}
	return data;
}


void List::Display()
{
	if (head != NULL)
	{
		Node* temp = head;
		while (temp != NULL)
		{
			cout << "| " << temp->data << " |";
			if (temp->next != NULL)
			{
				cout << " -> ";
			}
			temp = temp->next;
		}
		cout << endl;
	}
	else
	{
		cout << "List is Empty\r\n";
	}
}


class Stack
{
private:
	List list;
public:
	bool isFull() const;
	bool isEmpty() const;
	string top() const;
	void push(string value);
	string pop();
};

bool Stack::isFull() const
{
	return list.IsFull();
}
bool Stack::isEmpty() const
{
	return list.IsEmpty();
}
string Stack::top() const
{
	return list.ReadHead();
}
void Stack::push(string value)
{
	list.InsertAtHead(value);
}
string Stack::pop()
{
	return list.DeleteFromHead();
}

enum expressionType { prefix, infix, postfix };

class Expression
{
private:
	string expression;
	expressionType expression_type;

	int evaluatePrefix();
	int evaluateInfix();
	int evaluatePostfix();

	void prefixToInfix();
	void prefixToPostfix();
	void infixToPrefix();
	void infixToPostfix();
	void postfixToPrefix();
	void postfixToInfix();

	bool  isOperand(string ch) const
	{

		return ((ch >= "a" && ch <= "z") || (ch >= "A" && ch <= "Z"));
	}
	bool IsOperand(char x)
	{
		return (x >= 'a' && x <= 'z') ||
			(x >= 'A' && x <= 'Z');
	}
	bool isOperandDigit(char c)
	{

		return isdigit(c);
	}


	bool  isOperator(string ch) const
	{

		return (ch == "^" || ch == "*" || ch == "/" || ch == "+" || ch == "-");
	}
	bool IsOperator(char x)
	{
		switch (x) {
		case '+':
		case '-':
		case '/':
		case '*':
			return true;
		}
		return false;
	}

	int applyOp(int a, int b, char op) {
		switch (op) {
		case '+': return a + b;
		case '-': return a - b;
		case '*': return a * b;
		case '/': return a / b;
		}
	}
	int Precedence(char op) {
		if (op == '+' || op == '-')
			return 1;
		if (op == '*' || op == '/')
			return 2;
		return 0;
	}
	int precedence(string c)
	{
		if (c == "^")
			return 3;
		else if (c == "*" || c == "/")
			return 2;
		else if (c == "+" || c == "-")
			return 1;
		else
			return -1;
	}


public:
	Expression()
	{
		this->expression = "00000000000000000000000";
		this->expression_type = infix;
	}
	void setPrefix()
	{
		this->expression_type = prefix;
	}
	void setPostfix()
	{
		this->expression_type = postfix;
	}

	void convertExpression(expressionType convertTo)
	{
		if (this->expression_type == prefix)
		{
			switch (convertTo)
			{
			case infix:
				prefixToInfix();
				break;
			case postfix:
				prefixToPostfix();
				break;
			}
		}
		else if (this->expression_type == infix)
		{
			switch (convertTo)
			{
			case prefix:
				infixToPrefix();
				break;
			case postfix:
				infixToPostfix();
				break;
			}
		}
		else if (this->expression_type == postfix)
		{
			switch (convertTo)
			{
			case prefix:
				postfixToPrefix();
				break;
			case infix:
				postfixToInfix();
				break;
			}
		}
	}
	void evaluateExpression()
	{
		switch (this->expression_type)
		{
		case prefix:
			cout << "Evaluation of Prefix = " << evaluatePrefix() << endl;
			break;
		case infix:
			cout << "Evaluation of Infix = " << evaluateInfix() << endl;
			break;
		case postfix:
			cout << "Evaluation of Postfix = " << evaluatePostfix() << endl;
			break;
		}
	}
	void Display()
	{
		switch (this->expression_type)
		{
		case prefix:
			cout << "Prefix ";
			break;
		case infix:
			cout << "Infix ";
			break;
		case postfix:
			cout << "Postfix ";
			break;
		}
		cout << "Notation: " << this->expression << endl;
	}
	void setExpression(string expression)
	{
		this->expression = expression;
	}
};

void Expression::infixToPostfix()
{
	Stack stack;
	string postfixStr;
	if (this->expression_type == infix)
	{
		for (int i = 0; i < this->expression.length(); i++)
		{

			string ch(1, this->expression[i]);
			if (isOperand(ch))
			{
				postfixStr += ch;
			}

			else if (ch == "(")
			{
				stack.push(ch);
			}

			else if (ch == ")")
			{
				while (stack.top() != "(" && !stack.isEmpty())
				{
					string op = stack.pop();
					postfixStr += op;
				}
				if (stack.top() == "(")
				{
					stack.pop();
				}
			}

			else {
				while (!stack.isEmpty() && precedence(ch) <= precedence(stack.top()))
				{
					string op = stack.pop();
					postfixStr += op;
				}
				stack.push(ch);
			}
		}

		while (!stack.isEmpty())
		{
			string op = stack.pop();
			postfixStr += op;
		}

		this->expression = postfixStr;
		this->expression_type = postfix;
	}
	else
	{
		cout << "Sorry given expression is not in Infix notation." << endl;
	}
}
int Expression::evaluatePrefix()
{
	stack<int> s;

	for (int j = this->expression.size() - 1; j >= 0; j--) {


		if (isOperandDigit(this->expression[j]))
			s.push(this->expression[j] - '0');

		else {


			int o1 = s.top();
			s.pop();
			int o2 = s.top();
			s.pop();


			switch (this->expression[j]) {
			case '+':
				s.push(o1 + o2);
				break;
			case '-':
				s.push(o1 - o2);
				break;
			case '*':
				s.push(o1 * o2);
				break;
			case '/':
				s.push(o1 / o2);
				break;
			}
		}
	}

	return s.top();
}
int Expression::evaluatePostfix()
{

	stack<int>s;

	for (int i = 0; this->expression[i]; ++i)
	{

		if (isdigit(this->expression[i]))
			s.push(this->expression[i] - '0');

		else
		{
			int val1 = s.top();
			s.pop();
			int val2 = s.top();
			s.pop();
			switch (this->expression[i])
			{
			case '+':
				s.push(val2 + val1);
				break;
			case '-':
				s.push(val2 - val1);
				break;
			case '*':
				s.push(val2 * val1);
				break;
			case '/':
				s.push(val2 / val1);
				break;
			}
		}
	}
	return s.top();
}
int Expression::evaluateInfix()
{
	int i;


	stack <int> values;


	stack <char> ops;

	for (i = 0; i < this->expression.length(); i++) {


		if (this->expression[i] == ' ')
			continue;


		else if (this->expression[i] == '(') {
			ops.push(this->expression[i]);
		}


		else if (isdigit(this->expression[i])) {
			int val = 0;


			while (i < this->expression.length() &&
				isdigit(this->expression[i]))
			{
				val = (val * 10) + (this->expression[i] - '0');
				i++;
			}

			values.push(val);


			i--;
		}

		else if (this->expression[i] == ')')
		{
			while (!ops.empty() && ops.top() != '(')
			{
				int val2 = values.top();
				values.pop();

				int val1 = values.top();
				values.pop();

				char op = ops.top();
				ops.pop();

				values.push(applyOp(val1, val2, op));
			}


			if (!ops.empty())
				ops.pop();
		}


		else
		{

			while (!ops.empty() && Precedence(ops.top())
				>= Precedence(this->expression[i])) {
				int val2 = values.top();
				values.pop();

				int val1 = values.top();
				values.pop();

				char op = ops.top();
				ops.pop();

				values.push(applyOp(val1, val2, op));
			}


			ops.push(this->expression[i]);
		}
	}


	while (!ops.empty()) {
		int val2 = values.top();
		values.pop();

		int val1 = values.top();
		values.pop();

		char op = ops.top();
		ops.pop();

		values.push(applyOp(val1, val2, op));
	}


	return values.top();
}

void Expression::infixToPrefix()
{
	Stack operators_stack;
	Stack operands_stack;

	if (this->expression_type == infix)
	{
		for (int i = 0; i < this->expression.length(); i++)
		{

			string ch(1, this->expression[i]);

			if (ch == "(")
			{
				operators_stack.push(ch);
			}

			else if (ch == ")")
			{
				while (!operators_stack.isEmpty() && operators_stack.top() != "(")
				{

					string op1 = operands_stack.pop();


					string op2 = operands_stack.pop();


					string op = operators_stack.pop();

					string tmp = op + op2 + op1;
					operands_stack.push(tmp);
				}

				operators_stack.pop();
			}

			else if (!isOperator(ch)) {
				operands_stack.push(ch);
			}


			else {
				while (!operators_stack.isEmpty() && precedence(ch) <= precedence(operators_stack.top())) {

					string op1 = operands_stack.pop();
					string op2 = operands_stack.pop();
					string op = operators_stack.pop();

					string tmp = op + op2 + op1;
					operands_stack.push(tmp);
				}

				operators_stack.push(ch);
			}
		}

		while (!operators_stack.isEmpty()) {
			string op1 = operands_stack.pop();
			string op2 = operands_stack.pop();
			string op = operators_stack.pop();
			string tmp = op + op2 + op1;
			operands_stack.push(tmp);
		}

		this->expression = operands_stack.top();
		this->expression_type = prefix;
	}
	else
	{
		cout << "Sorry given expression is not in Infix notation." << endl;
	}
}
void Expression::prefixToInfix()
{

	Stack sTemp;

	int length = this->expression.size();

	for (int i = length - 1; i >= 0; i--) {


		if (IsOperator(this->expression[i]))
		{


			string op1 = sTemp.top();   sTemp.pop();
			string op2 = sTemp.top();   sTemp.pop();


			string temp = "(" + op1 + this->expression[i] + op2 + ")";


			sTemp.push(temp);
		}


		else {


			sTemp.push(string(1, this->expression[i]));
		}
	}
	this->expression = sTemp.top();
	this->expression_type = infix;


}
void Expression::prefixToPostfix()
{


	Stack sTemp;

	int length = this->expression.size();


	for (int i = length - 1; i >= 0; i--)
	{

		if (IsOperator(this->expression[i]))
		{

			string op1 = sTemp.top();
			sTemp.pop();
			string op2 = sTemp.top();
			sTemp.pop();


			string temp = op1 + op2 + this->expression[i];


			sTemp.push(temp);
		}


		else {


			sTemp.push(string(1, this->expression[i]));
		}
	}


	this->expression = sTemp.top();
	this->expression_type = postfix;
}
void Expression::postfixToPrefix()
{
	Stack s;

	int length = this->expression.size();


	for (int i = 0; i < length; i++) {


		if (IsOperator(this->expression[i])) {


			string op1 = s.top();
			s.pop();
			string op2 = s.top();
			s.pop();


			string temp = this->expression[i] + op2 + op1;


			s.push(temp);
		}


		else {


			s.push(string(1, this->expression[i]));
		}
	}
	this->expression = "";
	while (!s.isEmpty()) {
		this->expression += s.top();
		s.pop();
	}
	this->expression_type = prefix;
}
void Expression::postfixToInfix()
{
	Stack s;

	for (int i = 0; this->expression[i] != '\0'; i++)
	{

		if (IsOperand(this->expression[i]))
		{
			string op(1, this->expression[i]);
			s.push(op);
		}

		else
		{
			string op1 = s.top();
			s.pop();
			string op2 = s.top();
			s.pop();
			s.push("(" + op2 + this->expression[i] + op1 + ")");
		}
	}

	this->expression = s.top();
	this->expression_type = infix;
}

int main()
{
	Expression E1, E2;
	Expression E3, E4, E5, E6;
	Expression E7, E8, E9;

	string expression = "a+b*(c^d-e)^(f+g*h)-i"; //sample infix string to convert into a postfix string
	string expression2 = "(A-B/C)*(A/K-L)";		 // sample infix string to convert into a prefix string
	string expression3 = "*-A/BC-/AKL";			 //sample prefix string to convert into infix string
	string expression4 = "*-A/BC-/AKL";			 //sample prefix string to convert into postfix string
	string expression5 = "ABC/-AK/L-*";          //sample postfix string to convert into prefix string
	string expression6 = "ab*c+";                //sample postfix string to convert into infix string
	string expression7 = "+9*26";                //sample for prefix evaluation
	string expression8 = "231*+9-";				 //sample for postfix evaluation
	string expression9 = "100 * ( 2 + 12 )";	 //sample for infix evaluation


	cout << endl;
	setConsoleColor(FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
	cout << "Conversion from infix to postfix" << endl << endl;
	setConsoleColor(7);
	E1.setExpression(expression);
	E1.Display();
	E1.convertExpression(postfix);
	E1.Display();

	cout << endl;
	setConsoleColor(FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
	cout << "Conversion from infix to prefix" << endl << endl;
	setConsoleColor(7);
	E2.setExpression(expression2);
	E2.Display();
	E2.convertExpression(prefix);
	E2.Display();

	cout << endl;
	setConsoleColor(FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
	cout << "Conversion from prefix to infix" << endl << endl;
	setConsoleColor(7);
	E3.setPrefix();
	E3.setExpression(expression3);
	E3.Display();
	E3.convertExpression(infix);
	E3.Display();

	cout << endl;
	setConsoleColor(FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
	cout << "Conversion from prefix to postfix" << endl << endl;
	setConsoleColor(7);
	E4.setPrefix();
	E4.setExpression(expression4);
	E4.Display();
	E4.convertExpression(postfix);
	E4.Display();

	cout << endl;
	setConsoleColor(FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
	cout << "Conversion from postfix to prefix" << endl << endl;
	setConsoleColor(7);
	E5.setPostfix();
	E5.setExpression(expression5);
	E5.Display();
	E5.convertExpression(prefix);
	E5.Display();

	cout << endl;
	setConsoleColor(FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
	cout << "Conversion from postfix to infix" << endl << endl;
	setConsoleColor(7);
	E6.setPostfix();
	E6.setExpression(expression6);
	E6.Display();
	E6.convertExpression(infix);
	E6.Display();

	cout << endl;
	setConsoleColor(FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
	cout << "Prefix Evaluation";
	setConsoleColor(7);
	cout << endl << endl;
	E7.setPrefix();
	E7.setExpression(expression7);
	E7.Display();
	E7.evaluateExpression();

	cout << endl;
	setConsoleColor(FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
	cout << "Postfix Evaluation";
	setConsoleColor(7);
	cout << endl << endl;
	E8.setPostfix();
	E8.setExpression(expression8);
	E8.Display();
	E8.evaluateExpression();

	cout << endl;
	setConsoleColor(FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
	cout << "Infix Evaluation";
	setConsoleColor(7);
	cout << endl << endl;
	E9.setExpression(expression9);
	E9.Display();
	E9.evaluateExpression();
	return 0;
}
