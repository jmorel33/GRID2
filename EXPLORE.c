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

#include "data.h"            // ALL GAME DATA
#include "grid2.h"           // CODE

int main(void) {
    printf("PROGRAM STARTED - %s\n", SOFTWARE);
    return process_system(true, SOFTWARE);
}
