<h1>Testing a QWidget</h1>
QWidget class called PanelConcat which represents the central widget (content) of the following window:


The widget contains 2 input fields and 2 buttons. Pushing the button “CONCAT” merges the strings of the 2 input fields and prints the result to a label. Pushing the CANCEL button clears all the visible data. Nothing fancy or particularly complex, but this is just an example after all.

Testing GUI code normally requires a different approach to normal unit testing. That’s because usually testing public functions of a widget is not enough. To properly test a widget, it’s usually better if the tester class can access all its internal data and functions. The easiest way to achieve that is making the tester class friend of the tested class.

<b> Give acces </b>

When testing complex widget structures it could be necessary to provide full class access to more than one tester class. In that case a possible solution is to create a friend visitor class which is used by all the testers.

<h1>Structure</h1>

The full project structure includes 3 sub-projects:

    WidgetsLib – a dynamic library containing the widget class.
    ExampleApp – an example application using the PanelConcat widget.
    TestPanelConcat – the unit test of PanelConcat.

To try the example load the top subdirs project called GuiUnitTestingIntro in Qt Creator.

Keep in mind that by default running the project will launch the example application. To run the unit tests you can change the active run configuration, use the Tests panel or use the menu

Tools > Tests > Run All Tests
