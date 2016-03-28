#include "gpt.h"
#include <iostream>

using namespace std;

enum FlagState
{
	NONE,
	OUTFILE
};

int main(int argc, char** args)
{
	string outputFile;
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
		}
	}
	
	GPT disk(parts);
	disk.write(outputFile);
	return 0;
}
