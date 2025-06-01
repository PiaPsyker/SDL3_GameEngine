#include "Loader.hpp"
#include "map/LTexture.hpp"
#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <filesystem>

//---------------------------------------------------------//
/* Class Implementation */
//---------------------------------------------------------//

Loader * Loader::singleton = nullptr;

//---------------------------------------------------------//

Loader* Loader::getLoader() {
    
    if (Loader::singleton == nullptr) {
        Loader::singleton = new Loader(1920, 1080, 128);

    }
    return Loader::singleton;
}

//---------------------------------------------------------//

Loader::Loader(int screenW, int screenH, int mapS):

    window{nullptr},
    renderer{nullptr}

{

    screenWidth = screenW;
    screenHeight = screenH;

    mapSize = mapS;    

    camera = { 0.f, 0.f, (float)screenWidth, (float)screenHeight };

    genMap = new MapGenerator(mapSize, mapSize);

}

Loader::~Loader() {

    close();
    singleton = nullptr;

}

//---------------------------------------------------------//

bool Loader::init() {
    
    bool success{true};

    if(!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL couldnt initialize! SDL Error: %s\n", SDL_GetError());
        return false;
    }
    if(!TTF_Init()) {
        SDL_Log("TTF couldnt initialize! SDL Error: %s\n", SDL_GetError());
        return false;
    }
    if(!SDL_CreateWindowAndRenderer("SDL3 Text", screenWidth, screenHeight, SDL_WINDOW_FULLSCREEN, &window, &renderer)) {
        SDL_Log("Window couldnt be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    // SDL_SetRenderVSync( renderer, ( true ) ? 1 : SDL_RENDERER_VSYNC_DISABLED );

    return success;

}

//---------------------------------------------------------//

bool Loader::loadTextures() {

    bool success{true};

    for (const auto& dirEntry : std::filesystem::recursive_directory_iterator("resources")) {

        if(dirEntry.path().extension() == ".png") {

            LTexture* tempTex = new LTexture(renderer);
            tempTex->setCamera(&camera);
            tempTex->loadFromFile(dirEntry.path());

            TextureInfo* tex = new TextureInfo{dirEntry.path().filename(), tempTex};

            textures.push_front(tex);

            std::cout << "Added Texture: " << dirEntry.path().filename() << std::endl;
    
        }

        if(dirEntry.path().extension() == ".ttf") {

            TTF_Font* tempFont;

            std::string fPath = dirEntry.path();
            std::cout << fPath << std::endl;

            tempFont = TTF_OpenFont(dirEntry.path().c_str(), 48 );
            FontInfo* font = new FontInfo{dirEntry.path().filename(), tempFont};

            fonts.push_front(font);

            std::cout << "Added Font: " << dirEntry.path() << std::endl;

        }
    }

    return success;

}

//---------------------------------------------------------//

void Loader::close() {

    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
    SDL_DestroyWindow( window );
    window = nullptr;

    delete genMap;

    TTF_Quit();
    SDL_Quit();

}

//---------------------------------------------------------//

void Loader::setRenderer(SDL_Renderer* ren) {

    renderer = ren;

}

//---------------------------------------------------------//

int Loader::getScreenWidth() {

    return screenWidth;

}

//---------------------------------------------------------//

int Loader::getScreenHeight() {

    return screenHeight;

}

//---------------------------------------------------------//

LTexture* Loader::getTexture(std::string name) {

    for(TextureInfo* tex : textures) {

        if(tex->fileName == name) {

            return tex->texture;

        }

    }

    return nullptr;

}

//---------------------------------------------------------//

TTF_Font* Loader::getFont(std::string name) {

    for(FontInfo* ft : fonts) {

        if(ft->fileName == name) {

            return ft->font;

        }

    }

    return nullptr;

}

//---------------------------------------------------------//

SDL_FRect* Loader::getCamera() {

    return &camera;

}

//---------------------------------------------------------//

SDL_Renderer* Loader::getRenderer() {

    return renderer;

}