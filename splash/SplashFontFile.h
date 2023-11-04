//========================================================================
//
// SplashFontFile.h
//
//========================================================================

//========================================================================
//
// Modified under the Poppler project - http://poppler.freedesktop.org
//
// All changes made under the Poppler project to this file are licensed
// under GPL version 2 or later
//
// Copyright (C) 2006 Takashi Iwai <tiwai@suse.de>
// Copyright (C) 2008, 2010, 2018 Albert Astals Cid <aacid@kde.org>
//
// To see a description of the changes please see the Changelog file that
// came with your tarball or type make ChangeLog if you are building from git
//
//========================================================================

#ifndef SPLASHFONTFILE_H
#define SPLASHFONTFILE_H

#include "poppler-config.h"
#include "SplashTypes.h"
#include "poppler_private_export.h"

class GooString;
class SplashFontEngine;
class SplashFont;
class SplashFontFileID;

//------------------------------------------------------------------------
// SplashFontFile
//------------------------------------------------------------------------

class POPPLER_PRIVATE_EXPORT SplashFontSrc
{
public:
    SplashFontSrc();

    SplashFontSrc(const SplashFontSrc &) = delete;
    SplashFontSrc &operator=(const SplashFontSrc &) = delete;

    void setFile(GooString *file, bool del);
    void setFile(const char *file, bool del);
    void setBuf(char *bufA, int buflenA, bool del);

    void ref();
    void unref();

    bool isFile;
    GooString *fileName;
    char *buf;
    int bufLen;

private:
    ~SplashFontSrc();
    int refcnt;
    bool deleteSrc;
};

class POPPLER_PRIVATE_EXPORT SplashFontFile
{
public:
    virtual ~SplashFontFile();

    SplashFontFile(const SplashFontFile &) = delete;
    SplashFontFile &operator=(const SplashFontFile &) = delete;

    // Create a new SplashFont, i.e., a scaled instance of this font
    // file.
    virtual SplashFont *makeFont(SplashCoord *mat, const SplashCoord *textMat) = 0;

    // Get the font file ID.
    SplashFontFileID *getID() { return id; }

    // Increment the reference count.
    void incRefCnt();

    // Decrement the reference count.  If the new value is zero, delete
    // the SplashFontFile object.
    void decRefCnt();

    bool doAdjustMatrix;

protected:
    SplashFontFile(SplashFontFileID *idA, SplashFontSrc *srcA);

    SplashFontFileID *id;
    SplashFontSrc *src;
    int refCnt;

    friend class SplashFontEngine;
};

#endif
