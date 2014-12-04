package de.czempin.nicnac16.simulator;

import de.czempin.nicnac16.Instruction;

public class Decoder {

	public static Instruction decode(int opcode) {
		//TODO: make this more elegant
		switch (opcode) {
		case 0b0000:
			return Instruction.NOP;
		case 0b0110:
			return Instruction.ADD;
		default:
			throw new RuntimeException();
		}
	}

}
