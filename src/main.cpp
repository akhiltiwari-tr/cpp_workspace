#include<bits/stdc++.h>
#include<hello.hpp>

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <utility>
#include <vector>

using std::cout;
using std::endl;
using std::pair;
using std::vector;
using std::uint64_t;
using namespace std;

class BusSystem {
public:
  BusSystem(vector<uint64_t> stops);
  vector<uint64_t> closest_stops(uint64_t position) const;
  pair<uint64_t, bool>
  reverse_closest_stops(const vector<uint64_t> &closest) const;

private:
  vector<uint64_t> stops;
};

BusSystem::BusSystem(vector<uint64_t> new_stops) : stops{new_stops} {};

/*
 * Computes the 8 bus stops closest to the given position, in order of
 * increasing distance.
 */
vector<uint64_t> BusSystem::closest_stops(uint64_t position) const {
  vector<uint64_t> closest(stops);
  std::sort(closest.begin(), closest.end(), [position](uint64_t a, uint64_t b) {
    return (a ^ position) < (b ^ position);
  });
  closest.resize(8);
  return closest;
}

/*
 * Given the 8 closest stops to an unknown position, in order of increasing
 * distance, computes the position.
 *
 * The position is not necessarily unique: The function sets `position` to some
 * value such that `closest_stops` would produce `closest` as its output.
 *
 * If successful, `reverse_closest_stops` returns `true`; if no matching
 * position exists, it returns `false` as the second entry.
 */
pair<uint64_t, bool>
BusSystem::reverse_closest_stops(const vector<uint64_t> &closest) const {
  // TODO: Return a pair (p, true), such that closest_stops(p)
  //       would return exactly the given list of closest stops.
  //       Return (anything, false) if that is not possible.  
    uint64_t position=0, flag=0, diff_pos=0;
    for(uint64_t i=0; i<closest.size()-1; i++){ //travel through the stops taking one pair at a time
    uint64_t xored = closest[i] ^ closest[i+1];  // getting the bit positions where they differ
  diff_pos = log2(xored);// getting the MSB bit position where they differ.
   if(flag & 1<<diff_pos ) {
       if((position & (uint64_t)1<<diff_pos) == (closest[i]& (uint64_t)   1<<diff_pos)){
        return pair<uint64_t, bool>(uint64_t(0), false);
       }
    }
    else{
       flag |= 1<<diff_pos;
      position = position | (closest[i] & (uint64_t)1<<diff_pos);
    }
  }
  return pair<uint64_t, bool>(position, true);
}

/* Returns a random unsigned 64 bit integer. */
uint64_t rand64() {
  uint64_t r = 0;
  for (int i = 0; i < 64; i += 16) {
    r <<= (uint64_t)16;
    r ^= (uint64_t)rand();
  }
  return r;
}

/*
 * Compares the two arrays of length 8, and exits with an error if they
 * are not equal.
 */
void compare(const vector<uint64_t> &expected_closest,
             const vector<uint64_t> &closest) {
  if (expected_closest.size() != 8 || closest.size() != 8) {
    cout << "Wrong size!" << endl;
    exit(1);
  }
  for (int i = 0; i < 8; i++) {
    if (closest[i] != expected_closest[i]) {
      cout << "Entry " << i << " differs: " << closest[i]
           << " != " << expected_closest[i] << endl;
      exit(1);
    }
  }
}

/* Two examples for `closest_stops`. */
void test_examples() {
  BusSystem system({0, 1, 2, 3, 12, 13, 14, 15, 256, 257, 258, 259, 260, 384,
                    385, 386, 388});
  vector<uint64_t> expected_closest_7 = {3, 2, 1, 0, 15, 14, 13, 12};
  compare(expected_closest_7, system.closest_stops(7));

  vector<uint64_t> expected_closest_387 = {386, 385, 384, 388,
                                           259, 258, 257, 256};
  compare(expected_closest_387, system.closest_stops(387));
}

/*
 * For a random position computes the 8 closest stops, and then applies
 * `reverse_closest_stops` to it. The result does not need to equal the initial
 * position, but applying `closest_stops` to it again is expected to return the
 * same result.
 */
void test_random_position() {
  // Randomly initialise the list of all bus stops.
  vector<uint64_t> bus_stops;
  for (int i = 0; i < 10000; i++) {
    bus_stops.push_back(rand64());
  }
  BusSystem system(bus_stops);
  for (int i = 0; i < 100; i++) {
    // Compute the closest stops for a random position.
    vector<uint64_t> expected_closest = system.closest_stops(rand64());
    // Guess the position, based on the closest stops. Since such a position
    // exists, this must return true.
    pair<uint64_t, bool> guess = system.reverse_closest_stops(expected_closest);
    if (!guess.second) {
      cout << "reverse_closest_stops returned false." << endl;
      exit(1);
    }
    // Compute the closest stops again based on the guess and verify.
    compare(expected_closest, system.closest_stops(guess.first));
  }
}

/*
 * Applies `reverse_closest_stops` to a random list of close stops. Most of
 * the time, this should return false, but if a matching position exists, it
 * must return true and produce a guess that results in the given list of close
 * stops.
 */
void test_random_set() {
  // Randomly initialise the list of all bus stops.
  vector<uint64_t> bus_stops;
  for (int i = 0; i < 10000; i++) {
    bus_stops.push_back(rand64());
  }
  BusSystem system(bus_stops);
  for (int i = 0; i < 100; i++) {
    vector<uint64_t> expected_closest;
    for (int i = 0; i < 8; i++) {
      expected_closest.push_back(rand64());
    }
    // Guess the position, based on the closest stops. If it returns true, we
    // check the result.
    pair<uint64_t, bool> guess = system.reverse_closest_stops(expected_closest);
    if (guess.second) {
      // Compute the closest stops again based on the guess and verify.
      compare(expected_closest, system.closest_stops(guess.first));
    }
  }
}

/*
 * Runs the three test cases. If they all pass, prints success and returns
 * 0.
 */
int main() {
  test_examples();
  test_random_position();
  test_random_set();
  cout << "Success!" << endl;
  return 0;
}