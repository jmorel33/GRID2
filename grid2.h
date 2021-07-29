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

#define SUPPORT_TRACELOG 1
#include "utils.h"           // Required for: TRACELOG macros
#include "raylib.h"          // works on version 3.8 development
#include "raymath.h"
#include "rlgl.h"            // raylib OpenGL abstraction to OpenGL 1.1, 3.3 or ES2
#include <GLFW/glfw3.h>

//#include <windows.h> 
#include <stdlib.h>         // header of the general purpose standard library
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <limits.h>
#include <string.h>         // set of functions implementing operations on strings
#include <time.h>
//#include <strsafe.h>      // replace standard C string handling and I/O functions including printf, strlen, strcpy and strcat
//#include <tchar.h>        // for string functions makes code compliant to both Unicode and non-unicode environments
//#include <errno.h>        // A value (the error number) is stored in errno by certain library functions when they detect errors
//#include <unistd.h>       // provides access to the POSIX operating system API
//#include <fcntl.h>        // system-wide table of files opened by all processes, called the file table

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

#ifdef __cplusplus // Calling C code from C++
extern "C" { 
#endif

// **************************************************************************************** U T I L I T Y   M A C R O S   &   F U N C T I O N S

#define BITS_ON(a,b)    (a |= (b))
#define BITS_OFF(a,b)   (a &= ~(b))
#define BITS_INIT(a, b) (a = (b))
#define BITS_FLIP(a, b) (a ^= (b))
#define BITS_TEST(a, b) (a & (b))

#define BIT_LITERAL_ON_OFF(s) ((s) > 0 ? ("ON") : ("OFF"))
#define BIT_LITERAL_TRUE_FALSE(s) ((s) > 0 ? ("TRUE") : ("FALSE"))

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))
#define is_digit(c) ('0' <= (c) && (c) <= '9')

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
        for(i = 0; i < fifo_entries; i++) {            fifo_data[i] = fifo_data[i+1];	}
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

#define SIGN(x) ((x) >= 0 ? 1 : -1)
#define ABS(x) ((x) > 0 ? (x) : -(x))

#define EPSILON     1.19209290e-7f
#define TAU         6.28318530717958647692528676655900576f
#define TAU_OVER2   3.14159265358979323846264338327950288f
#define HALF_PI     1.570796326794896619231321691639751442f
#define QUARTER_PI  0.785398163397448309615660845819875721f
#define DIVIDEH_PI  0.159154943091895335768883763372514362f
#define DIVIDEH_TAU 0.636619772367581343075535053490057448f
#define LOG2        0.693147180559945309417232121458176568f
#define LOG10       2.30258509299404568401799145468436421f
#define E           2.71828182845904523536f
#define SQRT2       1.41421356237309504880168872420969808f
#define SQRT3       1.73205080756887729352744634150587236f
#define SQRT5       2.23606797749978969640917366873127623f

static inline float Rand(float a) {	return (float)rand()/(float)(RAND_MAX/a);}

static inline float fast_sin(double x) {
    x *= DIVIDEH_PI;
    x -= (int32_t) x;
    if (x <= 0.5) {
        double t = 2 * x * (2 * x - 1);
        return (TAU_OVER2 * t) / ((TAU_OVER2 - 4) * t - 1);
    } else {
        double t = 2 * (1 - x) * (1 - 2 * x);
        return -(TAU_OVER2 * t) / ((TAU_OVER2 - 4) * t - 1);
    }
}

static inline float fast_cos(double x) {
    return fast_sin(x + HALF_PI);
}

static inline double dfast_sin(double x) {
    x *= DIVIDEH_PI;
    x -= (int32_t) x;
    if (x <= 0.5) {
        double t = 2 * x * (2 * x - 1);
        return (TAU_OVER2 * t) / ((TAU_OVER2 - 4) * t - 1);
    } else {
        double t = 2 * (1 - x) * (1 - 2 * x);
        return -(TAU_OVER2 * t) / ((TAU_OVER2 - 4) * t - 1);
    }
}

static inline double dfast_cos(double x) {
    return fast_sin(x + HALF_PI);
}

float ffast_rsqrt(float value) {  /* PULLED FROM QUAKE SOURCE */
	union { int32_t i; float f; } t;
	float half = value * 0.5f;
	t.f = value;
	t.i = 0x5f375a86 - (t.i >> 1);
	t.f = t.f * (1.5f - (half * t.f * t.f)); /* 1st iteration */
	t.f = t.f * (1.5f - (half * t.f * t.f)); /* 2nd iteration, adds more precision */
	return t.f;
}

static inline float ffast_ceil(float x)  { return (float)((x < 0) ? (int32_t)x : ((int32_t)x)+1); }
static inline float ffast_floor(float x) { return (float)((x >= 0.0f) ? (int32_t)x : (int32_t)(x-0.9999999999999999f)); }
static inline float ffast_round(float x) { return (float)((x >= 0.0f) ? ffast_floor(x + 0.5f) : ffast_ceil(x - 0.5f)); }
static inline float ffast_remainder(float x, float y) {	return x - (ffast_round(x/y)*y);}
static inline float ffast_copysign(float x, float y) {
	int32_t ix, iy;
	ix = *(int32_t *)&x;
	iy = *(int32_t *)&y;
	ix &= 0x7fffffff;
	ix |= iy & 0x80000000;
	return *(float *)&ix;
}

static inline float ffast_mod(float x, float y) {
	float result;
	y = ABS(y);
	result = ffast_remainder(gb_abs(x), y);
	if (SIGN(result)) result += y;
	return ffast_copysign(result, x);
}

static inline float ffast_tan(float radians) {
    float rr = radians * radians;
    float a;
    a = 9.5168091e-03f;     a *= rr;
    a += 2.900525e-03f;     a *= rr;
    a += 2.45650893e-02f;   a *= rr;
    a += 5.33740603e-02f;   a *= rr;
    a += 1.333923995e-01f;  a *= rr;
    a += 3.333314036e-01f;  a *= rr;
    a += 1.0f;
    a *= radians;
    return a;
}

static inline float ffast_atan(float a)	{
    float u  = a*a;
    float u2 = u*u;
    float u3 = u2*u;
    float u4 = u3*u;
    float f  = 1.0f + 0.33288950512027f * u - 0.08467922817644f * u2 + 0.03252232640125f * u3 - 0.00749305860992f * u4;
    return a/f;
}

// use type punning instead of pointer arithmatics, to require proper alignment
static inline float absf(float f) {
    // optimizer will optimize away the `if` statement and the library call
    if (sizeof(float) == sizeof(uint32_t)) {
        union { float f; uint32_t i; } u;
        u.f = f;
        u.i &= 0x7fffffff;
        return u.f;
    }
    return fabsf(f);
}

static int32_t gcdl(int32_t a, int32_t b) {
    if (a == 0) return b; else if (b == 0) return a;
    if (a < b) return gcd_l(a, b % a); else return gcd_l(b, a % b);
}

static int32_t gcdi(int32_t a, int32_t b) {
    int32_t res = a%b;
    while (res > 0) { a = b; b = res; res = a % b; }
    return b;
}

//	Phase Shift 26.2 (These table values were sourced from the MAME project's TIA emulation for the palette management)
	/*static constexpr float color[16][2] =	{
		{  0.000,  0.000 }, {  0.192, -0.127 },	{  0.241, -0.048 },	{  0.240,  0.040 },	{  0.191,  0.121 },	{  0.103,  0.175 },	{ -0.008,  0.196 },	{ -0.116,  0.174 },
        { -0.199,  0.118 },	{ -0.243,  0.037 },	{ -0.237, -0.052 },	{ -0.180, -0.129 },	{ -0.087, -0.181 },	{  0.021, -0.196 },	{  0.130, -0.169 },	{  0.210, -0.107 }
	};*/
// YIQ formula for Atari 8bit GTIA colors (0-255) index
// https://atariage.com/forums/topic/107853-need-the-256-colors/page/2/#comments
// The following routine is currently dead code as I personally do not like the resulting colors...  Something is wrong in the translation from YIQ
// separate in tywo functions; one that takes a value and returns RGB, and one that takes YIQ and returns RGB
Color gtia_ntsc_to_rgb(int16_t val) {
    int16_t chroma = (val >> 4) & 15;
    int16_t luminence = val & 15;
    int16_t crlv = chroma ? 50 : 0;
 
    float phase = ((chroma - 1.) * 25. - 58.) * (2. * PI / 360.);

    float y = 255 * (luminence + 1.) / 16.;
    float i = crlv * cos(phase);
    float q = crlv * sin(phase);

    float r = y + 0.956294832320893995 * i + 0.621025125444728741 * q;
    float g = y - 0.2721214740839773195 * i - 0.6473809535176157223 * q;
    float b = y - 1.106989908567128216 * i + 1.704614975498829329 * q;

	if (r < 0) r = 0; else if (r > 255) r = 255;
	if (g < 0) g = 0; else if (g > 255) g = 255;;
	if (b < 0) b = 0; else if (b > 255) b = 255;;

    r = pow(r, 0.9);
    g = pow(g, 0.9);
	b = pow(b, 0.9);

    Color col={(uint8_t)r, (uint8_t)g, (uint8_t)b, 255};
    return col;
}

/*  VERY OLD Blitz3D code
Function yiq_rgb(y#,i#,q#, r#, g#, b#)
;Y = range [0.,1.] (luminance)
;I = range [-0.5957161349127745527,0.5957161349127745527] (red/green)
;Q = range [-0.5225910452916111684,0.5225910452916111684] (blue/yellow)
   red%   = (y + (0.956294832320893995 * i) + (0.621025125444728741 * q)) * r
   green% = (y - (0.2721214740839773195 * i) - (0.6473809535176157223 * q)) * g
   blue%  = (y - (1.106989908567128216 * i) + (1.704614975498829329 * q)) * b
   If red < 0   Then red = 0 ElseIf red > 255 Then red = 255
   If green < 0   Then green = 0 ElseIf green > 255 Then green = 255
   If blue < 0   Then blue = 0 ElseIf blue > 255 Then blue = 255
   Return ((red And $FF) Shl 16) Or ((green And $FF) Shl 8) Or (blue And $FF)
End Function
*/

/* ******** KEYBOARD SCANNING
************** USING WINDOWS: api_OemKeyScan% (wOemChar%) : "OemKeyScan"
Dim scancodes(256)
For i = 0 To 255
   scancodes(i) = api_OemKeyScan(i) And $ff
Next
repeat_delay = 500
repeat_rate = 100
Print "TYPE HERE:"
While Not KeyDown(1)
   timer = MilliSecs()
   ascii% = GetKey()
   If ascii > 0 Then
      ascii_repeat = ascii
      scancode% = scancodes(ascii)
      repeat_timer = timer + repeat_delay
      Write Chr$(ascii)
   EndIf
   If KeyDown(scancode) = True Then
      If timer >= repeat_timer Then
         Write Chr$(ascii_repeat)
         repeat_timer = timer + repeat_rate
      EndIf
   Else
      scancode = 0
   EndIf
Wend
*/

char *time_stamp(){
    char *timestamp = (char *)malloc(20);
    time_t ltime = time(NULL);
    struct tm *tm;
    tm = localtime(&ltime);
    sprintf(timestamp,"%04d/%02d/%02d-%02d:%02d:%02d", tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
    return timestamp;
}

// to be determined (need this to replace the RayLib basic Vector structs)
/*typedef union Vector2 {
	struct { float x, y; };
	float f[2];
} Vector2;

typedef union Vector3 {
	struct { float x, y, z; };
	struct { float r, g, b; };
	Vector2 xy;
	float f[3];
} Vector3;

typedef union Vector4 {
	struct { float x, y, z, w; };
	struct { float r, g, b, a; };
	struct { Vector2 xy, zw; };
	Vector3 xyz;
	Vector3 rgb;
	float f[4];
} Vector4;
*/
// **************************************************************************************** R A Y L I B   E X T E N S I O N S

void DrawTextImage(Texture texture, uint8_t* txt, Vector2 position) {
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
void DrawRectanglePro2(Rectangle rec, Vector2 origin, Vector2 skew, float rotation, Color color[4]) {
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
void DrawTexturePro2 (Texture texture, Rectangle source, Rectangle dest, Vector2 origin, Vector2 skew, float rotation, Color color[4]) {
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

Color get_pixel_color(Image *image, Vector2 position) {
    //check for out of bound

    uint32_t offset = (position.y * image->width + position.x) * 4;
    Color *data = &image->data;
    return data[offset];
//    uint8_t r = data[offset];
//    uint8_t g = data[offset + 1];
//    uint8_t b = data[offset + 2];
//    uint8_t a = data[offset + 3];
//    return (Color){r, g, b, a};
}


// **************************************************************************************** G R I D   S T R U C T U R E S
#define NAMELENGTH_MAX      80
#define GRID_MAX_CELLS      65536
#define GRID_MAX_PAGEGROUPS 5
#define GRID_MAX_PAGES      16
#define PAGE_MAX_PALETTES   8
#define PAGE_MAX_ASSETS     8


typedef struct EX_cell {
    uint64_t state;                        // all flags for cell
    uint16_t value;                       // value of cell
    uint8_t lines;                        // lines feature
    uint16_t asset_id;                    // Each cell can point to a different tileset
    uint16_t cycle_id;                    // cell animation sequence number
    uint16_t palette_id;                  // color palette used for whole page
    uint16_t colorfg_id;                  // palette index color for cell
    uint16_t colorfg_cycle_id;            // color cycle index for cell
    uint16_t colorbg_id;                  // palette index color for cell background
    uint16_t colorbg_cycle_id;            // color cycle index for cell background
    uint16_t colorln_id;                  // palette index color for cell lines
    uint16_t colorln_cycle_id;            // color cycle index for cell lines
    Vector2 offset;                             // displacement from top left (x,y)
    Vector2 skew;                               // horizontal and vertical skew
    Vector2 scale;                              // (x,y) cell scale
    Vector2 scale_speed;                        // (x,y) cell scale speed
    Vector2 scroll_speed;                       // (x,y) cell scroll speed
    float angle;                                // degree of angle used to rotate the cell
    float fg_brightness;                        // foreground brightness (values 0...1 divides, values 1 to 255 multiply)
    float bg_brightness;                        // background brightness (values 0...1 divides, values 1 to 255 multiply)
    uint8_t alpha;                        // transparency
    Color color_mask;                           // RGBA color mask of cell
    Color shadow_mask;                          // shadow RGBA mask
} EX_cell;

typedef struct EX_page {
    char name[NAMELENGTH_MAX + 1];
    uint64_t state;                        // all flags for grid
    uint16_t asset_id[PAGE_MAX_PALETTES];  // tilset used for this page
    uint16_t default_asset_id;
    Vector2 size;                               // total cells x and y
    uint16_t palette_id[PAGE_MAX_PALETTES]; // color palette used for whole page
    uint16_t default_palette_id;          // color palette used for whole page
    uint16_t default_colorfg_id;          // palette index color for cell
    uint16_t default_colorbg_id;          // palette index color for cell background
    uint16_t default_colorln_id;          // palette index color for cell lines
    Vector2 offset;                             // displacement from top left (x,y)
    Vector2 displace[4];                        // cell corner displacement (x,y)
    Vector2 scale;                              // (x,y) cell scale
    Vector2 scale_speed;                        // (x,y) cell scale speed
    Vector2 scroll_speed;                       // page scroll speed (x,y)
    float angle;                                // degree of angle to rotate page
    float fg_brightness;                        // foreground brightness (values 0...1 divides, values 1 to 255 multiply)
    float bg_brightness;                        // background brightness (values 0...1 divides, values 1 to 255 multiply)
    uint8_t alpha;                        // transparency
    Vector2 shadow;                             // shadow corner displacement (x,y)
    Vector2 shadow_displace[4];                 // shadow corners displacement (x,y)
    Color   color_mask;                         // RGBA color mask of page
    Color   shadow_mask;                        // shadow RGBA mask
    EX_cell mouse;                              // mouse cursor
    EX_cell keyboard;                           // key cursor
    EX_cell mask;                               // used for when replicating
    uint32_t cell_count;
    EX_cell* cell; // could be NULL
} EX_page;

typedef enum {
    PGGP_DELETE              = 0b10000000000000000000000000000000,
    PGGP_UPDATE              = 0b01000000000000000000000000000000,
    PGGP_INITIALIZED         = 0b00000000000000000000000000000001,
} pagegroup_states;

typedef struct EX_pagegroup {
    char name[NAMELENGTH_MAX + 1];
    uint32_t state;
    int page_count;                            // total number of pages
    uint16_t default_asset_id;
    uint16_t default_palette_id;          // color palette used for whole page
    uint16_t default_colorfg_id;          // palette index color for cell
    uint16_t default_colorbg_id;          // palette index color for cell background
    uint16_t default_colorln_id;          // palette index color for cell lines
    EX_page* page;                             // could be NULL (if not initialized)
} EX_pagegroup;

// **************************************************************************************** A S S E T   S T R U C T U R E S
#define MAXASSETS 1024
#define MAXPALETTECOLORS 4096

typedef struct EX_tileset {
    Vector2 tilesize;                           // Tile size
    Vector2 count;                              // number of tiles (x, y)
    Texture tex;                                // Characters texture atlas
    uint32_t total;                         // Number of Tiles
    int ascii_start;                            // if tileset if character font, identifies ascii code first tile
} EX_tileset;

typedef struct EX_asset {
    char name[NAMELENGTH_MAX + 1];
    uint32_t total_assets;
    uint16_t lines_id;
    uint16_t basefont_id;

    uint32_t dead_assets[MAXASSETS];

    uint32_t asset_type[MAXASSETS];
    uint32_t state[MAXASSETS];
    int data_size[MAXASSETS];                   // storage space size in bytes

    Image img[MAXASSETS];                       // storage space for unpacked images
    Texture tex[MAXASSETS];                     // storage space for textures
    Color *palette[MAXASSETS];                  // storage space for indexed colors
    uint32_t palette_colors[MAXASSETS];     // total number of colors in palette
    EX_tileset tileset[MAXASSETS];              // storage space for texture based fonts
    RenderTexture framebuffer[MAXASSETS];       // storage space for frame buffer
    Font font[MAXASSETS];                       // storage space for texture based fonts
    Music music[MAXASSETS];                     // storage space for unpacked music
    Shader shader[MAXASSETS];                   // storage space for shaders
    uint8_t *data[MAXASSETS];             // storage space for any text, data, JSON, LUA ...
} EX_asset;

// **************************************************************************************** A U D I O   S T R U C T U R E S

#define MAXAUDIOTRACKS 10
#define MAXORDERS 50

typedef struct EX_track {
    bool is_playing;
    uint32_t state;
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
#define UNFOCUSEDDISPLAY 3
#define TERMINALDISPLAY 4

typedef struct EX_video {
    //uint32_t state;
    uint32_t state[MAXDISPLAYS];            // virtual display state
    Vector2 screen[MAXDISPLAYS];                // Windows Display Resolution (x, y)
    uint32_t screen_rate[MAXDISPLAYS];               // screen refresh rate
    uint32_t fps[MAXDISPLAYS];                       // frames per second
    uint32_t frames[MAXDISPLAYS];                    // number of game frame elasped since initialisation
    double prev_time[MAXDISPLAYS];              // keep track of time to grab delta
    double elapsed_time_nofocus[MAXDISPLAYS];   // elapsed time since nofocus
    double elapsed_time[MAXDISPLAYS];           // elapsed time in milliseconds since last frame refresh
    float elapsed_time_var[MAXDISPLAYS];        // elapsed time in milliseconds since last frame refresh (with ratio)
    float elapsed_time_var_ratio[MAXDISPLAYS];  // multiplication factor
    float value_anim[MAXDISPLAYS];              // space for animated controls (to be elaborated)
    float frame_time[MAXDISPLAYS];
    float frame_time_inc[MAXDISPLAYS];
    Vector2 virtual_res[MAXDISPLAYS];           // framebuffer resolution (x, y)
    uint16_t virtual_asset[MAXDISPLAYS];             // framebuffer asset number

    EX_pagegroup pagegroup[MAXDISPLAYS];        // pagegroup data

    uint32_t windowstate_normal;            // screen window state in normal mode
    uint32_t windowstate_paused;            // screen window state when game is paused
    uint16_t display_id;                             // screen currently used
    bool screen_refresh;
    uint16_t current_virtual;                        // virtual display currently used
    uint16_t previous_virtual;                       // virtual display previously used

    bool window_focus;                          // last state of window focus (true = in applicatioo, false = outside of application)
} EX_video;


// **************************************************************************************** T E R M I N A L   S T R U C T U R E S

#define IOBUFFERSIZE 8192

typedef struct EX_terminal {
    uint32_t state;
    uint16_t asset_id;
    uint16_t pagegroup_id; // Where all terminal pages reside
    uint16_t current_page_id;
    uint16_t previous_page_id;
    Vector2 last_mouse_poll;
    Vector2 last_cursor_poll;
    uint8_t input_buffer[IOBUFFERSIZE];
    uint8_t output_buffer[IOBUFFERSIZE];
    uint32_t input_buffer_pos;
    uint32_t output_buffer_pos;
    
} EX_terminal;


// **************************************************************************************** A P P L I C A T I O N   S T R U C T U R E S

// The heartbeat of the system flows through these 64 oscillator states
// With this comes a period table spanning from slow 8 second up to fast millisecond level state changes
// With this a function to poll oscillator states
typedef struct EX_temporal {
    double period_table[64];
    uint64_t prev_osc;
    uint64_t osc;
    uint64_t osc_count[64];         // counts are on full cycles
    double osc_next_frame[64];  // calculated following frame to trigger a state change
} EX_temporal;

typedef struct EX_player {

} EX_player;

typedef struct EX_game {
    EX_player player;

} EX_game;

typedef enum {
    CTRL_DEINIT                 = 0b10000000000000000000000000000000,
    CTRL_INITIALIZE             = 0b01000000000000000000000000000000,
    CTRL_EXIT                   = 0b00100000000000000000000000000000,
    CTRL_INIT_TITLE             = 0b00010000000000000000000000000000,
    CTRL_IN_TITLE               = 0b00001000000000000000000000000000,
    CTRL_INIT_MENU1             = 0b00000100000000000000000000000000,
    CTRL_IN_MENU1               = 0b00000010000000000000000000000000,
    CTRL_INIT_MENU2             = 0b00000001000000000000000000000000,
    CTRL_IN_MENU2               = 0b00000000100000000000000000000000,
    CTRL_INIT_MENU3             = 0b00000000010000000000000000000000,
    CTRL_IN_MENU3               = 0b00000000001000000000000000000000,
    CTRL_INIT_MENU4             = 0b00000000000100000000000000000000,
    CTRL_IN_MENU4               = 0b00000000000010000000000000000000,
    CTRL_GAME_RESUME            = 0b00000000000001000000000000000000,
    CTRL_GAME_PLAY              = 0b00000000000000100000000000000000,
    CTRL_INIT_GAME              = 0b00000000000000010000000000000000,
    CTRL_GAME_NEXT              = 0b00000000000000001000000000000000,
    CTRL_GAMEOVER               = 0b00000000000000000100000000000000,
    CTRL_GAME_DEATH             = 0b00000000000000000010000000000000,
    CTRL_R13                    = 0b00000000000000000001000000000000,
    CTRL_OFF_FOCUS              = 0b00000000000000000000100000000000,
    CTRL_DEBUG                  = 0b00000000000000000000010000000000,
    CTRL_SHOW_TERMINAL          = 0b00000000000000000000001000000000,
    CTRL_GAME_PAUSED            = 0b00000000000000000000000100000000,
    CTRL_R8                     = 0b00000000000000000000000010000000,
    CTRL_IN_GAME                = 0b00000000000000000000000001000000,
    CTRL_RUNNING                = 0b00000000000000000000000000100000,
    CTRL_TEMPORAL_INITIALIZED   = 0b00000000000000000000000000010000,
    CTRL_AUDIO_INITIALIZED      = 0b00000000000000000000000000001000,
    CTRL_TERMINAL_INITIALIZED   = 0b00000000000000000000000000000100,
    CTRL_ASSETS_INITIALIZED     = 0b00000000000000000000000000000010,
    CTRL_VIDEO_INITIALIZED      = 0b00000000000000000000000000000001,
    CTRL_SWITCHBOARD_MASK       = 0b11111111111111111111000000000000, // to filter out base states
    CTRL_SERVICES_MASK          = 0b00000000000000000000111111111111, // to filter out switchboard states
    CTRL_NULL                   = 0b00000000000000000000000000000000  // in case that happens... (should never)
} control_state;

const char* control_state_literal(uint32_t state) {
    switch (state) {
    case CTRL_DEINIT:              return "SWITCHBOARD: CTRL_DEINIT";
    case CTRL_INITIALIZE:          return "SWITCHBOARD: CTRL_INITIALIZE";
    case CTRL_EXIT:                return "SWITCHBOARD: CTRL_EXIT";
    case CTRL_INIT_TITLE:          return "SWITCHBOARD: CTRL_INIT_TITLE";
    case CTRL_IN_TITLE:            return "SWITCHBOARD: CTRL_IN_TITLE";
    case CTRL_INIT_MENU1:          return "SWITCHBOARD: CTRL_INIT_MENU1";
    case CTRL_IN_MENU1:            return "SWITCHBOARD: CTRL_IN_MENU1";
    case CTRL_INIT_MENU2:          return "SWITCHBOARD: CTRL_INIT_MENU2";
    case CTRL_IN_MENU2:            return "SWITCHBOARD: CTRL_IN_MENU2";
    case CTRL_INIT_MENU3:          return "SWITCHBOARD: CTRL_INIT_MENU3";
    case CTRL_IN_MENU3:            return "SWITCHBOARD: CTRL_IN_MENU3";
    case CTRL_INIT_MENU4:          return "SWITCHBOARD: CTRL_INIT_MENU4";
    case CTRL_IN_MENU4:            return "SWITCHBOARD: CTRL_IN_MENU4";
    case CTRL_GAME_RESUME:         return "SWITCHBOARD: CTRL_GAME_RESUME";
    case CTRL_GAME_PLAY:           return "SWITCHBOARD: CTRL_GAME_PLAY";
    case CTRL_INIT_GAME:           return "SWITCHBOARD: CTRL_INIT_GAME";
    case CTRL_GAME_NEXT:           return "SWITCHBOARD: CTRL_GAME_NEXT";
    case CTRL_GAMEOVER:            return "SWITCHBOARD: CTRL_GAMEOVER";
    case CTRL_GAME_DEATH:          return "SWITCHBOARD: CTRL_GAME_DEATH";
    case CTRL_OFF_FOCUS:           return "BASE STATES: CTRL_OFF_FOCUS";
    case CTRL_DEBUG:               return "BASE STATES: CTRL_DEBUG";
    case CTRL_SHOW_TERMINAL:       return "BASE STATES: CTRL_SHOW_TERMINAL";
    case CTRL_GAME_PAUSED:         return "BASE STATES: CTRL_GAME_PAUSED";
    case CTRL_IN_GAME:             return "BASE STATES: CTRL_IN_GAME";
    case CTRL_RUNNING:             return "BASE STATES: CTRL_RUNNING";
    case CTRL_AUDIO_INITIALIZED:   return "BASE STATES: CTRL_AUDIO_INITIALIZED";
    case CTRL_TERMINAL_INITIALIZED:return "BASE STATES: CTRL_TERMINAL_INITIALIZED";
    case CTRL_ASSETS_INITIALIZED:  return "BASE STATES: CTRL_ASSETS_INITIALIZED";
    case CTRL_VIDEO_INITIALIZED:   return "BASE STATES: CTRL_VIDEO_INITIALIZED";
    default: return NULL;
    }
}

typedef enum {
    PMSN_INFINITE_LIVES     = 0b10000000000000000000000000000000,
    PMSN_INFINITE_POWER     = 0b01000000000000000000000000000000,
    PMSN_INFINITE_TIME      = 0b00100000000000000000000000000000,
    PMSN_NO_COLLISION       = 0b00010000000000000000000000000000,
    PMSN_POWERUPS           = 0b00001000000000000000000000000000,
    PMSN_NAVIGATE_LEVELS    = 0b00000100000000000000000000000000,
    PMSN_DEATH              = 0b00000010000000000000000000000000,
    PMSN_SUMMON             = 0b00000001000000000000000000000000,
    PMSN_END_GAME           = 0b00000000100000000000000000000000,
    PMSN_BENCHMARK          = 0b00000000000001000000000000000000,
    PMSN_ATTRACT            = 0b00000000000000100000000000000000,
    PMSN_R17                = 0b00000000000000010000000000000000,
    PMSN_TRACE              = 0b00000000000000001000000000000000,
    PMSN_R15                = 0b00000000000000000100000000000000,
    PMSN_R14                = 0b00000000000000000010000000000000,
    PMSN_R13                = 0b00000000000000000001000000000000,
    PMSN_R12                = 0b00000000000000000000100000000000,
    PMSN_R11                = 0b00000000000000000000010000000000,
    PMSN_R10                = 0b00000000000000000000001000000000,
    PMSN_R9                 = 0b00000000000000000000000100000000,
    PMSN_R8                 = 0b00000000000000000000000010000000,
    PMSN_R7                 = 0b00000000000000000000000001000000,
    PMSN_EDITOR_ADMIN       = 0b00000000000000000000000000100000,
    PMSN_EDITOR_USER        = 0b00000000000000000000000000010000,
    PMSN_TERMINAL_ADMIN     = 0b00000000000000000000000000001000,
    PMSN_TERMINAL_USER      = 0b00000000000000000000000000000100,
    PMSN_DEBUG_ADMIN        = 0b00000000000000000000000000000010,
    PMSN_DEBUG_USER         = 0b00000000000000000000000000000001,
    PMSN_OFF                = 0b00000000000000000000000000000000,
    PMSN_GAME_MASK          = 0b11111111111111110000000000000000,
    PMSN_GODMODE_MASK       = 0b11111111111111111111111111111111
} permission_state;

const char* permission_state_literal(uint32_t state) {
    switch (state) {
    case PMSN_INFINITE_LIVES:   return "PMSN_INFINITE_LIVES";
    case PMSN_INFINITE_POWER:   return "PMSN_INFINITE_POWER";
    case PMSN_INFINITE_TIME:    return "PMSN_INFINITE_TIME";
    case PMSN_NO_COLLISION:     return "PMSN_NO_COLLISION";
    case PMSN_POWERUPS:         return "PMSN_POWERUPS";
    case PMSN_NAVIGATE_LEVELS:  return "PMSN_NAVIGATE_LEVELS";
    case PMSN_DEATH:            return "PMSN_DEATH";
    case PMSN_SUMMON:           return "PMSN_SUMMON";
    case PMSN_END_GAME:         return "PMSN_END_GAME";
    case PMSN_BENCHMARK:        return "PMSN_BENCHMARK";
    case PMSN_ATTRACT:          return "PMSN_ATTRACT";
    case PMSN_TRACE:            return "PMSN_TRACE";
    case PMSN_EDITOR_ADMIN:     return "PMSN_EDITOR_ADMIN";
    case PMSN_EDITOR_USER:      return "PMSN_EDITOR_USER";
    case PMSN_TERMINAL_ADMIN:   return "PMSN_TERMINAL_ADMIN";
    case PMSN_TERMINAL_USER:    return "PMSN_TERMINAL_USER";
    case PMSN_DEBUG_ADMIN:      return "PMSN_DEBUG_ADMIN";
    case PMSN_DEBUG_USER:       return "PMSN_DEBUG_USER";
    default: return NULL;
    }
}

typedef struct EX_program {
        uint32_t ctrlstate;
        uint32_t ctrlstate_prev;
        uint32_t pmsnstate;
        char name[NAMELENGTH_MAX + 1];
        uint32_t status;
} EX_program;


// **************************************************************************************** S Y S T E M   S T R U C T U R E S

typedef struct EX_system {
    EX_temporal     temporal;
    EX_terminal     terminal;
    EX_asset        asset;
    EX_audio        audio;
    EX_video        video;
    EX_program      program;
} EX_system;

EX_system sys;

void set_permission(uint32_t state)     {BITS_ON(sys.program.pmsnstate, state);}
void unset_permission(uint32_t state)   {BITS_OFF(sys.program.pmsnstate, state);}
void flip_permission(uint32_t state)    {BITS_FLIP(sys.program.pmsnstate, state);}
uint32_t permission_valid(uint32_t state)   {return BITS_TEST(sys.program.pmsnstate, state);}

void add_service(uint32_t state)        {BITS_ON(sys.program.ctrlstate, state);}
void remove_service(uint32_t state)     {BITS_OFF(sys.program.ctrlstate, state);}
uint32_t service_active(uint32_t state)     {return BITS_TEST(sys.program.ctrlstate, state);}

void commute_to(uint32_t state) {
    BITS_OFF(sys.program.ctrlstate_prev, CTRL_SWITCHBOARD_MASK);
    BITS_ON(sys.program.ctrlstate_prev, sys.program.ctrlstate & CTRL_SWITCHBOARD_MASK);
    BITS_OFF(sys.program.ctrlstate, CTRL_SWITCHBOARD_MASK);
    BITS_ON(sys.program.ctrlstate, state);

    debug_console_out(">>>> commute_to", state);
};


Color get_palette_color(uint16_t palette_id, uint16_t id) {
    Color *color = sys.asset.palette[palette_id];
    return color[id];
}

Color get_palette_color2(uint16_t palette_id, uint16_t id, uint8_t alpha) {
    Color *color = sys.asset.palette[palette_id];
    return (Color){color[id].r, color[id].g, color[id].b, alpha};
}

Color get_palette_color_pro(uint16_t palette_id, uint16_t id, uint8_t alpha, float brightness) {
    Color *color = sys.asset.palette[palette_id];
    return (Color){color[id].r * brightness, color[id].g * brightness, color[id].b * brightness, 255};
}


#define GRIDILON     1.182940076

int init_temporal() {
    uint64_t osc;
    
    double range_high = 60.;
    double range_low = 1. / range_high;
    uint64_t steps = 64;

    double ratio =  range_low;
    double value = range_low;

    double t = GetTime();
    for (osc = 0; osc < steps; osc++) {
//        printf (" %i = %lf\n", osc, value);
        sys.temporal.period_table[osc] = value;
        sys.temporal.osc_count[osc] = 0;
        sys.temporal.osc_next_frame[osc] = sys.temporal.period_table[osc];

        value += range_low * ratio;
        ratio *= GRIDILON;
    }
    sys.temporal.prev_osc = 0; //
    sys.temporal.osc = 0; // oscillator states
    
    return osc;
}

void update_temporal() {
    uint64_t steps = 64;

    sys.temporal.prev_osc = sys.temporal.osc;
    double t = GetTime();
    for (uint64_t osc = 0; osc < steps; osc++) {
        if (t > sys.temporal.osc_next_frame[osc]) {
            while (1) {
                sys.temporal.osc_next_frame[osc] += sys.temporal.period_table[osc];
                sys.temporal.osc ^= ((uint64_t)1 << osc);
                sys.temporal.osc_count[osc] += 1;
                if (sys.temporal.osc_next_frame[osc] > t) break;
            }
        }
    }
}

// ********** G R I D   S Y S T E M  ***** G R I D   S Y S T E M  ***** G R I D   S Y S T E M  ***** B E G I N
// ********** G R I D   S Y S T E M  ***** G R I D   S Y S T E M  ***** G R I D   S Y S T E M  ***** B E G I N
// ********** G R I D   S Y S T E M  ***** G R I D   S Y S T E M  ***** G R I D   S Y S T E M  ***** B E G I N

typedef enum {
    GRFE_LINE_TOP           = 0b1000000000000000000000000000000000000000000000000000000000000000, // turn on line top
    GRFE_LINE_BOT           = 0b0100000000000000000000000000000000000000000000000000000000000000, // turn on line bottom
    GRFE_LINE_LEF           = 0b0010000000000000000000000000000000000000000000000000000000000000, // turn on line left
    GRFE_LINE_RIG           = 0b0001000000000000000000000000000000000000000000000000000000000000, // turn on line right
    GRFE_LINE_HOR           = 0b0000100000000000000000000000000000000000000000000000000000000000, // turn on line center horizontal
    GRFE_LINE_VER           = 0b0000010000000000000000000000000000000000000000000000000000000000, // turn on line center vertical
    GRFE_LINE_DOW           = 0b0000001000000000000000000000000000000000000000000000000000000000, // turn on line angle down
    GRFE_LINE_UP            = 0b0000000100000000000000000000000000000000000000000000000000000000, // turn on line angle up
    GRFE_LIABLEND_LL        = 0b0000000010000000000000000000000000000000000000000000000000000000, // lines vertex alpha blend lower left
    GRFE_LIABLEND_LR        = 0b0000000001000000000000000000000000000000000000000000000000000000, // lines vertex alpha blend lower right
    GRFE_LIABLEND_UR        = 0b0000000000100000000000000000000000000000000000000000000000000000, // lines vertex alpha blend upper right
    GRFE_LIABLEND_UL        = 0b0000000000010000000000000000000000000000000000000000000000000000, // lines vertex alpha blend upper left
    GRFE_LICBLEND_LL        = 0b0000000000001000000000000000000000000000000000000000000000000000, // lines vertex color blend lower left
    GRFE_LICBLEND_LR        = 0b0000000000000100000000000000000000000000000000000000000000000000, // lines vertex color blend lower right
    GRFE_LICBLEND_UR        = 0b0000000000000010000000000000000000000000000000000000000000000000, // lines vertex color blend upper right
    GRFE_LICBLEND_UL        = 0b0000000000000001000000000000000000000000000000000000000000000000, // lines vertex color blend upper left
    GRFE_BGABLEND_LL        = 0b0000000000000000100000000000000000000000000000000000000000000000, // background vertex alpha blend lower left
    GRFE_BGABLEND_LR        = 0b0000000000000000010000000000000000000000000000000000000000000000, // background vertex alpha blend lower right
    GRFE_BGABLEND_UR        = 0b0000000000000000001000000000000000000000000000000000000000000000, // background vertex alpha blend upper right
    GRFE_BGABLEND_UL        = 0b0000000000000000000100000000000000000000000000000000000000000000, // background vertex alpha blend upper left
    GRFE_BGCBLEND_LL        = 0b0000000000000000000010000000000000000000000000000000000000000000, // background vertex color blend lower left
    GRFE_BGCBLEND_LR        = 0b0000000000000000000001000000000000000000000000000000000000000000, // background vertex color blend lower right
    GRFE_BGCBLEND_UR        = 0b0000000000000000000000100000000000000000000000000000000000000000, // background vertex color blend upper right
    GRFE_BGCBLEND_UL        = 0b0000000000000000000000010000000000000000000000000000000000000000, // background vertex color blend upper left
    GRFE_FGABLEND_LL        = 0b0000000000000000000000001000000000000000000000000000000000000000, // foreground vertex alpha blend lower left
    GRFE_FGABLEND_LR        = 0b0000000000000000000000000100000000000000000000000000000000000000, // foreground vertex alpha blend lower right
    GRFE_FGABLEND_UR        = 0b0000000000000000000000000010000000000000000000000000000000000000, // foreground vertex alpha blend upper right
    GRFE_FGABLEND_UL        = 0b0000000000000000000000000001000000000000000000000000000000000000, // foreground vertex alpha blend upper left
    GRFE_FGCBLEND_LL        = 0b0000000000000000000000000000100000000000000000000000000000000000, // foreground vertex color blend lower left
    GRFE_FGCBLEND_LR        = 0b0000000000000000000000000000010000000000000000000000000000000000, // foreground vertex color blend lower right
    GRFE_FGCBLEND_UR        = 0b0000000000000000000000000000001000000000000000000000000000000000, // foreground vertex color blend upper right
    GRFE_FGCBLEND_UL        = 0b0000000000000000000000000000000100000000000000000000000000000000, // foreground vertex color blend upper left
    GRFE_LNBLINK3           = 0b0000000000000000000000000000000010000000000000000000000000000000, // lines blinking speed (0...7) 0 = no blink
    GRFE_LNBLINK2           = 0b0000000000000000000000000000000001000000000000000000000000000000, // lines blinking speed
    GRFE_LNBLINK1           = 0b0000000000000000000000000000000000100000000000000000000000000000, // lines blinking speed
    GRFE_BGBLINK3           = 0b0000000000000000000000000000000000010000000000000000000000000000, // background blinking speed (0...7) 0 = no blink
    GRFE_BGBLINK2           = 0b0000000000000000000000000000000000001000000000000000000000000000, // background blinking speed
    GRFE_BGBLINK1           = 0b0000000000000000000000000000000000000100000000000000000000000000, // background blinking speed
    GRFE_FGBLINK3           = 0b0000000000000000000000000000000000000010000000000000000000000000, // foreground blinking speed (0...7) 0 = no blink
    GRFE_FGBLINK2           = 0b0000000000000000000000000000000000000001000000000000000000000000, // foreground blinking speed
    GRFE_FGBLINK1           = 0b0000000000000000000000000000000000000000100000000000000000000000, // foreground blinking speed
    GRFE_DOUBLEHEIGHT       = 0b0000000000000000000000000000000000000000010000000000000000000000, // double height content
    GRFE_DOUBLEWIDTH        = 0b0000000000000000000000000000000000000000001000000000000000000000, // double width content
    GRFE_LINESSEQ           = 0b0000000000000000000000000000000000000000000100000000000000000000, // turn on lines sequencing
    GRFE_COLORSEQ           = 0b0000000000000000000000000000000000000000000010000000000000000000, // turn on color sequencing
    GRFE_VALUESEQ           = 0b0000000000000000000000000000000000000000000001000000000000000000, // turn on cell value sequencing
    GRFE_AUTOSCRX           = 0b0000000000000000000000000000000000000000000000100000000000000000, // turn on automatic scrolling on x axis
    GRFE_AUTOSCRY           = 0b0000000000000000000000000000000000000000000000010000000000000000, // turn on automatic scrolling on y axis
    GRFE_ROTATION           = 0b0000000000000000000000000000000000000000000000001000000000000000, // turn on rotation 
    GRFE_SKEW               = 0b0000000000000000000000000000000000000000000000000100000000000000, // turn on cell skewing
    GRFE_WRAP_X             = 0b0000000000000000000000000000000000000000000000000010000000000000, // turn on wrap around on x axis
    GRFE_WRAP_Y             = 0b0000000000000000000000000000000000000000000000000001000000000000, // turn on wrap around on y axis
    GRFE_SCALE_X            = 0b0000000000000000000000000000000000000000000000000000100000000000, // turn on cell scaling on x axis
    GRFE_SCALE_Y            = 0b0000000000000000000000000000000000000000000000000000010000000000, // turn on cell scaling on y axis
    GRFE_FLIPH              = 0b0000000000000000000000000000000000000000000000000000001000000000, // flip cell(s) horizontally
    GRFE_FLIPV              = 0b0000000000000000000000000000000000000000000000000000000100000000, // flip cell(s) vertically
    GRFE_RED                = 0b0000000000000000000000000000000000000000000000000000000010000000, // turn on red channel
    GRFE_GREEN              = 0b0000000000000000000000000000000000000000000000000000000001000000, // turn on green channel
    GRFE_BLUE               = 0b0000000000000000000000000000000000000000000000000000000000100000, // turn on blue channel
    GRFE_ALPHA              = 0b0000000000000000000000000000000000000000000000000000000000010000, // turn on transparency
    GRFE_PROTECTED          = 0b0000000000000000000000000000000000000000000000000000000000001000, // protect value from being changed
    GRFE_SHADOW             = 0b0000000000000000000000000000000000000000000000000000000000000100, // turn on shadow cell
    GRFE_BACKGROUND         = 0b0000000000000000000000000000000000000000000000000000000000000010, // turn on cell background (tile rectangle fill)
    GRFE_FOREGROUND         = 0b0000000000000000000000000000000000000000000000000000000000000001, // turn on cell foreground (value) (used for hidden mode)
    GRFE_LINES_MASK         = 0b1111111100000000000000000000000000000000000000000000000000000000, 
    GRFE_BLENDING_MASK      = 0b0000000011111111111111111111111100000000000000000000000000000000, 
    GRFE_LNBLINK_MASK       = 0b0000000000000000000000000000000011100000000000000000000000000000,
    GRFE_BGBLINK_MASK       = 0b0000000000000000000000000000000000011100000000000000000000000000,
    GRFE_FGBLINK_MASK       = 0b0000000000000000000000000000000000000011100000000000000000000000,
    GRFE_DEFAULT1           = 0b0000000000000000000000000000000000000000011100000000000011110101, // DEFAULT STATE :HEAVY PROCESSING
    GRFE_DEFAULT2           = 0b0000000000000000000000000000000000000000000000001100000011110111, // DEFAULT STATE :SCROLLTEXT
    GRFE_DEFAULT3           = 0b0000000000000000000000000000000000000000000000000000000000000000, // DEFAULT STATE :GAME page
    GRFE_DEFAULT4           = 0b0000000000000000000000000000000000000000000000000100000011110101  // DEFAULT STATE :TERMINAL DISPLAY
} grid_features;

#define GRFE_LINES_BITS 56
#define GRFE_LNBLINK_BITS 29
#define GRFE_BGBLINK_BITS 26
#define GRFE_FGBLINK_BITS 23
#define GET_FROM_STATE(state, mask, shift) ((state & mask) >> shift)

Rectangle get_tilezone_from_position(uint16_t asset_id, Vector2 position) {
    EX_tileset *tileset = &sys.asset.tileset[asset_id];
    if ((position.x >= tileset->count.x) || position.x < 0) return (Rectangle) {0.f, 0.f, tileset->tilesize.x, tileset->tilesize.y};
    if ((position.y >= tileset->count.y) || position.y < 0) return (Rectangle) {0.f, 0.f, tileset->tilesize.y, tileset->tilesize.y};
    Vector2 *tilesize = &sys.asset.tileset[asset_id].tilesize;
    return (Rectangle) {position.x * tilesize->x, position.y * tilesize->y,  tilesize->x, tilesize->y};
}

Rectangle get_tilezone_from_code(uint16_t asset_id, uint16_t code) {
    EX_tileset *tileset = &sys.asset.tileset[asset_id];

    code -= sys.asset.tileset[asset_id].ascii_start;
    if (code > sys.asset.tileset[asset_id].total || code < 0) return (Rectangle) {0.f, 0.f, tileset->tilesize.x, tileset->tilesize.y};

    float px = code % (int)tileset->count.x;
    float py = (int)(code / (int)tileset->count.x);
    Vector2 *tilesize = &sys.asset.tileset[asset_id].tilesize;
    return (Rectangle) {px * tilesize->x, py * tilesize->y,  tilesize->x, tilesize->y};
}

//        plot_character(ex_scrolltext[s].font, ch, position, (Vector2) {text_scale}, (Vector2) {2, 4}, ex_scrolltext[s].text_angle, col, ex_scrolltext[s].colorbg, colorln, state);
void plot_character(uint16_t asset_id, uint16_t palette_id, uint16_t code, Vector2 position, Vector2 scale, Vector2 skew, Vector2 shadow, float angle, Color colorfg, Color colorbg, Color colorln, uint64_t state) {
    Color vertex_colors[4];
    if (!(state & GRFE_ROTATION)) angle = 0.f;

    if (state & GRFE_BACKGROUND) {
        if (state & GRFE_RED)   vertex_colors[0].r = colorbg.r; else vertex_colors[0].r = 0;
        if (state & GRFE_GREEN) vertex_colors[0].g = colorbg.g; else vertex_colors[0].g = 0;
        if (state & GRFE_BLUE)  vertex_colors[0].b = colorbg.b; else vertex_colors[0].b = 0;
        if (state & GRFE_ALPHA) vertex_colors[0].a = colorbg.a; else vertex_colors[0].a = 0;
        vertex_colors[1] = vertex_colors[0];
        vertex_colors[2] = vertex_colors[0];
        vertex_colors[3] = vertex_colors[0];
        DrawRectanglePro2(
            (Rectangle) { position.x, position.y, scale.x, scale.y },
            (Vector2) {0,0}, (Vector2) {0,0}, angle, vertex_colors);
    }
    if (state & GRFE_FOREGROUND) {
            if (state & GRFE_SHADOW) {
                vertex_colors[0] = (Color) {0.f, 0.f, 0.f, 48.f};
                vertex_colors[1] = (Color) {0.f, 0.f, 0.f, 48.f};
                vertex_colors[2] = (Color) {0.f, 0.f, 0.f, 48.f};
                vertex_colors[3] = (Color) {0.f, 0.f, 0.f, 48.f};
                DrawTexturePro2(sys.asset.tex[asset_id],
                    get_tilezone_from_code(asset_id, code),
                    (Rectangle) { position.x + shadow.x, position.y + shadow.y, scale.x, scale.y },
                    (Vector2) {0,0}, skew, angle, vertex_colors);
            };
            if (state & GRFE_RED)   vertex_colors[0].r = colorfg.r; else vertex_colors[0].r = 0;
            if (state & GRFE_GREEN) vertex_colors[0].g = colorfg.g; else vertex_colors[0].g = 0;
            if (state & GRFE_BLUE)  vertex_colors[0].b = colorfg.b; else vertex_colors[0].b = 0;
            if (state & GRFE_ALPHA) vertex_colors[0].a = colorfg.a; else vertex_colors[0].a = 0;
            vertex_colors[1] = vertex_colors[0];
            vertex_colors[2] = vertex_colors[0];
            vertex_colors[3] = vertex_colors[0];
            DrawTexturePro2(sys.asset.tex[asset_id],
                get_tilezone_from_code(asset_id, code),
                (Rectangle) { position.x, position.y , scale.x, scale.y },
                (Vector2) {0,0}, skew, angle, vertex_colors);
    }

    uint8_t lines = GET_FROM_STATE(state, GRFE_LINES_MASK, GRFE_LINES_BITS);
    if (lines) {
            if (state & GRFE_RED)   vertex_colors[0].r = colorln.r; else vertex_colors[0].r = 0;
            if (state & GRFE_GREEN) vertex_colors[0].g = colorln.g; else vertex_colors[0].g = 0;
            if (state & GRFE_BLUE)  vertex_colors[0].b = colorln.b; else vertex_colors[0].b = 0;
            if (state & GRFE_ALPHA) vertex_colors[0].a = colorln.a; else vertex_colors[0].a = 0;
            vertex_colors[1] = vertex_colors[0];
            vertex_colors[2] = vertex_colors[0];
            vertex_colors[3] = vertex_colors[0];
            DrawTexturePro2(sys.asset.tex[sys.asset.lines_id],
                get_tilezone_from_code(sys.asset.lines_id, lines),
                (Rectangle) { position.x, position.y , scale.x, scale.y },
                (Vector2) {0,0}, skew, angle, vertex_colors);
    }
}

bool init_cell_linear(EX_cell *cell, uint64_t cell_state, uint32_t color_id, uint32_t colorbg_id) {
    cell->state = cell_state;
    cell->value = 0;
    cell->colorfg_id = color_id;
    cell->colorbg_id = colorbg_id;
    cell->offset = (Vector2) {0,0};
    cell->scale = (Vector2) {1,1};
    cell->angle = 0;

    cell->fg_brightness = 1.f;
    cell->bg_brightness = 1.f;
    return 0;
}


void set_page_default_palette(uint16_t pagegroup_id, uint16_t page_id, uint16_t palette_id) {
    EX_page *page = &sys.video.pagegroup[pagegroup_id].page[page_id];
    page->default_palette_id = palette_id;
}

void set_page_default_asset(uint16_t pagegroup_id, uint16_t page_id, uint16_t asset_id) {
    EX_page *page = &sys.video.pagegroup[pagegroup_id].page[page_id];
    page->default_asset_id = asset_id;
}

uint16_t init_page(uint16_t pagegroup_id, uint16_t page_id, Vector2 size, uint64_t page_state, uint64_t cell_state, uint16_t asset_id, uint16_t palette_id) {
    EX_pagegroup *pagegroup = &sys.video.pagegroup[pagegroup_id];
    EX_page *page = &sys.video.pagegroup[pagegroup_id].page[page_id];
    uint32_t cell_count = (uint16_t)size.x * (uint16_t)size.y;
    page->size = size;
    page->state = page_state;
    set_page_default_palette(pagegroup_id, page_id, palette_id);
    set_page_default_asset(pagegroup_id, page_id, asset_id);
    page->cell_count = cell_count;
    page->cell = calloc(cell_count, sizeof(EX_cell));
    page->offset = (Vector2) {0,0};
    page->scale = (Vector2) {1,1};
    page->angle = 0;
    page->fg_brightness = 1.f;
    page->bg_brightness = 1.f;
    page->alpha = 255;

    EX_cell *cell = &sys.video.pagegroup[pagegroup_id].page[page_id].cell[0];
    for (uint32_t i = 0; i < cell_count; i++) {
        init_cell_linear(&cell[i], cell_state, 0, 0);
    }
    return 1;
}

void set_pagegroup_default_palette(uint16_t pagegroup_id, uint16_t palette_id) {
    EX_pagegroup *pagegroup = &sys.video.pagegroup[pagegroup_id];
    pagegroup->default_palette_id = palette_id;
}

void set_pagegroup_default_asset(uint16_t pagegroup_id, uint16_t asset_id) {
    EX_pagegroup *pagegroup = &sys.video.pagegroup[pagegroup_id];
    pagegroup->default_asset_id = asset_id;
}

uint16_t init_pagegroup(uint32_t pagegroup_id, Vector2 size, uint16_t page_count, uint32_t pagegroup_state, uint64_t page_state, uint64_t cell_state, uint16_t asset_id, uint16_t palette_id) {
    uint16_t pages = 0;
    sys.video.pagegroup[pagegroup_id].state = pagegroup_state;
    sys.video.pagegroup[pagegroup_id].page_count = page_count;
    set_pagegroup_default_palette(pagegroup_id, palette_id);
    set_pagegroup_default_asset(pagegroup_id, asset_id);
    sys.video.pagegroup[pagegroup_id].page = calloc(sys.video.pagegroup[pagegroup_id].page_count, sizeof(EX_page));
    for (uint16_t page_id = 0; page_id < page_count; page_id++) {
        pages += init_page(pagegroup_id, page_id, size, page_state, cell_state, asset_id, palette_id);
    }
    return pages;
}

// *************** REFERENCING SHORTCUTS TO USE *****************
// EX_pagegroup  *pagegroup  = &sys.video.pagegroup[pagegroup_id];
// EX_page *page = &sys.video.pagegroup[pagegroup_id].page[page_id];
// EX_cell  *cell  = &sys.video.pagegroup[pagegroup_id].page[page_id].cell[0]; ( cell[50].state )
// This functionality requires setting a bunch of stuff afterwards;
// - per cell states
// - per page asset
bool init_pagegroup_multipage(Vector2 size, uint32_t pagegroup_state, uint64_t page_state[]) {
    uint16_t pagegroup_id = sys.video.current_virtual; // A single pagegroup per Virtual Display

    sys.video.pagegroup[pagegroup_id].state = pagegroup_state;
    sys.video.pagegroup[pagegroup_id].page_count = sizeof(page_state) / sizeof_member(EX_page, state);

    sys.video.pagegroup[pagegroup_id].page = calloc(sys.video.pagegroup[pagegroup_id].page_count, sizeof(EX_page));
    for (uint16_t i = 0; i < sys.video.pagegroup[pagegroup_id].page_count; i++) {
        init_page(pagegroup_id, i, size, page_state[i], 0, 0, 0);
    }
    return 0;
}

uint16_t unload_page(uint16_t pagegroup_id, uint16_t page_id) {
    EX_page *page = &sys.video.pagegroup[pagegroup_id].page[page_id];
    if (page->cell_count > 0) {
        page->size = (Vector2){0};
        page->state = 0;
        page->cell_count = 0;
        free(page->cell);
        return 1;
    } else {
        return 0; // was an empty page
    }
}

uint16_t unload_pagegroup(uint16_t pagegroup_id) {
    uint16_t pages = 0;
    EX_pagegroup *pagegroup = &sys.video.pagegroup[pagegroup_id];
    for (uint16_t page_id = 0; page_id < (pagegroup->page_count); page_id++) {
        pages += unload_page(pagegroup_id, page_id);
    }
    if (pages) free(sys.video.pagegroup[pagegroup_id].page);
    return pages;
}

uint16_t unload_all_pagegroups() {
    uint16_t pagegroups = 0, pages = 0;
    for (uint16_t pagegroup_id = 0; pagegroup_id < GRID_MAX_PAGEGROUPS; pagegroup_id++) {
        pages += unload_pagegroup(pagegroup_id);
        if (pages) ++pagegroups;
    }
    return pages;
}

void page_set_mouse_position(uint16_t pagegroup_id, uint16_t page_id, Vector2 target) {
    EX_page *page = &sys.video.pagegroup[pagegroup_id].page[page_id];
    uint16_t lsx = page->size.x, lsy = page->size.y;
    if (target.x >= lsx) target.x = lsx - 1; else if (target.x < 0) target.x = 0;
    if (target.y >= lsy) target.y = lsy - 1; else if (target.y < 0) target.y = 0;
    page->mouse.offset = target;
}

void page_set_keyboard_position(uint16_t pagegroup_id, uint16_t page_id, Vector2 target) {
    EX_page *page = &sys.video.pagegroup[pagegroup_id].page[page_id];
    uint16_t lsx = page->size.x, lsy = page->size.y;
    if (target.x >= lsx) target.x = lsx - 1; else if (target.x < 0) target.x = 0;
    if (target.y >= lsy) target.y = lsy - 1; else if (target.y < 0) target.y = 0;
    page->keyboard.offset = target;
}

void set_cell_state(uint16_t pagegroup_id, uint16_t page_id, Rectangle target, uint64_t state) {
    uint16_t linear_offset;
    EX_page *page = &sys.video.pagegroup[pagegroup_id].page[page_id];
    uint16_t lsx = page->size.x, lsy = page->size.y;
    EX_cell  *target_cell  = &sys.video.pagegroup[pagegroup_id].page[page_id].cell[0];

    if (target.x >= lsx || target.y >= lsy || (target.x + target.width) < 0 || (target.y + target.height) < 0) return;
    if ((target.x + target.width) > lsx) target.width = lsx - target.x; 
    if ((target.y + target.height) > lsy) target.height = lsy - target.y;

    for (uint16_t x = target.x; x++; x < (target.x + target.width)) {
        for (uint16_t y = target.y; y++; y < (target.y + target.height)) {
            linear_offset = lsx * y + x;
            BITS_ON(target_cell[linear_offset].state, state);
        }
    }
}

void clear_cell_state(uint16_t pagegroup_id, uint16_t page_id, Rectangle target, uint64_t state) {
    uint16_t linear_offset;
    EX_page *page = &sys.video.pagegroup[pagegroup_id].page[page_id];
    uint16_t lsx = page->size.x, lsy = page->size.y;
    EX_cell  *target_cell  = &sys.video.pagegroup[pagegroup_id].page[page_id].cell[0];

    if (target.x >= lsx || target.y >= lsy || (target.x + target.width) < 0 || (target.y + target.height) < 0) return;
    if ((target.x + target.width) > lsx) target.width = lsx - target.x; 
    if ((target.y + target.height) > lsy) target.height = lsy - target.y;

    for (uint16_t x = target.x; x++; x < (target.x + target.width)) {
        for (uint16_t y = target.y; y++; y < (target.y + target.height)) {
            linear_offset = lsx * y + x;
            BITS_OFF(target_cell[linear_offset].state, state);
        }
    }
}

void set_cell_colorfg(uint16_t pagegroup_id, uint16_t page_id, Rectangle target, uint16_t color_id) {
    uint16_t linear_offset;
    EX_page *page = &sys.video.pagegroup[pagegroup_id].page[page_id];
    uint16_t lsx = page->size.x, lsy = page->size.y;
    EX_cell  *target_cell  = &sys.video.pagegroup[pagegroup_id].page[page_id].cell[0];

    if (target.x >= lsx || target.y >= lsy || (target.x + target.width) < 0 || (target.y + target.height) < 0) return;
    if ((target.x + target.width) > lsx) target.width = lsx - target.x; 
    if ((target.y + target.height) > lsy) target.height = lsy - target.y;

    for (uint16_t x = target.x; x++; x < (target.x + target.width)) {
        for (uint16_t y = target.y; y++; y < (target.y + target.height)) {
            linear_offset = lsx * y + x;
            target_cell[linear_offset].colorfg_id = color_id;
        }
    }
}

void set_cell_colorbg(uint16_t pagegroup_id, uint16_t page_id, Rectangle target, uint16_t color_id) {
    uint16_t linear_offset;
    EX_page *page = &sys.video.pagegroup[pagegroup_id].page[page_id];
    uint16_t lsx = page->size.x, lsy = page->size.y;
    EX_cell  *target_cell  = &sys.video.pagegroup[pagegroup_id].page[page_id].cell[0];

    if (target.x >= lsx || target.y >= lsy || (target.x + target.width) < 0 || (target.y + target.height) < 0) return;
    if ((target.x + target.width) > lsx) target.width = lsx - target.x; 
    if ((target.y + target.height) > lsy) target.height = lsy - target.y;

    for (uint16_t x = target.x; x++; x < (target.x + target.width)) {
        for (uint16_t y = target.y; y++; y < (target.y + target.height)) {
            linear_offset = lsx * y + x;
            target_cell[linear_offset].colorbg_id = color_id;
        }
    }
}

void set_cell_colorln(uint16_t pagegroup_id, uint16_t page_id, Rectangle target, uint16_t color_id) {
    uint16_t linear_offset;
    EX_page *page = &sys.video.pagegroup[pagegroup_id].page[page_id];
    uint16_t lsx = page->size.x, lsy = page->size.y;
    EX_cell  *target_cell  = &sys.video.pagegroup[pagegroup_id].page[page_id].cell[0];

    if (target.x >= lsx || target.y >= lsy || (target.x + target.width) < 0 || (target.y + target.height) < 0) return;
    if ((target.x + target.width) > lsx) target.width = lsx - target.x; 
    if ((target.y + target.height) > lsy) target.height = lsy - target.y;

    for (uint16_t x = target.x; x++; x < (target.x + target.width)) {
        for (uint16_t y = target.y; y++; y < (target.y + target.height)) {
            linear_offset = lsx * y + x;
            target_cell[linear_offset].colorln_id = color_id;
        }
    }
}

void set_cell_color_mask(uint16_t pagegroup_id, uint16_t page_id, Rectangle target, Color color) {
    uint16_t linear_offset;
    EX_page *page = &sys.video.pagegroup[pagegroup_id].page[page_id];
    uint16_t lsx = page->size.x, lsy = page->size.y;
    EX_cell  *target_cell  = &sys.video.pagegroup[pagegroup_id].page[page_id].cell[0];

    if (target.x >= lsx || target.y >= lsy || (target.x + target.width) < 0 || (target.y + target.height) < 0) return;
    if ((target.x + target.width) > lsx) target.width = lsx - target.x; 
    if ((target.y + target.height) > lsy) target.height = lsy - target.y;

    for (uint16_t x = target.x; x++; x < (target.x + target.width)) {
        for (uint16_t y = target.y; y++; y < (target.y + target.height)) {
            linear_offset = lsx * y + x;
            target_cell[linear_offset].color_mask = color;
        }
    }
}

void set_cell_color_shadow_mask(uint16_t pagegroup_id, uint16_t page_id, Rectangle target, Color color) {
    uint16_t linear_offset;
    EX_page *page = &sys.video.pagegroup[pagegroup_id].page[page_id];
    uint16_t lsx = page->size.x, lsy = page->size.y;
    EX_cell  *target_cell  = &sys.video.pagegroup[pagegroup_id].page[page_id].cell[0];

    if (target.x >= lsx || target.y >= lsy || (target.x + target.width) < 0 || (target.y + target.height) < 0) return;
    if ((target.x + target.width) > lsx) target.width = lsx - target.x; 
    if ((target.y + target.height) > lsy) target.height = lsy - target.y;

    for (uint16_t x = target.x; x++; x < (target.x + target.width)) {
        for (uint16_t y = target.y; y++; y < (target.y + target.height)) {
            linear_offset = lsx * y + x;
            target_cell[linear_offset].shadow_mask = color;
        }
    }
}

void set_cell_offset(uint16_t pagegroup_id, uint16_t page_id, Rectangle target, Vector2 offset) {
    uint16_t linear_offset;
    EX_page *page = &sys.video.pagegroup[pagegroup_id].page[page_id];
    uint16_t lsx = page->size.x, lsy = page->size.y;
    EX_cell  *target_cell  = &sys.video.pagegroup[pagegroup_id].page[page_id].cell[0];

    if (target.x >= lsx || target.y >= lsy || (target.x + target.width) < 0 || (target.y + target.height) < 0) return;
    if ((target.x + target.width) > lsx) target.width = lsx - target.x; 
    if ((target.y + target.height) > lsy) target.height = lsy - target.y;

    for (uint16_t x = target.x; x++; x < (target.x + target.width)) {
        for (uint16_t y = target.y; y++; y < (target.y + target.height)) {
            linear_offset = lsx * y + x;
            target_cell[linear_offset].offset = offset;
        }
    }
}

void set_cell_angle(uint16_t pagegroup_id, uint16_t page_id, Rectangle target, float angle) {
    uint16_t linear_offset;
    EX_page *page = &sys.video.pagegroup[pagegroup_id].page[page_id];
    uint16_t lsx = page->size.x, lsy = page->size.y;
    EX_cell  *target_cell  = &sys.video.pagegroup[pagegroup_id].page[page_id].cell[0];

    if (target.x >= lsx || target.y >= lsy || (target.x + target.width) < 0 || (target.y + target.height) < 0) return;
    if ((target.x + target.width) > lsx) target.width = lsx - target.x; 
    if ((target.y + target.height) > lsy) target.height = lsy - target.y;

    for (uint16_t x = target.x; x++; x < (target.x + target.width)) {
        for (uint16_t y = target.y; y++; y < (target.y + target.height)) {
            linear_offset = lsx * y + x;
            target_cell[linear_offset].angle = angle;
        }
    }
}

void set_cell_scale(uint16_t pagegroup_id, uint16_t page_id, Rectangle target, Vector2 scale) {
    uint16_t linear_offset;
    EX_page *page = &sys.video.pagegroup[pagegroup_id].page[page_id];
    uint16_t lsx = page->size.x, lsy = page->size.y;
    EX_cell  *target_cell  = &sys.video.pagegroup[pagegroup_id].page[page_id].cell[0];

    if (target.x >= lsx || target.y >= lsy || (target.x + target.width) < 0 || (target.y + target.height) < 0) return;
    if ((target.x + target.width) > lsx) target.width = lsx - target.x; 
    if ((target.y + target.height) > lsy) target.height = lsy - target.y;

    for (uint16_t x = target.x; x++; x < (target.x + target.width)) {
        for (uint16_t y = target.y; y++; y < (target.y + target.height)) {
            linear_offset = lsx * y + x;
            target_cell[linear_offset].scale = scale;
        }
    }
}

// iterate through charracter ascii codes, if font pixels then copy desired source_cell information to the page
void plot_big_characters(uint16_t pagegroup_id, uint16_t page_id, Vector2 target, uint64_t state, uint16_t font_id, uint8_t *ch) {
    uint32_t linear_offset;
    EX_page *page = &sys.video.pagegroup[pagegroup_id].page[page_id];
    uint16_t lsx = page->size.x, lsy = page->size.y;
    EX_cell  *target_cell  = &sys.video.pagegroup[pagegroup_id].page[page_id].cell[0];

    uint32_t length = sizeof(ch);

    for (uint32_t i= 0; i++; i<length) {
// to complete
    }    
}

typedef enum {
    GFLD_R32                  = 0b10000000000000000000000000000000,
    GFLD_STATE                = 0b01000000000000000000000000000000,   // all flags for cell
    GFLD_VALUE                = 0b00010000000000000000000000000000,   // value of cell
    GFLD_LINES                = 0b00000010000000000000000000000000,   // lines feature
    GFLD_CYCLE                = 0b00000000000010000000000000000000,   // cell animation sequence number
    GFLD_FG_COLOR             = 0b00000000000000100000000000000000,   // palette index color for cell
    GFLD_FG_COLOR_CYCLE       = 0b00000000000000010000000000000000,   // color cycle index
    GFLD_BG_COLOR             = 0b00000000000000001000000000000000,   // palette index color for cell background
    GFLD_BG_COLOR_CYCLE       = 0b00000000000000000100000000000000,   // color cycle index
    GFLD_LINES_COLOR          = 0b00000000000000000010000000000000,   // palette index color for cell background
    GFLD_LINES_COLOR_CYCLE    = 0b00000000000000000001000000000000,   // color cycle index
    GFLD_OFFSET               = 0b00000000000000000000100000000000,   // displacement from top left (x,y)
    GFLD_SKEW                 = 0b00000000000000000000010000000000,   // horizontal and vertical skew
    GFLD_SCALE                = 0b00000000000000000000001000000000,   // (x,y) cell scale
    GFLD_SCALE_SPEED          = 0b00000000000000000000000100000000,   // (x,y) cell scale speed
    GFLD_SCROLL_SPEED         = 0b00000000000000000000000010000000,   // (x,y) cell scroll speed
    GFLD_ANGLE                = 0b00000000000000000000000001000000,   // degree of angle used to rotate the cell
    GFLD_FG_BRIGHTNESS        = 0b00000000000000000000000000100000,   // foreground brightness (values 0...1 divides, values 1 to 255 multiply)
    GFLD_BG_BRIGHTNESS        = 0b00000000000000000000000000010000,   // background brightness (values 0...1 divides, values 1 to 255 multiply)
    GFLD_ALPHA                = 0b00000000010000000000000000000000,   // alpha channel
    GFLD_COLOR_MASK           = 0b00000000000000000000000000001000,   // RGBA color mask of cell
    GFLD_SHADOW_MASK          = 0b00000000000000000000000000000100,   // shadow RGBA mask
    GFLD_ALL                  = 0b11111111111111111111111111111111,   // all fields
    GFLD_NO_STATE_MASK        = 0b00111111111111111111111111111111    // all fields except the state of the cell
} gridfield_features;

// init every cell using a prototype cell and based on a stat system
void init_cell (uint16_t pagegroup_id, uint16_t page_id, Rectangle target, EX_cell info_cell, uint64_t state) {
    uint32_t target_offset, source_offset;
    EX_page *page = &sys.video.pagegroup[pagegroup_id].page[page_id];
    uint16_t lsx = page->size.x, lsy = page->size.y;
    EX_cell  *target_cell  = &sys.video.pagegroup[pagegroup_id].page[page_id].cell[0];

    if (target.x >= lsx || target.y >= lsy || (target.x + target.width) < 0 || (target.y + target.height) < 0) return;

    for (uint16_t x = target.x; x++; x < (target.x + target.width)) {
        if (x >=0 && x < lsx ) {
            for (uint16_t y = target.y; y++; y < (target.y + target.height)) {
                if (y >= 0 && y < lsy) {
                    target_offset = lsx * y + x;
                    if (state & GFLD_ALL)                   target_cell[target_offset]                      = info_cell;
                    else {
                        if (state & GFLD_STATE)             target_cell[target_offset].state                = info_cell.state;
                        if (state & GFLD_VALUE)             target_cell[target_offset].value                = info_cell.value;
                        if (state & GFLD_LINES)             target_cell[target_offset].lines                = info_cell.lines;
                        if (state & GFLD_CYCLE)             target_cell[target_offset].cycle_id             = info_cell.cycle_id;
                        if (state & GFLD_FG_COLOR)          target_cell[target_offset].colorfg_id           = info_cell.colorfg_id;
                        if (state & GFLD_FG_COLOR_CYCLE)    target_cell[target_offset].colorfg_cycle_id     = info_cell.colorfg_cycle_id;
                        if (state & GFLD_BG_COLOR)          target_cell[target_offset].colorbg_id           = info_cell.colorbg_id;
                        if (state & GFLD_BG_COLOR_CYCLE)    target_cell[target_offset].colorbg_cycle_id     = info_cell.colorbg_cycle_id;
                        if (state & GFLD_LINES_COLOR)       target_cell[target_offset].colorln_id           = info_cell.colorln_id;
                        if (state & GFLD_LINES_COLOR_CYCLE) target_cell[target_offset].colorln_cycle_id     = info_cell.colorln_cycle_id;
                        if (state & GFLD_OFFSET)            target_cell[target_offset].offset               = info_cell.offset;
                        if (state & GFLD_SKEW)              target_cell[target_offset].skew                 = info_cell.skew;
                        if (state & GFLD_SCALE)             target_cell[target_offset].scale                = info_cell.scale;
                        if (state & GFLD_SCALE_SPEED)       target_cell[target_offset].scale_speed          = info_cell.scale_speed;
                        if (state & GFLD_SCROLL_SPEED)      target_cell[target_offset].scroll_speed         = info_cell.scroll_speed;
                        if (state & GFLD_ANGLE)             target_cell[target_offset].angle                = info_cell.angle;
                        if (state & GFLD_FG_BRIGHTNESS)     target_cell[target_offset].fg_brightness        = info_cell.fg_brightness;
                        if (state & GFLD_BG_BRIGHTNESS)     target_cell[target_offset].bg_brightness        = info_cell.bg_brightness;
                        if (state & GFLD_ALPHA)             target_cell[target_offset].alpha                = info_cell.alpha;
                        if (state & GFLD_COLOR_MASK)        target_cell[target_offset].color_mask           = info_cell.color_mask;
                        if (state & GFLD_SHADOW_MASK)       target_cell[target_offset].shadow_mask          = info_cell.shadow_mask;
                    }
                }
            }
        }
    }
}

void clear_cell (uint16_t pagegroup_id, uint16_t page_id, Rectangle target, uint64_t state) {
    static inline EX_cell blank_cell;
    init_cell(pagegroup_id, page_id, target, blank_cell, state);
}

void shift_cell_field_rectangle(uint16_t pagegroup_id, uint16_t page_id, Rectangle target, float shift, uint64_t state) {
    uint16_t target_offset;
    EX_page *page = &sys.video.pagegroup[pagegroup_id].page[page_id];
    uint16_t lsx = page->size.x, lsy = page->size.y;
    EX_cell  *target_cell  = &sys.video.pagegroup[pagegroup_id].page[page_id].cell[0];

    if (target.x >= lsx || target.y >= lsy || (target.x + target.width) < 0 || (target.y + target.height) < 0) return;
    if ((target.x + target.width) > lsx) target.width = lsx - target.x; 
    if ((target.y + target.height) > lsy) target.height = lsy - target.y;

    for (uint16_t x = target.x; x++; x < (target.x + target.width)) {
        for (uint16_t y = target.y; y++; y < (target.y + target.height)) {
            target_offset = lsx * y + x;
                        if (state & GFLD_STATE)             {target_cell[target_offset].state               += shift;} // 0xffffffff
                        if (state & GFLD_VALUE)             {target_cell[target_offset].value               += shift;} // determined by texture # tiles
                        if (state & GFLD_LINES)             {target_cell[target_offset].lines               += shift;} // 0...255
                        if (state & GFLD_CYCLE)             {target_cell[target_offset].cycle_id            += shift;} // determined by texture # tiles
                        if (state & GFLD_FG_COLOR)          {target_cell[target_offset].colorfg_id          += shift;} // 0...255 (or palette size)
                        if (state & GFLD_FG_COLOR_CYCLE)    {target_cell[target_offset].colorfg_cycle_id    += shift;} // 0...255 (or palette size)
                        if (state & GFLD_BG_COLOR)          {target_cell[target_offset].colorbg_id          += shift;} // 0...255 (or palette size)
                        if (state & GFLD_BG_COLOR_CYCLE)    {target_cell[target_offset].colorbg_cycle_id    += shift;} // 0...255 (or palette size)
                        if (state & GFLD_LINES_COLOR)       {target_cell[target_offset].colorln_id          += shift;} // 0...255 (or palette size)
                        if (state & GFLD_LINES_COLOR_CYCLE) {target_cell[target_offset].colorln_cycle_id    += shift;} // 0...255 (or palette size)
                        //if (state & GFLD_OFFSET)            {target_cell[target_offset].offset                += shift;} // Vector2 x,y
                        //if (state & GFLD_SKEW)              {target_cell[target_offset].skew                  += shift;} // Vector2 x,y
                        //if (state & GFLD_SCALE)             {target_cell[target_offset].scale                 += shift;} // Vector2 x,y
                        //if (state & GFLD_SCALE_SPEED)       {target_cell[target_offset].scale_speed           += shift;} // 
                        //if (state & GFLD_SCROLL_SPEED)      {target_cell[target_offset].scroll_speed          += shift;} // 
                        if (state & GFLD_ANGLE)             {target_cell[target_offset].angle               += shift;} // 0...360
                        if (state & GFLD_FG_BRIGHTNESS)     {target_cell[target_offset].fg_brightness       += shift;} // 0...255
                        if (state & GFLD_BG_BRIGHTNESS)     {target_cell[target_offset].bg_brightness       += shift;} // 0...255
                        //if (state & GFLD_COLOR_MASK)        {target_cell[target_offset].color_mask            += shift;} // Color
                        //if (state & GFLD_SHADOW_MASK)       {target_cell[target_offset].shadow_mask           += shift;} // Color
        }
    }
}

void shift_cell_field_circle(uint16_t pagegroup_id, uint16_t page_id, Rectangle target, float shift, uint64_t state) {
    uint32_t linear_offset;
    EX_page *page = &sys.video.pagegroup[pagegroup_id].page[page_id];
    uint16_t lsx = page->size.x, lsy = page->size.y;
    EX_cell  *target_cell  = &sys.video.pagegroup[pagegroup_id].page[page_id].cell[0];

    if (target.x >= lsx || target.y >= lsy || (target.x + target.width) < 0 || (target.y + target.height) < 0) return;
    if ((target.x + target.width) > lsx) target.width = lsx - target.x; 
    if ((target.y + target.height) > lsy) target.height = lsy - target.y;

    for (int16_t x = target.x; x++; x < (target.x + target.width)) {
        for (int16_t y = target.y; y++; y < (target.y + target.height)) {
            // determine if circle border or full and if inside then modify
            // The same logic as rectangle
            linear_offset = lsx * y + x;
            target_cell[linear_offset].value += shift;
        }
    }
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
} cell_direction;

void copy_cell_in_page(uint16_t pagegroup_id, uint16_t page_id, Rectangle source, Vector2 target, uint64_t state) {
    uint32_t source_offset, target_offset;
    EX_page *page = &sys.video.pagegroup[pagegroup_id].page[page_id];
    uint16_t lsx = page->size.x, lsy = page->size.y;
    EX_cell  *cell  = &sys.video.pagegroup[pagegroup_id].page[page_id].cell[0];
    
    if (source.x >= lsx || source.y >= lsy || target.x >= lsx || target.y >= lsy) return;
    if ((source.x + source.width) < 0 || (source.y + source.height) < 0 || (target.x + source.width) < 0 || (target.y + source.height) < 0) return;
    if ((source.x + source.width) > lsx) source.width = lsx - source.x;
    if ((source.y + source.width) > lsy) source.width = lsy - source.y;
    int16_t tx = target.x - source.x; // horizontal target displacement (can be positive or negative depending if target is left or right of source)
    int16_t ty = target.y - source.y; // vertical target displacement (can be positive or negative depending if target is above or below of source)
    int16_t xa, xb, xi, ya, yb, yi;
    if (tx <= 0) {xa = source.x; xb = (source.x + source.width); xi = 1;} else {xa = (source.x + source.width); xb = source.x; xi = -1;} // horizontal scanning parameters
    if (ty <= 0) {ya = source.y; yb = (source.y + source.height); yi = 1;} else {ya = (source.y + source.height); yb = source.y; yi = -1;} // vertical scanning parameters
    int16_t y = ya;
    while (1) {
        if (y >=0 && (y + ty) < lsy && (y + ty) >= 0) {
            int16_t x = xa;
            while (1) {
                if (x >= 0 && ((x + tx) < lsx) && (x + tx) >= 0) {
                    source_offset = lsx * y + x;
                    target_offset = lsx * (y + ty) + (x + tx);
                    if (state & GFLD_ALL)                   cell[target_offset]                       = cell[source_offset];
                    else {
                        if (state & GFLD_STATE)             cell[target_offset].state               = cell[source_offset].state;
                        if (state & GFLD_VALUE)             cell[target_offset].value               = cell[source_offset].value;
                        if (state & GFLD_LINES)             cell[target_offset].lines               = cell[source_offset].lines;
                        if (state & GFLD_CYCLE)             cell[target_offset].cycle_id            = cell[source_offset].cycle_id;
                        if (state & GFLD_FG_COLOR)          cell[target_offset].colorfg_id          = cell[source_offset].colorfg_id;
                        if (state & GFLD_FG_COLOR_CYCLE)    cell[target_offset].colorfg_cycle_id    = cell[source_offset].colorfg_cycle_id;
                        if (state & GFLD_BG_COLOR)          cell[target_offset].colorbg_id          = cell[source_offset].colorbg_id;
                        if (state & GFLD_BG_COLOR_CYCLE)    cell[target_offset].colorbg_cycle_id    = cell[source_offset].colorbg_cycle_id;
                        if (state & GFLD_LINES_COLOR)       cell[target_offset].colorln_id          = cell[source_offset].colorln_id;
                        if (state & GFLD_LINES_COLOR_CYCLE) cell[target_offset].colorln_cycle_id    = cell[source_offset].colorln_cycle_id;
                        if (state & GFLD_OFFSET)            cell[target_offset].offset              = cell[source_offset].offset;
                        if (state & GFLD_SKEW)              cell[target_offset].skew                = cell[source_offset].skew;
                        if (state & GFLD_SCALE)             cell[target_offset].scale               = cell[source_offset].scale;
                        if (state & GFLD_SCALE_SPEED)       cell[target_offset].scale_speed         = cell[source_offset].scale_speed;
                        if (state & GFLD_SCROLL_SPEED)      cell[target_offset].scroll_speed        = cell[source_offset].scroll_speed;
                        if (state & GFLD_ANGLE)             cell[target_offset].angle               = cell[source_offset].angle;
                        if (state & GFLD_FG_BRIGHTNESS)     cell[target_offset].fg_brightness       = cell[source_offset].fg_brightness;
                        if (state & GFLD_BG_BRIGHTNESS)     cell[target_offset].bg_brightness       = cell[source_offset].bg_brightness;
                        if (state & GFLD_COLOR_MASK)        cell[target_offset].color_mask          = cell[source_offset].color_mask;
                        if (state & GFLD_SHADOW_MASK)       cell[target_offset].shadow_mask         = cell[source_offset].shadow_mask;
                    }
                }
                x += xi; if (xi == 1) {if (x >= xb) break;} else if (x < xb) break;
            }
        }
        y += yi; if (yi == 1) {if (y >= yb) break;} else if (y < yb) break;
    }
}

// Move cell content to any of 8 directions
void shift_cell (uint16_t pagegroup_id, uint16_t page_id, Rectangle source, uint8_t shift_method, bool cycle, uint64_t state) {
    uint32_t source_offset, target_offset;
    EX_page *page = &sys.video.pagegroup[pagegroup_id].page[page_id];
    uint16_t lsx = page->size.x, lsy = page->size.y;
    EX_cell  *cell  = &sys.video.pagegroup[pagegroup_id].page[page_id].cell[0];

    //if (source.x >= lsx || source.y >= lsy || target.x >= lsx || target.y >= lsy) return;
    //if ((source.x + source.width) < 0 || (source.y + source.height) < 0 || (target.x + source.width) < 0 || (target.y + source.height) < 0) return;
    if ((source.x + source.width) > lsx) source.width = lsx - source.x;
    if ((source.y + source.width) > lsy) source.width = lsy - source.y;

}

void copy_cell_to_page(uint16_t source_pagegroup_id, uint16_t source_page_id, Rectangle source, uint16_t target_pagegroup_id, uint16_t target_page_id, Vector2 target, uint64_t state) {
    uint32_t source_offset, target_offset;

    EX_page *source_page = &sys.video.pagegroup[source_pagegroup_id].page[source_page_id];
    uint16_t lsx = source_page->size.x, lsy = source_page->size.y;
    EX_cell  *source_cell  = &sys.video.pagegroup[source_pagegroup_id].page[source_page_id].cell[0];

    EX_page *target_page = &sys.video.pagegroup[target_pagegroup_id].page[target_page_id];
    uint16_t ltx = target_page->size.x, lty = target_page->size.y;
    EX_cell  *target_cell  = &sys.video.pagegroup[target_pagegroup_id].page[target_page_id].cell[0];

    if (source.x >= lsx || source.y >= lsy || target.x >= ltx || target.y >= lty) return;
    if ((source.x + source.width) < 0 || (source.y + source.height) < 0 || (target.x + source.width) < 0 || (target.x + source.height) < 0) return;

    if ((source.x + source.width) > lsx) source.width = lsx - source.x;
    if ((source.y + source.width) > lsy) source.width = lsy - source.y;
    int16_t tx = target.x - source.x; // horizontal target displacement (can be positive or negative depending if target is left or right of source)
    int16_t ty = target.y - source.y; // vertical target displacement (can be positive or negative depending if target is above or below of source)
    for (int16_t x = source.x; x++; x < (source.x + source.width)) {
        if ( (x + tx) < lsx && (x + tx) < ltx && (x + tx) >= 0 ) {
            for (int16_t y = source.y; y++; y < (source.y + source.height)) {
                if ( (y + ty) < lsy && (y + ty) < lty && (y + ty) >= 0 ) {
                    source_offset = lsx * y + x;
                    target_offset = ltx * (y + ty) + (x + tx);

//    if (!(state & GRFE_PROTECTED))   // if not protected destination field, then you can write

                    if (state & GFLD_ALL)                   target_cell[target_offset]                      = source_cell[source_offset];
                    else {
                        if (state & GFLD_STATE)             target_cell[target_offset].state                = source_cell[source_offset].state;
                        if (state & GFLD_VALUE)             target_cell[target_offset].value                = source_cell[source_offset].value;
                        if (state & GFLD_LINES)             target_cell[target_offset].lines                = source_cell[source_offset].lines;
                        if (state & GFLD_CYCLE)             target_cell[target_offset].cycle_id             = source_cell[source_offset].cycle_id;
                        if (state & GFLD_FG_COLOR)          target_cell[target_offset].colorfg_id           = source_cell[source_offset].colorfg_id;
                        if (state & GFLD_FG_COLOR_CYCLE)    target_cell[target_offset].colorfg_cycle_id     = source_cell[source_offset].colorfg_cycle_id;
                        if (state & GFLD_BG_COLOR)          target_cell[target_offset].colorbg_id           = source_cell[source_offset].colorbg_id;
                        if (state & GFLD_BG_COLOR_CYCLE)    target_cell[target_offset].colorbg_cycle_id     = source_cell[source_offset].colorbg_cycle_id;
                        if (state & GFLD_LINES_COLOR)       target_cell[target_offset].colorln_id           = source_cell[source_offset].colorln_id;
                        if (state & GFLD_LINES_COLOR_CYCLE) target_cell[target_offset].colorln_cycle_id     = source_cell[source_offset].colorln_cycle_id;
                        if (state & GFLD_OFFSET)            target_cell[target_offset].offset               = source_cell[source_offset].offset;
                        if (state & GFLD_SKEW)              target_cell[target_offset].skew                 = source_cell[source_offset].skew;
                        if (state & GFLD_SCALE)             target_cell[target_offset].scale                = source_cell[source_offset].scale;
                        if (state & GFLD_SCALE_SPEED)       target_cell[target_offset].scale_speed          = source_cell[source_offset].scale_speed;
                        if (state & GFLD_SCROLL_SPEED)      target_cell[target_offset].scroll_speed         = source_cell[source_offset].scroll_speed;
                        if (state & GFLD_ANGLE)             target_cell[target_offset].angle                = source_cell[source_offset].angle;
                        if (state & GFLD_FG_BRIGHTNESS)     target_cell[target_offset].fg_brightness        = source_cell[source_offset].fg_brightness;
                        if (state & GFLD_BG_BRIGHTNESS)     target_cell[target_offset].bg_brightness        = source_cell[source_offset].bg_brightness;
                        if (state & GFLD_COLOR_MASK)        target_cell[target_offset].color_mask           = source_cell[source_offset].color_mask;
                        if (state & GFLD_SHADOW_MASK)       target_cell[target_offset].shadow_mask          = source_cell[source_offset].shadow_mask;
                    }
                }
            }
        }
    }
}

void render_page(uint16_t page_id) {
    Color vertex_colors[4];
    uint16_t pagegroup_id = sys.video.current_virtual; // A single pagegroup per Virtual Display

    EX_page *page = &sys.video.pagegroup[pagegroup_id].page[page_id];
    EX_cell  *cell  = &sys.video.pagegroup[pagegroup_id].page[page_id].cell[0];
    uint32_t cell_offset;
    Vector2 shadow = page->shadow;
    uint16_t lsx = page->size.x, lsy = page->size.y;
    for (uint16_t x = 0; x < lsx; x++) {
        for (uint16_t y = 0; y < lsy; y++) {
            cell_offset = lsx * y + x;
            EX_cell *c = &cell[cell_offset];
            uint64_t state = c->state;
            uint16_t palette_id = c->palette_id;
            if (!palette_id) palette_id = page->default_palette_id;
            // for now only page alpha supported, per cell alpha will force to use float to combine page and cell alpha (potentially), or set the texture alpha as the page alpha
            Color colorfg = get_palette_color_pro(palette_id, c->colorfg_id, page->alpha, c->fg_brightness * page->fg_brightness);
            Color colorbg = get_palette_color_pro(palette_id, c->colorbg_id, page->alpha, c->bg_brightness * page->bg_brightness);
            Color colorln = get_palette_color(palette_id, c->colorln_id);
            Vector2 offset = c->offset;
            Vector2 scale = c->scale;
            Vector2 skew = c->skew;
            float angle = c->angle;
            if (!(state & GRFE_ROTATION)) angle = 0.f;
            
            // we have the cell data we can use it to draw our background, foreground and shadow
            // calculate position x,y
            // ascii code is in c.value
            // reading color from palette get_palette_color(palette,id);
            // background set color of corner to color of next tile 
            //    GRFE_BGBLEND_LL       // background vertex color blend lower left
            //    GRFE_BGBLEND_LR       // background vertex color blend lower right
            //    GRFE_BGBLEND_UR       // background vertex color blend upper right
            //    GRFE_BGBLEND_UL       // background vertex color blend upper left
            // foreground set color of corner to color of next tile 
            //    GRFE_FGBLEND_LL       // foreground vertex color blend lower left
            //    GRFE_FGBLEND_LR       // foreground vertex color blend lower right
            //    GRFE_FGBLEND_UR       // foreground vertex color blend upper right
            //    GRFE_FGBLEND_UL       // foreground vertex color blend upper left
/*  All STATES (exhaustive logic) and LINES (just a DrawTexture) to consider
    // This is a different beast and not sure yet how to handle sequences
    GRFE_LINESSEQ            // turn on lines sequencing
    GRFE_COLORSEQ            // turn on color sequencing
    GRFE_VALUESEQ            // turn on cell value sequencing
    // This is a different beast and not sure yet how to handle scrolling of tiles
    GRFE_AUTOSCRX            // turn on automatic scrolling on x axis
    GRFE_AUTOSCRY            // turn on automatic scrolling on y axis
    if (state & GRFE_ROTATION) // then allow using the rotation value else use 0 
    if (state & GRFE_SKEW)   // then allow using the skew value else use 0
    if (state & GRFE_CELLDIS)  // then allow corner displacements
    GRFE_SCALE_X             // turn on cell scaling on x axis
    GRFE_SCALE_Y             // turn on cell scaling on y axis
    GRFE_WRAP_X              // turn on wrap around on x axis
    GRFE_WRAP_Y              // turn on wrap around on y axis
    GRFE_FLIPH               // flip cell(s) horizontally
    GRFE_FLIPV               // flip cell(s) vertically
    // a simple & of each Color value with the flag @ true
    GRFE_RED                 // turn on red channel
    GRFE_GREEN               // turn on green channel
    GRFE_BLUE                // turn on blue channel
    GRFE_ALPHA               // turn on transparency

    DrawTexturePro2(
    );
*/
            // to elaborate color blending between tiles... (will involve snooping all 4 directions for color depend on blending options)

            // establish scaling on screen....  For a 512x224 display = 64x28 tiles of 8 x 8 pixels, for that we need a ratio for x and y
            Vector2 ratio  = {8, 8};
            Vector2 cellpos = {page->offset.x + offset.x + x * ratio.x, page->offset.y + offset.y + y * ratio.y};
            if (state & GRFE_BACKGROUND) {
                if (state & GRFE_RED)   vertex_colors[0].r = colorbg.r; else vertex_colors[0].r = 0;
                if (state & GRFE_GREEN) vertex_colors[0].g = colorbg.g; else vertex_colors[0].g = 0;
                if (state & GRFE_BLUE)  vertex_colors[0].b = colorbg.b; else vertex_colors[0].b = 0;
                if (state & GRFE_ALPHA) vertex_colors[0].a = colorbg.a; else vertex_colors[0].a = 0;
                vertex_colors[1] = vertex_colors[0];
                vertex_colors[2] = vertex_colors[0];
                vertex_colors[3] = vertex_colors[0];
                DrawRectanglePro2(
                    (Rectangle) { cellpos.x, cellpos.y, scale.x, scale.y },
                    (Vector2) {0,0}, (Vector2) {0,0}, angle, vertex_colors);
            }
            uint16_t asset_id = c->asset_id;
            if (!asset_id) asset_id = page->default_asset_id;
            if (state & GRFE_FOREGROUND) {
                uint16_t value = c->value;
                if (state & GRFE_SHADOW) {
                    vertex_colors[0] = (Color) {0.f, 0.f, 0.f, 48.f};
                    vertex_colors[1] = (Color) {0.f, 0.f, 0.f, 48.f};
                    vertex_colors[2] = (Color) {0.f, 0.f, 0.f, 48.f};
                    vertex_colors[3] = (Color) {0.f, 0.f, 0.f, 48.f};
                    DrawTexturePro2(sys.asset.tex[asset_id],
                        get_tilezone_from_code(asset_id, value),
                        (Rectangle) { cellpos.x + shadow.x, cellpos.y + shadow.y, scale.x, scale.y },
                        (Vector2) {0,0}, skew, angle, vertex_colors);
                };
                if (state & GRFE_RED)   vertex_colors[0].r = colorfg.r; else vertex_colors[0].r = 0;
                if (state & GRFE_GREEN) vertex_colors[0].g = colorfg.g; else vertex_colors[0].g = 0;
                if (state & GRFE_BLUE)  vertex_colors[0].b = colorfg.b; else vertex_colors[0].b = 0;
                if (state & GRFE_ALPHA) vertex_colors[0].a = colorfg.a; else vertex_colors[0].a = 0;
                vertex_colors[1] = vertex_colors[0];
                vertex_colors[2] = vertex_colors[0];
                vertex_colors[3] = vertex_colors[0];
                DrawTexturePro2(sys.asset.tex[asset_id],
                    get_tilezone_from_code(asset_id, value),
                    (Rectangle) { cellpos.x, cellpos.y , scale.x, scale.y },
                    (Vector2) {0,0}, skew, angle, vertex_colors);
            }

            uint8_t lines = GET_FROM_STATE(state, GRFE_LINES_MASK, GRFE_LINES_BITS);
            if (lines) {
                if (state & GRFE_RED)   vertex_colors[0].r = colorln.r; else vertex_colors[0].r = 0;
                if (state & GRFE_GREEN) vertex_colors[0].g = colorln.g; else vertex_colors[0].g = 0;
                if (state & GRFE_BLUE)  vertex_colors[0].b = colorln.b; else vertex_colors[0].b = 0;
                if (state & GRFE_ALPHA) vertex_colors[0].a = colorln.a; else vertex_colors[0].a = 0;
                vertex_colors[1] = vertex_colors[0];
                vertex_colors[2] = vertex_colors[0];
                vertex_colors[3] = vertex_colors[0];
                DrawTexturePro2(sys.asset.tex[sys.asset.lines_id],
                    get_tilezone_from_code(sys.asset.lines_id, lines),
                    (Rectangle) { cellpos.x, cellpos.y , scale.x, scale.y },
                    (Vector2) {0,0}, skew, angle, vertex_colors);
            }
        }
    }
//logic to show mouse cursor
//IsCursorOnScreen(void)
//RLAPI Vector2 GetMousePosition(void);                         // Get mouse position XY
}

void render_pagegroup() {
    uint16_t pagegroup_id = sys.video.current_virtual; // A single pagegroup per Virtual Display
    EX_pagegroup  *pagegroup  = &sys.video.pagegroup[pagegroup_id];

//begin draw necessary here

    for (uint16_t i = 0; i < sys.video.pagegroup[pagegroup_id].page_count; i++) {
        render_page(i);
    }
    return 0;
// end draw here
}

// does the execution of the modifiers
void process_page(int page_id) {
}

void process_pagegroup(int pagegroup_id) {
    uint16_t page_id = 0;
    process_page(page_id);
    render_page(page_id);
}

void load_page() {
}

void save_page() {
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
    ASSET_TYPE_MASK     = 0b11111111111111110000000000000000, // All asset type definitions
    ASSET_STATUS_MASK   = 0b00000000000000001111111111111111, 
    ASSET_NULL          = 0b00000000000000000000000000000000  
} asset_state;

uint32_t asset_type(uint32_t state) {
    return (state & ASSET_TYPE_MASK);
}

void update_assets(void) {
    for (uint16_t id = 0; id < sys.asset.total_assets; id++) {
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

int load_asset (uint32_t assettype, const char* fileName, const char* fileType, const uint8_t* fileData, uint32_t dataSize, uint32_t pak) {
    uint16_t id = sys.asset.total_assets;
    debug_console_out("int load_asset", id);

    BITS_INIT(sys.asset.state[id], ASSET_INITIALIZED | assettype);

    if (fileName > NULL) strcpy(sys.asset.name, fileName);

    uint32_t dataSize_decompressed = 0;
    uint8_t *fileData_decompressed;
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


int load_palette(Vector2 count, const char* fileName, const char* fileType, const uint8_t* fileData, uint32_t dataSize, uint32_t pak) {
    uint16_t asset_id = load_asset(ASSET_PALETTE, fileName, fileType, fileData, dataSize, pak);
    float width = (float)sys.asset.img[asset_id].width;
    float height = (float)sys.asset.img[asset_id].height;

    sys.asset.tileset[asset_id].ascii_start = 0;
    sys.asset.tileset[asset_id].tilesize.x = width / count.x;
    sys.asset.tileset[asset_id].tilesize.y = height / count.y;
    sys.asset.tileset[asset_id].count.x = count.x;
    sys.asset.tileset[asset_id].count.y = count.y;
    sys.asset.tileset[asset_id].total = count.x * count.y;

    //debug_console_out(sprintf("load_palette ---- %s WIDTH=%f, HEIGHT=%f, COUNT (%f, %f), SIZE (%f, %f)", fileName, width, height, count.x, count.y, sys.asset.tileset[asset_id].tilesize.x, sys.asset.tileset[asset_id].tilesize.y), asset_id);
    return asset_id;
}


int load_tileset(Vector2 count, const char* fileName, const char* fileType, const uint8_t* fileData, uint32_t dataSize, uint32_t pak, uint16_t ascii_start) {

    uint16_t asset_id = load_asset(ASSET_TILESET, fileName, fileType, fileData, dataSize, pak);
    float width = (float)sys.asset.img[asset_id].width;
    float height = (float)sys.asset.img[asset_id].height;

    sys.asset.tileset[asset_id].ascii_start = ascii_start;
    sys.asset.tileset[asset_id].tilesize.x = width / count.x;
    sys.asset.tileset[asset_id].tilesize.y = height / count.y;
    sys.asset.tileset[asset_id].count.x = count.x;
    sys.asset.tileset[asset_id].count.y = count.y;
    sys.asset.tileset[asset_id].total = count.x * count.y;

    //debug_console_out(sprintf("load_tileset ---- %s WIDTH=%f, HEIGHT=%f, COUNT (%f, %f), SIZE (%f, %f)", fileName, width, height, count.x, count.y, sys.asset.tileset[asset_id].tilesize.x, sys.asset.tileset[asset_id].tilesize.y), asset_id);
    return asset_id;
}

static int16_t unload_asset(uint32_t id) {
    int16_t status = 0;
    if (BITS_TEST(sys.asset.state[id], ASSET_ACTIVE)) {
        sys.asset.state[id] |= ASSET_EXPIRED;
        uint32_t assettype = asset_type(sys.asset.asset_type[id]);
        switch (assettype) {
            case ASSET_ICON :
            UnloadImage(sys.asset.img[id]);
            sys.asset.asset_type[id] = NULL;
            BITS_OFF(sys.asset.state[id], ASSET_LOADED | assettype);
            BITS_ON(sys.asset.state[id], ASSET_UNLOADED);
            ++status; break;

            case ASSET_PALETTE :
            UnloadImage(sys.asset.img[id]);
            UnloadImagePalette(sys.asset.palette[id]);
            UnloadTexture(sys.asset.tex[id]);
            sys.asset.asset_type[id] = NULL;
            BITS_OFF(sys.asset.state[id], ASSET_LOADED | assettype);
            BITS_ON(sys.asset.state[id], ASSET_UNLOADED);
            ++status; break;

            case ASSET_TEXTURE :
            UnloadImage(sys.asset.img[id]);
            UnloadTexture(sys.asset.tex[id]);
            sys.asset.asset_type[id] = NULL;
            BITS_OFF(sys.asset.state[id], ASSET_LOADED | assettype);
            BITS_ON(sys.asset.state[id], ASSET_UNLOADED);
            ++status; break;

            case ASSET_FONT :
            UnloadImage(sys.asset.img[id]);
            UnloadTexture(sys.asset.font[id].texture);
            sys.asset.asset_type[id] = NULL;
            BITS_OFF(sys.asset.state[id], ASSET_LOADED | assettype);
            BITS_ON(sys.asset.state[id], ASSET_UNLOADED);
            ++status; break;

            case ASSET_TILESET :
            UnloadImage(sys.asset.img[id]);
            UnloadTexture(sys.asset.tileset[id].tex);
            sys.asset.asset_type[id] = NULL;
            BITS_OFF(sys.asset.state[id], ASSET_LOADED | assettype);
            BITS_ON(sys.asset.state[id], ASSET_UNLOADED);
            ++status; break;

            case ASSET_FRAMEBUFFER :
            UnloadRenderTexture(sys.asset.framebuffer[id]);
            sys.asset.asset_type[id] = NULL;
            BITS_OFF(sys.asset.state[id], ASSET_LOADED | assettype);
            BITS_ON(sys.asset.state[id], ASSET_UNLOADED);
            ++status; break;

            case ASSET_SHADER :
            UnloadShader(sys.asset.shader[id]);
            sys.asset.asset_type[id] = NULL;
            BITS_OFF(sys.asset.state[id], ASSET_LOADED | assettype);
            BITS_ON(sys.asset.state[id], ASSET_UNLOADED);
            ++status; break;

            case ASSET_XM :
            StopMusicStream(sys.asset.music[id]); // in case it is still playing
            UnloadMusicStream(sys.asset.music[id]);
            sys.asset.asset_type[id] = NULL;
            BITS_OFF(sys.asset.state[id], ASSET_LOADED | assettype);
            BITS_ON(sys.asset.state[id], ASSET_UNLOADED);
            ++status; break;

            case ASSET_WAV : // incomplete*********************************** get raylib functionality
            sys.asset.asset_type[id] = NULL;
            BITS_OFF(sys.asset.state[id], ASSET_LOADED | assettype);
            BITS_ON(sys.asset.state[id], ASSET_UNLOADED);
            ++status; break;

            case ASSET_MP3 : // incomplete*********************************** get raylib functionality
            sys.asset.asset_type[id] = NULL;
            BITS_OFF(sys.asset.state[id], ASSET_LOADED | assettype);
            BITS_ON(sys.asset.state[id], ASSET_UNLOADED);
            ++status; break;

            case ASSET_AUDIOSTREAM :
            sys.asset.asset_type[id] = NULL;
            BITS_OFF(sys.asset.state[id], ASSET_LOADED | assettype);
            BITS_ON(sys.asset.state[id], ASSET_UNLOADED);
            ++status; break;

            case ASSET_TEXT :
            sys.asset.asset_type[id] = NULL;
            BITS_OFF(sys.asset.state[id], ASSET_LOADED | assettype);
            BITS_ON(sys.asset.state[id], ASSET_UNLOADED);
            ++status; break;

            case ASSET_DATA :
            sys.asset.asset_type[id] = NULL;
            BITS_OFF(sys.asset.state[id], ASSET_LOADED | assettype);
            BITS_ON(sys.asset.state[id], ASSET_UNLOADED);
            ++status; break;

            default :
            BITS_ON(sys.asset.state[id], ASSET_ISSUE); // unknown asset, trigger issue
        };
        sys.asset.total_assets -= 1;
    };
    return status;
}

uint16_t unload_all_assets(void) {
    uint16_t count = 0;
    for(uint16_t asset = 0; asset < MAXASSETS; asset++) {
        count += unload_asset(asset);
    };
    return count;
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
    bool status = 0;
    InitAudioDevice();
    sys.audio.total_tracks = 0;
    sys.audio.global_volume = 1.0f;
    SetMasterVolume(sys.audio.global_volume); 
    for (uint16_t id=0; id < MAXAUDIOTRACKS; id++) {
        sys.audio.track[id].is_playing = false;
        sys.audio.track[id].volume = 1.0f;
        sys.audio.track[id].order_playing = 0;
        sys.audio.track[id].total_orders = 0;
        for (uint16_t j=0; j < MAXORDERS; j++) {
            sys.audio.track[id].order[j] = 0;
        }
    }
    if  (IsAudioDeviceReady()) return status; else return 1;
    return status;
}

void update_audio(void) {
    for (uint16_t id=0; id < MAXAUDIOTRACKS; id++) {
        if (sys.audio.track[id].is_playing) {
            if (sys.audio.track[id].virtual_display == sys.video.current_virtual) {
                UpdateMusicStream(sys.asset.music[sys.audio.track[id].asset]);
            }
        }
    }
}

static int16_t add_track(uint16_t display, uint32_t state, const char* fileName, const char* fileType, const uint8_t* fileData, uint32_t dataSize, uint32_t pak, uint16_t total_orders, uint16_t orderlist[]) {
    uint16_t track_id = sys.audio.total_tracks;
    sys.audio.track[track_id].virtual_display = display;
    sys.audio.track[track_id].state = state;
    sys.audio.track[track_id].asset = load_asset(ASSET_XM, fileName, fileType, fileData, dataSize, pak);
    sys.audio.track[track_id].volume = 1.f;
    //int asset = sys.audio.track[].asset_playing;

    //int total_orders = sizeof(orderlist[0]) / sizeof(int);
    for (uint16_t i = 0; i < total_orders; i++) {
        sys.audio.track[track_id].order[i] = orderlist[i];
    }
    sys.audio.track[track_id].total_orders = total_orders;

    sys.audio.total_tracks += 1;
    return track_id;
}

//StopMusicStream(sys.asset.music[asset]);
static void change_music_stream(uint16_t track_id, uint16_t order_id, bool immediate) {
    uint16_t asset = sys.audio.track[track_id].asset;
    sys.audio.track[track_id].order_playing = order_id;
    
    if (order_id < sys.audio.track[track_id].total_orders) {
        if (!immediate) { // switches at end of pattern
            jar_xm_pattern_jump(sys.asset.music[asset].ctxData, sys.audio.track[track_id].order[order_id]);
        } else { // switches immediately
            jar_xm_pattern_jump_immediate(sys.asset.music[asset].ctxData, sys.audio.track[track_id].order[order_id], true);
        };
    }
}

static void hint_restart_track(bool immediate) {
    for (uint16_t id=0; id < MAXAUDIOTRACKS; id++) {
        if (sys.audio.track[id].virtual_display == sys.video.current_virtual) {
            if (sys.audio.track[id].state || TRACK_RESTART_ON_FOCUS) {
                sys.audio.track[id].is_playing = true;
                uint16_t order = sys.audio.track[id].order_playing;
                change_music_stream(id, order, immediate);
            }
        }
    }
}

static void play_track(uint16_t track_id, uint16_t order_id, bool immediate) {
    sys.audio.track[track_id].is_playing = true;
    uint16_t asset = sys.audio.track[track_id].asset;
	PlayMusicStream(sys.asset.music[asset]);
    change_music_stream(track_id, order_id, immediate);
}

static void change_track_playing(uint16_t track_id, uint16_t value) {
    sys.audio.track[track_id].is_playing = true;
    uint16_t proposed_order = (sys.audio.track[track_id].order_playing + value) % sys.audio.track[track_id].total_orders;
    change_music_stream(track_id, proposed_order, true);
}

//    jar_xm_change_all_channel_volumes(sys.asset.music[asset].ctxData, (int) amount); // DO NOT USE, INSTEAD REVAMP TRACKER MIXER
static void change_track_volume(uint16_t track, float volume) {
    if (volume>=0.f && volume <=1.0f) sys.audio.track[track].volume = volume;
    uint16_t asset = sys.audio.track[track].asset;
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

static Vector2 ratio_info(float x, float y) {
    Vector2 p;

    float gcd_res = gcdi(x,y);
    p.x = x / gcd_res;
    p.y = y / gcd_res;
    return p;
}

void begin_draw(bool clear) {
    BeginTextureMode(sys.asset.framebuffer[sys.video.virtual_asset[sys.video.current_virtual]]);
    if (clear) ClearBackground(BLACK);
    rlDisableDepthMask();            // Disable depth writes
    rlDisableDepthTest();            // Disable depth test for speed
}

void end_draw(void) {
    rlEnableDepthMask();
    rlEnableDepthTest();
    EndTextureMode();
}

void flip_frame_buffer(uint16_t display, bool clear) {
    sys.video.previous_virtual = sys.video.current_virtual;
    sys.video.current_virtual = display;
    if (clear) sys.video.screen_refresh = true;
}

static void draw_frame_buffer(RenderTexture renderer, Vector2 position) {
	DrawTexturePro (renderer.texture,
    (Rectangle) {0.0, 0.0, (float)renderer.texture.width, (float)-renderer.texture.height},
    (Rectangle) {position.x, position.y, sys.video.screen[sys.video.display_id].x, sys.video.screen[sys.video.display_id].y},
    (Vector2)   {0.0, 0.0}, 0.0f, WHITE);
}

static uint16_t init_frame_buffer(uint16_t display, Vector2 resolution) {
    flip_frame_buffer(display, true);
    sys.video.virtual_res[sys.video.current_virtual] = resolution;
    sys.video.frames[sys.video.current_virtual] = 0;
    sys.video.elapsed_time_var_ratio[sys.video.current_virtual] = 5.f;
    sys.video.frame_time_inc[sys.video.current_virtual] = 0;
	uint16_t asset_id = load_asset(ASSET_FRAMEBUFFER, NULL, NULL, NULL, NULL, 0);
    flip_frame_buffer(sys.video.previous_virtual, true);
    return asset_id;
}

bool init_display_properties(bool hide_mouse) {
    bool status = 0;
    BITS_INIT(sys.video.windowstate_normal, 0);
    //sys.video.windowstate_normal = FLAG_WINDOW_UNDECORATED; // AVOID AT ALL COST (SCREEN TEARING when VSYNC)
    BITS_ON(sys.video.windowstate_normal, FLAG_FULLSCREEN_MODE);
    BITS_ON(sys.video.windowstate_normal, FLAG_WINDOW_ALWAYS_RUN);
    BITS_ON(sys.video.windowstate_normal, FLAG_WINDOW_TOPMOST);
    BITS_ON(sys.video.windowstate_normal, FLAG_MSAA_4X_HINT);
    BITS_ON(sys.video.windowstate_normal, FLAG_VSYNC_HINT);

    BITS_INIT(sys.video.windowstate_paused, 0);
    BITS_ON(sys.video.windowstate_paused, FLAG_FULLSCREEN_MODE);
    BITS_ON(sys.video.windowstate_paused, FLAG_WINDOW_UNFOCUSED);
    BITS_ON(sys.video.windowstate_paused, FLAG_WINDOW_MINIMIZED);
    BITS_ON(sys.video.windowstate_paused, FLAG_MSAA_4X_HINT);
    BITS_ON(sys.video.windowstate_paused, FLAG_VSYNC_HINT);

    SetConfigFlags(sys.video.windowstate_normal);
    InitWindow(0, 0, sys.program.name);
    sys.video.display_id = GetCurrentMonitor();
    if (hide_mouse) HideCursor();
    sys.video.screen[sys.video.display_id] = (Vector2) {GetScreenWidth(), GetScreenHeight()};
    sys.video.screen_rate[sys.video.display_id] = GetMonitorRefreshRate(sys.video.display_id);
    SetWindowSize(sys.video.screen[sys.video.display_id].x, sys.video.screen[sys.video.display_id].y);

    if (IsWindowReady()) return status; else return 1;
}

void flip_display_state(uint32_t state) {
    if (!(sys.program.ctrlstate & CTRL_OFF_FOCUS)) {
        BITS_FLIP(sys.video.windowstate_normal, state);
    } else {
        BITS_FLIP(sys.video.windowstate_paused, state);
    }
    if (IsWindowState(state)) { 
        ClearWindowState(state);
    } else {
        SetWindowState(state);
        // if (state & FLAG_VSYNC_HINT)  // ***GLFW issue with Refresh rate reset to 60 on VSYNC
        // since this is an issue, if we really want to do this right, we would have to possibly reload all assets
    }
}

    // The way this works right now is not proper, as we have 4-5 different virtual display, we need a way to display them all at once,
    // or at least display the MENU + poossibly the Terminal + the game
    // So first, the rendering to a texture part, needs to be expanded
    // then update_system needs to take into account the different virtual displays and how to decide on;
    // - The order in which they should be displayed
    // - Should they display
    // - And their alpha blending
void update_display(void) {
    uint16_t display = sys.video.current_virtual;
	BeginDrawing();
        if (sys.video.screen_refresh) {
            ClearBackground(BLACK);
            sys.video.screen_refresh = false;
        };
        draw_frame_buffer(sys.asset.framebuffer[sys.video.virtual_asset[display]], (Vector2) {0,0});

        if (sys.program.ctrlstate & CTRL_DEBUG) {
            // if debug functionalities activated
            // DISPLAY MANAGE DEBUG INFORMATION
            update_debug(true);
        }
	EndDrawing();

    sys.video.window_focus = IsWindowFocused();

    double next_frame = sys.video.prev_time[display] + (double)(1 / sys.video.screen_rate[sys.video.display_id]);
    float wait = (next_frame - GetTime());
    if (wait < 0) wait = 0;
    WaitTime(wait * 1000.f);

    double current_time = GetTime();

    sys.video.elapsed_time[display] = current_time - sys.video.prev_time[display];
    sys.video.prev_time[display] = current_time;

   if (sys.video.window_focus) {        // ************** GO TO APP MODE
        if (sys.program.ctrlstate & CTRL_OFF_FOCUS) {
            if (GetKeyPressed() != 0) {
                BITS_OFF(sys.program.ctrlstate, CTRL_OFF_FOCUS);
                flip_frame_buffer(PRIMARYDISPLAY, true);
                ClearWindowState(sys.video.windowstate_normal ^ sys.video.windowstate_paused);
                SetWindowState(sys.video.windowstate_normal);
                sys.video.prev_time[sys.video.current_virtual] = current_time;
            }
        }
    } else {        // ************* GO TO PAUSE MODE
        //IsWindowMinimized()
        if (!(sys.program.ctrlstate & CTRL_OFF_FOCUS)) {
            BITS_ON(sys.program.ctrlstate, CTRL_OFF_FOCUS);
            flip_frame_buffer(UNFOCUSEDDISPLAY, true);
            ClearWindowState(sys.video.windowstate_paused ^ sys.video.windowstate_normal);
            SetWindowState(sys.video.windowstate_paused);
            hint_restart_track(true);
            sys.video.prev_time[sys.video.current_virtual] = current_time;
        };
    };

    sys.video.frame_time[display] = (float)sys.video.elapsed_time[display] * (float)sys.video.screen_rate[sys.video.display_id];
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
    uint32_t current_state;
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
	
	for(uint16_t i = 0; i < MAXPARTICLES; i++) {
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
	for(uint16_t i = 0; i < MAXPARTICLES; i++) {
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

static void copper_animation(int16_t direction, uint16_t asset, uint16_t segments, uint16_t coppers, uint16_t size_y, float rastoffset, Vector2 offset, Vector3 ratio, float scale) {
    static bool do_it;
    static float y_start;
    static uint16_t copper;
    uint16_t display = sys.video.current_virtual;
    Vector2 vres = sys.video.virtual_res[sys.video.current_virtual];
	float size_x = vres.x / (float)segments;
    float amp = (vres.y * scale) - (size_y * 0.5);
    for(uint16_t y = 0; y < coppers; y++) {
        copper = y % 16;
        for(uint16_t x = 0; x < segments; x++) {
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
    uint16_t palette;
    int32_t palptr;
    float palptr_next_frame_time;
} EX_marquee;

EX_marquee ex_marquee[MAXDISPLAYS];

static void update_marquee_animation(uint16_t asset_id, uint16_t palette_id, Vector2 logosize, float transparency, Vector2 offset, float speed, float shadow_transparency) {
    uint16_t display = sys.video.current_virtual;
    if (ex_marquee[display].palptr_next_frame_time < sys.video.frame_time_inc[display]) {
        ex_marquee[display].palptr_next_frame_time = sys.video.frame_time_inc[display] + 1/absf(speed);
        if (speed > 0.0f) {
            ex_marquee[display].palptr += 1;
        } else {
            ex_marquee[display].palptr -= 1;
        }
        if (ex_marquee[display].palptr > 255) {ex_marquee[display].palptr -= 256;} else if (ex_marquee[display].palptr < 0) {ex_marquee[display].palptr += 256;};
    };
    int32_t palptr_loop = ex_marquee[display].palptr;

    if (transparency > 0.0f) {
        Vector2 scale = {(255.0f - transparency) * 0.01f + 1.0f, 1.0f};
        Vector2 final_offset = {offset.x + (sys.video.virtual_res[sys.video.current_virtual].x-(logosize.x * scale.x))/2.0, offset.y};
        for(uint16_t i = 0; i < logosize.y; i++) {
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
    uint16_t cells_x;
    uint16_t cells_y;
    int16_t pal_idx_cells;
    int16_t pal_idx_text;
    uint16_t font_id;
    uint16_t palette_id;
    Vector2 grid[CANOPYMAXY][CANOPYMAXX]; // set to max capacity
} EX_canopy;

EX_canopy ex_canopy;

static void init_canopy (uint16_t font_id, uint16_t palette_id, Vector2 cells, Vector2 cell_size, float transparency, float transparency_mod, Vector2 adjustment, int16_t pal_idx_cells, int16_t pal_idx_text) {
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
    
    for (uint16_t y = 0; y < ex_canopy.cells_y; y++) {
        for (uint16_t x = 0; x < ex_canopy.cells_x; x++) {
            ex_canopy.grid[y][x] = (Vector2) {ex_canopy.cell_size.x, ex_canopy.cell_size.y};
        };
    };
}

static void update_canopy(uint16_t asset_id) {
    ex_canopy.offset.x = (sys.video.virtual_res[sys.video.current_virtual].x-((ex_canopy.cells_x+1)*ex_canopy.cell_size.x))*0.5f;
    ex_canopy.offset.y = 7.0f * ex_canopy.cell_size.x + (255.f - ex_canopy.transparency);
    if ((ex_canopy.transparency > 0.0f) & (ex_canopy.offset.y <= sys.video.virtual_res[sys.video.current_virtual].y)) {
            
        Vector2 cell_size;
        int16_t col_idx;
        ex_canopy.sin_value_old.x = ex_canopy.sin_value.x;
        ex_canopy.sin_value_old.y = ex_canopy.sin_value.y;
        Color vertex_colors[4];
        for(int16_t y = (ex_canopy.cells_y - 1); y >= 0; y -= 1) {
            for(int16_t x = (ex_canopy.cells_x - 1); x >= 0; x -= 1) {
                float x_sin = fast_sin(ex_canopy.sin_value.x);
                float y_sin = fast_sin(ex_canopy.sin_value.y);
                ex_canopy.grid[y][x].x = ((float)x+x_sin)*ex_canopy.cell_size.x + ex_canopy.offset.x;
                ex_canopy.grid[y][x].y = ((float)y+y_sin)*ex_canopy.cell_size.x + ex_canopy.offset.y;

                if (x<(ex_canopy.cells_x-1)) {cell_size.x = ((ex_canopy.grid[y][x+1].x - ex_canopy.grid[y][x].x));} else {cell_size.x = ex_canopy.cell_size.x;};
                if (y<(ex_canopy.cells_y-1)) {cell_size.y = ((ex_canopy.grid[y+1][x].y - ex_canopy.grid[y][x].y) + 1.f);} else {cell_size.y = ex_canopy.cell_size.y;};
                    
                if (cell_size.x > 0 && cell_size.y > 0) {
                    col_idx = (int16_t)(y_sin * 4.0f); if (col_idx > 3) col_idx = 3;
                    vertex_colors[0] = get_palette_color(ex_canopy.palette_id,-col_idx + ex_canopy.pal_idx_cells);
                    vertex_colors[1] = vertex_colors[0];
                    vertex_colors[2] = vertex_colors[0];
                    vertex_colors[3] = vertex_colors[0];
                    DrawRectanglePro2(
                    (Rectangle){ex_canopy.grid[y][x].x, ex_canopy.grid[y][x].y, cell_size.x, cell_size.y}, 
                    (Vector2) {0.f, 0.f}, (Vector2) {0.f, 0.f}, 0.f,
                    vertex_colors);

                    // draw text from a grid
                    col_idx = (int16_t)(y_sin * 7.0f); if (col_idx > 6) col_idx = 6;
                    vertex_colors[0] = get_palette_color(ex_canopy.palette_id,-col_idx + ex_canopy.pal_idx_text);
                    vertex_colors[1] = vertex_colors[0];
                    vertex_colors[2] = vertex_colors[0];
                    vertex_colors[3] = vertex_colors[0];
                    float value = (float)(sys.asset.data[asset_id][y * ex_canopy.cells_x + x]);
                    DrawTexturePro2(sys.asset.tex[ex_canopy.font_id],
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
    uint16_t bar_count = sizeof(colorbar) / sizeof(Color);
    float x = sys.video.virtual_res[sys.video.current_virtual].x * 1/bar_count;
    for (uint16_t i = 0; i < bar_count; i++) {
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
    uint16_t asset_id;
    uint16_t font_id;
    uint16_t palette_id;
    Vector2 position;
    Vector2 skew;
    float alpha;
    int16_t text_wave_flag;
    int16_t text_angle;
    int16_t text_wave;
    float pause_found;
    float text_pause;
    float text_scroll_speed;
    float text_shadow;
    uint16_t colorfg;
    uint16_t colorfg_flag;
    uint16_t colorbg;
    uint16_t colorbg_flag;
} EX_scrolltext;

EX_scrolltext ex_scrolltext[16];

static void init_scrolltext(uint16_t s, uint16_t asset_id, uint16_t font_id, uint16_t palette_id, float speed, Vector2 position, Vector2 skew, float alpha) {
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
    ex_scrolltext[s].colorfg_flag = 0;
    ex_scrolltext[s].colorbg_flag = 0;
    ex_scrolltext[s].colorfg = 15;
    ex_scrolltext[s].colorbg = 0;
}

const uint16_t scrolltext_color[] = {
        33,   // BROWN
        41,   // BEIGE
        58,   // ORANGE
        30,   // YELLOW
        210,  // GREEN
        216,  // LIME
        82,   // MAGENTA
        89,   // PINK
        100,  // PURPLE
        104,  // VIOLET
        129,  // BLUE
        170,  // SKYBLUE
        49,   // MAROON
        69,   // RED
        0,    // BLACK
        4,    // DARKGRAY
        8,    // GRAY
        12,   // LIGHTGRAY
        15    // WHITE
};

uint16_t scrolltext_color_pick(int16_t id) {
    int16_t colors = sizeof(scrolltext_color) / sizeof(uint16_t);
    if (id >= colors) id = (colors - 1); else if (id < 0) id = 0;
    return scrolltext_color[id];
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

static void update_scrolltext(uint16_t s, float text_scale) {
    uint16_t palette_id = ex_scrolltext[s].palette_id;
    
    if (ex_scrolltext[s].text_pause <= 0.0) {
        ex_scrolltext[s].position.x -= (sys.video.frame_time[sys.video.current_virtual] * ex_scrolltext[s].text_scroll_speed) / text_scale;
    } else {
        ex_scrolltext[s].text_pause -= sys.video.frame_time[sys.video.current_virtual];
    };

    uint16_t id;
    float et_var = sys.video.elapsed_time_var[sys.video.current_virtual];
    Vector2 displacement;
    int16_t i_x = 0;

    uint8_t *text = &sys.asset.data[ex_scrolltext[s].asset_id];
	for(uint16_t i=0; i < sys.asset.data_size[ex_scrolltext[s].asset_id]; i++) {
        displacement.y = fast_sin(et_var) * text_scale;
        et_var += ((PI * 2) / 24);

        uint8_t ch = sys.asset.data[ex_scrolltext[s].asset_id][i];
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
            ex_scrolltext[s].colorfg_flag = 1;
            break;
        case SCROLL_TEXTCOLOR: // text color table chooser
            i++;
            ex_scrolltext[s].colorfg = scrolltext_color_pick((sys.asset.data[ex_scrolltext[s].asset_id][i]) - 97);
            break;
        case SCROLL_BKGNDCOLOR: // background color table chooser
            i++;
            ex_scrolltext[s].colorbg_flag = 1;
            id = (sys.asset.data[ex_scrolltext[s].asset_id][i]) - 97;
            ex_scrolltext[s].colorbg = scrolltext_color_pick(id);
            if (id > 18) ex_scrolltext[s].colorbg_flag = 0;
            break;
        case SCROLL_BKGNDCOLORX: // background color extended chooser 
            i++;
            ex_scrolltext[s].colorbg_flag = 1;
            uint8_t hue = (sys.asset.data[ex_scrolltext[s].asset_id][i]) - 97;
            if (hue > 15) hue = 15; // can not test id
            i++;
            uint8_t lum = (sys.asset.data[ex_scrolltext[s].asset_id][i]) - 97;
            if (lum > 15) lum = 15; // can not test id
            ex_scrolltext[s].colorbg = (hue * 16 + lum);
            break;
        case SCROLL_TEXTNOCOLOR: // text color normal
            ex_scrolltext[s].colorfg = 15;
            ex_scrolltext[s].colorfg_flag = 0;
            break;
        default:
            if(((ex_scrolltext[s].position.x + (i_x - 1)) * text_scale ) < sys.video.virtual_res[sys.video.current_virtual].x && ((ex_scrolltext[s].position.x + (i_x + 2)) * text_scale ) > 0) {
                if (ch == SCROLL_PAUSE) { // pause the scroll x amount of seconds (a-z = 1 to 26 seconds)
                    i++;
                    if (ex_scrolltext[s].pause_found != (i - 1)) {
                        ex_scrolltext[s].pause_found = i - 1;
                        if (ex_scrolltext[s].text_pause <= 0.0) {
                            ex_scrolltext[s].text_pause = sys.video.screen_rate[sys.video.display_id] * (float)(sys.asset.data[ex_scrolltext[s].asset_id][i] - 96); // set pause for x secs (a-z=1-26)
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
                    if (ex_scrolltext[s].colorfg_flag == 1) {
                        ex_scrolltext[s].colorfg = (int16_t)(displacement.y * 0.5f) + 7;
                    };
                    if (ex_scrolltext[s].text_pause > 0.0 || ex_scrolltext[s].text_wave_flag == 0) {
                        ex_scrolltext[s].text_angle = 0;
                    } else {
                        ex_scrolltext[s].text_angle = displacement.y;
                    };

                    uint64_t state = 0;
                    BITS_ON(state, GRFE_DEFAULT2);
                    if (ex_scrolltext[s].colorbg_flag == 0) BITS_OFF(state, GRFE_BACKGROUND);
                    if (!(ex_scrolltext[s].text_angle))     BITS_OFF(state, GRFE_ROTATION);
                    if (ex_scrolltext[s].text_shadow == 0.0) BITS_OFF(state, GRFE_SHADOW);
                    if (ex_scrolltext[s].text_angle)        BITS_OFF(state, GRFE_SKEW);

                    plot_character(ex_scrolltext[s].font_id, ex_scrolltext[s].palette_id, ch, 
                        (Vector2) {(ex_scrolltext[s].position.x +  i_x) * text_scale, (ex_scrolltext[s].position.y * text_scale) + ex_scrolltext[s].text_wave}, 
                        (Vector2) {text_scale, text_scale}, 
                        ex_scrolltext[s].skew,
                        (Vector2) {2, 2},
                        ex_scrolltext[s].text_angle, 
                        get_palette_color2(palette_id, ex_scrolltext[s].colorfg, ex_scrolltext[s].alpha), 
                        get_palette_color2(palette_id, ex_scrolltext[s].colorbg, ex_scrolltext[s].alpha),
                        (Color) {255, 255, 255, 255},
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

// ********** S C R O L L T E X T   S Y S T E M  ***** S C R O L L T E X T   S Y S T E M  ***** S C R O L L T E X T   S Y S T E M  ***** E N D
// ********** S C R O L L T E X T   S Y S T E M  ***** S C R O L L T E X T   S Y S T E M  ***** S C R O L L T E X T   S Y S T E M  ***** E N D
// ********** S C R O L L T E X T   S Y S T E M  ***** S C R O L L T E X T   S Y S T E M  ***** S C R O L L T E X T   S Y S T E M  ***** E N D

// ********** E D I T O R   S Y S T E M  ***** E D I T O R   S Y S T E M  ***** E D I T O R   S Y S T E M  ***** B E G I N
// ********** E D I T O R   S Y S T E M  ***** E D I T O R   S Y S T E M  ***** E D I T O R   S Y S T E M  ***** B E G I N
// ********** E D I T O R   S Y S T E M  ***** E D I T O R   S Y S T E M  ***** E D I T O R   S Y S T E M  ***** B E G I N

// MUSIC SCORING
typedef enum {
    octave_up           = 192,
    octave_down         = 193,
    instrument_up       = 194,
    instrument_down     = 195,
    enable_arpeggio     = 196,
    disable_arpeggio    = 197,
    perc_bd1            = 224,
    perc_bd2            = 225,
    perc_sn1            = 226,
    perc_sn2            = 227,
    perc_tom1           = 228,
    perc_tom2           = 229,
    perc_tom3           = 230,
    perc_cymbal         = 231,
    perc_oph            = 232,
    perc_clhh           = 233,
    perc_cbell          = 234,
    perc_wblk           = 235,
    perc_clap           = 236,
    perc_rim            = 237,
    perc_tamb           = 238,
    null_function       = 255
} track_editor;

static const kbmap_piano[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

// Add all level design tools and import / export capability
// Editor design will benefit from the paging system capabilities for menu options

// ********** E D I T O R   S Y S T E M  ***** E D I T O R   S Y S T E M  ***** E D I T O R   S Y S T E M  ***** E N D
// ********** E D I T O R   S Y S T E M  ***** E D I T O R   S Y S T E M  ***** E D I T O R   S Y S T E M  ***** E N D
// ********** E D I T O R   S Y S T E M  ***** E D I T O R   S Y S T E M  ***** E D I T O R   S Y S T E M  ***** E N D

// ********** T E R M I N A L   S Y S T E M  ***** T E R M I N A L   S Y S T E M  ***** T E R M I N A L   S Y S T E M  ***** B E G I N
// ********** T E R M I N A L   S Y S T E M  ***** T E R M I N A L   S Y S T E M  ***** T E R M I N A L   S Y S T E M  ***** B E G I N
// ********** T E R M I N A L   S Y S T E M  ***** T E R M I N A L   S Y S T E M  ***** T E R M I N A L   S Y S T E M  ***** B E G I N

static const kbmap_scancode[] = {
    KEY_ESCAPE ,0 , 0, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12, 0, KEY_PRINT_SCREEN, KEY_SCROLL_LOCK, KEY_PAUSE, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    KEY_GRAVE, KEY_ONE, KEY_TWO, KEY_THREE, KEY_FOUR, KEY_FIVE, KEY_SIX, KEY_SEVEN, KEY_EIGHT, KEY_NINE, KEY_ZERO, KEY_MINUS, KEY_EQUAL, KEY_BACKSPACE, KEY_BACKSPACE, 0, KEY_INSERT, KEY_HOME, KEY_PAGE_UP, 0, KEY_NUM_LOCK, KEY_KP_DIVIDE, KEY_KP_MULTIPLY, KEY_KP_SUBTRACT, 
    KEY_TAB, KEY_TAB, KEY_Q, KEY_W, KEY_E, KEY_R, KEY_T, KEY_Y, KEY_U, KEY_I, KEY_O, KEY_P, KEY_LEFT_BRACKET, KEY_RIGHT_BRACKET, KEY_BACKSLASH, 0, KEY_DELETE, KEY_END, KEY_PAGE_DOWN, 0, KEY_KP_7, KEY_KP_8, KEY_KP_9, KEY_KP_ADD, 
    KEY_CAPS_LOCK, KEY_CAPS_LOCK, KEY_A, KEY_S, KEY_D, KEY_F, KEY_G, KEY_H, KEY_J, KEY_K, KEY_L, KEY_SEMICOLON, KEY_APOSTROPHE, KEY_ENTER, KEY_ENTER, 0, 0, 0, 0, 0, KEY_KP_4, KEY_KP_5, KEY_KP_6, KEY_KP_ADD, 
    KEY_LEFT_SHIFT, KEY_LEFT_SHIFT, KEY_Z, KEY_X, KEY_C, KEY_V, KEY_B, KEY_N, KEY_M, KEY_COMMA, KEY_PERIOD, KEY_SLASH, KEY_RIGHT_SHIFT, KEY_RIGHT_SHIFT, KEY_RIGHT_SHIFT, 0, 0, KEY_UP, 0, 0, KEY_KP_1, KEY_KP_2, KEY_KP_3, KEY_KP_ENTER, 
    KEY_LEFT_CONTROL, KEY_LEFT_SUPER, KEY_LEFT_ALT, KEY_SPACE, KEY_SPACE, KEY_SPACE, KEY_SPACE, KEY_SPACE, KEY_SPACE, KEY_SPACE, KEY_SPACE, KEY_RIGHT_ALT, KEY_RIGHT_SUPER, KEY_KB_MENU, KEY_RIGHT_CONTROL, 0, KEY_LEFT, KEY_DOWN, KEY_RIGHT, 0, KEY_KP_0, KEY_KP_0, KEY_KP_DECIMAL, KEY_KP_ENTER
};

static const kbmap_ascii[] = {
    27, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    96, 49, 50, 51, 52, 53, 54, 55, 56, 57, 45, 61, 8, 0, 0, 0, 0, 0, 0, 0, 0, 47, 42, 45, 
    9, 9, 81, 87, 69, 82, 84, 89, 85, 73, 79, 80, 91, 93, 92, 0, 0, 0, 127, 0, 55, 56, 57, 43, 
    0, 0, 65, 83, 68, 70, 71, 72, 74, 75, 76, 59, 44, 13, 13, 0, 0, 0, 0, 0, 52, 53, 54, 43, 
    0, 0, 90, 88, 67, 86, 66, 78, 77, 44, 46, 47, 0, 0, 0, 0, 0, 0, 0, 0, 49, 50, 51, 13, 
    0, 0, 0, 32, 32, 32, 32, 32, 32, 32, 32, 32, 0, 0, 0, 0, 0, 0, 0, 0, 48, 48, 46, 13
};


//  Note for ANSi, colors expected are 0: black, 1: red, 2: green, 3: yellow, 4: blue, 5: magenta, 6: cyan, 7: white
// CSI introduces a Control Sequence, which continues until an alphabetic character is received (general rule).
// EXCELLENT REFERENCE OF USAGE: https://handwiki.org/wiki/ANSI_escape_code
// https://vt100.net/emu/dec_ansi_parser
typedef enum {
    CMD_CSI     = 155,  // Control Sequence Introducer, 0x9b ( ¢ ) or 0x1b ( ← ) + [, 0x5b ( [ ) is necessary when 7-bit (0x1b) CSI used
    CMD_SEP     = 59,   // Value separator for numeric parameter characters ( ; ) 
    CMD_ST      = 92,   // String Terminator ( \ )
    CMD_OSC     = 93,   // Operating System Command ( ] )
    CMD_PM      = 94,   // CSI ^    Privacy message (String Control Sequence)
    CMD_APC     = 95,   // CSI _    Application Program Command (for embedding custom commands)

    CMD_6       = 54,   // Move cursor back 1 column
    CMD_9       = 57,   // Move cursor forward 1 column
    CMD_LT      = 60,   // (VT-52) Enter ANSi mode
    CMD_EQ      = 61,   // (VT-52) Enter Alternate Keypad mode (num lock, directional arrows)
    CMD_GT      = 62,   // (VT-52) Exit alternate keypad mode (numeric character mode)
    CMD_A       = 65,   // (VT-52) Cursor up
    CMD_B       = 66,   // (VT-52) Cursor down
    CMD_C       = 67,   // (VT-52) Cursor right
    CMD_D       = 68,   // (VT-52) Cursor left
    CMD_E       = 69,   // (VT-52) Next Line
    CMD_F       = 70,   // (VT-52) Enter Graphics mode
    CMD_G       = 71,   // (VT-52) Exit Graphics mode
    CMD_H       = 72,   // (VT-52) Cursor to Home
    CMD_I       = 73,   // (VT-52) Reverse Line Feed
    CMD_J       = 74,   // (VT-52) Erase to end of screen
    CMD_K       = 75,   // (VT-52) Erase to end of line
    CMD_N       = 78,   // SS2 - Single Shift 2 - Call a single character from G2 font
    CMD_O       = 79,   // SS3 - Single Shift 3 - Call a single character from G3 font
    CMD_V       = 86,   // (VT-52) Print Cursor Line
    CMD_W       = 87,   // (VT-52) Enter printer controller mode
    CMD_X       = 88,   // (VT-52) Exit printer controller mode
    CMD_Y       = 89,   // (VT-52) Direct cursor address CSIY10 20
    CMD_Z       = 90,   // (VT-52) Identify (DECID)
    CMD_CL      = 93,   // (VT-52) Print screen
    CMD_EX      = 94,   // (VT-52) Enter auto print mode
    CMD_UN      = 95,   // (VT-52) Exit auto print mode
    CMD_LA      = 35,   // Line Attribute: Double height = CSI#3 Top Half, CSI#4 Bottom Half, Width = CSI#5 Single Width Line, CSI#6 Double Width Line
    CMD_DECALN  = 56,   // CSI#8    Screen Alignment Pattern; sets margins to extreem of pagegroup and cursor to home, fills display with pattern
    CMD_RIS     = 99,   // CSIc     Reset to Initial State (Performs a communications line disconnect.  Clears UDKs.    Clears a down-line-loaded character set.
                        // Clears the screen.  Returns the cursor to the upper-left corner of the screen.  Sets the SGR state to normal.
                        // Sets the selective erase attribute write state to "not erasable".   Sets all character sets to the default.)
    CMD_DCS     = 80,   // CSIP{Pc;Pl|Ky1/st1;ky2/st2;...kyn/stn}ST  Device Control String Introducer(P)
                        // {Pc} None or 0 = Clear all keys before loading new values. 1 = Load new key values, clear old ones
                        // {pl} None	or 0 = Lock the keys. (Cannot be redefined.) 1 = Do not lock the keys. (Can be redefined.)
                        // {Kyn/Stn} Function Key Definition string where Kyn = number (1 - 12), Stn = String parameter (up to 1024 char)
                        // User programmed function keys are accessed using the shift + Fn key combo
                        // CSIP{Ps v D...D}ST Load Answerback Message
                        // answerback data string may consist of from 0 to 30, 8-bit characters
                        // Ps =decoding mode, 1 = standard for VT510
                        // CSIP{Ps r D...D}ST Load Banner Message
                        // Ps = 0 Omitted, 1 Interprets as ASCII, 2 Loads as text in VT default character set
                        // D...D is a 30 character string

    CMD_DECSC   = 55,   // CSI 7    DEC Save cursor (position, graphic rendition, character set shift state, state of wrap flag, state of origin mode, state of selective erase)
    CMD_DECRC   = 56,   // CSI 8    DEC Restore Cursor
    CMD_CUU     = 65,   // CSI #A   Cursor Up: move cursor up # lines
    CMD_CUD     = 66,   // CSI #B   Cursor Down: move cursor down # lines
    CMD_CUF     = 67,   // CSI #C   Cursor Forward: move cursor right # columns
    CMD_CUB     = 68,   // CSI #D   Cursor Backwards: move cursor left # columns
    CMD_CNL     = 69,   // CSI #E   Cursor Next Line: moves cursor to beginning of next line, # lines down
    CMD_CPL     = 70,   // CSI #F   Cursor Previous Line: moves cursor to beginning of previous line, # lines down
    CMD_CHA     = 71,   // CSI #G   moves cursor to column # (Horizontal absolute)
    CMD_CUP     = 72,   // Cursor Position (ie. CSI H = cursor to home position (0, 0), CSI {line};{column}H = cursor to specific cell
    CMD_CHT     = 73,   // CSI #I   Cursor Horizontal Forward Tabulation (where # is the number of tabs)
    CMD_ED      = 74,   // Erase in Display
                        // CSI J    Erase from the cursor position to end of display (line attr become single width / height on erased lines)
                        // CSI 0J   <same as above>
                        // CSI 1J   clears from cursor to beginning of display
                        // CSI 2J   clears entire display
                        // CSI ?J   DECSCA Erase all erasable characters from the cursor position to end of display (line attr become single width / height on erased lines), does not affect video char attr or video line attr (SGR)
                        // CSI ?0J  DECSCA <same as above>
                        // CSI ?1J  DECSCA Erase all erasable characters from cursor to beginning of display, does not affect video char attr or video line attr (SGR)
                        // CSI ?2J  DECSCA Erase all erasable characters entire display, does not affect video char attr or video line attr (SGR)

    CMD_EL      = 75,   // Erase in Line
                        // CSI K    Erase to end of current line (including at cursor position)
                        // CSI 0K   <same as above>
                        // CSI 1K   clears from cursor to start of line
                        // CSI 2K   clears entire line
                        // CSI ?K   DECSCA Erase all erasable characters to end of current line (including at cursor position), does not affect video char attr or video line attr (SGR)
                        // CSI ?0K  DECSCA <same as above>
                        // CSI ?1K  DECSCA Erase all erasable characters from cursor to start of line, does not affect video char attr or video line attr (SGR)
                        // CSI ?2K  DECSCA Erase all erasable characters entire line, does not affect video char attr or video line attr (SGR)
    CMD_IL      = 76,   // CSI #L   Inserts # Lines at the cursor.  If fewer than # lines remain from the current line to the end of the scrolling region, the number of lines inserted is the lesser number.  Lines within the scrolling region at and below the cursor is moved down. Lines moved past the bottom margin are lost.  The cursor is reset to the first column. sequence is ignore outisde of the sscrolling rtegion.
    CMD_DL      = 77,    // CSI #M   Deletes # lines starting at the line with the cursor.  If fewer than # lines remain from the current line to the end of the scrolling region, the number of lines deleted is the lesser number. As lines are deleted, lines within the scrolling region and below the cursor move up, and blank lines are added at the bottom of the scrolling region. The cursor is reset to the first column. This sequence is ignored when the cursor is outside the scrolling region.
    CMD_ICH     = 64,   // CSI{#@   Insert # blank characters at the cursor position, with the character attributes set to normal. The cursor does not move and remains at the beginning of the inserted blank characters. A parameter of 0 or 1 inserts one blank character. Data on the line is shifted forward as in character insertion.
    CMD_SS2     = 78,   // CSI #N   Single Shift 2 = Get a character from G2 character set
    CMD_SS3     = 79,   // CSI #O   Single Shift 3 = Get a character from G3 character set
    CMD_DCH     = 80,   // CSI #P   Deletes # characters starting with the character at the cursor position. When a character is deleted, all characters to the right of the cursor move to the left. This creates a space character at the right margin for each character deleted. Character attributes move with the characters. The spaces created at the end of the line have all their character attributes off.
                        // pagegroup Position Absolute (PPA)     CSI #SPP
    CMD_PPR     = 81,   // pagegroup Position Relative (PPR)     CSI #SPQ
    CMD_CPR     = 82,   // CSI #;#R Report cursor position
                        // pagegroup Position Backward (PPB)     CSI #SPR
    CMD_SU      = 83,   // CSI #S   Scroll window up by n lines (pan down)
    CMD_SD      = 84,   // CSI #T   Scroll window down by n lines (pan up)
    CMD_NP      = 85,   // CSI #U   Next pagegroup
    CMD_PP      = 86,   // CSI #V   Previous pagegroup
    CMD_SOS     = 88,   // CSI {arg}X   Start Of String (String Control Sequence)
    CMD_IDENT   = 90,   // CSI Z    Identify what the terminal is
    CMD_VPA     = 100,  // CSI #d   Vertical Line Position Absolute: Where # is the column number (move cursor to line #)
    CMD_VPR     = 101,  // CSI #e   Vertical Position Relative: Where # is the # of columns to move cursor    
    CMD_HVP     = 102,  // Horizontal Vertical Position: CSI {line};{column}f	moves cursor to line #, column #
    CMD_TBC     = 103,  // CSI g (or 0g)  Clear horizontal tab stop at cursor position
                        // CSI 3g   Clear all horizontal tab stops
    CMD_SETMODE = 104,  // CSI 3h   Set Show Control Character mode
                        // CSI 12h  Local Echo off
                        // CSI ={value}h	Changes the screen width or type to the mode specified by value.
                        // CSI =0h  40 x 25 monochrome (text)                // CSI =1h	40 x 25 color (text)
                        // CSI =2h  80 x 25 monochrome (text)                // CSI =3h	80 x 25 color (text)
                        // CSI =4h  320 x 200 4-color (graphics)             // CSI =5h	320 x 200 monochrome (graphics)
                        // CSI =6h  640 x 200 monochrome (graphics)
                        // CSI =7h  Enables line wrapping
                        // CSI =13h	320 x 200 color (graphics)               // CSI =14h    640 x 200 color (16-color graphics)
                        // CSI =15h	640 x 350 monochrome (2-color graphics)  // CSI =16h    640 x 350 color (16-color graphics)
                        // CSI =17h	640 x 480 monochrome (2-color graphics)  // CSI =18h    640 x 480 color (16-color graphics)
                        // CSI =19h	320 x 200 color (256-color graphics)
                        // CSI ?3h  Set to 132 column mode
                        // CSI ?4h  enable scrolling
                        // CSI ?5h  enable display
                        // CSI ?6h  Enable Origin
                        // CSI ?7h  Enbable auto wrap
                        // CSI ?8h  Enable auto repeat (some keys do not repeat: Alt, Caps Lock, Ctrl, Enter, Scroll Lock, Num Lock, Shift)
                        // CSI ?25h	make cursor visible
                        // CSI ?34h Cursor direction right to left
                        // CSI ?47h	save screen
                        // CSI ?66h engage numlock
                        // CSI ?67h set backspace key for back arrow
                        // CSI ?69h engage vertical split screen
                        // CSI ?97h enable screen saver
                        // CSI ?100h set enables auto answerback
                        // CSI ?101h Conceal answerback message
                        // CSI ?103h Set Half-Duplex mode
                        // CSI ?109h    Set caps lock
                        // CSI ?110h    Set keyboard LED's host indicator mode
                        // CSI ?1049h	enables the alternative buffer
    CMD_RESMODE = 108,  // CSI 3l   Reset Interpret Control Character
                        // CSI 12l  Local Echo on
                        // CSI ={value}l    Resets the mode by using the same values that Set Mode uses, except for 7, which disables line wrapping.
                        // CSI =0l  40 x 25 monochrome (text)                // CSI =1l 40 x 25 color (text)
                        // CSI =2l  80 x 25 monochrome (text)                // CSI =3l 80 x 25 color (text)
                        // CSI =4l  320 x 200 4-color (graphics)             // CSI =5l 320 x 200 monochrome (graphics)
                        // CSI =6l  640 x 200 monochrome (graphics)
                        // CSI =7l  Disable line wrapping
                        // CSI =13l	320 x 200 color (graphics)               // CSI =14l    640 x 200 color (16-color graphics)
                        // CSI =15l	640 x 350 monochrome (2-color graphics)  // CSI =16l    640 x 350 color (16-color graphics)
                        // CSI =17l	640 x 480 monochrome (2-color graphics)  // CSI =18l    640 x 480 color (16-color graphics)
                        // CSI =19l	320 x 200 color (256-color graphics)
                        // CSI ?3l  set to 80 column mode
                        // CSI ?4l  disable scrolling
                        // CSI ?5l  disable display
                        // CSI ?6l  disable Origin
                        // CSI ?7l  disable auto wrap
                        // CSI ?8l  disable auto repeat
                        // CSI ?25l	make cursor invisible
                        // CSI ?34l Cursor direction left to right
                        // CSI ?47l	restore screen
                        // CSI ?66l disengage numlock
                        // CSI ?67l set delete key for back arrow (reset)
                        // CSI ?69l disengage vertical split screen
                        // CSI ?97l disable screen saver
                        // CSI ?100l reset disables auto answerback
                        // CSI ?101l do not conceal answerback message
                        // CSI ?103l Set Full-Duplex mode
                        // CSI ?109l    Reset caps lock
                        // CSI ?110h    Reset keyboard LED's host indicator mode
                        // CSI ?1049l	disables the alternative buffer
    CMD_SGR    = 109,   // CSI 1;34;{...}m	Select Graphic Rendition; set appearance of following characters (values separated by semicolon (;)).
                        // CSI 0m   (Reset or Normal) All Attributes off
                        // CSI 1m   (Bold or increased Intensity) set bold mode
                        // CSI 2m   (Faint, decreased intensity or dim) set dim/faint mode
                        // CSI 3m   (Italic) set italic mode
                        // CSI 4m   (Underline) set underline mode
                        // CSI 5m   (Slow Blink) set blinking mode, less than 150 per minute
                        // CSI 6m   (Rapid Blink) set blinking mode, more than 150 per minute
                        // CSI 7m   (Reverse Video or Invert) set inverse/reverse mode
                        // CSI 8m   (Conceal or Hide) set invisible mode
                        // CSI 9m   (Crossed-out, strike) set strikethrough mode.
                        // CSI 10m  (Primary (Default) font)
                        // CSI 11-19m   (Alternative font) - Select Alternative font n - 10
                        // CSI 20m      (Blackletter font)
                        // CSI 21m  (Doubly underlined, or not bold)
                        // CSI 22m  (Normal Intensity - Neither bold nor faint)
                        // CSI 23m  (neither Italic, nor blackletter)
                        // CSI 24m  (not underlined - Neither singly nor doubly underlined)
                        // CSI 25m  (not blinking)
                        // CSI 26m  (Proportional spacing)
                        // CSI 27m  (Not reversed)
                        // CSI 28m  (Reveal - not concealed)
                        // CSI 29m  (not crossed out)
                        // CSI 30-37m   Set text color from the basic color palette of 0-7
                        // CSI 38;5;{ID}m	Set foreground color
                        // CSI 38;2;{r};{g};{b}m	Set foreground color as RGB
                        // CSI 39m  Default foreground color
                        // CSI 40-47m   Set background color from the basic color palette of 0-7
                        // CSI 48;5;{ID}m	Set background color
                        // CSI 48;2;{r};{g};{b}m	Set background color as RGB
                        // CSI 49m  Default background color
                        // CSI 50m  Disable proportional spacing
                        // CSI 51m  Framed
                        // CSI 52m  Encircled
                        // CSI 53m  Overlined
                        // CSI 54m  Neither framed Nor Circled
                        // CSI 55m  Not overlined
                        // CSI 58{arg}m     Set Underline Color (Next arguments are 5;n or 2;r;g;b.)
                        // CSI 59m  Default underline color
                        // CSI 60m  Ideogram underline or right side line
                        // CSI 61m  Ideogram double underline or douible line on the right side
                        // CSI 62m  Ideogram overline or left side line
                        // CSI 63m  Ideogram double overline, or double lilne on the left side
                        // CSI 64m  Ideogram stress marking
                        // CSI 65m  No ideogram attributes / Reset the effects of all of 60-64
                        // CSI 73m  Superscript
                        // CSI 74m  Subscript
                        // CSI 75m  Neither subscript or superscript
                        // CSI 90-97m       Set bright foreground color
                        // CSI 100-107m     Set bright background color
    CMD_DSR     = 110,  // Device Status Report Call: CSI 5n
                        // Response: CSI 0n = terminal is ok
                        // Response: CSI 3n = terminal is not ok
                        // CSI 6n   Cursor Position Report : request cursor position, Response: CSI #;#R
    CMD_STRING  = 112,  // CSI {code};{string};{...}p
    CMD_DECSCA  = 113,  // CSI #q   (0=All attributes off.(Does not apply to SGR.)1=not erasable by DECSEL/DECSED. 2=Designate character as erasable by DECSEL/DECSED. (Attribute off.)))
    CMD_DECSTBM = 114,  // CSI #;#r   This sequence selects top and bottom margins defining the scrolling region
                        // Change Attributes in Rectangular Area    CSI Pt; Pl; Pb; Pr;Ps1; . . . Psn $r
                        // Source rectangle to change: Pt = Top Line, Pl = Left column, Pb = bottom line, Pr = right column, Ps1 = Select attribute to change
                        // 0 (default)	Attributes off (no bold, no underline, no blink, positive image)
                        // 1    Bold        // 4    Underline           // 5    Blink       // 7    Negative image
                        // 22   No bold     // 24   No underline        // 25   No blink    // 27   Positive image
    CMD_SCP     = 115,  // CSI s    Save Current Cursor Position
    CMD_RCP     = 117,  // CSI u    Restore Saved Cursor Position
    CMD_DECCRA  = 118,  // Copy Rectangular area CSI Pts; Pls; Pbs; Prs; Pps; Ptd; Pld; Ppd$v
                        // Source rectangle to copy: Pts = Top Line, Pls = Left column, Pbs = bottom line, Prs = right column, Pps = pagegroup number
                        // Destination: Ptd = top line border, Pld = Left column border, Ppd = pagegroup number
    CMD_DECFRA  = 120,  // Fill Rectangular Area CSI Pch;Pt; Pl; Pb; Pr $x
                        // Pch is the ascii value of the fill character
                        // Fill rectangle: Pt = Top Line, Pl = Left column, Pb = bottom line, Pr = right column
    CMD_DECTST  = 121,  // CSI 4;Ps;...;Psy
                        //  0	Test 1, 2, 3 and 6          1	Power-up self test          2	EIA port data loopback test
                        //  3	Printer port loopback test  4	Not used    5	Not used    6	EIA port modem control line loopback test
                        //  7	20 mA port loopback test    8	Not used                    9	Repeat any selected test continuously until power-off or failure
    CMD_DECINVM = 122,  // CSI#*z Invoke Macro (# is the macro id)
    CMD_DECIC   = 125,  // CSI#'}   Insert column in scrolling region from cursor column
    CMD_DECDC   = 126   // CSI #'~  Delete # of columns, shift columns of Righrt side to the left
} ansi_commands;

#define TERM_TOTALPAGES  8

static int16_t init_terminal(uint16_t tileset_id, uint16_t palette_id) {
    int16_t status;
    flip_frame_buffer(TERMINALDISPLAY, false);
    SetExitKey(false); // Disables the ESCAPE key from the RayLib core
    uint16_t display = sys.video.current_virtual;
    uint32_t pagegroup_state = 0;
    uint64_t page_state = GRFE_DEFAULT4;
    uint64_t cell_state = GRFE_DEFAULT4;
    sys.terminal.pagegroup_id = sys.video.current_virtual; // A single pagegroup per Virtual Display
    status = init_pagegroup(sys.terminal.pagegroup_id, (Vector2){64, 28}, TERM_TOTALPAGES, pagegroup_state, page_state, cell_state, tileset_id, palette_id);
    sys.terminal.current_page_id = 0;
    flip_frame_buffer(sys.video.previous_virtual, false);
    return status;
}

// Establish keyboard management / buffer
// Establish mouse management (old x,y / current x,y)
void update_terminal(void) {
// RLAPI void PollInputEvents(void);                             // Register all input events
// RLAPI int GetKeyPressed(void);                                // Get key pressed (keycode), call it multiple times for keys queued
// RLAPI int GetCharPressed(void);                               // Get char pressed (unicode), call it multiple times for chars queued
// RLAPI bool IsMouseButtonPressed(int button);                  // Check if a mouse button has been pressed once
// RLAPI bool IsMouseButtonDown(int button);                     // Check if a mouse button is being pressed
// RLAPI bool IsMouseButtonReleased(int button);                 // Check if a mouse button has been released once
// RLAPI bool IsMouseButtonUp(int button);                       // Check if a mouse button is NOT being pressed

}

void show_terminal(void) {
    // aimed at displaying the terminal pagegroup only
    flip_frame_buffer(TERMINALDISPLAY, false);

    begin_draw(true);
    render_page(sys.terminal.current_page_id);
    end_draw();

    flip_frame_buffer(sys.video.previous_virtual, false);
}

void shutdown_terminal(void) {
}

// ********** T E R M I N A L   S Y S T E M  ***** T E R M I N A L   S Y S T E M  ***** T E R M I N A L   S Y S T E M  ***** E N D
// ********** T E R M I N A L   S Y S T E M  ***** T E R M I N A L   S Y S T E M  ***** T E R M I N A L   S Y S T E M  ***** E N D
// ********** T E R M I N A L   S Y S T E M  ***** T E R M I N A L   S Y S T E M  ***** T E R M I N A L   S Y S T E M  ***** E N D

// *********** D E B U G   S Y S T E M ***** D E B U G   S Y S T E M ***** D E B U G   S Y S T E M ***** B E G I N
// *********** D E B U G   S Y S T E M ***** D E B U G   S Y S T E M ***** D E B U G   S Y S T E M ***** B E G I N
// *********** D E B U G   S Y S T E M ***** D E B U G   S Y S T E M ***** D E B U G   S Y S T E M ***** B E G I N

typedef struct EX_debug {
    bool audio;
    bool video;
    bool game_data;
    bool controls;
    bool fps;
    //bool trace;
} EX_debug;

static EX_debug debug; // = Init_debug();

void set_debug_audio(bool s)    {debug.audio = s;}
void set_debug_video(bool s)    {debug.video = s;}
void set_debug_game_data(bool s){debug.game_data = s;}
void set_debug_controls(bool s) {debug.controls = s;}
void set_debug_fps(bool s)      {debug.fps = s;}
//void set_debug_trace(bool s)    {debug.trace = s;}

void debug_audio_flip()         {debug.audio = !debug.audio;}
void debug_video_flip()         {debug.video = !debug.video;}
void debug_game_data_flip()     {debug.game_data = !debug.game_data;}
void debug_controls_flip()      {debug.controls = !debug.controls;}
void debug_fps_flip()           {debug.fps = !debug.fps;}
//void debug_trace_flip()         {debug.trace = !debug.trace;}

debug_display_option(bool bit, uint16_t x, uint16_t y, uint16_t size, const char* text) {
    if (bit) { DrawRectangle(x, y, size * 12, size, RED); } else { DrawRectangle(x, y, size * 12, size, GREEN); }
    DrawText(TextFormat("%s %s", text, BIT_LITERAL_ON_OFF(bit)), x, y, size, WHITE);
}

void display_keybed(void)  {
    uint16_t keys_in_row = 24;
    for (uint16_t j = 0; j < 7; j++) {
        for (int i = 0; i < keys_in_row; i++) {
            uint16_t key = (j * keys_in_row) + i;
            uint16_t code = kbmap_scancode[key];
            if (code) {
                uint8_t ascii = kbmap_ascii[key];
                if (IsKeyDown(code)) {
                    DrawRectangle(i*64, 20 + j * 64, 64, 64, GREEN);
                    DrawText(TextFormat("%c", (uint8_t)ascii), i * 64, 20 + j * 64, 64, WHITE);
                }
                else {
                    DrawRectangle(i*64, 20 + j * 64, 64, 64, DARKGRAY);
                    DrawText(TextFormat("%c", (uint8_t)ascii), i * 64, 20 + j * 64, 64, GRAY);
                };
            };
        
        };
    };
}

void display_all_res(void) {
    uint16_t count = 0;
    GLFWvidmode* modes = glfwGetVideoModes(glfwGetPrimaryMonitor(), &count);
    uint16_t size = 40;
    uint16_t x = 10;
    uint16_t y = 0;
    Vector2 ratio;
    for (uint16_t i = 0; i < count; i++) {
        ratio = ratio_info((uint16_t)modes[i].width, (uint16_t)modes[i].height);
        uint32_t bits = modes[i].redBits + modes[i].greenBits + modes[i].blueBits;
        DrawText( TextFormat("%ix%i - %ibit - %ifps - %i:%i", (uint16_t)modes[i].width, (uint16_t)modes[i].height, bits, (uint16_t)modes[i].refreshRate, (uint16_t)ratio.x, (uint16_t)ratio.y ),
        x, y, size, DARKGRAY);
        y += size; if (y > (sys.video.screen[sys.video.display_id].y - size)) {x+=768; y=0; };
    };
}

void update_debug(bool show_options) {
    uint16_t size = 80;
    uint16_t x = 0, y = 0;

    if (debug.audio) {
        sys.video.screen_refresh = true;
        if (IsKeyPressed(KEY_ZERO)) change_music_stream(0, 11, true);
        if (IsKeyPressed(KEY_ONE)) change_music_stream(0, 0, true);
        if (IsKeyPressed(KEY_TWO)) change_music_stream(0, 1, true);
        if (IsKeyPressed(KEY_THREE)) change_music_stream(0, 2, true);
        if (IsKeyPressed(KEY_FOUR)) change_music_stream(0, 3, true);
        if (IsKeyPressed(KEY_FIVE)) change_music_stream(0, 4, true);
        if (IsKeyPressed(KEY_SIX)) change_music_stream(0, 5, true);
        if (IsKeyPressed(KEY_SEVEN)) change_music_stream(0, 6, true);
        if (IsKeyPressed(KEY_EIGHT)) change_music_stream(0, 7, true);
        if (IsKeyPressed(KEY_NINE)) change_music_stream(0, 8, true);

        if (IsKeyPressed(KEY_A)) change_music_stream(1, 11, true);
        if (IsKeyPressed(KEY_B)) change_music_stream(1, 12, true);
        if (IsKeyPressed(KEY_C)) change_music_stream(1, 13, true);
        if (IsKeyPressed(KEY_D)) change_music_stream(1, 14, true);
        if (IsKeyPressed(KEY_E)) change_music_stream(1, 15, true);
        if (IsKeyPressed(KEY_F)) change_music_stream(1, 16, true);
        if (IsKeyPressed(KEY_G)) change_music_stream(1, 17, true);
        if (IsKeyPressed(KEY_H)) change_music_stream(1, 18, true);
        if (IsKeyPressed(KEY_I)) change_music_stream(1, 29, true);
        if (IsKeyPressed(KEY_J)) change_music_stream(1, 20, true);
        if (IsKeyPressed(KEY_K)) change_music_stream(1, 21, true);
        if (IsKeyPressed(KEY_L)) change_music_stream(1, 22, true);
        if (IsKeyPressed(KEY_M)) change_music_stream(1, 23, true);
        if (IsKeyPressed(KEY_N)) change_music_stream(1, 24, true);

/*        if (IsKeyPressed(KEY_LEFT)) change_track_playing(-1);
        if (IsKeyPressed(KEY_RIGHT)) change_track_playing(1);
        if (IsKeyPressed(KEY_UP))   change_track_volume(16);
        if (IsKeyPressed(KEY_DOWN)) change_track_volume(-16);
        if (IsKeyPressed(KEY_F7))   jar_xm_flip_comp_exp(sys.asset.music[sys.audio.asset_playing].ctxData);
        if (IsKeyPressed(KEY_F8))   jar_xm_flip_ramping(sys.asset.music[sys.audio.asset_playing].ctxData);
        if (IsKeyPressed(KEY_F9))   jar_xm_flip_linear_interpolation(sys.asset.music[sys.audio.asset_playing].ctxData);
*/
//        jar_xm_debug(sys.asset.music[sys.audio.asset_playing].ctxData);
        show_options = false;
	}

    if (debug.video) {
        sys.video.screen_refresh = true;
        if (IsKeyPressed(KEY_F10))  debug_fps_flip(&debug);
        if (IsKeyDown(KEY_F9))      display_all_res();
        if (IsKeyPressed(KEY_F11))  flip_display_state(FLAG_VSYNC_HINT);
        show_options = false;
    }

    if (debug.game_data) {
        sys.video.screen_refresh = true;
        if (IsKeyPressed(KEY_KP_1)) {ex_canopy.adjustment.y -= 0.002;};
        if (IsKeyPressed(KEY_KP_2)) {ex_canopy.adjustment.y += 0.002;};
        if (IsKeyPressed(KEY_KP_3)) {ex_canopy.pal_idx_cells -= 16; if(ex_canopy.pal_idx_cells < 0) {ex_canopy.pal_idx_cells +=256;};};
        if (IsKeyPressed(KEY_KP_4)) {ex_canopy.pal_idx_cells += 16; if(ex_canopy.pal_idx_cells > 255) {ex_canopy.pal_idx_cells -=256;};};
        if (IsKeyPressed(KEY_KP_5)) {ex_canopy.pal_idx_text -= 16; if(ex_canopy.pal_idx_text < 0) {ex_canopy.pal_idx_text +=256;};};
        if (IsKeyPressed(KEY_KP_6)) {ex_canopy.pal_idx_text += 16; if(ex_canopy.pal_idx_text > 255) {ex_canopy.pal_idx_text -=256;};};

        DrawText(TextFormat("%s", time_stamp()), 1400, 0, 40, DARKGRAY);
        DrawText(TextFormat("FRAMES=%i", (uint32_t)sys.video.frames[sys.video.display_id]), 0, 0, 20, DARKGRAY);
        DrawText(TextFormat("prev_time = %f", (float)sys.video.prev_time[sys.video.display_id]), 0, 0, 40, DARKGRAY);
        DrawText(TextFormat("monitors = %i, current = %i, %s", (uint16_t)GetMonitorCount(), (uint16_t)sys.video.display_id, GetMonitorName(sys.video.display_id)), 0, 60, 20, DARKGRAY);
        DrawText(TextFormat("screen is %ix%i at %i fps", (uint16_t)sys.video.screen[sys.video.display_id].x, (uint16_t)sys.video.screen[sys.video.display_id].y, (uint16_t)sys.video.screen_rate[sys.video.display_id]), 0, 100, 20, DARKGRAY);
        DrawText(TextFormat("screen is %ix%i mm", (uint16_t)GetMonitorPhysicalWidth(sys.video.display_id), (uint16_t)GetMonitorPhysicalHeight(sys.video.display_id)), 0, 120, 20, DARKGRAY);
        DrawText(TextFormat("ex_canopy.adjustment.y = %f", (float)ex_canopy.adjustment.y), 0, 140, 20, DARKGRAY);
        DrawText(TextFormat("ftime = %f and sys.video.frame_time_inc = %f",  (float)sys.video.elapsed_time[sys.video.display_id], (float)sys.video.frame_time_inc[sys.video.display_id]), 0, 160, 20, DARKGRAY);
//        DrawText(TextFormat("text_pause = %i, text_color_flag = %i, text_wave_flag = %i", (int)text_pause, (int)text_color_flag, (int)text_wave_flag), 0, 180, 20, DARKGRAY);
        DrawText(TextFormat("value_anim %i", (float)sys.video.value_anim[sys.video.display_id]), 0, 200, 20, DARKGRAY);
        DrawText(TextFormat("fast_sin = %f", fast_sin(sys.video.frame_time_inc[sys.video.display_id])), 0, 220, 20, DARKGRAY);
        DrawText(TextFormat("     sin = %f", sin(sys.video.frame_time_inc[sys.video.display_id])), 0, 240, 20, DARKGRAY);
        DrawText(TextFormat("fast_cos = %f", fast_cos(sys.video.frame_time_inc[sys.video.display_id])), 0, 260, 20, DARKGRAY);
        DrawText(TextFormat("     cos = %f", cos(sys.video.frame_time_inc[sys.video.display_id])), 0, 280, 20, DARKGRAY);

        uint16_t ys = 20;
        uint16_t y = sys.video.screen[sys.video.display_id].y - ys;
        for (uint64_t i = 0; i < 64; i++) {
            uint64_t bit = (sys.temporal.osc & (uint64_t)(1 <<i));
            Color col;
            if (bit) col = GREEN; else col = ORANGE;
            DrawRectangle(1280 - (i * ys), y, ys, ys, col);
        }
        show_options = false;
    }

    if (debug.controls) {
        sys.video.screen_refresh = true;
        display_keybed();
        show_options = false;
    }

    if (debug.fps) {
        sys.video.screen_refresh = true;
        DrawFPS(sys.video.screen[sys.video.display_id].x - 100, 0);
    }

    if (IsKeyDown(KEY_LEFT_CONTROL)) {
        x = (sys.video.screen[sys.video.display_id].x - 12 * size) * 0.5;
        y = (sys.video.screen[sys.video.display_id].y - 6 * size) * 0.5;
        if (show_options || debug.audio)     { sys.video.screen_refresh = true; y += size; debug_display_option(!debug.audio, x, y, size, "F1 -> AUDIO");};
        if (show_options || debug.video)     { sys.video.screen_refresh = true; y += size; debug_display_option(!debug.video, x, y, size, "F2 -> VIDEO");};
        if (show_options || debug.game_data) { sys.video.screen_refresh = true; y += size; debug_display_option(!debug.game_data, x, y, size, "F3 -> DATA");};
        if (show_options || debug.controls)  { sys.video.screen_refresh = true; y += size; debug_display_option(!debug.controls, x, y, size, "F4 -> CONTROLS");};
        if (permission_valid(PMSN_TRACE))    { sys.video.screen_refresh = true; y += size; debug_display_option(!permission_valid(PMSN_TRACE), x, y, size, "F5 -> TRACE");};
        if (show_options)                    { sys.video.screen_refresh = true; y += size; debug_display_option(0, x, y, size, "F8 -> EXIT");};
        if (IsKeyPressed(KEY_F1)) debug_audio_flip();
        if (IsKeyPressed(KEY_F2)) debug_video_flip();
        if (IsKeyPressed(KEY_F3)) debug_game_data_flip();
        if (IsKeyPressed(KEY_F4)) debug_controls_flip();
        if (IsKeyPressed(KEY_F5)) flip_permission(PMSN_TRACE);
        if (IsKeyPressed(KEY_F8)) commute_to(CTRL_DEINIT);
    }
}

void debug_console_out(const char* message, uint32_t status) {
    if (BITS_TEST(sys.program.pmsnstate, PMSN_TRACE)) {
        TRACELOG(LOG_INFO, "%s | %s | CTRL = 0x%000000008X | PMSN = 0x%000000008X | status = 0x%000000008X <<<<< %s",
        SOFTWARE,
        time_stamp(),
        sys.program.ctrlstate,
        sys.program.pmsnstate,
        status,
        message
        );
    }
}

// *********** D E B U G   S Y S T E M ***** D E B U G   S Y S T E M ***** D E B U G   S Y S T E M ***** E N D
// *********** D E B U G   S Y S T E M ***** D E B U G   S Y S T E M ***** D E B U G   S Y S T E M ***** E N D
// *********** D E B U G   S Y S T E M ***** D E B U G   S Y S T E M ***** D E B U G   S Y S T E M ***** E N D

// ********** G A M E   L O G I C ********** G A M E   L O G I C ********** G A M E   L O G I C ********** B E G I N
// ********** G A M E   L O G I C ********** G A M E   L O G I C ********** G A M E   L O G I C ********** B E G I N
// ********** G A M E   L O G I C ********** G A M E   L O G I C ********** G A M E   L O G I C ********** B E G I N

// SCRIPTING GOAL: Everything in GAME_LOGIC is supposed to be script basaed.
// SCRIPTING GOAL: In the current form it is not but it is simplified in a way to make it mport to scripting in the simplest way possible.
// SCRIPTING GOAL: Once the scripting is completed, we will see how to inject that into the dispatcher with hooks.
void game_init_assets(void) {
    uint16_t id;
	id = load_asset(ASSET_TEXTURE, TITLE_FILENAME, TITLE_FILEEXT, TITLE_DATA, TITLE_FILESIZE, TITLE_PAK);

	id = load_tileset((Vector2){32,32}, TL1_FILENAME, TL1_FILEEXT, TL1_DATA, TL1_FILESIZE, TL1_PAK, 0);
	id = load_tileset((Vector2){16,16}, TL2_FILENAME, TL2_FILEEXT, TL2_DATA, TL2_FILESIZE, TL2_PAK, 0);
	id = load_tileset((Vector2){64,64}, TL5_FILENAME, TL5_FILEEXT, TL5_DATA, TL5_FILESIZE, TL5_PAK, 0);
	id = load_tileset((Vector2){64,64}, TL8_FILENAME, TL8_FILEEXT, TL8_DATA, TL8_FILESIZE, TL8_PAK, 0);
	id = load_tileset((Vector2){32,32}, TL9_FILENAME, TL9_FILEEXT, TL9_DATA, TL9_FILESIZE, TL9_PAK, 0);

	id = load_asset(ASSET_TEXTURE, BALL1_FILENAME, BALL1_FILEEXT, BALL1_DATA, BALL1_FILESIZE, BALL1_PAK);
	id = load_asset(ASSET_TEXTURE, BALL2_FILENAME, BALL2_FILEEXT, BALL2_DATA, BALL2_FILESIZE, BALL2_PAK);
	id = load_asset(ASSET_TEXTURE, BALL3_FILENAME, BALL3_FILEEXT, BALL3_DATA, BALL3_FILESIZE, BALL3_PAK);

	id = load_asset(ASSET_TEXT, NULL, NULL, text_flag1, strlen(text_flag1), 0);
	id = load_asset(ASSET_TEXT, NULL, NULL, text_scroll1, strlen(text_scroll1), 0);
	id = load_asset(ASSET_TEXT, NULL, NULL, text_scroll2, strlen(text_scroll2), 0);
	id = load_asset(ASSET_TEXT, NULL, NULL, text_16hues, strlen(text_16hues), 0);
	id = load_asset(ASSET_TEXT, NULL, NULL, text_yo1, strlen(text_yo1), 0);
	id = load_asset(ASSET_TEXT, NULL, NULL, text_yo2, strlen(text_yo2), 0);
	id = load_asset(ASSET_TEXT, NULL, NULL, text_yo3, strlen(text_yo3), 0);

    uint16_t orderlist[] = {0, 4, 5, 13, 35, 60, 62, 64, 69, 72, 80, 84, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249};
    id = add_track(PRIMARYDISPLAY, 0,                        MUSIC_ALL1_FILENAME, MUSIC_ALL1_FILEEXT, MUSIC_ALL1_DATA, MUSIC_ALL1_FILESIZE, MUSIC_ALL1_PAK, 25, orderlist);
    id = add_track(PRIMARYDISPLAY,   TRACK_SWITCH_IMMEDIATE, MUSIC_ALL1_FILENAME, MUSIC_ALL1_FILEEXT, MUSIC_ALL1_DATA, MUSIC_ALL1_FILESIZE, MUSIC_ALL1_PAK, 25, orderlist);
    id = add_track(UNFOCUSEDDISPLAY, TRACK_RESTART_ON_FOCUS, MUSIC_ALL1_FILENAME, MUSIC_ALL1_FILEEXT, MUSIC_ALL1_DATA, MUSIC_ALL1_FILESIZE, MUSIC_ALL1_PAK, 25, orderlist);
}

particle bubbles[8];

void game_init_title(void) {
	bubbles[0] = init_particle(sys.asset.tex[20], (Vector2) {-32,-32}, (Vector2){1.0,2.0});
	bubbles[1] = init_particle(sys.asset.tex[20], (Vector2) {-32,-32}, (Vector2){1.2,1.5});
	bubbles[2] = init_particle(sys.asset.tex[20], (Vector2) {-32,-32}, (Vector2){1.2,1.2});
	bubbles[3] = init_particle(sys.asset.tex[21], (Vector2) {-32,-32}, (Vector2){1.0,1.0});
	bubbles[4] = init_particle(sys.asset.tex[21], (Vector2) {-32,-32}, (Vector2){0.8,0.8});
	bubbles[5] = init_particle(sys.asset.tex[22], (Vector2) {-32,-32}, (Vector2){0.6,0.5});
	bubbles[6] = init_particle(sys.asset.tex[22], (Vector2) {-32,-32}, (Vector2){0.4,0.3});
	bubbles[7] = init_particle(sys.asset.tex[22], (Vector2) {-32,-32}, (Vector2){0.3,0.2});

    init_scrolltext(0, 25, 11, 5, 2.0, (Vector2){32,10}, (Vector2){0,0}, 255);
    init_scrolltext(1, 24, 11, 5, 3.0, (Vector2){16,6}, (Vector2){32,0}, 255);
    init_scrolltext(2, 27, 11, 5, 2.9, (Vector2){16,5}, (Vector2){32,0}, 32);
    init_scrolltext(3, 28, 11, 5, 2.8, (Vector2){16,4}, (Vector2){32,0}, 64);
    init_scrolltext(4, 29, 11, 5, 2.7, (Vector2){16,3}, (Vector2){32,0}, 96);
    init_scrolltext(5, 27, 11, 5, 2.6, (Vector2){16,2}, (Vector2){32,0}, 96);
    init_scrolltext(6, 28, 11, 5, 2.5, (Vector2){16,1}, (Vector2){32,0}, 64);
    init_scrolltext(7, 27, 11, 5, 2.4, (Vector2){16,0}, (Vector2){32,0}, 32);
    init_scrolltext(8, 26, 11, 5, 0.0, (Vector2){0,6}, (Vector2){32,0}, 255);

    init_canopy(11, 5, (Vector2){36, 12}, (Vector2){8.0f, 8.0f}, 0.0f, 0.0f, (Vector2){0, 0.166}, 41, 57);

    play_track(0, 9, true);
    play_track(1, 11, true);
    play_track(2, 6, true);

	sys.video.frame_time_inc[UNFOCUSEDDISPLAY] = 17.0;
	sys.video.frame_time_inc[PRIMARYDISPLAY] = 102.0;

}

void game_update_title(void) {
    copper_animation(-1, 7, 128, 16, 32, 0.07, (Vector2){0,0}, (Vector3){.4, 1.25, .5},2);
    update_scrolltext(8,32);
    update_scrolltext(2,32);
    update_scrolltext(3,32);
    update_scrolltext(4,32);
    update_scrolltext(5,32);
    update_scrolltext(6,32);
    update_scrolltext(7,32);

    update_particle(&bubbles[7], (Vector2){0.0,-1});
    update_particle(&bubbles[6], (Vector2){0.0,-1});
    update_particle(&bubbles[5], (Vector2){0.0,-1});
    update_particle(&bubbles[4], (Vector2){0.0,-1});
    update_particle(&bubbles[3], (Vector2){0.0,-1});
    copper_animation(1, 7, 128, 16, 32, 0.07, (Vector2){0,0}, (Vector3){.4, 1.25, .5},2);
    update_particle(&bubbles[2], (Vector2){0.0,-1});
    update_marquee_animation(14, 5,(Vector2){330,42}, ex_canopy.transparency, (Vector2){0, (255.0f - ex_canopy.transparency) * 0.5f}, 20, .333);
    update_particle(&bubbles[1], (Vector2){0.0,-1});
    update_canopy(23);

    update_scrolltext(1,32);
    update_scrolltext(0,16);
    update_particle(&bubbles[0], (Vector2){0.0,-1});
}

void game_off_focus_scene(void) {
    draw_colorbar();
    copper_animation(-1, 7, 256, 2, 32, 0.5, (Vector2){0,56}, (Vector3){2, 20, 5},.25);
    update_marquee_animation(14, 5,(Vector2){330,42}, 255.0f, (Vector2){0, 90}, -50, .333);
    copper_animation(1, 7, 256, 2, 32, 0.5, (Vector2){0,56}, (Vector3){2, 20, 5},.25);
}

// ********** G A M E   L O G I C ********** G A M E   L O G I C ********** G A M E   L O G I C ********** E N D
// ********** G A M E   L O G I C ********** G A M E   L O G I C ********** G A M E   L O G I C ********** E N D
// ********** G A M E   L O G I C ********** G A M E   L O G I C ********** G A M E   L O G I C ********** E N D

// ********** R U N T I M E   S Y S T E M  ***** R U N T I M E   S Y S T E M  ***** R U N T I M E   S Y S T E M  ***** B E G I N
// ********** R U N T I M E   S Y S T E M  ***** R U N T I M E   S Y S T E M  ***** R U N T I M E   S Y S T E M  ***** B E G I N
// ********** R U N T I M E   S Y S T E M  ***** R U N T I M E   S Y S T E M  ***** R U N T I M E   S Y S T E M  ***** B E G I N

int16_t init_default_assets() {
    bool status = 0;
    
    sys.asset.total_assets = 0;

    uint16_t id; // when read, id returns -1 from total_assets
    id = init_frame_buffer(TERMINALDISPLAY, (Vector2) {512, 224});
    id = init_frame_buffer(UNFOCUSEDDISPLAY, (Vector2) {512, 224});
    id = init_frame_buffer(MENUDISPLAY, (Vector2) {284, 192});
    id = init_frame_buffer(PRIMARYDISPLAY, (Vector2) {512, 224});

	id = load_palette((Vector2){16,16}, VGACOLORS_FILENAME, VGACOLORS_FILEEXT, VGACOLORS_DATA, VGACOLORS_FILESIZE, VGACOLORS_PAK);
	id = load_palette((Vector2){16,16}, A8COLORS_FILENAME, A8COLORS_FILEEXT, A8COLORS_DATA, A8COLORS_FILESIZE, A8COLORS_PAK);
	id = load_asset(ASSET_ICON, ICON_FILENAME, ICON_FILEEXT, ICON_DATA, ICON_FILESIZE, ICON_PAK);

    id = load_tileset((Vector2){16,2}, A8COPPER_FILENAME, A8COPPER_FILEEXT, A8COPPER_DATA, A8COPPER_FILESIZE, A8COPPER_PAK, 0);
	id = load_tileset((Vector2){16,16}, FONT_ATASCII_FILENAME, FONT_ATASCII_FILEEXT, FONT_ATASCII_DATA, FONT_ATASCII_FILESIZE, FONT_ATASCII_PAK, 0);
	id = load_tileset((Vector2){16,16}, FONT_ATASCII_BIG_FILENAME, FONT_ATASCII_BIG_FILEEXT, FONT_ATASCII_BIG_DATA, FONT_ATASCII_BIG_FILESIZE, FONT_ATASCII_BIG_PAK, 0);
	id = load_tileset((Vector2){16,16}, FONT_VGA_FILENAME, FONT_VGA_FILEEXT, FONT_VGA_DATA, FONT_VGA_FILESIZE, FONT_VGA_PAK, 0);
	sys.asset.basefont_id = load_tileset((Vector2){64,1}, FONT_JJ_FILENAME, FONT_JJ_FILEEXT, FONT_JJ_DATA, FONT_JJ_FILESIZE, FONT_JJ_PAK, 32);
	id = load_tileset((Vector2){96,1}, FONT_OSD_FILENAME, FONT_OSD_FILEEXT, FONT_OSD_DATA, FONT_OSD_FILESIZE, FONT_OSD_PAK, 32);
	sys.asset.lines_id = load_tileset((Vector2){256,1}, LINES_FILENAME, LINES_FILEEXT, LINES_DATA, LINES_FILESIZE, LINES_PAK, 0);
    status = id + 1;
    return status;
}

// establish scripting mechanism.  A script is an asset.  Bootstrap is from a script asset(0) ("rom" program)

//RLAPI void SetExitKey(false);

int16_t init_system(void) {
    debug_console_out("//////// init_system", 0);
    uint32_t status = 0;

    int16_t display_status = init_display_properties(true);
    if (!display_status) add_service(CTRL_VIDEO_INITIALIZED); 
    debug_console_out("---------- VIDEO_INITIALISATION", display_status);
    
    int16_t assets_status = init_default_assets();
    if (assets_status) add_service(CTRL_ASSETS_INITIALIZED);
    debug_console_out("---------- ASSETS_INITIALISATION", assets_status);
    
    int16_t terminal_status = init_terminal(8, 5);
    if (!terminal_status) add_service(CTRL_TERMINAL_INITIALIZED);
    debug_console_out("---------- TERMINAL_INITIALISATION", terminal_status);
    
    int16_t audio_status = init_audio_properties();
    if (!audio_status) add_service(CTRL_AUDIO_INITIALIZED);
    debug_console_out("---------- AUDIO_INITIALISATION", audio_status);

    int16_t temporal_status = init_temporal();
    if (temporal_status) add_service(CTRL_TEMPORAL_INITIALIZED);
    debug_console_out("---------- TEMPORAL_INITIALISATION", temporal_status);
    
    // TODO: init bootstrap script

    //status = display_status | (assets_status << 1) | (terminal_status << 2) | (audio_status << 3);

    return status;
}

static int16_t deinit_system(void) {
    debug_console_out("//////// deinit_system", 0);
    int16_t status = 0;

    status = unload_all_assets();
    remove_service(CTRL_ASSETS_INITIALIZED);
    debug_console_out("---------- ASSETS_UNLOADED", status);

    status = unload_all_pagegroups();
    debug_console_out("---------- PAGES_UNLOADED", status);

    shutdown_terminal();
    remove_service(CTRL_TERMINAL_INITIALIZED);

    deinit_display();
    remove_service(CTRL_VIDEO_INITIALIZED);

    return status;
}

static int16_t update_system(void) {
    int16_t status = 0;
    
    if (sys.program.ctrlstate & CTRL_ASSETS_INITIALIZED) {
        update_assets();
    }
    if (sys.program.ctrlstate & CTRL_TERMINAL_INITIALIZED) {
        update_terminal();
    }
    if (sys.program.ctrlstate & CTRL_VIDEO_INITIALIZED) {
        update_display();
    }
    if (sys.program.ctrlstate & CTRL_AUDIO_INITIALIZED) {
        update_audio();
    }
    if (sys.program.ctrlstate & CTRL_TEMPORAL_INITIALIZED) {
        update_temporal();
    }
    return status;
}

void display_initialize_splash(void) {
//    if (sys.program.ctrlstate & CTRL_INITIALIZE) display_initialize_splash();

    update_system();
}

void manage_program() {
    debug_console_out( control_state_literal(sys.program.ctrlstate & CTRL_SWITCHBOARD_MASK) , 0);

    if (sys.program.ctrlstate & CTRL_OFF_FOCUS)
        game_off_focus_scene();
    else {
//        uint32_t switchboard_state = service_active(CTRL_SWITCHBOARD_MASK);
        switch (service_active(CTRL_SWITCHBOARD_MASK)) {   //(switchboard_state) {
            case CTRL_OFF_FOCUS:
                begin_draw(true);
                game_off_focus_scene();
                end_draw();
            case CTRL_INITIALIZE:
                add_service(CTRL_SHOW_TERMINAL);
                init_system();
                commute_to(CTRL_INIT_TITLE);
                game_init_assets();
                break;
            case CTRL_DEINIT:
                deinit_system();
                commute_to(CTRL_EXIT);
                break;
            case CTRL_EXIT:
                remove_service(CTRL_RUNNING);
                break;
            case CTRL_INIT_TITLE:
                game_init_title();
                commute_to(CTRL_IN_TITLE);
                break;
            case CTRL_IN_TITLE:
                begin_draw(true);
                game_update_title();
                end_draw();
                break;
            case CTRL_INIT_MENU1:
                break;
            case CTRL_IN_MENU1:
                break;
            case CTRL_INIT_MENU2:
                break;
            case CTRL_IN_MENU2:
                break;
            case CTRL_INIT_MENU3:
                break;
            case CTRL_IN_MENU3:
                break;
            case CTRL_INIT_MENU4:
                break;
            case CTRL_IN_MENU4:
                break;
            case CTRL_INIT_GAME:
                break;
            case CTRL_GAME_PLAY:
                break;
            case CTRL_GAME_NEXT:
                break;
            case CTRL_GAME_RESUME:
                break;
            case CTRL_GAMEOVER:
                break;
            case CTRL_GAME_DEATH:
                break;
            default: // nowhere?... only happens on program start
                add_service(CTRL_RUNNING);
                commute_to(CTRL_INITIALIZE);
                break;
        }
    }
}

////////////// ENTRY POINT FROM RUNTIME //////////////
// Once runtime heads here --> stuck till CTRL_END
int process_system(uint32_t ctrlstate, uint32_t pmsnstate, const char* name) {
    if (name > NULL) strcpy(sys.program.name, name); else strcpy(sys.program.name, "_o/");
    set_permission(pmsnstate);
    add_service(ctrlstate);

    debug_console_out(">>>~~~>>> P R O G R A M   S T A R T <<<~~~<<<", 0);

    commute_to(CTRL_INITIALIZE);
    add_service(CTRL_RUNNING);
    while (service_active(CTRL_RUNNING)) {
        //debug_console_out("MAIN LOOP_______BEGIN", 0);

        manage_program(); // mostly for the game program display and whereabouts, as well as initialize and exit of the aopplication

        if (service_active(CTRL_VIDEO_INITIALIZED)) {
            if (service_active(CTRL_IN_GAME))  {
                // possibly health information, lives left, score etc... (HUD)
            }
            if (service_active(CTRL_GAME_PAUSED)) {
            // something special happening while game is paused
            // DISPLAY PAUSE MESSAGE
            }
            if (IsKeyDown(KEY_RIGHT_CONTROL)) {
                if (sys.program.ctrlstate & CTRL_SHOW_TERMINAL) {
                    show_terminal();
                }
            }
            update_system();
        }
        //debug_console_out("MAIN LOOP_______END", 0);
    }
    return sys.program.status;
}

// ********** R U N T I M E   S Y S T E M  ***** R U N T I M E   S Y S T E M  ***** R U N T I M E   S Y S T E M  ***** E N D
// ********** R U N T I M E   S Y S T E M  ***** R U N T I M E   S Y S T E M  ***** R U N T I M E   S Y S T E M  ***** E N D
// ********** R U N T I M E   S Y S T E M  ***** R U N T I M E   S Y S T E M  ***** R U N T I M E   S Y S T E M  ***** E N D

#ifdef __cplusplus
}
#endif
