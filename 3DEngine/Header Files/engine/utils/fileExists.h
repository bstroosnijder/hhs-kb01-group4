#ifndef FILEEXISTS_H_
#define FILEEXISTS_H_

#include <string>
#include <sys/stat.h>

namespace engine
{
	bool fileExists(const std::string& argFilename);
}

#endif