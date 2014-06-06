#pragma once

#include <vector>
#include "Cell.h"
#include "D3DGraphics.h"
#include "Mouse.h"

class Grid
{
    std::vector<Cell> cells;
    WORD width, height;

public:
    Grid(WORD size);
    Grid(WORD width, WORD height);
    ~Grid();

    Cell GetCell(int xGrid, int yGrid) const;
    void SetCell(int xGrid, int yGrid, bool alive);
    std::vector<Cell*> GetNeighbors(int xGrid, int yGrid);

    void Fill();
    void Clear();

    void Update();
    void Draw(D3DGraphics& gfx);
};

