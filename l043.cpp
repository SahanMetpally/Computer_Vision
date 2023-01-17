#include <iostream>
#include <list>
#include <fstream>
#include <cstdio>
#include <ctime>
#include <math.h>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <tuple>
#include <chrono>
#include <map>
#include <queue>

using namespace std;

class Point{
private:
    double x,y;
    bool xC;
public:
    Point(double x1, double y1){
        x = x1;
        y = y1;
    }
    Point(double x1, double y1, bool xC1){
        x = x1;
        y = y1;
        xC = xC1;
    }
    double getX(){
        return x;
    }
    double getY(){
        return y;
    }
    bool getxC(){
        return xC;
    }
    void setxC(bool t){
        xC = t;
    }
    std::string toString(){
        return ("(" + std::to_string(x) + " " + std::to_string(y) + ") ");
    }
};

void circle(int x1, int y1, int radius, int board[800][800], int col){
    int x = radius;
    int y = 0;
    int err = 0;
    while (x >= y){
        if(x1 + x < 800 && x1 + x >= 0 && y1 + y < 800 && y1 + y >= 0){
            board[x1 + x][y1 + y] = col;
        }
        if(x1 + y < 800 && x1 + y >= 0 && y1 + x < 800 && y1 + x >= 0){
            board[x1 + y][y1 + x] = col;
        }
        if(x1 - y < 800 && x1 - y >= 0 && y1 + x < 800 && y1 + x >= 0){
            board[x1 - y][y1 + x] = col;
        }
        if(x1 - x < 800 && x1 - x >= 0 && y1 + y < 800 && y1 + y >= 0){
            board[x1 - x][y1 + y] = col;
        }
        if(x1 - x < 800 && x1 - x >= 0 && y1 - y < 800 && y1 - y >= 0){
            board[x1 - x][y1 - y] = col;
        }
        if(x1 - y < 800 && x1 - y >= 0 && y1 - x < 800 && y1 - x >= 0){
            board[x1 - y][y1 - x] = col;
        }
        if(x1 + y < 800 && x1 + y >= 0 && y1 - x < 800 && y1 - x >= 0){
            board[x1 + y][y1 - x] = col;
        }
        if(x1 + x < 800 && x1 + x >= 0 && y1 - y < 800 && y1 - y >= 0){
            board[x1 + x][y1 - y] = col;
        }
        if (err <= 0)
        {
            y += 1;
            err += 2*y + 1;
        }
        if (err > 0)
        {
            x -= 1;
            err -= 2*x + 1;
        }
    }
}

void print_ppm(vector<Point> ans, vector<int> nums){
    constexpr auto xSize = 800, ySize = 800;

    using namespace std;
    ofstream ofs("diagram.ppm", ios_base::out | ios_base::binary);
    ofs << "P3" << endl << xSize << ' ' << ySize << endl << "255" << endl;

    int board[xSize][ySize];

    for(int i = 0; i < xSize; i++){
        for(int j = 0; j < ySize; j++){
            board[i][j] = 0;
        }
    }
    for(int i = 0; i < nums.size(); i++){
        //std::cout << ans.at(nums.at(i)).getX() << " " << ans.at(nums.at(i)).getY() << std::endl;
        int x = int(ans.at(nums.at(i)).getX()*800);
        int y = int(ans.at(nums.at(i)).getY()*800);
        circle(y, x, 3, board, 1);
        bool xy = ans.at(nums.at(i)).getxC();
        if(xy == true){
            int xt = x;
            int yt = y+1;
            while(board[yt][xt] != 2 && board[yt][xt] != 3 && xt < 800 && xt >= 0 && yt < 800 && yt >= 0){
                board[yt][xt] = 3;
                yt += 1;
            }
            yt = y-1;
            while(board[yt][xt] != 2 && board[yt][xt] != 3 && xt < 800 && xt >= 0 && yt < 800 && yt >= 0){
                board[yt][xt] = 3;
                yt -= 1;
            }
        }
        else{
            int yt = y;
            int xt = x+1;
            while(board[yt][xt] != 2 && board[yt][xt] != 3 && xt < 800 && xt >= 0 && yt < 800 && yt >= 0){
                board[yt][xt] = 2;
                xt += 1;
            }
            xt = x-1;
            while(board[yt][xt] != 2 && board[yt][xt] != 3 && xt < 800 && xt >= 0 && yt < 800 && yt >= 0){
                board[yt][xt] = 2;
                xt -= 1;
            }
        }

    }

    for (int i = 0; i < xSize; i++) {
        for (int j = 0; j < ySize; j++) {
            if (board[i][j] == 0) {
                ofs << 255 << " " << 255 << " " << 255 << " ";
            }
            else if(board[i][j] == 1){
                ofs << 0 << " " << 0 << " " << 0 << " ";
            }
            else if(board[i][j] == 3){
                ofs << 255 << " " << 0 << " " << 0 << " ";
            }
            else{
                ofs << 0 << " " << 0 << " " << 255 << " ";
            }
        }
        ofs << "\n";
    }
    ofs.close();
}

//void make_order(vector<Point> temp){
//    vector<Point> map;
//    vector<int> solver;
//    for(int i = 0; i < 1102; i++){
//        map.push_back(Point(100,100));
//    }
//    map.at(0) = temp.at(0);
//    solver.push_back(0);
//    for(int i = 1; i < temp.size(); i++){
//        int pointer = 0;
//        int child = 0;
//        bool xy = true;
//        while(map.at(child).getX() != 100){
//            if(map.at(pointer).getxC() == true){
//                if(map.at(pointer).getX() > temp.at(i).getX()){
//                    int temp = pointer*2+1;
//                    pointer = child;
//                    child = temp;
//                    xy = false;
//                }
//                else{
//                    int temp = pointer*2+2;
//                    pointer = child;
//                    child = temp;
//                    xy = false;
//                }
//            }
//            else{
//                if(map.at(pointer).getY() > temp.at(i).getY()){
//                    int temp = pointer*2+1;
//                    pointer = child;
//                    child = temp;
//                    xy = true;
//                }
//                else{
//                    int temp = pointer*2+2;
//                    pointer = child;
//                    child = temp;
//                    xy = true;
//                }
//            }
//        }
//        Point t = temp.at(i);
//        t.setxC(xy);
//        map.at(child) = t;
//    }
//    for(int i = 0; i < map.size(); i++){
//        if(map.at(i).getX() != 100){
//            solver.push_back(i);
//        }
//    }
//    std::sort(solver.begin(), solver.end());
//    print_ppm(map, solver);
//}
void make_order(vector<Point> temp){
    std::map<int, Point> tree;
    vector<int> solver;

    tree.insert({0,temp.at(0)});
    solver.push_back(0);
    for(int i = 1; i < temp.size(); i++){
        int pointer = 0;
        int child = 0;
        bool xy = true;
        while(tree.count(child) == 1){
            if(tree.at(pointer).getxC() == true){
                if(tree.at(pointer).getX() > temp.at(i).getX()){
                    int temp = pointer*2+1;
                    pointer = child;
                    child = temp;
                    xy = false;
                }
                else{
                    int temp = pointer*2+2;
                    pointer = child;
                    child = temp;
                    xy = false;
                }
            }
            else{
                if(tree.at(pointer).getY() > temp.at(i).getY()){
                    int temp = pointer*2+1;
                    pointer = child;
                    child = temp;
                    xy = true;
                }
                else{
                    int temp = pointer*2+2;
                    pointer = child;
                    child = temp;
                    xy = true;
                }
            }
        }
        Point t = temp.at(i);
        t.setxC(xy);
        tree.insert({child,t});
        solver.push_back(child);
    }
    std::sort(solver.begin(), solver.end());
}
void part3(){
    std::cout << "Do you want to generate 10 points? (yes/no)" << std::endl;
    std::string gen;
    std::cin >> gen;
    vector<Point> points;
    if(gen == "yes"){
        std::ofstream file;
        file.open("points.txt");

        srand((unsigned) time(NULL));
        for(int i = 0; i < 10; i++){
            double x1=((double)rand()/(double)RAND_MAX);
            double y1=((double)rand()/(double)RAND_MAX);
            file << std::setprecision(23) << fixed << x1 << "  " << std::setprecision(23) << fixed << y1 << std::endl;
        }
    }
    if(gen == "no" || gen =="yes"){
        std::ifstream infile;
        infile.open("points.txt");
        std::string line = "";
        while(getline(infile,line)){
            int p = line.find(" ");
            double x1 = std::stod (line.substr(1,p));
            double y1 = std::stod (line.substr(p+2));
            Point temp(x1,y1,true);
            points.push_back(temp);
        }
        int x = 0;
    }
    else{
        std::cout << "Please enter proper input. (yes/no)";
    }
    make_order(points);
}

int main() {
    part3();
}
