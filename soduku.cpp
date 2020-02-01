#include <iostream>
#include <cmath>
#include <vector>


using namespace std;

#define DEBUG false

vector <vector <vector <int> >> solutions;


void printGrid(vector <vector <int>> grid)  
{  
    int G_SIZE = grid.size();
    for (int row = 0; row < G_SIZE; row++)  
    {  
    for (int col = 0; col < G_SIZE; col++)  
            cout << grid[row][col] << " "; 
        cout << endl; 
    }  
    cout<<endl;
}

void printDebugGrid(vector <vector <int>> grid)  
{  
    int G_SIZE = grid.size();
    clog<<"\t";
    for (int row = 0; row < G_SIZE; row++)  
    {  
    for (int col = 0; col < G_SIZE; col++)  
            clog << grid[row][col] << " "; 
        clog << endl<<"\t"; 
    }  
    clog<<endl;
}

bool isPreviousSolution(vector<vector <int>> grid, int row, int col, int val){
    int G_SIZE = grid.size();
    int last = solutions.size() - 1;
    if(last < 0){
        return false;
    }
    int modX = 0, modY = 0;
    bool f = false;
    for(int i = 0; i < G_SIZE; i++){
        for(int j = 0; j < G_SIZE; j++){
            if(grid[i][j] != solutions[last][i][j]){
                modX = i;
                modY = j;
                f = true;
                break;
            }
            if(f){
                break;
            }
        }
    }

    if(val <= solutions[last][row][col] && row < modX && col < modY){
        return true;
    }
    return false;
}

bool isValidChoice(int row, int col, vector <vector <int>> grid, int val){
    int G_SIZE = grid.size();
    if(DEBUG){
        clog<<"\n\tBegin isValidChoice() input row:"<<row<<" col:"<<col<<" val: "<<val<<endl<<endl;
        printDebugGrid(grid);
    }

    int subGridX = 0, subGridY = 0;

    int subGridSize = sqrt(G_SIZE);

    for(int i = 0; i < subGridSize; i++){
        if(row >= i * subGridSize &&  row < (i+1) * subGridSize){
            subGridX = i;
        }
    }
    for(int i = 0; i < subGridSize; i++){
        if(col >= i * subGridSize &&  col < (i+1) * subGridSize){
            subGridY = i;
        }
    }
    if(DEBUG)
        clog<<"\n\tSubGrid x: "<<subGridX<<" y: "<<subGridY<<" gridSize: "<<subGridSize<<endl;

    for(int i = 0;i < G_SIZE; i++){
        if(grid[row][i] == val){
            if(DEBUG)
                clog<<"\n\tEnd of isValidChoice()\n\tColumn Verification failed\n";
            return false;
        }
    }

    for(int i = 0;i < G_SIZE; i++){
        if(grid[i][col] == val){
            if(DEBUG)
                clog<<"\n\tEnd of isValidChoice()\n\tRow Verification failed\n";
            return false;
        }
    }

    for(int i = subGridX * subGridSize; i < (subGridX + 1) * subGridSize; i++){
        for(int j = subGridY * subGridSize; j < (subGridY + 1) * subGridSize; j++){
            if(grid[i][j] == val){
                if(DEBUG)
                    clog<<"\n\tEnd of isValidChoice()\n\tSub-Grid Verification failed\n";
                return 0;
            }
        }
    }

    if(isPreviousSolution(grid,row,col,val)){
        if(DEBUG)
                    clog<<"\n\tEnd of isValidChoice()\n\tIs Previous Solution: Verification failed\n";
        return false;
    }

    if(DEBUG)
        clog<<"\n\tEnd of isValidChoice\n\tAll Verifications Passed\n";
    return 1;

}


bool hasEmptySpace(int &row, int &col, vector <vector <int>> grid){
    int G_SIZE = grid.size();
    for(int i = 0; i < G_SIZE; i++){
        for(int j = 0; j < G_SIZE; j++){
            if(grid[i][j] == 0){
                row = i;
                col = j;
                return true;
            }
        }
    }
    return false;
}

int level = 0;

bool solveSoduku(vector<vector <int>> &grid, int row = 0, int col = 0){
    //Passed row and col as parameter for maintaining stack info and is used in clearing last cell when the solution is found
    
    int G_SIZE = grid.size();
    
    level++;
    
    if(!hasEmptySpace(row,col,grid)){
        if(DEBUG){
            clog<<"\nSolved at Level"<<level<<endl;
            printDebugGrid(grid);
        }
        solutions.push_back(grid);
        grid[row][col] = 0;
        cout<<"\rCount Till Now :"<<solutions.size();
        return false;
    }

    for(int i = 1; i <= G_SIZE; i++){
        if(isValidChoice(row,col,grid,i)){
            grid[row][col] = i;
            if (solveSoduku(grid,row,col)){
                
                level--;
                
                if(DEBUG)
                    clog<<"\nLevel Up: "<<level<<endl;
                
                return true;
            }
            grid[row][col] = 0;
        }
    }
    
    if(DEBUG)
        clog<<"\nRecurse Back Level: "<<level<<endl;
    
    level--;
    return false;

}



int main(){

    int s = 0;
    cout<<"Enter Grid Size :";
    cin>>s;
    
    vector <vector <int>> grid;

    float sq = sqrt(s);
    if(sq == ceil(sq)){
        for(int i = 0; i < s; i++){
            vector <int> temp;
            int x;
            for(int j = 0; j < s; j++){
                cin>>x;
                temp.push_back(x);
            }
            grid.push_back(temp);
        }
    }
    else{
        cout<<"\nInvalid Grid! Using default input!\n";
        grid =       {{1, 0, 4, 0, 3, 0, 0, 0, 8},  
                      {2, 0, 0, 0, 1, 0, 0, 0, 7},  
                      {3, 0, 0, 0, 2, 0, 5, 1, 0},  
                      {4, 0, 0, 0, 9, 0, 0, 0, 5},  
                      {5, 1, 2, 3, 4, 6, 7, 8, 9},  
                      {6, 0, 0, 0, 8, 0, 0, 0, 4},  
                      {7, 0, 0, 0, 5, 0, 0, 6, 3},  
                      {8, 0, 0, 1, 6, 0, 4, 0, 2},  
                      {9, 0, 0, 0, 7, 0, 8, 0, 1}};
    }


    solveSoduku(grid);
    if (solutions.size() > 0){
        cout<<endl<<endl<<"Solutions: "<<endl<<endl;
        for(int i = 0; i < solutions.size(); i++){
            printGrid(solutions[i]);
        }
    }
    cout << "\nNo more solutions exist. Total Found : "<<solutions.size()<<endl;  
  
    return 0;                        
}


