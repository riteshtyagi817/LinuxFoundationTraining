#!/bin/bash
echo "This script will install essential packages in a given order."

sudo apt-get update

echo "Installing build-essential"
sudo apt-get install build-essential

echo "Installing vim"
sudo apt-get install vim

echo "Installing tree"
sudo apt-get install tree

echo "Installing htop"
sudo apt-get install htop

echo "Installing btop"
sudo apt-get install btop

echo "Installing openssh-client"
sudo apt-get install openssh-client

echo "Installing linux-tools-common"
sudo apt-get install linux-tools-common

echo "Installing linux-tools-generic"
sudo apt-get install linux-tools-generic

echo "Installing linux-tools-\`uname -r\`"
sudo apt-get install linux-tools-`uname -r`

echo "Installing qemu"
sudo apt-get install qemu

echo "Installing qemu-utils"
sudo apt-get install qemu-utils

echo "Installing qemu-kvm"
sudo apt-get install qemu-kvm

echo "Installing virt-manager"
sudo apt-get install virt-manager

echo "Installing libvirt-daemon-system"
sudo apt-get install libvirt-daemon-system

echo "Installing libvirt-clients"
sudo apt-get install libvirt-clients

echo "Installing bridge-utils"
sudo apt-get install bridge-utils

echo "Installing qemu-system-arm"
sudo apt-get install qemu-system-arm

echo "Installing valgrind"
sudo apt-get install valgrind

echo "Installing mlocate"
sudo apt-get install mlocate

echo "Installing crossbuild-essential-armhf"
sudo apt-get install crossbuild-essential-armhf

echo "Installing git"
sudo apt-get install git

echo "Installing bc"
sudo apt-get install bc 

echo "Installing bison"
sudo apt-get install bison

echo "Installing flex"
sudo apt-get install flex

echo "Installing libssl-dev"
sudo apt-get install libssl-dev

echo "Installing make"
sudo apt-get install make

echo "Installing libc6-dev"
sudo apt-get install libc6-dev

echo "Installing libncurses5-dev"
sudo apt-get install libncurses5-dev

echo "Installing Fuse"
sudo apt-get install Fuse

echo "Installing gdb-multiarch"
sudo apt-get install gdb-multiarch

echo "Installing autoconf"
sudo apt-get install autconf

echo "Installing openocd"
sudo apt-get install openocd

echo "Completed"
