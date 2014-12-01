package de.czempin.nicnac16.simulator;

import de.czempin.nicnac16.Instruction;

public class Decoder {

	public static Instruction decode(int opcode) {
		switch (opcode) {
		case 0b0110:

			return Instruction.ADD;
		default:
			throw new RuntimeException();
		}
	}

}
