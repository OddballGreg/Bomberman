#pragma once

/**
 * Logging is accessed through macros so that it can be completely
 * omitted if deactivated.
 */

#define LOGERROR(MESSAGE) logger->append(loggererror, MESSAGE)

#define LOGINFO(MESSAGE) logger->append(loggerinfo, MESSAGE)

#if defined(DEBUG) || defined(_DEBUG) || !defined (NDEBUG)
#define LOGDEBUG(MESSAGE) logger->append(loggerdebug, MESSAGE)
#else
#define LOGDEBUG(MESSAGE)
#endif

#include <ostream>
#include <memory>

namespace gameEngine {

	std::string intToStr(const int number);

	/**
	 * @brief Possible logging levels.
	 */

	enum LogLevel {
		loggerinfo, loggerdebug, loggererror
	};

	/**
	 * @class Logger
	 * @brief The standard logging class for small3d.
	 */

	class Logger {
	private:
		std::ostream *logStream;
	public:

		/**
		 * @brief Constructor with stream for output.
		 *
		 * @param [in,out]	stream	The stream to which events will be logged.
		 */

		Logger(std::ostream &stream);

		Logger(const Logger &obj);

		/**
		 * @brief Overloaders
		 */
		Logger operator = (const Logger &obj);

		/**
		 * @brief Destructor.
		 */

		~Logger();

		/**
		 * @brief Appends a message to the logger.
		 *
		 * @param	level		The logging level (debug, info, etc).
		 * @param	message	The message.
		 */

		void append(const LogLevel level, const std::string message) const;
	};

	void initLogger();

	void initLogger(std::ostream &stream);

	void deleteLogger();
}

extern std::shared_ptr<gameEngine::Logger> logger;
