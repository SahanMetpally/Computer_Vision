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

class Pixel{
private:
    double r,g,b;
    int cluster;
public:
    Pixel(double r1, double g1, double b1, int c){
        r = r1;
        g = g1;
        b = b1;
        cluster = c;
    }
    int getR(){
       return r;
    }
    int getG(){
        return g;
    }
    int getB(){
        return b;
    }
    void setCluster(int c){
        cluster = c;
    }
    int getCluster(){
        return cluster;
    }
    double getDistance(double x, double y, double z){
        return sqrt((x-r)*(x-r)+(y-g)*(y-g)+(z-b)*(z-b));
    }
    std::string toString(){
        return (std::to_string(r) + " " + std::to_string(g) + " " + std::to_string(b));
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
void printppm2(std::vector<Pixel> points, std::vector<Pixel> centroids, int w, int h) {
    using namespace std;
    ofstream ofs("output.ppm", ios_base::out | ios_base::binary);
    ofs << "P3" << endl << w << ' ' << h << endl << "255" << endl;
    for(int i = 0; i < points.size(); i++){
        int c = points.at(i).getCluster();
        ofs << (int)centroids.at(c).getR() << " " << (int)centroids.at(c).getG() << " " << (int)centroids.at(c).getB() << " ";
    }
}

void kmeans2(std::vector<Pixel> points, std::vector <Pixel> centroids, int w, int h) {
    vector<Pixel> newCentroids;
    int match = 0;
    for(int i = 0; i < centroids.size(); i++){
        double x = 0.0;
        double y = 0.0;
        double z = 0.0;
        int count = 0;
        for(int j = 0; j < points.size(); j++){
            if(points.at(j).getCluster() == i){
                count += 1;
                x += points.at(j).getR();
                y += points.at(j).getG();
                z += points.at(j).getB();
            }
        }
        x /= count; y /= count; z /= count;
        newCentroids.push_back(Pixel(x,y,z,i));
        if((int)x == (int)centroids.at(i).getR() && (int)y == (int)centroids.at(i).getG() && (int)z == (int)centroids.at(i).getB()){
            match += 1;
        }
    }
    if(match == centroids.size()){
        printppm2(points, centroids, w, h);
    }
    else {
        //std::cout<< "Redo" << std::endl;
        for (int i = 0; i < points.size(); i++) {
            double dist = 10000;
            for (int j = 0; j < newCentroids.size(); j++) {
                double d = newCentroids.at(j).getDistance(points.at(i).getR(), points.at(i).getG(), points.at(i).getB());
                if (d < dist) {
                    dist = d;
                    points.at(i).setCluster(newCentroids.at(j).getCluster());
                }
            }
        }
        kmeans2(points, newCentroids, w, h);
    }
}
void part2(){
    std::ifstream infile;
    infile.open("input.ppm");
    std::string line = "";
    getline(infile,line);
    getline(infile,line);
    int pos = line.find(" ");
    int w = stoi(line.substr(0,pos));
    int h = stoi(line.substr(pos+1));
    getline(infile,line);
    vector<Pixel> pixels;
    while(getline(infile,line)) {
        while (!line.empty()) {
            pos = line.find(" ");
            int r = stoi(line.substr(0, pos));
            line = line.substr(pos+1);
            pos = line.find(" ");
            int g = stoi(line.substr(0, pos));
            line = line.substr(pos+1);
            pos = line.find(" ");
            int b = stoi(line.substr(0, pos));
            line = line.substr(pos+1);

            Pixel pi(r,g,b,0);
            pixels.push_back(pi);
        }
    }
    vector<Pixel> centroids;
    Pixel p(0,0,0,0);
    centroids.push_back(p);
    Pixel p1(85,85,85,1);
    centroids.push_back(p1);
    Pixel p2(170,170,170,2);
    centroids.push_back(p2);
    Pixel p3(255,255,255,3);
    centroids.push_back(p3);

    for(int i = 0; i < pixels.size(); i++){
        double dist = 1000;
        for(int j = 0; j < centroids.size(); j++){
            double d = centroids.at(j).getDistance(pixels.at(i).getR(), pixels.at(i).getG(), pixels.at(i).getB());
            if(d < dist){
                dist = d;
                pixels.at(i).setCluster(centroids.at(j).getCluster());
            }
        }
    }
    kmeans2(pixels, centroids, w, h);
}

int main() {
    //part1();
    part2();
}