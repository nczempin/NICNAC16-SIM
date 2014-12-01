package de.czempin.nicnac16;


public enum Instruction {
	ADD(){
		public void execute(int word, Processor p){
			int address = word & 0x00000FFF; // extract address
			System.out.println(address);
			int value = p.readMemory(address);
			System.out.println(value);
			p.PC++;
			p.AC += value; //TODO: condition bits
		}
	};

	public void execute(int instruction, Processor p) {
		// by default, do nothing
		
	}
}
