// GRID_][_GRID_][_GRID_][_GRID_][_GRID_][_GRID_][_GRID_][_GRID_][_GRID_][_GRID_][_GRID_][_GRID_][_GRID_][_GRID_][_GRID_][
// GRID_][                                                                                                         GRID_][
// GRID_][    filename: grid2                                                                                      GRID_][
// GRID_][                                                                                                         GRID_][
// GRID_][    written by Jacques Morel                                                                             GRID_][
// GRID_][    copywright (c) 2021 all rights reserved                                                              GRID_][
// GRID_][                                                                                                         GRID_][
// GRID_][    source code may not be used, redistributed, shared, hosted, archived without author's consent.       GRID_][
// GRID_][                                                                                                         GRID_][
// GRID_][_GRID_][_GRID_][_GRID_][_GRID_][_GRID_][_GRID_][_GRID_][_GRID_][_GRID_][_GRID_][_GRID_][_GRID_][_GRID_][_GRID_][
#pragma once

#include "raylib.h"             // works on version 3.8 development
#include "raymath.h"
#include "rlgl.h"               // raylib OpenGL abstraction layer to OpenGL 1.1, 3.3 or ES2
#include <GLFW/glfw3.h>

//#include <windows.h> 
#include <stdlib.h>  // header of the general purpose standard library
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <limits.h>
#include <string.h>  // set of functions implementing operations on strings
//#include <strsafe.h> // replace standard C string handling and I/O functions including printf, strlen, strcpy and strcat
//#include <tchar.h>  // for string functions makes code compliant to both Unicode and non-unicode environments
//#include <errno.h>   // A value (the error number) is stored in errno by certain library functions when they detect errors
//#include <unistd.h>  // provides access to the POSIX operating system API
//#include <fcntl.h> // system-wide table of files opened by all processes, called the file table

// **************************************************************************************** B A S E   A S S E T S
#include <VGACOLORS.h>
#include <A8COLORS.h>
#include <icon.h>
#include <A8COPPER.h>
#include <font_JJ.h>
#include <font_vga.h>
#include <font_atascii.h>
#include <font_atascii_big.h>
#include <font_OSD.h>
#include <lines.h>

// **************************************************************************************** L O O S E   S T R U C T U R E S


// **************************************************************************************** G R I D   S T R U C T U R E S
#define NAMELENGTH_MAX 80
#define GRID_MAX_CELLS 65536
#define GRID_MAX_PAGES 5
#define GRID_MAX_LAYERS 16

typedef struct EX_cell {
    unsigned int state;                             // all flags for cell
    unsigned short value;                           // value of cell
    unsigned char lines;                            // lines feature
    unsigned short cycle_id;                        // cell animation sequence number
    unsigned short fg_color_id;                     // palette index color for cell
    unsigned short fg_color_cycle_id;               // color cycle index
    unsigned short bg_color_id;                     // palette index color for cell background
    unsigned short bg_color_cycle_id;               // color cycle index
    unsigned short lines_color_id;                  // palette index color for cell background
    unsigned short lines_color_cycle_id;            // color cycle index
    Vector2 offset;                                 // displacement from top left (x,y)
    Vector2 skew;                                   // horizontal and vertical skew
    Vector2 scale;                                  // (x,y) cell scale
    Vector2 scale_speed;                            // (x,y) cell scale speed
    Vector2 scroll_speed;                           // (x,y) cell scroll speed
    float angle;                                    // degree of angle used to rotate the cell
    float fg_brightness;                            // foreground brightness (values 0...1 divides, values 1 to 255 multiply)
    float bg_brightness;                            // background brightness (values 0...1 divides, values 1 to 255 multiply)
    Color color_mask;                               // RGBA color mask of cell
    Color shadow_mask;                              // shadow RGBA mask
} EX_cell;

typedef struct EX_layer {
    char name[NAMELENGTH_MAX + 1];
    unsigned int state;                             // all flags for grid
    int asset_id;                                   // tilset used for this layer
    Vector2 size;                                   // total cells x and y
    unsigned short fg_color_id;                     // palette index color for cell
    unsigned short fg_color_cycle_id;               // color cycle index
    unsigned short bg_color_id;                     // palette index color for cell background
    unsigned short bg_color_cycle_id;               // color cycle index
    unsigned short lines_color_id;                  // palette index color for cell background
    unsigned short lines_color_cycle_id;            // color cycle index
    Vector2 offset;                                 // displacement from top left (x,y)
    Vector2 displace[4];                            // cell corner displacement (x,y)
    Vector2 scale;                                  // (x,y) cell scale
    Vector2 scale_speed;                            // (x,y) cell scale speed
    Vector2 scroll_speed;                           // layer scroll speed (x,y)
    float angle;                                    // degree of angle to rotate layer
    float fg_brightness;                            // foreground brightness (values 0...1 divides, values 1 to 255 multiply)
    float bg_brightness;                            // background brightness (values 0...1 divides, values 1 to 255 multiply)
    Vector2 shadow;                                 // shadow corner displacement (x,y)
    Vector2 shadow_displace[4];                      // shadow corners displacement (x,y)
    Color   color_mask;                             // RGBA color mask of layer
    Color   shadow_mask;                            // shadow RGBA mask
    EX_cell mouse;                                  // mouse cursor
    EX_cell keyboard;                               // key cursor
    EX_cell mask;                                   // used for when replicating
    unsigned int cell_count;
    EX_cell* cell; // could be NULL
} EX_layer;

typedef struct EX_page {
    unsigned int state;
    char name[NAMELENGTH_MAX + 1];
    int layer_count;                                // total number of layers
    EX_layer* layer;                                // could be NULL
} EX_page;

// **************************************************************************************** A S S E T   S T R U C T U R E S
#define MAXASSETS 256
#define MAXPALETTECOLORS 256

typedef struct EX_tileset {
    Vector2 tilesize;   // Tile size
    Vector2 count;       // number of tiles (x, y)
    Texture tex;        // Characters texture atlas
    unsigned int total; // Number of Tiles
    int ascii_start;    // if tileset if character font, identifies ascii code first tile
} EX_tileset;

typedef struct EX_asset {
    char name[NAMELENGTH_MAX + 1];
    unsigned int total_assets;
    unsigned int dead_assets[MAXASSETS];

    unsigned int asset_type[MAXASSETS];
    unsigned int state[MAXASSETS];
    int data_size[MAXASSETS];               // storage space size in bytes

    Image img[MAXASSETS];                   // storage space for unpacked images
    Texture tex[MAXASSETS];                 // storage space for textures
    Color *palette[MAXASSETS];              // storage space for indexed colors
    unsigned int palette_colors[MAXASSETS]; // total number of colors in palette
    EX_tileset tileset[MAXASSETS];          // storage space for texture based fonts
    RenderTexture framebuffer[MAXASSETS];   // storage space for frame buffer
    Font font[MAXASSETS];                   // storage space for texture based fonts
    Music music[MAXASSETS];                 // storage space for unpacked music
    Shader shader[MAXASSETS];               // storage space for shaders
    unsigned char *data[MAXASSETS];         // storage space for any text, data, JSON, LUA ...
} EX_asset;

// **************************************************************************************** A U D I O   S T R U C T U R E S

#define MAXAUDIOTRACKS 10
#define MAXORDERS 50

typedef struct EX_track {
    bool is_playing;
    int state;
    int asset;
    int virtual_display;
    float volume;
    float dest_volume; // TO DO
    float slide_speed; // TO DO
    int order_playing;
    int total_orders;
    int order[MAXORDERS];
} EX_track;

typedef struct EX_audio {
    int total_tracks;
    float global_volume;
    EX_track track[MAXAUDIOTRACKS];
} EX_audio;


// **************************************************************************************** V I D E O   S T R U C T U R E S

#define MAXDISPLAYS 5
#define PRIMARYDISPLAY 0
#define MENUDISPLAY 1
#define INGAMEDISPLAY 2
#define PAUSEDISPLAY 3
#define TERMINALDISPLAY 4

typedef struct EX_video {
    //unsigned int state;
    Vector2 physical_res[MAXDISPLAYS];          // physical display resolution (x, y)
    int refresh_rate[MAXDISPLAYS];              // physical display refresh rate
    int state[MAXDISPLAYS];                     // virtual display state
    int fps[MAXDISPLAYS];
    int frames[MAXDISPLAYS];                    // number of game frame elasped since initialisation
    double prev_time[MAXDISPLAYS];              // keep track of time to grab delta
    double elapsed_time[MAXDISPLAYS];           // elapsed time in milliseconds since last frame refresh
    float elapsed_time_var[MAXDISPLAYS];        // elapsed time in milliseconds since last frame refresh (with ratio)
    float elapsed_time_var_ratio[MAXDISPLAYS];  // multiplication factor
    float frame_time[MAXDISPLAYS];
    float frame_time_inc[MAXDISPLAYS];
    float value_anim[MAXDISPLAYS];              // space for animated controls (to be elaborated)
    float elapsed_time_nofocus[MAXDISPLAYS];    // elapsed time since nofocus
    Vector2 virtual_res[MAXDISPLAYS];           // virtual display resolution (x, y)
    int virtual_asset[MAXDISPLAYS];             // virtual display asset number

    EX_page page[MAXDISPLAYS];                  // page data

    int windowstate_normal;                     // physical display window state in normal mode
    int windowstate_paused;                     // physical display window state when game is paused
    int current_physical;                       // physical display currently used
    int next_physical_clear;
    int current_virtual;                        // virtual display currently used

    bool window_focus;                          // last state of window focus
} EX_video;

// **************************************************************************************** T E R M I N A L   S T R U C T U R E S

typedef struct EX_terminal {
    unsigned int state;
    int asset_id;
    int page_id;
    int layer_id;
} EX_terminal;


// **************************************************************************************** A P P L I C A T I O N   S T R U C T U R E S

typedef struct EX_player {

} EX_player;

typedef struct EX_game {
    EX_player player;

} EX_game;

typedef struct EX_application {
    
} EX_application;


// **************************************************************************************** S Y S T E M   S T R U C T U R E S

typedef struct EX_system {
    EX_terminal     terminal;
    EX_asset        asset;
    EX_audio        audio;
    EX_video        video;
    EX_application  app;
    bool pause;

} EX_system;

EX_system sys;

// **************************************************************************************** U T I L I T Y   F U N C T I O N S   &   M A C R O S

/*
#define STDIO_BUFFER_SIZE 4000
static char stdio_buffer[STDIO_BUFFER_SIZE + 1] = {0};
static int stdio_pipe[2];
*/

//void prepare_stdio(void) {
//    long flags = fcntl(stdio_pipe[0], F_GETFL);
//    flags |= O_NONBLOCK;
//    fcntl(stdio_pipe[0], F_SETFL, flags);
//};

//prepare_stdio(); 

//    enum { STATE_WAITING, STATE_LOADING, STATE_FINISHED } state = STATE_WAITING;

// C11: Sets the first n bytes starting at dest to the specified value, but maximal dmax bytes.
//#define EX_MEMSET(void *dest, rsize_t dmax, int value, rsize_t n)   memset_s(void *dest, rsize_t dmax, int value, rsize_t n)

// C11: This function copies at most smax bytes from src to dest, up to dmax.
//#define EX_MEMCPY(void *restrict dest, rsize_t dmax, const void *restrict src, rsize_t smax) memcpy_s(void *restrict dest, rsize_t dmax, const void *restrict src, rsize_t smax)

#ifdef __cplusplus // Calling C code from C++
extern "C" { 
#endif

/* --- PRINTF_BYTE_TO_BINARY macro's --- */
#define PRINTF_BINARY_PATTERN_INT8 "%c%c%c%c%c%c%c%c"
#define PRINTF_BYTE_TO_BINARY_INT8(i)    \
    (((i) & 0x80ll) ? '1' : '0'), (((i) & 0x40ll) ? '1' : '0'), (((i) & 0x20ll) ? '1' : '0'), (((i) & 0x10ll) ? '1' : '0'), \
    (((i) & 0x08ll) ? '1' : '0'), (((i) & 0x04ll) ? '1' : '0'), (((i) & 0x02ll) ? '1' : '0'), (((i) & 0x01ll) ? '1' : '0')

#define PRINTF_BINARY_PATTERN_INT16    PRINTF_BINARY_PATTERN_INT8              PRINTF_BINARY_PATTERN_INT8
#define PRINTF_BYTE_TO_BINARY_INT16(i) PRINTF_BYTE_TO_BINARY_INT8((i) >> 8),   PRINTF_BYTE_TO_BINARY_INT8(i)
#define PRINTF_BINARY_PATTERN_INT32    PRINTF_BINARY_PATTERN_INT16             PRINTF_BINARY_PATTERN_INT16
#define PRINTF_BYTE_TO_BINARY_INT32(i) PRINTF_BYTE_TO_BINARY_INT16((i) >> 16), PRINTF_BYTE_TO_BINARY_INT16(i)
#define PRINTF_BINARY_PATTERN_INT64    PRINTF_BINARY_PATTERN_INT32             PRINTF_BINARY_PATTERN_INT32
#define PRINTF_BYTE_TO_BINARY_INT64(i) PRINTF_BYTE_TO_BINARY_INT32((i) >> 32), PRINTF_BYTE_TO_BINARY_INT32(i)
// EXAMPLE USE CASE:     printf("mystate = "PRINTF_BINARY_PATTERN_INT32"\n", PRINTF_BYTE_TO_BINARY_INT32(mystate));
/* --- end macros --- */

//* Bound reader macros.
//* If we attempt to read the buffer out-of-bounds, pretend that the buffer is infinitely padded with zeroes.
#define READ_U8(offset) (((offset) < griddata_length) ? (*(uint8_t*)(griddata + (offset))) : 0)
#define READ_U16(offset) ((uint16_t)READ_U8(offset) | ((uint16_t)READ_U8((offset) + 1) << 8))
#define READ_U32(offset) ((uint32_t)READ_U16(offset) | ((uint32_t)READ_U16((offset) + 2) << 16))
#define READ_MEMCPY(ptr, offset, length) memcpy_pad(ptr, length, griddata, griddata_length, offset)
#define sizeof_member(type, member) sizeof(((type *)0)->member)
#define sizeof_member_dim(type, member) sizeof(((type*)0)->member) / sizeof(((type*)0)->member[0])

static void memcpy_pad(void *dst, size_t dst_len, const void *src, size_t src_len, size_t offset) {
    uint8_t *dst_c = dst;
    const uint8_t *src_c = src;

    /* how many bytes can be copied without overrunning `src` */
    size_t copy_bytes = (src_len >= offset) ? (src_len - offset) : 0;
    copy_bytes = copy_bytes > dst_len ? dst_len : copy_bytes;

    memcpy(dst_c, src_c + offset, copy_bytes);
    /* padded bytes */
    memset(dst_c + copy_bytes, 0, dst_len - copy_bytes);
}


uint8_t fifo_data[256];
uint32_t fifo_entries;
uint32_t fifo_lock;

void fifo_putc(uint8_t data) {
	while(fifo_lock);
	fifo_lock = 1;
	while(fifo_entries >= (sizeof(fifo_data)));
	fifo_entries++;
	fifo_data[fifo_entries-1] = data;
	fifo_lock = 0;
}

uint8_t fifo_getc() {
	uint8_t ret;
	uint32_t i;
	if (fifo_entries == 0) return 0;
	while(fifo_lock);
	fifo_lock = 1;
	ret = fifo_data[0];
	for(i = 0; i < fifo_entries; i++) {
		fifo_data[i] = fifo_data[i+1];
	}
	fifo_entries--;
	fifo_lock = 0;
	return ret;
}

/* EXAMPLE USE
	fifo_entries = 0, fifo_lock = 0;
	fifo_putc('A');	fifo_putc('B');	fifo_putc('C');	fifo_putc('D');	fifo_putc('E');	fifo_putc('\0');
	printf("'%s'\n", fifo_data);	printf("'%c'\n",
    fifo_getc());	printf("'%s'\n", fifo_data);	fifo_entries--;
	fifo_putc('f');	fifo_putc('\0');
	printf("'%s'\n", fifo_data);    
*/

#define BITS_ON(a,b)  (a |= b)
#define BITS_OFF(a,b) (a &= ~b)
#define INIT(a, b)    (a = b)

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))
#define is_digit(c) ('0' <= (c) && (c) <= '9')

static inline float Rand(float a) {
	return (float)rand()/(float)(RAND_MAX/a);
}
//#define PI         3.14159265358979323846f // raymath.h
#define HALF_PI    1.57079632679489661923f
#define QUARTER_PI 0.78539816339744830961f
#define DIVIDEH_PI 0.159154943091895335768f

static inline float fast_sin(double x) {
    x *= DIVIDEH_PI;
    x -= (int) x;
    if (x <= 0.5) {
        double t = 2 * x * (2 * x - 1);
        return (PI * t) / ((PI - 4) * t - 1);
    } else {
        double t = 2 * (1 - x) * (1 - 2 * x);
        return -(PI * t) / ((PI - 4) * t - 1);
    }
}

static inline float fast_cos(double x) {
    return fast_sin(x + HALF_PI);
}

static inline double dfast_sin(double x) {
    x *= DIVIDEH_PI;
    x -= (int) x;
    if (x <= 0.5) {
        double t = 2 * x * (2 * x - 1);
        return (PI * t) / ((PI - 4) * t - 1);
    } else {
        double t = 2 * (1 - x) * (1 - 2 * x);
        return -(PI * t) / ((PI - 4) * t - 1);
    }
}

static inline double dfast_cos(double x) {
    return fast_sin(x + HALF_PI);
}

// use type punning instead of pointer arithmatics, to require proper alignment
static inline float absf(float f) {
  // optimizer will optimize away the `if` statement and the library call
  if (sizeof(float) == sizeof(uint32_t)) {
    union {
      float f;
      uint32_t i;
    } u;
    u.f = f;
    u.i &= 0x7fffffff;
    return u.f;
  }
  return fabsf(f);
}

static long gcdl(long a, long b)
{
    if (a == 0)
        return b;
    else if (b == 0)
        return a;

    if (a < b)
        return gcd_l(a, b % a);
    else
        return gcd_l(b, a % b);
}

static int gcdi(int a, int b) {
    int res = a%b;
    while (res > 0) {
        a = b;
        b = res;
        res = a % b;
    }
    return b;
}

void DrawTextImage(Texture texture, char* txt, Vector2 position) {
	DrawTexturePro(texture,
    (Rectangle) { (txt[0] - 32) * 24, 0, 24, 24 } ,
    (Rectangle) { position.x , position.y, 64, 64 },
    (Vector2) {0},0,WHITE);
}


// draw Textured Quad
void DrawQuadSprite ( Texture texture , Vector2 position, Vector2 scale, Color color) {
	DrawTexturePro ( texture ,
    (Rectangle) { 0, 0, texture.width * scale.x, texture.height * scale.y },
    (Rectangle) { position.x, position.y, texture.width * scale.x, texture.height * scale.y },
    (Vector2) { 0,0 } , 0 , color );
}

// Draw a color-filled rectangle with pro parameters
void DrawRectangleProSK(Rectangle rec, Vector2 origin, Vector2 skew, float rotation, Color color[4]) {
    rlCheckRenderBatchLimit(4);

    const static inline Texture   texShapes = { 1, 1, 1, 1, 7 };
    const static inline Rectangle texShapesRec = { 0, 0, 1, 1 };

    Vector2 topLeft = { 0 }, topRight = { 0 }, bottomLeft = { 0 }, bottomRight = { 0 };

    if (rotation == 0.0f) {
        float x = rec.x - origin.x;
        float y = rec.y - origin.y;
        topLeft = (Vector2){ x, y };
        topRight = (Vector2){ x + rec.width, y };
        bottomLeft = (Vector2){ x, y + rec.height };
        bottomRight = (Vector2){ x + rec.width, y + rec.height };
    } else {
        float sinRotation = sinf(rotation*DEG2RAD);
        float cosRotation = cosf(rotation*DEG2RAD);
        float x = rec.x;
        float y = rec.y;
        float dx = -origin.x;
        float dy = -origin.y;
        topLeft.x = x + dx*cosRotation - dy*sinRotation;
        topLeft.y = y + dx*sinRotation + dy*cosRotation;
        topRight.x = x + (dx + rec.width)*cosRotation - dy*sinRotation;
        topRight.y = y + (dx + rec.width)*sinRotation + dy*cosRotation;
        bottomLeft.x = x + dx*cosRotation - (dy + rec.height)*sinRotation;
        bottomLeft.y = y + dx*sinRotation + (dy + rec.height)*cosRotation;
        bottomRight.x = x + (dx + rec.width)*cosRotation - (dy + rec.height)*sinRotation;
        bottomRight.y = y + (dx + rec.width)*sinRotation + (dy + rec.height)*cosRotation;
    }

    rlSetTexture(texShapes.id);
    rlBegin(RL_QUADS);
        rlNormal3f(0.0f, 0.0f, 1.0f);
         // Bottom-left corner for texture and quad
        rlColor4ub(color[0].r, color[0].g, color[0].b, color[0].a);
        rlTexCoord2f(texShapesRec.x/texShapes.width, texShapesRec.y/texShapes.height);
        rlVertex2f(topLeft.x + skew.x, topLeft.y);
        // Bottom-right corner for texture and quad
        rlColor4ub(color[1].r, color[1].g, color[1].b, color[1].a);
        rlTexCoord2f(texShapesRec.x/texShapes.width, (texShapesRec.y + texShapesRec.height)/texShapes.height);
        rlVertex2f(bottomLeft.x, bottomLeft.y);
        // Top-right corner for texture and quad
        rlColor4ub(color[2].r, color[2].g, color[2].b, color[2].a);
        rlTexCoord2f((texShapesRec.x + texShapesRec.width)/texShapes.width, (texShapesRec.y + texShapesRec.height)/texShapes.height);
        rlVertex2f(bottomRight.x, bottomRight.y + skew.y);
        // Top-left corner for texture and quad
        rlColor4ub(color[3].r, color[3].g, color[3].b, color[3].a);
        rlTexCoord2f((texShapesRec.x + texShapesRec.width)/texShapes.width, texShapesRec.y/texShapes.height);
        rlVertex2f(topRight.x + skew.x, topRight.y + skew.y);
    rlEnd();
}

// Draw a part of a texture (defined by a rectangle) with 'pro' parameters
// NOTE: origin is relative to destination rectangle size
void DrawTextureProSK (Texture texture, Rectangle source, Rectangle dest, Vector2 origin, Vector2 skew, float rotation, Color color[4]) {
    if (texture.id > 0) {
        float width = (float)texture.width;
        float height = (float)texture.height;
        bool flipX = false;
        if (source.width < 0) { flipX = true; source.width *= -1; }
        if (source.height < 0) source.y -= source.height;
        Vector2 topLeft = { 0 };        Vector2 topRight = { 0 };        Vector2 bottomLeft = { 0 };        Vector2 bottomRight = { 0 };

        if (rotation == 0.0f) { // do not calculate rotation
            float x = dest.x - origin.x;
            float y = dest.y - origin.y;
            topLeft = (Vector2){ x, y };
            topRight = (Vector2){ x + dest.width, y };
            bottomLeft = (Vector2){ x, y + dest.height };
            bottomRight = (Vector2){ x + dest.width, y + dest.height };
        } else {  // calculate rotation
            float sinRotation = sinf(rotation*DEG2RAD);
            float cosRotation = cosf(rotation*DEG2RAD);
            float x = dest.x;
            float y = dest.y;
            float dx = -origin.x;
            float dy = -origin.y;
            topLeft.x = x + dx*cosRotation - dy*sinRotation;
            topLeft.y = y + dx*sinRotation + dy*cosRotation;
            topRight.x = x + (dx + dest.width)*cosRotation - dy*sinRotation;
            topRight.y = y + (dx + dest.width)*sinRotation + dy*cosRotation;
            bottomLeft.x = x + dx*cosRotation - (dy + dest.height)*sinRotation;
            bottomLeft.y = y + dx*sinRotation + (dy + dest.height)*cosRotation;
            bottomRight.x = x + (dx + dest.width)*cosRotation - (dy + dest.height)*sinRotation;
            bottomRight.y = y + (dx + dest.width)*sinRotation + (dy + dest.height)*cosRotation;
        }

        rlCheckRenderBatchLimit(4);     // Make sure there is enough free space on the batch buffer
        rlSetTexture(texture.id);
        rlBegin(RL_QUADS);
            rlNormal3f(0.0f, 0.0f, 1.0f);                          // Normal vector pointing towards viewer
            // Bottom-left corner for texture and quad
            rlColor4ub(color[0].r, color[0].g, color[0].b, color[0].a);
            if (flipX) rlTexCoord2f((source.x + source.width)/width, source.y/height); else rlTexCoord2f(source.x/width, source.y/height);
            rlVertex2f(topLeft.x + skew.x, topLeft.y);
            // Bottom-right corner for texture and quad
            rlColor4ub(color[1].r, color[1].g, color[1].b, color[1].a);
            if (flipX) rlTexCoord2f((source.x + source.width)/width, (source.y + source.height)/height); else rlTexCoord2f(source.x/width, (source.y + source.height)/height);
            rlVertex2f(bottomLeft.x, bottomLeft.y);
            // Top-right corner for texture and quad
            rlColor4ub(color[2].r, color[2].g, color[2].b, color[2].a);
            if (flipX) rlTexCoord2f(source.x/width, (source.y + source.height)/height); else rlTexCoord2f((source.x + source.width)/width, (source.y + source.height)/height);
            rlVertex2f(bottomRight.x, bottomRight.y + skew.y);
            // Top-left corner for texture and quad
            rlColor4ub(color[3].r, color[3].g, color[3].b, color[3].a);
            if (flipX) rlTexCoord2f(source.x/width, source.y/height); else rlTexCoord2f((source.x + source.width)/width, (source.y)/height);
            rlVertex2f(topRight.x + skew.x, topRight.y + skew.y);
        rlEnd();
    }
}

//	Phase Shift 26.2 (These table values were sourced from the MAME project's TIA emulation for the palette management)
	/*static constexpr float color[16][2] =	{
		{  0.000,  0.000 }, {  0.192, -0.127 },	{  0.241, -0.048 },	{  0.240,  0.040 },	{  0.191,  0.121 },	{  0.103,  0.175 },	{ -0.008,  0.196 },	{ -0.116,  0.174 },
        { -0.199,  0.118 },	{ -0.243,  0.037 },	{ -0.237, -0.052 },	{ -0.180, -0.129 },	{ -0.087, -0.181 },	{  0.021, -0.196 },	{  0.130, -0.169 },	{  0.210, -0.107 }
	};*/
// YIQ formula for Atari 8bit GTIA colors (0-255) index
// https://atariage.com/forums/topic/107853-need-the-256-colors/page/2/#comments
// The following routine is currently dead code as I personally do not like the resulting colors...  Something is wrong in the translation from YIQ
Color gtia_ntsc_to_rgb(int val) {
    int chroma = (val >> 4) & 15;
    int luminence = val & 15;
    int crlv = chroma ? 50 : 0;
 
    float phase = ((chroma - 1.) * 25. - 58.) * (2. * PI / 360.);

    float y = 255 * (luminence + 1.) / 16.;
    float i = crlv * cos(phase);
    float q = crlv * sin(phase);

    float r = y + 0.9563 * i + 0.621 * q;
    float g = y - 0.2721 * i - 0.6474 * q;
    float b = y - 1.107 * i + 1.7046 * q;

	if (r < 0) r = 0;
	if (g < 0) g = 0;
	if (b < 0) b = 0;

    r = pow(r, 0.9);
    g = pow(g, 0.9);
	b = pow(b, 0.9);

	//if (r > 1) r = 1;
	//if (g > 1) g = 1;
	//if (b > 1) b = 1;

    Color col={r + 0.5, g + 0.5, b + 0.5, 255};
    return col;
}


Color get_palette_color(int palette_id, unsigned short id) {
    Color *color = sys.asset.palette[palette_id];
    return color[id];
}

Color get_palette_color_pro(int palette_id, unsigned short id, float alpha) {
    Color *color = sys.asset.palette[palette_id];
    return (Color){color[id].r, color[id].g, color[id].b, alpha};
}

Color get_pixel_color(Image *image, Vector2 position) {
    unsigned int offset = (position.y * image->width + position.x) * 4;
    Color *data = &image->data;
    return data[offset];
//    unsigned char r = data[offset];
//    unsigned char g = data[offset + 1];
//    unsigned char b = data[offset + 2];
//    unsigned char a = data[offset + 3];
//    return (Color){r, g, b, a};
}

// ********** G R I D   S Y S T E M  ***** G R I D   S Y S T E M  ***** G R I D   S Y S T E M  ***** B E G I N
// ********** G R I D   S Y S T E M  ***** G R I D   S Y S T E M  ***** G R I D   S Y S T E M  ***** B E G I N
// ********** G R I D   S Y S T E M  ***** G R I D   S Y S T E M  ***** G R I D   S Y S T E M  ***** B E G I N

typedef enum {
    GRID_BGBLEND_LLEFT      = 0b10000000000000000000000000000000, // background vertex color blend lower left
    GRID_BGBLEND_LRIGHT     = 0b01000000000000000000000000000000, // background vertex color blend lower right
    GRID_BGBLEND_URIGHT     = 0b00100000000000000000000000000000, // background vertex color blend upper right
    GRID_BGBLEND_ULEFT      = 0b00010000000000000000000000000000, // background vertex color blend upper left
    GRID_FGBLEND_LLEFT      = 0b00001000000000000000000000000000, // foreground vertex color blend lower left
    GRID_FGBLEND_LRIGHT     = 0b00000100000000000000000000000000, // foreground vertex color blend lower right
    GRID_FGBLEND_URIGHT     = 0b00000010000000000000000000000000, // foreground vertex color blend upper right
    GRID_FGBLEND_ULEFT      = 0b00000001000000000000000000000000, // foreground vertex color blend upper left
    GRID_PROTECTED          = 0b00000000100000000000000000000000, // protect value from being changed
    GRID_HIDDEN             = 0b00000000010000000000000000000000, // hide value (not displayed)
    GRID_CELLDIS            = 0b00000000001000000000000000000000, // turn on cell corners C1 to C4 displacements
    GRID_LINESSEQ           = 0b00000000000100000000000000000000, // turn on lines sequencing
    GRID_COLORSEQ           = 0b00000000000010000000000000000000, // turn on color sequencing
    GRID_VALUESEQ           = 0b00000000000001000000000000000000, // turn on cell value sequencing
    GRID_AUTOSCRX           = 0b00000000000000100000000000000000, // turn on automatic scrolling on x axis
    GRID_AUTOSCRY           = 0b00000000000000010000000000000000, // turn on automatic scrolling on y axis
    GRID_ROTATION           = 0b00000000000000001000000000000000, // turn on rotation 
    GRID_SKEW               = 0b00000000000000000100000000000000, // turn on cell skewing
    GRID_WRAP_X             = 0b00000000000000000010000000000000, // turn on wrap around on x axis
    GRID_WRAP_Y             = 0b00000000000000000001000000000000, // turn on wrap around on y axis
    GRID_SCALE_X            = 0b00000000000000000000100000000000, // turn on cell scaling on x axis
    GRID_SCALE_Y            = 0b00000000000000000000010000000000, // turn on cell scaling on y axis
    GRID_FLIPH              = 0b00000000000000000000001000000000, // flip cell(s) horizontally
    GRID_FLIPV              = 0b00000000000000000000000100000000, // flip cell(s) vertically
    GRID_RED                = 0b00000000000000000000000010000000, // turn on red channel
    GRID_GREEN              = 0b00000000000000000000000001000000, // turn on green channel
    GRID_BLUE               = 0b00000000000000000000000000100000, // turn on blue channel
    GRID_ALPHA              = 0b00000000000000000000000000010000, // turn on transparency
    GRID_LINES              = 0b00000000000000000000000000001000, // turn on lines tiles
    GRID_BACKGROUND         = 0b00000000000000000000000000000100, // turn on cell background (tile rectangle fill)
    GRID_SHADOW             = 0b00000000000000000000000000000010, // turn on shadow cell
    GRID_FOREGROUND         = 0b00000000000000000000000000000001, // turn on cell foreground (value)
    GRID_DEFAULT1           = 0b00000000011100000000000011111101, // DEFAULT STATE :HEAVY PROCESSING
    GRID_DEFAULT2           = 0b00000000000000000000000000000000, // DEFAULT STATE :LIGHT PROCESSING
    GRID_DEFAULT3           = 0b00000000000000000000000000000000, // DEFAULT STATE :GAME LAYER
    GRID_DEFAULT4           = 0b00000000000000000000000000000000  // DEFAULT STATE :TERMINAL DISPLAY
} grid_features;

typedef enum {
    LINE_TOP                = 0b10000000, // turn on line top
    LINE_BOT                = 0b01000000, // turn on line bottom
    LINE_LEF                = 0b00100000, // turn on line left
    LINE_RIG                = 0b00010000, // turn on line right
    LINE_HOR                = 0b00001000, // turn on line center horizontal
    LINE_VER                = 0b00000100, // turn on line center vertical
    LINE_UP                 = 0b00000010, // turn on line angle up
    LINE_DOW                = 0b00000001  // turn on line angle down
} lines_features;


Rectangle get_tilezone_from_position(int asset_id, Vector2 position) {
    EX_tileset *tileset = &sys.asset.tileset[asset_id];
    if ((position.x >= tileset->count.x) || position.x < 0) return (Rectangle) {0.f, 0.f, tileset->tilesize.x, tileset->tilesize.y};
    if ((position.y >= tileset->count.y) || position.y < 0) return (Rectangle) {0.f, 0.f, tileset->tilesize.y, tileset->tilesize.y};
    Vector2 *tilesize = &sys.asset.tileset[asset_id].tilesize;
    return (Rectangle) {position.x * tilesize->x, position.y * tilesize->y,  tilesize->x, tilesize->y};
}

Rectangle get_tilezone_from_code(int asset_id, int code) {
    EX_tileset *tileset = &sys.asset.tileset[asset_id];

    code -= sys.asset.tileset[asset_id].ascii_start;
    if (code > sys.asset.tileset[asset_id].total || code < 0) return (Rectangle) {0.f, 0.f, tileset->tilesize.x, tileset->tilesize.y};

    float px = code % (int)tileset->count.x;
    float py = (int)(code / (int)tileset->count.x);
    Vector2 *tilesize = &sys.asset.tileset[asset_id].tilesize;
    return (Rectangle) {px * tilesize->x, py * tilesize->y,  tilesize->x, tilesize->y};
}

//        plot_character(ex_scrolltext[s].font, ch, position, (Vector2) {text_scale}, (Vector2) {2, 4}, ex_scrolltext[s].text_angle, col, ex_scrolltext[s].bg_color, state);
void plot_character(int asset_id, int palette_id, int code, Vector2 position, Vector2 scale, Vector2 skew, Vector2 shadow, float angle, Color color_fg, Color color_bg, unsigned int state) {
    Color vertex_colors[4];
    if (!(state & GRID_ROTATION)) angle = 0.f;

    if (state & GRID_BACKGROUND) {
        vertex_colors[0] = color_bg;
        vertex_colors[1] = color_bg;
        vertex_colors[2] = color_bg;
        vertex_colors[3] = color_bg;
        DrawRectangleProSK(
            (Rectangle) { position.x, position.y, scale.x, scale.y },
            (Vector2) {0,0}, (Vector2) {0,0}, angle, vertex_colors);
    }
    if (state & GRID_FOREGROUND) {
            if (state & GRID_SHADOW) {
                vertex_colors[0] = (Color) {0.f, 0.f, 0.f, 48.f};
                vertex_colors[1] = (Color) {0.f, 0.f, 0.f, 48.f};
                vertex_colors[2] = (Color) {0.f, 0.f, 0.f, 48.f};
                vertex_colors[3] = (Color) {0.f, 0.f, 0.f, 48.f};
                DrawTextureProSK(sys.asset.tex[asset_id],
                    get_tilezone_from_code(asset_id, code),
                    (Rectangle) { position.x + shadow.x, position.y + shadow.y, scale.x, scale.y },
                    (Vector2) {0,0}, skew, angle, vertex_colors);
            };
            vertex_colors[0] = color_fg;
            vertex_colors[1] = color_fg;
            vertex_colors[2] = color_fg;
            vertex_colors[3] = color_fg;
            DrawTextureProSK(sys.asset.tex[asset_id],
                get_tilezone_from_code(asset_id, code),
                (Rectangle) { position.x, position.y , scale.x, scale.y },
                (Vector2) {0,0}, skew, angle, vertex_colors);
    }
}

bool init_cell_linear(EX_cell *cell, unsigned int cell_state, unsigned int color_id, unsigned int bg_color_id) {
    cell->state = cell_state;
    cell->value = 0;
    cell->fg_color_id = color_id;
    cell->bg_color_id = bg_color_id;
    cell->offset = (Vector2) {0,0};
    cell->scale = (Vector2) {1,1};
    cell->angle = 0;
    cell->fg_brightness = 1.f;
    cell->bg_brightness = 1.f;

    return 0;
}

bool init_layer(int page_id, int layer_id, Vector2 size, unsigned int layer_state, unsigned int cell_state, int asset_id) {
    int cell_count = (int)size.x * (int)size.y;
    EX_layer *layer = &sys.video.page[page_id].layer[layer_id];
    layer->size = size;
    layer->state = layer_state;
    layer->cell_count = cell_count;
    layer->cell = calloc(cell_count, sizeof(EX_cell));
    layer->offset = (Vector2) {0,0};
    layer->scale = (Vector2) {1,1};
    layer->angle = 0;
    layer->fg_brightness = 1.f;
    layer->bg_brightness = 1.f;

    EX_cell *cell = &sys.video.page[page_id].layer[layer_id].cell[0];
    for (int i = 0; i < cell_count; i++) {
        init_cell_linear(&cell[i], cell_state, 0, 0);
    }
    sys.video.page[page_id].layer[layer_id].asset_id = asset_id;
    
    return 0;
}

bool init_page(Vector2 size, unsigned int page_state, unsigned int layer_state, unsigned int cell_state, int asset_id) {
    int page_id = sys.video.current_virtual; // A single page per Virtual Display

    sys.video.page[page_id].state = page_state;
    sys.video.page[page_id].layer_count = 1;
    sys.video.page[page_id].layer = calloc(sys.video.page[page_id].layer_count, sizeof(EX_layer));
    init_layer(page_id, 0, size, layer_state, cell_state, asset_id);
    return 0;
}

// *************** REFERENCING SHORTCUTS TO USE *****************
// EX_page  *page  = &sys.video.page[page_id];
// EX_layer *layer = &sys.video.page[page_id].layer[layer_id];
// EX_cell  *cell  = &sys.video.page[page_id].layer[layer_id].cell[0]; ( cell[50].state )
// This functionality requires setting a bunch of stuff afterwards;
// - per cell states
// - per layer asset
bool init_page_multilayer(Vector2 size, unsigned int page_state, unsigned int layer_state[]) {
    int page_id = sys.video.current_virtual; // A single page per Virtual Display

    sys.video.page[page_id].state = page_state;
    sys.video.page[page_id].layer_count = sizeof(layer_state) / sizeof_member(EX_cell, state);

    sys.video.page[page_id].layer = calloc(sys.video.page[page_id].layer_count, sizeof(EX_layer));
    for (int i = 0; i < sys.video.page[page_id].layer_count; i++) {
        init_layer(page_id, i, size, layer_state[i], 0, 0);
    }
    return 0;
}

void layer_set_mouse_position(int page_id, int layer_id, Vector2 target) {
    sys.video.page[page_id].layer[layer_id].mouse.offset = target;
}

void layer_set_keyboard_position(int page_id, int layer_id, Vector2 target) {
    sys.video.page[page_id].layer[layer_id].keyboard.offset = target;
}

void set_cell_state(int page_id, int layer_id, Rectangle target, unsigned int state) {
    int linear_offset;
    EX_layer *layer = &sys.video.page[page_id].layer[layer_id];
    int lsx = layer->size.x, lsy = layer->size.y;
    EX_cell  *target_cell  = &sys.video.page[page_id].layer[layer_id].cell[0];

    if (target.x >= lsx || target.y >= lsy || (target.x + target.width) < 0 || (target.y + target.height) < 0) return;
    if ((target.x + target.width) > lsx) target.width = lsx - target.x; 
    if ((target.y + target.height) > lsy) target.height = lsy - target.y;

    for (int x = target.x; x++; x < (target.x + target.width)) {
        for (int y = target.y; y++; y < (target.y + target.height)) {
            linear_offset = lsx * y + x;
            BITS_ON(target_cell[linear_offset].state, state);
        }
    }
}

void clear_cell_state(int page_id, int layer_id, Rectangle target, unsigned int state) {
    int linear_offset;
    EX_layer *layer = &sys.video.page[page_id].layer[layer_id];
    int lsx = layer->size.x, lsy = layer->size.y;
    EX_cell  *target_cell  = &sys.video.page[page_id].layer[layer_id].cell[0];

    if (target.x >= lsx || target.y >= lsy || (target.x + target.width) < 0 || (target.y + target.height) < 0) return;
    if ((target.x + target.width) > lsx) target.width = lsx - target.x; 
    if ((target.y + target.height) > lsy) target.height = lsy - target.y;

    for (int x = target.x; x++; x < (target.x + target.width)) {
        for (int y = target.y; y++; y < (target.y + target.height)) {
            linear_offset = lsx * y + x;
            BITS_OFF(target_cell[linear_offset].state, state);
        }
    }
}

void set_cell_fg_color(int page_id, int layer_id, Rectangle target, int color_id) {
    int linear_offset;
    EX_layer *layer = &sys.video.page[page_id].layer[layer_id];
    int lsx = layer->size.x, lsy = layer->size.y;
    EX_cell  *target_cell  = &sys.video.page[page_id].layer[layer_id].cell[0];

    if (target.x >= lsx || target.y >= lsy || (target.x + target.width) < 0 || (target.y + target.height) < 0) return;
    if ((target.x + target.width) > lsx) target.width = lsx - target.x; 
    if ((target.y + target.height) > lsy) target.height = lsy - target.y;

    for (int x = target.x; x++; x < (target.x + target.width)) {
        for (int y = target.y; y++; y < (target.y + target.height)) {
            linear_offset = lsx * y + x;
            target_cell[linear_offset].fg_color_id = color_id;
        }
    }
}

void set_cell_bg_color(int page_id, int layer_id, Rectangle target, int color_id) {
    int linear_offset;
    EX_layer *layer = &sys.video.page[page_id].layer[layer_id];
    int lsx = layer->size.x, lsy = layer->size.y;
    EX_cell  *target_cell  = &sys.video.page[page_id].layer[layer_id].cell[0];

    if (target.x >= lsx || target.y >= lsy || (target.x + target.width) < 0 || (target.y + target.height) < 0) return;
    if ((target.x + target.width) > lsx) target.width = lsx - target.x; 
    if ((target.y + target.height) > lsy) target.height = lsy - target.y;

    for (int x = target.x; x++; x < (target.x + target.width)) {
        for (int y = target.y; y++; y < (target.y + target.height)) {
            linear_offset = lsx * y + x;
            target_cell[linear_offset].bg_color_id = color_id;
        }
    }
}

void set_cell_lines_color(int page_id, int layer_id, Rectangle target, int color_id) {
    int linear_offset;
    EX_layer *layer = &sys.video.page[page_id].layer[layer_id];
    int lsx = layer->size.x, lsy = layer->size.y;
    EX_cell  *target_cell  = &sys.video.page[page_id].layer[layer_id].cell[0];

    if (target.x >= lsx || target.y >= lsy || (target.x + target.width) < 0 || (target.y + target.height) < 0) return;
    if ((target.x + target.width) > lsx) target.width = lsx - target.x; 
    if ((target.y + target.height) > lsy) target.height = lsy - target.y;

    for (int x = target.x; x++; x < (target.x + target.width)) {
        for (int y = target.y; y++; y < (target.y + target.height)) {
            linear_offset = lsx * y + x;
            target_cell[linear_offset].lines_color_id = color_id;
        }
    }
}

void set_cell_color_mask(int page_id, int layer_id, Rectangle target, Color color) {
    int linear_offset;
    EX_layer *layer = &sys.video.page[page_id].layer[layer_id];
    int lsx = layer->size.x, lsy = layer->size.y;
    EX_cell  *target_cell  = &sys.video.page[page_id].layer[layer_id].cell[0];

    if (target.x >= lsx || target.y >= lsy || (target.x + target.width) < 0 || (target.y + target.height) < 0) return;
    if ((target.x + target.width) > lsx) target.width = lsx - target.x; 
    if ((target.y + target.height) > lsy) target.height = lsy - target.y;

    for (int x = target.x; x++; x < (target.x + target.width)) {
        for (int y = target.y; y++; y < (target.y + target.height)) {
            linear_offset = lsx * y + x;
            target_cell[linear_offset].color_mask = color;
        }
    }
}

void set_cell_color_shadow_mask(int page_id, int layer_id, Rectangle target, Color color) {
    int linear_offset;
    EX_layer *layer = &sys.video.page[page_id].layer[layer_id];
    int lsx = layer->size.x, lsy = layer->size.y;
    EX_cell  *target_cell  = &sys.video.page[page_id].layer[layer_id].cell[0];

    if (target.x >= lsx || target.y >= lsy || (target.x + target.width) < 0 || (target.y + target.height) < 0) return;
    if ((target.x + target.width) > lsx) target.width = lsx - target.x; 
    if ((target.y + target.height) > lsy) target.height = lsy - target.y;

    for (int x = target.x; x++; x < (target.x + target.width)) {
        for (int y = target.y; y++; y < (target.y + target.height)) {
            linear_offset = lsx * y + x;
            target_cell[linear_offset].shadow_mask = color;
        }
    }
}

void set_cell_offset(int page_id, int layer_id, Rectangle target, Vector2 offset) {
    int linear_offset;
    EX_layer *layer = &sys.video.page[page_id].layer[layer_id];
    int lsx = layer->size.x, lsy = layer->size.y;
    EX_cell  *target_cell  = &sys.video.page[page_id].layer[layer_id].cell[0];

    if (target.x >= lsx || target.y >= lsy || (target.x + target.width) < 0 || (target.y + target.height) < 0) return;
    if ((target.x + target.width) > lsx) target.width = lsx - target.x; 
    if ((target.y + target.height) > lsy) target.height = lsy - target.y;

    for (int x = target.x; x++; x < (target.x + target.width)) {
        for (int y = target.y; y++; y < (target.y + target.height)) {
            linear_offset = lsx * y + x;
            target_cell[linear_offset].offset = offset;
        }
    }
}

void set_cell_angle(int page_id, int layer_id, Rectangle target, float angle) {
    int linear_offset;
    EX_layer *layer = &sys.video.page[page_id].layer[layer_id];
    int lsx = layer->size.x, lsy = layer->size.y;
    EX_cell  *target_cell  = &sys.video.page[page_id].layer[layer_id].cell[0];

    if (target.x >= lsx || target.y >= lsy || (target.x + target.width) < 0 || (target.y + target.height) < 0) return;
    if ((target.x + target.width) > lsx) target.width = lsx - target.x; 
    if ((target.y + target.height) > lsy) target.height = lsy - target.y;

    for (int x = target.x; x++; x < (target.x + target.width)) {
        for (int y = target.y; y++; y < (target.y + target.height)) {
            linear_offset = lsx * y + x;
            target_cell[linear_offset].angle = angle;
        }
    }
}

void shift_cell_value(int page_id, int layer_id, Rectangle target, int shift) {
    int linear_offset;
    EX_layer *layer = &sys.video.page[page_id].layer[layer_id];
    int lsx = layer->size.x, lsy = layer->size.y;
    EX_cell  *target_cell  = &sys.video.page[page_id].layer[layer_id].cell[0];

    if (target.x >= lsx || target.y >= lsy || (target.x + target.width) < 0 || (target.y + target.height) < 0) return;
    if ((target.x + target.width) > lsx) target.width = lsx - target.x; 
    if ((target.y + target.height) > lsy) target.height = lsy - target.y;

    for (int x = target.x; x++; x < (target.x + target.width)) {
        for (int y = target.y; y++; y < (target.y + target.height)) {
            linear_offset = lsx * y + x;
            target_cell[linear_offset].value += shift;
        }
    }
}

void set_cell_scale(int page_id, int layer_id, Rectangle target, Vector2 scale) {
    int linear_offset;
    EX_layer *layer = &sys.video.page[page_id].layer[layer_id];
    int lsx = layer->size.x, lsy = layer->size.y;
    EX_cell  *target_cell  = &sys.video.page[page_id].layer[layer_id].cell[0];

    if (target.x >= lsx || target.y >= lsy || (target.x + target.width) < 0 || (target.y + target.height) < 0) return;
    if ((target.x + target.width) > lsx) target.width = lsx - target.x; 
    if ((target.y + target.height) > lsy) target.height = lsy - target.y;

    for (int x = target.x; x++; x < (target.x + target.width)) {
        for (int y = target.y; y++; y < (target.y + target.height)) {
            linear_offset = lsx * y + x;
            target_cell[linear_offset].scale = scale;
        }
    }
}

// iterate through charracter ascii codes, if font pixels then copy desired source_cell information to the layer
void plot_big_characters(int page_id, int layer_id, Vector2 target, unsigned int state, int font_id, EX_cell source_cell, unsigned char *ch) {
    int linear_offset;
    EX_layer *layer = &sys.video.page[page_id].layer[layer_id];
    int lsx = layer->size.x, lsy = layer->size.y;
    EX_cell  *target_cell  = &sys.video.page[page_id].layer[layer_id].cell[0];

    int length = sizeof(ch);

    for (int i= 0; i++; i<length) {

    }    
}

typedef enum {
    GRIDFIELD_RESERVED             = 0b10000000000000000000000000000000,
    GRIDFIELD_STATE                = 0b01000000000000000000000000000000,   // all flags for cell
    GRIDFIELD_VALUE                = 0b00010000000000000000000000000000,   // value of cell
    GRIDFIELD_LINES                = 0b00000010000000000000000000000000,   // lines feature
    GRIDFIELD_CYCLE                = 0b00000000000010000000000000000000,   // cell animation sequence number
    GRIDFIELD_FG_COLOR             = 0b00000000000000100000000000000000,   // palette index color for cell
    GRIDFIELD_FG_COLOR_CYCLE       = 0b00000000000000010000000000000000,   // color cycle index
    GRIDFIELD_BG_COLOR             = 0b00000000000000001000000000000000,   // palette index color for cell background
    GRIDFIELD_BG_COLOR_CYCLE       = 0b00000000000000000100000000000000,   // color cycle index
    GRIDFIELD_LINES_COLOR          = 0b00000000000000000010000000000000,   // palette index color for cell background
    GRIDFIELD_LINES_COLOR_CYCLE    = 0b00000000000000000001000000000000,   // color cycle index
    GRIDFIELD_OFFSET               = 0b00000000000000000000100000000000,   // displacement from top left (x,y)
    GRIDFIELD_SKEW                 = 0b00000000000000000000010000000000,   // horizontal and vertical skew
    GRIDFIELD_SCALE                = 0b00000000000000000000001000000000,   // (x,y) cell scale
    GRIDFIELD_SCALE_SPEED          = 0b00000000000000000000000100000000,   // (x,y) cell scale speed
    GRIDFIELD_SCROLL_SPEED         = 0b00000000000000000000000010000000,   // (x,y) cell scroll speed
    GRIDFIELD_ANGLE                = 0b00000000000000000000000001000000,   // degree of angle used to rotate the cell
    GRIDFIELD_FG_BRIGHTNESS        = 0b00000000000000000000000000100000,   // foreground brightness (values 0...1 divides, values 1 to 255 multiply)
    GRIDFIELD_BG_BRIGHTNESS        = 0b00000000000000000000000000010000,   // background brightness (values 0...1 divides, values 1 to 255 multiply)
    GRIDFIELD_COLOR_MASK           = 0b00000000000000000000000000001000,   // RGBA color mask of cell
    GRIDFIELD_SHADOW_MASK          = 0b00000000000000000000000000000100,   // shadow RGBA mask
    GRIDFIELD_ALL                  = 0b01111111111111111111111111111111,   // all fields
    GRIDFIELD_ALL_BUT_STATE        = 0b00111111111111111111111111111111    // all fields except the state of the cell
} gridfield_features;

void init_cell (int page_id, int layer_id, Rectangle target, EX_cell info_cell, unsigned int state) {
    int target_offset, source_offset;
    EX_layer *layer = &sys.video.page[page_id].layer[layer_id];
    int lsx = layer->size.x, lsy = layer->size.y;
    EX_cell  *target_cell  = &sys.video.page[page_id].layer[layer_id].cell[0];

    if (target.x >= lsx || target.y >= lsy || (target.x + target.width) < 0 || (target.y + target.height) < 0) return;

    for (int x = target.x; x++; x < (target.x + target.width)) {
        if (x >=0 && x < lsx ) {
            for (int y = target.y; y++; y < (target.y + target.height)) {
                if (y >= 0 && y < lsy) {
                    target_offset = lsx * y + x;
                    if (state & GRIDFIELD_ALL)                   target_cell[target_offset]                       = info_cell;
                    else {
                        if (state & GRIDFIELD_STATE)             target_cell[target_offset].state                 = info_cell.state;
                        if (state & GRIDFIELD_VALUE)             target_cell[target_offset].value                 = info_cell.value;
                        if (state & GRIDFIELD_LINES)             target_cell[target_offset].lines                 = info_cell.lines;
                        if (state & GRIDFIELD_CYCLE)             target_cell[target_offset].cycle_id              = info_cell.cycle_id;
                        if (state & GRIDFIELD_FG_COLOR)          target_cell[target_offset].fg_color_id           = info_cell.fg_color_id;
                        if (state & GRIDFIELD_FG_COLOR_CYCLE)    target_cell[target_offset].fg_color_cycle_id     = info_cell.fg_color_cycle_id;
                        if (state & GRIDFIELD_BG_COLOR)          target_cell[target_offset].bg_color_id           = info_cell.bg_color_id;
                        if (state & GRIDFIELD_BG_COLOR_CYCLE)    target_cell[target_offset].bg_color_cycle_id     = info_cell.bg_color_cycle_id;
                        if (state & GRIDFIELD_LINES_COLOR)       target_cell[target_offset].lines_color_id        = info_cell.lines_color_id;
                        if (state & GRIDFIELD_LINES_COLOR_CYCLE) target_cell[target_offset].lines_color_cycle_id  = info_cell.lines_color_cycle_id;
                        if (state & GRIDFIELD_OFFSET)            target_cell[target_offset].offset                = info_cell.offset;
                        if (state & GRIDFIELD_SKEW)              target_cell[target_offset].skew                  = info_cell.skew;
                        if (state & GRIDFIELD_SCALE)             target_cell[target_offset].scale                 = info_cell.scale;
                        if (state & GRIDFIELD_SCALE_SPEED)       target_cell[target_offset].scale_speed           = info_cell.scale_speed;
                        if (state & GRIDFIELD_SCROLL_SPEED)      target_cell[target_offset].scroll_speed          = info_cell.scroll_speed;
                        if (state & GRIDFIELD_ANGLE)             target_cell[target_offset].angle                 = info_cell.angle;
                        if (state & GRIDFIELD_FG_BRIGHTNESS)     target_cell[target_offset].fg_brightness         = info_cell.fg_brightness;
                        if (state & GRIDFIELD_BG_BRIGHTNESS)     target_cell[target_offset].bg_brightness         = info_cell.bg_brightness;
                        if (state & GRIDFIELD_COLOR_MASK)        target_cell[target_offset].color_mask            = info_cell.color_mask;
                        if (state & GRIDFIELD_SHADOW_MASK)       target_cell[target_offset].shadow_mask           = info_cell.shadow_mask;
                    }
                }
            }
        }
    }
}

void clear_cell (int page_id, int layer_id, Rectangle target, unsigned int state) {
    static inline EX_cell blank_cell;
    init_cell(page_id, layer_id, target, blank_cell, state);
}


typedef enum {
    GRIDSHIFT_UP        = 1,
    GRIDSHIFT_DOWN      = 2,
    GRIDSHIFT_LEFT      = 3,
    GRIDSHIFT_RIGHT     = 4,
    GRIDSHIFT_UPLEFT    = 5,
    GRIDSHIFT_DOWNLEFT  = 6,
    GRIDSHIFT_UPRIGHT   = 7,
    GRIDSHIFT_DOWNRIGHT = 8
};

void shift_cell (int page_id, int layer_id, Rectangle source, unsigned char shift_method, bool cycle, unsigned int state) {
}

void copy_cell_in_layer(int page_id, int layer_id, Rectangle source, Vector2 target, unsigned int state) {
    int source_offset, target_offset;
    EX_layer *layer = &sys.video.page[page_id].layer[layer_id];
    int lsx = layer->size.x, lsy = layer->size.y;
    EX_cell  *cell  = &sys.video.page[page_id].layer[layer_id].cell[0];
    
    if (source.x >= lsx || source.y >= lsy || target.x >= lsx || target.y >= lsy) return;
    if ((source.x + source.width) < 0 || (source.y + source.height) < 0 || (target.x + source.width) < 0 || (target.y + source.height) < 0) return;
    if ((source.x + source.width) > lsx) source.width = lsx - source.x;
    if ((source.y + source.width) > lsy) source.width = lsy - source.y;
    int tx = target.x - source.x; // horizontal target displacement (can be positive or negative depending if target is left or right of source)
    int ty = target.y - source.y; // vertical target displacement (can be positive or negative depending if target is above or below of source)
    int xa, xb, xi, ya, yb, yi;
    if (tx <= 0) {xa = source.x; xb = (source.x + source.width); xi = 1;} else {xa = (source.x + source.width); xb = source.x; xi = -1;} // horizontal scanning parameters
    if (ty <= 0) {ya = source.y; yb = (source.y + source.height); yi = 1;} else {ya = (source.y + source.height); yb = source.y; yi = -1;} // vertical scanning parameters
    int y = ya;
    while (1) {
        if (y >=0 && (y + ty) < lsy && (y + ty) >= 0) {
            int x = xa;
            while (1) {
                if (x >= 0 && ((x + tx) < lsx) && (x + tx) >= 0) {
                    source_offset = lsx * y + x;
                    target_offset = lsx * (y + ty) + (x + tx);
                    if (state & GRIDFIELD_ALL)                   cell[target_offset]                       = cell[source_offset];
                    else {
                        if (state & GRIDFIELD_STATE)             cell[target_offset].state                 = cell[source_offset].state;
                        if (state & GRIDFIELD_VALUE)             cell[target_offset].value                 = cell[source_offset].value;
                        if (state & GRIDFIELD_LINES)             cell[target_offset].lines                 = cell[source_offset].lines;
                        if (state & GRIDFIELD_CYCLE)             cell[target_offset].cycle_id              = cell[source_offset].cycle_id;
                        if (state & GRIDFIELD_FG_COLOR)          cell[target_offset].fg_color_id           = cell[source_offset].fg_color_id;
                        if (state & GRIDFIELD_FG_COLOR_CYCLE)    cell[target_offset].fg_color_cycle_id     = cell[source_offset].fg_color_cycle_id;
                        if (state & GRIDFIELD_BG_COLOR)          cell[target_offset].bg_color_id           = cell[source_offset].bg_color_id;
                        if (state & GRIDFIELD_BG_COLOR_CYCLE)    cell[target_offset].bg_color_cycle_id     = cell[source_offset].bg_color_cycle_id;
                        if (state & GRIDFIELD_LINES_COLOR)       cell[target_offset].lines_color_id        = cell[source_offset].lines_color_id;
                        if (state & GRIDFIELD_LINES_COLOR_CYCLE) cell[target_offset].lines_color_cycle_id  = cell[source_offset].lines_color_cycle_id;
                        if (state & GRIDFIELD_OFFSET)            cell[target_offset].offset                = cell[source_offset].offset;
                        if (state & GRIDFIELD_SKEW)              cell[target_offset].skew                  = cell[source_offset].skew;
                        if (state & GRIDFIELD_SCALE)             cell[target_offset].scale                 = cell[source_offset].scale;
                        if (state & GRIDFIELD_SCALE_SPEED)       cell[target_offset].scale_speed           = cell[source_offset].scale_speed;
                        if (state & GRIDFIELD_SCROLL_SPEED)      cell[target_offset].scroll_speed          = cell[source_offset].scroll_speed;
                        if (state & GRIDFIELD_ANGLE)             cell[target_offset].angle                 = cell[source_offset].angle;
                        if (state & GRIDFIELD_FG_BRIGHTNESS)     cell[target_offset].fg_brightness         = cell[source_offset].fg_brightness;
                        if (state & GRIDFIELD_BG_BRIGHTNESS)     cell[target_offset].bg_brightness         = cell[source_offset].bg_brightness;
                        if (state & GRIDFIELD_COLOR_MASK)        cell[target_offset].color_mask            = cell[source_offset].color_mask;
                        if (state & GRIDFIELD_SHADOW_MASK)       cell[target_offset].shadow_mask           = cell[source_offset].shadow_mask;
                    }
                }
                x += xi; if (xi == 1) {if (x >= xb) break;} else if (x < xb) break;
            }
        }
        y += yi; if (yi == 1) {if (y >= yb) break;} else if (y < yb) break;
    }
}

void copy_cell_to_layer(int source_page_id, int source_layer_id, Rectangle source, int target_page_id, int target_layer_id, Vector2 target, unsigned int state) {
    int source_offset, target_offset;

    EX_layer *source_layer = &sys.video.page[source_page_id].layer[source_layer_id];
    int lsx = source_layer->size.x, lsy = source_layer->size.y;
    EX_cell  *source_cell  = &sys.video.page[source_page_id].layer[source_layer_id].cell[0];

    EX_layer *target_layer = &sys.video.page[target_page_id].layer[target_layer_id];
    int ltx = target_layer->size.x, lty = target_layer->size.y;
    EX_cell  *target_cell  = &sys.video.page[target_page_id].layer[target_layer_id].cell[0];

    if (source.x >= lsx || source.y >= lsy || target.x >= ltx || target.y >= lty) return;
    if ((source.x + source.width) < 0 || (source.y + source.height) < 0 || (target.x + source.width) < 0 || (target.x + source.height) < 0) return;

    if ((source.x + source.width) > lsx) source.width = lsx - source.x;
    if ((source.y + source.width) > lsy) source.width = lsy - source.y;
    int tx = target.x - source.x; // horizontal target displacement (can be positive or negative depending if target is left or right of source)
    int ty = target.y - source.y; // vertical target displacement (can be positive or negative depending if target is above or below of source)
    for (int x = source.x; x++; x < (source.x + source.width)) {
        if ( (x + tx) < lsx && (x + tx) < ltx && (x + tx) >= 0 ) {
            for (int y = source.y; y++; y < (source.y + source.height)) {
                if ( (y + ty) < lsy && (y + ty) < lty && (y + ty) >= 0 ) {
                    source_offset = lsx * y + x;
                    target_offset = ltx * (y + ty) + (x + tx);
                    if (state & GRIDFIELD_ALL)                   target_cell[target_offset]                       = source_cell[source_offset];
                    else {
                        if (state & GRIDFIELD_STATE)             target_cell[target_offset].state                 = source_cell[source_offset].state;
                        if (state & GRIDFIELD_VALUE)             target_cell[target_offset].value                 = source_cell[source_offset].value;
                        if (state & GRIDFIELD_LINES)             target_cell[target_offset].lines                 = source_cell[source_offset].lines;
                        if (state & GRIDFIELD_CYCLE)             target_cell[target_offset].cycle_id              = source_cell[source_offset].cycle_id;
                        if (state & GRIDFIELD_FG_COLOR)          target_cell[target_offset].fg_color_id           = source_cell[source_offset].fg_color_id;
                        if (state & GRIDFIELD_FG_COLOR_CYCLE)    target_cell[target_offset].fg_color_cycle_id     = source_cell[source_offset].fg_color_cycle_id;
                        if (state & GRIDFIELD_BG_COLOR)          target_cell[target_offset].bg_color_id           = source_cell[source_offset].bg_color_id;
                        if (state & GRIDFIELD_BG_COLOR_CYCLE)    target_cell[target_offset].bg_color_cycle_id     = source_cell[source_offset].bg_color_cycle_id;
                        if (state & GRIDFIELD_LINES_COLOR)       target_cell[target_offset].lines_color_id        = source_cell[source_offset].lines_color_id;
                        if (state & GRIDFIELD_LINES_COLOR_CYCLE) target_cell[target_offset].lines_color_cycle_id  = source_cell[source_offset].lines_color_cycle_id;
                        if (state & GRIDFIELD_OFFSET)            target_cell[target_offset].offset                = source_cell[source_offset].offset;
                        if (state & GRIDFIELD_SKEW)              target_cell[target_offset].skew                  = source_cell[source_offset].skew;
                        if (state & GRIDFIELD_SCALE)             target_cell[target_offset].scale                 = source_cell[source_offset].scale;
                        if (state & GRIDFIELD_SCALE_SPEED)       target_cell[target_offset].scale_speed           = source_cell[source_offset].scale_speed;
                        if (state & GRIDFIELD_SCROLL_SPEED)      target_cell[target_offset].scroll_speed          = source_cell[source_offset].scroll_speed;
                        if (state & GRIDFIELD_ANGLE)             target_cell[target_offset].angle                 = source_cell[source_offset].angle;
                        if (state & GRIDFIELD_FG_BRIGHTNESS)     target_cell[target_offset].fg_brightness         = source_cell[source_offset].fg_brightness;
                        if (state & GRIDFIELD_BG_BRIGHTNESS)     target_cell[target_offset].bg_brightness         = source_cell[source_offset].bg_brightness;
                        if (state & GRIDFIELD_COLOR_MASK)        target_cell[target_offset].color_mask            = source_cell[source_offset].color_mask;
                        if (state & GRIDFIELD_SHADOW_MASK)       target_cell[target_offset].shadow_mask           = source_cell[source_offset].shadow_mask;
                    }
                }
            }
        }
    }
}

void render_layer(int layer_id) {
    int page_id = sys.video.current_virtual; // A single page per Virtual Display

    EX_layer *layer = &sys.video.page[page_id].layer[layer_id];
    EX_cell  *cell  = &sys.video.page[page_id].layer[layer_id].cell[0];
    int offset;
    int lsx = layer->size.x, sy = layer->size.y;
    for (int x = 0; x < lsx; x++) {
        for (int y = 0; y < sy; y++) {
            offset = lsx * y + x;
            EX_cell *c = &cell[offset];
            // we have the cell data we can use it to draw our background, foreground and shadow
            // calculate position x,y
            // ascii code is in c.value
            // reading color from palette get_palette_color(palette,id);
/*
                    unsigned int state = GRID_FOREGROUND | GRID_RED | GRID_GREEN | GRID_BLUE | GRID_SCALE_X | GRID_SCALE_Y;
                    if (ex_scrolltext[s].bg_color_flag > 0) state |= GRID_BACKGROUND;
                    if (ex_scrolltext[s].text_angle)        state |= GRID_ROTATION;
                    if (ex_scrolltext[s].text_shadow > 0.0) state |= GRID_SHADOW;
                    if (!(ex_scrolltext[s].text_angle))     state |= GRID_SKEW;
                    plot_character(ex_scrolltext[s].font_id, ex_scrolltext[s].palette_id, ch,
                        (Vector2) {x * text_scale, y * text_scale}, 
                        (Vector2) {text_scale, text_scale}, 
                        ex_scrolltext[s].skew,
                        (Vector2) {2, 2},
                        ex_scrolltext[s].text_angle, 
                        get_palette_color_pro(palette_id, ex_scrolltext[s].fg_color, ex_scrolltext[s].alpha), 
                        get_palette_color_pro(palette_id, ex_scrolltext[s].bg_color, ex_scrolltext[s].alpha), 
                        state);
*/
        }
    }
//logic to show mouse cursor
//IsCursorOnScreen(void)
//RLAPI Vector2 GetMousePosition(void);                         // Get mouse position XY
}

void render_page() {
    int page_id = sys.video.current_virtual; // A single page per Virtual Display
    EX_page  *page  = &sys.video.page[page_id];

//begin draw necessary here

    for (int i = 0; i < sys.video.page[page_id].layer_count; i++) {
        render_layer(i);
    }
    return 0;
// end draw here
}

void process_layer(int layer_id) {

}

void process_page(int page_id) {
    
}

/*char* load_page(int page_id, const char*, size_t, char*) {
}
*/

void deinit_layer(int id) {
    
}


// ********** G R I D   S Y S T E M  ***** G R I D   S Y S T E M  ***** G R I D   S Y S T E M  ***** E N D
// ********** G R I D   S Y S T E M  ***** G R I D   S Y S T E M  ***** G R I D   S Y S T E M  ***** E N D
// ********** G R I D   S Y S T E M  ***** G R I D   S Y S T E M  ***** G R I D   S Y S T E M  ***** E N D

// ********** A S S E T   S Y S T E M  ***** A S S E T   S Y S T E M  ***** A S S E T   S Y S T E M  ***** B E G I N
// ********** A S S E T   S Y S T E M  ***** A S S E T   S Y S T E M  ***** A S S E T   S Y S T E M  ***** B E G I N
// ********** A S S E T   S Y S T E M  ***** A S S E T   S Y S T E M  ***** A S S E T   S Y S T E M  ***** B E G I N

typedef enum {
    ASSET_RESERVED      = 0b10000000000000000000000000000000, //
    ASSET_ICON          = 0b01000000000000000000000000000000, // image loaded as Game Icon
    ASSET_PALETTE       = 0b00100000000000000000000000000000, // image loaded as palette
    ASSET_TEXTURE       = 0b00010000000000000000000000000000, // image loaded as texture
    ASSET_FONT          = 0b00001000000000000000000000000000, // image loaded as font
    ASSET_TILESET       = 0b00000100000000000000000000000000, // image loaded as tileset
    ASSET_FRAMEBUFFER   = 0b00000010000000000000000000000000, // image created as frame buffer
    ASSET_XM            = 0b00000001000000000000000000000000, // music loaded xm tracker
    ASSET_WAV           = 0b00000000100000000000000000000000, // sound loaded wav 
    ASSET_MP3           = 0b00000000010000000000000000000000, // sound loaded mp3
    ASSET_AUDIOSTREAM   = 0b00000000001000000000000000000000, // audio stream created
    ASSET_TEXT          = 0b00000000000100000000000000000000, // text content loaded
    ASSET_SHADER        = 0b00000000000010000000000000000000, // shader program
    ASSET_JSON          = 0b00000000000001000000000000000000, // scripted JSON content
    ASSET_SCRIPT        = 0b00000000000000100000000000000000, // scripted content loaded (not decided on language)
    ASSET_DATA          = 0b00000000000000010000000000000000, // data content loaded
    ASSET_TYPES         = 0b11111111111111110000000000000000, // All asset type definitions

    ASSET_RESERVED2     = 0b00000000000000001000000000000000, // 
    ASSET_COPY          = 0b00000000000000000100000000000000, // is a copy
    ASSET_REMOVE        = 0b00000000000000000010000000000000, // flagged for removal
    ASSET_UPDATE        = 0b00000000000000000001000000000000, // flagged for update
    ASSET_RUN           = 0b00000000000000000000100000000000, // flagged for execution (scripts)
    ASSET_STOP          = 0b00000000000000000000010000000000, // flagged for a stop (scripts)
    ASSET_UNLOADED      = 0b00000000000000000000001000000000, // was unloaded
    ASSET_LOADED        = 0b00000000000000000000000100000000, // was loaded
    ASSET_COMPRESSED    = 0b00000000000000000000000010000000, // uses raylib's compression method
    ASSET_DECOMPRESSED  = 0b00000000000000000000000001000000, // was compressed
    ASSET_EXPIRED       = 0b00000000000000000000000000100000, // not used anymore
    ASSET_ISSUE         = 0b00000000000000000000000000010000, // found an issue with the asset
    ASSET_LOCKED        = 0b00000000000000000000000000001000, // inaccessible
    ASSET_UPDATED       = 0b00000000000000000000000000000100, // was updated
    ASSET_ACTIVE        = 0b00000000000000000000000000000010, // can actively be used
    ASSET_INITIALIZED   = 0b00000000000000000000000000000001, // passed through the initialisation process successfully
    ASSET_TYPE_UNKNOWN  = 0b00000000000000000000000000000000, // not assigned = unknown
    ASSET_STATUS        = 0b00000000000000001111111111111111, 
    ASSET_NULL          = 0b00000000000000000000000000000000  
} asset_state;

unsigned int asset_type(unsigned int state) {
    return (state & ASSET_TYPES);
}

void update_assets(void) {
    for (int id = 0; id < sys.asset.total_assets; id++) {
        if ((sys.asset.state[id] & ASSET_UPDATE) && (sys.asset.state[id] & ASSET_ACTIVE)) {
            switch (sys.asset.asset_type[id]) {
                case ASSET_ICON : // assigns window icon for operating system
                SetWindowIcon(sys.asset.img[id]);
                BITS_OFF(sys.asset.state[id], ASSET_UPDATE);
                BITS_ON(sys.asset.state[id], ASSET_UPDATED);
                break;

                case ASSET_PALETTE : // palette is also loaded as texture
                sys.asset.palette[id] = LoadImagePalette(sys.asset.img[id], MAXPALETTECOLORS, &sys.asset.palette_colors[id]);
                UpdateTexture(sys.asset.tex[id], sys.asset.img[id].data);
                BITS_OFF(sys.asset.state[id], ASSET_UPDATE);
                BITS_ON(sys.asset.state[id], ASSET_UPDATED);
                break;

                case ASSET_TEXTURE :
                UpdateTexture(sys.asset.tex[id], sys.asset.img[id].data);
                BITS_OFF(sys.asset.state[id], ASSET_UPDATE);
                BITS_ON(sys.asset.state[id], ASSET_UPDATED);
                break;

                case ASSET_FONT :
                UpdateTexture(sys.asset.font[id].texture, sys.asset.img[id].data);
                BITS_OFF(sys.asset.state[id], ASSET_UPDATE);
                BITS_ON(sys.asset.state[id], ASSET_UPDATED);
                break;

                case ASSET_TILESET :
                UpdateTexture(sys.asset.tileset[id].tex, sys.asset.img[id].data);
                BITS_OFF(sys.asset.state[id], ASSET_UPDATE);
                BITS_ON(sys.asset.state[id], ASSET_UPDATED);
                break;

                case ASSET_FRAMEBUFFER :
                //sys.asset.framebuffer[id] = LoadRenderTexture( sys.video.virtual_res[sys.video.current_virtual].x, sys.video.virtual_res[sys.video.current_virtual].y );
                //LoadTextureFromImage(sys.asset.tileset[id].texture, sys.asset.img[id].data);
                BITS_OFF(sys.asset.state[id], ASSET_UPDATE);
                BITS_ON(sys.asset.state[id], ASSET_UPDATED);
                break;
                
                default: // THIS IS AN ISSUE!!!!!
                BITS_OFF(sys.asset.state[id], ASSET_UPDATE);
                BITS_ON(sys.asset.state[id], ASSET_ISSUE); // scheduled for update but unknown asset in updater process, trigger issue

                break;
            }
       }
    }    
}

int load_asset (unsigned int assettype, const char* fileName, const char* fileType, const unsigned char* fileData, int dataSize, int pak) {
    debug_console_out("int load_asset (unsigned int assettype, const char* fileName, const char* fileType, const unsigned char* fileData, int dataSize, int pak)");
    int id = sys.asset.total_assets;

    INIT(sys.asset.state[id], ASSET_INITIALIZED & assettype);

    if (fileName > NULL) strcpy(sys.asset.name, fileName);

    int dataSize_decompressed = 0;
    unsigned char *fileData_decompressed;
    if (pak) {
        BITS_ON(sys.asset.state[id], ASSET_COMPRESSED);
        fileData_decompressed = DecompressData(fileData, dataSize, &dataSize_decompressed);
        fileData = fileData_decompressed;
        dataSize = dataSize_decompressed;
    }

    switch (assettype) {
            case ASSET_ICON : // assigns icon for window operating system
            sys.asset.img[id] = LoadImageFromMemory(fileType, fileData, dataSize);
            BITS_ON(sys.asset.state[id], ASSET_LOADED);
         	SetWindowIcon(sys.asset.img[id]);
            sys.asset.data[id] = fileData;
            BITS_ON(sys.asset.state[id], ASSET_DATA);
            sys.asset.data_size[id] = dataSize;
            sys.asset.asset_type[id] = assettype;
            break;

            case ASSET_PALETTE : // palette is also loaded as texture
            sys.asset.img[id] = LoadImageFromMemory(fileType, fileData, dataSize);
            BITS_ON(sys.asset.state[id], ASSET_LOADED);
            sys.asset.palette_colors[id] = 0;
            sys.asset.palette[id] = LoadImagePalette(sys.asset.img[id], MAXPALETTECOLORS, &sys.asset.palette_colors[id]);
            sys.asset.tex[id] = LoadTextureFromImage(sys.asset.img[id]);
            BITS_ON(sys.asset.state[id], ASSET_TEXTURE);
            sys.asset.tileset[id].tex = sys.asset.tex[id];
            BITS_ON(sys.asset.state[id], ASSET_TILESET);
            sys.asset.data[id] = fileData;
            BITS_ON(sys.asset.state[id], ASSET_DATA);
            sys.asset.data_size[id] = dataSize;
            sys.asset.asset_type[id] = assettype;
            break;

            case ASSET_TEXTURE :
            sys.asset.img[id] = LoadImageFromMemory(fileType, fileData, dataSize);
            BITS_ON(sys.asset.state[id], ASSET_LOADED);
            sys.asset.tex[id] = LoadTextureFromImage(sys.asset.img[id]);
            sys.asset.data[id] = fileData;
            BITS_ON(sys.asset.state[id], ASSET_DATA);
            sys.asset.data_size[id] = dataSize;
            sys.asset.asset_type[id] = assettype;
            break;

            case ASSET_FONT :
            sys.asset.img[id] = LoadImageFromMemory(fileType, fileData, dataSize);
            BITS_ON(sys.asset.state[id], ASSET_LOADED);
            sys.asset.font[id].texture = LoadTextureFromImage(sys.asset.img[id]);
            BITS_ON(sys.asset.state[id], ASSET_TEXTURE);
            sys.asset.data[id] = fileData;
            BITS_ON(sys.asset.state[id], ASSET_DATA);
            sys.asset.data_size[id] = dataSize;
            sys.asset.asset_type[id] = assettype;
            break;

            case ASSET_TILESET :
            sys.asset.img[id] = LoadImageFromMemory(fileType, fileData, dataSize);
            BITS_ON(sys.asset.state[id], ASSET_LOADED);
            sys.asset.tex[id] = LoadTextureFromImage(sys.asset.img[id]);
            BITS_ON(sys.asset.state[id], ASSET_TEXTURE);
            sys.asset.tileset[id].tex = sys.asset.tex[id];
            sys.asset.data[id] = fileData;
            BITS_ON(sys.asset.state[id], ASSET_DATA);
            sys.asset.data_size[id] = dataSize;
            sys.asset.asset_type[id] = assettype;
            break;

            case ASSET_FRAMEBUFFER : // set current_virtual prior to use
            sys.asset.framebuffer[id] = LoadRenderTexture( sys.video.virtual_res[sys.video.current_virtual].x, sys.video.virtual_res[sys.video.current_virtual].y );
            BITS_ON(sys.asset.state[id], ASSET_LOADED);
            SetTextureFilter(sys.asset.framebuffer[id].texture, FILTER_POINT);
            sys.asset.data_size[id] = dataSize; // ??????????? WRONG !! There is no dataSize passed... so that is a NULL
            sys.video.virtual_asset[sys.video.current_virtual] = id;
            sys.asset.asset_type[id] = assettype;  
            break;

            case ASSET_SHADER :
            BITS_ON(sys.asset.state[id], ASSET_LOADED);
            // sys.asset.shader[id] = LoadShaderFromMemory(const char *vsCode, const char *fsCode)
            sys.asset.data[id] = fileData;
            BITS_ON(sys.asset.state[id], ASSET_DATA);
            sys.asset.data_size[id] = dataSize;
            sys.asset.asset_type[id] = assettype;
            break;

            case ASSET_XM :
            sys.asset.music[id] = LoadMusicStreamFromMemory(fileType, fileData, dataSize);
            BITS_ON(sys.asset.state[id], ASSET_LOADED);
            sys.asset.data[id] = fileData;
            BITS_ON(sys.asset.state[id], ASSET_DATA);
            sys.asset.data_size[id] = dataSize;
            sys.asset.asset_type[id] = assettype;
            break;

            case ASSET_WAV : // incomplete*********************************** get raylib functionality
            BITS_ON(sys.asset.state[id], ASSET_LOADED);
            sys.asset.data[id] = fileData;
            BITS_ON(sys.asset.state[id], ASSET_DATA);
            sys.asset.data_size[id] = dataSize;
            sys.asset.asset_type[id] = assettype;
            break;

            case ASSET_MP3 : // incomplete*********************************** get raylib functionality
            BITS_ON(sys.asset.state[id], ASSET_LOADED);
            sys.asset.data[id] = fileData;
            BITS_ON(sys.asset.state[id], ASSET_DATA);
            sys.asset.data_size[id] = dataSize;
            sys.asset.asset_type[id] = assettype;
            break;

            case ASSET_AUDIOSTREAM :
            BITS_ON(sys.asset.state[id], ASSET_LOADED);
            sys.asset.data_size[id] = dataSize;
            sys.asset.asset_type[id] = assettype;
            break;
            
            case ASSET_TEXT :
            BITS_ON(sys.asset.state[id], ASSET_LOADED);
            sys.asset.data[id] = fileData;
            BITS_ON(sys.asset.state[id], ASSET_DATA);
            sys.asset.data_size[id] = dataSize;
            sys.asset.asset_type[id] = assettype;
            break;

            case ASSET_DATA :
            BITS_ON(sys.asset.state[id], ASSET_LOADED);
            sys.asset.data[id] = fileData;
            BITS_ON(sys.asset.state[id], ASSET_DATA);
            sys.asset.data_size[id] = dataSize;
            sys.asset.asset_type[id] = assettype;
            break;

            default :
            BITS_ON(sys.asset.state[id], ASSET_ISSUE); // scheduled for initialisation but unknown asset in process, trigger issue
    }

    BITS_ON(sys.asset.state[id], ASSET_ACTIVE);

    //if (dataSize_decompressed) {
    if (pak) {
        MemFree(fileData_decompressed);
        BITS_ON(sys.asset.state[id], ASSET_DECOMPRESSED);
    };

    sys.asset.total_assets += 1;
    return id;
}


int load_palette(Vector2 count, const char* fileName, const char* fileType, const unsigned char* fileData, int dataSize, int pak) {
    int asset_id = load_asset(ASSET_PALETTE, fileName, fileType, fileData, dataSize, pak);
    float width = (float)sys.asset.img[asset_id].width;
    float height = (float)sys.asset.img[asset_id].height;

    sys.asset.tileset[asset_id].ascii_start = 0;
    sys.asset.tileset[asset_id].tilesize.x = width / count.x;
    sys.asset.tileset[asset_id].tilesize.y = height / count.y;
    sys.asset.tileset[asset_id].count.x = count.x;
    sys.asset.tileset[asset_id].count.y = count.y;
    sys.asset.tileset[asset_id].total = count.x * count.y;
    return asset_id;
}


int load_tileset(Vector2 count, const char* fileName, const char* fileType, const unsigned char* fileData, int dataSize, int pak, int ascii_start) {

    int asset_id = load_asset(ASSET_TILESET, fileName, fileType, fileData, dataSize, pak);
    float width = (float)sys.asset.img[asset_id].width;
    float height = (float)sys.asset.img[asset_id].height;

    sys.asset.tileset[asset_id].ascii_start = ascii_start;
    sys.asset.tileset[asset_id].tilesize.x = width / count.x;
    sys.asset.tileset[asset_id].tilesize.y = height / count.y;
    sys.asset.tileset[asset_id].count.x = count.x;
    sys.asset.tileset[asset_id].count.y = count.y;
    sys.asset.tileset[asset_id].total = count.x * count.y;

//    printf("%s WIDTH=%f, HEIGHT=%f, COUNT (%f, %f), SIZE (%f, %f) \n", fileName, width, height, count.x, count.y, sys.asset.tileset[asset_id].tilesize.x, sys.asset.tileset[asset_id].tilesize.y);
    return asset_id;
}

static void unload_asset(unsigned int id) {
    if (sys.asset.state[id] && ASSET_ACTIVE) {
        sys.asset.state[id] |= ASSET_EXPIRED;
        int assettype = asset_type(sys.asset.asset_type[id]);
        switch (assettype) {
            case ASSET_ICON :
            UnloadImage(sys.asset.img[id]);
            sys.asset.asset_type[id] = NULL;
            BITS_OFF(sys.asset.state[id], ASSET_LOADED & assettype);
            BITS_ON(sys.asset.state[id], ASSET_UNLOADED);
            break;

            case ASSET_PALETTE :
            UnloadImage(sys.asset.img[id]);
            UnloadImagePalette(sys.asset.palette[id]);
            UnloadTexture(sys.asset.tex[id]);
            sys.asset.asset_type[id] = NULL;
            BITS_OFF(sys.asset.state[id], ASSET_LOADED & assettype);
            BITS_ON(sys.asset.state[id], ASSET_UNLOADED);
            break;

            case ASSET_TEXTURE :
            UnloadImage(sys.asset.img[id]);
            UnloadTexture(sys.asset.tex[id]);
            sys.asset.asset_type[id] = NULL;
            BITS_OFF(sys.asset.state[id], ASSET_LOADED & assettype);
            BITS_ON(sys.asset.state[id], ASSET_UNLOADED);
            break;

            case ASSET_FONT :
            UnloadImage(sys.asset.img[id]);
            UnloadTexture(sys.asset.font[id].texture);
            sys.asset.asset_type[id] = NULL;
            BITS_OFF(sys.asset.state[id], ASSET_LOADED & assettype);
            BITS_ON(sys.asset.state[id], ASSET_UNLOADED);
            break;

            case ASSET_TILESET :
            UnloadImage(sys.asset.img[id]);
            UnloadTexture(sys.asset.tileset[id].tex);
            sys.asset.asset_type[id] = NULL;
            BITS_OFF(sys.asset.state[id], ASSET_LOADED & assettype);
            BITS_ON(sys.asset.state[id], ASSET_UNLOADED);
            break;

            case ASSET_FRAMEBUFFER :
            UnloadRenderTexture(sys.asset.framebuffer[id]);
            sys.asset.asset_type[id] = NULL;
            BITS_OFF(sys.asset.state[id], ASSET_LOADED & assettype);
            BITS_ON(sys.asset.state[id], ASSET_UNLOADED);
            break;

            case ASSET_SHADER :
            UnloadShader(sys.asset.shader[id]);
            sys.asset.asset_type[id] = NULL;
            BITS_OFF(sys.asset.state[id], ASSET_LOADED & assettype);
            BITS_ON(sys.asset.state[id], ASSET_UNLOADED);
            break;

            case ASSET_XM :
            StopMusicStream(sys.asset.music[id]); // in case it is still playing
            UnloadMusicStream(sys.asset.music[id]);
            sys.asset.asset_type[id] = NULL;
            BITS_OFF(sys.asset.state[id], ASSET_LOADED & assettype);
            BITS_ON(sys.asset.state[id], ASSET_UNLOADED);
            break;

            case ASSET_WAV : // incomplete*********************************** get raylib functionality
            sys.asset.asset_type[id] = NULL;
            BITS_OFF(sys.asset.state[id], ASSET_LOADED & assettype);
            BITS_ON(sys.asset.state[id], ASSET_UNLOADED);
            break;

            case ASSET_MP3 : // incomplete*********************************** get raylib functionality
            sys.asset.asset_type[id] = NULL;
            BITS_OFF(sys.asset.state[id], ASSET_LOADED & assettype);
            BITS_ON(sys.asset.state[id], ASSET_UNLOADED);
            break;

            case ASSET_AUDIOSTREAM :
            sys.asset.asset_type[id] = NULL;
            BITS_OFF(sys.asset.state[id], ASSET_LOADED & assettype);
            BITS_ON(sys.asset.state[id], ASSET_UNLOADED);
            break;

            case ASSET_TEXT :
            sys.asset.asset_type[id] = NULL;
            BITS_OFF(sys.asset.state[id], ASSET_LOADED & assettype);
            BITS_ON(sys.asset.state[id], ASSET_UNLOADED);
            break;

            case ASSET_DATA :
            sys.asset.asset_type[id] = NULL;
            BITS_OFF(sys.asset.state[id], ASSET_LOADED & assettype);
            BITS_ON(sys.asset.state[id], ASSET_UNLOADED);
            break;

            default :
            BITS_ON(sys.asset.state[id], ASSET_ISSUE); // unknown asset, trigger issue
        };
        sys.asset.total_assets -= 1;
    };
}

void unload_all_assets(void) {
    for(int asset = 0; asset < MAXASSETS; asset++) {
        unload_asset(asset);
    };
}


// ********** A S S E T   S Y S T E M  ***** A S S E T   S Y S T E M  ***** A S S E T   S Y S T E M  ***** E N D
// ********** A S S E T   S Y S T E M  ***** A S S E T   S Y S T E M  ***** A S S E T   S Y S T E M  ***** E N D
// ********** A S S E T   S Y S T E M  ***** A S S E T   S Y S T E M  ***** A S S E T   S Y S T E M  ***** E N D


// ********** A U D I O   S Y S T E M  ***** A U D I O   S Y S T E M  ***** A U D I O   S Y S T E M  ***** B E G I N
// ********** A U D I O   S Y S T E M  ***** A U D I O   S Y S T E M  ***** A U D I O   S Y S T E M  ***** B E G I N
// ********** A U D I O   S Y S T E M  ***** A U D I O   S Y S T E M  ***** A U D I O   S Y S T E M  ***** B E G I N
typedef enum {
    TRACK_RESERVED          = 0b10000000000000000000000000000000,
    TRACK_SWITCH_IMMEDIATE  = 0b00100000000000000000000000000000,
    TRACK_STOP_UNFOCUSED    = 0b00010000000000000000000000000000,
    TRACK_RESTART_ON_FOCUS  = 0b00001000000000000000000000000000,
    TRACK_PAUSE_ON_PAUSE    = 0b00000010000000000000000000000000,
    TRACK_PAUSE_ON_TERMINAL = 0b00000000100000000000000000000000,
    TRACK_STOPPED           = 0b00000000000000000000000000100000,
    TRACK_PAUSED            = 0b00000000000000000000000000010000,
    TRACK_FINISHED          = 0b00000000000000000000000000001000,
    TRACK_EXPIRED           = 0b00000000000000000000000000000010,
    TRACK_ACTIVE            = 0b00000000000000000000000000000001
};

// no wav or mp3 support implemented yet (!)

bool init_audio_properties(void) {
    bool status;
    InitAudioDevice();
    sys.audio.total_tracks = 0;
    sys.audio.global_volume = 1.0f;
    SetMasterVolume(sys.audio.global_volume); 
    for (int id=0; id < MAXAUDIOTRACKS; id++) {
        sys.audio.track[id].is_playing = false;
        sys.audio.track[id].volume = 1.0f;
        sys.audio.track[id].order_playing = 0;
        sys.audio.track[id].total_orders = 0;
        for (int j=0; j < MAXORDERS; j++) {
            sys.audio.track[id].order[j] = 0;
        }
    }
    status = IsAudioDeviceReady();
    return status;
}

void update_audio(void) {
    for (int id=0; id < MAXAUDIOTRACKS; id++) {
        if (sys.audio.track[id].is_playing) {
            if (sys.audio.track[id].virtual_display == sys.video.current_virtual) {
                UpdateMusicStream(sys.asset.music[sys.audio.track[id].asset]);
            }
        }
    }
}

static int add_track(int display, int state, const char* fileName, const char* fileType, const unsigned char* fileData, int dataSize, int pak, int total_orders, int orderlist[]) {
    int track_id = sys.audio.total_tracks;
    sys.audio.track[track_id].virtual_display = display;
    sys.audio.track[track_id].state = state;
    sys.audio.track[track_id].asset = load_asset(ASSET_XM, fileName, fileType, fileData, dataSize, pak);
    sys.audio.track[track_id].volume = 1.f;
    //int asset = sys.audio.track[].asset_playing;

    //int total_orders = sizeof(orderlist[0]) / sizeof(int);
    for (int i = 0; i < total_orders; i++) {
        sys.audio.track[track_id].order[i] = orderlist[i];
    }
    sys.audio.track[track_id].total_orders = total_orders;

    sys.audio.total_tracks += 1;
    return track_id;
}

//StopMusicStream(sys.asset.music[asset]);
static void change_music_stream(int track_id, int order_id, bool immediate) {
    int asset = sys.audio.track[track_id].asset;
    sys.audio.track[track_id].order_playing = order_id;
    
    if (!immediate) { // switches at end of pattern
        jar_xm_pattern_jump(sys.asset.music[asset].ctxData, sys.audio.track[track_id].order[order_id]);
    } else { // switches immediately
        jar_xm_pattern_jump_immediate(sys.asset.music[asset].ctxData, sys.audio.track[track_id].order[order_id], true);
    };
}

static void hint_restart_track(int immediate) {
    for (int id=0; id < MAXAUDIOTRACKS; id++) {
        if (sys.audio.track[id].virtual_display == sys.video.current_virtual) {
            if (sys.audio.track[id].state || TRACK_RESTART_ON_FOCUS) {
                sys.audio.track[id].is_playing = true;
                int order = sys.audio.track[id].order_playing;
                change_music_stream(id, order, immediate);
            }
        }
    }
}

static void play_track(int track, int order, int immediate) {
    sys.audio.track[track].is_playing = true;
    int asset = sys.audio.track[track].asset;
	PlayMusicStream(sys.asset.music[asset]);
    change_music_stream(track, order, immediate);
}

static void change_track_playing(int track, int order) {
    sys.audio.track[track].is_playing = true;
 //   if (sys.audio.track[track].orderlist >= sys.audio.total_tracks) sys.audio.track_playing = (sys.audio.total_tracks - 1); else if (sys.audio.track_playing < 0) sys.audio.track_playing = 0;
    //change_music_stream(tracksys.audio.track_playing, true);
}

//    jar_xm_change_all_channel_volumes(sys.asset.music[asset].ctxData, (int) amount); // DO NOT USE, INSTEAD REVAMP TRACKER MIXER
static void change_track_volume(int track, int volume) {
    if (volume>=0.f && volume <=1.0f) sys.audio.track[track].volume = volume;
    int asset = sys.audio.track[track].asset;
	SetMusicVolume(sys.asset.music[asset], sys.audio.track[track].volume);
}

static void change_global_volume(float amount) {
    sys.audio.global_volume += amount;
    if ( sys.audio.global_volume > 1.0f) sys.audio.global_volume = 1.0f; else if ( sys.audio.global_volume < 0.0f) sys.audio.global_volume = 0.0f;
    SetMasterVolume(sys.audio.global_volume);
}

// ********** A U D I O   S Y S T E M  ***** A U D I O   S Y S T E M  ***** A U D I O   S Y S T E M  ***** E N D
// ********** A U D I O   S Y S T E M  ***** A U D I O   S Y S T E M  ***** A U D I O   S Y S T E M  ***** E N D
// ********** A U D I O   S Y S T E M  ***** A U D I O   S Y S T E M  ***** A U D I O   S Y S T E M  ***** E N D

// ********** V I D E O   S Y S T E M  ***** V I D E O   S Y S T E M  ***** V I D E O   S Y S T E M  ***** B E G I N
// ********** V I D E O   S Y S T E M  ***** V I D E O   S Y S T E M  ***** V I D E O   S Y S T E M  ***** B E G I N
// ********** V I D E O   S Y S T E M  ***** V I D E O   S Y S T E M  ***** V I D E O   S Y S T E M  ***** B E G I N

typedef enum {
    VIDEO_RESERVED       = 0b10000000000000000000000000000000, // 
    VIDEO_ON_TOP         = 0b00001000000000000000000000000000, // Terminal display is above all other virtual displays
    VIDEO_MOVE_X         = 0b00000000000000000100000000000000, // 
    VIDEO_MOVE_Y         = 0b00000000000000000010000000000000, // 
    VIDEO_HIDDEN         = 0b00000000000000000000000010000000, // 
    VIDEO_FROZEN         = 0b00000000000000000000000000100000, // 
    VIDEO_EXPIRING       = 0b00000000000000000000000000001000, // 
    VIDEO_EXPIRED        = 0b00000000000000000000000000000010, // 
    VIDEO_ACTIVE         = 0b00000000000000000000000000000001  // 
};

// SET buffer aspect ratio
// RLAPI void rlOrtho(double left, double right, double bottom, double top, double znear, double zfar);

static int init_frame_buffer(int display, Vector2 resolution) {
    sys.video.current_virtual = display;
    flip_frame_buffer(display, true);
    sys.video.virtual_res[sys.video.current_virtual] = resolution;
    sys.video.frames[sys.video.current_virtual] = 0;
    sys.video.elapsed_time_var_ratio[sys.video.current_virtual] = 5.f;
    sys.video.frame_time_inc[sys.video.current_virtual] = 0;
	return load_asset(ASSET_FRAMEBUFFER, NULL, NULL, NULL, NULL, 0);
}

static void draw_frame_buffer(RenderTexture renderer) {
	DrawTexturePro (renderer.texture,
    (Rectangle) {0.0f, 0.0f, (float)renderer.texture.width, (float)-renderer.texture.height},
    (Rectangle) {0.0, 0.0, sys.video.physical_res[sys.video.current_physical].x, sys.video.physical_res[sys.video.current_physical].y},
    (Vector2)   {0.0, 0.0}, 0.0f, WHITE);
}

void flip_frame_buffer(int display, bool clear) {
    sys.video.current_virtual = display;
    if (clear) sys.video.next_physical_clear = true;
}

static Vector2 ratio_info(int x, int y) {
    Vector2 p;

    int gcd_res = gcdi(x,y);
    p.x = x / gcd_res;
    p.y = y / gcd_res;
    return p;
}

bool init_display_properties(bool hide_mouse, const char* title) {
    bool status;
    INIT(sys.video.windowstate_normal, 0);
    //sys.video.windowstate_normal = FLAG_WINDOW_UNDECORATED; // AVOID AT ALL COST (SCREEN TEARING when VSYNC)
    BITS_ON(sys.video.windowstate_normal, FLAG_FULLSCREEN_MODE);
    BITS_ON(sys.video.windowstate_normal, FLAG_WINDOW_ALWAYS_RUN);
    BITS_ON(sys.video.windowstate_normal, FLAG_WINDOW_TOPMOST);
    BITS_ON(sys.video.windowstate_normal, FLAG_MSAA_4X_HINT);
    BITS_ON(sys.video.windowstate_normal, FLAG_VSYNC_HINT);

    INIT(sys.video.windowstate_paused, 0);
    BITS_ON(sys.video.windowstate_paused, FLAG_FULLSCREEN_MODE);
    BITS_ON(sys.video.windowstate_paused, FLAG_WINDOW_UNFOCUSED);
    BITS_ON(sys.video.windowstate_paused, FLAG_WINDOW_MINIMIZED);
    BITS_ON(sys.video.windowstate_paused, FLAG_MSAA_4X_HINT);
    BITS_ON(sys.video.windowstate_paused, FLAG_VSYNC_HINT);

    SetConfigFlags(sys.video.windowstate_normal);
    InitWindow(0, 0, title);
    sys.video.current_physical = GetCurrentMonitor();
    if (hide_mouse) HideCursor();
    sys.video.physical_res[sys.video.current_physical] = (Vector2) {GetMonitorWidth(sys.video.current_physical), GetMonitorHeight(sys.video.current_physical)};
    sys.video.refresh_rate[sys.video.current_physical] = GetMonitorRefreshRate(sys.video.current_physical);

    status = IsWindowReady();
    return status;
}

void update_display(void) {
    int display = sys.video.current_virtual;
	BeginDrawing();
        if (sys.video.next_physical_clear) {
            ClearBackground(BLACK);
            sys.video.next_physical_clear = false;
        };
        draw_frame_buffer(sys.asset.framebuffer[sys.video.virtual_asset[display]]);
        update_debug(true);
	EndDrawing();

    sys.video.window_focus = IsWindowFocused();

    double next_frame = sys.video.prev_time[display] + (double)(1 / sys.video.refresh_rate[sys.video.current_physical]);
    float wait = (next_frame - GetTime());
    if (wait < 0) wait = 0;
    WaitTime(wait * 1000.f);

    double current_time = GetTime();

    sys.video.elapsed_time[display] = current_time - sys.video.prev_time[display];
    sys.video.prev_time[display] = current_time;

   if (sys.video.window_focus) {        // ************** GO TO APP MODE
        if (sys.pause) {
            if (GetKeyPressed() != 0) {
                sys.pause = false;
                flip_frame_buffer(PRIMARYDISPLAY, true);
                ClearWindowState(sys.video.windowstate_normal ^ sys.video.windowstate_paused);
                SetWindowState(sys.video.windowstate_normal);
                sys.video.prev_time[sys.video.current_virtual] = current_time;
            }
        }
    } else {        // ************* GO TO PAUSE MODE
        //IsWindowMinimized()
        if (!sys.pause) {
            sys.pause = true;
            flip_frame_buffer(PAUSEDISPLAY, true);
            ClearWindowState(sys.video.windowstate_paused ^ sys.video.windowstate_normal);
            SetWindowState(sys.video.windowstate_paused);
            hint_restart_track(true);
            sys.video.prev_time[sys.video.current_virtual] = current_time;
        };
    };

    sys.video.frame_time[display] = (float)sys.video.elapsed_time[display] * (float)sys.video.refresh_rate[sys.video.current_physical];
    sys.video.frame_time_inc[display] += (float)sys.video.elapsed_time[display];
    sys.video.elapsed_time_var[display] += (float)sys.video.elapsed_time[display] * sys.video.elapsed_time_var_ratio[display];
    sys.video.value_anim[display] = fast_sin(fast_cos(fast_sin(sys.video.frame_time_inc[display]) * fast_sin(sys.video.elapsed_time_var[display] * 0.1) * 0.1) * fast_cos(sys.video.elapsed_time_var[display] * 0.015) * 0.1 ) * 0.05 + 0.001;
    sys.video.frames[display]++;

}

void deinit_display(void) {
    ShowCursor();
	CloseWindow();
}

// ********** V I D E O   S Y S T E M  ***** V I D E O   S Y S T E M  ***** V I D E O   S Y S T E M  ***** E N D
// ********** V I D E O   S Y S T E M  ***** V I D E O   S Y S T E M  ***** V I D E O   S Y S T E M  ***** E N D
// ********** V I D E O   S Y S T E M  ***** V I D E O   S Y S T E M  ***** V I D E O   S Y S T E M  ***** E N D


// ********** P A R T I C L E   S Y S T E M  ***** P A R T I C L E   S Y S T E M  ***** P A R T I C L E   S Y S T E M  ***** B E G I N
// ********** P A R T I C L E   S Y S T E M  ***** P A R T I C L E   S Y S T E M  ***** P A R T I C L E   S Y S T E M  ***** B E G I N
// ********** P A R T I C L E   S Y S T E M  ***** P A R T I C L E   S Y S T E M  ***** P A R T I C L E   S Y S T E M  ***** B E G I N

typedef enum {
    PARTICLE_RESERVED       = 0b10000000000000000000000000000000, //
    PARTICLE_ROTATION       = 0b00000000001000000000000000000000, // turn on rotation
    PARTICLE_SCALE          = 0b00000000000100000000000000000000, // turn on scaling
    PARTICLE_R              = 0b00000000000000010000000000000000, // turn on red channel
    PARTICLE_G              = 0b00000000000000001000000000000000, // turn on green channel
    PARTICLE_B              = 0b00000000000000000100000000000000, // turn on blue channel
    PARTICLE_A              = 0b00000000000000000010000000000000, // turn on alpha channel
    PARTICLE_STAY           = 0b00000000000000000000001000000000, // does not move using speedX, speedY
    PARTICLE_HIDE           = 0b00000000000000000000000010000000, // does not display
    PARTICLE_FREEZE         = 0b00000000000000000000000000100000, // does not move at all or animate, speedX, speedY, xsin, ysin
    PARTICLE_DYING          = 0b00000000000000000000000000001000, // expiration sequence
    PARTICLE_EXPIRED        = 0b00000000000000000000000000000010, // decomissionned
    PARTICLE_ACTIVE         = 0b00000000000000000000000000000001
} particle_features;

#define MAXPARTICLES 65536

// The particle system for now is junk, it is just a placeholder for a grander scheme... (!)

typedef struct EX_sprite {
	Texture2D texture;
	Vector2 position;
	Vector2 size;
	float x;
	float y;
	float speedX;
	float speedY;
    float xsin;
    float ysin;
    int   current_state;
    float current_state_timer;    // current state timer
    float state_default_time[10]; // per state countdown time
    float state_default_next[10]; // per state following particle state
} EX_sprite;


typedef struct Sprite {
	float x;
	float y;
	float speedX;
	float speedY;
    float xsin;
    float ysin;
} Sprite;


#define MAXPARTICLES 5

typedef struct particle {
	Texture2D texture;
	Vector2 position;
	//Vector2 size;
	Sprite unit[MAXPARTICLES];
} particle;

particle init_particle(Texture texture, Vector2 r1, Vector2 speed) {
	Vector2 res = sys.video.virtual_res[sys.video.current_virtual];
	particle p;
	p.texture = texture;
	p.position = r1;
	//p.size = sys.video.virtual_res[sys.video.current_virtual];
	
	for(int i = 0; i < MAXPARTICLES; i++) {
		p.unit[i].x = GetRandomValue(p.position.x ,res.x + 32);
		p.unit[i].y = GetRandomValue(p.position.y ,res.y + 32);
		p.unit[i].speedX = speed.x;
		p.unit[i].speedY = speed.y;
		p.unit[i].xsin = (float)GetRandomValue(0,360);
		p.unit[i].ysin = (float)GetRandomValue(0,360);
	}
	return p;
};

void update_particle(particle *particle, Vector2 velocity) {
	Vector2 res = sys.video.virtual_res[sys.video.current_virtual];
    velocity.x *= sys.video.frame_time[sys.video.current_virtual];
    velocity.y *= sys.video.frame_time[sys.video.current_virtual];
	for(int i = 0; i < MAXPARTICLES; i++) {
		particle->unit[i].x += particle->unit[i].speedX * velocity.x;
		particle->unit[i].y += particle->unit[i].speedY * velocity.y;

		if( particle->unit[i].x > ( particle->position.x + res.x + 32) ) {
			particle->unit[i].x = particle->position.x;
			particle->unit[i].y = GetRandomValue(particle->position.y , particle->position.y + res.y + 32);
		}

		if( particle->unit[i].y > ( particle->position.y + res.y + 32) ) {
			particle->unit[i].y = particle->position.y;
			particle->unit[i].x = GetRandomValue(particle->position.x , particle->position.x + res.x + 32);
		}

		if( particle->unit[i].x < particle->position.x ) particle->unit[i].x = particle->position.x + res.x + 32;
		if( particle->unit[i].y > ( particle->position.y + res.y + 32 ) ) particle->unit[i].y = particle->position.y;
		if( particle->unit[i].y < particle->position.y ) particle->unit[i].y = particle->position.y + res.y + 32;

		DrawTexturePro(particle->texture,
            (Rectangle) { 0.0f, 0.0f, (float)particle->texture.width, (float)particle->texture.height },
            (Rectangle) {particle->unit[i].x + sin(particle->unit[i].xsin) * 3.0f, particle->unit[i].y + sin(particle->unit[i].ysin), (float)particle->texture.width, (float)particle->texture.height},
            (Vector2) {0.0f, 0.0f}, 0.0f,
            WHITE);
        particle->unit[i].xsin += (0.1f * velocity.y); //if (particle->unit[i].xsin > 360.f)  particle->unit[i].xsin -= 360.f;
        particle->unit[i].ysin += (0.1f * velocity.y); //if (particle->unit[i].ysin > 360.f)  particle->unit[i].ysin -= 360.f;
	};
}


typedef struct EX_copper {
    float prev_y[64][256];
} EX_copper;

EX_copper ex_copper[MAXDISPLAYS];

static void copper_animation(int direction, int asset, int segments, int coppers, int size_y, float rastoffset, Vector2 offset, Vector3 ratio, float scale) {
    static bool do_it;
    static float y_start;
    static int copper;
    int display = sys.video.current_virtual;
    Vector2 vres = sys.video.virtual_res[sys.video.current_virtual];
	float size_x = vres.x / (float)segments;
    float amp = (vres.y * scale) - (size_y * 0.5);
    for(int y = 0; y < coppers; y++) {
        copper = y % 16;
        for(int x = 0; x < segments; x++) {
            y_start = amp + fast_sin((sys.video.frame_time_inc[sys.video.current_virtual]*ratio.x)-rastoffset*((float)y*ratio.y)-((float)x * sys.video.value_anim[sys.video.current_virtual]*ratio.z)) * amp + offset.y;
            do_it = true;
            if (direction > 0) {
                if (y_start >= ex_copper[display].prev_y[y][x]) do_it = false;
                ex_copper[display].prev_y[y][x] = y_start;
            } else if (direction < 0) {
                if (y_start < ex_copper[display].prev_y[y][x]) do_it = false;
            }
            if ((y_start <= vres.y) && do_it) {
                DrawTexturePro( sys.asset.tex[asset],
                (Rectangle) { copper, 0, 1, 32 }, 
                (Rectangle) {(float) x * size_x, y_start, size_x, size_y }, 
                  (Vector2) {0}, 0, WHITE );
            }
      	}
    }
}

typedef struct EX_marquee {
    int palette;
    int palptr;
    float palptr_next_frame_time;
} EX_marquee;

EX_marquee ex_marquee[MAXDISPLAYS];

static void update_marquee_animation(int asset_id, int palette_id, Vector2 logosize, float transparency, Vector2 offset, float speed, float shadow_transparency) {
    int display = sys.video.current_virtual;
    if (ex_marquee[display].palptr_next_frame_time < sys.video.frame_time_inc[display]) {
        ex_marquee[display].palptr_next_frame_time = sys.video.frame_time_inc[display] + 1/absf(speed);
        if (speed > 0.0f) {
            ex_marquee[display].palptr += 1;
        } else {
            ex_marquee[display].palptr -= 1;
        }
        if (ex_marquee[display].palptr > 255) {ex_marquee[display].palptr -= 256;} else if (ex_marquee[display].palptr < 0) {ex_marquee[display].palptr += 256;};
    };
    int palptr_loop = ex_marquee[display].palptr;

    if (transparency > 0.0f) {
        Vector2 scale = {(255.0f - transparency) * 0.01f + 1.0f, 1.0f};
        Vector2 final_offset = {offset.x + (sys.video.virtual_res[sys.video.current_virtual].x-(logosize.x * scale.x))/2.0, offset.y};
        for(int i = 0; i < logosize.y; i++) {
            if (palptr_loop > 255) {palptr_loop -= 256;} else if (palptr_loop < 0) {palptr_loop += 256;};
            
            Color rgba = get_palette_color(palette_id, palptr_loop);
            
            float shadow_alpha = (transparency * shadow_transparency);
            if (shadow_alpha > 0) {
                DrawTexturePro( sys.asset.tex[asset_id],
                (Rectangle) { 0, i, logosize.x, 1 }, 
                (Rectangle) {final_offset.x + fast_sin(sys.video.frame_time_inc[sys.video.current_virtual] + sys.video.value_anim[sys.video.current_virtual] * (float) i * 2.0) * 32.0 + 2, final_offset.y+i + 4, logosize.x * scale.x, 1 }, 
                (Vector2) { 0, 0 }, 0, (Color){0, 0, 0, shadow_alpha} );
            }

            DrawTexturePro( sys.asset.tex[asset_id],
            (Rectangle) { 0, i, logosize.x, 1 }, 
            (Rectangle) {final_offset.x + fast_sin(sys.video.frame_time_inc[sys.video.current_virtual] + sys.video.value_anim[sys.video.current_virtual] * (float) i * 2.0) * 32.0, final_offset.y+i, logosize.x * scale.x, 1 }, 
            (Vector2) { 0, 0 }, 0, (Color){rgba.r, rgba.g, rgba.b, transparency} );

            palptr_loop -= 1;
        }
    }
}


// ********** P A R T I C L E   S Y S T E M  ***** P A R T I C L E   S Y S T E M  ***** P A R T I C L E   S Y S T E M  ***** E N D
// ********** P A R T I C L E   S Y S T E M  ***** P A R T I C L E   S Y S T E M  ***** P A R T I C L E   S Y S T E M  ***** E N D
// ********** P A R T I C L E   S Y S T E M  ***** P A R T I C L E   S Y S T E M  ***** P A R T I C L E   S Y S T E M  ***** E N D

// ********** C A N O P Y   S Y S T E M  ***** C A N O P Y   S Y S T E M  ***** C A N O P Y   S Y S T E M  ***** B E G I N
// ********** C A N O P Y   S Y S T E M  ***** C A N O P Y   S Y S T E M  ***** C A N O P Y   S Y S T E M  ***** B E G I N
// ********** C A N O P Y   S Y S T E M  ***** C A N O P Y   S Y S T E M  ***** C A N O P Y   S Y S T E M  ***** B E G I N

#define CANOPYMAXX 64
#define CANOPYMAXY 32

typedef struct EX_canopy {
    Vector2 sin_value;
    Vector2 sin_value_old;
    Vector2 cell_size;
    Vector2 offset;
    Vector2 adjustment;
    float transparency;
    float transparency_mod;
    int cells_x;
    int cells_y;
    int pal_idx_cells;
    int pal_idx_text;
    int font_id;
    int palette_id;
    Vector2 grid[CANOPYMAXY][CANOPYMAXX]; // set to max capacity
} EX_canopy;

EX_canopy ex_canopy;

static void init_canopy (int font_id, int palette_id, Vector2 cells, Vector2 cell_size, float transparency, float transparency_mod, Vector2 adjustment, int pal_idx_cells, int pal_idx_text) {
    ex_canopy.font_id = font_id;
    ex_canopy.palette_id = palette_id;
    ex_canopy.sin_value = (Vector2){0};
    ex_canopy.sin_value_old = (Vector2){0};
    ex_canopy.cell_size = cell_size;
    ex_canopy.offset = (Vector2){0};
    ex_canopy.adjustment = adjustment;
    ex_canopy.cells_x = cells.x;
    ex_canopy.cells_y = cells.y;
    ex_canopy.pal_idx_cells = pal_idx_cells;
    ex_canopy.pal_idx_text = pal_idx_text;
    ex_canopy.transparency = transparency;
    ex_canopy.transparency_mod = transparency_mod;
    
    for (int y = 0; y < ex_canopy.cells_y; y++) {
        for (int x = 0; x < ex_canopy.cells_x; x++) {
            ex_canopy.grid[y][x] = (Vector2) {ex_canopy.cell_size.x, ex_canopy.cell_size.y};
        };
    };
}

static void update_canopy(int asset_id) {
    ex_canopy.offset.x = (sys.video.virtual_res[sys.video.current_virtual].x-((ex_canopy.cells_x+1)*ex_canopy.cell_size.x))*0.5f;
    ex_canopy.offset.y = 7.0f * ex_canopy.cell_size.x + (255.f - ex_canopy.transparency);
    if ((ex_canopy.transparency > 0.0f) & (ex_canopy.offset.y <= sys.video.virtual_res[sys.video.current_virtual].y)) {
            
        Vector2 cell_size;
        int col_idx;
        ex_canopy.sin_value_old.x = ex_canopy.sin_value.x;
        ex_canopy.sin_value_old.y = ex_canopy.sin_value.y;
        Color vertex_colors[4];
        for(int y = (ex_canopy.cells_y - 1); y >= 0; y -= 1) {
            for(int x = (ex_canopy.cells_x - 1); x >= 0; x -= 1) {
                float x_sin = fast_sin(ex_canopy.sin_value.x);
                float y_sin = fast_sin(ex_canopy.sin_value.y);
                ex_canopy.grid[y][x].x = ((float)x+x_sin)*ex_canopy.cell_size.x + ex_canopy.offset.x;
                ex_canopy.grid[y][x].y = ((float)y+y_sin)*ex_canopy.cell_size.x + ex_canopy.offset.y;

                if (x<(ex_canopy.cells_x-1)) {cell_size.x = ((ex_canopy.grid[y][x+1].x - ex_canopy.grid[y][x].x));} else {cell_size.x = ex_canopy.cell_size.x;};
                if (y<(ex_canopy.cells_y-1)) {cell_size.y = ((ex_canopy.grid[y+1][x].y - ex_canopy.grid[y][x].y) + 1.f);} else {cell_size.y = ex_canopy.cell_size.y;};
                    
                if (cell_size.x > 0 && cell_size.y > 0) {
                    col_idx = (int)(y_sin * 4.0f); if (col_idx > 3) col_idx = 3;
                    vertex_colors[0] = get_palette_color(ex_canopy.palette_id,-col_idx + ex_canopy.pal_idx_cells);
                    vertex_colors[1] = vertex_colors[0];
                    vertex_colors[2] = vertex_colors[0];
                    vertex_colors[3] = vertex_colors[0];
                    DrawRectangleProSK(
                    (Rectangle){ex_canopy.grid[y][x].x, ex_canopy.grid[y][x].y, cell_size.x, cell_size.y}, 
                    (Vector2) {0.f, 0.f}, (Vector2) {0.f, 0.f}, 0.f,
                    vertex_colors);

                    // draw text from a grid
                    col_idx = (int)(y_sin * 7.0f); if (col_idx > 6) col_idx = 6;
                    vertex_colors[0] = get_palette_color(ex_canopy.palette_id,-col_idx + ex_canopy.pal_idx_text);
                    vertex_colors[1] = vertex_colors[0];
                    vertex_colors[2] = vertex_colors[0];
                    vertex_colors[3] = vertex_colors[0];
                    float value = (float)(sys.asset.data[asset_id][y * ex_canopy.cells_x + x]);
                    DrawTextureProSK(sys.asset.tex[ex_canopy.font_id],
                    get_tilezone_from_code(ex_canopy.font_id, value),
                    (Rectangle) {ex_canopy.grid[y][x].x, ex_canopy.grid[y][x].y, cell_size.x, cell_size.y},
                    (Vector2) {0.f, 0.f}, (Vector2) {0.f, 0.f},0.f,
                    vertex_colors);
                }
                ex_canopy.sin_value.y += (ex_canopy.adjustment.y + fast_sin(sys.video.frame_time_inc[sys.video.current_virtual]) * 0.005f);
            }

            ex_canopy.sin_value.y += (ex_canopy.cells_y/ex_canopy.cells_x)*1.0665f;  // this is the depth of the waves
            ex_canopy.sin_value.x = ex_canopy.sin_value_old.x;
        }
        ex_canopy.sin_value.y = ex_canopy.sin_value_old.y + 0.05f * sys.video.frame_time[sys.video.current_virtual];  // this is the vertical wave movement per frame
    }
    ex_canopy.transparency +=ex_canopy.transparency_mod * sys.video.frame_time[sys.video.current_virtual];
    if (ex_canopy.transparency > 255.0f) {ex_canopy.transparency = 255.0f;} else if (ex_canopy.transparency < 0.0f) {ex_canopy.transparency = 0.0f;};
};

const Color colorbar[] = {{255,255,255,255}, {255,255,0,255}, {0,255,255,255}, {0,255,0,255}, {255,0,255,255}, {255,0,0,255}, {0,0,255,255}, {0,0,0,255}};

static void draw_colorbar(void) {
    int bar_count = sizeof(colorbar) / sizeof(Color);
    float x = sys.video.virtual_res[sys.video.current_virtual].x * 1/bar_count;
    for (int i = 0; i<bar_count; i++) {
        DrawRectangle(i * x, 0, x, sys.video.virtual_res[sys.video.current_virtual].y, (Color) colorbar[i]);        
    }
}

// ********** C A N O P Y   S Y S T E M  ***** C A N O P Y   S Y S T E M  ***** C A N O P Y   S Y S T E M  ***** E N D
// ********** C A N O P Y   S Y S T E M  ***** C A N O P Y   S Y S T E M  ***** C A N O P Y   S Y S T E M  ***** E N D
// ********** C A N O P Y   S Y S T E M  ***** C A N O P Y   S Y S T E M  ***** C A N O P Y   S Y S T E M  ***** E N D


// ********** S C R O L L T E X T   S Y S T E M  ***** S C R O L L T E X T   S Y S T E M  ***** S C R O L L T E X T   S Y S T E M  ***** B E G I N
// ********** S C R O L L T E X T   S Y S T E M  ***** S C R O L L T E X T   S Y S T E M  ***** S C R O L L T E X T   S Y S T E M  ***** B E G I N
// ********** S C R O L L T E X T   S Y S T E M  ***** S C R O L L T E X T   S Y S T E M  ***** S C R O L L T E X T   S Y S T E M  ***** B E G I N

typedef struct EX_scrolltext {
    int asset_id;
    int font_id;
    int palette_id;
    Vector2 position;
    Vector2 skew;
    float alpha;
    int text_wave_flag;
    int text_angle;
    int text_wave;
    float pause_found;
    float text_pause;
    float text_scroll_speed;
    float text_shadow;
    unsigned short fg_color;
    unsigned short fg_color_flag;
    unsigned short bg_color;
    unsigned short bg_color_flag;
} EX_scrolltext;

EX_scrolltext ex_scrolltext[16];

static void init_scrolltext(int s, int asset_id, int font_id, int palette_id, float speed, Vector2 position, Vector2 skew, float alpha) {
    ex_scrolltext[s].asset_id = asset_id;
    ex_scrolltext[s].font_id = font_id;
    ex_scrolltext[s].palette_id = palette_id;
	ex_scrolltext[s].position = position;
    ex_scrolltext[s].pause_found = 0;
    ex_scrolltext[s].text_pause = 0.0;
    ex_scrolltext[s].text_wave_flag = 0;
    ex_scrolltext[s].text_angle = 0;
    ex_scrolltext[s].text_wave = 0;
    ex_scrolltext[s].skew = skew;
    ex_scrolltext[s].alpha = alpha;
    ex_scrolltext[s].text_scroll_speed = speed;
    ex_scrolltext[s].text_shadow = 0.0;
    ex_scrolltext[s].fg_color_flag = 0;
    ex_scrolltext[s].bg_color_flag = 0;
    ex_scrolltext[s].fg_color = 15;
    ex_scrolltext[s].bg_color = 0;
}

//S C R O L L T E X T   C O M M A N D S
#define SCROLL_BKGNDCOLOR   99  // letter c
#define SCROLL_SHADOWDEPTH  100 // letter d
#define SCROLL_BKGNDCOLORX  102 // letter f
#define SCROLL_CELLYPOS     111 // letter o
#define SCROLL_PLUSXCOL     113 // letter q
#define SCROLL_MINUSXCOL    114 // letter r
#define SCROLL_TEXTSPEED    115 // letter s
#define SCROLL_BIGWAVE      116 // letter t
#define SCROLL_BIGGERWAVE   117 // letter u
#define SCROLL_SMALLWAVE    119 // letter w
#define SCROLL_NOWAVE       120 // letter x
#define SCROLL_TEXTCOLOR    122 // letter z
#define SCROLL_TEXTCOLCYCLE 123 // symbol {
#define SCROLL_FADEFLAG     124 // symbol |
#define SCROLL_TEXTNOCOLOR  125 // sylbol }
#define SCROLL_PAUSE        126 // symbol ~

static void update_scrolltext(int s, float text_scale) {
    unsigned short palette_id = ex_scrolltext[s].palette_id;
    
    if (ex_scrolltext[s].text_pause <= 0.0) {
        ex_scrolltext[s].position.x -= (sys.video.frame_time[sys.video.current_virtual] * ex_scrolltext[s].text_scroll_speed) / text_scale;
    } else {
        ex_scrolltext[s].text_pause -= sys.video.frame_time[sys.video.current_virtual];
    };

    int id;
    float et_var = sys.video.elapsed_time_var[sys.video.current_virtual];
    Vector2 displacement;
    int i_x = 0;

    unsigned char *text = &sys.asset.data[ex_scrolltext[s].asset_id];
	for(int i=0; i < sys.asset.data_size[ex_scrolltext[s].asset_id]; i++) {
        displacement.y = fast_sin(et_var) * text_scale;
        et_var += ((PI * 2) / 24);

        int ch = sys.asset.data[ex_scrolltext[s].asset_id][i];
        switch (ch) {
        case SCROLL_SHADOWDEPTH: // text shadow depth
            i++;
            ex_scrolltext[s].text_shadow = sys.asset.data[ex_scrolltext[s].asset_id][i] - 97;
            break;
        case SCROLL_CELLYPOS: // text cell y position
            i++;
            ex_scrolltext[s].position.y = sys.asset.data[ex_scrolltext[s].asset_id][i] - 97;
            break;
        case SCROLL_PLUSXCOL: // plus x columns
            i++;
            i_x += sys.asset.data[ex_scrolltext[s].asset_id][i] - 96;
            break;
        case SCROLL_MINUSXCOL: // minus x columns
            i++;
            i_x -= sys.asset.data[ex_scrolltext[s].asset_id][i] - 96;
            break;                    
        case SCROLL_BIGWAVE: // wave strongly
            ex_scrolltext[s].text_wave_flag = 2;
            break;
        case SCROLL_BIGGERWAVE: // wave very strongly
            ex_scrolltext[s].text_wave_flag = 3;
            break;
        case SCROLL_SMALLWAVE: // wave lightly
            ex_scrolltext[s].text_wave_flag = 1;
            break;
        case SCROLL_NOWAVE: // do not wave
            ex_scrolltext[s].text_wave_flag = 0;
            break;
        case SCROLL_TEXTCOLCYCLE: // text color grayscale wave
            ex_scrolltext[s].fg_color_flag = 1;
            break;
        case SCROLL_TEXTCOLOR: // text color table chooser
            i++;
            ex_scrolltext[s].fg_color = scrolltext_color((sys.asset.data[ex_scrolltext[s].asset_id][i]) - 97);
            break;
        case SCROLL_BKGNDCOLOR: // background color table chooser
            i++;
            ex_scrolltext[s].bg_color_flag = 1;
            id = (sys.asset.data[ex_scrolltext[s].asset_id][i]) - 97;
            ex_scrolltext[s].bg_color = scrolltext_color(id);
            if (id > 18) ex_scrolltext[s].bg_color_flag = 0;
            break;
        case SCROLL_BKGNDCOLORX: // background color extended chooser 
            i++;
            ex_scrolltext[s].bg_color_flag = 1;
            int hue = (sys.asset.data[ex_scrolltext[s].asset_id][i]) - 97;
            if (hue > 15) hue = 15; // can not test id
            i++;
            int lum = (sys.asset.data[ex_scrolltext[s].asset_id][i]) - 97;
            if (lum > 15) lum = 15; // can not test id
            ex_scrolltext[s].bg_color = (hue * 16 + lum);
            break;
        case SCROLL_TEXTNOCOLOR: // text color normal
            ex_scrolltext[s].fg_color = 15;
            ex_scrolltext[s].fg_color_flag = 0;
            break;
        default:
            if(((ex_scrolltext[s].position.x + (i_x - 1)) * text_scale ) < sys.video.virtual_res[sys.video.current_virtual].x && ((ex_scrolltext[s].position.x + (i_x + 2)) * text_scale ) > 0) {
                if (ch == SCROLL_PAUSE) { // pause the scroll x amount of seconds (a-z = 1 to 26 seconds)
                    i++;
                    if (ex_scrolltext[s].pause_found != (i - 1)) {
                        ex_scrolltext[s].pause_found = i - 1;
                        if (ex_scrolltext[s].text_pause <= 0.0) {
                            ex_scrolltext[s].text_pause = sys.video.refresh_rate[sys.video.current_physical] * (float)(sys.asset.data[ex_scrolltext[s].asset_id][i] - 96); // set pause for x secs (a-z=1-26)
                        };
                    }
                } else if (ch == SCROLL_TEXTSPEED) { // set the speed of the scrolling text (a-z = slow to very fast)
                    i++;
                    ex_scrolltext[s].text_scroll_speed = (float)sys.asset.data[ex_scrolltext[s].asset_id][i] - 96.0;
                } else if (ch == SCROLL_FADEFLAG) { // fade in the flag
                    i++;
                    if (sys.asset.data[ex_scrolltext[s].asset_id][i] == 97 ) { // a = fade in, any other charqacters = fade out (...)
                        ex_canopy.transparency_mod = 1.0f;
                    } else {
                        ex_canopy.transparency_mod = -1.0f;
                    };
                } else if (ch < 97 && ch > 31) { // let upper case letters pass and numbers and other basic characters
                    if (ex_scrolltext[s].text_wave_flag == 1) {
                        ex_scrolltext[s].text_wave = displacement.y;
                    } else if (ex_scrolltext[s].text_wave_flag == 2) {
                        ex_scrolltext[s].text_wave = displacement.y * 2;
                    } else if (ex_scrolltext[s].text_wave_flag == 3) {
                        ex_scrolltext[s].text_wave = displacement.y * 4;
                    } else {
                        ex_scrolltext[s].text_wave = 0;
                    };
                    if (ex_scrolltext[s].fg_color_flag == 1) {
                        ex_scrolltext[s].fg_color = (unsigned short)(displacement.y * 0.5f) + 7;
                    };
                    if (ex_scrolltext[s].text_pause > 0.0 || ex_scrolltext[s].text_wave_flag == 0) {
                        ex_scrolltext[s].text_angle = 0;
                    } else {
                        ex_scrolltext[s].text_angle = displacement.y;
                    };

                    unsigned int state = 0;
                    BITS_ON(state, (GRID_FOREGROUND | GRID_RED | GRID_GREEN | GRID_BLUE | GRID_SCALE_X | GRID_SCALE_Y));
                    if (ex_scrolltext[s].bg_color_flag > 0) BITS_ON(state, GRID_BACKGROUND);
                    if (ex_scrolltext[s].text_angle)        BITS_ON(state, GRID_ROTATION);
                    if (ex_scrolltext[s].text_shadow > 0.0) BITS_ON(state, GRID_SHADOW);
                    if (!(ex_scrolltext[s].text_angle))     BITS_ON(state, GRID_SKEW);

                    plot_character(ex_scrolltext[s].font_id, ex_scrolltext[s].palette_id, ch,
                        (Vector2) {(ex_scrolltext[s].position.x +  i_x) * text_scale, (ex_scrolltext[s].position.y * text_scale) + ex_scrolltext[s].text_wave}, 
                        (Vector2) {text_scale, text_scale}, 
                        ex_scrolltext[s].skew,
                        (Vector2) {2, 2},
                        ex_scrolltext[s].text_angle, 
                        get_palette_color_pro(palette_id, ex_scrolltext[s].fg_color, ex_scrolltext[s].alpha), 
                        get_palette_color_pro(palette_id, ex_scrolltext[s].bg_color, ex_scrolltext[s].alpha), 
                        state);
                };
            } else {
                if (ch == SCROLL_PAUSE || ch == SCROLL_TEXTSPEED || ch == SCROLL_FADEFLAG) { i++;}
            };
            i_x ++;
            break;
		};
	};

    if (ex_scrolltext[s].position.x < -i_x) {
        ex_scrolltext[s].position.x = sys.video.virtual_res[sys.video.current_virtual].x / text_scale;
        ex_scrolltext[s].pause_found = 0;
    };

}

int scrolltext_color(int id) {
    switch (id) {
        case 0:   return 33;   // BROWN
        case 1:   return 41;   // BEIGE
        case 2:   return 58;   // ORANGE
        case 3:   return 30;   // YELLOW
        case 4:   return 210;  // GREEN
        case 5:   return 216;  // LIME
        case 6:   return 82;   // MAGENTA
        case 7:   return 89;   // PINK
        case 8:   return 100;  // PURPLE
        case 9:   return 104;  // VIOLET
        case 10:  return 129;  // BLUE
        case 11:  return 170;  // SKYBLUE
        case 12:  return 49;   // MAROON
        case 13:  return 69;   // RED
        case 14:  return 0;    // BLACK
        case 15:  return 4;    // DARKGRAY
        case 16:  return 8;    // GRAY
        case 17:  return 12;   // LIGHTGRAY
        default:  return 15;   // WHITE
    };
}

// ********** S C R O L L T E X T   S Y S T E M  ***** S C R O L L T E X T   S Y S T E M  ***** S C R O L L T E X T   S Y S T E M  ***** E N D
// ********** S C R O L L T E X T   S Y S T E M  ***** S C R O L L T E X T   S Y S T E M  ***** S C R O L L T E X T   S Y S T E M  ***** E N D
// ********** S C R O L L T E X T   S Y S T E M  ***** S C R O L L T E X T   S Y S T E M  ***** S C R O L L T E X T   S Y S T E M  ***** E N D

// ********** T E R M I N A L   S Y S T E M  ***** T E R M I N A L   S Y S T E M  ***** T E R M I N A L   S Y S T E M  ***** B E G I N
// ********** T E R M I N A L   S Y S T E M  ***** T E R M I N A L   S Y S T E M  ***** T E R M I N A L   S Y S T E M  ***** B E G I N
// ********** T E R M I N A L   S Y S T E M  ***** T E R M I N A L   S Y S T E M  ***** T E R M I N A L   S Y S T E M  ***** B E G I N

static const kb_layout[] = {
    KEY_ESCAPE ,0 , 0, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12, 0, KEY_PRINT_SCREEN, KEY_SCROLL_LOCK, KEY_PAUSE, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    KEY_GRAVE, KEY_ONE, KEY_TWO, KEY_THREE, KEY_FOUR, KEY_FIVE, KEY_SIX, KEY_SEVEN, KEY_EIGHT, KEY_NINE, KEY_ZERO, KEY_MINUS, KEY_EQUAL, KEY_BACKSPACE, KEY_BACKSPACE, 0, KEY_INSERT, KEY_HOME, KEY_PAGE_UP, 0, KEY_NUM_LOCK, KEY_KP_DIVIDE, KEY_KP_MULTIPLY, KEY_KP_SUBTRACT, 
    KEY_TAB, KEY_TAB, KEY_Q, KEY_W, KEY_E, KEY_R, KEY_T, KEY_Y, KEY_U, KEY_I, KEY_O, KEY_P, KEY_LEFT_BRACKET, KEY_RIGHT_BRACKET, KEY_BACKSLASH, 0, KEY_DELETE, KEY_END, KEY_PAGE_DOWN, 0, KEY_KP_7, KEY_KP_8, KEY_KP_9, KEY_KP_ADD, 
    KEY_CAPS_LOCK, KEY_CAPS_LOCK, KEY_A, KEY_S, KEY_D, KEY_F, KEY_G, KEY_H, KEY_J, KEY_K, KEY_L, KEY_SEMICOLON, KEY_APOSTROPHE, KEY_ENTER, KEY_ENTER, 0, 0, 0, 0, 0, KEY_KP_4, KEY_KP_5, KEY_KP_6, KEY_KP_ADD, 
    KEY_LEFT_SHIFT, KEY_LEFT_SHIFT, KEY_Z, KEY_X, KEY_C, KEY_V, KEY_B, KEY_N, KEY_M, KEY_COMMA, KEY_PERIOD, KEY_SLASH, KEY_RIGHT_SHIFT, KEY_RIGHT_SHIFT, KEY_RIGHT_SHIFT, 0, 0, KEY_UP, 0, 0, KEY_KP_1, KEY_KP_2, KEY_KP_3, KEY_KP_ENTER, 
    KEY_LEFT_CONTROL, KEY_LEFT_SUPER, KEY_LEFT_ALT, KEY_SPACE, KEY_SPACE, KEY_SPACE, KEY_SPACE, KEY_SPACE, KEY_SPACE, KEY_SPACE, KEY_SPACE, KEY_RIGHT_ALT, KEY_RIGHT_SUPER, KEY_KB_MENU, KEY_RIGHT_CONTROL, 0, KEY_LEFT, KEY_DOWN, KEY_RIGHT, 0, KEY_KP_0, KEY_KP_0, KEY_KP_DECIMAL, KEY_KP_ENTER
};

// TERMINALDISPLAY (ie. 4)

bool init_terminal(asset_id) {
    int display = sys.video.current_virtual;
    unsigned int page_state = 0;
    unsigned int layer_state = 0;
    unsigned int cell_state = 0;
    init_page((Vector2){40, 24}, page_state, layer_state, cell_state, asset_id);
    return 0;
}

// Establish keyboard management / buffer
// Establish mouse management (old x,y / current x,y)
void update_terminal(void) {
// RLAPI void PollInputEvents(void);                                 // Register all input events
// RLAPI int GetKeyPressed(void);                                // Get key pressed (keycode), call it multiple times for keys queued
// RLAPI int GetCharPressed(void);                               // Get char pressed (unicode), call it multiple times for chars queued
// RLAPI bool IsMouseButtonPressed(int button);                  // Check if a mouse button has been pressed once
// RLAPI bool IsMouseButtonDown(int button);                     // Check if a mouse button is being pressed
// RLAPI bool IsMouseButtonReleased(int button);                 // Check if a mouse button has been released once
// RLAPI bool IsMouseButtonUp(int button);                       // Check if a mouse button is NOT being pressed

}

// ********** T E R M I N A L   S Y S T E M  ***** T E R M I N A L   S Y S T E M  ***** T E R M I N A L   S Y S T E M  ***** E N D
// ********** T E R M I N A L   S Y S T E M  ***** T E R M I N A L   S Y S T E M  ***** T E R M I N A L   S Y S T E M  ***** E N D
// ********** T E R M I N A L   S Y S T E M  ***** T E R M I N A L   S Y S T E M  ***** T E R M I N A L   S Y S T E M  ***** E N D

// ********** R U N T I M E   S Y S T E M  ***** R U N T I M E   S Y S T E M  ***** R U N T I M E   S Y S T E M  ***** B E G I N
// ********** R U N T I M E   S Y S T E M  ***** R U N T I M E   S Y S T E M  ***** R U N T I M E   S Y S T E M  ***** B E G I N
// ********** R U N T I M E   S Y S T E M  ***** R U N T I M E   S Y S T E M  ***** R U N T I M E   S Y S T E M  ***** B E G I N

int init_default_assets() {
    sys.asset.total_assets = 0;

    int id; // when read, id returns -1 from total_assets
    id = init_frame_buffer(TERMINALDISPLAY, (Vector2) {512, 224});
    id = init_frame_buffer(PAUSEDISPLAY, (Vector2) {512, 224});
    id = init_frame_buffer(MENUDISPLAY, (Vector2) {284, 192});
    id = init_frame_buffer(PRIMARYDISPLAY, (Vector2) {512, 224});

	id = load_palette((Vector2){16,16}, VGACOLORS_FILENAME, VGACOLORS_FILEEXT, VGACOLORS_DATA, VGACOLORS_FILESIZE, VGACOLORS_PAK);
	id = load_palette((Vector2){16,16}, A8COLORS_FILENAME, A8COLORS_FILEEXT, A8COLORS_DATA, A8COLORS_FILESIZE, A8COLORS_PAK);
	id = load_asset(ASSET_ICON, ICON_FILENAME, ICON_FILEEXT, ICON_DATA, ICON_FILESIZE, ICON_PAK);

    id = load_tileset((Vector2){16,2}, A8COPPER_FILENAME, A8COPPER_FILEEXT, A8COPPER_DATA, A8COPPER_FILESIZE, A8COPPER_PAK, 0);
	id = load_tileset((Vector2){16,16}, FONT_ATASCII_FILENAME, FONT_ATASCII_FILEEXT, FONT_ATASCII_DATA, FONT_ATASCII_FILESIZE, FONT_ATASCII_PAK, 0);
	id = load_tileset((Vector2){16,16}, FONT_ATASCII_BIG_FILENAME, FONT_ATASCII_BIG_FILEEXT, FONT_ATASCII_BIG_DATA, FONT_ATASCII_BIG_FILESIZE, FONT_ATASCII_BIG_PAK, 0);
	id = load_tileset((Vector2){16,16}, FONT_VGA_FILENAME, FONT_VGA_FILEEXT, FONT_VGA_DATA, FONT_VGA_FILESIZE, FONT_VGA_PAK, 0);
	id = load_tileset((Vector2){64,1}, FONT_JJ_FILENAME, FONT_JJ_FILEEXT, FONT_JJ_DATA, FONT_JJ_FILESIZE, FONT_JJ_PAK, 32);
	id = load_tileset((Vector2){96,1}, FONT_OSD_FILENAME, FONT_OSD_FILEEXT, FONT_OSD_DATA, FONT_OSD_FILESIZE, FONT_OSD_PAK, 32);
	id = load_tileset((Vector2){16,16}, LINES_FILENAME, LINES_FILEEXT, LINES_DATA, LINES_FILESIZE, LINES_PAK, 0);
}

// establish scripting mechanism.  A script is an asset.  Bootstrap is from a script asset(0) ("rom" program)


//RLAPI void SetExitKey(false);

int init_system(const char* title) {
    int status = false;


    bool display_status = init_display_properties(true, title);
    bool assets_status = init_default_assets();
    bool terminal_status = init_terminal(8);
    bool audio_status = init_audio_properties();

    // init bootstrap script - TO DO

    return status;
}

static int update_system(void) {
    int status = false;
    
    update_terminal();
    update_assets();
    update_audio();
    update_display();

    return status;
}

static int exit_system(void) {
    int status = false;
    unload_all_assets();
// unload pages layers and cells
    deinit_display();
    return status;
}

int process_system(void) {
    //  stage following;
    //  - Initialisation process
    //  - updating process
    //  - exit process
}

// ********** R U N T I M E   S Y S T E M  ***** R U N T I M E   S Y S T E M  ***** R U N T I M E   S Y S T E M  ***** E N D
// ********** R U N T I M E   S Y S T E M  ***** R U N T I M E   S Y S T E M  ***** R U N T I M E   S Y S T E M  ***** E N D
// ********** R U N T I M E   S Y S T E M  ***** R U N T I M E   S Y S T E M  ***** R U N T I M E   S Y S T E M  ***** E N D

#ifdef __cplusplus
}
#endif
