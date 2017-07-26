/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghavenga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 20:09:25 by ghavenga          #+#    #+#             */
/*   Updated: 2017/05/26 20:09:42 by ghavenga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define  LOGGER_GLOBAL
#include "../includes/Logger.hpp"

//Constructors

Logger::Logger(std::string filename, int verbosity)
{
	_log_lock         = PTHREAD_MUTEX_INITIALIZER;
	this->_logfile    = new std::ofstream(filename, std::ofstream::out | std::ofstream::app);
	this->_verbosity  = verbosity;
	this->_depth      = 0;
	this->_buffer     = "";
	this->_printCount = 0;
	// if (this->_verbosity >= CRITICAL)
		*this->_logfile << std::endl << std::endl << "<----- |Logger|-----> Instantiated" << std::endl;
}

Logger::Logger(const Logger &obj)
{
	this->_logfile    = obj._logfile;
	this->_verbosity  = obj._verbosity;
	this->_depth      = obj._depth;
	this->_buffer     = obj._buffer;
	this->_printCount = obj._printCount;
}

Logger::~Logger()
{
	// if (this->_verbosity >= CRITICAL)
		*this->_logfile << "<----- |Logger|<----- Deconstructed" << std::endl;
	delete this->_logfile;
}

Logger &Logger::operator =(const Logger &obj)
{
	this->_logfile    = obj._logfile;
	this->_verbosity  = obj._verbosity;
	this->_depth      = obj._depth;
	this->_buffer     = obj._buffer;
	this->_printCount = obj._printCount;
	return *this;
}

// Setters
void Logger::setVerbosity(int verbosity) { this->_verbosity = verbosity; }

// Methods
void Logger::step_in(){this->_depth++;}
void Logger::step_out(){this->_depth--;}

void Logger::log(std::string message, int verbosity)
{	
	if (verbosity > this->_verbosity) return;
	this->tracked_print(message);
}

void Logger::log_step_in(std::string message, int verbosity)
{	
	if (verbosity > this->_verbosity) return;
	this->_depth += 1;
	this->tracked_print(message);
}

void Logger::log_step_out(std::string message, int verbosity)
{	
	if (verbosity > this->_verbosity) return;
	this->tracked_print(message);
	this->_depth -= 1;
}

void Logger::log(std::string message, int depth_step, int verbosity)
{	
	if (verbosity > this->_verbosity) return;
	if (depth_step > 0) this->_depth += 1;
	this->tracked_print(message);
	if (depth_step < 0) this->_depth -= 1;
}

void Logger::die(std::string message, int verbosity)
{	
	if (verbosity > this->_verbosity) return;
	this->tracked_print(message);
	exit(1);
}

// Special Overloads
/*
void Logger::log(std::string message, Coord coord, int verbosity)
{	
	if (verbosity > this->_verbosity)
		return;
	pthread_mutex_lock(&this->_log_lock);
	int i = -1;
	while (++i < this->_depth + 1)
		*this->_logfile << "\t";
	*this->_logfile << message << "X:" << coord.getX() << " Y:" << coord.getY() << std::endl;
	pthread_mutex_unlock(&this->_log_lock);
}

void Logger::log(std::string message, Direction direction, int verbosity)
{	
	if (verbosity > this->_verbosity)
		return;
	pthread_mutex_lock(&this->_log_lock);
	int i = -1;
	while (++i < this->_depth + 1)
		*this->_logfile << "\t";
	*this->_logfile << message << " " << direction.getDirectionString() << std::endl;
	pthread_mutex_unlock(&this->_log_lock);
}
*/

void Logger::log_num(std::string message, int num, int verbosity)
{	
	if (verbosity > this->_verbosity)
		return;
	pthread_mutex_lock(&this->_log_lock);
	this->print_indent();
	*this->_logfile << message << num << std::endl;
	pthread_mutex_unlock(&this->_log_lock);
}

//Private
void Logger::tracked_print(std::string message)
{
	if (this->_buffer.compare(message) == 0)
		this->_printCount++;
	else
	{
		pthread_mutex_lock(&this->_log_lock);
		if (this->_printCount > 0)
		{
			this->print(" X" + std::to_string(this->_printCount + 1));
			this->printEndl();
		}
		else
			this->printEndl();

		this->print_indent();
		this->print(message);
		this->_printCount = 0;
		this->_buffer = message;
		this->_logfile->flush();
		pthread_mutex_unlock(&this->_log_lock);
	}
}

void Logger::print_indent()
{
	int i = -1;
	while (++i < (this->_depth - 1) % 10)
		*this->_logfile << "|\t";
		// *this->_logfile << std::to_string(i) << "|\t";
}

void Logger::print(std::string message)	{ *this->_logfile << message; }
void Logger::puts(std::string message) 	{ *this->_logfile << message << std::endl; }
void Logger::printEndl() 				{ *this->_logfile << std::endl; }
