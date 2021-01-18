#pragma once
#include "Drawable_Parent.h"
#include <string>
using namespace std;
#include "ViewField.h"
#include "DEFs.h"
#include "GUI/CMUgraphicsLib\CMUgraphics.h"

class ITM_Img_list_field :
    public ViewField
{
    //file path for specified image
    string imgFilePath;
    //is used for specific purpose for showing the list of major. and getting the results bacl
    MAJORS major_flag;

   
public:
    ITM_Img_list_field(window* pWindstring, string filePath, MAJORS major_flag, int topLeftX, int topLeftY);
    //this constructor is made as it top left could be calculated from listField directly.
    ITM_Img_list_field(window* pWindstring, string filePath, MAJORS major_flag);
    void setWidtheHeightDefualt();
    void setWidtheHeight(int w, int h);
    void setWidth(int width);
    void setHeight(int height);
    //inherited function, that draws the object, essentially it checks first if it's clicked or not, and rediret it to the prober funtion 
    void DrawMe() const;
    void DrawMeClicked()const;
    void DrawMeNotClicked()const; 
    void setSelected(bool sel);
    bool isSelected()const;
    MAJORS getMajorFlag()const;
    void setTopLeft(graphicsInfoComprehensive gfc);
    void setTopLeft(int topLeftX, int topLeftY);
    //it will set the top left taking in calulatiof last object drawing on left
    void setTopLeftAtHorizentalLine(ITM_Img_list_field* lastImage);
    int getWidth();
    int getHeight();
    //just checks if user click on it.
    bool isXYinMe(int x, int y);
    //clear what was drawn with the specified backgournd color
    void clearArea();
};

