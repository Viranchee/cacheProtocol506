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
#include "cache.h"
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

void Dragon::PrRd(ulong addr, int processor_number) {
  reads++;
  current_cycle++;
  cache_line *line = find_line(addr);

  if (line == NULL) {
    // Read Miss
    read_misses++;
    cache_line *newline = allocate_line(addr);
    bus_reads++;
    sendBusRd(addr, processor_number);
    int count = sharers_exclude(addr, processor_number);
    if (count) {
      cache2cache++;
      newline->set_state(Sc);
    } else {
      memory_transactions++;
      newline->set_state(E);
    }
    return;
  }
  cache_state state = line->get_state();
  switch (state) {
  case E:
  case Sc:
  case Sm:
  case M:
    update_LRU(line);
  default:
    break;
  }
}

void Dragon::PrWr(ulong addr, int processor_number) {
  writes++;
  current_cycle++;
  cache_line *line = find_line(addr);
  if (line == NULL) {
    write_misses++;
    cache_line *newline = allocate_line(addr);
    int count = sharers_exclude(addr, processor_number);
    if (count) {
      cache2cache++;
      bus_reads++;
      sendBusRd(addr, processor_number);
      bus_writes++;
      sendBusWr(addr, processor_number);
      newline->set_state(Sm);
    } else {
      bus_reads++;
      memory_transactions++;
      sendBusRd(addr, processor_number);
      newline->set_state(M);
    }
    return;
  }
  cache_state state = line->get_state();
  switch (state) {
  case E: {
    line->set_state(M);
    break;
  }
  case M: {
    update_LRU(line);
    break;
  }
  case Sm: {
    update_LRU(line);
    sendBusWr(addr, processor_number);
    bus_writes++;
    int sharedLine =
        sharers_exclude(addr, processor_number); // CHECK Condition to be 1 or 0
    if (!sharedLine) {
      line->set_state(M);
    }
    break;
  }
  case Sc: {
    bool sharedLine = sharers(addr) > 1;
    if (sharedLine) {
      line->set_state(Sm);
    } else {
      line->set_state(M);
    }
    update_LRU(line);
    break;
  }
  default:
    break;
  }
}

void Dragon::BusRd(ulong addr) {
  cache_line *line = find_line(addr);
  cache_state state;
  if (line) {
    state = line->get_state();
    switch (state) {
    case E: {
      line->set_state(Sc);
      cache2cache++;
      break;
    }
    case M: {
      line->set_state(Sm);
      cache2cache++;
      break;
    }
    default:
      break;
    }
  }
}

void Dragon::BusRdX(ulong addr) {
  // LOL
}

void Dragon::BusUpgr(ulong addr) {
  // LOL
}

void Dragon::BusWr(ulong addr) {
  cache_line *line = find_line(addr);
  cache_state state;
  if (line) {
    state = line->get_state();
    switch (state) {
    case Sm: {
      line->set_state(Sc);
      cache2cache++;
      break;
    }
    default:
      break;
    }
  }
}
//}

bool Dragon::writeback_needed(cache_state state) {
  // LOL
}
