#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helper_functions.h"
// #include <bits/stdc++.h>
// using namespace std;

//Colours
void red () {
  printf("\033[1;31m");
}
void blue(){
	printf("\033[0;34m");
}
void yellow() {
  printf("\033[1;33m");
}
void green(){
	printf("\033[0;32m");
}
void reset () {
  printf("\033[0m");
}

void makezero(int g[]){
  for(int i=0; i<16; i++){
    if(g[i]<0)
      g[i]=0;
  }
}

//To print the grid as it is
void printGrid (int g[]){
    cout << endl;
    printf("---------------------\n");
    for(int i=0; i<4; i++){
      for(int j=0; j<4; j++){
        if(g[(4*i)+j] != 0){
          printf("|%4d", g[(4*i)+j]);
        }
        else{
          printf("|    ");
        }

      }
      printf("|\n");
      printf("---------------------\n");
    }
}


void printVars (map <char*, pair<int,int>> &m){
  yellow();
  for(int i=0; i<4; i++){
    for(int j=0; j<4; j++){
      for(auto itr: m){
        if(itr.second.first == i+1 && itr.second.second == j+1){
          cout << "2048> "<< itr.first << " -> (" << i+1 << "," << j+1 << ")\n";
        }
      }
    }
  }
  reset();
  cout << "----> ";
}

int printError (int g[], map <char*, pair<int,int>> &m){
  //Print tile values
  for (int i=0; i<4; i++){
    for (int j=0; j<4; j++){
      if(i==3 && j==3){
        std::cerr << g[(4*i)+j];
      }
      else
        std::cerr << g[(4*i)+j] << "\40";
    }
  }
  //return if map empty
  if(m.empty()){
    // std::cerr << "Map Empty" << '\n';
    return -1;
  }
  for (int i=0; i<4; i++){
    for (int j=0; j<4; j++){
      int c = 0;
      //count num of elements for this i,j
      for(auto itr : m) {
        if(itr.second.first==i+1 && itr.second.second==j+1){
          c++;
        }
      }

      if(c>0){
        std::cerr << "\40" << i+1 <<","<< j+1;
        for(auto itr: m){
          if(itr.second.first==i+1 && itr.second.second==j+1){
            if(c==1){
              std::cerr << itr.first;
            }
            else{
              std::cerr << itr.first<<",";
              c--;
            }
          }
        }
      }
    }
  }
  cout << "\n";
  return 0;
}

void check_map(int g[], map <char*, pair<int,int>> &m){
  int s = m.size();
  vector <char*> v;
  yellow();
  cout << "2048> Number of variables in memory: " << s << endl;
  reset();
  for (auto itr : m){
    cout << itr.first << "\n";
    if(g[(4*(itr.second.first-1)) + (itr.second.second-1)]==0){
      yellow();
      cout << "2048> Tile " << itr.first << " being freed.\n";
      reset();
      // m.erase((itr.first));
      v.push_back(itr.first);
      // cout << "2048> Successfully added to vector.\n";
    }
    s--;
    if(s==0){
      break;
    }
  }
  for(int i=0; i<v.size(); i++){
    m.erase(v[i]);
    yellow();
    cout << "2048> Successfully deleted " << v[i] << endl;
    reset();
  }
  yellow();
  cout << "2048> Map check complete\n";
  reset();
}

void insertRandom (int g[]){
    while(1){
        int nn = rand() % 16;
        int luck = rand() % 100;
        if(g[nn]==0){
            if(luck<80)
                g[nn] = 2;
            else
                g[nn] = 4;
            break;
        }
    }
}

void return_value (int g[], int x, int y){
  // printf("In the return_value function\n");
  if(g[(4*(x-1))+y-1]!=0){
    yellow();
    printf("2048> Value in %d, %d is %d\n", x, y, g[(4*(x-1))+y-1]);
    reset();
  }
  else{
    red();
    printf("There is no value in cell %d, %d as of now!\n", x, y);
    reset();
    std::cerr << "-1" << '\n';
  }
}

void assign_val (int g[], map<char*, pair <int, int>> &m, int val, int x, int y){
  // printf("In the assign function\n");
  if(x>4 || x<0 || y>4 || y<0){
    std::cerr << "-1" << '\n';
    red();
    printf("2048> Array index out of bounds. Indices can be in range {1, 2, 3, 4}\n");
    reset();
    printf("---->");
  }
  else if (val<0){
    std::cerr << "-1" << '\n';
    red();
    printf("2048> Value assigned can not be negative!\n");
    reset();
    printf("---->");
  }
  // cout<< i << " " << j << endl;
  else{
    g[4*(x-1)+y-1] = val;
    yellow();
    printf("2048> Value assigned to %d, %d is %d\n", x, y, val);
    reset();
    check_map(g, m);
    yellow();
    printf("2048> New Grid is as follows:\n");
    reset();
    printError(g, m);
    printGrid(g);
    printVars(m);
  }
}

void assign_var (int g[], map<char*, pair <int, int>> &m, char* id, int x, int y){
  // cout<<"In the function assign_var\n";
  if(g[(4*(x-1) + y-1)] == 0){
    std::cerr << "-1" << '\n';
    red();
    printf("2048> Can't assign variable to empty tile!\n");
    reset();
    printf("---->");
  }
  else if(x>4 || x<0 || y>4 || y<0){
    std::cerr << "-1" << '\n';
    red();
    printf("2048> Array index out of bounds. Indices can be in range {1, 2, 3, 4}\n");
    reset();
    printf("---->");
  }
  else{
    for(auto itr: m){
      if(strcmp(itr.first, id)==0){
        yellow();
        cout<<"2048> Assignment for " << id << " already exists. Deleting the older assignment\n";
        reset();
        m.erase(itr.first);
        break;
      }
    }
    m[id] = make_pair(x, y);   //working too
    // m.insert(make_pair(id, make_pair(x, y)));  //working
    yellow();
    printf("2048> String %s is in %d, %d\n", id, x, y);
    reset();
    printError(g, m);
    printGrid(g);
    printVars(m);
  }
}

//To find sum of all cells
int sumCells(int g[]){
    int sum = 0;
    for(int i=0; i<16; i++){
        sum = sum+g[i];
    }
    return sum;
}

//To initialize random cells as starting cells
void start(int g[]) {
  yellow();
  cout << "\n2048> Welcome to the game!\n";
  cout << "2048> Here is your starting Grid!\n\n";
  reset();
  srand(time(0));
  int pos1 = rand() % 16;
  int pos2 = rand() % 16;
  while(pos1==pos2){
    pos2 = rand() % 16;
  }
  g[pos1] = 2;
  g[pos2] = 2;
  printGrid(g);
  cout << "\n----> ";
}

//DONT TOUCH BELOW THIS
int shift_up_all(int g[], map <char*, pair<int,int>> &m){
    int ret_val = 0;
    while(1){
      int moves = 0;
      for(int i=0; i<3; i++){
        for(int j=0; j<4; j++){
          if(g[4*i+j]!=0){
            continue;
          }
          else{
            if(g[4*i+j+4]!=0){
              g[4*i+j] = g[4*i+j+4];
              g[4*i+j+4] = 0;
              moves++;
              ret_val++;
              int s = m.size();
              for(auto itr: m){
                if(itr.second.first==i+2 && itr.second.second==j+1){
                  // printf("Shifted var in %d, %d 1 up\n", i+2, j+1);
                  m[itr.first] = make_pair(i+1, j+1);
                  s--;
                  if(s==0){
                    break;
                  }
                }
              }
            }
          }
        }
      }
      if(moves==0)
          break;
    }
    return ret_val;
}

int move_up(int g[], map <char*, pair<int,int>> &m, int op){
    int ret_val = 0;
    ret_val += shift_up_all(g, m);
    int modified[16] = {0};
    for(int i=0; i<3; i++){
        for(int j=0; j<4; j++){
            if(modified[(4*i)+j]==0 && modified[(4*i)+j+4]==0){
                if(g[(4*i)+j]==g[(4*i)+j+4] && g[(4*i)+j]!=0){
                    modified[(4*i)+j]++;
                    modified[(4*i)+j+4]++;
                    if(op==1)
                      g[(4*i)+j] = 2*g[(4*i)+j];
                    else if (op==2)
                      g[(4*i)+j] = 0;
                    else if (op==3)
                      g[(4*i)+j] = g[(4*i)+j]*g[(4*i)+j];
                    else if (op==4)
                      g[(4*i)+j] = 1;
                    g[(4*i)+j+4] = 0;
                    int s = m.size();
                    for(auto itr: m){
                      if(itr.second.first==i+2 && itr.second.second==j+1){
                        m[itr.first] = make_pair(i+1, j+1);
                        s--;
                        if(s==0){
                          break;
                        }
                        // printf("Moved var in %d, %d to %d, %d\n", i+2, j+1, i+1, j+1);
                      }
                    }
                    ret_val++;
                }
            }
        }
    }
    ret_val += shift_up_all(g, m);
    return ret_val;
}

int shift_down_all(int g[], map <char*, pair<int,int>> &m){
    int ret_val = 0;
    while(1){
        int moves = 0;
        for(int i=3; i>0; i--){
            for(int j=0; j<4; j++){
                if(g[4*i+j]!=0){
                    continue;
                }
                else {
                    if(g[4*i+j-4]!=0){
                        g[4*i+j] = g[4*i+j-4];
                        g[4*i+j-4] = 0;
                        moves++;
                        ret_val++;
                        int s = m.size();
                        for(auto itr: m){
                          if(itr.second.first==i && itr.second.second==j+1){
                            // printf("Shifted var in %d, %d 1 down\n", i, j+1);
                            m[itr.first] = make_pair(i+1, j+1);
                            s--;
                            if(s==0){
                              break;
                            }
                          }
                        }
                    }
                }
            }
        }
        if(moves==0)
            break;
    }
    return ret_val;
}

int move_down(int g[], map <char*, pair<int,int>> &m, int op){
    int ret_val = 0;
    ret_val+=shift_down_all(g, m);
    int modified[16] = {0};
    for(int i=3; i>0; i--){
        for(int j=0; j<4; j++){
            if(modified[(4*i)+j]==0 && modified[(4*i)+j-4]==0){
                if(g[(4*i)+j]==g[(4*i)+j-4] && g[(4*i)+j]!=0){
                    modified[(4*i)+j]++;
                    modified[(4*i)+j-4]++;
                    if(op==1)
                      g[(4*i)+j] = 2*g[(4*i)+j];
                    else if (op==2)
                      g[(4*i)+j] = 0;
                    else if (op==3)
                      g[(4*i)+j] = g[(4*i)+j]*g[(4*i)+j];
                    else if (op==4)
                      g[(4*i)+j] = 1;
                    g[(4*i)+j-4] = 0;
                    int s = m.size();
                    for(auto itr: m){
                      if(itr.second.first==i && itr.second.second==j+1){
                        // printf("Moved var in %d, %d to %d, %d\n", i-1+1, j+1, i+1, j+1);
                        m[itr.first] = make_pair(i+1, j+1);
                        s--;
                        if(s==0){
                          break;
                        }
                      }
                    }
                    ret_val++;
                }
            }
        }
    }
    ret_val+=shift_down_all(g, m);
    // printGrid(g);
    return ret_val;

}

int shift_right_all(int g[], map <char*, pair<int,int>> &m){
    int ret_val = 0;
    while(1){
        int moves = 0;
        for(int i=0; i<4; i++){
            for(int j=3; j>0; j--){
                if(g[4*i+j]!=0){
                    continue;
                }
                else {
                    if(g[4*i+j-1]!=0){
                        g[4*i+j] = g[4*i+j-1];
                        g[4*i+j-1] = 0;
                        moves++;
                        ret_val++;
                        int s = m.size();
                        for(auto itr: m){
                          if(itr.second.first==i+1 && itr.second.second==j){
                            // printf("Shifted var in %d, %d 1 right\n", i+1, j);
                            m[itr.first] = make_pair(i+1, j+1);
                            s--;
                            if(s==0){
                              break;
                            }
                          }
                        }
                    }
                }
            }
        }
        if(moves==0)
            break;
    }
    return ret_val;
}

int move_right(int g[], map <char*, pair<int,int>> &m, int op){
    int ret_val = 0;
    ret_val+=shift_right_all(g, m);
    int modified[16] = {0};
    for(int i=0; i<4; i++){
        for(int j=3; j>0; j--){
            if(modified[(4*i)+j]==0 && modified[(4*i)+j-1]==0){
                if(g[(4*i)+j]==g[(4*i)+j-1] && g[(4*i)+j]!=0){
                    modified[(4*i)+j]++;
                    modified[(4*i)+j-1]++;
                    if(op==1)
                      g[(4*i)+j] = 2*g[(4*i)+j];
                    else if (op==2)
                      g[(4*i)+j] = 0;
                    else if (op==3)
                      g[(4*i)+j] = g[(4*i)+j]*g[(4*i)+j];
                    else if (op==4)
                      g[(4*i)+j] = 1;
                    g[(4*i)+j-1] = 0;
                    int s = m.size();
                    for(auto itr: m){
                      if(itr.second.first==i+1 && itr.second.second==j-1+1){
                        // printf("Moved var in %d, %d to %d, %d\n", i+1, j-1+1, i+1, j+1);
                        m[itr.first] = make_pair(i+1, j+1);
                        s--;
                        if(s==0){
                          break;
                        }
                      }
                    }
                    ret_val++;
                }
            }
        }
    }
    ret_val+=shift_right_all(g, m);
    // printGrid(g);
    return ret_val;
}

int shift_left_all(int g[], map <char*, pair<int,int>> &m){
    int ret_val = 0;
    while(1){
        int moves = 0;
        for(int i=0; i<4; i++){
            for(int j=0; j<3; j++){
                if(g[4*i+j]!=0){
                    continue;
                }
                else {
                    if(g[4*i+j+1]!=0){
                        g[4*i+j] = g[4*i+j+1];
                        g[4*i+j+1] = 0;
                        moves++;
                        ret_val++;
                        int s = m.size();
                        for(auto itr: m){
                          if(itr.second.first==i+1 && itr.second.second==j+2){
                            // printf("Shifted var in %d, %d 1 left\n", i+1, j+2);
                            m[itr.first] = make_pair(i+1, j+1);
                            s--;
                            if(s==0){
                              break;
                            }
                          }
                        }
                    }
                }
            }
        }
        if(moves==0)
            break;
    }
    return ret_val;
}

int move_left(int g[], map <char*, pair<int,int>> &m, int op){
    int ret_val = 0;
    ret_val+=shift_left_all(g, m);
    //modified keeps track of whether an operation has been performed on cell
    int modified[16] = {0};
    for(int i=0; i<4; i++){
        for(int j=0; j<3; j++){
            if(modified[(4*i)+j]==0 && modified[(4*i)+j+1]==0){
                if(g[(4*i)+j]==g[(4*i)+j+1] && g[(4*i)+j]!=0){
                    modified[(4*i)+j]++;
                    modified[(4*i)+j+1]++;
                    if(op==1)
                      g[(4*i)+j] = 2*g[(4*i)+j];
                    else if (op==2)
                      g[(4*i)+j] = 0;
                    else if (op==3)
                      g[(4*i)+j] = g[(4*i)+j]*g[(4*i)+j];
                    else if (op==4)
                      g[(4*i)+j] = 1;
                    g[(4*i)+j+1] = 0;
                    int s = m.size();
                    for(auto itr: m){
                      if(itr.second.first==i+1 && itr.second.second==j+2){
                        // printf("Moved var in %d, %d to %d, %d\n", i+1, j+2, i+1, j+1);
                        m[itr.first] = make_pair(i+1, j+1);
                        s--;
                        if(s==0){
                          break;
                        }
                      }
                    }
                    ret_val++;
                }
            }
        }
    }
    ret_val+=shift_left_all(g, m);
    // printGrid(g);
    return ret_val;
}

void move(int g[], map <char*, pair<int,int>> &m, int op, int dir){
  int temp[16] = {0};
  map <char*, pair<int, int>> m_temp;
  for(int i=0; i<16; i++){
    temp[i] = g[i];
  }
  if(dir==100){
    if(move_up(temp, m_temp, op)>0){
      // cout << "Actually moving\n";
      move_up(g, m, op);
      makezero(g);
      insertRandom(g);
    }
  }
  else if(dir==200){
    if(move_down(temp, m_temp, op)>0){
      // cout << "Actually moving\n";
      move_down(g, m, op);
      makezero(g);
      insertRandom(g);
    }
  }
  else if(dir==300){
    if(move_right(temp, m_temp, op)>0){
      // cout << "Actually moving\n";
      move_right(g, m, op);
      makezero(g);
      insertRandom(g);
    }
  }
  else if(dir==400){
    if(move_left(temp, m_temp, op)>0){
      // cout << "Actually moving\n";
      move_left(g, m, op);
      makezero(g);
      insertRandom(g);
    }
  }
  check_map(g, m);
  printError(g, m);
  printGrid(g);
  printVars(m);
}
