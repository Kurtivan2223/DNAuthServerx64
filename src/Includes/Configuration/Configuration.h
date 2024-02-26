#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <filesystem>

class Configuration
{
public:
	static Configuration* Instance();
	void Initialize();

	struct Info
	{
		int Version;
		int Nation;
		bool Debug;
	} info;

	struct DNAuthServer
	{
		int EmulatedPort;
		char* EmulatedIPAddress;
		int VirtualPort;
		char* VirtualIPAddress;
	} Auth;

	struct DatabaseInfo
	{
		int SQLMAX;
		char* Host;
		int Port;
		char* Username;
		char* Password;
		char* DBName;
	} DBInfo;

	void Parse(const std::string& filename);
private:
	Configuration();
	~Configuration();
};

#define SConfig Configuration::Instance()

#endif