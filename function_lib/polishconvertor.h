#include "stack.h"
class PolishConvertor {
private:
	int priority(char operation);

public:
	~PolishConvertor();
	PolishConvertor();
	char* ConvertToPolish(char* expression);
	void AddVar(char variable, double value);
	double Calculate(char* polishrecord);
};