#include "ListImagesFields.h"
#include "ViewField.h"
#include "ITM_Img_list_field.h"
#include <vector>
#include <iostream>
#include "DEFs.h"
using namespace std;

ListImagesFields::ListImagesFields(window* pWind, int topLeftX, int topLeftY) :ViewField(pWind)
{
    width = 650;
    height = 60;
    images = new vector<ITM_Img_list_field*>;
    GfxInfoComp.topLeft.x = topLeftX;
    GfxInfoComp.topLeft.y = topLeftY;
    GfxInfoComp.bottomRight.x = topLeftX+width;
    GfxInfoComp.bottomRight.y = topLeftY+height;
}


void ListImagesFields::addItmImage(ITM_Img_list_field* newImage)
{


    if (images->size() == 0)
    {
        newImage->setTopLeft(GfxInfoComp.topLeft.x+5, GfxInfoComp.topLeft.y+5);
        
    }
    else 
    {
        ITM_Img_list_field* lastImage = images->at(images->size() - 1);
        newImage->setTopLeftAtHorizentalLine(lastImage);
    }
    images->push_back(newImage);
}

void ListImagesFields::addItmImages(ITM_Img_list_field* newImage[], int size)
{
    for (int i = 0; i < size; i++)
    {
        addItmImage(newImage[i]);
    }
}

void ListImagesFields::addItmImagesAndClear(ITM_Img_list_field* newImages[], int size)
{
    clearAll();
    addItmImages(newImages, size);
}

void ListImagesFields::DrawMe() const
{
    for (int i = 0; i < images->size(); i++)
    {

        images->at(i)->DrawMe();

    }
}

void ListImagesFields::clearAll()
{
    images->clear();
}

void ListImagesFields::setSelectedForXY(int x, int y)
{
    if (isXYinME(x, y))
    {
     
        for (int i = 0; i < images->size(); i++)
        {

            if (images->at(i)->isXYinMe(x, y))
            {
                images->at(i)->setSelected(true);
            }
            else
            {
                images->at(i)->setSelected(false);
            }
        }
    }
}

bool ListImagesFields::isXYinME(int x, int y)
{
    if (x >= GfxInfoComp.topLeft.x
        && x <= GfxInfoComp.bottomRight.x
        && y >= GfxInfoComp.topLeft.y
        && y <= GfxInfoComp.bottomRight.y)
    {
        return true;
    }
    return false;
}

bool ListImagesFields::isSelected() const
{
    for (int i = 0; i < images->size(); i++)
    {
        if (images->at(i)->isSelected())
            return true;
    }
    return false;
}

void ListImagesFields::setSelectedForMajor(MAJORS maj)
{
    setSelectedForXY(images->at(maj-1)->getGfxInfoComp().topLeft.x + 5, images->at(maj-1)->getGfxInfoComp().topLeft.y + 5);

}

ITM_Img_list_field* ListImagesFields::getImageAtXY(int x, int y)
{
    return nullptr;
}

MAJORS ListImagesFields::getFinalMajorSelected()
{

    for (int i = 0; i < images->size(); i++)
    {
        if (images->at(i)->isSelected())
        {
            cout << "sel";
            return images->at(i)->getMajorFlag();

        }
    }
}

string ListImagesFields::getFinalMajorSelectedString()
{
    switch(getFinalMajorSelected())
    {
        case CIE:
            return "CIE";
        case ENV:
            return "ENV";
        case NANE:
            return "NANE";
        case REE:
            return "REE";
        case SPC:
            return "REE";

    }

}

void ListImagesFields::setSelected(int x, int y)
{
}


