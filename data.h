
#pragma once

// ************ TEXTURES, IMAGES, ANIMATIONS ASSETS
//#include <as_data.h>
#include <ball1.h>
#include <ball2.h>
#include <ball3.h>
#include <title.h>
#include <TL1.h>
#include <TL2.h>
#include <TL5.h>
#include <TL8.h>
#include <TL9.h>

// ************ ALL SOUNDS ASSETS
#include <music_all1.h>
//#include <slyder_pak.h>

// ************ ALL TEXT DATA

// ------------------------- FLAG LAYOUT is 36 by 12
const static char* text_flag1 =   "         EXPECTED  FEATURES         " \
                                "    *==========================*    " \
                                " 0       FUNKY RETRO STYLE        0 " \
                                " S  SIMILARITIES WITH PITFALL II  S " \
                                " S        2D ENVIRONMENTS         S " \
                                " S     PARALLAX AND SCROLLING     S " \
                                " S         MASSIVE LEVELS         S " \
                                " S         FUNKY PUZZLES          S " \
                                " S      EXTENDED SOUNDTRACK       S " \
                                " S                                S " \
                                " 0       EXPECTED FOR  2021       0 " \
                                "    *==========================*    ";
//const static int text_flag1_len = strlen(text_flag1);

const static char* text_scroll1 = " zf                          ........................................HOLD THE LEFT CONTROL KEY FOR THE DEBUG MENU .......... IN AUDIO DEBUG : TO CHANGE TRACK, USE THE LEFT OR RIGHT ARROWS... TO CHANGE THE VOLUME...  USE THE UP AND DOWN ARROWS......... THIS IS THE BEGINNINGS OF MY GAME ENGINE FOR A PLATFORMER PROJECT I QAM WORKING ON......... FEEL FREE TO ASK ME QUESTIONS IF YOU SEE ME ON DISCORD zd:P :P :P zl..................                            :D :D: D                       ";

const static char* text_scroll2 = "sa                      xdccc" \
                        "ok{------------------------}rx" \
                        "oj{---}     PRESENTS     {---}rx" \
                        "oi{---}zs                  {---}rx" \
                        "oh{---}zsM A N  T R O N I C{---}rx" \
                        "og{---}zrM A N  T R O N I C{---}rx" \
                        "of{---}zqM A N  T R O N I C{---}rx" \
                        "oe{------------------------}" \
                        "czd'     ~f" \
                        "wok ......HAAAAAAA YESSSSSS.... WELL IT'S A GAME PROJECT|a AND IT HAS TO START WITH SOMETHING ~c " \
                        "sa............. BEEN STUDYING FEW THINGIES LATELY sdAND TRYING SOME THINGS OUT! :sc) :)sb:)sa rl~b " \
                        "ohx{dccdWILL I MAKE IT???}zc......zzd'sc" \
                        "okczwrh....BEEN WORKING ON MY NEW GAME ENGINE FOR THE PAST FEW WEEKS... ~c " \
                        "oisd....HAD SOME FUN MAKING A GAME LOOP AND ORGANIZING THE CODE !... ~c " \
                        "ojsb {IF YOU FIND ANYTHING FUNKY HAPPENING IN THIS DEMO, PLEASE ADVIDE :D :D !!! }    tHAVE FUN CODING :P :P|bsb:Psa ~eu " \
                        "of rtza+zb+zc+zd+ze+zf+zg+zh+zi+zj+zk+zl+zm+zn+zo+zp+zq+zr+zs++++++++++++++++++++++++++++++roofHOPE YOU WILL ENJOY !!!" \
                        "oi rzrfza+zb+zc+zd+ze+zf+zg+zh+zi+zj+zk+zl+zm+zn+zo+zp+zq+zr+zs+++++++++++++++++++           xsc" \
                        "oa      cn    cz      rp" \
                        "ob    cn        cz    rp" \
                        "oc   cn          cz   rp" \
                        "od  cn cs  cn    cs  cn   cz  rp" \
                        "oe  cncs    cn  cs    cn  cz  rp" \
                        "of  cnck  cs  cn  ck  cs  cn  cz  rp" \
                        "og cn ck  cs  cn  ck  cs  cn   cz rp" \
                        "oh cn  cs  cn    cs  cn    cz rp" \
                        "oi cn              cz rp" \
                        "oj cn              cz rp" \
                        "ok cn              cz rp" \
                        "ol cn  cz cn   cz  cn   cz cn  cz rp" \
                        "om cn cz   cn  cz  cn  cz   cn cz " \
                        "oa      cl    cz      rp" \
                        "ob    cl        cz    rp" \
                        "oc   cl          cz   rp" \
                        "od  cl cs  cl    cs  cl   cz  rp" \
                        "oe  clcs    cl  cs    cl  cz  rp" \
                        "of  clck  cs  cl  ck  cs  cl  cz  rp" \
                        "og cl ck  cs  cl  ck  cs  cl   cz rp" \
                        "oh cl  cs  cl    cs  cl    cz rp" \
                        "oi cl              cz rp" \
                        "oj cl              cz rp" \
                        "ok cl              cz rp" \
                        "ol cl  cz cl   cz  cl   cz cl  cz rp" \
                        "om cl cz   cl  cz  cl  cz   cl cz " \
                        "oa      cb    cz      rp" \
                        "ob    cb        cz    rp" \
                        "oc   cb          cz   rp" \
                        "od  cb cs  cb    cs  cb   cz  rp" \
                        "oe  cbcs    cb  cs    cb  cz  rp" \
                        "of  cbck  cs  cb  ck  cs  cb  cz  rp" \
                        "og cb ck  cs  cb  ck  cs  cb   cz rp" \
                        "oh cb  cs  cb    cs  cb    cz rp" \
                        "oi cb              cz rp" \
                        "oj cb              cz rp" \
                        "ok cb              cz rp" \
                        "ol cb  cz cb   cz  cb   cz cb  cz rp" \
                        "om cb cz   cb  cz  cb  cz   cb cz " \
                        "oa      ch    cz      rp" \
                        "ob    ch        cz    rp" \
                        "oc   ch          cz   rp" \
                        "od  ch cs  ch    cs  ch   cz  rp" \
                        "oe  chcs    ch  cs    ch  cz  rp" \
                        "of  chck  cs  ch  ck  cs  ch  cz  rp" \
                        "og ch ck  cs  ch  ck  cs  ch   cz rp" \
                        "oh ch  cs  ch    cs  ch    cz rp" \
                        "oi ch              cz rp" \
                        "oj ch              cz rp" \
                        "ok ch              cz rp" \
                        "ol ch  cz ch   cz  ch   cz ch  cz rp" \
                        "om ch cz   ch  cz  ch  cz   ch cz " \
                        "                       ";

const static char* text_16hues = "faf fbf fcf fdf fef fff fgf fhf fif fjf fkf flf fmf fnf fof fpf ";

const static char* text_yo1 = " zfOMG THIS TIME HE REALLY SURPASSED HIMSELF... WOW I AM SO IMPRESSED  zd:D :D :D zl......THIS DUDE NEVER STOPS CODING ...WTF...... CALM DOWN BOIIIIII.....        :D :D: D                       ";
const static char* text_yo2 = " zfREALLY I'M NOT SURE WHY HE KEEPS ON PUTTING OUT THESE SILLY DEMOS IT GETS ANNOYING AT SOME POINT!  zd:( :( :() zl......DUDE STOP IT I HAVE WORK TO DO....  YOUR DEMOS IDK .....  UH THIS GUY  ... REALLY ......        :D :D: D                       ";
const static char* text_yo3 = " zf    !!!!  DAMN! !!! !       I WISH I HAD YOUR SKILLZZZZ BRO!!!....  DIZ ROCKS!!  WHERE D'YOU LEARN TO DO MUSIC BTW WTF YOU ROCK BROWWZZZZ...  HOPE YOU WILLL FINISH THIS I WANT TO SEEEEE.......";

