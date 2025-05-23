#!/bin/bash
set -e

# Install build tools and Python packages
sudo apt-get update
sudo apt-get install -y build-essential cmake python3 python3-pip
pip3 install --upgrade pip
pip3 install pytest flake8

# If using git submodules, initialize them
if [ -f .gitmodules ]; then
    git submodule update --init --recursive
fi
