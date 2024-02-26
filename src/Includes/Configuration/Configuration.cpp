#include "Configuration.h"
#include "../Logger/Logs.h"
#include "../Utility/Utility.h"

Configuration::Configuration() {}

Configuration::~Configuration()
{
    delete[] Auth.EmulatedIPAddress;
    delete[] Auth.VirtualIPAddress;
    delete[] DBInfo.Host;
    delete[] DBInfo.Username;
    delete[] DBInfo.Password;
    delete[] DBInfo.DBName;

    info = {};
    Auth = {};
    DBInfo = {};
}   

Configuration* Configuration::Instance()
{
    static Configuration Instance;

    return &Instance;
}

void Configuration::Initialize()
{
    std::string filename = "Config/DNAuthServer.ini";

    if (!SUtils->FileExists(filename))
    {
        WRITE_LOG(SEVERITY_LEVEL::LOG_FATAL, "Configuration File is missing!");
        exit(EXIT_FAILURE);
    }

    Parse(filename);

    if (info.Debug)
    {
        std::string temp;
        std::string temp_debug = info.Debug ? "true" : "false";

        WRITE_LOG(SEVERITY_LEVEL::LOG_DEBUG, "[INFO]");
        temp = "Version: " + std::to_string(info.Version) + " Nation: " + std::to_string(info.Nation) + " Debug: " + temp_debug;
        WRITE_LOG(SEVERITY_LEVEL::LOG_DEBUG, temp);
        

        WRITE_LOG(SEVERITY_LEVEL::LOG_DEBUG, "[CONNECTION]");
        temp = "EmulatedIP: [" + std::string(Auth.EmulatedIPAddress) + "] EmulatedPort: [" + std::to_string(Auth.EmulatedPort) + "] VirtualIP: [" + std::string(Auth.VirtualIPAddress) + "]  VirtualPort: [" + std::to_string(Auth.VirtualPort) + "]";
        WRITE_LOG(SEVERITY_LEVEL::LOG_DEBUG, temp);

        WRITE_LOG(SEVERITY_LEVEL::LOG_DEBUG, "[DATABASE]");
        temp = "DBHost: [" + std::string(DBInfo.Host) + "] DBPort: [" + std::to_string(DBInfo.Port) + "] DBName: [" + std::string(DBInfo.DBName) + "]";
        WRITE_LOG(SEVERITY_LEVEL::LOG_DEBUG, temp);
    }
}

void Configuration::Parse(const std::string& filename)
{
    try
    {
        boost::property_tree::ptree tree;
        boost::property_tree::read_ini(filename, tree);

        info.Version = tree.get<int>("Info.Version");
        info.Nation = tree.get<int>("Info.Nation");
        info.Debug = tree.get<bool>("Info.Debug");

        Auth.EmulatedPort = tree.get<int>("Connection.EmulatedPort");
        Auth.VirtualPort = tree.get<int>("Connection.VirtualPort");

        Auth.EmulatedIPAddress = new char[100];
        std::strcpy(Auth.EmulatedIPAddress, tree.get<std::string>("Connection.EmulatedIP").c_str());

        Auth.VirtualIPAddress = new char[100];
        std::strcpy(Auth.VirtualIPAddress, tree.get<std::string>("Connection.VirtualIP").c_str());

        DBInfo.SQLMAX = tree.get<int>("DB_DNMembership.SQLMax");

        DBInfo.Host = new char[100];
        std::strcpy(DBInfo.Host, tree.get<std::string>("DB_DNMembership.DBIP").c_str());

        DBInfo.Port = tree.get<int>("DB_DNMembership.DBPort");

        DBInfo.Username = new char[100];
        std::strcpy(DBInfo.Username, tree.get<std::string>("DB_DNMembership.DBID").c_str());

        DBInfo.Password = new char[100];
        std::strcpy(DBInfo.Password, tree.get<std::string>("DB_DNMembership.DBPassword").c_str());

        DBInfo.DBName = new char[100];
        std::strcpy(DBInfo.DBName, tree.get<std::string>("DB_DNMembership.DBName").c_str());

    } catch (const std::exception& error)
    {
        std::string temp = "Error: " + std::string(error.what());
        WRITE_LOG(SEVERITY_LEVEL::LOG_FATAL, temp);
        exit(EXIT_FAILURE);
    }
}