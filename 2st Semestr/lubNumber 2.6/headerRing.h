#pragma once
#ifndef MYLABS_HEADERRING_H
#define MYLABS_HEADERRING_H

#endif //MYLABS_HEADERRING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Ring
{
    int num;
    struct Ring *next;
    struct Ring *pref;
};