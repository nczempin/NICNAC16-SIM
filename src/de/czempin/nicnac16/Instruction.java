package de.czempin.nicnac16;

public enum Instruction {
	ADD() {
		public void execute(int word, Processor p) {
			super.execute(word, p);
			int address = word & 0x00000FFF; // extract address
			int value = p.readMemory(address);

			int oldAC = p.AC;
			p.AC += value; // TODO: condition bits
			int newAC = p.AC;
			String formatted = String.format("ADD %h: AC (%h)<- AC(%h) + mem[%h] (%h)", address, newAC, oldAC, address, value);
			System.out.println(formatted);
		}
	},
	NOP() {
		public void execute(int word, Processor p) {
			super.execute(word, p);
			System.out.println("NOP");
		}
	}, JMP, BL, RET, LDA, STA, BAN;

	public void execute(int instruction, Processor p) {
		p.PC++;
	}
}
