#include "TextureManager.h"

SDL_Texture *TextureManager::LoadTexture(const char *texture) {
    SDL_Surface *tempSurface = IMG_Load(texture);

    if (!tempSurface)
        SDL_Log("Failed to load texture %s\n", IMG_GetError());

    SDL_Texture *tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);

    if (!tex)
        SDL_Log("Failed to create texture %s\n", SDL_GetError());
    SDL_FreeSurface(tempSurface);

    return tex;
}

void TextureManager::Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip) {
    SDL_RenderCopyEx(Game::renderer, tex, &src, &dest, 0, nullptr, flip);
}
