#ifndef TC_READER_H
#define TC_READER_H

#include <bits/stdc++.h>
using namespace std;

class tc_reader {
private:
    FILE *f;

    bool is_space(int);
    void verify();
public:
    tc_reader(void) : f(NULL) { }
    tc_reader(string input_file) : f(NULL) { this->connect(input_file); }
    ~tc_reader() { this->disconnect(); }

    bool connect(string);
    bool reconnect(string);
    bool disconnect();

    int read_int();
    char read_char();
    float read_float();
    double read_double();
    long double read_long_double();
    string read_string();
    void read_cstring(char *, int = 256);

    string read_line(void);

    void read_array(vector<int>&);
    void read_array(vector<float>&);
    void read_array(vector<double>&);
    void read_array(vector<long double>&);
    void read_array(vector<string>&);

    void skip_token(void);
    void skip_array(void);
    void skip_line(void);
};

#endif
