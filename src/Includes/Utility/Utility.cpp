#include "Utility.h"

Utility* Utility::Instance()
{
	static Utility Instance;
	return &Instance;
}

bool Utility::FileExists(const std::string& file)
{
	return boost::filesystem::exists(file) && boost::filesystem::is_regular_file(file);
}

bool Utility::DirExists(const std::string& dir)
{
	return boost::filesystem::exists(dir) && boost::filesystem::is_directory(dir);
}