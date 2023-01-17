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

double x1;
double y;
double x2;
double y2;
double x3;
double y3;
double x4;
double y4;
double x5;
double y5;
double x6;
double y6;
double minimum1 = 10.0;
double minimum = 10.0;
auto time1 = 0;
auto time2 = 0;
double minimum3 = 10.0;
auto time3 = 0;

class Point{
private:
    double x,y;
public:
    Point(double x1, double y1){
        x = x1;
        y = y1;
    }
    double getX(){
        return x;
    }
    double getY(){
        return y;
    }
    double getDistance(double x1, double y1){
        return sqrt((x1-x)*(x1-x)+(y1-y)*(y1-y));
    }
    std::string toString(){
        return (std::to_string(x) + "  " + std::to_string(y));
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
void printList(list <Point> g){
    std::ofstream file;
    file.open("points.txt");

    list <Point> :: iterator it;
    for(it = g.begin(); it != g.end(); ++it) {
        file << std::setprecision(23) << fixed << it->getX() << "  " << std::setprecision(23) << fixed << it->getY() << std::endl;
    }
}
void printppm(list <Point> g, double x1, double y1, double x2, double y2){
    constexpr auto xSize = 800, ySize = 800;

    using namespace std;
    ofstream ofs("points.ppm", ios_base::out | ios_base::binary);
    ofs << "P3" << endl << xSize << ' ' << ySize << endl << "255" << endl;

    int board[xSize][ySize];

    for(int i = 0; i < xSize; i++){
        for(int j = 0; j < ySize; j++){
            board[i][j] = 0;
        }
    }
    list <Point> :: iterator it;
    for(it = g.begin(); it != g.end(); ++it) {
        board[int(it->getY()*800)][int(it->getX()*800)] = 1;
        circle(int(it->getY()*800), int(it->getX()*800), 2, board, 1);
    }
    circle(int(y1*800), int(x1*800), 2, board, 2);
    circle(int(y2*800), int(x2*800), 2, board, 2);
    for (int i = 0; i < xSize; i++) {
        for (int j = 0; j < ySize; j++) {
            if (board[i][j] == 0) {
                ofs << 255 << " " << 255 << " " << 255 << " ";
            }
            else if(board[i][j] == 1){
                ofs << 0 << " " << 0 << " " << 0 << " ";
            }
            else if(board[i][j] == 2){
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
void part1(){
    srand((unsigned) time(NULL));
    list<Point> points;
    for(int i = 0; i < 1600; i++){
        double x1=((double)rand()/(double)RAND_MAX);
        double y1=((double)rand()/(double)RAND_MAX);
        //std::cout << x1 <<  "  " << y1 <<  " " << i << std::endl;
        Point point(x1,y1);
        points.push_back(point);
    }
    printList(points);
    auto start = std::chrono::high_resolution_clock::now();
    list <Point> :: iterator it;
    list <Point> :: iterator jt;
    double x0 = 0; double y0 = 0; double x5 = 0; double y5 = 0;
    double distance = 10;
    for(it = points.begin(); it != points.end(); ++it) {
        for(jt = it; jt != points.end(); ++jt) {
            double temp = it->getDistance(jt->getX(), jt->getY());
            if(temp < distance && temp != 0){
                distance = temp;
                x0 = it->getX();
                y0 = it->getY();
                x5 = jt->getX();
                y5 = jt->getY();
            }
        }
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    time1 = duration.count();
    minimum1 = distance;
    x1 = x0;
    y = y0;
    x2 = x5;
    y2 = y5;
    //std::cout<< distance << std::endl;
    //std::cout << x1 << " " << y1 << " " << x2 << " " << y2 << std::endl;
    printppm(points, x0,y0,x5,y5);
}

bool compare(Point x, Point y) {
    return (x.getX() < y.getX());
}
bool compare2(Point x, Point y) {
    return (x.getY() < y.getY());
}
double brute(vector<Point> a){
    double min = minimum;
    //for(int i = 0; i < a.size(); i++){
    //for(int j = i+1; j < a.size(); j++){
    for(vector<Point>::iterator i = a.begin(); i != a.end(); ++i) {
        for (vector<Point>::iterator j = i; j != a.end(); ++j) {
            double t = i->getDistance(j->getX(), j->getY());
            if(t < min && t != 0) {
                min = t;
                minimum = min;
                x3 = i->getX();
                y3 = i->getY();
                x4 = j->getX();
                y4 = j->getY();
            }
        }
    }
    return min;
}

double stripSolver(vector<Point> a, double d){
    double min = d;
    int size = a.size();
    if (size > 15){
        size = 15;
    }
    for(int i = 0; i < size; i++){
        for(int j = i+1; j < size; j++){
            //std::cout << a.at(i).getDistance(a.at(j).getX(), a.at(j).getY()) << std::endl;
            double t = a.at(i).getDistance(a.at(j).getX(), a.at(j).getY());
            if(t < min){
                min = t;
                minimum = min;
                x3 = a.at(i).getX();
                y3 = a.at(i).getY();
                x4 = a.at(j).getX();
                y4 = a.at(j).getY();
                //std::cout << "here 2" << std::endl;
            }
        }
    }
    return min;
}
double recursion(vector<Point> temp){
    vector<Point> a = temp;
    int l = a.size();

    if(l <= 3){
        return brute(a);
    }
    int mid = a.size()/2;
    Point middle = a.at(mid);

    vector<Point> left;
    vector<Point> right;
    for(int i = 0; i < l; i++){
        if(i <= mid){
            left.push_back(a.at(i));
        }
        else{
            right.push_back(a.at(i));
        }
    }

    double d1 = recursion(left);
    double d2 = recursion(right);

    double d = min(d1, d2);

    vector<Point> strip;
    Point midpoint = a.at(mid);
    for(int i = 0; i < a.size(); i++){
        if(abs(midpoint.getX() - a.at(i).getX()) < d){
            strip.push_back(a.at(i));
        }
    }
    double distance = stripSolver(strip, d);
    return distance;
}

Point one4(0.0, 0.0);
Point two4(0.0,0.0);
auto time4 = 0.0;
double distance4 = 0.0;

void printResults(){
    std::ofstream file;
    file.open("results.txt");
    //file << "Brute Force: " << time1 << " microseconds " << std::setprecision(23) << fixed << minimum1 << " (" << std::setprecision(23) << fixed << x1 << "," << std::setprecision(23) << fixed << y << ")"<< " (" << std::setprecision(23) << fixed << x2 << "," << std::setprecision(23) << fixed << y2 << ")"<< std::endl;
    //file << "Recursion: " << time2 << " microseconds " << std::setprecision(23) << fixed << minimum << " (" << std::setprecision(23) << fixed << x3 << "," << std::setprecision(23) << fixed << y3 << ")"<< " (" << std::setprecision(23) << fixed << x4 << "," << std::setprecision(23) << fixed << y4 << ")" << std::endl;
    file << "Recursion Part 2: " << time3 << " microseconds " << std::setprecision(23) << fixed << minimum3 << " (" << std::setprecision(23) << fixed << x5 << "," << std::setprecision(23) << fixed << y5 << ")"<< " (" << std::setprecision(23) << fixed << x6 << "," << std::setprecision(23) << fixed << y6 << ")" << std::endl;
    file << "Randomized Approach: " << time4 << " microseconds " << std::setprecision(23) << fixed << distance4 << " (" << std::setprecision(23) << fixed << one4.getX() << "," << std::setprecision(23) << fixed << one4.getY() << ")"<< " (" << std::setprecision(23) << fixed << two4.getX() << "," << std::setprecision(23) << fixed << two4.getY() << ")" << std::endl;
    file.close();
    //std::cout << "Recursion: " << time2 << " microseconds " << std::setprecision(23) << fixed << minimum << " (" << std::setprecision(23) << fixed << x3 << "," << std::setprecision(23) << fixed << y3 << ")"<< " (" << std::setprecision(23) << fixed << x4 << "," << std::setprecision(23) << fixed << y4 << ")" << std::endl;
    std::cout << "Recursion Part 2: " << time3 << " microseconds " << std::setprecision(23) << fixed << minimum3 << " (" << std::setprecision(23) << fixed << x5 << "," << std::setprecision(23) << fixed << y5 << ")"<< " (" << std::setprecision(23) << fixed << x6 << "," << std::setprecision(23) << fixed << y6 << ")" << std::endl;
    std::cout << "Randomized Approach: " << time4 << " microseconds " << std::setprecision(23) << fixed << distance4 << " (" << std::setprecision(23) << fixed << one4.getX() << "," << std::setprecision(23) << fixed << one4.getY() << ")"<< " (" << std::setprecision(23) << fixed << two4.getX() << "," << std::setprecision(23) << fixed << two4.getY() << ")" << std::endl;

}
void part2(){
    vector<Point> vect;

    std::ifstream infile;
    infile.open("points.txt");
    std::string line = "";
    while(getline(infile,line)){
        int p = line.find(" ");
        double x1 = std::stod (line.substr(1,p));
        double y1 = std::stod (line.substr(p+2));
        Point temp(x1,y1);
        vect.push_back(temp);
    }
    auto start = std::chrono::high_resolution_clock::now();

    sort(vect.begin(), vect.end(), compare);
    double d = recursion(vect);

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    time2 = duration.count();
    //std::cout << x3 << " " << y3 << " " << x4 << " " << y4 << std::endl;
    //std::cout << d;
}
double brute3(vector<Point> a){
    double min = minimum3;
    //for(int i = 0; i < a.size(); i++){
    //for(int j = i+1; j < a.size(); j++){
    for(vector<Point>::iterator i = a.begin(); i != a.end(); ++i) {
        for (vector<Point>::iterator j = i; j != a.end(); ++j) {
            double t = i->getDistance(j->getX(), j->getY());
            if(t < min && t != 0) {
                min = t;
                minimum3 = min;
                x5 = i->getX();
                y5 = i->getY();
                x6 = j->getX();
                y6 = j->getY();
            }
        }
    }
    return min;
}
double stripSolver3(vector<Point> a, double d){
    double min = d;
    int size = a.size();
    if (size > 15){
        size = 15;
    }
    for(int i = 0; i < size; i++){
        for(int j = i+1; j < size; j++){
            //std::cout << a.at(i).getDistance(a.at(j).getX(), a.at(j).getY()) << std::endl;
            double t = a.at(i).getDistance(a.at(j).getX(), a.at(j).getY());
            if(t < min){
                min = t;
                minimum3 = min;
                x5 = a.at(i).getX();
                y5 = a.at(i).getY();
                x6 = a.at(j).getX();
                y6 = a.at(j).getY();
                //std::cout << "here 2" << std::endl;
            }
        }
    }
    return min;
}
double recursion3(vector<Point> temp){
    vector<Point> a = temp;
    int l = a.size();

    if(l <= 3){
        return brute3(a);
    }
    int mid = a.size()/2;
    Point middle = a.at(mid);

    vector<Point> left;
    vector<Point> right;
    for(int i = 0; i < a.size(); i++){
        if(i <= mid){
            left.push_back(a.at(i));
        }
        else{
            right.push_back(a.at(i));
        }
    }

    double d1 = recursion3(left);
    double d2 = recursion3(right);

    double d = min(d1, d2);

    vector<Point> strip;
    Point midpoint = a.at(mid);
    for(int i = 0; i < a.size(); i++){
        if(abs(midpoint.getX() - a.at(i).getX()) < d){
            strip.push_back(a.at(i));
        }
    }
    sort(strip.begin(), strip.end(), compare2);
    double distance = stripSolver3(strip, d);
    return distance;
}
void part3(){
    vector<Point> vect;

    std::ifstream infile;
    infile.open("points.txt");
    std::string line = "";
    while(getline(infile,line)){
        int p = line.find(" ");
        double x1 = std::stod (line.substr(1,p));
        double y1 = std::stod (line.substr(p+2));
        Point temp(x1,y1);
        vect.push_back(temp);
    }
    auto start = std::chrono::high_resolution_clock::now();

    sort(vect.begin(), vect.end(), compare);
    double d = recursion3(vect);

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    time3 = duration.count();
    //std::cout << x3 << " " << y3 << " " << x4 << " " << y4 << d << std::endl;
    //std::cout << d;
}
void swap(vector<Point> temp, int i, int j){
    Point x = temp.at(i);
    Point y = temp.at(j);
    temp[i] = y;
    temp[j] = x;
}
struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const
    {
        auto hash1 = hash<T1>{}(p.first);
        auto hash2 = hash<T2>{}(p.second);
        return hash1 ^ hash2;
    }
};
void part4(){
    vector<Point> vect3;

    std::ifstream infile;
    infile.open("points.txt");
    std::string line = "";
    while(getline(infile,line)){
        int p = line.find(" ");
        double x1 = std::stod (line.substr(1,p));
        double y1 = std::stod (line.substr(p+2));
        Point temp(x1,y1);
        vect3.push_back(temp);
    }
    auto start = std::chrono::high_resolution_clock::now();

    srand((unsigned) time(NULL));
    for(int i = 0; i < vect3.size(); i++){
        int rando = (int)(((double)rand()/(double)RAND_MAX)*(vect3.size()-i) + i);
        Point a = vect3.at(i);
        Point b = vect3.at(rando);
        vect3[i] = b;
        vect3[rando] = a;
    }

    unordered_map<pair<unsigned long long, unsigned long long>, Point, hash_pair> mappy;
    Point temp1 = vect3.at(0);
    Point temp2 = vect3.at(1);
    Point temp3 = vect3.at(0);
    Point temp4 = vect3.at(1);
    double d = vect3.at(0).getDistance(vect3.at(1).getX(), vect3.at(1).getY());
    for(int i = 0; i < vect3.size(); i++) {
        unsigned long long xC = ((vect3.at(i).getX())/(0.5*d));
        unsigned long long yC = ((vect3.at(i).getY())/(0.5*d));
        double tempD = 10.0;
        for(int b =-2; b < 3; b++){
            for(int a = -2; a < 3; a++){
                pair<unsigned long long, unsigned long long> key(xC+a, yC+b);
                if (mappy.find(key) != mappy.end()){
                    double tD2 = mappy.find(key)->second.getDistance(vect3.at(i).getX(), vect3.at(i).getY());
                  if (tD2 < tempD){
                     temp3 = vect3.at(i);
                    temp4 = mappy.find(key)->second;
                    tempD = tD2;
                }
                }
            }
        }
        if(tempD < d){
            d = tempD;
            temp1 = temp3;
            temp2 = temp4;
            mappy.clear();
            for(int j = 0; j <= i; j ++){
                //std::cout << vect3.at(j).toString() << std::endl;
                unsigned long long xC2 = ((vect3.at(j).getX())/(0.5*d));
                unsigned long long yC2 = ((vect3.at(j).getY())/(0.5*d));
                pair<unsigned long long, unsigned long long> t(xC2, yC2);
                mappy.insert({t, vect3.at(j)});
            }
        }
        else {
            pair<unsigned long long, unsigned long long> t(xC, yC);
            mappy.insert({t, vect3.at(i)});
        }
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    time4 = duration.count();
//    for(auto p: vect3){
//        std::cout << p.toString() << std::endl;
//    }
    distance4 = d;
    one4 = temp1;
    two4 = temp2;
    printResults();

    //std::cout << temp1.getDistance(temp2.getX(), temp2.getY())<< d;
}
int main() {
    //part1();
    //part2();
    part3();
    part4();
}
