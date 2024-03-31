// Copyright 2024 Kirill Nikitin

#include "TimedDoor.h"
#include <iostream>
#include <stdexcept>

DoorTimerAdapter::DoorTimerAdapter(TimedDoor& door) : door(door) {}

void DoorTimerAdapter::Timeout() {
  door.throwState();
}

TimedDoor::TimedDoor(int timeout) : iTimeout(timeout), opened(false) {
  adapter = new DoorTimerAdapter(*this);
}

bool TimedDoor::isDoorOpened() {
  return opened;
}

void TimedDoor::unlock() {
  opened = true;
  adapter->Timeout();
}

void TimedDoor::lock() {
  opened = false;
}

void TimedDoor::DoorTimeOut() {
  if (!opened) {
    throw std::runtime_error("Door Timeout");
  }
}

void TimedDoor::throwState() {
  DoorTimeOut();
}

void Timer::tregister(int timeout, TimerClient* client) {
  client->Timeout();
  sleep(timeout);
}
