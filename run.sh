#!/bin/sh
set -e

# Directory for compiled classes
BIN_DIR="bin"
SRC_DIR="src"
LIB_DIR="lib"

# Ensure bin directory exists
mkdir -p "$BIN_DIR"

# Generate sources from the shared ISA specification
scripts/generate_from_spec.py

# Build classpath from jars in lib directory and JUnit
CP="/opt/gradle/lib/junit-4.13.2.jar:/opt/gradle/lib/hamcrest-core-1.3.jar"
if ls "$LIB_DIR"/*.jar >/dev/null 2>&1; then
    EXTRA=$(echo "$LIB_DIR"/*.jar | tr ' ' ':')
    CP="$CP:$EXTRA"
fi

# Collect all Java source files
find "$SRC_DIR" -name '*.java' > sources.txt

# Compile
javac -d "$BIN_DIR" -cp "$CP" @sources.txt

# Determine test classes (all *Test.java under src/test/java)
TESTS=$(find "$SRC_DIR/test/java" -name '*Test.java' \
    | sed "s#^$SRC_DIR/test/java/##" \
    | sed 's#\.java$##' \
    | tr '/' '.')

# Run tests
java -cp "$BIN_DIR:$CP" org.junit.runner.JUnitCore $TESTS
