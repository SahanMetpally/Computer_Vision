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

void part2(){
    std::ifstream infile;
    infile.open("easy.ppm");
    std::string line = "";
    getline(infile,line);
    getline(infile,line);
    int pos = line.find(" ");
    const int w = stoi(line.substr(0,pos));
    const int h = stoi(line.substr(pos+1));
    getline(infile,line);

    vector<double> board;
    std::cout<<"Easy";
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
        }
    }
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

            int temp = 0;

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

            int temp2 = 0;

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
            G.push_back(sqrt(temp*temp + temp2*temp2));
            angles.push_back(atan(ang)*180/PI);
        }
    }
    double threshold = 0.0;
    for(int i = 0; i < h; i++){
        for(int j = 0; j < w; j++){
            int point = (i)*(w)+j;
            threshold += board.at(point);
        }
    }
    threshold /= w*h;
    int threshold2 = int(threshold * 1.4);
    threshold *= 0.5;
    int t = int(threshold);

    vector<int> hysth;

    for(int i = 0; i < h; i++){
        for(int j = 0; j < w; j++){
            int point = (i)*(w)+j;
            if(G.at(point) < t){
                hysth.push_back(0);
            }
            if(G.at(point) < threshold2 && G.at(point) >= t){
                hysth.push_back(1);
            }
            if(G.at(point) >= threshold2){
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
                if(big){
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
                if(big){
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
                if(big){
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
                if(big){
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
    vector<int> indexes;
    for(int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            int point = i*w+j;
            if(hysth.at(point) == 2){
                indexes.push_back(point);
            }
        }
    }
    for(int i = 0; i < indexes.size(); i++){
        area_fill(hysth, w, h, indexes.at(i));
    }

    using namespace std;
    ofstream ofs("image2.ppm", ios_base::out | ios_base::binary);
    ofs << "P3" << endl << w << ' ' << h << endl << "1" << endl;

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            int point = i*w+j;
            //cout << hysth.at(point) << " ";
            if (hysth.at(point) == 2) {
                ofs << 1 << " " << 1 << " " << 1 << " ";
                //cout << G.at(point) << " ";
            }
            else if(hysth.at(point) == 0 || hysth.at(point) == 1){
                ofs << 0 << " " << 0 << " " << 0 << " ";
                //cout << G.at(point) << " ";
            }
        }
        ofs << "\n";
    }
    ofs.close();

    using namespace std;
    ofstream ofs2("circle.ppm", ios_base::out | ios_base::binary);
    ofs2 << "P3" << endl << w << ' ' << h << endl << "1" << endl;

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            int point = i*w+j;
            if(maxS.at(point) == 1) {
                ofs2 << 1 << " " << 1 << " " << 1 << " ";
            }
            if(maxS.at(point) == 0) {
                ofs2 << 0 << " " << 0 << " " << 0 << " ";
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
    part2();
}