#ifndef TIME_H
# define TIME_H

# include <iostream>
# include <cstring>
# include <cstdio>
# include <time.h>

class Time {

protected:
	double	_delta{0};

public:

	Time( void );
	~Time( void );

	Time( Time const & copy );
	Time& operator=( Time const & copy );

	const tm*		getTime( void );
	const double	getDelta( void );
	const void		setDelta( double delta );

private:
	time_t rawtime;
	struct tm * timeinfo;
};

#endif
