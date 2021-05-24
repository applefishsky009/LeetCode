#include <queue>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <D:/Github/RylModule/vector.h>
using namespace std;

int global_time = 0;

class Tweet {
  public:
    int id;
    int time;
    Tweet *next;

    Tweet(int id) {     // 推文的构造函数
        this->id = id;
        this->time = global_time++;
        next = nullptr;
    }
};

class User {
  public:
    int id;
    Tweet *tweet;   //该用户发送的推文，是个链表
    unordered_set<int> follows;   // 该用户关注的用户

    User(int id) {  // 用户的构造函数
        this->id = id;
        tweet = nullptr;
    }

    void follow(int followeeId) {   // 维护关注集合
        if (followeeId == id) return;
        follows.insert(followeeId);
    }

    void unfollow(int followeeId) { // 维护关注集
        if (!follows.count(followeeId) || followeeId == id) return;
        follows.erase(followeeId);
    }

    void post(int tweetId) {    // 头插法插入新推文
        Tweet *newTweet = new Tweet(tweetId);
        newTweet->next = tweet;
        tweet = newTweet;
    }
};

// HT Heap Design
// time: O(1) + O(recentMax * num) + O(1) + O(1) num 为用户关注的人加上自己的数量和
// space: O(recentMax * tot) tot为推特总用户数
class Twitter {
  public:
    /** Initialize your data structure here. */
    Twitter() {
        user_map.clear();
    }

    /** compose a new tweet. */
    void postTweet(int userId, int tweetId) {
        if (!user_map.count(userId)) {   // 新用户则创建
            user_map[userId] = new User(userId);
        }
        user_map[userId]->post(tweetId);
    }

    /** Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by 
      users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent. */
    vector<int> getNewsFeed(int userId) {   // 每次调用都会创建一个新的大顶堆, 合并k个排序链表的思路
        if (!user_map.count(userId)) return {};
        priority_queue<Tweet*, vector<Tweet*>, cmp> ipriq;  // 这里不能使用匿名函数, 没有函数实体
        if (user_map[userId]->tweet) {  // 处理自己的推文链表
            ipriq.push(user_map[userId]->tweet);
        }
        for (int followeeId : user_map[userId]->follows) {  // 处理关注列表的推文列表
            if (!user_map.count(followeeId)) continue;
            Tweet *head = user_map[followeeId]->tweet;
            if (head == nullptr) continue;
            ipriq.push(head);
        }
        vector<int> rs;
        while (!ipriq.empty()) {    // 大顶堆维护各个用户的关注头列表,
            Tweet *t = ipriq.top();
            ipriq.pop();
            rs.push_back(t->id);
            if (rs.size() == 10) return rs;
            if (t->next) {
                ipriq.push(t->next);
            }
        }
        return rs;
    }

    /** Follower follows a followee. If the operation is invalid, it should be a no-op. */
    void follow(int followerId, int followeeId) {
        if (!user_map.count(followerId)) {  // 没有用户则新建
            user_map[followerId] = new User(followerId);
        }
        user_map[followerId]->follow(followeeId);   // 维护关注列表
    }

    /** Follower unfollows a followee. If the operation is invalid, it should be a no-op. */
    void unfollow(int followerId, int followeeId) {
        if (!user_map.count(followerId)) return;    // 没有用户则返回
        user_map[followerId]->unfollow(followeeId);
    }
  private:
    unordered_map<int, User*> user_map; // 所有的用户
    struct cmp {
        bool operator()(const Tweet *a, const Tweet *b) {
            return a->time < b->time;
        }
    };
};

int main() {
    Twitter *obj = new Twitter();
    obj->postTweet(0, 0);
    vector<int> param_2 = obj->getNewsFeed(0);
    show1DVector(param_2);
    obj->follow(0, 1);
    obj->unfollow(0, 1);
    return 0;
}