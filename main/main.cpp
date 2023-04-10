#include "token.hpp"

#include <config-file.hpp>
#include <iostream>

#ifdef WHEN_DEBUG_MODE
#	define DEBUG_UNUSED(x) (void) (x);
#endif

int main(int argc, char *argv[])
{
	DEBUG_UNUSED(argc);
	DEBUG_UNUSED(argv);

	std::cout << "programm  works correctly" << std::endl;
}