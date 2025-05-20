NICNAC16-SIM
============

Software simulator implementing the evolving Instruction Set Architecture of my NICNAC16 design.

Testing
-------

JUnit 4 tests reside under `src/test/java`. To run them you need the JUnit and
Hamcrest libraries on the class path. The JUnit jars that ship with the Gradle
installation on this environment can be used:

```
javac -d bin -cp /opt/gradle/lib/junit-4.13.2.jar:/opt/gradle/lib/hamcrest-core-1.3.jar \
    src/de/czempin/nicnac16/*.java src/de/czempin/nicnac16/simulator/*.java \
    src/test/java/de/czempin/nicnac16/simulator/DecoderTest.java
java -cp bin:/opt/gradle/lib/junit-4.13.2.jar:/opt/gradle/lib/hamcrest-core-1.3.jar \
    org.junit.runner.JUnitCore de.czempin.nicnac16.simulator.DecoderTest
```

Any IDE with JUnit support can run the tests as well.

Shared ISA Specification
-----------------------

The opcodes and fields are described in the `NICNAC16-ISA` directory.  During
`run.sh` the `scripts/generate_from_spec.py` script reads `isa.json` and
creates `Instruction.java` and `Decoder.java` automatically.  Other tools such
as the assembler or compiler should include the same specification (ideally via
a git submodule) so they stay in sync with the hardware description.

When the Verilog repository changes the instruction encoding, update the
specification and commit it to `NICNAC16-ISA`.  All projects consuming the spec
should update their submodules and regenerate sources.
