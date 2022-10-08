// #include "Texture.h"

// using namespace std;

// void Texture::logSDLError(ostream& os, const string &msg, bool fatal)
// {
//     os << msg << " Error: " << IMG_GetError() << endl;
//     if (fatal)
//     {
//         IMG_Quit();
//         SDL_Quit();
//         exit(1);
//     }
// }

// void Texture::free()
// {
//     if(texture != NULL)
//     {
//         SDL_DestroyTexture(texture);
//         texture = NULL;
//     }
// }

// void Texture::loadFromFile(string path, SDL_Renderer* renderer)
// {
//     SDL_Texture* new_texture = NULL;
//     SDL_Surface* loaded_surface = IMG_Load( path.c_str() );

//     if( loaded_surface == NULL )
//     {
//         logSDLError(cout, "IMG_load", true);
//     }
//     else
//     {
//         SDL_SetColorKey( loaded_surface, SDL_TRUE, SDL_MapRGB( loaded_surface->format, 0x00, 0xFF, 0xFF ) );
//         new_texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
//         if( new_texture == NULL )
//         {
//             logSDLError(cout, "SDL_CreateTextureFromSurface", true);
//         }
//         else
//         {
//             texture = new_texture;
//         }

//         SDL_FreeSurface(loaded_surface);
//     }

//     new_texture = NULL;
    
// }

// void Texture::loadPNGTexture(string path, SDL_Renderer * renderer, bool delete_font )
// {
//     //free();
//     SDL_Texture *new_texture = nullptr;
//     SDL_Surface* new_surface = IMG_Load(path.c_str());
//     SDL_SetColorKey(new_surface, (delete_font == true ? SDL_TRUE : SDL_FALSE), SDL_MapRGB( new_surface->format, 255, 255, 255 ));
//     if (new_surface != 0)
//     {
//         new_texture = SDL_CreateTextureFromSurface(renderer, new_surface );
//         SDL_FreeSurface(new_surface);

//         if (new_texture == nullptr)
//         {
//             logSDLError(cout, "bug in creat stage", true);
//         }

//     }
//     else
//         logSDLError(cout, "found in creat Texture stage", true);

//     texture = new_texture;
//     new_texture = NULL;

//     //The final texture
//     // SDL_Texture* newTexture = NULL;

//     // //Load image at specified path
//     // SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
//     // if( loadedSurface == NULL )
//     // {
//     //     printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
//     // }
//     // else
//     // {
//     //     //Create texture from surface pixels
//     //     newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
//     //     if( newTexture == NULL )
//     //     {
//     //         printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
//     //     }

//     //     //Get rid of old loaded surface
//     //     SDL_FreeSurface( loadedSurface );
//     // }
//     // texture = newTexture;

// }

// void Texture::loadFromRenderedText( TTF_Font * font, std::string textureText, SDL_Color textColor, SDL_Renderer * renderer )
// {
// 	//Get rid of preexisting texture
// 	//free();

// 	//Render text surface
// 	SDL_Surface* textSurface = TTF_RenderText_Solid( font, textureText.c_str(), textColor );
// 	if( textSurface == NULL )
// 	{
// 		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
// 	}
// 	else
// 	{
// 		//Create texture from surface pixels
//         texture = SDL_CreateTextureFromSurface( renderer, textSurface );
// 		if( texture == NULL )
// 		{
// 			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
// 		}
// 		else
// 		{
// 			//Get image dimensions
// 			width = textSurface->w;
// 			height = textSurface->h;
// 		}

// 		//Get rid of old surface
// 		SDL_FreeSurface( textSurface );
// 	}
	
// 	//Return success
	
// }

// void Texture::renderTexture(SDL_Renderer *ren, int x, int y)
// {
//     SDL_Rect dst;
// 	dst.x = x;
// 	dst.y = y;
// 	//Truy vẫn texture để lấy chiều rộng và cao (vào chiều rộng và cao tương ứng của hình chữ nhật đích)
// 	SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
//     //Đưa toàn bộ ảnh trong texture vào hình chữ nhật đích
// 	SDL_RenderCopy(ren, texture, NULL, &dst);
// }

// void Texture::renderTexture( SDL_Renderer *ren, int x, int y, int w, int h)
// {
// 	//Thiết lập hình chữ nhật đích mà chúng ta muốn vẽ ảnh vào trong
// 	SDL_Rect dst;
// 	dst.x = x;
// 	dst.y = y;
//     dst.w = w;
//     dst.h = h;
//     //Đưa toàn bộ ảnh trong texture vào hình chữ nhật đích
//     //(ảnh sẽ co dãn cho khớp với kích cỡ mới)
// 	SDL_RenderCopy(ren, texture, NULL, &dst);
// }

// void Texture::render( SDL_Renderer * renderer, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
// {
// 	//Set rendering space and render to screen
// 	SDL_Rect renderQuad = { x, y, width, height };

// 	//Set clip rendering dimensions
// 	if( clip != NULL )
// 	{
// 		renderQuad.w = clip->w;
// 		renderQuad.h = clip->h;
// 	}

// 	//Render to screen
// 	SDL_RenderCopyEx( renderer, texture, clip, &renderQuad, angle, center, flip );
// }

// void Texture::setColor(Uint8 red, Uint8 green, Uint8 blue )
// {
//     SDL_SetTextureColorMod( texture, red, green, blue );
// }

// int Texture::getX()
// {
//     return x;
// }

// int Texture::getY()
// {
//     return y;
// }

// int Texture::getWidth()
// {
//     return width;
// }

// int Texture::getHeight()
// {
//     return height;
// }



#include "Texture.h"

using namespace std;

void Texture::logSDLError(ostream& os, const string &msg, bool fatal)
{
    os << msg << " Error: " << IMG_GetError() << endl;
    if (fatal)
    {
        IMG_Quit();
        SDL_Quit();
        exit(1);
    }
}

void Texture::free(SDL_Texture* texture)
{
    if(texture != NULL)
    {
        SDL_DestroyTexture(texture);
        texture = NULL;
    }
}

void Texture::loadFromFile(string path, SDL_Renderer* renderer)
{
    SDL_Texture* new_texture = NULL;
    SDL_Surface* loaded_surface = IMG_Load( path.c_str() );

    if( loaded_surface == NULL )
    {
        logSDLError(cout, "IMG_load", true);
    }
    else
    {
        SDL_SetColorKey( loaded_surface, SDL_TRUE, SDL_MapRGB( loaded_surface->format, 0x00, 0xFF, 0xFF ) );
        new_texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
        if( new_texture == NULL )
        {
            logSDLError(cout, "SDL_CreateTextureFromSurface", true);
        }
        else
        {
            width.push_back(loaded_surface->w);
            height.push_back(loaded_surface->h);
        }

        SDL_FreeSurface(loaded_surface);
    }

     texture.push_back(new_texture);
     new_texture = NULL;
}

void Texture::render(int i, int x, int y, SDL_Renderer* renderer, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	//Truy vẫn texture để lấy chiều rộng và cao (vào chiều rộng và cao tương ứng của hình chữ nhật đích)
	SDL_QueryTexture(texture.at(i), NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopyEx(renderer, texture.at(i), NULL, &dst, angle, center, flip);
}

void Texture::setColor(const int &i, Uint8 red, Uint8 green, Uint8 blue )
{
    SDL_SetTextureColorMod( texture.at(i), red, green, blue );
}

float Texture::getX(int i)
{
    return x.at(i);
}

float Texture::getY(int i)
{
    return y.at(i);
}

int Texture::getWidth(int i)
{
    return width.at(i);
}

int Texture::getHeight(int i)
{
    return height.at(i);
}

void Texture::renderTexture(int i, SDL_Renderer *ren, int x, int y)
{
    SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	//Truy vẫn texture để lấy chiều rộng và cao (vào chiều rộng và cao tương ứng của hình chữ nhật đích)
	SDL_QueryTexture(texture.at(i), NULL, NULL, &dst.w, &dst.h);
    //Đưa toàn bộ ảnh trong texture vào hình chữ nhật đích
	SDL_RenderCopy(ren, texture.at(i), NULL, &dst);
}

vector<SDL_Texture*> Texture::getTexture() {
    return texture;
}


bool checkCollision(int y)
{ 
    if (y > 450)
        return true;
    return false;
}