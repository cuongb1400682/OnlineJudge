#include "tc_reader.h"

bool tc_reader::is_space(int c) {
    return c == ',' || c == '{' || c == '}' || isspace(c) || c == '"';
}

bool tc_reader::connect(string input_file) {
    if(f != NULL)
        throw string("File has already been opened");
    return ((f = fopen(input_file.c_str(),"rt"))) != NULL;
}

bool tc_reader::disconnect() {
    bool ans = true;
    if(f != NULL) {
        ans = fclose(f);
        f = NULL;
    }
    return ans;
}

bool tc_reader::reconnect(string new_input_file) {
    if (!this->disconnect())
        return false;
    else
        return this->connect(new_input_file);
}

void tc_reader::verify() {
    if (f == NULL)
        throw string("No file has been connected yet.\n"
                "Please call tc_reader::connect(input) to open a file.");
}

int tc_reader::read_int() {
    verify();
    int c;
    while(is_space(c = read_char()))
        ;
    ungetc(c,f);
    if(fscanf(f, "%d", &c) == EOF)
        throw string("Reached the end of file");
    return c;
}

char tc_reader::read_char() {
    verify();
    int c;
    if((c = fgetc(f)) == EOF)
        throw string(string("Reached the end of file"));
    return (char) c;
}

float tc_reader::read_float() {
    verify();
    char c;
    float ans;
    while(is_space(c = read_char()))
        ;
    ungetc(c,f);
    if(fscanf(f, "%f", &ans) == EOF)
        throw string("Reached the end of file");
    return ans;
}

double tc_reader::read_double() {
    verify();
    char c;
    double ans;
    while(is_space(c = read_char()))
        ;
    ungetc(c,f);
    if(fscanf(f, "%lf", &ans) == EOF)
        throw string("Reached the end of file");
    return ans;
}

long double tc_reader::read_long_double() {
    verify();
    char c;
    long double ans;
    while(is_space(c = read_char()))
        ;
    ungetc(c,f);
    if(fscanf(f, "%Lf", &ans) == EOF)
        throw string("Reached the end of file");
    return ans;
}

string tc_reader::read_line(void) {
    verify();
    if(feof(f))
        throw string("Reached the end of file");
    string ans = "";
    int c;
    while((c = fgetc(f)) != '\n' && c != '\r' && c != EOF)
        ans.push_back((char)c);
    return ans;
}

string tc_reader::read_string() {
    verify();
    string ans = "";
    char c;
    while((c = read_char()) != '"')
        ;
    while((c = read_char()) != '"')
        ans.push_back(c);
    return ans;
}

void tc_reader::read_array(vector<int>& a) {
    verify();
    a.clear();
    char c;
    while((c = read_char()) != '{')
        ;
    for(bool stop = false; !stop; ) {
        while(is_space(c = read_char()))
            if(c == '}') {
                stop = true;
                break;
            }
        if (!stop) {
            ungetc(c,f);
            a.push_back(read_int());
        }
    }
}

void tc_reader::read_array(vector<float>& a) {
    verify();
    a.clear();
    char c;
    while((c = read_char()) != '{')
        ;
    for(bool stop = false; !stop; ) {
        while(is_space(c = read_char()))
            if(c == '}') {
                stop = true;
                break;
            }
        if (!stop) {
            ungetc(c,f);
            a.push_back(read_float());
        }
    }
}

void tc_reader::read_array(vector<double>& a) {
    verify();
    a.clear();
    char c;
    while((c = read_char()) != '{')
        ;
    for(bool stop = false; !stop; ) {
        while(is_space(c = read_char()))
            if(c == '}') {
                stop = true;
                break;
            }
        if (!stop) {
            ungetc(c,f);
            a.push_back(read_double());
        }
    }
}

void tc_reader::read_array(vector<long double>& a) {
    verify();
    a.clear();
    char c;
    while((c = read_char()) != '{')
        ;
    for(bool stop = false; !stop; ) {
        while(is_space(c = read_char()))
            if(c == '}') {
                stop = true;
                break;
            }
        if (!stop) {
            ungetc(c,f);
            a.push_back(read_long_double());
        }
    }
}

void tc_reader::read_array(vector<string>& a) {
    verify();
    a.clear();
    char c;
    while((c = read_char()) != '{')
        ;
    for(bool stop = false; !stop; ) {
        while(is_space(c = read_char())) {
            if(c == '}') {
                stop = true;
                break;
            }
            if(c == '"')
                break;
        }
        if (!stop) {
            ungetc(c,f);
            a.push_back(read_string());
        }
    }
}

void tc_reader::skip_token(void) {
    verify();
    char c;
    while(is_space(c = read_char()) && c != '"')
        ;
    if (c == '"') {
        while((c = read_char()) != '"')
            ;
    } else {
        do {} while(!is_space(c = read_char()));
        ungetc(c,f);
    }
}

void tc_reader::read_cstring(char *s, int limit) {
    verify();
    char c;
    while((c = read_char()) != '"')
        ;
    while((c = read_char()) != '"' && limit--)
        *s++ = c;
    *s = '\0';
}

void tc_reader::skip_array(void) {
	verify();
    if(!feof(f)) {
        while(read_char() != '{')
            ;
        while(read_char() != '}')
            ;
    } else
        throw string("Reached the end of file");
}

void tc_reader::skip_line(void) {
	verify();
    if(!feof(f)) {
        int c;
        while((c = read_char()) != '\n')
            ;
    } else
        throw string("Reached the end of file");
}
