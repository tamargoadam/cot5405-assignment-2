#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct building {
    int left;
    int height;
    int right;

    building(){};
    building(int l, int h, int r){
        left=l;
        height=h;
        right=r;
    }
};

struct buildings {
    int capacity;
    int size;
    building * building_list;

    ~buildings() { delete[] building_list; }
    buildings(int c) {
        capacity = c;
        building_list = new building[capacity];
        size = 0;
    }

    void add_building(building b){
        building_list[size] = b;
        size++;
    }

    void print() {
        for (int i=0; i<size; i++) {
            cout << "(" << building_list[i].left << ", " << building_list[i].height << ", " << building_list[i].right << ") ";
        }
        cout << endl;
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

    void print() {
        for (int i=0; i<size; i++) {
            cout << "(" << segments[i].start << ", " << segments[i].height << ") ";
        }
        cout << endl;
    }
};

skyline* merge_skylines(skyline* s1, skyline* s2) {
    skyline * result= new skyline(s1->size + s2->size);
    skyline_seg seg;

    int i = 0;
    int j = 0;
    int h1 = 0;
    int h2 = 0;
    while (i < s1->size && j < s2->size) {
        if (s1->segments[i].start < s2->segments[j].start) {
            h1 = s1->segments[i].height;
            if (h1 != h2) {
                seg = skyline_seg(s1->segments[i].start, max(h1, h2));
                result->add_seg(seg);
            }
            i++;
        }
        else {
            h2 = s2->segments[j].height;
            if (h1 != h2) {
                seg = skyline_seg(s2->segments[j].start, max(h1, h2));
                result->add_seg(seg);
            }
            j++;
        }
    }

    while (i < s1->size) {
        result->add_seg(s1->segments[i]);
        i++;
    }
    while (j < s2->size) {
        result->add_seg(s2->segments[j]);
        j++;
    }

    return result;
}

// for input, buildings (l, h, r), assume ordered by l value and all values between 1 and 100
skyline* get_skyline(building* buildings, int l, int r){
    skyline* result = new skyline(r-l+1); 
    skyline_seg seg;

    // cout << l << " - " << r << ": ";
    // for(int i=l; i<=r; i++)
    //     cout << buildings[i].left << ", " << buildings[i].height << ", " << buildings[i].right << "; ";
    // cout << endl;

    // base cases
    if (l == r) {
        seg = skyline_seg(buildings[l].left, buildings[l].height);
        result->add_seg(seg);
        // if (buildings[0].right < 100) 
        //     result.add_seg(skyline_seg(buildings[0].right, 0));
        return result;
    }

    int mid = (l+r)/2;
    skyline* s1 = get_skyline(buildings, l, mid);
    skyline* s2 = get_skyline(buildings,mid+1, r);
    skyline* m = merge_skylines(s1, s2);
    cout << "S1: ";
    s1->print();
    cout << "S2: ";
    s2->print();
    cout << "RETURNED: ";
    m->print();
    return m;
}

buildings* generate_random_buildings(int num_buildings) {
    buildings* b = new buildings(num_buildings);
    vector<int> l_arr(num_buildings);

    for (int i = 0; i < num_buildings; i++)
        l_arr[i] = rand() % 100 + 1;
    sort(l_arr.begin(), l_arr.end());
    for (int i = 0; i < num_buildings; i++)
        b->add_building(building(l_arr[i], rand() % 100 + 1, rand() % (100-l_arr[i]) + l_arr[i]));
    
    return b;
}

int main(int argc, char const *argv[])
{
    if (argc < 2) {
        cout << "Please input the desired number of buildings.\n";
        return -1;
    }
    int num_buildings;
    sscanf(argv[1], "%d", &num_buildings);

    buildings* b = generate_random_buildings(num_buildings);
    cout << "Randomly generated buildings:\n";
    b->print();

    skyline* s = get_skyline(b->building_list, 0, b->size-1);
    cout << "Resulting skyline:\n";
    s->print();

    return 0;
}
