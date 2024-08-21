// choose union by size by uncommenting `size` lines and commenting `rank` lines.
// both have the same asymptotic complexity, but union by rank interacts slightly
// less with memory, so should be slightly faster in a very tight loop. choose
// union by rank by default unless you already need the component size for
// something else.

struct DisjointSetUnion {
    u32 components;
    vector<u32> representative;
    vector<u32> rank;
    //vector<u32> size;

    void init(u32 components_) {
        components = components_;
        representative.resize(components);
        rank.resize(components);
        //size.resize(components);

        for (u32 i = 0; i < components; ++i) {
            representative[i] = i;
            rank[i] = 0;
            //size[i] = 1;
        }
    }

    u32 find(u32 i) {
        while (representative[i] != i) {
            representative[i] = representative[representative[i]];
            i = representative[i];
        }
        return i;
    }

    bool union_(u32 i, u32 j) {
        i = find(i);
        j = find(j);
        if (i == j) return false;

        if (rank[i] < rank[j]) swap(i, j);
        //if (size[i] < size[j]) swap(i, j);

        if (rank[i] == rank[j]) rank[i] += 1;
        //size[i] += size[j];
        representative[j] = i;
        components -= 1;
        return true;
    }
};
