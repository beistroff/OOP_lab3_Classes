#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <time.h>
#include <math.h>
#include <clocale>
#define SIZE 20
#include <chrono>
#include <thread>

enum STATE {
    OK, BAD_INIT, BAD_DIV
};

using namespace std;

class Crosses {
private:
    char arr[3][3] = { ' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };
    bool player;
    char* player1 = new char(SIZE);
    char* player2 = new char(SIZE);
    bool status;
public:
    Crosses() : player(true), status(false) {}

    void startGame() {
        do {
            cout << "Enter name of the first player: ";
            cin >> player1;
            cout << "Enter name of the second player: ";
            cin >> player2;
        } while (!strcmp(player1, player2));
    }

    void showGrid() {
        cout << "       1    2    3" << endl;
        cout << "    ________________" << endl;
        cout << "  1 | " << 11 << " | " << 12 << " | " << 13 << " |" << endl;
        cout << "  2 | " << 21 << " | " << 22 << " | " << 23 << " |" << endl;
        cout << "  3 | " << 31 << " | " << 32 << " | " << 33 << " |" << endl;
        cout << endl;
    }

    void showGame() {
        cout << "\n" << "      1   2   3" << endl;
        cout << "    _____________" << endl;
        for (int i = 0; i < 3; i++) {
            cout << "  " << i + 1 << " | ";
            for (int j = 0; j < 3; j++) {
                cout << arr[i][j] << " | ";
            }
            cout << endl;
        }
    }

    void chooseCell() {
        int cell;
        while (true) {
            cout << endl;
            if (player) {
                cout << "  " << player1;
            }
            else {
                cout << "  " << player2;
            }
            cout << ", enter cell: ";

            cin >> cell;
            if (cell > 10 && cell < 34) {
                int i = cell / 10;
                int j = cell % 10;

                if (0 < j && j < 4) {
                    if (arr[i - 1][j - 1] != 'X' && arr[i - 1][j - 1] != 'O') {
                        if (player) {
                            arr[i - 1][j - 1] = 'X';
                        }
                        else {
                            arr[i - 1][j - 1] = 'O';
                        }
                        player = !player;
                        break;
                    }
                }
            }
            cout << "  Choose another cell: " << endl;
        }
    }

    bool checkStatus() {
        bool step = false;
        /*Here it's possible to make just a 3 or even 2 cycle, but we have only 8 winning combinations, so I do 8 if statement
        in order to see every single combination and be sure that it does works*/
        if (arr[0][0] == arr[0][1] && arr[0][1] == arr[0][2] && (arr[0][0] == 'X' || arr[0][0] == 'O')) {
            status = true;
            if (arr[0][0] == 'X') {
                step = true;
            }
        }
        else if (arr[1][0] == arr[1][1] && arr[1][1] == arr[1][2] && (arr[1][0] == 'X' || arr[1][0] == 'O')) {
            status = true;
            if (arr[1][0] == 'X') {
                step = true;
            }
        }
        else if (arr[2][0] == arr[2][1] && arr[2][1] == arr[2][2] && (arr[2][0] == 'X' || arr[2][0] == 'O')) {
            status = true;
            if (arr[2][0] == 'X') {
                step = true;
            }
        }
        else if (arr[0][0] == arr[1][0] && arr[1][0] == arr[2][0] && (arr[0][0] == 'X' || arr[0][0] == 'O')) {
            status = true;
            if (arr[0][0] == 'X') {
                step = true;
            }
        }
        else if (arr[0][1] == arr[1][1] && arr[1][1] == arr[2][1] && (arr[0][1] == 'X' || arr[0][1] == 'O')) {
            status = true;
            if (arr[0][1] == 'X') {
                step = true;
            }
        }
        else if (arr[0][2] == arr[1][2] && arr[1][2] == arr[2][2] && (arr[0][2] == 'X' || arr[0][2] == 'O')) {
            status = true;
            if (arr[0][2] == 'X') {
                step = true;
            }
        }
        else if (arr[0][0] == arr[1][1] && arr[1][1] == arr[2][2] && (arr[1][1] == 'X' || arr[1][1] == 'O')) {
            status = true;
            if (arr[1][1] == 'X') {
                step = true;
            }
        }
        else if (arr[0][2] == arr[1][1] && arr[1][1] == arr[2][0] && (arr[1][1] == 'X' || arr[1][1] == 'O')) {
            status = true;
            if (arr[1][1] == 'X') {
                step = true;
            }
        }

        if (status) {
            if (step) {
                cout << "\n  " << player1 << " win!" << endl;
            }
            else {
                cout << "\n  " << player2 << " win!" << endl;
            }
            return true;
        }
        else {
            bool draw = true;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (arr[i][j] != 'X' && arr[i][j] != 'O') {
                        draw = false;
                    }
                }
            }

            if (draw) {
                cout << "draw!";
                return true;
            }
        }
        return false;
    }
};

class Vector {
private:
    double* arr; // x y z
    int size = 3;
    int status;
    int const param;
    static int count;
public:
    Vector() : status(OK), param(0) {
        arr = new double[size];
        fill(arr, arr + size, 0);
        count++;
    }
    Vector(const Vector& s) : status(OK), param(0) {
        size = s.size;
        arr = new double[size];
        for (int i = 0; i < size; i++) arr[i] = s.arr[i];
        count++;
    }
    Vector& operator=(const Vector& s) {
        if (this == &s) return *this;
        if (size != s.size) {
            if (arr != nullptr) delete arr;
            size = s.size;
            arr = new double[size];
        }
        for (int i = 0; i < size; i++) {
            arr[i] = s.arr[i];
        }
        return *this;
    }
    Vector(double value) : param(0) {
        arr = new double[size];
        for (int i = 0; i < size; i++) {
            arr[i] = value;
        }
        status = OK;
        count++;
    }
    Vector(double* next);
    ~Vector() {
        count--;
        cout << "\n Current status of vector: " << status << endl;
        cout << " Vector delete" << endl;
    }
    int getState() {
        return status;
    }
    static int getCount() {
        if (count <= 0) cout << " There is no objects created ";
        return count;
    }
    Vector add(Vector& d);
    Vector minus(Vector& d);
    Vector divideShort(short num);
    Vector multiply(short num);
    void assignElem(int const param);
    void getElem();
    void input();
    void output();
    bool CompLessAll(Vector& s);
};

/*------------------------------------------------------*/
int Vector::count = 0;
Vector::Vector(double* next) : param(0) {
    arr = new double[size];
    if (next == nullptr) {
        status = BAD_INIT;
        arr[0] = 0; arr[1] = 0; arr[2] = 0;
    }
    else {
        arr[0] = next[0]; arr[1] = next[1]; arr[2] = next[2];
        status = OK;
    }
    count++;
}

Vector Vector::add(Vector& s) {
    Vector tmp;
    for (int i = 0; i < 3; i++) {
        tmp.arr[i] = arr[i] + s.arr[i];
    }
    return tmp;
}

Vector Vector::minus(Vector& m) {
    Vector tmp;
    for (int i = 0; i < 3; i++) {
        tmp.arr[i] = arr[i] - m.arr[i];
    }
    return tmp;
}

Vector Vector::divideShort(short num) {
    Vector tmp;
    if (num == 0) {
        tmp.status = BAD_DIV;
        cout << " Error divide \n";
        return *this;
    }
    for (int i = 0; i < 3; i++) {
        tmp.arr[i] = arr[i] / num;
    }
    return tmp;
}

Vector Vector::multiply(short num) {
    Vector tmp;
    if (num == 0) {
        tmp.status = BAD_DIV;
        cout << " Error multiply \n";
        return *this;
    }
    for (int i = 0; i < 3; i++) {
        tmp.arr[i] = arr[i] * num;
    }
    return tmp;
}

void Vector::assignElem(int const param) {
    srand(time(nullptr));
    int rndNum = rand() % 3;
    arr[rndNum] = param;
}

void Vector::getElem() {
    srand(time(nullptr));
    int rndNum = rand() % 3;
    cout << " Receive random element of array: " << arr[rndNum] << "\n";
}

void Vector::input() {
    cout << "\n Input element of vector(x, y, z): ";
    for (int i = 0; i < 3; i++) {
        cin >> arr[i];
    }
}

void Vector::output() {
    cout << " \nVector as array[x, y, z]:" << endl;
    for (int i = 0; i < 3; i++) {
        cout << " [" << i << "]: " << arr[i] << ", ";
    }
}

bool Vector::CompLessAll(Vector& s) {
    for (int i = 0; i < size; i++) {
        if (arr[i] < s.arr[i])
            return true;
    }
    return false;
}

void showSecondTaskVector() {
    using namespace std::this_thread; // sleep_for, sleep_until
    using namespace std::chrono; // nanoseconds, system_clock, seconds

    Vector emptyVector;
    Vector arrInput;
    arrInput.output();
    Vector initArrayOneParam(7.5);
    Vector objCopyInitArr(initArrayOneParam);
    double* v = nullptr, next[] = { 2.5, 0, 10 };
    Vector pointerArr(next);
    Vector anotherPointerArr(next);
    Vector getCount();

    cout << "\n Testing class Vector{}..." << endl;
    emptyVector.assignElem(3);
    emptyVector.getElem();
    emptyVector.output();
    initArrayOneParam.output();
    if (pointerArr.getState() != OK) cout << " Object pointer 1 = [0]: 0, [1]: 0, [2]: 0 \n"; //Here, I need to figure it out 
    pointerArr.output();
    if (anotherPointerArr.getState() != OK) cout << " Object pointer 1 = [0]: 0, [1]: 0, [2]: 0 \n";
    cout << "\n\n Quantity of created objects: " << Vector::getCount() << endl;

    arrInput.input();
    arrInput = arrInput.add(initArrayOneParam);
    arrInput.output();
    cout << "\n Quantity of created objects Vector before minus operation: " << Vector::getCount() << endl;
    sleep_for(nanoseconds(10));
    sleep_until(system_clock::now() + seconds(1));
    sleep_for(nanoseconds(10));
    sleep_until(system_clock::now() + seconds(1));
    arrInput = arrInput.minus(emptyVector);
    cout << "\n Quantity of created objects Vector after minus operation: " << Vector::getCount() << endl;
    arrInput.output();
    arrInput = arrInput.divideShort(2);
    sleep_for(nanoseconds(10));
    sleep_until(system_clock::now() + seconds(1));
    arrInput.output();
    arrInput = arrInput.multiply(10);
    sleep_for(nanoseconds(10));
    sleep_until(system_clock::now() + seconds(1));
    if (arrInput.getState() == STATE::BAD_DIV) cout << "BAD_DIV \n";
    arrInput.output();
    arrInput = arrInput.divideShort(0.0);
    sleep_for(nanoseconds(10));
    sleep_until(system_clock::now() + seconds(1));
    if (arrInput.getState() == STATE::BAD_DIV) cout << "BAD_DIV \n";
    arrInput.output();
    cout << "\n arrInput getState " << arrInput.getState() << endl;
    if (arrInput.CompLessAll(arrInput)) cout << "ObjCopy less than arrInput " << endl;
    cout << "End of testing... \n";
}

class TwoDimensionalArray {
private:
    long** arr;
    int row = 0;
    int col = 0;
    int state;
public:
    TwoDimensionalArray() : row(5), col(5), state(OK) {
        arr = new long* [row];
        for (int i = 0; i < col; i++)
            arr[i] = new long[col];

        for (int i = 0; i < row; i++)
            for (int j = 0; j < col; j++)
                arr[i][j] = 0;
    }
    TwoDimensionalArray(int n);
    TwoDimensionalArray(int n, int m, double value);
    TwoDimensionalArray(const TwoDimensionalArray& copy);
    TwoDimensionalArray& operator = (const TwoDimensionalArray& assign);
    ~TwoDimensionalArray() {
        cout << "\n Delete Two-dimensional array" << endl;
        if (arr) {
            delete[] arr;
        }
    }
    void assignElem(int n, int m, double const element);
    void receiveElem(int n, int m);
    void output();
    void input();
    TwoDimensionalArray add(const TwoDimensionalArray& add);
    TwoDimensionalArray minus(const TwoDimensionalArray& minus);
    TwoDimensionalArray muptiply(const TwoDimensionalArray&);
    TwoDimensionalArray divideOnScalar(const long scalar);
};

TwoDimensionalArray::TwoDimensionalArray(int n) : row(n), col(n), state(OK) {
    arr = new long* [n];
    for (int i = 0; i < n; i++)
        arr[i] = new long[n];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            arr[i][j] = 1;
        }
    }
}

TwoDimensionalArray::TwoDimensionalArray(int n, int m, double value) : row(n), col(m), state(OK) {
    arr = new long* [n];
    for (int i = 0; i < n; i++)
        arr[i] = new long[m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            arr[i][j] = value;
        }
    }
}

TwoDimensionalArray::TwoDimensionalArray(const TwoDimensionalArray& copy) : state(OK) {
    if (this == &copy) return;
    row = copy.row;
    col = copy.row;
    arr = new long* [row];
    for (int i = 0; i < col; i++)
        arr[i] = new long[col];

    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            arr[i][j] = copy.arr[i][j];
}

TwoDimensionalArray& TwoDimensionalArray::operator=(const TwoDimensionalArray& assign) {
    if (row != assign.row || col != assign.col) {
        for (int i = 0; i < row; i++) {
            delete[] arr[i];
        }
        delete[] arr;

        row = assign.row;
        col - assign.col;
        arr = new long* [row];
        for (int i = 0; i < row; i++)
            arr[i] = new long[col];
    }
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            arr[i][j] = assign.arr[i][j];
        }
    }
    return *this;
}

void TwoDimensionalArray::output() {
    cout << "\n        Matrix" << endl;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cout << " | " << arr[i][j];
        }
        cout << " |\n";
    }
}

void TwoDimensionalArray::input() {
    cout << "\n";
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cout << " Enter value arr[" << i << "][" << j << "]: ";
            cin >> arr[i][j];
        }
    }
}

void TwoDimensionalArray::assignElem(int n, int m, double const elem) {
    arr[n][m] = elem;
}

void TwoDimensionalArray::receiveElem(int n, int m) {
    cout << "\n Received element from matrix: a[" << n << "][" << m << "] = " << arr[n][m];
}

TwoDimensionalArray TwoDimensionalArray::add(const TwoDimensionalArray& add) {
    if (row == add.row && col == add.col) {
        TwoDimensionalArray temp(row, col, 0);

        for (int i = 0; i < temp.row; i++) {
            for (int j = 0; j < temp.col; j++) {
                temp.arr[i][j] = arr[i][j] + add.arr[i][j];
            }
        }
        return temp;
    }
    else {
        cout << "\n You can't add a matrix with different sizes!!!\n Return an empty matrix" << endl;
        TwoDimensionalArray emptyMatrix;
        return emptyMatrix;
    }
}

TwoDimensionalArray TwoDimensionalArray::minus(const TwoDimensionalArray& minus) {
    if (row == minus.row && col == minus.col) {
        TwoDimensionalArray temp(row, col, 0);

        for (int i = 0; i < temp.row; i++) {
            for (int j = 0; j < temp.col; j++) {
                temp.arr[i][j] = arr[i][j] - minus.arr[i][j];
            }
        }
        return temp;
    }
    else {
        cout << "\n You can't substract a matrix with different sizes!!!\n Return an empty matrix" << endl;
        TwoDimensionalArray emptyMatrix;
        return emptyMatrix;
    }
}

TwoDimensionalArray TwoDimensionalArray::muptiply(const TwoDimensionalArray& multiply) {
    if (col == multiply.row)
    {
        TwoDimensionalArray temp(row, multiply.col, 0);

        for (int i = 0; i < temp.row; i++) {
            for (int j = 0; j < temp.col; j++) {
                for (int ext = 0; ext < col; ext++) {
                    temp.arr[i][j] += arr[i][ext] * multiply.arr[ext][j];
                }

            }
        }
        return temp;
    }
    else {
        cout << "\n You can't mupltiply a matrix with different row sizes!!!\n Return an empty matrix" << endl;
        TwoDimensionalArray emptyMatrix;
        return emptyMatrix;
    }
}

TwoDimensionalArray TwoDimensionalArray::divideOnScalar(const long scalar) {
    if (scalar == 0) {
        state = BAD_INIT;
        cout << "\n state = " << state << endl;
        cout << "\n Bad initiallization. Can't divide on 0, because it returns empty Matrix with 0" << endl;
    }
    TwoDimensionalArray temp(row, col, 0);
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            temp.arr[i][j] += arr[i][j] / scalar;

    return temp;
}

/*------------------------------------------------------*/

void showFirstTaskTicTacToe() {
    Crosses ticTacToe;
    ticTacToe.startGame();
    while (true) {
        system("cls");
        ticTacToe.showGrid();
        ticTacToe.showGame();
        if (ticTacToe.checkStatus())
            break;
        ticTacToe.chooseCell();
    }
}

void showTwoDimensionalArray() {
    TwoDimensionalArray matrix;
    TwoDimensionalArray testMatrix;
    TwoDimensionalArray matrixNxN(3);
    TwoDimensionalArray matrixRowCol(3, 5, 10);
    TwoDimensionalArray additionForInstance(5, 5, 3.3);
    TwoDimensionalArray arrForMultiply(5, 5, 1);
    cout << "\n Empty matrix: " << endl;
    matrix.assignElem(2, 2, 5.5);      // assign element for arr[row][col]
    matrix.receiveElem(2, 2);          // means that we want to receive arr[row][col]
    matrix.output();
    cout << "\n The matrix with size NxN: " << endl;
    matrixNxN.output();
    matrixRowCol.assignElem(1, 3, -10);
    cout << "\n The matrix with size NxM and value: " << endl;
    matrixRowCol.output();
    matrixRowCol.receiveElem(1, 3);
    //testMatrix.input();
    testMatrix.assignElem(1, 2, -3.3);

    testMatrix = testMatrix.add(additionForInstance);
    cout << "\n Here we add matrices:" << endl;
    testMatrix.output();
    testMatrix = testMatrix.minus(additionForInstance);
    cout << "\n Here we substract matrices:" << endl;
    testMatrix.output();
    arrForMultiply.assignElem(1, 1, -5);
    additionForInstance = additionForInstance.muptiply(arrForMultiply);
    additionForInstance.output();
    additionForInstance = additionForInstance.divideOnScalar(3);
    additionForInstance.output();
    //cout << " Quantity of created objects: " << TwoDimensionalArray::getCount() << endl;

}

int showTask(int answerTask)
{
    switch (answerTask) {
    case 1:
        showFirstTaskTicTacToe();
        break;
    case 2:
        showSecondTaskVector();
        break;
    case 3:
        showTwoDimensionalArray();
        break;
    default:
        cout << "Try again!";
        break;
    }
    return answerTask;
}

int main() {
    int answer;
    cout << "Choose a task! Enter number from 1 to 3" << endl;
    cout << "    Main Menu  \n";
    cout << "    1.  Task 1  \n";
    cout << "    2.  Task 2  \n";
    cout << "    3.  Task 3  \n";

    do {
        cout << "\n    Enter: "; cin >> answer;
        showTask(answer);
    } while (answer <= 0 || answer > 3);

    return 0;
}