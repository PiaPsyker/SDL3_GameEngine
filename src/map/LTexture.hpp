//---------------------------------------------------------//
//
// Prototype Code for SDL3 - DO NOT USE FOR PROD
//
// PiaPsyker - 2025
//
//---------------------------------------------------------//
/* Library Loading */
//---------------------------------------------------------//
#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

//---------------------------------------------------------//
/* Class Prototype */
//---------------------------------------------------------//

class LTexture{

    public:

        LTexture(SDL_Renderer* pRenderer);
        ~LTexture();

        void setRender(SDL_Renderer* ren);

        bool loadFromFile(std::string path);
        bool loadFromText(TTF_Font* font, std::string text, SDL_Color textColor);

        void free();

        void move(float x, float y);

        void setCamera(SDL_FRect* cam);
        void setPosition(float x, float y);
        void setSize(float x, float y);
        void setClip(float x, float y, float w, float h);

        void render(SDL_FRect* camera=nullptr);

        int getWidth();
        int getHeight();

    private:

        SDL_Texture* mTexture;
        SDL_Renderer* mRenderer;
        SDL_FRect* camera;

        int mWidth;
        int mHeight;

        int rWidth;
        int rHeight;

        float posX;
        float posY;

        SDL_FRect* clip;

};

#endif