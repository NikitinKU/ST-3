// Copyright 2024 Kirill Nikitin

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdint>
#include <chrono> // NOLINT [build/c++11]
#include <thread> // NOLINT [build/c++11]
#include "TimedDoor.h"

class MockTimerClient : public TimerClient {
 public:
  MOCK_METHOD(void, Timeout, ());
};

class TimedDoorTest : public ::testing::Test {
 protected:
  TimedDoor door;
  MockTimerClient mockClient;
  Timer timer;

  TimedDoorTest() : door(1), timer() {}

  void SetUp() override {
      timer.tregister(door.getTimeOut(), &mockClient);
  }

  void TearDown() override {
      testing::Mock::VerifyAndClearExpectations(&mockClient);
  }
};

TEST_F(TimedDoorTest, id_door_open_method_test) {
  EXPECT_FALSE(door.isDoorOpened());
}

TEST_F(TimedDoorTest, close_door_method_test) {
  door.unlock();
  door.lock();
  EXPECT_FALSE(door.isDoorOpened());
}

TEST_F(TimedDoorTest, unlock_door_method_test) {
  door.unlock();
  EXPECT_TRUE(door.isDoorOpened());
}

TEST_F(TimedDoorTest, try_to_open_door_second_time_test) {
  door.unlock();
  EXPECT_THROW(door.unlock(), std::logic_error);
}

TEST_F(TimedDoorTest, lock_door_after_unlock_timeout_test) {
  std::this_thread::sleep_for(std::chrono::seconds(door.getTimeOut() + 1));
  EXPECT_NO_THROW(door.throwState());
}

TEST_F(TimedDoorTest, lock_before_timeout_then_open_throw_test) {
  std::this_thread::sleep_for(std::chrono::seconds(door.getTimeOut() + 1));
  door.unlock();
  EXPECT_THROW(door.throwState(), std::runtime_error);
}

TEST_F(TimedDoorTest, unlock_door_then_timeout_exception_test) {
  door.unlock();
  std::this_thread::sleep_for(std::chrono::seconds(door.getTimeOut()));
  EXPECT_THROW(door.throwState(), std::runtime_error);
}

TEST_F(TimedDoorTest, try_to_close_door_second_time) {
  EXPECT_THROW(door.lock(), std::logic_error);
}

TEST_F(TimedDoorTest, open_exception_test) {
    door.unlock();
    EXPECT_THROW(door.throwState(), std::runtime_error);
}

TEST_F(TimedDoorTest, close_timeout_test) {
    EXPECT_NO_THROW(door.throwState());
}
