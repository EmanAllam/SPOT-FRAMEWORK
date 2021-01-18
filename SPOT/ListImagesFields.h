#pragma once
#include "ViewField.h"
#include "ITM_Img_list_field.h"
#include <vector>
#include "DEFs.h"
#include "GUI/CMUgraphicsLib\CMUgraphics.h"

using namespace std;

class ListImagesFields :
    public ViewField
{
    vector<ITM_Img_list_field*>* images;


    ITM_Img_list_field* getImageAtXY(int x, int y);

public:
    ListImagesFields(window* pWind, int topLeftX, int topLeftY);
    void addItmImage(ITM_Img_list_field* newImage);
    void addItmImages(ITM_Img_list_field* newImage[], int size);
    //it clears first all previous images stored in images vector, and then add the new ones
    void addItmImagesAndClear(ITM_Img_list_field* newImage[], int size);
    //return the final major selected in enum
    MAJORS getFinalMajorSelected();
    //return the final major selected in string
    string getFinalMajorSelectedString();
    void setSelected(int x, int y);
    void virtual DrawMe() const;
    //clear what was drawn with the specified backgournd color
    void clearAll();
    void setSelectedForXY(int x, int y);
    bool isXYinME(int x, int y);
    //returns trur if at least user clicked on any major.
    bool isSelected()const;
    //VERY IMPORTANT--> this function assumes that order of MAJOR enum is the same as the order pictures were entered.
    void setSelectedForMajor(MAJORS maj);
};

