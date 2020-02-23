#ifndef SHOW_DISPLAYER_H_
#define SHOW_DISPLAYER_H_

#include <stdint.h>
#include "displayer.h"
#include "showing.h"
#include "types.h"

typedef struct
{
    uint8_t column;
    character_t sign;
} vote_place;

extern const vote_place PlacePlus;
extern const vote_place PlaceEgal;
extern const vote_place PlaceMinus;

void show_disp_vote(vote_place place, number_t value);
void show_disp_all();
void show_disp_error();

#endif
