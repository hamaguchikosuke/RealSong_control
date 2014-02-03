RealSong_control
================

MATLAB + xPCtarget based realtime detection of sound and playback 

This software is a collection of MATLAB codes for realtime detection 
of a target pattern in animal vocalization (like songbird's song) 
and generation of pre-designed outputs. 

To run this program, it requires two PCs, master and slave. 
Slave PC is installed DA/AD board (we use National Instrments's 
PCI-6251 or PCI-6052) and run in realtime. 
Master PC communicates with slave PC through TCP/IP connection 
and control the program, save data in sound event driven manner. 

All the code is written in MATLAB using xPCtarget toolbox, by Kosuke Hamaguchi.



Acknowledgement:

Sound feature calculation is based on Segal Saar's matlab code.
