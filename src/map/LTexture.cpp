#include "LTexture.hpp"
#include <SDL3/SDL_rect.h>


//---------------------------------------------------------//
/* Class Implementation */
//---------------------------------------------------------//

LTexture::LTexture(SDL_Renderer* pRenderer):

    mTexture{nullptr},
    mRenderer{nullptr},
    mWidth{0},
    mHeight{0},
    posX{0},
    posY{0},
    clip{nullptr}

{
    this->mRenderer = pRenderer;
}

//---------------------------------------------------------//

LTexture::~LTexture() {

    free();
    
}

//------------------------------------------
void LTexture::setRender(SDL_Renderer* ren) {

    mRenderer = ren;

}

//---------------------------------------------------------//

void LTexture::move(float x, float y) {

    posX += x;
    posY += y;

}

//---------------------------------------------------------//

void LTexture::setCamera(SDL_FRect* cam) {

    camera = cam;

}

//---------------------------------------------------------//

void LTexture::setPosition(float x, float y) {

    posX = x;
    posY = y;

}

//---------------------------------------------------------//

void LTexture::setSize(float x, float y) {

    rWidth = x;
    rHeight = y;

}

//---------------------------------------------------------//

void LTexture::setClip(float x, float y, float w, float h) {

    clip = new SDL_FRect{x,y,w,h};

}

//---------------------------------------------------------//

bool LTexture::loadFromFile(std::string path) {

    free();

    if(SDL_Surface* loadedSurface = IMG_Load(path.c_str()); loadedSurface == nullptr) {

        SDL_Log("Unable to load image! SDL Error: %s\n", SDL_GetError());

    } else {

        if(mTexture = SDL_CreateTextureFromSurface(mRenderer, loadedSurface); mTexture == nullptr) {
            SDL_Log("Unable to create texture! SDL Error: %s\n", SDL_GetError());
            printf("%d\n", mRenderer != nullptr);

        } else {

            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;

            rWidth =  mWidth;
            rHeight = mHeight;

            clip = new SDL_FRect{0.f, 0.f, static_cast<float>(mWidth), static_cast<float>(mHeight)};

        }

        SDL_DestroySurface(loadedSurface);

    }

    return mTexture != nullptr;

}

//---------------------------------------------------------//

void LTexture::free() {

    if(mTexture != nullptr) {

        SDL_DestroyTexture(mTexture);
        mTexture = nullptr;
        mWidth = 0;
        mHeight = 0;

    }
}

//---------------------------------------------------------//

void LTexture::render(SDL_FRect* camera){

    SDL_FRect dstRect = {posX - camera->x, posY - camera->y, static_cast<float>(mWidth), static_cast<float>(mHeight)};

    dstRect.w = rWidth;
    dstRect.h = rHeight;    

    SDL_RenderTexture(mRenderer, mTexture, clip, &dstRect);

}

//---------------------------------------------------------//

int LTexture::getWidth(){

    return mWidth;

}

//---------------------------------------------------------//

int LTexture::getHeight(){

    return mHeight;

}

//---------------------------------------------------------//
