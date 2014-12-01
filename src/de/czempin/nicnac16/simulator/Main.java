package de.czempin.nicnac16.simulator;

import de.czempin.nicnac16.assembler.Instruction;

public class Main {

	public static void main(String[] args) {
		boolean done = false;
		int PC = 0;
		int word = 0;
		int mem[]= new int[65636];
		int opcode;
		Instruction instruction = null;
		while(!done){
			// fetch instruction
			word = mem[PC];
			// decode instruction
			opcode = word / 4096; // shift right by 12 (4096 = 2´12)
			instruction = Decoder.decode(opcode);
			// execute instruction
			instruction.execute();
			done = true;
		}
				

	}

}
