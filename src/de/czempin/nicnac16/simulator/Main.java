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
		int next = 0;
		p.writeMemory(next++, 0b0100 * 4096 + 0xF01); // lda-instruction
		p.writeMemory(next++, 0b0001 * 4096 + 0xF03); // jmp-instruction
		p.writeMemory(0xf03, 0b0001 * 4096 + next); // jmp-instruction
		p.writeMemory(next++, 0b0110 * 4096 + 0xF00); // add-instruction
		p.writeMemory(next++, 0b0101 * 4096 + 0xF02); // sta-instruction
		p.writeMemory(next++, 0x7fff); // Halt and catch fire
		p.writeMemory(0xf00, 0xdead);
		p.writeMemory(0xf01, 0xbeef);
		p.printState();
		while (!done) {
			// fetch instruction
			word = p.readMemory(p.PC);
			
			if (word == 0b0111111111111111) { // magic number
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
