/*
 * Usage of CDK Matrix
 *
 * File:   example1.cc
 * Author: Stephen Perkins
 * Email:  stephen.perkins@utdallas.edu
 */

#include <iostream>
#include "cdk.h"
#include "Project6.h"
#include <fstream>
#include <stdint.h>
#include <string>
#include <sstream>
#include <iomanip>

#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 20
#define MATRIX_NAME_STRING "Test Matrix"

using namespace std;


int main()
{

  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  const char *rowTitles[MATRIX_HEIGHT+1] = {"R0", "R1", "R2", "R3", "R4", "R5"};
  const char *columnTitles[MATRIX_WIDTH+1] = {"C0", "C1", "C2", "C3"};
  int boxWidths[MATRIX_WIDTH+1] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int boxTypes[MATRIX_WIDTH+1] = {vMIXED, vMIXED, vMIXED, vMIXED};
  stringstream ss_magic, ss_version, ss_records;
  string Magic, Version, NumRecords;

  BinaryFileHeader *myRecord = new BinaryFileHeader();
  ifstream binInfile("cs3377.bin", ios::in | ios::binary);
  binInfile.read((char*)myRecord, sizeof(BinaryFileHeader));

  ss_magic << hex << uppercase << myRecord->magicNumber;
  ss_magic >> Magic;
  ss_version << myRecord->versionNumber;
  ss_version >> Version;
  ss_records <<  myRecord->numRecords;
  ss_records >> NumRecords;
  
  Magic = "Magic: 0x" + Magic;
  Version = "Version: " + Version;
  NumRecords = "NumRecords: " + NumRecords;
  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
  */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT,MATRIX_WIDTH,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);

  /*
   * Dipslay a message
   */
  setCDKMatrixCell(myMatrix, 1, 1, Magic.c_str());
  setCDKMatrixCell(myMatrix, 1, 2, Version.c_str());
  setCDKMatrixCell(myMatrix, 1, 3, NumRecords.c_str());
  drawCDKMatrix(myMatrix, true);    /* required  */

  /* so we can see results */
  unsigned char x;
  cin >> x;


  // Cleanup screen
  endCDK();
}
