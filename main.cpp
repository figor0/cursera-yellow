#include <iostream>
#include <vector>

int main()
{
	if (system("./test_cursera")){
		return 1;
		std::cerr << "test failed";
	}
	return 0;
}
