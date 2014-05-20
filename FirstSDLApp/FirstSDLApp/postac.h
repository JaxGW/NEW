#ifndef __postac_h_
#define __postac_h_

#include <SDL.h>
#include "SDL_opengl.h"
#include <stdlib.h>
#include <string>
#include <stdio.h>
#include <iostream>

class CPostac
{
private:
	SDL_Rect LudekDestination;
	SDL_Surface ludek;
public:
	CPostac();
	~CPostac();
	void ustaw(int x, int y);
};


#endif __postac_h_