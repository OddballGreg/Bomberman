#include "SpriteBatch.hpp"
#include <algorithm>
#include <vector>

#include "Log.hpp"
#include "Logger.hpp"

gameEngine::SpriteBatch::SpriteBatch() : _vbo(0), _vao(0), _sortType(GlyphSortType::TEXTURE) {
// Log log("SpriteBatch", "SpriteBatch", CRITICAL);
}

gameEngine::SpriteBatch::~SpriteBatch() {
// Log log("SpriteBatch", "~SpriteBatch", CRITICAL);
}

gameEngine::RenderBatch::RenderBatch(GLuint Offset, GLuint NumVertices, GLuint Texture) {
    // Log log("SpriteBatch", "RenderBatch", CRITICAL);
    offset = Offset;
    numVertices = NumVertices;
    texture = Texture;
}

void gameEngine::SpriteBatch::init() {
    // Log log("SpriteBatch", "init", CRITICAL);
    createVertexArray();
}

void gameEngine::SpriteBatch::begin(GlyphSortType sortType) {
    // Log log("SpriteBatch", "begin", CRITICAL);
    _sortType = sortType;
    _renderBatches.clear();

    for (int i = 0; i < _glyphs.size(); i++) {
        delete _glyphs[i];
    }
    _glyphs.clear();
}

void gameEngine::SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Colour& colour) {
    // Log log("SpriteBatch", "draw", CRITICAL);
    Glyph* newGlyph = new Glyph;

    newGlyph->texture = texture;
    newGlyph->depth = depth;

    newGlyph->topLeft.colour = colour;
    newGlyph->topLeft.setPosition(destRect.x, destRect.y + destRect.w);
    newGlyph->topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

    newGlyph->bottomLeft.colour = colour;
    newGlyph->bottomLeft.setPosition(destRect.x, destRect.y);
    newGlyph->bottomLeft.setUV(uvRect.x, uvRect.y); 

    newGlyph->bottomRight.colour = colour;
    newGlyph->bottomRight.setPosition(destRect.x + destRect.z, destRect.y);
    newGlyph->bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y); 

    newGlyph->topRight.colour = colour;
    newGlyph->topRight.setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
    newGlyph->topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

    _glyphs.push_back(newGlyph);
}

void gameEngine::SpriteBatch::end() {
    // Log log("SpriteBatch", "end", CRITICAL);
    sortGlyphs();
    createRenderBatches();
}

void gameEngine::SpriteBatch::renderBatch(){
    // Log log("SpriteBatch", "renderBatch", CRITICAL);

    glBindVertexArray(_vao);

    for (int i = 0; i < _renderBatches.size(); i++) {
        glBindTexture(GL_TEXTURE_2D, _renderBatches[i].texture);

        glDrawArrays(GL_TRIANGLES, _renderBatches[i].offset, _renderBatches[i].numVertices);
    }
    glBindVertexArray(0);
}

void gameEngine::SpriteBatch::createRenderBatches() {
    // Log log("SpriteBatch", "createRenderBatches", CRITICAL);

    std::vector <Vertex> vertices;
    vertices.resize(_glyphs.size() * 6);

    if (_glyphs.empty())
        return;

    int offset = 0;
    int currentVertex = 0;

    _renderBatches.emplace_back(offset, 6, _glyphs[0]->texture);
    
    vertices[currentVertex++] = _glyphs[0]->topLeft;
    vertices[currentVertex++] = _glyphs[0]->bottomLeft;
    vertices[currentVertex++] = _glyphs[0]->bottomRight;
    vertices[currentVertex++] = _glyphs[0]->bottomRight;
    vertices[currentVertex++] = _glyphs[0]->topRight;
    vertices[currentVertex++] = _glyphs[0]->topLeft;
    offset += 6;

    for (int currentGlyph = 1; currentGlyph < _glyphs.size(); currentGlyph++) {
        if (_glyphs[currentGlyph]->texture != _glyphs[currentGlyph - 1]->texture)
            _renderBatches.emplace_back(offset, 6, _glyphs[0]->texture);
        else
            _renderBatches.back().numVertices += 6;
            
        vertices[currentVertex++] = _glyphs[currentGlyph]->topLeft;
        vertices[currentVertex++] = _glyphs[currentGlyph]->bottomLeft;
        vertices[currentVertex++] = _glyphs[currentGlyph]->bottomRight;
        vertices[currentVertex++] = _glyphs[currentGlyph]->bottomRight;
        vertices[currentVertex++] = _glyphs[currentGlyph]->topRight;
        vertices[currentVertex++] = _glyphs[currentGlyph]->topLeft;
        offset += 6;
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    // Orphan the buffer
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
    // upload the data
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void gameEngine::SpriteBatch::createVertexArray() {
    // Log log("SpriteBatch", "createVertexArray", CRITICAL);

    if (_vao == 0)
        glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);

    if (_vbo == 0)
        glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    // This is the position attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    
    // this is the colour attribute
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, colour));

    // this is the uv attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

    glBindVertexArray(0);
}

void gameEngine::SpriteBatch::sortGlyphs() {
    // Log log("SpriteBatch", "sortGlyphs", CRITICAL);
    switch (_sortType) {
        case GlyphSortType::BACK_TO_FRONT:
            std::stable_sort(_glyphs.begin(), _glyphs.end(), compareBackToFront);
            break ;
        case GlyphSortType::FRONT_TO_BACK:
            std::stable_sort(_glyphs.begin(), _glyphs.end(), compareFrontToBack);
            break ;
        case GlyphSortType::TEXTURE:
            std::stable_sort(_glyphs.begin(), _glyphs.end(), compareTexture);
            break ;
    }
    
}

bool gameEngine::SpriteBatch::compareFrontToBack(Glyph* a, Glyph* b) {
    // Log log("SpriteBatch", "compareFrontToBack", CRITICAL);
    return (a->depth < b->depth);
}

bool gameEngine::SpriteBatch::compareBackToFront(Glyph* a, Glyph* b) {
    // Log log("SpriteBatch", "compareBackToFront", CRITICAL);
    return (a->depth > b->depth);
}

bool gameEngine::SpriteBatch::compareTexture(Glyph* a, Glyph* b) {
    // Log log("SpriteBatch", "AcompareTexture", CRITICAL);
    return (a->texture < b->texture);
}

