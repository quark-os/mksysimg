/*
 * partition.cpp
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


#include "partition.h"

#include <cstring>
#include <fstream>
#include <fsutil/file.h>

Partition::Partition()
{
	
}

Partition::Partition(string data)
{
	//50 45 41 4e 55 54 53 20       41 4e 44 20 53 4f 41 50
	this->data = data;
	this->guidLo = 0x205354554E414550;
	this->guidHi = 0x50414F5320444E41;
}

uint64_t Partition::blockCount()
{
	File f(data);
	return (f.getSize() + (512 - (f.getSize() % 512))) / 512;
}

uint64_t Partition::getGUIDLo()
{
	return guidLo;
}

uint64_t Partition::getGUIDHi()
{
	return guidHi;
}

void Partition::write(ostream& stream)
{
	ifstream in(data, ifstream::binary);
	uint64_t blocks = blockCount();
	char* filedata = new char[blocks*512];
	memset(filedata, 0, blocks*512);
	in.read(filedata, blocks*512);
	stream.write(filedata, blocks*512);
	in.close();
}


