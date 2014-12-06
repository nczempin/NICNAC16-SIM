package de.czempin.nicnac16;

public enum Instruction {
	ADD() {
		public void execute(int word, Processor p) {
			super.execute(word, p);
			int address = word & 0x00000FFF; // extract address
			int value = p.readMemory(address);

			int oldAC = p.AC;
			p.AC = (p.AC + value) % 0xffff; // TODO: condition bits
			int newAC = p.AC;
			String formatted = String.format("ADD %03x: AC (%04x)<- AC(%04x) + mem[%04x] (%04x)", address, newAC, oldAC, address, value);
			System.out.println(formatted);
		}
	},
	NOP() {
		public void execute(int word, Processor p) {
			super.execute(word, p);
			System.out.println("NOP");
		}
	},
	JMP() {
		public void execute(int word, Processor p) {
			super.execute(word, p); // TODO: Do we want to keep this? right now all it does is PC++
			int address = word & 0x00000FFF; // extract address
			p.PC = address;
			System.out.println(String.format("JMP %04x",address));
		}
	},
	BL() {
		public void execute(int word, Processor p) {
			super.execute(word, p);
			System.out.println("BL");
		}
	},
	RET() {
		public void execute(int word, Processor p) {
			super.execute(word, p);
			System.out.println("RET");
		}
	},
	LDA() {
		public void execute(int word, Processor p) {
			super.execute(word, p);
			int address = word & 0x00000FFF; // extract address
			int value = p.readMemory(address);

			p.AC = value; // TODO: condition bits?
			int newAC = p.AC;
			String formatted = String.format("LDA %03x: AC (%04x)<- mem[%04x] (%04x)", address, newAC, address, value);
			System.out.println(formatted);
		}
	},
	STA() {
		public void execute(int word, Processor p) {
			super.execute(word, p);
			int address = word & 0x00000FFF; // extract address
			int value = p.AC;

			p.writeMemory(address, value);
			String formatted = String.format("STA %03x: mem[%04x]<- AC (%04x)", address, address, value);
			System.out.println(formatted);
		}
	},
	BAN() {
		public void execute(int word, Processor p) {
			super.execute(word, p);
			System.out.println("BAN");
		}
	};

	public void execute(int instruction, Processor p) {
		p.PC++;
	}
}
