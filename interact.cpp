#include <chrono>               //For timing

#define OUTPUT(board);\
printf("-------------------------\n");\
for (int r = 0; r != 8; r++) {\
	for (int c = 0; c != 8; c++) {\
		printf("|");\
		switch (board[IND(r, c)]) {\
		case EMPTY: printf("  ");break;\
		case PAWN_WHITE: printf("PW");break;\
		case PAWN_BLACK: printf("PB");break;\
		case KNIGHT_WHITE: printf("KW");break;\
		case KNIGHT_BLACK: printf("KB");break;\
		case BISHOP_WHITE: printf("BW");break;\
		case BISHOP_BLACK: printf("BB");break;\
		case ROOK_WHITE: printf("RW");break;\
		case ROOK_BLACK: printf("RB");break;\
		case QUEEN_WHITE: printf("QW");break;\
		case QUEEN_BLACK: printf("QB");break;\
		case KING_WHITE: printf("KW");break;\
		case KING_BLACK: printf("KB");break;\
		}\
	}\
	printf("|\n-------------------------\n");\
}

#define engine_move(color,ind,ver);\
	auto sta = std::chrono::high_resolution_clock::now();\
	char* new_board = internal::suggest<ver>(board, time[ind],color);\
	auto sto = std::chrono::high_resolution_clock::now();\
	time[ind] -= std::chrono::duration_cast<std::chrono::nanoseconds>(sto - sta).count();\
	copy_board(board, new_board);

namespace testing {
	char getchar_() {
		char c;
		while ((c = getchar()) == (char)10) {}
		return c;
	}

	//Lässt zwei eval-Versionen gegeneinandr antreten
	inline unsigned* versus(unsigned games, TIME_TYPE t) {
		unsigned games2 = games >> 1;
		unsigned* ret = (unsigned*)malloc(3 * sizeof(unsigned));
		for (unsigned i = 0; i != games2; i++) {
			char board[66];
			copy_board(board, (char*)INITIAL_BOARD);
			TIME_TYPE time[2] = { t,t };
			while (true) {
				if (IS_GAME_FINISHED(board)) { goto end1; }
				else { engine_move(true, 0, true); }
				if (IS_GAME_FINISHED(board)) { goto end1; }
				else { engine_move(false, 1, false); }
			}
		end1:
			ret[IS_GAME_FINISHED(board) - 1]++;


			copy_board(board, (char*)INITIAL_BOARD);
			time[0] = t;
			time[1] = t;
			move1();
			while (true) {
				if (IS_GAME_FINISHED(board)) { goto end2; }
				else { engine_move(true, 0, false); }
				if (IS_GAME_FINISHED(board)) { goto end2; }
				else { enigne_move(false, 1, true); }
			}
		end2:
			ret[IS_GAME_FINISHED(board) - 1]++;
		}
		return ret;
	}

	//Lässt Person gegen Engine spielen
	inline void interactive(TIME_TYPE player_time, TIME_TYPE engine_time) {
		char board[66];
		copy_board(board, (char*)INITIAL_BOARD);
		TIME_TYPE time[2] = { player_time, engine_time };
		while (true) {
			if (IS_GAME_FINISHED(board)) { goto end1; }
			else {
				OUTPUT(board); //TODO: FIXIT
				auto  sta = std::chrono::high_resolution_clock::now();
				char r1, c1, r2, c2;
				c1 = getchar_() - 97;
				r1 = getchar_() - 49;
				c2 = getchar_() - 97;
				r2 = getchar_() - 49;
				printf("%d %d %d %d", c1, r1, c2, r2);
				auto  sto = std::chrono::high_resolution_clock::now();
				board[IND(r2, c2)] = board[IND(r1, c1)];
				board[IND(r1, c1)] = 0;
				time[0] -= std::chrono::duration_cast<std::chrono::nanoseconds>(sto - sta).count(); \
			}
			if (IS_GAME_FINISHED(board)) { goto end1; }
			else { engine_move(black, 1, true); }
		}
	end1:
		printf("%d", IS_GAME_FINISHED(board) - 1);
	}
}