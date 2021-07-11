#pragma once
#define TEXT_BYTES_PER_LINE 1024
#include <raylib.h>

int main() {
	int ok = false;
	
    ok = dump_data_pak("title.png", "title.h");
    ok = dump_data_pak("A8 font round.png", "font_atascii_big.h");
    ok = dump_data_pak("A8_256.png", "A8COLORS.h");
    ok = dump_data_pak("VGA_256.PNG", "VGACOLORS.h");
    ok = dump_data_pak("A8_256copper.png", "A8COPPER.h");
    ok = dump_data_pak("ATASCII.png", "font_atascii.h");
    ok = dump_data_pak("font_JJ_small.png", "font_JJ.h");
    ok = dump_data_pak("font_p.png", "font_p.h");
    ok = dump_data_pak("font_vga.png", "font_vga.h");
    ok = dump_data_pak("OSD.png", "font_OSD.h");
    ok = dump_data_pak("ball1.png", "ball1.h");
    ok = dump_data_pak("ball2.png", "ball2.h");
    ok = dump_data_pak("ball3.png", "ball3.h");
    ok = dump_data_pak("TL1.png", "TL1.h");
    ok = dump_data_pak("TL2.png", "TL2.h");
    ok = dump_data_pak("TL5.png", "TL5.h");
    ok = dump_data_pak("TL8.png", "TL8.h");
    ok = dump_data_pak("TL9.png", "TL9.h");
    ok = dump_data_pak("lines.png", "lines.h");
    ok = dump_data_pak("icon.png", "icon.h");

/*    ok = dump_data_pak("title.tga", "title.h");
    ok = dump_data_pak("A8 font round.tga", "font_atascii_big.h");
    ok = dump_data_pak("A8_256.tga", "A8COLORS.h");
    ok = dump_data_pak("A8_256copper.tga", "A8COPPER.h");
    ok = dump_data_pak("ATASCII.tga", "font_atascii.h");
    ok = dump_data_pak("font_JJ_small.tga", "font_JJ.h");
    ok = dump_data_pak("font_p.tga", "font_p.h");
    ok = dump_data_pak("font_vga.tga", "font_vga.h");
    ok = dump_data_pak("OSD.tga", "font_OSD.h");
    ok = dump_data_pak("ball1.tga", "ball1.h");
    ok = dump_data_pak("ball2.tga", "ball2.h");
    ok = dump_data_pak("ball3.tga", "ball3.h");
    ok = dump_data_pak("TL1.tga", "TL1.h");
    ok = dump_data_pak("TL2.tga", "TL2.h");
    ok = dump_data_pak("TL5.tga", "TL5.h");
    ok = dump_data_pak("TL8.tga", "TL8.h");
    ok = dump_data_pak("TL9.tga", "TL9.h");
    ok = dump_data_pak("icon.tga", "icon.h");
*/

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