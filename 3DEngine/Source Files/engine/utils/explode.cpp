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
		std::stringstream sStream (argContext);
		std::vector<std::string> exploded;

		std::string item;
		while(std::getline(sStream, item, argDelim))
		{
			exploded.push_back(item);
		}

		return exploded;
	}
}