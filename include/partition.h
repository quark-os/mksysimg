/*
 * partition.h
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


#ifndef PARTITION_H
#define PARTITION_H

#include <string>
#include <iostream>

using namespace std;

class Partition
{
public:

	Partition();
	
	Partition(string data);
	
	uint64_t getGUIDLo();
	
	uint64_t getGUIDHi();
	
	uint64_t blockCount();
	
	void write(ostream& stream);
			
private:

	string data;

	uint64_t guidLo;
	uint64_t guidHi;

};

#endif /* PARTITION_H */ 
