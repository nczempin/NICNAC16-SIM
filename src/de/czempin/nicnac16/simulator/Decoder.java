package de.czempin.nicnac16.simulator;

import de.czempin.nicnac16.Instruction;

public class Decoder {

	public static Instruction decode(int opcode) {
		// TODO: make this more elegant
		switch (opcode) {
		case 0b0000:
			return Instruction.NOP;
		case 0b0001:
			return Instruction.JMP;
		case 0b0010:
			return Instruction.BL;
		case 0b0011:
			return Instruction.RET;
		case 0b0100:
			return Instruction.LDA;
		case 0b0101:
			return Instruction.STA;
		case 0b0110:
			return Instruction.ADD;
		case 0b1000:
			return Instruction.BAN;
		default:
			throw new RuntimeException();
		}
	}
}
