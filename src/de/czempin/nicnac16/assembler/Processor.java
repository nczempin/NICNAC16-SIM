package de.czempin.nicnac16.assembler;

public class Processor {
	int mem[] = new int[65636];
	public int PC;
	protected int AC;

	public int readMemory(int address) {
		return mem[address];
	}

}
