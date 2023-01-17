#include <fstream>
#include <cstdio>
#include <iostream>
#include <math.h>

void bresenham(int x1, int y1, int x2, int y2, int board[800][800], int col){
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
int main() {
    constexpr auto xSize = 800, ySize = 800;

    using namespace std;
    ofstream ofs("triangle.ppm", ios_base::out | ios_base::binary);
    ofs << "P3" << endl << xSize << ' ' << ySize << endl << "255" << endl;

    int board[xSize][ySize];
    srand( time(NULL) );
    int x1 = rand() % 800; int y1 = rand() % 800; int x2 = rand() % 800; int y2 = rand() % 800; int x3 = rand() % 800; int y3 = rand() % 800;
    for(int i = 0; i < xSize; i++){
        for(int j = 0; j < ySize; j++){
            board[i][j] = 0;
        }
    }
    board[x1][y1] = 1;     board[x2][y2] = 1;    board[x3][y3] = 1;
    //std::cout << " (" << x1 << " " << y1 << ") (" << x2 << " " << y2 << ") (" << x3 << " " << y3 << ")" << std:: endl;
    //board[100][100] = 255;     board[500][700] = 255;    board[200][300] = 255;board[700][500] = 255;
        bresenham(x1, y1, x2, y2, board, 1);
        bresenham(x2, y2, x3, y3, board, 1);
        bresenham(x1, y1, x3, y3, board, 1);
        float ab = sqrt((y2-y1)*(y2-y1) + (x2-x1)*(x2-x1));
        float bc = sqrt((y2-y3)*(y2-y3) + (x2-x3)*(x2-x3));
        float ac = sqrt((y3-y1)*(y3-y1) + (x3-x1)*(x3-x1));
        int p = ab + bc + ac;
        int incenterX = (ab*x3 + ac*x2 + bc*x1)/p;
        int incenterY = (ab*y3 + ac*y2 + bc*y1)/p;
        //std::cout << x1 << ", " << y1 << " " << x2 << ", " << y2 << " " << incenterX << " " << incenterY << " ";
        board[incenterX][incenterY] = 255;
        int a = y2 - y1;
        int b = x1 - x2;
        int c = -1*(a*(x1) + b*(y1));
        float r = float(abs(a*incenterX + b*incenterY + c))/float(sqrt(a*a + b*b));
        //std::cout << a << " " << b << " " << c << " " << r;
        circle(incenterX, incenterY, r, board, 2);
        //std::cout << ab <<  " " << bc << " " << ac << " "<< std:: endl;
        float A = acos((ab*ab + ac*ac - bc*bc)/(2*ab*ac));
        float B = acos((ab*ab + bc*bc - ac*ac)/(2*ab*bc));
        float C = acos((bc*bc + ac*ac - ab*ab)/(2*bc*ac));
        int circumcenterX = int((x1*sin(2*A) + x2*sin(2*B) + x3*sin(2*C))/(sin(2*A) + sin(2*B) + sin(2*C)));
        int circumcenterY = int((y1*sin(2*A) + y2*sin(2*B) + y3*sin(2*C))/(sin(2*A) + sin(2*B) + sin(2*C)));

        int circumR = sqrt((x1 - circumcenterX)*(x1 - circumcenterX) + (y1 - circumcenterY)*(y1 - circumcenterY));
        board[circumcenterX][circumcenterY] = 255;
        //std::cout << A << " " << B << " " << C << " " << circumcenterX << " " << circumcenterY << " " << circumR;
        circle(circumcenterX, circumcenterY, circumR, board, 3);

        int centroidX = (x1 + x2 + x3)/3;
        int centroidY = (y1 + y2 + y3)/3;

        float temp1 = circumcenterY; float temp2 = 799 - circumcenterX; float temp3 = centroidY; float temp4 = 799 - centroidX;
        if(temp1 > temp3){
            float a = temp1; temp1 = temp3; temp3 = a;
            a = temp2; temp2 = temp4; temp4 = a;
        }
        float slopeE = float(temp4 - temp2)/float(temp3 - temp1);
        while(temp3 < 800 && temp3 > 0 && temp4 < 800 && temp4 > 0){
            temp3++;
            temp4 += slopeE;
        }
        while(temp1 < 800 && temp1 > 0 && temp2 < 800 && temp2 > 0){
            temp1--;
            temp2 -= slopeE;
        }
        //std::cout << centroidX << " " << centroidY << " " << circumcenterX << " " << circumcenterY << " " << slopeE;
        //bresenham(circumcenterX, circumcenterY, centroidX, centroidY,board, 1);

        bresenham(int(799 - temp2), int(temp1), int(799 - temp4), int(temp3),board, 5);

        int x12 = (x1+x2)/2;
        int y12 = (y1+y2)/2;
        int x23 = (x3+x2)/2;
        int y23 = (y3+y2)/2;
        int x13 = (x1+x3)/2;
        int y13 = (y1+y3)/2;

        ab = sqrt((y23-y12)*(y23-y12) + (x23-x12)*(x23-x12));
        bc = sqrt((y23-y13)*(y23-y13) + (x23-x13)*(x23-x13));
        ac = sqrt((y13-y12)*(y13-y12) + (x13-x12)*(x13-x12));

        A = acos((ab*ab + ac*ac - bc*bc)/(2*ab*ac));
        B = acos((ab*ab + bc*bc - ac*ac)/(2*ab*bc));
        C = acos((bc*bc + ac*ac - ab*ab)/(2*bc*ac));
        circumcenterX = int((x12*sin(2*A) + x23*sin(2*B) + x13*sin(2*C))/(sin(2*A) + sin(2*B) + sin(2*C)));
        circumcenterY = int((y12*sin(2*A) + y23*sin(2*B) + y13*sin(2*C))/(sin(2*A) + sin(2*B) + sin(2*C)));

        circumR = sqrt((x12 - circumcenterX)*(x12 - circumcenterX) + (y12 - circumcenterY)*(y12 - circumcenterY));
        board[circumcenterX][circumcenterY] = 255;
        circle(circumcenterX, circumcenterY, circumR, board, 4);


    for (int i = 0; i < xSize; i++) {
        for (int j = 0; j < ySize; j++) {
            if (board[i][j] == 0) {
                ofs << 0 << " " << 0 << " " << 0 << " ";
            }
            else if(board[i][j] == 1){
                ofs << 255 << " " << 255 << " " << 255 << " ";
            }
            else if(board[i][j] == 2){
                ofs << 0 << " " << 255 << " " << 0 << " ";
            }
            else if(board[i][j] == 3){
                ofs << 0 << " " << 0 << " " << 255 << " ";
            }
            else if(board[i][j] == 4){
                ofs << 125 << " " << 125 << " " << 0 << " ";
            }
            else{
                ofs << 255 << " " << 0 << " " << 0 << " ";
            }
        }
        ofs << "\n";
    }
    ofs.close();

    return EXIT_SUCCESS;
}
