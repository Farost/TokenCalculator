
#include "../include/calculator.h"

int main()
{
	std::string line;
	
	line = "1.0 + 88.033";
	
	std::istringstream stream(line);
	
	//stream >> Calculator::get();
	if (!Calculator::get().calcExpression(stream)) {
		std::cout << "Error occurred while calculator operation\n" << std::endl;
		Calculator::get().printStacks();
	}
	else {
		std::cout << Calculator::get().getResult() << std::endl;
	}
	
	return 0;
}
