#include "game.h"

using chess::Game;

void prepareSettings(Game::Settings *settings) {
    settings->setResizable(false);
}

CINDER_APP(Game, ci::app::RendererGl, prepareSettings);