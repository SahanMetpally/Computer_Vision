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

void part1(){
    std::ifstream infile;
    infile.open("image.ppm");
    std::string line = "";
    getline(infile,line);
    getline(infile,line);
    int pos = line.find(" ");
    const int w = stoi(line.substr(0,pos));
    const int h = stoi(line.substr(pos+1));
    getline(infile,line);

    vector<int> board;

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
            int gray = (r+g+b)/3;

            board.push_back(gray);
        }
    }

    vector<int> boardx;
    vector<int> boardy;
    vector<double> G;

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

            G.push_back(sqrt(temp*temp + temp2*temp2));
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
    threshold *= 1.6;
    int t = int(threshold);

    cout << G.at(0) << " ";

    using namespace std;
    ofstream ofs("imagem.ppm", ios_base::out | ios_base::binary);
    ofs << "P3" << endl << w << ' ' << h << endl << "1" << endl;

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            int point = i*w+j;
            if (G.at(point) < t) {
                ofs << 0 << " " << 0 << " " << 0 << " ";
                //cout << G.at(point) << " ";
            }
            else if(G.at(point) >= t){
                ofs << 1 << " " << 1 << " " << 1 << " ";
                //cout << G.at(point) << " ";
            }
        }
        ofs << "\n";
    }
    ofs.close();

    using namespace std;
    ofstream ofs2("imageg.ppm", ios_base::out | ios_base::binary);
    ofs2 << "P3" << endl << w << ' ' << h << endl << "255" << endl;

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            int point = i*w+j;
            ofs2 << board.at(point) << " " << board.at(point) << " " << board.at(point) << " ";
        }
        ofs2 << "\n";
    }
    ofs2.close();

}


int main() {
    part1();
}