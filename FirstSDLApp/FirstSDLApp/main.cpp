#include <SDL.h>
#include "SDL_opengl.h"
#include <stdlib.h>
#include <GL/freeglut.h>
#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
using namespace std;
//#include <SDL_mixer.h>
//#include <SDL_audio.h>



#include "postac.h"
SDL_Surface * ekran = NULL;
SDL_Surface * ludek = NULL;
SDL_Surface * tlo = NULL;
SDL_Surface * butelka = NULL;
SDL_Surface * butelka1 = NULL;
SDL_Surface * ogien = NULL;
SDL_Surface * przycisk = NULL;
SDL_Surface * kursor = NULL;

SDL_Event zdarzenie;

SDL_Rect LudekDestination;
SDL_Rect butelkaDestination;
SDL_Rect butelka1Destination;
SDL_Rect ogienDestination;
SDL_Rect przyciskDane;
SDL_Rect przyciskCel;
SDL_Rect kursorDane;
SDL_Rect butelkaDane;

Uint8 * keystate = SDL_GetKeyState( NULL );

int x, y, xBottle, yBottle, xBottle1, yBottle1, myszkaX, myszkaY;
int kursorX, kursorY;
int bulletx, bullety;
int bulletvx, bulletvy;

bool wyjscie = false;
bool CzyStrzelono = 1;
bool CzyStrzelonoMyszka = 1;


Uint32 start=0, startStrzaluMyszka=0, licznik=0;;

double delta=0, delta1;
double bulletdx, bulletdy;
double deltaX,deltaY;
double dlugosc;
//lvl 1500 800
const int SCREEN_WIDTH = 640; 
const int SCREEN_HEIGHT = 480; 
const int SCREEN_BPP = 32;
const int LEVEL_WIDTH = 1230; 
const int LEVEL_HEIGHT = 640;
const int LUDZIK_WIDTH = 100; 
const int LUDZIK_HEIGHT = 100;

SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
SDL_Rect cameraPomoc = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

SDL_Surface *load_image( std::string filename ) 
{ 
	//The image that's loaded 
	SDL_Surface* loadedImage = NULL; 
	//The optimized image that will be used 
	SDL_Surface* optimizedImage = NULL; 
	//Load the image 
	loadedImage = SDL_LoadBMP( filename.c_str() ); 
	//If the image loaded
	if( loadedImage != NULL ) 
	{ 
		//Create an optimized image 
		optimizedImage = SDL_DisplayFormat( loadedImage ); 
		//Free the old image 
		SDL_FreeSurface( loadedImage );
	//If the image was optimized just fine 
		if( optimizedImage != NULL ) 
		{ 
			//Map the color key 
			Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 255, 255, 255 );
			//Set all pixels of color R 0, G 0xFF, B 0xFF to be transparent 
			SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colorkey );
		}
	//Return the optimized image 
		return optimizedImage;

	}
}



	
int main (int argc, char *argv[])
{

SDL_Init( SDL_INIT_EVERYTHING );
    ekran = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE | SDL_DOUBLEBUF );
	tlo = SDL_LoadBMP( "tlo.bmp" );
    przycisk = SDL_LoadBMP( "przycisk.bmp" );
    /*kursor = SDL_LoadBMP( "kursor.bmp" );
	butelka = SDL_LoadBMP( "butelka.bmp" );
	butelka1 = SDL_LoadBMP( "butelka.bmp" );
	ogien = SDL_LoadBMP( "ogien.bmp" );*/
    
	ludek = load_image("ludek.bmp");
	kursor = load_image("kursor.bmp");
	butelka = load_image( "butelka.bmp" );
	butelka1 = load_image( "butelka.bmp" );
	ogien = load_image( "ogien.bmp" );
	
	przyciskDane.w = 50;
    przyciskDane.h = 50;
	przyciskCel.x = SCREEN_WIDTH-50;
    przyciskCel.y = 0;
    kursorDane.x = 0;
    kursorDane.y = 0;
	
 while( !wyjscie )
    {

		
		//SDL_Delay( ( 1000 / 60) - 10);
		cameraPomoc.x=-2*camera.x;
		cameraPomoc.y=-2*camera.y;
		//SDL_BlitSurface(tlo, NULL, ekran, &camera );

		SDL_FillRect( ekran, NULL, 0 );
		//SDL_BlitSurface( tlo, NULL, ekran, NULL ); przed scrollem
		SDL_BlitSurface(tlo, NULL , ekran, &cameraPomoc);
        SDL_ShowCursor( SDL_DISABLE );
        SDL_BlitSurface( przycisk, & przyciskDane, ekran, & przyciskCel );
        SDL_BlitSurface( kursor, NULL, ekran, & kursorDane );
        SDL_Flip( ekran );
		

		
		while( SDL_PollEvent( & zdarzenie ) )
        {
            if( zdarzenie.type == SDL_QUIT )
            {
                wyjscie = true;
            }

			 if( zdarzenie.type == SDL_MOUSEMOTION )
            {
                kursorDane.x = zdarzenie.motion.x;
                kursorDane.y = zdarzenie.motion.y;
				
            }
            if( zdarzenie.type == SDL_MOUSEBUTTONDOWN )
            {
                if( zdarzenie.button.button == SDL_BUTTON_LEFT &&
                ( kursorDane.x >= przyciskCel.x && kursorDane.x <= przyciskCel.x + przyciskDane.w ) &&
				( kursorDane.y >= przyciskCel.y && kursorDane.y <= przyciskCel.y + przyciskDane.h ) )
                {
                    wyjscie = true;
                }
				
				CzyStrzelonoMyszka=0;
				startStrzaluMyszka=SDL_GetTicks(); 

				xBottle1=xBottle;
                yBottle1=yBottle;
				bulletx=xBottle;
				bullety=yBottle;
                kursorX=kursorDane.x;
				kursorY=kursorDane.y;
            }
            if( zdarzenie.key.keysym.sym == SDLK_ESCAPE ) 
			{
				wyjscie = true;
			}
        }
        if( keystate[ SDLK_d ] )
        {
            if(x<(LEVEL_WIDTH-LUDZIK_WIDTH-480))
			{
			x=x+5;
			}

        }
		if( keystate[ SDLK_a ] )
        {
			if(x>0)
			{
            x=x-5;
			}
        }
		if( keystate[ SDLK_w ] )
        {
           if(y>0)
		   {
			y=y-5;
		   }
        }
		if( keystate[ SDLK_s ] )
        {
            if(y<(LEVEL_HEIGHT-LUDZIK_HEIGHT-150))
			{
			y=y+5;
			}
        }
		if( keystate[ SDLK_SPACE] )
        {
			xBottle=x+70;
			yBottle=y+25;
			CzyStrzelono=0;
			start=SDL_GetTicks(); 
        }
        
		
		//Strzelanie space
		if(CzyStrzelono==1)
		{
		xBottle=x+70;
		yBottle=y+25;
		if(x<LEVEL_WIDTH-680)
		{
		butelkaDestination.x = xBottle;
		}
		butelkaDestination.y = yBottle;
		}
		if(CzyStrzelono==0)
		{
			delta=(SDL_GetTicks()-start)/2;
			xBottle=xBottle+delta/5;
			yBottle=yBottle-20*sin(45*3.14/180)+delta/5;
			if(yBottle>(y+50))
			{
				CzyStrzelono=1;
				ogienDestination.x = xBottle;
				ogienDestination.y = yBottle;
				SDL_BlitSurface( ogien, NULL, ekran, & ogienDestination );	
			}
			butelkaDestination.x = xBottle;
			butelkaDestination.y = yBottle;
		}

		//Strzelanie myszka
		if(CzyStrzelonoMyszka==1)
		{
			bulletx=x+70;
			bullety=y+25;
			if(x<LEVEL_WIDTH-680)
		{
			butelka1Destination.x = bulletx;
			}
			butelka1Destination.y = bullety;
		}
		if(CzyStrzelonoMyszka==0)
		{
		if(butelka1Destination.x<LEVEL_WIDTH && butelka1Destination.y<LEVEL_WIDTH)
		{
		delta1=(SDL_GetTicks()-startStrzaluMyszka)/5;
		deltaX = kursorX - xBottle1; // delta to wektor w kierunku od punktu startowego do celu
		deltaY = kursorY - yBottle1;
		dlugosc = sqrt(deltaX * deltaX + deltaY * deltaY); // obliczamy d³ugoœæ wektora
		deltaX /= dlugosc; // normalizujemy wektor delta, tzn jego d³ugoœæ bêdzie teraz równa 1
		deltaY /= dlugosc;
		bulletx += deltaX*delta1;
		bullety += deltaY*delta1;
        butelka1Destination.x = bulletx;
		butelka1Destination.y = bullety;
		}
		else
		{
		CzyStrzelonoMyszka=1;
		}
		}
		
		 //Center the camera over the dot 
		camera.x = ( x + LUDZIK_WIDTH  ) - SCREEN_WIDTH / 2; 
		camera.y = ( y + LUDZIK_HEIGHT / 2 ) - SCREEN_HEIGHT / 2; 
		//Keep the camera in bounds. 
		if( camera.x < 0 ) 
		{
			camera.x = 0;
		} 
		if( camera.y < 0 ) 
		{ 
			camera.y = 0;
		} 
		if( camera.x > LEVEL_WIDTH - camera.w )
		{ 
			camera.x = LEVEL_WIDTH - camera.w;
		} 
		if( camera.y > LEVEL_HEIGHT - camera.h )
		{ 
			camera.y = LEVEL_HEIGHT - camera.h;
		} 
		
		if(x<LEVEL_WIDTH-680)
		{
		LudekDestination.x = x;
		}
		LudekDestination.y = y;

        SDL_BlitSurface( ludek, NULL, ekran, & LudekDestination );
        SDL_BlitSurface( butelka, NULL, ekran, & butelkaDestination );
        SDL_BlitSurface( butelka1, NULL, ekran, & butelka1Destination );
		SDL_Flip( ekran );
    }
	SDL_FreeSurface( ludek );
	SDL_FreeSurface( przycisk );
    SDL_FreeSurface( kursor );
	SDL_FreeSurface( tlo );
    SDL_Quit();
    return 0;
return 0;
}