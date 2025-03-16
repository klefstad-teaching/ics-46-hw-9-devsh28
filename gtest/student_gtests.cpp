#include <gtest/gtest.h>
#include "ladder.h"
#include "dijkstras.h"
#include <sstream>
#include <set>
#include <vector>
#include <string>
#include <limits>
#include <iostream>
#include <algorithm>
using namespace std;

class LadderTests : public ::testing::Test {
protected:
    set<string> word_list;
    void SetUp() override {
        word_list.insert("cat");
        word_list.insert("cot");
        word_list.insert("cog");
        word_list.insert("dog");
        word_list.insert("marty");
        word_list.insert("party");
        word_list.insert("carts");
        word_list.insert("cards");
        word_list.insert("curds");
        word_list.insert("curls");
        word_list.insert("code");
        word_list.insert("cade");
        word_list.insert("cake");
        word_list.insert("cate");
        word_list.insert("date");
        word_list.insert("data");
        word_list.insert("work");
        word_list.insert("wok");
        word_list.insert("wop");
        word_list.insert("wap");
        word_list.insert("lap");
        word_list.insert("play");
        word_list.insert("sleep");
        word_list.insert("sleet");
        word_list.insert("sheet");
        word_list.insert("sheep");
        word_list.insert("cheap");
        word_list.insert("cheat");
        word_list.insert("wheat");
        word_list.insert("awake");
        word_list.insert("car");
        word_list.insert("chat");
    }
};

TEST_F(LadderTests, CatToDog) {
    vector<string> ladder = generate_word_ladder("cat", "dog", word_list);
    EXPECT_EQ(ladder.size(), 4);
}


TEST_F(LadderTests, CarToCheat) {
    vector<string> ladder = generate_word_ladder("car", "cheat", word_list);
    EXPECT_EQ(ladder.size(), 4);
}

class DijkstrasTests : public ::testing::Test {
protected:
    Graph graph;
    void SetUp() override {
        graph.numVertices = 4;
        graph.resize(graph.numVertices);
        graph[0].push_back(Edge(0, 1, 1));
        graph[0].push_back(Edge(0, 2, 4));
        graph[1].push_back(Edge(1, 2, 2));
        graph[1].push_back(Edge(1, 3, 6));
        graph[2].push_back(Edge(2, 3, 3));
    }
};

TEST_F(DijkstrasTests, CorrectDistances) {
    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(graph, 0, previous);
    EXPECT_EQ(distances[0], 0);
    EXPECT_EQ(distances[1], 1);
    EXPECT_EQ(distances[2], 3);
    EXPECT_EQ(distances[3], 6);
}

TEST_F(DijkstrasTests, CorrectPathExtraction) {
    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(graph, 0, previous);
    vector<int> path = extract_shortest_path(distances, previous, 3);
    vector<int> expected_path = {0, 1, 2, 3};
    EXPECT_EQ(path, expected_path);
}

TEST(DijkstrasPrintPathTest, ValidPath1) {
    ostringstream output;
    streambuf* old_buf = cout.rdbuf(output.rdbuf());
    vector<int> path = {0, 7, 15, 5, 14, 11, 12};
    print_path(path, 0);
    cout.rdbuf(old_buf);
    string expected = "0 7 15 5 14 11 12 \nTotal cost is 0\n";
    EXPECT_EQ(expected, output.str());
}

TEST(DijkstrasPrintPathTest, ValidPath2) {
    ostringstream output;
    streambuf* old_buf = cout.rdbuf(output.rdbuf());
    vector<int> path = {0, 5, 3, 12, 10, 2};
    print_path(path, 0);
    cout.rdbuf(old_buf);
    string expected = "0 5 3 12 10 2 \nTotal cost is 0\n";
    EXPECT_EQ(expected, output.str());
}

TEST(DijkstrasPrintPathTest, ValidPath3) {
    ostringstream output;
    streambuf* old_buf = cout.rdbuf(output.rdbuf());
    vector<int> path = {0, 3, 6, 1};
    print_path(path, 0);
    cout.rdbuf(old_buf);
    string expected = "0 3 6 1 \nTotal cost is 0\n";
    EXPECT_EQ(expected, output.str());
}


TEST(DijkstrasPrintPathTest, ValidPath4) {
    ostringstream output;
    streambuf* old_buf = cout.rdbuf(output.rdbuf());
    vector<int> path = {1, 5, 6, 2, 8};
    print_path(path, 7);
    cout.rdbuf(old_buf);
    string expected = "1 5 6 2 8 \nTotal cost is 7\n";
    EXPECT_EQ(expected, output.str());
}

TEST(DijkstrasPrintPathTest, ValidPath5) {
    ostringstream output;
    streambuf* old_buf = cout.rdbuf(output.rdbuf());
    vector<int> path = {1, 5, 6, 2, 8, 10, 3};
    print_path(path, 0);
    cout.rdbuf(old_buf);
    string expected = "1 5 6 2 8 10 3 \nTotal cost is 0\n";
    EXPECT_EQ(expected, output.str());
}


TEST(LadderPrintTest, NoLadder) {
    ostringstream output;
    streambuf* old_buf = cout.rdbuf(output.rdbuf());
    vector<string> ladder;
    print_word_ladder(ladder);
    cout.rdbuf(old_buf);
    string expected = "No word ladder found.\n";
    EXPECT_EQ(expected, output.str());
}

TEST(LadderVerifyTest, VerifyWordLadder) {
    verify_word_ladder();
    SUCCEED();
}

