#include "PlatformFlagger.h"
#ifdef RB_OPENGL

#include "OpenGLDriver.h"

#include <stdint.h>

#include <iostream>

#include "RenderInfo.h"
#include "TextureInfo.h"
#include "MathHelper.h"
#include "MainWindow.h"
using namespace RedBox;

GLuint OpenGLDriver::maskedFramebuffer = 0;
GLuint OpenGLDriver::maskedTexture = 0;
Sprite * OpenGLDriver::maskedSprite = NULL;
TextureInfo * OpenGLDriver::maskedTextureInfo = NULL;


void OpenGLDriver::drawShapeWithTextureAndColor(GLfloat* vertices,
                                                RenderInfo& renderingInfo,
                                                unsigned int nbVertices) {
	if(renderingInfo.getColor().getAlpha() > 0) {
		const uint8_t* color = renderingInfo.getColor().getComponents();
		
        glColor4ub(color[0], color[1], color[2], color[3]);
		drawShapeWithTexture(vertices, renderingInfo, nbVertices);
        glColor4ub(255, 255, 255, 255);
        
	}
}

void OpenGLDriver::drawShapeWithTexture(GLfloat* vertices,
                                        RenderInfo& renderingInfo,
                                        unsigned int nbVertices) {
	// We make sure there is a valid texture information.
	if(renderingInfo.getTexInfo()) {
		glBindTexture(GL_TEXTURE_2D, renderingInfo.getTexInfo()->textureId);
        
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
#ifdef RB_OPENGLES
		glBlendFuncSeparateOES(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ZERO, GL_ONE);
#else
		glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ZERO, GL_ONE);
#endif
        
		glVertexPointer(2, GL_FLOAT, 0, vertices);
		glEnableClientState(GL_VERTEX_ARRAY);
        
        
		glTexCoordPointer(2, GL_FLOAT, 0, reinterpret_cast<GLfloat*>(&(renderingInfo.getTexCoords()[renderingInfo.getCurrentFrame()][0])));
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        
		glDrawArrays(GL_TRIANGLE_FAN, 0, nbVertices);
        
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);
	} else {
		// We draw the shape without the texture.
		drawShapeWithColor(vertices, renderingInfo, nbVertices);
	}
}

void OpenGLDriver::drawShapeWithColor(GLfloat* vertices,
                                      RenderInfo& renderingInfo,
                                      unsigned int nbVertices) {
	if(renderingInfo.getColor().getAlpha() > 0) {
		const uint8_t* color = renderingInfo.getColor().getComponents();
        glColor4ub(color[0], color[1], color[2], color[3]);
        
        
		glVertexPointer(2, GL_FLOAT, 0, vertices);
		glEnable(GL_BLEND);
#ifdef RB_OPENGLES
		glBlendFuncSeparateOES(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ZERO, GL_ONE);
#else
		glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ZERO, GL_ONE);
#endif
		glEnableClientState(GL_VERTEX_ARRAY);
        
		glDrawArrays(GL_TRIANGLE_FAN, 0, nbVertices);
        
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisable(GL_BLEND);
        glColor4ub(255, 255, 255, 255);
        
	}
}

void OpenGLDriver::drawMaskShapeWithTextureAndColor(GLfloat* vertices,
                                                    RenderInfo& renderingInfo,
                                                    unsigned int nbVertices) {
    
	if(renderingInfo.getColor().getAlpha() > 0) {
		const uint8_t* color = renderingInfo.getColor().getComponents();
        
        glColor4ub(color[0], color[1], color[2], color[3]);
        
        
		drawMaskShapeWithTexture(vertices, renderingInfo, nbVertices);
        
        glColor4ub(255, 255, 255, 255);
        
	}
    
}

void OpenGLDriver::drawBatchWithTextureAndColor(const CArray<Vector2>& vertices, const CArray<Vector2>& textureCoord, 
                                                const CArray<unsigned short>& indices, const TextureInfo & textureInfo, const CArray<unsigned char>& colors, bool printAlpha){
    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(4, GL_UNSIGNED_BYTE, 0, colors.array);
    
    drawBatchWithTexture(vertices, textureCoord,indices, textureInfo, printAlpha);
    glDisableClientState(GL_COLOR_ARRAY);
    
}

void OpenGLDriver::drawBatchWithTexture(const CArray<Vector2>& vertices, const CArray<Vector2>& textureCoord, 
                                        const CArray<unsigned short> & indices, const TextureInfo & textureInfo, bool printAlpha){
    
    glBindTexture(GL_TEXTURE_2D, textureInfo.textureId);
    
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    if (printAlpha) {
        
#ifdef RB_OPENGLES
        glBlendEquationSeparateOES(GL_FUNC_ADD_OES, GL_MAX_EXT);
        glBlendFuncSeparateOES(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
#else
        glBlendEquationSeparate(GL_FUNC_ADD, GL_MAX);
        glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
#endif
    }
    else{
#ifdef RB_OPENGLES
        glBlendFuncSeparateOES(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ZERO, GL_ONE);
#else
        glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ZERO, GL_ONE);
#endif
    }
    
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    
    
    glVertexPointer(2, GL_FLOAT, 0, reinterpret_cast<float*>(vertices.array));
    glTexCoordPointer(2, GL_FLOAT, 0, reinterpret_cast<float*>(textureCoord.array));
    
    glDrawElements(GL_TRIANGLE_STRIP, indices.elementCount ,GL_UNSIGNED_SHORT, indices.array);
    if (printAlpha) {
#ifdef RB_OPENGLES
        glBlendEquationOES(GL_FUNC_ADD_OES);
#else
        glBlendEquation(GL_FUNC_ADD);
#endif
    }
    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    
}

void OpenGLDriver::drawMaskedBatchWithTextureAndColor(const CArray<Vector2>& vertices, const CArray<Vector2>& textureCoord, 
                                                      const CArray<unsigned short>& indices, const TextureInfo & textureInfo, const CArray<unsigned char>& colors, bool inversedMask){
    
#ifdef RB_OPENGLES
    glBindFramebufferOES(GL_FRAMEBUFFER_OES, maskedFramebuffer);
#else
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, maskedFramebuffer);
#endif
#ifdef RB_OPENGLES
    glFramebufferTexture2DOES(GL_FRAMEBUFFER_OES, GL_COLOR_ATTACHMENT0_OES,
                              GL_TEXTURE_2D, maskedTexture, 0);
#else
    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT,
                              GL_TEXTURE_2D, maskedTexture, 0);
#endif
    
    //We can't call glclearcolor on a texture binded framebuffer, so we draw quad to clear the texture
    glColor4ub(0, 0, 0, 255);
    glVertexPointer(2, GL_FLOAT, 0, reinterpret_cast<GLfloat*>( &(maskedSprite->getVertices()[0])));
    glEnableClientState(GL_VERTEX_ARRAY);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    drawBatchWithTextureAndColor(vertices, textureCoord, indices, textureInfo, colors, true);
    
    glBindFramebufferOES(GL_FRAMEBUFFER_OES, 1);
    
    glPushMatrix();
    glLoadIdentity();
    glScalef(1.0f, -1.0f, 1.0f);
    glTranslatef(0.0f, -480.0f, 0.0f);
    maskedSprite->maskedRender(inversedMask);
    glPopMatrix();
        
        
    }

void OpenGLDriver::drawMaskBatchWithTextureAndColor(const CArray<Vector2>& vertices, const CArray<Vector2>& textureCoord, 
                                                     const CArray<unsigned short>& indices, const TextureInfo & textureInfo, 
                                                     const CArray<unsigned char> & colors){
    
    
    glBindTexture(GL_TEXTURE_2D, textureInfo.textureId);
    
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    
#ifdef RB_OPENGLES
    glBlendFuncSeparateOES(GL_ZERO, GL_ONE, GL_ZERO, GL_SRC_ALPHA);
#else
    glBlendFuncSeparate(GL_ZERO, GL_ONE, GL_ZERO, GL_SRC_ALPHA);
#endif
    glVertexPointer(2, GL_FLOAT, 0, reinterpret_cast<GLfloat*>(vertices.array));
    glEnableClientState(GL_VERTEX_ARRAY);
    
    glTexCoordPointer(2, GL_FLOAT, 0, reinterpret_cast<GLfloat*>(textureCoord.array));
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    
    glDrawElements(GL_TRIANGLE_STRIP, indices.elementCount ,GL_UNSIGNED_SHORT, indices.array);
    
    
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    
    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);

}
    
    
    
    void OpenGLDriver::drawMaskShapeWithTexture(GLfloat* vertices,
                                                RenderInfo& renderingInfo,
                                                unsigned int nbVertices) {
        glBindTexture(GL_TEXTURE_2D, renderingInfo.getTexInfo()->textureId);
        
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        
#ifdef RB_OPENGLES
        glBlendFuncSeparateOES(GL_ZERO, GL_ONE, GL_ZERO, GL_SRC_ALPHA);
#else
        glBlendFuncSeparate(GL_ZERO, GL_ONE, GL_ZERO, GL_SRC_ALPHA);
#endif
        glVertexPointer(2, GL_FLOAT, 0, vertices);
        glEnableClientState(GL_VERTEX_ARRAY);
        
        glTexCoordPointer(2, GL_FLOAT, 0, reinterpret_cast<GLfloat*>(&(renderingInfo.getTexCoords()[renderingInfo.getCurrentFrame()][0])));
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        
        glDrawArrays(GL_TRIANGLE_FAN, 0, nbVertices);
        
        
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        
        glDisable(GL_BLEND);
        glDisable(GL_TEXTURE_2D);
    }
void OpenGLDriver::unmaskBatch(const CArray<Vector2>& vertices, const CArray<unsigned short>& indices){
    glEnable(GL_BLEND);
    glVertexPointer(2, GL_FLOAT, 0, reinterpret_cast<GLfloat*>(vertices.array));
    glEnableClientState(GL_VERTEX_ARRAY);
    
#ifdef RB_OPENGLES
    glBlendFuncSeparateOES(GL_ZERO, GL_ONE, GL_ONE, GL_ONE);
#else
    glBlendFuncSeparate(GL_ZERO, GL_ONE, GL_ONE, GL_ONE);
#endif
    glColor4ub(255, 255, 255, 255);
    
    
    
    glDrawElements(GL_TRIANGLE_STRIP, indices.elementCount ,GL_UNSIGNED_SHORT, indices.array);
    
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisable(GL_BLEND);
}
    
    void OpenGLDriver::unmaskShape(GLfloat* vertices,
                              RenderInfo&,
                              unsigned int nbVertices) {
        glEnable(GL_BLEND);
        glVertexPointer(2, GL_FLOAT, 0, vertices);
        glEnableClientState(GL_VERTEX_ARRAY);
        
#ifdef RB_OPENGLES
        glBlendFuncSeparateOES(GL_ZERO, GL_ONE, GL_ONE, GL_ONE);
#else
        glBlendFuncSeparate(GL_ZERO, GL_ONE, GL_ONE, GL_ONE);
#endif
        glColor4ub(255, 255, 255, 255);
        
        
        
        glDrawArrays(GL_TRIANGLE_FAN, 0, nbVertices);
        
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisable(GL_BLEND);
    }
    
    
    void OpenGLDriver::drawMaskedShapeWithTextureAndColor(GLfloat* vertices,
                                                          RenderInfo& renderingInfo,
                                                          unsigned int nbVertices, bool inversedMask) {
        if(renderingInfo.getColor().getAlpha() > 0) {
            
            glEnable(GL_BLEND);
            
            if(inversedMask) {
                //First render, if are drawing an invered mask, we must prepare the alpha buffer.
                glDisable(GL_TEXTURE_2D);
#ifdef RB_OPENGLES
                glBlendEquationSeparateOES(GL_FUNC_ADD_OES, GL_FUNC_ADD_OES);
#else
                glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
#endif
                
                
#ifdef RB_OPENGLES
                glBlendFuncSeparateOES(GL_ZERO, GL_ONE, GL_ONE_MINUS_DST_ALPHA, GL_ZERO);
#else
                glBlendFuncSeparate(GL_ZERO, GL_ONE, GL_ONE_MINUS_DST_ALPHA, GL_ZERO);
#endif
                glColor4ub(255, 255, 255, 255);
                
                
                glVertexPointer(2, GL_FLOAT, 0, vertices);
                glEnableClientState(GL_VERTEX_ARRAY);
                
                glDrawArrays(GL_TRIANGLE_FAN, 0, nbVertices);
                
            }
            
            glBindTexture(GL_TEXTURE_2D, renderingInfo.getTexInfo()->textureId);
            
            glEnable(GL_TEXTURE_2D);
            //Second render (we must use the minimum alpha between the source and destination and let the RGB component unchanged).
#ifdef RB_OPENGLES
            glBlendEquationSeparateOES(GL_FUNC_ADD_OES, GL_MIN_EXT);
#else
            glBlendEquationSeparate(GL_FUNC_ADD, GL_MIN);
#endif
            glBlendFunc(GL_ZERO, GL_ONE);
            
            glVertexPointer(2, GL_FLOAT, 0, vertices);
            glEnableClientState(GL_VERTEX_ARRAY);
            
            glTexCoordPointer(2, GL_FLOAT, 0, reinterpret_cast<GLfloat*>(&(renderingInfo.getTexCoords()[renderingInfo.getCurrentFrame()][0])));
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            
            glDrawArrays(GL_TRIANGLE_FAN, 0, nbVertices);
            
            //Third render, we must render the color according to the buffer alpha channel,
            const uint8_t* color = renderingInfo.getColor().getComponents();
            glColor4ub(color[0], color[1], color[2], color[3]);
            
            
#ifdef RB_OPENGLES
            glBlendEquationOES(GL_FUNC_ADD_OES);
#else
            glBlendEquation(GL_FUNC_ADD);
#endif
            glBlendFunc(GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA);
            
            
            glDrawArrays(GL_TRIANGLE_FAN, 0, nbVertices);
            
            
            
            //Fourth render, we must reset the alpha channel and leave the RGB channels unchanged.
            glDisable(GL_TEXTURE_2D);
#ifdef RB_OPENGLES
            glBlendFuncSeparateOES(GL_ZERO, GL_ONE, GL_ONE, GL_ZERO);
#else
            glBlendFuncSeparate(GL_ZERO, GL_ONE, GL_ONE, GL_ZERO);
#endif
            glColor4ub(255, 255, 255, 255);
            
            glDrawArrays(GL_TRIANGLE_FAN, 0, nbVertices);
            
            
            glDisableClientState(GL_VERTEX_ARRAY);
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
            glDisable(GL_BLEND);
            
        }
        
    }
    
    
    
    
    void OpenGLDriver::prepareScene(const Vector2& position, float angle, float zoom,
                                    const Color& backgroundColor,
                                    const Vector2& rotationCenterOffset) {
        glClearColor(clampColorComponent(backgroundColor.getRed()),
                     clampColorComponent(backgroundColor.getGreen()),
                     clampColorComponent(backgroundColor.getBlue()),
                     1.0f);
        
        glClear(GL_COLOR_BUFFER_BIT);
        
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        
        glScalef(zoom, zoom, 1);
        glTranslatef(rotationCenterOffset.getX(), rotationCenterOffset.getY(), 0);
        glRotatef(angle, 0, 0, 1);
        glTranslatef(-rotationCenterOffset.getX(), -rotationCenterOffset.getY(), 0);
        glTranslatef(-(position.getX()), -(position.getY()), 0);
        
    }
    
    void OpenGLDriver::pushMatrix() {
        glPushMatrix();
    }
    
    void OpenGLDriver::translate(const Vector2& translation) {
        glTranslatef(-translation.getX(), -translation.getY(), 0.0f);
    }
    
    void OpenGLDriver::popMatrix() {
        glPopMatrix();
    }
    
    void OpenGLDriver::initializeGraphicDriver(unsigned int screenWidth,
                                               unsigned int screenHeight) {
        glShadeModel(GL_FLAT);
        
        glViewport(0, 0, static_cast<int>(screenWidth),
                   static_cast<int>(screenHeight));
        
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
#ifdef RB_OPENGLES
        glOrthof(0.0f, static_cast<float>(screenWidth), static_cast<float>(screenHeight), 0.0f, -1.0f, 1.0f);
#else
        glOrtho(0.0, static_cast<double>(screenWidth), static_cast<double>(screenHeight), 0.0, -1.0, 1.0);
#endif
#if defined(RB_MAC_PLATFORM) && defined(RB_SDL)
        int swapInterval = 1;
        CGLSetParameter(CGLGetCurrentContext(), kCGLCPSwapInterval, &swapInterval);
#endif
        
        //FBO and mask texture initialization
#ifdef RB_OPENGLES
        glGenFramebuffersOES(1, &maskedFramebuffer);
        glBindFramebufferOES(GL_FRAMEBUFFER_OES, maskedFramebuffer);
#else
        glGenFramebuffersEXT(1, &maskedFramebuffer);
        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, maskedFramebuffer);
#endif
        
        glGenTextures(1, &maskedTexture);
        glBindTexture(GL_TEXTURE_2D, maskedTexture);
        
        maskedTextureInfo = new TextureInfo();
        maskedTextureInfo->textureId = maskedTexture;
        maskedTextureInfo->imageWidth = MainWindow::getInstance().getResolutionWidth();
        maskedTextureInfo->imageHeight = MainWindow::getInstance().getResolutionHeight();
        maskedTextureInfo->poweredWidth = MathHelper::nextPowerOf2(maskedTextureInfo->imageWidth);
        maskedTextureInfo->poweredHeight = MathHelper::nextPowerOf2(maskedTextureInfo->imageHeight);
        
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, maskedTextureInfo->poweredWidth, maskedTextureInfo->poweredHeight, 0,
                     GL_RGBA, GL_UNSIGNED_BYTE, NULL);
        
        
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        
        maskedSprite = new Sprite(maskedTextureInfo);
        
    }
    
    
    TextureInfo* OpenGLDriver::loadTexture(PixMap* pixMap) {
        
        
        TextureInfo* texInfo = new TextureInfo();
        glGenTextures(1, &(texInfo->textureId));
        glBindTexture(GL_TEXTURE_2D, texInfo->textureId);
        
        
        
        int widthPoweredToTwo = MathHelper::nextPowerOf2(pixMap->getWidth());
        int heightPoweredToTwo = MathHelper::nextPowerOf2(pixMap->getHeight());
        
        
        PixMap poweredTo2Pixmap(widthPoweredToTwo, heightPoweredToTwo, pixMap->getColorFormat());
        poweredTo2Pixmap.insertSubPixMap(pixMap);
        
        
        texInfo->imageWidth = pixMap->getWidth();
        texInfo->imageHeight = pixMap->getHeight();
        
        texInfo->poweredWidth = widthPoweredToTwo;
        texInfo->poweredHeight = heightPoweredToTwo;
        
        GLint format;
        texInfo->colorFormat = pixMap->getColorFormat();
        if(pixMap->getColorFormat() == ColorFormat::RGBA) {
            format = GL_RGBA;
        } else if(pixMap->getColorFormat() == ColorFormat::ALPHA) {
            format = GL_ALPHA;
        }
        
        glTexImage2D(
                     GL_TEXTURE_2D,
                     0,
                     format,
                     widthPoweredToTwo,
                     heightPoweredToTwo,
                     0,
                     format,
                     GL_UNSIGNED_BYTE,
                     poweredTo2Pixmap.getBuffer());
        
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        
        return texInfo;
    }
    
    float OpenGLDriver::clampColorComponent(unsigned int component) {
        return static_cast<float>(component) / static_cast<float>(Color::MAX_COMPONENT_VALUE);
    }
    
#endif //RB_OPENGL
    
