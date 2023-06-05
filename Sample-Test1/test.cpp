#pragma once
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../Project2/DeviceDriver.cpp"

using namespace testing;

class FlashSystemMock : public FlashMemoryDevice
{
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

TEST(ReadTest, FiveTimes) {

	FlashSystemMock fs_mock;

	EXPECT_CALL(fs_mock, read)
		.Times(5);

	DeviceDriver device_driver(&fs_mock);
	device_driver.read(0xA);
}

TEST(ReadTest, Exception) {

	FlashSystemMock fs_mock;

	// 스터빙 4번은 잘 읽히는데 5번째는 잘 안읽힘
	EXPECT_CALL(fs_mock, read(0x2))
		.WillOnce(Return(0x7))
		.WillOnce(Return(0x7))
		.WillOnce(Return(0x7))
		.WillOnce(Return(0x7))
		.WillOnce(Return(0x3));

	DeviceDriver device_driver(&fs_mock);
	EXPECT_THROW(device_driver.read(0x2), std::exception);
}

TEST(WriteTest, OneTimes) {

	FlashSystemMock fs_mock;

	EXPECT_CALL(fs_mock, read(0x0))
		.Times(1)
		.WillOnce(Return(0xFF));
	
	EXPECT_CALL(fs_mock, write)
		.Times(1);

	DeviceDriver device_driver(&fs_mock);
	device_driver.write(0x0, 0x11);
}

TEST(WriteTest, Exception) {

	FlashSystemMock fs_mock;

	EXPECT_CALL(fs_mock, read(0x2))
		.WillOnce(Return(0x7));

	DeviceDriver device_driver(&fs_mock);
	EXPECT_THROW(device_driver.write(0x2, 0x0), std::exception);
}