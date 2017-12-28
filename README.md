# NandFlashTestGUI
### 1. Basic Introdution
+ This is a GUI application that use Qt to make the nand flash testing result visual.
+ Tools: Qt 5.9.0 + Visual Studio 2017 + MySQL 5.5.33 
+ Code Document: doxygen
### 2. Part Overview
+ Flash Type Selection Part  
  + Add
  + Delete
  + Search
  + Modify
+ Flash Viewer Checking Part
  + Zoom In/Out
  + Move
+ Flash Error Showing Part
### 3. History
   data   | version  |             content
:--------:|:--------:|----------------------------------
2017-12-11|0.1.0	 |construct the basic GUI
2017-12-12|0.2.0	 |basic zoomIn and zoomOut
2017-12-14|0.3.0	 |enable paint arbitrary flash
2017-12-18|0.4.0	 |use MySQL to manage the flash type
2017-12-19|0.4.1	 |fixed some bugs and optimizate code
2017-12-20|0.5.0	 |enable move flash viewer and fixed bugs
2017-12-23|0.6.0	 |add viewer reset func & prev/next viewer func
2017-12-25|0.6.1	 |change to doxygen comment style
2017-12-28|0.7.0	 |read test error file to show in the flash viewer
