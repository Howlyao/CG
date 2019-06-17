#pragma once
#include "GlobalVariable.h"
#include <ft2build.h>
#include <map>
#include FT_FREETYPE_H

class TextRenderer {

	
public:
	struct Character {
		GLuint TextureID;   // ID handle of the glyph texture
		glm::ivec2 Size;    // Size of glyph
		glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
		GLuint Advance;    // Horizontal offset to advance to next glyph
	};


	std::map<GLchar, Character> Characters;
	
	unsigned int VAO, VBO;
	TextRenderer();
	void init();
	void RenderText(Shader &shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
	
private:
	
};
