<h1>Data driven testing </h1>
An advanced feature of Qt Test is data driven testing. 

The idea is to separate tests and data to avoid to have a long list of similar QVERIFY or QCOMPARE macros and to replicate all the code needed to initialise a test.



<h1>QT CREATOR </h1>
The best way to run and manage them is creating a “parent” project. The right choice in this case is the  “Subdirs Project” template, which is listed in the “Other Project” group of the “New Project” dialog.

Qt Creator offers an excellent integration with Qt Test.

One of the panels in the left sidebar is called “Tests” and it shows all the unit test found in your container project.


Qt Creator tests panel

Using this panel you can disable some tests, run them all or run only a specific one. When doing data driven testing, you can also select which data sets are enabled. All this is extremely useful in a real project where you can have hundreds or even thousands of unit tests and you need to check/debug only one/few.

When running the unit test from the Tests panel the results are shown in the Test Results panel that you can also open with ALT-8.
