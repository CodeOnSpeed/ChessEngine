#pragma once
#include <array>
#include "constants.cpp"
#include "bitboard.cpp"
#include "hash_table.cpp"

//Thread-local
std::array<BOARD, MAX_DEPTH*MAX_BRANCH_FAC> tmp_searched;


//All threads
jv_hash_table<HASH_NODE, HASH_OUT_TYPE> trans_table;