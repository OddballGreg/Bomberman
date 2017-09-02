#ifndef TIME_H
# define TIME_H

# include <iostream>
# include <cstring>
# include <cstdio>

class Time {

protected:

public:

	Time( void );
	~Time( void );

	Time( Time const & copy );
	Time& operator=( Time const & copy );

	static long		getTime( void );
	static double	getDelta( void );
	static void		setDelta( double delta )

private:
	static double	delta;

};

#endif
