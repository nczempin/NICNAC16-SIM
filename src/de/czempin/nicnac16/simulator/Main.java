package de.czempin.nicnac16.simulator;

import de.czempin.nicnac16.Instruction;
import de.czempin.nicnac16.Processor;

public class Main {

	private static Processor p = new Processor();

	public static void main(String[] args) {
		boolean done = false;
		int word = 0;
		int opcode;
		Instruction instruction = null;
		p.writeMemory(0, 0b0100 * 4096 + 0xF01); // lda-instruction
		p.writeMemory(1, 0b0110 * 4096 + 0xF00); // add-instruction
		p.writeMemory(0xf, 0x7fff); // Halt and catch fire
		p.writeMemory(0xf00, 0xdead);
		p.writeMemory(0xf01, 0xbeef);
		p.printState();
		while (!done) {
			// fetch instruction
			word = p.readMemory(p.PC);
			
			if (word == 0b0111111111111111) {
				System.out.println("===== END OF LINE =====");
				done = true; // TODO: More elegant with a break? perhaps a processor state?
			} else {
				// decode instruction
				opcode = word / 4096; // shift right by 12 (4096 = 2´12).
				instruction = Decoder.decode(opcode);
				// execute instruction
				instruction.execute(word, p);
				p.printState();
			}
		}

	}

}
