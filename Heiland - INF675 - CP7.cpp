#include <vector>
#include <cmath>
#include <limits>

class Solution {
public:
    int minMoves(std::vector<int>& nums, int k) {
        // Store positions of 1s in the array
        std::vector<long long> pos;
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] == 1) pos.push_back(i);
        }

        // Calculate the prefix sum of positions to efficiently compute the cost of each window
        std::vector<long long> prefixSum(pos.size() + 1, 0);
        for (int i = 1; i < prefixSum.size(); ++i) {
            prefixSum[i] = prefixSum[i - 1] + pos[i - 1];
        }

        long long minCost = std::numeric_limits<long long>::max();
        for (int i = 0; i + k <= pos.size(); ++i) {
            // Find the middle index of the current window
            int mid = i + k / 2;

            // Calculate the cost to move 1s on the left of the median to the median
            long long leftCost = pos[mid] * (mid - i) - (prefixSum[mid] - prefixSum[i]);

            // Calculate the cost to move 1s on the right of the median to the median
            long long rightCost = (prefixSum[i + k] - prefixSum[mid]) - pos[mid] * (i + k - mid);

            // The total cost is the sum of left and right costs
            long long cost = leftCost + rightCost;

            // Adjust the cost for the natural sequence of numbers
            if (k % 2 == 0) {
                cost -= (k / 2) * ((k / 2) - 1) + (k / 2);
            } else {
                cost -= (k / 2) * ((k / 2) + 1);
            }

            // Update the minimum cost
            minCost = std::min(minCost, cost);
        }

        // Return the minimum cost after converting it back to int
        return static_cast<int>(minCost);
    }
};
/*
#include <deque>
class Solution {
public:
    int minMoves(vector<int>& nums, int k) {
        //First loop through vector and see if there are k consecutive 1's. 
        int i; //Loop counter.
        int count = 0;
        int moves = 0;
        int movesOne = 0; 
        int movesCopy = 0;
        int kCopy = k;

        vector<int> vect2;
        //Copy vector.
        for (int i=0; i < nums.size(); i++)  
            vect2.push_back(nums[i]); 


        deque<int> indexOfOnes; //Keeps track of the locations of all of the 1s in the vector, using a deque.

        for(i = 0; i < nums.size(); i++){
            if(nums[i] == 1){ //If the index is 1, then increment.
                count++;
                indexOfOnes.push_back(i); //Adds the indexes that contain 1. 
            } else { //If the index is 0, then reset count.
                count = 0; 
            }
            if(count == k){ //If the vector already has k consecutive 1's.
                return moves;
            }
        }

        int numberOfConsecutiveOnes = 0;
        //We are going to shift all the elements that are 1's to where 1 is rightmost.

        for(i = indexOfOnes.back(); i >= 0; i--){
            //If the current index is 1, then no shifting needs to be done.
            if(nums[i] == 1){
                indexOfOnes.pop_back();
            } else {
                //The current index has 0, so swap this index with the last element in indexOfOnes
                nums[indexOfOnes.back()] = 0;
                nums[i] = 1;

                //Keep track of how many moves that took.
                moves += (i - indexOfOnes.back());

                //Remove the last element in indexOfOnes
                indexOfOnes.pop_back(); 
            }
            ++numberOfConsecutiveOnes;
            if(numberOfConsecutiveOnes == k){
                break;
            }
        }

        //cout << moves << endl;

        //Now, we are going to shift everything to the left.
        numberOfConsecutiveOnes = 0;
        //We are going to shift all the elements that are 1's to where 1 is rightmost.

        int lastIndexOfOne = indexOfOnesCopy.back();
        //cout << lastIndexOfOne << endl;
        for(i = indexOfOnesCopy.front(); i <= lastIndexOfOne; i++){
            //cout << indexOfOnesCopy.front() << endl;
            //cout << i << endl;
            //If the current index is 1, then no shifting needs to be done.
            if(vect2[i] == 1){
                indexOfOnesCopy.pop_front();
            } else {
                //The current index has 0, so swap this index with the first element in indexOfOnes
                vect2[indexOfOnesCopy.front()] = 0;
                vect2[i] = 1;
//cout << indexOfOnesCopy.front() << endl;
                //Keep track of how many moves that took.
                movesOne += (indexOfOnesCopy.front() - i);

                //Remove the first element in indexOfOnes
                indexOfOnesCopy.pop_front(); 
            }
            ++numberOfConsecutiveOnes;
            if(numberOfConsecutiveOnes == k){
                break;
            }
        }
        //cout << movesOne;
        if(movesOne > moves){
            return moves;
        }
        return movesOne;      
    }
}; */