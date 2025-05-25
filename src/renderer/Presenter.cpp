#include "Presenter.hpp"


//---------------------------------------------------------//
/* Class Implementation */
//---------------------------------------------------------//

Presenter::Presenter() {


}

//---------------------------------------------------------//

void Presenter::render() {

    

    for(LTexture* object : renderObjects) {
        object->render();
    }

    SDL_RenderPresent(mRenderer);

}

//---------------------------------------------------------//

void Presenter::setRenderer(SDL_Renderer* ren) {

    mRenderer = ren;

}

//---------------------------------------------------------//

void Presenter::addRenderObject(LTexture* obj) {

    renderObjects.push_front(obj);

}
//---------------------------------------------------------//

void Presenter::free() {

    for(LTexture* object : renderObjects) {
        object->free();
    }
    SDL_DestroyRenderer( mRenderer );
    mRenderer = nullptr;

}

//---------------------------------------------------------//

SDL_Renderer* Presenter::getRenderer() {

    return mRenderer;

}

//---------------------------------------------------------//