package de.czempin.nicnac16.simulator;

import de.czempin.nicnac16.assembler.Instruction;
import de.czempin.nicnac16.assembler.Processor;

public class Main {

	private static Processor p = new Processor();

	public static void main(String[] args) {
		boolean done = false;
		int word = 0;
		int opcode;
		Instruction instruction = null;
		while (!done) {
			// fetch instruction
			word = p.readMemory(p.PC);
			// decode instruction
			opcode = word / 4096; // shift right by 12 (4096 = 2´12). 
			instruction = Decoder.decode(opcode);
			// execute instruction
			instruction.execute(word, p);
			
			done = true;
		}

	}

}
