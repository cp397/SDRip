/******************************************************************************
 * File:     main.cpp
 * Date:     Created July 2015
 * Author:   Ryan Middleton
 *           Real-time Intelligent Systems and Networks Lab
 *           Northern Arizona University
 *
 * Implements an "SD card ripper" that rips SEGA data from an SD card in RAW 
 * mode, since the SEGA Wisards write raw data to them without using a file 
 * system.
 *****************************************************************************/
//#include "includes.h"
//#include "core.h"

#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include "platform.h"
#include "core.h"
using namespace std;


int main(int argc, char *argv[])
{
	
	printf("Running...\r\n");
	chooseDrive();
	chooseAction();

	printf("Goodbye\r\n");
	return 0;
}

