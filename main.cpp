#pragma once
#include <cstdio>
#include "bitboard.cpp"

int main() {

}

void gen_bis_table() {
	static_assert(sizeof(BITBOARD) == 8);
	static_assert(sizeof(COL) == 1);

	for (int i = 0; i != 64; i++) {
		BITBOARD bis = 1ull << i;
		BITBOARD tmp = bis;
		for (int i = 1; i != 8; i++) {
			tmp = shift<RIGHT + UP>(tmp);
			bis |= tmp;
		}
		tmp = bis;
		for (int i = 1; i != 8; i++) {
			tmp = shift<LEFT + DOWN>(tmp);
			bis |= tmp;
		}
		printf("{%#018llx,",bis);


		bis = 1ull << i;
		tmp = bis;
		for (int i = 1; i != 8; i++) {
			tmp = shift<LEFT + UP>(tmp);
			bis |= tmp;
		}
		tmp = bis;
		for (int i = 1; i != 8; i++) {
			tmp = shift<RIGHT + DOWN>(tmp);
			bis |= tmp;
		}
		printf("%#018llx},\n", bis);
	}
}