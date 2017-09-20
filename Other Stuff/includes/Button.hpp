#ifndef BUTTON_HPP
# define BUTTON_HPP

# include <SDL2/SDL.h>
# include <string>

class Button
{
	public:
		/* Constructors & Destructors */
		Button(int x, int y, int w, int h, std::string title,
			SDL_Color background_colour, SDL_Color text_colour);
		Button(const Button &obj);
		~Button();

		/* Operators Overloads */
		Button&			operator =(const Button &obj);

		/* Setters */
		void			setX(int x);
		void			setY(int y);
		void			setW(unsigned int w);
		void			setH(unsigned int h);
		void			setSelected(bool s);
		void			setTitle(std::string title);
		void			setBackgroundColour(SDL_Color bg_colour);
		void			setTextColour(SDL_Color text_colour);

		/* Getters */
		int				getX(void);
		int				getY(void);
		unsigned int	getW(void);
		unsigned int	getH(void);
		bool			getSelected(void);
		std::string		getTitle(void);
		SDL_Color		getBackgroundColour(void);
		SDL_Color		getTextColour(void);
		
		/* Member Methods */
		bool			isMouseOver(void);
		bool			isMouseOver(int x, int y);
		void			draw(SDL_Renderer *renderer);

	private:
		/* Variables */
		int				_x, _y;
		unsigned int	_w, _h;
		bool			_selected;
		std::string		_title;

		SDL_Color		_bg_colour;
		SDL_Color		_text_colour;

		/* Member Methods */
		
};

#endif
