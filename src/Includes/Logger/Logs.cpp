#include "Logs.h"

Logs::Logs() {}

Logs::~Logs()
{
	boost::log::core::get()->remove_all_sinks();
}

Logs* Logs::Instance()
{
	static Logs Instance;
	return &Instance;
}

void Logs::Initialize()
{
	boost::log::add_common_attributes();
	boost::log::register_simple_formatter_factory<boost::log::trivial::severity_level, char>("Severity");

	{
		boost::log::add_console_log(
			std::cout,
			boost::log::keywords::format = "[%ThreadID%] - [%Severity%] [%TimeStamp%]: %Message%",
			boost::log::keywords::filter = boost::log::trivial::severity >= boost::log::trivial::severity_level::trace
		);
	}

	{
		boost::log::add_file_log(
			boost::log::keywords::file_name = "Logs/DNAuthServerx64_%Y_%m_%d.log",
			boost::log::keywords::format = "[%ThreadID%] - [%Severity%] [%TimeStamp%]: %Message%",
			boost::log::keywords::filter = boost::log::trivial::severity >= boost::log::trivial::severity_level::trace
		)->locked_backend()->auto_flush(true);

		boost::log::add_common_attributes();
	}
}

void Logs::Write(SEVERITY_LEVEL level, const std::string& message)
{
	switch (level)
	{
	case SEVERITY_LEVEL::LOG_TRACE:
		BOOST_LOG_TRIVIAL(trace) << message;
		break;
	case SEVERITY_LEVEL::LOG_DEBUG:
		BOOST_LOG_TRIVIAL(debug) << message;
		break;
	case SEVERITY_LEVEL::LOG_INFO:
		BOOST_LOG_TRIVIAL(info) << message;
		break;
	case SEVERITY_LEVEL::LOG_WARNING:
		BOOST_LOG_TRIVIAL(warning) << message;
		break;
	case SEVERITY_LEVEL::LOG_ERROR:
		BOOST_LOG_TRIVIAL(error) << message;
		break;
	case SEVERITY_LEVEL::LOG_FATAL:
		BOOST_LOG_TRIVIAL(fatal) << message;
		break;
	}
}