#include "Grid.h"
#include <exception>

Grid::Grid(WORD size)
:
width(size),
height(size)
{
    while(cells.size() < size * size)
    {
        cells.push_back(Cell());
    }
    for(Cell& c : cells)
        c.Birth();
}


Grid::Grid(WORD width, WORD height)
:
width(width),
height(height)
{
    while(cells.size() < width * height)
    {
        cells.push_back(Cell());
    }
}


Grid::~Grid()
{
}


Cell Grid::GetCell(int xGrid, int yGrid) const
{
    if(xGrid >= 0 && xGrid < width && yGrid >= 0 && yGrid < height)
    {
        return cells[xGrid + yGrid * width];
    }
    else throw std::exception("grid array out of bounds");
}


void Grid::SetCell(int xGrid, int yGrid, bool alive)
{
    if(xGrid >= 0 && xGrid < width && yGrid >= 0 && yGrid < height)
    {
        if(alive)
        {
            cells[xGrid + yGrid * width].Birth();
        }
        else
        {
            cells[xGrid + yGrid * width].Kill();
        }
    }
}


std::vector<Cell*> Grid::GetNeighbors(int xGrid, int yGrid)
{
    std::vector<Cell*> neighbors;
    for(int y2 = -1; y2 < 2; y2++)
    {
        for(int x2 = -1; x2 < 2; x2++)
        {
            int xa = xGrid + x2;
            int ya = yGrid + y2;
            int index = xa + ya * width;
            if(xa < width && xa >= 0 && ya < height &&  ya >= 0)
            {
                neighbors.push_back(&cells[index]);
            }
            else
            {
                neighbors.push_back(nullptr);
            }
        }
    }
    neighbors.erase(neighbors.begin() + 4);
    return neighbors;
}


void Grid::Fill()
{
    for(Cell& cell : cells)
    {
        cell.Birth();
    }
}


void Grid::Clear()
{
    for(Cell& cell : cells)
    {
        cell.Kill();
    }
}


void Grid::Update()
{
    std::vector<Cell*> markedForDeath;
    std::vector<Cell*> markedForBirth;
    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            auto neighbors(GetNeighbors(x, y));
            Cell* cell = &cells[x + y * width];
            int nAlive(0);
            for(auto& n : neighbors)
            {
                if(n != nullptr && n->Alive())
                {
                    nAlive++;
                }
            }
            if(cell->Alive() && (nAlive > 3 || nAlive < 2))
            {
                markedForDeath.push_back(cell);
            }
            else if(!cell->Alive() && nAlive == 3)
            {
                markedForBirth.push_back(cell);
            }
            cell->IterateAge();
        }
    }
    for(Cell* c : markedForDeath)
    {
        c->Kill();
    }
    for(Cell* c : markedForBirth)
    {
        c->Birth();
    }
}


void Grid::Draw(D3DGraphics& gfx)
{
    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            cells[x + y * width].Draw(x * D3DGraphics::TILESIZE, y * D3DGraphics::TILESIZE, gfx);
        }
    }
}