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

//#include <windows.h> 
#include <stdlib.h>         // header of the general purpose standard library
#include <xmmintrin.h>      // x86 cpu architecture dependency
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

#ifdef __cplusplus // Calling C code from C++
extern "C" { 
#endif

#define SUPPORT_TRACELOG 1
#include "raylib.h"          // works on version 3.8 development
#include "utils.h"           // Required for: TRACELOG macros
#include "raymath.h"
#include "rlgl.h"            // raylib OpenGL abstraction to OpenGL 1.1, 3.3 or ES2
#include <GLFW/glfw3.h>

// **************************************************************************************** U T I L I T Y   M A C R O S   &   F U N C T I O N S

#define __forceinline __attribute__((always_inline))    // non microsoft forced inline

#define BITS_ON(a,b)    (a |= (b))
#define BITS_OFF(a,b)   (a &= ~(b))
#define BITS_INIT(a, b) (a = (b))
#define BITS_FLIP(a, b) (a ^= (b))
#define BITS_TEST(a, b) (((a & (b)) == (b)) ? 1 : 0)
#define BITS_FILTER(a, b) (a & (b))

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
static uint16_t stdio_pipe[2];
*/

//void prepare_stdio(void) {
//    uint32_t flags = fcntl(stdio_pipe[0], F_GETFL);
//    flags |= O_NONBLOCK;
//    fcntl(stdio_pipe[0], F_SETFL, flags);
//};

//prepare_stdio(); 

//    enum { STATE_WAITING, STATE_LOADING, STATE_FINISHED } state = STATE_WAITING;

// C11: Sets the first n bytes starting at dest to the specified value, but maximal dmax bytes.
//#define EX_MEMSET(void *dest, rsize_t dmax, uint16_t value, rsize_t n)   memset_s(void *dest, rsize_t dmax, uint16_t value, rsize_t n)

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

__forceinline float Rand(float a) {	return (float)rand()/(float)(RAND_MAX/a);}

__forceinline float fast_sin(double x) {
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

__forceinline float fast_cos(double x) {
    return fast_sin(x + HALF_PI);
}

__forceinline double dfast_sin(double x) {
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

__forceinline double dfast_cos(double x) {
    return fast_sin(x + HALF_PI);
}

__forceinline float ffast_fisr(float value) {  /* FISR - PULLED FROM QUAKE SOURCE - DEPRECATED */
	union { int32_t i; float f; } t;
	float half = value * 0.5f;
	t.f = value;
	t.i = 0x5f375a86 - (t.i >> 1);
	t.f = t.f * (1.5f - (half * t.f * t.f)); /* 1st iteration */
//	t.f = t.f * (1.5f - (half * t.f * t.f)); /* 2nd iteration, adds more precision */
	return t.f;
}

__forceinline float ffast_rsqrt(const float f) {
    __m128 temp = _mm_set_ss(f);
    temp = _mm_rsqrt_ss(temp);
    return _mm_cvtss_f32(temp);
}

__forceinline float ffast_ceil(float x)  { return (float)((x < 0) ? (int32_t)x : ((int32_t)x)+1); }
__forceinline float ffast_floor(float x) { return (float)((x >= 0.0f) ? (int32_t)x : (int32_t)(x-0.9999999999999999f)); }
__forceinline float ffast_round(float x) { return (float)((x >= 0.0f) ? ffast_floor(x + 0.5f) : ffast_ceil(x - 0.5f)); }
__forceinline float ffast_remainder(float x, float y) {	return x - (ffast_round(x/y)*y);}
__forceinline float ffast_copysign(float x, float y) {
	int32_t ix, iy;
	ix = *(int32_t *)&x;
	iy = *(int32_t *)&y;
	ix &= 0x7fffffff;
	ix |= iy & 0x80000000;
	return *(float *)&ix;
}

// use type punning instead of pointer arithmatics, to require proper alignment
__forceinline float ffast_abs(float f) {
    if (sizeof(float) == sizeof(uint32_t)) {     // optimizer will optimize away the `if` statement and the library call
        union { float f; uint32_t i; } u;
        u.f = f;
        u.i &= 0x7fffffff;
        return u.f;
    }
    return ABS(f);
}

__forceinline float ffast_mod(float x, float y) {
	float result;
	y = ffast_abs(y);
	result = ffast_remainder(ffast_abs(x), y);
	if (SIGN(result)) result += y;
	return ffast_copysign(result, x);
}

__forceinline float ffast_tan(float radians) {
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

__forceinline float ffast_atan(float a)	{
    float u  = a*a;
    float u2 = u*u;
    float u3 = u2*u;
    float u4 = u3*u;
    float f  = 1.0f + 0.33288950512027f * u - 0.08467922817644f * u2 + 0.03252232640125f * u3 - 0.00749305860992f * u4;
    return a/f;
}

__forceinline int32_t gcdl(int32_t a, int32_t b) {
    if (a == 0) return b; else if (b == 0) return a;
    if (a < b) return gcdl(a, b % a); else return gcdl(b, a % b);
}

__forceinline int32_t gcdi(int32_t a, int32_t b) {
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
    int16_t luma = val & 15;
    int16_t crlv = chroma ? 50 : 0;
 
    float phase = ((chroma - 1.) * 25. - 58.) * (2. * PI / 360.);

    float y = 255 * (luma + 1.) / 16.;
    float i = crlv * cos(phase);
    float q = crlv * sin(phase);

    float r = (y + 0.956294832320893995 * i + 0.621025125444728741 * q);
    float g = (y - 0.2721214740839773195 * i - 0.6473809535176157223 * q);
    float b = (y - 1.106989908567128216 * i + 1.704614975498829329 * q);

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

void datetime_literal(char *datetime) {
//    char *datetime = (char *)malloc(20);
    time_t ltime = time(NULL);
    struct tm *tm;
    tm = localtime(&ltime);
    sprintf(datetime,"%04d/%02d/%02d-%02d:%02d:%02d", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
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

// SET buffer aspect ratio
// RLAPI void rlOrtho(double left, double right, double bottom, double top, double znear, double zfar);

static Vector2 ratio_info(float x, float y) {
    Vector2 p;

    float gcd_res = gcdi(x,y);
    p.x = x / gcd_res;
    p.y = y / gcd_res;
    return p;
}


// **************************************************************************************** R A Y L I B   E X T E N S I O N S

// draw Textured Quad
void DrawQuadSprite ( Texture texture , Vector2 position, Vector2 scale, Color color) {
    // expand concept, think about particles, player character, etc... color blending opotions, priority system... Use DrawTexturePro2 for skew, etc...
	DrawTexturePro ( texture ,
    (Rectangle) { 0, 0, texture.width * scale.x, texture.height * scale.y },
    (Rectangle) { position.x, position.y, texture.width * scale.x, texture.height * scale.y },
    (Vector2) { 0,0 } , 0 , color );
}

void DrawRectanglePro2(Rectangle rec, Vector2 origin, Vector2 skew, float rotation, Color color[4]) {
    rlCheckRenderBatchLimit(4);

    const static inline Texture   texShapes = { 1, 1, 1, 1, 7 };
    const static inline Rectangle texShapesRec = { 0, 0, 1, 1 };

    skew = (Vector2){skew.x * rec.width, skew.y * rec.height};
    Vector2 topLeft = { 0 }, topRight = { 0 }, bottomLeft = { 0 }, bottomRight = { 0 };

    if (rotation == 0.0f) {
        float x = rec.x - origin.x;
        float y = rec.y - origin.y;
        topLeft = (Vector2){ x, y };
        topRight = (Vector2){ x + rec.width, y };
        bottomLeft = (Vector2){ x, y + rec.height };
        bottomRight = (Vector2){ x + rec.width, y + rec.height };
    } else {
        float sinRotation = sinf(rotation * DEG2RAD);
        float cosRotation = cosf(rotation * DEG2RAD);
        float x = rec.x;
        float y = rec.y;
        float dx = -origin.x;
        float dy = -origin.y;
        topLeft.x       = x + dx * cosRotation - dy * sinRotation;
        topLeft.y       = y + dx * sinRotation + dy * cosRotation;
        topRight.x      = x + (dx + rec.width) * cosRotation - dy * sinRotation;
        topRight.y      = y + (dx + rec.width) * sinRotation + dy * cosRotation;
        bottomLeft.x    = x + dx * cosRotation - (dy + rec.height) * sinRotation;
        bottomLeft.y    = y + dx * sinRotation + (dy + rec.height) * cosRotation;
        bottomRight.x   = x + (dx + rec.width) * cosRotation - (dy + rec.height) * sinRotation;
        bottomRight.y   = y + (dx + rec.width) * sinRotation + (dy + rec.height) * cosRotation;
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

// NOTE: origin is relative to destination rectangle size
void DrawTexturePro2 (Texture texture, Rectangle source, Rectangle dest, Vector2 origin, Vector2 skew, float rotation, Color color[4]) {
    if (texture.id > 0) {
        rlCheckRenderBatchLimit(4);     // Make sure there is enough free space on the batch buffer
        float width = (float)texture.width;
        float height = (float)texture.height;
        bool flipX = false;
        if (source.width < 0) { flipX = true; source.width *= -1; }
        if (source.height < 0) source.y -= source.height;

        skew = (Vector2){skew.x * dest.width, skew.y * dest.height};
        Vector2 topLeft = { 0 }, topRight = { 0 }, bottomLeft = { 0 }, bottomRight = { 0 };

        if (rotation == 0.0f) { // do not calculate rotation
            float x = dest.x - origin.x;
            float y = dest.y - origin.y;
            topLeft = (Vector2){ x, y };
            topRight = (Vector2){ x + dest.width, y };
            bottomLeft = (Vector2){ x, y + dest.height };
            bottomRight = (Vector2){ x + dest.width, y + dest.height };
        } else {  // calculate rotation
            float sinRotation = sinf(rotation * DEG2RAD);
            float cosRotation = cosf(rotation * DEG2RAD);
            float x = dest.x;
            float y = dest.y;
            float dx = -origin.x;
            float dy = -origin.y;
            topLeft.x       = x + dx * cosRotation - dy * sinRotation;
            topLeft.y       = y + dx * sinRotation + dy * cosRotation;
            topRight.x      = x + (dx + dest.width) * cosRotation - dy * sinRotation;
            topRight.y      = y + (dx + dest.width) * sinRotation + dy * cosRotation;
            bottomLeft.x    = x + dx * cosRotation - (dy + dest.height) * sinRotation;
            bottomLeft.y    = y + dx * sinRotation + (dy + dest.height) * cosRotation;
            bottomRight.x   = x + (dx + dest.width) * cosRotation - (dy + dest.height) * sinRotation;
            bottomRight.y   = y + (dx + dest.width) * sinRotation + (dy + dest.height) * cosRotation;
        }

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
#define NAMELENGTH_MAX          80
#define GRID_MAX_CELLS          65536
#define GRID_MAX_CANVASGROUPS   5
#define GRID_MAX_CANVASES       16
#define CANVAS_MAX_PALETTES     8
#define CANVAS_MAX_ASSETS       8


typedef struct cell_s {
    uint64_t    state;                      // all flags for cell
    uint16_t    value;                      // value of cell
    uint8_t     lines;                      // lines feature
    uint16_t    asset_id;                   // Each cell can point to a different tileset
    uint16_t    cycle_id;                   // cell animation sequence number
    uint16_t    palette_id;                 // color palette used for whole canvas
    uint16_t    colorfg_id;                 // palette index color for cell
    uint16_t    colorfg_cycle_id;           // color cycle index for cell
    uint16_t    colorbg_id;                 // palette index color for cell background
    uint16_t    colorbg_cycle_id;           // color cycle index for cell background
    uint16_t    colorln_id;                 // palette index color for cell lines
    uint16_t    colorln_cycle_id;           // color cycle index for cell lines
    Vector2     offset;                     // displacement from top left (x,y)
    Vector2     skew;                       // horizontal and vertical skew
    Vector2     scale;                      // (x,y) cell scale
    Vector2     scale_speed;                // (x,y) cell scale speed
    Vector2     scroll_speed;               // (x,y) cell scroll speed
    float       angle;                      // degree of angle used to rotate the cell
    float       fg_brightness;              // foreground brightness (values 0...1 divides, values 1 to 255 multiply)
    float       bg_brightness;              // background brightness (values 0...1 divides, values 1 to 255 multiply)
    uint8_t     alpha;                      // transparency
    Color       color_mask;                 // RGBA color mask of cell
    Color       shadow_mask;                // shadow RGBA mask
} EX_cell;

typedef struct canvas_s {
    char        name[NAMELENGTH_MAX + 1];
    uint64_t    state;                      // all flags for grid
    uint16_t    asset_id[CANVAS_MAX_ASSETS];// tilset used for this canvas
    uint16_t    default_asset_id;           // tilset used for this canvas
    Vector2     size;                       // total cells x and y
    Vector2     default_tilesize;           
    uint16_t    palette_id[CANVAS_MAX_PALETTES];     // color palette used for whole canvas
    uint16_t    default_palette_id;         // color palette used for whole canvas
    uint16_t    default_colorfg_id;         // palette index color for cell
    uint16_t    default_colorbg_id;         // palette index color for cell background
    uint16_t    default_colorln_id;         // palette index color for cell lines
    Vector2     offset;                     // displacement from top left (x,y)
    Vector2     displace[4];                // cell corner displacement (x,y)
    Vector2     scale;                      // (x,y) cell scale
    Vector2     scale_speed;                // (x,y) cell scale speed
    Vector2     scroll_speed;               // canvas scroll speed (x,y)
    float       angle;                      // degree of angle to rotate canvas
    float       fg_brightness;              // foreground brightness (values 0...1 divides, values 1 to 255 multiply)
    float       bg_brightness;              // background brightness (values 0...1 divides, values 1 to 255 multiply)
    uint8_t     alpha;                      // transparency
    Vector2     shadow;                     // shadow corner displacement (x,y)
    Vector2     shadow_displace[4];         // shadow corners displacement (x,y)
    Color       color_mask;                 // RGBA color mask of canvas
    Color       shadow_mask;                // shadow RGBA mask
    EX_cell     mask;                       // used for when replicating
    uint32_t    cell_count;
    EX_cell*    cell;                       // could be NULL
} EX_canvas;

typedef enum {
    CVGP_DELETE              = 0b10000000000000000000000000000000,
    CVGP_UPDATE              = 0b01000000000000000000000000000000,
    CVGP_INITIALIZED         = 0b00000000000000000000000000000001,
// to be determined
} canvasgroup_states;

typedef struct canvasgroup_s {
    char        name[NAMELENGTH_MAX + 1];
    uint32_t    state;
    uint16_t    default_asset_id;
    uint16_t    default_palette_id;         // color palette used for whole canvas
    uint16_t    default_colorfg_id;         // palette index color for cell
    uint16_t    default_colorbg_id;         // palette index color for cell background
    uint16_t    default_colorln_id;         // palette index color for cell lines
    uint16_t    canvas_count;               // total number of canvases
    EX_canvas*  canvas;                     // could be NULL (if not initialized)    
} EX_canvasgroup;

// **************************************************************************************** A S S E T   S T R U C T U R E S
#define MAXASSETS           1024
#define MAXPALETTECOLORS    4096

typedef struct tileset_s {
    Vector2     tilesize;                   // Tile size
    Vector2     count;                      // number of tiles (x, y)
    Texture     tex;                        // Characters texture atlas
    uint32_t    total;                      // Number of Tiles
    uint16_t    ascii_start;                // if tileset if character font, identifies ascii code first tile
} EX_tileset;

typedef struct asset_s {
    char        name[NAMELENGTH_MAX + 1];
    uint32_t    total_assets;
    uint16_t    lines_id;
    uint16_t    basefont_id;

    uint32_t    state[MAXASSETS];
    uint32_t    dead_assets[MAXASSETS];
    uint32_t    asset_type[MAXASSETS];
    uint32_t    data_size[MAXASSETS];       // storage space size in bytes

    Image       img[MAXASSETS];             // storage space for unpacked images
    Texture     tex[MAXASSETS];             // storage space for textures
    Color       *palette[MAXASSETS];        // storage space for indexed colors
    uint32_t    palette_colors[MAXASSETS];  // total number of colors in palette
    EX_tileset  tileset[MAXASSETS];         // storage space for texture based fonts
    RenderTexture framebuffer[MAXASSETS];   // storage space for frame buffer
    Font        font[MAXASSETS];            // storage space for texture based fonts
    Music       music[MAXASSETS];           // storage space for unpacked music
    Shader      shader[MAXASSETS];          // storage space for shaders
    uint8_t     *data[MAXASSETS];           // storage space for any text, data, JSON, LUA ...
} EX_asset;

// **************************************************************************************** A U D I O   S T R U C T U R E S

#define MAXAUDIOTRACKS  10
#define MAXORDERS       50

typedef struct track_s {
    bool        is_playing;                 // 
    uint32_t    state;                      // 
    uint16_t    asset;                      // 
    uint16_t    virtual_display;            // 
    float       volume;                     // 
    float       dest_volume;                // TO DO
    float       slide_speed;                // TO DO
    uint16_t    order_playing;              // 
    uint16_t    total_orders;               // 
    uint16_t    order[MAXORDERS];           // 
} EX_track;

typedef struct audio_s {
    uint16_t    total_tracks;               // 
    float       global_volume;              // 
    EX_track    track[MAXAUDIOTRACKS];      // 
} EX_audio;

// **************************************************************************************** V I D E O   S T R U C T U R E S

#define MAXDISPLAYS         5
#define PRIMARYDISPLAY      0
#define MENUDISPLAY         1
#define INGAMEDISPLAY       2
#define UNFOCUSEDDISPLAY    3
#define TERMINALDISPLAY     4

typedef struct screenspace_s {
    uint32_t    state;                          // virtual display state
    Vector2     size;                           // framebuffer resolution (x, y)
    Vector2     offset;                         // Windows Display Resolution (x, y)
    uint32_t    refresh_rate;                   // screen refresh rate
    uint32_t    fps;                            // frames per second
    uint32_t    frames;                         // number of game frame elasped since initialisation
    double      prev_time;                      // keep track of time to grab delta
    double      elapsed_time_nofocus;           // elapsed time since nofocus
    double      elapsed_time;                   // elapsed time in milliseconds since last frame refresh
    float       elapsed_time_var;               // elapsed time in milliseconds since last frame refresh (with ratio)
    float       elapsed_time_var_ratio;         // multiplication factor
    float       value_anim;                     // space for animated controls (to be elaborated)
    float       frame_time;                     // 
    float       frame_time_inc;                 // 
    uint16_t    asset_id;                       // framebuffer asset number
} EX_screenspace;

typedef struct video_s {
    uint32_t    state;                          // 
    Vector2     screen;                         // Windows Display Resolution (x, y)
    uint32_t    windowstate_normal;             // screen window state in normal mode
    uint32_t    windowstate_paused;             // screen window state when game is paused
    uint16_t    display_id;                     // screen currently used
    bool        screen_refresh;                 // 
    bool        window_focus;                   // last state of window focus (true = in applicatioo, false = outside of application)

    uint16_t    current_virtual;                // virtual display currently used
    uint16_t    previous_virtual;               // virtual display previously used
    EX_screenspace vscreen[MAXDISPLAYS];        // 
    EX_canvasgroup canvasgroup[MAXDISPLAYS];    // canvasgroup data
} EX_video;


// **************************************************************************************** T E R M I N A L   S T R U C T U R E S

#define TERM_MAXPAGES       8
#define TERM_MAXFONTS       8
#define TERM_MAXPALETTES    8
#define IOBUFFERSIZE        65536
#define MAXTOKENS           1024

typedef struct page_s {
    uint32_t    state;                              // terminal page state
    Vector2     cursor_home_position;               // position when cursor home
    Vector2     cursor_previous_position;           // previous cursor position
    Vector2     cursor_position;                    // current cursor position
    uint16_t    default_font;                       // default font selection (not asset_id)
    uint16_t    previous_font;                      // previous font selection (not asset_id)
    uint16_t    default_palette;                    // default palette selection (not asset_id)
    uint16_t    previous_palette;                   // previous palette selection (not asset_id)
    uint16_t    default_colorfg_id;                 // 
    uint16_t    default_colorbg_id;                 // 
    uint16_t    previous_colorbg_id;                // 
    uint16_t    previous_colorfg_id;                // 
    uint16_t    colorbg_id, colorfg_id;             // 
    uint16_t    text_blink_rate;                    // 
    uint16_t    margin_left, margin_right, margin_top, margin_bottom; // page margin values for all sides
    Vector2     size;                               // Page size (in character count)
    Vector2     page_split;                         // Horizontal and vertical page split position (usually center)
    EX_cell     cell;                               // active cell template for the page
    EX_cell     mousecursor;                        // mouse cursor
    EX_cell     keycursor;                          // key cursor
} EX_page;

typedef struct token_s {
    uint16_t    position;                           // 
    uint16_t    len;                                // 
} EX_token;

typedef struct terminal_s {
    uint32_t    state;                              // 
    uint16_t    canvasgroup_id;                     // Where all terminal canvases reside
    uint16_t    previous_page_id;
    uint16_t    page_id;                            // 
    uint16_t    font_id[TERM_MAXFONTS];             // font to font_id cross reference
    uint16_t    fonts;                              // number of fonts loaded
    uint16_t    palette_id[TERM_MAXPALETTES];       // palette to palette_id cross reference
    uint16_t    palettes;                           // number of palettes loaded

    EX_page     page[TERM_MAXPAGES];                // space for all terminal pages
    uint32_t    screensaver_delay;                  // time in seconds before scerensaver kicks in
    uint32_t    screensaver_count;                  // countdown before screensaver takes effect

    uint8_t     iobuffer[IOBUFFERSIZE];             // 
    uint32_t    read_position;                      // 
    uint32_t    write_position;                     // 
    EX_token    token[MAXTOKENS];                   // 
    uint16_t    token_count;                        // 
    EX_canvas   canvas_template;                    // active canvas template for the terminal
} EX_terminal;


// **************************************************************************************** A P P L I C A T I O N   S T R U C T U R E S

// The heartbeat of the system flows through these 64 oscillator states
// With this comes a period table spanning from slow 8 second up to fast millisecond level state changes
// With this a function to poll oscillator states
#define TEMPORAL_ARRAY_SIZE 64

typedef struct temportal_s {
    char        datetime[20];                       // 
    double      period_table[TEMPORAL_ARRAY_SIZE];  // time slice period per oscillator
    uint64_t    prev_osc;                           // previous oscillator bits
    uint64_t    osc;                                // all oscillator bits
    uint64_t    osc_count[TEMPORAL_ARRAY_SIZE];     // number of cycles since start of program (counts are on full cycles)
    double      osc_next_frame[TEMPORAL_ARRAY_SIZE];// trigger for oscillator state update (calculated following frame)
} EX_temporal;

typedef struct EX_player {
// to be determined
} EX_player;

typedef struct EX_game {
    EX_player player;
// to be determined
} EX_game;

typedef enum {
    CTRL_DEINIT                 = 0b10000000000000000000000000000000, // 
    CTRL_INITIALIZE             = 0b01000000000000000000000000000000, // 
    CTRL_EXIT                   = 0b00100000000000000000000000000000, // 
    CTRL_INIT_TITLE             = 0b00010000000000000000000000000000, // 
    CTRL_IN_TITLE               = 0b00001000000000000000000000000000, // 
    CTRL_INIT_MENU1             = 0b00000100000000000000000000000000, // 
    CTRL_IN_MENU1               = 0b00000010000000000000000000000000, // 
    CTRL_INIT_MENU2             = 0b00000001000000000000000000000000, // 
    CTRL_IN_MENU2               = 0b00000000100000000000000000000000, // 
    CTRL_INIT_MENU3             = 0b00000000010000000000000000000000, // 
    CTRL_IN_MENU3               = 0b00000000001000000000000000000000, // 
    CTRL_INIT_MENU4             = 0b00000000000100000000000000000000, // 
    CTRL_IN_MENU4               = 0b00000000000010000000000000000000, // 
    CTRL_GAME_RESUME            = 0b00000000000001000000000000000000, // 
    CTRL_GAME_PLAY              = 0b00000000000000100000000000000000, // 
    CTRL_INIT_GAME              = 0b00000000000000010000000000000000, // 
    CTRL_GAME_NEXT              = 0b00000000000000001000000000000000, // 
    CTRL_GAMEOVER               = 0b00000000000000000100000000000000, // 
    CTRL_GAME_DEATH             = 0b00000000000000000010000000000000, // 
    CTRL_BOOTSTRAP_TRACE        = 0b00000000000000000001000000000000, // 
    CTRL_OFF_FOCUS              = 0b00000000000000000000100000000000, // 
    CTRL_DEBUG                  = 0b00000000000000000000010000000000, // 
    CTRL_TERMINAL               = 0b00000000000000000000001000000000, // 
    CTRL_GAME_PAUSED            = 0b00000000000000000000000100000000, // 
    CTRL_IN_GAME                = 0b00000000000000000000000010000000, // 
    CTRL_RUNNING                = 0b00000000000000000000000001000000, // 
    CTRL_TEMPORAL_INITIALIZED   = 0b00000000000000000000000000100000, // 
    CTRL_AUDIO_INITIALIZED      = 0b00000000000000000000000000010000, // 
    CTRL_TERMINAL_INITIALIZED   = 0b00000000000000000000000000001000, // 
    CTRL_ASSETS_INITIALIZED     = 0b00000000000000000000000000000100, // 
    CTRL_VIDEO_INITIALIZED      = 0b00000000000000000000000000000010, // 
    CTRL_DEBUG_INITIALIZED      = 0b00000000000000000000000000000001, // 
    CTRL_SWITCHBOARD_MASK       = 0b11111111111111111110000000000000, // to filter out base states
    CTRL_SERVICES_MASK          = 0b00000000000000000001111111111111, // to filter out switchboard states
    CTRL_TERMINAL_SERVICE_MASK  = 0b00000000000000000000001000001000, // 
    CTRL_DEBUG_SERVICE_MASK     = 0b00000000000000000000010000000001, // 
    CTRL_NULL                   = 0b00000000000000000000000000000000  // in case that happens... (should never)
} control_state;

const char* control_state_literal(uint32_t state) {
    switch (state) {
    case CTRL_DEINIT:               return "SWITCHBOARD: CTRL_DEINIT";
    case CTRL_INITIALIZE:           return "SWITCHBOARD: CTRL_INITIALIZE";
    case CTRL_EXIT:                 return "SWITCHBOARD: CTRL_EXIT";
    case CTRL_INIT_TITLE:           return "SWITCHBOARD: CTRL_INIT_TITLE";
    case CTRL_IN_TITLE:             return "SWITCHBOARD: CTRL_IN_TITLE";
    case CTRL_INIT_MENU1:           return "SWITCHBOARD: CTRL_INIT_MENU1";
    case CTRL_IN_MENU1:             return "SWITCHBOARD: CTRL_IN_MENU1";
    case CTRL_INIT_MENU2:           return "SWITCHBOARD: CTRL_INIT_MENU2";
    case CTRL_IN_MENU2:             return "SWITCHBOARD: CTRL_IN_MENU2";
    case CTRL_INIT_MENU3:           return "SWITCHBOARD: CTRL_INIT_MENU3";
    case CTRL_IN_MENU3:             return "SWITCHBOARD: CTRL_IN_MENU3";
    case CTRL_INIT_MENU4:           return "SWITCHBOARD: CTRL_INIT_MENU4";
    case CTRL_IN_MENU4:             return "SWITCHBOARD: CTRL_IN_MENU4";
    case CTRL_GAME_RESUME:          return "SWITCHBOARD: CTRL_GAME_RESUME";
    case CTRL_GAME_PLAY:            return "SWITCHBOARD: CTRL_GAME_PLAY";
    case CTRL_INIT_GAME:            return "SWITCHBOARD: CTRL_INIT_GAME";
    case CTRL_GAME_NEXT:            return "SWITCHBOARD: CTRL_GAME_NEXT";
    case CTRL_GAMEOVER:             return "SWITCHBOARD: CTRL_GAMEOVER";
    case CTRL_GAME_DEATH:           return "SWITCHBOARD: CTRL_GAME_DEATH";
    case CTRL_BOOTSTRAP_TRACE:      return "SWITCHBOARD: CTRL_BOOTSTRAP_TRACE";
    case CTRL_OFF_FOCUS:            return "BASE STATES: CTRL_OFF_FOCUS";
    case CTRL_DEBUG:                return "BASE STATES: CTRL_DEBUG";
    case CTRL_TERMINAL:             return "BASE STATES: CTRL_TERMINAL";
    case CTRL_GAME_PAUSED:          return "BASE STATES: CTRL_GAME_PAUSED";
    case CTRL_IN_GAME:              return "BASE STATES: CTRL_IN_GAME";
    case CTRL_RUNNING:              return "BASE STATES: CTRL_RUNNING";
    case CTRL_TEMPORAL_INITIALIZED: return "BASE STATES: CTRL_TEMPORAL_INITIALIZED";
    case CTRL_AUDIO_INITIALIZED:    return "BASE STATES: CTRL_AUDIO_INITIALIZED";
    case CTRL_TERMINAL_INITIALIZED: return "BASE STATES: CTRL_TERMINAL_INITIALIZED";
    case CTRL_ASSETS_INITIALIZED:   return "BASE STATES: CTRL_ASSETS_INITIALIZED";
    case CTRL_VIDEO_INITIALIZED:    return "BASE STATES: CTRL_VIDEO_INITIALIZED";
    case CTRL_DEBUG_INITIALIZED:    return "BASE STATES: CTRL_DEBUG_INITIALIZED";
    default: return NULL;
    }
}

typedef enum {
    PMSN_INFINITE_LIVES     = 0b10000000000000000000000000000000, // 
    PMSN_INFINITE_POWER     = 0b01000000000000000000000000000000, // 
    PMSN_INFINITE_TIME      = 0b00100000000000000000000000000000, // 
    PMSN_NO_COLLISION       = 0b00010000000000000000000000000000, // 
    PMSN_POWERUPS           = 0b00001000000000000000000000000000, // 
    PMSN_NAVIGATE_LEVELS    = 0b00000100000000000000000000000000, // 
    PMSN_DEATH              = 0b00000010000000000000000000000000, // 
    PMSN_SUMMON             = 0b00000001000000000000000000000000, // 
    PMSN_END_GAME           = 0b00000000100000000000000000000000, // 
    PMSN_BENCHMARK          = 0b00000000000001000000000000000000, // 
    PMSN_ATTRACT            = 0b00000000000000100000000000000000, // 
    PMSN_DEBUG_TERMINAL     = 0b00000000000000010000000000000000, // 
    PMSN_DEBUG_TRACE        = 0b00000000000000001000000000000000, // 
    PMSN_DEBUG_AUDIO        = 0b00000000000000000100000000000000, // 
    PMSN_DEBUG_FPS          = 0b00000000000000000010000000000000, // 
    PMSN_DEBUG_VIDEO        = 0b00000000000000000001000000000000, // 
    PMSN_DEBUG_CONTROLS     = 0b00000000000000000000100000000000, // 
    PMSN_DEBUG_DATA         = 0b00000000000000000000010000000000, // 
    PMSN_DEBUG_EXIT         = 0b00000000000000000000001000000000, // 
    PMSN_R9                 = 0b00000000000000000000000100000000, // 
    PMSN_R8                 = 0b00000000000000000000000010000000, // 
    PMSN_R7                 = 0b00000000000000000000000001000000, // 
    PMSN_EDITOR_ADMIN       = 0b00000000000000000000000000100000, // 
    PMSN_EDITOR_USER        = 0b00000000000000000000000000010000, // 
    PMSN_TERMINAL_ADMIN     = 0b00000000000000000000000000001000, // 
    PMSN_TERMINAL_USER      = 0b00000000000000000000000000000100, // 
    PMSN_R2                 = 0b00000000000000000000000000000010, // 
    PMSN_DEBUG              = 0b00000000000000000000000000000001, // 
    PMSN_OFF                = 0b00000000000000000000000000000000, // 
    PMSN_GAME_MASK          = 0b11111111111111100000000000000000, // 
    PMSN_DEBUG_OPTIONS      = 0b00000000000000011111111000111101, // 
    PMSN_GODMODE_MASK       = 0b11111111111111111111111111111111  // 
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
    case PMSN_DEBUG_TERMINAL:   return "PMSN_DEBUG_TERMINAL";
    case PMSN_DEBUG_TRACE:      return "PMSN_DEBUG_TRACE";
    case PMSN_DEBUG_AUDIO:      return "PMSN_DEBUG_AUDIO";
    case PMSN_DEBUG_FPS:        return "PMSN_DEBUG_FPS";
    case PMSN_DEBUG_VIDEO:      return "PMSN_DEBUG_VIDEO";
    case PMSN_DEBUG_CONTROLS:   return "PMSN_DEBUG_CONTROLS";
    case PMSN_DEBUG_DATA:       return "PMSN_DEBUG_DATA";
    case PMSN_DEBUG_EXIT:       return "PMSN_DEBUG_EXIT";
    case PMSN_EDITOR_ADMIN:     return "PMSN_EDITOR_ADMIN";
    case PMSN_EDITOR_USER:      return "PMSN_EDITOR_USER";
    case PMSN_TERMINAL_ADMIN:   return "PMSN_TERMINAL_ADMIN";
    case PMSN_TERMINAL_USER:    return "PMSN_TERMINAL_USER";
    case PMSN_DEBUG:            return "PMSN_DEBUG";
    default: return NULL;
    }
}

typedef struct program_s {
        uint32_t    ctrlstate;
        uint32_t    ctrlstate_prev;
        uint32_t    pmsnstate;
        char        name[NAMELENGTH_MAX + 1];
        uint32_t    status;
} EX_program;

typedef struct debug_s {
    uint32_t    state;
} EX_debug;


typedef struct io_s {
    uint16_t    last_key;                           // Last keyboard unicode key input
} EX_io;

// ********************* Declarations to avoid conflicts

int16_t update_debug(void);         // avoid conflicts

// **************************************************************************************** S Y S T E M   S T R U C T U R E S

typedef struct system_s {
    EX_program      program;
    EX_io           io;
    EX_debug        debug;
    EX_temporal     temporal;
    EX_terminal     terminal;
    EX_asset        asset;
    EX_audio        audio;
    EX_video        video;
} EX_system;
                /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
EX_system sys;  /* / / > > > > >   G l o b a l   W o r k i n g   S t o r a g e   < < < < < / / */
                /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

void add_debugging(uint32_t state)          {BITS_ON(sys.debug.state, state);}
void remove_debugging(uint32_t state)       {BITS_OFF(sys.debug.state, state);}
void flip_debugging(uint32_t state)         {BITS_FLIP(sys.debug.state, state);}
uint32_t active_debugging(uint32_t state)   {return BITS_TEST(sys.debug.state, state);}

void set_permission(uint32_t state)         {BITS_ON(sys.program.pmsnstate, state);}
void unset_permission(uint32_t state)       {BITS_OFF(sys.program.pmsnstate, state);}
void flip_permission(uint32_t state)        {BITS_FLIP(sys.program.pmsnstate, state);}
uint32_t valid_permission(uint32_t state)   {return BITS_TEST(sys.program.pmsnstate, state);}

void add_service(uint32_t state)            {BITS_ON(sys.program.ctrlstate, state);}
void remove_service(uint32_t state)         {BITS_OFF(sys.program.ctrlstate, state);}
void flip_service(uint32_t state)           {BITS_FLIP(sys.program.ctrlstate, state);}
uint32_t active_service(uint32_t state)     {return BITS_TEST(sys.program.ctrlstate, state);}
uint32_t only_service(uint32_t state)       {return BITS_FILTER(sys.program.ctrlstate, state);}

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
    return (Color){color[id].r * brightness, color[id].g * brightness, color[id].b * brightness, alpha};
}

Vector2 get_current_virtual_size(void) {
    return sys.video.vscreen[sys.video.current_virtual].size;
}

Vector2 get_tile_size(Vector2 tiles, Vector2 tileset_size) {
    return (Vector2){tileset_size.x/tiles.x, tileset_size.y/tiles.y};
}

Vector2 get_tile_size_from_asset(uint16_t asset_id) {
    return sys.asset.tileset[asset_id].tilesize;
}

Vector2 get_asset_pixelsize(asset_id) {
    return (Vector2){sys.asset.img[asset_id].width, sys.asset.img[asset_id].height};
}

Vector2 get_canvas_size(uint16_t tileset_id) {
    Vector2 size = get_current_virtual_size();
    return (Vector2){size.x / sys.asset.tileset[tileset_id].tilesize.x, size.y / sys.asset.tileset[tileset_id].tilesize.y};
}

#define GRIDEDGECYCLE       60          // determins range from 1/GRIDEDGECYCLEth of s second to GRIDEDGECYCLE seconds
#define GRIDILON            1.182940076 // For timer intervals (determined by GRIDEDGECYCLE and TEMPORAL_ARRAY_SIZE)

uint16_t init_temporal() {
    uint64_t osc;

    datetime_literal(&sys.temporal.datetime);
    
    double range_high = GRIDEDGECYCLE;
    double range_low = 1. / GRIDEDGECYCLE;

    double ratio = range_low;
    double value = range_low;

    double t = GetTime();
    for (osc = 0; osc < TEMPORAL_ARRAY_SIZE; osc++) {
//        printf (" %i = %lf\n", osc, value);
        sys.temporal.period_table[osc] = value;
        sys.temporal.osc_count[osc] = 0;
        sys.temporal.osc_next_frame[osc] = sys.temporal.period_table[osc];

        value += range_low * ratio;
        ratio *= GRIDILON;
    }
    sys.temporal.prev_osc = 0;  // oscillator states
    sys.temporal.osc = 0;       // oscillator states

    return osc;
}

int16_t update_temporal(void) {
    datetime_literal(&sys.temporal.datetime);

    sys.temporal.prev_osc = sys.temporal.osc;
    double t = GetTime();
    for (uint64_t osc = 0; osc < TEMPORAL_ARRAY_SIZE; osc++) {
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

// ********** I / O   H A N D L I N G ********** I / O   H A N D L I N G ********** I / O   H A N D L I N G ********** B E G I N
// ********** I / O   H A N D L I N G ********** I / O   H A N D L I N G ********** I / O   H A N D L I N G ********** B E G I N
// ********** I / O   H A N D L I N G ********** I / O   H A N D L I N G ********** I / O   H A N D L I N G ********** B E G I N

typedef enum {
    ASCII_NULL                      = 0,
    ASCII_START_OF_HEADER           = 1,
    ASCII_START_OF_TEXT             = 2,
    ASCII_END_OF_TEXT               = 3,
    ASCII_END_OF_TRANSMISSION       = 4,
    ASCII_ENQUIRY                   = 5,
    ASCII_ACKNOWLEDGE               = 6,
    ASCII_BELL                      = 7,
    ASCII_BACKSPACE                 = 8,
    ASCII_HORIZONTAL_TAB            = 9,
    ASCII_LINE_FEED                 = 10,
    ASCII_VERTICAL_TAB              = 11,
    ASCII_FORM_FEED                 = 12,
    ASCII_CARRIAGE_RETURN           = 13,
    ASCII_SHIFT_OUT                 = 14,
    ASCII_SHIFT_IN                  = 15,
    ASCII_DATA_LINK_ESCAPE          = 16,
    ASCII_DEVICE_CONTROL_1          = 17,
    ASCII_DEVICE_CONTROL_2          = 18,
    ASCII_DEVICE_CONTROL_3          = 19,
    ASCII_DEVICE_CONTROL_4          = 20,
    ASCII_NEGATIVE_ACKNOWLEDGE      = 21,
    ASCII_SYNCHRONOUS_IDLE          = 22,
    ASCII_END_TRANSMISSION_BLOCK    = 23,
    ASCII_CANCEL                    = 24,
    ASCII_END_OF_MEDIUM             = 25,
    ASCII_SUBSTITUTE                = 26,
    ASCII_ESCAPE                    = 27,
    ASCII_FILE_SEPARATOR            = 28,
    ASCII_GROUP_SEPARATOR           = 29,
    ASCII_RECORD_SEPARATOR          = 30,
    ASCII_UNIT_SEPARATOR            = 31,
    ASCII_SPACE                     = 32,
    ASCII_DELETE                    = 127
} ASCII_CONTROL_CODES;

//PollInputEvents();  // Register all input events
// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-oemkeyscan
uint16_t process_keyboard(void) {
// Establish keyboard management / buffer
// RLAPI int GetKeyPressed(void);                                // Get key pressed (keycode), call it multiple times for keys queued

    // This is a *temporary* very wonky way of handling keyboard inputs....
    uint16_t key = GetCharPressed();
    if (key > 0)                       { sys.io.last_key = key;                      return key;}
    if (IsKeyPressed(KEY_ENTER))       { sys.io.last_key = ASCII_CARRIAGE_RETURN;    return ASCII_CARRIAGE_RETURN;}
    if (IsKeyPressed(KEY_KP_ENTER))    { sys.io.last_key = ASCII_CARRIAGE_RETURN;    return ASCII_CARRIAGE_RETURN;}
    if (IsKeyPressed(KEY_ESCAPE))      { sys.io.last_key = ASCII_ESCAPE;             return ASCII_ESCAPE;}
    if (IsKeyPressed(KEY_TAB))         { sys.io.last_key = ASCII_HORIZONTAL_TAB;     return ASCII_HORIZONTAL_TAB;}
    if (IsKeyPressed(KEY_BACKSPACE))   { sys.io.last_key = ASCII_BACKSPACE;          return ASCII_BACKSPACE;}
    if (IsKeyPressed(KEY_DELETE))      { sys.io.last_key = ASCII_DELETE;             return ASCII_DELETE;}
    
}

// Establish mouse management (old x,y / current x,y)
void process_mouse(void) {
// RLAPI bool IsMouseButtonPressed(int button);                  // Check if a mouse button has been pressed once
// RLAPI bool IsMouseButtonDown(int button);                     // Check if a mouse button is being pressed
// RLAPI bool IsMouseButtonReleased(int button);                 // Check if a mouse button has been released once
// RLAPI bool IsMouseButtonUp(int button);                       // Check if a mouse button is NOT being pressed
}

// ********** I / O   H A N D L I N G ********** I / O   H A N D L I N G ********** I / O   H A N D L I N G ********** E N D
// ********** I / O   H A N D L I N G ********** I / O   H A N D L I N G ********** I / O   H A N D L I N G ********** E N D
// ********** I / O   H A N D L I N G ********** I / O   H A N D L I N G ********** I / O   H A N D L I N G ********** E N D

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

int16_t update_assets(void) {
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
                //sys.asset.framebuffer[id] = LoadRenderTexture( sys.video.vscreen[sys.video.current_virtual].size.x, sys.video.vscreen[sys.video.current_virtual].size.y );
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

uint16_t load_asset (uint32_t assettype, const char* fileName, const char* fileType, const uint8_t* fileData, uint32_t dataSize, uint32_t pak) {
    uint16_t id = sys.asset.total_assets;
    debug_console_out("load_asset", id);

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
            BITS_ON(sys.asset.state[id], ASSET_FONT);
            sys.asset.tileset[id].tex = sys.asset.tex[id];
            sys.asset.data[id] = fileData;
            BITS_ON(sys.asset.state[id], ASSET_DATA);
            sys.asset.data_size[id] = dataSize;
            sys.asset.asset_type[id] = assettype;
            break;

            case ASSET_FRAMEBUFFER : // set current_virtual prior to use
            sys.asset.framebuffer[id] = LoadRenderTexture(get_current_virtual_size().x, get_current_virtual_size().y);
            BITS_ON(sys.asset.state[id], ASSET_LOADED);
            SetTextureFilter(sys.asset.framebuffer[id].texture, FILTER_POINT);
            sys.asset.data_size[id] = dataSize; // ??????????? WRONG !! There is no dataSize passed... so that is a NULL
            sys.video.vscreen[sys.video.current_virtual].asset_id = id;
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
    for(uint16_t asset = 0; asset < MAXASSETS; asset++)
        count += unload_asset(asset);

    return count;
}

uint16_t get_palette_color_count(asset_id) { sys.asset.tileset[asset_id].total; }

uint16_t load_palette(Vector2 count, const char* fileName, const char* fileType, const uint8_t* fileData, uint32_t dataSize, uint32_t pak) {
    uint16_t asset_id = load_asset(ASSET_PALETTE, fileName, fileType, fileData, dataSize, pak);
    float width = (float)sys.asset.img[asset_id].width;
    float height = (float)sys.asset.img[asset_id].height;

    sys.asset.tileset[asset_id].ascii_start = 0;
    sys.asset.tileset[asset_id].tilesize = get_tile_size((Vector2) count, (Vector2) {width, height});
//    sys.asset.tileset[asset_id].tilesize.x = width / count.x;
//    sys.asset.tileset[asset_id].tilesize.y = height / count.y;
    sys.asset.tileset[asset_id].count = count;
    sys.asset.tileset[asset_id].total = count.x * count.y;

    //debug_console_out(sprintf("load_palette ---- %s WIDTH=%f, HEIGHT=%f, COUNT (%f, %f), SIZE (%f, %f)", fileName, width, height, count.x, count.y, sys.asset.tileset[asset_id].tilesize.x, sys.asset.tileset[asset_id].tilesize.y), asset_id);
    return asset_id;
}

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

    float px = code % (uint32_t)tileset->count.x;
    float py = (uint32_t)(code / (uint32_t)tileset->count.x);
    Vector2 *tilesize = &sys.asset.tileset[asset_id].tilesize;
    return (Rectangle) {px * tilesize->x, py * tilesize->y,  tilesize->x, tilesize->y};
}

uint16_t load_tileset(Vector2 count, const char* fileName, const char* fileType, const uint8_t* fileData, uint32_t dataSize, uint32_t pak, uint16_t ascii_start) {
    uint16_t asset_id = load_asset(ASSET_TILESET, fileName, fileType, fileData, dataSize, pak);
    float width = (float)sys.asset.img[asset_id].width;
    float height = (float)sys.asset.img[asset_id].height;

    sys.asset.tileset[asset_id].ascii_start = ascii_start;
    sys.asset.tileset[asset_id].tilesize = get_tile_size((Vector2) count, (Vector2) {width, height});
//    sys.asset.tileset[asset_id].tilesize.x = width / count.x;
//    sys.asset.tileset[asset_id].tilesize.y = height / count.y;
    sys.asset.tileset[asset_id].count = count;
    sys.asset.tileset[asset_id].total = count.x * count.y;

    //debug_console_out(sprintf("load_tileset ---- %s WIDTH=%f, HEIGHT=%f, COUNT (%f, %f), SIZE (%f, %f)", fileName, width, height, count.x, count.y, sys.asset.tileset[asset_id].tilesize.x, sys.asset.tileset[asset_id].tilesize.y), asset_id);
    return asset_id;
}

// ********** A S S E T   S Y S T E M  ***** A S S E T   S Y S T E M  ***** A S S E T   S Y S T E M  ***** E N D
// ********** A S S E T   S Y S T E M  ***** A S S E T   S Y S T E M  ***** A S S E T   S Y S T E M  ***** E N D
// ********** A S S E T   S Y S T E M  ***** A S S E T   S Y S T E M  ***** A S S E T   S Y S T E M  ***** E N D

// ********** C A N V A S   S Y S T E M  ***** C A N V A S   S Y S T E M  ***** C A N V A S   S Y S T E M  ***** B E G I N
// ********** C A N V A S   S Y S T E M  ***** C A N V A S   S Y S T E M  ***** C A N V A S   S Y S T E M  ***** B E G I N
// ********** C A N V A S   S Y S T E M  ***** C A N V A S   S Y S T E M  ***** C A N V A S   S Y S T E M  ***** B E G I N

typedef enum {
    CVFE_LINE_TOP           = 0b1000000000000000000000000000000000000000000000000000000000000000, // turn on line top
    CVFE_LINE_BOT           = 0b0100000000000000000000000000000000000000000000000000000000000000, // turn on line bottom
    CVFE_LINE_LEF           = 0b0010000000000000000000000000000000000000000000000000000000000000, // turn on line left
    CVFE_LINE_RIG           = 0b0001000000000000000000000000000000000000000000000000000000000000, // turn on line right
    CVFE_LINE_HOR           = 0b0000100000000000000000000000000000000000000000000000000000000000, // turn on line center horizontal
    CVFE_LINE_VER           = 0b0000010000000000000000000000000000000000000000000000000000000000, // turn on line center vertical
    CVFE_LINE_DOW           = 0b0000001000000000000000000000000000000000000000000000000000000000, // turn on line angle down
    CVFE_LINE_UP            = 0b0000000100000000000000000000000000000000000000000000000000000000, // turn on line angle up
    CVFE_LIABLEND_LL        = 0b0000000010000000000000000000000000000000000000000000000000000000, // lines vertex alpha blend lower left
    CVFE_LIABLEND_LR        = 0b0000000001000000000000000000000000000000000000000000000000000000, // lines vertex alpha blend lower right
    CVFE_LIABLEND_UR        = 0b0000000000100000000000000000000000000000000000000000000000000000, // lines vertex alpha blend upper right
    CVFE_LIABLEND_UL        = 0b0000000000010000000000000000000000000000000000000000000000000000, // lines vertex alpha blend upper left
    CVFE_LICBLEND_LL        = 0b0000000000001000000000000000000000000000000000000000000000000000, // lines vertex color blend lower left
    CVFE_LICBLEND_LR        = 0b0000000000000100000000000000000000000000000000000000000000000000, // lines vertex color blend lower right
    CVFE_LICBLEND_UR        = 0b0000000000000010000000000000000000000000000000000000000000000000, // lines vertex color blend upper right
    CVFE_LICBLEND_UL        = 0b0000000000000001000000000000000000000000000000000000000000000000, // lines vertex color blend upper left
    CVFE_BGABLEND_LL        = 0b0000000000000000100000000000000000000000000000000000000000000000, // background vertex alpha blend lower left
    CVFE_BGABLEND_LR        = 0b0000000000000000010000000000000000000000000000000000000000000000, // background vertex alpha blend lower right
    CVFE_BGABLEND_UR        = 0b0000000000000000001000000000000000000000000000000000000000000000, // background vertex alpha blend upper right
    CVFE_BGABLEND_UL        = 0b0000000000000000000100000000000000000000000000000000000000000000, // background vertex alpha blend upper left
    CVFE_BGCBLEND_LL        = 0b0000000000000000000010000000000000000000000000000000000000000000, // background vertex color blend lower left
    CVFE_BGCBLEND_LR        = 0b0000000000000000000001000000000000000000000000000000000000000000, // background vertex color blend lower right
    CVFE_BGCBLEND_UR        = 0b0000000000000000000000100000000000000000000000000000000000000000, // background vertex color blend upper right
    CVFE_BGCBLEND_UL        = 0b0000000000000000000000010000000000000000000000000000000000000000, // background vertex color blend upper left
    CVFE_FGABLEND_LL        = 0b0000000000000000000000001000000000000000000000000000000000000000, // foreground vertex alpha blend lower left
    CVFE_FGABLEND_LR        = 0b0000000000000000000000000100000000000000000000000000000000000000, // foreground vertex alpha blend lower right
    CVFE_FGABLEND_UR        = 0b0000000000000000000000000010000000000000000000000000000000000000, // foreground vertex alpha blend upper right
    CVFE_FGABLEND_UL        = 0b0000000000000000000000000001000000000000000000000000000000000000, // foreground vertex alpha blend upper left
    CVFE_FGCBLEND_LL        = 0b0000000000000000000000000000100000000000000000000000000000000000, // foreground vertex color blend lower left
    CVFE_FGCBLEND_LR        = 0b0000000000000000000000000000010000000000000000000000000000000000, // foreground vertex color blend lower right
    CVFE_FGCBLEND_UR        = 0b0000000000000000000000000000001000000000000000000000000000000000, // foreground vertex color blend upper right
    CVFE_FGCBLEND_UL        = 0b0000000000000000000000000000000100000000000000000000000000000000, // foreground vertex color blend upper left
    CVFE_LNBLINK3           = 0b0000000000000000000000000000000010000000000000000000000000000000, // lines blinking speed (0...7) 0 = no blink
    CVFE_LNBLINK2           = 0b0000000000000000000000000000000001000000000000000000000000000000, // lines blinking speed
    CVFE_LNBLINK1           = 0b0000000000000000000000000000000000100000000000000000000000000000, // lines blinking speed
    CVFE_BGBLINK3           = 0b0000000000000000000000000000000000010000000000000000000000000000, // background blinking speed (0...7) 0 = no blink
    CVFE_BGBLINK2           = 0b0000000000000000000000000000000000001000000000000000000000000000, // background blinking speed
    CVFE_BGBLINK1           = 0b0000000000000000000000000000000000000100000000000000000000000000, // background blinking speed
    CVFE_FGBLINK3           = 0b0000000000000000000000000000000000000010000000000000000000000000, // foreground blinking speed (0...7) 0 = no blink
    CVFE_FGBLINK2           = 0b0000000000000000000000000000000000000001000000000000000000000000, // foreground blinking speed
    CVFE_FGBLINK1           = 0b0000000000000000000000000000000000000000100000000000000000000000, // foreground blinking speed
    CVFE_DOUBLEHEIGHT       = 0b0000000000000000000000000000000000000000010000000000000000000000, // double height content
    CVFE_DOUBLEWIDTH        = 0b0000000000000000000000000000000000000000001000000000000000000000, // double width content
    CVFE_LINESSEQ           = 0b0000000000000000000000000000000000000000000100000000000000000000, // turn on lines sequencing
    CVFE_COLORSEQ           = 0b0000000000000000000000000000000000000000000010000000000000000000, // turn on color sequencing
    CVFE_VALUESEQ           = 0b0000000000000000000000000000000000000000000001000000000000000000, // turn on cell value sequencing
    CVFE_AUTOSCRX           = 0b0000000000000000000000000000000000000000000000100000000000000000, // turn on automatic scrolling on x axis
    CVFE_AUTOSCRY           = 0b0000000000000000000000000000000000000000000000010000000000000000, // turn on automatic scrolling on y axis
    CVFE_ROTATION           = 0b0000000000000000000000000000000000000000000000001000000000000000, // turn on rotation 
    CVFE_SKEW               = 0b0000000000000000000000000000000000000000000000000100000000000000, // turn on cell skewing
    CVFE_WRAP_X             = 0b0000000000000000000000000000000000000000000000000010000000000000, // turn on wrap around on x axis
    CVFE_WRAP_Y             = 0b0000000000000000000000000000000000000000000000000001000000000000, // turn on wrap around on y axis
    CVFE_SCALE_X            = 0b0000000000000000000000000000000000000000000000000000100000000000, // turn on cell scaling on x axis
    CVFE_SCALE_Y            = 0b0000000000000000000000000000000000000000000000000000010000000000, // turn on cell scaling on y axis
    CVFE_FLIPH              = 0b0000000000000000000000000000000000000000000000000000001000000000, // flip cell(s) horizontally
    CVFE_FLIPV              = 0b0000000000000000000000000000000000000000000000000000000100000000, // flip cell(s) vertically
    CVFE_RED                = 0b0000000000000000000000000000000000000000000000000000000010000000, // turn on red channel
    CVFE_GREEN              = 0b0000000000000000000000000000000000000000000000000000000001000000, // turn on green channel
    CVFE_BLUE               = 0b0000000000000000000000000000000000000000000000000000000000100000, // turn on blue channel
    CVFE_ALPHA              = 0b0000000000000000000000000000000000000000000000000000000000010000, // turn on transparency
    CVFE_PROTECTED          = 0b0000000000000000000000000000000000000000000000000000000000001000, // protect value from being changed
    CVFE_SHADOW             = 0b0000000000000000000000000000000000000000000000000000000000000100, // turn on shadow cell
    CVFE_BACKGROUND         = 0b0000000000000000000000000000000000000000000000000000000000000010, // turn on cell background (tile rectangle fill)
    CVFE_FOREGROUND         = 0b0000000000000000000000000000000000000000000000000000000000000001, // turn on cell foreground (value) (used for hidden mode)
    CVFE_LINES_MASK         = 0b1111111100000000000000000000000000000000000000000000000000000000, 
    CVFE_BLENDING_MASK      = 0b0000000011111111111111111111111100000000000000000000000000000000, 
    CVFE_LNBLINK_MASK       = 0b0000000000000000000000000000000011100000000000000000000000000000,
    CVFE_BGBLINK_MASK       = 0b0000000000000000000000000000000000011100000000000000000000000000,
    CVFE_FGBLINK_MASK       = 0b0000000000000000000000000000000000000011100000000000000000000000,
    CVFE_DEFAULT1           = 0b0000000000000000000000000000000000000000011100000000000011110101, // DEFAULT STATE :HEAVY PROCESSING
    CVFE_DEFAULT2           = 0b0000000000000000000000000000000000000000000000001100000011110111, // DEFAULT STATE :SCROLLTEXT
    CVFE_DEFAULT3           = 0b0000000000000000000000000000000000000000000011110000000011110001, // DEFAULT STATE :GAME canvas
    CVFE_DEFAULT4           = 0b0000000000000000000000000000000000000000000000000100000011110101  // DEFAULT STATE :TERMINAL DISPLAY
} canvas_features;

#define CVFE_LINES_BITS     56
#define CVFE_LNBLINK_BITS   29
#define CVFE_BGBLINK_BITS   26
#define CVFE_FGBLINK_BITS   23
#define GET_FROM_STATE(state, mask, shift) ((state & mask) >> shift) // be weary that shifting greater than 31 is invalid in non 64bit -march...

void plot_character(uint16_t asset_id, uint16_t palette_id, uint16_t code, Vector2 position, Vector2 scale, Vector2 skew, Vector2 shadow, float angle, Color colorfg, Color colorbg, Color colorln, uint64_t state) {
    //add logic for out of bound position
    // get the current render texture's size
    Color vertex_colors[4];
    if (!(state & CVFE_ROTATION)) angle = 0.f;

    if (state & CVFE_BACKGROUND) {
        if (state & CVFE_RED)   vertex_colors[0].r = colorbg.r; else vertex_colors[0].r = 0;
        if (state & CVFE_GREEN) vertex_colors[0].g = colorbg.g; else vertex_colors[0].g = 0;
        if (state & CVFE_BLUE)  vertex_colors[0].b = colorbg.b; else vertex_colors[0].b = 0;
        if (state & CVFE_ALPHA) vertex_colors[0].a = colorbg.a; else vertex_colors[0].a = 0;
        vertex_colors[1] = vertex_colors[0];
        vertex_colors[2] = vertex_colors[0];
        vertex_colors[3] = vertex_colors[0];
        DrawRectanglePro2(
            (Rectangle) { position.x, position.y, scale.x, scale.y },
            (Vector2) {0,0}, (Vector2) {0,0}, angle, vertex_colors);
    }
    if (state & CVFE_FOREGROUND) {
            if (state & CVFE_SHADOW) {
                vertex_colors[0] = (Color) {0.f, 0.f, 0.f, 48.f};
                vertex_colors[1] = (Color) {0.f, 0.f, 0.f, 48.f};
                vertex_colors[2] = (Color) {0.f, 0.f, 0.f, 48.f};
                vertex_colors[3] = (Color) {0.f, 0.f, 0.f, 48.f};
                DrawTexturePro2(sys.asset.tex[asset_id],
                    get_tilezone_from_code(asset_id, code),
                    (Rectangle) { position.x + shadow.x, position.y + shadow.y, scale.x, scale.y },
                    (Vector2) {0,0}, skew, angle, vertex_colors);
            };
            if (state & CVFE_RED)   vertex_colors[0].r = colorfg.r; else vertex_colors[0].r = 0;
            if (state & CVFE_GREEN) vertex_colors[0].g = colorfg.g; else vertex_colors[0].g = 0;
            if (state & CVFE_BLUE)  vertex_colors[0].b = colorfg.b; else vertex_colors[0].b = 0;
            if (state & CVFE_ALPHA) vertex_colors[0].a = colorfg.a; else vertex_colors[0].a = 0;
            vertex_colors[1] = vertex_colors[0];
            vertex_colors[2] = vertex_colors[0];
            vertex_colors[3] = vertex_colors[0];
            DrawTexturePro2(sys.asset.tex[asset_id],
                get_tilezone_from_code(asset_id, code),
                (Rectangle) { position.x, position.y , scale.x, scale.y },
                (Vector2) {0,0}, skew, angle, vertex_colors);
    }

    uint8_t lines = GET_FROM_STATE(state, CVFE_LINES_MASK, CVFE_LINES_BITS);
    if (lines) {
            if (state & CVFE_RED)   vertex_colors[0].r = colorln.r; else vertex_colors[0].r = 0;
            if (state & CVFE_GREEN) vertex_colors[0].g = colorln.g; else vertex_colors[0].g = 0;
            if (state & CVFE_BLUE)  vertex_colors[0].b = colorln.b; else vertex_colors[0].b = 0;
            if (state & CVFE_ALPHA) vertex_colors[0].a = colorln.a; else vertex_colors[0].a = 0;
            vertex_colors[1] = vertex_colors[0];
            vertex_colors[2] = vertex_colors[0];
            vertex_colors[3] = vertex_colors[0];
            DrawTexturePro2(sys.asset.tex[sys.asset.lines_id],
                get_tilezone_from_code(sys.asset.lines_id, lines),
                (Rectangle) { position.x, position.y , scale.x, scale.y },
                (Vector2) {0,0}, skew, angle, vertex_colors);
    }
}

static void plot_cell(uint16_t canvasgroup_id, uint16_t canvas_id, EX_cell *cell_t, Vector2 target) {
    EX_canvas *canvas = &sys.video.canvasgroup[canvasgroup_id].canvas[canvas_id];
    uint16_t lsx = canvas->size.x, lsy = canvas->size.y;    if (!lsx || !lsy) return; // empty canvas, can not process
    if (target.x >= lsx || target.y >= lsy || target.x < 0 || target.y < 0) return;

    uint16_t linear_offset = lsx * target.y + target.x;
    EX_cell *cell_array  = &sys.video.canvasgroup[canvasgroup_id].canvas[canvas_id].cell[0];
    EX_cell *cell = &cell_array[linear_offset];
    memcpy(cell, cell_t, sizeof(EX_cell));
}

int16_t init_cell_zone_linear(EX_cell *cell, uint64_t cell_state, uint32_t color_id, uint32_t colorbg_id) {
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

void set_canvas_default_palette(uint16_t canvasgroup_id, uint16_t canvas_id, uint16_t palette_id) {
    EX_canvas *canvas = &sys.video.canvasgroup[canvasgroup_id].canvas[canvas_id];
    canvas->default_palette_id = palette_id;
}

void set_canvas_default_asset(uint16_t canvasgroup_id, uint16_t canvas_id, uint16_t asset_id) {
    EX_canvas *canvas = &sys.video.canvasgroup[canvasgroup_id].canvas[canvas_id];
    canvas->default_asset_id = asset_id;
}

uint16_t init_canvas(uint16_t canvasgroup_id, uint16_t canvas_id, Vector2 size, uint64_t canvas_state, uint64_t cell_state, uint16_t asset_id, uint16_t palette_id) {
    //EX_canvasgroup *canvasgroup = sys.video.canvasgroup[canvasgroup_id];
    EX_canvas *canvas = &sys.video.canvasgroup[canvasgroup_id].canvas[canvas_id];
    uint32_t cell_count = (uint16_t)size.x * (uint16_t)size.y;
    canvas->size = size;
    canvas->state = canvas_state;
    set_canvas_default_palette(canvasgroup_id, canvas_id, palette_id);
    set_canvas_default_asset(canvasgroup_id, canvas_id, asset_id);
    canvas->cell_count = cell_count;
    canvas->cell = calloc(cell_count, sizeof(EX_cell));
    canvas->offset = (Vector2) {0,0};
    canvas->scale = (Vector2) {1,1};
    canvas->angle = 0;
    canvas->default_tilesize = get_tile_size(size, get_asset_pixelsize(asset_id));
    canvas->fg_brightness = 1.f;
    canvas->bg_brightness = 1.f;
    canvas->alpha = 255;

    EX_cell *cell = &sys.video.canvasgroup[canvasgroup_id].canvas[canvas_id].cell[0];
    for (uint32_t i = 0; i < cell_count; i++) {
        init_cell_zone_linear(&cell[i], cell_state, 0, 0); // this process is temporary, as the faster alternative is to mass copy a template cell
    }
    return 1;
}

uint16_t init_canvas_section_templated(uint16_t canvasgroup_id, uint16_t canvas_id, EX_cell *cell_t, Rectangle target) {
    uint16_t linear_offset;
    EX_canvas *canvas = &sys.video.canvasgroup[canvasgroup_id].canvas[canvas_id];
    uint16_t lsx = canvas->size.x, lsy = canvas->size.y;    if (!lsx || !lsy) return; // empty canvas, can not process

    if (target.x >= lsx || target.y >= lsy || (target.x + target.width) < 0 || (target.y + target.height) < 0) return;
    if ((target.x + target.width) > lsx) target.width = lsx - target.x; 
    if ((target.y + target.height) > lsy) target.height = lsy - target.y;

    EX_cell *cell_array = &sys.video.canvasgroup[canvasgroup_id].canvas[canvas_id].cell[0];
    for (uint16_t x = target.x; x++; x < (target.x + target.width)) {
        for (uint16_t y = target.y; y++; y < (target.y + target.height)) {
            linear_offset = lsx * y + x;
            EX_cell *cell = &cell_array[linear_offset];
            memcpy(cell, cell_t, sizeof(EX_cell));            
        }
    }
    return 1;
}

uint16_t init_canvas_templated(uint16_t canvasgroup_id, uint16_t canvas_id, EX_canvas *canvas_t, EX_cell *cell_t) {
    //EX_canvasgroup *canvasgroup = sys.video.canvasgroup[canvasgroup_id];
    EX_canvas *canvas = &sys.video.canvasgroup[canvasgroup_id].canvas[canvas_id];
    memcpy(canvas, canvas_t, sizeof(EX_canvas));//    canvas = (EX_canvas)canvas_t;
    canvas->cell_count = (canvas->size.x * canvas->size.y);
    canvas->cell = calloc(canvas->cell_count, sizeof(EX_cell));

    EX_cell *cell_array = &sys.video.canvasgroup[canvasgroup_id].canvas[canvas_id].cell[0];
    for (uint32_t linear_offset = 0; linear_offset < canvas->cell_count; linear_offset++) {
        EX_cell *cell = &cell_array[linear_offset];
        memcpy(cell, cell_t, sizeof(EX_cell));
    }
    return 1;
}

void set_canvasgroup_default_palette(uint16_t canvasgroup_id, uint16_t palette_id) {
    sys.video.canvasgroup[canvasgroup_id].default_palette_id = palette_id;
}

void set_canvasgroup_default_asset(uint16_t canvasgroup_id, uint16_t asset_id) {
    sys.video.canvasgroup[canvasgroup_id].default_asset_id = asset_id;
}

uint16_t init_canvasgroup(uint32_t canvasgroup_id, uint32_t canvasgroup_state, uint16_t canvas_count) {
//    uint16_t canvases = 0;
    sys.video.canvasgroup[canvasgroup_id].state = canvasgroup_state;
    sys.video.canvasgroup[canvasgroup_id].canvas_count = canvas_count;
//    set_canvasgroup_default_palette(canvasgroup_id, palette_id);
//    set_canvasgroup_default_asset(canvasgroup_id, asset_id);
    sys.video.canvasgroup[canvasgroup_id].canvas = calloc(canvas_count, sizeof(EX_canvas));
/*    for (uint16_t canvas_id = 0; canvas_id < canvas_count; canvas_id++) {
        canvases += init_canvas(canvasgroup_id, canvas_id, size, canvas_state, cell_state, asset_id, palette_id);
    }
    return canvases;
*/
    return canvas_count;
}

// *************** REFERENCE SHORTCUTS TO USE *****************
// EX_canvasgroup  *canvasgroup  = sys.video.canvasgroup[canvasgroup_id];
// EX_canvas *canvas = &sys.video.canvasgroup[canvasgroup_id].canvas[canvas_id];
// EX_cell  *cell  = &sys.video.canvasgroup[canvasgroup_id].canvas[canvas_id].cell[0]; ( cell[50].state )
// This functionality requires setting a bunch of stuff afterwards;
// - per cell states
// - per canvas asset
int16_t init_canvasgroup_multicanvas(Vector2 size, uint32_t canvasgroup_state, uint64_t canvas_state[]) {
    uint16_t canvasgroup_id = sys.video.current_virtual; // A single canvasgroup per Virtual Display

    sys.video.canvasgroup[canvasgroup_id].state = canvasgroup_state;
    sys.video.canvasgroup[canvasgroup_id].canvas_count = sizeof(canvas_state) / sizeof_member(EX_canvas, state);

    sys.video.canvasgroup[canvasgroup_id].canvas = calloc(sys.video.canvasgroup[canvasgroup_id].canvas_count, sizeof(EX_canvas));
    for (uint16_t i = 0; i < sys.video.canvasgroup[canvasgroup_id].canvas_count; i++) {
        init_canvas(canvasgroup_id, i, size, canvas_state[i], 0, 0, 0);
    }
    return 0;
}

uint16_t unload_canvas(uint16_t canvasgroup_id, uint16_t canvas_id) {
    EX_canvas *canvas = &sys.video.canvasgroup[canvasgroup_id].canvas[canvas_id];
    if (canvas->cell_count > 0) {
        canvas->size = (Vector2){0};
        canvas->state = 0;
        canvas->cell_count = 0;
        free(canvas->cell);
        return 1;
    } else {
        return 0; // was an empty canvas
    }
}

uint16_t unload_canvasgroup(uint16_t canvasgroup_id) {
    uint16_t canvases = 0;
    for (uint16_t canvas_id = 0; canvas_id < (sys.video.canvasgroup[canvasgroup_id].canvas_count); canvas_id++) {
        canvases += unload_canvas(canvasgroup_id, canvas_id);
    }
    if (canvases) free(sys.video.canvasgroup[canvasgroup_id].canvas);
    return canvases;
}

uint16_t unload_all_canvasgroups() {
    uint16_t canvasgroups = 0, canvases = 0;
    for (uint16_t canvasgroup_id = 0; canvasgroup_id < GRID_MAX_CANVASGROUPS; canvasgroup_id++) {
        canvases += unload_canvasgroup(canvasgroup_id);
        if (canvases) ++canvasgroups;
    }
    return canvases;
}

void canvas_set_mouse_position(uint16_t canvasgroup_id, uint16_t canvas_id, Vector2 target) {
    EX_canvas *canvas = &sys.video.canvasgroup[canvasgroup_id].canvas[canvas_id];
    uint16_t lsx = canvas->size.x, lsy = canvas->size.y;    if (!lsx || !lsy) return; // empty canvas, can not process
    if (target.x >= lsx) target.x = lsx - 1; else if (target.x < 0) target.x = 0;
    if (target.y >= lsy) target.y = lsy - 1; else if (target.y < 0) target.y = 0;
    //canvas->mousecursor->offset = target;
}

void canvas_set_keyboard_position(uint16_t canvasgroup_id, uint16_t canvas_id, Vector2 target) {
    EX_canvas *canvas = &sys.video.canvasgroup[canvasgroup_id].canvas[canvas_id];
    uint16_t lsx = canvas->size.x, lsy = canvas->size.y;    if (!lsx || !lsy) return; // empty canvas, can not process
    if (target.x >= lsx) target.x = lsx - 1; else if (target.x < 0) target.x = 0;
    if (target.y >= lsy) target.y = lsy - 1; else if (target.y < 0) target.y = 0;
    //canvas->keycursor->offset = target;
}

void set_cell_state(uint16_t canvasgroup_id, uint16_t canvas_id, Rectangle target, uint64_t state) {
    uint16_t linear_offset;
    EX_canvas *canvas = &sys.video.canvasgroup[canvasgroup_id].canvas[canvas_id];
    uint16_t lsx = canvas->size.x, lsy = canvas->size.y;    if (!lsx || !lsy) return; // empty canvas, can not process

    if (target.x >= lsx || target.y >= lsy || (target.x + target.width) < 0 || (target.y + target.height) < 0) return;
    if ((target.x + target.width) > lsx) target.width = lsx - target.x; 
    if ((target.y + target.height) > lsy) target.height = lsy - target.y;

    EX_cell  *target_cell  = &sys.video.canvasgroup[canvasgroup_id].canvas[canvas_id].cell[0];
    for (uint16_t x = target.x; x++; x < (target.x + target.width)) {
        for (uint16_t y = target.y; y++; y < (target.y + target.height)) {
            linear_offset = lsx * y + x;
            BITS_ON(target_cell[linear_offset].state, state);
        }
    }
}

void clear_cell_state(uint16_t canvasgroup_id, uint16_t canvas_id, Rectangle target, uint64_t state) {
    uint16_t linear_offset;
    EX_canvas *canvas = &sys.video.canvasgroup[canvasgroup_id].canvas[canvas_id];
    uint16_t lsx = canvas->size.x, lsy = canvas->size.y;    if (!lsx || !lsy) return; // empty canvas, can not process

    if (target.x >= lsx || target.y >= lsy || (target.x + target.width) < 0 || (target.y + target.height) < 0) return;
    if ((target.x + target.width) > lsx) target.width = lsx - target.x; 
    if ((target.y + target.height) > lsy) target.height = lsy - target.y;

    EX_cell  *target_cell  = &sys.video.canvasgroup[canvasgroup_id].canvas[canvas_id].cell[0];
    for (uint16_t x = target.x; x++; x < (target.x + target.width)) {
        for (uint16_t y = target.y; y++; y < (target.y + target.height)) {
            linear_offset = lsx * y + x;
            BITS_OFF(target_cell[linear_offset].state, state);
        }
    }
}

void set_cell_colorfg(uint16_t canvasgroup_id, uint16_t canvas_id, Rectangle target, uint16_t color_id) {
    uint16_t linear_offset;
    EX_canvas *canvas = &sys.video.canvasgroup[canvasgroup_id].canvas[canvas_id];
    uint16_t lsx = canvas->size.x, lsy = canvas->size.y;    if (!lsx || !lsy) return; // empty canvas, can not process

    if (target.x >= lsx || target.y >= lsy || (target.x + target.width) < 0 || (target.y + target.height) < 0) return;
    if ((target.x + target.width) > lsx) target.width = lsx - target.x; 
    if ((target.y + target.height) > lsy) target.height = lsy - target.y;

    EX_cell  *target_cell  = &sys.video.canvasgroup[canvasgroup_id].canvas[canvas_id].cell[0];
    for (uint16_t x = target.x; x++; x < (target.x + target.width)) {
        for (uint16_t y = target.y; y++; y < (target.y + target.height)) {
            linear_offset = lsx * y + x;
            target_cell[linear_offset].colorfg_id = color_id;
        }
    }
}

void set_cell_colorbg(uint16_t canvasgroup_id, uint16_t canvas_id, Rectangle target, uint16_t color_id) {
    uint16_t linear_offset;
    EX_canvas *canvas = &sys.video.canvasgroup[canvasgroup_id].canvas[canvas_id];
    uint16_t lsx = canvas->size.x, lsy = canvas->size.y;    if (!lsx || !lsy) return; // empty canvas, can not process

    if (target.x >= lsx || target.y >= lsy || (target.x + target.width) < 0 || (target.y + target.height) < 0) return;
    if ((target.x + target.width) > lsx) target.width = lsx - target.x; 
    if ((target.y + target.height) > lsy) target.height = lsy - target.y;

    EX_cell  *target_cell  = &sys.video.canvasgroup[canvasgroup_id].canvas[canvas_id].cell[0];
    for (uint16_t x = target.x; x++; x < (target.x + target.width)) {
        for (uint16_t y = target.y; y++; y < (target.y + target.height)) {
            linear_offset = lsx * y + x;
            target_cell[linear_offset].colorbg_id = color_id;
        }
    }
}

void set_cell_colorln(uint16_t canvasgroup_id, uint16_t canvas_id, Rectangle target, uint16_t color_id) {
    uint16_t linear_offset;
    EX_canvas *canvas = &sys.video.canvasgroup[canvasgroup_id].canvas[canvas_id];
    uint16_t lsx = canvas->size.x, lsy = canvas->size.y;    if (!lsx || !lsy) return; // empty canvas, can not process

    if (target.x >= lsx || target.y >= lsy || (target.x + target.width) < 0 || (target.y + target.height) < 0) return;
    if ((target.x + target.width) > lsx) target.width = lsx - target.x; 
    if ((target.y + target.height) > lsy) target.height = lsy - target.y;

    EX_cell  *target_cell  = &sys.video.canvasgroup[canvasgroup_id].canvas[canvas_id].cell[0];
    for (uint16_t x = target.x; x++; x < (target.x + target.width)) {
        for (uint16_t y = target.y; y++; y < (target.y + target.height)) {
            linear_offset = lsx * y + x;
            target_cell[linear_offset].colorln_id = color_id;
        }
    }
}

void set_cell_color_mask(uint16_t canvasgroup_id, uint16_t canvas_id, Rectangle target, Color color) {
    uint16_t linear_offset;
    EX_canvas *canvas = &sys.video.canvasgroup[canvasgroup_id].canvas[canvas_id];
    uint16_t lsx = canvas->size.x, lsy = canvas->size.y;    if (!lsx || !lsy) return; // empty canvas, can not process

    if (target.x >= lsx || target.y >= lsy || (target.x + target.width) < 0 || (target.y + target.height) < 0) return;
    if ((target.x + target.width) > lsx) target.width = lsx - target.x; 
    if ((target.y + target.height) > lsy) target.height = lsy - target.y;

    EX_cell  *target_cell  = &sys.video.canvasgroup[canvasgroup_id].canvas[canvas_id].cell[0];
    for (uint16_t x = target.x; x++; x < (target.x + target.width)) {
        for (uint16_t y = target.y; y++; y < (target.y + target.height)) {
            linear_offset = lsx * y + x;
            target_cell[linear_offset].color_mask = color;
        }
    }
}

void set_cell_color_shadow_mask(uint16_t canvasgroup_id, uint16_t canvas_id, Rectangle target, Color color) {
    uint16_t linear_offset;
    EX_canvas *canvas = &sys.video.canvasgroup[canvasgroup_id].canvas[canvas_id];
    uint16_t lsx = canvas->size.x, lsy = canvas->size.y;    if (!lsx || !lsy) return; // empty canvas, can not process

    if (target.x >= lsx || target.y >= lsy || (target.x + target.width) < 0 || (target.y + target.height) < 0) return;
    if ((target.x + target.width) > lsx) target.width = lsx - target.x; 
    if ((target.y + target.height) > lsy) target.height = lsy - target.y;

    EX_cell  *target_cell  = &sys.video.canvasgroup[canvasgroup_id].canvas[canvas_id].cell[0];
    for (uint16_t x = target.x; x++; x < (target.x + target.width)) {
        for (uint16_t y = target.y; y++; y < (target.y + target.height)) {
            linear_offset = lsx * y + x;
            target_cell[linear_offset].shadow_mask = color;
        }
    }
}

void set_cell_offset(uint16_t canvasgroup_id, uint16_t canvas_id, Rectangle target, Vector2 offset) {
    uint16_t linear_offset;
    EX_canvas *canvas = &sys.video.canvasgroup[canvasgroup_id].canvas[canvas_id];
    uint16_t lsx = canvas->size.x, lsy = canvas->size.y;    if (!lsx || !lsy) return; // empty canvas, can not process

    if (target.x >= lsx || target.y >= lsy || (target.x + target.width) < 0 || (target.y + target.height) < 0) return;
    if ((target.x + target.width) > lsx) target.width = lsx - target.x; 
    if ((target.y + target.height) > lsy) target.height = lsy - target.y;

    EX_cell  *target_cell  = &sys.video.canvasgroup[canvasgroup_id].canvas[canvas_id].cell[0];
    for (uint16_t x = target.x; x++; x < (target.x + target.width)) {
        for (uint16_t y = target.y; y++; y < (target.y + target.height)) {
            linear_offset = (lsx * y + x);
            target_cell[linear_offset].offset = offset;
        }
    }
}

void set_cell_angle(uint16_t canvasgroup_id, uint16_t canvas_id, Rectangle target, float angle) {
    uint16_t linear_offset;
    EX_canvas *canvas = &sys.video.canvasgroup[canvasgroup_id].canvas[canvas_id];
    uint16_t lsx = canvas->size.x, lsy = canvas->size.y;    if (!lsx || !lsy) return; // empty canvas, can not process

    if (target.x >= lsx || target.y >= lsy || (target.x + target.width) < 0 || (target.y + target.height) < 0) return;
    if ((target.x + target.width) > lsx) target.width = lsx - target.x; 
    if ((target.y + target.height) > lsy) target.height = lsy - target.y;

    EX_cell  *target_cell  = &sys.video.canvasgroup[canvasgroup_id].canvas[canvas_id].cell[0];
    for (uint16_t x = target.x; x++; x < (target.x + target.width)) {
        for (uint16_t y = target.y; y++; y < (target.y + target.height)) {
            linear_offset = (lsx * y + x);
            target_cell[linear_offset].angle = angle;
        }
    }
}

void set_cell_scale(uint16_t canvasgroup_id, uint16_t canvas_id, Rectangle target, Vector2 scale) {
    uint16_t linear_offset;
    EX_canvas *canvas = &sys.video.canvasgroup[canvasgroup_id].canvas[canvas_id];
    uint16_t lsx = canvas->size.x, lsy = canvas->size.y;    if (!lsx || !lsy) return; // empty canvas, can not process

    if (target.x >= lsx || target.y >= lsy || (target.x + target.width) < 0 || (target.y + target.height) < 0) return;
    if ((target.x + target.width) > lsx) target.width = lsx - target.x; 
    if ((target.y + target.height) > lsy) target.height = lsy - target.y;

    EX_cell  *target_cell  = &sys.video.canvasgroup[canvasgroup_id].canvas[canvas_id].cell[0];
    for (uint16_t x = target.x; x++; x < (target.x + target.width)) {
        for (uint16_t y = target.y; y++; y < (target.y + target.height)) {
            linear_offset = (lsx * y + x);
            target_cell[linear_offset].scale = scale;
        }
    }
}

uint16_t get_cell_colorfg(uint16_t canvas_id, Vector2 target) {
    uint16_t canvasgroup_id = sys.video.current_virtual;
    EX_canvas *canvas = &sys.video.canvasgroup[canvasgroup_id].canvas[canvas_id];
    uint16_t lsx = canvas->size.x, lsy = canvas->size.y;    if (!lsx || !lsy) return; // empty canvas, can not process

    if (target.x >= lsx || target.y >= lsy || target.x < 0 || target.y < 0) return;

    EX_cell  *target_cell  = &sys.video.canvasgroup[canvasgroup_id].canvas[canvas_id].cell[0];
    uint16_t linear_offset = (lsx * target.y + target.x);
    return target_cell[linear_offset].colorfg_id;
}

uint16_t get_cell_colorbg(uint16_t canvas_id, Vector2 target) {
    uint16_t canvasgroup_id = sys.video.current_virtual;
    EX_canvas *canvas = &sys.video.canvasgroup[canvasgroup_id].canvas[canvas_id];
    uint16_t lsx = canvas->size.x, lsy = canvas->size.y;    if (!lsx || !lsy) return; // empty canvas, can not process

    if (target.x >= lsx || target.y >= lsy || target.x < 0 || target.y < 0) return;

    EX_cell  *target_cell  = &sys.video.canvasgroup[canvasgroup_id].canvas[canvas_id].cell[0];
    uint16_t linear_offset = (lsx * target.y + target.x);
    return target_cell[linear_offset].colorbg_id;
}


// iterate through charracter ascii codes, if font pixels then copy desired source_cell information to the canvas
void plot_big_characters(uint16_t canvasgroup_id, uint16_t canvas_id, Vector2 target, uint64_t state, uint16_t font_id, uint8_t *ch) {
    uint32_t linear_offset;
    EX_canvas *canvas = &sys.video.canvasgroup[canvasgroup_id].canvas[canvas_id];
    uint16_t lsx = canvas->size.x, lsy = canvas->size.y;
    EX_cell  *target_cell  = &sys.video.canvasgroup[canvasgroup_id].canvas[canvas_id].cell[0];

    uint32_t length = sizeof(ch);

    for (uint32_t i= 0; i++; i<length) {
// to complete
    }    
}

typedef enum {
    CFLD_R32                  = 0b10000000000000000000000000000000,
    CFLD_STATE                = 0b01000000000000000000000000000000,   // all flags for cell
    CFLD_VALUE                = 0b00010000000000000000000000000000,   // value of cell
    CFLD_LINES                = 0b00000010000000000000000000000000,   // lines feature
    CFLD_CYCLE                = 0b00000000000010000000000000000000,   // cell animation sequence number
    CFLD_FG_COLOR             = 0b00000000000000100000000000000000,   // palette index color for cell
    CFLD_FG_COLOR_CYCLE       = 0b00000000000000010000000000000000,   // color cycle index
    CFLD_BG_COLOR             = 0b00000000000000001000000000000000,   // palette index color for cell background
    CFLD_BG_COLOR_CYCLE       = 0b00000000000000000100000000000000,   // color cycle index
    CFLD_LINES_COLOR          = 0b00000000000000000010000000000000,   // palette index color for cell background
    CFLD_LINES_COLOR_CYCLE    = 0b00000000000000000001000000000000,   // color cycle index
    CFLD_OFFSET               = 0b00000000000000000000100000000000,   // displacement from top left (x,y)
    CFLD_SKEW                 = 0b00000000000000000000010000000000,   // horizontal and vertical skew
    CFLD_SCALE                = 0b00000000000000000000001000000000,   // (x,y) cell scale
    CFLD_SCALE_SPEED          = 0b00000000000000000000000100000000,   // (x,y) cell scale speed
    CFLD_SCROLL_SPEED         = 0b00000000000000000000000010000000,   // (x,y) cell scroll speed
    CFLD_ANGLE                = 0b00000000000000000000000001000000,   // degree of angle used to rotate the cell
    CFLD_FG_BRIGHTNESS        = 0b00000000000000000000000000100000,   // foreground brightness (values 0...1 divides, values 1 to 255 multiply)
    CFLD_BG_BRIGHTNESS        = 0b00000000000000000000000000010000,   // background brightness (values 0...1 divides, values 1 to 255 multiply)
    CFLD_ALPHA                = 0b00000000010000000000000000000000,   // alpha channel
    CFLD_COLOR_MASK           = 0b00000000000000000000000000001000,   // RGBA color mask of cell
    CFLD_SHADOW_MASK          = 0b00000000000000000000000000000100,   // shadow RGBA mask
    CFLD_ALL                  = 0b11111111111111111111111111111111,   // all fields
    CFLD_NO_STATE_MASK        = 0b00111111111111111111111111111111    // all fields except the state of the cell
} cellfield_features;

// init every cell using a prototype cell and based on a stat system
void init_cell_zone (uint16_t canvasgroup_id, uint16_t canvas_id, Rectangle target, EX_cell info_cell, uint64_t state) {
    uint32_t target_offset, source_offset;
    EX_canvas *canvas = &sys.video.canvasgroup[canvasgroup_id].canvas[canvas_id];
    uint16_t lsx = canvas->size.x, lsy = canvas->size.y;    if (!lsx || !lsy) return; // empty canvas, can not process

    EX_cell  *target_cell  = &sys.video.canvasgroup[canvasgroup_id].canvas[canvas_id].cell[0];

    if (target.x >= lsx || target.y >= lsy || (target.x + target.width) < 0 || (target.y + target.height) < 0) return;

    for (uint16_t x = target.x; x++; x < (target.x + target.width)) {
        if (x >=0 && x < lsx ) {
            for (uint16_t y = target.y; y++; y < (target.y + target.height)) {
                if (y >= 0 && y < lsy) {
                    target_offset = lsx * y + x;
                    if (state & CFLD_ALL)                   target_cell[target_offset]                      = info_cell;
                    else {
                        if (state & CFLD_STATE)             target_cell[target_offset].state                = info_cell.state;
                        if (state & CFLD_VALUE)             target_cell[target_offset].value                = info_cell.value;
                        if (state & CFLD_LINES)             target_cell[target_offset].lines                = info_cell.lines;
                        if (state & CFLD_CYCLE)             target_cell[target_offset].cycle_id             = info_cell.cycle_id;
                        if (state & CFLD_FG_COLOR)          target_cell[target_offset].colorfg_id           = info_cell.colorfg_id;
                        if (state & CFLD_FG_COLOR_CYCLE)    target_cell[target_offset].colorfg_cycle_id     = info_cell.colorfg_cycle_id;
                        if (state & CFLD_BG_COLOR)          target_cell[target_offset].colorbg_id           = info_cell.colorbg_id;
                        if (state & CFLD_BG_COLOR_CYCLE)    target_cell[target_offset].colorbg_cycle_id     = info_cell.colorbg_cycle_id;
                        if (state & CFLD_LINES_COLOR)       target_cell[target_offset].colorln_id           = info_cell.colorln_id;
                        if (state & CFLD_LINES_COLOR_CYCLE) target_cell[target_offset].colorln_cycle_id     = info_cell.colorln_cycle_id;
                        if (state & CFLD_OFFSET)            target_cell[target_offset].offset               = info_cell.offset;
                        if (state & CFLD_SKEW)              target_cell[target_offset].skew                 = info_cell.skew;
                        if (state & CFLD_SCALE)             target_cell[target_offset].scale                = info_cell.scale;
                        if (state & CFLD_SCALE_SPEED)       target_cell[target_offset].scale_speed          = info_cell.scale_speed;
                        if (state & CFLD_SCROLL_SPEED)      target_cell[target_offset].scroll_speed         = info_cell.scroll_speed;
                        if (state & CFLD_ANGLE)             target_cell[target_offset].angle                = info_cell.angle;
                        if (state & CFLD_FG_BRIGHTNESS)     target_cell[target_offset].fg_brightness        = info_cell.fg_brightness;
                        if (state & CFLD_BG_BRIGHTNESS)     target_cell[target_offset].bg_brightness        = info_cell.bg_brightness;
                        if (state & CFLD_ALPHA)             target_cell[target_offset].alpha                = info_cell.alpha;
                        if (state & CFLD_COLOR_MASK)        target_cell[target_offset].color_mask           = info_cell.color_mask;
                        if (state & CFLD_SHADOW_MASK)       target_cell[target_offset].shadow_mask          = info_cell.shadow_mask;
                    }
                }
            }
        }
    }
}

void clear_cell (uint16_t canvasgroup_id, uint16_t canvas_id, Rectangle target, uint64_t state) {
    static inline EX_cell blank_cell;
    init_cell_zone(canvasgroup_id, canvas_id, target, blank_cell, state);
}

void shift_cell_field_rectangle(uint16_t canvasgroup_id, uint16_t canvas_id, Rectangle target, float shift, uint64_t state) {
    uint16_t target_offset;
    EX_canvas *canvas = &sys.video.canvasgroup[canvasgroup_id].canvas[canvas_id];
    uint16_t lsx = canvas->size.x, lsy = canvas->size.y;    if (!lsx || !lsy) return; // empty canvas, can not process

    EX_cell  *target_cell  = &sys.video.canvasgroup[canvasgroup_id].canvas[canvas_id].cell[0];

    if (target.x >= lsx || target.y >= lsy || (target.x + target.width) < 0 || (target.y + target.height) < 0) return;
    if ((target.x + target.width) > lsx) target.width = lsx - target.x; 
    if ((target.y + target.height) > lsy) target.height = lsy - target.y;

    for (uint16_t x = target.x; x++; x < (target.x + target.width)) {
        for (uint16_t y = target.y; y++; y < (target.y + target.height)) {
            target_offset = lsx * y + x;
            if (state & CFLD_STATE)             {target_cell[target_offset].state               += shift;} // 0xffffffff
            if (state & CFLD_VALUE)             {target_cell[target_offset].value               += shift;} // determined by texture # tiles
            if (state & CFLD_LINES)             {target_cell[target_offset].lines               += shift;} // 0...255
            if (state & CFLD_CYCLE)             {target_cell[target_offset].cycle_id            += shift;} // determined by texture # tiles
            if (state & CFLD_FG_COLOR)          {target_cell[target_offset].colorfg_id          += shift;} // 0...255 (or palette size)
            if (state & CFLD_FG_COLOR_CYCLE)    {target_cell[target_offset].colorfg_cycle_id    += shift;} // 0...255 (or palette size)
            if (state & CFLD_BG_COLOR)          {target_cell[target_offset].colorbg_id          += shift;} // 0...255 (or palette size)
            if (state & CFLD_BG_COLOR_CYCLE)    {target_cell[target_offset].colorbg_cycle_id    += shift;} // 0...255 (or palette size)
            if (state & CFLD_LINES_COLOR)       {target_cell[target_offset].colorln_id          += shift;} // 0...255 (or palette size)
            if (state & CFLD_LINES_COLOR_CYCLE) {target_cell[target_offset].colorln_cycle_id    += shift;} // 0...255 (or palette size)
            //if (state & CFLD_OFFSET)            {target_cell[target_offset].offset                += shift;} // Vector2 x,y
            //if (state & CFLD_SKEW)              {target_cell[target_offset].skew                  += shift;} // Vector2 x,y
            //if (state & CFLD_SCALE)             {target_cell[target_offset].scale                 += shift;} // Vector2 x,y
            //if (state & CFLD_SCALE_SPEED)       {target_cell[target_offset].scale_speed           += shift;} // 
            //if (state & CFLD_SCROLL_SPEED)      {target_cell[target_offset].scroll_speed          += shift;} // 
            if (state & CFLD_ANGLE)             {target_cell[target_offset].angle               += shift;} // 0...360
            if (state & CFLD_FG_BRIGHTNESS)     {target_cell[target_offset].fg_brightness       += shift;} // 0...255
            if (state & CFLD_BG_BRIGHTNESS)     {target_cell[target_offset].bg_brightness       += shift;} // 0...255
            //if (state & CFLD_COLOR_MASK)        {target_cell[target_offset].color_mask            += shift;} // Color
            //if (state & CFLD_SHADOW_MASK)       {target_cell[target_offset].shadow_mask           += shift;} // Color
        }
    }
}

void shift_cell_field_circle(uint16_t canvasgroup_id, uint16_t canvas_id, Rectangle target, float shift, uint64_t state) {
    uint32_t linear_offset;
    EX_canvas *canvas = &sys.video.canvasgroup[canvasgroup_id].canvas[canvas_id];
    uint16_t lsx = canvas->size.x, lsy = canvas->size.y;    if (!lsx || !lsy) return; // empty canvas, can not process

    EX_cell  *target_cell  = &sys.video.canvasgroup[canvasgroup_id].canvas[canvas_id].cell[0];

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
    CELLSHIFT_UP        = 1,
    CELLSHIFT_DOWN      = 2,
    CELLSHIFT_LEFT      = 3,
    CELLSHIFT_RIGHT     = 4,
    CELLSHIFT_UPLEFT    = 5,
    CELLSHIFT_DOWNLEFT  = 6,
    CELLSHIFT_UPRIGHT   = 7,
    CELLSHIFT_DOWNRIGHT = 8
} cell_direction;

void copy_cell_in_canvas(uint16_t canvasgroup_id, uint16_t canvas_id, Rectangle source, Vector2 target, uint64_t state) {
    uint32_t source_offset, target_offset;
    EX_canvas *canvas = &sys.video.canvasgroup[canvasgroup_id].canvas[canvas_id];
    uint16_t lsx = canvas->size.x, lsy = canvas->size.y;    if (!lsx || !lsy) return; // empty canvas, can not process

    EX_cell  *cell  = &sys.video.canvasgroup[canvasgroup_id].canvas[canvas_id].cell[0];
    
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
                    if (state & CFLD_ALL)                   cell[target_offset]                       = cell[source_offset];
                    else {
                        if (state & CFLD_STATE)             cell[target_offset].state               = cell[source_offset].state;
                        if (state & CFLD_VALUE)             cell[target_offset].value               = cell[source_offset].value;
                        if (state & CFLD_LINES)             cell[target_offset].lines               = cell[source_offset].lines;
                        if (state & CFLD_CYCLE)             cell[target_offset].cycle_id            = cell[source_offset].cycle_id;
                        if (state & CFLD_FG_COLOR)          cell[target_offset].colorfg_id          = cell[source_offset].colorfg_id;
                        if (state & CFLD_FG_COLOR_CYCLE)    cell[target_offset].colorfg_cycle_id    = cell[source_offset].colorfg_cycle_id;
                        if (state & CFLD_BG_COLOR)          cell[target_offset].colorbg_id          = cell[source_offset].colorbg_id;
                        if (state & CFLD_BG_COLOR_CYCLE)    cell[target_offset].colorbg_cycle_id    = cell[source_offset].colorbg_cycle_id;
                        if (state & CFLD_LINES_COLOR)       cell[target_offset].colorln_id          = cell[source_offset].colorln_id;
                        if (state & CFLD_LINES_COLOR_CYCLE) cell[target_offset].colorln_cycle_id    = cell[source_offset].colorln_cycle_id;
                        if (state & CFLD_OFFSET)            cell[target_offset].offset              = cell[source_offset].offset;
                        if (state & CFLD_SKEW)              cell[target_offset].skew                = cell[source_offset].skew;
                        if (state & CFLD_SCALE)             cell[target_offset].scale               = cell[source_offset].scale;
                        if (state & CFLD_SCALE_SPEED)       cell[target_offset].scale_speed         = cell[source_offset].scale_speed;
                        if (state & CFLD_SCROLL_SPEED)      cell[target_offset].scroll_speed        = cell[source_offset].scroll_speed;
                        if (state & CFLD_ANGLE)             cell[target_offset].angle               = cell[source_offset].angle;
                        if (state & CFLD_FG_BRIGHTNESS)     cell[target_offset].fg_brightness       = cell[source_offset].fg_brightness;
                        if (state & CFLD_BG_BRIGHTNESS)     cell[target_offset].bg_brightness       = cell[source_offset].bg_brightness;
                        if (state & CFLD_COLOR_MASK)        cell[target_offset].color_mask          = cell[source_offset].color_mask;
                        if (state & CFLD_SHADOW_MASK)       cell[target_offset].shadow_mask         = cell[source_offset].shadow_mask;
                    }
                }
                x += xi; if (xi == 1) {if (x >= xb) break;} else if (x < xb) break;
            }
        }
        y += yi; if (yi == 1) {if (y >= yb) break;} else if (y < yb) break;
    }
}

// Move cell content to any of 8 directions
void shift_cell (uint16_t canvasgroup_id, uint16_t canvas_id, Rectangle source, uint8_t shift_method, bool cycle, uint64_t state) {
    uint32_t source_offset, target_offset;
    EX_canvas *canvas = &sys.video.canvasgroup[canvasgroup_id].canvas[canvas_id];
    uint16_t lsx = canvas->size.x, lsy = canvas->size.y;    if (!lsx || !lsy) return; // empty canvas, can not process
    EX_cell  *cell  = &sys.video.canvasgroup[canvasgroup_id].canvas[canvas_id].cell[0];

    //if (source.x >= lsx || source.y >= lsy || target.x >= lsx || target.y >= lsy) return;
    //if ((source.x + source.width) < 0 || (source.y + source.height) < 0 || (target.x + source.width) < 0 || (target.y + source.height) < 0) return;
    if ((source.x + source.width) > lsx) source.width = lsx - source.x;
    if ((source.y + source.width) > lsy) source.width = lsy - source.y;

}

void copy_cell_to_canvas(uint16_t source_canvasgroup_id, uint16_t source_canvas_id, Rectangle source, uint16_t target_canvasgroup_id, uint16_t target_canvas_id, Vector2 target, uint64_t state) {
    uint32_t source_offset, target_offset;

    EX_canvas *source_canvas = &sys.video.canvasgroup[source_canvasgroup_id].canvas[source_canvas_id];
    uint16_t lsx = source_canvas->size.x, lsy = source_canvas->size.y;    if (!lsx || !lsy) return; // empty canvas, can not process

    EX_cell  *source_cell  = &sys.video.canvasgroup[source_canvasgroup_id].canvas[source_canvas_id].cell[0];

    EX_canvas *target_canvas = &sys.video.canvasgroup[target_canvasgroup_id].canvas[target_canvas_id];
    uint16_t ltx = target_canvas->size.x, lty = target_canvas->size.y;
    EX_cell  *target_cell  = &sys.video.canvasgroup[target_canvasgroup_id].canvas[target_canvas_id].cell[0];

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

//    if (!(state & CVFE_PROTECTED))   // if not protected destination field, then you can write

                    if (state & CFLD_ALL)                   target_cell[target_offset]                      = source_cell[source_offset];
                    else {
                        if (state & CFLD_STATE)             target_cell[target_offset].state                = source_cell[source_offset].state;
                        if (state & CFLD_VALUE)             target_cell[target_offset].value                = source_cell[source_offset].value;
                        if (state & CFLD_LINES)             target_cell[target_offset].lines                = source_cell[source_offset].lines;
                        if (state & CFLD_CYCLE)             target_cell[target_offset].cycle_id             = source_cell[source_offset].cycle_id;
                        if (state & CFLD_FG_COLOR)          target_cell[target_offset].colorfg_id           = source_cell[source_offset].colorfg_id;
                        if (state & CFLD_FG_COLOR_CYCLE)    target_cell[target_offset].colorfg_cycle_id     = source_cell[source_offset].colorfg_cycle_id;
                        if (state & CFLD_BG_COLOR)          target_cell[target_offset].colorbg_id           = source_cell[source_offset].colorbg_id;
                        if (state & CFLD_BG_COLOR_CYCLE)    target_cell[target_offset].colorbg_cycle_id     = source_cell[source_offset].colorbg_cycle_id;
                        if (state & CFLD_LINES_COLOR)       target_cell[target_offset].colorln_id           = source_cell[source_offset].colorln_id;
                        if (state & CFLD_LINES_COLOR_CYCLE) target_cell[target_offset].colorln_cycle_id     = source_cell[source_offset].colorln_cycle_id;
                        if (state & CFLD_OFFSET)            target_cell[target_offset].offset               = source_cell[source_offset].offset;
                        if (state & CFLD_SKEW)              target_cell[target_offset].skew                 = source_cell[source_offset].skew;
                        if (state & CFLD_SCALE)             target_cell[target_offset].scale                = source_cell[source_offset].scale;
                        if (state & CFLD_SCALE_SPEED)       target_cell[target_offset].scale_speed          = source_cell[source_offset].scale_speed;
                        if (state & CFLD_SCROLL_SPEED)      target_cell[target_offset].scroll_speed         = source_cell[source_offset].scroll_speed;
                        if (state & CFLD_ANGLE)             target_cell[target_offset].angle                = source_cell[source_offset].angle;
                        if (state & CFLD_FG_BRIGHTNESS)     target_cell[target_offset].fg_brightness        = source_cell[source_offset].fg_brightness;
                        if (state & CFLD_BG_BRIGHTNESS)     target_cell[target_offset].bg_brightness        = source_cell[source_offset].bg_brightness;
                        if (state & CFLD_COLOR_MASK)        target_cell[target_offset].color_mask           = source_cell[source_offset].color_mask;
                        if (state & CFLD_SHADOW_MASK)       target_cell[target_offset].shadow_mask          = source_cell[source_offset].shadow_mask;
                    }
                }
            }
        }
    }
}

void copy_canvas() {
    // copy canvas routine, mostly used for backup restore of canvas content from / to a copy buffer
    // potentially use calloc.... then ....memcpy(dest, src, len);
}

void render_canvas(uint16_t canvas_id) {
    static Color vertex_colors[4];
    uint16_t canvasgroup_id = sys.video.current_virtual; // A single canvasgroup per Virtual Display

    EX_canvas *canvas = &sys.video.canvasgroup[canvasgroup_id].canvas[canvas_id];
    EX_cell  *cell  = &sys.video.canvasgroup[canvasgroup_id].canvas[canvas_id].cell[0];
    uint32_t cell_offset;
    Vector2 rendersize = get_current_virtual_size();
    Vector2 shadow = canvas->shadow;
    uint16_t lsx = canvas->size.x, lsy = canvas->size.y;    if (!lsx || !lsy) return; // empty canvas, can not process

    Vector2 tsize, tscaled, offset, cellpos, skew; // per cell calculated values

    for (uint16_t x = 0; x < lsx; x++) {
        for (uint16_t y = 0; y < lsy; y++) {
            cell_offset = (lsx * y + x);
            EX_cell *c = &cell[cell_offset];
            uint64_t state = c->state;

            // establish scaling on screen....  For a 512x224 display = 64x28 tiles of 8 x 8 pixels, for that we need a ratio for x and y
            tsize  = canvas->default_tilesize;
            if (state & CVFE_SCALE_X) tscaled.x = c->scale.x * tsize.x; else tscaled.x = tsize.x;
            if (state & CVFE_SCALE_Y) tscaled.y = c->scale.y * tsize.y; else tscaled.y = tsize.y;
            offset = c->offset;
            cellpos = (Vector2){canvas->offset.x + offset.x + x * tsize.x, canvas->offset.y + offset.y + y * tsize.y};
            if (!(state & CVFE_SKEW))     skew = (Vector2){0}; else skew = c->skew;

            // if inbound proceed to draw cell tiles
            if (((cellpos.x + tscaled.x + skew.x) >= 0) && ((cellpos.y + tscaled.y + skew.y) >= 0) && (cellpos.x <= rendersize.x) && (cellpos.y <= rendersize.y)) {

/*  
    if (state & CVFE_LINESSEQ)            // turn on lines sequencing
    if (state & CVFE_COLORSEQ)            // turn on color sequencing
    if (state & CVFE_VALUESEQ)            // turn on cell value sequencing
    if (state & CVFE_AUTOSCRX)            // turn on automatic scrolling on x axis
    if (state & CVFE_AUTOSCRY)            // turn on automatic scrolling on y axis
    if (state & CVFE_CELLDIS)             // then allow corner displacements
    if (state & CVFE_WRAP_X)              // turn on wrap around on x axis
    if (state & CVFE_WRAP_Y)              // turn on wrap around on y axis
    if (state & CVFE_FLIPH)               // flip cell(s) horizontally
    if (state & CVFE_FLIPV)               // flip cell(s) vertically
*/
                uint16_t palette_id = c->palette_id;   if (!palette_id) palette_id = canvas->default_palette_id;

                // for now only canvas alpha supported, per cell alpha will force to use float to combine canvas and cell alpha (potentially), or set the texture alpha as the canvas alpha
                Color colorfg = get_palette_color_pro(palette_id, c->colorfg_id, 255, c->fg_brightness * canvas->fg_brightness); // canvas->alpha
                Color colorbg = get_palette_color_pro(palette_id, c->colorbg_id, 255, c->bg_brightness * canvas->bg_brightness); // canvas->alpha
                Color colorln = get_palette_color(palette_id, c->colorln_id);
 
                float angle = angle = c->angle;     if (!(state & CVFE_ROTATION))  angle = 0.f;

                if (state & CVFE_BACKGROUND) {
                    // background set color of corner to color of next tile 
                    //    CVFE_BGBLEND_LL       // background vertex color blend lower left
                    //    CVFE_BGBLEND_LR       // background vertex color blend lower right
                    //    CVFE_BGBLEND_UR       // background vertex color blend upper right
                    //    CVFE_BGBLEND_UL       // background vertex color blend upper left
                    // to elaborate color blending between tiles... (will involve snooping all 4 directions for color depend on blending options)
                    if (state & CVFE_RED)   vertex_colors[0].r = colorbg.r; else vertex_colors[0].r = 0;
                    if (state & CVFE_GREEN) vertex_colors[0].g = colorbg.g; else vertex_colors[0].g = 0;
                    if (state & CVFE_BLUE)  vertex_colors[0].b = colorbg.b; else vertex_colors[0].b = 0;
                    if (state & CVFE_ALPHA) vertex_colors[0].a = colorbg.a; else vertex_colors[0].a = 0;
                    vertex_colors[1] = vertex_colors[0]; //  for now just copy the color content to all corners... (TEMPORARY) *******************
                    vertex_colors[2] = vertex_colors[0];
                    vertex_colors[3] = vertex_colors[0];
                    DrawRectanglePro2(
                        (Rectangle) { cellpos.x, cellpos.y, tscaled.x, tscaled.y },
                        (Vector2) {0,0}, (Vector2) {0,0}, angle, vertex_colors);
                }
                uint16_t asset_id = c->asset_id;     if (!asset_id) asset_id = canvas->default_asset_id;
                if (state & CVFE_FOREGROUND) {
                    if (state & CVFE_SHADOW) {
                        if (shadow.x != 0 || shadow.y != 0) {
                            vertex_colors[0] = (Color) {0.f, 0.f, 0.f, 48.f};
                            vertex_colors[1] = (Color) {0.f, 0.f, 0.f, 48.f};
                            vertex_colors[2] = (Color) {0.f, 0.f, 0.f, 48.f};
                            vertex_colors[3] = (Color) {0.f, 0.f, 0.f, 48.f};
                            DrawTexturePro2(sys.asset.tex[asset_id],
                                get_tilezone_from_code(asset_id, c->value),
                                (Rectangle) { cellpos.x + shadow.x, cellpos.y + shadow.y, tscaled.x, tscaled.y },
                                (Vector2) {0,0}, skew, angle, vertex_colors);
                        }
                    };
                    // we have the cell data we can use it to draw our background, foreground and shadow
                    // reading color from palette get_palette_color(palette,id);
                    // foreground set color of corner to color of next tile 
                    //    CVFE_FGBLEND_LL       // foreground vertex color blend lower left
                    //    CVFE_FGBLEND_LR       // foreground vertex color blend lower right
                    //    CVFE_FGBLEND_UR       // foreground vertex color blend upper right
                    //    CVFE_FGBLEND_UL       // foreground vertex color blend upper left
                    if (state & CVFE_RED)   vertex_colors[0].r = colorfg.r; else vertex_colors[0].r = 0;
                    if (state & CVFE_GREEN) vertex_colors[0].g = colorfg.g; else vertex_colors[0].g = 0;
                    if (state & CVFE_BLUE)  vertex_colors[0].b = colorfg.b; else vertex_colors[0].b = 0;
                    if (state & CVFE_ALPHA) vertex_colors[0].a = colorfg.a; else vertex_colors[0].a = 0;
                    vertex_colors[1] = vertex_colors[0];
                    vertex_colors[2] = vertex_colors[0];
                    vertex_colors[3] = vertex_colors[0];
                    DrawTexturePro2(sys.asset.tex[asset_id],
                        get_tilezone_from_code(asset_id, c->value),
                        (Rectangle) { cellpos.x, cellpos.y , tscaled.x, tscaled.y },
                        (Vector2) {0,0}, skew, angle, vertex_colors);
                }

                uint8_t lines = GET_FROM_STATE(state, CVFE_LINES_MASK, CVFE_LINES_BITS);
                if (lines) {
                    if (state & CVFE_RED)   vertex_colors[0].r = colorln.r; else vertex_colors[0].r = 0;
                    if (state & CVFE_GREEN) vertex_colors[0].g = colorln.g; else vertex_colors[0].g = 0;
                    if (state & CVFE_BLUE)  vertex_colors[0].b = colorln.b; else vertex_colors[0].b = 0;
                    if (state & CVFE_ALPHA) vertex_colors[0].a = colorln.a; else vertex_colors[0].a = 0;
                    vertex_colors[1] = vertex_colors[0];
                    vertex_colors[2] = vertex_colors[0];
                    vertex_colors[3] = vertex_colors[0];
                    DrawTexturePro2(sys.asset.tex[sys.asset.lines_id],
                        get_tilezone_from_code(sys.asset.lines_id, lines),
                        (Rectangle) { cellpos.x, cellpos.y , tscaled.x, tscaled.y },
                        (Vector2) {0,0}, skew, angle, vertex_colors);
                }
                //DrawText(TextFormat("%c", (char)c->value), cellpos.x, cellpos.y, 5, WHITE); // DEBUG!!!!!!!!!!!!!!!!!!!!!!!!!!
                //DrawText(TextFormat("%i", asset_id), cellpos.x, cellpos.y, 10, WHITE); // DEBUG!!!!!!!!!!!!!!!!!!!!!!!!!!
                //DrawText(TextFormat("%i", palette_id), cellpos.x, cellpos.y, 10, WHITE); // DEBUG!!!!!!!!!!!!!!!!!!!!!!!!!!
            }
        }
    }
    //DrawText(TextFormat("CANVAS SIZE = %ix%i", lsx, lsy), 0, 0, 10, GREEN); // DEBUG!!!!!!!!!!!!!!!!!!!!!!!!!!
//logic to show mouse cursor
//IsCursorOnScreen(void)
//RLAPI Vector2 GetMousePosition(void);
}

void render_canvasgroup(void) {
    uint16_t canvasgroup_id = sys.video.current_virtual; // A single canvasgroup per Virtual Display
    //EX_canvasgroup  *canvasgroup  = &sys.video.canvasgroup[canvasgroup_id];

    begin_draw(true);
    for (uint16_t i = 0; i < sys.video.canvasgroup[canvasgroup_id].canvas_count; i++) {
        // get_current_virtual_size()
        render_canvas(i);
    }
    return 0;
    end_draw();
}

// does the execution of the modifiers
void process_canvas(uint16_t canvas_id) {
    // modifiers logic
    // temporal considerations
}

int16_t process_canvasgroup(uint16_t canvasgroup_id) {
    uint16_t canvas_id = 0;
    process_canvas(canvas_id);
}


// ********** C A N V A S   S Y S T E M  ***** C A N V A S   S Y S T E M  ***** C A N V A S   S Y S T E M  ***** E N D
// ********** C A N V A S   S Y S T E M  ***** C A N V A S   S Y S T E M  ***** C A N V A S   S Y S T E M  ***** E N D
// ********** C A N V A S   S Y S T E M  ***** C A N V A S   S Y S T E M  ***** C A N V A S   S Y S T E M  ***** E N D

// ********** P A R T I C L E   S Y S T E M  ***** P A R T I C L E   S Y S T E M  ***** P A R T I C L E   S Y S T E M  ***** B E G I N
// ********** P A R T I C L E   S Y S T E M  ***** P A R T I C L E   S Y S T E M  ***** P A R T I C L E   S Y S T E M  ***** B E G I N
// ********** P A R T I C L E   S Y S T E M  ***** P A R T I C L E   S Y S T E M  ***** P A R T I C L E   S Y S T E M  ***** B E G I N

typedef enum {
    PTFE_RESERVED       = 0b10000000000000000000000000000000, //
    PTFE_ROTATION       = 0b00000000001000000000000000000000, // turn on rotation
    PTFE_SCALE          = 0b00000000000100000000000000000000, // turn on scaling
    PTFE_R              = 0b00000000000000010000000000000000, // turn on red channel
    PTFE_G              = 0b00000000000000001000000000000000, // turn on green channel
    PTFE_B              = 0b00000000000000000100000000000000, // turn on blue channel
    PTFE_A              = 0b00000000000000000010000000000000, // turn on alpha channel
    PTFE_STAY           = 0b00000000000000000000001000000000, // does not move using speedX, speedY
    PTFE_HIDE           = 0b00000000000000000000000010000000, // does not display
    PTFE_FREEZE         = 0b00000000000000000000000000100000, // does not move at all or animate, speedX, speedY, xsin, ysin
    PTFE_DYING          = 0b00000000000000000000000000001000, // expiration sequence
    PTFE_EXPIRED        = 0b00000000000000000000000000000010, // decomissionned
    PTFE_ACTIVE         = 0b00000000000000000000000000000001
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
	Vector2 res = get_current_virtual_size();
	particle p;
	p.texture = texture;
	p.position = r1;
	//p.size = sys.video.vscreen[sys.video.current_virtual].size;
	
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

int16_t update_particle(particle *particle, Vector2 velocity) {
	Vector2 res = get_current_virtual_size();
    velocity.x *= sys.video.vscreen[sys.video.current_virtual].frame_time;
    velocity.y *= sys.video.vscreen[sys.video.current_virtual].frame_time;
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
    Vector2 vres = get_current_virtual_size();
	float size_x = vres.x / (float)segments;
    float amp = (vres.y * scale) - (size_y * 0.5);
    for(uint16_t y = 0; y < coppers; y++) {
        copper = y % 16;
        for(uint16_t x = 0; x < segments; x++) {
            y_start = amp + fast_sin((sys.video.vscreen[sys.video.current_virtual].frame_time_inc * ratio.x) - rastoffset*((float)y*ratio.y)-((float)x * sys.video.vscreen[sys.video.current_virtual].value_anim * ratio.z)) * amp + offset.y;
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

static int16_t update_marquee_animation(uint16_t asset_id, uint16_t palette_id, Vector2 logosize, float transparency, Vector2 offset, float speed, float shadow_transparency) {
    uint16_t display = sys.video.current_virtual;
    Vector2 vres = get_current_virtual_size();
    if (ex_marquee[display].palptr_next_frame_time < sys.video.vscreen[display].frame_time_inc) {
        ex_marquee[display].palptr_next_frame_time = sys.video.vscreen[display].frame_time_inc + 1/ffast_abs(speed);
        if (speed > 0.0f)  ex_marquee[display].palptr += 1;  else  ex_marquee[display].palptr -= 1;
        if (ex_marquee[display].palptr > 255) {ex_marquee[display].palptr -= 256;} else if (ex_marquee[display].palptr < 0) {ex_marquee[display].palptr += 256;};
    };
    int32_t palptr_loop = ex_marquee[display].palptr;

    if (transparency > 0.0f) {
        Vector2 scale = {(255.0f - transparency) * 0.01f + 1.0f, 1.0f};
        Vector2 final_offset = {offset.x + (vres.x-(logosize.x * scale.x))/2.0, offset.y};
        for(uint16_t i = 0; i < logosize.y; i++) {
            if (palptr_loop > 255) {palptr_loop -= 256;} else if (palptr_loop < 0) {palptr_loop += 256;};
            
            Color rgba = get_palette_color(palette_id, palptr_loop);
            
            float shadow_alpha = (transparency * shadow_transparency);
            if (shadow_alpha > 0) {
                DrawTexturePro( sys.asset.tex[asset_id],
                (Rectangle) { 0, i, logosize.x, 1 }, 
                (Rectangle) {final_offset.x + fast_sin(sys.video.vscreen[sys.video.current_virtual].frame_time_inc + sys.video.vscreen[sys.video.current_virtual].value_anim * (float) i * 2.0) * 32.0 + 2, final_offset.y+i + 4, logosize.x * scale.x, 1 }, 
                (Vector2) { 0, 0 }, 0, (Color){0, 0, 0, shadow_alpha} );
            }

            DrawTexturePro( sys.asset.tex[asset_id],
            (Rectangle) { 0, i, logosize.x, 1 }, 
            (Rectangle) {final_offset.x + fast_sin(sys.video.vscreen[sys.video.current_virtual].frame_time_inc + sys.video.vscreen[sys.video.current_virtual].value_anim * (float) i * 2.0) * 32.0, final_offset.y+i, logosize.x * scale.x, 1 }, 
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

#define CANOPYMAX_X 64
#define CANOPYMAX_Y 32

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
    Vector2 grid[CANOPYMAX_Y][CANOPYMAX_X]; // set to max capacity
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

static int16_t update_canopy(uint16_t asset_id) {
    Vector2 vres = get_current_virtual_size();
    ex_canopy.offset.x = (vres.x - ((ex_canopy.cells_x) * ex_canopy.cell_size.x)) * 0.5f;
    ex_canopy.offset.y = 7.0f * ex_canopy.cell_size.x + (255.f - ex_canopy.transparency);
    if ((ex_canopy.transparency > 0.0f) & (ex_canopy.offset.y <= vres.y)) {
            
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
                ex_canopy.sin_value.y += (ex_canopy.adjustment.y + fast_sin(sys.video.vscreen[sys.video.current_virtual].frame_time_inc) * 0.005f);
            }

            ex_canopy.sin_value.y += (ex_canopy.cells_y/ex_canopy.cells_x)*1.0665f;  // this is the depth of the waves
            ex_canopy.sin_value.x = ex_canopy.sin_value_old.x;
        }
        ex_canopy.sin_value.y = ex_canopy.sin_value_old.y + 0.05f * sys.video.vscreen[sys.video.current_virtual].frame_time;  // this is the vertical wave movement per frame
    }
    ex_canopy.transparency +=ex_canopy.transparency_mod * sys.video.vscreen[sys.video.current_virtual].frame_time;
    if (ex_canopy.transparency > 255.0f) {ex_canopy.transparency = 255.0f;} else if (ex_canopy.transparency < 0.0f) {ex_canopy.transparency = 0.0f;};
};

const Color colorbar[] = {{255,255,255,255}, {255,255,0,255}, {0,255,255,255}, {0,255,0,255}, {255,0,255,255}, {255,0,0,255}, {0,0,255,255}, {0,0,0,255}};

static void draw_colorbar(void) {
    Vector2 vres = get_current_virtual_size();
    uint16_t bar_count = sizeof(colorbar) / sizeof(Color);
    float x = vres.x * 1/bar_count;
    for (uint16_t i = 0; i < bar_count; i++) {
        DrawRectangle(i * x, 0, x, vres.y, (Color) colorbar[i]);        
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

// picks from the Atari 256 GTIA colors as indexed
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

static int16_t update_scrolltext(uint16_t s, float text_scale) {
    uint16_t palette_id = ex_scrolltext[s].palette_id;
    Vector2 vres = get_current_virtual_size();
    
    if (ex_scrolltext[s].text_pause <= 0.0) {
        ex_scrolltext[s].position.x -= (sys.video.vscreen[sys.video.current_virtual].frame_time * ex_scrolltext[s].text_scroll_speed) / text_scale;
    } else {
        ex_scrolltext[s].text_pause -= sys.video.vscreen[sys.video.current_virtual].frame_time;
    };

    uint16_t id;
    float et_var = sys.video.vscreen[sys.video.current_virtual].elapsed_time_var;
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
            if(((ex_scrolltext[s].position.x + (i_x - 1)) * text_scale ) < vres.x && ((ex_scrolltext[s].position.x + (i_x + 2)) * text_scale ) > 0) {
                if (ch == SCROLL_PAUSE) { // pause the scroll x amount of seconds (a-z = 1 to 26 seconds)
                    i++;
                    if (ex_scrolltext[s].pause_found != (i - 1)) {
                        ex_scrolltext[s].pause_found = i - 1;
                        if (ex_scrolltext[s].text_pause <= 0.0) {
                            ex_scrolltext[s].text_pause = sys.video.vscreen[sys.video.display_id].refresh_rate * (float)(sys.asset.data[ex_scrolltext[s].asset_id][i] - 96); // set pause for x secs (a-z=1-26)
                        };
                    }
                } else if (ch == SCROLL_TEXTSPEED) { // set the speed of the scrolling text (a-z = slow to very fast)
                    i++;
                    ex_scrolltext[s].text_scroll_speed = (float)sys.asset.data[ex_scrolltext[s].asset_id][i] - 96.0;
                } else if (ch == SCROLL_FADEFLAG) { // fade in the flag
                    i++;
                    if (sys.asset.data[ex_scrolltext[s].asset_id][i] == 97 ) // a = fade in, any other charqacters = fade out (...)
                        ex_canopy.transparency_mod = 1.0f;
                    else
                        ex_canopy.transparency_mod = -1.0f;
                } else if (ch < 97 && ch > 31) { // let upper case letters pass and numbers and other basic characters
                    if (ex_scrolltext[s].text_wave_flag == 1)
                        ex_scrolltext[s].text_wave = displacement.y;
                    else if (ex_scrolltext[s].text_wave_flag == 2)
                        ex_scrolltext[s].text_wave = displacement.y * 2;
                    else if (ex_scrolltext[s].text_wave_flag == 3)
                        ex_scrolltext[s].text_wave = displacement.y * 4;
                    else
                        ex_scrolltext[s].text_wave = 0;

                    if (ex_scrolltext[s].colorfg_flag == 1) {
                        ex_scrolltext[s].colorfg = (int16_t)(displacement.y * 0.5f) + 7;
                    };
                    if (ex_scrolltext[s].text_pause > 0.0 || ex_scrolltext[s].text_wave_flag == 0) {
                        ex_scrolltext[s].text_angle = 0;
                    } else {
                        ex_scrolltext[s].text_angle = displacement.y;
                    };

                    uint64_t state = CVFE_DEFAULT2;
                    if (ex_scrolltext[s].colorbg_flag == 0) BITS_OFF(state, CVFE_BACKGROUND);
                    if (!(ex_scrolltext[s].text_angle))     BITS_OFF(state, CVFE_ROTATION);
                    if (ex_scrolltext[s].text_shadow == 0.0) BITS_OFF(state, CVFE_SHADOW);
                    if (ex_scrolltext[s].text_angle)        BITS_OFF(state, CVFE_SKEW);

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
        ex_scrolltext[s].position.x = vres.x / text_scale;
        ex_scrolltext[s].pause_found = 0;
    };
}

// ********** S C R O L L T E X T   S Y S T E M  ***** S C R O L L T E X T   S Y S T E M  ***** S C R O L L T E X T   S Y S T E M  ***** E N D
// ********** S C R O L L T E X T   S Y S T E M  ***** S C R O L L T E X T   S Y S T E M  ***** S C R O L L T E X T   S Y S T E M  ***** E N D
// ********** S C R O L L T E X T   S Y S T E M  ***** S C R O L L T E X T   S Y S T E M  ***** S C R O L L T E X T   S Y S T E M  ***** E N D

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

int16_t init_audio_properties(void) {
    bool status = 0;
    InitAudioDevice();
    sys.audio.total_tracks = 0;
    sys.audio.global_volume = 0.5f;
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

int16_t update_audio(void) {
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
    //uint16_t asset = sys.audio.track[].asset_playing;

    //uint16_t total_orders = sizeof(orderlist[0]) / sizeof(int);
    for (uint16_t i = 0; i < total_orders; i++) {
        sys.audio.track[track_id].order[i] = orderlist[i];
    }
    sys.audio.track[track_id].total_orders = total_orders;

    sys.audio.total_tracks += 1;
    return track_id;
}

//StopMusicStream(sys.asset.music[asset]);
void change_music_stream(uint16_t track_id, uint16_t order_id, bool immediate) {
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
    VIDEO_ON_TOP         = 0b00001000000000000000000000000000, // 
    VIDEO_MOVE_X         = 0b00000000000000000100000000000000, // 
    VIDEO_MOVE_Y         = 0b00000000000000000010000000000000, // 
    VIDEO_HIDDEN         = 0b00000000000000000000000010000000, // 
    VIDEO_FROZEN         = 0b00000000000000000000000000100000, // 
    VIDEO_EXPIRING       = 0b00000000000000000000000000001000, // 
    VIDEO_EXPIRED        = 0b00000000000000000000000000000010, // 
    VIDEO_ACTIVE         = 0b00000000000000000000000000000001  // 
};

void begin_draw(bool clear) {
    BeginTextureMode(sys.asset.framebuffer[sys.video.vscreen[sys.video.current_virtual].asset_id]);
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
    (Rectangle) {position.x, position.y, sys.video.screen.x, sys.video.screen.y},
    (Vector2)   {0.0, 0.0}, 0.0f, WHITE);
}

static uint16_t init_frame_buffer(uint16_t display, Vector2 resolution) {
    flip_frame_buffer(display, true);
    sys.video.vscreen[sys.video.current_virtual].size = resolution;
    sys.video.vscreen[sys.video.current_virtual].frames = 0;
    sys.video.vscreen[sys.video.current_virtual].elapsed_time_var_ratio = 5.f;
    sys.video.vscreen[sys.video.current_virtual].frame_time_inc = 0;
	uint16_t asset_id = load_asset(ASSET_FRAMEBUFFER, NULL, NULL, NULL, NULL, 0);
    flip_frame_buffer(sys.video.previous_virtual, true);
    return asset_id;
}

int16_t init_display_properties(bool hide_mouse) {
    int16_t status = 0;
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
    sys.video.screen = (Vector2){GetScreenWidth(), GetScreenHeight()};
    sys.video.vscreen[sys.video.display_id].refresh_rate = GetMonitorRefreshRate(sys.video.display_id);
    SetWindowSize(sys.video.screen.x, sys.video.screen.y);

    if (IsWindowReady()) return status; else return 1;
}

void flip_display_state(uint32_t state) {
    if (!(sys.program.ctrlstate & CTRL_OFF_FOCUS))
        BITS_FLIP(sys.video.windowstate_normal, state);
    else
        BITS_FLIP(sys.video.windowstate_paused, state);
        
    if (IsWindowState(state)) { 
        ClearWindowState(state);
    } else {
        SetWindowState(state);
        // if (state & FLAG_VSYNC_HINT)  // ***GLFW issue with Refresh rate reset to 60 on VSYNC
        // since this is an issue, if we really want to do this right, we would have to possibly reload all assets
    }
}

    // The way this works right now is not proper, as we have 4-5 different virtual display, we need a way to display them all at once,
    // or at least display the MENU + possibly the Terminal + the game
    // So first, the rendering to a texture part, needs to be expanded
    // then update_system needs to take into account the different virtual displays and how to decide on;
    // - The order in which they should be displayed
    // - Should they display
    // - And their alpha blending
int16_t update_display(void) {
    int16_t status = 0;
    uint16_t display = sys.video.current_virtual;


    double next_frame = sys.video.vscreen[display].prev_time + (double)(1 / sys.video.vscreen[sys.video.display_id].refresh_rate);
    float wait = (next_frame - GetTime());
    if (wait < 0) wait = 0;
    WaitTime(wait * 1000.f);

    double current_time = GetTime();

    sys.video.vscreen[display].elapsed_time = current_time - sys.video.vscreen[display].prev_time;
    sys.video.vscreen[display].prev_time = current_time;

    if (sys.video.screen_refresh) {
        //sys.video.screen_refresh = false;
        BeginDrawing();
        ClearBackground(BLANK);
        draw_frame_buffer(sys.asset.framebuffer[sys.video.vscreen[display].asset_id], sys.video.vscreen[display].offset);
        if (active_service(CTRL_TERMINAL_SERVICE_MASK)) {
            draw_frame_buffer(sys.asset.framebuffer[sys.video.vscreen[TERMINALDISPLAY].asset_id], sys.video.vscreen[TERMINALDISPLAY].offset);
        }
        if (active_service(CTRL_DEBUG_SERVICE_MASK)) {
            status = update_debug();
        }
        EndDrawing();
        sys.video.vscreen[display].frame_time = (float)sys.video.vscreen[display].elapsed_time * (float)sys.video.vscreen[sys.video.display_id].refresh_rate;
        sys.video.vscreen[display].frame_time_inc += (float)sys.video.vscreen[display].elapsed_time;
        sys.video.vscreen[display].elapsed_time_var += (float)sys.video.vscreen[display].elapsed_time * sys.video.vscreen[display].elapsed_time_var_ratio;
        sys.video.vscreen[display].value_anim = fast_sin(fast_cos(fast_sin(sys.video.vscreen[display].frame_time_inc) * fast_sin(sys.video.vscreen[display].elapsed_time_var * 0.1) * 0.1) * fast_cos(sys.video.vscreen[display].elapsed_time_var * 0.015) * 0.1 ) * 0.05 + 0.001;        sys.video.vscreen[display].frames++;
    };

   sys.video.window_focus = IsWindowFocused();
   if (sys.video.window_focus) {        // ************** GO TO APP MODE
        if (sys.program.ctrlstate & CTRL_OFF_FOCUS) {
            if (GetKeyPressed() != 0) {
                BITS_OFF(sys.program.ctrlstate, CTRL_OFF_FOCUS);
                flip_frame_buffer(PRIMARYDISPLAY, true);
                ClearWindowState(sys.video.windowstate_normal ^ sys.video.windowstate_paused);
                SetWindowState(sys.video.windowstate_normal);
                sys.video.vscreen[sys.video.current_virtual].prev_time = current_time;
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
            sys.video.vscreen[sys.video.current_virtual].prev_time = current_time;
        };
    };
}

void deinit_display(void) {
    ShowCursor();
	CloseWindow();
}

// ********** V I D E O   S Y S T E M  ***** V I D E O   S Y S T E M  ***** V I D E O   S Y S T E M  ***** E N D
// ********** V I D E O   S Y S T E M  ***** V I D E O   S Y S T E M  ***** V I D E O   S Y S T E M  ***** E N D
// ********** V I D E O   S Y S T E M  ***** V I D E O   S Y S T E M  ***** V I D E O   S Y S T E M  ***** E N D

// ********** T E R M I N A L   S Y S T E M  ***** T E R M I N A L   S Y S T E M  ***** T E R M I N A L   S Y S T E M  ***** B E G I N
// ********** T E R M I N A L   S Y S T E M  ***** T E R M I N A L   S Y S T E M  ***** T E R M I N A L   S Y S T E M  ***** B E G I N
// ********** T E R M I N A L   S Y S T E M  ***** T E R M I N A L   S Y S T E M  ***** T E R M I N A L   S Y S T E M  ***** B E G I N

// eventually we want to remove all the hardcoded key bindings to allow AZERTY QWERTY QWERTZ etc...
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
    CMD_PM      = 94,   // ^    Privacy message (String Control Sequence)
    CMD_APC     = 95,   // _    Application Program Command (for embedding custom commands)

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
    CMD_Y       = 89,   // (VT-52) Direct cursor address, example: CSIY10 20
    CMD_Z       = 90,   // (VT-52) Identify (DECID)
    CMD_CL      = 93,   // (VT-52) Print screen
    CMD_EX      = 94,   // (VT-52) Enter auto print mode
    CMD_UN      = 95,   // (VT-52) Exit auto print mode
    CMD_LA      = 35,   // Line Attribute: Double height = #3 Top Half, #4 Bottom Half, Width = #5 Single Width Line, #6 Double Width Line
    CMD_DECALN  = 56,   // #8    Screen Alignment Pattern; sets margins to extreem of canvasgroup and cursor to home, fills display with pattern
    CMD_RIS     = 99,   // c     Reset to Initial State (Performs a communications line disconnect.  Clears UDKs.    Clears a down-line-loaded character set.
                        // Clears the screen.  Returns the cursor to the upper-left corner of the screen.  Sets the SGR state to normal.
                        // Sets the selective erase attribute write state to "not erasable".   Sets all character sets to the default.)
    CMD_DCS     = 80,   // P{Pc;Pl|Ky1/st1;ky2/st2;...kyn/stn}ST  Device Control String Introducer(P)
                        // {Pc} None or 0 = Clear all keys before loading new values. 1 = Load new key values, clear old ones
                        // {pl} None	or 0 = Lock the keys. (Cannot be redefined.) 1 = Do not lock the keys. (Can be redefined.)
                        // {Kyn/Stn} Function Key Definition string where Kyn = number (1 - 12), Stn = String parameter (up to 1024 char)
                        // User programmed function keys are accessed using the shift + Fn key combo
                        // P{Ps v D...D}ST Load Answerback Message
                        // answerback data string may consist of from 0 to 30, 8-bit characters
                        // Ps =decoding mode, 1 = standard for VT510
                        // P{Ps r D...D}ST Load Banner Message
                        // Ps = 0 Omitted, 1 Interprets as ASCII, 2 Loads as text in VT default character set
                        // D...D is a 30 character string

    CMD_DECSC   = 55,   // 7    DEC Save cursor (position, graphic rendition, character set shift state, state of wrap flag, state of origin mode, state of selective erase)
    CMD_DECRC   = 56,   // 8    DEC Restore Cursor
    CMD_CUU     = 65,   // #A   Cursor Up: move cursor up # lines
    CMD_CUD     = 66,   // #B   Cursor Down: move cursor down # lines
    CMD_CUF     = 67,   // #C   Cursor Forward: move cursor right # columns
    CMD_CUB     = 68,   // #D   Cursor Backwards: move cursor left # columns
    CMD_CNL     = 69,   // #E   Cursor Next Line: moves cursor to beginning of next line, # lines down
    CMD_CPL     = 70,   // #F   Cursor Previous Line: moves cursor to beginning of previous line, # lines down
    CMD_CHA     = 71,   // #G   moves cursor to column # (Horizontal absolute)
    CMD_CUP     = 72,   // Cursor Position (ie.  H = cursor to home position (0, 0),  {line};{column}H = cursor to specific cell
    CMD_CHT     = 73,   // #I   Cursor Horizontal Forward Tabulation (where # is the number of tabs)
    CMD_ED      = 74,   // Erase in Display
                        // J    Erase from the cursor position to end of display (line attr become single width / height on erased lines)
                        // 0J   <same as above>
                        // 1J   clears from cursor to beginning of display
                        // 2J   clears entire display
                        // ?J   DECSCA Erase all erasable characters from the cursor position to end of display (line attr become single width / height on erased lines), does not affect video char attr or video line attr (SGR)
                        // ?0J  DECSCA <same as above>
                        // ?1J  DECSCA Erase all erasable characters from cursor to beginning of display, does not affect video char attr or video line attr (SGR)
                        // ?2J  DECSCA Erase all erasable characters entire display, does not affect video char attr or video line attr (SGR)

    CMD_EL      = 75,   // Erase in Line
                        // K    Erase to end of current line (including at cursor position)
                        // 0K   <same as above>
                        // 1K   clears from cursor to start of line
                        // 2K   clears entire line
                        // ?K   DECSCA Erase all erasable characters to end of current line (including at cursor position), does not affect video char attr or video line attr (SGR)
                        // ?0K  DECSCA <same as above>
                        // ?1K  DECSCA Erase all erasable characters from cursor to start of line, does not affect video char attr or video line attr (SGR)
                        // ?2K  DECSCA Erase all erasable characters entire line, does not affect video char attr or video line attr (SGR)
    CMD_IL      = 76,   // #L   Inserts # Lines at the cursor.  If fewer than # lines remain from the current line to the end of the scrolling region, the number of lines inserted is the lesser number.  Lines within the scrolling region at and below the cursor is moved down. Lines moved past the bottom margin are lost.  The cursor is reset to the first column. sequence is ignore outisde of the sscrolling rtegion.
    CMD_DL      = 77,    // #M   Deletes # lines starting at the line with the cursor.  If fewer than # lines remain from the current line to the end of the scrolling region, the number of lines deleted is the lesser number. As lines are deleted, lines within the scrolling region and below the cursor move up, and blank lines are added at the bottom of the scrolling region. The cursor is reset to the first column. This sequence is ignored when the cursor is outside the scrolling region.
    CMD_ICH     = 64,   // {#@   Insert # blank characters at the cursor position, with the character attributes set to normal. The cursor does not move and remains at the beginning of the inserted blank characters. A parameter of 0 or 1 inserts one blank character. Data on the line is shifted forward as in character insertion.
    CMD_SS2     = 78,   // #N   Single Shift 2 = Get a character from G2 character set
    CMD_SS3     = 79,   // #O   Single Shift 3 = Get a character from G3 character set
    CMD_DCH     = 80,   // #P   Deletes # characters starting with the character at the cursor position. When a character is deleted, all characters to the right of the cursor move to the left. This creates a space character at the right margin for each character deleted. Character attributes move with the characters. The spaces created at the end of the line have all their character attributes off.
                        // page Position Absolute (PPA) #SPP
    CMD_PPR     = 81,   // page Position Relative (PPR) #SPQ
    CMD_CPR     = 82,   // #;#R Report cursor position
                        // page Position Backward (PPB) #SPR
    CMD_SU      = 83,   // #S   Scroll window up by n lines (pan down)
    CMD_SD      = 84,   // #T   Scroll window down by n lines (pan up)
    CMD_NP      = 85,   // #U   Next page
    CMD_PP      = 86,   // #V   Previous page
    CMD_SOS     = 88,   // {arg}X   Start Of String (String Control Sequence)
    CMD_IDENT   = 90,   // Z    Identify what the terminal is
    CMD_VPA     = 100,  // #d   Vertical Line Position Absolute: Where # is the column number (move cursor to line #)
    CMD_VPR     = 101,  // #e   Vertical Position Relative: Where # is the # of columns to move cursor    
    CMD_HVP     = 102,  // Horizontal Vertical Position:  {line};{column}f	moves cursor to line #, column #
    CMD_TBC     = 103,  // g (or 0g)  Clear horizontal tab stop at cursor position
                        // 3g   Clear all horizontal tab stops
    CMD_SETMODE = 104,  // 3h   Set Show Control Character mode
                        // 12h  Local Echo off
                        // ={value}h	Changes the screen width or type to the mode specified by value.
                        // =0h  40 x 25 monochrome (text)                //  =1h    40 x 25 color (text)
                        // =2h  80 x 25 monochrome (text)                //  =3h    80 x 25 color (text)
                        // =4h  320 x 200 4-color (graphics)             //  =5h    320 x 200 monochrome (graphics)
                        // =6h  640 x 200 monochrome (graphics)
                        // =7h  Enables line wrapping
                        // =13h	320 x 200 color (graphics)               //  =14h   640 x 200 color (16-color graphics)
                        // =15h	640 x 350 monochrome (2-color graphics)  //  =16h   640 x 350 color (16-color graphics)
                        // =17h	640 x 480 monochrome (2-color graphics)  //  =18h   640 x 480 color (16-color graphics)
                        // =19h	320 x 200 color (256-color graphics)
                        // ?3h  Set to 132 column mode
                        // ?4h  enable scrolling
                        // ?5h  enable display
                        // ?6h  Enable Origin
                        // ?7h  Enable auto wrap
                        // ?8h  Enable auto repeat (some keys do not repeat: Alt, Caps Lock, Ctrl, Enter, Scroll Lock, Num Lock, Shift)
                        // ?25h	make cursor visible
                        // ?34h Cursor direction right to left
                        // ?47h	save screen
                        // ?66h engage numlock
                        // ?67h set backspace key for back arrow
                        // ?69h engage vertical split screen
                        // ?97h enable screen saver
                        // ?100h set enables auto answerback
                        // ?101h Conceal answerback message
                        // ?103h Set Half-Duplex mode
                        // ?109h Set caps lock
                        // ?110h Set keyboard LED's host indicator mode
                        // ?1049h enables the alternative buffer
    CMD_RESMODE = 108,  // 3l   Reset Interpret Control Character
                        // 12l  Local Echo on
                        // ={value}l    Resets the mode by using the same values that Set Mode uses, except for 7, which disables line wrapping.
                        // =0l  40 x 25 monochrome (text)                // =1l 40 x 25 color (text)
                        // =2l  80 x 25 monochrome (text)                // =3l 80 x 25 color (text)
                        // =4l  320 x 200 4-color (graphics)             // =5l 320 x 200 monochrome (graphics)
                        // =6l  640 x 200 monochrome (graphics)
                        // =7l  Disable line wrapping
                        // =13l	320 x 200 color (graphics)               // =14l 640 x 200 color (16-color graphics)
                        // =15l	640 x 350 monochrome (2-color graphics)  // =16l 640 x 350 color (16-color graphics)
                        // =17l	640 x 480 monochrome (2-color graphics)  // =18l 640 x 480 color (16-color graphics)
                        // =19l	320 x 200 color (256-color graphics)
                        // ?3l  set to 80 column mode
                        // ?4l  disable scrolling
                        // ?5l  disable display
                        // ?6l  disable Origin
                        // ?7l  disable auto wrap
                        // ?8l  disable auto repeat
                        // ?25l	make cursor invisible
                        // ?34l Cursor direction left to right
                        // ?47l	restore screen
                        // ?66l disengage numlock
                        // ?67l set delete key for back arrow (reset)
                        // ?69l disengage vertical split screen
                        // ?97l disable screen saver
                        // ?100l    reset disables auto answerback
                        // ?101l    do not conceal answerback message
                        // ?103l    Set Full-Duplex mode
                        // ?109l    Reset caps lock
                        // ?110h    Reset keyboard LED's host indicator mode
                        // ?1049l	disables the alternative buffer
    CMD_SGR    = 109,   // 1;34;{...}m	Select Graphic Rendition; set appearance of following characters (values separated by semicolon (;)).
                        // 0m   (Reset or Normal) All Attributes off
                        // 1m   (Bold or increased Intensity) set bold mode
                        // 2m   (Faint, decreased intensity or dim) set dim/faint mode
                        // 3m   (Italic) set italic mode
                        // 4m   (Underline) set underline mode
                        // 5m   (Slow Blink) set blinking mode, less than 150 per minute
                        // 6m   (Rapid Blink) set blinking mode, more than 150 per minute
                        // 7m   (Reverse Video or Invert) set inverse/reverse mode
                        // m    (Conceal or Hide) set invisible mode
                        // 9m   (Crossed-out, strike) set strikethrough mode.
                        // 10m  (Primary (Default) font)
                        // 11-19m (Alternative font) - Select Alternative font n - 10
                        // 20m  (Blackletter font)
                        // 21m  (Doubly underlined, or not bold)
                        // 22m  (Normal Intensity - Neither bold nor faint)
                        // 23m  (neither Italic, nor blackletter)
                        // 24m  (not underlined - Neither singly nor doubly underlined)
                        // 25m  (not blinking)
                        // 26m  (Proportional spacing)
                        // 27m  (Not reversed)
                        // 28m  (Reveal - not concealed)
                        // 29m  (not crossed out)
                        // 30-37m   Set text color from the basic color palette of 0-7
                        // 38;5;{ID}m	Set foreground color
                        // 38;2;{r};{g};{b}m	Set foreground color as RGB
                        // 39m  Default foreground color
                        // 40-47m   Set background color from the basic color palette of 0-7
                        // 48;5;{ID}m	Set background color
                        // 48;2;{r};{g};{b}m	Set background color as RGB
                        // 49m  Default background color
                        // 50m  Disable proportional spacing
                        // 51m  Framed
                        // 52m  Encircled
                        // 53m  Overlined
                        // 54m  Neither framed Nor Circled
                        // 55m  Not overlined
                        // 58{arg}m     Set Underline Color (Next arguments are 5;n or 2;r;g;b.)
                        // 59m  Default underline color
                        // 60m  Ideogram underline or right side line
                        // 61m  Ideogram double underline or double line on the right side
                        // 62m  Ideogram overline or left side line
                        // 63m  Ideogram double overline, or double line on the left side
                        // 64m  Ideogram stress marking
                        // 65m  No ideogram attributes / Reset the effects of all of 60-64
                        // 73m  Superscript
                        // 74m  Subscript
                        // 75m  Neither subscript or superscript
                        // 90-97m       Set bright foreground color
                        // 100-107m     Set bright background color
    CMD_DSR     = 110,  // Device Status Report Call:  5n
                        // Response:  0n = terminal is ok
                        // Response:  3n = terminal is not ok
                        // 6n   Cursor Position Report : request cursor position, Response:  #;#R
    CMD_STRING  = 112,  // {code};{string};{...}p
    CMD_DECSCA  = 113,  // #q   (0=All attributes off.(Does not apply to SGR.)1=not erasable by DECSEL/DECSED. 2=Designate character as erasable by DECSEL/DECSED. (Attribute off.)))
    CMD_DECSTBM = 114,  // #;#r   This sequence selects top and bottom margins defining the scrolling region
                        // Change Attributes in Rectangular Area     Pt; Pl; Pb; Pr;Ps1; . . . Psn $r
                        // Source rectangle to change: Pt = Top Line, Pl = Left column, Pb = bottom line, Pr = right column, Ps1 = Select attribute to change
                        // 0 (default)	Attributes off (no bold, no underline, no blink, positive image)
                        // 1    Bold        // 4    Underline           // 5    Blink       // 7    Negative image
                        // 22   No bold     // 24   No underline        // 25   No blink    // 27   Positive image
    CMD_SCP     = 115,  // s    Save Current Cursor Position
    CMD_RCP     = 117,  // u    Restore Saved Cursor Position
    CMD_DECCRA  = 118,  // Copy Rectangular area  Pts; Pls; Pbs; Prs; Pps; Ptd; Pld; Ppd$v
                        // Source rectangle to copy: Pts = Top Line, Pls = Left column, Pbs = bottom line, Prs = right column, Pps = page number
                        // Destination: Ptd = top line border, Pld = Left column border, Ppd = page number
    CMD_DECFRA  = 120,  // Fill Rectangular Area  Pch;Pt; Pl; Pb; Pr $x
                        // Pch is the ascii value of the fill character
                        // Fill rectangle: Pt = Top Line, Pl = Left column, Pb = bottom line, Pr = right column
    CMD_DECTST  = 121,  // 4;Ps;...;Psy
                        // 0	Test 1, 2, 3 and 6          1	Power-up self test          2	EIA port data loopback test
                        // 3	Printer port loopback test  4	Not used    5	Not used    6	EIA port modem control line loopback test
                        // 7	20 mA port loopback test    8	Not used                    9	Repeat any selected test continuously until power-off or failure
    CMD_DECINVM = 122,  // #*z Invoke Macro (# is the macro id)
    CMD_DECIC   = 125,  // #'}   Insert column in scrolling region from cursor column
    CMD_DECDC   = 126   // #'~  Delete # of columns, shift columns of Right side to the left
} ansi_commands;


typedef enum {
    TCAPS_PAGE8             = 0b10000000000000000000000000000000, // enable page 8
    TCAPS_PAGE7             = 0b01000000000000000000000000000000, // enable page 7
    TCAPS_PAGE6             = 0b00100000000000000000000000000000, // enable page 6
    TCAPS_PAGE5             = 0b00010000000000000000000000000000, // enable page 5
    TCAPS_PAGE4             = 0b00001000000000000000000000000000, // enable page 4
    TCAPS_PAGE3             = 0b00000100000000000000000000000000, // enable page 3
    TCAPS_PAGE2             = 0b00000010000000000000000000000000, // enable page 2
    TCAPS_PAGE1             = 0b00000001000000000000000000000000, // enable page 1
    TCAPS_OFFSET_TOP        = 0b00000000100000000000000000000000, // 
    TCAPS_OFFSET_BOTTOM     = 0b00000000010000000000000000000000, // 
    TCAPS_OFFSET_LEFT       = 0b00000000001000000000000000000000, // 
    TCAPS_OFFSET_RIGHT      = 0b00000000000100000000000000000000, // 
    TCAPS_R20               = 0b00000000000010000000000000000000, // 
    TCAPS_R19               = 0b00000000000001000000000000000000, // 
    TCAPS_R18               = 0b00000000000000100000000000000000, // 
    TCAPS_SCREENSAVER       = 0b00000000000000010000000000000000, // allows screen to go in screensaver mode
    TCAPS_NUMLOCK           = 0b00000000000000001000000000000000, // numeric lock keyboard state
    TCAPS_CAPSLOCK          = 0b00000000000000000100000000000000, // caps lock keyboard state
    TCAPS_INSLOCK           = 0b00000000000000000010000000000000, // insert lock keyboard state
    TCAPS_SHOW_HOSTLEDS     = 0b00000000000000000001000000000000, // allows to show or hide led status lights on keyboard
    TCAPS_R12               = 0b00000000000000000000100000000000, // 
    TCAPS_R11               = 0b00000000000000000000010000000000, // 
    TCAPS_R10               = 0b00000000000000000000001000000000, // 
    TCAPS_R9                = 0b00000000000000000000000100000000, // 
    TCAPS_R8                = 0b00000000000000000000000010000000, // 
    TCAPS_SWITCH_PAGE       = 0b00000000000000000000000001000000, // enable switching pages
    TCAPS_R6                = 0b00000000000000000000000000100000, // 
    TCAPS_R5                = 0b00000000000000000000000000010000, // 
    TCAPS_MOUSE_INPUT       = 0b00000000000000000000000000001000, // enable mouse input
    TCAPS_KEYBOARD_INPUT    = 0b00000000000000000000000000000100, // enable keyboard input
    TCAPS_DISPLAY           = 0b00000000000000000000000000000010, // enable terminal display
    TCAPS_INITIALIZED       = 0b00000000000000000000000000000001, // terminal was initialized
    TCAPS_DEFAULT_MASK      = 0b00000001000000010001000001001111, // 
    TCAPS_ENABLE_MASK       = 0b11111111000000000000000000000000  // 
} terminal_capabilities;

typedef enum {
    PCAPS_RVIDEO            = 0b10000000000000000000000000000000, // reverse colors between froeground a background
    PCAPS_BOLD              = 0b01000000000000000000000000000000, // turns foreground color 2 * brightness
    PCAPS_FAINT             = 0b00100000000000000000000000000000, // turns foreground color .5 * brightness
    PCAPS_ENCIRCLED         = 0b00010000000000000000000000000000, // puts a circle around character
    PCAPS_FRAMED            = 0b00001000000000000000000000000000, // puts a box around character
    PCAPS_OVERLINED         = 0b00000100000000000000000000000000, // draws a line on top of character
    PCAPS_DSTRIKEOUT        = 0b00000010000000000000000000000000, // draws a double line through character
    PCAPS_STRIKEOUT         = 0b00000001000000000000000000000000, // draws a line through character
    PCAPS_UNDERLINED        = 0b00000000100000000000000000000000, // draws a line under character
    PCAPS_SUPERSCRIPT       = 0b00000000010000000000000000000000, // displace character upwards
    PCAPS_SUBSCRIPT         = 0b00000000001000000000000000000000, // displace character downwards
    PCAPS_R21               = 0b00000000000100000000000000000000, // 
    PCAPS_STRESSMARK        = 0b00000000000010000000000000000000, // 
    PCAPS_ITALIC            = 0b00000000000001000000000000000000, // uses skew to pent characters
    PCAPS_BLINK             = 0b00000000000000100000000000000000, // set character to blink
    PCAPS_R17               = 0b00000000000000010000000000000000, // 
    PCAPS_LOCAL_ECHO        = 0b00000000000000001000000000000000, // repeat characters to page from input
    PCAPS_R13               = 0b00000000000000000100000000000000, // 
    PCAPS_SHOW_CURSOR       = 0b00000000000000000010000000000000, // show cursor on page
    PCAPS_SHOW_MOUSE        = 0b00000000000000000001000000000000, // show mouse on page
    PCAPS_SHOW_COMMAND      = 0b00000000000000000000100000000000, // show terminal commands (default is hidden)
    PCAPS_CURSOR_RTOL       = 0b00000000000000000000010000000000, // set cursor to move from right to left (default is left to right)
    PCAPS_AUTO_WRAP         = 0b00000000000000000000001000000000, // automatically wraps around screen when at end of line
    PCAPS_AUTO_REPEAT       = 0b00000000000000000000000100000000, // keyboard auto repeat last character pressed
    PCAPS_AUTO_SCROLL       = 0b00000000000000000000000010000000, // scroll page when moving past last line (new line)
    PCAPS_HALF_DUPLEX       = 0b00000000000000000000000001000000, // 
    PCAPS_HSPLIT            = 0b00000000000000000000000000100000, // horizontal page split
    PCAPS_VSPLIT            = 0b00000000000000000000000000010000, // vertical page split
    PCAPS_MOUSE_INPUT       = 0b00000000000000000000000000001000, // enable mouse input
    PCAPS_KEYBOARD_INPUT    = 0b00000000000000000000000000000100, // enable keyboard input
    PCAPS_DISPLAY           = 0b00000000000000000000000000000010, // turn on page display (default is on)
    PCAPS_INITIALIZED       = 0b00000000000000000000000000000001, // page was initialized
    PCAPS_DEFAULT_MASK      = 0b00000000000000010001101010101011, // 
    PCAPS_COL_NORMAL_MASK   = 0b11100000000000000000000000000000, // 
    PCAPS_TF_NORMAL_MASK    = 0b00000000011011100000000000000000  // 
} page_capabilities;

static void set_terminal_state(uint32_t state) { BITS_ON(sys.terminal.state, state); }
static void clear_terminal_state(uint32_t state) { BITS_OFF(sys.terminal.state, state); }
static void flip_terminal_state(uint32_t state) { BITS_FLIP(sys.terminal.state, state); }
uint32_t active_terminal(uint32_t state)     {return BITS_TEST(sys.terminal.state, state);}

static void set_page_state(uint32_t state) { BITS_ON(sys.terminal.page[sys.terminal.page_id].state, state); }
static void clear_page_state(uint32_t state) { BITS_OFF(sys.terminal.page[sys.terminal.page_id].state, state); }
static void flip_page_state(uint32_t state) { BITS_FLIP(sys.terminal.page[sys.terminal.page_id].state, state); }
uint32_t page_status(uint32_t state)     {return BITS_TEST(sys.terminal.page[sys.terminal.page_id].state, state);}

static uint16_t set_current_page(uint16_t page_id) {
    if (page_id >= TERM_MAXPAGES) return 1;
    sys.terminal.previous_page_id = sys.terminal.page_id;
    sys.terminal.page_id = page_id;
    return 0;
}

static void goto_previous_page(void) {
    sys.terminal.page_id = sys.terminal.previous_page_id;
}

static void move_to_next_page(void) {
    sys.terminal.page_id += 1;
    if  (sys.terminal.page_id >= TERM_MAXPAGES) sys.terminal.page_id -= TERM_MAXPAGES;    
}

static void move_to_previous_page(void) {
    sys.terminal.page_id -= 1;
    if  (sys.terminal.page_id < 0) sys.terminal.page_id += TERM_MAXPAGES;        
}

static uint16_t get_terminal_font_asset(uint16_t value) {
    if (value >= TERM_MAXFONTS || value < 0) return 0; // should be flagged as out of range value
    return sys.terminal.font_id[value];
}

static uint16_t get_terminal_font_from_asset(uint16_t font_id) {
    for (uint16_t font = 0; font < TERM_MAXFONTS; ++font) {
        if (sys.terminal.font_id[font] == font_id) return font;
    }
    return 0;
}

static uint16_t get_terminal_palette_asset(uint16_t value) {
    if (value >= TERM_MAXPALETTES || value < 0) return 0; // should be flagged as out of range value
    return sys.terminal.palette_id[value];
}

static uint16_t get_terminal_palette_from_asset(uint16_t palette_id) {
    for (uint16_t palette = 0; palette < TERM_MAXPALETTES; ++palette) {
        if (sys.terminal.palette_id[palette] == palette_id) return palette;
    }
    return 0;
}

static bool enable_page(uint16_t page_id) {
    EX_page *page = &sys.terminal.page[sys.terminal.page_id];
    // return error is page not PCAPS_INITIALIZED
}

static uint16_t get_writing_font(void)              {return get_terminal_font_from_asset(sys.terminal.page[sys.terminal.page_id].cell.asset_id);}
static uint16_t get_writing_palette(void)           {return get_terminal_palette_from_asset(sys.terminal.page[sys.terminal.page_id].cell.palette_id);}
static uint16_t get_writing_foreground_color(void)  {return sys.terminal.page[sys.terminal.page_id].cell.colorfg_id;}
static uint16_t get_writing_background_color(void)  {return sys.terminal.page[sys.terminal.page_id].cell.colorbg_id;}

static bool set_writing_font(uint16_t font) {
    EX_page *page = &sys.terminal.page[sys.terminal.page_id];
    if (font >= sys.terminal.fonts) return true;
    page->previous_font = get_terminal_font_from_asset(page->cell.asset_id);
    page->cell.asset_id = get_terminal_font_asset(font);
    return false;
}

static bool set_writing_palette(uint16_t palette) {
    EX_page *page = &sys.terminal.page[sys.terminal.page_id];
    if (palette >= sys.terminal.palettes) return true;
    page->previous_palette = get_terminal_palette_from_asset(page->cell.asset_id);
    page->cell.palette_id = get_terminal_palette_asset(palette);
    return false;
}

static bool set_writing_blinking_rate(uint16_t rate) {
    EX_page *page = &sys.terminal.page[sys.terminal.page_id];
    // establish blinking rates / temporal
    page->text_blink_rate = rate;
}

static bool set_writing_foreground_color(uint16_t color_id) {
    EX_page *page = &sys.terminal.page[sys.terminal.page_id];
    uint16_t colors = 255;//get_palette_color_count(get_writing_palette());
    if (color_id < 0 || color_id >= colors) return true;
    page->previous_colorfg_id = page->cell.colorfg_id;
    page->colorfg_id = color_id;
    page->cell.colorfg_id = color_id;
    return false;
}

static bool set_writing_background_color(uint16_t color_id) {
    EX_page *page = &sys.terminal.page[sys.terminal.page_id];
    uint16_t colors = get_palette_color_count(get_writing_palette());
    if (color_id < 0 || color_id >= colors) return true;
    page->previous_colorbg_id = page->cell.colorbg_id;
    page->colorbg_id = color_id;
    page->cell.colorbg_id = color_id;
    return false;
}

static void set_writing_colors_reverse(void)        {
    EX_page *page = &sys.terminal.page[sys.terminal.page_id];
    set_page_state(PCAPS_RVIDEO);
    page->cell.colorfg_id = page->colorbg_id;
    page->cell.colorbg_id = page->colorfg_id;
}

static void set_writing_colors_normal(void) {
    EX_page *page = &sys.terminal.page[sys.terminal.page_id];
    clear_page_state(PCAPS_COL_NORMAL_MASK);
    page->cell.colorfg_id = page->colorfg_id;
    page->cell.colorbg_id = page->colorbg_id;
}

static void set_writing_colors_bold(void)           {set_page_state(PCAPS_BOLD);}     // unclear yet how to handle colors for this
static void set_writing_colors_faint(void)          {set_page_state(PCAPS_FAINT);}    // unclear yet how to handle colors for this
static void set_writing_typeface_subscript(void)    {set_page_state(PCAPS_SUBSCRIPT);}
static void set_writing_typeface_superscript(void)  {set_page_state(PCAPS_SUPERSCRIPT);}
static void set_writing_typeface_italic(void)       {set_page_state(PCAPS_ITALIC);}
static void set_writing_typeface_overlined(void)    {set_page_state(PCAPS_OVERLINED);}
static void set_writing_typeface_underlined(void)   {set_page_state(PCAPS_UNDERLINED);}
static void set_writing_typeface_normal(void)       {clear_page_state(PCAPS_TF_NORMAL_MASK);}
static void set_writing_cursor_rtol(void)           {set_page_state(PCAPS_CURSOR_RTOL);}
static void set_writing_cursor_ltor(void)           {clear_page_state(PCAPS_CURSOR_RTOL);}

static bool set_page_default_font(uint16_t font) {
    EX_page *page = &sys.terminal.page[sys.terminal.page_id];
    if (font >= TERM_MAXFONTS) return true;
    page->default_font = font;
    return false;
}

static bool set_page_margins(uint16_t top, uint16_t bottom, uint16_t left, uint16_t right) {
    EX_page *page = &sys.terminal.page[sys.terminal.page_id];
    if (left > right || top > bottom) return;
    if (page->size.x < left)    page->margin_left = (page->size.x - 1);     else page->margin_left  = left;
    if (page->size.x < right)   page->margin_right = (page->size.x - 1);    else page->margin_right = right;
    if (page->size.y < top)     page->margin_top = (page->size.y - 1);      else page->margin_top   = top;
    if (page->size.y < bottom)  page->margin_bottom = (page->size.y - 1);   else page->margin_bottom= bottom;
    return false;
}

static bool set_page_default_foreground_color(uint16_t color_id) {
    EX_page *page = &sys.terminal.page[sys.terminal.page_id];
    uint16_t colors = get_palette_color_count(get_writing_palette());
    if (color_id < 0 || color_id >= colors) return true;
    page->default_colorfg_id = color_id;
    return false;
}

static bool set_page_default_background_color(uint16_t color_id) {
    EX_page *page = &sys.terminal.page[sys.terminal.page_id];
    uint16_t colors = get_palette_color_count(get_writing_palette());
    if (color_id < 0 || color_id >= colors) return true;
    page->default_colorbg_id = color_id;
    return false;
}

static void set_page_split_horizontal(void) {
} // configure page to be horizontally split

static void set_page_split_vertical(void) {
} // configure page to be vertically split

static void unset_page_split(void) {
} // remove page split configuration


static void blank_column_terminal_page(uint16_t column) {
// copy a cell template with space to whole column
}

static void blank_row_terminal_page(uint16_t row) {
    uint16_t page_id = sys.terminal.page_id;
    EX_canvas *canvas = &sys.terminal.canvas_template;
    EX_page *page = &sys.terminal.page[page_id];
    EX_cell *cell = &sys.terminal.page[page_id].cell;

    cell->value = 32;
    // copy a cell template with space to whole row
    //page->size
    Rectangle target = {0,row,page->size.x,1};
    uint16_t status = init_canvas_section_templated(sys.terminal.canvasgroup_id, page_id, cell, target);
}

static void scroll_terminal_page(uint16_t direction) {

    switch (direction) {
        case 1: // scroll up
        break;

        case 2: // scroll down
        break;

        case 3: // scroll left
        break;

        case 4: // scroll right
        break;

        default: // invalid
        break;
    }
}

static bool set_keyboard_cursor_position(Vector2 position) {
    EX_page *page = &sys.terminal.page[sys.terminal.page_id];
    if (position.x > page->margin_right || position.x < page->margin_left || position.y > page->margin_bottom || position.y < page->margin_top) return true;
    page->cursor_previous_position = page->cursor_position;
    page->cursor_position = position;
    return false;
}

static bool move_keyboard_cursor_position(Vector2 value) {
    EX_page *page = &sys.terminal.page[sys.terminal.page_id];
    Vector2 position = {page->cursor_position.x + value.x, page->cursor_position.y + value.y};
    if (position.x > page->margin_right || position.x < page->margin_left || position.y > page->margin_bottom || position.y < page->margin_top) return true;
    page->cursor_previous_position = page->cursor_position;
    page->cursor_position = position;
    return false;
}

static bool move_keyboard_cursor_up() {
    EX_page *page = &sys.terminal.page[sys.terminal.page_id];
    Vector2 position = {page->cursor_position.x, page->cursor_position.y - 1};
    if (position.y < page->margin_top) return true;
    if (position.y < 0) return true;
    page->cursor_position = position;
    return false;
}

static bool move_keyboard_cursor_down() {
    EX_page *page = &sys.terminal.page[sys.terminal.page_id];
    Vector2 position = {page->cursor_position.x, page->cursor_position.y + 1};
    if (position.y > page->margin_bottom) return true;
    if (position.y >= page->size.y) return true;
    page->cursor_position = position;
    return false;
}

static bool move_keyboard_cursor_left() {
    EX_page *page = &sys.terminal.page[sys.terminal.page_id];
    Vector2 position = {page->cursor_position.x - 1, page->cursor_position.y};
    if (position.x < page->margin_left) return true;
    if (position.x < 0) return true;
    page->cursor_position = position;
    return false;
}

static bool move_keyboard_cursor_right() {
    EX_page *page = &sys.terminal.page[sys.terminal.page_id];
    Vector2 position = {page->cursor_position.x + 1, page->cursor_position.y};
    if (position.x > page->margin_right) return true;
    if (position.x >= page->size.x) return true;
    page->cursor_position = position;
    return false;
}

static bool move_keyboard_cursor_new_line(void) {
    EX_page *page = &sys.terminal.page[sys.terminal.page_id];
    uint16_t status = false;
    if (page_status(PCAPS_CURSOR_RTOL)) {
        page->cursor_position.x = page->margin_right;
        status = move_keyboard_cursor_down();
    } else {
        page->cursor_position.x = page->margin_left;
        status = move_keyboard_cursor_down();
    }    
    if (status) {
        if (page_status(PCAPS_AUTO_SCROLL)) {
            scroll_terminal_page(1);
            blank_row_terminal_page(page->cursor_position.y);
        }
    }
}

static bool move_keyboard_cursor_next() {
    EX_page *page = &sys.terminal.page[sys.terminal.page_id];
    // check for protected cell, move to new line (check borders)
    uint16_t status;
     if (page_status(PCAPS_CURSOR_RTOL)) {
        status = move_keyboard_cursor_left();
        if (status) move_keyboard_cursor_new_line();
    } else {
        status = move_keyboard_cursor_right();
        if (status) move_keyboard_cursor_new_line();
    }
}

static Vector2 get_keyboard_cursor_position(void) {
    EX_page *page = &sys.terminal.page[sys.terminal.page_id];
    return page->cursor_position;
}

static bool set_cursor_home_position(Vector2 position) {
    EX_page *page = &sys.terminal.page[sys.terminal.page_id];
    if (position.x > page->margin_right || position.x < page->margin_left || position.y > page->margin_bottom || position.y < page->margin_top) return true;
    page->cursor_home_position = position;
    return false;
}

static bool move_cursor_home(void) {
    EX_page *page = &sys.terminal.page[sys.terminal.page_id];
    return set_keyboard_cursor_position(page->cursor_home_position);
}

static void page_scroll_up(void) {
// copy within margins 1 up on canvas
}

static bool page_clear_line(uint16_t line) {
    EX_page *page = &sys.terminal.page[sys.terminal.page_id];
    if (line >= page->margin_top || line <= page->margin_bottom) {
    // ok to clear row on canvas
    }
    return false;
}

static uint16_t init_terminal_page(uint16_t page_id, Vector2 size) {
    uint16_t status = 0;
    if (page_id >= TERM_MAXPAGES) return 1;
    if (page_status(TCAPS_INITIALIZED)) return 9;
    set_current_page(page_id);
    set_page_state(PCAPS_DEFAULT_MASK);
    EX_canvas *canvas = &sys.terminal.canvas_template;
    EX_page *page = &sys.terminal.page[page_id];
    canvas->size = size;
    page->size = size;
    page->page_split = (Vector2){0,0};

    status += set_page_default_font(3);
    status += set_writing_font(3);
    status += set_writing_palette(1);
    status += set_page_default_foreground_color(canvas->default_colorfg_id);
    status += set_page_default_background_color(canvas->default_colorbg_id);
    status += set_writing_foreground_color(canvas->default_colorfg_id);
    status += set_writing_background_color(canvas->default_colorbg_id);
    status += set_writing_blinking_rate(0);
    status += set_page_margins(0, canvas->size.y - 1, 0, canvas->size.x - 1);
    status += set_cursor_home_position((Vector2){page->margin_left, page->margin_top});
    status += move_cursor_home();

    EX_cell *cell = &sys.terminal.page[page_id].cell;
    cell->state = canvas->state;
    cell->asset_id = get_terminal_font_asset(get_writing_font());
    //cell->state |= (CVFE_LINE_BOT | CVFE_LINE_TOP | CVFE_LINE_LEF | CVFE_LINE_RIG);
    cell->value = 32;
    cell->palette_id = get_terminal_palette_asset(get_writing_palette());
    cell->colorfg_id = get_writing_foreground_color();
    cell->colorbg_id = get_writing_background_color();
    cell->colorln_id = canvas->default_colorln_id;
    
    cell->fg_brightness = 1.f;
    cell->bg_brightness = 1.f;
    init_canvas_templated(sys.terminal.canvasgroup_id, page_id, canvas, cell);

    enable_page(page_id);
    goto_previous_page();
    return status;
}

static void set_terminal_assets(void) {
    sys.terminal.fonts = 0;
    sys.terminal.palettes = 0;
    for (uint16_t asset_id = 0; asset_id < MAXASSETS; ++asset_id) {
        if (sys.asset.state[asset_id] & ASSET_PALETTE) {
            if (sys.terminal.palettes < TERM_MAXPALETTES) {
                sys.terminal.palette_id[sys.terminal.palettes] = asset_id;
                ++sys.terminal.palettes;
            }
        } else if (sys.asset.state[asset_id] & ASSET_FONT) {
            if (sys.terminal.fonts < TERM_MAXFONTS) {
                sys.terminal.font_id[sys.terminal.fonts] = asset_id;
                ++sys.terminal.fonts;
            }
        }
    }    
}

static void hide_terminal(void) {remove_service(CTRL_TERMINAL);}
static void show_terminal(void) {add_service(CTRL_TERMINAL);}

static void reset_terminal_canvas_template(uint64_t canvas_state) {
    EX_canvas* canvas = &sys.terminal.canvas_template;
    strcpy_s(canvas->name, sizeof(canvas->name), "TERMINAL");
    canvas->state = canvas_state;
    canvas->default_palette_id = get_terminal_palette_asset(0);
    canvas->default_asset_id = get_terminal_font_asset(0);
    canvas->asset_id[0] = canvas->default_asset_id;
    canvas->size = (Vector2){80.f, 25.f}; //get_canvas_size(sys.video.current_virtual); ************************ REMOVE HARDCODE
    canvas->default_tilesize = (Vector2){8, 16}; //get_tile_size_from_asset(canvas->default_asset_id); ************************ REMOVE HARDCODE
    canvas->scale = (Vector2){1,1};
    canvas->angle = 0.f;
    canvas->default_colorfg_id = 7;
    canvas->default_colorbg_id = 14;
    canvas->default_colorln_id = 7;
    canvas->fg_brightness = 1.f;
    canvas->bg_brightness = 1.f;
    canvas->shadow = (Vector2){0,0};
    canvas->alpha = 255;
    canvas->offset = (Vector2){0,0};
//    EX_cell* keycursor = sys.terminal.canvas_template.keycursor;
//    EX_cell* mousecursor = sys.terminal.canvas_template.mousecursor;

}

static bool write_to_terminal_page(uint16_t value) {
    uint16_t page_id = sys.terminal.page_id;
    EX_page *page = &sys.terminal.page[page_id];
    Vector2 position = page->cursor_position;
    //    sys.terminal.canvasgroup_id
    // pass on all graphics rendition to the cell template
    
    EX_cell *cell = &sys.terminal.page[page_id].cell;

    cell->value = value;
//    state |= 0; // assign corresponding lines based on some states (underline, strikeout, box, ...)
    if (page->state & PCAPS_OVERLINED) set_terminal_state(CVFE_LINE_TOP);
    if (page->state & PCAPS_UNDERLINED) set_terminal_state(CVFE_LINE_BOT);
    if (page->state & PCAPS_STRIKEOUT) set_terminal_state(CVFE_LINE_HOR);
    if (page->state & PCAPS_FRAMED) set_terminal_state(CVFE_LINE_BOT | CVFE_LINE_TOP | CVFE_LINE_LEF | CVFE_LINE_RIG);
// also set the font and the fg and bg colors
    if (page->state & PCAPS_ITALIC) cell->skew = (Vector2) {0.25,0}; else  cell->skew = (Vector2) {0,0};
    cell->offset = (Vector2){0,0};    // set offset for superscript or subscript
    plot_cell(TERMINALDISPLAY, page_id, cell, position);
    return true; // mostly if writing to the cell worked
}

static void handle_terminal_input(uint16_t value) {
    EX_page *page = &sys.terminal.page[sys.terminal.page_id];
    bool status;
    Vector2 position = page->cursor_position;

    if (!page_status(PCAPS_HALF_DUPLEX)) {
        switch (value) {
        
            case ASCII_CARRIAGE_RETURN:
            move_keyboard_cursor_new_line();
            break;

            case ASCII_ESCAPE:
            break;

            case ASCII_HORIZONTAL_TAB:
            break;

            case ASCII_BACKSPACE:
            break;

            case ASCII_DELETE:
            break;

            default:
            status = write_to_terminal_page(value);
            if (status) {
                uint16_t border = move_keyboard_cursor_next();
            // check if beyond last row, and if scroll then copy content of whole page 1 up then
            // page_scroll_up();
            // page_clear_line(page->margin_bottom);
            }
            break;

        }
    }
}
    
void render_terminal(void) {
    // aimed at displaying the terminal canvasgroup only
    flip_frame_buffer(TERMINALDISPLAY, false);

    begin_draw(true);
    ClearBackground(BLANK);
    render_canvas(sys.terminal.page_id);
    end_draw();
    flip_frame_buffer(sys.video.previous_virtual, false);
}

void process_command(uint32_t queue_ptr) {

}

void process_queue() {
    
}

static int16_t init_terminal(void) {
    int16_t status = 0;
    flip_frame_buffer(TERMINALDISPLAY, false);
    SetExitKey(false); // Disables the ESCAPE key from the RayLib core
    sys.terminal.canvasgroup_id = sys.video.current_virtual;
    set_terminal_assets();
    set_terminal_state(TCAPS_DEFAULT_MASK);
    uint32_t canvasgroup_state = 0;

    reset_terminal_canvas_template(CVFE_DEFAULT4); 
    init_canvasgroup(sys.terminal.canvasgroup_id, canvasgroup_state, TERM_MAXPAGES);
    for (uint16_t page_id = 0; page_id < TERM_MAXPAGES; ++page_id) {
        init_terminal_page(page_id, sys.terminal.canvas_template.size);
    }
    set_current_page(0);
    flip_frame_buffer(sys.video.previous_virtual, false);
    return status;
}


int16_t update_terminal(uint16_t value) {
    bool status;

    if (value > 0)     handle_terminal_input(value);
    status = process_canvasgroup(TERMINALDISPLAY);

}

void shutdown_terminal(void) {
    hide_terminal();
}

// ********** T E R M I N A L   S Y S T E M  ***** T E R M I N A L   S Y S T E M  ***** T E R M I N A L   S Y S T E M  ***** E N D
// ********** T E R M I N A L   S Y S T E M  ***** T E R M I N A L   S Y S T E M  ***** T E R M I N A L   S Y S T E M  ***** E N D
// ********** T E R M I N A L   S Y S T E M  ***** T E R M I N A L   S Y S T E M  ***** T E R M I N A L   S Y S T E M  ***** E N D

// *********** D E B U G   S Y S T E M ***** D E B U G   S Y S T E M ***** D E B U G   S Y S T E M ***** B E G I N
// *********** D E B U G   S Y S T E M ***** D E B U G   S Y S T E M ***** D E B U G   S Y S T E M ***** B E G I N
// *********** D E B U G   S Y S T E M ***** D E B U G   S Y S T E M ***** D E B U G   S Y S T E M ***** B E G I N

typedef enum {
    DEBUG_R32                   = 0b10000000000000000000000000000000, // 
    DEBUG_SHOW_OPTION_AUDIO     = 0b00000000000000001000000000000000, // 
    DEBUG_SHOW_OPTION_FPS       = 0b00000000000000000100000000000000, // 
    DEBUG_SHOW_OPTION_VIDEO     = 0b00000000000000000010000000000000, // 
    DEBUG_SHOW_OPTION_CONTROLS  = 0b00000000000000000001000000000000, // 
    DEBUG_SHOW_OPTION_DATA      = 0b00000000000000000000100000000000, // 
    DEBUG_SHOW_OPTION_TERMINAL  = 0b00000000000000000000010000000000, // 
    DEBUG_SHOW_OPTION_TRACE     = 0b00000000000000000000001000000000, // 
    DEBUG_SHOW_OPTION_EXIT      = 0b00000000000000000000000100000000, // 
    DEBUG_AUDIO                 = 0b00000000000000000000000010000000, // 
    DEBUG_FPS                   = 0b00000000000000000000000001000000, // 
    DEBUG_VIDEO                 = 0b00000000000000000000000000100000, // 
    DEBUG_CONTROLS              = 0b00000000000000000000000000010000, // 
    DEBUG_DATA                  = 0b00000000000000000000000000001000, // 
    DEBUG_TERMINAL              = 0b00000000000000000000000000000100, // 
    DEBUG_TRACE                 = 0b00000000000000000000000000000010, // 
    DEBUG_EXIT                  = 0b00000000000000000000000000000001, // 
    DEBUG_SHOW_OPTIONS_MASK     = 0b00000000000000001111111100000000, // 
    DEBUG_OPTIONS_MASK          = 0b00000000000000000000000001111111, //
    DEBUG_INITIALIZE_MASK       = 0b00000000000000001111111100000000  // 
} debug_flags;

void debug_console_out(const char* message, uint32_t status) {
    // also provide option to TRACELOG to -> TERMINAL or to FILE
    if (active_debugging(DEBUG_TRACE)) {
        TRACELOG(LOG_INFO, "%s | %s | DEBUG = 0x%000000008X | CTRL = 0x%000000008X | PMSN = 0x%000000008X | status = 0x%000000008X <<<<< %s",
        SOFTWARE,
        sys.temporal.datetime,
        sys.debug.state,
        sys.program.ctrlstate,
        sys.program.pmsnstate,
        status,
        message
        );
    }
}

void show_state_bits(uint64_t state, uint16_t length, Vector2 size, Vector2 position) {
    uint16_t y = position.y - size.y;
    uint16_t x = position.x + (length - 1) * size.x;
    uint64_t bit_tested = 1;
    Color col;
    for (uint64_t i = 0; i < length; i++) {
        uint64_t bit = state & bit_tested;
        if (bit) col = GREEN; else col = ORANGE;
        DrawRectangle(x - (i * size.x), y, size.x - 2, size.y - 2, col);
        bit_tested = bit_tested << 1;
    }
}

void display_debug_option(bool bit, uint16_t x, uint16_t y, uint16_t size, const char* text) {
    sys.video.screen_refresh = true;
    if (bit)
        DrawRectangle(x, y, size * 12, size, RED);
    else
        DrawRectangle(x, y, size * 12, size, GREEN);
    DrawText(TextFormat("%s %s", text, BIT_LITERAL_ON_OFF(bit)), x, y, size, WHITE);
}

void display_keybed(void)  {
    sys.video.screen_refresh = true;
    uint16_t keys_in_row = 24;
    for (uint16_t j = 0; j < 7; j++) {
        for (uint16_t i = 0; i < keys_in_row; i++) {
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
        y += size; if (y > (sys.video.screen.y - size)) {x+=768; y=0; };
    };
}

int16_t debug_data_menu(uint16_t size) {
    sys.video.screen_refresh = true;
    uint16_t x = 0, y = 0;
    DrawText(TextFormat("%s", sys.temporal.datetime), 1400, 0, 40, DARKGRAY);
    DrawText(TextFormat("FRAMES=%i", (uint32_t)sys.video.vscreen[sys.video.display_id].frames), 0, 0, 20, DARKGRAY);
    DrawText(TextFormat("prev_time = %f", (float)sys.video.vscreen[sys.video.display_id].prev_time), 0, 0, 40, DARKGRAY);
    DrawText(TextFormat("monitors = %i, current = %i, %s", (uint16_t)GetMonitorCount(), (uint16_t)sys.video.display_id, GetMonitorName(sys.video.display_id)), 0, 60, 20, DARKGRAY);
    DrawText(TextFormat("screen is %ix%i at %i fps", (uint16_t)sys.video.screen.x, (uint16_t)sys.video.screen.y, (uint16_t)sys.video.vscreen[sys.video.display_id].refresh_rate), 0, 100, 20, DARKGRAY);
    DrawText(TextFormat("screen is %ix%i mm", (uint16_t)GetMonitorPhysicalWidth(sys.video.display_id), (uint16_t)GetMonitorPhysicalHeight(sys.video.display_id)), 0, 120, 20, DARKGRAY);
    DrawText(TextFormat("ex_canopy.adjustment.y = %f", (float)ex_canopy.adjustment.y), 0, 140, 20, DARKGRAY);
    DrawText(TextFormat("ftime = %f and sys.video.frame_time_inc = %f",  (float)sys.video.vscreen[sys.video.display_id].elapsed_time, (float)sys.video.vscreen[sys.video.display_id].frame_time_inc), 0, 160, 20, DARKGRAY);
//    DrawText(TextFormat("text_pause = %i, text_color_flag = %i, text_wave_flag = %i", (int)text_pause, (int)text_color_flag, (int)text_wave_flag), 0, 180, 20, DARKGRAY);
    DrawText(TextFormat("value_anim %i", (float)sys.video.vscreen[sys.video.display_id].value_anim), 0, 200, 20, DARKGRAY);
    DrawText(TextFormat("fast_sin = %f", fast_sin(sys.video.vscreen[sys.video.display_id].frame_time_inc)), 0, 220, 20, DARKGRAY);
    DrawText(TextFormat("     sin = %f", sin(sys.video.vscreen[sys.video.display_id].frame_time_inc)), 0, 240, 20, DARKGRAY);
    DrawText(TextFormat("fast_cos = %f", fast_cos(sys.video.vscreen[sys.video.display_id].frame_time_inc)), 0, 260, 20, DARKGRAY);
    DrawText(TextFormat("     cos = %f", cos(sys.video.vscreen[sys.video.display_id].frame_time_inc)), 0, 280, 20, DARKGRAY);
    show_state_bits(sys.temporal.osc, TEMPORAL_ARRAY_SIZE, (Vector2){16, 32}, (Vector2) {sys.video.screen.y * 0.5, sys.video.screen.y - 32});

    show_state_bits(sys.program.ctrlstate, 32, (Vector2) {16, 32}, (Vector2) {sys.video.screen.x - 512, 96});
    show_state_bits(sys.program.pmsnstate, 32, (Vector2) {16, 32}, (Vector2) {sys.video.screen.x - 512, 128});
    DrawText(TextFormat("%s, ctrlstate & pmsnstate", sys.program.name), sys.video.screen.x - 512, 32, 20, DARKGRAY);

    if (IsKeyPressed(KEY_KP_1)) {ex_canopy.adjustment.y -= 0.002;};
    if (IsKeyPressed(KEY_KP_2)) {ex_canopy.adjustment.y += 0.002;};
    if (IsKeyPressed(KEY_KP_3)) {ex_canopy.pal_idx_cells -= 16; if(ex_canopy.pal_idx_cells < 0) {ex_canopy.pal_idx_cells +=256;};};
    if (IsKeyPressed(KEY_KP_4)) {ex_canopy.pal_idx_cells += 16; if(ex_canopy.pal_idx_cells > 255) {ex_canopy.pal_idx_cells -=256;};};
    if (IsKeyPressed(KEY_KP_5)) {ex_canopy.pal_idx_text -= 16; if(ex_canopy.pal_idx_text < 0) {ex_canopy.pal_idx_text +=256;};};
    if (IsKeyPressed(KEY_KP_6)) {ex_canopy.pal_idx_text += 16; if(ex_canopy.pal_idx_text > 255) {ex_canopy.pal_idx_text -=256;};};
}

int16_t debug_audio_menu(uint16_t size) {
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

/*    if (IsKeyPressed(KEY_LEFT)) change_track_playing(-1);
    if (IsKeyPressed(KEY_RIGHT)) change_track_playing(1);
    if (IsKeyPressed(KEY_UP))   change_track_volume(16);
    if (IsKeyPressed(KEY_DOWN)) change_track_volume(-16);
    if (IsKeyPressed(KEY_F7))   jar_xm_flip_comp_exp(sys.asset.music[sys.audio.asset_playing].ctxData);
    if (IsKeyPressed(KEY_F8))   jar_xm_flip_ramping(sys.asset.music[sys.audio.asset_playing].ctxData);
    if (IsKeyPressed(KEY_F9))   jar_xm_flip_linear_interpolation(sys.asset.music[sys.audio.asset_playing].ctxData);
*/
//    jar_xm_debug(sys.asset.music[sys.audio.asset_playing].ctxData);
}

int16_t debug_canvas(EX_canvas* canvas, uint16_t xpos, uint16_t fontsize) {
//    EX_canvas *canvas = &sys.terminal->canvas_template;
    DrawText(TextFormat("name = %s", canvas->name), xpos, 300, fontsize, WHITE);
    DrawText(TextFormat("state = %i", (uint32_t)canvas->state), xpos, 320, fontsize, WHITE);
//    uint16_t    asset_id[CANVAS_MAX_ASSETS];// tilset used for this canvas
    DrawText(TextFormat("default_asset_id = %i", (uint32_t)canvas->default_asset_id), xpos, 360, fontsize, WHITE);
    DrawText(TextFormat("size = %ix%i", (uint32_t)canvas->size.x, (uint32_t)canvas->size.y), xpos, 380, fontsize, WHITE);
    DrawText(TextFormat("default_tilesize = %ix%i", (uint32_t)canvas->default_tilesize.x,  (uint32_t)canvas->default_tilesize.y), xpos, 400, fontsize, WHITE);           
//    uint16_t    palette_id[CANVAS_MAX_PALETTES];     // color palette used for whole canvas
    DrawText(TextFormat("default_palette_id = %i", (uint32_t)canvas->default_palette_id), xpos, 440, fontsize, WHITE);
    DrawText(TextFormat("default_colorfg_id = %i", (uint32_t)canvas->default_colorfg_id), xpos, 460, fontsize, WHITE);
    DrawText(TextFormat("default_colorbg_id = %i", (uint32_t)canvas->default_colorbg_id), xpos, 480, fontsize, WHITE);
    DrawText(TextFormat("default_colorln_id = %i", (uint32_t)canvas->default_colorln_id), xpos, 500, fontsize, WHITE);
    DrawText(TextFormat("offset = %ix%i", (uint32_t)canvas->offset.x, (uint32_t)canvas->offset.y), xpos, 520, fontsize, WHITE);
//    Vector2     displace[4];                // cell corner displacement (x,y)
    DrawText(TextFormat("scale = %ix%i", (uint32_t)canvas->scale.x, (uint32_t)canvas->scale.y), xpos, 560, fontsize, WHITE);
//    Vector2     scale_speed;                // (x,y) cell scale speed
//    Vector2     scroll_speed;               // canvas scroll speed (x,y)
    DrawText(TextFormat("angle = %i", (uint32_t)canvas->angle), xpos, 620, fontsize, WHITE);
//    float       fg_brightness;              // foreground brightness (values 0...1 divides, values 1 to 255 multiply)
//    float       bg_brightness;              // background brightness (values 0...1 divides, values 1 to 255 multiply)
//    uint8_t     alpha;                      // transparency
//    Vector2     shadow;                     // shadow corner displacement (x,y)
//    Vector2     shadow_displace[4];         // shadow corners displacement (x,y)
//    Color       color_mask;                 // RGBA color mask of canvas
//    Color       shadow_mask;                // shadow RGBA mask
//    EX_cell     mousecursor;                // mouse cursor
//    EX_cell     keycursor;                  // key cursor
//    EX_cell     mask;                       // used for when replicating
//    uint32_t    cell_count;
//    EX_cell*    cell;                       // could be NULL

}

int16_t debug_terminal_menu(void) {
    EX_canvas* canvas;

//    debug_console_out("debug_terminal_menu", size});

    sys.video.screen_refresh = true;

    flip_frame_buffer(TERMINALDISPLAY, false);
//    Vector2 size = get_current_virtual_size();
    
    uint16_t canvasgroup_id = TERMINALDISPLAY;
    uint16_t canvas_id = sys.terminal.page_id;


    DrawText(TextFormat("LAST_KEY = %i",(int)sys.io.last_key), 0, 700, 40, WHITE);     

    DrawText(TextFormat("canvasgroup_id=%i", (uint32_t)sys.terminal.canvasgroup_id), 0, 80, 10, WHITE);
    DrawText(TextFormat("previous_page_id=%i", (uint32_t)sys.terminal.previous_page_id), 0, 100, 10, WHITE);
    DrawText(TextFormat("page_id=%i", (uint32_t)sys.terminal.page_id), 0, 120, 10, WHITE);
    DrawText(TextFormat("font_id[0...7]=%i %i %i %i %i %i %i %i", (uint16_t)sys.terminal.font_id[0], (uint16_t)sys.terminal.font_id[1], (uint16_t)sys.terminal.font_id[2], (uint16_t)sys.terminal.font_id[3], (uint16_t)sys.terminal.font_id[4], (uint16_t)sys.terminal.font_id[5], (uint16_t)sys.terminal.font_id[6], (uint16_t)sys.terminal.font_id[7]), 0, 140, 10, WHITE);
    DrawText(TextFormat("fonts=%i", (uint32_t)sys.terminal.fonts), 0, 160, 10, WHITE);
    DrawText(TextFormat("palette_id[0...7]=%i %i %i %i %i %i %i %i", (uint16_t)sys.terminal.palette_id[0], (uint16_t)sys.terminal.palette_id[1], (uint16_t)sys.terminal.palette_id[2], (uint16_t)sys.terminal.palette_id[3], (uint16_t)sys.terminal.palette_id[4], (uint16_t)sys.terminal.palette_id[5], (uint16_t)sys.terminal.palette_id[6], (uint16_t)sys.terminal.palette_id[7]), 0, 180, 10, WHITE);
    DrawText(TextFormat("palettes=%i", (uint32_t)sys.terminal.palettes), 0, 200, 10, WHITE);
    DrawText(TextFormat("read_position=%i", (uint32_t)sys.terminal.read_position), 0, 240, 10, WHITE);
    DrawText(TextFormat("write_position=%i", (uint32_t)sys.terminal.write_position), 0, 260, 10, WHITE);

//    EX_canvas *canvas = &sys.video.canvasgroup[canvasgroup_id].canvas[canvas_id];
    canvas = &sys.terminal.canvas_template;
    debug_canvas(canvas, 0, 10);

    show_state_bits(sys.terminal.state, 32, (Vector2) {16, 32}, (Vector2) {sys.video.screen.x - 512, 0});
    DrawText(TextFormat("curr %i", (uint16_t)canvas_id), sys.video.screen.x - 700, 00, 20, WHITE);

    uint16_t xpos = 150;
    for (uint16_t i = 0; i < TERM_MAXPAGES; ++i) {
        canvas = &sys.video.canvasgroup[canvasgroup_id].canvas[i];
        show_state_bits(sys.terminal.page[i].state, 32, (Vector2) {16, 32}, (Vector2) {sys.video.screen.x - 512, (i +3) * 32});
        DrawText(TextFormat("page %i", (uint16_t)i), sys.video.screen.x - 700, (i +2) * 32, 20, WHITE);
        debug_canvas(canvas, xpos, 10);
        xpos += 150;
    }

/*    for (uint16_t i = 0; i < ; ++i) {
    }
*/    flip_frame_buffer(sys.video.previous_virtual, false);
}

int16_t debug_video_menu(uint16_t size) {
    sys.video.screen_refresh = true;
    if (IsKeyDown(KEY_F9))      display_all_res();
    if (IsKeyPressed(KEY_F10))  flip_debugging(DEBUG_FPS);
    if (IsKeyPressed(KEY_F11))  flip_display_state(FLAG_VSYNC_HINT);
}

int16_t handle_debug_menu(uint16_t size) {
    debug_console_out("handle_debug_menu", size);
    sys.video.screen_refresh = true;
    uint16_t x = (sys.video.screen.x - 12 * size) * 0.5;
    uint16_t y = (sys.video.screen.y - 6 * size) * 0.5;
    if (valid_permission(PMSN_DEBUG_AUDIO) && active_debugging(DEBUG_SHOW_OPTION_AUDIO))         { y += size; display_debug_option(!active_debugging(DEBUG_AUDIO), x, y, size, "F1 -> AUDIO");}
    if (valid_permission(PMSN_DEBUG_VIDEO) && active_debugging(DEBUG_SHOW_OPTION_VIDEO))         { y += size; display_debug_option(!active_debugging(DEBUG_VIDEO), x, y, size, "F2 -> VIDEO");}
    if (valid_permission(PMSN_DEBUG_DATA) && active_debugging(DEBUG_SHOW_OPTION_DATA))           { y += size; display_debug_option(!active_debugging(DEBUG_DATA), x, y, size, "F3 -> DATA");}
    if (valid_permission(PMSN_DEBUG_CONTROLS) && active_debugging(DEBUG_SHOW_OPTION_CONTROLS))   { y += size; display_debug_option(!active_debugging(DEBUG_CONTROLS), x, y, size, "F4 -> CONTROLS");}
    if (valid_permission(PMSN_DEBUG_TERMINAL) && active_debugging(DEBUG_SHOW_OPTION_TERMINAL))   { y += size; display_debug_option(!active_debugging(DEBUG_TERMINAL), x, y, size, "F5 -> TERMINAL");}
    if (valid_permission(PMSN_DEBUG_TRACE) && active_debugging(DEBUG_SHOW_OPTION_TRACE))         { y += size; display_debug_option(!active_debugging(DEBUG_TRACE), x, y, size, "F6 -> TRACE");}
    if (valid_permission(PMSN_DEBUG_EXIT) && active_debugging(DEBUG_SHOW_OPTION_EXIT))           { y += size; display_debug_option(0, x, y, size, "F8 -> EXIT");}
    if (valid_permission(PMSN_DEBUG_AUDIO) && IsKeyPressed(KEY_F1))       flip_debugging(DEBUG_AUDIO);
    if (valid_permission(PMSN_DEBUG_VIDEO) && IsKeyPressed(KEY_F2))       flip_debugging(DEBUG_VIDEO);
    if (valid_permission(PMSN_DEBUG_DATA) && IsKeyPressed(KEY_F3))        flip_debugging(DEBUG_DATA);
    if (valid_permission(PMSN_DEBUG_CONTROLS) && IsKeyPressed(KEY_F4))    flip_debugging(DEBUG_CONTROLS);
    if (valid_permission(PMSN_DEBUG_TERMINAL) && IsKeyPressed(KEY_F5))    flip_debugging(DEBUG_TERMINAL);
    if (valid_permission(PMSN_DEBUG_TRACE) && IsKeyPressed(KEY_F6))       flip_debugging(DEBUG_TRACE);
    if (valid_permission(PMSN_DEBUG_EXIT) && IsKeyPressed(KEY_F8))        commute_to(CTRL_DEINIT);

    if (IsKeyPressed(KEY_F9))        flip_service(CTRL_TERMINAL);
}

int16_t init_debug(void) {
    add_debugging(DEBUG_INITIALIZE_MASK);
    return 0;
}

int16_t update_debug(void) {
    uint16_t size = 80;

    if (active_debugging(DEBUG_AUDIO))      debug_audio_menu(size);
    if (active_debugging(DEBUG_VIDEO))      debug_video_menu(size);
    if (active_debugging(DEBUG_DATA))       debug_data_menu(size);
    if (active_debugging(DEBUG_CONTROLS))   display_keybed();
    if (active_debugging(DEBUG_TERMINAL))   debug_terminal_menu();
    if (active_debugging(DEBUG_FPS))        DrawFPS(sys.video.screen.x - size, 0);
    if (IsKeyDown(KEY_LEFT_CONTROL))        handle_debug_menu(size);
}

// *********** D E B U G   S Y S T E M ***** D E B U G   S Y S T E M ***** D E B U G   S Y S T E M ***** E N D
// *********** D E B U G   S Y S T E M ***** D E B U G   S Y S T E M ***** D E B U G   S Y S T E M ***** E N D
// *********** D E B U G   S Y S T E M ***** D E B U G   S Y S T E M ***** D E B U G   S Y S T E M ***** E N D

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
    init_scrolltext(1, 24, 11, 5, 3.0, (Vector2){16,6}, (Vector2){1,0}, 255);
    init_scrolltext(2, 27, 11, 5, 2.9, (Vector2){16,5}, (Vector2){1,0}, 32);
    init_scrolltext(3, 28, 11, 5, 2.8, (Vector2){16,4}, (Vector2){1,0}, 64);
    init_scrolltext(4, 29, 11, 5, 2.7, (Vector2){16,3}, (Vector2){1,0}, 96);
    init_scrolltext(5, 27, 11, 5, 2.6, (Vector2){16,2}, (Vector2){1,0}, 96);
    init_scrolltext(6, 28, 11, 5, 2.5, (Vector2){16,1}, (Vector2){1,0}, 64);
    init_scrolltext(7, 27, 11, 5, 2.4, (Vector2){16,0}, (Vector2){1,0}, 32);
    init_scrolltext(8, 26, 11, 5, 0.0, (Vector2){0,6}, (Vector2){1,0}, 255);

    init_canopy(11, 5, (Vector2){36, 12}, (Vector2){8.0f, 8.0f}, 0.0f, 0.0f, (Vector2){0, 0.166}, 41, 57);

    play_track(0, 9, true);
    play_track(1, 11, true);
    play_track(2, 6, true);

	sys.video.vscreen[UNFOCUSEDDISPLAY].frame_time_inc = 17.0;
	sys.video.vscreen[PRIMARYDISPLAY].frame_time_inc = 102.0;

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

// ******************** B A S E   A S S E T S
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

int16_t init_default_assets() {
    bool status = 0;
    
    sys.asset.total_assets = 0;

    uint16_t asset_id; // when read, asset_id returns total_assets - 1
    asset_id = init_frame_buffer(TERMINALDISPLAY, (Vector2) {640, 400});
    asset_id = init_frame_buffer(UNFOCUSEDDISPLAY, (Vector2) {512, 224});
    asset_id = init_frame_buffer(MENUDISPLAY, (Vector2) {284, 192});
    asset_id = init_frame_buffer(PRIMARYDISPLAY, (Vector2) {512, 224});

	asset_id = load_palette((Vector2){16,16}, VGACOLORS_FILENAME, VGACOLORS_FILEEXT, VGACOLORS_DATA, VGACOLORS_FILESIZE, VGACOLORS_PAK);
	asset_id = load_palette((Vector2){16,16}, A8COLORS_FILENAME, A8COLORS_FILEEXT, A8COLORS_DATA, A8COLORS_FILESIZE, A8COLORS_PAK);
	asset_id = load_asset(ASSET_ICON, ICON_FILENAME, ICON_FILEEXT, ICON_DATA, ICON_FILESIZE, ICON_PAK);

    asset_id = load_tileset((Vector2){16,2}, A8COPPER_FILENAME, A8COPPER_FILEEXT, A8COPPER_DATA, A8COPPER_FILESIZE, A8COPPER_PAK, 0);
	asset_id = load_tileset((Vector2){16,16}, FONT_ATASCII_FILENAME, FONT_ATASCII_FILEEXT, FONT_ATASCII_DATA, FONT_ATASCII_FILESIZE, FONT_ATASCII_PAK, 0);
	asset_id = load_tileset((Vector2){16,16}, FONT_ATASCII_BIG_FILENAME, FONT_ATASCII_BIG_FILEEXT, FONT_ATASCII_BIG_DATA, FONT_ATASCII_BIG_FILESIZE, FONT_ATASCII_BIG_PAK, 0);
	asset_id = load_tileset((Vector2){16,16}, FONT_VGA_FILENAME, FONT_VGA_FILEEXT, FONT_VGA_DATA, FONT_VGA_FILESIZE, FONT_VGA_PAK, 0);
	sys.asset.basefont_id = load_tileset((Vector2){64,1}, FONT_JJ_FILENAME, FONT_JJ_FILEEXT, FONT_JJ_DATA, FONT_JJ_FILESIZE, FONT_JJ_PAK, 32);
	asset_id = load_tileset((Vector2){96,1}, FONT_OSD_FILENAME, FONT_OSD_FILEEXT, FONT_OSD_DATA, FONT_OSD_FILESIZE, FONT_OSD_PAK, 32);
	sys.asset.lines_id = load_tileset((Vector2){256,1}, LINES_FILENAME, LINES_FILEEXT, LINES_DATA, LINES_FILESIZE, LINES_PAK, 0);
    status = asset_id + 1;
    return status;
}

// establish scripting mechanism.  A script is an asset.  Bootstrap is from a script asset(0) ("rom" program)

//RLAPI void SetExitKey(false);

int16_t init_system(void) {
    debug_console_out("//////// init_system", 0);
    uint32_t status = 0;

    int16_t temporal_status = init_temporal();
    if (temporal_status) add_service(CTRL_TEMPORAL_INITIALIZED);
    debug_console_out("---------- TEMPORAL_INITIALISATION", temporal_status);

    int16_t debug_status = init_debug();
    if (!debug_status) add_service(CTRL_DEBUG_SERVICE_MASK); 
    debug_console_out("---------- DEBUG_INITIALISATION", debug_status);
    
    int16_t display_status = init_display_properties(true);
    if (!display_status) add_service(CTRL_VIDEO_INITIALIZED); 
    debug_console_out("---------- VIDEO_INITIALISATION", display_status);
    
    int16_t assets_status = init_default_assets();
    if (assets_status) add_service(CTRL_ASSETS_INITIALIZED);
    debug_console_out("---------- ASSETS_INITIALISATION", assets_status);
    
    int16_t terminal_status = init_terminal();
    if (!terminal_status) add_service(CTRL_TERMINAL_SERVICE_MASK);
    debug_console_out("---------- TERMINAL_INITIALISATION", terminal_status);
    
    int16_t audio_status = init_audio_properties();
    if (!audio_status) add_service(CTRL_AUDIO_INITIALIZED);
    debug_console_out("---------- AUDIO_INITIALISATION", audio_status);
    
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

    status = unload_all_canvasgroups();
    debug_console_out("---------- CANVASES_UNLOADED", status);

    shutdown_terminal();
    remove_service(CTRL_TERMINAL_INITIALIZED);

    deinit_display();
    remove_service(CTRL_VIDEO_INITIALIZED);

    return status;
}

static int16_t update_system(void) {
    int16_t status = 0;
    
    uint16_t key = process_keyboard();
    process_mouse();

    if (active_service(CTRL_TEMPORAL_INITIALIZED))  status += update_temporal();
    if (active_service(CTRL_TERMINAL_INITIALIZED))  status += update_terminal(key);
    if (active_service(CTRL_ASSETS_INITIALIZED))    status += update_assets();
    if (active_service(CTRL_VIDEO_INITIALIZED))     status += update_display();
    if (active_service(CTRL_AUDIO_INITIALIZED))     status += update_audio();

    return status;
}

void display_initialize_splash(void) {
//    if (sys.program.ctrlstate & CTRL_INITIALIZE) display_initialize_splash();
    update_system();
}

void manage_program() {
    debug_console_out( control_state_literal(sys.program.ctrlstate & CTRL_SWITCHBOARD_MASK), 0);

    if (active_service(CTRL_OFF_FOCUS))
        game_off_focus_scene();
    else {
        switch (only_service(CTRL_SWITCHBOARD_MASK)) {
            case CTRL_OFF_FOCUS:
                begin_draw(true);
                game_off_focus_scene();
                end_draw();
            case CTRL_INITIALIZE:
                add_service(CTRL_TERMINAL);
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
int16_t process_system(uint32_t ctrlstate, uint32_t pmsnstate, const char* name) {
    add_service(ctrlstate);
    debug_console_out(">>>~~~>>> P R O C E S S   S Y S T E M <<<~~~<<<", 0);
    set_permission(pmsnstate);
    if (active_service(CTRL_BOOTSTRAP_TRACE))
        flip_debugging(DEBUG_TRACE);

    if (name > NULL) strcpy_s(sys.program.name, sizeof(sys.program.name), name); else strcpy_s(sys.program.name, sizeof(sys.program.name), "_o/");

    commute_to(CTRL_INITIALIZE);
    add_service(CTRL_RUNNING);
    while (active_service(CTRL_RUNNING)) {
        //debug_console_out("MAIN LOOP_______BEGIN", 0);

        manage_program(); // mostly for the game program display and whereabouts, as well as initialize and exit of the aopplication

        if (active_service(CTRL_VIDEO_INITIALIZED)) {
            if (active_service(CTRL_IN_GAME))  {
                // possibly health information, lives left, score etc... (HUD)
            }
            if (active_service(CTRL_GAME_PAUSED)) {
            // something special happening while game is paused
            // DISPLAY PAUSE MESSAGE
            }
            if (active_service(CTRL_TERMINAL)) {
                render_terminal();
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
