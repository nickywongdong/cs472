//neat integer concatenation function found on stack overflow
//source: https://stackoverflow.com/questions/12700497/how-to-concatenate-two-integers-in-c

unsigned concatenate(unsigned x, unsigned y) {
    unsigned pow = 10;
    while(y >= pow)
        pow *= 10;
    return x * pow + y;        
}