#pragma once

class Input {
    public:

        Input(SDL_Event& eventsRef, bool& quitRef) : events(eventsRef), quit(quitRef)
        {
        }

        SDL_Event& events;
        bool& quit;

        void inputUpdate() {
            //Handle events on queue
            while( SDL_PollEvent( &events ) != 0 ) {
                //User requests quit
                if( events.type == SDL_QUIT ) {
                    quit = true;
                }

                if (events.type == SDL_KEYDOWN ) {
                    switch (events.key.keysym.sym) {
                        case SDLK_UP:
                        flags = flags | INFLAG_UP;
                        break;

                        case SDLK_DOWN:
                        flags = flags | INFLAG_DOWN;
                        break;

                        case SDLK_LEFT:
                        flags = flags | INFLAG_LEFT;
                        break;

                        case SDLK_RIGHT:
                        flags = flags | INFLAG_RIGHT;
                        break;
                    }
                }
                
                if (events.type == SDL_KEYUP ) {
                    switch (events.key.keysym.sym) {
                        case SDLK_UP:
                        flags = flags & ~INFLAG_UP;
                        break;

                        case SDLK_DOWN:
                        flags = flags & ~INFLAG_DOWN;
                        break;

                        case SDLK_LEFT:
                        flags = flags & ~INFLAG_LEFT;
                        break;

                        case SDLK_RIGHT:
                        flags = flags & ~INFLAG_RIGHT;
                        break;
                    }
                }

            }
        }
};