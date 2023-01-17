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

#define PI 3.14159265

using namespace std;

void area_fill(vector<int> &hysth, int w, int h, int point){
    if(hysth.at(point) == 2) {
        int point2 = point - w;
        int point3 = point + w;

        int point4 = point - w - 1;
        int point5 = point - w + 1;

        int point6 = point - 1;
        int point7 = point + 1;

        int point8 = point + w - 1;
        int point9 = point + w + 1;
        if (point2 >= 0) {
            //cout<<2<<endl;
            if (hysth.at(point2) == 1) {
                hysth.at(point2) = 2;
                area_fill(hysth, w, h, point2);
            }
        }
        if (point3 < w*h) {
            //cout<<3<<endl;
            if (hysth.at(point3) == 1) {
                hysth.at(point3) = 2;
                area_fill(hysth, w, h, point3);
            }
        }
        if (point % w != 0 && point4 >= 0) {
            //cout<<4<<endl;
            if (hysth.at(point4) == 1) {
                hysth.at(point4) = 2;
                area_fill(hysth, w, h, point4);
            }
        }
        if (point % w != w - 1 && point5 >= 0) {
            //cout<<5<<endl;
            if (hysth.at(point5) == 1) {
                hysth.at(point5) = 2;
                area_fill(hysth, w, h, point5);
            }
        }
        if (point % w != 0 && point6 >= 0){
            //cout<<6<<endl;
            if (hysth.at(point6) == 1) {
                hysth.at(point6) = 2;
                area_fill(hysth, w, h, point6);
            }
        }
        if (point % w != w-1 && point7 < w*h) {
            //cout<<7<<endl;
            if (hysth.at(point7) == 1) {
                hysth.at(point7) = 2;
                area_fill(hysth, w, h, point7);
            }
        }
        if(point8 < w*h && point%w != 0) {
            //cout<<8<<endl;
            if (hysth.at(point8) == 1) {
                hysth.at(point8) = 2;
                area_fill(hysth, w, h, point8);
            }
        }
        if(point9 < w*h && point%w != w-1) {
            //cout<<point9<<endl;
            if(hysth.at(point9) == 1) {
                hysth.at(point9) = 2;
                area_fill(hysth, w, h, point9);
            }
        }
        return;
    }
}


void circle(int x1, int y1, int radius, vector<int> &centers, int col, int h, int w){
    int x = radius;
    int y = 0;
    int err = 0;

    while (x >= y){
        if(x1 + x < h && x1 + x >= 0 && y1 + y < w && y1 + y >= 0){
            //std::cout << "1 " << std::endl;
            int p = (x1 + x)*w+(y1 + y);
            centers.at(p) = col;
        }
        if(x1 + y < h && x1 + y >= 0 && y1 + x < w && y1 + x >= 0){
            //std::cout << "2 " << std::endl;
            int p = (x1 + y)*w+(y1 + x);
            centers.at(p) = col;
        }
        if(x1 - y < h && x1 - y >= 0 && y1 + x < w && y1 + x >= 0){
            //std::cout << "3 " << std::endl;
            int p = (x1 - y)*w+(y1 + x);
            centers.at(p) = col;
        }
        if(x1 - x < h && x1 - x >= 0 && y1 + y < w && y1 + y >= 0){
            //std::cout << "4 " << std::endl;
            int p = (x1 - x)*w+(y1 + y);
            centers.at(p) = col;
        }
        if(x1 - x < h && x1 - x >= 0 && y1 - y < w && y1 - y >= 0){
            //std::cout << "5 " << std::endl;
            int p = (x1 - x)*w+(y1 - y);
            centers.at(p) = col;
        }
        if(x1 - y < h && x1 - y >= 0 && y1 - x < w && y1 - x >= 0){
            //std::cout << "6 " << std::endl;
            int p = (x1 - y)*w+(y1 - x);
            centers.at(p) = col;
        }
        if(x1 + y < h && x1 + y >= 0 && y1 - x < w && y1 - x >= 0){
            //std::cout << "7 " << std::endl;
            int p = (x1 + y)*w+(y1 - x);
            centers.at(p) = col;
        }
        if(x1 + x < h && x1 + x >= 0 && y1 - y < w && y1 - y >= 0){
            //std::cout << "8 " << std::endl;
            int p = (x1 + x)*w+(y1 - y);
            centers.at(p) = col;
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

void bresenham(int x1, int y1, int x2, int y2, vector<int> &votes, int w, int h){
    if(y2 < y1){
        int a = x1; x1 = x2; x2 = a;
        a = y1; y1 = y2; y2 = a;
    }
    int xs = y1, ys = w - x1, xe = y2, ye = w - x2;
    int dx = xe - xs, dy = ye - ys, errorX = abs(dx), errorY = abs(dy);
    int dx1 = 1, dy1 = 0, dx2 = 1, dy2 = 0;

    if (dy<0) {
        dy1 = -1;
    }
    else if (dy>0) {
        dy1 = 1;
    }

    if (errorX <= errorY){
        errorX = abs(dy);
        errorY = abs(dx);
        if (dy < 0) {
            dy2 = -1;
        }
        else if (dy > 0) {
            dy2 = 1;
        }
        dx2 = 0;
    }
    //vector<int> changed;
    int di = errorX/2;
    while(xs != xe || ys != ye){
        int point = (w-ys)*w+xs;
        //changed.push_back(point);
        votes.at(point) = votes.at(point) + 1;
        di += errorY;
        if(!(di < errorX)){
            di -= errorX;
            xs += dx1;
            ys += dy1;
        }
        else{
            xs += dx2;
            ys += dy2;
        }
    }
    //bool test = true;
}

void part1(){
    std::ifstream infile;
    infile.open("coinsHard.ppm");
    std::string line = "";
    getline(infile,line);
    getline(infile,line);
    int pos = line.find(" ");
    const int w = stoi(line.substr(0,pos));
    const int h = stoi(line.substr(pos+1));
    getline(infile,line);

    vector<double> board;
    vector<int> red;vector<int> green;vector<int> blue;

    while(getline(infile,line)) {
        while (!line.empty()) {
            pos = line.find(" ");
            double r = stod(line.substr(0, pos));
            line = line.substr(pos+1);
            pos = line.find(" ");
            double g = stod(line.substr(0, pos));
            line = line.substr(pos+1);
            pos = line.find(" ");
            double b = stod(line.substr(0, pos));
            line = line.substr(pos + 1);
            double gray = (r+g+b)/3;
            board.push_back(gray);
            red.push_back(int(r));
            green.push_back(int(g));
            blue.push_back(int(b));
        }
    }

    //std::cout<<"Finished reading in file"<<std::endl;

    vector<int> boardx;
    vector<int> boardy;
    vector<double> G;
    vector<double> angles;
    vector<int> maxS;

    for(int i = 0; i < h; i++){
        for(int j = 0; j < w; j++){
            int val1 = (i-1)*(w)+(j-1);
            int val2 = (i-1)*(w)+(j+1);
            int val3 = (i)*(w)+(j-1);
            int val4 = (i)*(w)+(j+1);
            int val5 = (i+1)*(w)+(j-1);
            int val6 = (i+1)*(w)+(j+1);

            double temp = 0;

            if(i != 0){
                if(j != 0){
                    temp += -1*board.at(val1);
                }
                if(j != w-1){
                    temp += board.at(val2);
                }
            }
            if(i != h-1){
                if(j != 0){
                    temp += -1*board.at(val5);
                }
                if(j != w-1){
                    temp += board.at(val6);
                }
            }
            if(j != 0){
                temp += - 2*board.at(val3);
            }
            if(j != w-1){
                temp += 2*board.at(val4);
            }

            boardx.push_back(temp);

            val1 = (i-1)*(w)+(j-1);
            val2 = (i-1)*(w)+(j);
            val3 = (i-1)*(w)+(j+1);
            val4 = (i+1)*(w)+(j-1);
            val5 = (i+1)*(w)+(j);
            val6 = (i+1)*(w)+(j+1);

            double temp2 = 0;

            if(i != 0){
                if(j != 0){
                    temp2 += -1*board.at(val1);
                }
                if(j != w-1){
                    temp2 += -1*board.at(val3);
                }
                temp2 += -2*board.at(val2);
            }
            if(i != h-1){
                if(j != 0){
                    temp2 += board.at(val4);
                }
                if(j != w-1){
                    temp2 += board.at(val6);
                }
                temp2 += 2*board.at(val5);
            }
            boardy.push_back(temp2);
            double ang = 0.0;
            if(temp == 0.0){
                ang = 0.0;
            }
            else{
                ang = temp2/temp;
            }
            //std::cout << ang << std::endl;
            G.push_back(sqrt(temp*temp + temp2*temp2));
            angles.push_back(atan(ang)*180/PI);
        }
    }
    //std::cout<<"Finished making G and angles"<<std::endl;

    double threshold = 0.0;
    for(int i = 0; i < h; i++){
        for(int j = 0; j < w; j++){
            int point = (i)*(w)+j;
            threshold += board.at(point);
        }
    }

    //std::cout<<"Finished making threshold"<<std::endl;

    threshold /= w*h;
    int threshold2 = int(threshold * 1.2);
    threshold *= 0.285;
    int t = int(threshold);

    vector<int> hysth;

    for(int i = 0; i < h; i++){
        for(int j = 0; j < w; j++){
            int point = (i)*(w)+j;
            if(point%w == 0 || point%w == w-1 || point/w == 0 || point/w == h-1){
                hysth.push_back(0);
            }
            else if(G.at(point) < t){
                hysth.push_back(0);
            }
            else if(G.at(point) < threshold2 && G.at(point) >= t){
                hysth.push_back(1);
            }
            else if(G.at(point) >= threshold2){
                hysth.push_back(2);
            }
            double a = angles.at(point);
            if((a > -22.5 && a <=0) || (a>= 0 && a < 22.5) || (a < -157.5 && a >=-180) || (a > 157.5 && a <= 180) || int(a) == -180 || int(a) == 180){
                //cout << "1" << endl;
                bool big = true;
                int t = point-1;
                int t2 = point+1;
                if(t >= 0 && point%w != 0){
                    if(G.at(point) <= G.at(t)){
                        big = false;
                    }
                }
                if(t2 < w*h && point%w != w-1){
                    if(G.at(point) <= G.at(t2)){
                        big = false;
                    }
                }
                if(big == true){
                    maxS.push_back(1);
                }
                else{
                    maxS.push_back(0);
                }
            }
            else if((a <= 67.5 && a >= 22.5) || (a >= -157.5 && a <= -112.5)){
                //cout << "2" << endl;
                bool big = true;
                int t = point-w-1;
                int t2 = point+w+1;
                if(t >= 0 && point%w != 0){
                    if(G.at(point) <= G.at(t)){
                        big = false;
                    }
                }
                if(t2 < w*h && point%w != w-1){
                    if(G.at(point) <= G.at(t2)){
                        big = false;
                    }
                }
                if(big == true){
                    maxS.push_back(1);
                }
                else{
                    maxS.push_back(0);
                }
            }
            else if((a < 112.5 && a > 67.5) || (a > -112.5 && a < -67.5)){
                //cout << "3" << endl;
                bool big = true;
                int t = point-w;
                int t2 = point+w;
                if(t >= 0){
                    if(G.at(point) <= G.at(t)){
                        big = false;
                    }
                }
                if(t2 < w*h){
                    if(G.at(point) <= G.at(t2)){
                        big = false;
                    }
                }
                if(big == true){
                    maxS.push_back(1);
                }
                else{
                    maxS.push_back(0);
                }
            }
            else if((a <= 157.5 && a >= 112.5) || (a <= -22.5 && a >= -67.5)){
                //cout << "4" << endl;
                bool big = true;
                int t = point-(w)+1;
                int t2 = point+(w-1);
                if(t >= 0 && point%w != w-1){
                    //cout << t << endl;
                    if(G.at(point) <= G.at(t)){
                        big = false;
                    }
                }
                if(t2 < w*h && point%w != 0){
                    //cout << t2 << endl;
                    if(G.at(point) <= G.at(t2)){
                        big = false;
                    }
                }
                if(big == true){
                    maxS.push_back(1);
                }
                else{
                    maxS.push_back(0);
                }
            }
            else{
                cout<<a<<endl;
            }
        }
    }

    //std::cout<<"Finished making hystheresis and non max suppression"<<std::endl;

    vector<int> indexes;
    vector<int> votes;

    for(int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            int point = i*w+j;
            if(hysth.at(point) == 2){
                indexes.push_back(point);
            }
            votes.push_back(0);
        }
    }

    for(int i = 0; i < indexes.size(); i++){
        area_fill(hysth, w, h, indexes.at(i));
    }
    //std::cout<<"Finished area fill"<<std::endl;

    bool done = false;
    for(int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            int point = i*w+j;
            if(maxS.at(point) == 1 && hysth.at(point) == 2) {
                double a = angles.at(point);
                double s = tan(a*PI/180) * -1;

                double x1 = i;
                double x2 = i;
                double y1 = j;
                double y2 = j;
                while (x1 < h - abs(s) && x1 > abs(s) && y1 < w - 1 && y1 > 1) {
                    x1 += s;
                    y1 -= 1;
                }
                while (x2 < h - abs(s) && x2 > abs(s) && y2 < w - 1 && y2 > 1) {
                    x2 -= s;
                    y2 += 1;
                }

                bresenham(int(x1), int(y1), i, j, votes, w, h);
                bresenham(int(x2), int(y2), i, j, votes, w, h);
            }
        }
    }

    //std::cout<<"Finished votes"<<std::endl;

    vector<int> centers;

    int max = 0;
    for(int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            int point = i*w+j;
            if(votes.at(point) > max){
                max= votes.at(point);
            }
            centers.push_back(0);
        }
    }
    //std::cout<<max<<std::endl;

    int temp = 0;
    //int val = 4000;
    for(int i = 5; i < h-5; i++) {
        for (int j = 5; j < w-5; j++) {
            int point = i*w+j;
//            double sum = 0;
//            double sum2 = 0;
//            for(int x = -3; x < 4; x++){
//                for(int y = -3; y < 4; y++){
//                    sum += votes.at(point + (x*w + y));
//                }
//            }
//            for(int x = -5; x < 6; x++){
//                for(int y = -5; y < 6; y++){
//                    sum2 += votes.at(point + (x*w + y));
//                    if(abs(x) <= 3 && abs(y) <= 3){
//                        sum += votes.at(point + (x*w + y));
//                    }
//                }
//            }
            if(votes.at(point) >= int(max/2)){
                //std::cout << point << std::endl;
                temp += 1;
                circle(i,j,1, centers, 1, h, w);
                circle(i,j,2, centers, 1, h, w);
                circle(i,j,3, centers, 1, h, w);
                circle(i,j,4, centers, 1, h, w);
                circle(i,j,5, centers, 1, h, w);
            }
        }
    }
    //std::cout<<val<<std::endl;

    std::cout<<temp<<std::endl;

    using namespace std;
    ofstream ofs("imagev.ppm", ios_base::out | ios_base::binary);
    ofs << "P3" << endl << w << ' ' << h << endl << max << endl;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            int point = i*w+j;
            if(votes.at(point) == max){
                ofs << votes.at(point) << " " << 0 << " " << 0 << " ";
            }
            else{
                ofs << votes.at(point) << " " << votes.at(point) << " " << votes.at(point) << " ";
            }
        }
        ofs << "\n";
    }
    ofs.close();

    using namespace std;
    ofstream ofs2("imageCC.ppm", ios_base::out | ios_base::binary);
    ofs2 << "P3" << endl << w << ' ' << h << endl << "255" << endl;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            int point = i*w+j;
            if(centers.at(point) == 0){
                ofs2 << red.at(point) << " " << green.at(point) << " " << blue.at(point) << " ";
            }
            else{
                ofs2 << 255 << " " << 0 << " " << 0 << " ";
            }
        }
        ofs2 << "\n";
    }
    ofs2.close();

    using namespace std;
    ofstream ofs3("imagef.ppm", ios_base::out | ios_base::binary);
    ofs3 << "P3" << endl << w << ' ' << h << endl << "1" << endl;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            int point = i*w+j;
            if(maxS.at(point) == 1 && hysth.at(point) == 2) {
                ofs3 << 1 << " " << 1 << " " << 1 << " ";
            }
            else{
                ofs3 << 0 << " " << 0 << " " << 0 << " ";
            }
        }
        ofs3 << "\n";
    }
    ofs3.close();
}

int main() {
    part1();
}