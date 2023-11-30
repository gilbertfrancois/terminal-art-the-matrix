#!/usr/bin/env bash

pushd /tmp
rm -rf vasm
wget http://phoenix.owl.de/tags/vasm.tar.gz
tar zxvf vasm.tar.gz
cd vasm
make CPU=z80 SYNTAX=oldstyle -Wparentheses
sudo cp vasmz80_oldstyle /usr/local/bin
make CPU=z80 SYNTAX=std -Wparentheses
sudo cp vasmz80_std /usr/local/bin
popd
