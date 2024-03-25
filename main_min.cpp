#define _USE_MATH_DEFINES
#include<stdio.h>
#include<string.h>
#include <math.h>

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}

#define SCREEN_WIDTH 690
#define SCREEN_HEIGHT 480
#define MARIO_STARTING_POSITION_X 50
#define MARIO_STARTING_POSITION_Y SCREEN_HEIGHT - 64
#define BARREL_STARTING_POSITION_X SCREEN_WIDTH / 2 - 40
#define BARREL_STARTING_POSITION_Y 110
#define RIGHT 1 //Mario position
#define LEFT -1 //Mario position
#define CLIMBING 2 //Mario position
#define MOVEMENT_SPEED 5 //Mario speed
#define MOVEMENT_SPEED_BARREL 5 //Barrel speed
#define JUMP_HEIGHT 30 //height of mario jump
#define MARIO_HEIGHT 30 // height of mario image
#define MARIO_WIDTH 30 // width of mario image
#define PLATFORM_HEIGHT 15 //Height of platform
#define HEIGHT_BETWEEN_LEVELS 59 // Height between levels (from 2 to 5)
#define LENGTH_TO_BOTTOM_MARIO 15 // lenght from middle of mario image to his bottom
#define STARTING_BARREL_LEVEL 6 // Level on which barrel starts rolling
#define STARTING_MARIO_LEVEL 1 // level on which mario starts

#ifdef __cplusplus
extern "C"
#endif

struct Timer {
    Uint32 lastTime = SDL_GetTicks();
    int t1 = lastTime;
    int t2 = lastTime;
    double delta = 0;
    double delta_barrel = 0;
    double worldTime = 0;
    double barrel_time = 0;
    double jump_time = 0;
    double delta_jump = 0;
    double delta_barrel2 = 0;
    double barrel2_time = 0;

};

struct Surface
{
    SDL_Surface* screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);;
    SDL_Texture* scrtex;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Event event;
};

struct Mario
{
    int mario_x = MARIO_STARTING_POSITION_X;
    int mario_y = MARIO_STARTING_POSITION_Y;
    int level = STARTING_MARIO_LEVEL;
    bool jumping = false;
    int direction = RIGHT; // 1 FOR RIGHT -1 FOR LEFT AND 2 FOR CLIMBING
    bool up = false;
    Uint32 lastJumpTime = 0;
    int mario_y_before_jump = 0;
    SDL_Surface* current_image;

};

struct Barrel
{
    int Barrel_x = BARREL_STARTING_POSITION_X;
    int Barrel_y = BARREL_STARTING_POSITION_Y;
    int barrel_level = 6;
    Uint32 lastBarrelMoveTime = 0;
    int movement;
    SDL_Surface* current_image;

};

struct Barrel2
{
    int Barrel_x = BARREL_STARTING_POSITION_X;
    int Barrel_y = BARREL_STARTING_POSITION_Y;
    int barrel_level = STARTING_BARREL_LEVEL;
    Uint32 lastBarrel2MoveTime = 0;
    int movement;
    SDL_Surface* current_image;

};

struct Images {

    SDL_Surface* imageStanding = SDL_LoadBMP("./images/mario333.bmp");
    SDL_Surface* imagejumping = SDL_LoadBMP("./images/mario_mario.jumping.bmp");
    SDL_Surface* imageStanding_flipped = SDL_LoadBMP("./images/mario_flip.bmp");
    SDL_Surface* mario_jump = SDL_LoadBMP("./images/mario_jump.bmp");
    SDL_Surface* mario_jump_flip = SDL_LoadBMP("./images/mario_jump_flipped.bmp");
    SDL_Surface* map = SDL_LoadBMP("./images/map.bmp");
    SDL_Surface* barrel = SDL_LoadBMP("./images/barrel.bmp");
    SDL_Surface* item = SDL_LoadBMP("./images/item.bmp");
    SDL_Surface* item2 = SDL_LoadBMP("./images/item2.bmp");
    SDL_Surface* barrel_2 = SDL_LoadBMP("./images/barrel_2.bmp");
    SDL_Surface* Start = SDL_LoadBMP("./images/start_game.bmp");
    SDL_Surface* kong1 = SDL_LoadBMP("./images/kong1.bmp");
    SDL_Surface* mario_ladder = SDL_LoadBMP("./images/mario_ladder.bmp");
    SDL_Surface* charset = SDL_LoadBMP("./images/cs8x8.bmp");
};

struct Game
{
    bool gameStarted = false;
    bool quit = false;
};

struct Colors
{
    int czarny;
    int zielony;
    int czerwony;
    int niebieski;
};

void InitColors(Colors* color, Surface* surface)
{
    color->czarny = SDL_MapRGB(surface->screen->format, 0x00, 0x00, 0x00);
    color->zielony = SDL_MapRGB(surface->screen->format, 0x00, 0xFF, 0x00);
    color->czerwony = SDL_MapRGB(surface->screen->format, 0xFF, 0x00, 0x00);
    color->niebieski = SDL_MapRGB(surface->screen->format, 0x11, 0x11, 0xCC);
}

double updateTimer(Timer& timer) {
    timer.t2 = SDL_GetTicks();
    timer.delta = (timer.t2 - timer.t1) * 0.001;
    timer.delta_barrel = (timer.t2 - timer.t1) * 0.01;
    timer.delta_barrel2 = (timer.t2 - timer.t1) * 0.01;
    timer.delta_jump = (timer.t2 - timer.t1) * 0.01;
    timer.t1 = timer.t2;
    timer.worldTime += timer.delta;
    timer.barrel_time += timer.delta_barrel;
    timer.barrel2_time += timer.delta_barrel2;
    timer.jump_time += timer.delta_jump;
    return timer.delta;
    return timer.delta_barrel;
    return timer.delta_jump;
    return timer.delta_barrel2;
}

double TimerFunction(Timer& timer) {
    return updateTimer(timer);
}

int Barrel_move(int barrel_level)
{
    if (barrel_level % 2 == 1) { return -10; }
    else if (barrel_level % 2 == 0) { return 10; }
}

SDL_Surface* Mario_image(int direction, SDL_Surface* imageStanding_flipped, SDL_Surface* mario_ladder, SDL_Surface* imageStanding, SDL_Surface* mario_jump, bool jump, SDL_Surface* mario_jump_flipped)
{
    if (direction == 1) {
        if (jump)
        {
            return mario_jump_flipped;
        }
        else
        {
            return imageStanding_flipped;
        }
    }
    else if (direction == 2)
    {
        return mario_ladder;
    }
    else if (direction == -1) {
        if (jump)
        {
            return mario_jump;
        }
        else
        {
            return imageStanding;
        }
    }
}

void DrawSprite(SDL_Surface* screen, SDL_Surface* spriteSheet, int srcX, int srcY, int srcW, int srcH, int destX, int destY) {
    SDL_Rect srcRect = { srcX, srcY, srcW, srcH };
    SDL_Rect destRect = { destX, destY, srcW, srcH };
    SDL_BlitSurface(spriteSheet, &srcRect, screen, &destRect);
}

void DrawString(SDL_Surface* screen, int x, int y, const char* text, SDL_Surface* charset) {
    int px, py, c;
    SDL_Rect s, d;
    s.w = 8;
    s.h = 8;
    d.w = 8;
    d.h = 8;
    while (*text) {
        c = *text & 255;
        px = (c % 16) * 8;
        py = (c / 16) * 8;
        s.x = px;
        s.y = py;
        d.x = x;
        d.y = y;
        SDL_BlitSurface(charset, &s, screen, &d);
        x += 8;
        text++;
    };
};

void DrawSurface(SDL_Surface* screen, SDL_Surface* sprite, int x, int y) {
    SDL_Rect dest;
    dest.x = x - sprite->w / 2;
    dest.y = y - sprite->h / 2;
    dest.w = sprite->w;
    dest.h = sprite->h;
    SDL_BlitSurface(sprite, NULL, screen, &dest);
};

void FreeAndDestroy(SDL_Surface* charset, SDL_Surface* screen, SDL_Surface* imageStanding, SDL_Texture* scrtex)
{
    SDL_FreeSurface(charset);
    SDL_FreeSurface(screen);
    SDL_DestroyTexture(scrtex);
    SDL_FreeSurface(imageStanding);
    SDL_CloseAudio();
}

void DrawPixel(SDL_Surface* surface, int x, int y, Uint32 color) {
    int bpp = surface->format->BytesPerPixel;
    Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;
    *(Uint32*)p = color;
};

void DrawLine(SDL_Surface* screen, int x, int y, int l, int dx, int dy, Uint32 color) {
    for (int i = 0; i < l; i++) {
        DrawPixel(screen, x, y, color);
        x += dx;
        y += dy;
    };
};

void DrawRectangle(SDL_Surface* screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor) {
    int i;
    DrawLine(screen, x, y, k, 0, 1, outlineColor);
    DrawLine(screen, x + l - 1, y, k, 0, 1, outlineColor);
    DrawLine(screen, x, y, l, 1, 0, outlineColor);
    DrawLine(screen, x, y + k - 1, l, 1, 0, outlineColor);
    for (i = y + 1; i < y + k - 1; i++)
        DrawLine(screen, x + 1, i, l - 2, 1, 0, fillColor);
};

int Mario_level(int y)
{
    if (y <= SCREEN_HEIGHT - 50 && y > SCREEN_HEIGHT - 107) { return 1; }
    else if (y <= SCREEN_HEIGHT - 107 && y > SCREEN_HEIGHT - 166) { return  2; }
    else if (y <= SCREEN_HEIGHT - 166 && y > SCREEN_HEIGHT - 166 - HEIGHT_BETWEEN_LEVELS) { return  3; }
    else if (y <= SCREEN_HEIGHT - 166 - HEIGHT_BETWEEN_LEVELS * 1 && y > SCREEN_HEIGHT - 166 - HEIGHT_BETWEEN_LEVELS * 2) { return  4; }
    else if (y <= SCREEN_HEIGHT - 166 - HEIGHT_BETWEEN_LEVELS * 2 && y > SCREEN_HEIGHT - 166 - HEIGHT_BETWEEN_LEVELS * 3) { return  5; }
    else if (y <= SCREEN_HEIGHT - 166 - HEIGHT_BETWEEN_LEVELS * 3) { return 6; }
}

int Barrel_level(int Barrel_y)
{
    if (Barrel_y <= SCREEN_HEIGHT - 50 && Barrel_y > SCREEN_HEIGHT - 100) { return 1; }
    else if (Barrel_y <= SCREEN_HEIGHT - 100 && Barrel_y > SCREEN_HEIGHT - 160) { return  2; }
    else if (Barrel_y <= SCREEN_HEIGHT - 160 && Barrel_y > SCREEN_HEIGHT - 160 - HEIGHT_BETWEEN_LEVELS) { return  3; }
    else if (Barrel_y <= SCREEN_HEIGHT - 160 - HEIGHT_BETWEEN_LEVELS && Barrel_y > SCREEN_HEIGHT - 160 - HEIGHT_BETWEEN_LEVELS * 2) { return  4; }
    else if (Barrel_y <= SCREEN_HEIGHT - 160 - HEIGHT_BETWEEN_LEVELS * 2 && Barrel_y > SCREEN_HEIGHT - 160 - HEIGHT_BETWEEN_LEVELS * 3) { return  5; }
    else if (Barrel_y <= SCREEN_HEIGHT - 160 - HEIGHT_BETWEEN_LEVELS * 3) { return 6; }
}

void Init_Game(Surface& surface, Barrel& barrel, Barrel2& barrel2, Images& images, Mario& mario)
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &surface.window, &surface.renderer);
    SDL_SetRenderDrawColor(surface.renderer, 0, 0, 0, 255);
    surface.scrtex = SDL_CreateTexture(surface.renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
    barrel.current_image = images.barrel;
    barrel2.current_image = images.barrel_2;
    mario.current_image = images.imageStanding;
}

int point_counter(int Barrel_x, int Barrel_y, int mario_x, int mario_y, int mario_level, int barrel_level, int Barrel2_x, int Barrel2_y, int barrel2_level)
{
    if (Barrel_x >= mario_x - 5 && Barrel_x <= mario_x && mario_y <= Barrel_y && mario_level == barrel_level)
    {
        return 500;
    }
    else if (Barrel2_x >= mario_x - 5 && Barrel2_x <= mario_x && mario_y <= Barrel2_y && mario_level == barrel2_level)
    {
        return 500;
    }
    else
    {
        return 0;
    }
}

void Draw_Menu(SDL_Surface* screen, int mario_move_right_left, int mario_move_down_up, SDL_Surface* charset, int niebieski, Timer timer, char* text, int* POINTS)
{
    DrawRectangle(screen, SCREEN_WIDTH / 1.5, 0, SCREEN_WIDTH / 3, 30, niebieski, niebieski);
    sprintf(text, "TIME: %.1lf s", timer.worldTime);
    DrawString(screen, SCREEN_WIDTH / 1.3, 10, text, charset);
    sprintf(text, "Press n to start new game");
    DrawString(screen, SCREEN_WIDTH / 1.43, 20, text, charset);
    sprintf(text, "POINTS: %06d", *POINTS);
    DrawString(screen, SCREEN_WIDTH / 1.3, 60, text, charset);
}

void updateAndRender(SDL_Surface* screen, SDL_Texture* scrtex, SDL_Renderer* renderer)
{
    SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
    SDL_RenderCopy(renderer, scrtex, NULL, NULL);
    SDL_RenderPresent(renderer);
}

void Draw_StartScreen(SDL_Surface* screen, SDL_Surface* Start, SDL_Surface* kong1, SDL_Surface* charset, char* text)
{
    DrawSurface(screen, Start, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    DrawSurface(screen, kong1, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 1.3);
    DrawString(screen, SCREEN_WIDTH / 2 - 40, SCREEN_HEIGHT / 2, text, charset);
    sprintf(text, "KING DONKEY");
}

Uint32 GetPixel(SDL_Surface* surface, int Position_x, int Position_y) {
    int Bytes_Per_Pixel = 4;
    Uint8* pPixel = (Uint8*)surface->pixels + Position_y * surface->pitch + Position_x * Bytes_Per_Pixel;
    return *(Uint32*)pPixel;
}

bool can_go_left(int level, int mario_x)
{
    if (level == 1)
    {
        if (mario_x > 35)
        {
            return true;
        }
        else
        {
            return false;
        }

    }
    else if (level == 2 || level == 4)
    {
        if (mario_x > 50)
        {
            return true;
        }
        else
        {
            return false;
        }

    }
    else if (level == 3 || level == 5)
    {
        if (mario_x > 90)
        {
            return true;
        }
        else
        {
            return false;
        }

    }
    else if (level == 6)
    {
        if (mario_x > SCREEN_WIDTH / 2)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

bool can_go_right(int level, int mario_x)
{
    if (level == 1)
    {
        if (mario_x <= SCREEN_WIDTH - 35)
        {
            return true;
        }
        else
        {
            return false;
        }

    }

    else if (level == 2 || level == 4 || level == 6)
    {
        if (mario_x < SCREEN_WIDTH - 95)
        {
            return true;
        }
        else
        {
            return false;
        }

    }
    else if (level == 3 || level == 5)
    {
        if (mario_x < SCREEN_WIDTH - 45)
        {
            return true;
        }
        else
        {
            return false;
        }

    }
}

int CheckCollision_ladder(int x, int y) {
    //1st LEVEL FROM SCREEN_HEIGHT - 50 TO SCREEN_HEIGHT - 107
    //2nd LEVEL FROM SCREEN_HEIGHT - 107 TO SCREEN_HEIGHT - 166
    //3rd LEVEL FROM SCREEN_HEIGHT - 166 TO SCREEN_HEIGHT - 166 - HEIGHT_BETWEEN_LEVELS * 1
    //4th LEVEL FROM SCREEN_HEIGHT - 166 - HEIGHT_BETWEEN_LEVELS * 1 TO  SCREEN_HEIGHT - 166 - HEIGHT_BETWEEN_LEVELS * 2
    //5th LEVEL FROM SCREEN_HEIGHT - 166 - HEIGHT_BETWEEN_LEVELS * 2 TO SCREEN_HEIGHT - 166 - HEIGHT_BETWEEN_LEVELS * 3
    //FIRST LEVEL RIGHT BOTTOM LADDER
    //FIRST LEVEL FIRST  LADDER RIGHT BOTTOM
    if (x <= SCREEN_WIDTH - 130 && x >= SCREEN_WIDTH - 150 && y <= SCREEN_HEIGHT - 59 && y >= SCREEN_HEIGHT - 107)
    {
        return 1;
    }
    //SECOND LEVEL FIRST LADDER (LEFT)
    else if (x <= 150 && x >= 130 && y <= SCREEN_HEIGHT - 120 && y >= SCREEN_HEIGHT - 166)
    {
        return 1;
    }
    //SECOND LEVEL LADDER MIDDLE
    else if (x <= SCREEN_WIDTH - 360 && x >= SCREEN_WIDTH - 385 && y <= SCREEN_HEIGHT - 115 && y >= SCREEN_HEIGHT - 172)
    {
        return 1;
    }
    //THIRD LEVEL LADDER RIGHT
    else if (x <= SCREEN_WIDTH - 130 && x >= SCREEN_WIDTH - 150 && y <= SCREEN_HEIGHT - 180 && y >= SCREEN_HEIGHT - 166 - HEIGHT_BETWEEN_LEVELS)
    {
        return 1;
    }
    //THIRD LEVEL LADDER MIDDLE
    else if (x <= SCREEN_WIDTH / 2 + 25 && x >= SCREEN_WIDTH / 2 && y <= SCREEN_HEIGHT - 174 && y >= SCREEN_HEIGHT - 231)
    {
        return 1;
    }
    //FOURTH LEVEL LADDER LEFT
    else if (x <= 150 && x >= 130 && y <= SCREEN_HEIGHT - 166 - HEIGHT_BETWEEN_LEVELS - 14 && y >= SCREEN_HEIGHT - 166 - HEIGHT_BETWEEN_LEVELS * 2 - 1)
    {
        return 1;
    }
    //FOURTH LEVEL LADDER MIDDLE
    else if (x <= 260 && x >= 240 && y <= SCREEN_HEIGHT - 235 && y >= SCREEN_HEIGHT - 289)
    {
        return 1;
    }
    //FIFTH LEVEL LADDER RIGHT
    else if (x <= SCREEN_WIDTH - 130 && x >= SCREEN_WIDTH - 150 && y <= SCREEN_HEIGHT - 166 - HEIGHT_BETWEEN_LEVELS * 2 - 15 && y >= SCREEN_HEIGHT - 166 - HEIGHT_BETWEEN_LEVELS * 3 - 1)
    {
        return 1;
    }
    //SIXTH LEVEL LADDER MIDDLE
    else if (x <= SCREEN_WIDTH / 2 + 65 && x >= SCREEN_WIDTH / 2 + 45 && y <= SCREEN_HEIGHT - 166 - HEIGHT_BETWEEN_LEVELS * 3 - 7 && y >= SCREEN_HEIGHT - 166 - HEIGHT_BETWEEN_LEVELS * 3 - 56)
    {
        return 1;
    }

    else
    {
        return 0;
    }
}

int Check_if_on_top_ladder(int x, int y)
{
    //FIRST LEVEL RIGHT BOTTOM LADDER
    if (x <= SCREEN_WIDTH - 130 && x >= SCREEN_WIDTH - 150 && y <= SCREEN_HEIGHT - 107 + MOVEMENT_SPEED && y > SCREEN_HEIGHT - 107 - MOVEMENT_SPEED * 2)
    {
        return 1;
    }
    //SECOND LEVEL LEFT LADDER 
    else if (x <= 150 && x >= 130 && y <= SCREEN_HEIGHT - 166 + MOVEMENT_SPEED && y > SCREEN_HEIGHT - 166 - MOVEMENT_SPEED * 2)
    {
        return 1;
    }
    //SECOND LEVEL LADDER MIDDLE 305 -> 330   364 -> 278
    else if (x <= SCREEN_WIDTH - 360 && x >= SCREEN_WIDTH - 385 && y <= SCREEN_HEIGHT - 173 + MOVEMENT_SPEED && y >= SCREEN_HEIGHT - 173 - MOVEMENT_SPEED * 2)
    {
        return 1;
    }
    //THIRD LEVEL RIGHT LEVEL
    else if (x <= SCREEN_WIDTH - 130 && x >= SCREEN_WIDTH - 150 && y <= SCREEN_HEIGHT - 166 - HEIGHT_BETWEEN_LEVELS + MOVEMENT_SPEED && y >= SCREEN_HEIGHT - 166 - HEIGHT_BETWEEN_LEVELS - MOVEMENT_SPEED * 2)
    {
        return 1;
    }
    //THIRD LEVEL MIDDLE LADDER
    else if (x <= SCREEN_WIDTH / 2 + 25 && x >= SCREEN_WIDTH / 2 && y <= SCREEN_HEIGHT - 231 + MOVEMENT_SPEED && y >= SCREEN_HEIGHT - 231 - MOVEMENT_SPEED * 2)
    {
        return 1;
    }
    //FOURTH LEVEL LEFT LADDER
    else if (x <= 150 && x >= 130 && y <= SCREEN_HEIGHT - 166 - HEIGHT_BETWEEN_LEVELS * 2 + MOVEMENT_SPEED && y >= SCREEN_HEIGHT - 166 - HEIGHT_BETWEEN_LEVELS * 2 - MOVEMENT_SPEED * 2)
    {
        return 1;
    }
    //FOURTH LEVEL LADDER MIDDLE
    else if (x <= 260 && x >= 240 && y <= SCREEN_HEIGHT - 289 + MOVEMENT_SPEED && y >= SCREEN_HEIGHT - 289 - MOVEMENT_SPEED * 2)
    {
        return 1;
    }
    //FIFTH LEVEL LADDER RIGHT
    else if (x <= SCREEN_WIDTH - 130 && x >= SCREEN_WIDTH - 150 && y <= SCREEN_HEIGHT - 166 - HEIGHT_BETWEEN_LEVELS * 3 + MOVEMENT_SPEED && y >= SCREEN_HEIGHT - 166 - HEIGHT_BETWEEN_LEVELS * 3 - 1 - MOVEMENT_SPEED * 2)
    {
        return 1;
    }
    //SIXTH LEVEL LADDER MIDDLE
    else if (x <= SCREEN_WIDTH / 2 + 65 && x >= SCREEN_WIDTH / 2 + 45 && y <= SCREEN_HEIGHT - 166 - HEIGHT_BETWEEN_LEVELS * 3 - 56 + MOVEMENT_SPEED && y >= SCREEN_HEIGHT - 166 - HEIGHT_BETWEEN_LEVELS * 3 - 56 - MOVEMENT_SPEED * 2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int Check_if_on_bottom_ladder(int x, int y)
{

    //FIRST LEVEL RIGHT BOTTOM LADDER
    if (x <= SCREEN_WIDTH - 130 && x >= SCREEN_WIDTH - 150 && y >= SCREEN_HEIGHT - 59 - MOVEMENT_SPEED && y <= SCREEN_HEIGHT - 59 + MOVEMENT_SPEED)
    {
        return 1;
    }
    //SECOND LEVEL LEFT LADDER 
    else if (x <= 150 && x >= 130 && y >= SCREEN_HEIGHT - 120 - MOVEMENT_SPEED && y <= SCREEN_HEIGHT - 120 + MOVEMENT_SPEED)
    {
        return 1;
    }
    //SECOND LEVEL LADDER MIDDLE 305 -> 330   364 -> 278
    else if (x <= SCREEN_WIDTH - 360 && x >= SCREEN_WIDTH - 385 && y >= SCREEN_HEIGHT - 111 - MOVEMENT_SPEED * 2 && y <= SCREEN_HEIGHT - 111 + MOVEMENT_SPEED * 2)
    {
        return 1;
    }
    //THIRD LEVEL RIGHT LEVEL
    else if (x <= SCREEN_WIDTH - 130 && x >= SCREEN_WIDTH - 150 && y >= SCREEN_HEIGHT - 180 - MOVEMENT_SPEED && y <= SCREEN_HEIGHT - 180 + MOVEMENT_SPEED)
    {
        return 1;
    }
    //THIRD LEVEL LADDER MIDDLE
    else if (x <= SCREEN_WIDTH / 2 + 25 && x >= SCREEN_WIDTH / 2 && y >= SCREEN_HEIGHT - 174 - MOVEMENT_SPEED && y <= SCREEN_HEIGHT - 174 + MOVEMENT_SPEED)
    {
        return 1;
    }
    //FOURTH LEVEL LEFT LADDER
    else if (x <= 150 && x >= 130 && y >= SCREEN_HEIGHT - 180 - HEIGHT_BETWEEN_LEVELS - MOVEMENT_SPEED * 2 && y <= SCREEN_HEIGHT - 166 - HEIGHT_BETWEEN_LEVELS + MOVEMENT_SPEED)
    {
        return 1;
    }
    //FOURTH LEVEL LADDER MIDDLE
    else if (x <= 260 && x >= 240 && y >= SCREEN_HEIGHT - 235 - MOVEMENT_SPEED && y <= SCREEN_HEIGHT - 235 + MOVEMENT_SPEED)
    {
        return 1;
    }
    //FIFTH LEVEL LADDER RIGHT
    else if (x <= SCREEN_WIDTH - 130 && x >= SCREEN_WIDTH - 150 && y >= SCREEN_HEIGHT - 180 - HEIGHT_BETWEEN_LEVELS * 2 - MOVEMENT_SPEED * 2 && y <= SCREEN_HEIGHT - 180 - HEIGHT_BETWEEN_LEVELS * 2 + MOVEMENT_SPEED * 2)
    {
        return 1;
    }
    //SIXTH LEVEL LADDER MIDDLE
    else if (x <= SCREEN_WIDTH / 2 + 65 && x >= SCREEN_WIDTH / 2 + 45 && y >= SCREEN_HEIGHT - 166 - HEIGHT_BETWEEN_LEVELS * 3 - 7 - MOVEMENT_SPEED && y <= SCREEN_HEIGHT - 166 - HEIGHT_BETWEEN_LEVELS * 3 - 7 + MOVEMENT_SPEED)
    {
        return 1;
    }

    else
    {
        return 0;
    }
}

int CheckFloorColision(SDL_Surface* map, int x, int y) {
    Uint32 pixel = GetPixel(map, x, y);
    Uint8 r, g, b;
    SDL_GetRGB(pixel, map->format, &r, &g, &b);
    int red = 79, green = 23, blue = 34;
    int possible_mistake = 40;
    if (abs(r - red) <= possible_mistake && abs(g - green) <= possible_mistake && abs(b - blue) <= possible_mistake) {
        return 1;
    }
    return 0;
}

int CheckBarrelCollision(int Barrel_x, int Barrel_y, int mario_x, int mario_y, int Barrel2_x, int Barrel2_y) {

    if (Barrel_x >= mario_x - 5 && Barrel_x <= mario_x + 5 && Barrel_y >= mario_y - 10 && Barrel_y <= mario_y + 10) {
        return 1;
    }
    else if (Barrel2_x >= mario_x - 5 && Barrel2_x <= mario_x + 5 && Barrel2_y >= mario_y - 10 && Barrel2_y <= mario_y + 10) {
        return 1;
    }
    return 0;
}

void StartingPosition(Mario& mario, Timer& timer, Barrel& barrel, Images& images, int* POINTS, Barrel2& barrel2)
{
    mario.mario_x = MARIO_STARTING_POSITION_X;
    mario.mario_y = MARIO_STARTING_POSITION_Y;
    timer.worldTime = 0;
    mario.direction = RIGHT;
    barrel.Barrel_x = BARREL_STARTING_POSITION_X;
    barrel.Barrel_y = BARREL_STARTING_POSITION_Y;
    barrel2.Barrel_x = BARREL_STARTING_POSITION_X;
    barrel2.Barrel_y = BARREL_STARTING_POSITION_Y;
    *POINTS = 0;
}

void Win(Mario* mario, Barrel* barrel, Surface* surface, Images* images, Timer* timer, int czarny, int* POINTS, char* text, int* current_level, Barrel2& barrel2) {
    if (mario->mario_y <= SCREEN_HEIGHT - 166 - HEIGHT_BETWEEN_LEVELS * 3 - 75) {
        mario->mario_x = MARIO_STARTING_POSITION_X;
        mario->mario_y = MARIO_STARTING_POSITION_Y;
        mario->direction = RIGHT;
        barrel->Barrel_x = BARREL_STARTING_POSITION_X;
        barrel->Barrel_y = BARREL_STARTING_POSITION_Y;
        barrel2.Barrel_x = BARREL_STARTING_POSITION_X;
        barrel2.Barrel_y = BARREL_STARTING_POSITION_Y;
        SDL_FillRect(surface->screen, NULL, czarny);
        sprintf(text, "YOU WON!!!");
        DrawString(surface->screen, SCREEN_WIDTH / 2 - 40, SCREEN_HEIGHT / 2, text, images->charset);
        *POINTS += 1000;
        *current_level = STARTING_MARIO_LEVEL;
        sprintf(text, "POINTS: %06d", *POINTS);
        DrawString(surface->screen, SCREEN_WIDTH / 2 - 60, SCREEN_HEIGHT / 2 + 10, text, images->charset);
        SDL_UpdateTexture(surface->scrtex, NULL, surface->screen->pixels, surface->screen->pitch);
        SDL_RenderCopy(surface->renderer, surface->scrtex, NULL, NULL);
        SDL_RenderPresent(surface->renderer);
        SDL_Delay(3000);
        int delay = 3;
        timer->worldTime = 0;
        timer->worldTime -= 3;
    }
}

void Dead(Mario* mario, Barrel* barrel, Surface* surface, Images* images, Timer* timer, int czarny, int* POINTS, char* text, Barrel2& barrel2)
{
    if (CheckBarrelCollision(barrel->Barrel_x, barrel->Barrel_y, mario->mario_x, mario->mario_y, barrel2.Barrel_x, barrel2.Barrel_y) == 1)
    {
        mario->mario_x = MARIO_STARTING_POSITION_X;
        mario->mario_y = MARIO_STARTING_POSITION_Y;
        mario->direction = RIGHT;
        barrel->Barrel_x = BARREL_STARTING_POSITION_X;
        barrel->Barrel_y = BARREL_STARTING_POSITION_Y;
        barrel2.Barrel_x = BARREL_STARTING_POSITION_X;
        barrel2.Barrel_y = BARREL_STARTING_POSITION_Y;
        SDL_FillRect(surface->screen, NULL, czarny);
        sprintf(text, "YOU DIED :(");
        DrawString(surface->screen, SCREEN_WIDTH / 2 - 60, SCREEN_HEIGHT / 2 + 10, text, images->charset);
        *POINTS -= 500;
        sprintf(text, "-500");
        DrawString(surface->screen, SCREEN_WIDTH / 2 - 40, SCREEN_HEIGHT / 2 + 20, text, images->charset);
        SDL_UpdateTexture(surface->scrtex, NULL, surface->screen->pixels, surface->screen->pitch);
        SDL_RenderCopy(surface->renderer, surface->scrtex, NULL, NULL);
        SDL_RenderPresent(surface->renderer);
        SDL_Delay(3000);
        int delay = 3;
        timer->worldTime = 0;
        timer->worldTime -= 3;
    }
}

void UpdateTextures(Mario* mario, Barrel* barrel, Surface* surface, Images* images, Barrel2* barrel2, Timer* timer)
{
    DrawSurface(surface->screen, images->map, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    DrawSurface(surface->screen, barrel->current_image, barrel->Barrel_x, barrel->Barrel_y);
    if (timer->worldTime > 16) { DrawSurface(surface->screen, barrel2->current_image, barrel2->Barrel_x, barrel2->Barrel_y); }
    DrawSurface(surface->screen, mario->current_image, mario->mario_x, mario->mario_y);
}

void Mario_position(Mario& mario, Images& images)
{
    if ((mario.direction == RIGHT || mario.direction == LEFT) && !mario.jumping)
    {
        for (int i = 0; i < 6; i++)
        {
            if (CheckFloorColision(images.map, mario.mario_x, mario.mario_y + 15) != 1 && CheckCollision_ladder(mario.mario_x, mario.mario_y + 15) != 1)
            {

                if (mario.level % 2 == 1 && mario.direction == RIGHT) { mario.mario_y -= 1; }
                else if (mario.level % 2 == 1 && mario.direction == LEFT) { mario.mario_y += 1; }
                else if (mario.level % 2 == 0 && mario.direction == RIGHT) { mario.mario_y += 1; }
                else if (mario.level % 2 == 0 && mario.direction == LEFT) { mario.mario_y -= 1; }


            }
        }
    }
}

void Jump(Mario& mario, Timer& timer, Barrel& barrel, Images& images, int* POINTS, Barrel2& barrel2) {
    int current_points = *POINTS;

    if (timer.jump_time - mario.lastJumpTime >= 1 && mario.jumping) {
        if (mario.mario_y > mario.mario_y_before_jump - JUMP_HEIGHT && !mario.up) {
            mario.mario_y -= 5;
            mario.current_image = images.mario_jump;
            *POINTS += point_counter(barrel.Barrel_x, barrel.Barrel_y, mario.mario_x, mario.mario_y, mario.level, barrel.barrel_level, barrel2.Barrel_x, barrel2.Barrel_y, barrel2.barrel_level);
        }
        else if (mario.mario_y < mario.mario_y_before_jump) {
            mario.up = true;
            mario.mario_y += 5;
            mario.current_image = images.mario_jump;
            if (current_points == *POINTS) {
                *POINTS += point_counter(barrel.Barrel_x, barrel.Barrel_y, mario.mario_x, mario.mario_y, mario.level, barrel.barrel_level, barrel2.Barrel_x, barrel2.Barrel_y, barrel2.barrel_level);
            }
        }
        else {
            mario.jumping = false;
            mario.up = false;
        }
        mario.lastJumpTime = timer.jump_time;
    }
}

void Items(bool* taken_1_item, Surface& surface, Images& images, Mario& mario, int* POINTS, bool* taken_2_item)
{
    if (!*taken_1_item) { DrawSurface(surface.screen, images.item, SCREEN_WIDTH / 2 - 30, SCREEN_HEIGHT / 2 + 1); }
    if (!*taken_2_item) { DrawSurface(surface.screen, images.item2, SCREEN_WIDTH - 250, SCREEN_HEIGHT / 3 + 20); }
    if (!*taken_2_item && mario.mario_x >= SCREEN_WIDTH - 250 && mario.mario_x <= SCREEN_WIDTH - 245 && mario.mario_y <= SCREEN_HEIGHT / 3 + 20 && mario.mario_y >= SCREEN_HEIGHT / 3 + 10)
    {
        *POINTS += 800;
        *taken_2_item = true;
        SDL_FreeSurface(images.item2);

    }
    if (!*taken_1_item && mario.mario_x >= SCREEN_WIDTH / 2 - 30 && mario.mario_x <= SCREEN_WIDTH / 2 - 25 && mario.mario_y <= SCREEN_HEIGHT / 2 + 1 && mario.mario_y >= SCREEN_HEIGHT / 2 - 9)
    {
        *POINTS += 800;
        *taken_1_item = true;
        SDL_FreeSurface(images.item);
    }
}

void Barrel1Movement(Timer& timer, Barrel& barrel, Images& images)
{
    barrel.movement = Barrel_move(barrel.barrel_level);

    if (timer.barrel_time - barrel.lastBarrelMoveTime >= 1) {
        barrel.Barrel_x += barrel.movement;

        barrel.lastBarrelMoveTime = timer.barrel_time;
    }
    if (int(timer.barrel_time) % 3 == 0)
    {
        barrel.current_image = images.barrel_2;
    }
    else
    {
        barrel.current_image = images.barrel;
    }
}

void Barrel2Movement(Timer& timer, Barrel2& barrel2, Images& images)
{
    barrel2.movement = Barrel_move(barrel2.barrel_level);
    if (timer.barrel2_time - barrel2.lastBarrel2MoveTime >= 1 && timer.worldTime > 16) {
        barrel2.Barrel_x += barrel2.movement;

        barrel2.lastBarrel2MoveTime = timer.barrel2_time;
    }
    if (int(timer.barrel2_time) % 3 == 0)
    {
        barrel2.current_image = images.barrel;
    }
    else
    {
        barrel2.current_image = images.barrel_2;
    }
}

void BarrelRespawnAgain(Barrel& barrel, Barrel2& barrel2)
{
    if (barrel.Barrel_x <= MARIO_STARTING_POSITION_X)
    {
        barrel.Barrel_x = BARREL_STARTING_POSITION_X;
        barrel.Barrel_y = BARREL_STARTING_POSITION_Y;
    }

    if (barrel2.Barrel_x <= MARIO_STARTING_POSITION_X)
    {
        barrel2.Barrel_x = BARREL_STARTING_POSITION_X;
        barrel2.Barrel_y = BARREL_STARTING_POSITION_Y;
    }
}

void LevelPoints(Mario& mario, int* current_level, int* POINTS)
{
    mario.level = Mario_level(mario.mario_y);
    if (mario.level > *current_level)
    {
        *POINTS += 300;
        (*current_level)++;
    }
}

void BarrelCurrentLevel(Barrel& barrel, Barrel2& barrel2)
{
    barrel.barrel_level = Barrel_level(barrel.Barrel_y);
    barrel2.barrel_level = Barrel_level(barrel2.Barrel_y);
}

void BarrelFloorCollision(Barrel& barrel, Barrel2& barrel2, Images& images)
{
    if (CheckFloorColision(images.map, barrel.Barrel_x, barrel.Barrel_y + 10) != 1) { barrel.Barrel_y += 1; }
    if (CheckFloorColision(images.map, barrel2.Barrel_x, barrel2.Barrel_y + 10) != 1) { barrel2.Barrel_y += 1; }
}

void CurrentMarioImage(Mario& mario, Images& images)
{
    mario.current_image = Mario_image(mario.direction, images.imageStanding_flipped, images.mario_ladder, images.imageStanding, images.mario_jump, mario.jumping, images.mario_jump_flip);
}

void Keys(Game& game, Timer& timer, Surface& surface, Mario& mario, Barrel& barrel, Barrel2& barrel2, int* POINTS, Images& images, int* current_level)
{

    double deltaTime = TimerFunction(timer);
    while (SDL_PollEvent(&surface.event) != 0) {
        if (surface.event.type == SDL_QUIT) {
            game.quit = true;
        }
        else if (!game.gameStarted && surface.event.key.keysym.sym == SDLK_SPACE)
        {
            game.gameStarted = true;
            timer.worldTime = 0;
        }
        else if (game.gameStarted && surface.event.type == SDL_KEYDOWN) {
            switch (surface.event.key.keysym.sym) {
            case SDLK_UP:

                if (CheckCollision_ladder(mario.mario_x, mario.mario_y + LENGTH_TO_BOTTOM_MARIO) == 1) {

                    if (Check_if_on_top_ladder(mario.mario_x, mario.mario_y + LENGTH_TO_BOTTOM_MARIO) == 1)
                    {
                        mario.mario_y -= MOVEMENT_SPEED;
                        if (mario.level % 2 == 0) { mario.direction = RIGHT; }
                        else { mario.direction = LEFT; }
                    }
                    else
                    {
                        mario.direction = CLIMBING;
                        mario.mario_y -= MOVEMENT_SPEED;
                    }
                }
                break;
            case SDLK_DOWN:
                if (CheckCollision_ladder(mario.mario_x, mario.mario_y + LENGTH_TO_BOTTOM_MARIO) == 1) {

                    if (Check_if_on_bottom_ladder(mario.mario_x, mario.mario_y + LENGTH_TO_BOTTOM_MARIO) == 1)
                    {

                        mario.mario_y += MOVEMENT_SPEED;
                        if (mario.level % 2 == 0) { mario.direction = LEFT; }
                        else { mario.direction = RIGHT; }

                    }
                    else
                    {
                        mario.direction = CLIMBING;
                        mario.mario_y += MOVEMENT_SPEED;
                    }
                }

                break;
            case SDLK_LEFT:
                if (can_go_left(mario.level, mario.mario_x) && mario.direction != CLIMBING) { mario.mario_x -= MOVEMENT_SPEED; mario.direction = LEFT; }
                break;
            case SDLK_RIGHT:
                if (can_go_right(mario.level, mario.mario_x) && mario.direction != CLIMBING) { mario.mario_x += MOVEMENT_SPEED; mario.direction = RIGHT; }
                break;
            case SDLK_SPACE:
                if (!mario.jumping) {
                    mario.jumping = true;
                    mario.mario_y_before_jump = mario.mario_y;
                }
                break;
            case SDLK_n:
                StartingPosition(mario, timer, barrel, images, POINTS, barrel2);
                *current_level = 1;
                break;
            case SDLK_ESCAPE:
                game.quit = true;
                break;
            }
        }
    }
}


void StartedGame(Game& game, Timer& timer, Surface& surface, Mario& mario, Barrel& barrel, Barrel2& barrel2, int* POINTS, Images& images, int* current_level, Colors& color, bool* taken_1_item, bool* taken_2_item, char* text)
{

    Dead(&mario, &barrel, &surface, &images, &timer, color.czarny, POINTS, text, barrel2);// if mario was hit displays it
    Win(&mario, &barrel, &surface, &images, &timer, color.czarny, POINTS, text, current_level, barrel2); //if mario is on top displays a win
    LevelPoints(mario, current_level, POINTS); //add points when mario discover new level
    BarrelCurrentLevel(barrel, barrel2); //changes current barrel level
    Mario_position(mario, images); //adjusts position of mario (y)
    BarrelFloorCollision(barrel, barrel2, images);//adjust position  of falling barrel and makes sure that barrel touches floor
    BarrelRespawnAgain(barrel, barrel2);// respawns barrel when they hit the end of the map
    Jump(mario, timer, barrel, images, POINTS, barrel2);//handles mario jumping
    Barrel1Movement(timer, barrel, images);//adjust first barrel movement
    Barrel2Movement(timer, barrel2, images);//adjust second barrel movement
    UpdateTextures(&mario, &barrel, &surface, &images, &barrel2, &timer);//updates textures on the screen
    Items(taken_1_item, surface, images, mario, POINTS, taken_2_item);//respawn and despawn items on the platforms
    Draw_Menu(surface.screen, mario.mario_x, mario.mario_y, images.charset, color.niebieski, timer, text, POINTS);//draws thw whole menu
    CurrentMarioImage(mario, images);//changes current mario image

}

int main(int argc, char** argv) {
    Surface surface; // Structure for surface scrtx and window
    Images images; // Structure for every image on the screen
    Mario mario; // Structure for mario(player)
    Game game; // structure for game things
    Barrel barrel; // structure for the fisrt barrel
    Barrel2 barrel2; // structure for the second barrel
    Timer timer; // structure for everything which includes time
    Colors color; // structure for 4 colors
    Init_Game(surface, barrel, barrel2, images, mario);
    InitColors(&color, &surface);
    int current_level = STARTING_MARIO_LEVEL, POINTS = 0;
    bool taken_1_item = false, taken_2_item = false;
    char text[128]; //holds text displayed on the screen (menu)
    if (surface.window == nullptr || surface.renderer == nullptr) {
        fprintf(stderr, "Error creating window/renderer: %s\n", SDL_GetError());
        return -1;
    }
    else {
        while (!game.quit) {
            Keys(game, timer, surface, mario, barrel, barrel2, &POINTS, images, &current_level); // handles keyboard pressed keys
            if (game.gameStarted)
            {
                //game function
                StartedGame(game, timer, surface, mario, barrel, barrel2, &POINTS, images, &current_level, color, &taken_1_item, &taken_2_item, text);
            }
            else
            {
                //draws strting screen when game does not start
                Draw_StartScreen(surface.screen, images.Start, images.kong1, images.charset, text);
            }
            updateAndRender(surface.screen, surface.scrtex, surface.renderer);//updates textures and render them
        }
        FreeAndDestroy(images.charset, surface.screen, images.imageStanding, surface.scrtex);//destroys textures at the end of the program
    }

    SDL_DestroyRenderer(surface.renderer);//destroys renderer
    SDL_DestroyWindow(surface.window);//destroys window
    SDL_Quit();
    return 0;
}