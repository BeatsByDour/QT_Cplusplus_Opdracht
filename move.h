#pragma once
#ifndef MOVE_H
#define MOVE_H

#include <string>

enum class MoveCategory
{
    Physical,
    Special,
    Status
};
enum class Status
{
    None,
    Sleep,
    Paralyze,
    Burn,
    Poison,
    Freeze
};

enum class Type
{
    Earth,
    Water,
    Fire,
    Air,
    Light,
    Dark,
    Flying,
    Ice,
    Normal,
    Count // Voor loops/array sizes
};
struct Move
{
    int     id{};
    std::string name{};
    int     power{};
    int     accuracy{};
    int     maxPP{};
    MoveCategory category{};
    Type    type{};  // 1 type per move
};



#endif // MOVE_H
