#pragma once

#include <switch.h>
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <memory>
#include <vector>
#include <string>

// Forward declarations
class Sprite;
class Texture;
class Shader;

struct Vertex {
    float x, y, z;    // Position
    float u, v;        // Texture coordinates
    float r, g, b, a;  // Color
};

struct RenderCommand {
    enum Type {
        DRAW_SPRITE,
        DRAW_TEXT,
        DRAW_LINE,
        DRAW_RECTANGLE
    };
    
    Type type;
    float x, y, z;
    float width, height;
    float r, g, b, a;
    std::string textureName;
    std::string text;
    float fontSize;
};

class Renderer {
public:
    Renderer();
    ~Renderer();
    
    // Initialization
    bool initialize();
    void shutdown();
    
    // Frame management
    void beginFrame();
    void endFrame();
    void clear(float r, float g, float b, float a);
    
    // Rendering commands
    void drawSprite(const std::string& textureName, float x, float y, float width, float height);
    void drawSprite(const std::string& textureName, float x, float y, float width, float height, float rotation);
    void drawText(const std::string& text, float x, float y, float fontSize, float r, float g, float b, float a);
    void drawRectangle(float x, float y, float width, float height, float r, float g, float b, float a);
    void drawLine(float x1, float y1, float x2, float y2, float r, float g, float b, float a, float thickness);
    
    // Texture management
    bool loadTexture(const std::string& name, const std::string& filename);
    void unloadTexture(const std::string& name);
    bool textureExists(const std::string& name) const;
    
    // Shader management
    bool loadShader(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);
    void useShader(const std::string& name);
    
    // Viewport and projection
    void setViewport(int x, int y, int width, int height);
    void setProjection(float left, float right, float bottom, float top, float near, float far);
    void setOrthographic(float left, float right, float bottom, float top, float near, float far);
    
    // Switch-specific
    void onOperationModeChanged(); // Called when docked/undocked
    void setDisplayMode(bool docked);
    
    // Utility
    void getDisplaySize(int& width, int& height) const;
    float getAspectRatio() const;
    
private:
    // EGL context
    EGLDisplay eglDisplay;
    EGLContext eglContext;
    EGLSurface eglSurface;
    
    // OpenGL state
    GLuint defaultShader;
    GLuint textShader;
    GLuint spriteShader;
    
    // Vertex buffers
    GLuint vertexBuffer;
    GLuint indexBuffer;
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    
    // Texture cache
    std::unordered_map<std::string, std::unique_ptr<Texture>> textures;
    
    // Shader cache
    std::unordered_map<std::string, std::unique_ptr<Shader>> shaders;
    
    // Render commands
    std::vector<RenderCommand> renderCommands;
    
    // Display state
    bool isDocked;
    int displayWidth;
    int displayHeight;
    
    // Private methods
    bool initializeEGL();
    bool initializeOpenGL();
    void cleanupEGL();
    void cleanupOpenGL();
    
    void setupVertexBuffer();
    void setupIndexBuffer();
    
    void executeRenderCommands();
    void flushRenderCommands();
    
    // Shader compilation
    GLuint compileShader(GLenum type, const std::string& source);
    GLuint createShaderProgram(const std::string& vertexSource, const std::string& fragmentSource);
    
    // Utility
    void checkGLError(const std::string& operation);
    std::string getGLErrorString(GLenum error);
};