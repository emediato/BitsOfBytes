<h1>Testing a QWidget</h1>
QWidget class called PanelConcat which represents the central widget (content) of the following window:


The widget contains 2 input fields and 2 buttons. Pushing the button “CONCAT” merges the strings of the 2 input fields and prints the result to a label. Pushing the CANCEL button clears all the visible data. Nothing fancy or particularly complex, but this is just an example after all.

Testing GUI code normally requires a different approach to normal unit testing. That’s because usually testing public functions of a widget is not enough. To properly test a widget, it’s usually better if the tester class can access all its internal data and functions. The easiest way to achieve that is making the tester class friend of the tested class.



