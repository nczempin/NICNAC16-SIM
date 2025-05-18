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
