#include <gtest/gtest.h>
#include "ladder.h"
#include "dijkstras.h"
#include <set>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>


class LadderTests : public ::testing::Test {
protected:
    std::set<std::string> word_list;

    void SetUp() override {
        word_list.insert("cat");
        word_list.insert("dog");
        word_list.insert("party");
        word_list.insert("parts");
        word_list.insert("carts");
        word_list.insert("cards");
        word_list.insert("curds");
        word_list.insert("curls");
        word_list.insert("code");
        word_list.insert("cade");
        word_list.insert("cate");
        word_list.insert("date");
        word_list.insert("data");
        word_list.insert("work");
        word_list.insert("play");
        word_list.insert("sleep");
        word_list.insert("awake");
        word_list.insert("chat");
        word_list.insert("cheat");
        word_list.insert("car");
    }
};

TEST_F(LadderTests, CatToDog) {
    std::vector<std::string> ladder = generate_word_ladder("cat", "dog", word_list);
    EXPECT_EQ(ladder.size(), 4);
}

TEST_F(LadderTests, MartyToCurls) {
    std::vector<std::string> ladder = generate_word_ladder("marty", "curls", word_list);
    EXPECT_EQ(ladder.size(), 6);
}

TEST_F(LadderTests, CodeToData) {
    std::vector<std::string> ladder = generate_word_ladder("code", "data", word_list);
    EXPECT_EQ(ladder.size(), 6);
}

TEST_F(LadderTests, WorkToPlay) {
    std::vector<std::string> ladder = generate_word_ladder("work", "play", word_list);
    EXPECT_EQ(ladder.size(), 6);
}

TEST_F(LadderTests, SleepToAwake) {
    std::vector<std::string> ladder = generate_word_ladder("sleep", "awake", word_list);
    EXPECT_EQ(ladder.size(), 8);
}

TEST_F(LadderTests, CarToCheat) {
    std::vector<std::string> ladder = generate_word_ladder("car", "cheat", word_list);
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
    std::vector<int> previous;
    std::vector<int> distances = dijkstra_shortest_path(graph, 0, previous);
    EXPECT_EQ(distances[0], 0);
    EXPECT_EQ(distances[1], 1);
    EXPECT_EQ(distances[2], 3);
    EXPECT_EQ(distances[3], 6);
}

TEST_F(DijkstrasTests, CorrectPathExtraction) {
    std::vector<int> previous;
    std::vector<int> distances = dijkstra_shortest_path(graph, 0, previous);
    // Expected shortest path from vertex 0 to vertex 3 is: 0 -> 1 -> 2 -> 3.
    std::vector<int> path = extract_shortest_path(distances, previous, 3);
    std::vector<int> expected_path = {0, 1, 2, 3};
    EXPECT_EQ(path, expected_path);
}

