#include <string>
#include <CppUnitTest.h>

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1 {
  TEST_CLASS(HelloWorldTest) {
    TEST_METHOD(CreateStringFromLiteral) {
      string s = "Hello, World!";
      Assert::AreEqual("Hello, World!", s.c_str());
    }

    TEST_METHOD(CreateStringFromChars) {
      string s = { 'H', 'e', 'l', 'l', 'o', ',', ' ', 'W', 'o', 'r', 'l', 'd', '!' };
      Assert::AreEqual("Hello, World!", s.c_str());
    }
  };
}
