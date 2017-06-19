#include "Calculation.h"
#include "TestCalculation/TestCalculation.h"
/******************************************************************************************************
* У программы два режима:
*	Test Mode - прогоняет все тесты, которые прописаны в TestCalculation.h
*  	Обычный режим - просит ввести строку с арифметическим выражением, после 
*  	выдачи результата пользователю спрашивает о продолжнеии работы.
*
* Чтобы избавиться от зависимостей, не использовались фреймворки для написания юнит-тестов.
* В случае некорректного ввода, функция расчета (Calculation) выводит предупреждение об ошибке в консоль 
* и возвращает значение DBL_MAX.
* P.S. Деление на 0 дает бесконечность 
*
*******************************************************************************************************/
int main(int argc, char* argv[])
{
	string answer = "";

	for (;;)
	{	
		answer.clear();
		cout << "Enable Test Mode?(y/n):";
		getline(cin,answer);

		if (answer == "y")
			return RunAllTest();

		else if (answer == "n")
			break;

		else
			continue;
	}

	string expression = "";	 

	auto Continue = [&answer]()->bool
	{
		for(;;)
		{
			answer.clear();
			cout << "Continue? (Y/y/N/n): ";
			getline(cin,answer);

			if (isAnyOf(answer,"Y","y"))
				return true;

			else if(isAnyOf(answer,"N","n"))
				return false;

			else
				cout << "I don't understand you =( Please, try again.\n";
		}	
	};

	cout << "Good day!\n"
		 << "Let's calculation!\n";

	do
	{
		expression.clear();
		cout << "Enter expression: ";
		getline(cin,expression);
		
		double result = Calculation(expression);

		if (result != DBL_MAX)
			cout << result << endl;	

	} while(Continue());

	return 0;
} 