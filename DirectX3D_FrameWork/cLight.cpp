#include "stdafx.h"
#include "cLight.h"
#include "cTransform.h"


cLight::cLight()
	: Intensity(1.0f)
{
	this->pTransform = new cTransform();
}


cLight::~cLight()
{
	SAFE_DELETE(this->pTransform);
}
