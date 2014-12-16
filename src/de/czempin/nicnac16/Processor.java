package de.czempin.nicnac16;

public class Processor {
	int mem[] = new int[65636];
	public int PC;
	public int AC;

	public int readMemory(int address) {
		printMemory(address);
		return mem[address];
	}
	public void writeMemory(int address, int value) {
		mem[address] = value;
		printMemory(address);
	}

	private void printMemory(int address) {
		// align to 8 words
		int start = (address / 8) * 8;
		System.out.print(String.format("(%04x): ", start));
		for (int i = start; i < start + 8; i++) {
			String string = String.format("%04x", mem[i]);
			System.out.print(string);
			if (i == address) {
				System.out.print("*");
			} else {
				System.out.print(" ");
			}
		}
		System.out.println();
	}


	public void printState() {
		// registers
		final String formatted = String.format("PC: %h, AC: %h", PC, AC);
		System.out.println(formatted);
	}

}
