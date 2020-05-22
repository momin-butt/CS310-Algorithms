#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <stack>
#include <vector>
#include <stdlib.h>
#include <stack>
#include <string>
#include <queue>
#include <sstream>
#include <set>
#include <bits/stdc++.h> 
using namespace std;

/* 

Recurrence Relation: 4T(n/2) + c
Time Complexity: O(n^2)

*/

int counter = 0;

string ans = "";
  
// string boomerang(){
// 	string ans = "";
//     ans = ans + to_string(1) + " ("+to_string(0)+","+to_string(1)+")" + " ("+to_string(1)+","+to_string(1)+") " + " ("+to_string(0)+","+to_string(0)+") " + "\n"; //trailing spaces and endlines dont matter
//     ans = ans + to_string(2)+" ("+to_string(0)+","+to_string(2)+")" + " ("+to_string(1)+","+to_string(3)+")  " + " ("+to_string(0)+","+to_string(3)+")" + "\n";
//     ans = ans + to_string(3)+" ("+to_string(2)+","+to_string(1)+") " + " ("+to_string(2)+","+to_string(2)+")" + " ("+to_string(1)+","+to_string(2)+")" + "\n";
//     ans = ans + to_string(4)+" ("+to_string(3)+","+to_string(1)+")" + " ("+to_string(2)+","+to_string(0)+")" + " ("+to_string(3)+","+to_string(0)+")" + "\n";
//     ans = ans + to_string(5)+" ("+to_string(2)+","+to_string(3)+")" + " ("+to_string(3)+","+to_string(2)+")" + " ("+to_string(3)+","+to_string(3)+")  " + "\n\n\n";
//     return ans;
// }

void addShape(int** board, pair<int, int> b1, pair<int, int> b2, pair<int, int> b3)
{

    board[b1.first][b1.second] = counter;
    board[b2.first][b2.second] = counter;
    board[b3.first][b3.second] = counter;
}

void makeBoard(int** board, int boardsize, int row_str, int col_str, int hole_r, int hole_c)
{

    if(boardsize == 2)
    {
        counter++;
        ans = ans + to_string(counter);
        for(int i = row_str; i < boardsize+row_str; i++)
        {
            for(int j = col_str; j < boardsize+col_str; j++)
            {
                if(board[i][j] == 0)
                {
                    
                    board[i][j] = counter;
                    ans = ans + "(" + to_string(i) + "," + to_string(j) + ")";

                }
                
            }

           
        }

             ans = ans + "\n";


        return;
    }

    else
    {
        counter++;
        int mid_r = (row_str+(boardsize/2));
        int mid_c = (col_str+(boardsize/2));

        pair<int, int> first_blck, second_blck, third_blck, fourth_blck;

        first_blck.first = mid_r - 1;
        first_blck.second = mid_c - 1;

        second_blck.first = mid_r - 1;
        second_blck.second = mid_c;

        third_blck.first = mid_r;
        third_blck.second = mid_c - 1;

        fourth_blck.first = mid_r;
        fourth_blck.second = mid_c;

        int newSize = boardsize/2;

        if(hole_r < mid_r && hole_c < mid_c) //hole in first block
        {
                // counter++;

                ans = ans + to_string(counter) + "(" + to_string(second_blck.first) + "," + to_string(second_blck.second) + ")";
                ans = ans + "(" + to_string(third_blck.first) + "," + to_string(third_blck.second) + ")";
                ans = ans + "(" + to_string(fourth_blck.first) + "," + to_string(fourth_blck.second) + ")\n";

                addShape(board, third_blck, second_blck, fourth_blck);
                makeBoard(board,newSize,row_str,col_str,hole_r,hole_c);
                makeBoard(board, newSize, mid_r, mid_c, fourth_blck.first, fourth_blck.second );
                makeBoard(board, newSize, mid_r, col_str, third_blck.first, third_blck.second );
                makeBoard(board, newSize, row_str, mid_c, second_blck.first, second_blck.second );

        }

        else if(hole_r >= mid_r && hole_c < mid_c) //hole in third block
        {
                // counter++;

                ans = ans + to_string(counter) + "(" + to_string(first_blck.first) + "," + to_string(first_blck.second) + ")";
                ans = ans + "(" + to_string(second_blck.first) + "," + to_string(second_blck.second) + ")";
                ans = ans + "(" + to_string(fourth_blck.first) + "," + to_string(fourth_blck.second) + ")\n";

                addShape(board, first_blck, second_blck, fourth_blck);
                makeBoard(board,newSize,mid_r,col_str,hole_r,hole_c);
                makeBoard(board, newSize, row_str, mid_c, second_blck.first, second_blck.second );
                makeBoard(board, newSize, row_str, col_str, first_blck.first, first_blck.second );
                makeBoard(board, newSize, mid_r, mid_c, fourth_blck.first, fourth_blck.second );

        }

        else if(hole_r < mid_r && hole_c >= mid_c) //hole in second block
        {
                // counter++;
                ans = ans + to_string(counter) + "(" + to_string(first_blck.first) + "," + to_string(first_blck.second) + ")";
                ans = ans + "(" + to_string(third_blck.first) + "," + to_string(third_blck.second) + ")";
                ans = ans + "(" + to_string(fourth_blck.first) + "," + to_string(fourth_blck.second) + ")\n";

                addShape(board,first_blck, third_blck, fourth_blck);
                makeBoard(board,newSize,row_str,mid_c,hole_r,hole_c);
                makeBoard(board, newSize, row_str, col_str, first_blck.first, first_blck.second );
                makeBoard(board, newSize, mid_r, mid_c, fourth_blck.first, fourth_blck.second );
                makeBoard(board, newSize, mid_r, col_str, third_blck.first, third_blck.second );
        }

        else if(hole_r >= mid_r && hole_c >= mid_c) //hole in fourth block
        {
                // counter++;
                ans = ans + to_string(counter) + "(" + to_string(first_blck.first) + "," + to_string(first_blck.second) + ")";
                ans = ans + "(" + to_string(second_blck.first) + "," + to_string(second_blck.second) + ")";
                ans = ans + "(" + to_string(third_blck.first) + "," + to_string(third_blck.second) + ")\n";

                addShape(board, first_blck, second_blck, third_blck);
                makeBoard(board,newSize,mid_r,mid_c,hole_r,hole_c);
                makeBoard(board, newSize, row_str, col_str, first_blck.first, first_blck.second);
                makeBoard(board, newSize, row_str, mid_c, second_blck.first, second_blck.second );
                makeBoard(board, newSize, mid_r, col_str, third_blck.first, third_blck.second );

            
        }

            return;

    }

}

void printBoard(int** board, int boardsize, int row_str, int col_str)
{
    for(int i = 0; i < boardsize; i++)
    {
        for(int j = 0; j < boardsize; j++)
        {
            cout << board[i][j] << "\t";
        }

        cout << endl;
    }
}



int main(int argc, char** argv) 
{ 
	// string ans = boomerang();
    //    cout<<ans;

    char* filename = argv[1];

    string line;
    int size = 0;
    int given_r, given_c = 0;

    ifstream myFile;
    myFile.open(filename);

    if(!myFile)
    {
        cout << "Error! Unable to open the file. \n";
        return 0;
    }

    getline(myFile,line);

    stringstream s0(line);

    string temp0;
    s0 >> temp0;
    s0 >> size;

    int** board = new int*[size];
    for(int i = 0; i < size; i++)
    {
        board[i] = new int[size];
        for(int j = 0; j < size; j++)
        {
            board[i][j] = 0;
            // cout << board[i][j] << " ";
        }
    }

    getline(myFile,line);

    int len = line.length();

    for(int i = 0; i < len; i++)
    {
        if(line[i] == ',')
        {
            given_r = stoi(line.substr(1,i-1));
            given_c = stoi(line.substr(i+1,len-1));
        }
    }

    board[given_r][given_c] = -1;

    makeBoard(board,size,0,0,given_r,given_c);

    // printBoard(board,size,0,0);

    cout<<ans;

    return 0; 
} 
