//========================================================================
//
// PDFDocEncoding.h
//
// Copyright 2002-2003 Glyph & Cog, LLC
//
//========================================================================

//========================================================================
//
// Modified under the Poppler project - http://poppler.freedesktop.org
//
// All changes made under the Poppler project to this file are licensed
// under GPL version 2 or later
//
// Copyright (C) 2007 Adrian Johnson <ajohnson@redneon.com>
// Copyright (C) 2019 Volker Krause <vkrause@kde.org>
// Copyright (C) 2020 Oliver Sander <oliver.sander@tu-dresden.de>
//
// To see a description of the changes please see the Changelog file that
// came with your tarball or type make ChangeLog if you are building from git
//
//========================================================================

#ifndef PDFDOCENCODING_H
#define PDFDOCENCODING_H

#include "poppler-config.h"
#include <string>

#include "CharTypes.h"
#include "poppler_private_export.h"

class GooString;

extern const Unicode POPPLER_PRIVATE_EXPORT pdfDocEncoding[256];

char POPPLER_PRIVATE_EXPORT *pdfDocEncodingToUTF16(const std::string &orig, int *length);

#endif
