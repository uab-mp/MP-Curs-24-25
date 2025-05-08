//
//  GraphicManager.hpp
//  MP_Practica
//
//  Created by Enric Vergara on 13/03/2021.
//  Copyright © 2021 CompiledCreations. All rights reserved.
//

#ifndef GraphicManager_hpp
#define GraphicManager_hpp

#include "../Graphic Lib/libreria.h"
#include "../Graphic Lib/NFont/NFont.h"
#include <stdio.h>
#include <string>
#include <map>
using namespace std;


typedef enum 
{
    GRAFIC_FONS = 0,
    GRAFIC_TAULER,
    GRAFIC_POSICIO_VALIDA,
    GRAFIC_FITXA_BLANCA,
    GRAFIC_DAMA_BLANCA,
    GRAFIC_FITXA_NEGRA,
    GRAFIC_DAMA_NEGRA,
    GRAFIC_NUM_MAX
} IMAGE_NAME;

typedef enum 
{
    FONT_WHITE_30 = 0,
    FONT_RED_30,
    FONT_GREEN_30,
    
    FONT_NUM_MAX
} FONT_NAME;


class GraphicManager
{
public:
    
    void            drawSprite  (IMAGE_NAME name, float posX, float posY);
    //size: [0-1]
    NFont::Rectf    drawFont    (FONT_NAME name, float posX,
                                 float posY, float size,
                                 const string& msg);
    
    
    static GraphicManager *getInstance()
    {
        if (instance == NULL)
          instance = new GraphicManager();
        return instance;
    }
    

protected:
    GraphicManager();
    virtual ~GraphicManager() {}
    GraphicManager(GraphicManager const&);
    GraphicManager& operator=(GraphicManager const&);

private:
    static GraphicManager *instance;
    
    Sprite  m_aSprites[GRAFIC_NUM_MAX];
    NFont   m_oFontWhite_30;
    NFont   m_oFontRed_30;
    NFont   m_oFontGreen_30;
    
private:
    string getImagePath (IMAGE_NAME);
    string getFontPath  (FONT_NAME);
};



#endif /* GraphicManager_hpp */
