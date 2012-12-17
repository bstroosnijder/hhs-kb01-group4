#include "explode.h"

namespace engine
{
	std::vector<char*> explode(char argDelim, char* argContext)
	{
		std::vector<char*> exploded;
		std::string context (argContext);
		int pos = 0;

		while(pos < context.size())
		{
			int nPos = context.find(argDelim, pos);
			std::string value = context.substr(pos, (nPos - pos));

			char* writable = new char[value.size() + 1];
			std::copy(value.begin(), value.end(), writable);
			writable[value.size()] = '\0';

			exploded.push_back(writable);
			pos = (nPos + 1);
		}

		return exploded;
	}
}