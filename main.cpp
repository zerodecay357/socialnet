#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <algorithm>
#include <sstream>
#include <ctime>
using namespace std;

// Forward declarations
class User;

// ==============================
// Simple UI Functions
// ==============================
void printBanner() {
    cout << "\033[1;36m";  // Cyan color
    cout << "\n";
    cout << "  ███████╗ ██████╗  ██████╗██╗ █████╗ ██╗     ███╗   ██╗███████╗████████╗\n";
    cout << "  ██╔════╝██╔═══██╗██╔════╝██║██╔══██╗██║     ████╗  ██║██╔════╝╚══██╔══╝\n";
    cout << "  ███████╗██║   ██║██║     ██║███████║██║     ██╔██╗ ██║█████╗     ██║   \n";
    cout << "  ╚════██║██║   ██║██║     ██║██╔══██║██║     ██║╚██╗██║██╔══╝     ██║   \n";
    cout << "  ███████║╚██████╔╝╚██████╗██║██║  ██║███████╗██║ ╚████║███████╗   ██║   \n";
    cout << "  ╚══════╝ ╚═════╝  ╚═════╝╚═╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═══╝╚══════╝   ╚═╝   \n";
    cout << "\033[0m";  // Reset color
    cout << "\033[1;33m";  // Yellow color
    cout << "                         SIMULATOR v1.0\n";
    cout << "\033[0m";  // Reset color
    cout << "\033[1;90m";  // Gray color
    cout << "                    COL106 - Data Structures\n";
    cout << "\033[0m\n";  // Reset color
}

void printHelp() {
    cout << "\n";
    cout << "========================================\n";
    cout << "         COMMAND REFERENCE\n";
    cout << "========================================\n";
    cout << "\n";
    cout << "USER MANAGEMENT:\n";
    cout << "  ADD USER <username>\n";
    cout << "    - Add a new user to the network\n";
    cout << "    - Example: ADD USER john_doe\n";
    cout << "\n";
    cout << "FRIENDSHIP OPERATIONS:\n";
    cout << "  ADD FRIEND <username1> <username2>\n";
    cout << "    - Create a friendship between two users\n";
    cout << "    - Example: ADD FRIEND alice bob\n";
    cout << "\n";
    cout << "  LIST FRIENDS <username>\n";
    cout << "    - Display all friends of a user (alphabetically sorted)\n";
    cout << "    - Example: LIST FRIENDS alice\n";
    cout << "\n";
    cout << "  SUGGEST FRIENDS <username> <N>\n";
    cout << "    - Suggest up to N friends based on mutual connections\n";
    cout << "    - Example: SUGGEST FRIENDS alice 5\n";
    cout << "\n";
    cout << "  DEGREES OF SEPARATION <username1> <username2>\n";
    cout << "    - Find shortest friendship path between two users\n";
    cout << "    - Example: DEGREES OF SEPARATION alice charlie\n";
    cout << "\n";
    cout << "POST OPERATIONS:\n";
    cout << "  ADD POST <username> \"<content>\"\n";
    cout << "    - Create a new post for a user\n";
    cout << "    - Example: ADD POST alice \"Hello World!\"\n";
    cout << "\n";
    cout << "  OUTPUT POSTS <username> <N>\n";
    cout << "    - Display N most recent posts (use -1 for all posts)\n";
    cout << "    - Example: OUTPUT POSTS alice 10\n";
    cout << "\n";
    cout << "SYSTEM COMMANDS:\n";
    cout << "  HELP\n";
    cout << "    - Display this help message\n";
    cout << "\n";
    cout << "  CLEAR\n";
    cout << "    - Clear the screen\n";
    cout << "\n";
    cout << "  EXIT or QUIT\n";
    cout << "    - Exit the simulator\n";
    cout << "\n";
    cout << "NOTES:\n";
    cout << "  - Usernames are case-insensitive\n";
    cout << "  - Post content must be enclosed in double quotes\n";
    cout << "  - Use Ctrl+D to exit (EOF)\n";
    cout << "\n";
}

void printWelcome() {
    printBanner();
    cout << "System initialized successfully\n";
    cout << "Type 'HELP' for command reference or 'EXIT' to quit\n";
    cout << "\n";
}

void clearScreen() {
    cout << "\033[2J\033[1;1H";
}

void printPrompt() {
    cout << "socialnet>> ";
}

void printSuccess(const string& message) {
    cout << "SUCCESS: " << message << "\n";
}

void printError(const string& message) {
    cout << "ERROR: " << message << "\n";
}

void printInfo(const string& message) {
    cout << "INFO: " << message << "\n";
}

// ==============================
// Class: Post
// ==============================
struct Post {
    string content;
    time_t timestamp;
    
    Post(string content) {
        this->content = content;
        this->timestamp = time(NULL);
    }
    
    string getContent() {
        return this->content;
    }
    
    time_t getTimestamp() {
        return this->timestamp;
    }
};

// ==============================
// AVL Node for Posts
// Stores posts sorted by timestamp
// ==============================
class PostNode {
public:
    PostNode* left;
    PostNode* right;
    int height;
    Post* data;
    
    PostNode(string content) {
        data = new Post(content);
        left = nullptr;
        right = nullptr;
        height = 1;
    }
    
};

// ==============================
// AVL Tree for Posts
// Maintains posts in chronological order
// ==============================
class PostAVLTree {
private:
    PostNode* root;
    
    // Get height of node
    int height(PostNode* node) {
        if (node == nullptr) return 0;
        return node->height;
    }
    
    // Update height after insertion/deletion
    void updateHeight(PostNode* node) {
        if (node == nullptr) return;
        node->height = 1 + max(height(node->left), height(node->right));
    }
    
    // Get balance factor
    int getBalance(PostNode* node) {
        if (node == nullptr) return 0;
        return height(node->left) - height(node->right);
    }
    
    // Right rotation
    PostNode* rotateRight(PostNode* y) {
        PostNode* x = y->left;
        PostNode* T2 = x->right;
        
        x->right = y;
        y->left = T2;
        
        updateHeight(y);
        updateHeight(x);
        
        return x;
    }
    
    // Left rotation
    PostNode* rotateLeft(PostNode* x) {
        PostNode* y = x->right;
        PostNode* T2 = y->left;
        
        y->left = x;
        x->right = T2;
        
        updateHeight(x);
        updateHeight(y);
        
        return y;
    }
    
    // Insert node helper - inserts based on timestamp
    PostNode* insertNode(PostNode* node, string content, time_t timestamp) {
        if (node == nullptr) {
            PostNode* newNode = new PostNode(content);
            newNode->data->timestamp = timestamp;
            return newNode;
        }

        if (timestamp < node->data->getTimestamp()) {
            node->left = insertNode(node->left, content, timestamp);
        } else {
            node->right = insertNode(node->right, content, timestamp);
        }

        updateHeight(node);
        
        int balance = getBalance(node);
       
        // Left Left Case
        if (balance > 1 && timestamp < node->left->data->getTimestamp()) {
            return rotateRight(node);
        }
        
        // Right Right Case
        if (balance < -1 && timestamp >= node->right->data->getTimestamp()) {
            return rotateLeft(node);
        }
        
        // Left Right Case
        if (balance > 1 && timestamp >= node->left->data->getTimestamp()) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        
        // Right Left Case
        if (balance < -1 && timestamp < node->right->data->getTimestamp()) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        
        return node;
    }
    
    // Collect posts in reverse chronological order (right to left traversal)
    void collectPostsReverse(PostNode* node, vector<string>& posts) {
        if (node == nullptr) return;
        
        // Visit right subtree first (newer posts)
        collectPostsReverse(node->right, posts);
        
        // Visit current node
        posts.push_back(node->data->getContent());
        
        // Visit left subtree (older posts)
        collectPostsReverse(node->left, posts);
    }
    
    // Clear all nodes
    void clear(PostNode* node) {
        if (node == nullptr) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }
    
public:
    PostAVLTree() {
        root = nullptr;
    }
    
    ~PostAVLTree() {
        clear(root);
    }
    
    // Insert a new post
    void insert(string content) {
        time_t timestamp = time(NULL);
        root = insertNode(root, content, timestamp);
    }
    
    // Get N most recent posts
    vector<string> getRecentPosts(int N) {
        vector<string> allPosts;
        collectPostsReverse(root, allPosts);
        
        // If N is -1, return all posts
        if (N == -1) {
            return allPosts;
        }
        
        // Return only N posts if available
        if (N > (int)allPosts.size()) {
            return allPosts;
        }
        
        vector<string> result(allPosts.begin(), allPosts.begin() + N);
        return result;
    }
};

// ==============================
// AVL Node for Friends
// Stores friends sorted alphabetically by username
// ==============================
class FriendNode {
public:
    FriendNode* left;
    FriendNode* right;
    int height;
    User* friendPtr;
    
    FriendNode(User* user) {
        friendPtr = user;
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};

// ==============================
// AVL Tree for Friends
// Maintains friends in alphabetical order
//faster deletion and insertion.
// ==============================
class FriendAVLTree {
private:
    FriendNode* root;
    
    // Get height of node
    int height(FriendNode* node) {
        if (node == nullptr) {
            return 0;}
        return node->height;
    }
    
    // Update height
    void updateHeight(FriendNode* node) {
        if (node == nullptr) return;
        node->height = 1 + max(height(node->left), height(node->right));
    }
    
    // Get balance factor
    int getBalance(FriendNode* node) {
        if (node == nullptr) return 0;
        return height(node->left) - height(node->right);
    }
    
    // Right rotation
    FriendNode* rotateRight(FriendNode* y) {
        FriendNode* x = y->left;
        FriendNode* T2 = x->right;
        
        x->right = y;
        y->left = T2;
        
        updateHeight(y);
        updateHeight(x);
        
        return x;
    }
    
    // Left rotation
    FriendNode* rotateLeft(FriendNode* x) {
        FriendNode* y = x->right;
        FriendNode* T2 = y->left;
        
        y->left = x;
        x->right = T2;
        
        updateHeight(x);
        updateHeight(y);
        
        return y;
    }
    
    // Insert node helper
    FriendNode* insertNode(FriendNode* node, User* user);
    
    // Check if a user is already a friend
    bool contains(FriendNode* node, User* user);
    
    // Collect all friends in alphabetical order
    void collectFriendsInOrder(FriendNode* node, vector<User*>& friends) {
        if (node == nullptr) return;
        
        collectFriendsInOrder(node->left, friends);
        friends.push_back(node->friendPtr);
        collectFriendsInOrder(node->right, friends);
    }
    
    // Clear all nodes
    void clear(FriendNode* node) {
        if (node == nullptr) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }
    
public:
    FriendAVLTree() {
        root = nullptr;
    }
    
    ~FriendAVLTree() {
        clear(root);
    }
    
    void insert(User* user) {
        root = insertNode(root, user);
    }
    
    bool isFriend(User* user) {


        return contains(root, user);
    }
    
    vector<User*> getAllFriends() {
        vector<User*> friends;
        collectFriendsInOrder(root, friends);
        return friends;
    }
};

// ==============================
// Class: User
// ==============================
class User {
private:
    string username;
    FriendAVLTree* friends;

    PostAVLTree* posts;
    
public:
    User(string username) {
        this->username = username;
        transform(this->username.begin(), this->username.end(), this->username.begin(), ::tolower);
        
        friends = new FriendAVLTree();
        posts = new PostAVLTree();
    }
    
    string getUsername() {
        return this->username;
    }
    
    void addFriend(User* friendUser) {
        friends->insert(friendUser);
    }
    
    bool isFriend(User* friendUser) {
        return friends->isFriend(friendUser);
    }
    
    void addPost(string content) {
        posts->insert(content);
    }
    
    vector<string> getRecentPosts(int N) {

        return posts->getRecentPosts(N);
    }
    
    vector<User*> getFriends() {
        return friends->getAllFriends();
    }
};

// Implement FriendNode insertion
FriendNode* FriendAVLTree::insertNode(FriendNode* node, User* user) {
    if (node == nullptr) {
        return new FriendNode(user);
    }
    
    string newUsername = user->getUsername();
    string nodeUsername = node->friendPtr->getUsername();
    
    if (newUsername < nodeUsername) {
        node->left = insertNode(node->left, user);
    } else if (newUsername > nodeUsername) {
        node->right = insertNode(node->right, user);
    } else {
        return node;
    }
    
    updateHeight(node);
    int balance = getBalance(node);
    
    if (balance > 1 && newUsername < node->left->friendPtr->getUsername()) {

        return rotateRight(node);
    }
    
    if (balance < -1 && newUsername > node->right->friendPtr->getUsername()) {
        return rotateLeft(node);
    }
    
    if (balance > 1 && newUsername > node->left->friendPtr->getUsername()) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    
    if (balance < -1 && newUsername < node->right->friendPtr->getUsername()) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    
    return node;
}

bool FriendAVLTree::contains(FriendNode* node, User* user) {
    if (node == nullptr) return false;
    
    string searchUsername = user->getUsername();


    string nodeUsername = node->friendPtr->getUsername();
    
    if (searchUsername == nodeUsername) {
        return true;
    } else if (searchUsername < nodeUsername) {
        return contains(node->left, user);
    } else {
        return contains(node->right, user);
    }
}

// ==============================
// Class: SocialGraph
// ==============================
class SocialGraph {
private:
    unordered_map<string, User*> userMap;
    
    string toLower(string str) {
        transform(str.begin(), str.end(), str.begin(), ::tolower);
        return str;
    }
    
public:
    
    void addUser(string username) {
        username = toLower(username);
        
        if (username.empty()) {
            printError("Username cannot be empty");
            return;
        }
        
        if (userMap.find(username) != userMap.end()) {
            printError("User '" + username + "' already exists");
            return;
        }
        
        User* newUser = new User(username);
        userMap[username] = newUser;
        printSuccess("User '" + username + "' added successfully");
    }
    
    void addFriendship(string user1, string user2) {
        user1 = toLower(user1);

        user2 = toLower(user2);
        
        if (user1 == user2) {
            printError("Users cannot be friends with themselves");
            return;
        }
        
        auto it1 = userMap.find(user1);


        auto it2 = userMap.find(user2);
        
        if (it1 == userMap.end()) {
            printError("User '" + user1 + "' does not exist");
            return;
        }
        

        if (it2 == userMap.end()) {
            printError("User '" + user2 + "' does not exist");


            return;
        }
        
        if (it1->second->isFriend(it2->second)) {
            printError("Users '" + user1 + "' and '" + user2 + "' are already friends");
            return;
        }
        
        it1->second->addFriend(it2->second);
        it2->second->addFriend(it1->second);

        printSuccess( user1 + "' and '" + user2 + "are friends now.");
    }
    
    void listFriends(string username) {
        username = toLower(username);
        
        auto it = userMap.find(username);
        if (it == userMap.end()) {
            printError("User '" + username + "' does not exist");
            return;
        }
        
        vector<User*> friends = it->second->getFriends();
        
        if (friends.empty()) {
            printInfo("User '" + username + "' has no friends yet");
            return;
        }
        cout << "\nFriends of '" << username << "':\n";
        for (size_t i = 0; i < friends.size(); i++) {
            cout << friends[i]->getUsername() << "\n";
        }
        cout << "\n";
    }
    
    void suggestFriends(string u, int n) {
        u = toLower(u);
        
        if (n == 0) {
            return;
        }
        
        auto it = userMap.find(u);
        if (it == userMap.end()) {
            printError("User '" + u + "' does not exist");
            return;
        }

        User* user = it->second;
        vector<User*> friends = user->getFriends();
        unordered_set<User*> fs(friends.begin(), friends.end());
        
        

        unordered_map<string,int> counts;
        for(auto i:friends){
            vector <User*> fof =i->getFriends();
            for(auto it:fof){
                if(it==user && fs.find(it)!=fs.end()){
                    continue;
                }
                else{
                    counts[it->getUsername()]=counts[it->getUsername()]+1;
                }
            }

        }
        

        
        vector<pair<string, int>> sugg;//stored in a pair for the sort.
        for (const auto& p : counts) {
            sugg.push_back(p);
        }
        //sorting it on basis of the conditions
        sort(sugg.begin(), sugg.end(),
            [](const pair<string, int>& a, const pair<string, int>& b) {


                if (a.second != b.second) return a.second > b.second;
                return a.first < b.first;
            });
        
        if (sugg.empty()) {
            printInfo("No friend suggestions available for '" + u + "'");
            return;
        }
        
        cout << "\nFriend suggestions for '" << u << "':\n";
        int c = min(n, (int)sugg.size());
        for (int i = 0; i < c; i++) {
            cout << sugg[i].first << "\n";
        }
        cout << "\n";
    }
    
    int degreesOfSeparation(string u1, string u2) {
        u1 = toLower(u1);
        u2 = toLower(u2);
        
        auto it1 = userMap.find(u1);
        auto it2 = userMap.find(u2);
        
        if (it1 == userMap.end()) {
            printError("User '" + u1 + "' does not exist");
            return -1;
        }
        
        if (it2 == userMap.end()) {
            printError("User '" + u2 + "' does not exist");
            return -1;
        }
        
        if (u1 == u2) {
            return 0;
        }
        
        unordered_map<string, int> dist;
        queue<string> q;
        
        for (const auto& p : userMap) {
            dist[p.first] = -1;
        }
        
        dist[u1] = 0;
        q.push(u1);
        
        while (!q.empty()) {
            string cur = q.front();
            q.pop();
            
            vector<User*> nb = userMap[cur]->getFriends();
            for (User* f : nb) {
                string name = f->getUsername();
                
                if (dist[name] == -1) {
                    dist[name] = dist[cur] + 1;
                    
                    if (name == u2) {
                        return dist[name];
                    }
                    
                    q.push(name);
                }
            }
        }
        
        
        return -1;
    }
    
    void addPost(string username, string content) {
        username = toLower(username);
        


        auto it = userMap.find(username);
        if (it == userMap.end()) {
            printError("User '" + username + "' does not exist");
            return;


        }
        
        if (content.empty()) {


            printError("Post content cannot be empty,invalid content");
            return;
        }
        
        it->second->addPost(content);
        printSuccess("Post is added '" + username + "'");
    }
    
    void outputPosts(string username, int N) {
        username = toLower(username);
        
        auto it = userMap.find(username);
        if (it == userMap.end()) {


            printError("User '" + username + "' does not exist");
            return;
        }
        
        if (N == 0) {
            return;
        }
        
        vector<string> posts = it->second->getRecentPosts(N);
        
        if (posts.empty()) {
            printInfo("User '" + username + "' has no posts yet");
            return;
        }
        
        cout << "\nPosts by '" << username << "':\n";
        for (size_t i = 0; i < posts.size(); i++) {
            cout << posts[i] << "\n";


        }
        cout << "\n";
    }
};

// ==============================
// Class: SocialNetSimulator (main driver function )
// ==============================
class SocialNetSimulator {
private:
    SocialGraph network;
    bool running;
    
    vector<string> parseCommand(string line) {
        vector<string> tokens;
        bool inQuotes = false;

        string currentToken = "";
        
        for (size_t i = 0; i < line.length(); i++) {
            char c = line[i];


            
            if (c == '"') {
                inQuotes = !inQuotes;
                if (!inQuotes && !currentToken.empty()) {


                    tokens.push_back(currentToken);
                    currentToken = "";
                }
            } else if (c == ' ' && !inQuotes) {
                if (!currentToken.empty()) {


                    tokens.push_back(currentToken);
                    currentToken = "";
                }
            } else {
                currentToken += c;
            }
        }
        
        if (!currentToken.empty()) {
            tokens.push_back(currentToken);
        }
        
        return tokens;
    }
    
    string toUpper(string str) {


        transform(str.begin(), str.end(), str.begin(), ::toupper);
        return str;
    }
    
    void processCommand(vector<string>& tokens) {
        if (tokens.empty()) {
            return;


        }
        
        string cmd = toUpper(tokens[0]);
        
        // System commands
        if (cmd == "HELP") {
            printHelp();
            return;
        }
        
        if (cmd == "CLEAR") {
            clearScreen();
            printBanner();
            return;
        }
        
        if (cmd == "EXIT" ) {
            running = false;

            cout << "\nThank you for using SocialNet Simulator!\n\n";
            cout << "2024CS10237, Shivanshu Aryan.";

            return;
        }
        
        // Network commands
        if (cmd == "ADD" && tokens.size() > 1) {
            string subcmd = toUpper(tokens[1]);
            if (subcmd == "USER" && tokens.size() >= 3) {
                network.addUser(tokens[2]);
            } else if (subcmd == "FRIEND" && tokens.size() >= 4) {
                network.addFriendship(tokens[2], tokens[3]);


            } else if (subcmd == "POST" && tokens.size() >= 4) {


                network.addPost(tokens[2], tokens[3]);
            } else {
                printError("Invalid ADD command. Type 'HELP' for usage");
            }
            return;
        }
        
        if (cmd == "LIST" && tokens.size() > 1) {
            string subcmd = toUpper(tokens[1]);
            if (subcmd == "FRIENDS" && tokens.size() >= 3) {
                network.listFriends(tokens[2]);
            } else {
                printError("Invalid LIST command. Type 'HELP' for usage");
            }
            return;
        }
        
        if (cmd == "SUGGEST" && tokens.size() > 1) {
            string subcmd = toUpper(tokens[1]);
            if (subcmd == "FRIENDS" && tokens.size() >= 4) {
                try {
                    int N = stoi(tokens[3]);
                    if (N < 0) {
                        printError("N must be non-negative");
                        return;
                    }
                    network.suggestFriends(tokens[2], N);
                } catch (...) {
                    printError("Invalid number format");
                }
            } else {
                printError("Invalid SUGGEST command. Type 'HELP' for usage");
            }
            return;
        }
        
        if (cmd == "DEGREES" && tokens.size() > 1) {
            string subcmd = toUpper(tokens[1]);
            if (subcmd == "OF" && tokens.size() >= 5 && toUpper(tokens[2]) == "SEPARATION") {
                int degrees = network.degreesOfSeparation(tokens[3], tokens[4]);
                if (degrees >= 0) {
                    cout << "\nDegrees of separation: " << degrees << "\n\n";
                } else {
                    printInfo("No connection found between users");
                }
            } else {
                printError("Invalid DEGREES command. Type 'HELP' for usage");
            }
            return;
        }
        
        if (cmd == "OUTPUT" && tokens.size() > 1) {
            string subcmd = toUpper(tokens[1]);
            if (subcmd == "POSTS" && tokens.size() >= 4) {
                
                    int N = stoi(tokens[3]);
                    network.outputPosts(tokens[2], N);
                }
            else {
                printError("Invalid OUTPUT command. Type 'HELP' for usage");
            }
            return;
        }
        
        // Unknown command
        printError("Unknown command '" + tokens[0] + "'. Type 'HELP' for usage");
    }
    
public:
    SocialNetSimulator(){
        running=true;
    }
    
    void run() {
        printWelcome();
        
        string line;
        while (running) {
            printPrompt();
            
            if (!getline(cin, line)) {
            
                break;
            }

            line.erase(0, line.find_first_not_of(" \t\n\r"));
            line.erase(line.find_last_not_of(" \t\n\r") + 1);
            
            if (line.empty()) continue;
            
            vector<string> tokens = parseCommand(line);
            processCommand(tokens);
        }
        
        if (running) {
            cout << "\nThank you for using SocialNet Simulator!\n\n";
            cout << "2024CS10237, Shivanshu Aryan.";
        }
    }
};


int main() {
    SocialNetSimulator simulator;
    simulator.run();
    return 0;
}