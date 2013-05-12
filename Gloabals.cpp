#include "Gloabals.h"



SpaceInvaderEngine &Globals::GetSpaceInvaderEngine()
{
	static SpaceInvaderEngine eng;
	return eng;
}