#pragma once
#include <array>
#include <x86intrin.h>

/*Bitboards are stored like this:     Corresponding bits:
	+--+--+--+--+--+--+--+--+           +--+--+--+--+--+--+--+--+
	|a8|b8|c8|d8|e8|f8|g8|h8|           |56|57|58|59|60|61|62|63|
	+--+--+--+--+--+--+--+--+           +--+--+--+--+--+--+--+--+
	|a7|b7|c7|d7|e7|f7|g7|h7|           |48|49|50|51|52|53|54|55|
	+--+--+--+--+--+--+--+--+           +--+--+--+--+--+--+--+--+
	|a6|b6|c6|d6|e6|f6|g6|h6|           |40|41|42|43|44|45|46|47|
	+--+--+--+--+--+--+--+--+           +--+--+--+--+--+--+--+--+
	|a5|b5|c5|d5|e5|f5|g5|h5|           |32|33|34|35|36|37|38|39|
	+--+--+--+--+--+--+--+--+           +--+--+--+--+--+--+--+--+
	|a4|b4|c4|d4|e4|f4|g4|h4|           |24|25|26|27|28|29|30|31|
	+--+--+--+--+--+--+--+--+           +--+--+--+--+--+--+--+--+
	|a3|b3|c3|d3|e3|f3|g3|h3|           |16|17|18|19|20|21|22|23|
	+--+--+--+--+--+--+--+--+           +--+--+--+--+--+--+--+--+
	|a2|b2|c2|d2|e2|f2|g2|h2|           |08|09|10|11|12|13|14|15|
	+--+--+--+--+--+--+--+--+           +--+--+--+--+--+--+--+--+
	|a1|b1|c1|d1|e1|f1|g1|h1|           |00|01|02|03|04|05|06|07|
	+--+--+--+--+--+--+--+--+           +--+--+--+--+--+--+--+--+

	             |63|62|...|56|55|...|48|...|00|
	BITBOARD b = {h8,g8,...,a8,h7,...,a7,...,a1};
*/
#define BITBOARD unsigned long long
#define COL      unsigned char

struct BOARD {//100Bytes
	//Standart stuff
	BITBOARD pawn_white;
	BITBOARD pawn_black;
	BITBOARD rook_white;
	BITBOARD rook_black;
	BITBOARD knight_white;
	BITBOARD knight_black;
	BITBOARD bishop_white;
	BITBOARD bishop_black;
	BITBOARD queen_white;
	BITBOARD queen_black;
	BITBOARD king_white;
	BITBOARD king_black;
};

namespace detail {
	constexpr std::array<const BITBOARD, 8> col = { \
		(1ull << 56 | 1ull << 48 | 1ull << 40 | 1ull << 32 | 1ull << 24 | 1ull << 16 | 1ull <<  8 | 1ull << 0),\
		(1ull << 57 | 1ull << 49 | 1ull << 41 | 1ull << 33 | 1ull << 25 | 1ull << 17 | 1ull <<  9 | 1ull << 1),\
		(1ull << 58 | 1ull << 50 | 1ull << 42 | 1ull << 34 | 1ull << 26 | 1ull << 18 | 1ull << 10 | 1ull << 2),\
		(1ull << 59 | 1ull << 51 | 1ull << 43 | 1ull << 35 | 1ull << 27 | 1ull << 19 | 1ull << 11 | 1ull << 3),\
		(1ull << 60 | 1ull << 52 | 1ull << 44 | 1ull << 36 | 1ull << 28 | 1ull << 20 | 1ull << 12 | 1ull << 4),\
		(1ull << 61 | 1ull << 53 | 1ull << 45 | 1ull << 37 | 1ull << 29 | 1ull << 21 | 1ull << 13 | 1ull << 5),\
		(1ull << 62 | 1ull << 54 | 1ull << 46 | 1ull << 38 | 1ull << 30 | 1ull << 22 | 1ull << 14 | 1ull << 6),\
		(1ull << 63 | 1ull << 55 | 1ull << 47 | 1ull << 39 | 1ull << 31 | 1ull << 23 | 1ull << 15 | 1ull << 7) \
	};

	constexpr std::array<const BITBOARD, 8> col_block_l = { \
		col[0], \
		col[0] | col[1],\
		col[0] | col[1] | col[2],\
		col[0] | col[1] | col[2] | col[3],\
		col[0] | col[1] | col[2] | col[3] | col[4],\
		col[0] | col[1] | col[2] | col[3] | col[4] | col[5],\
		col[0] | col[1] | col[2] | col[3] | col[4] | col[5] | col[6],\
		col[0] | col[1] | col[2] | col[3] | col[4] | col[5] | col[6] | col[7]\
	};

	constexpr std::array<const BITBOARD, 8> col_block_r = { \
		col[7],\
		col[7] | col[6],\
		col[7] | col[6] | col[5],\
		col[7] | col[6] | col[5] | col[4],\
		col[7] | col[6] | col[5] | col[4] | col[3],\
		col[7] | col[6] | col[5] | col[4] | col[3] | col[2],\
		col[7] | col[6] | col[5] | col[4] | col[3] | col[2] | col[1],\
		col[7] | col[6] | col[5] | col[4] | col[3] | col[2] | col[1] | col[0]\
	};

	constexpr std::array<const BITBOARD, 8> row = { \
		0b11111111ull <<  0, \
		0b11111111ull <<  8, \
		0b11111111ull << 16, \
		0b11111111ull << 24, \
		0b11111111ull << 32, \
		0b11111111ull << 40, \
		0b11111111ull << 48, \
		0b11111111ull << 56  \
	};
}

template<char c>
inline constexpr BITBOARD column(BITBOARD in) {//Not inplace
	static_assert(1<=c && c<=8, "Invalid column");
	return (in)&(detail::col[c-1]);
}

template<char r>
inline constexpr BITBOARD row(BITBOARD in) {//Not inplace
	static_assert(true,"Invalide row");
	return (in)&(detail::row[r-1]);
}

namespace detail {
	//r and c in {0,...,7}
	inline constexpr bool element(BITBOARD b, char r, char c) {
		return (b >> (8 * r + c)) & 1;
	}
}

inline void PRINT_BOARD(BITBOARD b) {
	printf("\n");
	for (int r = 7; r >= 0; r--) {
		printf("\n+-+-+-+-+-+-+-+-+\n|");
		for (int c = 0; c != 8; c++) {
			printf("%d|", detail::element(b,r,c));
		}
	}
	printf("\n+-+-+-+-+-+-+-+-+\n");
}

namespace detail {
	template<unsigned char s>
	inline constexpr BITBOARD shift_up(BITBOARD in) {
		static_assert(1<=s && s<=7, "Invalid shift");
		return in << (8 * s);
	}
	template<unsigned char s>
	inline constexpr BITBOARD shift_down(BITBOARD in) {
		static_assert(1 <= s && s <= 7, "Invalid shift");
		return in >> (8 * s);
	}
	template<unsigned char s>
	inline constexpr BITBOARD shift_left(BITBOARD in) {
		static_assert(1 <= s && s <= 7, "Invalid shift");
		return (in >> s)&(~detail::col_block_r[s - 1]);
	}

	template<unsigned char s>
	inline constexpr BITBOARD shift_right(BITBOARD in) {
		static_assert(1 <= s && s <= 7, "Invalid shift");
		return (in << s)&(~detail::col_block_l[s - 1]);
	}
}

#define UP    (1ull<<0)
#define DOWN  (1ull<<3)
#define LEFT  (1ull<<6)
#define RIGHT (1ull<<9)

template<unsigned short s>
inline constexpr BITBOARD shift(BITBOARD in) {
	constexpr unsigned char up    = (s & (7ull * UP   )) / UP   ;
	constexpr unsigned char down  = (s & (7ull * DOWN )) / DOWN ;
	constexpr unsigned char left  = (s & (7ull * LEFT )) / LEFT ;
	constexpr unsigned char right = (s & (7ull * RIGHT)) / RIGHT;

	BITBOARD ret = in;

	if constexpr (up != 0)
		ret = detail::shift_up<up>(ret);
	if constexpr (down != 0)
		ret = detail::shift_down<down>(ret);
	if constexpr (left != 0)
		ret = detail::shift_left<left>(ret);
	if constexpr (right != 0)
		ret = detail::shift_right<right>(ret);
	return ret;
}

namespace detail {
	/*  Erster Index:
			0 => unten links  bis oben rechts
			1 => unten rechts bis oben links
	
		[0][0]
		00000001
		00000010
		00000100
		00001000
		00010000
		00100000
		01000000
		10000000
		=> 0b1000000001000000001000000001000000001000000001000000001000000001
		=> 0x8040201008040201
	*/
	constexpr std::array<const std::array<BITBOARD, 2>, 64> bishop_attack = {
		(const std::array<BITBOARD, 2>) {0x8040201008040201,0x0000000000000001},
		(const std::array<BITBOARD, 2>) {0x0080402010080402,0x0000000000000102},
		(const std::array<BITBOARD, 2>) {0x0000804020100804,0x0000000000010204},
		(const std::array<BITBOARD, 2>) {0x0000008040201008,0x0000000001020408},
		(const std::array<BITBOARD, 2>) {0x0000000080402010,0x0000000102040810},
		(const std::array<BITBOARD, 2>) {0x0000000000804020,0x0000010204081020},
		(const std::array<BITBOARD, 2>) {0x0000000000008040,0x0001020408102040},
		(const std::array<BITBOARD, 2>) {0x0000000000000080,0x0102040810204080},
		(const std::array<BITBOARD, 2>) {0x4020100804020100,0x0000000000000102},
		(const std::array<BITBOARD, 2>) {0x8040201008040201,0x0000000000010204},
		(const std::array<BITBOARD, 2>) {0x0080402010080402,0x0000000001020408},
		(const std::array<BITBOARD, 2>) {0x0000804020100804,0x0000000102040810},
		(const std::array<BITBOARD, 2>) {0x0000008040201008,0x0000010204081020},
		(const std::array<BITBOARD, 2>) {0x0000000080402010,0x0001020408102040},
		(const std::array<BITBOARD, 2>) {0x0000000000804020,0x0102040810204080},
		(const std::array<BITBOARD, 2>) {0x0000000000008040,0x0204081020408000},
		(const std::array<BITBOARD, 2>) {0x2010080402010000,0x0000000000010204},
		(const std::array<BITBOARD, 2>) {0x4020100804020100,0x0000000001020408},
		(const std::array<BITBOARD, 2>) {0x8040201008040201,0x0000000102040810},
		(const std::array<BITBOARD, 2>) {0x0080402010080402,0x0000010204081020},
		(const std::array<BITBOARD, 2>) {0x0000804020100804,0x0001020408102040},
		(const std::array<BITBOARD, 2>) {0x0000008040201008,0x0102040810204080},
		(const std::array<BITBOARD, 2>) {0x0000000080402010,0x0204081020408000},
		(const std::array<BITBOARD, 2>) {0x0000000000804020,0x0408102040800000},
		(const std::array<BITBOARD, 2>) {0x1008040201000000,0x0000000001020408},
		(const std::array<BITBOARD, 2>) {0x2010080402010000,0x0000000102040810},
		(const std::array<BITBOARD, 2>) {0x4020100804020100,0x0000010204081020},
		(const std::array<BITBOARD, 2>) {0x8040201008040201,0x0001020408102040},
		(const std::array<BITBOARD, 2>) {0x0080402010080402,0x0102040810204080},
		(const std::array<BITBOARD, 2>) {0x0000804020100804,0x0204081020408000},
		(const std::array<BITBOARD, 2>) {0x0000008040201008,0x0408102040800000},
		(const std::array<BITBOARD, 2>) {0x0000000080402010,0x0810204080000000},
		(const std::array<BITBOARD, 2>) {0x0804020100000000,0x0000000102040810},
		(const std::array<BITBOARD, 2>) {0x1008040201000000,0x0000010204081020},
		(const std::array<BITBOARD, 2>) {0x2010080402010000,0x0001020408102040},
		(const std::array<BITBOARD, 2>) {0x4020100804020100,0x0102040810204080},
		(const std::array<BITBOARD, 2>) {0x8040201008040201,0x0204081020408000},
		(const std::array<BITBOARD, 2>) {0x0080402010080402,0x0408102040800000},
		(const std::array<BITBOARD, 2>) {0x0000804020100804,0x0810204080000000},
		(const std::array<BITBOARD, 2>) {0x0000008040201008,0x1020408000000000},
		(const std::array<BITBOARD, 2>) {0x0402010000000000,0x0000010204081020},
		(const std::array<BITBOARD, 2>) {0x0804020100000000,0x0001020408102040},
		(const std::array<BITBOARD, 2>) {0x1008040201000000,0x0102040810204080},
		(const std::array<BITBOARD, 2>) {0x2010080402010000,0x0204081020408000},
		(const std::array<BITBOARD, 2>) {0x4020100804020100,0x0408102040800000},
		(const std::array<BITBOARD, 2>) {0x8040201008040201,0x0810204080000000},
		(const std::array<BITBOARD, 2>) {0x0080402010080402,0x1020408000000000},
		(const std::array<BITBOARD, 2>) {0x0000804020100804,0x2040800000000000},
		(const std::array<BITBOARD, 2>) {0x0201000000000000,0x0001020408102040},
		(const std::array<BITBOARD, 2>) {0x0402010000000000,0x0102040810204080},
		(const std::array<BITBOARD, 2>) {0x0804020100000000,0x0204081020408000},
		(const std::array<BITBOARD, 2>) {0x1008040201000000,0x0408102040800000},
		(const std::array<BITBOARD, 2>) {0x2010080402010000,0x0810204080000000},
		(const std::array<BITBOARD, 2>) {0x4020100804020100,0x1020408000000000},
		(const std::array<BITBOARD, 2>) {0x8040201008040201,0x2040800000000000},
		(const std::array<BITBOARD, 2>) {0x0080402010080402,0x4080000000000000},
		(const std::array<BITBOARD, 2>) {0x0100000000000000,0x0102040810204080},
		(const std::array<BITBOARD, 2>) {0x0201000000000000,0x0204081020408000},
		(const std::array<BITBOARD, 2>) {0x0402010000000000,0x0408102040800000},
		(const std::array<BITBOARD, 2>) {0x0804020100000000,0x0810204080000000},
		(const std::array<BITBOARD, 2>) {0x1008040201000000,0x1020408000000000},
		(const std::array<BITBOARD, 2>) {0x2010080402010000,0x2040800000000000},
		(const std::array<BITBOARD, 2>) {0x4020100804020100,0x4080000000000000},
		(const std::array<BITBOARD, 2>) {0x8040201008040201,0x8000000000000000}
	};
	constexpr std::array<const std::array<BITBOARD, 2>, 64> rook_attack = {
		(const std::array<BITBOARD, 2>) {col[0],row[1]},
		(const std::array<BITBOARD, 2>) {col[1],row[1]},
		(const std::array<BITBOARD, 2>) {col[2],row[1]},
		(const std::array<BITBOARD, 2>) {col[3],row[1]},
		(const std::array<BITBOARD, 2>) {col[4],row[1]},
		(const std::array<BITBOARD, 2>) {col[5],row[1]},
		(const std::array<BITBOARD, 2>) {col[6],row[1]},
		(const std::array<BITBOARD, 2>) {col[7],row[1]},
		(const std::array<BITBOARD, 2>) {col[0],row[1]},
		(const std::array<BITBOARD, 2>) {col[1],row[1]},
		(const std::array<BITBOARD, 2>) {col[2],row[1]},
		(const std::array<BITBOARD, 2>) {col[3],row[1]},
		(const std::array<BITBOARD, 2>) {col[4],row[1]},
		(const std::array<BITBOARD, 2>) {col[5],row[1]},
		(const std::array<BITBOARD, 2>) {col[6],row[1]},
		(const std::array<BITBOARD, 2>) {col[7],row[1]},
		(const std::array<BITBOARD, 2>) {col[0],row[2]},
		(const std::array<BITBOARD, 2>) {col[1],row[2]},
		(const std::array<BITBOARD, 2>) {col[2],row[2]},
		(const std::array<BITBOARD, 2>) {col[3],row[2]},
		(const std::array<BITBOARD, 2>) {col[4],row[2]},
		(const std::array<BITBOARD, 2>) {col[5],row[2]},
		(const std::array<BITBOARD, 2>) {col[6],row[2]},
		(const std::array<BITBOARD, 2>) {col[7],row[2]},
		(const std::array<BITBOARD, 2>) {col[0],row[3]},
		(const std::array<BITBOARD, 2>) {col[1],row[3]},
		(const std::array<BITBOARD, 2>) {col[2],row[3]},
		(const std::array<BITBOARD, 2>) {col[3],row[3]},
		(const std::array<BITBOARD, 2>) {col[4],row[3]},
		(const std::array<BITBOARD, 2>) {col[5],row[3]},
		(const std::array<BITBOARD, 2>) {col[6],row[3]},
		(const std::array<BITBOARD, 2>) {col[7],row[3]},
		(const std::array<BITBOARD, 2>) {col[0],row[4]},
		(const std::array<BITBOARD, 2>) {col[1],row[4]},
		(const std::array<BITBOARD, 2>) {col[2],row[4]},
		(const std::array<BITBOARD, 2>) {col[3],row[4]},
		(const std::array<BITBOARD, 2>) {col[4],row[4]},
		(const std::array<BITBOARD, 2>) {col[5],row[4]},
		(const std::array<BITBOARD, 2>) {col[6],row[4]},
		(const std::array<BITBOARD, 2>) {col[7],row[4]},
		(const std::array<BITBOARD, 2>) {col[0],row[5]},
		(const std::array<BITBOARD, 2>) {col[1],row[5]},
		(const std::array<BITBOARD, 2>) {col[2],row[5]},
		(const std::array<BITBOARD, 2>) {col[3],row[5]},
		(const std::array<BITBOARD, 2>) {col[4],row[5]},
		(const std::array<BITBOARD, 2>) {col[5],row[5]},
		(const std::array<BITBOARD, 2>) {col[6],row[5]},
		(const std::array<BITBOARD, 2>) {col[7],row[5]},
		(const std::array<BITBOARD, 2>) {col[0],row[6]},
		(const std::array<BITBOARD, 2>) {col[1],row[6]},
		(const std::array<BITBOARD, 2>) {col[2],row[6]},
		(const std::array<BITBOARD, 2>) {col[3],row[6]},
		(const std::array<BITBOARD, 2>) {col[4],row[6]},
		(const std::array<BITBOARD, 2>) {col[5],row[6]},
		(const std::array<BITBOARD, 2>) {col[6],row[6]},
		(const std::array<BITBOARD, 2>) {col[7],row[6]},
		(const std::array<BITBOARD, 2>) {col[0],row[7]},
		(const std::array<BITBOARD, 2>) {col[1],row[7]},
		(const std::array<BITBOARD, 2>) {col[2],row[7]},
		(const std::array<BITBOARD, 2>) {col[3],row[7]},
		(const std::array<BITBOARD, 2>) {col[4],row[7]},
		(const std::array<BITBOARD, 2>) {col[5],row[7]},
		(const std::array<BITBOARD, 2>) {col[6],row[7]},
		(const std::array<BITBOARD, 2>) {col[7],row[7]}
	};
	//Does not contain initial square but all captures
	constexpr std::array<COL, 2048> attack_table; //TODO: Initialize this

	template<typename T>
	inline constexpr T min(T a, T b) {
		return (a < b) ? a : b;
	}
	template<typename T>
	inline constexpr T max(T a, T b) {
		return (a < b) ? b : a;
	}
}

//Returns a mask of each position the first bishop inf bis can move to.
inline constexpr BITBOARD bishop_attack_mask(BITBOARD bis, BITBOARD unified, BITBOARD unified_same_team) {
	int ind = __builtin_ffsll(bis);
	BITBOARD mask1 = detail::bishop_attack[ind][0];
	BITBOARD mask2 = detail::bishop_attack[ind][1];
	COL att1 = /*((COL)0b11111111) &*/ _pext_u64(unified, mask1);
	COL att2 = /*((COL)0b11111111) &*/ _pext_u64(unified, mask2);
	int att_ind1 = std::move(  min(ind >> 3, ind & 0b111));
	int att_ind2 = std::move(7-max(ind >> 3, ind & 0b111));
	COL res1 = detail::attack_table[(att1 << 3) + att_ind1] & ~unified_same_team;
	COL res2 = detail::attack_table[(att2 << 3) + att_ind2] & ~unified_same_team;
	return _pdep_u64(res1, mask1) | _pdep_u64(res2, mask2);
}

//Returns a mask of each position the first rook inf rook can move to.
inline constexpr BITBOARD rook_attack_mask(BITBOARD rook, BITBOARD unified, BITBOARD unified_same_team) {
	int ind = __builtin_ffsll(rook);
	BITBOARD mask1 = detail::rook_attack[ind][0];
	BITBOARD mask2 = detail::rook_attack[ind][1];
	COL att1 = /*((COL)0b11111111) &*/ _pext_u64(unified, mask1);
	COL att2 = /*((COL)0b11111111) &*/ _pext_u64(unified, mask2);
	int att_ind1 = ind >> 3;
	int att_ind2 = ind & 0b111;
	COL res1 = detail::attack_table[(att1 << 3) + att_ind1] & ~unified_same_team;
	COL res2 = detail::attack_table[(att2 << 3) + att_ind2] & ~unified_same_team;
	return _pdep_u64(res1, mask1) | _pdep_u64(res2, mask2);
}