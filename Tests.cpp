#include "stdafx.h"
#include "CppUnitTest.h"
#include "../sem4_lab3/Shannon_Fano.h"
#include <stdexcept>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(Shannon_Fano_Tests)
{
public:
	Shannon_Fano * testFano;
	TEST_METHOD_INITIALIZE(SetUp)
	{
		testFano = new Shannon_Fano;
	}

	TEST_METHOD_CLEANUP(CleanUp)
	{
		delete testFano;
	}

	TEST_METHOD(Exception_Nothing_to_encode)
	{
		string input = "";
		try
		{
			testFano->encoding(input);
		}
		catch (invalid_argument message)
		{
			Assert::AreEqual("Nothing to encode", message.what());
		}
	}
	TEST_METHOD(input_one_symbol)
	{
		string input = "s";
		testFano->encoding(input);

		Assert::IsTrue(testFano->get_string_size() == 8 && testFano->get_encoded_size()==1);
	}
	TEST_METHOD(Exception_Wrong_code)
	{
		string input = "asdf";
		string code = "1";
		testFano->encoding(input);
		try
		{
			testFano->decoding(code);
		}
		catch (invalid_argument message)
		{
			Assert::AreEqual("Wrong code", message.what());
		}
	}
	TEST_METHOD(Exception_Wrong_code2)
	{
		string input = "asdf";
		string code = "111";
		testFano->encoding(input);
		try
		{
			testFano->decoding(code);
		}
		catch (invalid_argument message)
		{
			Assert::AreEqual("Wrong code", message.what());
		}
	}
	TEST_METHOD(Compression_test)
	{
		string input = "asdf";
		testFano->encoding(input);
		Assert::IsTrue(testFano->get_string_size() > testFano->get_encoded_size());
	}
	TEST_METHOD(string_size)
	{
		string input = "asdf";
		testFano->encoding(input);
		Assert::IsTrue(testFano->get_string_size() == 32);
	}
	TEST_METHOD(encoded_size)
	{
		string input = "asdf";
		testFano->encoding(input);
		Assert::IsTrue(testFano->get_encoded_size() == 8);
	}
};
