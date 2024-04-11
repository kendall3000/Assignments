Use the Adapter pattern to modify and create the necessary classes so the
VideoSocket class uses HDMIPlug's digitalDisplay() implementation instead of
VGAPlug's display() method when calling its VideoPlug's display() method.

Note that you cannot simply create and use an HDMIPlug in VideoSocket. You must
use an implementation of the VideoPlug interface. 

Follow any directions in the code comments.
