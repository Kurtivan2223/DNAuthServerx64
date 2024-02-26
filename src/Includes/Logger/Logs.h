#ifndef LOGS_H_
#define LOGS_H_

#pragma once
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/attributes/mutable_constant.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/sources/severity_channel_logger.hpp>
#include <boost/log/attributes/named_scope.hpp>
#include <boost/log/attributes/current_thread_id.hpp>

enum SEVERITY_LEVEL {
	LOG_TRACE,
	LOG_DEBUG,
	LOG_INFO,
	LOG_WARNING,
	LOG_ERROR,
	LOG_FATAL
};

class Logs
{
public:
	static Logs* Instance();
	void Initialize();
	void Write(SEVERITY_LEVEL level, const std::string& message);
private:
	Logs();
	~Logs();
};

#define SLog Logs::Instance()

#define LOG_MESSAGE_BODY(__SEVERITY__, __MESSAGE__) \
	do { \
		SLog->Write(__SEVERITY__, __MESSAGE__); \
	} while (0)

#define WRITE_LOG(__SEVERITY__, __MESSAGE__) \
	LOG_MESSAGE_BODY(__SEVERITY__, __MESSAGE__)

#endif