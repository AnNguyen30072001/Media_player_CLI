#ifndef C44BD54D_8A21_4D96_99D1_7ACC89A697A2
#define C44BD54D_8A21_4D96_99D1_7ACC89A697A2

#include "MediaFile.h"
#include <vector>

using namespace std;

class Playlist {
private:
    string name;
    vector<MediaFile> files;
public:
    Playlist(const string& n) : name(n) {}
    ~Playlist() = default;

    void addFile(MediaFile* file);

    void deleteFile(int file_idx);

    string getName();

    vector<MediaFile> getFiles();
};

#endif /* C44BD54D_8A21_4D96_99D1_7ACC89A697A2 */
