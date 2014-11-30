package de.czempin.nicnac16.simulator;

import de.czempin.nicnac16.assembler.AddInstruction;
import de.czempin.nicnac16.assembler.Instruction;

public class Decoder {

	public static Instruction decode(int opcode) {
		return new AddInstruction();
	}

}
