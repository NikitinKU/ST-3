// Copyright 2024 Kirill Nikitin

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdint>
#include "TimedDoor.h"

class MockTimerClient : public TimerClient {
public:
  MOCK_METHOD(void, Timeout, ());
};

class TimedDoorTest : public ::testing::Test {
protected:
  void SetUp() override {
    door = new TimedDoor(100);
  }

  void TearDown() override {
    delete door;
  }

  TimedDoor* door;
};

TEST_F(TimedDoorTest, DoorIsInitiallyClosed) {
  EXPECT_FALSE(door->isDoorOpened());
}

TEST_F(TimedDoorTest, UnlockDoor) {
  door->unlock();
  EXPECT_TRUE(door->isDoorOpened());
}

TEST_F(TimedDoorTest, LockDoor) {
  door->unlock();
  door->lock();
  EXPECT_FALSE(door->isDoorOpened());
}

TEST_F(TimedDoorTest, DoorTimeoutWithClosedDoor) {
  EXPECT_THROW(door->DoorTimeOut(), std::runtime_error);
  EXPECT_FALSE(door->isDoorOpened());
}

TEST_F(TimedDoorTest, DoorTimeoutWithOpenDoor) {
  door->unlock();
  EXPECT_NO_THROW(door->DoorTimeOut());
  EXPECT_TRUE(door->isDoorOpened());
}

TEST_F(TimedDoorTest, DoorTimeoutWithOpenAndCloseDoor) {
  door->unlock();
  door->lock();
  EXPECT_THROW(door->DoorTimeOut(), std::runtime_error);
  EXPECT_FALSE(door->isDoorOpened());
}

TEST_F(TimedDoorTest, DoorTimeoutWithOpenAndUnlockDoor) {
  door->unlock();
  door->unlock();
  EXPECT_NO_THROW(door->DoorTimeOut());
  EXPECT_TRUE(door->isDoorOpened());
}

TEST(TimerTest, RegisterTimerClient) {
  Timer timer;
  MockTimerClient client;
  EXPECT_CALL(client, Timeout()).Times(1);
  timer.tregister(100, &client);
}
