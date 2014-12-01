package de.czempin.nicnac16.assembler;

public enum Instruction {
	ADD(){
		public void execute(int word, Processor p){
			int address = word & 0x00000FFF; // extract address
			System.out.println(address);
			int value = p.mem(address);
			System.out.println(value);
			
		}
	};

	public void execute(int instruction, Processor p) {
		// by default, do nothing
		
	}
}
