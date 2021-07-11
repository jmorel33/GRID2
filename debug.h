//***************************************************************************
#if !defined(SOFTWARE)
    #define SOFTWARE "DEBUG"
#endif

#include "raylib.h"
#include "utils.h"
#include <time.h>

char *time_stamp(){
    char *timestamp = (char *)malloc(20);
    time_t ltime = time(NULL);
    struct tm *tm;
    tm = localtime(&ltime);
    sprintf(timestamp,"%04d/%02d/%02d-%02d:%02d:%02d", tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
    return timestamp;
}

typedef struct Debug_info {
    bool audio;
    bool video;
    bool game_data;
    bool controls;
    bool fps;
    bool trace;
} Debug_info;

static Debug_info debug_status; // = Init_debug();


#ifdef __cplusplus // Calling C code from C++
extern "C" { 
#endif

//    SetExitKey(false); // Disables the ESCAPE key from the RayLib core

void set_debug_audio(bool s)    {debug_status.audio = s;}
void set_debug_video(bool s)    {debug_status.video = s;}
void set_debug_game_data(bool s){debug_status.game_data = s;}
void set_debug_controls(bool s) {debug_status.controls = s;}
void set_debug_fps(bool s)      {debug_status.fps = s;}
void set_debug_trace(bool s)    {debug_status.trace = s;}

void debug_audio_flip()         {debug_status.audio = !debug_status.audio;}
void debug_video_flip()         {debug_status.video = !debug_status.video;}
void debug_game_data_flip()     {debug_status.game_data = !debug_status.game_data;}
void debug_controls_flip()      {debug_status.controls = !debug_status.controls;}
void debug_fps_flip()           {debug_status.fps = !debug_status.fps;}
void debug_trace_flip()         {debug_status.trace = !debug_status.trace;}

char *bit_status_text(bool s) {if (s) {return "ON";} else {return "OFF";}}

debug_display_option(bool bit, int x, int y, int size, const char* text) {
    if (bit) { DrawRectangle(x, y, size * 12, size, RED); } else { DrawRectangle(x, y, size * 12, size, GREEN); }
    DrawText(TextFormat("%s %s", text, bit_status_text(bit)), x, y, size, WHITE);
}

void display_keybed(void)  {
    int row = 24;
    for (int j = 0; j < 7; j++) {
        for (int i = 0; i < row; i++) {
            int letter = (j*row)+i;
            int key = kb_layout[letter];
            if (key) {
                if (IsKeyDown(key)) {
                    DrawRectangle(i*64, 20+j*64, 64, 64, GREEN);
                    DrawText(TextFormat("%c", (int)key), i*64, 20+j*64, 64, WHITE);
                }
                else {
                    DrawRectangle(i*64, 20+j*64, 64, 64, DARKGRAY);
                    DrawText(TextFormat("%c", (int)key), i*64, 20+j*64, 64, GRAY);
                };
            };
        
        };
    };
}

void display_all_res(void) {
    int count = 0;
    GLFWvidmode* modes = glfwGetVideoModes(glfwGetPrimaryMonitor(), &count);
    int size = 40;
    int x = 10;
    int y = 0;
    Vector2 ratio;
    for (int i = 0; i < count; i++) {
        ratio = ratio_info((int)modes[i].width, (int)modes[i].height);
        int bits = modes[i].redBits + modes[i].greenBits + modes[i].blueBits;
        DrawText( TextFormat("%ix%i - %ibit - %ifps - %i:%i", (int)modes[i].width, (int)modes[i].height, bits, (int)modes[i].refreshRate, (int)ratio.x, (int)ratio.y ),
        x, y, size, DARKGRAY);
        y += size; if (y > (sys.video.physical_res[sys.video.current_physical].y - size)) {x+=768; y=0; };
    };
}

void update_debug(bool show_options) {
    int size = 80;
    int x = 0, y = 0;

    if (debug_status.audio) {
        sys.video.next_physical_clear = true;
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

    if (debug_status.video) {
        sys.video.next_physical_clear = true;
        if (IsKeyPressed(KEY_F10)) debug_fps_flip(&debug_status);
        if (IsKeyDown(KEY_F8))  display_all_res();
        //if (IsKeyPressed(KEY_F11)) FlipConfigFlags(FLAG_VSYNC_HINT);
        show_options = false;
    }

    if (debug_status.game_data) {
        sys.video.next_physical_clear = true;
        if (IsKeyPressed(KEY_KP_1)) {ex_canopy.adjustment.y -= 0.002;};
        if (IsKeyPressed(KEY_KP_2)) {ex_canopy.adjustment.y += 0.002;};
        if (IsKeyPressed(KEY_KP_3)) {ex_canopy.pal_idx_cells -= 16; if(ex_canopy.pal_idx_cells < 0) {ex_canopy.pal_idx_cells +=256;};};
        if (IsKeyPressed(KEY_KP_4)) {ex_canopy.pal_idx_cells += 16; if(ex_canopy.pal_idx_cells > 255) {ex_canopy.pal_idx_cells -=256;};};
        if (IsKeyPressed(KEY_KP_5)) {ex_canopy.pal_idx_text -= 16; if(ex_canopy.pal_idx_text < 0) {ex_canopy.pal_idx_text +=256;};};
        if (IsKeyPressed(KEY_KP_6)) {ex_canopy.pal_idx_text += 16; if(ex_canopy.pal_idx_text > 255) {ex_canopy.pal_idx_text -=256;};};

        DrawText(TextFormat("%s", time_stamp()), 1600, 0, 40, DARKGRAY);
        DrawText(TextFormat("FRAMES=%i", (int)sys.video.frames[sys.video.current_physical]), 0, 0, 20, DARKGRAY);
        DrawText(TextFormat("prev_time = %f", (float)sys.video.prev_time[sys.video.current_physical]), 0, 0, 40, DARKGRAY);
        DrawText(TextFormat("monitors = %i, current = %i", (int)GetMonitorCount(), (int)sys.video.current_physical), 0, 60, 20, DARKGRAY);
        DrawText(GetMonitorName(sys.video.current_physical), 0, 80, 20, DARKGRAY);
        DrawText(TextFormat("screen is %ix%i at %i fps", (int)sys.video.physical_res[sys.video.current_physical].x, (int)sys.video.physical_res[sys.video.current_physical].y, (int)sys.video.refresh_rate[sys.video.current_physical]), 0, 100, 20, DARKGRAY);
        DrawText(TextFormat("screen is %ix%i mm", (int)GetMonitorPhysicalWidth(sys.video.current_physical), (int)GetMonitorPhysicalHeight(sys.video.current_physical)), 0, 120, 20, DARKGRAY);
        DrawText(TextFormat("ex_canopy.adjustment.y = %f", (float)ex_canopy.adjustment.y), 0, 140, 20, DARKGRAY);
        DrawText(TextFormat("ftime = %f and sys.video.frame_time_inc = %f",  (float)sys.video.elapsed_time[sys.video.current_physical], (float)sys.video.frame_time_inc[sys.video.current_physical]), 0, 160, 20, DARKGRAY);
//        DrawText(TextFormat("text_pause = %i, text_color_flag = %i, text_wave_flag = %i", (int)text_pause, (int)text_color_flag, (int)text_wave_flag), 0, 180, 20, DARKGRAY);
        DrawText(TextFormat("value_anim %i", (float)sys.video.value_anim[sys.video.current_physical]), 0, 200, 20, DARKGRAY);
        DrawText(TextFormat("fast_sin = %f", fast_sin(sys.video.frame_time_inc[sys.video.current_physical])), 0, 220, 20, DARKGRAY);
        DrawText(TextFormat("     sin = %f", sin(sys.video.frame_time_inc[sys.video.current_physical])), 0, 240, 20, DARKGRAY);
        DrawText(TextFormat("fast_cos = %f", fast_cos(sys.video.frame_time_inc[sys.video.current_physical])), 0, 260, 20, DARKGRAY);
        DrawText(TextFormat("     cos = %f", cos(sys.video.frame_time_inc[sys.video.current_physical])), 0, 280, 20, DARKGRAY);
        show_options = false;
    }

    if (debug_status.controls) {
        sys.video.next_physical_clear = true;
        display_keybed();
        show_options = false;
    }

    if (debug_status.fps) {
        sys.video.next_physical_clear = true;
        DrawFPS(GetMonitorWidth(sys.video.current_physical) - 100, 10);
    }

    if (IsKeyDown(KEY_LEFT_CONTROL)) {
        x = (GetMonitorWidth(sys.video.current_physical) - 12 * size) * 0.5;
        y = (GetMonitorHeight(sys.video.current_physical) - 6 * size) * 0.5;
        if (show_options || debug_status.audio)     { sys.video.next_physical_clear = true; y += size; debug_display_option(!debug_status.audio, x, y, size, "F1 -> AUDIO");};
        if (show_options || debug_status.video)     { sys.video.next_physical_clear = true; y += size; debug_display_option(!debug_status.video, x, y, size, "F2 -> VIDEO");};
        if (show_options || debug_status.game_data) { sys.video.next_physical_clear = true; y += size; debug_display_option(!debug_status.game_data, x, y, size, "F3 -> DATA");};
        if (show_options || debug_status.controls)  { sys.video.next_physical_clear = true; y += size; debug_display_option(!debug_status.controls, x, y, size, "F4 -> CONTROLS");};
        if (show_options || debug_status.trace)     { sys.video.next_physical_clear = true; y += size; debug_display_option(!debug_status.trace, x, y, size, "F5 -> TRACE");};
        if (IsKeyPressed(KEY_F1)) debug_audio_flip();
        if (IsKeyPressed(KEY_F2)) debug_video_flip();
        if (IsKeyPressed(KEY_F3)) debug_game_data_flip();
        if (IsKeyPressed(KEY_F4)) debug_controls_flip();
        if (IsKeyPressed(KEY_F5)) debug_trace_flip();
    }
}


void debug_console_out(const char* message) {
    if (debug_status.trace) TRACELOG(LOG_INFO, "%s | %s >>>>>%s", SOFTWARE, time_stamp(), message);
}


#ifdef __cplusplus
}
#endif
