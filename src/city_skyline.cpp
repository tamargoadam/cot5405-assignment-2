#include <vector>
#include <iostream>
#include <algorithm>
#include <sys/time.h> 

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
    building** building_list;

    ~buildings() { delete[] building_list; }
    buildings(int c) {
        capacity = c;
        building_list = new building*[capacity];
        size = 0;
    }

    void add_building(building* b){
        building_list[size] = b;
        size++;
    }

    void print() {
        for (int i=0; i<size; i++) {
            cout << "(" << building_list[i]->left << ", " << building_list[i]->height << ", " << building_list[i]->right << ") ";
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
        if (size > 0) {
            if (segments[size-1].height == seg.height)
                return;
            if (segments[size-1].start == seg.start) {
                segments[size-1].height = max(segments[size-1].height, seg.height);
                return;
            }
        }

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

    // protect against edge case where last segments are equal
    if (s1->segments[s1->size-1].start == s2->segments[s2->size-1].start
    && s1->segments[s1->size-1].height == s2->segments[s2->size-1].height) {
        if (s1->segments[s1->size-2].height <= s2->segments[s2->size-2].height) {
            s1->segments[s1->size-1].start--;
        } else {
            s2->segments[s2->size-1].start--;
        }
    }

    int i = 0;
    int j = 0;
    int h1 = -1;
    int h2 = -1;
    while (i < s1->size && j < s2->size) {
        if (s1->segments[i].start < s2->segments[j].start) {
            h1 = s1->segments[i].height;
            seg = skyline_seg(s1->segments[i].start, max(h1, h2));
            result->add_seg(seg);
            i++;
        }
        else {
            h2 = s2->segments[j].height;
            seg = skyline_seg(s2->segments[j].start, max(h1, h2));
            result->add_seg(seg);
            j++;
        }
    }

    while (i < s1->size) {
        h1 = s1->segments[i].height;
        seg = skyline_seg(s1->segments[i].start, max(h1, h2));
        result->add_seg(seg);
        i++;
    }
    while (j < s2->size) {
        h2 = s2->segments[j].height;
        seg = skyline_seg(s2->segments[j].start, max(h1, h2));
        result->add_seg(seg);
        j++;
    }


    return result;
}

// for input, buildings (l, h, r), assume ordered by l value and all values between 1 and 100
skyline* get_skyline(building** buildings, int l, int r){
    skyline* result = new skyline(r-l+3); 
    skyline_seg seg;

    // base cases
    if (l == r) {
        if (buildings[l]->left > 1) 
            result->add_seg(skyline_seg(1, 0));
        seg = skyline_seg(buildings[l]->left, buildings[l]->height);
        result->add_seg(seg);
        if (buildings[l]->right < 100) 
            result->add_seg(skyline_seg(buildings[l]->right, 0));
        return result;
    }

    int mid = (l+r)/2;
    skyline* s1 = get_skyline(buildings, l, mid);
    skyline* s2 = get_skyline(buildings,mid+1, r);
    skyline* m = merge_skylines(s1, s2);
    return m;
}

buildings* generate_random_buildings(int num_buildings) {
    buildings* b = new buildings(num_buildings);
    vector<int> l_arr(num_buildings);
    int rand_h = 0;
    int rand_r = 0;
    srand(time(0));

    for (int i = 0; i < num_buildings; i++)
        l_arr[i] = rand() % 99 + 1;
    sort(l_arr.begin(), l_arr.end());
    for (int i = 0; i < num_buildings; i++) 
        b->add_building(new building(l_arr[i], rand() % 100 + 1, rand() % (100-l_arr[i]) + l_arr[i] + 1));

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
    if (num_buildings < 1000) {
        cout << "Randomly generated buildings:\n";
        b->print();
    } else {
        cout << num_buildings << " buildings have been randomly generated.\n";
    }

    struct timeval t1, t2;
    double time_elapsed;
    gettimeofday(&t1, NULL);

    // find skyling for buildings in b
    skyline* s = get_skyline(b->building_list, 0, b->size-1);

    gettimeofday(&t2, NULL);
    time_elapsed = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
    time_elapsed += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms

    cout << "Resulting skyline:\n";
    s->print();
    cout << "CPU time to find skyline: " << time_elapsed << " ms\n";

    return 0;
}
