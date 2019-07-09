#include<iostream>
#include<list>
#include<cstdlib>
using namespace std;

typedef unsigned int ADDR;

template<typename T>
struct Node{
    T val;
    ADDR prev;
    ADDR next;
};
template <typename T>
class List{
public:
    int _capacity = 1000;
    int _size;
    ADDR pos;
    Node<T> node[1000+2];
    T Temp[1000];
    ADDR HEAD;
    ADDR TAIL;


private:
    ADDR link(const ADDR& prev, const ADDR& next, const T& val){
        node[pos].val = val;

        node[pos].next = next;
        node[pos].prev = prev;

        node[prev].next = pos;
        node[next].prev = pos;

        ++pos; ++_size;
        return pos;
    }

    ADDR unlink(const ADDR& target){
        ADDR prev = node[target].prev;
        ADDR next = node[target].next;

        node[prev].next = next;
        node[next].prev = prev;

        --_size;
        return prev;
    }
public:
    List(){
        clear();
    }
    void clear(){
        pos = _size = 0;
        HEAD = _capacity;
        TAIL = _capacity+1;
        node[HEAD].next = TAIL;
        node[TAIL].prev = HEAD;
    }

    void push_back(const T& val){
        ADDR prev = node[TAIL].prev;
        ADDR next = node[prev].next;

        link(prev, next, val);
    }

    void push_front(const T& val){
        ADDR next = node[HEAD].next;
        ADDR prev = node[next].prev;

        link(prev,next,val);
    }

    void pop_back(){
        ADDR target = node[TAIL].prev;

        unlink(target);
    }

    void pop_front(){
        ADDR target = node[HEAD].next;

        unlink(target);
    }

    ADDR at(int cnt) const{
        ADDR cur = node[HEAD].next;
        for(int p = 0; p < cnt; p++) cur = node[cur].next;

        return cur;
    }

    ADDR erase(ADDR target){
        return unlink(target);
    }

    ADDR insert(ADDR prev, T val){
        ADDR next = node[prev].next;
        link(prev, next, val);
    }

    ADDR insert(int cnt, T val){
        ADDR prev = at(cnt);
        ADDR next = node[prev].next;

        link(prev, next, val);
    }

    T get(ADDR target) const{
        return node[target].val;
    }

    ADDR prev(ADDR cur){
        return node[cur].prev;
    }
    ADDR next(ADDR cur){
        return node[cur].next;
    }

    ADDR begin() const{
        return node[HEAD].next;
    }

    ADDR end() const{
        return TAIL;
    }

    void defrag(){
        if(_size == pos) return;

        int idx = 0;

        for(ADDR cur = begin(); cur != end(); cur = next(cur) ){
            Temp[idx++] = get(cur);
        }
        int __size = _size;
        clear();

        for(int i = 0; i < __size; i++) push_back(Temp[i]);
    }

    void merge(int left, int mid, int right){
        int l = left, r = mid+1, n = left;

        while(l <= mid && r <= right){
            if(node[l].val < node[r].val) Temp[n++] = node[l++].val;
            else Temp[n++] = node[r++].val;
        }

        if( l > mid){
            for(int i = r; i <= right; i++) Temp[n++] = node[i].val;
        }else{
            for(int i = l; i <= mid; i++) Temp[n++] = node[i].val;
        }

        for(int i = left; i <= right; i++) node[i].val = Temp[i];
    }
    void sort(int left, int right){
        if(left >= right) return;

        int mid = (left+right) >> 1;

        sort(left, mid);
        sort(mid+1, right);
        merge(left, mid, right);
    }

    void sort(){
        defrag();
        sort(0, _size -1);
    }
};


int main() {
    List<int> A = List<int>();

    list<int> stl;
    srand(4);
    const int MOD = 1007;

    for(int i = 0; i <= 40; i++){
        int num = rand()%MOD;
        A.push_back( num );
        stl.push_back( num);
        if(i) {
            if (i % 5 == 0) A.pop_front(), stl.pop_front();
            if (i % 9 == 0) A.pop_back(), stl.pop_back();
            //if (i % 17 == 0) A.insert(rand() % MOD, (int) (i - 11));
        }
    }

    for(ADDR it = A.begin(); it != A.end(); it = A.next(it)){
        cout << A.get(it) << " ";
    }cout << "\n";

    for(list<int>::iterator it = stl.begin(); it != stl.end(); ++it){
        cout << *it << " ";
    }cout << "\n";

    for(int i = 0; i < A.pos; i++){
        cout << A.node[i].val << " ";
    }cout << "\n";

    A.defrag();
    for(ADDR it = A.begin(); it != A.end(); it = A.next(it)){
        cout << A.get(it) << " ";
    }cout << "\n";

    A.sort();

    for(ADDR it = A.begin(); it != A.end(); it = A.next(it)){
        cout << A.get(it) << " ";
    }cout << "\n";

    stl.sort();
    for(list<int>::iterator it = stl.begin(); it != stl.end(); ++it){
        cout << *it << " ";
    }cout << "\n";

    for(int i = 0; i < A.pos; i++){
        cout << A.node[i].val << " ";
    }cout << "\n";

    return 0;
}