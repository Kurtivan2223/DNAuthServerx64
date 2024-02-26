#ifndef UTILITY_H_
#define UTILITY_H_

#pragma once
#include <boost/filesystem.hpp>

using namespace boost::filesystem;

class Utility
{
public:
	static Utility* Instance();
	bool FileExists(const std::string& file);
	bool DirExists(const std::string& dir);
};

#define SUtils Utility::Instance()

#endif