#pragma once
#ifndef MOVE_H
#define MOVE_H
#include <cstdint>
#include <string>
enum class MoveCategory
{
    Physical,
    Special,
    Status
};  // uint8_t voor memory efficiency
enum class Status : uint8_t
{
    None,
    Sleep,
    Paralyze,
    Burn,
    Poison,
    Freeze
};

enum class Type : uint8_t
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
// template struct
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
