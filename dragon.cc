/************************************************************
                        Course          :       CSC506
                        Source          :       dragon.cc
                        Instructor      :       Ed Gehringer
                        Email Id        :       efg@ncsu.edu
------------------------------------------------------------
        © Please do not replicate this code without consulting
                the owner & instructor! Thanks!
Code Integration : Tarun Govind Kesavamurthi
*************************************************************/
#include <assert.h>
#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
#include "dragon.h"
#include "main.h"

/*
------------------------------------------------------
Don't modify the fucntions included in this section
------------------------------------------------------
*/
cache_line *Dragon::allocate_line_dir(ulong addr) { return NULL; }
void Dragon::signalRd(ulong addr, int processor_number) {}
void Dragon::signalRdX(ulong addr, int processor_number) {}
void Dragon::signalUpgr(ulong addr, int processor_number) {}
void Dragon::Inv(ulong addr) {}
void Dragon::Int(ulong addr) {}
void Dragon::PrRdDir(ulong addr, int processor_number) {}
void Dragon::PrWrDir(ulong addr, int processor_number) {}
//-------------------------------------------------------------
// Section ends here. edit the functions in the section below
//-------------------------------------------------------------

void Dragon::PrRd(ulong addr, int processor_number) {}

void Dragon::PrWr(ulong addr, int processor_number) {}

void Dragon::BusRd(ulong addr) {}

void Dragon::BusRdX(ulong addr) {}

void Dragon::BusUpgr(ulong addr) {}

void Dragon::BusWr(ulong addr) {}
//}

bool Dragon::writeback_needed(cache_state state) {}
