#include <iostream>
#include <vector>
#include <stdio.h>
#include <string.h>
#include "tree.h"

using namespace std;

int main()
{
	try {
		Tree tree;
		tree.create();
	}
	catch (std::exception& e)
	{
	    std::cerr << "Exception catched : " << e.what() << std::endl;
	}
	return 0;
}
