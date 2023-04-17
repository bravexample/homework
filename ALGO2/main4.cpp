// A program to ind the minimum number of audio segments
// and the total duration of time without any speakers speaking.

// library needed
#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>

// std namespace
using namespace std;

// function of comparing segments
bool compare(pair<int, int> &a, pair<int, int> &b)
{
    return a.first < b.first;
}

// main function
int main()
{
    // Get the number of the segments
    // and the total time length of the audio
    int N, L;
    scanf("%d %d", &N, &L);
    
    // Create a vector of segments
    vector<pair<int, int>> segments;

    // Get the segments and check if the segments are valid
    pair<int, int> input;
    for (int i = 0; i < N; i++)
    {
        scanf("%d %d", &input.first, &input.second);
        if (input.first == input.second)
            continue;

        segments.push_back(input);
    }

    // Sort the segments
    sort(segments.begin(), segments.end(), compare);

    // Count the minimum posible number of segments
    // and the total duration of time without any speakers speaking
    int added = 0;
    int count = 0;
    int duration = 0;
    vector<pair<int, int>> segment_pair = {make_pair(-1, -1), make_pair(-1, 0)};
    for (auto i : segments)
    {
        // If the current segment is not overlapped with the last combined segment
        if (i.first > segment_pair[1].second)
        {
            // Add the last combined segment to the result
            duration += i.first - segment_pair[1].second;
            count++;

            // Update the last combined segment
            segment_pair[0].first = segment_pair[0].second = i.first;
            segment_pair[1] = i;
        }
        // If the current segment is overlapped with the last combined segment
        else if (i.second > segment_pair[1].second)
        {
            // If not overlapped with the first segment of the last combined segment
            if (i.first > segment_pair[0].second)
            {
                // Add the last combined segment to the result
                count++;

                // Update the last combined segment
                segment_pair[0] = segment_pair[1];
                segment_pair[1] = i;
            }
            // If overlapped with the first segment of the last combined segment
            else
            {
                // Update the last combined segment
                segment_pair[1] = i;
            }
        }
    }

    // Add the time after the last segment
    duration += L - segment_pair[1].second;

    // Print the result
    printf("%d %d", count, duration);

    return 0;
}