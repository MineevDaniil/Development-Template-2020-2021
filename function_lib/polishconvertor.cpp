#include "polishconvertor.h"
#include "stack.h"

#define MAX_EXPRESSION 1024
#define DIGIT 1000

PolishConvertor::~PolishConvertor() {

}

PolishConvertor::PolishConvertor() {

}

char* PolishConvertor::ConvertToPolish(char* expression) {

	TStack operation_stack;

	char* result = new char[MAX_EXPRESSION];
	int result_size = 0;

	result[0] = '\0';

	char curr_symbol;

	bool prev_sybol_is_blank = false;

	for (int i=0;i<MAX_EXPRESSION-1; i++) {

		curr_symbol = expression[i];
		
		if (curr_symbol == '\0')
		{
			while (operation_stack.IsEmpty()!=1)
			{
				char operation = operation_stack.Get();

				if (operation != '(' && operation != '[') {

					result_size++;
					result[result_size - 1] = ' ';

					result_size++;
					result[result_size - 1] = operation;
				}
			}

			result[result_size] = '\0';

			return result;
		}

		if (operation_stack.IsEmpty()==1) {
			if (priority(curr_symbol)<DIGIT && curr_symbol!=')' && curr_symbol != ']') {
				operation_stack.Put(curr_symbol);
			}
			else {
				if (curr_symbol != ' ')
				{
					result_size++;
					result[result_size - 1] = curr_symbol;
					continue;
				}
			}
		}
		else {
			if (priority(curr_symbol) < DIGIT && operation_stack.IsEmpty()!=1) {
				char last_operation = operation_stack.Get();
				int priority_curr_operation = priority(curr_symbol);
				int priority_last_operation = priority(last_operation);

				if (priority_curr_operation <= priority_last_operation) {
					
					if (prev_sybol_is_blank != true)
					{
						result_size++;
						result[result_size - 1] = ' ';
					}

					bool direction_to_output = false;

					if (last_operation != '(' && last_operation != ')' && last_operation != '[')
					{
						result_size++;
						result[result_size - 1] = last_operation;
						direction_to_output = true;
					}

					if (last_operation != ']' && direction_to_output != true)
					{
						operation_stack.Put(last_operation);
						
					}

					if (curr_symbol != ')')
					{
						operation_stack.Put(curr_symbol);
					}

					continue;
				}
				else
				{
					if (prev_sybol_is_blank != true)
					{
						result_size++;
						result[result_size - 1] = ' ';
					}

					result_size++;
					result[result_size - 1] = last_operation;

					while (operation_stack.IsEmpty()!=1)
					{
						char operation = operation_stack.Get();

						if (operation != '(')
						{
							result_size++;
							result[result_size - 1] = ' ';

							result_size++;
							result[result_size - 1] = operation;
						}
					}

					if (curr_symbol != ')')operation_stack.Put(curr_symbol);
					continue;
				}
				
			}
			else {

				if (curr_symbol == ' ' && prev_sybol_is_blank == true) continue;

				result_size++;
				result[result_size - 1]=curr_symbol;

				if (curr_symbol == ' ') prev_sybol_is_blank = true;
				else  prev_sybol_is_blank = false;

				continue;
			}

		}

	}

	return result;

}

void PolishConvertor::AddVar(char variable, double value) {


}

double PolishConvertor::Calculate(char* polishrecord) {

	TStack master_stack;

	int polishrecord_size = strlen(polishrecord);

	char curr_symbol = polishrecord[0];

	for (int i = polishrecord_size-1; i >= 0; i--)
	{
		curr_symbol = polishrecord[i];
		master_stack.Put(curr_symbol);
	}

	double result = 0;
	char operands[MAX_EXPRESSION];
	operands[0] = '\0';
	int operands_size = 0;

	while (master_stack.IsEmpty() != 1)
	{
		curr_symbol = master_stack.Get();

		while (priority(curr_symbol) == DIGIT)
		{
			operands_size++;
			operands[operands_size - 1] = curr_symbol;
			if(master_stack.IsEmpty() != 1)curr_symbol = master_stack.Get();
			else
			{
				return result;
			}
		}

		if(operands[operands_size-1]==' ')operands[operands_size-1] = '\0';
		else operands[operands_size] = '\0';

		float operand1 = 0;
		float operand2 = 0;
		char blank[MAX_EXPRESSION];
		char result_string[MAX_EXPRESSION];

		if (curr_symbol == '+')
		{
			int err=sscanf(operands, "%f %f", &operand1, &operand2);
			if (err != 2)throw std::logic_error("Error expression format!");
			result = operand1 + operand2;
		}
		else if(curr_symbol=='-')
		{
			int err = sscanf(operands, "%f %f", &operand1, &operand2);
			if (err != 2)throw std::logic_error("Error expression format!");
			result = operand1 - operand2;
		}
		else if (curr_symbol == '/')
		{
			int err = sscanf(operands, "%f %f", &operand1, &operand2);
			if (err != 2)throw std::logic_error("Error expression format!");
			result = operand1 / operand2;
		}
		else if (curr_symbol == '*')
		{
			int err = sscanf(operands, "%f %f", &operand1, &operand2);
			if (err != 2)throw std::logic_error("Error expression format!");
			result = operand1 * operand2;
		}
		else if (curr_symbol == '^')
		{
			int err = sscanf(operands, "%f %f", &operand1, &operand2);
			if (err != 2)throw std::logic_error("Error expression format!");
			result = pow(operand1, operand2);
		}
		else if (curr_symbol == ']')
		{
			int err = sscanf(operands, "%f", &operand1);
			if (err != 1)throw std::logic_error("Error expression format!");
			result = abs(operand1);
		}
		else if (curr_symbol == '_')
		{
			int err = sscanf(operands, "%f", &operand1);
			if (err != 1)throw std::logic_error("Error expression format!");
			result = operand1*(-1);
		}

		sprintf(result_string, "%f", result);

		int res_sym_counter = strlen(result_string);

		for (int j = res_sym_counter-1; j >= 0; j--)
		{
			master_stack.Put(result_string[j]);
		}

		operands[0] = '\0';
		operands_size = 0;

	}

	return result;
}

int PolishConvertor::priority(char operation) {

	char priority_3[] = { '(',')','[', ']', '_' };
	char priority_2[] = { '^'};
	char priority_1[] = {'*','/'};
	char priority_0[] = { '+','-' };

	int priority3_size = 5;
	int priority2_size = 1;
	int priority1_size = 2;
	int priority0_size = 2;

	for (int i = 0; i < priority3_size; i++)
	{
		if (operation == priority_3[i]){
			return 3;
		}
	}

	for (int i = 0; i < priority2_size; i++)
	{
		if (operation == priority_2[i]) {
			return 2;
		}
	}

	for (int i = 0; i < priority1_size; i++)
	{
		if (operation == priority_1[i]) {
			return 1;
		}
	}

	for (int i = 0; i < priority0_size; i++)
	{
		if (operation == priority_0[i]) {
			return 0;
		}
	}

	return DIGIT;

}


