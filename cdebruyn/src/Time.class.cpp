#define TIME_FILE
#include "../include/Time.class.hpp"

Time::Time( void ) {
	//
};

Time::~Time( void ) {
	//
};

Time::Time(Time const &copy) {
	*this = copy;
};

Time&		Time::operator=(Time const &copy) {
    if (this != &copy) {
        *this = copy;
    }
	return *this;
};

const tm*		Time::getTime( void ) {
	time (&rawtime);
	timeinfo = localtime (&rawtime);
	return (timeinfo);
};

const double	Time::getDelta( void ) {
	return _delta;
};

const void		Time::setDelta( double delta ) {
	this->_delta = delta;
};

