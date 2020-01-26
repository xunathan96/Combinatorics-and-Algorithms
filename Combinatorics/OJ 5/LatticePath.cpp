#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define M 1000000007

vector< vector<int> > lattice_coordinates(1001, vector<int>(1001, -1));
int x1, y1, x2, y2;

int calculate_lattice_paths(int i, int j, int dir_x, int dir_y){
    //EDGE CASES
    if(i<0 || i>1000 || j<0 || j>1000){
        return 0;
    }
    if( (i > x1 && i > x2) || (i < x1 && i < x2) || (j < y1 && j < y2) || (j > y1 && j > y2) ){
        return 0;
    }

    //BASE CASE
    if(lattice_coordinates[i][j] != -1){
        return lattice_coordinates[i][j];
    }
    //RECURSIVE CASE
    else{
        lattice_coordinates[i][j] = (calculate_lattice_paths(i - dir_x, j, dir_x, dir_y) + calculate_lattice_paths(i, j - dir_y, dir_x, dir_y)) % M;
        return lattice_coordinates[i][j];
    }
}


int num_lattice_paths(){
    //SET NUMBER OF LATTICE PATHS AT y=x TO BE 0
    for(int i=0; i<1001; i++){
        lattice_coordinates[i][i] = 0;
    }

    //SET NUMBER OF LATTICE PATHS AT END/START POINT TO BE -1/1
    lattice_coordinates[x2][y2] = -1;
    lattice_coordinates[x1][y1] = 1;

    //SET DIRECTION BASIS FOR SHORTEST PATH
    int dir_x = (x1 < x2) ? 1 : -1;
    int dir_y = (y1 < y2) ? 1 : -1;

    return calculate_lattice_paths(x2, y2, dir_x, dir_y);
}


int main(){
    cin >> x1 >> y1 >> x2 >> y2;

    //TRANSFORM POINTS TO 1ST QUADRANT
    x1 = x1+500;
    x2 = x2+500;
    y1 = y1+500;
    y2 = y2+500;

    cout << num_lattice_paths() << endl;

    return 0;
}
