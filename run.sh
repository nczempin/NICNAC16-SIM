#!/bin/sh
set -e

# Directory for compiled classes
BIN_DIR="bin"
SRC_DIR="src"
LIB_DIR="lib"

# Ensure bin directory exists
mkdir -p "$BIN_DIR"

# Build classpath from jars in lib directory
CP=$(echo "$LIB_DIR"/*.jar | tr ' ' ':')

# Collect all Java source files
find "$SRC_DIR" -name '*.java' > sources.txt

# Compile
javac -d "$BIN_DIR" -cp "$CP" @sources.txt

# Determine test classes (all *Test.java under src/test/java)
TESTS=$(find "$SRC_DIR"/test/java -name '*Test.java' | sed 's#^$SRC_DIR/test/java/##;s#\\.java$##;s#/#.#g')

# Run tests
java -cp "$BIN_DIR:$CP" org.junit.runner.JUnitCore $TESTS
