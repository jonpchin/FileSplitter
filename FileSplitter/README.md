# FileSplitter<br>
![Alt text](notepadCantOpen.png?raw=true "NotePad cannot open")<br>

Use Case: If a file is too big to open in memory then split it into multiple smaller files!<br>

This program splits an input file into multiple output files<br>
To run the program ./filesplit inputFile numOfFiles outputFile<br>
numOfFiles is the number of files to split the input file and outputFile is the name of the outputfile without the extension.<br>
numOfFiles and outputFile are optional so you can just run ./filesplit inputFile<br>
If only inputFile parameter is passed in then the default will split into two files calling output0 and output1<br>
File extensions of the output will match the extension of the file input.<br>
Output files are created in the same directory the filesplit program is executed in.<br>

Example Usage:<br>
![Alt text](FileSplitExample.png?raw=true "filesplit example")<br>


FileSplit can be downloaded here: https://github.com/jonpchin/FileSplitter/releases/download/%40FirstRelease/filesplit.exe