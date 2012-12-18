#include "..\..\..\Header Files\engine\utils\explode.h"

namespace engine
{
	/**
	 * Explodes a string based on the delimeter
	 * @param		char							The char to use as delimeter
	 * @param		std::string						The string to explode
	 * @return		std::vector<std::string>
	 */
	std::vector<std::string> explode(char argDelim, std::string argContext)
	{
		std::vector<std::string> exploded;
		int pos = 0;

		while(pos < argContext.size())
		{
			int nPos = argContext.find(argDelim, pos);
			std::string value = argContext.substr(pos, (nPos - pos));

			exploded.push_back(value);
			pos = (nPos + 1);
		}

		return exploded;
	}
}