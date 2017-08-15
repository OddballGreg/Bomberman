/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Log.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghavenga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 20:09:52 by ghavenga          #+#    #+#             */
/*   Updated: 2017/05/26 20:14:43 by ghavenga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOG_HPP
# define LOG_HPP

// # include "Direction.hpp"
// # include "Coord.hpp"
# include "Logger.hpp"

# define NONE			0
# define CRITICAL		1
# define IMPORTANT		2
# define AVERAGE		3
# define UNIMPORTANT	4
# define ALL			5

class Log
{
	public:
		// Constructors & Destructors
		Log(std::string class_name, std::string function_name, int verbosity);
		Log(const Log &obj);
		~Log();

		// Operators Overloads
		Log& operator =(const Log &obj);

		// Setters
		void setVerbosity(int verbosity);

		// Member Methods
		void log(std::string message, int verbosity);
		void log(std::string message, int depth_step, int verbosity);
		// void log(std::string message, Coord coord, int verbosity);
		// void log(std::string message, Direction direction, int verbosity);
		void log_step_in(std::string message, int verbosity);
		void log_step_out(std::string message, int verbosity);
		void die(std::string message, int verbosity);

	private:
		int			_verbosity;
		int			_calls;
		std::string	_class;
		std::string	_function;
};

#endif
