/*
 * gpt.cpp
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


#include "gpt.h"

#include <cstring>
#include <fstream>

GPT::GPT()
{
	
}

GPT::GPT(list<Partition>& parts)
{
	this->parts = parts;
}

void GPT::write(string file)
{
	ofstream fout(file, ofstream::binary);
	writeMBR(fout);
	writeHeader(fout);
	
	size_t index = 0;
	size_t partStart = 40;
	for(Partition p : parts)
	{
		writeEntry(fout, p, partStart);
		partStart += p.blockCount();
		index++;
	}
	for(; index < 152; index++)
	{
		char* zeros = new char[ENTRY_SIZE];
		memset(zeros, 0, ENTRY_SIZE);
		fout.write(zeros, ENTRY_SIZE);
	}
	for(Partition p : parts)
	{
		p.write(fout);
	}
}

void GPT::writeMBR(ofstream& fout)
{
	ifstream fin(mbrFile, ifstream::binary);
	char* data = new char[512];
	memset(data, 0, 512);
	fin.read(data, 512);
	fout.write(data, 512);
	fin.close();
	delete[] data;
}

void GPT::writeHeader(ofstream& fout)
{
	uint32_t numParts = parts.size();
	uint64_t lastLBA = 40;
	for(Partition p : parts)
		lastLBA += p.blockCount();
	
	char* data = new char[512];
	memset(data, 0, 512);
	memcpy(data, &MAGIC, 8);
	memcpy(data+8, &GPT_REV, 4);
	memcpy(data+12, &HEADER_SIZE, 4);
	memcpy(data+24, &HEADER_LBA, 8);
	memcpy(data+40, &FIRST_LBA, 8);
	memcpy(data+48, &lastLBA, 8);
	memcpy(data+72, &ENTRY_LBA, 8);
	memcpy(data+80, &numParts, 4);
	memcpy(data+84, &ENTRY_SIZE, 4);
	fout.write(data, 512);
	delete[] data;
}

void GPT::writeEntry(ofstream& fout, Partition& part, uint64_t start)
{
	uint64_t end = start + part.blockCount() - 1;
	uint64_t guidLo = part.getGUIDLo();
	uint64_t guidHi = part.getGUIDHi();
	char* data = new char[ENTRY_SIZE];
	memset(data, 0, ENTRY_SIZE);
	memcpy(data, &guidLo, 8);
	memcpy(data+8, &guidHi, 8);
	memcpy(data+32, &start, 8);
	memcpy(data+40, &end, 8);
	fout.write(data, ENTRY_SIZE);
}
