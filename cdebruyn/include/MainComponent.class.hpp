#ifndef MAIN_COMPONENT_H
# define MAIN_COMPONENT_H

# include <iostream>
# include <cstring>

# include "../environ/GLFW/GLFW.class.hpp"

class MainComponent {

protected:

public:

    MainComponent( void );
    ~MainComponent( void );

    MainComponent( MainComponent const & copy );
    MainComponent& operator=( MainComponent const & copy );

};

#endif
