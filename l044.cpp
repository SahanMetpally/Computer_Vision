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
    double mx, my, Mx, My;
    bool xC;
public:
    vector<Point> possible;
    vector<Point> centroid;
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
    void setCentroid(Point c){
        centroid.clear();
        centroid.push_back(c);
    }
    Point getCluster(){
        return centroid.at(0);
    }
    double getMinX(){
        return mx;
    }
    double getMinY(){
        return my;
    }
    double getMaxX(){
        return Mx;
    }
    double getMaxY(){
        return My;
    }
    void setMinX(double tx){
        mx = tx;
    }
    void setMinY(double ty){
        my = ty;
    }
    void setMaxX(double tx){
        Mx = tx;
    }
    void setMaxY(double ty){
        My = ty;
    }
    double getDistance(double x1, double y1){
        return sqrt((x1-x)*(x1-x)+(y1-y)*(y1-y));
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

void printppm(map<int,Point> points, std::vector<Point> centroids) {
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

    std::map<int, Point>::iterator it;
    for (it = points.begin(); it != points.end(); it++){
        Point rt = it ->second;
        for(int i = 0; i < centroids.size(); i++){
            if(rt.getCluster().getDistance(centroids.at(i).getX(), centroids.at(i).getY()) == 0.0){
                circle(int(rt.getX()*800), int(rt.getY()*800), 2, board, i);
            }
        }
    }
    for(int i = 0; i < centroids.size(); i++){
        circle(int(centroids.at(i).getX()*800), int(centroids.at(i).getY()*800), 1, board, 5);
        circle(int(centroids.at(i).getX()*800), int(centroids.at(i).getY()*800), 2, board, 5);
        circle(int(centroids.at(i).getX()*800), int(centroids.at(i).getY()*800), 3, board, 5);
        circle(int(centroids.at(i).getX()*800), int(centroids.at(i).getY()*800), 4, board, 5);
        circle(int(centroids.at(i).getX()*800), int(centroids.at(i).getY()*800), 5, board, 5);
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

void kmeans(map<int,Point> map, std::vector <Point> points, std::vector <Point> centroids) {
    vector<Point> newCentroids;
    int match = 0;
    vector<int> indices;
    std::map<int, Point>::iterator it;
    for (it = map.begin(); it != map.end(); it++)
    {
        int index = it -> first;
        Point t = it -> second;
        t.possible = centroids;
        t.setCentroid(centroids.at(0));
        indices.push_back(index);
    }
    for(int i = 0; i < indices.size(); i++){
        int r = indices.at(i);
        vector<Point> dominated;
        for(int j = 0; j < centroids.size(); j++){
            for(int z = j; z < centroids.size(); z++){
                Point one = centroids.at(j);
                Point two = centroids.at(z);
                double minX = map.at(r).getMinX();
                double minY = map.at(r).getMinY();
                double maxX = map.at(r).getMaxX();
                double maxY = map.at(r).getMaxY();
                if(one.getDistance(minX, minY) < two.getDistance(minX, minY) && one.getDistance(minX, maxY) < two.getDistance(minX, maxY) && one.getDistance(maxX, minY) < two.getDistance(maxX, minY) && one.getDistance(maxX, maxY) < two.getDistance(maxX, maxY)){
                    dominated.push_back(two);
                }
                else if(one.getDistance(minX, minY) > two.getDistance(minX, minY) && one.getDistance(minX, maxY) > two.getDistance(minX, maxY) && one.getDistance(maxX, minY) > two.getDistance(maxX, minY) && one.getDistance(maxX, maxY) > two.getDistance(maxX, maxY)){
                    dominated.push_back(one);
                }
            }
        }
        for(int j = 0; j < centroids.size(); j++){
            bool poss = true;
            for(int k = 0; k < dominated.size(); k++){
                if(dominated.at(k).getDistance(centroids.at(j).getX(), centroids.at(j).getY()) == 0){
                    poss = false;
                }
            }
            if(poss){
                newCentroids.push_back(centroids.at(j));
            }
        }
        if(map.count(r*2+1) == 1){
            map.at(r*2+1).possible = newCentroids;
        }
        if(map.count(r*2+2) == 1){
            map.at(r*2+2).possible = newCentroids;
        }
        double min = 10.0;
        Point closest(0.0,0.0);
        for(int f = 0; f < newCentroids.size(); f++){
            if(newCentroids.at(f).getDistance(map.at(r).getX(), map.at(r).getY()) < min){
                min = newCentroids.at(f).getDistance(map.at(r).getX(), map.at(r).getY());
                closest = newCentroids.at(f);
            }
        }
        map.at(r).setCentroid(closest);
    }
    vector<Point> updateCentroids;
    bool done = true;
    for(int i = 0; i < centroids.size(); i++){
        std::map<int, Point>::iterator it;
        double xN = 0.0;
        double yN = 0.0;
        int count = 0;
        for (it = map.begin(); it != map.end(); it++)
        {
            if(it->second.getDistance(centroids.at(i).getX(), centroids.at(i).getY()) == 0){
                count += 1;
                xN += it->second.getX();
                yN += it->second.getY();
            }
        }
        updateCentroids.push_back(Point(xN/count,yN/count));
        if(xN/count != centroids.at(i).getX() || yN/count != centroids.at(i).getY()){
            done = false;
        }
    }
    if(!done){
        kmeans(map, points, updateCentroids);
    }
    else{
        printppm(map,updateCentroids);
    }
}

void make_order(vector<Point> temp, vector<Point> centroids){
    std::map<int, Point> tree;
    vector<int> solver;
    temp.at(0).setMinX(0.0);
    temp.at(0).setMinY(0.0);
    temp.at(0).setMaxY(1.0);
    temp.at(0).setMaxY(1.0);

    tree.insert({0,temp.at(0)});
    solver.push_back(0);
    for(int i = 1; i < temp.size(); i++){
        int pointer = 0;
        int child = 0;
        bool xy = true;
        bool left = true;
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
                    left = true;
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
                    left = false;
                }
            }
        }
        Point t = temp.at(i);
        t.setxC(xy);
        if(!xy){
            if(left){
                t.setMinX(0.0);
                t.setMaxX(tree.at(pointer).getX());
                t.setMinY(tree.at(pointer).getMinY());
                t.setMaxY(tree.at(pointer).getMaxY());
            }
            else{
                t.setMinX(tree.at(pointer).getX());
                t.setMaxX(1.0);
                t.setMinY(tree.at(pointer).getMinY());
                t.setMaxY(tree.at(pointer).getMaxY());
            }
        }
        else{
            if(left){
                t.setMinY(0.0);
                t.setMaxY(tree.at(pointer).getY());
                t.setMinX(tree.at(pointer).getMinX());
                t.setMaxX(tree.at(pointer).getMaxX());
            }
            else{
                t.setMinY(tree.at(pointer).getY());
                t.setMaxY(1.0);
                t.setMinX(tree.at(pointer).getMinX());
                t.setMaxX(tree.at(pointer).getMaxX());
            }
        }
        tree.insert({child,t});
        solver.push_back(child);
    }
    std::sort(solver.begin(), solver.end());
    kmeans(tree, temp, centroids);
}
void part4(){
    std::cout << "Do you want to generate 50 points? (yes/no)" << std::endl;
    std::string gen;
    std::cin >> gen;
    vector<Point> points;
    if(gen == "yes"){
        std::ofstream file;
        file.open("points.txt");

        srand((unsigned) time(NULL));
        for(int i = 0; i < 50; i++){
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
    vector<Point> centroids;

    for(int i = 0; i < 5; i++){
        centroids.push_back(points.at(i));
    }
    make_order(points, centroids);

}

int main() {
    part4();
}

