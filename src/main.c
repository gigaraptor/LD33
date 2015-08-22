#ifndef INCLUDE_LOCK
#define INCLUDE_LOCK
#include "main.h"
#endif

int main(int argc, char *argv[])
{
	int isSuccess;
	char *jsonContents, inBattle;
	options mainOpt;
	SDL_Window *mainWin;
	SDL_Renderer *render;
	SDL_Event eventHandler;
	baseEntity *title, **buttons, **sprites, **dead, *map;
	baseEntity mouse;
	entity *titleToDisp;
	entity **titleElements;
	isSuccess = SUCCESS;
	inBattle = FAIL;
	jsonContents = loadJsonFile(OPTIONS_FILE,&isSuccess);
	mainOpt = initOptions(jsonContents, &isSuccess);
	mainWin = initSDL(&mainOpt, &isSuccess);
	render = createRenderer(mainWin, &isSuccess);
	
	title = initBaseEntity(mainOpt.title_img, render, &isSuccess, &mainOpt);
	titleToDisp = initTitle(*title, &isSuccess, &mainOpt);
	buttons = loadButtons(render,&isSuccess, &mainOpt); 
	sprites = loadSprites(render, &isSuccess, &mainOpt);
	dead = loadCorpses(render, &isSuccess, &mainOpt);
	titleElements = createMenuButtons(buttons, &isSuccess, &mainOpt);
	map = loadMap(mainOpt.map_path, render, &isSuccess, &mainOpt);  
	while(isSuccess == SUCCESS)
	{
		SDL_GetMouseState(&(mouse.dimensions.x), &(mouse.dimensions.y));
		while(SDL_PollEvent(&eventHandler) != 0)
		{
			if(eventHandler.type == SDL_QUIT)
			{
				isSuccess = FAIL;
			
			}
		
		
		}
		SDL_RenderClear(render);
		SDL_SetRenderDrawColor(render,mainOpt.R_COL,mainOpt.G_COL,mainOpt.B_COL,mainOpt.A_COL);
		if(inBattle != SUCCESS)
		{
	
			SDL_RenderCopy(render,titleToDisp->liveAnimation, NULL, &(titleToDisp->posAndHitbox));
			drawMenuButtons(titleElements, render);
			if(checkButtonClicked(&mouse, titleElements[0], &eventHandler) == SUCCESS)
			{
				inBattle = SUCCESS;
			
			}
			if(checkButtonClicked(&mouse, titleElements[1], &eventHandler) == SUCCESS)
			{
				isSuccess = FAIL;
			
			}
		}
		if(inBattle == SUCCESS)
		{
			drawBaseEntity(map, render);
		
		}
		SDL_RenderPresent(render);
	}
	freeButtons(buttons, &mainOpt);
	freeSprites(sprites, &mainOpt);
	freeCorpses(dead, &mainOpt);
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(mainWin);
	deinit();
	return 0;
}