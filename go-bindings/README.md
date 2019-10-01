# WIP/DEBUG - go-bindings for Chia BLS signatures

## Install

Using a fresh Ubuntu 18.04 (latest LTS) install:

```sh
# Install prerequisites
sudo apt update
sudo apt install -y cmake bison build-essential python3 python3-pip

# Clone BLS Signatures and build the library
git clone -b go-bindings2 https://github.com/nmarley/bls-signatures.git
cd bls-signatures
git submodule update --init --recursive
mkdir build
cd build
cmake ../
cmake --build . -- -j 6

# Install Go using gvm
cd $HOME
bash < <(curl -s -S -L https://raw.githubusercontent.com/moovweb/gvm/master/binscripts/gvm-installer)
source $HOME/.gvm/scripts/gvm
gvm install go1.13 -B
gvm use go1.13 --default
```

## Usage

Run the test:

```sh
cd bls-signatures/go-bindings
make
```

This actually passes about 10-20% of the time. The rest of the time it fails
with all `0` bytes for the serialized bytes.

Curiously it only ever fails when `SecretKeyFromBytes` is called. The key
returned from `SecretKeyFromSeed` works every time, never fails at all.
