#include "gpt.h"
#include <iostream>

using namespace std;

enum FlagState
{
	NONE,
	OUTFILE,
	MBRFILE
};

int main(int argc, char** args)
{
	string outputFile = "sys.img";
	string mbrFile = "";
	list<Partition> parts;
	FlagState flagState = NONE;
	for(size_t index = 1; index < argc; index++)
	{
		string arg(args[index]);
		switch(flagState)
		{
		case NONE:
			if(arg[0] != '-')
			{
				parts.push_back(Partition(arg));
			}
			else if(arg == "-o")
			{
				flagState = OUTFILE;
			}
			else if(arg == "-m")
			{
				flagState = MBRFILE;
			}
			break;
		case OUTFILE:
			if(arg[0] != '-')
			{
				outputFile = arg;
			}
			else
			{
				cout << "Invalid use of -o" << endl;
				return -1;
			}
			flagState = NONE;
			break;
		case MBRFILE:
			if(arg[0] != '-')
			{
				mbrFile = arg;
			}
			else
			{
				cout << "Invalid use of -m" << endl;
				return -1;
			}
			flagState = NONE;
		}
	}
	
	GPT disk(parts, mbrFile);
	disk.write(outputFile);
	return 0;
}
