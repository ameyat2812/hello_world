// A simple program that computes the square root of a number
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;


class Glyph {
public:
	virtual void Print() const = 0;
	virtual ~Glyph() {};
};

class Empty : public Glyph {
public:
	virtual void Print() const {
	}
};

class Text : public Glyph {
public:
	Text(const string &text) : text_(text) {}
	virtual ~Text() {}
	virtual void Print() const { cout << text_; }

private:
	string text_;
};

class Value : public Glyph {
public:
	Value(const int &value) : value_(value) {}
	virtual ~Value() {}
	virtual void Print() const { cout << value_; }

private:
	int value_;
};

class Spreadsheet : public Glyph {

	void InsertAfterEmptyElem(vector<Glyph*> &vec, unsigned int num, Glyph *data) {
		vec.insert(vec.end(), num, new Empty());
		vec.insert(vec.end(), data);
	}
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

	void Update(const unsigned int row, const unsigned int col, Glyph *data) {
		if (!row || !col)
			return;

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
			unsigned int col_number = 0;
			for (auto &elem : sheet_[row - 1]) {
				col_number++;
				if (col_number == col) {					
					delete(elem);
					elem = data;
					return;
				}
			}
			InsertAfterEmptyElem(sheet_[row - 1], (col - col_number - 1), data);
			return;
		}
		else {
			InsertAfterEmptyVector(sheet_, (row - row_number - 1), col, data);
			return;
		}

	}

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
	auto spread_sheet = Spreadsheet(4, 3);
	spread_sheet.Update(1, 1, new Text("bob"));
	spread_sheet.Update(1, 2, new Value(10));
	spread_sheet.Update(2, 3, new Text("foo"));
	spread_sheet.Update(2, 1, new Text("alice"));
	spread_sheet.Update(4, 4, new Value(5));
	spread_sheet.Update(5, 7, new Text("total"));
	

	spread_sheet.Print();
	
	spread_sheet.Clear();
	system("pause");

}