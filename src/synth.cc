//*************************************************************************
// File name: synth.cc
// Wizards's Polyphonic Synthesis Sample.
//*************************************************************************
// ./synth 500 600 700 | aplay -f s16_le -r 24000

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>
#include "../include/Nco.h"

int main(int argc, char **argv)
{
	
	if(argc < 2){
		//if you see this you're a fuckin idiot do it right idiot.
		printf("Usage: $s freq1, freq2, freq3 | aplay -f s16_le -r 11520\r\n");
		exit(0);
	}
	
	//no sense in even getting here until we do some checks.
	int16_t sample;
	float floatSample;
	float iValue, qValue;
	Nco *ncoPtr1, *ncoPtr2, *ncoPtr3;

	//more checks and assignment
	if(argc >= 2) ncoPtr1 = new Nco(24000,atof(argv[1]));
	if(argc >= 3) ncoPtr2 = new Nco(24000,atof(argv[2]));
	if(argc >= 4) ncoPtr3 = new Nco(24000,atof(argv[3]));
	
	//i like to localise vars to avoid confusion and mixup and my own sanity...
	int i;
	for (i = 0; i < 32768; i++)
	{

		//toneA
		if(argc >= 2) ncoPtr1->run(&iValue,&qValue);
		if(argc >= 2) floatSample = iValue;
		//toneB
		if(argc >= 3) ncoPtr2->run(&iValue,&qValue);
		if(argc >= 3) floatSample += iValue;
		//toneC
		if(argc >= 4) ncoPtr3->run(&iValue,&qValue);
		if(argc >= 4) floatSample += iValue;
		
		//count
		floatSample *= 32767;
		floatSample /= argc;
		
		//cast it.
		sample = (int16_t)floatSample;
		//write it to stdout to be picked up by: | aplay -f s16_le -r 11520
		fwrite(&sample,sizeof(int16_t),1,stdout);

	}
	
	//clean up
	if(argc >= 2) delete ncoPtr1;
	if(argc >= 3) delete ncoPtr2;
	if(argc >= 4) delete ncoPtr3;

	//return 0 like a human being...
	return 0;

} 

