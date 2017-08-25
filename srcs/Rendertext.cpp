#include "Rendertext.hpp" 

//Constructors
Rendertext::Rendertext(FT_Face face, FT_GlyphSlot g)
{
	Log log("Rendertext", "Constructor", CRITICAL);
	this->_face = face;
	this->_g = g;
}


Rendertext::Rendertext(const Rendertext &obj)
{
	Log log("Rendertext", "Copy Constructor", CRITICAL);
	this->_face = obj._face;
	this->_g = obj._g;
}

Rendertext::~Rendertext()
{
	Log log("Rendertext", "Deconstructor", CRITICAL);
}

Rendertext &Rendertext::operator =(const Rendertext &obj)
{ 
	Log log("Rendertext", "= Operator", CRITICAL);
	this->_face = obj._face;
	this->_g = obj._g;
	return *this; 
}

// Setters
void	Rendertext::setFace(FT_Face face) { this->_face = face; }
void	Rendertext::setG(FT_GlyphSlot g) { this->_g = g; }

// Getters
FT_Face	Rendertext::getFace() { return this->_face; }
FT_GlyphSlot	Rendertext::getG() { return this->_g; }

// Methods
void	Rendertext::init(std::string font, int size)
{
			FT_Library ft;
	
			if(FT_Init_FreeType(&ft)) {
				fprintf(stderr, "Could not init freetype library\n");
				return (1);
			}
	
			// example font: "FreeSans.ttf"
			if(FT_New_Face(ft, font.c_str(), 0, &face)) {
				fprintf(stderr, "Could not open font\n");
				return (1);
			}
	
			FT_Set_Pixel_Sizes(face, 0, size);
	
			GLuint tex;
			glActiveTexture(GL_TEXTURE0);
			glGenTextures(1, &tex);
			glBindTexture(GL_TEXTURE_2D, tex);
			glUniform1i(uniform_tex, 0);
	
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	
			GLuint vbo;
			glGenBuffers(1, &vbo);
			glEnableVertexAttribArray(attribute_coord);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glVertexAttribPointer(attribute_coord, 4, GL_FLOAT, GL_FALSE, 0, 0);
	
			g = face->glyph;
}

render	Rendertext::char*(float x, float y, float sx, float sy)
{
			const char	*s;
	
			float	x2, y2, w, h;
			GLfloat	box[4][4];
	
			for (s = text; *s; s++) {
				if (FT_Load_Char(face, *s, FT_LOAD_RENDER))
					continue ;
	
				glTexOmage2D(GL_TEXTURE_2D, 0, GL_RED, g->bitmap.width, g->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, g->bitmap.buffer);
	
				x2 = x + g->bitmap_lect * sx;
				y2 = -y - g->bitmap_top * sy;
				w = g->bitmap.width * sx;
				h = g->bitmap.rows * sy;
	
				box = {
					{x2		,	-y2,		0,		0},
					{x2 + w	,	-y2,		1,		0},
					{x2		,	-y2 - h,	0,		1},
					{x2 + w	,	-y2 - h,	1,		1},
				};
	
				GLBufferData(GL_ARRAY_BUFFER, sizeof(box), box, GL_DYNAMIC_DRAW);
				glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	
				x += (g->advance.x >> 6) * sx;
				y += (g->advance.y >> 6) * sy;
			}
}

