#!/bin/sh
set -e

# Install required packages
sudo apt-get update
sudo apt-get install -y build-essential cmake python3

# Fetch git submodules
git submodule update --init --recursive

echo "Setup complete."
