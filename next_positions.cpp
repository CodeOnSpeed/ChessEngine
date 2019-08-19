#pragma once
char *moves_bishop(char *feld, char f, bool is){
  char *res = (char *) malloc(sizeof(char) * 32);
  for(int i = 0; i < 32; i++){
    *(res + i) = -1;
  }
  int j = 0;
  char i1 = 7-(f&7);
  char i2 = (f&7);
  char i3 = 7-(f>>3);
  char i4 = (f>>3);
  if(is == true){
    for(int i = 1; i <= min_2(i2, i4); i++){
      if((*(feld + f - i*9)&1) == 1){
	break;
      }
      else if(*(feld + f - i*9) == 0){
	res[j++] = f - i*9;
      }
      else{
	res[j++] = f - i*9;
	break;
      }
    }
    for(int i = 1; i <= min_2(i2, i3); i++){
      if((*(feld + f + i*7)&1) == 1){
	break;
      }
      else if(*(feld + f + i*7) == 0){
	res[j++] = f + i*7;
      }
      else{
	res[j++] = f + i*7;
	break;
      }
    }
    for(int i = 1; i <= min_2(i1, i4); i++){
      if((*(feld + f - i*7)&1) == 1){
	break;
      }
      else if(*(feld + f - i*7) == 0){
	res[j++] = f - i*7;
      }
      else{
	res[j++] = f - i*7;
	break;
      }
    }
    for(int i = 1; i <= min_2(i1, i3); i++){
      if((*(feld + f + i*9)&1) == 1){
	break;
      }
      else if(*(feld + f + i*9) == 0){
	res[j++] = f + i*9;
      }
      else{
	res[j++] = f + i*9;
	break;
      }
    }
  }
  else{
    for(int i = 1; i <= min_2(i2, i4); i++){
      if((*(feld + f - i*9)) == 0){
	res[j++] = f - i*9;
      }
      else if((*(feld + f - i*9)&1) == 0){
	break;
      }
      else{
	res[j++] = f - i*9;
	break;
      }
    }
    for(int i = 1; i <= min_2(i2, i3); i++){
      if(*(feld + f + i*7) == 0){
	res[j++] = f + i*7;
      }
      else if((*(feld + f + i*7)&1) == 0){
	break;
      }
      else{
	res[j++] = f + i*7;
	break;
      }
    }
    for(int i = 1; i <= min_2(i1, i4); i++){
      if((*(feld + f - i*7)) == 0){
	res[j++] = f - i*7;
      }
      else if((*(feld + f - i*7)&1) == 0){
	break;
      }
      else{
	res[j++] = f - i*7;
	break;
      }
    }
    for(int i = 1; i <= min_2(i1, i3); i++){
      if(*(feld + f + i*9) == 0){
	res[j++] = f + i*9;
      }
      else if((*(feld + f + i*9)&1) == 0){
	break;
      }
      else{
	res[j++] = f + i*9;
	break;
      }
    }
  }
  return res;
}
//FIXIT
char *moves_rook(char *feld, char f, bool is){
  char *res = (char *) malloc(sizeof(char) * 32);
  int j = 0;
  char i1 = 7-(f&7);
  char i2 = (f&7);
  char i3 = 7-(f>>3);
  char i4 = (f>>3);
  for(int i = 0; i < 32; i++){
    *(res + i) = -1;
  }
  if(is == true){
    for(int i = 1; i <= i2; i++){
      if(*(feld + f - i) == 0){
	res[j++] = f - i;
      }
      else if((*(feld + f - i)&1) == 1){
	break;
      }
      else{
	res[j++] = f - i;
	break;
      }
    }
    for(int i = 1; i <= i1; i++){
      if(*(feld + f + i) == 0){
	res[j++] = f + i;
      }
      else if((*(feld + f + i)&1) == 1){
	break;
      }
      else{
	res[j++] = f + i;
	break;
      }
    }
    for(int i = 1; i <= i4; i++){
      if(*(feld + f - 8*i) == 0){
	res[j++] = f - 8*i;
      }
      else if((*(feld + f - 8*i)&1) == 1){
	break;
      }
      else{
	res[j++] = f - 8*i;
	break;
      }
    }
    for(int i = 1; i <= i3; i++){
      if(*(feld + f + 8*i) == 0){
	res[j++] = f + 8*i;
      }
      else if((*(feld + f + 8*i)&1) == 1){
	break;
      }
      else{
	res[j++] = f + 8*i;
	break;
      }
    }
  }
  else{
    for(int i = 1; i <= i2; i++){
      if(*(feld + f - i) == 0){
	res[j++] = f - i;
      }
      else if((*(feld + f - i)&1) == 0){
	break;
      }
      else{
	res[j++] = f - i;
	break;
      }
    }
    for(int i = 1; i <= i1; i++){
      if(*(feld + f + i) == 0){
	res[j++] = f + i;
      }
      else if((*(feld + f + i)&1) == 0){
	break;
      }
      else{
	res[j++] = f + i;
	break;
      }
    }
    for(int i = 1; i <= i4; i++){
      if(*(feld + f - 8*i) == 0){
	res[j++] = f - 8*i;
      }
      else if((*(feld + f - 8*i)&1) == 0){
	break;
      }
      else{
	res[j++] = f - 8*i;
	break;
      }
    }
    for(int i = 1; i <= i3; i++){
      if(*(feld + f + 8*i) == 0){
	res[j++] = f + 8*i;
      }
      else if((*(feld + f + 8*i)&1) == 0){
	break;
      }
      else{
	res[j++] = f + 8*i;
	break;
      }
    }
  }
  return res;
}

char *moves_pawn(char *feld, char f, bool is){
  char *res = (char *) malloc(sizeof(char) * 32);
  int i = 0;
  for(int i = 0; i < 32; i++){
    *(res + i) = -1;
  }
  i = 0;
  if(is == true){
    if((f&7) == 1){
      if(*(feld + f + 1) == EMPTY){
	res[i++] = f + 1;
	if(*(feld + f + 2) == EMPTY){
	  res[i++] = f + 2;
	}
      }
      if(f > 8){
	if(*(feld + f - 7) == 0){
	  ;
	}
	else if((*(feld + f - 7) & 1) == 0){
	  res[i++] = f - 7;
	}
      }
      if(*(feld + f + 9) == 0);
      else if(f < 55 && (*(feld + f + 9) & 1) == 0){
	res[i++] = f + 9;
      }
    }
    else{
      if(*(feld + f + 1) == EMPTY){
	res[i++] = f + 1;
      }
      if(*(feld + f - 7) == 0);
      else if(f > 7 && (*(feld + f - 7) & 1) == 0){
	res[i++] = f - 7;
      }
      if(*(feld + f + 9) == 0);
      else if(f < 56 && (*(feld + f + 9) & 1) == 0){
	res[i++] = f + 9;
      }
    }
  }
  else{
    if((f&7) == 6){
      if(*(feld + f - 1) == EMPTY){
	res[i++] = f - 1;
	if(*(feld + f - 2) == EMPTY){
	  res[i++] = f - 2;
	}
      }
      if(f < 56){
	if((*(feld + f + 7) & 1) == 1){
	  res[i++] = f + 7;
	}
      }
      if(f > 9 && (*(feld + f - 9) & 1) == 1){
	res[i++] = f - 9;
      }
    }
    else{
      if(*(feld + f - 1) == EMPTY){
	res[i++] = f - 1;
      }
      if(f > 9 && (*(feld + f - 9) & 1) == 1){
	res[i++] = f - 9;
      }
      if(f < 56 && (*(feld + f + 7) & 1) == 1){
	res[i++] = f + 7;
      }
    }
  }
  return res;
}

char *moves_knight(char *feld, char f, bool is){
  int i = 0;
  char *res = (char *) malloc(sizeof(char) * 32);
  for(int i = 0; i < 32; i++){
    *(res + i) = -1;
  }
  if(is == true){
    if(f+2*8 < 63){
      if(((f+1)&7) > (f&7)){
	if((*(feld + f + 2*8 + 1)&1) == 0){
	  res[i++] = f + 2*8 + 1;
	}
      }
      if(((f-1)&7) < (f&7)){
	if((*(feld + f + 2*8 - 1)&1) == 0){
	  res[i++] = f + 2*8 - 1;
	}
      }
    }
    if(f-2*8 >= 0){
      if(((f+1)&7) > (f&7)){
	if((*(feld + f - 2*8 + 1)&1) == 0){
	  res[i++] = f - 2*8 + 1;
	}
      }
      if(((f-1)&7) < (f&7)){
	if((*(feld + f - 2*8 - 1)&1) == 0){
	  res[i++] = f - 2*8 - 1;
	}
      }
    }
    if(f+8 < 64){
      if(((f+2)&7) > (f&7)){
	if((*(feld + f + 1*8 + 2)&1) == 0){
	  res[i++] = f + 1*8 + 2;
	}
      }
      if(((f-2)&7) < (f&7)){
	if((*(feld + f + 1*8 - 2)&1) == 0){
	  res[i++] = f + 1*8 - 2;
	}
      }
    }
    if(f-8 >= 0){
      if(((f+2)&7) > (f&7)){
	if((*(feld + f - 1*8 + 2)&1) == 0){
	  res[i++] = f - 1*8 + 2;
	}
      }
      if(((f-2)&7) < (f&7)){
	if((*(feld + f - 1*8 - 2)&1) == 0){
	  res[i++] = f - 1*8 - 2;
	}
      }
    }
  }
  else{
    if(f+2*8 < 64){
      if(((f+1)&7) > (f&7)){
	if((*(feld + f + 2*8 + 1)&1) == 1 || *(feld + f +2*8 + 1) == 0){
	  res[i++] = f + 2*8 + 1;
	}
      }
      if(((f-1)&7) < (f&7)){
	if((*(feld + f + 2*8 - 1)&1) == 1 || *(feld + f +2*8 - 1) == 0){
	  res[i++] = f + 2*8 - 1;
	}
      }
    }
    if(f-2*8 >= 0){
      if(((f+1)&7) > (f&7)){
	if((*(feld + f - 2*8 + 1)&1) == 1 || *(feld + f -2*8 + 1) == 0){
	  res[i++] = f - 2*8 + 1;
	}
      }
      if(((f-1)&7) < (f&7)){
	if((*(feld + f - 2*8 - 1)&1) == 1 || *(feld + f -2*8 - 1) == 0){
	  res[i++] = f - 2*8 - 1;
	}
      }
    }
    if(f+8 <= 63){
      if(((f+2)&7) > (f&7)){
	if((*(feld + f + 1*8 + 2)&1) == 1 || *(feld + f +1*8 + 2) == 0){
	  res[i++] = f + 1*8 + 2;
	}
      }
      if(((f-2)&7) < (f&7)){
	if((*(feld + f + 1*8 - 2)&1) == 1 ||*(feld + f +1*8 - 2) == 0){
	  res[i++] = f + 1*8 - 2;
	}
      }
    }
    if(f-8 >= 0){
      if(((f+2)&7) > (f&7)){
	if((*(feld + f - 1*8 + 2)&1) == 1 || *(feld + f -1*8 + 2) == 0){
	  res[i++] = f - 1*8 + 2;
	}
      }
      if(((f-2)&7) < (f&7)){
	if((*(feld + f - 1*8 - 2)&1) == 1 || *(feld + f -1*8 - 2) == 0){
	  res[i++] = f - 1*8 - 2;
	}
      }
    }
  }
  return res;
}

char *moves_king(char *feld, char f, bool is){
  char *res = (char *) malloc(sizeof(char) * 32);
  char i1 = (f&7);
  char i3 = (f>>3);
  int j = 0;
  for(int i = 0; i < 32; i++){
    *(res + i) = -1;
  }
  if(is == true){
    if((i1 < 7)){
      if((*(feld + f + 1)&1) == 0){
	res[j++] = f + 1;
      }
      if(i3 < 7){
	if((*(feld + f + 8)&1) == 0){
	  res[j++] = f + 8;
	}
	if((*(feld + f + 9)&1) == 0){
	  res[j++] = f + 9;
	}
	if(i1 > 0){
	  if((*(feld + f + 7)&1) == 0){
	    res[j++] = f + 7;
	  }
	  if((*(feld + f - 1)&1) == 0){
	    res[j++] = f - 1;
	  }
	}
      }
      if(i3>0){
	if((*(feld + f - 8)&1) == 0){
	  res[j++] = f - 8;
	}
	if((*(feld + f - 7)&1) == 0){
	  res[j++] = f - 7;
	}
	if(i1 > 0){
	  if((*(feld + f - 9)&1) == 0){
	    res[j++] = f - 9;
	  }
	}
      }
    }
    else if(i3 > 0){ 
      if((*(feld + f - 1)&1) == 0){
	res[j++] = f - 1;
      }
      if((*(feld + f - 8)&1) == 0){
	res[j++] = f - 8;
      }
      if((*(feld + f - 9)&1) == 0){
	res[j++] = f - 9;
      }
      if(i3 < 7){
	if((*(feld + f + 8)&1) == 0){
	  res[j++] = f + 8;
	}
	if((*(feld + f + 7)&1) == 0){
	  res[j++] = f + 7;
	}
      }
    }
    else{
      if((*(feld + f - 1)&1) == 0){
	res[j++] = f - 1;
      }
      if((*(feld + f + 8)&1) == 0){
	res[j++] = f + 8;
      }
      if((*(feld + f + 9)&1) == 0){
	res[j++] = f + 9;
      }
    }
  }
  else{
    if((i1 < 7)){
      if((*(feld + f + 1)&1) == 1 || *(feld + f + 1) == 0){
	res[j++] = f + 1;
      }
      if(i3 < 7){
	if((*(feld + f + 8)&1) == 1 || *(feld + f + 8) == 0 ){
	  res[j++] = f + 8;
	}
	if((*(feld + f + 9)&1) == 1 || *(feld + f + 9) == 0){
	  res[j++] = f + 9;
	}
	if(i1 > 0){
	  if((*(feld + f + 7)&1) == 1 || *(feld + f + 7) == 0){
	    res[j++] = f + 7;
	  }
	  if((*(feld + f - 1)&1) == 1 || *(feld + f - 1) == 0 ){
	    res[j++] = f - 1;
	  }
	}
      }
      if(i3>0){
	if((*(feld + f - 8)&1) == 1 || *(feld + f - 8) == 0 ){
	  res[j++] = f - 8;
	}
	if((*(feld + f - 7)&1) == 1 || *(feld + f - 7) == 0){
	  res[j++] = f - 7;
	}
	if(i1 > 0){
	  if((*(feld + f - 9)&1) == 1 || *(feld + f - 9) == 0){
	    res[j++] = f - 9;
	  }
	}
      }
    }
    else if(i3 > 0){
      if((*(feld + f - 1)&1) == 1 || *(feld + f - 1) == 0){
	res[j++] = f - 1;
      }
      if((*(feld + f - 8)&1) == 1 || *(feld + f - 8) == 0){
	res[j++] = f - 8;
      }
      if((*(feld + f - 9)&1) == 1 || *(feld + f - 9) == 0){
      res[j++] = f - 9;
      }
      if(i3 < 7){
	if((*(feld + f + 8)&1) == 1 || *(feld + f + 8) == 0){
	  res[j++] = f + 8;
	}
	if((*(feld + f + 7)&1) == 1 || *(feld + f + 7) == 0){
	  res[j++] = f + 7;
	}
      }
    }
    else{
      if((*(feld + f - 1)&1) == 1 || *(feld + f - 1) == 0){
	res[j++] = f - 1;
      }
      if((*(feld + f + 8)&1) == 1 || *(feld + f + 8) == 0){
	res[j++] = f + 8;
      }
      if((*(feld + f + 7)&1) == 1 || *(feld + f + 7) == 0){
	res[j++] = f + 7;
      }
    }
  }
  return res;
}
char *moves_queen(char *feld, char f, bool is){
  char *ret = (char *) malloc(sizeof(char) * 32);
  char *temp = (char *) malloc(sizeof(char) * 16);
  int j = 0;
  for(int i = 0; i < 32; i++){
    *(ret + i) = -1;
  }
  temp = moves_bishop(feld, f, is);
  ret = moves_rook(feld, f, is);
  while(*(ret + (j++)) >= 0);
  for(int i = 0; i < 16; i++){
    *(ret + i + j - 1) = *(temp + i);
  }
  free(temp);
  return ret;
}
char *next_positions(char *feld, bool is){
  count++;
  char king_flag_white = 0;
  int i;
  char king_flag_black = 0;
  char *ret = (char *) malloc(sizeof(char) * 66 * 100);
  char *save = (char *) malloc(sizeof(char) * 32);
  int j2 = 0;
  int j = 0;
  if(is == true){
    for(int ii = 16; ii < 80; ii++){
      i = ii % 64;
      if(*(feld + i) == KING_BLACK){
	king_flag_black = 1;
	continue;
      }
      else if((*(feld + i)&1) == 0){
	continue;
      }
      else if(*(feld + i) == PAWN_WHITE){
	save = moves_pawn(feld, i, true);
	while(*(save + j)  >= 0){
	  for(int i1 = 0; i1 < 66; i1++){
	    *(ret + i1 + (j2)*66) = *(feld + i1);;
	  }
	  *(ret + i + (j2)*66) = 0;
	  *(ret + *(save + j) + (j2)*66) = PAWN_WHITE;
	  if(*(save + j) - i == 2){
	    *(ret + 65 + (j2)*66) -= (*(ret + 65 + (j2)*66)&0b1111);
	    *(ret + 65 + (j2)*66) += 1 + 2*(i>>3);
	  }
	  if((*(save + j)&7) == 7){
	    *(ret + *(save + j) + (j2)*66) = QUEEN_WHITE;
	  }
	  j2++;
	  j++;
	}
	if((*(feld + 65)&1) == 1){
	  if((i&7) == 4 && ((i>>3) == ((*(feld + 65)&0b1110)>>1) - 1)){
	    for(int i1 = 0; i1 < 66; i1++){
	      *(ret + i1 + (j2)*66) = *(feld + i1);
	    }
	    *(ret + i + (j2)*66) = 0;
	    *(ret + 65 + (j2)*66) -= 1;
	    *(ret + i + 9 + (j2++)*66) = PAWN_WHITE;
	  }
	  else if((i&7) == 4 && (i>>3) == ((*(feld + 65)&0b1110)>>1) + 1){
	    for(int i1 = 0; i1 < 66; i1++){
	      *(ret + i1 + (j2)*66) = *(feld + i1);
	    }
	    *(ret + i + (j2)*66) = 0;
	    *(ret + 65 + (j2)*66) -= 1;
	    *(ret + i - 7 + (j2++)*66) = PAWN_WHITE;
	  }
	}//
	/*if(((*save)&7) == 7){
	  *(ret + i) = 0;
	  *(ret + *save + (j2++)*66) = QUEEN_WHITE;
	  }*/
      }
      else if(*(feld + i) == KNIGHT_WHITE){
	save = moves_knight(feld, i, true);
	while(*(save + j) != -1){
	  for(int i1 = 0; i1 < 66; i1++){
	    *(ret + i1 + (j2)*66) = *(feld + i1);
	  }
	  *(ret + i + (j2)*66) = 0;
	  *(ret + *(save + j) + (j2)*66) = KNIGHT_WHITE;
	  j++;
	  *(ret + 65 + (j2++)*66) = 0;
	}
      }
      else if(*(feld + i) == BISHOP_WHITE){
	save = moves_bishop(feld, i, true);
	while(*(save + j) != -1){
	  for(int i1 = 0; i1 < 66; i1++){
	    *(ret + i1 + (j2)*66) = *(feld + i1);
	  }
	  *(ret + i + (j2)*66) = 0;
	  *(ret + *(save + j) + (j2)*66) = BISHOP_WHITE;
	  j++;
	   *(ret + 65 + (j2++)*66) = 0;
	}
      }
      else if(*(feld + i) == ROOK_WHITE){
	save = moves_rook(feld, i, true);
	while(*(save + j) != -1){
	  for(int i1 = 0; i1 < 66; i1++){
	    *(ret + i1 + (j2)*66) = *(feld + i1);
	  }
	  
	  *(ret + i + (j2)*66) = 0;
	  *(ret + *(save + j) + (j2)*66) = ROOK_WHITE;
	  j++;
	   *(ret + 65 + (j2++)*66) = 0;
	}
      }
      else if(*(feld + i) == QUEEN_WHITE){
	save = moves_queen(feld, i, true);
	while(*(save + j) != -1){
	  for(int i1 = 0; i1 < 66; i1++){
	    *(ret + i1 + (j2)*66) = *(feld + i1);
	  }
	  
	  *(ret + i + (j2)*66) = 0;
	  *(ret + *(save + j) + (j2)*66) = QUEEN_WHITE;
	  j++;
	   *(ret + 65 + (j2++)*66) = 0;
	}
      }
      else if(*(feld + i) == KING_WHITE){
	king_flag_white = 1;
	save = moves_king(feld, i, true);
	while(*(save + j) != -1){
	  for(int i1 = 0; i1 < 66; i1++){
	    *(ret + i1 + (j2)*66) = *(feld + i1);
	  }
	  
	  *(ret + i + (j2)*66) = 0;
	  *(ret + *(save + j) + (j2)*66) = KING_WHITE;
	  j++;
	   *(ret + 65 + (j2++)*66) = 0;
	}
      }
      j = 0;
    }
  }
  else{
    for(int ii = 16; ii < 80; ii++){
      i = ii % 64;
      if(*(feld + i) == KING_WHITE){
	king_flag_white = 1;
	continue;
      }
      if(*(feld + i) == EMPTY ||(*(feld + i)&1) == 1){
	continue;
      }
      else if(*(feld + i) == PAWN_BLACK){
	save = moves_pawn(feld, i, false);
	while(*(save + j) != -1){
	  for(int i1 = 0; i1 < 66; i1++){
	    *(ret + i1 + (j2)*66) = *(feld + i1);
	  }
	  *(ret + i + (j2)*66) = 0;
	  *(ret + *(save + j) + (j2)*66) = PAWN_BLACK;
	  if(*(save + j) - i == -2){
	    *(ret + 65 + (j2)*66) -= (*(ret + 65 + (j2)*66)&0b1111);
	    *(ret + 65 + (j2)*66) += 1 + 2*(i>>3);
	  }
	  if((*(save + j)&7) == 0){
	    *(ret + *(save + j) + (j2)*66) = QUEEN_BLACK;
	  }
	  j++;
	  j2++;
	}
	if((*(feld + 65)&1) == 1){
	  if((i&7) == 3 && ((i>>3) == ((*(feld + 65)&0b1110)>>1) - 1)){
	    for(int i1 = 0; i1 < 66; i1++){
	      *(ret + i1 + (j2)*66) = *(feld + i1);
	    }
	    *(ret + i + (j2)*66) = 0;
	    *(ret + 65 + (j2)*66) -= 1;
	    *(ret + i + 7 + (j2++)*66) = PAWN_BLACK;
	  }
	  else if((i&7) == 3 && (i>>3) == ((*(feld + 65)&0b1110)>>1) + 1){
	    for(int i1 = 0; i1 < 66; i1++){
	      *(ret + i1 + (j2)*66) = *(feld + i1);
	    }
	    *(ret + i + (j2)*66) = 0;
	    *(ret + 65 + (j2)*66) -= 1;
	    *(ret + i - 9 + (j2++)*66) = PAWN_BLACK;
	  }
	}
	/*if(((*save)&7) == 0){
	  *(ret + i) = 0;
	  *(ret + *save + (j2++)*66) = QUEEN_BLACK;
	  }*/
      }
      else if(*(feld + i) == KNIGHT_BLACK){
	save = moves_knight(feld, i, false);
	while(*(save + j) != -1){
	  for(int i1 = 0; i1 < 66; i1++){
	    *(ret + i1 + (j2)*66) = *(feld + i1);
	  }
	  
	  *(ret + i + (j2)*66) = 0;
	  *(ret + *(save + j) + (j2)*66) = KNIGHT_BLACK;
	  j++;
	   *(ret + 65 + (j2++)*66) = 0;
	}
      }
      else if(*(feld + i) == BISHOP_BLACK){
	save = moves_bishop(feld, i, false);
	while(*(save + j) != -1){
	  for(int i1 = 0; i1 < 66; i1++){
	    *(ret + i1 + (j2)*66) = *(feld + i1);
	  }
	  
	      *(ret + i + (j2)*66) = 0;
	      *(ret + *(save + j) + (j2)*66) = BISHOP_BLACK;
	  j++;
	   *(ret + 65 + (j2++)*66) = 0;
	}
      }
      else if(*(feld + i) == ROOK_BLACK){
	save = moves_rook(feld, i, false);
	while(*(save + j) != -1){
	  for(int i1 = 0; i1 < 66; i1++){
	    *(ret + i1 + (j2)*66) = *(feld + i1);
	  }
	  
	      *(ret + i + (j2)*66) = 0;
	      *(ret + *(save + j) + (j2)*66) = ROOK_BLACK;
	  j++;
	   *(ret + 65 + (j2++)*66) = 0;
	}
      }
      else if(*(feld + i) == QUEEN_BLACK){
	save = moves_queen(feld, i, false);
	while(*(save + j) != -1){
	  for(int i1 = 0; i1 < 66; i1++){
	    *(ret + i1 + (j2)*66) = *(feld + i1);
	  }
	  
	      *(ret + i + (j2)*66) = 0;
	      *(ret + *(save + j) + (j2)*66) = QUEEN_BLACK;
	  j++;
	   *(ret + 65 + (j2++)*66) = 0;
	}
      }
      else if(*(feld + i) == KING_BLACK){
	king_flag_black = 1;
	save = moves_king(feld, i, false);
	while(*(save + j) != -1){
	  for(int i1 = 0; i1 < 66; i1++){
	    *(ret + i1 + (j2)*66) = *(feld + i1);
	  }
	  
	      *(ret + i + (j2)*66) = 0;
	      *(ret + *(save + j) + (j2)*66) = KING_BLACK;
	  j++;
	   *(ret + 65 + (j2++)*66) = 0;
	}
      }
      j=0;
    }
  }
  if(king_flag_white == 0 || king_flag_black == 0){
    possible_moves = 0;
  }
  else{
    possible_moves = j2;
  }
  free(save);
  return ret;
}
