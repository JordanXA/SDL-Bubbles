#pragma once

class Input {
    public:
        Input(SDL_Event& eventsRef) : events(eventsRef)
        {
        }

        SDL_Event& events;
        bool quit;
        int plyr1flags;

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
                        plyr1flags = plyr1flags | INFLAG_UP;
                        break;

                        case SDLK_DOWN:
                        plyr1flags = plyr1flags | INFLAG_DOWN;
                        break;

                        case SDLK_LEFT:
                        plyr1flags = plyr1flags | INFLAG_LEFT;
                        break;

                        case SDLK_RIGHT:
                        plyr1flags = plyr1flags | INFLAG_RIGHT;
                        break;
                    }
                }
                
                if (events.type == SDL_KEYUP ) {
                    switch (events.key.keysym.sym) {
                        case SDLK_UP:
                        plyr1flags = plyr1flags & ~INFLAG_UP;
                        break;

                        case SDLK_DOWN:
                        plyr1flags = plyr1flags & ~INFLAG_DOWN;
                        break;

                        case SDLK_LEFT:
                        plyr1flags = plyr1flags & ~INFLAG_LEFT;
                        break;

                        case SDLK_RIGHT:
                        plyr1flags = plyr1flags & ~INFLAG_RIGHT;
                        break;
                    }
                }

            }
        }
};