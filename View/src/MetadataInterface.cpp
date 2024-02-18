#include "main.h"
#include "MetadataInterface.h"

void MetadataInterface::menuInterface()
{
    cout << "--------------------------------------------------------" << endl;
    cout << "METADATA MENU:" << endl;
    cout << "1. Show metadata." << endl;
    cout << "2. Update metadata." << endl;
    cout << "0. Back." << endl;
    cout << "Input your command: " << endl;
}

void MetadataInterface::chooseMetadataField()
{
    cout << "Choose a metadata field to modify: " << endl;
}

void MetadataInterface::enterMetadataValue()
{
    cout << "Enter new value: " << endl;
}

void MetadataInterface::getMetadataError()
{
    cerr << "Could not open file or retrieve tag." << endl;
}

void MetadataInterface::metadataChooseFile(int input_case)
{
    switch (input_case)
    {
    case SHOW_METADATA:
        cout << "Enter index of media file that you want to show metadata: " << endl;
        break;

    case UPDATE_METADATA:
        cout << "Enter index of media file that you want to update metadata: " << endl;
        break;

    default:
        cerr << "Error!" << endl;
    }
}

void MetadataInterface::modifyMetadataError()
{
    cout << "This field cannot be modify." << endl;
}

void MetadataInterface::modifyMetadataSuccess()
{
    cout << "Metadata updated succesfully!" << endl;
}

void MetadataInterface::listEmpty(int input_case)
{
    switch (input_case)
    {
    case SHOW_METADATA:
        cout << "There is nothing to show metadata of. Going back..." << endl;
        break;

    case UPDATE_METADATA:
        cout << "There is nothing to update metadata of. Going back..." << endl;
        break;

    default:
        cerr << "Error!" << endl;
    }
}
