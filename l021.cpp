#include <fstream>
#include <cstdio>
#include <iostream>
#include <math.h>
#include <iomanip>

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
void bresenham(int x1, int y1, int x2, int y2, int board[800][800], int col){
    //std::cout<< "hello";
    if(y2 < y1){
        int a = x1; x1 = x2; x2 = a;
        a = y1; y1 = y2; y2 = a;
    }
    int xs = y1, ys = 799 - x1, xe = y2, ye = 799 - x2;
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
    int di = errorX/2;
    while(xs != xe || ys != ye){
        if(board[799 - ys][xs] == 0) {
            board[799 - ys][xs] = col;
        }
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
}

double area(double x1, double y1, double x2, double y2, double x3, double y3){
    return abs(double((x1*(y2-y3) + x2*(y3-y1) + x3*(y1-y2))/2.0));
}
bool check(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4){
    double A = area(x1,y1,x2,y2,x3,y3);
    double A1 = area(x1,y1,x2,y2,x4,y4);
    double A2 = area(x1,y1,x3,y3,x4,y4);
    double A3 = area(x2,y2,x3,y3,x4,y4);
    double A4 = A1 + A2 + A3;
    if(A > A4 - 0.001 && A < A4 + 0.001){
        //std::cout << "Hello";
        return true;
    }
    //std::cout << A1 << " " << A4;
    return false;
    //return (A > (A1 + A2 + A3 - 0.0001) && A < (A1 + A2 + A3 + 0.0001));
}

void part1(){
    std::ofstream file ("points.txt");

    srand( time(NULL) );
    double x1 = (double) rand()/RAND_MAX;     double y1 = (double) rand()/RAND_MAX;
    double x2 = (double) rand()/RAND_MAX;     double y2 = (double) rand()/RAND_MAX;
    double x3 = (double) rand()/RAND_MAX;     double y3 = (double) rand()/RAND_MAX;
    double x4 = (double) rand()/RAND_MAX;     double y4 = (double) rand()/RAND_MAX;
    while(check(x1, y1, x2, y2, x3, y3, x4, y4)
    || check(x4, y4, x2, y2, x3, y3, x1, y1)
    || check(x1, y1, x4, y4, x3, y3, x2, y2)
    || check(x1, y1, x2, y2, x4, y4, x3, y3)){
        x4 = (double) rand()/RAND_MAX;     y4 = (double) rand()/RAND_MAX;
        //std::cout << x4 << " " << y4 << std::endl;
    }
    file << "(" << std::setprecision(17) << x1 << "," << std::setprecision(17) << y1 << ") , ";
    file << "(" << std::setprecision(17) << x2 << "," << std::setprecision(17) << y2 << ") , ";
    file << "(" << std::setprecision(17) << x3 << "," << std::setprecision(17) << y3 << ") , ";
    file << "(" << std::setprecision(17) << x4 << "," << std::setprecision(17) << y4 << ")";

    file.close();
}
double angle(double x1, double y1, double x2, double y2, double x3, double y3){
    double aX = sqrt((y2-y1)*(y2-y1) + (x2-x1)*(x2-x1));
    double bX = sqrt((y2-y3)*(y2-y3) + (x2-x3)*(x2-x3));
    double ab = sqrt((y3-y1)*(y3-y1) + (x3-x1)*(x3-x1));

    double angle = acos((aX*aX + bX*bX - ab*ab)/(2*aX*bX));

    return angle;
}

double Ldistance(double x1, double y1, double x2, double y2){
    return sqrt((y2-y1)*(y2-y1)+(x2-x1)*(x2-x1));
}
double yIntersect(double m1, double b1, double x){
    return (m1*x + b1);
}
double xIntersect(double m1, double b1, double m2, double b2){
    return ((b2-b1)/(m1-m2));
}
void draw(double x1, double y1, double x2, double y2, int board[800][800], int col) {
    if (x1 > x2) {
        draw(x2, y2, x1, y1, board, col);
    }
    else {
        float slopeE = float(y2 - y1) / float(x2 - x1);
        while (x2 < 1 && x2 > 0 && y2 < 1 && y2 > 0) {
            x2+= 0.00125;
            y2 += (slopeE/800);
        }
        while (x1 < 1 && x1 > 0 && y1 < 1 && y1 > 0) {
            x1-= 0.00125;
            y1 -= (slopeE/800);
        }
        //std::cout<< x1 << " " << y1 << " " << x2 << " " << y2 << std::endl;
        bresenham(int(y1*800), int(x1*800), int(y2*800), int(x2*800), board, col);
    }
}
void printSmallest(double Ax, double Ay, double Bx, double By, double Cx, double Cy, double Dx, double Dy, double points[6][8], double areas[6], int index){
    constexpr auto xSize = 800, ySize = 800;

    using namespace std;
    ofstream ofs("output.ppm", ios_base::out | ios_base::binary);
    ofs << "P3" << endl << xSize << ' ' << ySize << endl << "255" << endl;

    int board[xSize][ySize];

    for(int i = 0; i < xSize; i++){
        for(int j = 0; j < ySize; j++){
            board[i][j] = 0;
        }
    }

    board[int(Ay*800)][int(Ax*800)] = 1;
    board[int(By*800)][int(Bx*800)] = 1;
    board[int(Cy*800)][int(Cx*800)] = 1;
    board[int(Dy*800)][int(Dx*800)] = 1;

    circle(int(Ay*800), int(Ax*800), 2, board, 1);
    circle(int(By*800), int(Bx*800), 2, board, 1);
    circle(int(Cy*800), int(Cx*800), 2, board, 1);
    circle(int(Dy*800), int(Dx*800), 2, board, 1);
    double x1 = points[index][0];
    double y1 = points[index][1];
    double x2 = points[index][2];
    double y2 = points[index][3];
    double x3 = points[index][4];
    double y3 = points[index][5];
    double x4 = points[index][6];
    double y4 = points[index][7];

    circle(int(y1*800), int(x1*800), 5, board, 1);
    circle(int(y2*800), int(x2*800), 5, board, 1);
    circle(int(y3*800), int(x3*800), 5, board, 1);
    circle(int(y4*800), int(x4*800), 5, board, 1);

    draw(x1, y1, x2, y2, board, 1);
    draw(x1, y1, x3, y3, board, 1);
    draw(x4, y4, x3, y3, board, 1);
    draw(x4, y4, x2, y2, board, 1);

    for (int i = 0; i < xSize; i++) {
        for (int j = 0; j < ySize; j++) {
            if (board[i][j] == 0) {
                ofs << 255 << " " << 255 << " " << 255 << " ";
            }
            else if(board[i][j] == 1){
                ofs << 0 << " " << 0 << " " << 0 << " ";
            }
            else{
                ofs << 255 << " " << 0 << " " << 0 << " ";
            }
        }
        ofs << "\n";
    }
    ofs.close();
}
void printTxt(double Ax, double Ay, double Bx, double By, double Cx, double Cy, double Dx, double Dy, double points[6][8], double areas[6]){
    std::ofstream file;
    file.open("output.txt");
    file << "(" << std::setprecision(17) << Ax << "," << std::setprecision(17) << Ay << ") , ";
    file << "(" << std::setprecision(17) << Bx << "," << std::setprecision(17) << By << ") , ";
    file << "(" << std::setprecision(17) << Cx << "," << std::setprecision(17) << Cy << ") , ";
    file << "(" << std::setprecision(17) << Dx << "," << std::setprecision(17) << Dy << ")" << std::endl;

    for(int i = 0; i < 6; i++){
        file << "(" << std::setprecision(17) << points[i][0] << "," << std::setprecision(17) << points[i][1] << ") , ";
        file << "(" << std::setprecision(17) << points[i][2] << "," << std::setprecision(17) << points[i][3] << ") , ";
        file << "(" << std::setprecision(17) << points[i][4] << "," << std::setprecision(17) << points[i][5] << ") , ";
        file << "(" << std::setprecision(17) << points[i][6] << "," << std::setprecision(17) << points[i][7] << ") Area = " << std::setprecision(17) << areas[i] << std::endl;
    }
    file.close();
}
void squareSolver(double Ax, double Ay, double Bx, double By, double Cx, double Cy, double Dx, double Dy, double Ex, double Ey, int index, double points[6][8], double areas[6]){
    double m = (Ey-Dy)/(Ex-Dx);
    double b = Dy - m*Dx;

    double m1 = -1/m;
    double b1 = Ay - m1*Ax;

    double m2 = -1/m;
    double b2 = Cy - m2*Cx;

    double m3 = m;
    double b3 = By - m3*Bx;

    double x1 = xIntersect(m,b,m1,b1);
    double y1 = yIntersect(m,b,x1);

    double x2 = xIntersect(m,b,m2,b2);
    double y2 = yIntersect(m,b,x2);

    double x3 = xIntersect(m1,b1,m3,b3);
    double y3 = yIntersect(m1,b1,x3);

    double x4 = xIntersect(m2,b2,m3,b3);
    double y4 = yIntersect(m2,b2,x4);

//    std::cout<< index << std::endl;
//    std::cout << x1 << " " << y1 << std::endl;
//    std::cout << x2 << " " << y2 << std::endl;
//    std::cout << x3 << " " << y3 << std::endl;
//    std::cout << x4 << " " << y4 << std::endl;

    double area = Ldistance(x1,y1,x2,y2)*Ldistance(x1,y1,x2,y2);

//    std::cout<< area << std::endl;
    areas[index] = area;
    points[index][0] = x1;
    points[index][1] = y1;
    points[index][2] = x2;
    points[index][3] = y2;
    points[index][4] = x3;
    points[index][5] = y3;
    points[index][6] = x4;
    points[index][7] = y4;
}
void solve(double Ax, double Ay, double Bx, double By, double Cx, double Cy, double Dx, double Dy, int index, double points[6][8], double areas[6]) {
    double t1 = Ay - Cy;
    double t2 = Ax - Cx;
    double E1x = Bx + (t1);
    double E1y = By - (t2);

    double E2x = Bx - (t1);
    double E2y = By + (t2);

    squareSolver(Ax, Ay, Bx, By, Cx, Cy, Dx, Dy, E1x, E1y, index, points, areas);
    squareSolver(Ax, Ay, Bx, By, Cx, Cy, Dx, Dy, E2x, E2y, index+1, points, areas);
}
int getLength(std::string line, int start){
    int size = 0;
    for(int i = start; i < line.length(); i++){
        if(isdigit(line[i]) || line[i]=='.'){
            size ++;
        }
        else{
            break;
        }
    }
    return size;
}
void part2(){
    std::ifstream infile;
    infile.open("points.txt");
    std::string line = "";
    (getline(infile, line));
    int size = getLength(line, 1);
    int start = 1;
    double x1 = std::stod (line.substr(1,size));
    start = start + size+1;
    size = getLength(line, start);
    double y1 = std::stod (line.substr(start,size));
    start = start + size + 6;
    size = getLength(line, start);
    double x2 = std::stod (line.substr(start,size));
    start = start + size + 1;
    size = getLength(line, start);
    double y2 = std::stod (line.substr(start,size));
    start = start + size + 6;
    size = getLength(line, start);
    double x3 = std::stod (line.substr(start,size));
    start = start + size + 1;
    size = getLength(line, start);
    double y3 = std::stod (line.substr(start,size));
    start = start + size + 6;
    size = getLength(line, start);
    double x4 = std::stod (line.substr(start,size));
    start = start + size + 1;
    size = getLength(line, start);
    double y4 = std::stod (line.substr(start,size));

    double points [6][8] = {};
    double areas [6] = {};

    solve(x1,y1,x2,y2,x3,y3,x4,y4,0, points, areas);
    solve(x1,y1,x3,y3,x2,y2,x4,y4,2, points, areas);
    solve(x2,y2,x1,y1,x3,y3,x4,y4,4, points, areas);

    printTxt(x1,y1,x2,y2,x3,y3,x4,y4, points, areas);
    int minIndex = 0;
    for(int i = 0; i < 6; i++){
        if(areas[i] < areas[minIndex]){
            minIndex = i;
        }
    }
    printSmallest(x1,y1,x2,y2,x3,y3,x4,y4,points,areas,minIndex);
}
int main() {
    part1();
    //part2();
}
