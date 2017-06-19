#pragma once 

#include <iostream>
#include <stack>
#include <cfloat>
#include <cmath>

using namespace std;

template<typename T, typename U>
bool isAnyOf(T&& t, U&& u)
{
	return (t == u);
}

template<typename T, typename U, typename... Ts>
bool isAnyOf(T&& t, U&& u, Ts&&... args)
{
	return (t == u) || isAnyOf(t, std::forward<Ts>(args)...);
}

//назначение приоритета операций: 
//унарные > бинарные(*, /) > бинарные (+, -)
int GetPriority (char operation)
{
	if(operation < 0)
		return 3;

	if (isAnyOf(operation,'+','-'))  
		return 1;

	else if (isAnyOf(operation,'/','*'))
		return 2;

	else 
		return -1;
}

//вычисление выражений
void ProcessCalculation(stack<double>& stResult, char operation)
{
	if (operation > 0)
	{
		double rigth_op = stResult.top(); 
		stResult.pop();
		double left_op = stResult.top();
		stResult.pop();

		switch (operation)
		{
			case '+':	 
				stResult.push(left_op + rigth_op); 
				break;

			case '-':	 
				stResult.push(left_op - rigth_op); 
				break;

			case '*':	 
				stResult.push(left_op * rigth_op); 
				break;

			case '/':	 
				stResult.push(left_op / rigth_op); 
				break;
		}
	}
	else 
	{		
		double left_op = stResult.top();
		stResult.pop();

		switch(-operation)
		{
			case '+': 
					stResult.push(left_op);
					break;

			case '-':
					stResult.push(-left_op);
					break;
		}
	}
}

double Calculation(string str)
{
	stack<double> stResult;
	stack<char> stOperation;
	bool op_unary = true;
	size_t open_bracket = 0;

	if (str == "")
	{
		cout << "Error Calculation(): invalid input! The expression can not be empty!" << endl;
		return DBL_MAX;
	}

	for (size_t i=0; i<str.length(); ++i)
	{
		if(str[i] != ' ') 
		{
			if(str[i] == '(')
			{
				stOperation.push(str[i]);
				op_unary = true;
				++open_bracket;
			}

			else if (str[i] == ')')
			{

				if (open_bracket == 0)
				{
					cout << "Error Calculation(): invalid input! Missed '(' !" << endl;
					return DBL_MAX;
				}

				while(stOperation.top() != '(')
				{	
					ProcessCalculation(stResult,stOperation.top());
					stOperation.pop();
				}
				--open_bracket;
				stOperation.pop();

				op_unary = false;
			} 

			else if (isAnyOf(str[i],'+','-','/','*'))
			{
				char curop = str[i];

				if(op_unary)
					curop = -curop;

				while(!stOperation.empty() && (curop>=0 && GetPriority(stOperation.top())>= GetPriority(str[i])
										   || (curop <0 && GetPriority(stOperation.top()) > GetPriority(curop))))
				{
					ProcessCalculation(stResult, stOperation.top());
					stOperation.pop();
				}

				stOperation.push(curop);
				op_unary = true;
			}

			else
			{
				string operand = "";

				if (!isdigit(str[i]))
				{
					cout << "Error Calculation(): invalid input! In the expression can not be letters!" << endl;
					return DBL_MAX;
				}

				while( isdigit(str[i]) || isAnyOf(str[i],',','.',' '))
				{ 
					if (str[i] == ' ')
					{
						i++;
						continue;
					}
					
					if (isAnyOf(str[i],',','.'))
					{
						if (operand.back() == '.')
						{
							cout<<"Error Calculation(): invalid input! In the expression can not be double point!"<<endl;
							return DBL_MAX;
						}
						else 
						{
							operand.push_back('.');
							i++;
						}
					}
					else 
						operand.push_back(str[i++]);
				}

				--i;
				stResult.push(atof(operand.c_str()));
				op_unary = false;
			}
		}
	
	}

	if (stResult.empty())
	{
		cout<<"Error Calculation(): invalid input! In the expression can be number!"<<endl;
		return DBL_MAX;
	}

	while(!stOperation.empty())
	{
		ProcessCalculation(stResult,stOperation.top());
		stOperation.pop();
	}
    
	double result = floor(stResult.top()*100 +0.5)/100;

	return result;
}