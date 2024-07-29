#ifndef WORLDCONSTANTS_H
#define WORLDCONSTANTS_H

constexpr int
CHUNK_W = 16,
CHUNK_D = 16,
CHUNK_H = 100,
CHUNK_AREA = CHUNK_W * CHUNK_D,
CHUNK_VOL = CHUNK_AREA * CHUNK_H;

constexpr float
DAYCYCLE_TICKS = 24000.0f;

#endif