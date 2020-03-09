# Spread Sheet
##Problem statement
Design a spreadsheet type data structure to store different types of data such as text, number, and print it on the console with grids clearly showing cells in the spreadsheet.

## The solution
The solution implements composite design pattern to create an Abstract base class to represent a Glyph and then mulpiple concrete classes of this Glyph as text, value etc. The Spreadsheet class itself is a composite of Glyph and can be used to form even more complicated tables.
