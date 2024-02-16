#ifndef __METADATA_INTERFACE_
#define __METADATA_INTERFACE_

class MetadataInterface 
{
public:
    void menuInterface();

    void chooseMetadataField();

    void enterMetadataValue();

    void getMetadataError();

    void metadataChooseFile(int input_case);

    void modifyMetadataError();

    void modifyMetadataSuccess();

    void listEmpty(int input_case);
};


#endif /* __METADATA_INTERFACE_ */