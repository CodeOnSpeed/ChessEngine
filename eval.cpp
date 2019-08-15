EVAL_TYPE fast_eval(BOARD b) {
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

  EVAL_TYPE ret; 
  EVAL_TYPE tmp; 

  //Material
  tmp = 1*(__builtin_popcount(b.pawn_white)\
          -__builtin_popcount(b.pawn_black))\
       +3*(__builtin_popcount(b.bishop_white)\
          +__builtin_popcount(b.knight_white)\
          -__builtin_popcount(b.bishop_black)\
          -__builtin_popcount(b.knight_black))\
       +5*(__builtin_popcount(b.rook_white)\
          -__builtin_popcount(b.rook_black))\
       +8*(__builtin_popcount(b.queen_white)\
          -__builtin_popcount(b.queen_black));
  ret += tmp*MATERIAL; 

  //Pawns
  BITBOARD pawn_unified = b.pawn_white | b.pawn_black;
  if(  b.queen_white & b.queen_black ){//Not endgame: Pawns should be in the center
    tmp = __builtin_popcount(center<true>(b.queen_white))\
         +__builtin_popcount(center<false>(b.queen_white))\
         -__builtin_popcount(center<true>(b.queen_black))\
         -__builtin_popcount(center<false>(b.queen_black)); 
    ret += tmp*CENTER;

	//King: should have as many own pawns in front of it as possible
	tmp  = __builtin_popcount(king_front_white & b.pawn_white);
	tmp -= __builtin_popcount(king_front_black & b.pawn_black);
	ret += tmp * KING_MOD;

  } else {//Endgame: King should protect/attack as much pawns as possible, passed pawns are very good
    tmp  = __builtin_popcount(king_area_white&pawn_unified);
    tmp -= __builtin_popcount(king_area_black&pawn_unified);
    ret += tmp*END_PAWN;

    for(char i=1; i<=8; i++){//Pawn are passed, if they are the only one on their column
      char col = colum<i>(pawn_unified);
      tmp += col&pawn_white;
      tmp -= col&pawn_black;
    }
    ret += tmp*PASSED;
  }
  ret += b.protect_pawn*PROTECT;

  //Rooks
  tmp  = __builtin_popcount(row<7>(b.rook_white));
  tmp -= __builtin_popcount(row<2>(b.rook_black));
  ret += tmp*SEVENTH;

  ret += b.protect_rook*CONNECT;

  if(column<1>(pawn_unified)==0)
    tmp = __builtin_popcount(column<1>(b.rook_white))\
         -__builtin_popcount(column<1>(b.rook_black));
  for(i=2; i!=8; i++){
    if(column<i>(pawn_unified)==0){
      tmp += __builtin_popcount(column<i>(b.rook_white));
      tmp -= __builtin_popcount(column<i>(b.rook_black));
    }
  }
  ret += tmp*OPENLINE;

  //Knight
  /*A knight is good, if
      - it is protected by a pawn
      - it is not attackable by a pawn
  */

  /*Wrong version: protected and not imediatly attacked
  tmp = __builtin_popcount(\
           (shift<LEFT+UP>(b.pawn_white)\
           | shift<RIGHT+UP>(b.pawn_white))\
        & b.knight_black
        & ~(shift<LEFT+DOWN>(b.pawn_black)\
           | shift<RIGHT+DOWN>(b.pawn_black))\
        );*/

  BITBOARD paw_ = shift<LEFT+UP>(b.pawn_white) | shift<RIGHT+UP>(b.pawn_white);
  BITBOARD paw = paw | shift<UP>(paw) | shift<2 * UP>(paw) | shift<3 * UP>(paw) | shift<4 * UP>(paw) | shift<5 * UP>(paw);
  BITBOARD pab_ = shift<LEFT + DOWN>(b.pawn_black) | shift<RIGHT + DOWN>(b.pawn_black);
  BITBOARD pab = pab | shift<DOWN>(pab) | shift<2 * DOWN>(pab) | shift<3 * DOWN>(pab) | shift<4 * DOWN>(pab) | shift<5 * DOWN>(pab);

  tmp  = __builtin_popcount(paw_ & b.pawn_white & ~pab);
  tmp -= __builtin_popcount(pab_ & b.pawn_black & ~paw);
  ret += tmp * KNIGHT_STRENGHT;

  //Bishop
  //A bishop is good, if it has many moves and/or is opposite of the enemie's king.
  ret += b.bishop_mobility*BISHOP_MOD;
  /* Bishop mobility can be easiely be generated during next_positions
   * Otherwise, use this:
	
	BITBOARD unified = pawns_unified|b.rook_white|b.rook_black|b.knight_white|b.knight_black|b.bishop_white|b.bishop_black|b.queen_white|b.queen_black|b.king_white|b.king_black;
	unsigned char b=0;
	
	shift_inplace<LEFT+UP>(b.bishop_white);
	b.bishop_white &= ~(unified);
	tmp = __builtin_popcount(b.bishop_white);
	for(int i=2; i<=7; i++){
		shift_inplace<LEFT+UP>(b.bishop_white);
		b.bishop_white &= ~(unified);
		tmp += __builtin_popcount(b.bishop_white);
	}
	for(int i=1; i<=7; i++){
		shift_inplace<RIGHT+UP>(b.bishop_white);
		b.bishop_white &= ~(unified);
		tmp += __builtin_popcount(b.bishop_white);
	}
	for(int i=1; i<=7; i++){
		shift_inplace<LEFT+DOWN>(b.bishop_white);
		b.bishop_white &= ~(unified);
		tmp += __builtin_popcount(b.bishop_white);
	}
	for(int i=1; i<=7; i++){
		shift_inplace<RIGHT+DOWN>(b.bishop_white);
		b.bishop_white &= ~(unified);
		tmp += __builtin_popcount(b.bishop_white);
	}
	for(int i=1; i<=7; i++){
		shift_inplace<LEFT+UP>(b.bishop_black);
		b.bishop_black &= ~(unified);
		tmp -= __builtin_popcount(b.bishop_black);
	}
	for(int i=1; i<=7; i++){
		shift_inplace<RIGHT+UP>(b.bishop_black);
		b.bishop_black &= ~(unified);
		tmp -= __builtin_popcount(b.bishop_black);
	}
	for(int i=1; i<=7; i++){
		shift_inplace<LEFT+DOWN>(b.bishop_black);
		b.bishop_black &= ~(unified);
		tmp -= __builtin_popcount(b.bishop_black);
	}
	for(int i=1; i<=7; i++){
		shift_inplace<RIGHT+DOWN>(b.bishop_black);
		b.bishop_black &= ~(unified);
		tmp -= __builtin_popcount(b.bishop_black);
	}
	ret += tmp*BISHOP_MOD;
  */

  //Queen:
  //Like the bishop, a queen is good, if it has many squares
  ret += b.queen_mobility*QUEEN_MOD;
  /*
	If not generated in next_positions_use a similar script
	as for the bishop.
  */
}