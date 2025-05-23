#!/bin/sh
set -e

# Install required packages
sudo apt-get update
sudo apt-get install -y g++ cmake python3

echo "Setup complete."
