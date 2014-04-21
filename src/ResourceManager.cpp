//
//  ResourceManager.cpp
//  Controlease
//
//  Created by Gal Sasson on 2/19/14.
//
//

#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
    circleImg.loadImage("BlurryCircle.png");
    circleImg.setImageType(OF_IMAGE_COLOR_ALPHA);
}
