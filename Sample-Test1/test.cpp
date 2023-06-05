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

TEST(TestCaseName, FiveRead) {

	FlashSystemMock fs_mock;

	EXPECT_CALL(fs_mock, read)
		.Times(5);

	DeviceDriver device_driver(&fs_mock);
	device_driver.read(0xA);
}

TEST(TestCaseName, Exception) {

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