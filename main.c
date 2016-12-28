// Jonathan Chin
// 12/27/2016
// FileSplitter
// This program splits an input file into multiple output files
// To run the program ./filesplit <inputFile> <numOfFiles> <outputFile>
// numOfFiles and outputFile are optional so you can just run ./filesplit <inputFile>
// output files are created in the same directory the filesplit program is executed in

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCHARPERLINE 2000000 //maximum number of characters per line
#define MAXOUTPUTSIZE 200 //who names their files more then 200 characters?

// used to get file extension, returns .txt when test.txt is passed in
const char *get_filename_ext(const char *filename);

int main(int argc, char *argv[]){

    // there needs to be at least one or more arguments passed in
	if(argc >= 2){
		FILE *fin = fopen(argv[1], "r");

		if(fin){
            char line[MAXCHARPERLINE];
            int lines = 0;

            // loops until reaches the end of the file
            while(fgets(line, sizeof(line), fin)){
                lines++;
            }

            printf("Number of lines in %s is %d\n", argv[1], lines);

            // sets the file pointer back to the start of the file
            rewind(fin);
            //the number of files to split the input file into too
            int split = 2;
            if(argc >= 3){
                split = strtoul(argv[2], NULL, 10);
            }

            if(split > lines){
                split = lines;
                printf("You can't split more then the number of lines in input file.");
            }


            int i;
            int separate = lines/split;
            char defaultOutputFile[] = "output";

            for(i=0; i<split; ++i){

                char fileOutput[MAXOUTPUTSIZE] = "";
                if(argc >= 4){
                    strcat(fileOutput, argv[3]);
                }else{
                    strcat(fileOutput, defaultOutputFile);
                }

                char numString[20];
                sprintf(numString, "%d", i);
                // This ensures when files are split they have different names
                strcat(fileOutput, numString);
                // finally concat the file extension
                strcat(fileOutput, get_filename_ext(argv[1]));
                FILE *fout = fopen(fileOutput, "w");
                int j;

                // add the extra left over lines to the last file if
                // since its possible the file wasn't split evenly
                if(i+1 >= split){
                    separate+=(lines%split);
                }
                for(j=0; j<separate; ++j){
                    fgets(line, sizeof(line), fin);
                    fprintf(fout, "%s", line);
                }

                // need to clear the file output array before
                // concating the next file name
                memset(fileOutput, 0, MAXOUTPUTSIZE);
                fclose(fout);
            }
            printf("File %s have been separated into %d file(s).", argv[1], split);
            fclose(fin);

		}else{
            printf("File not found.");
		}
	}else{
		printf("No arguement supplied");
	}
	return 0;
}

const char *get_filename_ext(const char *filename) {
    const char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) {
        return "";
    }
    return dot;
}
