#include "Cell.h"

const D3DCOLOR Cell::COLORS[Cell::COLORS_SIZE] = {BLACK, RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE, WHITE};


Cell::Cell(bool alive)
    :
state(alive)
{
    age = (alive)? 1 : 0;
}


Cell::~Cell()
{}


bool Cell::Alive() const
{
    return state;
}


void Cell::IterateAge()
{
    if(state && age < COLORS_SIZE - 1)
    {
        age++;
    }
}


void Cell::Kill()
{
    state = false;
    age = 0;
}


void Cell::Birth()
{
    state = true;
    age = 1;
}


void Cell::Draw(int xPixel, int yPixel, D3DGraphics& gfx)
{
    gfx.DrawTile(xPixel, yPixel, Cell::COLORS[age]);
}


void Cell::Draw(Vec2 pt, D3DGraphics& gfx)
{
    gfx.DrawTile(int(pt.x), int(pt.y), Cell::COLORS[age]);
}