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
  cache_state state;
  reads++;
  current_cycle++;
  cache_line *line = find_line(addr);
  if (line == NULL) {
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
  } else {
    state = line->get_state();
    if (state == Sm) {
      update_LRU(line);
    } else if (state == Sc) {
      update_LRU(line);
    } else if (state == M) {
      update_LRU(line);
    } else if (state == E) {
      update_LRU(line);
    }
  }
}

void Dragon::PrWr(ulong addr, int processor_number) {
  cache_state state;
  current_cycle++;
  writes++;
  cache_line *line = find_line(addr);

  if (line == NULL) {
    write_misses++;
    cache_line *newline = allocate_line(addr);
    int count = sharers_exclude(addr, processor_number);
    if (count) {
      cache2cache++;
      newline->set_state(Sm);
      bus_writes++;
      sendBusWr(addr, processor_number);

    } else {
      memory_transactions++;
      bus_reads++;
      sendBusRd(addr, processor_number);
      newline->set_state(M);
    }
  } else {
    state = line->get_state();
    if (state == Sm) {
      int shared_line = sharers(addr) > 1;
      if (shared_line) {
        bus_writes++;
        sendBusWr(addr, processor_number);
        update_LRU(line);
      } else {
        line->set_state(M);
        update_LRU(line);
      }
    } else if (state == M) {
      update_LRU(line);
    } else if (state == Sc) {

      int shared_line = sharers(addr) > 1;
      if (shared_line) {
        line->set_state(Sm);
        update_LRU(line);
        bus_writes++;
        sendBusWr(addr, processor_number);
      } else {
        line->set_state(M);
        update_LRU(line);
      }

    } else if (state == E) {
      line->set_state(M);
      update_LRU(line);
    }
  }
}

void Dragon::BusRd(ulong addr) {
  cache_state state;
  cache_line *line = find_line(addr);
  if (line != NULL) {
    state = line->get_state();
    if (state == E) {
      line->set_state(Sc);
    }
    if (state == M) {
      line->set_state(Sm);
      flushes++;
    }
    if (state == Sm) {
      flushes++;
    }
  }
}

void Dragon::BusRdX(ulong addr) {}

void Dragon::BusUpgr(ulong addr) {}

void Dragon::BusWr(ulong addr) {
  cache_state state;
  cache_line *line = find_line(addr);
  if (line != NULL) {
    state = line->get_state();
    if (state == Sm) {
      line->set_state(Sc);
    }
  }
}

bool Dragon::writeback_needed(cache_state state) {
  if (state == Sm || state == M)
    return true;
  else
    return false;
}