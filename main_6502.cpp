#include <stdio.h>
#include <stdlib.h>

using Byte = unsigned char;
using Word = unsigned short;

using u32 = unsigned int;

struct Mem {
	static constexpr u32 MAX_MEM = 1024 * 64;
	Byte Data[MAX_MEM];

	void Initialize() {
		for (u32 i = 0; i < MAX_MEM; i++) {
			Data[i] = 0;
		}
	}
	
	Byte operator[]( u32 Address ) const {
		return Data[Address];
	}
};

struct CPU {
	Word PC;
	Word SP;
	
	Byte A, X, Y;
	
	Byte C : 1;
	Byte Z : 1;
	Byte I : 1;
	Byte D : 1;
	Byte B : 1;
	Byte V : 1;
	Byte N : 1;
	
	void Reset( Mem& memory ) {
		PC = 0xFFFC;
		SP = 0x0100;
		C = Z = I = D = B = V = N = 0;
		A = X = Y = 0;
		
		memory.Initialize();
	}
	
	Byte FetchByte( u32& cycles, Mem& memory ) {
		Byte Data = memory[PC];	
		PC++;
		cycles--;
		
		return Data;
	}

	static constexpr Byte INS_LDA_IM = 0xA9;

	void Execute( u32 cycles, Mem& memory ) {
		while (cycles > 0) {
			Byte Ins = FetchByte( cycles, memory);
			switch (Ins) {
				case INS_LDA_IM: {
					Byte Value = FetchByte( cycles, memory);
					A = Value;
					Z = (A == 0);
					N = (A & 0b10000000) > 0;
				} break;
			}
		}
	}
};

int main() {
	Mem mem;
	CPU cpu;
	cpu.Reset( mem );
	cpu.Execute( 2, mem );
	return 0;
}

