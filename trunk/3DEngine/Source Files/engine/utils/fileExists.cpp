#include "..\..\..\Header Files\engine\utils\fileExists.h"

namespace engine
{
	/**
	 * Checks if the parameter filename exists
	 * @param		const std::string&		The filename to check
	 * @return		bool
	 */
	bool fileExists(const std::string& argFilename)
	{
		struct stat buf;
		if (stat(argFilename.c_str(), &buf) != -1)
		{
			return true;
		}
		return false;
	}
}