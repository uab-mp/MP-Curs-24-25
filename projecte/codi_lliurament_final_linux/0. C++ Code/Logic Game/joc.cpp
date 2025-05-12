//
//  CurrentGame.cpp
//  LearnChess
//
//  Created by Enric Vergara on 21/2/22.
//

#include "joc.hpp"
#include <iostream>
#include <fstream>
#include "GraphicManager.h"


bool Joc::actualitza(int mousePosX, int mousePosY, bool mouseStatus) {
    //TODO 1: Interactuar amb la crida per dibuixar gràfics (sprites).
    // 	      Dibuixar a pantalla el fons i el gràfic amb el tauler buit.
    //------------------------------------------------------------------

    //TODO 1.1 Afegir l'include de GraphicManager --> #include "GraphicManager.h"
    //TODO 1.2 Fer la crida de dibuixar un sprite --> GraphicManager::getInstance()->drawSprite(image, posX, posY);
    //	    Per començar podem cridar el drawSprite amb els params --> 
    //          (GRAFIC_FONS,0,0) i
    //          (GRAFIC_TAULER, POS_X_TAULER, POS_Y_TAULER)


    //TODO 1.3: Dibuixar a pantalla el gràfic amb el tauler i una fitxa blanca a la posició (fila, columna ) del tauler


    //TODO 2: Interactuar amb el ratolí.
    //------------------------------------------------------------------
    //TODO 2.1: Dibuixar la fitxa blanca al tauler només si estem pressionant el botó del ratolí


    //TODO 2.2: Dibuixar la fitxa blanca al tauler només si estem pressionant el botó del ratolí i el ratolí
    // està dins del límits del tauler


    //TODO 2.3: Dibuixar la fitxa blanca al tauler només si estem pressionant el botó del ratolí i el ratolí
    // està dins del límits del tauler. Dibuixa la fitxa a la casella on està el ratolí


    //TODO 2.4: Dibuixar la fitxa blanca a la casella on cliquem al ratolí. La fitxa s'ha de mantenir dibuixada
    // a la casella quan deixem de clicar amb el ratolí. Quan cliquem a una altra casella, la fitxa canvia de posició
    // a la nova casella


    // TODO 3: Imprimir text per pantalla
    //------------------------------------------
    // TODO 3.1: Mostrar la posició actual del ratolí a sota del tauler


    return false;
}
