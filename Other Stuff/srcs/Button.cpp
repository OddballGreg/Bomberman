#include "../includes/Button.hpp"

/*
** Constructors and Destructors
*/
Button::Button(int x, int y, int w, int h, std::string title,
		SDL_Color background_colour, SDL_Color text_colour) :
	_x(x),
	_y(y),
	_w(w),
	_h(h),
	_selected(false),
	_title(title),
	_bg_colour(background_colour),
	_text_colour(text_colour) {}

Button::Button(const Button &obj) :
	_x(obj._x),
	_y(obj._y),
	_w(obj._w),
	_h(obj._h),
	_selected(obj._selected),
	_title(obj._title),
	_bg_colour(obj._bg_colour),
	_text_colour(obj._text_colour) {}

Button::~Button(void) {}

/*
** Setters
*/
void			Button::setX(int x) { _x = x; }
void			Button::setY(int y) { _y = y; }
void			Button::setW(unsigned int w) { _w = w; }
void			Button::setH(unsigned int h) { _h = h; }
void			Button::setSelected(bool s) { _selected = s; }
void			Button::setTitle(std::string title) { _title = title; }
void			Button::setBackgroundColour(SDL_Color bg_colour) { _bg_colour = bg_colour; }
void			Button::setTextColour(SDL_Color text_colour) { _text_colour = text_colour; }

/*
** Getters
*/
int				Button::getX(void) { return (_x); }
int				Button::getY(void) { return (_y); }
unsigned int	Button::getW(void) { return (_w); }
unsigned int	Button::getH(void) { return (_h); }
std::string		Button::getTitle(void) { return (_title); }
SDL_Color		Button::getBackgroundColour(void) { return (_bg_colour); }
SDL_Color		Button::getTextColour(void) { return (_text_colour); }

/*
** Memeber Methods
*/
bool			Button::isMouseOver(void) {
	int		x, y;

	// SDL_PumpEvents();
	SDL_GetMouseState(&x, &y);

	return (0 <= x && x < _x && 0 <= y && y < _y);
}

bool			Button::isMouseOver(int x, int y) {
	return (0 <= x && x < _x && 0 <= y && y < _y);
}

void			Button::draw(SDL_Renderer *renderer) {
	SDL_Rect	rect;

	rect.x = _x;
	rect.y = _y;
	rect.w = _w;
	rect.h = _h;

	SDL_RenderDrawRect(renderer, &rect);

	rect.w *= 0.9;
	rect.h *= 0.9;
	rect.x -= 0.05 * _w;
	rect.y -= 0.05 * _h;
}
