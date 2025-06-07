package de.czempin.nicnac16.simulator;

import static org.junit.Assert.assertEquals;

import org.junit.Test;

import de.czempin.nicnac16.Instruction;

public class DecoderTest {

    @Test
    public void decodeNop() {
        assertEquals(Instruction.NOP, Decoder.decode(0b0000));
    }

    @Test
    public void decodeJmp() {
        assertEquals(Instruction.JMP, Decoder.decode(0b0001));
    }

    @Test
    public void decodeBl() {
        assertEquals(Instruction.BL, Decoder.decode(0b0010));
    }

    @Test
    public void decodeRet() {
        assertEquals(Instruction.RET, Decoder.decode(0b0011));
    }

    @Test
    public void decodeLda() {
        assertEquals(Instruction.LDA, Decoder.decode(0b0100));
    }

    @Test
    public void decodeSta() {
        assertEquals(Instruction.STA, Decoder.decode(0b0101));
    }

    @Test
    public void decodeAdd() {
        assertEquals(Instruction.ADD, Decoder.decode(0b0110));
    }

    @Test
    public void decodeBan() {
        assertEquals(Instruction.BAN, Decoder.decode(0b1000));
    }

    @Test(expected = RuntimeException.class)
    public void decodeInvalidThrows() {
        Decoder.decode(0b1111);
    }
}
