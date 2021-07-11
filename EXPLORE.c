// EXPLOREEXPLOREEXPLOREEXPLOREEXPLOREEXPLOREEXPLOREEXPLOREEXPLOREEXPLOREEXPLOREEXPLOREEXPLOREEXPLOREEXPLOREEXPLOREEXPLORE
// EXPLORE                                                                                                         EXPLORE
// EXPLORE    filename: EXPLORE.c                                                                                  EXPLORE
// EXPLORE                                                                                                         EXPLORE
// EXPLORE    written by Jacques Morel                                                                             EXPLORE
// EXPLORE    copywright (c) 2021 all rights reserved                                                              EXPLORE
// EXPLORE                                                                                                         EXPLORE
// EXPLORE    source code may not be used, redistributed, shared, hosted, archived without author's consent.       EXPLORE
// EXPLORE                                                                                                         EXPLORE
// EXPLOREEXPLOREEXPLOREEXPLOREEXPLOREEXPLOREEXPLOREEXPLOREEXPLOREEXPLOREEXPLOREEXPLOREEXPLOREEXPLOREEXPLOREEXPLOREEXPLORE

#pragma once

#define SOFTWARE "EXPLORE - W.I.P. build"
#define SUPPORT_TRACELOG 1
#include "utils.h"         // Required for: TRACELOG macros
#include "raylib.h"             // works on version 3.8 development

//***** G A M E   I N C L U D E S ***** BEGIN
#include "data.h"          // ALL GAME DATA
#include "grid2.h"         // CODE
#include "debug.h"         // CODE
//***** G A M E   I N C L U D E S ***** END

void load_assets(void) {
    debug_console_out("LOADING ASSETS");
    int id;
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

    int orderlist[] = {0, 4, 5, 13, 35, 60, 62, 64, 69, 72, 80, 84, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249};
    id = add_track(PRIMARYDISPLAY, 0,                      MUSIC_ALL1_FILENAME, MUSIC_ALL1_FILEEXT, MUSIC_ALL1_DATA, MUSIC_ALL1_FILESIZE, MUSIC_ALL1_PAK, 25, orderlist);
    id = add_track(PRIMARYDISPLAY, TRACK_SWITCH_IMMEDIATE, MUSIC_ALL1_FILENAME, MUSIC_ALL1_FILEEXT, MUSIC_ALL1_DATA, MUSIC_ALL1_FILESIZE, MUSIC_ALL1_PAK, 25, orderlist);
    id = add_track(PAUSEDISPLAY,   TRACK_RESTART_ON_FOCUS, MUSIC_ALL1_FILENAME, MUSIC_ALL1_FILEEXT, MUSIC_ALL1_DATA, MUSIC_ALL1_FILESIZE, MUSIC_ALL1_PAK, 25, orderlist);
}

particle bubbles[8];

void init_scene(void) {
    debug_console_out("INITIALIZING SCENE");

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

	sys.video.frame_time_inc[PAUSEDISPLAY] = 17.0;
	sys.video.frame_time_inc[PRIMARYDISPLAY] = 102.0;

}

void update_scene(void) {
    debug_console_out("UPDATING SCENE");
    if (sys.pause) {
        draw_colorbar();
        copper_animation(-1, 7, 256, 2, 32, 0.5, (Vector2){0,56}, (Vector3){2, 20, 5},.25);
        update_marquee_animation(14, 5,(Vector2){330,42}, 255.0f, (Vector2){0, 90}, -50, .333);
        copper_animation(1, 7, 256, 2, 32, 0.5, (Vector2){0,56}, (Vector3){2, 20, 5},.25);
    } else {
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
    };
}

int main(void) {
    //set_debug_trace(true);
    debug_console_out(">>>~~~>>> START <<<~~~<<<");
    init_system(SOFTWARE);

    load_assets();
    init_scene();

	while(!WindowShouldClose()) {
        debug_console_out("_______MAIN LOOP_______BEGIN");
        BeginTextureMode(sys.asset.framebuffer[sys.video.virtual_asset[sys.video.current_virtual]]);
            ClearBackground(BLACK);
            rlDisableDepthMask();            // Disable depth writes
            rlDisableDepthTest();            // Disable depth test for speed

            update_scene();

            rlEnableDepthMask();
            rlEnableDepthTest();
        EndTextureMode();

        update_system();
        debug_console_out("_______MAIN LOOP_______END");
	};
	return exit_system();
}
