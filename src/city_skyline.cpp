#include <tuple>
#include <iostream>

using namespace std;

struct building {
    int left;
    int height;
    int right;

    building(int l, int h, int r){
        left=l;
        height=h;
        right=r;
    }
};

struct skyline_seg {
    int start;
    int height;

    skyline_seg(){};
    skyline_seg(int s, int h){
        start=s;
        height=h;
    }
};

struct skyline {
    int capacity;
    skyline_seg * segments;
    int size;

    ~skyline() { delete[] segments; }
    skyline(int c) {
        capacity = c;
        segments = new skyline_seg[capacity];
        size = 0;
    }

    void add_seg(skyline_seg seg){
        segments[size] = seg;
        size++;
    }
};

skyline merge_skylines(skyline s1, skyline s2) {
    skyline result(s1.size + s2.size);
    
    // TODO: merge s1 and s2 into result here

    return result;
}

// for input, buildings (l, h, r), assume ordered by l value and all values between 1 and 100
skyline get_skyline(building * buildings, int l, int r){
    skyline result = skyline(r-l+1); 

    // base cases
    if (l = r) {
        result.add_seg(skyline_seg(buildings[0].left, buildings[0].height));
        if (buildings[0].right < 100) 
            result.add_seg(skyline_seg(buildings[0].right, 0));
        return result;
    }

    int mid = (l+r)/2;
    return merge_skylines(get_skyline(buildings, l, mid), get_skyline(buildings,mid+1, r));
}