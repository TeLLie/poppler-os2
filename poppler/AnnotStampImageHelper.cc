//========================================================================
//
// AnnotStampImageHelper.cc
//
// Copyright (C) 2021 Mahmoud Ahmed Khalil <mahmoudkhalil11@gmail.com>
//
// Licensed under GPLv2 or later
//
//========================================================================

#include "AnnotStampImageHelper.h"

#include "goo/gmem.h"
#include "goo/gstrtod.h"
#include "PDFDoc.h"
#include "Stream.h"
#include "Dict.h"

#include <iostream>

AnnotStampImageHelper::AnnotStampImageHelper(PDFDoc *docA, int widthA, int heightA, ColorSpace colorSpace, int bitsPerComponent, char *data, int dataLength)
{
    initialize(docA, widthA, heightA, colorSpace, bitsPerComponent, data, dataLength);
}

AnnotStampImageHelper::AnnotStampImageHelper(PDFDoc *docA, int widthA, int heightA, ColorSpace colorSpace, int bitsPerComponent, char *data, int dataLength, Ref softMaskRef)
{
    initialize(docA, widthA, heightA, colorSpace, bitsPerComponent, data, dataLength);

    sMaskRef = softMaskRef;
    Dict *dict = imgObj.streamGetDict();
    dict->add("SMask", Object(sMaskRef));
}

void AnnotStampImageHelper::initialize(PDFDoc *docA, int widthA, int heightA, ColorSpace colorSpace, int bitsPerComponent, char *data, int dataLength)
{
    doc = docA;
    width = widthA;
    height = heightA;
    sMaskRef = Ref::INVALID();

    Dict *dict = new Dict(docA->getXRef());
    dict->add("Type", Object(objName, "XObject"));
    dict->add("Subtype", Object(objName, "Image"));
    dict->add("Width", Object(width));
    dict->add("Height", Object(height));
    dict->add("ImageMask", Object(false));
    dict->add("BitsPerComponent", Object(bitsPerComponent));
    dict->add("Length", Object(dataLength));

    switch (colorSpace) {
    case ColorSpace::DeviceGray:
        dict->add("ColorSpace", Object(objName, "DeviceGray"));
        break;
    case ColorSpace::DeviceRGB:
        dict->add("ColorSpace", Object(objName, "DeviceRGB"));
        break;
    case ColorSpace::DeviceCMYK:
        dict->add("ColorSpace", Object(objName, "DeviceCMYK"));
        break;
    }

    char *dataCopied = (char *)gmalloc(sizeof(char) * (dataLength));
    std::memcpy(dataCopied, data, dataLength);

    Stream *dataStream = new AutoFreeMemStream(dataCopied, 0, dataLength, Object(dict));
    imgObj = Object(dataStream);
    ref = doc->getXRef()->addIndirectObject(&imgObj);
}

void AnnotStampImageHelper::removeAnnotStampImageObject()
{
    if (sMaskRef != Ref::INVALID())
        doc->getXRef()->removeIndirectObject(sMaskRef);

    doc->getXRef()->removeIndirectObject(ref);
}
