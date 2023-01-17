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
#include <unordered_map>
using namespace std;

class Point{
private:
    double x,y;
    int cluster;
public:
    Point(double x1, double y1, int i){
        x = x1;
        y = y1;
        cluster = i;
    }
    double getX(){
        return x;
    }
    double getY(){
        return y;
    }
    void setCluster(int c){
        cluster = c;
    }
    int getCluster(){
        return cluster;
    }
    double getDistance(double x1, double y1){
        return sqrt((x1-x)*(x1-x)+(y1-y)*(y1-y));
    }
    std::string toString(){
        return (std::to_string(x) + " " + std::to_string(y));
    }
};
void circle(int x1, int y1, int radius, int board[800][800], int col){
    int x = radius;
    int y = 0;
    int err = 0;
    while (x >= y){
        if(x1 + x < 800 && x1 + x >= 0 && y1 + y < 800 && y1 + y >= 0){
//std::cout << "1 " << std::endl;
            board[x1 + x][y1 + y] = col;
        }
        if(x1 + y < 800 && x1 + y >= 0 && y1 + x < 800 && y1 + x >= 0){
//std::cout << "2 " << std::endl;
            board[x1 + y][y1 + x] = col;
        }
        if(x1 - y < 800 && x1 - y >= 0 && y1 + x < 800 && y1 + x >= 0){
//std::cout << "3 " << std::endl;
            board[x1 - y][y1 + x] = col;
        }
        if(x1 - x < 800 && x1 - x >= 0 && y1 + y < 800 && y1 + y >= 0){
//std::cout << "4 " << std::endl;
            board[x1 - x][y1 + y] = col;
        }
        if(x1 - x < 800 && x1 - x >= 0 && y1 - y < 800 && y1 - y >= 0){
//std::cout << "5 " << std::endl;
            board[x1 - x][y1 - y] = col;
        }
        if(x1 - y < 800 && x1 - y >= 0 && y1 - x < 800 && y1 - x >= 0){
//std::cout << "6 " << std::endl;
            board[x1 - y][y1 - x] = col;
        }
        if(x1 + y < 800 && x1 + y >= 0 && y1 - x < 800 && y1 - x >= 0){
//std::cout << "7 " << std::endl;
            board[x1 + y][y1 - x] = col;
        }
        if(x1 + x < 800 && x1 + x >= 0 && y1 - y < 800 && y1 - y >= 0){
//std::cout << "8 " << std::endl;
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

void printppm(std::vector<Point> points, std::vector<Point> centroids) {
    constexpr auto xSize = 800, ySize = 800;
    using namespace std;
    ofstream ofs("clusters.ppm", ios_base::out | ios_base::binary);
    ofs << "P3" << endl << xSize << ' ' << ySize << endl << "255" << endl;
    int board[xSize][ySize];
    for(int i = 0; i < xSize; i++){
        for(int j = 0; j < ySize; j++){
            board[i][j] = 10;
        }
    }
    for(int i = 0; i < centroids.size(); i++){
        circle(int(centroids.at(i).getX()*800), int(centroids.at(i).getY()*800), 3, board, 5);
    }
    for(int i = 0; i < points.size(); i++){
        circle(int(points.at(i).getX()*800), int(points.at(i).getY()*800), 2, board, points.at(i).getCluster());
    }
    for (int i = 0; i < xSize; i++) {
        for (int j = 0; j < ySize; j++) {
            if (board[i][j] == 0) {
                ofs << 255 << " " << 0 << " " << 255 << " ";
            }
            else if(board[i][j] == 1){
                ofs << 255 << " " << 0 << " " << 0 << " ";
            }
            else if(board[i][j] == 2){
                ofs << 0 << " " << 255 << " " << 0 << " ";
            }
            else if(board[i][j] == 3){
                ofs << 0 << " " << 0 << " " << 255 << " ";
            }
            else if(board[i][j] == 4){
                ofs << 0 << " " << 255 << " " << 255 << " ";
            }
            else if(board[i][j] == 5){
                ofs << 0 << " " << 0 << " " << 0 << " ";
            }
            else{
                ofs << 255 << " " << 255 << " " << 255 << " ";
            }
        }
        ofs << "\n";
    }
    ofs.close();
}

void kmeans(std::vector<Point> points, std::vector <Point> centroids) {
    vector<Point> newCentroids;
    int match = 0;
    for(int i = 0; i < centroids.size(); i++){
        double x = 0.0;
        double y = 0.0;
        int count = 0;
        for(int j = 0; j < points.size(); j++){
            if(points.at(j).getCluster() == i){
            count += 1;
            x += points.at(j).getX();
            y += points.at(i).getY();
            }
        }
        x /= count; y /= count;
        newCentroids.push_back(Point(x,y,i));
        if(x == centroids.at(i).getX() && y == centroids.at(i).getY()){
            match += 1;
        }
    }
    if(match == centroids.size()){
        printppm(points, centroids);
    }
    else {
        for (int i = 0; i < points.size(); i++) {
            double dist = 10;
            for (int j = 0; j < newCentroids.size(); j++) {
                double d = newCentroids.at(j).getDistance(points.at(i).getX(), points.at(i).getY());
                if (d < dist) {
                    dist = d;
                    points.at(i).setCluster(newCentroids.at(j).getCluster());
                }
            }
        }
        kmeans(points, newCentroids);
    }
}
void part1() {
    srand((unsigned) time(NULL));
    vector<Point> points;
    vector<Point> centroids;
    for(int i = 0; i < 100; i++){
        double x1=((double)rand()/(double)RAND_MAX);
        double y1=((double)rand()/(double)RAND_MAX);
        //std::cout << x1 << " " << y1 << " " << i << std::endl;
        Point point(x1,y1,0);
        points.push_back(point);
    }
    srand((unsigned) time(NULL));
    for(int i = 0; i < 5; i++){
        int random = int(rand() % 100);
        points.at(random).setCluster(i);
        centroids.push_back(points.at(random));
    }
    for(int i = 0; i < points.size(); i++){
        double dist = 10;
        for(int j = 0; j < centroids.size(); j++){
            double d = centroids.at(j).getDistance(points.at(i).getX(), points.at(i).getY());
            if(d < dist){
                dist = d;
                points.at(i).setCluster(centroids.at(j).getCluster());
            }
        }
    }
    kmeans(points, centroids);
}

int main() {
    part1();
}