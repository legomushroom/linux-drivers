#!/bin/bash

sudo apt-get install kmod -y
sudo apt-get install linux-headers-$(uname -r) -y
sudo apt-get install flex -y
# [??] sudo apt-get install linux-headers-$(uname -r | sed 's/\(.*\)-[a-z]*/\1/'):i386
