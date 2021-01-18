#pragma once
#include "ViewField.h"
#include <string>
#include "GUI/CMUgraphicsLib\CMUgraphics.h"

using namespace std;
class ButtonField :
    public ViewField
{

    //used to know what to show on that button
    string text;
    color colorSpecified;

public:
    ButtonField(window* pWind, int topLeftX, int topLeftY, int width, int height);
    ButtonField(window* pWind, int topLeftX, int topLeftY);
    void setColor(color c);
    void DrawMe();
    bool isButtonClick(int x, int y);
};

