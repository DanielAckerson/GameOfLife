/****************************************************************************************** 
 *	Chili DirectX Framework Version 14.03.22											  *	
 *	Game.cpp																			  *
 *	Copyright 2014 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "Game.h"

Game::Game( HWND hWnd,KeyboardServer& kServer,const MouseServer& mServer )
:	gfx( hWnd ),
	audio( hWnd ),
	kbd( kServer ),
	mouse( mServer ),
    grid(D3DGraphics::SCREENWIDTH / D3DGraphics::TILESIZE, D3DGraphics::SCREENHEIGHT / D3DGraphics::TILESIZE)
{
}

Game::~Game()
{
}

void Game::Go()
{
	UpdateModel();
	gfx.BeginFrame();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel( )
{
    if(mouse.LeftIsPressed() && mouse.IsInWindow())
    {
        int xCell = mouse.GetMouseX() / D3DGraphics::TILESIZE;
        int yCell = mouse.GetMouseY() / D3DGraphics::TILESIZE;
        grid.SetCell(xCell, yCell, true);
    }
    else if(mouse.RightIsPressed() && mouse.IsInWindow())
    {
        int xCell = mouse.GetMouseX() / D3DGraphics::TILESIZE;
        int yCell = mouse.GetMouseY() / D3DGraphics::TILESIZE;
        grid.SetCell(xCell, yCell, false);
    }

    if(kbd.ReadChar() == VK_SPACE)
    {
        grid.Update();
    }

    if(kbd.ReadKey().GetCode() == VK_RETURN)
    {
        if(kbd.KeyIsPressed(VK_CONTROL))
        {
            grid.Clear();
        }
        else
        {
            grid.Fill();
        }
    }
}

void Game::ComposeFrame()
{
    grid.Draw(gfx);
}
