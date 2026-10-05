class Solution {
public:
    vector<int> kWeakestRows(vector<vector<int>>& mat, int k) {
        vector<pair<uint8_t, uint8_t>> mat_rows(mat.size());
        uint8_t count = 0;

        for (const vector<int>& row : mat)
        {
            mat_rows[count] = pair<uint8_t, uint8_t>(0, count);
            
            for (int el : row)
            {
                mat_rows[count].first += static_cast<uint8_t>(el);
            }

            ++count;
        }

        auto comp = [](const pair<uint8_t, uint8_t>& r, const pair<uint8_t, uint8_t>& l)
        {
            return r.first > l.first || (!(r.first ^ l.first) && r.second > l.second);
        };

        make_heap(mat_rows.begin(), mat_rows.end(), comp);

        vector<int> indices;

        for (count = 0; k > 0; --k, ++count)
        {
            indices.emplace_back(mat_rows[0].second);
            pop_heap(mat_rows.begin(), mat_rows.end() - count, comp);
        }

        return indices;
    }
};
