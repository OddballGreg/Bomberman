#ifndef RENDERTEXT_HPP
# define RENDERTEXT_HPP

# include <freetype.h>
# include FT_FREETYPE_H

class Rendertext
{
	public:
		// Constructors & Destructors
		Rendertext(FT_Face face, FT_GlyphSlot g);
		Rendertext(const Rendertext &obj);
		~Rendertext();

		// Operators Overloads
		Rendertext&		operator =(const Rendertext &obj);

		// Setters
		void	setFace(FT_Face face);
		void	setG(FT_GlyphSlot g);

		// Getters
		FT_Face	getFace();
		FT_GlyphSlot	getG();
		
		// Member Methods
		void	init(std::string font, int size);
		render	char*(float x, float y, float sx, float sy);

	private:
		FT_Face	_face;
		FT_GlyphSlot	_g;
};

#endif
