package de.czempin.nicnac16;

public class Processor {
	int mem[] = new int[65636];
	public int PC;
	public int AC;

	public int readMemory(int address) {
		return mem[address];
	}

	public void writeMemory(int address, int value) {
		mem[address] = value;
	}

}
