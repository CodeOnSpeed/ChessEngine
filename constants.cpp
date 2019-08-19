#pragma once
//Types
#define EVAL_TYPE signed short
#define NEXT_MOVES_TYPE unsigned char
#define TIME_TYPE long long int
#define HASH_OUT_TYPE unsigned

//Eval-Weights
#define MATERIAL          (30)
#define ROOK_CONNECT      (6 )
#define ROOK_DOUBLE       (7 )
#define ROOK_OPENLINE     (9 )
#define ROOK_HALFOPENLINE (4 )
#define ROOK_SEVENTH      (15)
#define ROOK_QUEEN        (2 )
#define PAWN_PROTEC       (3 )
#define PAWN_END          (18)
#define PAWN_CENTER       (9 )
#define PAWN_PASSED       (12)
#define KING_POS          (9 )
#define QUEEN_POS         (1 )
#define BISHOP_POS        (1 )
#define BISHOP_PAIR       (1 )
#define BISHOP_KING       (1 )
#define KNIGHT_STRENGTH   (10)

//suggest-constants
#define MAX_DEPTH         (96)
#define MAX_BRANCH_FAC    (128)
#define MULTI_THREAD      (false)
#define THREADS           (1 )

//Hashtable-constants
#deinfe MAX_HASH_ENTRYS 1e9