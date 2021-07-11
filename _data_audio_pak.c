#pragma once
#define TEXT_BYTES_PER_LINE 1024
#include <raylib.h>

int main() {
	int ok = false;
	
//    ok = dump_data_pak("slyder.xm", "slyder.h");
    ok = dump_data_pak("music_all1.xm", "music_all1.h");
}

int dump_data(char *input, char *output) {
    /*
    Image image = LoadImage(input);     // Loaded in CPU memory (RAM)
	int success = ExportImageAsCode(image, output);
    UnloadImage(image);
    return success;
    */
    unsigned int fileSize = 0;
    unsigned char *fileData = LoadFileData(input, &fileSize);
	int success = ExportFileAsCode(fileData, input, fileSize, output, false);
    RL_FREE(fileData);
    return success;
};

int dump_data_pak(char *input, char *output) {
    unsigned int fileSize = 0;
    unsigned char *fileData = LoadFileData(input, &fileSize);
    unsigned int compressedSize = 0;
    unsigned char *compressed = CompressData(fileData, fileSize + 1, &compressedSize);
    RL_FREE(fileData);

	int success = ExportFileAsCode(compressed, input, compressedSize, output, true);
    RL_FREE(compressed);
    return success;
};

// Export data to code (.h)
int ExportFileAsCode(unsigned char *fileData, const char *inName, unsigned int fileSize,  const char *outName, int filePak) {
    const char *fileExt;
    fileExt = strrchr(inName, '.');
    bool success = false;
#ifndef TEXT_BYTES_PER_LINE
    #define TEXT_BYTES_PER_LINE     20
#endif
    int filesize = fileSize;

    // NOTE: Text data buffer size is estimated considering wave data size in bytes
    // and requiring 6 char bytes for every byte: "0x00, "
    char *txtData = (char *)RL_CALLOC(6*filesize + 2000, sizeof(char));

    int bytesCount = 0;
    bytesCount += sprintf(txtData + bytesCount, "\n//////////////////////////////////////////////////////////////////////////////////\n");
    bytesCount += sprintf(txtData + bytesCount, "//                                                                              //\n");
    bytesCount += sprintf(txtData + bytesCount, "// FileAsCode exporter v1.0 - data exported as an array of bytes                //\n");
    bytesCount += sprintf(txtData + bytesCount, "//                                                                              //\n");
    bytesCount += sprintf(txtData + bytesCount, "// Refactored from ExportWaveAsCode by m4ntr0n1c                                //\n");
    bytesCount += sprintf(txtData + bytesCount, "//                                                                              //\n");
    bytesCount += sprintf(txtData + bytesCount, "//////////////////////////////////////////////////////////////////////////////////\n\n");

    char varFileName[256] = { 0 };
#if !defined(RAUDIO_STANDALONE)
    // Get file name from path and convert variable name to uppercase
    strcpy(varFileName, GetFileNameWithoutExt(outName));
    for (int i = 0; varFileName[i] != '\0'; i++) if (varFileName[i] >= 'a' && varFileName[i] <= 'z') { varFileName[i] = varFileName[i] - 32; }
#else
    strcpy(varFileName, fileName);
#endif

    bytesCount += sprintf(txtData + bytesCount, "//data information\n");
    bytesCount += sprintf(txtData + bytesCount, "#define %s_FILENAME     \"%s\"\n", varFileName, inName);
    bytesCount += sprintf(txtData + bytesCount, "#define %s_FILEEXT      \"%s\"\n", varFileName, fileExt);
    bytesCount += sprintf(txtData + bytesCount, "#define %s_FILESIZE     %u\n", varFileName, filesize);
    bytesCount += sprintf(txtData + bytesCount, "#define %s_PAK          %i\n", varFileName, filePak);

    // Write byte data as hexadecimal text
    bytesCount += sprintf(txtData + bytesCount, "static unsigned char %s_DATA[%i] = { ", varFileName, filesize);
    for (int i = 0; i < filesize - 1; i++) bytesCount += sprintf(txtData + bytesCount, ((i%TEXT_BYTES_PER_LINE == 0)? "0x%x,\n" : "0x%x, "), ((unsigned char *)fileData)[i]);
    bytesCount += sprintf(txtData + bytesCount, "0x%x };\n", ((unsigned char *)fileData)[filesize - 1]);

    // NOTE: Text data length exported is determined by '\0' (NULL) character
    success = SaveFileText(outName, txtData);
    RL_FREE(txtData);
    return success;
}