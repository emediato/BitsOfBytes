# QT DOCUMENTATION
https://doc.qt.io/qt-5/qtest.html

# BEST PRACTICES

# Explicitly Ignore Expected Warnings
If a test is expected to cause Qt to output a warning or debug message on the console, it should call QTest::ignoreMessage() to filter that message out of the test output and to fail the test if the message is not output.

If such a message is only output when Qt is built in debug mode, use QLibraryInfo::isDebugBuild() to determine whether the Qt libraries were built in debug mode. Using #ifdef QT_DEBUG is not enough, as it will only tell you whether the test was built in debug mode, and that does not guarantee that the Qt libraries were also built in debug mode.
# Avoid Printing Debug Messages from Autotests
# Write Well-structured Diagnostic Code
# Compile All Classes into Libraries

In small to medium sized projects, a build script typically lists all source files and then compiles the executable in one go. This means that the build scripts for the tests must list the needed source files again.

It is easier to list the source files and the headers only once in a script to build a static library. Then the main() function will be linked against the static library to build the executable and the tests will be linked against the static libraries.

# Avoid Bitmap Capture and Comparison
# Beware of Timing-dependent Behavior
# Avoid Side-effects in Verification Steps

When performing verification steps in an autotest using QCOMPARE(), QVERIFY(), and so on, side-effects should be avoided. Side-effects in verification steps can make a test difficult to understand. Also, they can easily break a test in ways that are difficult to diagnose when the test is changed to use QTRY_VERIFY(), QTRY_COMPARE() or QBENCHMARK(). These can execute the passed expression multiple times, thus repeating any side-effects.

When side-effects are unavoidable, ensure that the prior state is restored at the end of the test function, even if the test fails. This commonly requires use of an RAII (resource acquisition is initialization) class that restores state when the function returns, or a cleanup() method. Do not simply put the restoration code at the end of the test. If part of the test fails, such code will be skipped and the prior state will not be restored.

# Avoid Fixed Timeouts

Avoid using hard-coded timeouts, such as QTest::qWait() to wait for some conditions to become true. Consider using the QSignalSpy class, the QTRY_VERIFY() or QTRY_COMPARE() macros, or the QSignalSpy class in conjunction with the QTRY_ macro variants.

The qWait() function can be used to set a delay for a fixed period between performing some action and waiting for some asynchronous behavior triggered by that action to be completed. For example, changing the state of a widget and then waiting for the widget to be repainted. However, such timeouts often cause failures when a test written on a workstation is executed on a device, where the expected behavior might take longer to complete. Increasing the fixed timeout to a value several times larger than needed on the slowest test platform is not a good solution, because it slows down the test run on all platforms, particularly for table-driven tests.

If the code under test issues Qt signals on completion of the asynchronous behavior, a better approach is to use the QSignalSpy class to notify the test function that the verification step can now be performed.

If there are no Qt signals, use the QTRY_COMPARE() and QTRY_VERIFY() macros, which periodically test a specified condition until it becomes true or some maximum timeout is reached. These macros prevent the test from taking longer than necessary, while avoiding breakages when tests are written on workstations and later executed on embedded platforms.

If there are no Qt signals, and you are writing the test as part of developing a new API, consider whether the API could benefit from the addition of a signal that reports the completion of the asynchronous behavior.

# BITSOFBYTES
# BitsOfBytes
In this repository you can find source code and projects from my [blog](http://blog.davidecoppola.com/) posts.

All the content here is released under The Unlicense license unless stated otherwise in a sub-directory.

## Examples

### How to create a plugin for Qt Creator
[blog post](http://blog.davidecoppola.com/2019/12/how-to-create-a-qt-creator-plugin/) - [source code](https://github.com/vivaladav/BitsOfBytes/tree/master/how-to-create-a-plugin-for-qt-creator)

### GUI unit testing with Qt Test – part 2 – advanced testing
[blog post](http://blog.davidecoppola.com/2018/01/gui-unit-testing-with-qt-test-advanced/) - [source code](https://github.com/vivaladav/BitsOfBytes/tree/master/gui-unit-testing-with-qt-test-advanced/GuiUnitTestingAdv)

### GUI unit testing with Qt Test – part 1 – introduction
[blog post](http://blog.davidecoppola.com/2018/01/gui-unit-testing-with-qt-test-introduction/) - [source code](https://github.com/vivaladav/BitsOfBytes/tree/master/gui-unit-testing-with-qt-test-introduction/GuiUnitTestingIntro)

### C++ unit testing with Qt Test – part 2 – advanced testing
[blog post](http://blog.davidecoppola.com/2017/11/cpp-unit-testing-with-qt-test-advanced) - [source code](https://github.com/vivaladav/BitsOfBytes/tree/master/cpp-unit-testing-with-qt-test-advanced/UnitTests)

### C++ unit testing with Qt Test - part 1 - introduction
[blog post](http://blog.davidecoppola.com/2017/11/cpp-unit-testing-with-qt-test-introduction/) - [source code](https://github.com/vivaladav/BitsOfBytes/tree/master/cpp-unit-testing-with-qt-test-introduction/QtTestIntroduction)

### A C++ program to get CPU usage from command line in Linux
[blog post](http://blog.davidecoppola.com/2016/12/cpp-program-to-get-cpu-usage-from-command-line-in-linux/) - [source code](https://github.com/vivaladav/BitsOfBytes/tree/master/cpp-program-to-get-cpu-usage-from-command-line-in-linux)

### Qt Network and JSON example: a simple Hacker News reader
[blog post](http://blog.davidecoppola.com/2016/11/qt-network-and-json-example-simple-hacker-news-reader/) - [source code](https://github.com/vivaladav/BitsOfBytes/tree/master/qt-network-and-json-example-simple-hacker-news-reader)

### How to embed a database in your application with SQLite and Qt
[blog post](http://blog.davidecoppola.com/2016/11/howto-embed-database-in-application-with-sqlite-and-qt/) - [source code](https://github.com/vivaladav/BitsOfBytes/tree/master/howto-embed-database-in-application-with-sqlite-and-qt/)

### How to create an application with Qt and C++
[blog post](http://blog.davidecoppola.com/2016/10/how-to-create-an-application-with-qt-and-cpp/) - [source code](https://github.com/vivaladav/BitsOfBytes/tree/master/how-to-create-an-application-with-qt-and-cpp/)

### How to traverse a git repository using libgit2 and C++
[blog post](http://blog.davidecoppola.com/2016/10/how-to-traverse-git-repository-using-libgit2-and-cpp/) - [source code](https://github.com/vivaladav/BitsOfBytes/tree/master/how-to-traverse-git-repository-using-libgit2-and-cpp/)
