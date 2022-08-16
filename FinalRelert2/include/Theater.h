#pragma once

#include <Always.h>

struct TheaterDataType
{
    char Name[16];
    char UIName[32];
    char Root[10];
    char DataMix[10];
    char ExpansionMix[10];
    char Suffix[4];
    char MMSuffix[4];
    char Letter[2];
    float BrightnessAtMinLevel;
    float BrightnessAtMaxLevel;
};
