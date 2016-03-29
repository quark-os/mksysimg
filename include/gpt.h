/*
 * gpt.h
 * 
 * Copyright 2016 Nathan Giddings <nathan@localhost>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#ifndef GPT_H
#define GPT_H

#include "partition.h"

#include <list>
#include <string>

using namespace std;

class GPT
{
public:

	GPT();
	
	GPT(list<Partition>& parts, string mbrFile);
	
	void write(string file);
			
private:

	static const uint64_t MAGIC = 0x5452415020494645;
	static const uint64_t HEADER_LBA = 1;
	static const uint64_t ENTRY_LBA = 2;
	static const uint64_t FIRST_LBA = 40;
	static const uint32_t HEADER_SIZE = 92;
	static const uint32_t ENTRY_SIZE = 128;
	static const uint32_t GPT_REV = 0x00000100;
	
	void writeMBR(ofstream& fout);

	void writeHeader(ofstream& fout);
	
	void writeEntry(ofstream& fout, Partition& part, uint64_t start);
	
	list<Partition> parts;
	
	string mbrFile;
		
};

#endif /* GPT_H */ 
