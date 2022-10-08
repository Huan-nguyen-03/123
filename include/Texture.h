// #pragma once

// #include <iostream>
// #include "SDL2/SDL_image.h"
// #include "SDL2/SDL_ttf.h"

// using namespace std;

// class Texture
// {
// public:
//     void logSDLError(ostream& os, const string &msg, bool fatal);                               //hàm báo lỗi
//     void free();                                                                    //hàm giải phóng tài nguyên
//     void loadFromFile(string path, SDL_Renderer*); 
//     void loadPNGTexture(string path, SDL_Renderer * Renderer, bool delete_font );

//     void loadFromRenderedText( TTF_Font * font, std::string textureText, SDL_Color textColor , SDL_Renderer * renderer);

//     void renderTexture(SDL_Renderer *, int , int );
//     void renderTexture(SDL_Renderer *, int , int , int , int );

//     void render( SDL_Renderer * renderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

//     void setColor( Uint8 red, Uint8 green, Uint8 blue);


//     int getWidth();
//     int getHeight();
//     int getX();
//     int getY();
// protected:

//     int width, height;
//     int x, y;
//     SDL_Texture * texture;

 
// private:
    

// };


#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"


using namespace std;

//đây là base class cho mấy cái class kia
class Texture
{
public:
    void logSDLError(ostream& os, const string &msg, bool fatal);                               //hàm báo lỗi
    void free(SDL_Texture*);                                                                    //hàm giải phóng tài nguyên
    void loadFromFile(string path, SDL_Renderer*);                                              //hàm load file ảnh

    void loadFromRenderedText( TTF_Font * font, std::string textureText, SDL_Color textColor , SDL_Renderer * renderer);

    void renderTexture(int i, SDL_Renderer *ren, int x, int y);
    void render(int, int, int, SDL_Renderer*, double, SDL_Point*, SDL_RendererFlip);  //hàm render (dùng đc trong mọi điều kiện)
    void render1part(int i, SDL_Renderer *ren, int x, int y, int w, int h);

    void setColor(const int &i, Uint8 red, Uint8 green, Uint8 blue);
    vector<SDL_Texture*> getTexture();


    void setBlendMode(int i, SDL_BlendMode blending );
    void setAlpha(int i, Uint8 alpha);

    int getWidth(int i);
    int getHeight(int i);
    float getX(int i);
    float getY(int i);

    float setX(int i, int number);
    float setY(int i, int number);
    vector <SDL_Rect> getCollider();

protected:
    vector <int> width, height;
    vector <float> x, y;
    vector <SDL_Texture*> texture;
    
    


private:

};

bool checkCollision(int y);
