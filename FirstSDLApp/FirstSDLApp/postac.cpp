#include "postac.h"

CPostac::CPostac()
{
	LudekDestination.x=0;
	LudekDestination.y=0;
}

CPostac::~CPostac()
{
}

void CPostac::ustaw(int x, int y)
{
	this->LudekDestination.x=x;
	this->LudekDestination.y=y;
}