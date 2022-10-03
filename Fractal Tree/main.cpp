//
//  main.cpp
//  Fractal Tree
//
//  Created by Taj Telesford on 9/26/22.
//

#define WIDTH 500
#define HEIGHT 500
#define TITLE "FRACTAL TREE"

#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include <cmath>

#define ANGLE M_PI/2

using namespace std;

struct lineVector{
    double x;
    double y;
};

struct posVec{
    lineVector start;
    lineVector end;
};

double BRANCH_ANGLE = M_PI / 3;
double TRUNK_RATIO = .3;
int LIMIT = 5;

void createStartingVector(lineVector& P0, lineVector& P1)
{
    P1.x = WIDTH/2;
    P1.y = HEIGHT - 100;
    
    P0.x = WIDTH/2;
    P0.y = HEIGHT;
}


void makeTree(lineVector pos0, lineVector pos1, int limit, SDL_Renderer *renderer)
{
    double dx = pos1.x - pos0.x;
    double dy = pos1.y - pos0.y;
    double dist = sqrt((dx * dx) + (dy * dy));
    double angle = atan2(dy, dx);
    double BRANCH_LENGTH = dist * (1-TRUNK_RATIO);
    lineVector PA, PB, PC;
    PA.x = pos0.x + dx * TRUNK_RATIO;
    PA.y = pos0.y + dy * TRUNK_RATIO;
    cout << "x "<< PA.x <<" y "<< PA.y;
    
    PB.x = PA.x + cos(angle + BRANCH_ANGLE) * BRANCH_LENGTH;
    PB.y = PA.y + sin(angle + BRANCH_ANGLE) * BRANCH_LENGTH;
    
    PC.x = PA.x + cos(angle - BRANCH_ANGLE) * BRANCH_LENGTH;
    PC.y = PA.y + sin(angle - BRANCH_ANGLE) * BRANCH_LENGTH;
    
    
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    SDL_RenderDrawLine(renderer, pos0.x, pos0.y, PA.x, PA.y);
    
   if(limit > 0)
    {
        makeTree(PA, PC, limit-1, renderer);
        makeTree(PA, PB, limit-1, renderer);
    }
}

int main(int argc, const char * argv[]) {
    // Checking the Instalization of SDL
    
    SDL_Init(SDL_INIT_VIDEO);
    if( SDL_Init( SDL_INIT_EVERYTHING ) == 0 ){
        std::cout<< "SDL has been initializaed..." << std::endl;
    }
    else{
        std::cout << "SDL has failed.. Errors: " << SDL_GetError() << std::endl;
    }
    
    //Creating Window
   SDL_Window *window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
   
    SDL_Event e;
    lineVector startPos0, startPos1;
    createStartingVector(startPos0, startPos1);
    
    //SDL_RenderPresent(renderer);
    bool running =true;
        while(running)
        {
            while(SDL_PollEvent(&e))
            {
                if( e.type == SDL_QUIT ) { running = false; }
            }
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
            makeTree(startPos0, startPos1, LIMIT, renderer);
            
            SDL_RenderPresent(renderer);
            SDL_Delay(50);
        }
    
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
}
