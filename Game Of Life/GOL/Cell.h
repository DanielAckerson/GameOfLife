#pragma once

#include "Colors.h"
#include "D3DGraphics.h"


class Cell
{
    static const BYTE COLORS_SIZE = 8;
    static const D3DCOLOR COLORS[COLORS_SIZE];
    bool state;
    DWORD age;

public:
    Cell(bool alive = false);
    ~Cell();
    
    void IterateAge();
    bool Alive() const;
    void Kill();
    void Birth();

    void Draw(int xPixel, int yPixel, D3DGraphics& gfx);
    void Draw(Vec2 pt, D3DGraphics& gfx);
};