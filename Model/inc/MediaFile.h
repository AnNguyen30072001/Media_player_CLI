#ifndef FA207558_4C00_4F98_A43A_F413D7F41F8D
#define FA207558_4C00_4F98_A43A_F413D7F41F8D

#include <iostream>
using namespace std;

class MediaFile
{
protected:
    string name;
    string path;
    int type;

public:
    MediaFile(const string &n, const string &p);
    virtual ~MediaFile() = default;

    string getName();
    string getPath();
    int getType();
};

#endif /* FA207558_4C00_4F98_A43A_F413D7F41F8D */
