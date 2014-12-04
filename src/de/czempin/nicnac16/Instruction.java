package de.czempin.nicnac16;

public enum Instruction {
	ADD() {
		public void execute(int word, Processor p) {
			super.execute(word, p);
			int address = word & 0x00000FFF; // extract address
			System.out.println(String.format("address: %h", address));
			int value = p.readMemory(address);
			String formatted = String.format("value: %h", value);
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
