#!/bin/bash

sudo rmmod char
sudo make && sudo insmod char.ko
