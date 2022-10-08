
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
    try
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
    catch (bad_alloc& ex)
    {
        cout << ex.what();
    }
}

void Texture::loadFromRenderedText( TTF_Font * font, std::string textureText, SDL_Color textColor , SDL_Renderer * renderer)
{
    SDL_Texture * new_texture = NULL;
    SDL_Surface* textSurface = TTF_RenderText_Solid( font, textureText.c_str(), textColor );
	if( textSurface == NULL )
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        new_texture = SDL_CreateTextureFromSurface( renderer, textSurface );
		if( new_texture == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get image dimensions

            width.push_back(textSurface->w);
            height.push_back(textSurface->h);
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
      
	}
    texture.push_back(new_texture);


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


///////////////////////////////

void Texture::setBlendMode(int i, SDL_BlendMode blending )
{
	//Set blending function
	SDL_SetTextureBlendMode( texture.at(i), blending );
}

void Texture::setAlpha(int i, Uint8 alpha)
{
    SDL_SetTextureAlphaMod( texture.at(i), alpha );
}
////////////////////////////


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

float Texture::setX(int i, int number)
{
    x.at(i) = number;
}
float Texture::setY(int i, int number)
{
    y.at(i) = number;
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

void Texture::render1part(int i, SDL_Renderer *ren, int x, int y, int w, int h)
{
    SDL_Rect dst;
	dst.x = x;
	dst.y = y;
    dst.w = w;
    dst.h = h;
	//Truy vẫn texture để lấy chiều rộng và cao (vào chiều rộng và cao tương ứng của hình chữ nhật đích)
	// SDL_QueryTexture(texture.at(i), NULL, NULL, &dst.w, &dst.h);
    //Đưa toàn bộ ảnh trong texture vào hình chữ nhật đích

    // SDL_Rect src;
    // src.x = x;
    // src.y = y; 
    // src.h = h;
    // src.w = w;

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