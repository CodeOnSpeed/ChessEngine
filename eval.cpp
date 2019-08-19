#include "constants.cpp"
#include "bitboard.cpp"

template<char v> //Allows multiple versions of eval to compare
EVAL_TYPE eval(BOARD b) {
	if(__builtin_popcount(b.king_white)==0)
		return std::numeric_limit<EVAL_TYPE>::min();
	if(__builtin_popcount(b.king_black)==0)
		return std::numeric_limit<EVAL_TYPE>::max();

	BITBOARD king_front_white = shift<UP>(b.king_white);
	king_front_white = shift<LEFT>(king_front_white) | shift<RIGHT>(king_front_white);
	BITBOARD king_front_black = shift<DOWN>(b.king_black);
	king_front_black = shift<LEFT>(king_front_black) | shift<RIGHT>(king_front_black);
	
	BITBOARD king_area_white = shift<DOWN>(b.king_front_white) | shift<2*DOWN>(b.king_front_white);
	BITBOARD king_area_black = shift<UP>(b.king_front_black) | shift<2*UP>(b.king_front_black);

	BITBOARD unified_white = b.pawn_white|b.rook_white|b.knight_white|b.bishop_white|b.queen_white|b.king_white;
	BITBOARD unified_black = b.pawn_black|b.rook_black|b.knight_black|b.bishop_black|b.queen_black|b.king_black;
	BITBOARD unified = unified_white | unified_black;

	EVAL_TYPE ret; 
	EVAL_TYPE tmp; 

	//Material
	tmp = 1*(__builtin_popcount(b.pawn_white)   \
	        -__builtin_popcount(b.pawn_black))  \
	     +3*(__builtin_popcount(b.bishop_white) \
	        +__builtin_popcount(b.knight_white) \
	        -__builtin_popcount(b.bishop_black) \
	        -__builtin_popcount(b.knight_black))\
	     +5*(__builtin_popcount(b.rook_white)   \
	        -__builtin_popcount(b.rook_black))  \
	     +8*(__builtin_popcount(b.queen_white)  \
	        -__builtin_popcount(b.queen_black));
	ret = tmp*MATERIAL; 

	//Pawns
	BITBOARD pawn_unified = b.pawn_white | b.pawn_black;
	if(  b.queen_white & b.queen_black ){//Not endgame: Pawns should be in the center
		tmp =  __builtin_popcount(center<true>(b.queen_white)) \
		      +__builtin_popcount(center<false>(b.queen_white))\
		      -__builtin_popcount(center<true>(b.queen_black)) \
		      -__builtin_popcount(center<false>(b.queen_black)); 
		ret += tmp*PAWN_CENTER;

		//King: should have as many own pawns in front of it as possible
		tmp  = __builtin_popcount(king_front_white & b.pawn_white);
		tmp -= __builtin_popcount(king_front_black & b.pawn_black);
		ret += tmp * KING_POS;

	} else {//Endgame: King should protect/attack as much pawns as possible, passed pawns are very good
		tmp  = __builtin_popcount(king_area_white&pawn_unified);
		tmp -= __builtin_popcount(king_area_black&pawn_unified);
		ret += tmp* PAWN_END;

		for(char i=1; i<=8; i++){//Pawn are passed, if they are the only one on their column
			char col = colum<i>(pawn_unified);
			tmp += col&pawn_white;
			tmp -= col&pawn_black;
		}
		ret += tmp*PAWN_PASSED;
	}
	ret += b.protect_pawn*PAWN_PROTEC;

	//Rooks
	/* A rook is good, if
	*	- on the seventh rank and equivalent
	*	- it is on an half-open or (even better) open file
	*	- connectet to another own rook (doubled or connected)
	*	- opposite the enemy's queen
	*/
	tmp  = __builtin_popcount(row<7>(b.rook_white));
	tmp -= __builtin_popcount(row<2>(b.rook_black));
	ret += tmp*ROOK_SEVENTH;

	BITBOARD tmp_rook = b.rook_white;
	for (int i = 0; i != __builtin_popcount(b.rook_white); i++) {
		//Code modified form rook_attack_mask
		int ind = __builtin_ffsll(tmp_rook);
		BITBOARD mask1 = detail::rook_attack[ind][0];
		BITBOARD mask2 = detail::rook_attack[ind][1];
		COL att1 = _pext_u64(unified, mask1);
		COL att2 = _pext_u64(unified, mask2);
		
		if (mask1 & pawn_unified == 0)
			ret += ROOK_OPENLINE;
		else if (__builtin_popcount(mask1 & b.pawn_white) == 0)
			ret += ROOK_HALFOPENLINE;
		if (mask1 & b.queen_black != 0 )
			ret += ROOK_QUEEN;
		
		int att_ind1 = ind >> 3;
		int att_ind2 = ind & 0b111;
		COL res1 = detail::attack_table[(att1 << 3) + att_ind1] & ~unified_white;
		COL res2 = detail::attack_table[(att2 << 3) + att_ind2] & ~unified_white;
		if (_pdep_u64(res1, mask1) & b.rook_white != 0)
			ret += ROOK_DOUBLE;
		if (_pdep_u64(res2, mask2) & b.rook_white != 0)
			ret += ROOK_CONNECT;
		tmp_rook = _blsr_u64(tmp_rook);
	}
	tmp_rook = b.rook_black;
	for (int i = 0; i != __builtin_popcount(b.rook_black); i++) {
		//Code modified form rook_attack_mask
		int ind = __builtin_ffsll(tmp_rook);
		BITBOARD mask1 = detail::rook_attack[ind][0];
		BITBOARD mask2 = detail::rook_attack[ind][1];
		COL att1 = _pext_u64(unified, mask1);
		COL att2 = _pext_u64(unified, mask2);

		if (mask1 & pawn_unified == 0)
			ret -= ROOK_OPENLINE;
		else if (__builtin_popcount(mask1 & b.pawn_black) == 0)
			ret -= ROOK_HALFOPENLINE;
		if (mask1 & b.queen_white != 0)
			ret -= ROOK_QUEEN;

		int att_ind1 = ind >> 3;
		int att_ind2 = ind & 0b111;
		COL res1 = detail::attack_table[(att1 << 3) + att_ind1] & ~unified_black;
		COL res2 = detail::attack_table[(att2 << 3) + att_ind2] & ~unified_black;
		if (_pdep_u64(res1, mask1) & b.rook_black != 0)
			ret -= ROOK_DOUBLE;
		if (_pdep_u64(res2, mask2) & b.rook_black != 0)
			ret -= ROOK_CONNECT;
		tmp_rook = _blsr_u64(tmp_rook);
	}
	
	//Knight
	/*A knight is good, if
		- it is protected by a pawn
		- it is not attackable by a pawn
	*/

	/*Wrong version: protected and not imediatly attacked
	tmp = __builtin_popcount(                 \
	          (shift<LEFT+UP>(b.pawn_white)   \
		    | shift<RIGHT+UP>(b.pawn_white))  \
            & b.knight_black                  \
            & ~(shift<LEFT+DOWN>(b.pawn_black)\
            | shift<RIGHT+DOWN>(b.pawn_black))\
          );
	*/

	BITBOARD paw_ = shift<LEFT+UP>(b.pawn_white) | shift<RIGHT+UP>(b.pawn_white);
	BITBOARD paw = paw | shift<UP>(paw) | shift<2 * UP>(paw) | shift<3 * UP>(paw) | shift<4 * UP>(paw) | shift<5 * UP>(paw);
	BITBOARD pab_ = shift<LEFT + DOWN>(b.pawn_black) | shift<RIGHT + DOWN>(b.pawn_black);
	BITBOARD pab = pab | shift<DOWN>(pab) | shift<2 * DOWN>(pab) | shift<3 * DOWN>(pab) | shift<4 * DOWN>(pab) | shift<5 * DOWN>(pab);

	tmp  = __builtin_popcount(paw_ & b.pawn_white & ~pab);
	tmp -= __builtin_popcount(pab_ & b.pawn_black & ~paw);
	ret += tmp * KNIGHT_STRENGTH;

	//Bishop
	/*A bishop is good, if
	*	- it has many moves
	*	- is opposite of the enemie's king
	*	- is part of a bishop-pair
	*/
	char n_bis_w = __builtin_popcount(b.bishop_white);
	char n_bis_b = __builtin_popcount(b.bishop_black);

	ret += BISHOP_PAIR * ((n_bis_w >> 1) - (n_bis_b >> 1); //Assumes, that there are never more than two bishops per side. When queening, the material value of a queen should outweigh this.
	
	tmp = 0;
	BITBOARD tmp_bis = b.bishop_white;
	for (int i = 0; i != n_bis_w; i++) {
		//Code modified form bishop_attack_mask
		int ind = __builtin_ffsll(tmp_bis); //Index of least significant 1-bit
		BITBOARD mask1 = detail::bishop_attack[ind][0];
		BITBOARD mask2 = detail::bishop_attack[ind][1];

		if ((mask1 | mask2) & b.king_black != 0)
			ret += BISHOP_KING;

		COL att1 = _pext_u64(unified, mask1);
		COL att2 = _pext_u64(unified, mask2);
		int att_ind1 = std::move(    min(ind >> 3, ind & 0b111));
		int	att_ind2 = std::move(7 - max(ind >> 3, ind & 0b111));
		COL res1 = detail::attack_table[(att1 << 3) + att_ind1] & ~unified_white;
		COL res2 = detail::attack_table[(att2 << 3) + att_ind2] & ~unified_white;
		tmp += __builtin_popcount(res1) + __builtin_popcount(res2);
		tmp_bis = _blsr_u64(tmp_bis);
	}
	tmp_bis = b.bishop_black;
	for (int i = 0; i != n_bis_b; i++) {
		//Code modified form bishop_attack_mask
		int ind = __builtin_ffsll(tmp_bis); //Index of least significant 1-bit
		BITBOARD mask1 = detail::bishop_attack[ind][0];
		BITBOARD mask2 = detail::bishop_attack[ind][1];

		if ((mask1 | mask2) & b.king_white != 0)
			ret -= BISHOP_KING;

		COL att1 = _pext_u64(unified, mask1);
		COL att2 = _pext_u64(unified, mask2);
		int att_ind1 = std::move(    min(ind >> 3, ind & 0b111));
		int	att_ind2 = std::move(7 - max(ind >> 3, ind & 0b111));
		COL res1 = detail::attack_table[(att1 << 3) + att_ind1] & ~unified_black;
		COL res2 = detail::attack_table[(att2 << 3) + att_ind2] & ~unified_black;
		tmp -= __builtin_popcount(res1) + __builtin_popcount(res2);
		tmp_bis = _blsr_u64(tmp_bis);
	}
	ret += tmp*BISHOP_POS;
	

	//Queen:
	//A queen is good, if it has many squares
	tmp = 0;
	BITBOARD tmp_que = b.queen_white;
	for(int i=0; i!=__builtin_popcount(b.queen_white); i++){
		int ind = __builtin_ffsll(tmp_que);		
		BITBOARD mask1 = detail::rook_attack[ind][0];
		BITBOARD mask2 = detail::rook_attack[ind][1];
		BITBOARD mask3 = detail::bishop_attack[ind][0];
		BITBOARD mask4 = detail::bishop_attack[ind][1];
		COL att1 = _pext_u64(unified, mask1);
		COL att2 = _pext_u64(unified, mask2);
		COL att3 = _pext_u64(unified, mask3);
		COL att4 = _pext_u64(unified, mask4);
		int att_ind1 = ind >> 3;
		int att_ind2 = ind & 0b111;
		int att_ind3 = std::move(    min(att_ind1, att_ind2));
		int att_ind4 = std::move(7 - max(att_ind1, att_ind2));
		COL res1 = detail::attack_table[(att1 << 3) + att_ind1] & ~unified_white;
		COL res2 = detail::attack_table[(att2 << 3) + att_ind2] & ~unified_white;
		COL res3 = detail::attack_table[(att3 << 3) + att_ind3] & ~unified_white;
		COL res4 = detail::attack_table[(att4 << 3) + att_ind4] & ~unified_white;
		tmp += __builtin_popcount(   \
			_pdep_u64(res1, mask1) | \
			_pdep_u64(res2, mask2) | \
			_pdep_u64(res3, mask3) | \
			_pdep_u64(res4, mask4)   \
		);
	}
	tmp_que = b.queen_black;
	for (int i = 0; i != __builtin_popcount(b.queen_black); i++) {
		int ind = __builtin_ffsll(tmp_que);
		BITBOARD mask1 = detail::rook_attack[ind][0];
		BITBOARD mask2 = detail::rook_attack[ind][1];
		BITBOARD mask3 = detail::bishop_attack[ind][0];
		BITBOARD mask4 = detail::bishop_attack[ind][1];
		COL att1 = _pext_u64(unified, mask1);
		COL att2 = _pext_u64(unified, mask2);
		COL att3 = _pext_u64(unified, mask3);
		COL att4 = _pext_u64(unified, mask4);
		int att_ind1 = ind >> 3;
		int att_ind2 = ind & 0b111;
		int att_ind3 = std::move(min(att_ind1, att_ind2));
		int att_ind4 = std::move(7 - max(att_ind1, att_ind2));
		COL res1 = detail::attack_table[(att1 << 3) + att_ind1] & ~unified_black;
		COL res2 = detail::attack_table[(att2 << 3) + att_ind2] & ~unified_black;
		COL res3 = detail::attack_table[(att3 << 3) + att_ind3] & ~unified_black;
		COL res4 = detail::attack_table[(att4 << 3) + att_ind4] & ~unified_black;
		tmp += __builtin_popcount(\
			_pdep_u64(res1, mask1) | \
			_pdep_u64(res2, mask2) | \
			_pdep_u64(res3, mask3) | \
			_pdep_u64(res4, mask4)   \
		);
		tmp_bis = _blsr_u64(tmp_que);
	}
	ret += QUEEN_POS * tmp;

	return ret;
}