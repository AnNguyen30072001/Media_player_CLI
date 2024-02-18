#include "main.h"
#include "MediaFile.h"

MediaFile::MediaFile(const string &n, const string &p) : name(n), path(p)
{
    type = UNKNOWN_FILE_TYPE;
}

string MediaFile::getName()
{
    return name;
}

string MediaFile::getPath()
{
    return path;
}

int MediaFile::getType()
{
    return type;
}