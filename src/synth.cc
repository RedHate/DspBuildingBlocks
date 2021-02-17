
//*************************************************************************
// File name: synth.cc
// Wizards's Polyphonic Synthesis Sample.
//*************************************************************************
// ./synth 500 600 700 | aplay -f s16_le -r 24000

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>
#include "src/Nco.h"

#define MAX (32768)
#define RATE (24000)

int main(int argc, char **argv)
{
	
	//first of all let's make sure we even have the correct number of arguments.
	if(argc < 2){ 
		printf("Usage: $s freq1, freq2, freq3 | aplay -f s16_le -r 11520\r\n");
		exit(0);
	}
	
	//now we declare our vars, after making sure the program even has the correct args
	//no sense in populating the ram with anything before checking to see if the params
	//are even correct...
	int16_t sample;
	float floatSample;
	float iValue, qValue;
	Nco *ncoPtr[3];

	//if tail param (s), assign pointer and set frequency value 
	if(argc >= 2) ncoPtr[0] = new Nco(RATE,atof(argv[1]));
	if(argc >= 3) ncoPtr[1] = new Nco(RATE,atof(argv[2]));
	if(argc >= 4) ncoPtr[2] = new Nco(RATE,atof(argv[3]));
	
	//i like to localise vars to avoid confusion and mixup and my own sanity...
	int i;
	for (i=0;i<MAX;i++){

		//tone A mutation
		if(argc >= 2) ncoPtr[0]->run(&iValue,&qValue);
		if(argc >= 2) floatSample = iValue;
		
		//tone B mutation
		if(argc >= 3) ncoPtr[1]->run(&iValue,&qValue);
		if(argc >= 3) floatSample += iValue;
		
		//tone C mutation
		if(argc >= 4) ncoPtr[2]->run(&iValue,&qValue);
		if(argc >= 4) floatSample += iValue;
		
		//count
		floatSample *= MAX-1;
		floatSample /= argc;
		
		//cast it to the correct type..
		sample = (int16_t)floatSample;
		
		//write it to stdout to be picked up by: | aplay -f s16_le -r 24000
		fwrite(&sample,sizeof(int16_t),1,stdout);

	}
	
	//clean up
	//int i already declared once above..
	for(i=0;i<argc-1;i++) delete ncoPtr[i];
	
	//return 0 like a human being...
	return 0;

} 


