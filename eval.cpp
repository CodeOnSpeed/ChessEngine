int eval(char *feld /*protec*/){
  int material_weiss = 0;
  int material_schwarz = 0;
  char koenig_schwarz_b = 0;
  char koenig_weiss_b = 0;
  char flag = 0;
  char flag1 = 0;
  char flag2 = 0;
  char flag3 = 0;
  char flag4 = 0;
  char *pawn_white = (char *) alloca(sizeof(char) * 8);
  int j1 = 0;
  char *knight_white = (char *) alloca(sizeof(char) * 2);
  int j2 = 0;
  char *bishop_white = (char *) alloca(sizeof(char) * 2);
  int j3 = 0;
  char *rook_white = (char *) alloca(sizeof(char) * 2);
  int j4 = 0;
  char *queen_white = (char *) alloca(sizeof(char) * 2);
  char queen_white_free = 0;
  char queen_black_free = 0;
  *(queen_white) = 0;
  *(queen_white + 1) = 0;
  char king_white;
  char *pawn_black = (char *) alloca(sizeof(char) * 8);
  int j5 = 0;
  char *knight_black = (char *) alloca(sizeof(char) * 2);
  int j6 = 0;
  char *bishop_black = (char *) alloca(sizeof(char) * 2);
  int j7 = 0;
  char *rook_black = (char *) alloca(sizeof(char) * 2);
  int j8 = 0;
  char *queen_black = (char *) alloca(sizeof(char) * 2);
  *knight_black = 0;
  *knight_white = 0;
  char king_black;
  char bishop_black_free = 0;
  char bishop_white_free = 0;
  char connect_rooks_white = 0;
  char connect_rooks_black = 0;
  char seventh_white = 0;
  char seventh_black = 0;
  char knight_pos_white = 0;
  char knight_pos_black = 0;
  char temp1;
  char temp2;
  char temp_feld;
  char temp = 0;
  char tmp = 0;
  char rook_open_white = 0;
  char rook_open_black = 0;
  int j9 = 0;
  int j10 = 0;
  char center_pawn_white = 0;
  char center_pawn_black = 0;
  char pawn_close_white = 0;
  char pawn_close_black = 0;
  char white_king_pos = 0;
  char black_king_pos = 0;
  char passed_pawn_black = 0;
  char passed_pawn_white = 0;
  *(knight_white + 1) = 0;
  *(knight_black + 1) = 0;
  
  *(queen_black) = 0;
  *(queen_black + 1) = 0;
  for(int i = 0; i < 64; i++){ //no need to check for pawns on 1 or 8 line
    temp_feld = *(feld + i);
    if(temp_feld == EMPTY){
      continue;
    }
    else if(temp_feld == PAWN_WHITE){
      material_weiss++;
      pawn_white[j1++] = i;
    }
    else if(temp_feld == PAWN_BLACK){
      material_schwarz++;
      pawn_black[j2++] = i;
    }
    else if(temp_feld == KNIGHT_WHITE){
      material_weiss+=3;
      knight_white[j3++] = i;
    }
    else if(temp_feld == KNIGHT_BLACK){
      material_schwarz+=3;
      knight_black[j4++] = i;
    }
    else if(temp_feld == BISHOP_WHITE){
      material_weiss+=3;
      bishop_white[j5++] = i;
    }
    else if(temp_feld == BISHOP_BLACK){
      material_schwarz+=3;
      bishop_black[j6++] = i;
    }
    else if(temp_feld == ROOK_WHITE){
      material_weiss+=5;
      rook_white[j7++] = i;
    }
    else if(temp_feld == ROOK_BLACK){
      material_schwarz+=5;
      rook_black[j8++] = i;
    }
    else if(temp_feld == QUEEN_WHITE){
      material_weiss+=8;
      queen_white[j9++] = i;
    }
    else if(temp_feld == QUEEN_BLACK){
      material_schwarz+=8;
      queen_black[j10++] = i;
    }
    else if(temp_feld == KING_WHITE){
      koenig_weiss_b = 1;
      king_white = i;
    }
    else if(temp_feld == KING_BLACK){
      koenig_schwarz_b = 1;
      king_black = i;
    }
  }
  if(koenig_schwarz_b != 1){
    return INT_MAX - 1;
  }
  else if(koenig_weiss_b != 1){
    return -INT_MAX + 1;
  }
  if(j7 >= 1){//possibly better: check how many pawns there are
    temp1 = rook_white[0];
    if(j7 == 2){ //Checking if Rooks are connected
      temp2 = rook_white[1];

      
      //fix of the white one

      
      temp = 0;
      if((temp1&7)==(temp2&7)){
	for(int k = 1; k < (temp2>>3)-(temp1>>3) - 1; k++){
	  if(*(feld + temp1 + 8*k) != 0){
	    temp = 1;
	    break;
	  }
	}
	if(temp == 0){
	  connect_rooks_white = 2;
	}
	else{
	  temp = 0;
	}
      }
      
      if((temp1>>3)==(temp2>>3)){
	for(int k = 1; k < (temp2&7)-(temp1&7); k++){
	  if(*(feld + temp1 + k) != 0){
	    temp = 1;
	    break;
	  }
	}
	if(temp == 0){
	  connect_rooks_white = 3;
	}
	else{
	  temp = 0;
	}
      }

      
      //fix of the white one

      
      if((temp1&7)==6||(temp2&7)==6){
	seventh_white = 1;
	if((temp1&7)==(temp2&7)){         
	  seventh_white = 3;
	}
      }
      for(int i = 0; i < j1; i++){
	if((temp1>>3)==(pawn_white[i]>>3)){
	  temp = 1;
	}
	if((temp2>>3)==(pawn_white[i]>>3)){
	  tmp = 1;
	}
      }
      if(temp == 0){//it goes in here
	rook_open_white++;
	if(tmp == 0){
	  rook_open_white+=2;
	}
      }
      else if(tmp == 0){
        rook_open_white++;
      }
      tmp = 0;
    }
    else{
      if((temp1&7)==6){
	seventh_white = 1;
      }
      for(int i = 0; i < j1; i++){
	if((temp1>>3)==(pawn_white[i]>>3)){
	  temp = 1;
	}
      }
      if(temp==0){
	rook_open_white = 1;
      }
    }
  }
  
  if(j8 >= 1){//possibly better: check how many pawns there are
    temp1 = rook_black[0];
    if(j8 == 2){ //Checking if Rooks are connected
      temp2 = rook_black[1];


      //fix of connect_rooks

      temp = 0;
      if((temp1&7)==(temp2&7)){
	for(int k = 1; k < (temp2>>3)-(temp1>>3) - 1; k++){
	  if(*(feld + temp1 + 8*k) != 0){
	    temp = 1;
	    break;
	  }
	}
	if(temp == 0){
	  connect_rooks_black = 2;
	}
	else{
	  temp = 0;
	}
      }
      
      if((temp1>>3)==(temp2>>3)){
	for(int k = 1; k < (temp2&7)-(temp1&7); k++){
	  if(*(feld + temp1 + k) != 0){
	    temp = 1;
	    break;
	  }
	}
	if(temp == 0){
	  connect_rooks_black = 3;
	}
	else{
	  temp = 0;
	}
      }
      //fix if connext_rooks

      
      if((temp1&7)==1||(temp2&7)==1){
	seventh_black = 1;
	if((temp1&7)==(temp2&7)){         
	  seventh_black = 3;
	}
      }
      temp = 0;
      for(int i = 0; i < j2; i++){
	if((temp1>>3)==(pawn_black[i]>>3)){
	  temp = 1;
	}
	if((temp2>>3)==(pawn_black[i]>>3)){
	  tmp = 1;
	}
      }
      if(temp == 0){
	rook_open_black++;
	if(tmp == 0){
	  rook_open_black+=2;
	}
      }
      else if(tmp == 0){
	rook_open_black++;
      }
    }
    else{
      if((temp1&7)==1){
	seventh_black = 1;
      }
      temp = 0;
      for(int i = 0; i < j2; i++){
	if((temp1>>3)==(pawn_black[i]>>3)){
	  temp = 1;
	}
      }
      if(temp == 0){
	rook_open_black++;
      }
    }
  }
  if(queen_black != 0){
    for(int i = 0; i < j1; i++){
      temp1 = pawn_white[i];
      if((temp1&7) < 6 && (temp1&7) > 1 && (temp1>>3) > 1 && (temp1>>3) < 6){
	if((temp1&7) < 5 && (temp1&7) > 2 && (temp1>>3) > 2 && (temp1>>3) < 5){
	  center_pawn_white+=2;
	}
	else{
	  center_pawn_white++;
	}
      }
    }
    flag1 = 7-(*queen_black&7);
    flag2 = (*queen_black&7);
    flag3 = 7-(*queen_black>>3);
    flag4 = (*queen_black>>3);
    for(int i = 1; i <= min_2(flag2, flag4); i++){
      if(*(feld + *queen_black - i*9) != 0){
	break;
      }
      else{
	queen_black_free++;
      }
    }
    for(int i = 1; i <= min_2(flag1, flag4); i++){
      if(*(feld + *queen_black - i*7) != 0){
	break;
      }
      else{
	queen_black_free++;
      }
    }
    for(int i = 1; i <= min_2(flag2, flag3); i++){
      if(*(feld + *queen_black + i*7) != 0){
	break;
      }
      else{
	queen_black_free++;
      }
    }
    for(int i = 1; i <= min_2(flag1,flag3); i++){
      if(*(feld + *queen_black + i*9) != 0){
	break;
      }
      else{
	queen_black_free++;
      }
    }
  }
    

    
  else{
    for(int i = 0; i < j1; i++){
      material_weiss++;//pawns are worth more
      pawn_close_white += (pawn_white[i]&7);
    }
    if(*(queen_black) == 0 && (king_white>>3) > 2 && (king_white>>3) < 6 && (king_white&7) > 2 && (king_white&7) < 6){
      white_king_pos = 1;
    }
  }
  if(queen_white != 0){
    for(int i = 0; i < j2; i++){
      temp1 = pawn_black[i];
      if(((temp1&7) < 6) && ((temp1&7) > 1) && ((temp1>>3) > 1) && ((temp1>>3) < 6)){
	if(((temp1&7) < 5) &&((temp1&7) > 2) && ((temp1>>3) > 2) && ((temp1>>3) < 5)){
	  center_pawn_black+=2;
	}
	else{
	  center_pawn_black++;
	}
      }
    }
    
    flag1 = 7-(*queen_white&7);
    flag2 = (*queen_white&7);
    flag3 = 7-(*queen_white>>3);
    flag4 = (*queen_white>>3);
    for(int i = 1; i <= min_2(flag2, flag4); i++){
      if(*(feld + *queen_white - i*9) != 0){
	break;
      }
      else{
	queen_white_free++;
      }
    }
    for(int i = 1; i <= min_2(flag1, flag4); i++){
      if(*(feld + *queen_white - i*7) != 0){
	break;
      }
      else{
	queen_white_free++;
      }
    }
    for(int i = 1; i <= min_2(flag2, flag3); i++){
      if(*(feld + *queen_white + i*7) != 0){
	break;
      }
      else{
	queen_white_free++;
      }
    }
    for(int i = 1; i <= min_2(flag1,flag3); i++){
      if(*(feld + *queen_white + i*9) != 0){
	break;
      }
      else{
	queen_white_free++;
      }
    }
  }
  for(int a = 0; a < 2; a++){
    flag = 0;
    if(*(knight_black + a) != 0){
      if(*(knight_black + a) > 7 && *(knight_black + a)< 56){
	temp = *(knight_black + a);
	for(int i = temp; ((i)&7) < ((i + 1)&7); i--){
	  if(*(feld - 7 + i + temp) == PAWN_WHITE || *(feld + 9 + i + temp) == PAWN_WHITE){
	    flag = 1;
	  }
	}
	if(flag == 0){
	  for(int i = temp; ((i)&7) < ((i + 1)&7); i--){
	    if(*(feld+i) == PAWN_WHITE){
	      flag = 1;
	    }
	  }
	  if(flag == 1){
	    knight_pos_black = 1;
	  }
	}
      }
    }
  }
  
  for(int z = 0; z < 2; z++){
    flag1 = 7-(bishop_white[z]&7);
    flag2 = (bishop_white[z]&7);
    flag3 = 7-(bishop_white[z]>>3);
    flag4 = (bishop_white[z]>>3);
    for(int i = 1; i <= min_2(flag2, flag4); i++){
      if(*(feld + bishop_white[z] - i*9) != 0){
	break;
      }
      else{
	bishop_white_free++;
      }
    }
    for(int i = 1; i <= min_2(flag1, flag4); i++){
      if(*(feld + bishop_white[z] - i*7) != 0){
	break;
      }
      else{
	bishop_white_free++;
      }
    }
    for(int i = 1; i <= min_2(flag2, flag3); i++){
      if(*(feld + bishop_white[z] + i*7) != 0){
	break;
      }
      else{
	bishop_white_free++;
      }
    }
    for(int i = 1; i <= min_2(flag1,flag3); i++){
      if(*(feld + bishop_white[z] + i*9) != 0){
	break;
      }
      else{
	bishop_white_free++;
      }
    }
  }

  for(int z = 0; z < 2; z++){
    flag1 = 7-(bishop_black[z]&7);
    flag2 = (bishop_black[z]&7);
    flag3 = 7-(bishop_black[z]>>3);
    flag4 = (bishop_black[z]>>3);
    for(int i = 1; i <= min_2(flag2, flag4); i++){
      if(*(feld + bishop_black[z] - i*9) != 0){
	break;
      }
      else{
	bishop_black_free++;
      }
    }
    for(int i = 1; i <= min_2(flag1, flag4); i++){
      if(*(feld + bishop_black[z] - i*7) != 0){
	break;
      }
      else{
	bishop_black_free++;
      }
    }
    for(int i = 1; i <= min_2(flag2, flag3); i++){
      if(*(feld + bishop_black[z] + i*7) != 0){
	break;
      }
      else{
	bishop_black_free++;
      }
    }
    for(int i = 1; i <= min_2(flag1,flag3); i++){
      if(*(feld + bishop_black[z] + i*9) != 0){
	break;
      }
      else{
	bishop_black_free++;
      }
    }
  }
  
  if(*(queen_black) != 0){
    if((king_white&7)<((king_white + 1)&7)){
      for(int i = 0; i < j1; i++){
	if(pawn_white[i] == king_white + 1){
	  white_king_pos++;
	}
      }
      if((king_white + 8) < 64){
	for(int i = 0; i < j1; i++){
	  if(pawn_white[i] == king_white + 9){
	    white_king_pos++;
	  }
	}
      }
      if((king_white - 8) > 0){
	for(int i = 0; i < j1; i++){
	  if(pawn_white[i] == king_white - 7){
	    white_king_pos++;
	  }
	}
      }
    }
  }
  else{
    flag1 = 0;
    for(int o = 0; o < j1; o++){
      for(int z = (pawn_white[o]&7); z > 0; z--){
	if((pawn_white[o]&7)-z == PAWN_BLACK){
	  flag1 = 1;
	}
      }
    }
    if(flag1 == 0){
      passed_pawn_black++;
    }
    white_king_pos = 0;
  }
  if(*(queen_white) != 0){
    if((king_black&7)>((king_black - 1)&7)){
      for(int i = 0; i < j2; i++){
	if(pawn_black[i] == king_black - 1){
	  black_king_pos ++;
	}
      }
      if((king_black + 8) < 64){
	for(int i = 0; i < j2; i++){
	  if(pawn_black[i] == king_black + 7){
	    black_king_pos++;
	  }
	}
      }
      if((king_black - 8) > 0){
	for(int i = 0; i < j2; i++){
	  if(pawn_black[i] == king_black - 9){
	    black_king_pos++;
	  }
	}
      }
    }
  }
  else{
    flag1 = 0;
    for(int o = 0; o < j2; o++){
      for(int z = (pawn_black[o]&7); z > 0; z--){
	if((pawn_black[o]&7)-z == PAWN_WHITE){
	  flag1 = 1;
	}
      }
    }
    if(flag1 == 0){
      passed_pawn_black++;
    }
    black_king_pos = 0;
  }
  /*printf("%i\n", (passed_pawn_white - passed_pawn_black));
  printf("%i\n", (material_weiss - material_schwarz));
  printf("%i\n", (connect_rooks_white - connect_rooks_black));
  printf("%i\n", (center_pawn_white - center_pawn_black));
  printf("%i\n", (seventh_white - seventh_black));
  printf("%i\n", (rook_open_white - rook_open_black));
  printf("%i\n", (pawn_close_white - pawn_close_black));
  printf("%i\n", (white_king_pos - black_king_pos));
  printf("%i\n", (queen_white_free - queen_black_free));
  printf("%i\n", (knight_pos_white - knight_pos_black));
  printf("%i\n", (bishop_white_free - bishop_black_free));*/
  int aq = PASSED*(passed_pawn_white-passed_pawn_black)+MATERIAL*(material_weiss-material_schwarz)+CONNECT*(connect_rooks_white-connect_rooks_black)+SEVENTH*(seventh_white-seventh_black)+OPENLINE*(rook_open_white-rook_open_black)/*+PROTEC*(protec_white-protec_black)*/+CENTER*(center_pawn_white-center_pawn_black)+END_PAWN*(pawn_close_white-pawn_close_black)+KING_POS*(white_king_pos-black_king_pos)+QUEEN_MOD*(queen_white_free-queen_black_free)+KNIGHT_STRENGTH*(knight_pos_white-knight_pos_black)+BISHOP_MOD*(bishop_white_free-bishop_black_free);
  //printf("%i\n", aq);
  return aq;
}


EVAL_TYPE fast_eval(BOARD b) {
  if(__builtin_popcount(b.king_white)==0)
    return std::numeric_limit<EVAL_TYPE>::min();
  if(__builtin_popcount(b.king_black)==0)
    return std::numeric_limit<EVAL_TYPE>::max();

  BITBOARD king_area_white = area<true>(b.king_white);
  BITBOARD king_area_black = area<true>(b.king_black);

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
  ret +=  tmp*MATERIAL; 

  //Pawns
  BITBOARD pawn_unified = b.pawn_white | b.pawn_black;
  if(  b.queen_white & b.queen_black ){//Not endgame: Pawns should be in the center
    tmp = __builtin_popcount(center<true>(b.queen_white))\
         +__builtin_popcount(center<false>(b.queen_white))\
         -__builtin_popcount(center<true>(b.queen_black))\
         -__builtin_popcount(center<false>(b.queen_black)); 
    ret += tmp*CENTER;
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
  tmp  = row<7>(b.rook_white);
  tmp -= row<2>(b.rook_black);
  ret += tmp*SEVENTH;

  ret += b.protect_rook*CONNECT;

  if(column<0>(pawn_unified)==0)
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
      - it is not attacked by a pawn
  */

  tmp = __builtin_popcount(\
           (shift<LEFT+UP>(b.pawn_white)\
           | shift<RIGHT+UP>(b.pawn_white))\
        & b.knight_black
        & ~(shift<LEFT+DOWN>(b.pawn_black)\
           | shift<RIGHT+DOWN>(b.pawn_black))\
        );

   ret += tmp*KNIGHT_STRENGHT;

}
