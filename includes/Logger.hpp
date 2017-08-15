/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghavenga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 20:09:52 by ghavenga          #+#    #+#             */
/*   Updated: 2017/05/26 20:14:43 by ghavenga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGGER_HPP
# define LOGGER_HPP

# include <iostream>
# include <fstream>
# include <pthread.h>

// # include "Direction.hpp"
// # include "Coord.hpp"

# define NONE			0
# define CRITICAL		1
# define IMPORTANT		2
# define AVERAGE		3
# define UNIMPORTANT	4
# define ALL			5

class Logger
{
	public:
		// Constructors & Destructors
		Logger(std::string logfile, int verbosity);
		Logger(const Logger &obj);
		~Logger();

		// Operators Overloads
		Logger& operator =(const Logger &obj);

		// Setters
		void setVerbosity(int verbosity);

		// Member Methods
		void step_in();
		void step_out();
		void log(std::string message, int verbosity);
		void log(std::string message, int depth_step, int verbosity);
		// void log(std::string message, Coord coord, int verbosity);
		// void log(std::string message, Direction direction, int verbosity);
		void log_num(std::string message, int num, int verbosity);
		void log_step_in(std::string message, int verbosity);
		void log_step_out(std::string message, int verbosity);
		void die(std::string message, int verbosity);

	private:
		pthread_mutex_t _log_lock;
		int				_verbosity;
		int				_depth;
		std::string		_buffer;
		int				_printCount;
		std::ofstream*	_logfile;

		void	tracked_print(std::string message);
		void	print_indent();
		void	print(std::string message);
		void	puts(std::string message);
		void	printEndl();
};

# ifdef LOGGER_GLOBAL

Logger		logger("bomberman_log.txt", ALL);

# else

extern Logger	logger;

# endif

#endif
