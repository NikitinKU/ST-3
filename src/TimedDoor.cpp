// Copyright 2024 Kirill Nikitin

#include "TimedDoor.h"
#include <iostream>
#include <stdexcept>
#include <thread> // NOLINT [build/c++11]
#include <chrono> // NOLINT [build/c++11]

DoorTimerAdapter::DoorTimerAdapter(TimedDoor& door) : door(door) {}

void DoorTimerAdapter::Timeout() {
  if (door.isDoorOpened())
    throw std::runtime_error("Your time's up!");
  return;
}

TimedDoor::TimedDoor(int timeout) : iTimeout(timeout), isOpened(false) {
  adapter = new DoorTimerAdapter(*this);
}

bool TimedDoor::isDoorOpened() {
  return isOpened;
}

void TimedDoor::unlock() {
  if (isOpened)
        throw std::logic_error("Door is open!!!");
  isOpened = true;
}

void TimedDoor::lock() {
  if (!isOpened)
    throw std::logic_error("Door is close!!!");
  isOpened = false;
}

int TimedDoor::getTimeOut() const {
    return iTimeout;
}

void TimedDoor::throwState() {
  adapter->Timeout();
}

void Timer::sleep(int time_) {
    std::this_thread::sleep_for(std::chrono::seconds(time_));
}

void Timer::tregister(int timeout, TimerClient* client) {
  client->Timeout();
  sleep(timeout);
  client->Timeout();
}
