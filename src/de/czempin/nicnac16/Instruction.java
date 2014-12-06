package de.czempin.nicnac16;

public enum Instruction {
	ADD() {
		public void execute(int word, Processor p) {
			super.execute(word, p);
			int address = word & 0x00000FFF; // extract address
			int value = p.readMemory(address);

			int newAC = 0; //TODO
			int oldAC = 0; //TODO
			String formatted = String.format("ADD %h: AC (%h)<- AC(%h) + mem[%h] (%h)", address, newAC, oldAC, address, value);
			System.out.println(formatted);
			p.AC += value; // TODO: condition bits
		}
	},
	NOP() {
		public void execute(int word, Processor p) {
			super.execute(word, p);
			System.out.println("NOP");
		}
	};

	public void execute(int instruction, Processor p) {
		p.PC++;
	}
}
