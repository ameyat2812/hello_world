// A simple program that stores the data in spreadsheet and prits it
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

/*Abstract base class for any type of data, can be a 
extended to a phone number, date etc*/
class Glyph {
public:
    virtual void Print() const = 0;
    virtual ~Glyph() {};
};

/*Represents an empty cell*/
class Empty : public Glyph {
public:
    virtual void Print() const {
    }
};

/*For storing texual data*/
class Text : public Glyph {
public:
    Text(const string &text) : text_(text) {}
    virtual ~Text() {}
    virtual void Print() const { cout << text_; }

private:
    string text_;
};

/*This represents an int number*/
class Number : public Glyph {
public:
    Number(const int &value) : value_(value) {}
    virtual ~Number() {}
    virtual void Print() const { cout << value_; }

private:
    int value_;
};

/*Composite of Glyph to store a two dimentional vector of Glyph* */
class Spreadsheet : public Glyph {
    
    /*To insert num empty elements before adding data at the end of the vector*/
    void InsertAfterEmptyElem(vector<Glyph*> &vec, unsigned int num, Glyph *data) {
        vec.insert(vec.end(), num, new Empty());
        vec.insert(vec.end(), data);
    }
    /*To insert num of empty vectors before adding a vector with data at the end of it*/
    void InsertAfterEmptyVector(vector<vector<Glyph*> > &vec_vec, unsigned int num, unsigned int col, Glyph *data) {
        vec_vec.insert(vec_vec.end(), num, vector<Glyph*>());
        vector<Glyph*> temp(col);
        temp[col - 1] = data;
        vec_vec.insert(vec_vec.end(), temp);

    }
public:
    Spreadsheet(const unsigned int rows, const unsigned int cols)
        : sheet_(rows, vector<Glyph*>(cols)) {
    }

    /*To add Glyph to the spreadsheet at desired row and col. Note that the row and col are not zero indexed.*/
    void Update(const unsigned int row, const unsigned int col, Glyph *data) {
        /*Reject 0 index*/
        if (!row || !col)
            return;
        
        /*Find if the row is already present*/
        bool row_found = false;
        unsigned int row_number = 0;
        for (auto &elem : sheet_) {
            row_number++;
            if (row_number == row) {
                row_found = true;
                break;
            }
        }
        if (row_found) {
            /*Find if the col is already present*/
            unsigned int col_number = 0;
            for (auto &elem : sheet_[row - 1]) {
                col_number++;
                if (col_number == col) {					
                    delete(elem);
                    elem = data;
                    return;
                }
            }
            /*If col is not present then add col - col_number - 1 empty glyphs before adding data*/
            InsertAfterEmptyElem(sheet_[row - 1], (col - col_number - 1), data);
            return;
        }
        else {
            /*If row not found then add (row - row_number - 1) empty rows and add data at col of last row*/
            InsertAfterEmptyVector(sheet_, (row - row_number - 1), col, data);
            return;
        }

    }
    /*Print the spreadsheet with every cell surrounded by '|'. They are printed with 
    the bars column aligned*/
    void Print(void) const {
        for (const auto &row : sheet_) {
            cout << "|";
            for (const auto &col : row) {
                if (col) {
                    cout.width(10);
                    col->Print();
                }
                else {
                    cout.width(11);
                }
                cout << '|';
            }
            cout << endl;
        }
    }

    /*Clear the stored data at once.*/
    void Clear(void) {
        for (auto &row : sheet_) {
            for (auto &col : row) {
                delete(col);
            }
            row.clear();
        }
        sheet_.clear();
    }
private:
    vector<vector<Glyph*> > sheet_;
};

int main(int argc, char *argv[]) {
    /*Add data at random row/col position and print at the end.*/
    auto spread_sheet = Spreadsheet(4, 3);
    spread_sheet.Update(1, 1, new Text("bob"));
    spread_sheet.Update(1, 2, new Number(10));
    spread_sheet.Update(2, 3, new Text("foo"));
    spread_sheet.Update(2, 1, new Text("alice"));
    spread_sheet.Update(4, 4, new Number(5));
    spread_sheet.Update(5, 7, new Text("total"));
    

    spread_sheet.Print();
    
    spread_sheet.Clear();
    /*Wait for user input before terminate.*/
    system("pause");
    exit(0);
}